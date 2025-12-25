/**
 * @file kdGenMemOpsMoveBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsMoveBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsMoveBound function test"
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
     * Test NULL pointer validation, zero-size parameters, and out-of-bounds indices.
     * All failure cases should set moved_sz to 0 (if pointer valid)
     * and leave destination unchanged.
     */
    byte  dst[64];
    byte  src[64];
    byte  dst_orig[64];
    usize moved_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillVal(dst, USIZE_C(64), U8_C(0xAA));
    kdi_FillVal(dst_orig, USIZE_C(64), U8_C(0xAA));
    kdi_FillSeq(src, USIZE_C(64), U8_C(0x10));

    /* moved_sz pointer is null */
    result = GenMemOpsMoveBound(dst, USIZE_C(64), null, src, USIZE_C(64), USIZE_C(0), USIZE_C(0), USIZE_C(16));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* dst_base is null */
    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveBound(null, USIZE_C(64), &moved_sz, src, USIZE_C(64), USIZE_C(0), USIZE_C(0), USIZE_C(16));
    assert(result == RESULT_FAILURE);
    assert(moved_sz == USIZE_C(0));

    /* src_base is null */
    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveBound(dst, USIZE_C(64), &moved_sz, null, USIZE_C(64), USIZE_C(0), USIZE_C(0), USIZE_C(16));
    assert(result == RESULT_FAILURE);
    assert(moved_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* dst_idx out of bounds (equals dst_base_sz) */
    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveBound(dst, USIZE_C(64), &moved_sz, src, USIZE_C(64), USIZE_C(64), USIZE_C(0), USIZE_C(16));
    assert(result == RESULT_FAILURE);
    assert(moved_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* dst_idx out of bounds (greater than dst_base_sz) */
    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveBound(dst, USIZE_C(64), &moved_sz, src, USIZE_C(64), USIZE_C(100), USIZE_C(0), USIZE_C(16));
    assert(result == RESULT_FAILURE);
    assert(moved_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* src_idx out of bounds (equals src_base_sz) */
    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveBound(dst, USIZE_C(64), &moved_sz, src, USIZE_C(64), USIZE_C(0), USIZE_C(64), USIZE_C(16));
    assert(result == RESULT_FAILURE);
    assert(moved_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* src_idx out of bounds (greater than src_base_sz) */
    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveBound(dst, USIZE_C(64), &moved_sz, src, USIZE_C(64), USIZE_C(0), USIZE_C(100), USIZE_C(16));
    assert(result == RESULT_FAILURE);
    assert(moved_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* byte_count is zero */
    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveBound(dst, USIZE_C(64), &moved_sz, src, USIZE_C(64), USIZE_C(0), USIZE_C(0), USIZE_C(0));
    assert(result == RESULT_FAILURE);
    assert(moved_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(64)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
ExactMoveWithinBounds(void)
{
    /*
     * Move src[10..25] (16 bytes) to dst[5..20] (16 bytes).
     * Both regions fit exactly, no truncation.
     */
    byte  dst[32];
    byte  dst_orig[32];
    byte  src[40];
    usize moved_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "ExactMoveWithinBounds -> ");

    kdi_FillVal(dst, USIZE_C(32), U8_C(0xFF));
    kdi_FillVal(dst_orig, USIZE_C(32), U8_C(0xFF));
    kdi_FillSeq(src, USIZE_C(40), U8_C(0x00));

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveBound(dst, USIZE_C(32), &moved_sz, src, USIZE_C(40), USIZE_C(5), USIZE_C(10), USIZE_C(16));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(16));

    /* Head of dst (0..4) should remain unchanged */
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(5)) == RESULT_SUCCESS);

    /* Middle of dst (5..20) should contain src[10..25] */
    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        assert(dst[USIZE_C(5) + i] == src[USIZE_C(10) + i]);
    }

    /* Tail of dst (21..31) should remain unchanged */
    assert(kdi_BytesEqual(dst + USIZE_C(21), dst_orig + USIZE_C(21), USIZE_C(11)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
MoveAtStartOfBothBuffers(void)
{
    /*
     * Move src[0..15] to dst[0..15].
     * Both starting at index 0.
     */
    byte  dst[32];
    byte  dst_orig[32];
    byte  src[32];
    usize moved_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "MoveAtStartOfBothBuffers -> ");

    kdi_FillVal(dst, USIZE_C(32), U8_C(0xEE));
    kdi_FillVal(dst_orig, USIZE_C(32), U8_C(0xEE));
    kdi_FillSeq(src, USIZE_C(32), U8_C(0x20));

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveBound(dst, USIZE_C(32), &moved_sz, src, USIZE_C(32), USIZE_C(0), USIZE_C(0), USIZE_C(16));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(16));

    /* First 16 bytes should be moved */
    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        assert(dst[i] == src[i]);
    }

    /* Remaining bytes should be unchanged */
    assert(kdi_BytesEqual(dst + USIZE_C(16), dst_orig + USIZE_C(16), USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
TruncationDueToDstSpace(void)
{
    /*
     * Request to move 20 bytes starting at dst_idx=50 into dst of size 60.
     * Only 10 bytes available, so moved_sz should be 10.
     */
    byte  dst[60];
    byte  src[40];
    usize moved_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "TruncationDueToDstSpace -> ");

    kdi_FillVal(dst, USIZE_C(60), U8_C(0x00));
    kdi_FillSeq(src, USIZE_C(40), U8_C(0x40));

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveBound(dst, USIZE_C(60), &moved_sz, src, USIZE_C(40), USIZE_C(50), USIZE_C(0), USIZE_C(20));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(10));

    /* dst[50..59] should contain src[0..9] */
    for (i = USIZE_C(0); i < USIZE_C(10); ++i)
    {
        assert(dst[USIZE_C(50) + i] == src[i]);
    }

    printf("PASSED\n");
}


void
TruncationDueToSrcSpace(void)
{
    /*
     * Request to move 20 bytes starting at src_idx=25 from src of size 30.
     * Only 5 bytes available in src, so moved_sz should be 5.
     */
    byte  dst[40];
    byte  src[30];
    usize moved_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "TruncationDueToSrcSpace -> ");

    kdi_FillVal(dst, USIZE_C(40), U8_C(0x00));
    kdi_FillSeq(src, USIZE_C(30), U8_C(0x50));

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveBound(dst, USIZE_C(40), &moved_sz, src, USIZE_C(30), USIZE_C(0), USIZE_C(25), USIZE_C(20));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(5));

    /* dst[0..4] should contain src[25..29] */
    for (i = USIZE_C(0); i < USIZE_C(5); ++i)
    {
        assert(dst[i] == src[USIZE_C(25) + i]);
    }

    printf("PASSED\n");
}


void
TruncationDueToBothLimits(void)
{
    /*
     * Request 30 bytes, but dst has 10 available and src has 15 available.
     * Should move min(30, 10, 15) = 10 bytes.
     */
    byte  dst[25];
    byte  src[35];
    usize moved_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "TruncationDueToBothLimits -> ");

    kdi_FillVal(dst, USIZE_C(25), U8_C(0x00));
    kdi_FillSeq(src, USIZE_C(35), U8_C(0x60));

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveBound(dst, USIZE_C(25), &moved_sz, src, USIZE_C(35), USIZE_C(15), USIZE_C(20), USIZE_C(30));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(10));

    /* dst[15..24] should contain src[20..29] */
    for (i = USIZE_C(0); i < USIZE_C(10); ++i)
    {
        assert(dst[USIZE_C(15) + i] == src[USIZE_C(20) + i]);
    }

    printf("PASSED\n");
}


void
SingleByteMove(void)
{
    /*
     * Minimal case: move 1 byte from specific offset to specific offset.
     */
    byte  dst[10];
    byte  src[10];
    usize moved_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "SingleByteMove -> ");

    kdi_FillVal(dst, USIZE_C(10), U8_C(0xFF));
    kdi_FillSeq(src, USIZE_C(10), U8_C(0x70));

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveBound(dst, USIZE_C(10), &moved_sz, src, USIZE_C(10), USIZE_C(5), USIZE_C(3), USIZE_C(1));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(1));
    assert(dst[5] == src[3]);

    printf("PASSED\n");
}


void
MoveToEndOfDst(void)
{
    /*
     * Move to the very last byte(s) of destination.
     */
    byte  dst[20];
    byte  src[20];
    usize moved_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "MoveToEndOfDst -> ");

    kdi_FillVal(dst, USIZE_C(20), U8_C(0x00));
    kdi_FillSeq(src, USIZE_C(20), U8_C(0x80));

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveBound(dst, USIZE_C(20), &moved_sz, src, USIZE_C(20), USIZE_C(15), USIZE_C(0), USIZE_C(5));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(5));

    /* dst[15..19] should contain src[0..4] */
    for (i = USIZE_C(0); i < USIZE_C(5); ++i)
    {
        assert(dst[USIZE_C(15) + i] == src[i]);
    }

    printf("PASSED\n");
}


void
MoveFromEndOfSrc(void)
{
    /*
     * Move from the very last byte(s) of source.
     */
    byte  dst[20];
    byte  src[20];
    usize moved_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "MoveFromEndOfSrc -> ");

    kdi_FillVal(dst, USIZE_C(20), U8_C(0x00));
    kdi_FillSeq(src, USIZE_C(20), U8_C(0x90));

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveBound(dst, USIZE_C(20), &moved_sz, src, USIZE_C(20), USIZE_C(0), USIZE_C(15), USIZE_C(5));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(5));

    /* dst[0..4] should contain src[15..19] */
    for (i = USIZE_C(0); i < USIZE_C(5); ++i)
    {
        assert(dst[i] == src[USIZE_C(15) + i]);
    }

    printf("PASSED\n");
}


void
LargeBuffersWithOffsets(void)
{
    /*
     * Large buffers with various offsets.
     */
    byte  dst[256];
    byte  src[256];
    usize moved_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffersWithOffsets -> ");

    kdi_FillVal(dst, USIZE_C(256), U8_C(0x00));
    kdi_FillSeq(src, USIZE_C(256), U8_C(0x00));

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveBound(dst, USIZE_C(256), &moved_sz, src, USIZE_C(256), USIZE_C(50), USIZE_C(100), USIZE_C(80));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(80));

    /* dst[50..129] should contain src[100..179] */
    for (i = USIZE_C(0); i < USIZE_C(80); ++i)
    {
        assert(dst[USIZE_C(50) + i] == src[USIZE_C(100) + i]);
    }

    printf("PASSED\n");
}


void
OverlappingMoveForward(void)
{
    /*
     * Overlapping regions within same buffer where dst_idx > src_idx.
     * buf: [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
     * Move buf[2..9] to buf[5..12]
     * Result: [0,1,2,3,4,2,3,4,5,6,7,8,12,13,14,15]
     */
    byte  buf[16];
    byte  expected[16];
    usize moved_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "OverlappingMoveForward -> ");

    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    expected[0]  = U8_C(0x00);
    expected[1]  = U8_C(0x01);
    expected[2]  = U8_C(0x02);
    expected[3]  = U8_C(0x03);
    expected[4]  = U8_C(0x04);
    expected[5]  = U8_C(0x02);
    expected[6]  = U8_C(0x03);
    expected[7]  = U8_C(0x04);
    expected[8]  = U8_C(0x05);
    expected[9]  = U8_C(0x06);
    expected[10] = U8_C(0x07);
    expected[11] = U8_C(0x08);
    expected[12] = U8_C(0x09);
    expected[13] = U8_C(0x0D);
    expected[14] = U8_C(0x0E);
    expected[15] = U8_C(0x0F);

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveBound(buf, USIZE_C(16), &moved_sz, buf, USIZE_C(16), USIZE_C(5), USIZE_C(2), USIZE_C(8));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(8));
    assert(kdi_BytesEqual(buf, expected, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
OverlappingMoveBackward(void)
{
    /*
     * Overlapping regions within same buffer where dst_idx < src_idx.
     * buf: [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
     * Move buf[5..12] to buf[2..9]
     * Result: [0,1,5,6,7,8,9,10,11,12,8,9,10,11,14,15]
     */
    byte  buf[16];
    byte  expected[16];
    usize moved_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "OverlappingMoveBackward -> ");

    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    expected[0]  = U8_C(0x00);
    expected[1]  = U8_C(0x01);
    expected[2]  = U8_C(0x05);
    expected[3]  = U8_C(0x06);
    expected[4]  = U8_C(0x07);
    expected[5]  = U8_C(0x08);
    expected[6]  = U8_C(0x09);
    expected[7]  = U8_C(0x0A);
    expected[8]  = U8_C(0x0B);
    expected[9]  = U8_C(0x0C);
    expected[10] = U8_C(0x0A);
    expected[11] = U8_C(0x0B);
    expected[12] = U8_C(0x0C);
    expected[13] = U8_C(0x0D);
    expected[14] = U8_C(0x0E);
    expected[15] = U8_C(0x0F);

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveBound(buf, USIZE_C(16), &moved_sz, buf, USIZE_C(16), USIZE_C(2), USIZE_C(5), USIZE_C(8));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(8));
    assert(kdi_BytesEqual(buf, expected, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
DstOnlyOneByteAvailable(void)
{
    /*
     * Destination has only 1 byte available from dst_idx.
     * Request more, but should move only 1.
     */
    byte  dst[16];
    byte  src[16];
    usize moved_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "DstOnlyOneByteAvailable -> ");

    kdi_FillVal(dst, USIZE_C(16), U8_C(0xCC));
    kdi_FillSeq(src, USIZE_C(16), U8_C(0xA0));

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveBound(dst, USIZE_C(16), &moved_sz, src, USIZE_C(16), USIZE_C(15), USIZE_C(0), USIZE_C(10));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(1));
    assert(dst[15] == src[0]);

    printf("PASSED\n");
}


void
SrcOnlyOneByteAvailable(void)
{
    /*
     * Source has only 1 byte available from src_idx.
     * Request more, but should move only 1.
     */
    byte  dst[16];
    byte  src[16];
    usize moved_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "SrcOnlyOneByteAvailable -> ");

    kdi_FillVal(dst, USIZE_C(16), U8_C(0x00));
    kdi_FillSeq(src, USIZE_C(16), U8_C(0xB0));

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveBound(dst, USIZE_C(16), &moved_sz, src, USIZE_C(16), USIZE_C(0), USIZE_C(15), USIZE_C(10));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(1));
    assert(dst[0] == src[15]);

    printf("PASSED\n");
}


void
MoveMiddleToMiddle(void)
{
    /*
     * Move from middle of source to middle of destination.
     */
    byte  dst[50];
    byte  dst_orig[50];
    byte  src[50];
    usize moved_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "MoveMiddleToMiddle -> ");

    kdi_FillVal(dst, USIZE_C(50), U8_C(0x11));
    kdi_FillVal(dst_orig, USIZE_C(50), U8_C(0x11));
    kdi_FillSeq(src, USIZE_C(50), U8_C(0xC0));

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveBound(dst, USIZE_C(50), &moved_sz, src, USIZE_C(50), USIZE_C(20), USIZE_C(15), USIZE_C(12));

    assert(result == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(12));

    /* Head should remain unchanged */
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(20)) == RESULT_SUCCESS);

    /* Middle should contain moved data */
    for (i = USIZE_C(0); i < USIZE_C(12); ++i)
    {
        assert(dst[USIZE_C(20) + i] == src[USIZE_C(15) + i]);
    }

    /* Tail should remain unchanged */
    assert(kdi_BytesEqual(dst + USIZE_C(32), dst_orig + USIZE_C(32), USIZE_C(18)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
ExcessiveByteCountRequest(void)
{
    /*
     * Request very large byte_count that exceeds both dst and src availability.
     * Should move only what's possible.
     */
    byte  dst[20];
    byte  src[20];
    usize moved_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "ExcessiveByteCountRequest -> ");

    kdi_FillVal(dst, USIZE_C(20), U8_C(0x00));
    kdi_FillSeq(src, USIZE_C(20), U8_C(0xD0));

    moved_sz = USIZE_C(0xDEAD);
    result   = GenMemOpsMoveBound(dst, USIZE_C(20), &moved_sz, src, USIZE_C(20), USIZE_C(10), USIZE_C(5), USIZE_C(1000));

    assert(result == RESULT_SUCCESS);
    /* dst has 10 bytes available (20-10), src has 15 bytes available (20-5) */
    /* Should move min(1000, 10, 15) = 10 */
    assert(moved_sz == USIZE_C(10));

    for (i = USIZE_C(0); i < USIZE_C(10); ++i)
    {
        assert(dst[USIZE_C(10) + i] == src[USIZE_C(5) + i]);
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
    ExactMoveWithinBounds();
    MoveAtStartOfBothBuffers();
    TruncationDueToDstSpace();
    TruncationDueToSrcSpace();
    TruncationDueToBothLimits();
    SingleByteMove();
    MoveToEndOfDst();
    MoveFromEndOfSrc();
    LargeBuffersWithOffsets();
    OverlappingMoveForward();
    OverlappingMoveBackward();
    DstOnlyOneByteAvailable();
    SrcOnlyOneByteAvailable();
    MoveMiddleToMiddle();
    ExcessiveByteCountRequest();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
