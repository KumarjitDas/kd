/**
 * @file kdGenMemOpsSwapBytesRange.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsSwapBytesRange function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsSwapBytesRange function test"
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
    byte buf1[8];
    byte buf2[8];
    byte buf_orig[8];
    bool result;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillSeq(buf1, USIZE_C(8), U8_C(0x10));
    kdi_FillSeq(buf2, USIZE_C(8), U8_C(0x20));
    kdi_FillSeq(buf_orig, USIZE_C(8), U8_C(0x10));

    /* base_1 is null -> failure */
    result = GenMemOpsSwapBytesRange(null, USIZE_C(8), USIZE_C(0), buf2, USIZE_C(8), USIZE_C(0));
    assert(result == RESULT_FAILURE);

    /* base_2 is null -> failure */
    result = GenMemOpsSwapBytesRange(buf1, USIZE_C(8), USIZE_C(0), null, USIZE_C(8), USIZE_C(0));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf1, buf_orig, USIZE_C(8)) == RESULT_SUCCESS);

    /* base_1_sz is zero -> failure */
    result = GenMemOpsSwapBytesRange(buf1, USIZE_C(0), USIZE_C(0), buf2, USIZE_C(8), USIZE_C(0));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf1, buf_orig, USIZE_C(8)) == RESULT_SUCCESS);

    /* base_2_sz is zero -> failure */
    result = GenMemOpsSwapBytesRange(buf1, USIZE_C(8), USIZE_C(0), buf2, USIZE_C(0), USIZE_C(0));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf1, buf_orig, USIZE_C(8)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
IndicesOutOfBounds(void)
{
    byte buf1[8];
    byte buf2[8];
    byte buf1_orig[8];
    bool result;

    printf(LOG_PREFIX_CSTR "IndicesOutOfBounds -> ");

    kdi_FillSeq(buf1, USIZE_C(8), U8_C(0x30));
    kdi_FillSeq(buf2, USIZE_C(8), U8_C(0x40));
    kdi_FillSeq(buf1_orig, USIZE_C(8), U8_C(0x30));

    /* base_1_idx >= base_1_sz */
    result = GenMemOpsSwapBytesRange(buf1, USIZE_C(8), USIZE_C(8), buf2, USIZE_C(8), USIZE_C(0));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf1, buf1_orig, USIZE_C(8)) == RESULT_SUCCESS);

    /* base_2_idx >= base_2_sz */
    result = GenMemOpsSwapBytesRange(buf1, USIZE_C(8), USIZE_C(0), buf2, USIZE_C(8), USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf1, buf1_orig, USIZE_C(8)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SwapDistinctBuffers(void)
{
    byte buf1[4];
    byte buf2[4];
    byte expected1[4];
    byte expected2[4];
    bool result;

    printf(LOG_PREFIX_CSTR "SwapDistinctBuffers -> ");

    /* Init: buf1=0x10.., buf2=0x20.. */
    kdi_FillSeq(buf1, USIZE_C(4), U8_C(0x10));
    kdi_FillSeq(buf2, USIZE_C(4), U8_C(0x20));

    /* Expected: Swap buf1[1] (0x11) with buf2[2] (0x22) */
    /* buf1 -> 0x10, 0x22, 0x12, 0x13 */
    expected1[0] = U8_C(0x10);
    expected1[1] = U8_C(0x22);
    expected1[2] = U8_C(0x12);
    expected1[3] = U8_C(0x13);

    /* buf2 -> 0x20, 0x21, 0x11, 0x23 */
    expected2[0] = U8_C(0x20);
    expected2[1] = U8_C(0x21);
    expected2[2] = U8_C(0x11);
    expected2[3] = U8_C(0x23);

    result       = GenMemOpsSwapBytesRange(buf1, USIZE_C(4), USIZE_C(1), buf2, USIZE_C(4), USIZE_C(2));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf1, expected1, USIZE_C(4)) == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf2, expected2, USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SwapSameBufferDistinctIndices(void)
{
    byte buf[4];
    byte expected[4];
    bool result;

    printf(LOG_PREFIX_CSTR "SwapSameBufferDistinctIndices -> ");

    /* Init: 0x50, 0x51, 0x52, 0x53 */
    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x50));

    /* Expected: Swap index 0 (0x50) and 3 (0x53) -> 0x53, 0x51, 0x52, 0x50 */
    expected[0] = U8_C(0x53);
    expected[1] = U8_C(0x51);
    expected[2] = U8_C(0x52);
    expected[3] = U8_C(0x50);

    /* Pass same buffer as base_1 and base_2 */
    result      = GenMemOpsSwapBytesRange(buf, USIZE_C(4), USIZE_C(0), buf, USIZE_C(4), USIZE_C(3));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SwapSameBufferSameIndex(void)
{
    byte buf[4];
    byte expected[4];
    bool result;

    printf(LOG_PREFIX_CSTR "SwapSameBufferSameIndex -> ");

    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x60));
    kdi_FillSeq(expected, USIZE_C(4), U8_C(0x60));

    /* Swap index 2 with 2 -> no-op */
    result = GenMemOpsSwapBytesRange(buf, USIZE_C(4), USIZE_C(2), buf, USIZE_C(4), USIZE_C(2));

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
    SwapDistinctBuffers();
    SwapSameBufferDistinctIndices();
    SwapSameBufferSameIndex();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
