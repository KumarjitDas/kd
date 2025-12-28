/**
 * @file kdGenMemOpsFindLastNotBlockIndex.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindLastNotBlockIndex function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>
#include <string.h>   /* For memset */

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h" /* For kdi_Fill_u8 */


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindLastNotBlockIndex function test"
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
    status = kdGenMemOpsFindLastNotBlockIndex(NULL, buf, USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base is NULL -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndex(&idx, NULL, USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is NULL -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndex(&idx, buf, USIZE_C(32), NULL, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndex(&idx, buf, USIZE_C(0), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndex(&idx, buf, USIZE_C(32), blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* base_sz not divisible by block_sz -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndex(&idx, buf, USIZE_C(31), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Valid arguments - all blocks in buf are 0xAA, search for NOT 0xBB.
     * All blocks in buf are NOT 0xBB, so the last block (index 28) should be found. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndex(&idx, buf, USIZE_C(32), blk, USIZE_C(4));
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

    /* Search for last block NOT equal to blk.
     * Since all blocks in buf match blk, this should fail.
     */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndex(&idx, buf, USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SingleMismatchLast(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleMismatchLast -> ");

    /* Fill buffer with 0xAA blocks */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xAA));
    /* Target block is 0xAA */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xAA));

    /* Change last block (Offset 28) to 0xBB */
    kdi_Fill_u8(buf + 28, USIZE_C(4), U8_C(0xBB));

    /* Search for last block NOT 0xAA. Should find 0xBB at index 28. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndex(&idx, buf, USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(28));

    printf("PASSED\n");
}


void
SingleMismatchFirst(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleMismatchFirst -> ");

    /* Fill buffer with 0xAA blocks */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xAA));
    /* Target block is 0xAA */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xAA));

    /* Change first block (Offset 0) to 0xBB */
    kdi_Fill_u8(buf, USIZE_C(4), U8_C(0xBB));

    /* Search for last block NOT 0xAA. Should find 0xBB at index 0 (as it's the only one). */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndex(&idx, buf, USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    printf("PASSED\n");
}


void
MultipleMismatches(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "MultipleMismatches -> ");

    /* Fill buffer with 0xAA blocks */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xAA));
    /* Target block is 0xAA */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xAA));

    /* Mismatches at Offset 4 (Block index 1) and Offset 20 (Block index 5) */
    kdi_Fill_u8(buf + 4, USIZE_C(4), U8_C(0xBB));
    kdi_Fill_u8(buf + 20, USIZE_C(4), U8_C(0xCC));

    /* Search for last block NOT 0xAA. Should find the one at Offset 20. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndex(&idx, buf, USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(20));

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

    /* Find Last NOT 0xAA block. Last 0x55 block is at index 28. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndex(&idx, buf, USIZE_C(32), blk_AA, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(28));

    /* Find Last NOT 0x55 block. Last 0xAA block is at index 24. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndex(&idx, buf, USIZE_C(32), blk_55, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(24));

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

    /* Set some non-matching blocks at specific points */
    kdi_Fill_u8(buf + 96, USIZE_C(16), U8_C(0xDD)); /* Mismatch at aligned offset 96 (Block index 6) */
    kdi_Fill_u8(buf + 496, USIZE_C(16), U8_C(0xEE)); /* Mismatch at aligned offset 496 (Block index 31) */
    kdi_Fill_u8(buf + 896, USIZE_C(16), U8_C(0xFF)); /* Last mismatch at aligned offset 896 (Block index 56) */

    /* Find Last NOT 0xCC block. Should find 0xFF block at index 900. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndex(&idx, buf, USIZE_C(1024), blk, USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(896));

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

    /* Find Last NOT blk (0..15).
     * The last block that does *not* match 0..15 is the one right before the end
     * if the last block happens to match 0..15.
     * The very last block starts at index 1024 - 16 = 1008.
     * Its values are 1008%256, ..., 1023%256 which is 240, 241, ..., 255.
     * This does NOT match 0..15. So the last block itself is a mismatch.
     */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndex(&idx, buf, USIZE_C(1024), blk, USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(1008)); /* Last block (offset 1008) is not 0..15 */

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

    /* Find NOT 0xDD block. Should find the 0xCC block at index 0. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndex(&idx, buf, sizeof(buf), blk, sizeof(blk));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    /* Target block is 0xCC */
    kdi_Fill_u8(blk, sizeof(blk), U8_C(0xCC));
    /* Find NOT 0xCC block. Should fail. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndex(&idx, buf, sizeof(buf), blk, sizeof(blk));
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

    /* Should find the last non-matching block at offset 12. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndex(&idx, (u8 *)buf, sizeof(buf), (u8 *)blk, sizeof(blk));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(12));

    /* Search for block {0xDDDD, 0xEEEE} */
    blk[0] = 0xDDDD;
    blk[1] = 0xEEEE;

    /* Find Last NOT {0xDDDD, 0xEEEE}.
     * The last block is {0xDDDD, 0xEEEE}.
     * The block before that, at offset 8, is {0xAAAA, 0xAAAA}. This is a mismatch.
     * So, the last mismatch found should be at index 8. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndex(&idx, (u8 *)buf, sizeof(buf), (u8 *)blk, sizeof(blk));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(8));

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

    /* All blocks are [0x77]*4 */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x77));
    /* Target block is [0x00]*4 */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0x00));

    /* Find last block NOT [0x00]*4. All blocks are [0x77]*4, so they are all mismatches.
     * Should return index 28 (the last block). */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndex(&idx, buf, USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(28));

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

    /* Find last block NOT 0xAA. Should be at index 24 (last 0xFF block). */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndex(&idx, buf, USIZE_C(30), blk, USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(24));

    /* Target block is 0xFF */
    kdi_Fill_u8(blk, USIZE_C(3), U8_C(0xFF));

    /* Find last block NOT 0xFF. Should be at index 27 (last 0xAA block). */
    idx    = 999;
    status = kdGenMemOpsFindLastNotBlockIndex(&idx, buf, USIZE_C(30), blk, USIZE_C(3));
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
    SingleMismatchLast();
    SingleMismatchFirst();
    MultipleMismatches();
    AlternatingBlocks();
    LargeBuffer();
    SingleBlockBuffer();
    U16_Buffer();
    AllSameBlockNotTarget();
    OddBlockSize();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
