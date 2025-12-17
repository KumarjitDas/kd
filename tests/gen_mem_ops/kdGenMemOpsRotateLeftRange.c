/**
 * @file kdGenMemOpsRotateLeftRange.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsRotateLeftRange function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsRotateLeftRange function test"
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

    /* base is null -> failure */
    status = GenMemOpsRotateLeftRange(null, USIZE_C(16), USIZE_C(0), USIZE_C(4), USIZE_C(1));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = GenMemOpsRotateLeftRange(buf, USIZE_C(0), USIZE_C(0), USIZE_C(4), USIZE_C(1));
    assert(status == RESULT_FAILURE);

    /* count is zero -> success (trivial, nothing happens) */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));
    status = GenMemOpsRotateLeftRange(buf, USIZE_C(16), USIZE_C(0), USIZE_C(0), USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(buf[0] == U8_C(0x00));

    /* k is zero -> success (trivial, nothing happens) */
    status = GenMemOpsRotateLeftRange(buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    assert(buf[0] == U8_C(0x00));

    printf("PASSED\n");
}


void
CountClamping(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "CountClamping -> ");

    /* Init: 0x00 .. 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Request: Start 12, Count 100, k=1.
     * Clamping: Available = 16 - 12 = 4 bytes (indices 12, 13, 14, 15).
     * Values: 0x0C, 0x0D, 0x0E, 0x0F.
     * Rotate Left by 1: 0x0D, 0x0E, 0x0F, 0x0C.
     */
    status = GenMemOpsRotateLeftRange(buf, USIZE_C(16), USIZE_C(12), USIZE_C(100), USIZE_C(1));
    assert(status == RESULT_SUCCESS);

    /* Verify Pre-range (touched check) */
    assert(buf[11] == U8_C(0x0B));

    /* Verify Range */
    assert(buf[12] == U8_C(0x0D));
    assert(buf[13] == U8_C(0x0E));
    assert(buf[14] == U8_C(0x0F));
    assert(buf[15] == U8_C(0x0C));

    printf("PASSED\n");
}


void
IndicesOutOfBounds(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "IndicesOutOfBounds -> ");

    /* begin_idx >= base_sz -> failure */
    status = GenMemOpsRotateLeftRange(buf, USIZE_C(16), USIZE_C(16), USIZE_C(4), USIZE_C(1));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
RangeRotateLeft(void)
{
    u8   buf[8];
    u8   expected[8];
    bool status;

    printf(LOG_PREFIX_CSTR "RangeRotateLeft -> ");

    /* Init: 0, 1, 2, 3, 4, 5, 6, 7 */
    kdi_FillSeq(buf, USIZE_C(8), U8_C(0));

    /* Rotate range [2..6] (count 5) left by 2.
     * Sub-sequence: 2, 3, 4, 5, 6
     * Rotate Left 2: 4, 5, 6, 2, 3
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

    status      = GenMemOpsRotateLeftRange(buf, USIZE_C(8), USIZE_C(2), USIZE_C(5), USIZE_C(2));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(8)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
RangeRotateLeftModulo(void)
{
    u8   buf[5];
    u8   expected[5];
    bool status;

    printf(LOG_PREFIX_CSTR "RangeRotateLeftModulo -> ");

    /* Init: 0, 1, 2, 3, 4 */
    kdi_FillSeq(buf, USIZE_C(5), U8_C(0));

    /* Rotate range [1..3] (count 3: values 1, 2, 3) left by 4.
     * k = 4, count = 3. Effective k = 4 % 3 = 1.
     * Sub-sequence: 1, 2, 3
     * Rotate Left 1: 2, 3, 1
     * Full Result: 0, [2, 3, 1], 4
     */
    expected[0] = 0;
    expected[1] = 2;
    expected[2] = 3;
    expected[3] = 1;
    expected[4] = 4;

    status      = GenMemOpsRotateLeftRange(buf, USIZE_C(5), USIZE_C(1), USIZE_C(3), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(5)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


/* ------------------------------------------------------------------------------------------------------------------ */
/* New Tests */
/* ------------------------------------------------------------------------------------------------------------------ */

void
U16_RangeRotateLeft(void)
{
    u16  buf[6];
    u16  expected[6];
    bool status;

    printf(LOG_PREFIX_CSTR "U16_RangeRotateLeft -> ");

    /* Init: 0, 10, 20, 30, 40, 50 */
    buf[0]      = 0;
    buf[1]      = 10;
    buf[2]      = 20;
    buf[3]      = 30;
    buf[4]      = 40;
    buf[5]      = 50;

    /* Rotate range [1..4] (count 4 elements: 10, 20, 30, 40) left by 1 element.
     * k = sizeof(u16).
     * Sub-seq: 10, 20, 30, 40
     * Rotated: 20, 30, 40, 10
     * Full: 0, [20, 30, 40, 10], 50
     */
    expected[0] = 0;
    expected[1] = 20;
    expected[2] = 30;
    expected[3] = 40;
    expected[4] = 10;
    expected[5] = 50;

    status      = GenMemOpsRotateLeftRange(buf, sizeof(buf), sizeof(u16), USIZE_C(4) * sizeof(u16), sizeof(u16));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
U32_RangeRotateLeft(void)
{
    u32  buf[5];
    u32  expected[5];
    bool status;

    printf(LOG_PREFIX_CSTR "U32_RangeRotateLeft -> ");

    /* Init: 1, 2, 3, 4, 5 */
    buf[0]      = 1;
    buf[1]      = 2;
    buf[2]      = 3;
    buf[3]      = 4;
    buf[4]      = 5;

    /* Rotate range [0..2] (count 3 elements: 1, 2, 3) left by 2 elements.
     * Sub-seq: 1, 2, 3
     * Rotated 2: 3, 1, 2
     * Full: [3, 1, 2], 4, 5
     */
    expected[0] = 3;
    expected[1] = 1;
    expected[2] = 2;
    expected[3] = 4;
    expected[4] = 5;

    status      = GenMemOpsRotateLeftRange(buf, sizeof(buf), 0, USIZE_C(3) * sizeof(u32), USIZE_C(2) * sizeof(u32));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_RangeRotateLeft(void)
{
    u64  buf[4];
    u64  expected[4];
    bool status;

    printf(LOG_PREFIX_CSTR "U64_RangeRotateLeft -> ");

    /* Init: 100, 200, 300, 400 */
    buf[0]      = 100;
    buf[1]      = 200;
    buf[2]      = 300;
    buf[3]      = 400;

    /* Rotate range [1..3] (count 3 elements: 200, 300, 400) left by 1 element.
     * Sub-seq: 200, 300, 400
     * Rotated 1: 300, 400, 200
     * Full: 100, [300, 400, 200]
     */
    expected[0] = 100;
    expected[1] = 300;
    expected[2] = 400;
    expected[3] = 200;

    status      = GenMemOpsRotateLeftRange(buf, sizeof(buf), sizeof(u64), USIZE_C(3) * sizeof(u64), sizeof(u64));

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
Struct_RangeRotateLeft(void)
{
    kdi_LargeStruct buf[5];
    kdi_LargeStruct expected[5];
    bool            status;

    printf(LOG_PREFIX_CSTR "Struct_RangeRotateLeft -> ");

    /* Init: S0, S1, S2, S3, S4 */
    buf[0].a    = 0;
    buf[0].b    = 0;
    buf[0].c    = 0;
    buf[0].d    = 0;
    buf[1].a    = 1;
    buf[1].b    = 10;
    buf[1].c    = 10;
    buf[1].d    = 10;
    buf[2].a    = 2;
    buf[2].b    = 20;
    buf[2].c    = 20;
    buf[2].d    = 20;
    buf[3].a    = 3;
    buf[3].b    = 30;
    buf[3].c    = 30;
    buf[3].d    = 30;
    buf[4].a    = 4;
    buf[4].b    = 40;
    buf[4].c    = 40;
    buf[4].d    = 40;

    /* Rotate range [1..3] (count 3: S1, S2, S3) left by 1 struct.
     * Sub-seq: S1, S2, S3
     * Rotated 1: S2, S3, S1
     * Full: S0, [S2, S3, S1], S4
     */
    expected[0] = buf[0];
    expected[1] = buf[2];
    expected[2] = buf[3];
    expected[3] = buf[1];
    expected[4] = buf[4];

    status      = GenMemOpsRotateLeftRange(buf, sizeof(buf), sizeof(kdi_LargeStruct), USIZE_C(3) * sizeof(kdi_LargeStruct), sizeof(kdi_LargeStruct));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
LargeArray_RangeRotateLeft(void)
{
    u8    buf[100];
    u8    expected[100];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeArray_RangeRotateLeft -> ");

    /* Init: 0..99 */
    for (i = 0; i < 100; ++i)
        buf[i] = (u8)i;

    /* Rotate range [20..79] (count 60) left by 10.
     * Range: 20..79
     * k = 10.
     * The first 10 elements [20..29] move to back [70..79].
     * The rest [30..79] shift left to [20..69].
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

    status = GenMemOpsRotateLeftRange(buf, USIZE_C(100), USIZE_C(20), USIZE_C(60), USIZE_C(10));

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
    CountClamping();
    IndicesOutOfBounds();
    RangeRotateLeft();
    RangeRotateLeftModulo();

    U16_RangeRotateLeft();
    U32_RangeRotateLeft();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_RangeRotateLeft();
#endif
    Struct_RangeRotateLeft();
    LargeArray_RangeRotateLeft();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
