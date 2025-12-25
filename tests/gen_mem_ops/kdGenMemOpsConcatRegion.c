/**
 * @file kdGenMemOpsConcatRegion.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsConcatRegion function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsConcatRegion function test"
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
    byte  src1[16];
    byte  src2[16];
    byte  dst_orig[32];
    usize concat_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillSeq(dst, USIZE_C(32), U8_C(0xAA));
    kdi_FillSeq(dst_orig, USIZE_C(32), U8_C(0xAA));
    kdi_FillSeq(src1, USIZE_C(16), U8_C(0x11));
    kdi_FillSeq(src2, USIZE_C(16), U8_C(0x22));

    /* concat_sz pointer is null */
    result = GenMemOpsConcatRegion(dst, USIZE_C(32), null, src1, USIZE_C(8), src2, USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* dst is null */
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRegion(null, USIZE_C(32), &concat_sz, src1, USIZE_C(8), src2, USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));

    /* src1 is null */
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRegion(dst, USIZE_C(32), &concat_sz, null, USIZE_C(8), src2, USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* src2 is null */
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRegion(dst, USIZE_C(32), &concat_sz, src1, USIZE_C(8), null, USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* dst_sz is zero */
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRegion(dst, USIZE_C(0), &concat_sz, src1, USIZE_C(8), src2, USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* src_1_sz is zero */
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRegion(dst, USIZE_C(32), &concat_sz, src1, USIZE_C(0), src2, USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(concat_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* src_2_sz is zero */
    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRegion(dst, USIZE_C(32), &concat_sz, src1, USIZE_C(8), src2, USIZE_C(0));
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
    usize i;

    printf(LOG_PREFIX_CSTR "ExactFitConcat -> ");

    kdi_FillSeq(src1, USIZE_C(8), U8_C(0x01));
    kdi_FillSeq(src2, USIZE_C(8), U8_C(0x11));

    /* Build expected = src1[0..7] || src2[0..7] */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        expected[i] = src1[i];
    }
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        expected[USIZE_C(8) + i] = src2[i];
    }

    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRegion(dst, USIZE_C(16), &concat_sz, src1, USIZE_C(8), src2, USIZE_C(8));

    assert(result == RESULT_SUCCESS);
    assert(concat_sz == USIZE_C(16));
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
    usize concat_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "DstLargerThanTotal -> ");

    kdi_FillSeq(dst, USIZE_C(32), U8_C(0xAA));
    kdi_FillSeq(dst_orig, USIZE_C(32), U8_C(0xAA));
    kdi_FillSeq(src1, USIZE_C(8), U8_C(0x01));
    kdi_FillSeq(src2, USIZE_C(8), U8_C(0x11));

    /* expected first 16 bytes = src1[0..7] || src2[0..7] */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        expected[i] = src1[i];
    }
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        expected[USIZE_C(8) + i] = src2[i];
    }

    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRegion(dst, USIZE_C(32), &concat_sz, src1, USIZE_C(8), src2, USIZE_C(8));

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
    byte  expected_truncated[10];
    usize concat_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "DstSmallerThanTotal -> ");

    kdi_FillSeq(dst, USIZE_C(10), U8_C(0xAA));
    kdi_FillSeq(dst_orig, USIZE_C(10), U8_C(0xAA));
    kdi_FillSeq(src1, USIZE_C(8), U8_C(0x01));
    kdi_FillSeq(src2, USIZE_C(8), U8_C(0x11));

    /* Trying to concat 8+8=16 bytes into dst of size 10 */
    /* Should only copy what fits: all 8 from src1, then 2 from src2 */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        expected_truncated[i] = src1[i];
    }
    for (i = USIZE_C(0); i < USIZE_C(2); ++i)
    {
        expected_truncated[USIZE_C(8) + i] = src2[i];
    }

    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRegion(dst, USIZE_C(10), &concat_sz, src1, USIZE_C(8), src2, USIZE_C(8));

    assert(result == RESULT_SUCCESS);
    assert(concat_sz == USIZE_C(10));
    assert(kdi_BytesEqual(dst, expected_truncated, USIZE_C(10)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
UnequalSourceSizes(void)
{
    byte  dst[32];
    byte  src1[12];
    byte  src2[5];
    byte  expected[17];
    usize concat_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "UnequalSourceSizes -> ");

    kdi_FillSeq(src1, USIZE_C(12), U8_C(0x10));
    kdi_FillSeq(src2, USIZE_C(5), U8_C(0x20));

    /* Build expected = src1[0..11] || src2[0..4] */
    for (i = USIZE_C(0); i < USIZE_C(12); ++i)
    {
        expected[i] = src1[i];
    }
    for (i = USIZE_C(0); i < USIZE_C(5); ++i)
    {
        expected[USIZE_C(12) + i] = src2[i];
    }

    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRegion(dst, USIZE_C(32), &concat_sz, src1, USIZE_C(12), src2, USIZE_C(5));

    assert(result == RESULT_SUCCESS);
    assert(concat_sz == USIZE_C(17));
    assert(kdi_BytesEqual(dst, expected, USIZE_C(17)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SingleByteFromEach(void)
{
    byte  dst[2];
    byte  src1[1];
    byte  src2[1];
    usize concat_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "SingleByteFromEach -> ");

    src1[0] = U8_C(0xAA);
    src2[0] = U8_C(0x55);

    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRegion(dst, USIZE_C(2), &concat_sz, src1, USIZE_C(1), src2, USIZE_C(1));

    assert(result == RESULT_SUCCESS);
    assert(concat_sz == USIZE_C(2));
    assert(dst[0] == U8_C(0xAA));
    assert(dst[1] == U8_C(0x55));

    printf("PASSED\n");
}


void
LargeSourcesExactFit(void)
{
    byte  dst[256];
    byte  src1[128];
    byte  src2[128];
    byte  expected[256];
    usize concat_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeSourcesExactFit -> ");

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

    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRegion(dst, USIZE_C(256), &concat_sz, src1, USIZE_C(128), src2, USIZE_C(128));

    assert(result == RESULT_SUCCESS);
    assert(concat_sz == USIZE_C(256));
    assert(kdi_BytesEqual(dst, expected, USIZE_C(256)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
LargeSourcesTruncated(void)
{
    byte  dst[100];
    byte  src1[80];
    byte  src2[80];
    byte  expected[100];
    usize concat_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeSourcesTruncated -> ");

    kdi_FillSeq(src1, USIZE_C(80), U8_C(0x01));
    kdi_FillSeq(src2, USIZE_C(80), U8_C(0x41));

    /* Trying to concat 80+80=160 bytes into 100-byte dst */
    /* Should get all 80 from src1, then 20 from src2 */
    for (i = USIZE_C(0); i < USIZE_C(80); ++i)
    {
        expected[i] = src1[i];
    }
    for (i = USIZE_C(0); i < USIZE_C(20); ++i)
    {
        expected[USIZE_C(80) + i] = src2[i];
    }

    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRegion(dst, USIZE_C(100), &concat_sz, src1, USIZE_C(80), src2, USIZE_C(80));

    assert(result == RESULT_SUCCESS);
    assert(concat_sz == USIZE_C(100));
    assert(kdi_BytesEqual(dst, expected, USIZE_C(100)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
DstBarelySufficientForSrc1(void)
{
    byte  dst[8];
    byte  src1[8];
    byte  src2[16];
    byte  expected[8];
    usize concat_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "DstBarelySufficientForSrc1 -> ");

    kdi_FillSeq(src1, USIZE_C(8), U8_C(0x10));
    kdi_FillSeq(src2, USIZE_C(16), U8_C(0x20));

    /* dst can only hold src1, no room for src2 */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        expected[i] = src1[i];
    }

    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRegion(dst, USIZE_C(8), &concat_sz, src1, USIZE_C(8), src2, USIZE_C(16));

    assert(result == RESULT_SUCCESS);
    assert(concat_sz == USIZE_C(8));
    assert(kdi_BytesEqual(dst, expected, USIZE_C(8)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
DstSmallerThanSrc1(void)
{
    byte  dst[5];
    byte  src1[8];
    byte  src2[8];
    byte  expected[5];
    usize concat_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "DstSmallerThanSrc1 -> ");

    kdi_FillSeq(src1, USIZE_C(8), U8_C(0xA0));
    kdi_FillSeq(src2, USIZE_C(8), U8_C(0xB0));

    /* dst can only hold 5 bytes from src1, none from src2 */
    for (i = USIZE_C(0); i < USIZE_C(5); ++i)
    {
        expected[i] = src1[i];
    }

    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRegion(dst, USIZE_C(5), &concat_sz, src1, USIZE_C(8), src2, USIZE_C(8));

    assert(result == RESULT_SUCCESS);
    assert(concat_sz == USIZE_C(5));
    assert(kdi_BytesEqual(dst, expected, USIZE_C(5)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
VeryLargeSrc1SmallSrc2(void)
{
    byte  dst[200];
    byte  src1[180];
    byte  src2[10];
    byte  expected[190];
    usize concat_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "VeryLargeSrc1SmallSrc2 -> ");

    kdi_FillSeq(src1, USIZE_C(180), U8_C(0x05));
    kdi_FillSeq(src2, USIZE_C(10), U8_C(0xF0));

    /* Build expected = src1[0..179] || src2[0..9] */
    for (i = USIZE_C(0); i < USIZE_C(180); ++i)
    {
        expected[i] = src1[i];
    }
    for (i = USIZE_C(0); i < USIZE_C(10); ++i)
    {
        expected[USIZE_C(180) + i] = src2[i];
    }

    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRegion(dst, USIZE_C(200), &concat_sz, src1, USIZE_C(180), src2, USIZE_C(10));

    assert(result == RESULT_SUCCESS);
    assert(concat_sz == USIZE_C(190));
    assert(kdi_BytesEqual(dst, expected, USIZE_C(190)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SmallSrc1VeryLargeSrc2(void)
{
    byte  dst[200];
    byte  src1[10];
    byte  src2[180];
    byte  expected[190];
    usize concat_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "SmallSrc1VeryLargeSrc2 -> ");

    kdi_FillSeq(src1, USIZE_C(10), U8_C(0xE0));
    kdi_FillSeq(src2, USIZE_C(180), U8_C(0x30));

    /* Build expected = src1[0..9] || src2[0..179] */
    for (i = USIZE_C(0); i < USIZE_C(10); ++i)
    {
        expected[i] = src1[i];
    }
    for (i = USIZE_C(0); i < USIZE_C(180); ++i)
    {
        expected[USIZE_C(10) + i] = src2[i];
    }

    concat_sz = USIZE_C(0xDEAD);
    result    = GenMemOpsConcatRegion(dst, USIZE_C(200), &concat_sz, src1, USIZE_C(10), src2, USIZE_C(180));

    assert(result == RESULT_SUCCESS);
    assert(concat_sz == USIZE_C(190));
    assert(kdi_BytesEqual(dst, expected, USIZE_C(190)) == RESULT_SUCCESS);

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
    DstSmallerThanTotal();
    UnequalSourceSizes();
    SingleByteFromEach();
    LargeSourcesExactFit();
    LargeSourcesTruncated();
    DstBarelySufficientForSrc1();
    DstSmallerThanSrc1();
    VeryLargeSrc1SmallSrc2();
    SmallSrc1VeryLargeSrc2();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
