/**
 * @file kdGenMemOpsReverseBlocksBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsReverseBlocksBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsReverseBlocksBound function test"
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
    status = GenMemOpsReverseBlocksBound(null, USIZE_C(16), USIZE_C(0), USIZE_C(16), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ZeroBaseSize(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ZeroBaseSize -> ");

    /* base_sz is zero -> failure (caught by begin_idx >= base_sz when begin_idx >= 0) */
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(0), USIZE_C(0), USIZE_C(4), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ZeroBlockSize(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ZeroBlockSize -> ");

    /* block_sz is zero -> failure */
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), USIZE_C(0));
    assert(status == RESULT_FAILURE);

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
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(15), USIZE_C(0), USIZE_C(12), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_sz=17, block_sz=2: 17 % 2 = 1, not aligned */
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(17), USIZE_C(0), USIZE_C(16), USIZE_C(2));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
BeginIndexMisaligned(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BeginIndexMisaligned -> ");

    /* begin_idx not aligned to block_sz -> failure */
    /* begin_idx=5, block_sz=4: 5 % 4 = 1, not aligned */
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(16), USIZE_C(5), USIZE_C(8), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* begin_idx=3, block_sz=2: 3 % 2 = 1, not aligned */
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(16), USIZE_C(3), USIZE_C(8), USIZE_C(2));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ZeroByteCount(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ZeroByteCount -> ");

    /* byte_count is zero -> failure (!byte_count check) */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(16), USIZE_C(0), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
BaseSizeLessThanBlockSize(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BaseSizeLessThanBlockSize -> ");

    /* base_sz < block_sz -> fails alignment check (base_sz % block_sz != 0 when base_sz < block_sz) */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* base_sz=2, block_sz=4: 2 % 4 = 2, not aligned -> failure */
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(2), USIZE_C(0), USIZE_C(2), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_sz=3, block_sz=4: 3 % 4 = 3, not aligned -> failure */
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(3), USIZE_C(0), USIZE_C(3), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_sz=1, block_sz=2: 1 % 2 = 1, not aligned -> failure */
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(1), USIZE_C(0), USIZE_C(1), USIZE_C(2));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
BeginIndexOutOfBounds(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BeginIndexOutOfBounds -> ");

    /* begin_idx >= base_sz -> failure */
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(16), USIZE_C(16), USIZE_C(4), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(16), USIZE_C(20), USIZE_C(4), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ExactFit(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ExactFit -> ");

    /* Init: 0x00 ... 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Reverse entire buffer: begin_idx=0, byte_count=16, block_sz=4 */
    /* 4 blocks: [0-3], [4-7], [8-11], [12-15] */
    /* Expected: [12-15], [8-11], [4-7], [0-3] */
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Verify first block (now contains last block) */
    assert(buf[0] == U8_C(0x0C));
    assert(buf[1] == U8_C(0x0D));
    assert(buf[2] == U8_C(0x0E));
    assert(buf[3] == U8_C(0x0F));

    /* Verify last block (now contains first block) */
    assert(buf[12] == U8_C(0x00));
    assert(buf[13] == U8_C(0x01));
    assert(buf[14] == U8_C(0x02));
    assert(buf[15] == U8_C(0x03));

    printf("PASSED\n");
}


void
ByteCountClamping(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ByteCountClamping -> ");

    /* Init: 0x00 .. 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Request: Start 10, Count 100, Block 2.
     * Clamping: Available = 16 - 10 = 6 bytes.
     * Count becomes 6.
     * Blocks: 3 blocks of size 2 at indices [10,11], [12,13], [14,15].
     * Reverse them: [14,15], [12,13], [10,11].
     */
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(16), USIZE_C(10), USIZE_C(100), USIZE_C(2));
    assert(status == RESULT_SUCCESS);

    /* Verify pre-range untouched */
    assert(buf[9] == U8_C(0x09));

    /* Verify range reversed */
    /* Index 10,11 should hold old 14,15 (0x0E, 0x0F) */
    assert(buf[10] == U8_C(0x0E));
    assert(buf[11] == U8_C(0x0F));

    /* Index 12,13 should hold old 12,13 (0x0C, 0x0D) - Middle block stays */
    assert(buf[12] == U8_C(0x0C));
    assert(buf[13] == U8_C(0x0D));

    /* Index 14,15 should hold old 10,11 (0x0A, 0x0B) */
    assert(buf[14] == U8_C(0x0A));
    assert(buf[15] == U8_C(0x0B));

    printf("PASSED\n");
}


void
MiddleRegion_BlockSize2(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "MiddleRegion_BlockSize2 -> ");

    /* Init: 0x00 ... 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Reverse middle: begin_idx=4, byte_count=8, block_sz=2 */
    /* Region: indices 4-11 */
    /* Blocks: [4,5], [6,7], [8,9], [10,11] */
    /* Expected: [10,11], [8,9], [6,7], [4,5] */
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(16), USIZE_C(4), USIZE_C(8), USIZE_C(2));
    assert(status == RESULT_SUCCESS);

    /* Verify pre-range untouched */
    assert(buf[3] == U8_C(0x03));

    /* Verify reversed range */
    assert(buf[4] == U8_C(0x0A));
    assert(buf[5] == U8_C(0x0B));
    assert(buf[6] == U8_C(0x08));
    assert(buf[7] == U8_C(0x09));
    assert(buf[8] == U8_C(0x06));
    assert(buf[9] == U8_C(0x07));
    assert(buf[10] == U8_C(0x04));
    assert(buf[11] == U8_C(0x05));

    /* Verify post-range untouched */
    assert(buf[12] == U8_C(0x0C));

    printf("PASSED\n");
}


void
MiddleRegion_BlockSize4(void)
{
    u8   buf[20];
    bool status;

    printf(LOG_PREFIX_CSTR "MiddleRegion_BlockSize4 -> ");

    /* Init: 0x00 ... 0x13 */
    kdi_FillSeq(buf, USIZE_C(20), U8_C(0x00));

    /* Reverse middle: begin_idx=4, byte_count=12, block_sz=4 */
    /* Region: indices 4-15 */
    /* Blocks: [4-7], [8-11], [12-15] */
    /* Expected: [12-15], [8-11], [4-7] */
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(20), USIZE_C(4), USIZE_C(12), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Verify pre-range */
    assert(buf[3] == U8_C(0x03));

    /* Verify reversed blocks */
    assert(buf[4] == U8_C(0x0C));
    assert(buf[7] == U8_C(0x0F));
    assert(buf[8] == U8_C(0x08));
    assert(buf[11] == U8_C(0x0B));
    assert(buf[12] == U8_C(0x04));
    assert(buf[15] == U8_C(0x07));

    /* Verify post-range */
    assert(buf[16] == U8_C(0x10));

    printf("PASSED\n");
}


void
SingleBlockRegion(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "SingleBlockRegion -> ");

    /* Init: 0x00 ... 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Reverse single block at index 4: begin_idx=4, byte_count=4, block_sz=4 */
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(16), USIZE_C(4), USIZE_C(4), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Single block reversal doesn't change anything */
    assert(buf[4] == U8_C(0x04));
    assert(buf[5] == U8_C(0x05));
    assert(buf[6] == U8_C(0x06));
    assert(buf[7] == U8_C(0x07));

    /* Verify neighbors untouched */
    assert(buf[3] == U8_C(0x03));
    assert(buf[8] == U8_C(0x08));

    printf("PASSED\n");
}


void
TwoBlockRegion(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "TwoBlockRegion -> ");

    /* Init: 0x00 ... 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Reverse two blocks: begin_idx=4, byte_count=8, block_sz=4 */
    /* Blocks: [4-7], [8-11] */
    /* Expected: [8-11], [4-7] */
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(16), USIZE_C(4), USIZE_C(8), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Verify blocks swapped */
    assert(buf[4] == U8_C(0x08));
    assert(buf[5] == U8_C(0x09));
    assert(buf[6] == U8_C(0x0A));
    assert(buf[7] == U8_C(0x0B));
    assert(buf[8] == U8_C(0x04));
    assert(buf[9] == U8_C(0x05));
    assert(buf[10] == U8_C(0x06));
    assert(buf[11] == U8_C(0x07));

    /* Verify neighbors untouched */
    assert(buf[3] == U8_C(0x03));
    assert(buf[12] == U8_C(0x0C));

    printf("PASSED\n");
}


void
BeginningRegion(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BeginningRegion -> ");

    /* Init: 0x00 ... 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Reverse first 8 bytes: begin_idx=0, byte_count=8, block_sz=2 */
    /* Blocks: [0,1], [2,3], [4,5], [6,7] */
    /* Expected: [6,7], [4,5], [2,3], [0,1] */
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(16), USIZE_C(0), USIZE_C(8), USIZE_C(2));
    assert(status == RESULT_SUCCESS);

    /* Verify reversed blocks */
    assert(buf[0] == U8_C(0x06));
    assert(buf[1] == U8_C(0x07));
    assert(buf[2] == U8_C(0x04));
    assert(buf[3] == U8_C(0x05));
    assert(buf[4] == U8_C(0x02));
    assert(buf[5] == U8_C(0x03));
    assert(buf[6] == U8_C(0x00));
    assert(buf[7] == U8_C(0x01));

    /* Verify rest untouched */
    assert(buf[8] == U8_C(0x08));
    assert(buf[15] == U8_C(0x0F));

    printf("PASSED\n");
}


void
EndRegion(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "EndRegion -> ");

    /* Init: 0x00 ... 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Reverse last 8 bytes: begin_idx=8, byte_count=8, block_sz=2 */
    /* Blocks: [8,9], [10,11], [12,13], [14,15] */
    /* Expected: [14,15], [12,13], [10,11], [8,9] */
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(16), USIZE_C(8), USIZE_C(8), USIZE_C(2));
    assert(status == RESULT_SUCCESS);

    /* Verify beginning untouched */
    assert(buf[7] == U8_C(0x07));

    /* Verify reversed blocks */
    assert(buf[8] == U8_C(0x0E));
    assert(buf[9] == U8_C(0x0F));
    assert(buf[10] == U8_C(0x0C));
    assert(buf[11] == U8_C(0x0D));
    assert(buf[12] == U8_C(0x0A));
    assert(buf[13] == U8_C(0x0B));
    assert(buf[14] == U8_C(0x08));
    assert(buf[15] == U8_C(0x09));

    printf("PASSED\n");
}


void
BlockSizeOne(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BlockSizeOne -> ");

    /* Init: 0x00 ... 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Block size 1 = byte reverse for the region */
    /* begin_idx=4, byte_count=8, block_sz=1 */
    /* Expected: indices 4-11 reversed */
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(16), USIZE_C(4), USIZE_C(8), USIZE_C(1));
    assert(status == RESULT_SUCCESS);

    /* Verify pre-range */
    assert(buf[3] == U8_C(0x03));

    /* Verify reversed region */
    assert(buf[4] == U8_C(0x0B));
    assert(buf[5] == U8_C(0x0A));
    assert(buf[6] == U8_C(0x09));
    assert(buf[7] == U8_C(0x08));
    assert(buf[8] == U8_C(0x07));
    assert(buf[9] == U8_C(0x06));
    assert(buf[10] == U8_C(0x05));
    assert(buf[11] == U8_C(0x04));

    /* Verify post-range */
    assert(buf[12] == U8_C(0x0C));

    printf("PASSED\n");
}


void
U16_Blocks_RangeReverse(void)
{
    u16  buf[8];
    bool status;

    printf(LOG_PREFIX_CSTR "U16_Blocks_RangeReverse -> ");

    /* Init: 0, 1, 2, 3, 4, 5, 6, 7 */
    buf[0] = U16_C(0);
    buf[1] = U16_C(1);
    buf[2] = U16_C(2);
    buf[3] = U16_C(3);
    buf[4] = U16_C(4);
    buf[5] = U16_C(5);
    buf[6] = U16_C(6);
    buf[7] = U16_C(7);

    /* Reverse middle 4 blocks: begin_idx=2*sizeof(u16), byte_count=4*sizeof(u16), block_sz=sizeof(u16) */
    /* Elements 2, 3, 4, 5 -> 5, 4, 3, 2 */
    /* Expected: 0, 1, 5, 4, 3, 2, 6, 7 */
    status = GenMemOpsReverseBlocksBound(buf, sizeof(buf), USIZE_C(2) * sizeof(u16), USIZE_C(4) * sizeof(u16), sizeof(u16));
    assert(status == RESULT_SUCCESS);

    assert(buf[0] == U16_C(0));
    assert(buf[1] == U16_C(1));
    assert(buf[2] == U16_C(5));
    assert(buf[3] == U16_C(4));
    assert(buf[4] == U16_C(3));
    assert(buf[5] == U16_C(2));
    assert(buf[6] == U16_C(6));
    assert(buf[7] == U16_C(7));

    printf("PASSED\n");
}


void
U32_Blocks_RangeReverse(void)
{
    u32  buf[6];
    bool status;

    printf(LOG_PREFIX_CSTR "U32_Blocks_RangeReverse -> ");

    /* Init: 10, 20, 30, 40, 50, 60 */
    buf[0] = U32_C(10);
    buf[1] = U32_C(20);
    buf[2] = U32_C(30);
    buf[3] = U32_C(40);
    buf[4] = U32_C(50);
    buf[5] = U32_C(60);

    /* Reverse middle 3 blocks: begin_idx=1*sizeof(u32), byte_count=3*sizeof(u32), block_sz=sizeof(u32) */
    /* Elements 1, 2, 3 -> 40, 30, 20 */
    /* Expected: 10, 40, 30, 20, 50, 60 */
    status = GenMemOpsReverseBlocksBound(buf, sizeof(buf), USIZE_C(1) * sizeof(u32), USIZE_C(3) * sizeof(u32), sizeof(u32));
    assert(status == RESULT_SUCCESS);

    assert(buf[0] == U32_C(10));
    assert(buf[1] == U32_C(40));
    assert(buf[2] == U32_C(30));
    assert(buf[3] == U32_C(20));
    assert(buf[4] == U32_C(50));
    assert(buf[5] == U32_C(60));

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_Blocks_RangeReverse(void)
{
    u64  buf[8];
    bool status;

    printf(LOG_PREFIX_CSTR "U64_Blocks_RangeReverse -> ");

    /* Init: 0, 10, 20, 30, 40, 50, 60, 70 */
    buf[0] = U64_C(0);
    buf[1] = U64_C(10);
    buf[2] = U64_C(20);
    buf[3] = U64_C(30);
    buf[4] = U64_C(40);
    buf[5] = U64_C(50);
    buf[6] = U64_C(60);
    buf[7] = U64_C(70);

    /* Reverse indices 2, 3, 4, 5 */
    /* Values: 20, 30, 40, 50 -> 50, 40, 30, 20 */
    /* Expected: 0, 10, 50, 40, 30, 20, 60, 70 */
    status = GenMemOpsReverseBlocksBound(buf, sizeof(buf), USIZE_C(2) * sizeof(u64), USIZE_C(4) * sizeof(u64), sizeof(u64));
    assert(status == RESULT_SUCCESS);

    assert(buf[0] == U64_C(0));
    assert(buf[1] == U64_C(10));
    assert(buf[2] == U64_C(50));
    assert(buf[3] == U64_C(40));
    assert(buf[4] == U64_C(30));
    assert(buf[5] == U64_C(20));
    assert(buf[6] == U64_C(60));
    assert(buf[7] == U64_C(70));

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
Struct_Blocks_RangeReverse(void)
{
    kdi_SmallStruct buf[5];
    bool            status;

    printf(LOG_PREFIX_CSTR "Struct_Blocks_RangeReverse -> ");

    /* Init: S0, S1, S2, S3, S4 */
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
    buf[4].a = U32_C(5);
    buf[4].b = U32_C(50);
    buf[4].c = U8_C(70);

    /* Reverse first 3 structs: begin_idx=0, byte_count=3*sizeof(struct), block_sz=sizeof(struct) */
    /* S0, S1, S2 -> S2, S1, S0 */
    /* Expected: S2, S1, S0, S3, S4 */
    status = GenMemOpsReverseBlocksBound(buf, sizeof(buf), USIZE_C(0), USIZE_C(3) * sizeof(kdi_SmallStruct), sizeof(kdi_SmallStruct));
    assert(status == RESULT_SUCCESS);

    assert(buf[0].a == U32_C(3) && buf[0].b == U32_C(30) && buf[0].c == U8_C(50));
    assert(buf[1].a == U32_C(2) && buf[1].b == U32_C(20) && buf[1].c == U8_C(200));
    assert(buf[2].a == U32_C(1) && buf[2].b == U32_C(10) && buf[2].c == U8_C(100));
    assert(buf[3].a == U32_C(4) && buf[3].b == U32_C(40) && buf[3].c == U8_C(60));
    assert(buf[4].a == U32_C(5) && buf[4].b == U32_C(50) && buf[4].c == U8_C(70));

    printf("PASSED\n");
}


void
RemainderIgnored_InRange(void)
{
    u8   buf[20];
    bool status;

    printf(LOG_PREFIX_CSTR "RemainderIgnored_InRange -> ");

    /* Init: 0x00 ... 0x13 */
    kdi_FillSeq(buf, USIZE_C(20), U8_C(0x00));

    /* begin_idx=4, byte_count=10, block_sz=4 */
    /* Range: indices 4-13 (10 bytes) */
    /* Blocks: [4-7], [8-11] (2 complete blocks) */
    /* Remainder: [12-13] (2 bytes) */
    /* Expected: [8-11], [4-7], [12-13] untouched */
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(20), USIZE_C(4), USIZE_C(10), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Verify pre-range */
    assert(buf[3] == U8_C(0x03));

    /* Verify first block (now contains second block) */
    assert(buf[4] == U8_C(0x08));
    assert(buf[5] == U8_C(0x09));
    assert(buf[6] == U8_C(0x0A));
    assert(buf[7] == U8_C(0x0B));

    /* Verify second block (now contains first block) */
    assert(buf[8] == U8_C(0x04));
    assert(buf[9] == U8_C(0x05));
    assert(buf[10] == U8_C(0x06));
    assert(buf[11] == U8_C(0x07));

    /* Verify remainder untouched */
    assert(buf[12] == U8_C(0x0C));
    assert(buf[13] == U8_C(0x0D));

    /* Verify post-range */
    assert(buf[14] == U8_C(0x0E));

    printf("PASSED\n");
}


void
RemainderIgnored_ThreeBytes(void)
{
    u8   buf[20];
    bool status;

    printf(LOG_PREFIX_CSTR "RemainderIgnored_ThreeBytes -> ");

    /* Init: 0x00 ... 0x13 */
    kdi_FillSeq(buf, USIZE_C(20), U8_C(0x00));

    /* begin_idx=0, byte_count=11, block_sz=4 */
    /* Blocks: [0-3], [4-7] (2 complete blocks) */
    /* Remainder: [8-10] (3 bytes) */
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(20), USIZE_C(0), USIZE_C(11), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Verify blocks swapped */
    assert(buf[0] == U8_C(0x04));
    assert(buf[4] == U8_C(0x00));

    /* Verify remainder untouched */
    assert(buf[8] == U8_C(0x08));
    assert(buf[9] == U8_C(0x09));
    assert(buf[10] == U8_C(0x0A));

    /* Verify post-range */
    assert(buf[11] == U8_C(0x0B));

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    u8    buf[200];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    /* Init: 0..199 (values wrap in u8) */
    kdi_FillSeq(buf, USIZE_C(200), U8_C(0));

    /* Reverse middle section: begin_idx=48, byte_count=100, block_sz=4 */
    /* Range: indices 48-147 (100 bytes) */
    /* 25 blocks of size 4 */
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(200), USIZE_C(48), USIZE_C(100), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Verify pre-range untouched */
    for (i = USIZE_C(0); i < USIZE_C(48); ++i)
    {
        assert(buf[i] == (u8)i);
    }

    /* Verify first block in range (now contains last block) */
    assert(buf[48] == U8_C(144));
    assert(buf[49] == U8_C(145));
    assert(buf[50] == U8_C(146));
    assert(buf[51] == U8_C(147));

    /* Verify last block in range (now contains first block) */
    assert(buf[144] == U8_C(48));
    assert(buf[145] == U8_C(49));
    assert(buf[146] == U8_C(50));
    assert(buf[147] == U8_C(51));

    /* Verify post-range untouched */
    for (i = USIZE_C(148); i < USIZE_C(200); ++i)
    {
        assert(buf[i] == (u8)i);
    }

    printf("PASSED\n");
}


void
DoubleReverse(void)
{
    u8    buf[32];
    u8    original[32];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "DoubleReverse -> ");

    /* Init: 0x00 ... 0x1F */
    kdi_FillSeq(buf, USIZE_C(32), U8_C(0x00));

    /* Keep copy of original */
    for (i = USIZE_C(0); i < USIZE_C(32); ++i)
    {
        original[i] = buf[i];
    }

    /* Reverse middle region once */
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(32), USIZE_C(8), USIZE_C(16), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Reverse again - should restore */
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(32), USIZE_C(8), USIZE_C(16), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Verify restored to original */
    for (i = USIZE_C(0); i < USIZE_C(32); ++i)
    {
        assert(buf[i] == original[i]);
    }

    printf("PASSED\n");
}


void
AllBlocksSameValue(void)
{
    u32   buf[16];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "AllBlocksSameValue -> ");

    /* Fill all blocks with same value */
    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        buf[i] = U32_C(0xDEADBEEF);
    }

    /* Reverse a region */
    status = GenMemOpsReverseBlocksBound(buf, sizeof(buf), USIZE_C(4) * sizeof(u32), USIZE_C(8) * sizeof(u32), sizeof(u32));
    assert(status == RESULT_SUCCESS);

    /* All values should still be the same */
    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        assert(buf[i] == U32_C(0xDEADBEEF));
    }

    printf("PASSED\n");
}


void
BlockSizeExceedsByteCount(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BlockSizeExceedsByteCount -> ");

    /* Init: 0x00 ... 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* block_sz > byte_count -> 0 blocks -> failure, nothing changes */
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(16), USIZE_C(4), USIZE_C(4), USIZE_C(8));
    assert(status == RESULT_FAILURE);

    /* Buffer should be unchanged */
    assert(buf[4] == U8_C(0x04));
    assert(buf[5] == U8_C(0x05));
    assert(buf[6] == U8_C(0x06));
    assert(buf[7] == U8_C(0x07));

    printf("PASSED\n");
}


void
AdjacentRegions(void)
{
    u8   buf[32];
    bool status;

    printf(LOG_PREFIX_CSTR "AdjacentRegions -> ");

    /* Init: 0x00 ... 0x1F */
    kdi_FillSeq(buf, USIZE_C(32), U8_C(0x00));

    /* Reverse first half: begin_idx=0, byte_count=16, block_sz=4 */
    /* Blocks: [0-3], [4-7], [8-11], [12-15] */
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(32), USIZE_C(0), USIZE_C(16), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Reverse second half: begin_idx=16, byte_count=16, block_sz=4 */
    /* Blocks: [16-19], [20-23], [24-27], [28-31] */
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(32), USIZE_C(16), USIZE_C(16), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Verify first half reversed */
    assert(buf[0] == U8_C(0x0C));
    assert(buf[4] == U8_C(0x08));
    assert(buf[8] == U8_C(0x04));
    assert(buf[12] == U8_C(0x00));

    /* Verify second half reversed */
    assert(buf[16] == U8_C(0x1C));
    assert(buf[20] == U8_C(0x18));
    assert(buf[24] == U8_C(0x14));
    assert(buf[28] == U8_C(0x10));

    printf("PASSED\n");
}


void
VeryLargeByteCount(void)
{
    u8   buf[32];
    bool status;

    printf(LOG_PREFIX_CSTR "VeryLargeByteCount -> ");

    /* Init: 0x00 ... 0x1F */
    kdi_FillSeq(buf, USIZE_C(32), U8_C(0x00));

    /* Request huge byte_count - should clamp to available space */
    /* begin_idx=16, byte_count=1000, block_sz=4 */
    /* Available: 32 - 16 = 16 bytes */
    /* 4 blocks: [16-19], [20-23], [24-27], [28-31] */
    status = GenMemOpsReverseBlocksBound(buf, USIZE_C(32), USIZE_C(16), USIZE_C(1000), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Verify beginning untouched */
    assert(buf[15] == U8_C(0x0F));

    /* Verify reversed region */
    assert(buf[16] == U8_C(0x1C));
    assert(buf[17] == U8_C(0x1D));
    assert(buf[18] == U8_C(0x1E));
    assert(buf[19] == U8_C(0x1F));
    assert(buf[28] == U8_C(0x10));
    assert(buf[29] == U8_C(0x11));
    assert(buf[30] == U8_C(0x12));
    assert(buf[31] == U8_C(0x13));

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
    BeginIndexMisaligned();
    BaseSizeLessThanBlockSize();
    ZeroByteCount();
    BeginIndexOutOfBounds();
    ExactFit();
    ByteCountClamping();
    MiddleRegion_BlockSize2();
    MiddleRegion_BlockSize4();
    SingleBlockRegion();
    TwoBlockRegion();
    BeginningRegion();
    EndRegion();
    BlockSizeOne();
    U16_Blocks_RangeReverse();
    U32_Blocks_RangeReverse();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_Blocks_RangeReverse();
#endif
    Struct_Blocks_RangeReverse();
    RemainderIgnored_InRange();
    RemainderIgnored_ThreeBytes();
    LargeBuffer();
    DoubleReverse();
    AllBlocksSameValue();
    BlockSizeExceedsByteCount();
    AdjacentRegions();
    VeryLargeByteCount();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
