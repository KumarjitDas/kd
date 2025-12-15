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

    /* ptr is null -> failure */
    result = GenMemOpsInnerSwapBytes(null, USIZE_C(0), USIZE_C(1));
    assert(result == RESULT_FAILURE);

    /* Valid ptr should succeed (indices validity relies on caller for this API) */
    result = GenMemOpsInnerSwapBytes(buf, USIZE_C(0), USIZE_C(1));
    assert(result == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SwapDistinctIndices(void)
{
    byte buf[4];
    byte expected[4];
    bool result;

    printf(LOG_PREFIX_CSTR "SwapDistinctIndices -> ");

    /* Init: 0x10, 0x11, 0x12, 0x13 */
    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x10));

    /* Expected: Swap index 0 and 3 -> 0x13, 0x11, 0x12, 0x10 */
    expected[0] = U8_C(0x13);
    expected[1] = U8_C(0x11);
    expected[2] = U8_C(0x12);
    expected[3] = U8_C(0x10);

    result      = GenMemOpsInnerSwapBytes(buf, USIZE_C(0), USIZE_C(3));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SwapSameIndex_IsNoOp(void)
{
    byte buf[4];
    byte expected[4];
    bool result;

    printf(LOG_PREFIX_CSTR "SwapSameIndex_IsNoOp -> ");

    /* Init: 0x20, 0x21, 0x22, 0x23 */
    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x20));
    kdi_FillSeq(expected, USIZE_C(4), U8_C(0x20));

    /* Swap index 1 with 1 */
    result = GenMemOpsInnerSwapBytes(buf, USIZE_C(1), USIZE_C(1));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SwapAdjacentIndices(void)
{
    byte buf[4];
    byte expected[4];
    bool result;

    printf(LOG_PREFIX_CSTR "SwapAdjacentIndices -> ");

    /* Init: 0xA0, 0xA1, 0xA2, 0xA3 */
    kdi_FillSeq(buf, USIZE_C(4), U8_C(0xA0));

    /* Swap index 1 and 2 -> 0xA0, 0xA2, 0xA1, 0xA3 */
    expected[0] = U8_C(0xA0);
    expected[1] = U8_C(0xA2);
    expected[2] = U8_C(0xA1);
    expected[3] = U8_C(0xA3);

    result      = GenMemOpsInnerSwapBytes(buf, USIZE_C(1), USIZE_C(2));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
DoubleSwapRestoresOriginal(void)
{
    byte buf[4];
    byte original[4];
    bool result;

    printf(LOG_PREFIX_CSTR "DoubleSwapRestoresOriginal -> ");

    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x50));
    kdi_FillSeq(original, USIZE_C(4), U8_C(0x50));

    /* Swap 0 and 2 */
    result = GenMemOpsInnerSwapBytes(buf, USIZE_C(0), USIZE_C(2));
    assert(result == RESULT_SUCCESS);
    /* Swap 0 and 2 again */
    result = GenMemOpsInnerSwapBytes(buf, USIZE_C(0), USIZE_C(2));
    assert(result == RESULT_SUCCESS);

    assert(kdi_BytesEqual(buf, original, USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    SwapDistinctIndices();
    SwapSameIndex_IsNoOp();
    SwapAdjacentIndices();
    DoubleSwapRestoresOriginal();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
