/**
 * @file kdGenMemOpsSwapBytes.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsSwapBytes function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsSwapBytes function test"
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
    byte val = U8_C(0xAA);
    bool result;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* ptr_1 is null -> failure */
    result = GenMemOpsSwapBytes(null, &val);
    assert(result == RESULT_FAILURE);
    assert(val == U8_C(0xAA));

    /* ptr_2 is null -> failure */
    result = GenMemOpsSwapBytes(&val, null);
    assert(result == RESULT_FAILURE);
    assert(val == U8_C(0xAA));

    /* both null -> failure */
    result = GenMemOpsSwapBytes(null, null);
    assert(result == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SwapDistinctBytes(void)
{
    byte a = U8_C(0x10);
    byte b = U8_C(0x20);
    bool result;

    printf(LOG_PREFIX_CSTR "SwapDistinctBytes -> ");

    result = GenMemOpsSwapBytes(&a, &b);

    assert(result == RESULT_SUCCESS);
    assert(a == U8_C(0x20));
    assert(b == U8_C(0x10));

    printf("PASSED\n");
}


void
SwapSameAddress(void)
{
    byte a = U8_C(0x55);
    bool result;

    printf(LOG_PREFIX_CSTR "SwapSameAddress -> ");

    /* Swapping a byte with itself should succeed and be a no-op */
    result = GenMemOpsSwapBytes(&a, &a);

    assert(result == RESULT_SUCCESS);
    assert(a == U8_C(0x55));

    printf("PASSED\n");
}


void
SwapInArray(void)
{
    byte buf[4];
    byte expected[4];
    bool result;

    printf(LOG_PREFIX_CSTR "SwapInArray -> ");

    /* Init: 0x00, 0x01, 0x02, 0x03 */
    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x00));

    /* Swap index 1 and 2 */
    /* Expected: 0x00, 0x02, 0x01, 0x03 */
    expected[0] = U8_C(0x00);
    expected[1] = U8_C(0x02);
    expected[2] = U8_C(0x01);
    expected[3] = U8_C(0x03);

    result      = GenMemOpsSwapBytes(&buf[1], &buf[2]);

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
DoubleSwapRestoresOriginal(void)
{
    byte a = U8_C(0xAA);
    byte b = U8_C(0xBB);
    bool result;

    printf(LOG_PREFIX_CSTR "DoubleSwapRestoresOriginal -> ");

    /* First swap */
    result = GenMemOpsSwapBytes(&a, &b);
    assert(result == RESULT_SUCCESS);

    /* Second swap */
    result = GenMemOpsSwapBytes(&a, &b);
    assert(result == RESULT_SUCCESS);

    assert(a == U8_C(0xAA));
    assert(b == U8_C(0xBB));

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    SwapDistinctBytes();
    SwapSameAddress();
    SwapInArray();
    DoubleSwapRestoresOriginal();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
