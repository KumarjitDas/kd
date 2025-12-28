/**
 * @file kdGenMemOpsCountBlocksBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsCountBlocksBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsCountBlocksBound function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8    buf[32];
    u8    blk[4];
    usize count = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0x00));

    /* count pointer is null -> failure */
    status = kdGenMemOpsCountBlocksBound(null, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountBlocksBound(&count, null, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* block is null -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountBlocksBound(&count, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* begin_idx >= base_sz -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountBlocksBound(&count, buf, USIZE_C(32), USIZE_C(32), USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* end_count_byte is zero -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountBlocksBound(&count, buf, USIZE_C(32), USIZE_C(0), USIZE_C(0), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* block_sz is zero -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountBlocksBound(&count, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* base_sz not divisible by block_sz -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountBlocksBound(&count, buf, USIZE_C(31), USIZE_C(0), USIZE_C(31), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* begin_idx not aligned to block_sz -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountBlocksBound(&count, buf, USIZE_C(32), USIZE_C(3), USIZE_C(29), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* Valid arguments - 8 matching blocks of size 4 = count of 32 */
    count  = 55;
    status = kdGenMemOpsCountBlocksBound(&count, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(32)); /* 8 blocks × 4 bytes = 32 */

    printf("PASSED\n");
}


void
CountNone(void)
{
    u8    buf[32];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountNone -> ");

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));
    blk[0] = 0x11;
    blk[1] = 0x22;
    blk[2] = 0x33;
    blk[3] = 0x44;

    /* Search for non-existent block in range [0, 32) */
    status = kdGenMemOpsCountBlocksBound(&count, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    printf("PASSED\n");
}


void
CountAll(void)
{
    u8    buf[32];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountAll -> ");

    /* Fill entire buffer with same block pattern */
    blk[0] = 0xAA;
    blk[1] = 0xBB;
    blk[2] = 0xCC;
    blk[3] = 0xDD;

    for (usize i = 0; i < 8; ++i)
    {
        buf[i * 4]     = 0xAA;
        buf[i * 4 + 1] = 0xBB;
        buf[i * 4 + 2] = 0xCC;
        buf[i * 4 + 3] = 0xDD;
    }

    /* Search in full range - all 8 blocks match */
    status = kdGenMemOpsCountBlocksBound(&count, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(32)); /* 8 blocks × 4 bytes = 32 */

    printf("PASSED\n");
}


void
CountSubrange(void)
{
    u8    buf[40];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountSubrange -> ");

    /* Pattern: blocks at positions 0, 8, 16, 24, 32 match, others don't */
    kdi_Fill_u8(buf, USIZE_C(40), U8_C(0x00));
    
    blk[0] = 0xFF;
    blk[1] = 0xFF;
    blk[2] = 0xFF;
    blk[3] = 0xFF;

    /* Set matching blocks */
    buf[0] = 0xFF; buf[1] = 0xFF; buf[2] = 0xFF; buf[3] = 0xFF;
    buf[8] = 0xFF; buf[9] = 0xFF; buf[10] = 0xFF; buf[11] = 0xFF;
    buf[16] = 0xFF; buf[17] = 0xFF; buf[18] = 0xFF; buf[19] = 0xFF;
    buf[24] = 0xFF; buf[25] = 0xFF; buf[26] = 0xFF; buf[27] = 0xFF;
    buf[32] = 0xFF; buf[33] = 0xFF; buf[34] = 0xFF; buf[35] = 0xFF;

    /* Range [4, 28) - byte indices 4-27, includes blocks at 8, 16, 24 = 3 blocks */
    status = kdGenMemOpsCountBlocksBound(&count, buf, USIZE_C(40), USIZE_C(4), USIZE_C(24), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(12)); /* 3 blocks × 4 bytes = 12 */

    /* Range [0, 20) - blocks at 0, 8, 16 = 3 blocks */
    status = kdGenMemOpsCountBlocksBound(&count, buf, USIZE_C(40), USIZE_C(0), USIZE_C(20), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(12)); /* 3 blocks × 4 bytes = 12 */

    /* Range [20, 40) - blocks at 24, 32 = 2 blocks */
    status = kdGenMemOpsCountBlocksBound(&count, buf, USIZE_C(40), USIZE_C(20), USIZE_C(20), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(8)); /* 2 blocks × 4 bytes = 8 */

    printf("PASSED\n");
}


void
ClampedEndCount(void)
{
    u8    buf[32];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ClampedEndCount -> ");

    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xBB));

    for (usize i = 0; i < 8; ++i)
    {
        buf[i * 4]     = 0xBB;
        buf[i * 4 + 1] = 0xBB;
        buf[i * 4 + 2] = 0xBB;
        buf[i * 4 + 3] = 0xBB;
    }

    /* Request 100 bytes starting at 0, should clamp to 32 */
    status = kdGenMemOpsCountBlocksBound(&count, buf, USIZE_C(32), USIZE_C(0), USIZE_C(100), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(32)); /* 8 blocks × 4 bytes = 32 */

    /* Request 50 bytes starting at 16, should clamp to 16 (blocks at 16, 20, 24, 28) */
    status = kdGenMemOpsCountBlocksBound(&count, buf, USIZE_C(32), USIZE_C(16), USIZE_C(50), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16)); /* 4 blocks × 4 bytes = 16 */

    printf("PASSED\n");
}


void
SingleBlock(void)
{
    u8    buf[16];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleBlock -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));
    
    blk[0] = 0x11;
    blk[1] = 0x22;
    blk[2] = 0x33;
    blk[3] = 0x44;

    /* Set one matching block at offset 8 */
    buf[8] = 0x11; buf[9] = 0x22; buf[10] = 0x33; buf[11] = 0x44;

    /* Range [8, 12) - single block match */
    status = kdGenMemOpsCountBlocksBound(&count, buf, USIZE_C(16), USIZE_C(8), USIZE_C(4), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(4)); /* 1 block × 4 bytes = 4 */

    /* Range [0, 8) - no match */
    status = kdGenMemOpsCountBlocksBound(&count, buf, USIZE_C(16), USIZE_C(0), USIZE_C(8), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    printf("PASSED\n");
}


void
U16_CountBlocksBound(void)
{
    u16   buf[16];
    u16   blk[1];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "U16_CountBlocksBound -> ");

    /* Pattern: 100, 200, 100, 300, 100, 400, 100, 500, ... */
    buf[0] = 100; buf[1] = 200; buf[2] = 100; buf[3] = 300;
    buf[4] = 100; buf[5] = 400; buf[6] = 100; buf[7] = 500;
    buf[8] = 100; buf[9] = 600; buf[10] = 100; buf[11] = 700;
    buf[12] = 100; buf[13] = 800; buf[14] = 100; buf[15] = 900;

    blk[0] = 100;

    /* Range [0, 32) - full buffer, 8 matches */
    status = kdGenMemOpsCountBlocksBound(&count, buf, sizeof(buf), USIZE_C(0), sizeof(buf), blk, sizeof(u16));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16)); /* 8 blocks × 2 bytes = 16 */

    /* Range [4, 20) - byte range 4-19, u16 indices 2-9, matches at 2,4,6,8 = 4 */
    status = kdGenMemOpsCountBlocksBound(&count, buf, sizeof(buf), USIZE_C(4), USIZE_C(16), blk, sizeof(u16));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(8)); /* 4 blocks × 2 bytes = 8 */

    printf("PASSED\n");
}


void
U32_CountBlocksBound(void)
{
    u32   buf[12];
    u32   blk[1];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_CountBlocksBound -> ");

    /* Pattern: 1000 at even indices, others at odd */
    buf[0] = 1000; buf[1] = 2000; buf[2] = 1000; buf[3] = 3000;
    buf[4] = 1000; buf[5] = 4000; buf[6] = 1000; buf[7] = 5000;
    buf[8] = 1000; buf[9] = 6000; buf[10] = 1000; buf[11] = 7000;

    blk[0] = 1000;

    /* Range [0, 48) - full buffer, 6 matches */
    status = kdGenMemOpsCountBlocksBound(&count, buf, sizeof(buf), USIZE_C(0), sizeof(buf), blk, sizeof(u32));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(24)); /* 6 blocks × 4 bytes = 24 */

    /* Range [8, 32) - byte range 8-31, u32 indices 2-7, matches at 2,4,6 = 3 */
    status = kdGenMemOpsCountBlocksBound(&count, buf, sizeof(buf), USIZE_C(8), USIZE_C(24), blk, sizeof(u32));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(12)); /* 3 blocks × 4 bytes = 12 */

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_CountBlocksBound(void)
{
    u64   buf[10];
    u64   blk[1];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "U64_CountBlocksBound -> ");

    /* Pattern: 0xAAAA... at even indices, 0xBBBB... at odd */
    buf[0] = U64_C(0xAAAAAAAAAAAAAAAA);
    buf[1] = U64_C(0xBBBBBBBBBBBBBBBB);
    buf[2] = U64_C(0xAAAAAAAAAAAAAAAA);
    buf[3] = U64_C(0xCCCCCCCCCCCCCCCC);
    buf[4] = U64_C(0xAAAAAAAAAAAAAAAA);
    buf[5] = U64_C(0xDDDDDDDDDDDDDDDD);
    buf[6] = U64_C(0xAAAAAAAAAAAAAAAA);
    buf[7] = U64_C(0xEEEEEEEEEEEEEEEE);
    buf[8] = U64_C(0xAAAAAAAAAAAAAAAA);
    buf[9] = U64_C(0xFFFFFFFFFFFFFFFF);

    blk[0] = U64_C(0xAAAAAAAAAAAAAAAA);

    /* Range [0, 80) - full buffer, 5 matches */
    status = kdGenMemOpsCountBlocksBound(&count, buf, sizeof(buf), USIZE_C(0), sizeof(buf), blk, sizeof(u64));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(40)); /* 5 blocks × 8 bytes = 40 */

    /* Range [16, 64) - byte range 16-63, u64 indices 2-7, matches at 2,4,6 = 3 */
    status = kdGenMemOpsCountBlocksBound(&count, buf, sizeof(buf), USIZE_C(16), USIZE_C(48), blk, sizeof(u64));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(24)); /* 3 blocks × 8 bytes = 24 */

    printf("PASSED\n");
}
#endif


typedef struct kdi_TestStruct
{
    u32 x;
    u32 y;
    u16 z;
} kdi_TestStruct;


void
Struct_CountBlocksBound(void)
{
    kdi_TestStruct buf[8];
    kdi_TestStruct blk;
    usize          count;
    bool           status;
    usize          struct_sz = sizeof(kdi_TestStruct);

    printf(LOG_PREFIX_CSTR "Struct_CountBlocksBound -> ");

    /* Target struct */
    blk.x = 100;
    blk.y = 200;
    blk.z = 300;

    /* Pattern: target at indices 0, 2, 4, 6 */
    buf[0] = blk;
    buf[1].x = 999; buf[1].y = 999; buf[1].z = 999;
    buf[2] = blk;
    buf[3].x = 888; buf[3].y = 888; buf[3].z = 888;
    buf[4] = blk;
    buf[5].x = 777; buf[5].y = 777; buf[5].z = 777;
    buf[6] = blk;
    buf[7].x = 666; buf[7].y = 666; buf[7].z = 666;

    /* Range [0, full) - 4 matches */
    status = kdGenMemOpsCountBlocksBound(&count, buf, sizeof(buf), USIZE_C(0), sizeof(buf), &blk, struct_sz);
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(4) * struct_sz); /* 4 blocks × struct size */

    /* Range [struct_sz, 4*struct_sz) - indices 1-3, match at index 2 = 1 */
    status = kdGenMemOpsCountBlocksBound(&count, buf, sizeof(buf), struct_sz, USIZE_C(3) * struct_sz, &blk, struct_sz);
    assert(status == RESULT_SUCCESS);
    assert(count == struct_sz); /* 1 block × struct size */

    printf("PASSED\n");
}


void
EdgeBlocks(void)
{
    u8    buf[32];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "EdgeBlocks -> ");

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xFF));

    /* Set first and last blocks */
    buf[0] = 0xFF; buf[1] = 0xFF; buf[2] = 0xFF; buf[3] = 0xFF;
    buf[28] = 0xFF; buf[29] = 0xFF; buf[30] = 0xFF; buf[31] = 0xFF;

    /* Range [0, 4) - first block only */
    status = kdGenMemOpsCountBlocksBound(&count, buf, USIZE_C(32), USIZE_C(0), USIZE_C(4), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(4)); /* 1 block × 4 bytes = 4 */

    /* Range [28, 32) - last block only */
    status = kdGenMemOpsCountBlocksBound(&count, buf, USIZE_C(32), USIZE_C(28), USIZE_C(4), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(4)); /* 1 block × 4 bytes = 4 */

    /* Range [0, 32) - both edges */
    status = kdGenMemOpsCountBlocksBound(&count, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(8)); /* 2 blocks × 4 bytes = 8 */

    printf("PASSED\n");
}


void
ConsecutiveBlocks(void)
{
    u8    buf[48];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ConsecutiveBlocks -> ");

    /* First 24 bytes: target blocks, last 24 bytes: different */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xAA));

    for (usize i = 0; i < 6; ++i)
    {
        buf[i * 4]     = 0xAA;
        buf[i * 4 + 1] = 0xAA;
        buf[i * 4 + 2] = 0xAA;
        buf[i * 4 + 3] = 0xAA;
    }

    kdi_Fill_u8(buf + 24, USIZE_C(24), U8_C(0xBB));

    /* Range [8, 32) - includes last 4 of target and first 2 of non-target */
    status = kdGenMemOpsCountBlocksBound(&count, buf, USIZE_C(48), USIZE_C(8), USIZE_C(24), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16)); /* 4 blocks × 4 bytes = 16 */

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    u8    buf[200];
    u8    blk[5];
    usize count;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    /* Pattern: repeating 1,2,3,4,5 */
    for (i = 0; i < 200; ++i)
    {
        buf[i] = (u8)((i % 5) + 1);
    }

    blk[0] = 1; blk[1] = 2; blk[2] = 3; blk[3] = 4; blk[4] = 5;

    /* Range [0, 200) - full buffer, 40 blocks */
    status = kdGenMemOpsCountBlocksBound(&count, buf, USIZE_C(200), USIZE_C(0), USIZE_C(200), blk, USIZE_C(5));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(200)); /* 40 blocks × 5 bytes = 200 */

    /* Range [50, 150) - 20 blocks */
    status = kdGenMemOpsCountBlocksBound(&count, buf, USIZE_C(200), USIZE_C(50), USIZE_C(100), blk, USIZE_C(5));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(100)); /* 20 blocks × 5 bytes = 100 */

    printf("PASSED\n");
}


void
PartialBlocks(void)
{
    u8    buf[32];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "PartialBlocks -> ");

    /* Pattern: blocks that partially match but not completely */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));
    
    blk[0] = 1; blk[1] = 2; blk[2] = 3; blk[3] = 4;

    /* Set blocks: [1,2,3,4] at 0, [1,2,3,5] at 8, [1,2,3,4] at 16, [1,9,3,4] at 24 */
    buf[0] = 1; buf[1] = 2; buf[2] = 3; buf[3] = 4;
    buf[8] = 1; buf[9] = 2; buf[10] = 3; buf[11] = 5; /* partial */
    buf[16] = 1; buf[17] = 2; buf[18] = 3; buf[19] = 4;
    buf[24] = 1; buf[25] = 9; buf[26] = 3; buf[27] = 4; /* partial */

    /* Range [0, 32) - only full matches at 0 and 16 = 2 */
    status = kdGenMemOpsCountBlocksBound(&count, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(8)); /* 2 blocks × 4 bytes = 8 */

    printf("PASSED\n");
}


void
SingleByteBlocks(void)
{
    u8    buf[20];
    u8    blk[1];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleByteBlocks -> ");

    kdi_Fill_u8(buf, USIZE_C(20), U8_C(0x00));
    buf[3] = 0xFF;
    buf[7] = 0xFF;
    buf[11] = 0xFF;
    buf[15] = 0xFF;
    buf[19] = 0xFF;

    blk[0] = 0xFF;

    /* Range [0, 20) - 5 matches */
    status = kdGenMemOpsCountBlocksBound(&count, buf, USIZE_C(20), USIZE_C(0), USIZE_C(20), blk, USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(5)); /* 5 blocks × 1 byte = 5 */

    /* Range [5, 15) - matches at 7, 11 = 2 */
    status = kdGenMemOpsCountBlocksBound(&count, buf, USIZE_C(20), USIZE_C(5), USIZE_C(10), blk, USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(2)); /* 2 blocks × 1 byte = 2 */

    printf("PASSED\n");
}


void
OddSizes(void)
{
    u8    buf[39];
    u8    blk[3];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "OddSizes -> ");

    /* Fill with repeating pattern */
    kdi_Fill_u8(blk, USIZE_C(3), U8_C(0x77));

    for (usize i = 0; i < 13; ++i)
    {
        buf[i * 3]     = 0x77;
        buf[i * 3 + 1] = 0x77;
        buf[i * 3 + 2] = 0x77;
    }

    /* Range [3, 33) - 10 blocks */
    status = kdGenMemOpsCountBlocksBound(&count, buf, USIZE_C(39), USIZE_C(3), USIZE_C(30), blk, USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(30)); /* 10 blocks × 3 bytes = 30 */

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    CountNone();
    CountAll();
    CountSubrange();
    ClampedEndCount();
    SingleBlock();

    U16_CountBlocksBound();
    U32_CountBlocksBound();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_CountBlocksBound();
#endif
    Struct_CountBlocksBound();

    EdgeBlocks();
    ConsecutiveBlocks();
    LargeBuffer();
    PartialBlocks();
    SingleByteBlocks();
    OddSizes();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}