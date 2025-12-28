/**
 * @file kdGenMemOpsCountNotBlocksBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsCountNotBlocksBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsCountNotBlocksBound function test"
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
    status = kdGenMemOpsCountNotBlocksBound(null, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountNotBlocksBound(&count, null, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* block is null -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* begin_idx >= base_sz -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(32), USIZE_C(32), USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* end_count_byte is zero -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(32), USIZE_C(0), USIZE_C(0), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* block_sz is zero -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* base_sz not divisible by block_sz -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(31), USIZE_C(0), USIZE_C(31), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* begin_idx not aligned to block_sz -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(32), USIZE_C(3), USIZE_C(29), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* Valid arguments - all blocks match, so count NOT = 0 */
    count  = 55;
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

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

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xAA));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xAA));

    /* Search for NOT matching block in range [0, 32) - all match */
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));

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

    /* Buffer blocks are all 0x00, target is 0xFF - none match */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xFF));

    /* Search in full range - all 8 blocks are NOT 0xFF */
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(32)); /* 8 blocks × 4 bytes = 32 */

    printf("PASSED\n");
}


void
CountSingle(void)
{
    u8    buf[32];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountSingle -> ");

    /* All blocks are 0xAA except one */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xAA));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xAA));

    /* Change block at offset 12 to 0xFF */
    kdi_Fill_u8(buf + 12, USIZE_C(4), U8_C(0xFF));

    /* Count NOT 0xAA blocks in range [0, 32). Only 1 block doesn't match. */
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(4));

    printf("PASSED\n");
}


void
RangeConstraints(void)
{
    u8    buf[48];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "RangeConstraints -> ");

    /* 12 blocks total */
    kdi_Fill_u8(buf, USIZE_C(48), U8_C(0xAA));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xAA));

    /* Set mismatches at blocks 1, 4, 7, 10 (offsets 4, 16, 28, 40) */
    kdi_Fill_u8(buf + 4, USIZE_C(4), U8_C(0xBB));
    kdi_Fill_u8(buf + 16, USIZE_C(4), U8_C(0xBB));
    kdi_Fill_u8(buf + 28, USIZE_C(4), U8_C(0xBB));
    kdi_Fill_u8(buf + 40, USIZE_C(4), U8_C(0xBB));

    /* Range [8, 36). Blocks 2-8 (offsets 8, 12, 16, 20, 24, 28, 32).
     * Mismatches at offsets 16, 28. Count = 2 × 4 = 8. */
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(48), USIZE_C(8), USIZE_C(28), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(8));

    printf("PASSED\n");
}


void
EndValueClamping(void)
{
    u8    buf[32];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "EndValueClamping -> ");

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xAA));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xAA));

    /* Set mismatch at last block (offset 28) */
    kdi_Fill_u8(buf + 28, USIZE_C(4), U8_C(0xBB));

    /* Requesting 100 bytes starting at 0, clamps to 32. Range [0, 32). */
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(32), USIZE_C(0), USIZE_C(100), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(4)); /* 1 mismatch × 4 bytes = 4 */

    printf("PASSED\n");
}


void
StartAlignment(void)
{
    u8    buf[32];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "StartAlignment -> ");

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xAA));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xAA));

    /* Start 1 (not aligned) -> failure */
    count  = 55;
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(32), USIZE_C(1), USIZE_C(28), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* Start 8 (aligned) -> success */
    count  = 55;
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(32), USIZE_C(8), USIZE_C(24), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
U16_CountNotBlocksBound(void)
{
    u16   buf[12];
    u16   blk = 0xAAAA;
    usize count;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "U16_CountNotBlocksBound -> ");

    for (i = 0; i < 12; ++i)
        buf[i] = 0xAAAA;

    /* Set mismatches at indices 2, 5, 8 */
    buf[2] = 0xBBBB;
    buf[5] = 0xBBBB;
    buf[8] = 0xBBBB;

    /* Range [4, 20) in bytes = indices 2-9.
     * Mismatches at indices 2, 5, 8. Count = 3 × 2 = 6. */
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, sizeof(buf), USIZE_C(4), USIZE_C(16), &blk, sizeof(u16));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(6));

    printf("PASSED\n");
}


void
U32_CountNotBlocksBound(void)
{
    u32   buf[10];
    u32   blk = 0x12345678;
    usize count;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "U32_CountNotBlocksBound -> ");

    for (i = 0; i < 10; ++i)
        buf[i] = 0x12345678;

    /* Set mismatches at indices 1, 3, 8 */
    buf[1] = 0x99999999;
    buf[3] = 0x88888888;
    buf[8] = 0x77777777;

    /* Range [0, 40) in bytes = all 10 blocks.
     * Mismatches: 3. Count = 3 × 4 = 12. */
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, sizeof(buf), USIZE_C(0), USIZE_C(40), &blk, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(12));

    /* Range [8, 32) in bytes = indices 2-7.
     * Mismatch at index 3. Count = 1 × 4 = 4. */
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, sizeof(buf), USIZE_C(8), USIZE_C(24), &blk, sizeof(u32));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(4));

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_CountNotBlocksBound(void)
{
    u64   buf[10];
    u64   blk = U64_C(0x1111222233334444);
    usize count;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "U64_CountNotBlocksBound -> ");

    for (i = 0; i < 10; ++i)
        buf[i] = blk;

    /* Set mismatches at indices 2, 5 */
    buf[2] = U64_C(0xFFFFFFFFFFFFFFFF);
    buf[5] = U64_C(0xEEEEEEEEEEEEEEEE);

    /* Range [16, 64) in bytes = indices 2-7.
     * Mismatches at 2, 5. Count = 2 × 8 = 16. */
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, sizeof(buf), USIZE_C(16), USIZE_C(48), &blk, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

    printf("PASSED\n");
}
#endif


typedef struct kdi_TestStruct
{
    u64 a;
    u64 b;
    u64 c;
} kdi_TestStruct;


void
Struct_CountNotBlocksBound(void)
{
    kdi_TestStruct buf[8];
    kdi_TestStruct blk;
    usize          count;
    bool           status;
    usize          i;

    printf(LOG_PREFIX_CSTR "Struct_CountNotBlocksBound -> ");

    blk.a = 1;
    blk.b = 2;
    blk.c = 3;

    for (i = 0; i < 8; ++i)
        buf[i] = blk;

    /* Set mismatches at indices 1, 4, 6 */
    buf[1].a = 99;
    buf[4].a = 88;
    buf[6].a = 77;

    /* Range [0, sizeof(buf)). All 8 blocks.
     * Mismatches: 3. Count = 3 × 24 = 72. */
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, sizeof(buf), USIZE_C(0), sizeof(buf), &blk, sizeof(kdi_TestStruct));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(72));

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    u8    buf[1000];
    u8    blk[10];
    usize count;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    /* Pattern: 0, 1, 2, ..., 9 repeating */
    for (i = 0; i < 1000; ++i)
    {
        buf[i] = (u8)(i % 10);
    }

    /* Target: [0, 1, 2, ..., 9] */
    for (i = 0; i < 10; ++i)
    {
        blk[i] = (u8)i;
    }

    /* All 100 blocks match, so count NOT = 0. */
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(1000), USIZE_C(0), USIZE_C(1000), blk, USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    /* Modify blocks at offsets 100, 300, 500, 700, 900 */
    buf[100] = 0xFF;
    buf[300] = 0xFF;
    buf[500] = 0xFF;
    buf[700] = 0xFF;
    buf[900] = 0xFF;

    /* Now 5 blocks are modified. Count NOT = 5 × 10 = 50. */
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(1000), USIZE_C(0), USIZE_C(1000), blk, USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(50));

    /* Range [200, 800). Includes modified blocks at 300, 500, 700.
     * Count = 3 × 10 = 30. */
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(1000), USIZE_C(200), USIZE_C(600), blk, USIZE_C(10));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(30));

    printf("PASSED\n");
}


void
AlternatingBlocks(void)
{
    u8    buf[40];
    u8    blk[5];
    usize count;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "AlternatingBlocks -> ");

    /* Pattern: [A,A,A,A,A], [B,B,B,B,B], ... */
    for (i = 0; i < 8; ++i)
    {
        kdi_Fill_u8(buf + i * 5, USIZE_C(5), (i % 2 == 0) ? U8_C(0xAA) : U8_C(0xBB));
    }

    kdi_Fill_u8(blk, USIZE_C(5), U8_C(0xAA));

    /* Count NOT [A,A,A,A,A] in range [0, 40). 4 blocks are [B,B,B,B,B].
     * Count = 4 × 5 = 20. */
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(40), USIZE_C(0), USIZE_C(40), blk, USIZE_C(5));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(20));

    /* Range [10, 30). Blocks 2-5 (offsets 10, 15, 20, 25).
     * Pattern: A, B, A, B. 2 are NOT A. Count = 2 × 5 = 10. */
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(40), USIZE_C(10), USIZE_C(20), blk, USIZE_C(5));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(10));

    printf("PASSED\n");
}


void
ConsecutiveMatches(void)
{
    u8    buf[48];
    u8    blk[6];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ConsecutiveMatches -> ");

    /* First 4 blocks: [1,2,3,4,5,6], last 4 blocks: [7,8,9,A,B,C] */
    kdi_Fill_u8(blk, USIZE_C(6), U8_C(0x00));
    blk[0] = 1;
    blk[1] = 2;
    blk[2] = 3;
    blk[3] = 4;
    blk[4] = 5;
    blk[5] = 6;

    for (usize i = 0; i < 4; ++i)
    {
        buf[i * 6]     = 1;
        buf[i * 6 + 1] = 2;
        buf[i * 6 + 2] = 3;
        buf[i * 6 + 3] = 4;
        buf[i * 6 + 4] = 5;
        buf[i * 6 + 5] = 6;
    }

    kdi_Fill_u8(buf + 24, USIZE_C(24), U8_C(0xFF));

    /* Count NOT [1,2,3,4,5,6] in range [0, 48). Last 4 blocks don't match.
     * Count = 4 × 6 = 24. */
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(48), USIZE_C(0), USIZE_C(48), blk, USIZE_C(6));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(24));

    printf("PASSED\n");
}


void
OddSizes(void)
{
    u8    buf[33];
    u8    blk[3];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "OddSizes -> ");

    /* 11 blocks of size 3 */
    kdi_Fill_u8(buf, USIZE_C(33), U8_C(0x77));
    kdi_Fill_u8(blk, USIZE_C(3), U8_C(0x77));

    /* All match, so count NOT = 0. */
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(33), USIZE_C(0), USIZE_C(33), blk, USIZE_C(3));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    /* Change blocks at offsets 6, 15 */
    kdi_Fill_u8(buf + 6, USIZE_C(3), U8_C(0x88));
    kdi_Fill_u8(buf + 15, USIZE_C(3), U8_C(0x99));

    /* Count NOT in range [0, 33). 2 blocks don't match. Count = 2 × 3 = 6. */
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(33), USIZE_C(0), USIZE_C(33), blk, USIZE_C(3));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(6));

    /* Range [9, 24). Blocks 3-7 (offsets 9, 12, 15, 18, 21).
     * Mismatch at offset 15. Count = 1 × 3 = 3. */
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(33), USIZE_C(9), USIZE_C(15), blk, USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(3));

    printf("PASSED\n");
}


void
SparseMatches(void)
{
    u8    buf[100];
    u8    blk[5];
    usize count;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "SparseMatches -> ");

    /* Pattern: [1,2,3,4,5] repeating */
    for (i = 0; i < 100; ++i)
    {
        buf[i] = (u8)((i % 5) + 1);
    }

    blk[0] = 1;
    blk[1] = 2;
    blk[2] = 3;
    blk[3] = 4;
    blk[4] = 5;

    /* All 20 blocks match, so count NOT = 0. */
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(100), USIZE_C(0), USIZE_C(100), blk, USIZE_C(5));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    /* Change every other block */
    for (i = 0; i < 100; i += 10)
    {
        buf[i] = 0xFF;
    }

    /* Now 10 blocks don't match. Count = 10 × 5 = 50. */
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(100), USIZE_C(0), USIZE_C(100), blk, USIZE_C(5));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(50));

    /* Range [30, 70). 8 blocks. Modified at offsets 30, 40, 50, 60.
     * 4 mismatches. Count = 4 × 5 = 20. */
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(100), USIZE_C(30), USIZE_C(40), blk, USIZE_C(5));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(20));

    printf("PASSED\n");
}


void
LargeBlockSize(void)
{
    u8    buf[256];
    u8    blk[32];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "LargeBlockSize -> ");

    /* 8 blocks of size 32 */
    kdi_Fill_u8(buf, USIZE_C(256), U8_C(0x55));
    kdi_Fill_u8(blk, USIZE_C(32), U8_C(0x55));

    /* All match, so count NOT = 0. */
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(256), USIZE_C(0), USIZE_C(256), blk, USIZE_C(32));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    /* Change blocks at offsets 64 and 192 */
    kdi_Fill_u8(buf + 64, USIZE_C(32), U8_C(0xAA));
    kdi_Fill_u8(buf + 192, USIZE_C(32), U8_C(0xBB));

    /* Count NOT in range [0, 256). 2 blocks don't match. Count = 2 × 32 = 64. */
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(256), USIZE_C(0), USIZE_C(256), blk, USIZE_C(32));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(64));

    /* Range [32, 128). Blocks 1-3 (offsets 32, 64, 96).
     * Mismatch at offset 64. Count = 1 × 32 = 32. */
    status = kdGenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(256), USIZE_C(32), USIZE_C(96), blk, USIZE_C(32));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(32));

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
    CountSingle();
    RangeConstraints();
    EndValueClamping();
    StartAlignment();
    U16_CountNotBlocksBound();
    U32_CountNotBlocksBound();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_CountNotBlocksBound();
#endif
    Struct_CountNotBlocksBound();
    LargeBuffer();
    AlternatingBlocks();
    ConsecutiveMatches();
    OddSizes();
    SparseMatches();
    LargeBlockSize();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}