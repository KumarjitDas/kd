/**
 * @file kdGenMemOpsMoveRegion.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsMoveRegion function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsMoveRegion function test"
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
     * All failure cases should set moved_sz to 0 (if pointer valid)
     * and leave destination unchanged.
     */
    byte  dst[32];
    byte  src[32];
    byte  dst_orig[32];
    usize moved_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillVal(dst, USIZE_C(32), U8_C(0xAA));
    kdi_FillVal(dst_orig, USIZE_C(32), U8_C(0xAA));
    kdi_FillSeq(src, USIZE_C(32), U8_C(0x10));

    /* moved_sz pointer is null */
    result = GenMemOpsMoveRegion(dst, USIZE_C(32), null, src, USIZE_C(16));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* dst is null */
    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveRegion(null, USIZE_C(32), &moved_sz, src, USIZE_C(16));
    assert(result == RESULT_FAILURE);
    assert(moved_sz == USIZE_C(0));

    /* src is null */
    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveRegion(dst, USIZE_C(32), &moved_sz, null, USIZE_C(16));
    assert(result == RESULT_FAILURE);
    assert(moved_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* dst_sz is zero */
    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveRegion(dst, USIZE_C(0), &moved_sz, src, USIZE_C(16));
    assert(result == RESULT_FAILURE);
    assert(moved_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* src_sz is zero */
    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveRegion(dst, USIZE_C(32), &moved_sz, src, USIZE_C(0));
    assert(result == RESULT_FAILURE);
    assert(moved_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
ExactFitMove(void)
{
    /*
     * Source and destination are same size.
     * Should move all bytes, moved_sz equals src_sz and dst_sz.
     */
    byte  dst[16];
    byte  src[16];
    usize moved_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "ExactFitMove -> ");

    kdi_FillVal(dst, USIZE_C(16), U8_C(0x00));
    kdi_FillSeq(src, USIZE_C(16), U8_C(0x20));

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveRegion(dst, USIZE_C(16), &moved_sz, src, USIZE_C(16));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(16));
    assert(kdi_BytesEqual(dst, src, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
DstLargerThanSrc(void)
{
    /*
     * Destination is larger than source.
     * Should move all of src, moved_sz equals src_sz.
     * Remaining dst bytes should remain unchanged.
     */
    byte  dst[32];
    byte  dst_orig[32];
    byte  src[16];
    usize moved_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "DstLargerThanSrc -> ");

    kdi_FillVal(dst, USIZE_C(32), U8_C(0xFF));
    kdi_FillVal(dst_orig, USIZE_C(32), U8_C(0xFF));
    kdi_FillSeq(src, USIZE_C(16), U8_C(0x30));

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveRegion(dst, USIZE_C(32), &moved_sz, src, USIZE_C(16));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(16));
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
     * Should move only what fits in dst, moved_sz equals dst_sz.
     * Move is truncated.
     */
    byte  dst[10];
    byte  src[24];
    byte  expected[10];
    usize moved_sz;
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

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveRegion(dst, USIZE_C(10), &moved_sz, src, USIZE_C(24));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(10));
    assert(kdi_BytesEqual(dst, expected, USIZE_C(10)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SingleByteMove(void)
{
    /*
     * Minimal case: move 1 byte from 1-byte src to 1-byte dst.
     */
    byte  dst[1];
    byte  src[1];
    usize moved_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "SingleByteMove -> ");

    dst[0] = U8_C(0x00);
    src[0] = U8_C(0xAB);

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveRegion(dst, USIZE_C(1), &moved_sz, src, USIZE_C(1));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(1));
    assert(dst[0] == U8_C(0xAB));

    printf("PASSED\n");
}


void
LargeBuffersMove(void)
{
    /*
     * Large buffers: 256 bytes src to 256 bytes dst.
     */
    byte  dst[256];
    byte  src[256];
    usize moved_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "LargeBuffersMove -> ");

    kdi_FillVal(dst, USIZE_C(256), U8_C(0x00));
    kdi_FillSeq(src, USIZE_C(256), U8_C(0x00));

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveRegion(dst, USIZE_C(256), &moved_sz, src, USIZE_C(256));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(256));
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
    usize moved_sz;
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

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveRegion(dst, USIZE_C(100), &moved_sz, src, USIZE_C(200));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(100));
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
    usize moved_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "VerySmallSrcLargeDst -> ");

    kdi_FillVal(dst, USIZE_C(50), U8_C(0xEE));
    kdi_FillVal(dst_orig, USIZE_C(50), U8_C(0xEE));
    src[0] = U8_C(0x11);
    src[1] = U8_C(0x22);
    src[2] = U8_C(0x33);

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveRegion(dst, USIZE_C(50), &moved_sz, src, USIZE_C(3));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(3));
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
     * Should move only 1 byte.
     */
    byte  dst[1];
    byte  src[20];
    usize moved_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "DstSizeOne -> ");

    dst[0] = U8_C(0x00);
    kdi_FillSeq(src, USIZE_C(20), U8_C(0x50));

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveRegion(dst, USIZE_C(1), &moved_sz, src, USIZE_C(20));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(1));
    assert(dst[0] == src[0]);

    printf("PASSED\n");
}


void
SrcSizeOne(void)
{
    /*
     * Source is 1 byte, destination is larger.
     * Should move only 1 byte.
     */
    byte  dst[20];
    byte  dst_orig[20];
    byte  src[1];
    usize moved_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "SrcSizeOne -> ");

    kdi_FillVal(dst, USIZE_C(20), U8_C(0xDD));
    kdi_FillVal(dst_orig, USIZE_C(20), U8_C(0xDD));
    src[0] = U8_C(0x77);

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveRegion(dst, USIZE_C(20), &moved_sz, src, USIZE_C(1));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(1));
    assert(dst[0] == U8_C(0x77));
    /* Rest should be unchanged */
    assert(kdi_BytesEqual(dst + USIZE_C(1), dst_orig + USIZE_C(1), USIZE_C(19)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
OverlappingMoveForward(void)
{
    /*
     * Overlapping regions where dst and src are from same buffer.
     * dst > src: forward/right shift within single buffer.
     * buf: [0,1,2,3,4,5,6,7,8,9]
     * Move buf treated as src[0..4] to buf treated as dst[3..7]
     * Result: [0,1,2,0,1,2,3,4,8,9]
     */
    byte  buf[10];
    byte  expected[10];
    usize moved_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "OverlappingMoveForward -> ");

    kdi_FillSeq(buf, USIZE_C(10), U8_C(0x00));

    expected[0] = U8_C(0x00);
    expected[1] = U8_C(0x01);
    expected[2] = U8_C(0x02);
    expected[3] = U8_C(0x00);
    expected[4] = U8_C(0x01);
    expected[5] = U8_C(0x02);
    expected[6] = U8_C(0x03);
    expected[7] = U8_C(0x04);
    expected[8] = U8_C(0x08);
    expected[9] = U8_C(0x09);

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveRegion(buf + USIZE_C(3), USIZE_C(7), &moved_sz, buf, USIZE_C(5));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(5));
    assert(kdi_BytesEqual(buf, expected, USIZE_C(10)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
OverlappingMoveBackward(void)
{
    /*
     * Overlapping regions where dst and src are from same buffer.
     * dst < src: backward/left shift within single buffer.
     * buf: [0,1,2,3,4,5,6,7,8,9]
     * Move buf treated as src[3..7] to buf treated as dst[1..5]
     * Result: [0,3,4,5,6,7,6,7,8,9]
     */
    byte  buf[10];
    byte  expected[10];
    usize moved_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "OverlappingMoveBackward -> ");

    kdi_FillSeq(buf, USIZE_C(10), U8_C(0x00));

    expected[0] = U8_C(0x00);
    expected[1] = U8_C(0x03);
    expected[2] = U8_C(0x04);
    expected[3] = U8_C(0x05);
    expected[4] = U8_C(0x06);
    expected[5] = U8_C(0x07);
    expected[6] = U8_C(0x06);
    expected[7] = U8_C(0x07);
    expected[8] = U8_C(0x08);
    expected[9] = U8_C(0x09);

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveRegion(buf + USIZE_C(1), USIZE_C(9), &moved_sz, buf + USIZE_C(3), USIZE_C(5));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(5));
    assert(kdi_BytesEqual(buf, expected, USIZE_C(10)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
AllZerosMove(void)
{
    /*
     * Move buffer of all zeros.
     */
    byte  dst[16];
    byte  src[16];
    usize moved_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "AllZerosMove -> ");

    kdi_FillVal(src, USIZE_C(16), U8_C(0x00));
    kdi_FillVal(dst, USIZE_C(16), U8_C(0xFF));

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveRegion(dst, USIZE_C(16), &moved_sz, src, USIZE_C(16));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(16));
    assert(kdi_BytesEqual(dst, src, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
AllOnesMove(void)
{
    /*
     * Move buffer of all 0xFF bytes.
     */
    byte  dst[16];
    byte  src[16];
    usize moved_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "AllOnesMove -> ");

    kdi_FillVal(src, USIZE_C(16), U8_C(0xFF));
    kdi_FillVal(dst, USIZE_C(16), U8_C(0x00));

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveRegion(dst, USIZE_C(16), &moved_sz, src, USIZE_C(16));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(16));
    assert(kdi_BytesEqual(dst, src, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
AlternatingPatternMove(void)
{
    /*
     * Verify data integrity with alternating byte pattern.
     */
    byte  dst[32];
    byte  src[32];
    usize moved_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "AlternatingPatternMove -> ");

    kdi_FillVal(dst, USIZE_C(32), U8_C(0x00));

    /* Create alternating pattern in src */
    for (i = USIZE_C(0); i < USIZE_C(32); ++i)
    {
        src[i] = (i & USIZE_C(1)) ? U8_C(0xAA) : U8_C(0x55);
    }

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveRegion(dst, USIZE_C(32), &moved_sz, src, USIZE_C(32));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(32));
    assert(kdi_BytesEqual(dst, src, USIZE_C(32)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    ExactFitMove();
    DstLargerThanSrc();
    SrcLargerThanDst();
    SingleByteMove();
    LargeBuffersMove();
    LargeBuffersTruncated();
    VerySmallSrcLargeDst();
    DstSizeOne();
    SrcSizeOne();
    OverlappingMoveForward();
    OverlappingMoveBackward();
    AllZerosMove();
    AllOnesMove();
    AlternatingPatternMove();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}