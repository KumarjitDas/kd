/**
 * @file kdGenMemOpsFindBlockIndex.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindBlockIndex function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindBlockIndex function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8    buf[16];
    u8    blk[4];
    usize idx = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0x00));

    /* idx pointer is null -> failure */
    status = kdGenMemOpsFindBlockIndex(null, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    idx    = 55;
    status = kdGenMemOpsFindBlockIndex(&idx, null, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    idx    = 55;
    status = kdGenMemOpsFindBlockIndex(&idx, buf, USIZE_C(16), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr_sz is zero -> failure */
    idx    = 55;
    status = kdGenMemOpsFindBlockIndex(&idx, buf, USIZE_C(0), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    idx    = 55;
    status = kdGenMemOpsFindBlockIndex(&idx, buf, USIZE_C(16), blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr_sz not divisible by block_sz -> failure */
    idx    = 55;
    status = kdGenMemOpsFindBlockIndex(&idx, buf, USIZE_C(15), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Valid arguments - found at offset 0 */
    idx    = 55;
    status = kdGenMemOpsFindBlockIndex(&idx, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    printf("PASSED\n");
}


void
FindNone(void)
{
    u8    buf[16];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNone -> ");

    /* Init: 0x00 */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Search for 0xFF block */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xFF));

    idx    = 999;
    status = kdGenMemOpsFindBlockIndex(&idx, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Search for block larger than buffer */
    idx    = 999;
    status = kdGenMemOpsFindBlockIndex(&idx, buf, USIZE_C(16), blk, USIZE_C(20));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
FindFirst(void)
{
    u8    buf[16];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindFirst -> ");

    /* Block Size: 4 */
    /* Blocks: [01,02,03,04], [00,00,00,00], [00,00,00,00], [00,00,00,00] */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Block 0 (Offset 0) */
    buf[0] = 0x01;
    buf[1] = 0x02;
    buf[2] = 0x03;
    buf[3] = 0x04;

    /* Search: [01,02,03,04] */
    blk[0] = 0x01;
    blk[1] = 0x02;
    blk[2] = 0x03;
    blk[3] = 0x04;

    status = kdGenMemOpsFindBlockIndex(&idx, buf, USIZE_C(16), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    printf("PASSED\n");
}


void
FindLast(void)
{
    u8    buf[16];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindLast -> ");

    /* Block Size: 4 */
    /* Blocks: [00,00,00,00], [00,00,00,00], [00,00,00,00], [01,02,03,04] */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Block 3 (Offset 12) */
    buf[12] = 0x01;
    buf[13] = 0x02;
    buf[14] = 0x03;
    buf[15] = 0x04;

    /* Search: [01,02,03,04] */
    blk[0]  = 0x01;
    blk[1]  = 0x02;
    blk[2]  = 0x03;
    blk[3]  = 0x04;

    status  = kdGenMemOpsFindBlockIndex(&idx, buf, USIZE_C(16), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(12));

    printf("PASSED\n");
}


void
FindMiddle(void)
{
    u8    buf[16];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindMiddle -> ");

    /* Block Size: 4 */
    /* Blocks: [00,00,00,00], [01,02,03,04], [00,00,00,00], [00,00,00,00] */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Block 1 (Offset 4) */
    buf[4] = 0x01;
    buf[5] = 0x02;
    buf[6] = 0x03;
    buf[7] = 0x04;

    /* Search: [01,02,03,04] */
    blk[0] = 0x01;
    blk[1] = 0x02;
    blk[2] = 0x03;
    blk[3] = 0x04;

    status = kdGenMemOpsFindBlockIndex(&idx, buf, USIZE_C(16), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(4));

    printf("PASSED\n");
}


void
FindMultiple(void)
{
    u8    buf[16];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindMultiple -> ");

    /* Block Size 4 */
    /* Buffer: [01,02,03,04], [00,00,00,00], [01,02,03,04], [00,00,00,00] */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    buf[0] = 0x01;
    buf[1] = 0x02;
    buf[2] = 0x03;
    buf[3] = 0x04; /* Block 0 */
    buf[8] = 0x01;
    buf[9] = 0x02;
    buf[10] = 0x03;
    buf[11] = 0x04; /* Block 2 */

    blk[0] = 0x01;
    blk[1] = 0x02;
    blk[2] = 0x03;
    blk[3] = 0x04;

    /* Should find FIRST occurrence (Block 0, Offset 0) */
    status = kdGenMemOpsFindBlockIndex(&idx, buf, USIZE_C(16), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    printf("PASSED\n");
}


void
UnalignedMatchFail(void)
{
    u8    buf[8];
    u8    blk[2];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "UnalignedMatchFail -> ");

    /* Buffer: 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 */
    buf[0] = 1;
    buf[1] = 2;
    buf[2] = 3;
    buf[3] = 4;
    buf[4] = 5;
    buf[5] = 6;
    buf[6] = 7;
    buf[7] = 8;

    /* Block Size: 2 */
    /* Block 0: [1, 2] */
    /* Block 1: [3, 4] */
    /* Block 2: [5, 6] */
    /* Block 3: [7, 8] */

    /* Search for: [2, 3] */
    /* Sequence exists at offset 1, but it crosses block boundaries. */
    blk[0] = 2;
    blk[1] = 3;

    status = kdGenMemOpsFindBlockIndex(&idx, buf, USIZE_C(8), blk, USIZE_C(2));

    /* Should fail because it is not aligned to a block boundary */
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SingleByteBlocks(void)
{
    u8    buf[10];
    u8    blk = 0x42;
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleByteBlocks -> ");

    /* Pattern: 0x00, 0x00, 0x42, 0x00, 0x42, 0x00, 0x00, 0x42, 0x00, 0x00 */
    kdi_Fill_u8(buf, USIZE_C(10), U8_C(0x00));
    buf[2] = 0x42;
    buf[4] = 0x42;
    buf[7] = 0x42;

    /* Find 0x42. Should return FIRST occurrence at offset 2. */
    status = kdGenMemOpsFindBlockIndex(&idx, buf, USIZE_C(10), &blk, USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(2));

    printf("PASSED\n");
}


void
U16_FindBlock(void)
{
    u16   buf[6];
    u16   blk = 300;
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U16_FindBlock -> ");

    /* Blocks: [100], [200], [300], [400], [300], [500] */
    buf[0] = 100;
    buf[1] = 200;
    buf[2] = 300;
    buf[3] = 400;
    buf[4] = 300;
    buf[5] = 500;

    /* Search 300 (First occurrence at index 2) */
    status = kdGenMemOpsFindBlockIndex(&idx, buf, sizeof(buf), &blk, sizeof(u16));

    assert(status == RESULT_SUCCESS);
    /* Index 2 * 2 bytes = Offset 4 */
    assert(idx == USIZE_C(4));

    printf("PASSED\n");
}


void
U16_MultiByteBlocks(void)
{
    u16   buf[8];
    u16   blk[2];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U16_MultiByteBlocks -> ");

    /* 4 blocks of 2 u16s each */
    /* Block 0: [10, 20] */
    /* Block 1: [30, 40] */
    /* Block 2: [10, 20] - Match */
    /* Block 3: [50, 60] */

    buf[0] = 99;
    buf[1] = 99;
    buf[2] = 30;
    buf[3] = 40;
    buf[4] = 10;
    buf[5] = 20;
    buf[6] = 50;
    buf[7] = 60;

    blk[0] = 10;
    blk[1] = 20;

    /* Should find [10, 20] at block 2, offset 8 */
    status = kdGenMemOpsFindBlockIndex(&idx, buf, sizeof(buf), blk, sizeof(u16) * 2);

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(8));

    printf("PASSED\n");
}


void
U32_FindBlock(void)
{
    u32   buf[5];
    u32   blk = 30;
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_FindBlock -> ");

    /* Blocks: [10], [20], [30], [40], [50] */
    buf[0] = 10;
    buf[1] = 20;
    buf[2] = 30;
    buf[3] = 40;
    buf[4] = 50;

    /* Search 30 (at index 2) */
    status = kdGenMemOpsFindBlockIndex(&idx, buf, sizeof(buf), &blk, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    /* Index 2 * 4 bytes = Offset 8 */
    assert(idx == USIZE_C(8));

    printf("PASSED\n");
}


void
U32_MultiBlocks(void)
{
    u32   buf[6];
    u32   blk[2];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_MultiBlocks -> ");

    /* 3 blocks of 2 u32s each */
    buf[0] = 88;
    buf[1] = 88;
    buf[2] = 10;
    buf[3] = 20;
    buf[4] = 99;
    buf[5] = 99;

    blk[0] = 10;
    blk[1] = 20;

    /* Should find [10, 20] at block 1, offset 8 */
    status = kdGenMemOpsFindBlockIndex(&idx, buf, sizeof(buf), blk, sizeof(u32) * 2);

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(8));

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_FindBlock(void)
{
    u64   buf[5];
    u64   blk = U64_C(0xBBBBBBBBBBBBBBBB);
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U64_FindBlock -> ");

    /* Blocks: A, B, C, B, D */
    buf[0] = U64_C(0xAAAAAAAAAAAAAAAA);
    buf[1] = U64_C(0xBBBBBBBBBBBBBBBB);
    buf[2] = U64_C(0xCCCCCCCCCCCCCCCC);
    buf[3] = U64_C(0xBBBBBBBBBBBBBBBB);
    buf[4] = U64_C(0xDDDDDDDDDDDDDDDD);

    /* Search B (First occurrence at index 1) */
    status = kdGenMemOpsFindBlockIndex(&idx, buf, sizeof(buf), &blk, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    /* Index 1 * 8 bytes = Offset 8 */
    assert(idx == USIZE_C(8));

    printf("PASSED\n");
}


void
U64_MultiBlocks(void)
{
    u64   buf[6];
    u64   blk[2];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U64_MultiBlocks -> ");

    /* 3 blocks of 2 u64s each */
    buf[0] = U64_C(0x9999999999999999);
    buf[1] = U64_C(0x9999999999999999);
    buf[2] = U64_C(0x1111111111111111);
    buf[3] = U64_C(0x2222222222222222);
    buf[4] = U64_C(0x8888888888888888);
    buf[5] = U64_C(0x8888888888888888);

    blk[0] = U64_C(0x1111111111111111);
    blk[1] = U64_C(0x2222222222222222);

    /* Should find at block 1, offset 16 */
    status = kdGenMemOpsFindBlockIndex(&idx, buf, sizeof(buf), blk, sizeof(u64) * 2);

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(16));

    printf("PASSED\n");
}
#endif


typedef struct kdi_SmallStruct
{
    u32 a;
    u16 b;
} kdi_SmallStruct;


typedef struct kdi_LargeStruct
{
    u64 a;
    u64 b;
    u32 c;
    u8  d;
} kdi_LargeStruct;


void
Struct_FindBlock(void)
{
    kdi_LargeStruct buf[5];
    kdi_LargeStruct blk;
    usize           idx;
    bool            status;

    printf(LOG_PREFIX_CSTR "Struct_FindBlock -> ");

    /* Target: S_TARGET */
    blk.a = 1;
    blk.b = 2;
    blk.c = 3;
    blk.d = 4;

    /* Buffer: S0, S1, S_TARGET, S3, S4 */
    buf[0].a = 99;
    buf[0].b = 99;
    buf[0].c = 99;
    buf[0].d = 99;

    buf[1].a = 88;
    buf[1].b = 88;
    buf[1].c = 88;
    buf[1].d = 88;

    buf[2]   = blk;

    buf[3].a = 77;
    buf[3].b = 77;
    buf[3].c = 77;
    buf[3].d = 77;

    buf[4].a = 66;
    buf[4].b = 66;
    buf[4].c = 66;
    buf[4].d = 66;

    status   = kdGenMemOpsFindBlockIndex(&idx, buf, sizeof(buf), &blk, sizeof(kdi_LargeStruct));

    assert(status == RESULT_SUCCESS);
    /* Index 2 * sizeof(struct) */
    assert(idx == sizeof(kdi_LargeStruct) * 2);

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    u8    buf[1000];
    u8    blk[10];
    usize idx;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    /* Pattern: 0, 1, 2, ..., 9 repeating */
    for (i = 0; i < 1000; ++i)
    {
        buf[i] = (u8)(i % 10);
    }

    /* Block Size: 10 */
    /* Blocks start at 0, 10, 20, ... */

    /* Search for Block 0 (Indices 0..9) */
    /* Values: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 */
    for (i = 0; i < 10; ++i)
    {
        blk[i] = (u8)i;
    }

    /* Should find at offset 0 */
    status = kdGenMemOpsFindBlockIndex(&idx, buf, USIZE_C(1000), blk, USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    /* Search for unaligned sequence (Indices 5..14) */
    /* Values: 5, 6, 7, 8, 9, 0, 1, 2, 3, 4 */
    /* This crosses from Block 0 to Block 1. Should fail. */
    for (i = 0; i < 10; ++i)
    {
        blk[i] = (u8)((i + 5) % 10);
    }

    status = kdGenMemOpsFindBlockIndex(&idx, buf, USIZE_C(1000), blk, USIZE_C(10));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
AllSameBlocks(void)
{
    u8    buf[20];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "AllSameBlocks -> ");

    /* All blocks are [0x77, 0x77, 0x77, 0x77] */
    kdi_Fill_u8(buf, USIZE_C(20), U8_C(0x77));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0x77));

    /* Should find at offset 0 (first block) */
    status = kdGenMemOpsFindBlockIndex(&idx, buf, USIZE_C(20), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    printf("PASSED\n");
}


void
ZeroBlocks(void)
{
    u8    buf[20];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "ZeroBlocks -> ");

    /* All blocks are [0x00, 0x00, 0x00, 0x00] */
    kdi_Fill_u8(buf, USIZE_C(20), U8_C(0x00));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0x00));

    /* Should find at offset 0 (first block) */
    status = kdGenMemOpsFindBlockIndex(&idx, buf, USIZE_C(20), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    printf("PASSED\n");
}


void
AlternatingBlocks(void)
{
    u8    buf[24];
    u8    blk[3];
    usize idx;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "AlternatingBlocks -> ");

    /* Pattern: [A,A,A], [B,B,B], [A,A,A], [B,B,B], ... */
    for (i = 0; i < 8; ++i)
    {
        kdi_Fill_u8(buf + i * 3, USIZE_C(3), (i % 2 == 0) ? U8_C(0xAA) : U8_C(0xBB));
    }

    /* Search for [A,A,A] */
    kdi_Fill_u8(blk, USIZE_C(3), U8_C(0xAA));

    /* Should find first occurrence at offset 0 */
    status = kdGenMemOpsFindBlockIndex(&idx, buf, USIZE_C(24), blk, USIZE_C(3));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    /* Search for [B,B,B] */
    kdi_Fill_u8(blk, USIZE_C(3), U8_C(0xBB));

    /* Should find first occurrence at offset 3 */
    status = kdGenMemOpsFindBlockIndex(&idx, buf, USIZE_C(24), blk, USIZE_C(3));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(3));

    printf("PASSED\n");
}


void
OddSizes(void)
{
    u8    buf[33];
    u8    blk[3];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "OddSizes -> ");

    /* 11 blocks of size 3 */
    kdi_Fill_u8(buf, USIZE_C(33), U8_C(0x77));

    /* Set block at offset 15 to different value */
    kdi_Fill_u8(buf + 15, USIZE_C(3), U8_C(0x88));

    /* Search for 0x88 block */
    kdi_Fill_u8(blk, USIZE_C(3), U8_C(0x88));

    status = kdGenMemOpsFindBlockIndex(&idx, buf, USIZE_C(33), blk, USIZE_C(3));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(15));

    printf("PASSED\n");
}


void
LargeBlockSize(void)
{
    u8    buf[256];
    u8    blk[32];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "LargeBlockSize -> ");

    /* 8 blocks of size 32 */
    kdi_Fill_u8(buf, USIZE_C(256), U8_C(0x55));

    /* Set block at offset 128 to different value */
    kdi_Fill_u8(buf + 128, USIZE_C(32), U8_C(0xAA));

    /* Search for 0xAA block */
    kdi_Fill_u8(blk, USIZE_C(32), U8_C(0xAA));

    status = kdGenMemOpsFindBlockIndex(&idx, buf, USIZE_C(256), blk, USIZE_C(32));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(128));

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
    FindMiddle();
    FindMultiple();
    UnalignedMatchFail();
    SingleByteBlocks();
    U16_FindBlock();
    U16_MultiByteBlocks();
    U32_FindBlock();
    U32_MultiBlocks();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_FindBlock();
    U64_MultiBlocks();
#endif
    Struct_FindBlock();
    LargeBuffer();
    AllSameBlocks();
    ZeroBlocks();
    AlternatingBlocks();
    OddSizes();
    LargeBlockSize();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}