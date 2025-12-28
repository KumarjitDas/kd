/**
 * @file kdGenMemOpsCountNotBlocks.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsCountNotBlocks function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsCountNotBlocks function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8    buf[16];
    u8    blk[4];
    usize count = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0x00));

    /* count pointer is null -> failure */
    status = kdGenMemOpsCountNotBlocks(null, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountNotBlocks(&count, null, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* block is null -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountNotBlocks(&count, buf, USIZE_C(16), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* ptr_sz is zero -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountNotBlocks(&count, buf, USIZE_C(0), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* block_sz is zero -> failure */
    count  = 55;
    status = kdGenMemOpsCountNotBlocks(&count, buf, USIZE_C(16), blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* ptr_sz not divisible by block_sz -> failure */
    count  = 55;
    status = kdGenMemOpsCountNotBlocks(&count, buf, USIZE_C(15), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* Valid arguments - all blocks match, so count NOT = 0 */
    count  = 55;
    status = kdGenMemOpsCountNotBlocks(&count, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    printf("PASSED\n");
}


void
CountNone(void)
{
    u8    buf[16];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountNone -> ");

    /* All blocks match the target block */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xAA));

    /* Count NOT matching blocks. All match, so count = 0. */
    status = kdGenMemOpsCountNotBlocks(&count, buf, USIZE_C(16), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    printf("PASSED\n");
}


void
CountAll(void)
{
    u8    buf[16];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountAll -> ");

    /* Buffer blocks are all 0x00, target is 0xFF - none match */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xFF));

    /* Count NOT matching. All 4 blocks are NOT 0xFF, count = 4 * 4 = 16. */
    status = kdGenMemOpsCountNotBlocks(&count, buf, USIZE_C(16), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

    printf("PASSED\n");
}


void
CountSingle(void)
{
    u8    buf[16];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountSingle -> ");

    /* All blocks are 0xAA except one */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xAA));

    /* Change second block (offset 4) to 0xFF */
    kdi_Fill_u8(buf + 4, USIZE_C(4), U8_C(0xFF));

    /* Count NOT 0xAA blocks. Only 1 block doesn't match. */
    status = kdGenMemOpsCountNotBlocks(&count, buf, USIZE_C(16), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(4));

    printf("PASSED\n");
}


void
CountMultiple(void)
{
    u8    buf[20];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountMultiple -> ");

    /* 5 blocks total */
    /* Block 0: [1,2,3,4] - Match */
    /* Block 1: [5,6,7,8] - No Match */
    /* Block 2: [1,2,3,4] - Match */
    /* Block 3: [9,A,B,C] - No Match */
    /* Block 4: [1,2,3,4] - Match */

    buf[0]  = 1;
    buf[1]  = 2;
    buf[2]  = 3;
    buf[3]  = 4;
    buf[4]  = 5;
    buf[5]  = 6;
    buf[6]  = 7;
    buf[7]  = 8;
    buf[8]  = 1;
    buf[9]  = 2;
    buf[10] = 3;
    buf[11] = 4;
    buf[12] = 9;
    buf[13] = 0xA;
    buf[14] = 0xB;
    buf[15] = 0xC;
    buf[16] = 1;
    buf[17] = 2;
    buf[18] = 3;
    buf[19] = 4;

    blk[0]  = 1;
    blk[1]  = 2;
    blk[2]  = 3;
    blk[3]  = 4;

    /* Count NOT [1,2,3,4]. 2 blocks don't match (1 and 3). */
    status  = kdGenMemOpsCountNotBlocks(&count, buf, USIZE_C(20), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(8));

    printf("PASSED\n");
}


void
SingleByteBlocks(void)
{
    u8    buf[10];
    u8    blk = 0x42;
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleByteBlocks -> ");

    /* Pattern: 0x42, 0x99, 0x42, 0x42, 0x99, 0x42, 0x99, 0x42, 0x42, 0x99 */
    buf[0] = 0x42;
    buf[1] = 0x99;
    buf[2] = 0x42;
    buf[3] = 0x42;
    buf[4] = 0x99;
    buf[5] = 0x42;
    buf[6] = 0x99;
    buf[7] = 0x42;
    buf[8] = 0x42;
    buf[9] = 0x99;

    /* Count NOT 0x42. 4 bytes are 0x99 (NOT 0x42). */
    status = kdGenMemOpsCountNotBlocks(&count, buf, USIZE_C(10), &blk, USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(4));

    printf("PASSED\n");
}


void
U16_CountNotBlocks(void)
{
    u16   buf[6];
    u16   blk = 100;
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "U16_CountNotBlocks -> ");

    /* Blocks: 100, 200, 100, 300, 100, 400 */
    buf[0] = 100;
    buf[1] = 200;
    buf[2] = 100;
    buf[3] = 300;
    buf[4] = 100;
    buf[5] = 400;

    /* Count NOT 100. 3 blocks don't match (200, 300, 400). */
    status = kdGenMemOpsCountNotBlocks(&count, buf, sizeof(buf), &blk, sizeof(u16));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(6));

    printf("PASSED\n");
}


void
U16_MultiByteBlocks(void)
{
    u16   buf[8];
    u16   blk[2];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "U16_MultiByteBlocks -> ");

    /* 4 blocks of 2 u16s each */
    /* Block 0: [10, 20] - Match */
    /* Block 1: [30, 40] - No Match */
    /* Block 2: [10, 20] - Match */
    /* Block 3: [50, 60] - No Match */

    buf[0] = 10;
    buf[1] = 20;
    buf[2] = 30;
    buf[3] = 40;
    buf[4] = 10;
    buf[5] = 20;
    buf[6] = 50;
    buf[7] = 60;

    blk[0] = 10;
    blk[1] = 20;

    /* Count NOT [10, 20]. 2 blocks don't match. */
    status = kdGenMemOpsCountNotBlocks(&count, buf, sizeof(buf), blk, sizeof(u16) * 2);

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(8));

    printf("PASSED\n");
}


void
U32_CountNotBlocks(void)
{
    u32   buf[4];
    u32   blk = 0xAAAAAAAA;
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_CountNotBlocks -> ");

    /* Blocks: A, B, A, C */
    buf[0] = 0xAAAAAAAA;
    buf[1] = 0xBBBBBBBB;
    buf[2] = 0xAAAAAAAA;
    buf[3] = 0xCCCCCCCC;

    /* Count NOT A. 2 blocks don't match (B and C). */
    status = kdGenMemOpsCountNotBlocks(&count, buf, sizeof(buf), &blk, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(8));

    printf("PASSED\n");
}


void
U32_MultiBlocks(void)
{
    u32   buf[6];
    u32   blk[2];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_MultiBlocks -> ");

    /* 3 blocks of 2 u32s each */
    /* Block 0: [10, 20] - Match */
    /* Block 1: [99, 99] - No Match */
    /* Block 2: [10, 20] - Match */

    buf[0] = 10;
    buf[1] = 20;
    buf[2] = 99;
    buf[3] = 99;
    buf[4] = 10;
    buf[5] = 20;

    blk[0] = 10;
    blk[1] = 20;

    /* Count NOT [10, 20]. 1 block doesn't match. */
    status = kdGenMemOpsCountNotBlocks(&count, buf, sizeof(buf), blk, sizeof(u32) * 2);

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(8));

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_CountNotBlocks(void)
{
    u64   buf[4];
    u64   blk = U64_C(0xAAAAAAAAAAAAAAAA);
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "U64_CountNotBlocks -> ");

    /* Blocks: A, B, A, C */
    buf[0] = U64_C(0xAAAAAAAAAAAAAAAA);
    buf[1] = U64_C(0xBBBBBBBBBBBBBBBB);
    buf[2] = U64_C(0xAAAAAAAAAAAAAAAA);
    buf[3] = U64_C(0xCCCCCCCCCCCCCCCC);

    /* Count NOT A. 2 blocks don't match. */
    status = kdGenMemOpsCountNotBlocks(&count, buf, sizeof(buf), &blk, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

    printf("PASSED\n");
}


void
U64_MultiBlocks(void)
{
    u64   buf[6];
    u64   blk[2];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "U64_MultiBlocks -> ");

    /* 3 blocks of 2 u64s each */
    buf[0] = U64_C(0x1111111111111111);
    buf[1] = U64_C(0x2222222222222222);
    buf[2] = U64_C(0x9999999999999999);
    buf[3] = U64_C(0x9999999999999999);
    buf[4] = U64_C(0x1111111111111111);
    buf[5] = U64_C(0x2222222222222222);

    blk[0] = U64_C(0x1111111111111111);
    blk[1] = U64_C(0x2222222222222222);

    /* Count NOT matching. 1 block doesn't match. */
    status = kdGenMemOpsCountNotBlocks(&count, buf, sizeof(buf), blk, sizeof(u64) * 2);

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

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
Struct_CountNotBlocks(void)
{
    kdi_LargeStruct buf[5];
    kdi_LargeStruct blk;
    usize           count;
    bool            status;

    printf(LOG_PREFIX_CSTR "Struct_CountNotBlocks -> ");

    /* Target block */
    blk.a = 1;
    blk.b = 2;
    blk.c = 3;
    blk.d = 4;

    /* Buffer: A, B, A, C, A */
    buf[0]   = blk;
    buf[1].a = 99;
    buf[1].b = 99;
    buf[1].c = 99;
    buf[1].d = 99;
    buf[2]   = blk;
    buf[3].a = 88;
    buf[3].b = 88;
    buf[3].c = 88;
    buf[3].d = 88;
    buf[4]   = blk;

    /* Count NOT A. 2 blocks don't match (B and C). */
    status   = kdGenMemOpsCountNotBlocks(&count, buf, sizeof(buf), &blk, sizeof(kdi_LargeStruct));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(48));

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
    status = kdGenMemOpsCountNotBlocks(&count, buf, USIZE_C(1000), blk, USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    /* Modify every 10th block (indices 0, 100, 200, ..., 900) */
    for (i = 0; i < 1000; i += 100)
    {
        buf[i] = 0xFF;
    }

    /* Now 10 blocks are modified, so count NOT = 10 * 10 = 100. */
    status = kdGenMemOpsCountNotBlocks(&count, buf, USIZE_C(1000), blk, USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(100));

    printf("PASSED\n");
}


void
ConsecutiveMatches(void)
{
    u8    buf[32];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ConsecutiveMatches -> ");

    /* First half: [1,2,3,4], second half: [5,6,7,8] */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));
    kdi_Fill_u8(buf + 16, USIZE_C(16), U8_C(0xFF));

    buf[0] = 1;
    buf[1] = 2;
    buf[2] = 3;
    buf[3] = 4;
    buf[4] = 1;
    buf[5] = 2;
    buf[6] = 3;
    buf[7] = 4;
    buf[8] = 1;
    buf[9] = 2;
    buf[10] = 3;
    buf[11] = 4;
    buf[12] = 1;
    buf[13] = 2;
    buf[14] = 3;
    buf[15] = 4;

    blk[0] = 1;
    blk[1] = 2;
    blk[2] = 3;
    blk[3] = 4;

    /* Count NOT [1,2,3,4]. Last 4 blocks don't match. */
    status = kdGenMemOpsCountNotBlocks(&count, buf, USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

    printf("PASSED\n");
}


void
ZeroBlocks(void)
{
    u8    buf[20];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ZeroBlocks -> ");

    /* All zero blocks */
    kdi_Fill_u8(buf, USIZE_C(20), U8_C(0x00));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0x00));

    /* Count NOT zero blocks. All are zero, so count = 0. */
    status = kdGenMemOpsCountNotBlocks(&count, buf, USIZE_C(20), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    printf("PASSED\n");
}


void
AlternatingBlocks(void)
{
    u8    buf[24];
    u8    blk[3];
    usize count;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "AlternatingBlocks -> ");

    /* Pattern: [A,A,A], [B,B,B], [A,A,A], [B,B,B], ... */
    for (i = 0; i < 8; ++i)
    {
        buf[i * 3 + 0] = (i % 2 == 0) ? U8_C(0xAA) : U8_C(0xBB);
        buf[i * 3 + 1] = (i % 2 == 0) ? U8_C(0xAA) : U8_C(0xBB);
        buf[i * 3 + 2] = (i % 2 == 0) ? U8_C(0xAA) : U8_C(0xBB);
    }

    blk[0] = U8_C(0xAA);
    blk[1] = U8_C(0xAA);
    blk[2] = U8_C(0xAA);

    /* Count NOT [A,A,A]. Half are [B,B,B], so 4 blocks. */
    status = kdGenMemOpsCountNotBlocks(&count, buf, USIZE_C(24), blk, USIZE_C(3));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(12));

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
    status = kdGenMemOpsCountNotBlocks(&count, buf, USIZE_C(33), blk, USIZE_C(3));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    /* Change one block */
    kdi_Fill_u8(buf + 15, USIZE_C(3), U8_C(0x88));

    status = kdGenMemOpsCountNotBlocks(&count, buf, USIZE_C(33), blk, USIZE_C(3));

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
    status = kdGenMemOpsCountNotBlocks(&count, buf, USIZE_C(100), blk, USIZE_C(5));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    /* Change every other block */
    for (i = 0; i < 100; i += 10)
    {
        buf[i] = 0xFF;
    }

    /* Now 10 blocks don't match. */
    status = kdGenMemOpsCountNotBlocks(&count, buf, USIZE_C(100), blk, USIZE_C(5));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(50));

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
    status = kdGenMemOpsCountNotBlocks(&count, buf, USIZE_C(256), blk, USIZE_C(32));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    /* Change blocks at offsets 64 and 192 */
    kdi_Fill_u8(buf + 64, USIZE_C(32), U8_C(0xAA));
    kdi_Fill_u8(buf + 192, USIZE_C(32), U8_C(0xBB));

    /* 2 blocks don't match. */
    status = kdGenMemOpsCountNotBlocks(&count, buf, USIZE_C(256), blk, USIZE_C(32));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(64));

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
    CountMultiple();
    SingleByteBlocks();
    U16_CountNotBlocks();
    U16_MultiByteBlocks();
    U32_CountNotBlocks();
    U32_MultiBlocks();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_CountNotBlocks();
    U64_MultiBlocks();
#endif
    Struct_CountNotBlocks();
    LargeBuffer();
    ConsecutiveMatches();
    ZeroBlocks();
    AlternatingBlocks();
    OddSizes();
    SparseMatches();
    LargeBlockSize();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
