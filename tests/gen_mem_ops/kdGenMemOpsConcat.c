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
    byte dst[32];
    byte src1[16];
    byte src2[16];
    byte dst_orig[32];
    bool result;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillSeq(dst, USIZE_C(32), U8_C(0xAA));
    kdi_FillSeq(dst_orig, USIZE_C(32), U8_C(0xAA));
    kdi_FillSeq(src1, USIZE_C(16), U8_C(0x11));
    kdi_FillSeq(src2, USIZE_C(16), U8_C(0x22));

    /* dst is null */
    result = GenMemOpsConcat(null, USIZE_C(32), src1, src2, USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* src1 is null */
    result = GenMemOpsConcat(dst, USIZE_C(32), null, src2, USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* src2 is null */
    result = GenMemOpsConcat(dst, USIZE_C(32), src1, null, USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* dst_sz is zero */
    result = GenMemOpsConcat(dst, USIZE_C(0), src1, src2, USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* concat_sz is zero */
    result = GenMemOpsConcat(dst, USIZE_C(32), src1, src2, USIZE_C(0));
    assert(result == RESULT_FAILURE);
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
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "ExactFitConcat -> ");

    kdi_FillSeq(src1, USIZE_C(8), U8_C(0x01));
    kdi_FillSeq(src2, USIZE_C(8), U8_C(0x11));

    /* Build expected = first 8 bytes of src1 || first 8 bytes of src2 */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        expected[i] = src1[i];
    }
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        expected[USIZE_C(8) + i] = src2[i];
    }

    result = GenMemOpsConcat(dst, USIZE_C(16), src1, src2, USIZE_C(8));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, expected, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
DstLargerThanTotal(void)
{
    byte  dst[32];
    byte  dst_orig[32];
    byte  src1[8];
    byte  src2[8];
    byte  expected[16];
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "DstLargerThanTotal -> ");

    kdi_FillSeq(dst, USIZE_C(32), U8_C(0xAA));
    kdi_FillSeq(dst_orig, USIZE_C(32), U8_C(0xAA));
    kdi_FillSeq(src1, USIZE_C(8), U8_C(0x01));
    kdi_FillSeq(src2, USIZE_C(8), U8_C(0x11));

    /* expected first 16 bytes = first 8 of src1 || first 8 of src2 */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        expected[i] = src1[i];
    }
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        expected[USIZE_C(8) + i] = src2[i];
    }

    result = GenMemOpsConcat(dst, USIZE_C(32), src1, src2, USIZE_C(8));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, expected, USIZE_C(16)) == RESULT_SUCCESS);
    /* tail of dst (16..31) should remain untouched */
    assert(kdi_BytesEqual(dst + USIZE_C(16), dst_orig + USIZE_C(16), USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
PartialConcat(void)
{
    byte  dst[12];
    byte  src1[16];
    byte  src2[16];
    byte  expected[12];
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "PartialConcat -> ");

    kdi_FillSeq(src1, USIZE_C(16), U8_C(0x10));
    kdi_FillSeq(src2, USIZE_C(16), U8_C(0x20));

    /* Concatenate first 6 bytes from each source */
    /* expected = src1[0..5] || src2[0..5] */
    for (i = USIZE_C(0); i < USIZE_C(6); ++i)
    {
        expected[i] = src1[i];
    }
    for (i = USIZE_C(0); i < USIZE_C(6); ++i)
    {
        expected[USIZE_C(6) + i] = src2[i];
    }

    result = GenMemOpsConcat(dst, USIZE_C(12), src1, src2, USIZE_C(6));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, expected, USIZE_C(12)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SingleByteFromEach(void)
{
    byte dst[2];
    byte src1[4];
    byte src2[4];
    bool result;

    printf(LOG_PREFIX_CSTR "SingleByteFromEach -> ");

    src1[0] = U8_C(0xAA);
    src1[1] = U8_C(0xBB);
    src1[2] = U8_C(0xCC);
    src1[3] = U8_C(0xDD);

    src2[0] = U8_C(0x11);
    src2[1] = U8_C(0x22);
    src2[2] = U8_C(0x33);
    src2[3] = U8_C(0x44);

    dst[0] = U8_C(0xFF);
    dst[1] = U8_C(0xFF);

    result = GenMemOpsConcat(dst, USIZE_C(2), src1, src2, USIZE_C(1));

    assert(result == RESULT_SUCCESS);
    assert(dst[0] == U8_C(0xAA));
    assert(dst[1] == U8_C(0x11));

    printf("PASSED\n");
}


void
LargeConcat(void)
{
    byte  dst[256];
    byte  src1[128];
    byte  src2[128];
    byte  expected[256];
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeConcat -> ");

    kdi_FillSeq(src1, USIZE_C(128), U8_C(0x00));
    kdi_FillSeq(src2, USIZE_C(128), U8_C(0x80));

    /* Build expected */
    for (i = USIZE_C(0); i < USIZE_C(128); ++i)
    {
        expected[i] = src1[i];
    }
    for (i = USIZE_C(0); i < USIZE_C(128); ++i)
    {
        expected[USIZE_C(128) + i] = src2[i];
    }

    result = GenMemOpsConcat(dst, USIZE_C(256), src1, src2, USIZE_C(128));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, expected, USIZE_C(256)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
DstSmallerThanTotalNeeded(void)
{
    byte  dst[10];
    byte  dst_orig[10];
    byte  src1[8];
    byte  src2[8];
    byte  expected_truncated[10];
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "DstSmallerThanTotalNeeded -> ");

    kdi_FillSeq(dst, USIZE_C(10), U8_C(0xAA));
    kdi_FillSeq(dst_orig, USIZE_C(10), U8_C(0xAA));
    kdi_FillSeq(src1, USIZE_C(8), U8_C(0x01));
    kdi_FillSeq(src2, USIZE_C(8), U8_C(0x11));

    /* Trying to concat 8+8=16 bytes into dst of size 10 */
    /* Should only copy what fits: first 8 from src1, then 2 from src2 */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        expected_truncated[i] = src1[i];
    }
    for (i = USIZE_C(0); i < USIZE_C(2); ++i)
    {
        expected_truncated[USIZE_C(8) + i] = src2[i];
    }

    result = GenMemOpsConcat(dst, USIZE_C(10), src1, src2, USIZE_C(8));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, expected_truncated, USIZE_C(10)) == RESULT_SUCCESS);

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
    DstLargerThanTotal();
    PartialConcat();
    SingleByteFromEach();
    LargeConcat();
    DstSmallerThanTotalNeeded();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}