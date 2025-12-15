/**
 * @file kdGenMemOpsInnerSwapBytesRange.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsInnerSwapBytesRange function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsInnerSwapBytesRange function test"
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
    byte buf[8];
    byte buf_orig[8];
    bool result;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillSeq(buf, USIZE_C(8), U8_C(0x10));
    kdi_FillSeq(buf_orig, USIZE_C(8), U8_C(0x10));

    /* base is null -> failure */
    result = GenMemOpsInnerSwapBytesRange(null, USIZE_C(8), USIZE_C(0), USIZE_C(1));
    assert(result == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    result = GenMemOpsInnerSwapBytesRange(buf, USIZE_C(0), USIZE_C(0), USIZE_C(0));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(8)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
IndicesOutOfBounds(void)
{
    byte buf[8];
    byte buf_orig[8];
    bool result;

    printf(LOG_PREFIX_CSTR "IndicesOutOfBounds -> ");

    kdi_FillSeq(buf, USIZE_C(8), U8_C(0x20));
    kdi_FillSeq(buf_orig, USIZE_C(8), U8_C(0x20));

    /* idx_1 out of bounds (== base_sz) */
    result = GenMemOpsInnerSwapBytesRange(buf, USIZE_C(8), USIZE_C(8), USIZE_C(0));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(8)) == RESULT_SUCCESS);

    /* idx_2 out of bounds (== base_sz) */
    result = GenMemOpsInnerSwapBytesRange(buf, USIZE_C(8), USIZE_C(0), USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(8)) == RESULT_SUCCESS);

    /* both out of bounds */
    result = GenMemOpsInnerSwapBytesRange(buf, USIZE_C(8), USIZE_C(10), USIZE_C(12));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(8)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
ValidSwapLowIndex(void)
{
    byte buf[4];
    byte expected[4];
    bool result;

    printf(LOG_PREFIX_CSTR "ValidSwapLowIndex -> ");

    /* Init: 0x30, 0x31, 0x32, 0x33 */
    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x30));

    /* Expected: Swap index 0 and 1 -> 0x31, 0x30, 0x32, 0x33 */
    expected[0] = U8_C(0x31);
    expected[1] = U8_C(0x30);
    expected[2] = U8_C(0x32);
    expected[3] = U8_C(0x33);

    result      = GenMemOpsInnerSwapBytesRange(buf, USIZE_C(4), USIZE_C(0), USIZE_C(1));
    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
ValidSwapHighIndex(void)
{
    byte buf[4];
    byte expected[4];
    bool result;

    printf(LOG_PREFIX_CSTR "ValidSwapHighIndex -> ");

    /* Init: 0x40, 0x41, 0x42, 0x43 */
    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x40));

    /* Expected: Swap index 2 and 3 -> 0x40, 0x41, 0x43, 0x42 */
    expected[0] = U8_C(0x40);
    expected[1] = U8_C(0x41);
    expected[2] = U8_C(0x43);
    expected[3] = U8_C(0x42);

    result      = GenMemOpsInnerSwapBytesRange(buf, USIZE_C(4), USIZE_C(2), USIZE_C(3));
    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
ValidSwapEnds(void)
{
    byte buf[4];
    byte expected[4];
    bool result;

    printf(LOG_PREFIX_CSTR "ValidSwapEnds -> ");

    /* Init: 0x50, 0x51, 0x52, 0x53 */
    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x50));

    /* Expected: Swap index 0 and 3 -> 0x53, 0x51, 0x52, 0x50 */
    expected[0] = U8_C(0x53);
    expected[1] = U8_C(0x51);
    expected[2] = U8_C(0x52);
    expected[3] = U8_C(0x50);

    result      = GenMemOpsInnerSwapBytesRange(buf, USIZE_C(4), USIZE_C(0), USIZE_C(3));
    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SwapSameIndex(void)
{
    byte buf[4];
    byte expected[4];
    bool result;

    printf(LOG_PREFIX_CSTR "SwapSameIndex -> ");

    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x60));
    kdi_FillSeq(expected, USIZE_C(4), U8_C(0x60));

    /* Swap 2 with 2 -> no change */
    result = GenMemOpsInnerSwapBytesRange(buf, USIZE_C(4), USIZE_C(2), USIZE_C(2));
    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    IndicesOutOfBounds();
    ValidSwapLowIndex();
    ValidSwapHighIndex();
    ValidSwapEnds();
    SwapSameIndex();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
