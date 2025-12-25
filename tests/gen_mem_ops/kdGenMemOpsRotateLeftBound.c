/**
 * @file kdGenMemOpsRotateLeftBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsRotateLeftBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsRotateLeftBound function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BaseNull(void)
{
    bool status;

    printf(LOG_PREFIX_CSTR "BaseNull -> ");

    /* base is null -> failure */
    status = GenMemOpsRotateLeftBound(null, USIZE_C(16), USIZE_C(0), USIZE_C(4), USIZE_C(1));
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
    status = GenMemOpsRotateLeftBound(buf, USIZE_C(0), USIZE_C(0), USIZE_C(4), USIZE_C(1));
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
    status = GenMemOpsRotateLeftBound(buf, USIZE_C(16), USIZE_C(16), USIZE_C(4), USIZE_C(1));
    assert(status == RESULT_FAILURE);

    status = GenMemOpsRotateLeftBound(buf, USIZE_C(16), USIZE_C(20), USIZE_C(4), USIZE_C(1));
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
    status = GenMemOpsRotateLeftBound(buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), USIZE_C(0));
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
     * Rotate Left by 1: 0x0D, 0x0E, 0x0F, 0x0C
     */
    status = GenMemOpsRotateLeftBound(buf, USIZE_C(16), USIZE_C(12), USIZE_C(100), USIZE_C(1));
    assert(status == RESULT_SUCCESS);

    /* Verify pre-range unchanged */
    assert(buf[11] == U8_C(0x0B));

    /* Verify rotated range */
    assert(buf[12] == U8_C(0x0D));
    assert(buf[13] == U8_C(0x0E));
    assert(buf[14] == U8_C(0x0F));
    assert(buf[15] == U8_C(0x0C));

    printf("PASSED\n");
}


void
RotateLeftBoundSimple(void)
{
    u8   buf[8];
    u8   expected[8];
    bool status;

    printf(LOG_PREFIX_CSTR "RotateLeftBoundSimple -> ");

    /* Init: 0, 1, 2, 3, 4, 5, 6, 7 */
    kdi_FillSeq_u8(buf, USIZE_C(8), U8_C(0));

    /* Rotate range [2..6] (byte_count=5, values: 2,3,4,5,6) left by 2
     * Sub-sequence: 2, 3, 4, 5, 6
     * Rotate Left by 2: 4, 5, 6, 2, 3
     * Full Result: 0, 1, [4, 5, 6, 2, 3], 7
     */
    expected[0] = 0;
    expected[1] = 1;
    expected[2] = 4;
    expected[3] = 5;
    expected[4] = 6;
    expected[5] = 2;
    expected[6] = 3;
    expected[7] = 7;

    status      = GenMemOpsRotateLeftBound(buf, USIZE_C(8), USIZE_C(2), USIZE_C(5), USIZE_C(2));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(8)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
RotateLeftBoundOne(void)
{
    u8   buf[6];
    u8   expected[6];
    bool status;

    printf(LOG_PREFIX_CSTR "RotateLeftBoundOne -> ");

    /* Init: 10, 11, 12, 13, 14, 15 */
    kdi_FillSeq_u8(buf, USIZE_C(6), U8_C(10));

    /* Rotate range [1..3] (byte_count=3, values: 11,12,13) left by 1
     * Sub-sequence: 11, 12, 13
     * Rotate Left by 1: 12, 13, 11
     * Full Result: 10, [12, 13, 11], 14, 15
     */
    expected[0] = 10;
    expected[1] = 12;
    expected[2] = 13;
    expected[3] = 11;
    expected[4] = 14;
    expected[5] = 15;

    status      = GenMemOpsRotateLeftBound(buf, USIZE_C(6), USIZE_C(1), USIZE_C(3), USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(6)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
RotateLeftBoundModulo(void)
{
    u8   buf[5];
    u8   expected[5];
    bool status;

    printf(LOG_PREFIX_CSTR "RotateLeftBoundModulo -> ");

    /* Init: 0, 1, 2, 3, 4 */
    kdi_FillSeq_u8(buf, USIZE_C(5), U8_C(0));

    /* Rotate range [1..3] (byte_count=3, values: 1,2,3) left by 4
     * k=4, byte_count=3, effective k = 4 % 3 = 1
     * Sub-sequence: 1, 2, 3
     * Rotate Left by 1: 2, 3, 1
     * Full Result: 0, [2, 3, 1], 4
     */
    expected[0] = 0;
    expected[1] = 2;
    expected[2] = 3;
    expected[3] = 1;
    expected[4] = 4;

    status      = GenMemOpsRotateLeftBound(buf, USIZE_C(5), USIZE_C(1), USIZE_C(3), USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(5)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
RotateLeftBoundLargeShift(void)
{
    u8   buf[6];
    u8   expected[6];
    bool status;

    printf(LOG_PREFIX_CSTR "RotateLeftBoundLargeShift -> ");

    /* Init: 0, 1, 2, 3, 4, 5 */
    kdi_FillSeq_u8(buf, USIZE_C(6), U8_C(0));

    /* Rotate range [1..4] (byte_count=4, values: 1,2,3,4) left by 10
     * k=10, byte_count=4, effective k = 10 % 4 = 2
     * Sub-sequence: 1, 2, 3, 4
     * Rotate Left by 2: 3, 4, 1, 2
     * Full Result: 0, [3, 4, 1, 2], 5
     */
    expected[0] = 0;
    expected[1] = 3;
    expected[2] = 4;
    expected[3] = 1;
    expected[4] = 2;
    expected[5] = 5;

    status      = GenMemOpsRotateLeftBound(buf, USIZE_C(6), USIZE_C(1), USIZE_C(4), USIZE_C(10));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(6)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
RotateLeftBoundFullBuffer(void)
{
    u8   buf[5];
    u8   expected[5];
    bool status;

    printf(LOG_PREFIX_CSTR "RotateLeftBoundFullBuffer -> ");

    /* Init: 1, 2, 3, 4, 5 */
    kdi_FillSeq_u8(buf, USIZE_C(5), U8_C(1));

    /* Rotate full buffer [0..4] (byte_count=5) left by 2
     * Sub-sequence: 1, 2, 3, 4, 5
     * Rotate Left by 2: 3, 4, 5, 1, 2
     */
    expected[0] = 3;
    expected[1] = 4;
    expected[2] = 5;
    expected[3] = 1;
    expected[4] = 2;

    status      = GenMemOpsRotateLeftBound(buf, USIZE_C(5), USIZE_C(0), USIZE_C(5), USIZE_C(2));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(5)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
RotateLeftBoundBeginAtEnd(void)
{
    u8   buf[10];
    u8   expected[10];
    bool status;

    printf(LOG_PREFIX_CSTR "RotateLeftBoundBeginAtEnd -> ");

    /* Init: 0..9 */
    kdi_FillSeq_u8(buf, USIZE_C(10), U8_C(0));

    /* Rotate range [7..9] (byte_count=3, values: 7,8,9) left by 1
     * Sub-sequence: 7, 8, 9
     * Rotate Left by 1: 8, 9, 7
     * Full Result: 0,1,2,3,4,5,6, [8, 9, 7]
     */
    expected[0] = 0;
    expected[1] = 1;
    expected[2] = 2;
    expected[3] = 3;
    expected[4] = 4;
    expected[5] = 5;
    expected[6] = 6;
    expected[7] = 8;
    expected[8] = 9;
    expected[9] = 7;

    status      = GenMemOpsRotateLeftBound(buf, USIZE_C(10), USIZE_C(7), USIZE_C(3), USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(10)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
U16_RotateLeftBound(void)
{
    u16  buf[6];
    u16  expected[6];
    bool status;

    printf(LOG_PREFIX_CSTR "U16_RotateLeftBound -> ");

    /* Init: 0, 10, 20, 30, 40, 50 */
    buf[0] = 0;
    buf[1] = 10;
    buf[2] = 20;
    buf[3] = 30;
    buf[4] = 40;
    buf[5] = 50;

    /* Rotate range [1..4] (byte_count=4*sizeof(u16), values: 10,20,30,40) left by 1 element
     * k = sizeof(u16)
     * Sub-sequence: 10, 20, 30, 40
     * Rotate Left by 1: 20, 30, 40, 10
     * Full Result: 0, [20, 30, 40, 10], 50
     */
    expected[0] = 0;
    expected[1] = 20;
    expected[2] = 30;
    expected[3] = 40;
    expected[4] = 10;
    expected[5] = 50;

    status      = GenMemOpsRotateLeftBound(buf, sizeof(buf), sizeof(u16), USIZE_C(4) * sizeof(u16), sizeof(u16));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
U32_RotateLeftBound(void)
{
    u32  buf[5];
    u32  expected[5];
    bool status;

    printf(LOG_PREFIX_CSTR "U32_RotateLeftBound -> ");

    /* Init: 1, 2, 3, 4, 5 */
    buf[0] = 1;
    buf[1] = 2;
    buf[2] = 3;
    buf[3] = 4;
    buf[4] = 5;

    /* Rotate range [0..2] (byte_count=3*sizeof(u32), values: 1,2,3) left by 2 elements
     * k = 2 * sizeof(u32)
     * Sub-sequence: 1, 2, 3
     * Rotate Left by 2: 3, 1, 2
     * Full Result: [3, 1, 2], 4, 5
     */
    expected[0] = 3;
    expected[1] = 1;
    expected[2] = 2;
    expected[3] = 4;
    expected[4] = 5;

    status      = GenMemOpsRotateLeftBound(buf, sizeof(buf), 0, USIZE_C(3) * sizeof(u32), USIZE_C(2) * sizeof(u32));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_RotateLeftBound(void)
{
    u64  buf[4];
    u64  expected[4];
    bool status;

    printf(LOG_PREFIX_CSTR "U64_RotateLeftBound -> ");

    /* Init: 100, 200, 300, 400 */
    buf[0] = 100;
    buf[1] = 200;
    buf[2] = 300;
    buf[3] = 400;

    /* Rotate range [1..3] (byte_count=3*sizeof(u64), values: 200,300,400) left by 1 element
     * k = sizeof(u64)
     * Sub-sequence: 200, 300, 400
     * Rotate Left by 1: 300, 400, 200
     * Full Result: 100, [300, 400, 200]
     */
    expected[0] = 100;
    expected[1] = 300;
    expected[2] = 400;
    expected[3] = 200;

    status      = GenMemOpsRotateLeftBound(buf, sizeof(buf), sizeof(u64), USIZE_C(3) * sizeof(u64), sizeof(u64));
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
Struct_RotateLeftBound(void)
{
    kdi_LargeStruct buf[5];
    kdi_LargeStruct expected[5];
    bool            status;

    printf(LOG_PREFIX_CSTR "Struct_RotateLeftBound -> ");

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

    /* Rotate range [1..3] (byte_count=3*sizeof(struct), values: S1,S2,S3) left by 1 struct
     * k = sizeof(kdi_LargeStruct)
     * Sub-sequence: S1, S2, S3
     * Rotate Left by 1: S2, S3, S1
     * Full Result: S0, [S2, S3, S1], S4
     */
    expected[0] = buf[0];
    expected[1] = buf[2];
    expected[2] = buf[3];
    expected[3] = buf[1];
    expected[4] = buf[4];

    status      = GenMemOpsRotateLeftBound(buf, sizeof(buf), sizeof(kdi_LargeStruct), USIZE_C(3) * sizeof(kdi_LargeStruct), sizeof(kdi_LargeStruct));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
LargeArray_RotateLeftBound(void)
{
    u8    buf[100];
    u8    expected[100];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeArray_RotateLeftBound -> ");

    /* Init: 0..99 */
    for (i = 0; i < 100; ++i)
        buf[i] = (u8)i;

    /* Rotate range [20..79] (byte_count=60, values: 20..79) left by 10
     * k=10
     * The first 10 elements [20..29] move to end [70..79]
     * The last 50 elements [30..79] shift left to [20..69]
     */

    /* Pre-range [0..19] unchanged */
    for (i = 0; i < 20; ++i)
        expected[i] = (u8)i;

    /* Range part 1: old [30..79] -> new [20..69] */
    for (i = 0; i < 50; ++i)
        expected[20 + i] = (u8)(30 + i);

    /* Range part 2: old [20..29] -> new [70..79] */
    for (i = 0; i < 10; ++i)
        expected[70 + i] = (u8)(20 + i);

    /* Post-range [80..99] unchanged */
    for (i = 80; i < 100; ++i)
        expected[i] = (u8)i;

    status = GenMemOpsRotateLeftBound(buf, USIZE_C(100), USIZE_C(20), USIZE_C(60), USIZE_C(10));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(100)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
DoubleRotate(void)
{
    u8    buf[10];
    u8    original[10];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "DoubleRotate -> ");

    /* Init: 0..9 */
    kdi_FillSeq_u8(buf, USIZE_C(10), U8_C(0));

    /* Keep copy of original */
    for (i = USIZE_C(0); i < USIZE_C(10); ++i)
    {
        original[i] = buf[i];
    }

    /* Rotate range [2..7] (byte_count=6) left by 2 */
    status = GenMemOpsRotateLeftBound(buf, USIZE_C(10), USIZE_C(2), USIZE_C(6), USIZE_C(2));
    assert(status == RESULT_SUCCESS);

    /* Rotate same range right by 2 (should restore) */
    status = GenMemOpsRotateRightBound(buf, USIZE_C(10), USIZE_C(2), USIZE_C(6), USIZE_C(2));
    assert(status == RESULT_SUCCESS);

    /* Verify restored to original */
    for (i = USIZE_C(0); i < USIZE_C(10); ++i)
    {
        assert(buf[i] == original[i]);
    }

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
    RotateLeftBoundSimple();
    RotateLeftBoundOne();
    RotateLeftBoundModulo();
    RotateLeftBoundLargeShift();
    RotateLeftBoundFullBuffer();
    RotateLeftBoundBeginAtEnd();

    U16_RotateLeftBound();
    U32_RotateLeftBound();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_RotateLeftBound();
#endif
    Struct_RotateLeftBound();
    LargeArray_RotateLeftBound();
    DoubleRotate();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}