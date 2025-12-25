/**
 * @file kdGenMemOpsRotateRightBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsRotateRightBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsRotateRightBound function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BaseNull(void)
{
    bool status;

    printf(LOG_PREFIX_CSTR "BaseNull -> ");

    /* base is null -> failure */
    status = GenMemOpsRotateRightBound(null, USIZE_C(16), USIZE_C(0), USIZE_C(4), USIZE_C(1));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
BaseSizeZero(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BaseSizeZero -> ");

    /* base_sz is zero -> failure */
    status = GenMemOpsRotateRightBound(buf, USIZE_C(0), USIZE_C(0), USIZE_C(4), USIZE_C(1));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
BeginIdxOutOfBounds(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BeginIdxOutOfBounds -> ");

    /* begin_idx >= base_sz -> failure */
    status = GenMemOpsRotateRightBound(buf, USIZE_C(16), USIZE_C(16), USIZE_C(4), USIZE_C(1));
    assert(status == RESULT_FAILURE);

    status = GenMemOpsRotateRightBound(buf, USIZE_C(16), USIZE_C(20), USIZE_C(4), USIZE_C(1));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
KZero(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "KZero -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x00));

    /* k is zero -> success (no-op) */
    status = GenMemOpsRotateRightBound(buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), USIZE_C(0));
    assert(status == RESULT_SUCCESS);

    /* Verify unchanged */
    assert(buf[0] == U8_C(0x00));
    assert(buf[15] == U8_C(0x0F));

    printf("PASSED\n");
}


void
ByteCountClamping(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ByteCountClamping -> ");

    /* Init: 0x00 .. 0x0F */
    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Request: begin_idx=12, byte_count=100, k=1
     * Clamping: Available = 16 - 12 = 4 bytes (indices 12, 13, 14, 15)
     * Values: 0x0C, 0x0D, 0x0E, 0x0F
     * Rotate Right by 1: 0x0F, 0x0C, 0x0D, 0x0E
     */
    status = GenMemOpsRotateRightBound(buf, USIZE_C(16), USIZE_C(12), USIZE_C(100), USIZE_C(1));
    assert(status == RESULT_SUCCESS);

    /* Verify pre-range unchanged */
    assert(buf[11] == U8_C(0x0B));

    /* Verify rotated range */
    assert(buf[12] == U8_C(0x0F));
    assert(buf[13] == U8_C(0x0C));
    assert(buf[14] == U8_C(0x0D));
    assert(buf[15] == U8_C(0x0E));

    printf("PASSED\n");
}


void
RotateRightBoundSimple(void)
{
    u8   buf[8];
    u8   expected[8];
    bool status;

    printf(LOG_PREFIX_CSTR "RotateRightBoundSimple -> ");

    /* Init: 0, 1, 2, 3, 4, 5, 6, 7 */
    kdi_FillSeq_u8(buf, USIZE_C(8), U8_C(0));

    /* Rotate range [2..6] (byte_count=5, values: 2,3,4,5,6) right by 2
     * Sub-sequence: 2, 3, 4, 5, 6
     * Rotate Right by 2: 5, 6, 2, 3, 4
     * Full Result: 0, 1, [5, 6, 2, 3, 4], 7
     */
    expected[0] = 0;
    expected[1] = 1;
    expected[2] = 5;
    expected[3] = 6;
    expected[4] = 2;
    expected[5] = 3;
    expected[6] = 4;
    expected[7] = 7;

    status      = GenMemOpsRotateRightBound(buf, USIZE_C(8), USIZE_C(2), USIZE_C(5), USIZE_C(2));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(8)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
RotateRightBoundOne(void)
{
    u8   buf[6];
    u8   expected[6];
    bool status;

    printf(LOG_PREFIX_CSTR "RotateRightBoundOne -> ");

    /* Init: 10, 11, 12, 13, 14, 15 */
    kdi_FillSeq_u8(buf, USIZE_C(6), U8_C(10));

    /* Rotate range [1..3] (byte_count=3, values: 11,12,13) right by 1
     * Sub-sequence: 11, 12, 13
     * Rotate Right by 1: 13, 11, 12
     * Full Result: 10, [13, 11, 12], 14, 15
     */
    expected[0] = 10;
    expected[1] = 13;
    expected[2] = 11;
    expected[3] = 12;
    expected[4] = 14;
    expected[5] = 15;

    status      = GenMemOpsRotateRightBound(buf, USIZE_C(6), USIZE_C(1), USIZE_C(3), USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(6)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
RotateRightBoundModulo(void)
{
    u8   buf[5];
    u8   expected[5];
    bool status;

    printf(LOG_PREFIX_CSTR "RotateRightBoundModulo -> ");

    /* Init: 0, 1, 2, 3, 4 */
    kdi_FillSeq_u8(buf, USIZE_C(5), U8_C(0));

    /* Rotate range [1..3] (byte_count=3, values: 1,2,3) right by 4
     * k=4, byte_count=3, effective k = 4 % 3 = 1
     * Sub-sequence: 1, 2, 3
     * Rotate Right by 1: 3, 1, 2
     * Full Result: 0, [3, 1, 2], 4
     */
    expected[0] = 0;
    expected[1] = 3;
    expected[2] = 1;
    expected[3] = 2;
    expected[4] = 4;

    status      = GenMemOpsRotateRightBound(buf, USIZE_C(5), USIZE_C(1), USIZE_C(3), USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(5)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
RotateRightBoundLargeShift(void)
{
    u8   buf[6];
    u8   expected[6];
    bool status;

    printf(LOG_PREFIX_CSTR "RotateRightBoundLargeShift -> ");

    /* Init: 0, 1, 2, 3, 4, 5 */
    kdi_FillSeq_u8(buf, USIZE_C(6), U8_C(0));

    /* Rotate range [1..4] (byte_count=4, values: 1,2,3,4) right by 10
     * k=10, byte_count=4, effective k = 10 % 4 = 2
     * Sub-sequence: 1, 2, 3, 4
     * Rotate Right by 2: 3, 4, 1, 2
     * Full Result: 0, [3, 4, 1, 2], 5
     */
    expected[0] = 0;
    expected[1] = 3;
    expected[2] = 4;
    expected[3] = 1;
    expected[4] = 2;
    expected[5] = 5;

    status      = GenMemOpsRotateRightBound(buf, USIZE_C(6), USIZE_C(1), USIZE_C(4), USIZE_C(10));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(6)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
RotateRightBoundFullBuffer(void)
{
    u8   buf[5];
    u8   expected[5];
    bool status;

    printf(LOG_PREFIX_CSTR "RotateRightBoundFullBuffer -> ");

    /* Init: 1, 2, 3, 4, 5 */
    kdi_FillSeq_u8(buf, USIZE_C(5), U8_C(1));

    /* Rotate full buffer [0..4] (byte_count=5) right by 2
     * Sub-sequence: 1, 2, 3, 4, 5
     * Rotate Right by 2: 4, 5, 1, 2, 3
     */
    expected[0] = 4;
    expected[1] = 5;
    expected[2] = 1;
    expected[3] = 2;
    expected[4] = 3;

    status      = GenMemOpsRotateRightBound(buf, USIZE_C(5), USIZE_C(0), USIZE_C(5), USIZE_C(2));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(5)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
RotateRightBoundBeginAtEnd(void)
{
    u8   buf[10];
    u8   expected[10];
    bool status;

    printf(LOG_PREFIX_CSTR "RotateRightBoundBeginAtEnd -> ");

    /* Init: 0..9 */
    kdi_FillSeq_u8(buf, USIZE_C(10), U8_C(0));

    /* Rotate range [7..9] (byte_count=3, values: 7,8,9) right by 1
     * Sub-sequence: 7, 8, 9
     * Rotate Right by 1: 9, 7, 8
     * Full Result: 0,1,2,3,4,5,6, [9, 7, 8]
     */
    expected[0] = 0;
    expected[1] = 1;
    expected[2] = 2;
    expected[3] = 3;
    expected[4] = 4;
    expected[5] = 5;
    expected[6] = 6;
    expected[7] = 9;
    expected[8] = 7;
    expected[9] = 8;

    status      = GenMemOpsRotateRightBound(buf, USIZE_C(10), USIZE_C(7), USIZE_C(3), USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(10)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
U16_RotateRightBound(void)
{
    u16  buf[6];
    u16  expected[6];
    bool status;

    printf(LOG_PREFIX_CSTR "U16_RotateRightBound -> ");

    /* Init: 0, 10, 20, 30, 40, 50 */
    buf[0] = 0;
    buf[1] = 10;
    buf[2] = 20;
    buf[3] = 30;
    buf[4] = 40;
    buf[5] = 50;

    /* Rotate range [1..4] (byte_count=4*sizeof(u16), values: 10,20,30,40) right by 1 element
     * k = sizeof(u16)
     * Sub-sequence: 10, 20, 30, 40
     * Rotate Right by 1: 40, 10, 20, 30
     * Full Result: 0, [40, 10, 20, 30], 50
     */
    expected[0] = 0;
    expected[1] = 40;
    expected[2] = 10;
    expected[3] = 20;
    expected[4] = 30;
    expected[5] = 50;

    status      = GenMemOpsRotateRightBound(buf, sizeof(buf), sizeof(u16), USIZE_C(4) * sizeof(u16), sizeof(u16));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
U32_RotateRightBound(void)
{
    u32  buf[5];
    u32  expected[5];
    bool status;

    printf(LOG_PREFIX_CSTR "U32_RotateRightBound -> ");

    /* Init: 1, 2, 3, 4, 5 */
    buf[0] = 1;
    buf[1] = 2;
    buf[2] = 3;
    buf[3] = 4;
    buf[4] = 5;

    /* Rotate range [0..2] (byte_count=3*sizeof(u32), values: 1,2,3) right by 2 elements
     * k = 2 * sizeof(u32)
     * Sub-sequence: 1, 2, 3
     * Rotate Right by 2: 2, 3, 1
     * Full Result: [2, 3, 1], 4, 5
     */
    expected[0] = 2;
    expected[1] = 3;
    expected[2] = 1;
    expected[3] = 4;
    expected[4] = 5;

    status      = GenMemOpsRotateRightBound(buf, sizeof(buf), 0, USIZE_C(3) * sizeof(u32), USIZE_C(2) * sizeof(u32));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_RotateRightBound(void)
{
    u64  buf[4];
    u64  expected[4];
    bool status;

    printf(LOG_PREFIX_CSTR "U64_RotateRightBound -> ");

    /* Init: 100, 200, 300, 400 */
    buf[0] = 100;
    buf[1] = 200;
    buf[2] = 300;
    buf[3] = 400;

    /* Rotate range [1..3] (byte_count=3*sizeof(u64), values: 200,300,400) right by 1 element
     * k = sizeof(u64)
     * Sub-sequence: 200, 300, 400
     * Rotate Right by 1: 400, 200, 300
     * Full Result: 100, [400, 200, 300]
     */
    expected[0] = 100;
    expected[1] = 400;
    expected[2] = 200;
    expected[3] = 300;

    status      = GenMemOpsRotateRightBound(buf, sizeof(buf), sizeof(u64), USIZE_C(3) * sizeof(u64), sizeof(u64));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}
#endif


typedef struct kdi_LargeStruct
{
    u64 a;
    u64 b;
    u32 c;
    u8  d;
} kdi_LargeStruct;


void
Struct_RotateRightBound(void)
{
    kdi_LargeStruct buf[5];
    kdi_LargeStruct expected[5];
    bool            status;

    printf(LOG_PREFIX_CSTR "Struct_RotateRightBound -> ");

    /* Init: S0, S1, S2, S3, S4 */
    buf[0].a = 0;
    buf[0].b = 0;
    buf[0].c = 0;
    buf[0].d = 0;
    buf[1].a = 1;
    buf[1].b = 10;
    buf[1].c = 10;
    buf[1].d = 10;
    buf[2].a = 2;
    buf[2].b = 20;
    buf[2].c = 20;
    buf[2].d = 20;
    buf[3].a = 3;
    buf[3].b = 30;
    buf[3].c = 30;
    buf[3].d = 30;
    buf[4].a = 4;
    buf[4].b = 40;
    buf[4].c = 40;
    buf[4].d = 40;

    /* Rotate range [1..3] (byte_count=3*sizeof(struct), values: S1,S2,S3) right by 1 struct
     * k = sizeof(kdi_LargeStruct)
     * Sub-sequence: S1, S2, S3
     * Rotate Right by 1: S3, S1, S2
     * Full Result: S0, [S3, S1, S2], S4
     */
    expected[0] = buf[0];
    expected[1] = buf[3];
    expected[2] = buf[1];
    expected[3] = buf[2];
    expected[4] = buf[4];

    status      = GenMemOpsRotateRightBound(buf, sizeof(buf), sizeof(kdi_LargeStruct), USIZE_C(3) * sizeof(kdi_LargeStruct), sizeof(kdi_LargeStruct));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
LargeArray_RotateRightBound(void)
{
    u8    buf[100];
    u8    expected[100];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeArray_RotateRightBound -> ");

    /* Init: 0..99 */
    for (i = 0; i < 100; ++i)
        buf[i] = (u8)i;

    /* Rotate range [20..79] (byte_count=60, values: 20..79) right by 10
     * k=10
     * The last 10 elements [70..79] move to front [20..29]
     * The first 50 elements [20..69] shift right to [30..79]
     */

    /* Pre-range [0..19] unchanged */
    for (i = 0; i < 20; ++i)
        expected[i] = (u8)i;

    /* Range part 1: old [70..79] -> new [20..29] */
    for (i = 0; i < 10; ++i)
        expected[20 + i] = (u8)(70 + i);

    /* Range part 2: old [20..69] -> new [30..79] */
    for (i = 0; i < 50; ++i)
        expected[30 + i] = (u8)(20 + i);

    /* Post-range [80..99] unchanged */
    for (i = 80; i < 100; ++i)
        expected[i] = (u8)i;

    status = GenMemOpsRotateRightBound(buf, USIZE_C(100), USIZE_C(20), USIZE_C(60), USIZE_C(10));
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

    BaseNull();
    BaseSizeZero();
    BeginIdxOutOfBounds();
    KZero();
    ByteCountClamping();
    RotateRightBoundSimple();
    RotateRightBoundOne();
    RotateRightBoundModulo();
    RotateRightBoundLargeShift();
    RotateRightBoundFullBuffer();
    RotateRightBoundBeginAtEnd();

    U16_RotateRightBound();
    U32_RotateRightBound();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_RotateRightBound();
#endif
    Struct_RotateRightBound();
    LargeArray_RotateRightBound();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}