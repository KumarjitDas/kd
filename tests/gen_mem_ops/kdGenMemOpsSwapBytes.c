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


void
Ptr1Null(void)
{
    u8   val2;
    bool status;

    printf(LOG_PREFIX_CSTR "Ptr1Null -> ");

    val2 = U8_C(0x22);

    /* ptr_1 is null -> failure */
    status = GenMemOpsSwapBytes(null, &val2);
    assert(status == RESULT_FAILURE);

    /* Verify val2 unchanged */
    assert(val2 == U8_C(0x22));

    printf("PASSED\n");
}


void
Ptr2Null(void)
{
    u8   val1;
    bool status;

    printf(LOG_PREFIX_CSTR "Ptr2Null -> ");

    val1 = U8_C(0x11);

    /* ptr_2 is null -> failure */
    status = GenMemOpsSwapBytes(&val1, null);
    assert(status == RESULT_FAILURE);

    /* Verify val1 unchanged */
    assert(val1 == U8_C(0x11));

    printf("PASSED\n");
}


void
BothNull(void)
{
    bool status;

    printf(LOG_PREFIX_CSTR "BothNull -> ");

    /* Both null -> failure */
    status = GenMemOpsSwapBytes(null, null);
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SwapSamePointer(void)
{
    u8   val;
    bool status;

    printf(LOG_PREFIX_CSTR "SwapSamePointer -> ");

    val = U8_C(0x42);

    /* Swap pointer with itself -> success, no change */
    status = GenMemOpsSwapBytes(&val, &val);
    assert(status == RESULT_SUCCESS);

    /* Value should remain unchanged */
    assert(val == U8_C(0x42));

    printf("PASSED\n");
}


void
SwapDifferentValues(void)
{
    u8   val1, val2;
    bool status;

    printf(LOG_PREFIX_CSTR "SwapDifferentValues -> ");

    val1 = U8_C(0xAA);
    val2 = U8_C(0xBB);

    status = GenMemOpsSwapBytes(&val1, &val2);
    assert(status == RESULT_SUCCESS);

    /* Values should be swapped */
    assert(val1 == U8_C(0xBB));
    assert(val2 == U8_C(0xAA));

    printf("PASSED\n");
}


void
SwapZeroAndNonZero(void)
{
    u8   val1, val2;
    bool status;

    printf(LOG_PREFIX_CSTR "SwapZeroAndNonZero -> ");

    val1 = U8_C(0x00);
    val2 = U8_C(0xFF);

    status = GenMemOpsSwapBytes(&val1, &val2);
    assert(status == RESULT_SUCCESS);

    assert(val1 == U8_C(0xFF));
    assert(val2 == U8_C(0x00));

    printf("PASSED\n");
}


void
SwapSameValues(void)
{
    u8   val1, val2;
    bool status;

    printf(LOG_PREFIX_CSTR "SwapSameValues -> ");

    val1 = U8_C(0x55);
    val2 = U8_C(0x55);

    status = GenMemOpsSwapBytes(&val1, &val2);
    assert(status == RESULT_SUCCESS);

    /* Both should still be 0x55 */
    assert(val1 == U8_C(0x55));
    assert(val2 == U8_C(0x55));

    printf("PASSED\n");
}


void
DoubleSwap(void)
{
    u8   val1, val2;
    u8   orig1, orig2;
    bool status;

    printf(LOG_PREFIX_CSTR "DoubleSwap -> ");

    val1 = U8_C(0x12);
    val2 = U8_C(0x34);
    orig1 = val1;
    orig2 = val2;

    /* Swap once */
    status = GenMemOpsSwapBytes(&val1, &val2);
    assert(status == RESULT_SUCCESS);

    /* Swap again - should restore */
    status = GenMemOpsSwapBytes(&val1, &val2);
    assert(status == RESULT_SUCCESS);

    /* Should be back to original */
    assert(val1 == orig1);
    assert(val2 == orig2);

    printf("PASSED\n");
}


void
SwapArrayElements(void)
{
    u8   arr[4];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapArrayElements -> ");

    arr[0] = U8_C(0x10);
    arr[1] = U8_C(0x20);
    arr[2] = U8_C(0x30);
    arr[3] = U8_C(0x40);

    /* Swap arr[0] and arr[3] */
    status = GenMemOpsSwapBytes(&arr[0], &arr[3]);
    assert(status == RESULT_SUCCESS);

    assert(arr[0] == U8_C(0x40));
    assert(arr[1] == U8_C(0x20));
    assert(arr[2] == U8_C(0x30));
    assert(arr[3] == U8_C(0x10));

    printf("PASSED\n");
}


void
SwapAdjacentElements(void)
{
    u8   arr[4];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapAdjacentElements -> ");

    arr[0] = U8_C(0x11);
    arr[1] = U8_C(0x22);
    arr[2] = U8_C(0x33);
    arr[3] = U8_C(0x44);

    /* Swap arr[1] and arr[2] */
    status = GenMemOpsSwapBytes(&arr[1], &arr[2]);
    assert(status == RESULT_SUCCESS);

    assert(arr[0] == U8_C(0x11));
    assert(arr[1] == U8_C(0x33));
    assert(arr[2] == U8_C(0x22));
    assert(arr[3] == U8_C(0x44));

    printf("PASSED\n");
}


void
MultipleSwaps(void)
{
    u8   arr[4];
    bool status;

    printf(LOG_PREFIX_CSTR "MultipleSwaps -> ");

    arr[0] = U8_C(0xA0);
    arr[1] = U8_C(0xA1);
    arr[2] = U8_C(0xA2);
    arr[3] = U8_C(0xA3);

    /* Swap 0 and 3 */
    status = GenMemOpsSwapBytes(&arr[0], &arr[3]);
    assert(status == RESULT_SUCCESS);

    /* Swap 1 and 2 */
    status = GenMemOpsSwapBytes(&arr[1], &arr[2]);
    assert(status == RESULT_SUCCESS);

    /* Expected: A3, A2, A1, A0 */
    assert(arr[0] == U8_C(0xA3));
    assert(arr[1] == U8_C(0xA2));
    assert(arr[2] == U8_C(0xA1));
    assert(arr[3] == U8_C(0xA0));

    printf("PASSED\n");
}


void
SwapStructMembers(void)
{
    struct {
        u8 a;
        u8 b;
        u8 c;
        u8 d;
    } data;
    bool status;

    printf(LOG_PREFIX_CSTR "SwapStructMembers -> ");

    data.a = U8_C(0x01);
    data.b = U8_C(0x02);
    data.c = U8_C(0x03);
    data.d = U8_C(0x04);

    /* Swap a and d */
    status = GenMemOpsSwapBytes(&data.a, &data.d);
    assert(status == RESULT_SUCCESS);

    assert(data.a == U8_C(0x04));
    assert(data.b == U8_C(0x02));
    assert(data.c == U8_C(0x03));
    assert(data.d == U8_C(0x01));

    printf("PASSED\n");
}


void
SwapBoundaryValues(void)
{
    u8   val1, val2;
    bool status;

    printf(LOG_PREFIX_CSTR "SwapBoundaryValues -> ");

    /* Test with min and max byte values */
    val1 = U8_C(0x00);
    val2 = U8_C(0xFF);

    status = GenMemOpsSwapBytes(&val1, &val2);
    assert(status == RESULT_SUCCESS);

    assert(val1 == U8_C(0xFF));
    assert(val2 == U8_C(0x00));

    printf("PASSED\n");
}


void
ChainSwap(void)
{
    u8   a, b, c;
    bool status;

    printf(LOG_PREFIX_CSTR "ChainSwap -> ");

    a = U8_C(0x11);
    b = U8_C(0x22);
    c = U8_C(0x33);

    /* Rotate values: a->b, b->c, c->a */
    /* Swap a and b */
    status = GenMemOpsSwapBytes(&a, &b);
    assert(status == RESULT_SUCCESS);
    /* Now: a=0x22, b=0x11, c=0x33 */

    /* Swap a and c */
    status = GenMemOpsSwapBytes(&a, &c);
    assert(status == RESULT_SUCCESS);
    /* Now: a=0x33, b=0x11, c=0x22 */

    /* Swap b and c */
    status = GenMemOpsSwapBytes(&b, &c);
    assert(status == RESULT_SUCCESS);
    /* Now: a=0x33, b=0x22, c=0x11 */

    assert(a == U8_C(0x33));
    assert(b == U8_C(0x22));
    assert(c == U8_C(0x11));

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    Ptr1Null();
    Ptr2Null();
    BothNull();
    SwapSamePointer();
    SwapDifferentValues();
    SwapZeroAndNonZero();
    SwapSameValues();
    DoubleSwap();
    SwapArrayElements();
    SwapAdjacentElements();
    MultipleSwaps();
    SwapStructMembers();
    SwapBoundaryValues();
    ChainSwap();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}