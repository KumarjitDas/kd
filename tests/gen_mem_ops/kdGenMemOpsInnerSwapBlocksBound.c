/**
 * @file kdGenMemOpsInnerSwapBlocksBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsInnerSwapBlocksBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsInnerSwapBlocksBound function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


static bool
kdi_BytesEqual(const byte *a, const byte *b, usize sz)
{
    usize i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        if (a[i] != b[i])
        {
            return RESULT_FAILURE;
        }
    }

    return RESULT_SUCCESS;
}


static void
kdi_FillSeq(u8 *dst, usize sz, u8 start)
{
    usize i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        dst[i] = (u8)(start + (u8)i);
    }
}


void
NullPointer(void)
{
    bool status;

    printf(LOG_PREFIX_CSTR "NullPointer -> ");

    /* base is null -> failure */
    status = GenMemOpsInnerSwapBlocksBound(null, USIZE_C(16), USIZE_C(0), USIZE_C(4), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ZeroBaseSize(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ZeroBaseSize -> ");

    /* base_sz is zero -> failure (caught by idx >= base_sz when idx >= 0) */
    status = GenMemOpsInnerSwapBlocksBound(buf, USIZE_C(0), USIZE_C(0), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ZeroBlockSize(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ZeroBlockSize -> ");

    /* Init buffer */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* block_sz is zero -> failure */
    status = GenMemOpsInnerSwapBlocksBound(buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* Verify buffer unchanged */
    assert(buf[0] == U8_C(0x00));
    assert(buf[15] == U8_C(0x0F));

    printf("PASSED\n");
}


void
BaseSizeMisaligned(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BaseSizeMisaligned -> ");

    /* base_sz not aligned to block_sz -> failure */
    /* base_sz=15, block_sz=4: 15 % 4 = 3, not aligned */
    status = GenMemOpsInnerSwapBlocksBound(buf, USIZE_C(15), USIZE_C(0), USIZE_C(8), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_sz=17, block_sz=2: 17 % 2 = 1, not aligned */
    status = GenMemOpsInnerSwapBlocksBound(buf, USIZE_C(17), USIZE_C(0), USIZE_C(4), USIZE_C(2));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
Idx1Misaligned(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "Idx1Misaligned -> ");

    /* Init buffer */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* idx_1 not aligned to block_sz -> failure */
    /* idx_1=5, block_sz=4: 5 % 4 = 1, not aligned */
    status = GenMemOpsInnerSwapBlocksBound(buf, USIZE_C(16), USIZE_C(5), USIZE_C(8), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* idx_1=3, block_sz=2: 3 % 2 = 1, not aligned */
    status = GenMemOpsInnerSwapBlocksBound(buf, USIZE_C(16), USIZE_C(3), USIZE_C(8), USIZE_C(2));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
Idx2Misaligned(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "Idx2Misaligned -> ");

    /* Init buffer */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* idx_2 not aligned to block_sz -> failure */
    /* idx_2=5, block_sz=4: 5 % 4 = 1, not aligned */
    status = GenMemOpsInnerSwapBlocksBound(buf, USIZE_C(16), USIZE_C(0), USIZE_C(5), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* idx_2=7, block_sz=2: 7 % 2 = 1, not aligned */
    status = GenMemOpsInnerSwapBlocksBound(buf, USIZE_C(16), USIZE_C(0), USIZE_C(7), USIZE_C(2));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
BothIndicesMisaligned(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BothIndicesMisaligned -> ");

    /* Init buffer */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Both indices misaligned -> failure */
    status = GenMemOpsInnerSwapBlocksBound(buf, USIZE_C(16), USIZE_C(5), USIZE_C(9), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
Idx1OutOfBounds(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "Idx1OutOfBounds -> ");

    /* Init buffer */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* idx_1 + block_sz > base_sz -> failure */
    /* 13 + 4 = 17 > 16 */
    status = GenMemOpsInnerSwapBlocksBound(buf, USIZE_C(16), USIZE_C(13), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* idx_1 == base_sz -> failure */
    status = GenMemOpsInnerSwapBlocksBound(buf, USIZE_C(16), USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Verify buffer unchanged */
    assert(buf[0] == U8_C(0x00));
    assert(buf[15] == U8_C(0x0F));

    printf("PASSED\n");
}


void
Idx2OutOfBounds(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "Idx2OutOfBounds -> ");

    /* Init buffer */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* idx_2 + block_sz > base_sz -> failure */
    /* 14 + 4 = 18 > 16 */
    status = GenMemOpsInnerSwapBlocksBound(buf, USIZE_C(16), USIZE_C(0), USIZE_C(14), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* idx_2 == base_sz -> failure */
    status = GenMemOpsInnerSwapBlocksBound(buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Verify buffer unchanged */
    assert(buf[0] == U8_C(0x00));
    assert(buf[15] == U8_C(0x0F));

    printf("PASSED\n");
}


void
BothIndicesOutOfBounds(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BothIndicesOutOfBounds -> ");

    /* Init buffer */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x10));

    /* Both indices out of bounds */
    status = GenMemOpsInnerSwapBlocksBound(buf, USIZE_C(16), USIZE_C(20), USIZE_C(24), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Verify buffer unchanged */
    assert(buf[0] == U8_C(0x10));
    assert(buf[15] == U8_C(0x1F));

    printf("PASSED\n");
}


void
SwapSameIndex(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapSameIndex -> ");

    /* Init: 0x00..0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Swap block at index 4 with itself (block_sz=4) */
    status = GenMemOpsInnerSwapBlocksBound(buf, USIZE_C(16), USIZE_C(4), USIZE_C(4), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Expected: unchanged */
    assert(buf[4] == U8_C(0x04));
    assert(buf[5] == U8_C(0x05));
    assert(buf[6] == U8_C(0x06));
    assert(buf[7] == U8_C(0x07));

    printf("PASSED\n");
}


void
ValidSwapDistinctBlocks(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ValidSwapDistinctBlocks -> ");

    /* Init: 0x00..0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Block size 4. Swap index 0 (bytes 0-3) and index 12 (bytes 12-15) */
    status = GenMemOpsInnerSwapBlocksBound(buf, USIZE_C(16), USIZE_C(0), USIZE_C(12), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Expected: [0C 0D 0E 0F] [04..0B] [00 01 02 03] */
    assert(buf[0] == U8_C(0x0C));
    assert(buf[1] == U8_C(0x0D));
    assert(buf[2] == U8_C(0x0E));
    assert(buf[3] == U8_C(0x0F));
    assert(buf[4] == U8_C(0x04));
    assert(buf[11] == U8_C(0x0B));
    assert(buf[12] == U8_C(0x00));
    assert(buf[13] == U8_C(0x01));
    assert(buf[14] == U8_C(0x02));
    assert(buf[15] == U8_C(0x03));

    printf("PASSED\n");
}


void
ValidSwapAdjacentBlocks(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ValidSwapAdjacentBlocks -> ");

    /* Init: 0x00..0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Block size 4. Swap index 0 (bytes 0-3) and index 4 (bytes 4-7) */
    status = GenMemOpsInnerSwapBlocksBound(buf, USIZE_C(16), USIZE_C(0), USIZE_C(4), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Expected: [04 05 06 07] [00 01 02 03] [08..0F] */
    assert(buf[0] == U8_C(0x04));
    assert(buf[3] == U8_C(0x07));
    assert(buf[4] == U8_C(0x00));
    assert(buf[7] == U8_C(0x03));
    assert(buf[8] == U8_C(0x08));

    printf("PASSED\n");
}


void
ValidSwapMiddleBlocks(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ValidSwapMiddleBlocks -> ");

    /* Init: 0x00..0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Block size 2. Swap index 4 (bytes 4-5) and index 10 (bytes 10-11) */
    status = GenMemOpsInnerSwapBlocksBound(buf, USIZE_C(16), USIZE_C(4), USIZE_C(10), USIZE_C(2));
    assert(status == RESULT_SUCCESS);

    /* Verify pre-swap region */
    assert(buf[3] == U8_C(0x03));

    /* Verify first swapped block */
    assert(buf[4] == U8_C(0x0A));
    assert(buf[5] == U8_C(0x0B));

    /* Verify middle region */
    assert(buf[6] == U8_C(0x06));
    assert(buf[9] == U8_C(0x09));

    /* Verify second swapped block */
    assert(buf[10] == U8_C(0x04));
    assert(buf[11] == U8_C(0x05));

    /* Verify post-swap region */
    assert(buf[12] == U8_C(0x0C));

    printf("PASSED\n");
}


void
ValidSwapReversedIndices(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ValidSwapReversedIndices -> ");

    /* Init: 0x00..0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Block size 4. Swap index 12 and index 0 (reverse order) */
    status = GenMemOpsInnerSwapBlocksBound(buf, USIZE_C(16), USIZE_C(12), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Expected: same as ValidSwapDistinctBlocks */
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

    /* Init: 0x00..0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Keep copy of original */
    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        original[i] = buf[i];
    }

    /* Swap index 0 and 8 (block_sz=4) */
    status = GenMemOpsInnerSwapBlocksBound(buf, USIZE_C(16), USIZE_C(0), USIZE_C(8), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Swap index 0 and 8 again - should restore */
    status = GenMemOpsInnerSwapBlocksBound(buf, USIZE_C(16), USIZE_C(0), USIZE_C(8), USIZE_C(4));
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

    /* Init: 0x00..0x07 */
    kdi_FillSeq(buf, USIZE_C(8), U8_C(0x00));

    /* Block size 1 = byte swap. Swap index 2 and 5 */
    status = GenMemOpsInnerSwapBlocksBound(buf, USIZE_C(8), USIZE_C(2), USIZE_C(5), USIZE_C(1));
    assert(status == RESULT_SUCCESS);

    /* Expected: 00 01 05 03 04 02 06 07 */
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
U16_Blocks_ValidSwap(void)
{
    u16  buf[8];
    bool status;

    printf(LOG_PREFIX_CSTR "U16_Blocks_ValidSwap -> ");

    /* Init: 0, 1, 2, 3, 4, 5, 6, 7 */
    buf[0] = U16_C(0);
    buf[1] = U16_C(1);
    buf[2] = U16_C(2);
    buf[3] = U16_C(3);
    buf[4] = U16_C(4);
    buf[5] = U16_C(5);
    buf[6] = U16_C(6);
    buf[7] = U16_C(7);

    /* Swap element 1 (idx=2 bytes) and element 6 (idx=12 bytes) */
    status = GenMemOpsInnerSwapBlocksBound(buf, sizeof(buf), USIZE_C(1) * sizeof(u16), USIZE_C(6) * sizeof(u16), sizeof(u16));
    assert(status == RESULT_SUCCESS);

    /* Expected: 0, 6, 2, 3, 4, 5, 1, 7 */
    assert(buf[0] == U16_C(0));
    assert(buf[1] == U16_C(6));
    assert(buf[2] == U16_C(2));
    assert(buf[5] == U16_C(5));
    assert(buf[6] == U16_C(1));
    assert(buf[7] == U16_C(7));

    printf("PASSED\n");
}


void
U16_Blocks_OutOfBounds(void)
{
    u16  buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "U16_Blocks_OutOfBounds -> ");

    /* Init: 0x1111, 0x2222, 0x3333, 0x4444 */
    buf[0] = U16_C(0x1111);
    buf[1] = U16_C(0x2222);
    buf[2] = U16_C(0x3333);
    buf[3] = U16_C(0x4444);

    /* idx_2 = 8 bytes = beyond buffer (size = 8 bytes) */
    status = GenMemOpsInnerSwapBlocksBound(buf, sizeof(buf), USIZE_C(0), sizeof(buf), sizeof(u16));
    assert(status == RESULT_FAILURE);

    /* Verify buffer unchanged */
    assert(buf[0] == U16_C(0x1111));
    assert(buf[3] == U16_C(0x4444));

    printf("PASSED\n");
}


void
U32_Blocks_ValidSwap(void)
{
    u32  buf[6];
    bool status;

    printf(LOG_PREFIX_CSTR "U32_Blocks_ValidSwap -> ");

    /* Init: 10, 20, 30, 40, 50, 60 */
    buf[0] = U32_C(10);
    buf[1] = U32_C(20);
    buf[2] = U32_C(30);
    buf[3] = U32_C(40);
    buf[4] = U32_C(50);
    buf[5] = U32_C(60);

    /* Swap element 1 (idx=4 bytes) and element 4 (idx=16 bytes) */
    status = GenMemOpsInnerSwapBlocksBound(buf, sizeof(buf), USIZE_C(1) * sizeof(u32), USIZE_C(4) * sizeof(u32), sizeof(u32));
    assert(status == RESULT_SUCCESS);

    /* Expected: 10, 50, 30, 40, 20, 60 */
    assert(buf[0] == U32_C(10));
    assert(buf[1] == U32_C(50));
    assert(buf[2] == U32_C(30));
    assert(buf[3] == U32_C(40));
    assert(buf[4] == U32_C(20));
    assert(buf[5] == U32_C(60));

    printf("PASSED\n");
}


void
U32_Blocks_MultipleSwaps(void)
{
    u32  buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "U32_Blocks_MultipleSwaps -> ");

    /* Init: 10, 20, 30, 40 */
    buf[0] = U32_C(10);
    buf[1] = U32_C(20);
    buf[2] = U32_C(30);
    buf[3] = U32_C(40);

    /* Swap 0 and 3 */
    status = GenMemOpsInnerSwapBlocksBound(buf, sizeof(buf), USIZE_C(0), USIZE_C(3) * sizeof(u32), sizeof(u32));
    assert(status == RESULT_SUCCESS);

    /* Swap 1 and 2 */
    status = GenMemOpsInnerSwapBlocksBound(buf, sizeof(buf), USIZE_C(1) * sizeof(u32), USIZE_C(2) * sizeof(u32), sizeof(u32));
    assert(status == RESULT_SUCCESS);

    /* Expected: 40, 30, 20, 10 */
    assert(buf[0] == U32_C(40));
    assert(buf[1] == U32_C(30));
    assert(buf[2] == U32_C(20));
    assert(buf[3] == U32_C(10));

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_Blocks_ValidSwap(void)
{
    u64  buf[6];
    bool status;

    printf(LOG_PREFIX_CSTR "U64_Blocks_ValidSwap -> ");

    /* Init: 0, 10, 20, 30, 40, 50 */
    buf[0] = U64_C(0);
    buf[1] = U64_C(10);
    buf[2] = U64_C(20);
    buf[3] = U64_C(30);
    buf[4] = U64_C(40);
    buf[5] = U64_C(50);

    /* Swap element 0 (idx=0) and element 5 (idx=40 bytes) */
    status = GenMemOpsInnerSwapBlocksBound(buf, sizeof(buf), USIZE_C(0), USIZE_C(5) * sizeof(u64), sizeof(u64));
    assert(status == RESULT_SUCCESS);

    /* Expected: 50, 10, 20, 30, 40, 0 */
    assert(buf[0] == U64_C(50));
    assert(buf[1] == U64_C(10));
    assert(buf[4] == U64_C(40));
    assert(buf[5] == U64_C(0));

    printf("PASSED\n");
}


void
U64_Blocks_OutOfBounds(void)
{
    u64  buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "U64_Blocks_OutOfBounds -> ");

    /* Init */
    buf[0] = U64_C(0x1111111111111111);
    buf[1] = U64_C(0x2222222222222222);
    buf[2] = U64_C(0x3333333333333333);
    buf[3] = U64_C(0x4444444444444444);

    /* idx_1 = 24, idx_1 + block_sz = 24 + 8 = 32 > base_sz(32) - 1 -> actually equal, boundary case */
    /* idx_1 = 32 = base_sz -> out of bounds */
    status = GenMemOpsInnerSwapBlocksBound(buf, sizeof(buf), sizeof(buf), USIZE_C(0), sizeof(u64));
    assert(status == RESULT_FAILURE);

    /* Verify buffer unchanged */
    assert(buf[0] == U64_C(0x1111111111111111));
    assert(buf[3] == U64_C(0x4444444444444444));

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
Struct_Blocks_ValidSwap(void)
{
    kdi_SmallStruct buf[4];
    bool            status;

    printf(LOG_PREFIX_CSTR "Struct_Blocks_ValidSwap -> ");

    /* Init: S0, S1, S2, S3 */
    buf[0].a = U32_C(1);
    buf[0].b = U32_C(10);
    buf[0].c = U8_C(100);
    buf[1].a = U32_C(2);
    buf[1].b = U32_C(20);
    buf[1].c = U8_C(200);
    buf[2].a = U32_C(3);
    buf[2].b = U32_C(30);
    buf[2].c = U8_C(50);
    buf[3].a = U32_C(4);
    buf[3].b = U32_C(40);
    buf[3].c = U8_C(60);

    /* Swap element 1 and element 3 */
    status = GenMemOpsInnerSwapBlocksBound(buf, sizeof(buf), USIZE_C(1) * sizeof(kdi_SmallStruct), USIZE_C(3) * sizeof(kdi_SmallStruct), sizeof(kdi_SmallStruct));
    assert(status == RESULT_SUCCESS);

    /* Expected: S0, S3, S2, S1 */
    assert(buf[0].a == U32_C(1) && buf[0].b == U32_C(10) && buf[0].c == U8_C(100));
    assert(buf[1].a == U32_C(4) && buf[1].b == U32_C(40) && buf[1].c == U8_C(60));
    assert(buf[2].a == U32_C(3) && buf[2].b == U32_C(30) && buf[2].c == U8_C(50));
    assert(buf[3].a == U32_C(2) && buf[3].b == U32_C(20) && buf[3].c == U8_C(200));

    printf("PASSED\n");
}


void
Struct_Blocks_OutOfBounds(void)
{
    kdi_SmallStruct buf[3];
    bool            status;

    printf(LOG_PREFIX_CSTR "Struct_Blocks_OutOfBounds -> ");

    /* Init: S0, S1, S2 */
    buf[0].a = U32_C(1);
    buf[0].b = U32_C(10);
    buf[0].c = U8_C(100);
    buf[1].a = U32_C(2);
    buf[1].b = U32_C(20);
    buf[1].c = U8_C(200);
    buf[2].a = U32_C(3);
    buf[2].b = U32_C(30);
    buf[2].c = U8_C(50);

    /* idx_2 = 3 * sizeof(struct) = beyond array */
    status = GenMemOpsInnerSwapBlocksBound(buf, sizeof(buf), USIZE_C(0), USIZE_C(3) * sizeof(kdi_SmallStruct), sizeof(kdi_SmallStruct));
    assert(status == RESULT_FAILURE);

    /* Verify buffer unchanged */
    assert(buf[0].a == U32_C(1));
    assert(buf[2].c == U8_C(50));

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    u8    buf[128];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    /* Init: 0..127 */
    kdi_FillSeq(buf, USIZE_C(128), U8_C(0));

    /* Swap blocks: idx=16 (bytes 16-23) and idx=96 (bytes 96-103), block_sz=8 */
    status = GenMemOpsInnerSwapBlocksBound(buf, USIZE_C(128), USIZE_C(16), USIZE_C(96), USIZE_C(8));
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
BoundarySwap(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BoundarySwap -> ");

    /* Init: 0x00..0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Swap last two blocks: idx=8 (bytes 8-11) and idx=12 (bytes 12-15), block_sz=4 */
    status = GenMemOpsInnerSwapBlocksBound(buf, USIZE_C(16), USIZE_C(8), USIZE_C(12), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Verify beginning unchanged */
    assert(buf[7] == U8_C(0x07));

    /* Verify swapped blocks */
    assert(buf[8] == U8_C(0x0C));
    assert(buf[11] == U8_C(0x0F));
    assert(buf[12] == U8_C(0x08));
    assert(buf[15] == U8_C(0x0B));

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
        buf[i] = U32_C(0xBAADF00D);
    }

    /* Swap blocks */
    status = GenMemOpsInnerSwapBlocksBound(buf, sizeof(buf), USIZE_C(1) * sizeof(u32), USIZE_C(5) * sizeof(u32), sizeof(u32));
    assert(status == RESULT_SUCCESS);

    /* All values should still be the same */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        assert(buf[i] == U32_C(0xBAADF00D));
    }

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    NullPointer();
    ZeroBaseSize();
    ZeroBlockSize();
    BaseSizeMisaligned();
    Idx1Misaligned();
    Idx2Misaligned();
    BothIndicesMisaligned();
    Idx1OutOfBounds();
    Idx2OutOfBounds();
    BothIndicesOutOfBounds();
    SwapSameIndex();
    ValidSwapDistinctBlocks();
    ValidSwapAdjacentBlocks();
    ValidSwapMiddleBlocks();
    ValidSwapReversedIndices();
    DoubleSwap();
    BlockSizeOne();
    U16_Blocks_ValidSwap();
    U16_Blocks_OutOfBounds();
    U32_Blocks_ValidSwap();
    U32_Blocks_MultipleSwaps();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_Blocks_ValidSwap();
    U64_Blocks_OutOfBounds();
#endif
    Struct_Blocks_ValidSwap();
    Struct_Blocks_OutOfBounds();
    LargeBuffer();
    BoundarySwap();
    AllSameBlocks();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}