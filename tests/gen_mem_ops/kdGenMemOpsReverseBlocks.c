/**
 * @file kdGenMemOpsReverseBlocks.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsReverseBlocks function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsReverseBlocks function test"
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
    status = GenMemOpsReverseBlocks(null, USIZE_C(16), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = GenMemOpsReverseBlocks(buf, USIZE_C(16), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr_sz is zero -> success (trivial, 0 blocks) */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));
    status = GenMemOpsReverseBlocks(buf, USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(buf[0] == U8_C(0x00));

    printf("PASSED\n");
}


void
BlockSizeOne(void)
{
    u8   buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "BlockSizeOne -> ");

    /* Block size 1 = Byte Reverse */
    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x01)); /* 1, 2, 3, 4 */

    status = GenMemOpsReverseBlocks(buf, USIZE_C(4), USIZE_C(1));
    assert(status == RESULT_SUCCESS);

    /* Expected: 4, 3, 2, 1 */
    assert(buf[0] == U8_C(0x04));
    assert(buf[3] == U8_C(0x01));

    printf("PASSED\n");
}


void
U16_Blocks_AreReversedCorrectly(void)
{
    u16  buf[4];
    u16  expected[4];
    bool result;

    printf(LOG_PREFIX_CSTR "U16_Blocks_AreReversedCorrectly -> ");

    /* Init: 0x1111, 0x2222, 0x3333, 0x4444 */
    buf[0]      = U16_C(0x1111);
    buf[1]      = U16_C(0x2222);
    buf[2]      = U16_C(0x3333);
    buf[3]      = U16_C(0x4444);

    /* Expected Reverse: 0x4444, 0x3333, 0x2222, 0x1111 */
    expected[0] = U16_C(0x4444);
    expected[1] = U16_C(0x3333);
    expected[2] = U16_C(0x2222);
    expected[3] = U16_C(0x1111);

    result      = GenMemOpsReverseBlocks(buf, sizeof(buf), sizeof(u16));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
U32_Blocks_AreReversedCorrectly(void)
{
    u32  buf[3];
    u32  expected[3];
    bool result;

    printf(LOG_PREFIX_CSTR "U32_Blocks_AreReversedCorrectly -> ");

    /* Init: A, B, C */
    buf[0]      = U32_C(0xAAAAAAAA);
    buf[1]      = U32_C(0xBBBBBBBB);
    buf[2]      = U32_C(0xCCCCCCCC);

    /* Expected: C, B, A */
    expected[0] = U32_C(0xCCCCCCCC);
    expected[1] = U32_C(0xBBBBBBBB);
    expected[2] = U32_C(0xAAAAAAAA);

    result      = GenMemOpsReverseBlocks(buf, sizeof(buf), sizeof(u32));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_Blocks_AreReversedCorrectly(void)
{
    u64  buf[4];
    u64  expected[4];
    bool result;

    printf(LOG_PREFIX_CSTR "U64_Blocks_AreReversedCorrectly -> ");

    /* Init: 1, 2, 3, 4 */
    buf[0]      = U64_C(0x1111111111111111);
    buf[1]      = U64_C(0x2222222222222222);
    buf[2]      = U64_C(0x3333333333333333);
    buf[3]      = U64_C(0x4444444444444444);

    /* Expected: 4, 3, 2, 1 */
    expected[0] = U64_C(0x4444444444444444);
    expected[1] = U64_C(0x3333333333333333);
    expected[2] = U64_C(0x2222222222222222);
    expected[3] = U64_C(0x1111111111111111);

    result      = GenMemOpsReverseBlocks(buf, sizeof(buf), sizeof(u64));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}
#endif


typedef struct kdi_BigStruct
{
    u32 a;
    u32 b;
    u8  c;
} kdi_BigStruct;


void
Struct_Blocks_AreReversedCorrectly(void)
{
    kdi_BigStruct buf[3];
    kdi_BigStruct expected[3];
    bool          result;

    printf(LOG_PREFIX_CSTR "Struct_Blocks_AreReversedCorrectly -> ");

    /* Init: S1, S2, S3 */
    buf[0].a    = 1;
    buf[0].b    = 10;
    buf[0].c    = 100;
    buf[1].a    = 2;
    buf[1].b    = 20;
    buf[1].c    = 200;
    buf[2].a    = 3;
    buf[2].b    = 30;
    buf[2].c    = 220;

    /* Expected: S3, S2, S1 */
    expected[0] = buf[2];
    expected[1] = buf[1];
    expected[2] = buf[0];

    result      = GenMemOpsReverseBlocks(buf, sizeof(buf), sizeof(kdi_BigStruct));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
RemainderIgnored(void)
{
    u8   buf[10];
    bool status;

    printf(LOG_PREFIX_CSTR "RemainderIgnored -> ");

    /* Init: 0x00..0x09 */
    kdi_FillSeq(buf, USIZE_C(10), U8_C(0x00));

    /* Block size 4. 10 / 4 = 2 blocks. Remainder 2 bytes. */
    /* Blocks: [0,1,2,3] and [4,5,6,7]. Remainder [8,9] */
    /* Expected: [4,5,6,7] [0,1,2,3] [8,9] */

    status = GenMemOpsReverseBlocks(buf, USIZE_C(10), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Verify Block 0 (Swapped with 1) */
    assert(buf[0] == U8_C(0x04));

    /* Verify Block 1 (Swapped with 0) */
    assert(buf[4] == U8_C(0x00));

    /* Verify Remainder (Untouched) */
    assert(buf[8] == U8_C(0x08));
    assert(buf[9] == U8_C(0x09));

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    BlockSizeOne();

    U16_Blocks_AreReversedCorrectly();
    U32_Blocks_AreReversedCorrectly();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_Blocks_AreReversedCorrectly();
#endif
    Struct_Blocks_AreReversedCorrectly();

    RemainderIgnored();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
