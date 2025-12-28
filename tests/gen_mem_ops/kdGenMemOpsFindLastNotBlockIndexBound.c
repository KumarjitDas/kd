/**
 * @file kdGenMemOpsFindLastNotBlockIndexBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindLastNotBlockIndexBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>
#include <string.h>   /* For memset */

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h" /* For kdi_Fill_u8, kdi_FillSeq_u8 */


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindLastNotBlockIndexBound function test"
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
    kdi_Fill_u8(blk, sizeof(blk), U8_C(0xBB)); /* Target is 0xBB block, different from buf */

    /* idx pointer is NULL -> failure */
    status = kdGenMemOpsFindLastNotBlockIndexBound(NULL, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base is NULL -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, NULL, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is NULL -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), NULL, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* begin_idx >= base_sz -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(32), USIZE_C(4), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* end_count_byte is zero -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(0), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* base_sz not divisible by block_sz -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(31), USIZE_C(0), USIZE_C(31), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* begin_idx not aligned to block_sz -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(3), USIZE_C(29), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Valid arguments - all blocks in buf are 0xAA, search for NOT 0xBB.
     * All blocks in buf are NOT 0xBB, so the last block (index 28) should be found. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(28)); /* Last block is at index 28 (32 - 4) */

    printf("PASSED\n");
}


void
AllMatchTarget(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "AllMatchTarget -> ");

    /* Fill buffer with 0xAA blocks */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xAA));
    /* Target block is also 0xAA */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xAA));

    /* Range [0, 32). Search for last block NOT equal to blk.
     * Since all blocks in buf match blk, this should fail.
     */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SingleMismatchLastInBound(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleMismatchLastInBound -> ");

    /* Fill buffer with 0xAA blocks */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xAA));
    /* Target block is 0xAA */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xAA));

    /* Set last block in range [0, 32) to 0xBB */
    kdi_Fill_u8(buf + 28, USIZE_C(4), U8_C(0xBB));

    /* Search for last block NOT 0xAA in range [0, 32). Should find 0xBB at index 28. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(28));

    printf("PASSED\n");
}


void
SingleMismatchFirstInBound(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleMismatchFirstInBound -> ");

    /* Fill buffer with 0xAA blocks */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xAA));
    /* Target block is 0xAA */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xAA));

    /* Set first block in range [0, 32) to 0xBB */
    kdi_Fill_u8(buf, USIZE_C(4), U8_C(0xBB));

    /* Search for last block NOT 0xAA in range [0, 32). Should find 0xBB at index 0. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    printf("PASSED\n");
}


void
MultipleMismatchesInBound(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "MultipleMismatchesInBound -> ");

    /* Fill buffer with 0xAA blocks */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xAA));
    /* Target block is 0xAA */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xAA));

    /* Mismatches at Offset 4 (Block index 1) and Offset 20 (Block index 5) */
    kdi_Fill_u8(buf + 4, USIZE_C(4), U8_C(0xBB));
    kdi_Fill_u8(buf + 20, USIZE_C(4), U8_C(0xCC));

    /* Search for last block NOT 0xAA in range [0, 32). Should find the one at Offset 20. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(20));

    /* Search for last NOT 0xAA in range [0, 16). Excludes 20. Should find 4. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(4));

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
    /* Init buffer to all 0xAA blocks */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xAA));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xAA)); /* Target block is 0xAA */

    /* Set some non-matching blocks.
     * Blocks at offsets 4, 12, 20 are 0xBB.
     */
    kdi_Fill_u8(buf + 4, USIZE_C(4), U8_C(0xBB));
    kdi_Fill_u8(buf + 12, USIZE_C(4), U8_C(0xBB));
    kdi_Fill_u8(buf + 20, USIZE_C(4), U8_C(0xBB));

    /* Range [0, 32). Search for NOT 0xAA.
     * Non-matching blocks at 4, 12, 20. Last is at 20.
     */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(20));

    /* Range [0, 20). Excludes 20. Non-matching blocks at 4, 12. Last is at 12. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(20), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(12));

    /* Range [8, 24). Begin_idx=8, end_count_byte=16. Blocks considered: 8, 12, 16, 20.
     * Block at 8 is 0xAA (matches target).
     * Block at 12 is 0xBB (mismatch).
     * Block at 16 is 0xAA (matches target).
     * Block at 20 is 0xBB (mismatch).
     * Last mismatch in this range is at offset 20.
     */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(8), USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(20));

    /* Create a range where all blocks match the target to test failure. */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xCC)); /* All 0xCC */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xCC));  /* Target is 0xCC */
    /* Range [4, 12). Blocks at 4, 8. All 0xCC. Search for NOT 0xCC. Should fail. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(4), USIZE_C(8), blk, USIZE_C(4));
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

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xAA));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xAA)); /* Target block is 0xAA */

    /* Mismatch at last possible block (Offset 28) */
    kdi_Fill_u8(buf + 28, USIZE_C(4), U8_C(0xBB));

    /* Requesting 100 bytes starting at 0. Clamps end to 32. Range [0, 32).
     * Search for NOT 0xAA. Should find 0xBB block at index 28.
     */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(100), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(28));

    /* Add another mismatch before last one */
    kdi_Fill_u8(buf + 24, USIZE_C(4), U8_C(0xCC)); /* Mismatch at offset 24 */

    /* Requesting 27 bytes starting at 0. Internally, end_count_byte will be
     * aligned to (27 - (27 % 4)) = 24 bytes. The search range will be [0, 24).
     * Since the only mismatch (0xCC) is at index 24, it should not be found.
     */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(27), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(idx == USIZE_C(999)); /* idx should not be modified on failure */

    /* Test end_count_byte alignment. */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xAA)); /* Reset buffer */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xAA)); /* Target block is 0xAA */
    kdi_Fill_u8(buf + 24, USIZE_C(4), U8_C(0xBB)); /* Mismatch at offset 24 */

    /* Requesting 27 bytes starting at 0. Internally, end_count_byte will be
     * aligned to (27 - (27 % 4)) = 24 bytes. The search range will be [0, 24).
     * Since the only mismatch (0xBB) is at index 24, it should not be found.
     */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(27), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(idx == USIZE_C(999)); /* idx should not be modified on failure */

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

    /* Find Last NOT 0xAA block in range [0, 32). Last 0x55 block is at index 28. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk_AA, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(28));

    /* Find Last NOT 0x55 block in range [0, 32). Last 0xAA block is at index 24. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk_55, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(24));

    /* Find Last NOT 0xAA block in range [8, 21). Begin_idx=8, end_count_byte=13.
     * Internally, end_count_byte will be aligned to (13 - (13 % 4)) = 12 bytes.
     * The search range will be [8, 8 + 12), which is [8, 20).
     * Blocks in range [8, 20): 8 (AA), 12 (55), 16 (AA).
     * Last NOT 0xAA is 0x55 at index 12. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(8), USIZE_C(13), blk_AA, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(12));

    /* Test end_count_byte alignment behavior causing no match. */
    /* Find Last NOT 0xAA block in range [0, 7). Begin_idx=0, end_count_byte=7.
     * Unaligned: Range [0, 7) includes block at index 4 (0x55). Expected: SUCCESS, idx=4.
     * Internally, end_count_byte will be aligned to (7 - (7 % 4)) = 4 bytes.
     * The search range will be [0, 4).
     * Blocks in range [0, 4): 0 (AA). No NOT 0xAA block found. Expected: FAILURE, idx=999.
     */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(7), blk_AA, USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(idx == USIZE_C(999)); /* idx should not be modified on failure */

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

    /* Set some non-matching blocks at specific aligned points */
    kdi_Fill_u8(buf + (USIZE_C(16) * 6), USIZE_C(16), U8_C(0xDD));  /* Mismatch at offset 96 (block index 6) */
    kdi_Fill_u8(buf + (USIZE_C(16) * 31), USIZE_C(16), U8_C(0xEE)); /* Mismatch at offset 496 (block index 31) */
    kdi_Fill_u8(buf + (USIZE_C(16) * 56), USIZE_C(16), U8_C(0xFF)); /* Last mismatch at offset 896 (block index 56) */

    /* Find Last NOT 0xCC block in range [0, 1024). Should find 0xFF block at index 896. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(1024), USIZE_C(0), USIZE_C(1024), blk, USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(896));

    /* Find Last NOT 0xCC block in range [0, 520).
     * Non-matching blocks for 0xCC are at 96, 496, 896.
     * In effective range [0, 496), the last non-matching block is at offset 496. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(1024), USIZE_C(0), USIZE_C(520), blk, USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(496));

    /* Now, fill with sequential values (0..255 repeating) */
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

    /* Find Last NOT blk (0..15) in range [0, 1024).
     * The last block that does NOT match 0..15 starts at offset 1008.
     * Its values are 1008%256, ..., 1023%256 which is 240, 241, ..., 255.
     * This does NOT match 0..15. So the last block itself is a mismatch.
     */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(1024), USIZE_C(0), USIZE_C(1024), blk, USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(1008)); /* Last block (offset 1008) is not 0..15 */

    /* Find Last NOT blk (0..15) in range [0, 790). Excludes 1008.
     * The blocks that match 0..15 are at 0, 256, 512, 768.
     * Blocks that don't match are everything else.
     * The last block in range [0, 790) is at offset 768.
     * The block at 768 is a match. So we need to look earlier.
     * The block at 768-16 = 752 is (752%256)... This is a mismatch.
     * The block at 752 is actually the last one NOT 0..15 (if we ignore 768 for a moment).
     * Corrected thinking:
     * The last candidate block in range [0, 790) is at index 768.
     * This block (at 768) matches `blk` (0..15).
     * So, we skip 768.
     * The next candidate block backwards is at 768 - 16 = 752.
     * This block (at 752) is (752%256 ...). This is NOT 0..15. So, match at 752.
     */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(1024), USIZE_C(0), USIZE_C(790), blk, USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(752));

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
    /* Target block is 0xDD */
    kdi_Fill_u8(blk, sizeof(blk), U8_C(0xDD));

    /* Find NOT 0xDD block in range [0, 8). Should find the 0xCC block at index 0. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, sizeof(buf), USIZE_C(0), sizeof(buf), blk, sizeof(blk));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    /* Target block is 0xCC */
    kdi_Fill_u8(blk, sizeof(blk), U8_C(0xCC));
    /* Find NOT 0xCC block in range [0, 8). Should fail. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, sizeof(buf), USIZE_C(0), sizeof(buf), blk, sizeof(blk));
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

    /* Init buf with 0xAAAA (blocks of {0xAA,0xAA} in u8 terms) */
    memset(buf, 0xAA, sizeof(buf)); /* This fills u16 with 0xAAAA */

    /* Set some non-matching blocks. Block size for comparison is 2 * sizeof(u16) = 4 bytes */
    /* Block at offset 4 (buf[2], buf[3]) becomes {0xBBBB, 0xCCCC} */
    buf[2] = 0xBBBB;
    buf[3] = 0xCCCC;
    /* Block at offset 12 (buf[6], buf[7]) becomes {0xDDDD, 0xEEEE} */
    buf[6] = 0xDDDD;
    buf[7] = 0xEEEE;

    /* Search for block {0xAAAA, 0xAAAA} (which is all 0xAA in u8 terms) */
    blk[0] = 0xAAAA;
    blk[1] = 0xAAAA;

    /* Find Last NOT {0xAAAA, 0xAAAA} in range [0, 16). end_count_byte 16 is aligned. Effective range [0, 16).
     * Non-matching blocks at 4, 12.
     * In effective range [0, 16), the last non-matching block is at offset 12. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, (u8 *)buf, sizeof(buf), USIZE_C(0), USIZE_C(16), (u8 *)blk, sizeof(blk));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(12));

    /* Find Last NOT {0xAAAA, 0xAAAA} in range [0, 12). end_count_byte 12 is aligned. Effective range [0, 12).
     * Non-matching blocks at 4, 12.
     * In effective range [0, 12), the last non-matching block is at offset 4. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, (u8 *)buf, sizeof(buf), USIZE_C(0), USIZE_C(12), (u8 *)blk, sizeof(blk));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(4));

    /* Search for block {0xBBBB, 0xCCCC} */
    blk[0] = 0xBBBB;
    blk[1] = 0xCCCC;

    /* Find Last NOT {0xBBBB, 0xCCCC} in range [0, 16). Last non-matching block is {0xDDDD, 0xEEEE} at offset 12. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, (u8 *)buf, sizeof(buf), USIZE_C(0), USIZE_C(16), (u8 *)blk, sizeof(blk));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(12));

    printf("PASSED\n");
}


void
AllSameBlockNotTarget(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "AllSameBlockNotTarget -> ");

    /* All blocks in buf are [0x77]*4 */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x77));
    /* Target block is [0x00]*4 */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0x00));

    /* Find last block NOT [0x00]*4 in range [0, 32). All blocks are [0x77]*4, so they are all mismatches.
     * Should return index 28 (the last block). */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(28));

    /* Find last block NOT [0x00]*4 in range [0, 20). end_count_byte 20 is aligned. Effective range [0, 20).
     * All blocks are [0x77]*4. All are non-matching.
     * In effective range [0, 20), the last block is at offset 16. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(20), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(16));

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

    /* Target block is 0xAA */
    kdi_Fill_u8(blk, USIZE_C(3), U8_C(0xAA));

    /* Find last block NOT 0xAA in range [0, 30). Should be at index 24 (last 0xFF block). */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(30), USIZE_C(0), USIZE_C(30), blk, USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(24));

    /* Find last 0xFF block in range [0, 20). end_count_byte 20 truncates to 18. Effective range [0, 18).
     * Matches for 0xFF are at 9, 24.
     * In effective range [0, 18), the last match is at index 9. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(30), USIZE_C(0), USIZE_C(20), blk, USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(9));

    /* Target block is 0xFF */
    kdi_Fill_u8(blk, USIZE_C(3), U8_C(0xFF));

    /* Find last block NOT 0xFF in range [0, 30). Should be at index 27 (last 0xAA block). */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndexBound(&idx, buf, USIZE_C(30), USIZE_C(0), USIZE_C(30), blk, USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(27));

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    AllMatchTarget();
    SingleMismatchLastInBound();
    SingleMismatchFirstInBound();
    MultipleMismatchesInBound();
    RangeConstraints();
    EndValueClamping();
    AlternatingBlocks();
    LargeBuffer();
    SingleBlockBuffer();
    U16_Buffer();
    AllSameBlockNotTarget();
    OddBlockSize();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
