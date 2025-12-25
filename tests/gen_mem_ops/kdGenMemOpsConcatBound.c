/**
 * @file kdGenMemOpsConcatBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsConcatBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsConcatBound function test"
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
    byte  dst[64];
    byte  src1[32];
    byte  src2[32];
    byte  dst_orig[64];
    usize concat_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillSeq(dst, USIZE_C(64), U8_C(0xAA));
    kdi_FillSeq(dst_orig, USIZE_C(64), U8_C(0xAA));
    kdi_FillSeq(src1, USIZE_C(32), U8_C(0x11));
    kdi_FillSeq(src2, USIZE_C(32), U8_C(0x22));

    /* concat_sz pointer is null */
    result = GenMemOpsConcatBound(dst, USIZE_C(64), USIZE_C(0), null, src1, USIZE_C(32), USIZE_C(0), USIZE_C(8), src2, USIZE_C(32), USIZE_C(0), USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* dst_base is null */
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatBound(null, USIZE_C(64), USIZE_C(0), &concat_sz, src1, USIZE_C(32), USIZE_C(0), USIZE_C(8), src2, USIZE_C(32), USIZE_C(0), USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));

    /* src_base_1 is null */
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatBound(dst, USIZE_C(64), USIZE_C(0), &concat_sz, null, USIZE_C(32), USIZE_C(0), USIZE_C(8), src2, USIZE_C(32), USIZE_C(0), USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* src_base_2 is null */
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatBound(dst, USIZE_C(64), USIZE_C(0), &concat_sz, src1, USIZE_C(32), USIZE_C(0), USIZE_C(8), null, USIZE_C(32), USIZE_C(0), USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* dst_idx out of bounds (equals dst_base_sz) */
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatBound(dst, USIZE_C(64), USIZE_C(64), &concat_sz, src1, USIZE_C(32), USIZE_C(0), USIZE_C(8), src2, USIZE_C(32), USIZE_C(0), USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* dst_idx out of bounds (greater than dst_base_sz) */
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatBound(dst, USIZE_C(64), USIZE_C(100), &concat_sz, src1, USIZE_C(32), USIZE_C(0), USIZE_C(8), src2, USIZE_C(32), USIZE_C(0), USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* src_1_begin_idx out of bounds (equals src_base_1_sz) */
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatBound(dst, USIZE_C(64), USIZE_C(0), &concat_sz, src1, USIZE_C(32), USIZE_C(32), USIZE_C(8), src2, USIZE_C(32), USIZE_C(0), USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* src_2_begin_idx out of bounds (equals src_base_2_sz) */
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatBound(dst, USIZE_C(64), USIZE_C(0), &concat_sz, src1, USIZE_C(32), USIZE_C(0), USIZE_C(8), src2, USIZE_C(32), USIZE_C(32), USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* src_1_byte_count is zero */
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatBound(dst, USIZE_C(64), USIZE_C(0), &concat_sz, src1, USIZE_C(32), USIZE_C(0), USIZE_C(0), src2, USIZE_C(32), USIZE_C(0), USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* src_2_byte_count is zero */
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatBound(dst, USIZE_C(64), USIZE_C(0), &concat_sz, src1, USIZE_C(32), USIZE_C(0), USIZE_C(8), src2, USIZE_C(32), USIZE_C(0), USIZE_C(0));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(64)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
ExactFitConcat(void)
{
    /*
     * Concatenate src1[5..12] (8 bytes) and src2[10..17] (8 bytes)
     * into dst starting at dst[0]. Total 16 bytes fit exactly.
     */
    byte  dst[16];
    byte  src1[20];
    byte  src2[24];
    byte  expected[16];
    usize concat_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "ExactFitConcat -> ");

    kdi_FillSeq(src1, USIZE_C(20), U8_C(0x10));
    kdi_FillSeq(src2, USIZE_C(24), U8_C(0x30));

    /* Build expected: src1[5..12] || src2[10..17] */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        expected[i] = src1[USIZE_C(5) + i];
    }
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        expected[USIZE_C(8) + i] = src2[USIZE_C(10) + i];
    }

    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatBound(dst, USIZE_C(16), USIZE_C(0), &concat_sz, src1, USIZE_C(20), USIZE_C(5), USIZE_C(8), src2, USIZE_C(24), USIZE_C(10), USIZE_C(8));

    assert(result == RESULT_SUCCESS);
    assert(concat_sz == USIZE_C(16));
    assert(kdi_BytesEqual(dst, expected, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
ConcatAtOffset(void)
{
    /*
     * Concatenate into middle of destination buffer.
     * dst[10..25] = src1[0..7] || src2[0..7]
     * Head and tail of dst should remain unchanged.
     */
    byte  dst[32];
    byte  dst_orig[32];
    byte  src1[16];
    byte  src2[16];
    usize concat_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "ConcatAtOffset -> ");

    kdi_FillVal(dst, USIZE_C(32), U8_C(0xFF));
    kdi_FillVal(dst_orig, USIZE_C(32), U8_C(0xFF));
    kdi_FillSeq(src1, USIZE_C(16), U8_C(0xA0));
    kdi_FillSeq(src2, USIZE_C(16), U8_C(0xB0));

    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatBound(dst, USIZE_C(32), USIZE_C(10), &concat_sz, src1, USIZE_C(16), USIZE_C(0), USIZE_C(8), src2, USIZE_C(16), USIZE_C(0), USIZE_C(8));

    assert(result == RESULT_SUCCESS);
    assert(concat_sz == USIZE_C(16));

    /* Head (0..9) should remain untouched */
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(10)) == RESULT_SUCCESS);

    /* Middle (10..17) should be src1[0..7] */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        assert(dst[USIZE_C(10) + i] == src1[i]);
    }

    /* Middle (18..25) should be src2[0..7] */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        assert(dst[USIZE_C(18) + i] == src2[i]);
    }

    /* Tail (26..31) should remain untouched */
    assert(kdi_BytesEqual(dst + USIZE_C(26), dst_orig + USIZE_C(26), USIZE_C(6)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
TruncationDueToDestSize(void)
{
    /*
     * Requesting 8+8=16 bytes but dst only has 12 bytes available from dst_idx.
     * Should copy all 8 from src1, then only 4 from src2.
     */
    byte  dst[20];
    byte  src1[16];
    byte  src2[16];
    usize concat_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "TruncationDueToDestSize -> ");

    kdi_FillVal(dst, USIZE_C(20), U8_C(0x00));
    kdi_FillSeq(src1, USIZE_C(16), U8_C(0x50));
    kdi_FillSeq(src2, USIZE_C(16), U8_C(0x60));

    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatBound(dst, USIZE_C(20), USIZE_C(8), &concat_sz, src1, USIZE_C(16), USIZE_C(0), USIZE_C(8), src2, USIZE_C(16), USIZE_C(0), USIZE_C(8));

    assert(result == RESULT_SUCCESS);
    assert(concat_sz == USIZE_C(12));

    /* dst[8..15] should be src1[0..7] */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        assert(dst[USIZE_C(8) + i] == src1[i]);
    }

    /* dst[16..19] should be src2[0..3] (truncated) */
    for (i = USIZE_C(0); i < USIZE_C(4); ++i)
    {
        assert(dst[USIZE_C(16) + i] == src2[i]);
    }

    printf("PASSED\n");
}


void
TruncationDueToSrc1Available(void)
{
    /*
     * Request 10 bytes from src1 starting at index 25, but src1 only has 32 bytes total.
     * Available: src1[25..31] = 7 bytes only.
     * Should copy only 7 bytes from src1, then all requested from src2.
     */
    byte  dst[32];
    byte  src1[32];
    byte  src2[16];
    usize concat_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "TruncationDueToSrc1Available -> ");

    kdi_FillVal(dst, USIZE_C(32), U8_C(0x00));
    kdi_FillSeq(src1, USIZE_C(32), U8_C(0x01));
    kdi_FillSeq(src2, USIZE_C(16), U8_C(0x41));

    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatBound(dst, USIZE_C(32), USIZE_C(0), &concat_sz, src1, USIZE_C(32), USIZE_C(25), USIZE_C(10), src2, USIZE_C(16), USIZE_C(0), USIZE_C(8));

    assert(result == RESULT_SUCCESS);
    assert(concat_sz == USIZE_C(15));

    /* dst[0..6] should be src1[25..31] (only 7 bytes available) */
    for (i = USIZE_C(0); i < USIZE_C(7); ++i)
    {
        assert(dst[i] == src1[USIZE_C(25) + i]);
    }

    /* dst[7..14] should be src2[0..7] */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        assert(dst[USIZE_C(7) + i] == src2[i]);
    }

    printf("PASSED\n");
}


void
TruncationDueToSrc2Available(void)
{
    /*
     * Request 10 bytes from src2 starting at index 10, but src2 only has 15 bytes total.
     * Available: src2[10..14] = 5 bytes only.
     * Should copy all requested from src1, then only 5 bytes from src2.
     */
    byte  dst[32];
    byte  src1[16];
    byte  src2[15];
    usize concat_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "TruncationDueToSrc2Available -> ");

    kdi_FillVal(dst, USIZE_C(32), U8_C(0x00));
    kdi_FillSeq(src1, USIZE_C(16), U8_C(0x70));
    kdi_FillSeq(src2, USIZE_C(15), U8_C(0x80));

    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatBound(dst, USIZE_C(32), USIZE_C(0), &concat_sz, src1, USIZE_C(16), USIZE_C(0), USIZE_C(8), src2, USIZE_C(15), USIZE_C(10), USIZE_C(10));

    assert(result == RESULT_SUCCESS);
    assert(concat_sz == USIZE_C(13));

    /* dst[0..7] should be src1[0..7] */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        assert(dst[i] == src1[i]);
    }

    /* dst[8..12] should be src2[10..14] (only 5 bytes available) */
    for (i = USIZE_C(0); i < USIZE_C(5); ++i)
    {
        assert(dst[USIZE_C(8) + i] == src2[USIZE_C(10) + i]);
    }

    printf("PASSED\n");
}


void
SingleByteFromEachSource(void)
{
    /*
     * Minimal case: 1 byte from each source at specific offsets.
     */
    byte  dst[8];
    byte  src1[10];
    byte  src2[10];
    usize concat_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "SingleByteFromEachSource -> ");

    kdi_FillVal(dst, USIZE_C(8), U8_C(0xFF));
    kdi_FillSeq(src1, USIZE_C(10), U8_C(0x10));
    kdi_FillSeq(src2, USIZE_C(10), U8_C(0x20));

    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatBound(dst, USIZE_C(8), USIZE_C(3), &concat_sz, src1, USIZE_C(10), USIZE_C(5), USIZE_C(1), src2, USIZE_C(10), USIZE_C(7), USIZE_C(1));

    assert(result == RESULT_SUCCESS);
    assert(concat_sz == USIZE_C(2));
    assert(dst[3] == src1[5]);
    assert(dst[4] == src2[7]);

    printf("PASSED\n");
}


void
LargeBuffersWithOffsets(void)
{
    /*
     * Large buffers with various offsets and byte counts.
     */
    byte  dst[256];
    byte  src1[128];
    byte  src2[128];
    usize concat_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffersWithOffsets -> ");

    kdi_FillVal(dst, USIZE_C(256), U8_C(0x00));
    kdi_FillSeq(src1, USIZE_C(128), U8_C(0x00));
    kdi_FillSeq(src2, USIZE_C(128), U8_C(0x80));

    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatBound(dst, USIZE_C(256), USIZE_C(50), &concat_sz, src1, USIZE_C(128), USIZE_C(20), USIZE_C(60), src2, USIZE_C(128), USIZE_C(30), USIZE_C(50));

    assert(result == RESULT_SUCCESS);
    assert(concat_sz == USIZE_C(110));

    /* dst[50..109] should be src1[20..79] */
    for (i = USIZE_C(0); i < USIZE_C(60); ++i)
    {
        assert(dst[USIZE_C(50) + i] == src1[USIZE_C(20) + i]);
    }

    /* dst[110..159] should be src2[30..79] */
    for (i = USIZE_C(0); i < USIZE_C(50); ++i)
    {
        assert(dst[USIZE_C(110) + i] == src2[USIZE_C(30) + i]);
    }

    printf("PASSED\n");
}


void
MultipleTruncations(void)
{
    /*
     * Multiple truncation factors at once:
     * - Limited source1 availability
     * - Limited destination space
     * - Excessive byte count requests
     */
    byte  dst[20];
    byte  src1[15];
    byte  src2[12];
    usize concat_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "MultipleTruncations -> ");

    kdi_FillVal(dst, USIZE_C(20), U8_C(0xEE));
    kdi_FillSeq(src1, USIZE_C(15), U8_C(0xC0));
    kdi_FillSeq(src2, USIZE_C(12), U8_C(0xD0));

    /* dst has 20 bytes, start at idx 5 = 15 bytes available
     * Request 12 bytes from src1[2..13], but src1[2..14] has 13 available
     * Request 8 bytes from src2[3..10], but src2[3..11] has 9 available
     * Total would be 13+8=21, but dst only has 15 available
     */
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatBound(dst, USIZE_C(20), USIZE_C(5), &concat_sz, src1, USIZE_C(15), USIZE_C(2), USIZE_C(12), src2, USIZE_C(12), USIZE_C(3), USIZE_C(8));

    assert(result == RESULT_SUCCESS);
    assert(concat_sz == USIZE_C(15));

    /* Should get min(12, 13) = 12 bytes from src1 */
    for (i = USIZE_C(0); i < USIZE_C(12); ++i)
    {
        assert(dst[USIZE_C(5) + i] == src1[USIZE_C(2) + i]);
    }

    /* Then remaining 3 bytes from src2 */
    for (i = USIZE_C(0); i < USIZE_C(3); ++i)
    {
        assert(dst[USIZE_C(17) + i] == src2[USIZE_C(3) + i]);
    }

    printf("PASSED\n");
}


void
DstTooSmallForSrc1(void)
{
    /*
     * Destination doesn't have enough space even for all of src1 portion.
     * Should get partial src1, no src2.
     */
    byte  dst[12];
    byte  src1[20];
    byte  src2[20];
    usize concat_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "DstTooSmallForSrc1 -> ");

    kdi_FillVal(dst, USIZE_C(12), U8_C(0x00));
    kdi_FillSeq(src1, USIZE_C(20), U8_C(0x90));
    kdi_FillSeq(src2, USIZE_C(20), U8_C(0xA0));

    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatBound(dst, USIZE_C(12), USIZE_C(5), &concat_sz, src1, USIZE_C(20), USIZE_C(0), USIZE_C(10), src2, USIZE_C(20), USIZE_C(0), USIZE_C(10));

    assert(result == RESULT_SUCCESS);
    assert(concat_sz == USIZE_C(7));

    /* Should only get src1[0..6] (7 bytes available in dst from idx 5) */
    for (i = USIZE_C(0); i < USIZE_C(7); ++i)
    {
        assert(dst[USIZE_C(5) + i] == src1[i]);
    }

    printf("PASSED\n");
}


void
UnequalSourceSizes(void)
{
    /*
     * Asymmetric source regions: large src1 portion, small src2 portion.
     */
    byte  dst[64];
    byte  src1[40];
    byte  src2[16];
    usize concat_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "UnequalSourceSizes -> ");

    kdi_FillVal(dst, USIZE_C(64), U8_C(0x00));
    kdi_FillSeq(src1, USIZE_C(40), U8_C(0x05));
    kdi_FillSeq(src2, USIZE_C(16), U8_C(0xF5));

    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatBound(dst, USIZE_C(64), USIZE_C(10), &concat_sz, src1, USIZE_C(40), USIZE_C(5), USIZE_C(30), src2, USIZE_C(16), USIZE_C(2), USIZE_C(8));

    assert(result == RESULT_SUCCESS);
    assert(concat_sz == USIZE_C(38));

    /* dst[10..39] should be src1[5..34] */
    for (i = USIZE_C(0); i < USIZE_C(30); ++i)
    {
        assert(dst[USIZE_C(10) + i] == src1[USIZE_C(5) + i]);
    }

    /* dst[40..47] should be src2[2..9] */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        assert(dst[USIZE_C(40) + i] == src2[USIZE_C(2) + i]);
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
    ExactFitConcat();
    ConcatAtOffset();
    TruncationDueToDestSize();
    TruncationDueToSrc1Available();
    TruncationDueToSrc2Available();
    SingleByteFromEachSource();
    LargeBuffersWithOffsets();
    MultipleTruncations();
    DstTooSmallForSrc1();
    UnequalSourceSizes();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
