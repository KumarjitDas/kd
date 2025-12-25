/**
 * @file kdGenMemOpsInnerSwapBytes.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsInnerSwapBytes function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsInnerSwapBytes function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


static void
kdi_FillSeq(u8 *dst, usize sz, u8 start)
{
    usize i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        dst[i] = (u8)(start + (u8)i);
    }
}


void
NullPointer(void)
{
    bool status;

    printf(LOG_PREFIX_CSTR "NullPointer -> ");

    /* ptr is null -> failure */
    status = GenMemOpsInnerSwapBytes(null, USIZE_C(0), USIZE_C(1));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SwapDistinctIndices(void)
{
    u8   buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapDistinctIndices -> ");

    /* Init: 0x10, 0x11, 0x12, 0x13 */
    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x10));

    /* Swap index 0 and 3 */
    status = GenMemOpsInnerSwapBytes(buf, USIZE_C(0), USIZE_C(3));
    assert(status == RESULT_SUCCESS);

    /* Expected: 0x13, 0x11, 0x12, 0x10 */
    assert(buf[0] == U8_C(0x13));
    assert(buf[1] == U8_C(0x11));
    assert(buf[2] == U8_C(0x12));
    assert(buf[3] == U8_C(0x10));

    printf("PASSED\n");
}


void
SwapSameIndex(void)
{
    u8   buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapSameIndex -> ");

    /* Init: 0x20, 0x21, 0x22, 0x23 */
    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x20));

    /* Swap index 1 with itself */
    status = GenMemOpsInnerSwapBytes(buf, USIZE_C(1), USIZE_C(1));
    assert(status == RESULT_SUCCESS);

    /* Expected: unchanged */
    assert(buf[0] == U8_C(0x20));
    assert(buf[1] == U8_C(0x21));
    assert(buf[2] == U8_C(0x22));
    assert(buf[3] == U8_C(0x23));

    printf("PASSED\n");
}


void
SwapAdjacentIndices(void)
{
    u8   buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapAdjacentIndices -> ");

    /* Init: 0xA0, 0xA1, 0xA2, 0xA3 */
    kdi_FillSeq(buf, USIZE_C(4), U8_C(0xA0));

    /* Swap index 1 and 2 */
    status = GenMemOpsInnerSwapBytes(buf, USIZE_C(1), USIZE_C(2));
    assert(status == RESULT_SUCCESS);

    /* Expected: 0xA0, 0xA2, 0xA1, 0xA3 */
    assert(buf[0] == U8_C(0xA0));
    assert(buf[1] == U8_C(0xA2));
    assert(buf[2] == U8_C(0xA1));
    assert(buf[3] == U8_C(0xA3));

    printf("PASSED\n");
}


void
SwapFirstAndLast(void)
{
    u8   buf[8];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapFirstAndLast -> ");

    /* Init: 0x00, 0x01, ..., 0x07 */
    kdi_FillSeq(buf, USIZE_C(8), U8_C(0x00));

    /* Swap index 0 and 7 */
    status = GenMemOpsInnerSwapBytes(buf, USIZE_C(0), USIZE_C(7));
    assert(status == RESULT_SUCCESS);

    /* Expected: 0x07, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x00 */
    assert(buf[0] == U8_C(0x07));
    assert(buf[1] == U8_C(0x01));
    assert(buf[6] == U8_C(0x06));
    assert(buf[7] == U8_C(0x00));

    printf("PASSED\n");
}


void
SwapMiddleIndices(void)
{
    u8   buf[8];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapMiddleIndices -> ");

    /* Init: 0x00, 0x01, ..., 0x07 */
    kdi_FillSeq(buf, USIZE_C(8), U8_C(0x00));

    /* Swap index 3 and 5 */
    status = GenMemOpsInnerSwapBytes(buf, USIZE_C(3), USIZE_C(5));
    assert(status == RESULT_SUCCESS);

    /* Expected: 0x00, 0x01, 0x02, 0x05, 0x04, 0x03, 0x06, 0x07 */
    assert(buf[0] == U8_C(0x00));
    assert(buf[1] == U8_C(0x01));
    assert(buf[2] == U8_C(0x02));
    assert(buf[3] == U8_C(0x05));
    assert(buf[4] == U8_C(0x04));
    assert(buf[5] == U8_C(0x03));
    assert(buf[6] == U8_C(0x06));
    assert(buf[7] == U8_C(0x07));

    printf("PASSED\n");
}


void
SwapReversedIndices(void)
{
    u8   buf[8];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapReversedIndices -> ");

    /* Init: 0x00, 0x01, ..., 0x07 */
    kdi_FillSeq(buf, USIZE_C(8), U8_C(0x00));

    /* Swap index 6 and 2 (reverse order) */
    status = GenMemOpsInnerSwapBytes(buf, USIZE_C(6), USIZE_C(2));
    assert(status == RESULT_SUCCESS);

    /* Expected: 0x00, 0x01, 0x06, 0x03, 0x04, 0x05, 0x02, 0x07 */
    assert(buf[2] == U8_C(0x06));
    assert(buf[6] == U8_C(0x02));

    printf("PASSED\n");
}


void
DoubleSwap(void)
{
    u8    buf[4];
    u8    original[4];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "DoubleSwap -> ");

    /* Init: 0x50, 0x51, 0x52, 0x53 */
    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x50));

    /* Keep copy of original */
    for (i = USIZE_C(0); i < USIZE_C(4); ++i)
    {
        original[i] = buf[i];
    }

    /* Swap 0 and 2 */
    status = GenMemOpsInnerSwapBytes(buf, USIZE_C(0), USIZE_C(2));
    assert(status == RESULT_SUCCESS);

    /* Swap 0 and 2 again - should restore */
    status = GenMemOpsInnerSwapBytes(buf, USIZE_C(0), USIZE_C(2));
    assert(status == RESULT_SUCCESS);

    /* Verify restored to original */
    for (i = USIZE_C(0); i < USIZE_C(4); ++i)
    {
        assert(buf[i] == original[i]);
    }

    printf("PASSED\n");
}


void
MultipleSwaps(void)
{
    u8   buf[8];
    bool status;

    printf(LOG_PREFIX_CSTR "MultipleSwaps -> ");

    /* Init: 0x00, 0x01, ..., 0x07 */
    kdi_FillSeq(buf, USIZE_C(8), U8_C(0x00));

    /* Swap 0 and 7 */
    status = GenMemOpsInnerSwapBytes(buf, USIZE_C(0), USIZE_C(7));
    assert(status == RESULT_SUCCESS);

    /* Swap 1 and 6 */
    status = GenMemOpsInnerSwapBytes(buf, USIZE_C(1), USIZE_C(6));
    assert(status == RESULT_SUCCESS);

    /* Swap 2 and 5 */
    status = GenMemOpsInnerSwapBytes(buf, USIZE_C(2), USIZE_C(5));
    assert(status == RESULT_SUCCESS);

    /* Swap 3 and 4 */
    status = GenMemOpsInnerSwapBytes(buf, USIZE_C(3), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Expected: completely reversed */
    assert(buf[0] == U8_C(0x07));
    assert(buf[1] == U8_C(0x06));
    assert(buf[2] == U8_C(0x05));
    assert(buf[3] == U8_C(0x04));
    assert(buf[4] == U8_C(0x03));
    assert(buf[5] == U8_C(0x02));
    assert(buf[6] == U8_C(0x01));
    assert(buf[7] == U8_C(0x00));

    printf("PASSED\n");
}


void
SwapZeroIndex(void)
{
    u8   buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapZeroIndex -> ");

    /* Init: 0xAA, 0xBB, 0xCC, 0xDD */
    buf[0] = U8_C(0xAA);
    buf[1] = U8_C(0xBB);
    buf[2] = U8_C(0xCC);
    buf[3] = U8_C(0xDD);

    /* Swap index 0 with 0 */
    status = GenMemOpsInnerSwapBytes(buf, USIZE_C(0), USIZE_C(0));
    assert(status == RESULT_SUCCESS);

    /* Expected: unchanged */
    assert(buf[0] == U8_C(0xAA));
    assert(buf[1] == U8_C(0xBB));
    assert(buf[2] == U8_C(0xCC));
    assert(buf[3] == U8_C(0xDD));

    printf("PASSED\n");
}


void
SwapLargeBuffer(void)
{
    u8    buf[100];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "SwapLargeBuffer -> ");

    /* Init: 0..99 */
    kdi_FillSeq(buf, USIZE_C(100), U8_C(0));

    /* Swap index 10 and 90 */
    status = GenMemOpsInnerSwapBytes(buf, USIZE_C(10), USIZE_C(90));
    assert(status == RESULT_SUCCESS);

    /* Verify swap occurred */
    assert(buf[10] == U8_C(90));
    assert(buf[90] == U8_C(10));

    /* Verify other elements unchanged */
    for (i = USIZE_C(0); i < USIZE_C(10); ++i)
    {
        assert(buf[i] == (u8)i);
    }
    for (i = USIZE_C(11); i < USIZE_C(90); ++i)
    {
        assert(buf[i] == (u8)i);
    }
    for (i = USIZE_C(91); i < USIZE_C(100); ++i)
    {
        assert(buf[i] == (u8)i);
    }

    printf("PASSED\n");
}


void
SwapSameValues(void)
{
    u8   buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapSameValues -> ");

    /* Init: all same value */
    buf[0] = U8_C(0x77);
    buf[1] = U8_C(0x77);
    buf[2] = U8_C(0x77);
    buf[3] = U8_C(0x77);

    /* Swap index 0 and 3 */
    status = GenMemOpsInnerSwapBytes(buf, USIZE_C(0), USIZE_C(3));
    assert(status == RESULT_SUCCESS);

    /* Expected: still all same value */
    assert(buf[0] == U8_C(0x77));
    assert(buf[1] == U8_C(0x77));
    assert(buf[2] == U8_C(0x77));
    assert(buf[3] == U8_C(0x77));

    printf("PASSED\n");
}


void
SwapWithZeroBytes(void)
{
    u8   buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapWithZeroBytes -> ");

    buf[0] = U8_C(0x00);
    buf[1] = U8_C(0xFF);
    buf[2] = U8_C(0x00);
    buf[3] = U8_C(0xFF);

    /* Swap index 0 and 1 */
    status = GenMemOpsInnerSwapBytes(buf, USIZE_C(0), USIZE_C(1));
    assert(status == RESULT_SUCCESS);

    /* Expected: 0xFF, 0x00, 0x00, 0xFF */
    assert(buf[0] == U8_C(0xFF));
    assert(buf[1] == U8_C(0x00));
    assert(buf[2] == U8_C(0x00));
    assert(buf[3] == U8_C(0xFF));

    printf("PASSED\n");
}


void
SwapPattern(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapPattern -> ");

    /* Init: 0x00, 0x01, ..., 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Create a specific pattern with swaps */
    status = GenMemOpsInnerSwapBytes(buf, USIZE_C(0), USIZE_C(15));
    assert(status == RESULT_SUCCESS);
    status = GenMemOpsInnerSwapBytes(buf, USIZE_C(1), USIZE_C(14));
    assert(status == RESULT_SUCCESS);

    /* Verify specific swaps */
    assert(buf[0] == U8_C(0x0F));
    assert(buf[1] == U8_C(0x0E));
    assert(buf[14] == U8_C(0x01));
    assert(buf[15] == U8_C(0x00));

    /* Verify middle untouched */
    assert(buf[7] == U8_C(0x07));
    assert(buf[8] == U8_C(0x08));

    printf("PASSED\n");
}


void
ChainedSwaps(void)
{
    u8   buf[5];
    bool status;

    printf(LOG_PREFIX_CSTR "ChainedSwaps -> ");

    /* Init: 0xA0, 0xA1, 0xA2, 0xA3, 0xA4 */
    kdi_FillSeq(buf, USIZE_C(5), U8_C(0xA0));

    /* Rotate pattern: 0->1, 1->2, 2->3, 3->4, 4->0 */
    /* First get value at 0 */
    /* Swap 3 and 4 */
    status = GenMemOpsInnerSwapBytes(buf, USIZE_C(3), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Swap 2 and 3 */
    status = GenMemOpsInnerSwapBytes(buf, USIZE_C(2), USIZE_C(3));
    assert(status == RESULT_SUCCESS);

    /* Swap 1 and 2 */
    status = GenMemOpsInnerSwapBytes(buf, USIZE_C(1), USIZE_C(2));
    assert(status == RESULT_SUCCESS);

    /* Swap 0 and 1 */
    status = GenMemOpsInnerSwapBytes(buf, USIZE_C(0), USIZE_C(1));
    assert(status == RESULT_SUCCESS);

    /* Expected: 0xA1, 0xA2, 0xA3, 0xA4, 0xA0 */
    assert(buf[0] == U8_C(0xA4));
    assert(buf[1] == U8_C(0xA0));
    assert(buf[2] == U8_C(0xA1));
    assert(buf[3] == U8_C(0xA2));
    assert(buf[4] == U8_C(0xA3));

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    NullPointer();
    SwapDistinctIndices();
    SwapSameIndex();
    SwapAdjacentIndices();
    SwapFirstAndLast();
    SwapMiddleIndices();
    SwapReversedIndices();
    DoubleSwap();
    MultipleSwaps();
    SwapZeroIndex();
    SwapLargeBuffer();
    SwapSameValues();
    SwapWithZeroBytes();
    SwapPattern();
    ChainedSwaps();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
