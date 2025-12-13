/**
 * @file kdGenMemOpsConcat.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsConcat function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsConcat function test"
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
    byte  src1[8];
    byte  src2[8];
    byte  dst_orig[32];
    usize concat_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillSeq(dst, USIZE_C(32), U8_C(0xAA));
    kdi_FillSeq(dst_orig, USIZE_C(32), U8_C(0xAA));
    kdi_FillSeq(src1, USIZE_C(8), U8_C(0x11));
    kdi_FillSeq(src2, USIZE_C(8), U8_C(0x22));

    /* concat_sz pointer is null */
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcat(dst, USIZE_C(32), null, src1, USIZE_C(8), src2, USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0xDEAD));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* dst is null */
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcat(null, USIZE_C(32), &concat_sz, src1, USIZE_C(8), src2, USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));

    /* src1 is null */
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcat(dst, USIZE_C(32), &concat_sz, null, USIZE_C(8), src2, USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* src2 is null */
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcat(dst, USIZE_C(32), &concat_sz, src1, USIZE_C(8), null, USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* dst_sz is zero */
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcat(dst, USIZE_C(0), &concat_sz, src1, USIZE_C(8), src2, USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* src_1_sz is zero */
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcat(dst, USIZE_C(32), &concat_sz, src1, USIZE_C(0), src2, USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* src_2_sz is zero */
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcat(dst, USIZE_C(32), &concat_sz, src1, USIZE_C(8), src2, USIZE_C(0));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
ExactFitConcat(void)
{
    byte  dst[16];
    byte  src1[8];
    byte  src2[8];
    byte  expected[16];
    usize concat_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "ExactFitConcat -> ");

    kdi_FillSeq(src1, USIZE_C(8), U8_C(0x01));
    kdi_FillSeq(src2, USIZE_C(8), U8_C(0x11));

    /* Build expected = src1 || src2 */
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
    result    = GenMemOpsConcat(dst, USIZE_C(16), &concat_sz, src1, USIZE_C(8), src2, USIZE_C(8));

    assert(result == RESULT_SUCCESS);
    assert(concat_sz == USIZE_C(16));
    assert(kdi_BytesEqual(dst, expected, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
DstLargerThanNeeded(void)
{
    byte  dst[32];
    byte  dst_orig[32];
    byte  src1[8];
    byte  src2[8];
    byte  expected[16];
    usize concat_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "DstLargerThanNeeded -> ");

    kdi_FillSeq(dst, USIZE_C(32), U8_C(0xAA));
    kdi_FillSeq(dst_orig, USIZE_C(32), U8_C(0xAA));
    kdi_FillSeq(src1, USIZE_C(8), U8_C(0x01));
    kdi_FillSeq(src2, USIZE_C(8), U8_C(0x11));

    /* expected first 16 bytes = src1 || src2 */
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
    result    = GenMemOpsConcat(dst, USIZE_C(32), &concat_sz, src1, USIZE_C(8), src2, USIZE_C(8));

    assert(result == RESULT_SUCCESS);
    assert(concat_sz == USIZE_C(16));
    assert(kdi_BytesEqual(dst, expected, USIZE_C(16)) == RESULT_SUCCESS);
    /* tail of dst (16..31) should remain untouched */
    assert(kdi_BytesEqual(dst + USIZE_C(16), dst_orig + USIZE_C(16), USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
DstSmallerThanTotal(void)
{
    byte  dst[10];
    byte  dst_orig[10];
    byte  src1[8];
    byte  src2[8];
    byte  expected_full[16];
    usize concat_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "DstSmallerThanTotal -> ");

    kdi_FillSeq(dst, USIZE_C(10), U8_C(0xAA));
    kdi_FillSeq(dst_orig, USIZE_C(10), U8_C(0xAA));
    kdi_FillSeq(src1, USIZE_C(8), U8_C(0x01));
    kdi_FillSeq(src2, USIZE_C(8), U8_C(0x11));

    /* Build full concatenation src1 || src2 into expected_full */
    {
        usize i;
        for (i = USIZE_C(0); i < USIZE_C(8); ++i)
        {
            expected_full[i] = src1[i];
        }
        for (i = USIZE_C(0); i < USIZE_C(8); ++i)
        {
            expected_full[USIZE_C(8) + i] = src2[i];
        }
    }

    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcat(dst, USIZE_C(10), &concat_sz, src1, USIZE_C(8), src2, USIZE_C(8));

    assert(result == RESULT_SUCCESS);
    assert(concat_sz == USIZE_C(10));
    /* First 10 bytes of dst must match first 10 bytes of full concatenation */
    assert(kdi_BytesEqual(dst, expected_full, USIZE_C(10)) == RESULT_SUCCESS);

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
    DstLargerThanNeeded();
    DstSmallerThanTotal();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
