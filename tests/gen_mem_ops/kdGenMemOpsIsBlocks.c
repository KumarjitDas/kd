/**
 * @file kdGenMemOpsIsBlocks.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsIsBlocks function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsIsBlocks function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
ResultNull(void)
{
    u8   buf[16];
    u8   block[4];
    bool status;

    printf(LOG_PREFIX_CSTR "ResultNull -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));
    kdi_Fill_u8(block, USIZE_C(4), U8_C(0x00));

    /* result pointer is null -> failure */
    status = kdGenMemOpsIsBlocks(null, buf, USIZE_C(16), block, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
PtrNull(void)
{
    u8   block[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "PtrNull -> ");

    kdi_Fill_u8(block, USIZE_C(4), U8_C(0x00));

    /* ptr is null -> failure */
    status = kdGenMemOpsIsBlocks(&result, null, USIZE_C(16), block, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
BlockNull(void)
{
    u8   buf[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "BlockNull -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* block is null -> failure */
    status = kdGenMemOpsIsBlocks(&result, buf, USIZE_C(16), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
PtrSizeZero(void)
{
    u8   buf[16];
    u8   block[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "PtrSizeZero -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));
    kdi_Fill_u8(block, USIZE_C(4), U8_C(0x00));

    /* ptr_sz is zero -> failure */
    status = kdGenMemOpsIsBlocks(&result, buf, USIZE_C(0), block, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
BlockSizeZero(void)
{
    u8   buf[16];
    u8   block[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "BlockSizeZero -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));
    kdi_Fill_u8(block, USIZE_C(4), U8_C(0x00));

    /* block_sz is zero -> failure */
    status = kdGenMemOpsIsBlocks(&result, buf, USIZE_C(16), block, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
BlockSizeGreaterThanPtrSize(void)
{
    u8   buf[8];
    u8   block[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "BlockSizeGreaterThanPtrSize -> ");

    kdi_Fill_u8(buf, USIZE_C(8), U8_C(0xAA));
    kdi_Fill_u8(block, USIZE_C(16), U8_C(0xAA));

    /* block_sz > ptr_sz -> failure */
    status = kdGenMemOpsIsBlocks(&result, buf, USIZE_C(8), block, USIZE_C(16));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SingleBlockMatch(void)
{
    u8   buf[4];
    u8   block[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "SingleBlockMatch -> ");

    kdi_FillSeq_u8(buf, USIZE_C(4), U8_C(0x10));
    kdi_FillSeq_u8(block, USIZE_C(4), U8_C(0x10));

    /* Buffer contains exactly one block */
    result = false;
    status = kdGenMemOpsIsBlocks(&result, buf, USIZE_C(4), block, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
SingleBlockNoMatch(void)
{
    u8   buf[4];
    u8   block[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "SingleBlockNoMatch -> ");

    kdi_FillSeq_u8(buf, USIZE_C(4), U8_C(0x10));
    kdi_FillSeq_u8(block, USIZE_C(4), U8_C(0x20));

    /* Buffer contains exactly one block but doesn't match */
    result = true;
    status = kdGenMemOpsIsBlocks(&result, buf, USIZE_C(4), block, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
MultipleBlocksAllMatch(void)
{
    u8   buf[16];
    u8   block[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "MultipleBlocksAllMatch -> ");

    /* Set up block pattern */
    block[0] = U8_C(0x11);
    block[1] = U8_C(0x22);
    block[2] = U8_C(0x33);
    block[3] = U8_C(0x44);

    /* Repeat block 4 times in buffer */
    buf[0]   = U8_C(0x11);
    buf[1]   = U8_C(0x22);
    buf[2]   = U8_C(0x33);
    buf[3]   = U8_C(0x44);
    buf[4]   = U8_C(0x11);
    buf[5]   = U8_C(0x22);
    buf[6]   = U8_C(0x33);
    buf[7]   = U8_C(0x44);
    buf[8]   = U8_C(0x11);
    buf[9]   = U8_C(0x22);
    buf[10]  = U8_C(0x33);
    buf[11]  = U8_C(0x44);
    buf[12]  = U8_C(0x11);
    buf[13]  = U8_C(0x22);
    buf[14]  = U8_C(0x33);
    buf[15]  = U8_C(0x44);

    result   = false;
    status   = kdGenMemOpsIsBlocks(&result, buf, USIZE_C(16), block, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
MultipleBlocksOneMismatch(void)
{
    u8   buf[16];
    u8   block[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "MultipleBlocksOneMismatch -> ");

    /* Set up block pattern */
    block[0] = U8_C(0x11);
    block[1] = U8_C(0x22);
    block[2] = U8_C(0x33);
    block[3] = U8_C(0x44);

    /* Repeat block 4 times in buffer */
    buf[0]   = U8_C(0x11);
    buf[1]   = U8_C(0x22);
    buf[2]   = U8_C(0x33);
    buf[3]   = U8_C(0x44);
    buf[4]   = U8_C(0x11);
    buf[5]   = U8_C(0x22);
    buf[6]   = U8_C(0x33);
    buf[7]   = U8_C(0x44);
    buf[8]   = U8_C(0x11);
    buf[9]   = U8_C(0xFF); /* Mismatch */
    buf[10]  = U8_C(0x33);
    buf[11]  = U8_C(0x44);
    buf[12]  = U8_C(0x11);
    buf[13]  = U8_C(0x22);
    buf[14]  = U8_C(0x33);
    buf[15]  = U8_C(0x44);

    result   = true;
    status   = kdGenMemOpsIsBlocks(&result, buf, USIZE_C(16), block, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
SingleByteBlock(void)
{
    u8   buf[8];
    u8   block;
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "SingleByteBlock -> ");

    /* Block size is 1, repeated 8 times */
    kdi_Fill_u8(buf, USIZE_C(8), U8_C(0xAA));
    block  = U8_C(0xAA);

    result = false;
    status = kdGenMemOpsIsBlocks(&result, buf, USIZE_C(8), &block, USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
TwoByteBlock(void)
{
    u8   buf[16];
    u8   block[2];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "TwoByteBlock -> ");

    /* Block pattern: 0xAB 0xCD repeated 8 times */
    block[0] = U8_C(0xAB);
    block[1] = U8_C(0xCD);

    buf[0]   = U8_C(0xAB);
    buf[1]   = U8_C(0xCD);
    buf[2]   = U8_C(0xAB);
    buf[3]   = U8_C(0xCD);
    buf[4]   = U8_C(0xAB);
    buf[5]   = U8_C(0xCD);
    buf[6]   = U8_C(0xAB);
    buf[7]   = U8_C(0xCD);
    buf[8]   = U8_C(0xAB);
    buf[9]   = U8_C(0xCD);
    buf[10]  = U8_C(0xAB);
    buf[11]  = U8_C(0xCD);
    buf[12]  = U8_C(0xAB);
    buf[13]  = U8_C(0xCD);
    buf[14]  = U8_C(0xAB);
    buf[15]  = U8_C(0xCD);

    result   = false;
    status   = kdGenMemOpsIsBlocks(&result, buf, USIZE_C(16), block, USIZE_C(2));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
OddBlockSizes(void)
{
    u8   buf[27];
    u8   block[3];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "OddBlockSizes -> ");

    /* Block size 3, repeated 9 times */
    block[0] = U8_C(0x10);
    block[1] = U8_C(0x20);
    block[2] = U8_C(0x30);

    /* Repeat the 3-byte block 9 times */

    buf[0]   = U8_C(0x10);
    buf[1]   = U8_C(0x20);
    buf[2]   = U8_C(0x30);

    buf[3]   = U8_C(0x10);
    buf[4]   = U8_C(0x20);
    buf[5]   = U8_C(0x30);

    buf[6]   = U8_C(0x10);
    buf[7]   = U8_C(0x20);
    buf[8]   = U8_C(0x30);

    buf[9]   = U8_C(0x10);
    buf[10]  = U8_C(0x20);
    buf[11]  = U8_C(0x30);

    buf[12]  = U8_C(0x10);
    buf[13]  = U8_C(0x20);
    buf[14]  = U8_C(0x30);

    buf[15]  = U8_C(0x10);
    buf[16]  = U8_C(0x20);
    buf[17]  = U8_C(0x30);

    buf[18]  = U8_C(0x10);
    buf[19]  = U8_C(0x20);
    buf[20]  = U8_C(0x30);

    buf[21]  = U8_C(0x10);
    buf[22]  = U8_C(0x20);
    buf[23]  = U8_C(0x30);

    buf[24]  = U8_C(0x10);
    buf[25]  = U8_C(0x20);
    buf[26]  = U8_C(0x30);

    result   = false;
    status   = kdGenMemOpsIsBlocks(&result, buf, USIZE_C(27), block, USIZE_C(3));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
NonPowerOfTwoBlockSize(void)
{
    u8    buf[30];
    u8    block[5];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "NonPowerOfTwoBlockSize -> ");

    /* Block size 5 (non-power-of-2), repeated 6 times */
    block[0] = U8_C(0x11);
    block[1] = U8_C(0x22);
    block[2] = U8_C(0x33);
    block[3] = U8_C(0x44);
    block[4] = U8_C(0x55);

    /* Repeat the 5-byte block 6 times */
    for (i = 0; i < 6; ++i)
    {
        buf[i * 5 + 0] = U8_C(0x11);
        buf[i * 5 + 1] = U8_C(0x22);
        buf[i * 5 + 2] = U8_C(0x33);
        buf[i * 5 + 3] = U8_C(0x44);
        buf[i * 5 + 4] = U8_C(0x55);
    }

    result = false;
    status = kdGenMemOpsIsBlocks(&result, buf, USIZE_C(30), block, USIZE_C(5));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
LargeBlockSize(void)
{
    u8    buf[64];
    u8    block[16];
    bool  result;
    bool  status;
    usize i, j;

    printf(LOG_PREFIX_CSTR "LargeBlockSize -> ");

    /* Block size 16, repeated 4 times */
    for (i = 0; i < 16; ++i)
    {
        block[i] = (u8)(i + 0x10);
    }

    /* Repeat the 16-byte block 4 times */
    for (i = 0; i < 4; ++i)
    {
        for (j = 0; j < 16; ++j)
        {
            buf[i * 16 + j] = (u8)(j + 0x10);
        }
    }

    result = false;
    status = kdGenMemOpsIsBlocks(&result, buf, USIZE_C(64), block, USIZE_C(16));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
MismatchInFirstBlock(void)
{
    u8   buf[12];
    u8   block[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "MismatchInFirstBlock -> ");

    /* Set up block pattern */
    block[0] = U8_C(0xAA);
    block[1] = U8_C(0xBB);
    block[2] = U8_C(0xCC);
    block[3] = U8_C(0xDD);

    /* First block has mismatch */
    buf[0]   = U8_C(0xAA);
    buf[1]   = U8_C(0xBB);
    buf[2]   = U8_C(0xFF); /* Mismatch */
    buf[3]   = U8_C(0xDD);
    buf[4]   = U8_C(0xAA);
    buf[5]   = U8_C(0xBB);
    buf[6]   = U8_C(0xCC);
    buf[7]   = U8_C(0xDD);
    buf[8]   = U8_C(0xAA);
    buf[9]   = U8_C(0xBB);
    buf[10]  = U8_C(0xCC);
    buf[11]  = U8_C(0xDD);

    result   = true;
    status   = kdGenMemOpsIsBlocks(&result, buf, USIZE_C(12), block, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
MismatchInLastBlock(void)
{
    u8   buf[12];
    u8   block[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "MismatchInLastBlock -> ");

    /* Set up block pattern */
    block[0] = U8_C(0xAA);
    block[1] = U8_C(0xBB);
    block[2] = U8_C(0xCC);
    block[3] = U8_C(0xDD);

    /* Last block has mismatch */
    buf[0]   = U8_C(0xAA);
    buf[1]   = U8_C(0xBB);
    buf[2]   = U8_C(0xCC);
    buf[3]   = U8_C(0xDD);
    buf[4]   = U8_C(0xAA);
    buf[5]   = U8_C(0xBB);
    buf[6]   = U8_C(0xCC);
    buf[7]   = U8_C(0xDD);
    buf[8]   = U8_C(0xAA);
    buf[9]   = U8_C(0xBB);
    buf[10]  = U8_C(0xCC);
    buf[11]  = U8_C(0xEE); /* Mismatch */

    result   = true;
    status   = kdGenMemOpsIsBlocks(&result, buf, USIZE_C(12), block, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
AllZerosBlock(void)
{
    u8   buf[16];
    u8   block[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "AllZerosBlock -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));
    kdi_Fill_u8(block, USIZE_C(4), U8_C(0x00));

    result = false;
    status = kdGenMemOpsIsBlocks(&result, buf, USIZE_C(16), block, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
AllOnesBlock(void)
{
    u8   buf[16];
    u8   block[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "AllOnesBlock -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xFF));
    kdi_Fill_u8(block, USIZE_C(4), U8_C(0xFF));

    result = false;
    status = kdGenMemOpsIsBlocks(&result, buf, USIZE_C(16), block, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
PtrSizeNotMultipleOfBlockSize(void)
{
    u8    buf[17];
    u8    block[4];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "PtrSizeNotMultipleOfBlockSize -> ");

    /* Set up block pattern */
    block[0] = U8_C(0x11);
    block[1] = U8_C(0x22);
    block[2] = U8_C(0x33);
    block[3] = U8_C(0x44);

    /* Fill buffer: 4 complete blocks + 1 extra byte */
    for (i = 0; i < 4; ++i)
    {
        buf[i * 4 + 0] = U8_C(0x11);
        buf[i * 4 + 1] = U8_C(0x22);
        buf[i * 4 + 2] = U8_C(0x33);
        buf[i * 4 + 3] = U8_C(0x44);
    }
    buf[16] = U8_C(0x11); /* Partial block */

    /* ptr_sz not a multiple of block_sz -> failure */
    status = kdGenMemOpsIsBlocks(&result, buf, USIZE_C(17), block, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
U16Blocks(void)
{
    u16   buf[8];
    u16   block[2];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "U16Blocks -> ");

    /* Block pattern: two u16 values */
    block[0] = U16_C(0x1234);
    block[1] = U16_C(0x5678);

    /* Repeat the block 4 times */
    for (i = 0; i < 4; ++i)
    {
        buf[i * 2 + 0] = U16_C(0x1234);
        buf[i * 2 + 1] = U16_C(0x5678);
    }

    result = false;
    status = kdGenMemOpsIsBlocks(&result, buf, sizeof(buf), block, sizeof(block));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
U32Blocks(void)
{
    u32   buf[8];
    u32   block[2];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "U32Blocks -> ");

    /* Block pattern: two u32 values */
    block[0] = U32_C(0x12345678);
    block[1] = U32_C(0xABCDEF01);

    /* Repeat the block 4 times */
    for (i = 0; i < 4; ++i)
    {
        buf[i * 2 + 0] = U32_C(0x12345678);
        buf[i * 2 + 1] = U32_C(0xABCDEF01);
    }

    result = false;
    status = kdGenMemOpsIsBlocks(&result, buf, sizeof(buf), block, sizeof(block));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    ResultNull();
    PtrNull();
    BlockNull();
    PtrSizeZero();
    BlockSizeZero();
    BlockSizeGreaterThanPtrSize();
    SingleBlockMatch();
    SingleBlockNoMatch();
    MultipleBlocksAllMatch();
    MultipleBlocksOneMismatch();
    SingleByteBlock();
    TwoByteBlock();
    OddBlockSizes();
    NonPowerOfTwoBlockSize();
    LargeBlockSize();
    MismatchInFirstBlock();
    MismatchInLastBlock();
    AllZerosBlock();
    AllOnesBlock();
    PtrSizeNotMultipleOfBlockSize();
    U16Blocks();
    U32Blocks();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
