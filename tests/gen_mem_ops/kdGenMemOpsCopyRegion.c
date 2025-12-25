/**
 * @file kdGenMemOpsCopyRegion.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsCopyRegion function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsCopyRegion function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


static bool
kdi_BytesEqual(const byte *a, const byte *b, usize sz)
{
    usize i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        if (a[i] != b[i])
        {
            return RESULT_FAILURE;
        }
    }

    return RESULT_SUCCESS;
}


static void
kdi_FillSeq(byte *dst, usize sz, byte start)
{
    usize i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        dst[i] = (byte)(start + (byte)i);
    }
}


static void
kdi_FillVal(byte *dst, usize sz, byte val)
{
    usize i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        dst[i] = val;
    }
}


void
BasicArguments(void)
{
    /*
     * Test NULL pointer validation and zero-size parameters.
     * All failure cases should set copied_sz to 0 (if pointer valid)
     * and leave destination unchanged.
     */
    byte  dst[32];
    byte  src[32];
    byte  dst_orig[32];
    usize copied_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillVal(dst, USIZE_C(32), U8_C(0xAA));
    kdi_FillVal(dst_orig, USIZE_C(32), U8_C(0xAA));
    kdi_FillSeq(src, USIZE_C(32), U8_C(0x10));

    /* copied_sz pointer is null */
    result = GenMemOpsCopyRegion(dst, USIZE_C(32), null, src, USIZE_C(16));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* dst is null */
    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyRegion(null, USIZE_C(32), &copied_sz, src, USIZE_C(16));
    assert(result == RESULT_FAILURE);
    assert(copied_sz == USIZE_C(0));

    /* src is null */
    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyRegion(dst, USIZE_C(32), &copied_sz, null, USIZE_C(16));
    assert(result == RESULT_FAILURE);
    assert(copied_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* dst_sz is zero */
    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyRegion(dst, USIZE_C(0), &copied_sz, src, USIZE_C(16));
    assert(result == RESULT_FAILURE);
    assert(copied_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* src_sz is zero */
    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyRegion(dst, USIZE_C(32), &copied_sz, src, USIZE_C(0));
    assert(result == RESULT_FAILURE);
    assert(copied_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
ExactFitCopy(void)
{
    /*
     * Source and destination are same size.
     * Should copy all bytes, copied_sz equals src_sz and dst_sz.
     */
    byte  dst[16];
    byte  src[16];
    usize copied_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "ExactFitCopy -> ");

    kdi_FillVal(dst, USIZE_C(16), U8_C(0x00));
    kdi_FillSeq(src, USIZE_C(16), U8_C(0x20));

    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyRegion(dst, USIZE_C(16), &copied_sz, src, USIZE_C(16));

    assert(result == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(16));
    assert(kdi_BytesEqual(dst, src, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
DstLargerThanSrc(void)
{
    /*
     * Destination is larger than source.
     * Should copy all of src, copied_sz equals src_sz.
     * Remaining dst bytes should remain unchanged.
     */
    byte  dst[32];
    byte  dst_orig[32];
    byte  src[16];
    usize copied_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "DstLargerThanSrc -> ");

    kdi_FillVal(dst, USIZE_C(32), U8_C(0xFF));
    kdi_FillVal(dst_orig, USIZE_C(32), U8_C(0xFF));
    kdi_FillSeq(src, USIZE_C(16), U8_C(0x30));

    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyRegion(dst, USIZE_C(32), &copied_sz, src, USIZE_C(16));

    assert(result == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(16));
    assert(kdi_BytesEqual(dst, src, USIZE_C(16)) == RESULT_SUCCESS);
    /* Tail of dst (16..31) should remain unchanged */
    assert(kdi_BytesEqual(dst + USIZE_C(16), dst_orig + USIZE_C(16), USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SrcLargerThanDst(void)
{
    /*
     * Source is larger than destination.
     * Should copy only what fits in dst, copied_sz equals dst_sz.
     * Copy is truncated.
     */
    byte  dst[10];
    byte  src[24];
    byte  expected[10];
    usize copied_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "SrcLargerThanDst -> ");

    kdi_FillVal(dst, USIZE_C(10), U8_C(0x00));
    kdi_FillSeq(src, USIZE_C(24), U8_C(0x40));

    /* Expected: first 10 bytes of src */
    for (i = USIZE_C(0); i < USIZE_C(10); ++i)
    {
        expected[i] = src[i];
    }

    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyRegion(dst, USIZE_C(10), &copied_sz, src, USIZE_C(24));

    assert(result == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(10));
    assert(kdi_BytesEqual(dst, expected, USIZE_C(10)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SingleByteCopy(void)
{
    /*
     * Minimal case: copy 1 byte from 1-byte src to 1-byte dst.
     */
    byte  dst[1];
    byte  src[1];
    usize copied_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "SingleByteCopy -> ");

    dst[0] = U8_C(0x00);
    src[0] = U8_C(0xAB);

    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyRegion(dst, USIZE_C(1), &copied_sz, src, USIZE_C(1));

    assert(result == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(1));
    assert(dst[0] == U8_C(0xAB));

    printf("PASSED\n");
}


void
LargeBuffersCopy(void)
{
    /*
     * Large buffers: 256 bytes src to 256 bytes dst.
     */
    byte  dst[256];
    byte  src[256];
    usize copied_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "LargeBuffersCopy -> ");

    kdi_FillVal(dst, USIZE_C(256), U8_C(0x00));
    kdi_FillSeq(src, USIZE_C(256), U8_C(0x00));

    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyRegion(dst, USIZE_C(256), &copied_sz, src, USIZE_C(256));

    assert(result == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(256));
    assert(kdi_BytesEqual(dst, src, USIZE_C(256)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
LargeBuffersTruncated(void)
{
    /*
     * Large source (200 bytes) truncated to smaller dst (100 bytes).
     */
    byte  dst[100];
    byte  src[200];
    byte  expected[100];
    usize copied_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffersTruncated -> ");

    kdi_FillVal(dst, USIZE_C(100), U8_C(0x00));
    kdi_FillSeq(src, USIZE_C(200), U8_C(0x01));

    /* Expected: first 100 bytes of src */
    for (i = USIZE_C(0); i < USIZE_C(100); ++i)
    {
        expected[i] = src[i];
    }

    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyRegion(dst, USIZE_C(100), &copied_sz, src, USIZE_C(200));

    assert(result == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(100));
    assert(kdi_BytesEqual(dst, expected, USIZE_C(100)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
VerySmallSrcLargeDst(void)
{
    /*
     * Very small source (3 bytes) into large destination (50 bytes).
     */
    byte  dst[50];
    byte  dst_orig[50];
    byte  src[3];
    usize copied_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "VerySmallSrcLargeDst -> ");

    kdi_FillVal(dst, USIZE_C(50), U8_C(0xEE));
    kdi_FillVal(dst_orig, USIZE_C(50), U8_C(0xEE));
    src[0] = U8_C(0x11);
    src[1] = U8_C(0x22);
    src[2] = U8_C(0x33);

    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyRegion(dst, USIZE_C(50), &copied_sz, src, USIZE_C(3));

    assert(result == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(3));
    assert(dst[0] == U8_C(0x11));
    assert(dst[1] == U8_C(0x22));
    assert(dst[2] == U8_C(0x33));
    /* Remainder should be unchanged */
    assert(kdi_BytesEqual(dst + USIZE_C(3), dst_orig + USIZE_C(3), USIZE_C(47)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
DstSizeOne(void)
{
    /*
     * Destination is 1 byte, source is larger.
     * Should copy only 1 byte.
     */
    byte  dst[1];
    byte  src[20];
    usize copied_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "DstSizeOne -> ");

    dst[0] = U8_C(0x00);
    kdi_FillSeq(src, USIZE_C(20), U8_C(0x50));

    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyRegion(dst, USIZE_C(1), &copied_sz, src, USIZE_C(20));

    assert(result == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(1));
    assert(dst[0] == src[0]);

    printf("PASSED\n");
}


void
SrcSizeOne(void)
{
    /*
     * Source is 1 byte, destination is larger.
     * Should copy only 1 byte.
     */
    byte  dst[20];
    byte  dst_orig[20];
    byte  src[1];
    usize copied_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "SrcSizeOne -> ");

    kdi_FillVal(dst, USIZE_C(20), U8_C(0xDD));
    kdi_FillVal(dst_orig, USIZE_C(20), U8_C(0xDD));
    src[0] = U8_C(0x77);

    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyRegion(dst, USIZE_C(20), &copied_sz, src, USIZE_C(1));

    assert(result == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(1));
    assert(dst[0] == U8_C(0x77));
    /* Rest should be unchanged */
    assert(kdi_BytesEqual(dst + USIZE_C(1), dst_orig + USIZE_C(1), USIZE_C(19)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
AlternatingPatternCopy(void)
{
    /*
     * Verify data integrity with alternating byte pattern.
     */
    byte  dst[32];
    byte  src[32];
    usize copied_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "AlternatingPatternCopy -> ");

    kdi_FillVal(dst, USIZE_C(32), U8_C(0x00));

    /* Create alternating pattern in src */
    for (i = USIZE_C(0); i < USIZE_C(32); ++i)
    {
        src[i] = (i & USIZE_C(1)) ? U8_C(0xAA) : U8_C(0x55);
    }

    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyRegion(dst, USIZE_C(32), &copied_sz, src, USIZE_C(32));

    assert(result == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(32));
    assert(kdi_BytesEqual(dst, src, USIZE_C(32)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
AllZerosCopy(void)
{
    /*
     * Copy buffer of all zeros.
     */
    byte  dst[16];
    byte  src[16];
    usize copied_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "AllZerosCopy -> ");

    kdi_FillVal(dst, USIZE_C(16), U8_C(0xFF));
    kdi_FillVal(src, USIZE_C(16), U8_C(0x00));

    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyRegion(dst, USIZE_C(16), &copied_sz, src, USIZE_C(16));

    assert(result == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(16));
    assert(kdi_BytesEqual(dst, src, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
AllOnesCopy(void)
{
    /*
     * Copy buffer of all 0xFF bytes.
     */
    byte  dst[16];
    byte  src[16];
    usize copied_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "AllOnesCopy -> ");

    kdi_FillVal(dst, USIZE_C(16), U8_C(0x00));
    kdi_FillVal(src, USIZE_C(16), U8_C(0xFF));

    copied_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsCopyRegion(dst, USIZE_C(16), &copied_sz, src, USIZE_C(16));

    assert(result == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(16));
    assert(kdi_BytesEqual(dst, src, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    ExactFitCopy();
    DstLargerThanSrc();
    SrcLargerThanDst();
    SingleByteCopy();
    LargeBuffersCopy();
    LargeBuffersTruncated();
    VerySmallSrcLargeDst();
    DstSizeOne();
    SrcSizeOne();
    AlternatingPatternCopy();
    AllZerosCopy();
    AllOnesCopy();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}