/**
 * @file kdGenMemOpsCopy.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsCopy function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsCopy function test"
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
     * Test NULL pointer validation and zero-size parameter.
     * Failures should not modify destination.
     */
    byte src[8];
    byte dst[8];
    byte dst_orig[8];
    bool result;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillSeq(src, USIZE_C(8), U8_C(0x10));
    kdi_FillVal(dst, USIZE_C(8), U8_C(0xAA));
    kdi_FillVal(dst_orig, USIZE_C(8), U8_C(0xAA));

    /* dst is null */
    result = GenMemOpsCopy(null, src, USIZE_C(8));
    assert(result == RESULT_FAILURE);

    /* src is null */
    result = GenMemOpsCopy(dst, null, USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(8)) == RESULT_SUCCESS);

    /* sz is zero */
    result = GenMemOpsCopy(dst, src, USIZE_C(0));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(8)) == RESULT_SUCCESS);

    /* Valid arguments */
    result = GenMemOpsCopy(dst, src, USIZE_C(8));
    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, src, USIZE_C(8)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SingleByteCopy(void)
{
    /*
     * Minimal case: copy exactly 1 byte.
     */
    byte src[1];
    byte dst[1];
    bool result;

    printf(LOG_PREFIX_CSTR "SingleByteCopy -> ");

    src[0] = U8_C(0x42);
    dst[0] = U8_C(0x00);

    result = GenMemOpsCopy(dst, src, USIZE_C(1));

    assert(result == RESULT_SUCCESS);
    assert(dst[0] == U8_C(0x42));

    printf("PASSED\n");
}


void
SmallBufferCopy(void)
{
    /*
     * Copy a small 8-byte buffer.
     */
    byte  src[8];
    byte  dst[8];
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "SmallBufferCopy -> ");

    kdi_FillSeq(src, USIZE_C(8), U8_C(0x20));
    kdi_FillVal(dst, USIZE_C(8), U8_C(0x00));

    result = GenMemOpsCopy(dst, src, USIZE_C(8));

    assert(result == RESULT_SUCCESS);
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        assert(dst[i] == src[i]);
    }

    printf("PASSED\n");
}


void
MediumBufferCopy(void)
{
    /*
     * Copy a 64-byte buffer.
     */
    byte src[64];
    byte dst[64];
    bool result;

    printf(LOG_PREFIX_CSTR "MediumBufferCopy -> ");

    kdi_FillSeq(src, USIZE_C(64), U8_C(0x00));
    kdi_FillVal(dst, USIZE_C(64), U8_C(0xFF));

    result = GenMemOpsCopy(dst, src, USIZE_C(64));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, src, USIZE_C(64)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
LargeBufferCopy(void)
{
    /*
     * Copy a large 256-byte buffer.
     */
    byte src[256];
    byte dst[256];
    bool result;

    printf(LOG_PREFIX_CSTR "LargeBufferCopy -> ");

    kdi_FillSeq(src, USIZE_C(256), U8_C(0x00));
    kdi_FillVal(dst, USIZE_C(256), U8_C(0x00));

    result = GenMemOpsCopy(dst, src, USIZE_C(256));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, src, USIZE_C(256)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
VeryLargeBufferCopy(void)
{
    /*
     * Copy a very large 1024-byte buffer.
     */
    byte src[1024];
    byte dst[1024];
    bool result;

    printf(LOG_PREFIX_CSTR "VeryLargeBufferCopy -> ");

    kdi_FillSeq(src, USIZE_C(1024), U8_C(0x00));
    kdi_FillVal(dst, USIZE_C(1024), U8_C(0xAA));

    result = GenMemOpsCopy(dst, src, USIZE_C(1024));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, src, USIZE_C(1024)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
CopyWithPointerArithmetic(void)
{
    /*
     * Copy using pointer arithmetic to access sub-regions.
     * Demonstrates copying from/to middle of buffers.
     */
    byte  src[32];
    byte  dst[32];
    byte  dst_orig[32];
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "CopyWithPointerArithmetic -> ");

    kdi_FillSeq(src, USIZE_C(32), U8_C(0x10));
    kdi_FillVal(dst, USIZE_C(32), U8_C(0xFF));
    kdi_FillVal(dst_orig, USIZE_C(32), U8_C(0xFF));

    /* Copy src[5..14] (10 bytes) to dst[10..19] */
    result = GenMemOpsCopy(dst + USIZE_C(10), src + USIZE_C(5), USIZE_C(10));

    assert(result == RESULT_SUCCESS);

    /* Head of dst (0..9) should remain unchanged */
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(10)) == RESULT_SUCCESS);

    /* Middle of dst (10..19) should match src[5..14] */
    for (i = USIZE_C(0); i < USIZE_C(10); ++i)
    {
        assert(dst[USIZE_C(10) + i] == src[USIZE_C(5) + i]);
    }

    /* Tail of dst (20..31) should remain unchanged */
    assert(kdi_BytesEqual(dst + USIZE_C(20), dst_orig + USIZE_C(20), USIZE_C(12)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SelfCopyIdenticalPointers(void)
{
    /*
     * Copy where dst and src point to the same location.
     * Should succeed (idempotent operation).
     */
    byte  buf[16];
    byte  buf_orig[16];
    bool  result;

    printf(LOG_PREFIX_CSTR "SelfCopyIdenticalPointers -> ");

    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x30));
    kdi_FillSeq(buf_orig, USIZE_C(16), U8_C(0x30));

    result = GenMemOpsCopy(buf, buf, USIZE_C(16));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
AllZerosCopy(void)
{
    /*
     * Copy buffer containing all zero bytes.
     */
    byte src[16];
    byte dst[16];
    bool result;

    printf(LOG_PREFIX_CSTR "AllZerosCopy -> ");

    kdi_FillVal(src, USIZE_C(16), U8_C(0x00));
    kdi_FillVal(dst, USIZE_C(16), U8_C(0xFF));

    result = GenMemOpsCopy(dst, src, USIZE_C(16));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, src, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
AllOnesCopy(void)
{
    /*
     * Copy buffer containing all 0xFF bytes.
     */
    byte src[16];
    byte dst[16];
    bool result;

    printf(LOG_PREFIX_CSTR "AllOnesCopy -> ");

    kdi_FillVal(src, USIZE_C(16), U8_C(0xFF));
    kdi_FillVal(dst, USIZE_C(16), U8_C(0x00));

    result = GenMemOpsCopy(dst, src, USIZE_C(16));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, src, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
AlternatingPatternCopy(void)
{
    /*
     * Copy buffer with alternating byte pattern (0xAA, 0x55, 0xAA, 0x55...).
     */
    byte  src[32];
    byte  dst[32];
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "AlternatingPatternCopy -> ");

    kdi_FillVal(dst, USIZE_C(32), U8_C(0x00));

    /* Create alternating pattern */
    for (i = USIZE_C(0); i < USIZE_C(32); ++i)
    {
        src[i] = (i & USIZE_C(1)) ? U8_C(0x55) : U8_C(0xAA);
    }

    result = GenMemOpsCopy(dst, src, USIZE_C(32));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, src, USIZE_C(32)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SequentialPatternCopy(void)
{
    /*
     * Copy buffer with sequential incrementing bytes.
     */
    byte src[100];
    byte dst[100];
    bool result;

    printf(LOG_PREFIX_CSTR "SequentialPatternCopy -> ");

    kdi_FillSeq(src, USIZE_C(100), U8_C(0x00));
    kdi_FillVal(dst, USIZE_C(100), U8_C(0xFF));

    result = GenMemOpsCopy(dst, src, USIZE_C(100));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, src, USIZE_C(100)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
OddSizeCopy(void)
{
    /*
     * Copy buffers with odd sizes (not power of 2).
     */
    byte src[17];
    byte dst[17];
    bool result;

    printf(LOG_PREFIX_CSTR "OddSizeCopy -> ");

    kdi_FillSeq(src, USIZE_C(17), U8_C(0x40));
    kdi_FillVal(dst, USIZE_C(17), U8_C(0x00));

    result = GenMemOpsCopy(dst, src, USIZE_C(17));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, src, USIZE_C(17)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
PrimeNumberSizeCopy(void)
{
    /*
     * Copy buffers with prime number size (37 bytes).
     */
    byte src[37];
    byte dst[37];
    bool result;

    printf(LOG_PREFIX_CSTR "PrimeNumberSizeCopy -> ");

    kdi_FillSeq(src, USIZE_C(37), U8_C(0x50));
    kdi_FillVal(dst, USIZE_C(37), U8_C(0x00));

    result = GenMemOpsCopy(dst, src, USIZE_C(37));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, src, USIZE_C(37)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
CopyOverwritesPreviousData(void)
{
    /*
     * Verify that copy completely overwrites destination data.
     */
    byte  src[8];
    byte  dst[8];
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "CopyOverwritesPreviousData -> ");

    kdi_FillSeq(src, USIZE_C(8), U8_C(0x00));

    /* Fill dst with distinct pattern */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        dst[i] = U8_C(0xCC);
    }

    result = GenMemOpsCopy(dst, src, USIZE_C(8));

    assert(result == RESULT_SUCCESS);

    /* Verify all bytes match src, none of old 0xCC pattern remains */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        assert(dst[i] == src[i]);
        assert(dst[i] != U8_C(0xCC));
    }

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    SingleByteCopy();
    SmallBufferCopy();
    MediumBufferCopy();
    LargeBufferCopy();
    VeryLargeBufferCopy();
    CopyWithPointerArithmetic();
    SelfCopyIdenticalPointers();
    AllZerosCopy();
    AllOnesCopy();
    AlternatingPatternCopy();
    SequentialPatternCopy();
    OddSizeCopy();
    PrimeNumberSizeCopy();
    CopyOverwritesPreviousData();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}