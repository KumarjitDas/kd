/**
 * @file kdGenMemOpsSwapBlocksBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsSwapBlocksBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsSwapBlocksBound function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
Base1Null(void)
{
    u8   buf2[8];
    bool status;

    printf(LOG_PREFIX_CSTR "Base1Null -> ");

    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x00));

    /* base_1 is null -> failure */
    status = GenMemOpsSwapBlocksBound(null, USIZE_C(8), USIZE_C(0), buf2, USIZE_C(8), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Verify buf2 unchanged */
    assert(buf2[0] == U8_C(0x00));

    printf("PASSED\n");
}


void
Base2Null(void)
{
    u8   buf1[8];
    bool status;

    printf(LOG_PREFIX_CSTR "Base2Null -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x00));

    /* base_2 is null -> failure */
    status = GenMemOpsSwapBlocksBound(buf1, USIZE_C(8), USIZE_C(0), null, USIZE_C(8), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Verify buf1 unchanged */
    assert(buf1[0] == U8_C(0x00));

    printf("PASSED\n");
}


void
BothBasesNull(void)
{
    bool status;

    printf(LOG_PREFIX_CSTR "BothBasesNull -> ");

    /* Both bases null -> failure */
    status = GenMemOpsSwapBlocksBound(null, USIZE_C(8), USIZE_C(0), null, USIZE_C(8), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
Base1SizeZero(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool status;

    printf(LOG_PREFIX_CSTR "Base1SizeZero -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x10));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x20));

    /* base_1_sz is zero -> failure */
    status = GenMemOpsSwapBlocksBound(buf1, USIZE_C(0), USIZE_C(0), buf2, USIZE_C(8), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Verify buffers unchanged */
    assert(buf1[0] == U8_C(0x10));
    assert(buf2[0] == U8_C(0x20));

    printf("PASSED\n");
}


void
Base2SizeZero(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool status;

    printf(LOG_PREFIX_CSTR "Base2SizeZero -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x10));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x20));

    /* base_2_sz is zero -> failure */
    status = GenMemOpsSwapBlocksBound(buf1, USIZE_C(8), USIZE_C(0), buf2, USIZE_C(0), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Verify buffers unchanged */
    assert(buf1[0] == U8_C(0x10));
    assert(buf2[0] == U8_C(0x20));

    printf("PASSED\n");
}


void
BothSizesZero(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool status;

    printf(LOG_PREFIX_CSTR "BothSizesZero -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x10));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x20));

    /* Both sizes zero -> failure */
    status = GenMemOpsSwapBlocksBound(buf1, USIZE_C(0), USIZE_C(0), buf2, USIZE_C(0), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Verify buffers unchanged */
    assert(buf1[0] == U8_C(0x10));
    assert(buf2[0] == U8_C(0x20));

    printf("PASSED\n");
}


void
BlockSizeZero(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BlockSizeZero -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(16), U8_C(0x00));
    kdi_FillSeq_u8(buf2, USIZE_C(16), U8_C(0x10));

    /* block_sz is zero -> failure */
    status = GenMemOpsSwapBlocksBound(buf1, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* Verify buffers unchanged */
    assert(buf1[0] == U8_C(0x00));
    assert(buf2[0] == U8_C(0x10));

    printf("PASSED\n");
}


void
Base1SizeMisaligned(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool status;

    printf(LOG_PREFIX_CSTR "Base1SizeMisaligned -> ");

    /* base_1_sz not aligned to block_sz -> failure */
    /* base_1_sz=15, block_sz=4: 15 % 4 = 3, not aligned */
    status = GenMemOpsSwapBlocksBound(buf1, USIZE_C(15), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_1_sz=17, block_sz=2: 17 % 2 = 1, not aligned */
    status = GenMemOpsSwapBlocksBound(buf1, USIZE_C(17), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(2));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
Base2SizeMisaligned(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool status;

    printf(LOG_PREFIX_CSTR "Base2SizeMisaligned -> ");

    /* base_2_sz not aligned to block_sz -> failure */
    /* base_2_sz=15, block_sz=4: 15 % 4 = 3, not aligned */
    status = GenMemOpsSwapBlocksBound(buf1, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(15), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_2_sz=17, block_sz=2: 17 % 2 = 1, not aligned */
    status = GenMemOpsSwapBlocksBound(buf1, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(17), USIZE_C(0), USIZE_C(2));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
Base1IdxMisaligned(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool status;

    printf(LOG_PREFIX_CSTR "Base1IdxMisaligned -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x10));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x20));

    /* base_1_idx not aligned to block_sz -> failure */
    /* base_1_idx=5, block_sz=4: 5 % 4 = 1, not aligned */
    status = GenMemOpsSwapBlocksBound(buf1, USIZE_C(16), USIZE_C(5), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_1_idx=3, block_sz=2: 3 % 2 = 1, not aligned */
    status = GenMemOpsSwapBlocksBound(buf1, USIZE_C(16), USIZE_C(3), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(2));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
Base2IdxMisaligned(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool status;

    printf(LOG_PREFIX_CSTR "Base2IdxMisaligned -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x10));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x20));

    /* base_2_idx not aligned to block_sz -> failure */
    /* base_2_idx=5, block_sz=4: 5 % 4 = 1, not aligned */
    status = GenMemOpsSwapBlocksBound(buf1, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(5), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_2_idx=7, block_sz=2: 7 % 2 = 1, not aligned */
    status = GenMemOpsSwapBlocksBound(buf1, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(7), USIZE_C(2));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
Base1IdxOutOfBounds(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool status;

    printf(LOG_PREFIX_CSTR "Base1IdxOutOfBounds -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x10));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x20));

    /* base_1_idx >= base_1_sz -> failure */
    status = GenMemOpsSwapBlocksBound(buf1, USIZE_C(16), USIZE_C(16), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    status = GenMemOpsSwapBlocksBound(buf1, USIZE_C(16), USIZE_C(20), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Verify buffers unchanged */
    assert(buf1[0] == U8_C(0x10));
    assert(buf2[0] == U8_C(0x20));

    printf("PASSED\n");
}


void
Base2IdxOutOfBounds(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool status;

    printf(LOG_PREFIX_CSTR "Base2IdxOutOfBounds -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x10));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x20));

    /* base_2_idx >= base_2_sz -> failure */
    status = GenMemOpsSwapBlocksBound(buf1, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(16), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    status = GenMemOpsSwapBlocksBound(buf1, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(20), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Verify buffers unchanged */
    assert(buf1[0] == U8_C(0x10));
    assert(buf2[0] == U8_C(0x20));

    printf("PASSED\n");
}


void
Base1IdxPlusBlockSizeExceedsSize(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool status;

    printf(LOG_PREFIX_CSTR "Base1IdxPlusBlockSizeExceedsSize -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x10));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x20));

    /* (base_1_idx + block_sz) > base_1_sz -> failure */
    /* 14 + 4 = 18 > 16 */
    status = GenMemOpsSwapBlocksBound(buf1, USIZE_C(16), USIZE_C(14), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Verify buffers unchanged */
    assert(buf1[0] == U8_C(0x10));
    assert(buf2[0] == U8_C(0x20));

    printf("PASSED\n");
}


void
Base2IdxPlusBlockSizeExceedsSize(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool status;

    printf(LOG_PREFIX_CSTR "Base2IdxPlusBlockSizeExceedsSize -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x10));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x20));

    /* (base_2_idx + block_sz) > base_2_sz -> failure */
    /* 14 + 4 = 18 > 16 */
    status = GenMemOpsSwapBlocksBound(buf1, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(14), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Verify buffers unchanged */
    assert(buf1[0] == U8_C(0x10));
    assert(buf2[0] == U8_C(0x20));

    printf("PASSED\n");
}


void
SwapDifferentBuffers(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapDifferentBuffers -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(16), U8_C(0x00));
    kdi_FillSeq_u8(buf2, USIZE_C(16), U8_C(0x10));

    /* Swap buf1[0-3] with buf2[0-3], block_sz=4 */
    status = GenMemOpsSwapBlocksBound(buf1, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Verify swap */
    assert(buf1[0] == U8_C(0x10));
    assert(buf1[1] == U8_C(0x11));
    assert(buf1[2] == U8_C(0x12));
    assert(buf1[3] == U8_C(0x13));
    assert(buf2[0] == U8_C(0x00));
    assert(buf2[1] == U8_C(0x01));
    assert(buf2[2] == U8_C(0x02));
    assert(buf2[3] == U8_C(0x03));

    /* Verify rest unchanged */
    assert(buf1[4] == U8_C(0x04));
    assert(buf2[4] == U8_C(0x14));

    printf("PASSED\n");
}


void
SwapSameBufferDifferentIndices(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapSameBufferDifferentIndices -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Swap buf[0-3] with buf[8-11] (same buffer), block_sz=4 */
    status = GenMemOpsSwapBlocksBound(buf, USIZE_C(16), USIZE_C(0), buf, USIZE_C(16), USIZE_C(8), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Verify swap */
    assert(buf[0] == U8_C(0x08));
    assert(buf[1] == U8_C(0x09));
    assert(buf[2] == U8_C(0x0A));
    assert(buf[3] == U8_C(0x0B));
    assert(buf[8] == U8_C(0x00));
    assert(buf[9] == U8_C(0x01));
    assert(buf[10] == U8_C(0x02));
    assert(buf[11] == U8_C(0x03));

    /* Verify rest unchanged */
    assert(buf[4] == U8_C(0x04));
    assert(buf[7] == U8_C(0x07));
    assert(buf[12] == U8_C(0x0C));

    printf("PASSED\n");
}


void
SwapSameBufferSameIndex(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapSameBufferSameIndex -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Swap buf[4-7] with buf[4-7] (same location) -> success, no change */
    status = GenMemOpsSwapBlocksBound(buf, USIZE_C(16), USIZE_C(4), buf, USIZE_C(16), USIZE_C(4), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Values should remain unchanged */
    assert(buf[4] == U8_C(0x04));
    assert(buf[5] == U8_C(0x05));
    assert(buf[6] == U8_C(0x06));
    assert(buf[7] == U8_C(0x07));

    /* Verify entire buffer unchanged */
    assert(buf[0] == U8_C(0x00));
    assert(buf[15] == U8_C(0x0F));

    printf("PASSED\n");
}


void
SwapAdjacentBlocks(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapAdjacentBlocks -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(16), U8_C(0x00));
    kdi_FillSeq_u8(buf2, USIZE_C(16), U8_C(0x20));

    /* Swap buf1[4-7] with buf2[8-11], block_sz=4 */
    status = GenMemOpsSwapBlocksBound(buf1, USIZE_C(16), USIZE_C(4), buf2, USIZE_C(16), USIZE_C(8), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Verify swap */
    assert(buf1[4] == U8_C(0x28));
    assert(buf1[5] == U8_C(0x29));
    assert(buf1[6] == U8_C(0x2A));
    assert(buf1[7] == U8_C(0x2B));
    assert(buf2[8] == U8_C(0x04));
    assert(buf2[9] == U8_C(0x05));
    assert(buf2[10] == U8_C(0x06));
    assert(buf2[11] == U8_C(0x07));

    /* Verify neighbors unchanged */
    assert(buf1[3] == U8_C(0x03));
    assert(buf1[8] == U8_C(0x08));
    assert(buf2[7] == U8_C(0x27));
    assert(buf2[12] == U8_C(0x2C));

    printf("PASSED\n");
}


void
SwapFirstBlocks(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapFirstBlocks -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x10));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x20));

    /* Swap first blocks */
    status = GenMemOpsSwapBlocksBound(buf1, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    assert(buf1[0] == U8_C(0x20));
    assert(buf1[3] == U8_C(0x23));
    assert(buf2[0] == U8_C(0x10));
    assert(buf2[3] == U8_C(0x13));

    printf("PASSED\n");
}


void
SwapLastBlocks(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapLastBlocks -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(16), U8_C(0x10));
    kdi_FillSeq_u8(buf2, USIZE_C(16), U8_C(0x20));

    /* Swap last blocks */
    status = GenMemOpsSwapBlocksBound(buf1, USIZE_C(16), USIZE_C(12), buf2, USIZE_C(16), USIZE_C(12), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    assert(buf1[12] == U8_C(0x2C));
    assert(buf1[15] == U8_C(0x2F));
    assert(buf2[12] == U8_C(0x1C));
    assert(buf2[15] == U8_C(0x1F));

    /* Verify rest unchanged */
    assert(buf1[11] == U8_C(0x1B));
    assert(buf2[11] == U8_C(0x2B));

    printf("PASSED\n");
}


void
SwapDifferentSizedBuffers(void)
{
    u8   buf1[32];
    u8   buf2[16];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapDifferentSizedBuffers -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(32), U8_C(0x00));
    kdi_FillSeq_u8(buf2, USIZE_C(16), U8_C(0x20));

    /* Swap buf1[20-23] with buf2[8-11], block_sz=4 */
    status = GenMemOpsSwapBlocksBound(buf1, USIZE_C(32), USIZE_C(20), buf2, USIZE_C(16), USIZE_C(8), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    assert(buf1[20] == U8_C(0x28));
    assert(buf1[23] == U8_C(0x2B));
    assert(buf2[8] == U8_C(0x14));
    assert(buf2[11] == U8_C(0x17));

    printf("PASSED\n");
}


void
DoubleSwap(void)
{
    u8   buf1[16];
    u8   buf2[16];
    u8   orig1[4], orig2[4];
    bool status;

    printf(LOG_PREFIX_CSTR "DoubleSwap -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(16), U8_C(0x00));
    kdi_FillSeq_u8(buf2, USIZE_C(16), U8_C(0x10));

    /* Keep copy of original blocks */
    orig1[0] = buf1[4];
    orig1[1] = buf1[5];
    orig1[2] = buf1[6];
    orig1[3] = buf1[7];
    orig2[0] = buf2[8];
    orig2[1] = buf2[9];
    orig2[2] = buf2[10];
    orig2[3] = buf2[11];

    /* Swap once */
    status   = GenMemOpsSwapBlocksBound(buf1, USIZE_C(16), USIZE_C(4), buf2, USIZE_C(16), USIZE_C(8), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Swap again - should restore */
    status = GenMemOpsSwapBlocksBound(buf1, USIZE_C(16), USIZE_C(4), buf2, USIZE_C(16), USIZE_C(8), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Should be back to original */
    assert(buf1[4] == orig1[0] && buf1[5] == orig1[1]);
    assert(buf2[8] == orig2[0] && buf2[9] == orig2[1]);

    printf("PASSED\n");
}


void
BlockSizeOne(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BlockSizeOne -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(16), U8_C(0x00));
    kdi_FillSeq_u8(buf2, USIZE_C(16), U8_C(0x10));

    /* Block size 1 = byte swap */
    status = GenMemOpsSwapBlocksBound(buf1, USIZE_C(16), USIZE_C(5), buf2, USIZE_C(16), USIZE_C(7), USIZE_C(1));
    assert(status == RESULT_SUCCESS);

    assert(buf1[5] == U8_C(0x17));
    assert(buf2[7] == U8_C(0x05));

    /* Verify neighbors unchanged */
    assert(buf1[4] == U8_C(0x04));
    assert(buf1[6] == U8_C(0x06));
    assert(buf2[6] == U8_C(0x16));
    assert(buf2[8] == U8_C(0x18));

    printf("PASSED\n");
}


void
U16_Blocks_Swap(void)
{
    u16  buf1[8];
    u16  buf2[8];
    bool status;

    printf(LOG_PREFIX_CSTR "U16_Blocks_Swap -> ");

    buf1[0] = U16_C(0);
    buf1[1] = U16_C(1);
    buf1[2] = U16_C(2);
    buf1[3] = U16_C(3);
    buf1[4] = U16_C(4);
    buf1[5] = U16_C(5);
    buf1[6] = U16_C(6);
    buf1[7] = U16_C(7);
    buf2[0] = U16_C(10);
    buf2[1] = U16_C(11);
    buf2[2] = U16_C(12);
    buf2[3] = U16_C(13);
    buf2[4] = U16_C(14);
    buf2[5] = U16_C(15);
    buf2[6] = U16_C(16);
    buf2[7] = U16_C(17);

    /* Swap buf1[2] (idx=4 bytes) with buf2[5] (idx=10 bytes), block_sz=2 */
    status  = GenMemOpsSwapBlocksBound(buf1, sizeof(buf1), USIZE_C(2) * sizeof(u16), buf2, sizeof(buf2), USIZE_C(5) * sizeof(u16), sizeof(u16));
    assert(status == RESULT_SUCCESS);

    assert(buf1[2] == U16_C(15));
    assert(buf2[5] == U16_C(2));

    /* Verify neighbors unchanged */
    assert(buf1[1] == U16_C(1));
    assert(buf1[3] == U16_C(3));
    assert(buf2[4] == U16_C(14));
    assert(buf2[6] == U16_C(16));

    printf("PASSED\n");
}


void
U32_Blocks_Swap(void)
{
    u32  buf1[6];
    u32  buf2[6];
    bool status;

    printf(LOG_PREFIX_CSTR "U32_Blocks_Swap -> ");

    buf1[0] = U32_C(10);
    buf1[1] = U32_C(20);
    buf1[2] = U32_C(30);
    buf1[3] = U32_C(40);
    buf1[4] = U32_C(50);
    buf1[5] = U32_C(60);
    buf2[0] = U32_C(100);
    buf2[1] = U32_C(200);
    buf2[2] = U32_C(300);
    buf2[3] = U32_C(400);
    buf2[4] = U32_C(500);
    buf2[5] = U32_C(600);

    /* Swap buf1[1] (idx=4 bytes) with buf2[4] (idx=16 bytes), block_sz=4 */
    status  = GenMemOpsSwapBlocksBound(buf1, sizeof(buf1), USIZE_C(1) * sizeof(u32), buf2, sizeof(buf2), USIZE_C(4) * sizeof(u32), sizeof(u32));
    assert(status == RESULT_SUCCESS);

    assert(buf1[1] == U32_C(500));
    assert(buf2[4] == U32_C(20));

    /* Verify neighbors unchanged */
    assert(buf1[0] == U32_C(10));
    assert(buf1[2] == U32_C(30));
    assert(buf2[3] == U32_C(400));
    assert(buf2[5] == U32_C(600));

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_Blocks_Swap(void)
{
    u64  buf1[6];
    u64  buf2[6];
    bool status;

    printf(LOG_PREFIX_CSTR "U64_Blocks_Swap -> ");

    buf1[0] = U64_C(0);
    buf1[1] = U64_C(10);
    buf1[2] = U64_C(20);
    buf1[3] = U64_C(30);
    buf1[4] = U64_C(40);
    buf1[5] = U64_C(50);
    buf2[0] = U64_C(100);
    buf2[1] = U64_C(110);
    buf2[2] = U64_C(120);
    buf2[3] = U64_C(130);
    buf2[4] = U64_C(140);
    buf2[5] = U64_C(150);

    /* Swap buf1[0] (idx=0) and buf2[5] (idx=40 bytes), block_sz=8 */
    status  = GenMemOpsSwapBlocksBound(buf1, sizeof(buf1), USIZE_C(0), buf2, sizeof(buf2), USIZE_C(5) * sizeof(u64), sizeof(u64));
    assert(status == RESULT_SUCCESS);

    assert(buf1[0] == U64_C(150));
    assert(buf2[5] == U64_C(0));

    /* Verify neighbors unchanged */
    assert(buf1[1] == U64_C(10));
    assert(buf2[4] == U64_C(140));

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
    kdi_SmallStruct buf1[4];
    kdi_SmallStruct buf2[4];
    bool            status;

    printf(LOG_PREFIX_CSTR "Struct_Blocks_Swap -> ");

    buf1[0].a = U32_C(1);
    buf1[0].b = U32_C(10);
    buf1[0].c = U8_C(100);
    buf1[1].a = U32_C(2);
    buf1[1].b = U32_C(20);
    buf1[1].c = U8_C(200);
    buf1[2].a = U32_C(3);
    buf1[2].b = U32_C(30);
    buf1[2].c = U8_C(50);
    buf1[3].a = U32_C(4);
    buf1[3].b = U32_C(40);
    buf1[3].c = U8_C(60);

    buf2[0].a = U32_C(11);
    buf2[0].b = U32_C(110);
    buf2[0].c = U8_C(101);
    buf2[1].a = U32_C(12);
    buf2[1].b = U32_C(120);
    buf2[1].c = U8_C(102);
    buf2[2].a = U32_C(13);
    buf2[2].b = U32_C(130);
    buf2[2].c = U8_C(103);
    buf2[3].a = U32_C(14);
    buf2[3].b = U32_C(140);
    buf2[3].c = U8_C(104);

    /* Swap buf1[1] and buf2[3] */
    status    = GenMemOpsSwapBlocksBound(buf1, sizeof(buf1), USIZE_C(1) * sizeof(kdi_SmallStruct), buf2, sizeof(buf2), USIZE_C(3) * sizeof(kdi_SmallStruct), sizeof(kdi_SmallStruct));
    assert(status == RESULT_SUCCESS);

    assert(buf1[1].a == U32_C(14) && buf1[1].b == U32_C(140) && buf1[1].c == U8_C(104));
    assert(buf2[3].a == U32_C(2) && buf2[3].b == U32_C(20) && buf2[3].c == U8_C(200));

    /* Verify neighbors unchanged */
    assert(buf1[0].a == U32_C(1));
    assert(buf1[2].a == U32_C(3));
    assert(buf2[2].a == U32_C(13));

    printf("PASSED\n");
}


void
LargeBuffers(void)
{
    u8    buf1[128];
    u8    buf2[128];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffers -> ");

    kdi_Fill_u8(buf1, USIZE_C(128), U8_C(0xAA));
    kdi_Fill_u8(buf2, USIZE_C(128), U8_C(0xBB));

    /* Swap blocks: buf1[16-23] with buf2[96-103], block_sz=8 */
    status = GenMemOpsSwapBlocksBound(buf1, USIZE_C(128), USIZE_C(16), buf2, USIZE_C(128), USIZE_C(96), USIZE_C(8));
    assert(status == RESULT_SUCCESS);

    /* Verify swapped block in buf1 (indices 16-23 should now be 0xBB) */
    for (i = USIZE_C(16); i < USIZE_C(24); ++i)
    {
        assert(buf1[i] == U8_C(0xBB));
    }

    /* Verify swapped block in buf2 (indices 96-103 should now be 0xAA) */
    for (i = USIZE_C(96); i < USIZE_C(104); ++i)
    {
        assert(buf2[i] == U8_C(0xAA));
    }

    /* Verify some unchanged regions */
    assert(buf1[0] == U8_C(0xAA));
    assert(buf1[15] == U8_C(0xAA));
    assert(buf1[24] == U8_C(0xAA));
    assert(buf1[127] == U8_C(0xAA));
    assert(buf2[0] == U8_C(0xBB));
    assert(buf2[95] == U8_C(0xBB));
    assert(buf2[104] == U8_C(0xBB));
    assert(buf2[127] == U8_C(0xBB));

    printf("PASSED\n");
}


void
AllSameBlocks(void)
{
    u32   buf1[8];
    u32   buf2[8];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "AllSameBlocks -> ");

    /* Fill all blocks with same value */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        buf1[i] = U32_C(0xBAADF00D);
        buf2[i] = U32_C(0xBAADF00D);
    }

    /* Swap blocks */
    status = GenMemOpsSwapBlocksBound(buf1, sizeof(buf1), USIZE_C(1) * sizeof(u32), buf2, sizeof(buf2), USIZE_C(5) * sizeof(u32), sizeof(u32));
    assert(status == RESULT_SUCCESS);

    /* All values should still be the same */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        assert(buf1[i] == U32_C(0xBAADF00D));
        assert(buf2[i] == U32_C(0xBAADF00D));
    }

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    Base1Null();
    Base2Null();
    BothBasesNull();
    Base1SizeZero();
    Base2SizeZero();
    BothSizesZero();
    BlockSizeZero();
    Base1SizeMisaligned();
    Base2SizeMisaligned();
    Base1IdxMisaligned();
    Base2IdxMisaligned();
    Base1IdxOutOfBounds();
    Base2IdxOutOfBounds();
    Base1IdxPlusBlockSizeExceedsSize();
    Base2IdxPlusBlockSizeExceedsSize();
    SwapDifferentBuffers();
    SwapSameBufferDifferentIndices();
    SwapSameBufferSameIndex();
    SwapAdjacentBlocks();
    SwapFirstBlocks();
    SwapLastBlocks();
    SwapDifferentSizedBuffers();
    DoubleSwap();
    BlockSizeOne();
    U16_Blocks_Swap();
    U32_Blocks_Swap();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_Blocks_Swap();
#endif
    Struct_Blocks_Swap();
    LargeBuffers();
    AllSameBlocks();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
