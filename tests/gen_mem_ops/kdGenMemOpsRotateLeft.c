/**
 * @file kdGenMemOpsRotateLeft.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsRotateLeft function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsRotateLeft function test"
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
kdi_FillSeq(u8 *dst, usize sz, u8 start)
{
    usize i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        dst[i] = (u8)(start + (u8)i);
    }
}


void
BasicArguments(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* ptr is null -> failure */
    status = GenMemOpsRotateLeft(null, USIZE_C(16), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* sz is zero -> success (trivial) */
    status = GenMemOpsRotateLeft(buf, USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* k is zero -> success (no op) */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));
    status = GenMemOpsRotateLeft(buf, USIZE_C(16), USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    assert(buf[0] == U8_C(0x00));
    assert(buf[15] == U8_C(0x0F));

    printf("PASSED\n");
}


void
RotateLeftSimple(void)
{
    u8   buf[5];
    u8   expected[5];
    bool status;

    printf(LOG_PREFIX_CSTR "RotateLeftSimple -> ");

    /* Init: 1, 2, 3, 4, 5 */
    kdi_FillSeq(buf, USIZE_C(5), U8_C(0x01));

    /* Rotate Left by 2 */
    /* Expected: 3, 4, 5, 1, 2 */
    expected[0] = 3;
    expected[1] = 4;
    expected[2] = 5;
    expected[3] = 1;
    expected[4] = 2;

    status      = GenMemOpsRotateLeft(buf, USIZE_C(5), USIZE_C(2));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(5)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
RotateLeftOne(void)
{
    u8   buf[4];
    u8   expected[4];
    bool status;

    printf(LOG_PREFIX_CSTR "RotateLeftOne -> ");

    /* Init: 10, 11, 12, 13 */
    kdi_FillSeq(buf, USIZE_C(4), U8_C(10));

    /* Rotate Left by 1 */
    /* Expected: 11, 12, 13, 10 */
    expected[0] = 11;
    expected[1] = 12;
    expected[2] = 13;
    expected[3] = 10;

    status      = GenMemOpsRotateLeft(buf, USIZE_C(4), USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
RotateLeftModulo(void)
{
    u8   buf[3];
    u8   expected[3];
    bool status;

    printf(LOG_PREFIX_CSTR "RotateLeftModulo -> ");

    /* Init: 1, 2, 3 */
    kdi_FillSeq(buf, USIZE_C(3), U8_C(1));

    /* Rotate Left by 4. (4 % 3 = 1) */
    /* Equivalent to Rotate Left by 1 */
    /* Expected: 2, 3, 1 */
    expected[0] = 2;
    expected[1] = 3;
    expected[2] = 1;

    status      = GenMemOpsRotateLeft(buf, USIZE_C(3), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(3)) == RESULT_SUCCESS);

    /* Rotate Left by 3 (Full cycle). Should return to start. */
    /* Current state: 2, 3, 1. Rotate 3 -> 2, 3, 1 */
    status = GenMemOpsRotateLeft(buf, USIZE_C(3), USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(3)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
RotateLeftLargeShift(void)
{
    u8   buf[4];
    u8   expected[4];
    bool status;

    printf(LOG_PREFIX_CSTR "RotateLeftLargeShift -> ");

    /* Init: 1, 2, 3, 4 */
    kdi_FillSeq(buf, USIZE_C(4), U8_C(1));

    /* Rotate Left by 10. (10 % 4 = 2) */
    /* Expected: 3, 4, 1, 2 */
    expected[0] = 3;
    expected[1] = 4;
    expected[2] = 1;
    expected[3] = 2;

    status      = GenMemOpsRotateLeft(buf, USIZE_C(4), USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
U16_RotateLeft(void)
{
    u16  buf[4];
    u16  expected[4];
    bool status;

    printf(LOG_PREFIX_CSTR "U16_RotateLeft -> ");

    /* Init: 10, 20, 30, 40 */
    buf[0]      = 10;
    buf[1]      = 20;
    buf[2]      = 30;
    buf[3]      = 40;

    /* Rotate Left by 1 element (sizeof(u16) bytes) */
    /* Expected: 20, 30, 40, 10 */
    expected[0] = 20;
    expected[1] = 30;
    expected[2] = 40;
    expected[3] = 10;

    status      = GenMemOpsRotateLeft(buf, sizeof(buf), sizeof(u16));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
U32_RotateLeft(void)
{
    u32  buf[5];
    u32  expected[5];
    bool status;

    printf(LOG_PREFIX_CSTR "U32_RotateLeft -> ");

    /* Init: 1, 2, 3, 4, 5 */
    buf[0]      = 1;
    buf[1]      = 2;
    buf[2]      = 3;
    buf[3]      = 4;
    buf[4]      = 5;

    /* Rotate Left by 2 elements (2 * sizeof(u32)) */
    /* Expected: 3, 4, 5, 1, 2 */
    expected[0] = 3;
    expected[1] = 4;
    expected[2] = 5;
    expected[3] = 1;
    expected[4] = 2;

    status      = GenMemOpsRotateLeft(buf, sizeof(buf), USIZE_C(2) * sizeof(u32));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_RotateLeft(void)
{
    u64  buf[3];
    u64  expected[3];
    bool status;

    printf(LOG_PREFIX_CSTR "U64_RotateLeft -> ");

    /* Init: A, B, C */
    buf[0]      = U64_C(0xAAAAAAAAAAAAAAAA);
    buf[1]      = U64_C(0xBBBBBBBBBBBBBBBB);
    buf[2]      = U64_C(0xCCCCCCCCCCCCCCCC);

    /* Rotate Left by 1 element */
    /* Expected: B, C, A */
    expected[0] = U64_C(0xBBBBBBBBBBBBBBBB);
    expected[1] = U64_C(0xCCCCCCCCCCCCCCCC);
    expected[2] = U64_C(0xAAAAAAAAAAAAAAAA);

    status      = GenMemOpsRotateLeft(buf, sizeof(buf), sizeof(u64));

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
Struct_RotateLeft(void)
{
    kdi_LargeStruct buf[4];
    kdi_LargeStruct expected[4];
    bool            status;

    printf(LOG_PREFIX_CSTR "Struct_RotateLeft -> ");

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

    /* Rotate Left by 1 struct */
    /* Expected: S1, S2, S3, S0 */
    expected[0] = buf[1];
    expected[1] = buf[2];
    expected[2] = buf[3];
    expected[3] = buf[0];

    status      = GenMemOpsRotateLeft(buf, sizeof(buf), sizeof(kdi_LargeStruct));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
LargeArray_RotateLeft(void)
{
    u8    buf[100];
    u8    expected[100];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeArray_RotateLeft -> ");

    /* Init: 0..99 */
    for (i = 0; i < 100; ++i)
        buf[i] = (u8)i;

    /* Rotate Left by 25 */
    /* Indices [0..24] move to back [75..99] */
    /* Indices [25..99] move to front [0..74] */

    /* Fill expected */
    for (i = 0; i < 75; ++i)
        expected[i] = (u8)(25 + i);
    for (i = 0; i < 25; ++i)
        expected[75 + i] = (u8)i;

    status = GenMemOpsRotateLeft(buf, USIZE_C(100), USIZE_C(25));

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
    RotateLeftSimple();
    RotateLeftOne();
    RotateLeftModulo();
    RotateLeftLargeShift();

    U16_RotateLeft();
    U32_RotateLeft();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_RotateLeft();
#endif
    Struct_RotateLeft();
    LargeArray_RotateLeft();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
