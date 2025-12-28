/**
 * @file kdGenMemOpsFindLastBlockIndexBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindLastBlockIndexBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>
#include <string.h>   /* For memset */

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h" /* For kdi_Fill_u8, kdi_FillSeq_u8 */


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindLastBlockIndexBound function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx = 999;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_Fill_u8(buf, sizeof(buf), U8_C(0xAA));
    kdi_Fill_u8(blk, sizeof(blk), U8_C(0xAA));

    /* idx pointer is NULL -> failure */
    status = kdGenMemOpsFindLastBlockIndexBound(NULL, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base is NULL -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, NULL, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is NULL -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), NULL, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* begin_idx >= base_sz -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(32), USIZE_C(4), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* end_count_byte is zero -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(0), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* base_sz not divisible by block_sz -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(31), USIZE_C(0), USIZE_C(31), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* begin_idx not aligned to block_sz -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(3), USIZE_C(29), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Valid arguments - target found at last possible index within bounds */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(28)); /* Last block is at index 28 (32 - 4) */

    printf("PASSED\n");
}


void
FindNone(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNone -> ");

    /* Init: all blocks are [0x00, 0x00, 0x00, 0x00] */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));

    /* Search for [0xFF, 0xFF, 0xFF, 0xFF] in range [0, 32) - not present */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xFF));

    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
FindFirstInBound(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindFirstInBound -> ");

    /* Init: 0x00 */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));

    /* Set first block in range [0, 4) to 0xFF */
    kdi_Fill_u8(buf, USIZE_C(4), U8_C(0xFF));

    /* Search for 0xFF block */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xFF));

    /* Range [0, 4). Only one block, so it's the last. */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(4), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    printf("PASSED\n");
}


void
FindLastInBound(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindLastInBound -> ");

    /* Init: 0x00 */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));

    /* Set last block in range [0, 32) to 0xFF */
    kdi_Fill_u8(buf + 28, USIZE_C(4), U8_C(0xFF));

    /* Search for 0xFF block */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xFF));

    /* Range [0, 32). Should find the block at index 28. */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(28));

    printf("PASSED\n");
}


void
FindMultipleInBound(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindMultipleInBound -> ");

    /* Init: 0x00 */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));

    /* Set 0xFF blocks at offsets 4, 12, 20 */
    kdi_Fill_u8(buf + 4, USIZE_C(4), U8_C(0xFF));
    kdi_Fill_u8(buf + 12, USIZE_C(4), U8_C(0xFF));
    kdi_Fill_u8(buf + 20, USIZE_C(4), U8_C(0xFF));

    /* Target block */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xFF));

    /* Range [0, 32). Should find last one at 20. */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(20));

    /* Range [0, 20). Excludes 20. Includes 4, 12. Should find 12. */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(20), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(12));

    /* Range [0, 8). Includes 4. Excludes 12, 20. Should find 4. */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(8), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(4));

    /* Range [8, 24). Includes 8, 12, 16, 20. Should find 20. */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(8), USIZE_C(16), blk, USIZE_C(4)); /* Range [8, 24) */
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(20));

    printf("PASSED\n");
}


void
RangeConstraints(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "RangeConstraints -> ");

    /* Block Size: 4 */
    /* Blocks at indices: 0, 4, 8, 12, 16, 20, 24, 28 */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));

    /* Set distinct values for blocks */
    kdi_Fill_u8(buf + 0, USIZE_C(4), U8_C(0xAA));  /* Block 0 */
    kdi_Fill_u8(buf + 4, USIZE_C(4), U8_C(0xBB));  /* Block 1 */
    kdi_Fill_u8(buf + 8, USIZE_C(4), U8_C(0xCC));  /* Block 2 */
    kdi_Fill_u8(buf + 12, USIZE_C(4), U8_C(0xDD)); /* Block 3 */
    kdi_Fill_u8(buf + 16, USIZE_C(4), U8_C(0xAA)); /* Block 4 */
    kdi_Fill_u8(buf + 20, USIZE_C(4), U8_C(0xBB)); /* Block 5 */
    kdi_Fill_u8(buf + 24, USIZE_C(4), U8_C(0xCC)); /* Block 6 */
    kdi_Fill_u8(buf + 28, USIZE_C(4), U8_C(0xDD)); /* Block 7 */

    /* Range [4, 24). Begin_idx=4, end_count_byte=20. Includes blocks at 4, 8, 12, 16, 20.
     * Values: BB, CC, DD, AA, BB
     * Find 0xBB block. Last is at index 20. */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xBB));
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(4), USIZE_C(20), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(20));

    /* Range [0, 12). Begin_idx=0, end_count_byte=12. Includes blocks at 0, 4, 8.
     * Values: AA, BB, CC
     * Find 0xAA block. Last is at index 0. */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xAA));
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(12), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    /* Range [16, 28). Begin_idx=16, end_count_byte=12. Includes blocks at 16, 20, 24.
     * Values: AA, BB, CC
     * Find 0xDD block (not in range) -> Fail */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xDD));
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(16), USIZE_C(12), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
EndValueClamping(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "EndValueClamping -> ");

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xFF));

    /* Set last block in buffer to 0xFF */
    kdi_Fill_u8(buf + 28, USIZE_C(4), U8_C(0xFF));

    /* Requesting 100 bytes starting at 0. Clamps end to 32. Range [0, 32). */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(100), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(28));

    printf("PASSED\n");
}


void
UnalignedBeginIndex(void)
{
    u8    buf[16];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "UnalignedBeginIndex -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xAA));

    /* begin_idx (1) is not aligned to block_sz (4) -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(16), USIZE_C(1), USIZE_C(15), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* begin_idx (2) is not aligned to block_sz (4) -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(16), USIZE_C(2), USIZE_C(14), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
AlternatingBlocks(void)
{
    u8    buf[32];
    u8    blk_AA[4];
    u8    blk_55[4];
    usize idx;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "AlternatingBlocks -> ");

    /* Alternating 0xAA (block A) and 0x55 (block B) */
    /* Block size 4. */
    for (i = 0; i < 32; i += 4)
    {
        if ((i / 4) % 2 == 0)
        { /* Even block index */
            kdi_Fill_u8(buf + i, USIZE_C(4), U8_C(0xAA));
        }
        else
        { /* Odd block index */
            kdi_Fill_u8(buf + i, USIZE_C(4), U8_C(0x55));
        }
    }
    /* Blocks:
     * 0-3:   AA AA AA AA
     * 4-7:   55 55 55 55
     * 8-11:  AA AA AA AA
     * 12-15: 55 55 55 55
     * 16-19: AA AA AA AA
     * 20-23: 55 55 55 55
     * 24-27: AA AA AA AA
     * 28-31: 55 55 55 55
     */

    kdi_Fill_u8(blk_AA, USIZE_C(4), U8_C(0xAA));
    kdi_Fill_u8(blk_55, USIZE_C(4), U8_C(0x55));

    /* Find Last 0xAA block in range [0, 32). Last 0xAA block is at index 24. */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk_AA, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(24));

    /* Find Last 0x55 block in range [0, 32). Last 0x55 block is at index 28. */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk_55, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(28));

    /* Find Last 0xAA block in range [10, 20). Begin_idx=8, end_count_byte=16 -> Range [8, 24).
     * Blocks 8, 12, 16, 20. Pattern: AA, 55, AA, 55. Last 0xAA is at index 16. */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(8), USIZE_C(16), blk_AA, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(16));

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    static u8 buf[1024]; /* Static to avoid stack overflow for large array */
    u8        blk[16];
    usize     idx;
    bool      status;
    usize     i;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    /* Init buffer with target pattern (0xCC blocks) */
    kdi_Fill_u8(buf, USIZE_C(1024), U8_C(0xCC));
    /* Target block is 0xCC */
    kdi_Fill_u8(blk, USIZE_C(16), U8_C(0xCC));

    /* Set some matching blocks at specific aligned points */
    kdi_Fill_u8(buf + (USIZE_C(16) * 6), USIZE_C(16), U8_C(0xFF));  /* Match at offset 96 (block index 6) */
    kdi_Fill_u8(buf + (USIZE_C(16) * 31), USIZE_C(16), U8_C(0xFF)); /* Match at offset 496 (block index 31) */
    kdi_Fill_u8(buf + (USIZE_C(16) * 56), USIZE_C(16), U8_C(0xFF)); /* Last match at offset 896 (block index 56) */

    /* Search for 0xFF block in range [0, 1024). Should find 0xFF block at index 896. */
    kdi_Fill_u8(blk, USIZE_C(16), U8_C(0xFF)); /* Now blk is 0xFF */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(1024), USIZE_C(0), USIZE_C(1024), blk, USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(896));

    /* Search for 0xFF block in range [0, 500). end_count_byte 500 truncates to 496. Effective range [0, 496).\n     * Matches for 0xFF are at 96, 496, 896.\n     * In effective range [0, 496), the last match is at offset 96. */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(1024), USIZE_C(0), USIZE_C(500), blk, USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(96));

    /* Now, fill with sequential values and test */
    for (i = 0; i < 1024; ++i)
    {
        buf[i] = (u8)(i % 256);
    }
    /* Pattern: 0, 1, ..., 255, 0, 1, ... */

    /* Create a target block that matches `buf` at offset 0 (0..15) */
    for (i = 0; i < 16; ++i)
    {
        blk[i] = (u8)((0 + i) % 256); /* This is 0, 1, ..., 15 */
    }

    /* Find Last matching block (0..15).
     * Occurrences are at offsets 0, 256, 512, 768.
     * Last match in range [0, 1024) should be at offset 768.
     */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(1024), USIZE_C(0), USIZE_C(1024), blk, USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(768));

    /* Find Last matching block (0..15) in range [0, 800). end_count_byte 800 is aligned. Effective range [0, 800).\n     * Occurrences are at offsets 0, 256, 512, 768.\n     * The last match in this effective range is at offset 768. */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(1024), USIZE_C(0), USIZE_C(800), blk, USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(768));

    printf("PASSED\n");
}


void
SingleBlockBuffer(void)
{
    u8    buf[8];
    u8    blk[8];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleBlockBuffer -> ");

    /* Buffer is a single block of 0xCC */
    kdi_Fill_u8(buf, sizeof(buf), U8_C(0xCC));
    /* Target block is 0xCC */
    kdi_Fill_u8(blk, sizeof(blk), U8_C(0xCC));

    /* Find 0xCC block in range [0, 8). Should find at index 0. */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, sizeof(buf), USIZE_C(0), sizeof(buf), blk, sizeof(blk));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    /* Target block is 0xDD */
    kdi_Fill_u8(blk, sizeof(blk), U8_C(0xDD));
    /* Find 0xDD block in range [0, 8). Should fail. */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, sizeof(buf), USIZE_C(0), sizeof(buf), blk, sizeof(blk));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
U16_Buffer(void)
{
    u16   buf[8]; /* 16 bytes total */
    u16   blk[2]; /* 4 bytes for search block */
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U16_Buffer -> ");

    /* Init buf with 0x0000 */
    memset(buf, 0x00, sizeof(buf)); /* This fills u16 with 0x0000 */

    /* Set some blocks. Block size for comparison is 2 * sizeof(u16) = 4 bytes */
    /* Blocks are at offsets 0, 4, 8, 12 */

    /* Block at offset 4 (buf[2], buf[3]) becomes {0xAAAA, 0xBBBB} */
    buf[2] = 0xAAAA;
    buf[3] = 0xBBBB;
    /* Block at offset 12 (buf[6], buf[7]) becomes {0xAAAA, 0xBBBB} */
    buf[6] = 0xAAAA;
    buf[7] = 0xBBBB;

    /* Search for block {0xAAAA, 0xBBBB} */
    blk[0] = 0xAAAA;
    blk[1] = 0xBBBB;

    /* Find Last block {0xAAAA, 0xBBBB} in range [0, 16). Should find at offset 12. */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, (u8 *)buf, sizeof(buf), USIZE_C(0), USIZE_C(16), (u8 *)blk, sizeof(blk));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(12));

    /* Find Last block {0xAAAA, 0xBBBB} in range [0, 12). Excludes 12. Should find at offset 4. */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, (u8 *)buf, sizeof(buf), USIZE_C(0), USIZE_C(12), (u8 *)blk, sizeof(blk));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(4));

    /* Find Last block {0xAAAA, 0xBBBB} in range [8, 16). Includes 12. Should find at offset 12. */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, (u8 *)buf, sizeof(buf), USIZE_C(8), USIZE_C(8), (u8 *)blk, sizeof(blk)); /* Range [8, 16) */
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(12));

    printf("PASSED\n");
}


void
AllSameBlock(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "AllSameBlock -> ");

    /* All blocks are [0x77]*4 */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x77));
    /* Target block is [0x77]*4 */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0x77));

    /* Find last 0x77 block in range [0, 32). Should be at index 28. */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(28));

    /* Find last 0x77 block in range [0, 20). Excludes 20, 24, 28. Should be at index 16. */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(20), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(16));

    /* Search for 0x00 block (not present in range) */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0x00));
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
OddBlockSize(void)
{
    u8    buf[30]; /* 10 blocks of 3 bytes */
    u8    blk[3];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "OddBlockSize -> ");

    /* Init buf with 0xAA */
    kdi_Fill_u8(buf, USIZE_C(30), U8_C(0xAA));

    /* Set 0xFF block at 9 (block 3) and 24 (block 8) */
    kdi_Fill_u8(buf + 9, USIZE_C(3), U8_C(0xFF));
    kdi_Fill_u8(buf + 24, USIZE_C(3), U8_C(0xFF));

    /* Target block is 0xFF */
    kdi_Fill_u8(blk, USIZE_C(3), U8_C(0xFF));

    /* Find last 0xFF block in range [0, 30). Should be at index 24. */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(30), USIZE_C(0), USIZE_C(30), blk, USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(24));

    /* Find last 0xFF block in range [0, 20). end_count_byte 20 truncates to 18. Effective range [0, 18).\n     * Matches for 0xFF are at 9, 24.\n     * In effective range [0, 18), the last match is at index 9. */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(30), USIZE_C(0), USIZE_C(20), blk, USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(9));

    /* Find last 0xFF block in range [10, 30). Begin_idx=9 -> not aligned. Will fail.
     * However, if begin_idx is 12 (aligned), then range [12, 30).
     * Only 0xFF block at 24 is in range. */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndexBound(&idx, buf, USIZE_C(30), USIZE_C(12), USIZE_C(18), blk, USIZE_C(3)); /* Range [12, 30) */
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(24));

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    FindNone();
    FindFirstInBound();
    FindLastInBound();
    FindMultipleInBound();
    RangeConstraints();
    EndValueClamping();
    UnalignedBeginIndex();
    AlternatingBlocks();
    LargeBuffer();
    SingleBlockBuffer();
    U16_Buffer();
    AllSameBlock();
    OddBlockSize();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
