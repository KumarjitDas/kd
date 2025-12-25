/**
 * @file kdGenMemOpsSwapBlocks.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsSwapBlocks function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsSwapBlocks function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
PtrNull(void)
{
    bool status;

    printf(LOG_PREFIX_CSTR "PtrNull -> ");

    /* ptr is null -> failure */
    status = GenMemOpsSwapBlocks(null, null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
BlockSizeZero(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BlockSizeZero -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x00));

    /* block_sz is zero -> failure */
    status = GenMemOpsSwapBlocks(&buf[0], &buf[4], USIZE_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SwapSameIndex(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapSameIndex -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Swap block at &buf[4] with itself (block_sz=4) -> success, no change */
    status = GenMemOpsSwapBlocks(&buf[4], &buf[4], USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Verify unchanged */
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

    kdi_FillSeq_u8(buf, USIZE_C(8), U8_C(0x00));

    /* Block size 2. Swap &buf[0] (bytes 0-1) and &buf[2] (bytes 2-3) */
    status = GenMemOpsSwapBlocks(&buf[0], &buf[2], USIZE_C(2));
    assert(status == RESULT_SUCCESS);

    assert(buf[0] == U8_C(0x02));
    assert(buf[1] == U8_C(0x03));
    assert(buf[2] == U8_C(0x00));
    assert(buf[3] == U8_C(0x01));
    assert(buf[4] == U8_C(0x04));

    printf("PASSED\n");
}


void
SwapAdjacentBlocks_Size4(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapAdjacentBlocks_Size4 -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Block size 4. Swap &buf[0] (bytes 0-3) and &buf[4] (bytes 4-7) */
    status = GenMemOpsSwapBlocks(&buf[0], &buf[4], USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    assert(buf[0] == U8_C(0x04));
    assert(buf[3] == U8_C(0x07));
    assert(buf[4] == U8_C(0x00));
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

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Block size 4. Swap &buf[0] (bytes 0-3) and &buf[12] (bytes 12-15) */
    status = GenMemOpsSwapBlocks(&buf[0], &buf[12], USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    assert(buf[0] == U8_C(0x0C));
    assert(buf[3] == U8_C(0x0F));
    assert(buf[4] == U8_C(0x04));
    assert(buf[11] == U8_C(0x0B));
    assert(buf[12] == U8_C(0x00));
    assert(buf[15] == U8_C(0x03));

    printf("PASSED\n");
}


void
SwapMiddleBlocks(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapMiddleBlocks -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Block size 2. Swap &buf[4] (bytes 4-5) and &buf[10] (bytes 10-11) */
    status = GenMemOpsSwapBlocks(&buf[4], &buf[10], USIZE_C(2));
    assert(status == RESULT_SUCCESS);

    assert(buf[3] == U8_C(0x03));
    assert(buf[4] == U8_C(0x0A));
    assert(buf[5] == U8_C(0x0B));
    assert(buf[6] == U8_C(0x06));
    assert(buf[9] == U8_C(0x09));
    assert(buf[10] == U8_C(0x04));
    assert(buf[11] == U8_C(0x05));
    assert(buf[12] == U8_C(0x0C));

    printf("PASSED\n");
}


void
SwapReversedIndices(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapReversedIndices -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Block size 4. Swap &buf[12] and &buf[0] (reverse order) */
    status = GenMemOpsSwapBlocks(&buf[12], &buf[0], USIZE_C(4));
    assert(status == RESULT_SUCCESS);

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

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Keep copy of original */
    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        original[i] = buf[i];
    }

    /* Swap &buf[0] and &buf[8] (block_sz=4) */
    status = GenMemOpsSwapBlocks(&buf[0], &buf[8], USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Swap &buf[0] and &buf[8] again - should restore */
    status = GenMemOpsSwapBlocks(&buf[0], &buf[8], USIZE_C(4));
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

    kdi_FillSeq_u8(buf, USIZE_C(8), U8_C(0x00));

    /* Block size 1 = byte swap. Swap &buf[2] and &buf[5] */
    status = GenMemOpsSwapBlocks(&buf[2], &buf[5], USIZE_C(1));
    assert(status == RESULT_SUCCESS);

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
U16_Blocks_Swap(void)
{
    u16  buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "U16_Blocks_Swap -> ");

    buf[0] = U16_C(0x1111);
    buf[1] = U16_C(0x2222);
    buf[2] = U16_C(0x3333);
    buf[3] = U16_C(0x4444);

    /* Swap element 0 and element 2 */
    status = GenMemOpsSwapBlocks(&buf[0], &buf[2], sizeof(u16));
    assert(status == RESULT_SUCCESS);

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

    buf[0] = U16_C(0xAAAA);
    buf[1] = U16_C(0xBBBB);
    buf[2] = U16_C(0xCCCC);
    buf[3] = U16_C(0xDDDD);

    /* Swap element 1 and element 2 */
    status = GenMemOpsSwapBlocks(&buf[1], &buf[2], sizeof(u16));
    assert(status == RESULT_SUCCESS);

    assert(buf[0] == U16_C(0xAAAA));
    assert(buf[1] == U16_C(0xCCCC));
    assert(buf[2] == U16_C(0xBBBB));
    assert(buf[3] == U16_C(0xDDDD));

    printf("PASSED\n");
}


void
U32_Blocks_Swap(void)
{
    u32  buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "U32_Blocks_Swap -> ");

    buf[0] = U32_C(0x11111111);
    buf[1] = U32_C(0x22222222);
    buf[2] = U32_C(0x33333333);
    buf[3] = U32_C(0x44444444);

    /* Swap element 0 and element 2 */
    status = GenMemOpsSwapBlocks(&buf[0], &buf[2], sizeof(u32));
    assert(status == RESULT_SUCCESS);

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

    buf[0] = U32_C(10);
    buf[1] = U32_C(20);
    buf[2] = U32_C(30);
    buf[3] = U32_C(40);

    /* Swap 0 and 3 */
    status = GenMemOpsSwapBlocks(&buf[0], &buf[3], sizeof(u32));
    assert(status == RESULT_SUCCESS);

    /* Swap 1 and 2 */
    status = GenMemOpsSwapBlocks(&buf[1], &buf[2], sizeof(u32));
    assert(status == RESULT_SUCCESS);

    assert(buf[0] == U32_C(40));
    assert(buf[1] == U32_C(30));
    assert(buf[2] == U32_C(20));
    assert(buf[3] == U32_C(10));

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_Blocks_Swap(void)
{
    u64  buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "U64_Blocks_Swap -> ");

    buf[0] = U64_C(0x1111111111111111);
    buf[1] = U64_C(0x2222222222222222);
    buf[2] = U64_C(0x3333333333333333);
    buf[3] = U64_C(0x4444444444444444);

    /* Swap element 1 and element 3 */
    status = GenMemOpsSwapBlocks(&buf[1], &buf[3], sizeof(u64));
    assert(status == RESULT_SUCCESS);

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

    buf[0] = U64_C(0);
    buf[1] = U64_C(10);
    buf[2] = U64_C(20);
    buf[3] = U64_C(30);
    buf[4] = U64_C(40);
    buf[5] = U64_C(50);

    /* Swap element 0 and element 5 */
    status = GenMemOpsSwapBlocks(&buf[0], &buf[5], sizeof(u64));
    assert(status == RESULT_SUCCESS);

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
Struct_Blocks_Swap(void)
{
    kdi_SmallStruct buf[3];
    bool            status;

    printf(LOG_PREFIX_CSTR "Struct_Blocks_Swap -> ");

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
    status   = GenMemOpsSwapBlocks(&buf[1], &buf[2], sizeof(kdi_SmallStruct));
    assert(status == RESULT_SUCCESS);

    assert(buf[0].a == U32_C(1) && buf[0].b == U32_C(10) && buf[0].c == U8_C(100));
    assert(buf[1].a == U32_C(3) && buf[1].b == U32_C(30) && buf[1].c == U8_C(50));
    assert(buf[2].a == U32_C(2) && buf[2].b == U32_C(20) && buf[2].c == U8_C(200));

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    u8    buf[128];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    kdi_FillSeq_u8(buf, USIZE_C(128), U8_C(0));

    /* Swap blocks: &buf[16] (bytes 16-23) and &buf[96] (bytes 96-103), block_sz=8 */
    status = GenMemOpsSwapBlocks(&buf[16], &buf[96], USIZE_C(8));
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

    kdi_FillSeq_u8(buf, USIZE_C(8), U8_C(0x00));

    /* Swap block at &buf[0] with itself (same) */
    status = GenMemOpsSwapBlocks(&buf[0], &buf[0], USIZE_C(4));
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
    status = GenMemOpsSwapBlocks(&buf[1], &buf[5], sizeof(u32));
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

    PtrNull();
    BlockSizeZero();
    SwapSameIndex();
    SwapAdjacentBlocks_Size2();
    SwapAdjacentBlocks_Size4();
    SwapDistantBlocks();
    SwapMiddleBlocks();
    SwapReversedIndices();
    DoubleSwap();
    BlockSizeOne();
    U16_Blocks_Swap();
    U16_Blocks_Adjacent();
    U32_Blocks_Swap();
    U32_Blocks_MultipleSwaps();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_Blocks_Swap();
    U64_Blocks_FirstAndLast();
#endif
    Struct_Blocks_Swap();
    LargeBuffer();
    ZeroIndexSwap();
    AllSameBlocks();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
