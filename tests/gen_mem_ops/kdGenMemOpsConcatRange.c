/**
 * @file kdGenMemOpsConcatRange.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsConcatRange function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsConcatRange function test"
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


void
BasicArguments(void)
{
    byte  dst[32];
    byte  dst_orig[32];
    byte  src1[16];
    byte  src2[16];
    usize concat_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillSeq(dst, USIZE_C(32), U8_C(0xAA));
    kdi_FillSeq(dst_orig, USIZE_C(32), U8_C(0xAA));
    kdi_FillSeq(src1, USIZE_C(16), U8_C(0x10));
    kdi_FillSeq(src2, USIZE_C(16), U8_C(0x20));

    /* concat_sz pointer is null: must not touch concat_sz, dst or sources */
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRange(dst, USIZE_C(32), USIZE_C(0), null, src1, USIZE_C(16), USIZE_C(0), USIZE_C(8), src2, USIZE_C(16), USIZE_C(0), USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0xDEAD));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* dst_base is null */
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRange(null, USIZE_C(32), USIZE_C(0), &concat_sz, src1, USIZE_C(16), USIZE_C(0), USIZE_C(8), src2, USIZE_C(16), USIZE_C(0), USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));

    /* src_base_1 is null */
    kdi_FillSeq(dst, USIZE_C(32), U8_C(0xAA));
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRange(dst, USIZE_C(32), USIZE_C(0), &concat_sz, null, USIZE_C(16), USIZE_C(0), USIZE_C(8), src2, USIZE_C(16), USIZE_C(0), USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* src_base_2 is null */
    kdi_FillSeq(dst, USIZE_C(32), U8_C(0xAA));
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRange(dst, USIZE_C(32), USIZE_C(0), &concat_sz, src1, USIZE_C(16), USIZE_C(0), USIZE_C(8), null, USIZE_C(16), USIZE_C(0), USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* dst_base_sz is zero */
    kdi_FillSeq(dst, USIZE_C(32), U8_C(0xAA));
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRange(dst, USIZE_C(0), USIZE_C(0), &concat_sz, src1, USIZE_C(16), USIZE_C(0), USIZE_C(8), src2, USIZE_C(16), USIZE_C(0), USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* src_base_1_sz is zero */
    kdi_FillSeq(dst, USIZE_C(32), U8_C(0xAA));
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRange(dst, USIZE_C(32), USIZE_C(0), &concat_sz, src1, USIZE_C(0), USIZE_C(0), USIZE_C(8), src2, USIZE_C(16), USIZE_C(0), USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* src_base_2_sz is zero */
    kdi_FillSeq(dst, USIZE_C(32), U8_C(0xAA));
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRange(dst, USIZE_C(32), USIZE_C(0), &concat_sz, src1, USIZE_C(16), USIZE_C(0), USIZE_C(8), src2, USIZE_C(0), USIZE_C(0), USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* src_1_byte_count is zero */
    kdi_FillSeq(dst, USIZE_C(32), U8_C(0xAA));
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRange(dst, USIZE_C(32), USIZE_C(0), &concat_sz, src1, USIZE_C(16), USIZE_C(0), USIZE_C(0), src2, USIZE_C(16), USIZE_C(0), USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* src_2_byte_count is zero */
    kdi_FillSeq(dst, USIZE_C(32), U8_C(0xAA));
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRange(dst, USIZE_C(32), USIZE_C(0), &concat_sz, src1, USIZE_C(16), USIZE_C(0), USIZE_C(8), src2, USIZE_C(16), USIZE_C(0), USIZE_C(0));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* dst_idx out of bounds (dst_idx >= dst_base_sz) */
    kdi_FillSeq(dst, USIZE_C(32), U8_C(0xAA));
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRange(dst, USIZE_C(16), USIZE_C(16), &concat_sz, src1, USIZE_C(16), USIZE_C(0), USIZE_C(8), src2, USIZE_C(16), USIZE_C(0), USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* src_1_begin_idx out of bounds (>= src_base_1_sz) */
    kdi_FillSeq(dst, USIZE_C(32), U8_C(0xAA));
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRange(dst, USIZE_C(32), USIZE_C(0), &concat_sz, src1, USIZE_C(16), USIZE_C(16), USIZE_C(4), src2, USIZE_C(16), USIZE_C(0), USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* src_2_begin_idx out of bounds (>= src_base_2_sz) */
    kdi_FillSeq(dst, USIZE_C(32), U8_C(0xAA));
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRange(dst, USIZE_C(32), USIZE_C(0), &concat_sz, src1, USIZE_C(16), USIZE_C(0), USIZE_C(8), src2, USIZE_C(16), USIZE_C(16), USIZE_C(4));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
ExactFitRange(void)
{
    byte  dst[16];
    byte  src1[16];
    byte  src2[16];
    byte  expected[16];
    usize concat_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "ExactFitRange -> ");

    /* src1: 0x01..0x10, src2: 0x21..0x30 */
    kdi_FillSeq(src1, USIZE_C(16), U8_C(0x01));
    kdi_FillSeq(src2, USIZE_C(16), U8_C(0x21));

    /* Take first 8 bytes from each, start writing at dst_idx = 0 */
    {
        usize i;
        for (i = USIZE_C(0); i < USIZE_C(8); ++i)
        {
            expected[i] = src1[i];
        }
        for (i = USIZE_C(0); i < USIZE_C(8); ++i)
        {
            expected[USIZE_C(8) + i] = src2[i];
        }
    }

    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRange(dst, USIZE_C(16), USIZE_C(0), &concat_sz, src1, USIZE_C(16), USIZE_C(0), USIZE_C(8), src2, USIZE_C(16), USIZE_C(0), USIZE_C(8));

    assert(result == RESULT_SUCCESS);
    assert(concat_sz == USIZE_C(16));
    assert(kdi_BytesEqual(dst, expected, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
RangeOffsetsWork(void)
{
    byte  dst[24];
    byte  dst_orig[24];
    byte  src1[16];
    byte  src2[16];
    byte  expected[24];
    usize concat_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "RangeOffsetsWork -> ");

    kdi_FillSeq(dst, USIZE_C(24), U8_C(0xAA));
    kdi_FillSeq(dst_orig, USIZE_C(24), U8_C(0xAA));

    /* src1: 0x10..0x1F, src2: 0x20..0x2F */
    kdi_FillSeq(src1, USIZE_C(16), U8_C(0x10));
    kdi_FillSeq(src2, USIZE_C(16), U8_C(0x20));

    /* dst_idx = 4, from src1: bytes [4..12), from src2: bytes [2..10) */
    {
        usize i;

        /* prefix before dst_idx remains unchanged */
        for (i = USIZE_C(0); i < USIZE_C(4); ++i)
        {
            expected[i] = dst_orig[i];
        }

        for (i = USIZE_C(0); i < USIZE_C(8); ++i)
        {
            expected[USIZE_C(4) + i] = src1[USIZE_C(4) + i];
        }
        for (i = USIZE_C(0); i < USIZE_C(8); ++i)
        {
            expected[USIZE_C(12) + i] = src2[USIZE_C(2) + i];
        }

        /* tail after written region remains unchanged */
        for (i = USIZE_C(20); i < USIZE_C(24); ++i)
        {
            expected[i] = dst_orig[i];
        }
    }

    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRange(dst, USIZE_C(24), USIZE_C(4), &concat_sz, src1, USIZE_C(16), USIZE_C(4), USIZE_C(8), src2, USIZE_C(16), USIZE_C(2), USIZE_C(8));

    assert(result == RESULT_SUCCESS);
    assert(concat_sz == USIZE_C(16));
    assert(kdi_BytesEqual(dst, expected, USIZE_C(24)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
DstLargerThanNeededRange(void)
{
    byte  dst[32];
    byte  dst_orig[32];
    byte  src1[16];
    byte  src2[16];
    byte  expected[32];
    usize concat_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "DstLargerThanNeededRange -> ");

    kdi_FillSeq(dst, USIZE_C(32), U8_C(0xAA));
    kdi_FillSeq(dst_orig, USIZE_C(32), U8_C(0xAA));
    kdi_FillSeq(src1, USIZE_C(16), U8_C(0x01));
    kdi_FillSeq(src2, USIZE_C(16), U8_C(0x11));

    {
        usize i;

        /* prefix (first 4 bytes) unchanged */
        for (i = USIZE_C(0); i < USIZE_C(4); ++i)
        {
            expected[i] = dst_orig[i];
        }

        /* write starting at dst_idx = 4, 8 bytes from each src */
        for (i = USIZE_C(0); i < USIZE_C(8); ++i)
        {
            expected[USIZE_C(4) + i] = src1[i];
        }
        for (i = USIZE_C(0); i < USIZE_C(8); ++i)
        {
            expected[USIZE_C(12) + i] = src2[i];
        }

        /* tail after written region unchanged */
        for (i = USIZE_C(20); i < USIZE_C(32); ++i)
        {
            expected[i] = dst_orig[i];
        }
    }

    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRange(dst, USIZE_C(32), USIZE_C(4), &concat_sz, src1, USIZE_C(16), USIZE_C(0), USIZE_C(8), src2, USIZE_C(16), USIZE_C(0), USIZE_C(8));

    assert(result == RESULT_SUCCESS);
    assert(concat_sz == USIZE_C(16));
    assert(kdi_BytesEqual(dst, expected, USIZE_C(32)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
DstSmallerThanTotalRange(void)
{
    byte  dst[10];
    byte  src1[16];
    byte  src2[16];
    byte  full_concat[16];
    usize concat_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "DstSmallerThanTotalRange -> ");

    kdi_FillSeq(dst, USIZE_C(10), U8_C(0xAA));
    kdi_FillSeq(src1, USIZE_C(16), U8_C(0x01));
    kdi_FillSeq(src2, USIZE_C(16), U8_C(0x11));

    /* full concat (virtual): first 8 from src1 then first 8 from src2 */
    {
        usize i;
        for (i = USIZE_C(0); i < USIZE_C(8); ++i)
        {
            full_concat[i] = src1[i];
        }
        for (i = USIZE_C(0); i < USIZE_C(8); ++i)
        {
            full_concat[USIZE_C(8) + i] = src2[i];
        }
    }

    /* dst_base_sz (10) < total (16), dst_idx = 0, so concat_sz = 10 */
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRange(dst, USIZE_C(10), USIZE_C(0), &concat_sz, src1, USIZE_C(16), USIZE_C(0), USIZE_C(8), src2, USIZE_C(16), USIZE_C(0), USIZE_C(8));

    assert(result == RESULT_SUCCESS);
    assert(concat_sz == USIZE_C(10));
    assert(kdi_BytesEqual(dst, full_concat, USIZE_C(10)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    ExactFitRange();
    RangeOffsetsWork();
    DstLargerThanNeededRange();
    DstSmallerThanTotalRange();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
