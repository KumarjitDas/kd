/**
 * @file kdGenMemOpsInnerSwapBlocks.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsInnerSwapBlocks function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsInnerSwapBlocks function test"
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
NullPointer(void)
{
    bool status;

    printf(LOG_PREFIX_CSTR "NullPointer -> ");

    /* ptr is null -> failure */
    status = GenMemOpsInnerSwapBlocks(null, USIZE_C(0), USIZE_C(4), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ZeroBlockSize(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ZeroBlockSize -> ");

    /* Init buffer */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* block_sz is zero -> failure */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(0), USIZE_C(4), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* Verify buffer unchanged */
    assert(buf[0] == U8_C(0x00));
    assert(buf[15] == U8_C(0x0F));

    printf("PASSED\n");
}


void
Idx1Misaligned(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "Idx1Misaligned -> ");

    /* Init buffer */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* idx_1 not aligned to block_sz -> failure */
    /* idx_1=5, block_sz=4: 5 % 4 = 1, not aligned */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(5), USIZE_C(8), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* idx_1=3, block_sz=2: 3 % 2 = 1, not aligned */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(3), USIZE_C(8), USIZE_C(2));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
Idx2Misaligned(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "Idx2Misaligned -> ");

    /* Init buffer */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* idx_2 not aligned to block_sz -> failure */
    /* idx_2=5, block_sz=4: 5 % 4 = 1, not aligned */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(0), USIZE_C(5), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* idx_2=7, block_sz=2: 7 % 2 = 1, not aligned */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(0), USIZE_C(7), USIZE_C(2));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
BothIndicesMisaligned(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BothIndicesMisaligned -> ");

    /* Init buffer */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Both indices misaligned -> failure */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(5), USIZE_C(9), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SwapSameIndex(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapSameIndex -> ");

    /* Init: 0x00..0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Swap block at index 4 with itself (block_sz=4) */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(4), USIZE_C(4), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Expected: unchanged */
    assert(buf[4] == U8_C(0x04));
    assert(buf[5] == U8_C(0x05));
    assert(buf[6] == U8_C(0x06));
    assert(buf[7] == U8_C(0x07));

    printf("PASSED\n");
}


void
SwapAdjacentBlocks_Size2(void)
{
    u8   buf[8];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapAdjacentBlocks_Size2 -> ");

    /* Init: 0x00..0x07 */
    kdi_FillSeq(buf, USIZE_C(8), U8_C(0x00));

    /* Block size 2. Swap index 0 (bytes 0-1) and index 2 (bytes 2-3) */
    /* Original: [00 01] [02 03] [04 05 06 07] */
    /* Expected: [02 03] [00 01] [04 05 06 07] */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(0), USIZE_C(2), USIZE_C(2));
    assert(status == RESULT_SUCCESS);

    assert(buf[0] == U8_C(0x02));
    assert(buf[1] == U8_C(0x03));
    assert(buf[2] == U8_C(0x00));
    assert(buf[3] == U8_C(0x01));
    assert(buf[4] == U8_C(0x04));
    assert(buf[5] == U8_C(0x05));
    assert(buf[6] == U8_C(0x06));
    assert(buf[7] == U8_C(0x07));

    printf("PASSED\n");
}


void
SwapAdjacentBlocks_Size4(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapAdjacentBlocks_Size4 -> ");

    /* Init: 0x00..0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Block size 4. Swap index 0 (bytes 0-3) and index 4 (bytes 4-7) */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(0), USIZE_C(4), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Expected: [04 05 06 07] [00 01 02 03] [08..0F] */
    assert(buf[0] == U8_C(0x04));
    assert(buf[1] == U8_C(0x05));
    assert(buf[2] == U8_C(0x06));
    assert(buf[3] == U8_C(0x07));
    assert(buf[4] == U8_C(0x00));
    assert(buf[5] == U8_C(0x01));
    assert(buf[6] == U8_C(0x02));
    assert(buf[7] == U8_C(0x03));
    assert(buf[8] == U8_C(0x08));

    printf("PASSED\n");
}


void
SwapDistantBlocks(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapDistantBlocks -> ");

    /* Init: 0x00..0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Block size 4. Swap index 0 (bytes 0-3) and index 12 (bytes 12-15) */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(0), USIZE_C(12), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Expected: [0C 0D 0E 0F] [04..0B] [00 01 02 03] */
    assert(buf[0] == U8_C(0x0C));
    assert(buf[1] == U8_C(0x0D));
    assert(buf[2] == U8_C(0x0E));
    assert(buf[3] == U8_C(0x0F));
    assert(buf[4] == U8_C(0x04));
    assert(buf[11] == U8_C(0x0B));
    assert(buf[12] == U8_C(0x00));
    assert(buf[13] == U8_C(0x01));
    assert(buf[14] == U8_C(0x02));
    assert(buf[15] == U8_C(0x03));

    printf("PASSED\n");
}


void
SwapMiddleBlocks(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapMiddleBlocks -> ");

    /* Init: 0x00..0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Block size 2. Swap index 4 (bytes 4-5) and index 10 (bytes 10-11) */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(4), USIZE_C(10), USIZE_C(2));
    assert(status == RESULT_SUCCESS);

    /* Verify pre-swap region */
    assert(buf[3] == U8_C(0x03));

    /* Verify first swapped block */
    assert(buf[4] == U8_C(0x0A));
    assert(buf[5] == U8_C(0x0B));

    /* Verify middle region */
    assert(buf[6] == U8_C(0x06));
    assert(buf[9] == U8_C(0x09));

    /* Verify second swapped block */
    assert(buf[10] == U8_C(0x04));
    assert(buf[11] == U8_C(0x05));

    /* Verify post-swap region */
    assert(buf[12] == U8_C(0x0C));

    printf("PASSED\n");
}


void
SwapReversedIndices(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapReversedIndices -> ");

    /* Init: 0x00..0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Block size 4. Swap index 12 and index 0 (reverse order) */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(12), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Expected: same as SwapDistantBlocks */
    assert(buf[0] == U8_C(0x0C));
    assert(buf[3] == U8_C(0x0F));
    assert(buf[12] == U8_C(0x00));
    assert(buf[15] == U8_C(0x03));

    printf("PASSED\n");
}


void
DoubleSwap(void)
{
    u8    buf[16];
    u8    original[16];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "DoubleSwap -> ");

    /* Init: 0x00..0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Keep copy of original */
    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        original[i] = buf[i];
    }

    /* Swap index 0 and 8 (block_sz=4) */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(0), USIZE_C(8), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Swap index 0 and 8 again - should restore */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(0), USIZE_C(8), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Verify restored to original */
    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        assert(buf[i] == original[i]);
    }

    printf("PASSED\n");
}


void
BlockSizeOne(void)
{
    u8   buf[8];
    bool status;

    printf(LOG_PREFIX_CSTR "BlockSizeOne -> ");

    /* Init: 0x00..0x07 */
    kdi_FillSeq(buf, USIZE_C(8), U8_C(0x00));

    /* Block size 1 = byte swap. Swap index 2 and 5 */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(2), USIZE_C(5), USIZE_C(1));
    assert(status == RESULT_SUCCESS);

    /* Expected: 00 01 05 03 04 02 06 07 */
    assert(buf[0] == U8_C(0x00));
    assert(buf[1] == U8_C(0x01));
    assert(buf[2] == U8_C(0x05));
    assert(buf[3] == U8_C(0x03));
    assert(buf[4] == U8_C(0x04));
    assert(buf[5] == U8_C(0x02));
    assert(buf[6] == U8_C(0x06));
    assert(buf[7] == U8_C(0x07));

    printf("PASSED\n");
}


void
U16_Blocks_TwoBlocks(void)
{
    u16  buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "U16_Blocks_TwoBlocks -> ");

    /* Init: 0x1111, 0x2222, 0x3333, 0x4444 */
    buf[0] = U16_C(0x1111);
    buf[1] = U16_C(0x2222);
    buf[2] = U16_C(0x3333);
    buf[3] = U16_C(0x4444);

    /* Swap element 0 (idx=0) and element 2 (idx=4 bytes) */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(0), USIZE_C(2) * sizeof(u16), sizeof(u16));
    assert(status == RESULT_SUCCESS);

    /* Expected: 0x3333, 0x2222, 0x1111, 0x4444 */
    assert(buf[0] == U16_C(0x3333));
    assert(buf[1] == U16_C(0x2222));
    assert(buf[2] == U16_C(0x1111));
    assert(buf[3] == U16_C(0x4444));

    printf("PASSED\n");
}


void
U16_Blocks_Adjacent(void)
{
    u16  buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "U16_Blocks_Adjacent -> ");

    /* Init: 0xAAAA, 0xBBBB, 0xCCCC, 0xDDDD */
    buf[0] = U16_C(0xAAAA);
    buf[1] = U16_C(0xBBBB);
    buf[2] = U16_C(0xCCCC);
    buf[3] = U16_C(0xDDDD);

    /* Swap element 1 (idx=2 bytes) and element 2 (idx=4 bytes) */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(1) * sizeof(u16), USIZE_C(2) * sizeof(u16), sizeof(u16));
    assert(status == RESULT_SUCCESS);

    /* Expected: 0xAAAA, 0xCCCC, 0xBBBB, 0xDDDD */
    assert(buf[0] == U16_C(0xAAAA));
    assert(buf[1] == U16_C(0xCCCC));
    assert(buf[2] == U16_C(0xBBBB));
    assert(buf[3] == U16_C(0xDDDD));

    printf("PASSED\n");
}


void
U16_Blocks_FirstAndLast(void)
{
    u16  buf[8];
    bool status;

    printf(LOG_PREFIX_CSTR "U16_Blocks_FirstAndLast -> ");

    /* Init: 0, 1, 2, 3, 4, 5, 6, 7 */
    buf[0] = U16_C(0);
    buf[1] = U16_C(1);
    buf[2] = U16_C(2);
    buf[3] = U16_C(3);
    buf[4] = U16_C(4);
    buf[5] = U16_C(5);
    buf[6] = U16_C(6);
    buf[7] = U16_C(7);

    /* Swap element 0 and element 7 */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(0), USIZE_C(7) * sizeof(u16), sizeof(u16));
    assert(status == RESULT_SUCCESS);

    /* Expected: 7, 1, 2, 3, 4, 5, 6, 0 */
    assert(buf[0] == U16_C(7));
    assert(buf[1] == U16_C(1));
    assert(buf[6] == U16_C(6));
    assert(buf[7] == U16_C(0));

    printf("PASSED\n");
}


void
U32_Blocks_TwoBlocks(void)
{
    u32  buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "U32_Blocks_TwoBlocks -> ");

    /* Init: 0x11111111, 0x22222222, 0x33333333, 0x44444444 */
    buf[0] = U32_C(0x11111111);
    buf[1] = U32_C(0x22222222);
    buf[2] = U32_C(0x33333333);
    buf[3] = U32_C(0x44444444);

    /* Swap element 0 (idx=0) and element 2 (idx=8 bytes) */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(0), USIZE_C(2) * sizeof(u32), sizeof(u32));
    assert(status == RESULT_SUCCESS);

    /* Expected: 0x33333333, 0x22222222, 0x11111111, 0x44444444 */
    assert(buf[0] == U32_C(0x33333333));
    assert(buf[1] == U32_C(0x22222222));
    assert(buf[2] == U32_C(0x11111111));
    assert(buf[3] == U32_C(0x44444444));

    printf("PASSED\n");
}


void
U32_Blocks_MultipleSwaps(void)
{
    u32  buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "U32_Blocks_MultipleSwaps -> ");

    /* Init: 10, 20, 30, 40 */
    buf[0] = U32_C(10);
    buf[1] = U32_C(20);
    buf[2] = U32_C(30);
    buf[3] = U32_C(40);

    /* Swap 0 and 3 */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(0), USIZE_C(3) * sizeof(u32), sizeof(u32));
    assert(status == RESULT_SUCCESS);

    /* Swap 1 and 2 */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(1) * sizeof(u32), USIZE_C(2) * sizeof(u32), sizeof(u32));
    assert(status == RESULT_SUCCESS);

    /* Expected: 40, 30, 20, 10 */
    assert(buf[0] == U32_C(40));
    assert(buf[1] == U32_C(30));
    assert(buf[2] == U32_C(20));
    assert(buf[3] == U32_C(10));

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_Blocks_TwoBlocks(void)
{
    u64  buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "U64_Blocks_TwoBlocks -> ");

    /* Init */
    buf[0] = U64_C(0x1111111111111111);
    buf[1] = U64_C(0x2222222222222222);
    buf[2] = U64_C(0x3333333333333333);
    buf[3] = U64_C(0x4444444444444444);

    /* Swap element 1 (idx=8 bytes) and element 3 (idx=24 bytes) */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(1) * sizeof(u64), USIZE_C(3) * sizeof(u64), sizeof(u64));
    assert(status == RESULT_SUCCESS);

    /* Expected: 0x1111..., 0x4444..., 0x3333..., 0x2222... */
    assert(buf[0] == U64_C(0x1111111111111111));
    assert(buf[1] == U64_C(0x4444444444444444));
    assert(buf[2] == U64_C(0x3333333333333333));
    assert(buf[3] == U64_C(0x2222222222222222));

    printf("PASSED\n");
}


void
U64_Blocks_FirstAndLast(void)
{
    u64  buf[6];
    bool status;

    printf(LOG_PREFIX_CSTR "U64_Blocks_FirstAndLast -> ");

    /* Init: 0, 10, 20, 30, 40, 50 */
    buf[0] = U64_C(0);
    buf[1] = U64_C(10);
    buf[2] = U64_C(20);
    buf[3] = U64_C(30);
    buf[4] = U64_C(40);
    buf[5] = U64_C(50);

    /* Swap element 0 and element 5 */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(0), USIZE_C(5) * sizeof(u64), sizeof(u64));
    assert(status == RESULT_SUCCESS);

    /* Expected: 50, 10, 20, 30, 40, 0 */
    assert(buf[0] == U64_C(50));
    assert(buf[1] == U64_C(10));
    assert(buf[4] == U64_C(40));
    assert(buf[5] == U64_C(0));

    printf("PASSED\n");
}
#endif


typedef struct kdi_SmallStruct
{
    u32 a;
    u32 b;
    u8  c;
} kdi_SmallStruct;


void
Struct_Blocks_TwoBlocks(void)
{
    kdi_SmallStruct buf[3];
    bool            status;

    printf(LOG_PREFIX_CSTR "Struct_Blocks_TwoBlocks -> ");

    /* Init */
    buf[0].a = U32_C(1);
    buf[0].b = U32_C(10);
    buf[0].c = U8_C(100);
    buf[1].a = U32_C(2);
    buf[1].b = U32_C(20);
    buf[1].c = U8_C(200);
    buf[2].a = U32_C(3);
    buf[2].b = U32_C(30);
    buf[2].c = U8_C(50);

    /* Swap element 1 and element 2 */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(1) * sizeof(kdi_SmallStruct), USIZE_C(2) * sizeof(kdi_SmallStruct), sizeof(kdi_SmallStruct));
    assert(status == RESULT_SUCCESS);

    /* Expected: S0, S2, S1 */
    assert(buf[0].a == U32_C(1) && buf[0].b == U32_C(10) && buf[0].c == U8_C(100));
    assert(buf[1].a == U32_C(3) && buf[1].b == U32_C(30) && buf[1].c == U8_C(50));
    assert(buf[2].a == U32_C(2) && buf[2].b == U32_C(20) && buf[2].c == U8_C(200));

    printf("PASSED\n");
}


void
Struct_Blocks_FirstAndLast(void)
{
    kdi_SmallStruct buf[4];
    bool            status;

    printf(LOG_PREFIX_CSTR "Struct_Blocks_FirstAndLast -> ");

    /* Init: S0, S1, S2, S3 */
    buf[0].a = U32_C(1);
    buf[0].b = U32_C(10);
    buf[0].c = U8_C(100);
    buf[1].a = U32_C(2);
    buf[1].b = U32_C(20);
    buf[1].c = U8_C(200);
    buf[2].a = U32_C(3);
    buf[2].b = U32_C(30);
    buf[2].c = U8_C(50);
    buf[3].a = U32_C(4);
    buf[3].b = U32_C(40);
    buf[3].c = U8_C(60);

    /* Swap element 0 and element 3 */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(0), USIZE_C(3) * sizeof(kdi_SmallStruct), sizeof(kdi_SmallStruct));
    assert(status == RESULT_SUCCESS);

    /* Expected: S3, S1, S2, S0 */
    assert(buf[0].a == U32_C(4) && buf[0].b == U32_C(40) && buf[0].c == U8_C(60));
    assert(buf[1].a == U32_C(2) && buf[1].b == U32_C(20) && buf[1].c == U8_C(200));
    assert(buf[2].a == U32_C(3) && buf[2].b == U32_C(30) && buf[2].c == U8_C(50));
    assert(buf[3].a == U32_C(1) && buf[3].b == U32_C(10) && buf[3].c == U8_C(100));

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    u8    buf[128];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    /* Init: 0..127 */
    kdi_FillSeq(buf, USIZE_C(128), U8_C(0));

    /* Swap blocks: idx=16 (bytes 16-23) and idx=96 (bytes 96-103), block_sz=8 */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(16), USIZE_C(96), USIZE_C(8));
    assert(status == RESULT_SUCCESS);

    /* Verify first swapped block (now contains 96-103) */
    for (i = USIZE_C(16); i < USIZE_C(24); ++i)
    {
        assert(buf[i] == (u8)(i + 80));
    }

    /* Verify second swapped block (now contains 16-23) */
    for (i = USIZE_C(96); i < USIZE_C(104); ++i)
    {
        assert(buf[i] == (u8)(i - 80));
    }

    /* Verify pre-swap region */
    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        assert(buf[i] == (u8)i);
    }

    /* Verify middle region */
    for (i = USIZE_C(24); i < USIZE_C(96); ++i)
    {
        assert(buf[i] == (u8)i);
    }

    /* Verify post-swap region */
    for (i = USIZE_C(104); i < USIZE_C(128); ++i)
    {
        assert(buf[i] == (u8)i);
    }

    printf("PASSED\n");
}


void
ZeroIndexSwap(void)
{
    u8   buf[8];
    bool status;

    printf(LOG_PREFIX_CSTR "ZeroIndexSwap -> ");

    /* Init: 0x00..0x07 */
    kdi_FillSeq(buf, USIZE_C(8), U8_C(0x00));

    /* Swap block at index 0 with block at index 0 (same) */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(0), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Expected: unchanged */
    assert(buf[0] == U8_C(0x00));
    assert(buf[3] == U8_C(0x03));
    assert(buf[7] == U8_C(0x07));

    printf("PASSED\n");
}


void
AllSameBlocks(void)
{
    u32   buf[8];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "AllSameBlocks -> ");

    /* Fill all blocks with same value */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        buf[i] = U32_C(0xDEADBEEF);
    }

    /* Swap blocks */
    status = GenMemOpsInnerSwapBlocks(buf, USIZE_C(1) * sizeof(u32), USIZE_C(5) * sizeof(u32), sizeof(u32));
    assert(status == RESULT_SUCCESS);

    /* All values should still be the same */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        assert(buf[i] == U32_C(0xDEADBEEF));
    }

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    NullPointer();
    ZeroBlockSize();
    Idx1Misaligned();
    Idx2Misaligned();
    BothIndicesMisaligned();
    SwapSameIndex();
    SwapAdjacentBlocks_Size2();
    SwapAdjacentBlocks_Size4();
    SwapDistantBlocks();
    SwapMiddleBlocks();
    SwapReversedIndices();
    DoubleSwap();
    BlockSizeOne();
    U16_Blocks_TwoBlocks();
    U16_Blocks_Adjacent();
    U16_Blocks_FirstAndLast();
    U32_Blocks_TwoBlocks();
    U32_Blocks_MultipleSwaps();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_Blocks_TwoBlocks();
    U64_Blocks_FirstAndLast();
#endif
    Struct_Blocks_TwoBlocks();
    Struct_Blocks_FirstAndLast();
    LargeBuffer();
    ZeroIndexSwap();
    AllSameBlocks();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}