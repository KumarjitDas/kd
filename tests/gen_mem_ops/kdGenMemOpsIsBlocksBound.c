/**
 * @file kdGenMemOpsIsBlocksBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsIsBlocksBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsIsBlocksBound function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8   buf[32];
    u8   block[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xAA));
    kdi_Fill_u8(block, USIZE_C(4), U8_C(0xAA));

    /* result pointer is null -> failure */
    status = kdGenMemOpsIsBlocksBound(null, buf, USIZE_C(32), USIZE_C(0), USIZE_C(16), block, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure */
    status = kdGenMemOpsIsBlocksBound(&result, null, USIZE_C(32), USIZE_C(0), USIZE_C(16), block, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    status = kdGenMemOpsIsBlocksBound(&result, buf, USIZE_C(32), USIZE_C(0), USIZE_C(16), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = kdGenMemOpsIsBlocksBound(&result, buf, USIZE_C(0), USIZE_C(0), USIZE_C(16), block, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* byte_count is zero -> failure (!byte_count check) */
    status = kdGenMemOpsIsBlocksBound(&result, buf, USIZE_C(32), USIZE_C(0), USIZE_C(0), block, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = kdGenMemOpsIsBlocksBound(&result, buf, USIZE_C(32), USIZE_C(0), USIZE_C(16), block, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
BeginIndexOutOfBounds(void)
{
    u8   buf[32];
    u8   block[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "BeginIndexOutOfBounds -> ");

    /* begin_idx >= base_sz */
    status = kdGenMemOpsIsBlocksBound(&result, buf, USIZE_C(32), USIZE_C(32), USIZE_C(8), block, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* begin_idx > base_sz */
    status = kdGenMemOpsIsBlocksBound(&result, buf, USIZE_C(32), USIZE_C(40), USIZE_C(8), block, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
BlockSizeGreaterThanByteCount(void)
{
    u8   buf[32];
    u8   block[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "BlockSizeGreaterThanByteCount -> ");

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xAA));
    kdi_Fill_u8(block, USIZE_C(16), U8_C(0xAA));

    /* block_sz > byte_count -> failure */
    status = kdGenMemOpsIsBlocksBound(&result, buf, USIZE_C(32), USIZE_C(0), USIZE_C(8), block, USIZE_C(16));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SingleBlockInRange(void)
{
    u8   buf[32];
    u8   block[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "SingleBlockInRange -> ");

    /* Set up buffer with repeating pattern */
    block[0] = U8_C(0x11);
    block[1] = U8_C(0x22);
    block[2] = U8_C(0x33);
    block[3] = U8_C(0x44);

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xFF));

    /* Place single block at index 8 */
    buf[8]  = U8_C(0x11);
    buf[9]  = U8_C(0x22);
    buf[10] = U8_C(0x33);
    buf[11] = U8_C(0x44);

    /* Check single block */
    result  = false;
    status  = kdGenMemOpsIsBlocksBound(&result, buf, USIZE_C(32), USIZE_C(8), USIZE_C(4), block, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
MultipleBlocksInRangeAllMatch(void)
{
    u8    buf[32];
    u8    block[4];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "MultipleBlocksInRangeAllMatch -> ");

    /* Set up block pattern */
    block[0] = U8_C(0xAA);
    block[1] = U8_C(0xBB);
    block[2] = U8_C(0xCC);
    block[3] = U8_C(0xDD);

    /* Fill buffer outside range with different value */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xFF));

    /* Fill range [8..23] with repeating block (4 repetitions) */
    for (i = 0; i < 4; ++i)
    {
        buf[8 + i * 4 + 0] = U8_C(0xAA);
        buf[8 + i * 4 + 1] = U8_C(0xBB);
        buf[8 + i * 4 + 2] = U8_C(0xCC);
        buf[8 + i * 4 + 3] = U8_C(0xDD);
    }

    /* Check range [8..23] (16 bytes) */
    result = false;
    status = kdGenMemOpsIsBlocksBound(&result, buf, USIZE_C(32), USIZE_C(8), USIZE_C(16), block, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
MultipleBlocksInRangeOneMismatch(void)
{
    u8    buf[32];
    u8    block[4];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "MultipleBlocksInRangeOneMismatch -> ");

    /* Set up block pattern */
    block[0] = U8_C(0xAA);
    block[1] = U8_C(0xBB);
    block[2] = U8_C(0xCC);
    block[3] = U8_C(0xDD);

    /* Fill buffer outside range with different value */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xFF));

    /* Fill range [8..23] with repeating block (4 repetitions) */
    for (i = 0; i < 4; ++i)
    {
        buf[8 + i * 4 + 0] = U8_C(0xAA);
        buf[8 + i * 4 + 1] = U8_C(0xBB);
        buf[8 + i * 4 + 2] = U8_C(0xCC);
        buf[8 + i * 4 + 3] = U8_C(0xDD);
    }

    /* Create mismatch in third block */
    buf[18] = U8_C(0xEE);

    /* Check range [8..23] (16 bytes) */
    result  = true;
    status  = kdGenMemOpsIsBlocksBound(&result, buf, USIZE_C(32), USIZE_C(8), USIZE_C(16), block, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
SingleByteBlockInRange(void)
{
    u8   buf[32];
    u8   block;
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "SingleByteBlockInRange -> ");

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xFF));

    /* Fill range [8..15] with 0xAA */
    kdi_Fill_u8(&buf[8], USIZE_C(8), U8_C(0xAA));

    block  = U8_C(0xAA);

    /* Check range */
    result = false;
    status = kdGenMemOpsIsBlocksBound(&result, buf, USIZE_C(32), USIZE_C(8), USIZE_C(8), &block, USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
TwoByteBlockInRange(void)
{
    u8    buf[32];
    u8    block[2];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "TwoByteBlockInRange -> ");

    block[0] = U8_C(0x12);
    block[1] = U8_C(0x34);

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xFF));

    /* Fill range [6..21] with repeating 2-byte block (8 repetitions) */
    for (i = 0; i < 8; ++i)
    {
        buf[6 + i * 2 + 0] = U8_C(0x12);
        buf[6 + i * 2 + 1] = U8_C(0x34);
    }

    result = false;
    status = kdGenMemOpsIsBlocksBound(&result, buf, USIZE_C(32), USIZE_C(6), USIZE_C(16), block, USIZE_C(2));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
OddBlockSizeInRange(void)
{
    u8    buf[30];
    u8    block[3];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "OddBlockSizeInRange -> ");

    block[0] = U8_C(0xA1);
    block[1] = U8_C(0xA2);
    block[2] = U8_C(0xA3);

    kdi_Fill_u8(buf, USIZE_C(30), U8_C(0xFF));

    /* Fill range [3..17] with repeating 3-byte block (5 repetitions) */
    for (i = 0; i < 5; ++i)
    {
        buf[3 + i * 3 + 0] = U8_C(0xA1);
        buf[3 + i * 3 + 1] = U8_C(0xA2);
        buf[3 + i * 3 + 2] = U8_C(0xA3);
    }

    result = false;
    status = kdGenMemOpsIsBlocksBound(&result, buf, USIZE_C(30), USIZE_C(3), USIZE_C(15), block, USIZE_C(3));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
NonPowerOfTwoBlockSizeInRange(void)
{
    u8    buf[65];
    u8    block[5];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "NonPowerOfTwoBlockSizeInRange -> ");

    block[0] = U8_C(0x10);
    block[1] = U8_C(0x20);
    block[2] = U8_C(0x30);
    block[3] = U8_C(0x40);
    block[4] = U8_C(0x50);

    kdi_Fill_u8(buf, USIZE_C(65), U8_C(0xFF));

    /* Fill range [10..39] with repeating 5-byte block (6 repetitions) */
    for (i = 0; i < 6; ++i)
    {
        buf[10 + i * 5 + 0] = U8_C(0x10);
        buf[10 + i * 5 + 1] = U8_C(0x20);
        buf[10 + i * 5 + 2] = U8_C(0x30);
        buf[10 + i * 5 + 3] = U8_C(0x40);
        buf[10 + i * 5 + 4] = U8_C(0x50);
    }

    result = false;
    status = kdGenMemOpsIsBlocksBound(&result, buf, USIZE_C(65), USIZE_C(10), USIZE_C(30), block, USIZE_C(5));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
CountClamping(void)
{
    u8    buf[32];
    u8    block[4];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "CountClamping -> ");

    /* Set up block pattern */
    block[0] = U8_C(0x11);
    block[1] = U8_C(0x22);
    block[2] = U8_C(0x33);
    block[3] = U8_C(0x44);

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xFF));

    /* Fill last 8 bytes with repeating block (2 repetitions) */
    for (i = 0; i < 2; ++i)
    {
        buf[24 + i * 4 + 0] = U8_C(0x11);
        buf[24 + i * 4 + 1] = U8_C(0x22);
        buf[24 + i * 4 + 2] = U8_C(0x33);
        buf[24 + i * 4 + 3] = U8_C(0x44);
    }

    /* Request 100 bytes starting from index 24.
     * Available = 32 - 24 = 8 bytes.
     * Clamped count = 8.
     */
    result = false;
    status = kdGenMemOpsIsBlocksBound(&result, buf, USIZE_C(32), USIZE_C(24), USIZE_C(100), block, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
MismatchInFirstBlockOfRange(void)
{
    u8    buf[32];
    u8    block[4];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "MismatchInFirstBlockOfRange -> ");

    block[0] = U8_C(0xAA);
    block[1] = U8_C(0xBB);
    block[2] = U8_C(0xCC);
    block[3] = U8_C(0xDD);

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xFF));

    /* Fill range with repeating block */
    for (i = 0; i < 4; ++i)
    {
        buf[8 + i * 4 + 0] = U8_C(0xAA);
        buf[8 + i * 4 + 1] = U8_C(0xBB);
        buf[8 + i * 4 + 2] = U8_C(0xCC);
        buf[8 + i * 4 + 3] = U8_C(0xDD);
    }

    /* Create mismatch in first block of range */
    buf[9] = U8_C(0xEE);

    result = true;
    status = kdGenMemOpsIsBlocksBound(&result, buf, USIZE_C(32), USIZE_C(8), USIZE_C(16), block, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
MismatchInLastBlockOfRange(void)
{
    u8    buf[32];
    u8    block[4];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "MismatchInLastBlockOfRange -> ");

    block[0] = U8_C(0xAA);
    block[1] = U8_C(0xBB);
    block[2] = U8_C(0xCC);
    block[3] = U8_C(0xDD);

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xFF));

    /* Fill range with repeating block */
    for (i = 0; i < 4; ++i)
    {
        buf[8 + i * 4 + 0] = U8_C(0xAA);
        buf[8 + i * 4 + 1] = U8_C(0xBB);
        buf[8 + i * 4 + 2] = U8_C(0xCC);
        buf[8 + i * 4 + 3] = U8_C(0xDD);
    }

    /* Create mismatch in last block of range */
    buf[23] = U8_C(0xEE);

    result  = true;
    status  = kdGenMemOpsIsBlocksBound(&result, buf, USIZE_C(32), USIZE_C(8), USIZE_C(16), block, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
AllZerosBlockInRange(void)
{
    u8   buf[32];
    u8   block[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "AllZerosBlockInRange -> ");

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xFF));
    kdi_Fill_u8(&buf[8], USIZE_C(16), U8_C(0x00));
    kdi_Fill_u8(block, USIZE_C(4), U8_C(0x00));

    result = false;
    status = kdGenMemOpsIsBlocksBound(&result, buf, USIZE_C(32), USIZE_C(8), USIZE_C(16), block, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
AllOnesBlockInRange(void)
{
    u8   buf[32];
    u8   block[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "AllOnesBlockInRange -> ");

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));
    kdi_Fill_u8(&buf[8], USIZE_C(16), U8_C(0xFF));
    kdi_Fill_u8(block, USIZE_C(4), U8_C(0xFF));

    result = false;
    status = kdGenMemOpsIsBlocksBound(&result, buf, USIZE_C(32), USIZE_C(8), USIZE_C(16), block, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
RangeOutsideMatchingPattern(void)
{
    u8    buf[48];
    u8    block[4];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "RangeOutsideMatchingPattern -> ");

    block[0] = U8_C(0x11);
    block[1] = U8_C(0x22);
    block[2] = U8_C(0x33);
    block[3] = U8_C(0x44);

    /* Fill buffer with three regions */
    kdi_Fill_u8(&buf[0], USIZE_C(16), U8_C(0xFF));  /* Before range */
    kdi_Fill_u8(&buf[32], USIZE_C(16), U8_C(0xEE)); /* After range */

    /* Fill middle range [16..31] with repeating block */
    for (i = 0; i < 4; ++i)
    {
        buf[16 + i * 4 + 0] = U8_C(0x11);
        buf[16 + i * 4 + 1] = U8_C(0x22);
        buf[16 + i * 4 + 2] = U8_C(0x33);
        buf[16 + i * 4 + 3] = U8_C(0x44);
    }

    /* Check only middle range */
    result = false;
    status = kdGenMemOpsIsBlocksBound(&result, buf, USIZE_C(48), USIZE_C(16), USIZE_C(16), block, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Verify outside regions weren't affected */
    assert(buf[0] == U8_C(0xFF));
    assert(buf[15] == U8_C(0xFF));
    assert(buf[32] == U8_C(0xEE));
    assert(buf[47] == U8_C(0xEE));

    printf("PASSED\n");
}


void
LargeBufferWithLargeBlockSize(void)
{
    u8    buf[256];
    u8    block[16];
    bool  result;
    bool  status;
    usize i, j;

    printf(LOG_PREFIX_CSTR "LargeBufferWithLargeBlockSize -> ");

    /* Set up 16-byte block pattern */
    for (i = 0; i < 16; ++i)
    {
        block[i] = (u8)(i + 0x10);
    }

    kdi_Fill_u8(buf, USIZE_C(256), U8_C(0xFF));

    /* Fill range [64..191] with repeating 16-byte block (8 repetitions) */
    for (i = 0; i < 8; ++i)
    {
        for (j = 0; j < 16; ++j)
        {
            buf[64 + i * 16 + j] = (u8)(j + 0x10);
        }
    }

    result = false;
    status = kdGenMemOpsIsBlocksBound(&result, buf, USIZE_C(256), USIZE_C(64), USIZE_C(128), block, USIZE_C(16));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
ArbitraryByteCounts(void)
{
    u8    buf[63];
    u8    block[3];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "ArbitraryByteCounts -> ");

    block[0] = U8_C(0xA1);
    block[1] = U8_C(0xA2);
    block[2] = U8_C(0xA3);

    kdi_Fill_u8(buf, USIZE_C(63), U8_C(0xFF));

    /* Fill range [9..35] with repeating 3-byte block (9 repetitions) */
    for (i = 0; i < 9; ++i)
    {
        buf[9 + i * 3 + 0] = U8_C(0xA1);
        buf[9 + i * 3 + 1] = U8_C(0xA2);
        buf[9 + i * 3 + 2] = U8_C(0xA3);
    }

    /* Odd byte count (9 bytes, 3 blocks) */
    result = false;
    status = kdGenMemOpsIsBlocksBound(&result, buf, USIZE_C(63), USIZE_C(9), USIZE_C(9), block, USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Odd byte count (15 bytes, 5 blocks) */
    result = false;
    status = kdGenMemOpsIsBlocksBound(&result, buf, USIZE_C(63), USIZE_C(9), USIZE_C(15), block, USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Non-power-of-2 count (6 bytes, 2 blocks) */
    result = false;
    status = kdGenMemOpsIsBlocksBound(&result, buf, USIZE_C(63), USIZE_C(9), USIZE_C(6), block, USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Non-power-of-2 count (21 bytes, 7 blocks) */
    result = false;
    status = kdGenMemOpsIsBlocksBound(&result, buf, USIZE_C(63), USIZE_C(9), USIZE_C(21), block, USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
ByteCountNotMultipleOfBlockSize(void)
{
    u8    buf[32];
    u8    block[4];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "ByteCountNotMultipleOfBlockSize -> ");

    block[0] = U8_C(0xAA);
    block[1] = U8_C(0xBB);
    block[2] = U8_C(0xCC);
    block[3] = U8_C(0xDD);

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xFF));

    /* Fill range with repeating block */
    for (i = 0; i < 4; ++i)
    {
        buf[8 + i * 4 + 0] = U8_C(0xAA);
        buf[8 + i * 4 + 1] = U8_C(0xBB);
        buf[8 + i * 4 + 2] = U8_C(0xCC);
        buf[8 + i * 4 + 3] = U8_C(0xDD);
    }

    /* byte_count = 14 (not multiple of block_sz = 4) */
    /* Should check 3 complete blocks, ignore partial */
    result = true;
    status = kdGenMemOpsIsBlocksBound(&result, buf, USIZE_C(32), USIZE_C(8), USIZE_C(14), block, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
U16BlocksInRange(void)
{
    u16   buf[32];
    u16   block[2];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "U16BlocksInRange -> ");

    /* Block pattern: two u16 values */
    block[0] = U16_C(0x1234);
    block[1] = U16_C(0x5678);

    /* Fill buffer outside range */
    for (i = 0; i < 32; ++i)
    {
        buf[i] = U16_C(0xFFFF);
    }

    /* Fill range [index 8..23] with repeating block (4 repetitions) */
    for (i = 0; i < 4; ++i)
    {
        buf[8 + i * 2 + 0] = U16_C(0x1234);
        buf[8 + i * 2 + 1] = U16_C(0x5678);
    }

    result = false;
    status = kdGenMemOpsIsBlocksBound(&result, buf, sizeof(buf), USIZE_C(16), USIZE_C(16), block, sizeof(block));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
U32BlocksInRange(void)
{
    u32   buf[24];
    u32   block[2];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "U32BlocksInRange -> ");

    /* Block pattern: two u32 values */
    block[0] = U32_C(0x12345678);
    block[1] = U32_C(0xABCDEF01);

    /* Fill buffer outside range */
    for (i = 0; i < 24; ++i)
    {
        buf[i] = U32_C(0xFFFFFFFF);
    }

    /* Fill range [index 8..15] with repeating block (4 repetitions) */
    for (i = 0; i < 4; ++i)
    {
        buf[8 + i * 2 + 0] = U32_C(0x12345678);
        buf[8 + i * 2 + 1] = U32_C(0xABCDEF01);
    }

    result = false;
    status = kdGenMemOpsIsBlocksBound(&result, buf, sizeof(buf), USIZE_C(32), USIZE_C(32), block, sizeof(block));

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

    BasicArguments();
    BeginIndexOutOfBounds();
    BlockSizeGreaterThanByteCount();
    SingleBlockInRange();
    MultipleBlocksInRangeAllMatch();
    MultipleBlocksInRangeOneMismatch();
    SingleByteBlockInRange();
    TwoByteBlockInRange();
    OddBlockSizeInRange();
    NonPowerOfTwoBlockSizeInRange();
    CountClamping();
    MismatchInFirstBlockOfRange();
    MismatchInLastBlockOfRange();
    AllZerosBlockInRange();
    AllOnesBlockInRange();
    RangeOutsideMatchingPattern();
    LargeBufferWithLargeBlockSize();
    ArbitraryByteCounts();
    ByteCountNotMultipleOfBlockSize();
    U16BlocksInRange();
    U32BlocksInRange();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
