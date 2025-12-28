/**
 * @file kdGenMemOpsFindLastBlockIndex.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindLastBlockIndex function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindLastBlockIndex function test"
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

    /* idx pointer is null -> failure */
    status = kdGenMemOpsFindLastBlockIndex(null, buf, USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndex(&idx, null, USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndex(&idx, buf, USIZE_C(32), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndex(&idx, buf, USIZE_C(0), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndex(&idx, buf, USIZE_C(32), blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* base_sz not divisible by block_sz -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndex(&idx, buf, USIZE_C(31), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Valid arguments - target found at last possible index */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndex(&idx, buf, USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(28));

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

    /* Search for [0xFF, 0xFF, 0xFF, 0xFF] (not present) */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xFF));

    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndex(&idx, buf, USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
FindFirst(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindFirst -> ");

    /* Init: 0x00 */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));

    /* Set first block to [0xFF, 0xFF, 0xFF, 0xFF] */
    kdi_Fill_u8(buf, USIZE_C(4), U8_C(0xFF));

    /* Search for [0xFF, 0xFF, 0xFF, 0xFF] */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xFF));

    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndex(&idx, buf, USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    printf("PASSED\n");
}


void
FindLast(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindLast -> ");

    /* Init: 0x00 */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));

    /* Set last block to [0xFF, 0xFF, 0xFF, 0xFF] */
    kdi_Fill_u8(buf + 28, USIZE_C(4), U8_C(0xFF));

    /* Search for [0xFF, 0xFF, 0xFF, 0xFF] */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xFF));

    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndex(&idx, buf, USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(28));

    printf("PASSED\n");
}


void
FindMultiple(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindMultiple -> ");

    /* Init: 0x00 */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));

    /* Set 0xFF blocks at indices 4, 12, 20 */
    kdi_Fill_u8(buf + 4, USIZE_C(4), U8_C(0xFF));
    kdi_Fill_u8(buf + 12, USIZE_C(4), U8_C(0xFF));
    kdi_Fill_u8(buf + 20, USIZE_C(4), U8_C(0xFF));

    /* Target block */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xFF));

    /* Find Last 0xFF block. Should return index 20. */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndex(&idx, buf, USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(20));

    printf("PASSED\n");
}


void
UnalignedMatchFail(void)
{
    u8    buf[4];
    u8    blk[2];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "UnalignedMatchFail -> ");

    /* Buffer: 0x01, 0x02, 0x03, 0x04 */
    buf[0] = 1;
    buf[1] = 2;
    buf[2] = 3;
    buf[3] = 4;

    /* Block Size: 2 */
    /* Block 0: [1, 2] */
    /* Block 1: [3, 4] */

    /* Search for: 2, 3 */
    /* Sequence exists at offset 1, but it crosses block boundaries. */
    blk[0] = 2;
    blk[1] = 3;

    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndex(&idx, buf, USIZE_C(4), blk, USIZE_C(2));

    /* Should fail because it is not a discrete block */
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
        {
            kdi_Fill_u8(buf + i, USIZE_C(4), U8_C(0xAA));
        }
        else
        {
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

    /* Find Last 0xAA block. Should return index 24. */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndex(&idx, buf, USIZE_C(32), blk_AA, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(24));

    /* Find Last 0x55 block. Should return index 28. */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndex(&idx, buf, USIZE_C(32), blk_55, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(28));

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    u8    buf[1024];
    u8    blk[16];
    usize idx;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    /* Init with pattern 0..255 repeating */
    for (i = 0; i < 1024; ++i)
    {
        buf[i] = (u8)(i % 256);
    }

    /* Create target pattern `blk` for value at offset 512 in `buf` */
    for (i = 0; i < 16; ++i)
    {
        blk[i] = (u8)((512 + i) % 256);
    }

    /* Place another instance of the block pattern further down at offset 768 */

    for (i = 0; i < 16; ++i)
    {
        buf[768 + i] = (u8)((512 + i) % 256);
    }

    /* Find Last occurrence of `blk`. Should find the one at 768. */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndex(&idx, buf, USIZE_C(1024), blk, USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(768));

    /* Create a non-existent block pattern */
    kdi_Fill_u8(blk, USIZE_C(16), U8_C(0xFF));
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndex(&idx, buf, USIZE_C(1024), blk, USIZE_C(16));
    assert(status == RESULT_FAILURE);

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

    /* Buffer is a single block */
    kdi_Fill_u8(buf, sizeof(buf), U8_C(0xCC));
    kdi_Fill_u8(blk, sizeof(blk), U8_C(0xCC));

    /* Find the block */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndex(&idx, buf, sizeof(buf), blk, sizeof(blk));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    /* Find a different block */
    kdi_Fill_u8(blk, sizeof(blk), U8_C(0xDD));
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndex(&idx, buf, sizeof(buf), blk, sizeof(blk));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
U16_Buffer(void)
{
    u16   buf[8];
    u16   blk[2];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U16_Buffer -> ");

    /* Init buf with 0x0000 */
    memset(buf, 0x00, sizeof(buf));

    /* Set some blocks. Block size for comparison is 2 * sizeof(u16) = 4 bytes */

    buf[2] = 0xAAAA;
    buf[3] = 0xBBBB;

    buf[6] = 0xAAAA;
    buf[7] = 0xBBBB;

    /* Search for block {0xAAAA, 0xBBBB} */
    blk[0] = 0xAAAA;
    blk[1] = 0xBBBB;

    /* Should find the last one at offset 12 */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndex(&idx, (u8 *)buf, sizeof(buf), (u8 *)blk, sizeof(blk));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(12));

    /* Search for non-existent block */
    blk[0] = 0x1111;
    blk[1] = 0x2222;
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndex(&idx, (u8 *)buf, sizeof(buf), (u8 *)blk, sizeof(blk));
    assert(status == RESULT_FAILURE);

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
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0x77));

    /* Find last 0x77 block. Should be at index 28. */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndex(&idx, buf, USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(28));

    /* Search for 0x00 block (not present) */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0x00));
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndex(&idx, buf, USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
OddBlockSize(void)
{
    u8    buf[30];
    u8    blk[3];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "OddBlockSize -> ");

    /* Init 0x00 */
    kdi_Fill_u8(buf, USIZE_C(30), U8_C(0x00));

    /* Set 0xFF block at 9 (block 3) and 24 (block 8) */
    kdi_Fill_u8(buf + 9, USIZE_C(3), U8_C(0xFF));
    kdi_Fill_u8(buf + 24, USIZE_C(3), U8_C(0xFF));

    /* Search for 0xFF block */
    kdi_Fill_u8(blk, USIZE_C(3), U8_C(0xFF));

    /* Find last 0xFF block. Should be at index 24. */
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndex(&idx, buf, USIZE_C(30), blk, USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(24));

    /* Find 0x00 block. Should be at index 27. */
    kdi_Fill_u8(blk, USIZE_C(3), U8_C(0x00));
    idx    = 999;
    status = kdGenMemOpsFindLastBlockIndex(&idx, buf, USIZE_C(30), blk, USIZE_C(3));
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
    FindNone();
    FindFirst();
    FindLast();
    FindMultiple();
    UnalignedMatchFail();
    AlternatingBlocks();
    LargeBuffer();
    SingleBlockBuffer();
    U16_Buffer();
    AllSameBlock();
    OddBlockSize();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
