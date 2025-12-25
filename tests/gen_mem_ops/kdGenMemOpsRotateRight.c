/**
 * @file kdGenMemOpsRotateRight.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsRotateRight function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsRotateRight function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* ptr is null -> failure */
    status = GenMemOpsRotateRight(null, USIZE_C(16), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* sz is zero -> failure */
    status = GenMemOpsRotateRight(buf, USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* k is zero -> success (no op) */
    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x00));
    status = GenMemOpsRotateRight(buf, USIZE_C(16), USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    assert(buf[0] == U8_C(0x00));
    assert(buf[15] == U8_C(0x0F));

    printf("PASSED\n");
}


void
RotateRightSimple(void)
{
    u8   buf[5];
    u8   expected[5];
    bool status;

    printf(LOG_PREFIX_CSTR "RotateRightSimple -> ");

    /* Init: 1, 2, 3, 4, 5 */
    kdi_FillSeq_u8(buf, USIZE_C(5), U8_C(0x01));

    /* Rotate Right by 2 */
    /* Expected: 4, 5, 1, 2, 3 */
    expected[0] = 4;
    expected[1] = 5;
    expected[2] = 1;
    expected[3] = 2;
    expected[4] = 3;

    status      = GenMemOpsRotateRight(buf, USIZE_C(5), USIZE_C(2));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(5)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
RotateRightOne(void)
{
    u8   buf[4];
    u8   expected[4];
    bool status;

    printf(LOG_PREFIX_CSTR "RotateRightOne -> ");

    /* Init: 10, 11, 12, 13 */
    kdi_FillSeq_u8(buf, USIZE_C(4), U8_C(10));

    /* Rotate Right by 1 */
    /* Expected: 13, 10, 11, 12 */
    expected[0] = 13;
    expected[1] = 10;
    expected[2] = 11;
    expected[3] = 12;

    status      = GenMemOpsRotateRight(buf, USIZE_C(4), USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
RotateRightModulo(void)
{
    u8   buf[3];
    u8   expected[3];
    bool status;

    printf(LOG_PREFIX_CSTR "RotateRightModulo -> ");

    /* Init: 1, 2, 3 */
    kdi_FillSeq_u8(buf, USIZE_C(3), U8_C(1));

    /* Rotate Right by 4. (4 % 3 = 1) */
    /* Equivalent to Rotate Right by 1 */
    /* Expected: 3, 1, 2 */
    expected[0] = 3;
    expected[1] = 1;
    expected[2] = 2;

    status      = GenMemOpsRotateRight(buf, USIZE_C(3), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(3)) == RESULT_SUCCESS);

    /* Rotate Right by 3 (Full cycle). Should return to start. */
    /* Current state: 3, 1, 2. Rotate 3 -> 3, 1, 2 */
    status = GenMemOpsRotateRight(buf, USIZE_C(3), USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(3)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
RotateRightLargeShift(void)
{
    u8   buf[4];
    u8   expected[4];
    bool status;

    printf(LOG_PREFIX_CSTR "RotateRightLargeShift -> ");

    /* Init: 1, 2, 3, 4 */
    kdi_FillSeq_u8(buf, USIZE_C(4), U8_C(1));

    /* Rotate Right by 10. (10 % 4 = 2) */
    /* Expected: 3, 4, 1, 2 */
    expected[0] = 3;
    expected[1] = 4;
    expected[2] = 1;
    expected[3] = 2;

    status      = GenMemOpsRotateRight(buf, USIZE_C(4), USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
U16_RotateRight(void)
{
    u16  buf[4];
    u16  expected[4];
    bool status;

    printf(LOG_PREFIX_CSTR "U16_RotateRight -> ");

    /* Init: 10, 20, 30, 40 */
    buf[0]      = 10;
    buf[1]      = 20;
    buf[2]      = 30;
    buf[3]      = 40;

    /* Rotate Right by 1 element (sizeof(u16) bytes) */
    /* Expected: 40, 10, 20, 30 */
    expected[0] = 40;
    expected[1] = 10;
    expected[2] = 20;
    expected[3] = 30;

    status      = GenMemOpsRotateRight(buf, sizeof(buf), sizeof(u16));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
U32_RotateRight(void)
{
    u32  buf[5];
    u32  expected[5];
    bool status;

    printf(LOG_PREFIX_CSTR "U32_RotateRight -> ");

    /* Init: 1, 2, 3, 4, 5 */
    buf[0]      = 1;
    buf[1]      = 2;
    buf[2]      = 3;
    buf[3]      = 4;
    buf[4]      = 5;

    /* Rotate Right by 2 elements (2 * sizeof(u32)) */
    /* Expected: 4, 5, 1, 2, 3 */
    expected[0] = 4;
    expected[1] = 5;
    expected[2] = 1;
    expected[3] = 2;
    expected[4] = 3;

    status      = GenMemOpsRotateRight(buf, sizeof(buf), USIZE_C(2) * sizeof(u32));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_RotateRight(void)
{
    u64  buf[3];
    u64  expected[3];
    bool status;

    printf(LOG_PREFIX_CSTR "U64_RotateRight -> ");

    /* Init: A, B, C */
    buf[0]      = U64_C(0xAAAAAAAAAAAAAAAA);
    buf[1]      = U64_C(0xBBBBBBBBBBBBBBBB);
    buf[2]      = U64_C(0xCCCCCCCCCCCCCCCC);

    /* Rotate Right by 1 element */
    /* Expected: C, A, B */
    expected[0] = U64_C(0xCCCCCCCCCCCCCCCC);
    expected[1] = U64_C(0xAAAAAAAAAAAAAAAA);
    expected[2] = U64_C(0xBBBBBBBBBBBBBBBB);

    status      = GenMemOpsRotateRight(buf, sizeof(buf), sizeof(u64));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}
#endif


/* Struct significantly larger than 64 bits (approx 24 bytes) */
typedef struct kdi_LargeStruct
{
    u64 a;
    u64 b;
    u32 c;
    u8  d;
} kdi_LargeStruct;


void
Struct_RotateRight(void)
{
    kdi_LargeStruct buf[4];
    kdi_LargeStruct expected[4];
    bool            status;

    printf(LOG_PREFIX_CSTR "Struct_RotateRight -> ");

    /* Init: S0, S1, S2, S3 */
    buf[0].a    = 1;
    buf[0].b    = 10;
    buf[0].c    = 100;
    buf[0].d    = 255;
    buf[1].a    = 2;
    buf[1].b    = 20;
    buf[1].c    = 200;
    buf[1].d    = 254;
    buf[2].a    = 3;
    buf[2].b    = 30;
    buf[2].c    = 300;
    buf[2].d    = 253;
    buf[3].a    = 4;
    buf[3].b    = 40;
    buf[3].c    = 400;
    buf[3].d    = 252;

    /* Rotate Right by 1 struct */
    /* Expected: S3, S0, S1, S2 */
    expected[0] = buf[3];
    expected[1] = buf[0];
    expected[2] = buf[1];
    expected[3] = buf[2];

    status      = GenMemOpsRotateRight(buf, sizeof(buf), sizeof(kdi_LargeStruct));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
LargeArray_RotateRight(void)
{
    u8    buf[100];
    u8    expected[100];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeArray_RotateRight -> ");

    /* Init: 0..99 */
    for (i = 0; i < 100; ++i)
        buf[i] = (u8)i;

    /* Rotate Right by 25 */
    /* Indices [75..99] move to front [0..24] */
    /* Indices [0..74] move to back [25..99] */

    /* Fill expected */
    for (i = 0; i < 25; ++i)
        expected[i] = (u8)(75 + i);
    for (i = 0; i < 75; ++i)
        expected[25 + i] = (u8)i;

    status = GenMemOpsRotateRight(buf, USIZE_C(100), USIZE_C(25));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(100)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    RotateRightSimple();
    RotateRightOne();
    RotateRightModulo();
    RotateRightLargeShift();

    U16_RotateRight();
    U32_RotateRight();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_RotateRight();
#endif
    Struct_RotateRight();
    LargeArray_RotateRight();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
