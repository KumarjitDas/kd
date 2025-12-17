/**
 * @file kdGenMemOpsReverseBlocksRange.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsReverseBlocksRange function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsReverseBlocksRange function test"
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
    status = GenMemOpsReverseBlocksRange(null, USIZE_C(16), USIZE_C(0), USIZE_C(16), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = GenMemOpsReverseBlocksRange(buf, USIZE_C(0), USIZE_C(0), USIZE_C(4), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = GenMemOpsReverseBlocksRange(buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* byte_count is zero -> success (trivial, nothing changes) */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));
    status = GenMemOpsReverseBlocksRange(buf, USIZE_C(16), USIZE_C(0), USIZE_C(0), USIZE_C(4));
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

    /* Request: Start 10, Count 100, Block 2.
     * Clamping: Available = 16 - 10 = 6 bytes.
     * Count becomes 6.
     * Blocks: 3 blocks of size 2 at indices [10,11], [12,13], [14,15].
     * Reverse them: [14,15], [12,13], [10,11].
     */
    status = GenMemOpsReverseBlocksRange(buf, USIZE_C(16), USIZE_C(10), USIZE_C(100), USIZE_C(2));
    assert(status == RESULT_SUCCESS);

    /* Verify Pre-range (touched check) */
    assert(buf[9] == U8_C(0x09));

    /* Verify Range */
    /* Index 10,11 should hold old 14,15 (0x0E, 0x0F) */
    assert(buf[10] == U8_C(0x0E));
    assert(buf[11] == U8_C(0x0F));

    /* Index 12,13 should hold old 12,13 (0x0C, 0x0D) - Middle block stays */
    assert(buf[12] == U8_C(0x0C));
    assert(buf[13] == U8_C(0x0D));

    /* Index 14,15 should hold old 10,11 (0x0A, 0x0B) */
    assert(buf[14] == U8_C(0x0A));
    assert(buf[15] == U8_C(0x0B));

    printf("PASSED\n");
}


void
IndicesOutOfBounds(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "IndicesOutOfBounds -> ");

    /* begin_idx >= base_sz -> failure */
    status = GenMemOpsReverseBlocksRange(buf, USIZE_C(16), USIZE_C(16), USIZE_C(4), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
U16_Blocks_RangeReverse(void)
{
    u16  buf[6];
    u16  expected[6];
    bool result;

    printf(LOG_PREFIX_CSTR "U16_Blocks_RangeReverse -> ");

    /* Init: 0, 1, 2, 3, 4, 5 */
    buf[0]      = 0;
    buf[1]      = 1;
    buf[2]      = 2;
    buf[3]      = 3;
    buf[4]      = 4;
    buf[5]      = 5;

    /* Request: Start index 1 (offset 1 * sizeof(u16)), Count 4 * sizeof(u16), Block sizeof(u16) */
    /* Range in elements: indices 1, 2, 3, 4 */
    /* Sub-sequence to reverse: 1, 2, 3, 4 */
    /* Expected sub-sequence:   4, 3, 2, 1 */
    /* Full Expected: 0, 4, 3, 2, 1, 5 */

    expected[0] = 0;
    expected[1] = 4;
    expected[2] = 3;
    expected[3] = 2;
    expected[4] = 1;
    expected[5] = 5;

    result      = GenMemOpsReverseBlocksRange(buf, sizeof(buf), sizeof(u16), USIZE_C(4) * sizeof(u16), sizeof(u16));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
U32_Blocks_RangeReverse(void)
{
    u32  buf[5];
    u32  expected[5];
    bool result;

    printf(LOG_PREFIX_CSTR "U32_Blocks_RangeReverse -> ");

    /* Init: 10, 20, 30, 40, 50 */
    buf[0]      = 10;
    buf[1]      = 20;
    buf[2]      = 30;
    buf[3]      = 40;
    buf[4]      = 50;

    /* Reverse middle 3 blocks (indices 1, 2, 3) */
    /* Expected: 10, 40, 30, 20, 50 */
    expected[0] = 10;
    expected[1] = 40;
    expected[2] = 30;
    expected[3] = 20;
    expected[4] = 50;

    result      = GenMemOpsReverseBlocksRange(buf, sizeof(buf), sizeof(u32), USIZE_C(3) * sizeof(u32), sizeof(u32));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_Blocks_RangeReverse(void)
{
    u64  buf[6];
    u64  expected[6];
    bool result;

    printf(LOG_PREFIX_CSTR "U64_Blocks_RangeReverse -> ");

    /* Init: 0, 10, 20, 30, 40, 50 */
    buf[0]      = U64_C(0);
    buf[1]      = U64_C(10);
    buf[2]      = U64_C(20);
    buf[3]      = U64_C(30);
    buf[4]      = U64_C(40);
    buf[5]      = U64_C(50);

    /* Reverse indices 2, 3, 4 (Start at index 2, count 3 blocks) */
    /* Values to reverse: 20, 30, 40 */
    /* Result: 40, 30, 20 */

    expected[0] = U64_C(0);
    expected[1] = U64_C(10);
    expected[2] = U64_C(40);
    expected[3] = U64_C(30);
    expected[4] = U64_C(20);
    expected[5] = U64_C(50);

    result      = GenMemOpsReverseBlocksRange(buf, sizeof(buf), USIZE_C(2) * sizeof(u64), USIZE_C(3) * sizeof(u64), sizeof(u64));

    assert(result == RESULT_SUCCESS);
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
    /* Total size >= 8+8+4+1 = 21 bytes */
} kdi_LargeStruct;


void
Struct_Blocks_RangeReverse(void)
{
    kdi_LargeStruct buf[4];
    kdi_LargeStruct expected[4];
    bool            result;

    printf(LOG_PREFIX_CSTR "Struct_Blocks_RangeReverse -> ");

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

    /* Reverse first 3 structs: S0, S1, S2 -> S2, S1, S0 */
    /* Expected: S2, S1, S0, S3 */
    expected[0] = buf[2];
    expected[1] = buf[1];
    expected[2] = buf[0];
    expected[3] = buf[3];

    result      = GenMemOpsReverseBlocksRange(buf, sizeof(buf), USIZE_C(0), USIZE_C(3) * sizeof(kdi_LargeStruct), sizeof(kdi_LargeStruct));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
RemainderIgnoredInRange(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "RemainderIgnoredInRange -> ");

    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Start 0, Count 10, Block 4.
     * Range: [0..9] (10 bytes).
     * Blocks: 10 / 4 = 2 blocks ([0..3], [4..7]).
     * Remainder: 2 bytes ([8..9]).
     * Swap the 2 blocks: [4,5,6,7] and [0,1,2,3].
     * Remainder [8,9] untouched.
     * Tail [10..15] untouched.
     */
    status = GenMemOpsReverseBlocksRange(buf, USIZE_C(16), USIZE_C(0), USIZE_C(10), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Check Block 0 (now contains old Block 1: 04,05,06,07) */
    assert(buf[0] == U8_C(0x04));

    /* Check Block 1 (now contains old Block 0: 00,01,02,03) */
    assert(buf[4] == U8_C(0x00));

    /* Check Remainder (08,09) */
    assert(buf[8] == U8_C(0x08));
    assert(buf[9] == U8_C(0x09));

    /* Check outside range */
    assert(buf[10] == U8_C(0x0A));

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

    U16_Blocks_RangeReverse();
    U32_Blocks_RangeReverse();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_Blocks_RangeReverse();
#endif
    Struct_Blocks_RangeReverse();

    RemainderIgnoredInRange();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
