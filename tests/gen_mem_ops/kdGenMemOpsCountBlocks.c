/**
 * @file kdGenMemOpsCountBlocks.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsCountBlocks function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsCountBlocks function test"
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
    status = kdGenMemOpsCountBlocks(null, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountBlocks(&count, null, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* block is null -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountBlocks(&count, buf, USIZE_C(16), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* ptr_sz is zero -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountBlocks(&count, buf, USIZE_C(0), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* block_sz is zero -> failure */
    count  = 55;
    status = kdGenMemOpsCountBlocks(&count, buf, USIZE_C(16), blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* ptr_sz not divisible by block_sz -> failure */
    count  = 55;
    status = kdGenMemOpsCountBlocks(&count, buf, USIZE_C(15), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* Valid arguments - 4 blocks of size 4 = count of 16 */
    count  = 55;
    status = kdGenMemOpsCountBlocks(&count, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

    printf("PASSED\n");
}


void
CountNone(void)
{
    u8    buf[16];
    u8    blk[2];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountNone -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));
    blk[0] = 0x01;
    blk[1] = 0x02;

    status = kdGenMemOpsCountBlocks(&count, buf, USIZE_C(16), blk, USIZE_C(2));

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

    /* Fill buffer with repeating block pattern */
    blk[0] = 0xAA;
    blk[1] = 0xBB;
    blk[2] = 0xCC;
    blk[3] = 0xDD;

    /* Set all 4 blocks to same pattern */
    kdi_Fill_u8(&buf[0], USIZE_C(4), blk[0]);
    buf[0]  = 0xAA;
    buf[1]  = 0xBB;
    buf[2]  = 0xCC;
    buf[3]  = 0xDD;
    buf[4]  = 0xAA;
    buf[5]  = 0xBB;
    buf[6]  = 0xCC;
    buf[7]  = 0xDD;
    buf[8]  = 0xAA;
    buf[9]  = 0xBB;
    buf[10] = 0xCC;
    buf[11] = 0xDD;
    buf[12] = 0xAA;
    buf[13] = 0xBB;
    buf[14] = 0xCC;
    buf[15] = 0xDD;

    status  = kdGenMemOpsCountBlocks(&count, buf, USIZE_C(16), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16)); /* 4 matching blocks × 4 bytes = 16 */

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

    /* Fill with zeros except one block */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    blk[0] = 0x11;
    blk[1] = 0x22;
    blk[2] = 0x33;
    blk[3] = 0x44;

    /* Set middle block */
    buf[4] = 0x11;
    buf[5] = 0x22;
    buf[6] = 0x33;
    buf[7] = 0x44;

    status = kdGenMemOpsCountBlocks(&count, buf, USIZE_C(16), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(4)); /* 1 matching block × 4 bytes = 4 */

    printf("PASSED\n");
}


void
CountMultiple(void)
{
    u8    buf[20];
    u8    blk[2];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountMultiple -> ");

    /* Buffer: 10 blocks of size 2
     * Blocks: [01 02], [00 00], [01 02], [00 00], [01 02],
     *         [00 00], [01 02], [00 00], [01 02], [00 00]
     */
    kdi_Fill_u8(buf, USIZE_C(20), U8_C(0x00));
    buf[0]  = 0x01;
    buf[1]  = 0x02;
    buf[4]  = 0x01;
    buf[5]  = 0x02;
    buf[8]  = 0x01;
    buf[9]  = 0x02;
    buf[12] = 0x01;
    buf[13] = 0x02;
    buf[16] = 0x01;
    buf[17] = 0x02;

    blk[0]  = 0x01;
    blk[1]  = 0x02;

    status  = kdGenMemOpsCountBlocks(&count, buf, USIZE_C(20), blk, USIZE_C(2));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(10)); /* 5 matching blocks × 2 bytes = 10 */

    printf("PASSED\n");
}


void
BlockAlignment(void)
{
    u8    buf[8];
    u8    blk[2];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "BlockAlignment -> ");

    /* Buffer: [1, 2, 3, 4, 1, 2, 5, 6] */
    buf[0] = 1;
    buf[1] = 2;
    buf[2] = 3;
    buf[3] = 4;
    buf[4] = 1;
    buf[5] = 2;
    buf[6] = 5;
    buf[7] = 6;

    /* Search for [1, 2] - should find blocks at offsets 0 and 4 */
    blk[0] = 1;
    blk[1] = 2;
    status = kdGenMemOpsCountBlocks(&count, buf, USIZE_C(8), blk, USIZE_C(2));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(4)); /* 2 matching blocks × 2 bytes = 4 */

    /* Search for [2, 3] - crosses block boundary, should NOT be found */
    blk[0] = 2;
    blk[1] = 3;
    status = kdGenMemOpsCountBlocks(&count, buf, USIZE_C(8), blk, USIZE_C(2));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    /* Search for [3, 4] - aligned block at offset 2 */
    blk[0] = 3;
    blk[1] = 4;
    status = kdGenMemOpsCountBlocks(&count, buf, USIZE_C(8), blk, USIZE_C(2));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(2)); /* 1 matching block × 2 bytes = 2 */

    printf("PASSED\n");
}


void
SingleByteBlocks(void)
{
    u8    buf[16];
    u8    blk[1];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleByteBlocks -> ");

    /* Buffer with alternating pattern */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));
    buf[1] = 0xFF;
    buf[3] = 0xFF;
    buf[5] = 0xFF;
    buf[7] = 0xFF;
    buf[9] = 0xFF;

    blk[0] = 0xFF;

    status = kdGenMemOpsCountBlocks(&count, buf, USIZE_C(16), blk, USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(5)); /* 5 matching blocks × 1 byte = 5 */

    printf("PASSED\n");
}


void
U16_CountBlocks(void)
{
    u16   buf[8];
    u16   blk[1];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "U16_CountBlocks -> ");

    /* Blocks: [100], [200], [100], [300], [100], [400], [100], [500] */
    buf[0] = 100;
    buf[1] = 200;
    buf[2] = 100;
    buf[3] = 300;
    buf[4] = 100;
    buf[5] = 400;
    buf[6] = 100;
    buf[7] = 500;

    blk[0] = 100;

    status = kdGenMemOpsCountBlocks(&count, buf, sizeof(buf), blk, sizeof(u16));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(8)); /* 4 matching blocks × 2 bytes = 8 */

    /* Count 200 */
    blk[0] = 200;
    status = kdGenMemOpsCountBlocks(&count, buf, sizeof(buf), blk, sizeof(u16));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(2)); /* 1 matching block × 2 bytes = 2 */

    /* Count non-existent 999 */
    blk[0] = 999;
    status = kdGenMemOpsCountBlocks(&count, buf, sizeof(buf), blk, sizeof(u16));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

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

    /* Blocks (size = 2*u16 = 4 bytes):
     * [10, 20], [99, 99], [10, 20], [88, 88]
     */
    buf[0] = 10;
    buf[1] = 20;
    buf[2] = 99;
    buf[3] = 99;
    buf[4] = 10;
    buf[5] = 20;
    buf[6] = 88;
    buf[7] = 88;

    blk[0] = 10;
    blk[1] = 20;

    status = kdGenMemOpsCountBlocks(&count, buf, sizeof(buf), blk, sizeof(u16) * 2);

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(8)); /* 2 matching blocks × 4 bytes = 8 */

    printf("PASSED\n");
}


void
U32_CountBlocks(void)
{
    u32   buf[8];
    u32   blk[1];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_CountBlocks -> ");

    /* Blocks: [1000], [2000], [1000], [3000], [1000], [4000], [1000], [5000] */
    buf[0] = 1000;
    buf[1] = 2000;
    buf[2] = 1000;
    buf[3] = 3000;
    buf[4] = 1000;
    buf[5] = 4000;
    buf[6] = 1000;
    buf[7] = 5000;

    blk[0] = 1000;

    status = kdGenMemOpsCountBlocks(&count, buf, sizeof(buf), blk, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16)); /* 4 matching blocks × 4 bytes = 16 */

    printf("PASSED\n");
}


void
U32_MultiBlocks(void)
{
    u32   buf[8];
    u32   blk[2];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_MultiBlocks -> ");

    /* Blocks (size = 2*u32 = 8 bytes):
     * [10, 20], [99, 99], [10, 20], [88, 88]
     */
    buf[0] = 10;
    buf[1] = 20;
    buf[2] = 99;
    buf[3] = 99;
    buf[4] = 10;
    buf[5] = 20;
    buf[6] = 88;
    buf[7] = 88;

    blk[0] = 10;
    blk[1] = 20;

    status = kdGenMemOpsCountBlocks(&count, buf, sizeof(buf), blk, sizeof(u32) * 2);

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16)); /* 2 matching blocks × 8 bytes = 16 */

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_CountBlocks(void)
{
    u64   buf[6];
    u64   blk[1];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "U64_CountBlocks -> ");

    /* Blocks: [A], [B], [A], [C], [A], [D] */
    buf[0] = U64_C(0xAAAAAAAAAAAAAAAA);
    buf[1] = U64_C(0xBBBBBBBBBBBBBBBB);
    buf[2] = U64_C(0xAAAAAAAAAAAAAAAA);
    buf[3] = U64_C(0xCCCCCCCCCCCCCCCC);
    buf[4] = U64_C(0xAAAAAAAAAAAAAAAA);
    buf[5] = U64_C(0xDDDDDDDDDDDDDDDD);

    blk[0] = U64_C(0xAAAAAAAAAAAAAAAA);

    status = kdGenMemOpsCountBlocks(&count, buf, sizeof(buf), blk, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(24)); /* 3 matching blocks × 8 bytes = 24 */

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

    /* Blocks (size = 2*u64 = 16 bytes):
     * [1, 2], [99, 99], [1, 2]
     */
    buf[0] = 1;
    buf[1] = 2;
    buf[2] = 99;
    buf[3] = 99;
    buf[4] = 1;
    buf[5] = 2;

    blk[0] = 1;
    blk[1] = 2;

    status = kdGenMemOpsCountBlocks(&count, buf, sizeof(buf), blk, sizeof(u64) * 2);

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(32)); /* 2 matching blocks × 16 bytes = 32 */

    printf("PASSED\n");
}
#endif


typedef struct kdi_SmallStruct
{
    u16 a;
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
Struct_CountBlocks(void)
{
    kdi_LargeStruct buf[6];
    kdi_LargeStruct blk;
    usize           count;
    bool            status;

    printf(LOG_PREFIX_CSTR "Struct_CountBlocks -> ");

    /* Target struct: A */
    blk.a    = 1;
    blk.b    = 2;
    blk.c    = 3;
    blk.d    = 4;

    /* Blocks: [A], [B], [A], [C], [A], [D] */
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

    buf[5].a = 77;
    buf[5].b = 77;
    buf[5].c = 77;
    buf[5].d = 77;

    status   = kdGenMemOpsCountBlocks(&count, buf, sizeof(buf), &blk, sizeof(kdi_LargeStruct));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(3) * sizeof(kdi_LargeStruct)); /* 3 matching blocks × struct size */

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    u8    buf[200];
    u8    blk[5];
    usize count;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    /* Fill with repeating pattern: 1,2,3,4,5... */
    for (i = 0; i < 200; ++i)
        buf[i] = (u8)((i % 5) + 1);

    /* Search for 1,2,3,4,5 */
    blk[0] = 1;
    blk[1] = 2;
    blk[2] = 3;
    blk[3] = 4;
    blk[4] = 5;

    /* Pattern repeats every 5 bytes. 200 / 5 = 40 aligned blocks. */
    status = kdGenMemOpsCountBlocks(&count, buf, USIZE_C(200), blk, USIZE_C(5));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(200)); /* 40 matching blocks × 5 bytes = 200 */

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

    /* All blocks are the same */
    blk[0] = 0xAA;
    blk[1] = 0xBB;
    blk[2] = 0xCC;
    blk[3] = 0xDD;

    /* Fill entire buffer with same block */
    for (usize i = 0; i < 8; ++i)
    {
        buf[i * 4]     = 0xAA;
        buf[i * 4 + 1] = 0xBB;
        buf[i * 4 + 2] = 0xCC;
        buf[i * 4 + 3] = 0xDD;
    }

    status = kdGenMemOpsCountBlocks(&count, buf, USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(32)); /* 8 matching blocks × 4 bytes = 32 */

    printf("PASSED\n");
}


void
ZeroBlocks(void)
{
    u8    buf[32];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ZeroBlocks -> ");

    /* Fill with zeros */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));

    /* Search for zero block */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0x00));

    status = kdGenMemOpsCountBlocks(&count, buf, USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(32)); /* 8 matching blocks × 4 bytes = 32 */

    printf("PASSED\n");
}


void
MaxValueBlocks(void)
{
    u8    buf[24];
    u8    blk[3];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "MaxValueBlocks -> ");

    /* Fill with 0xFF */
    kdi_Fill_u8(buf, USIZE_C(24), U8_C(0xFF));

    /* Search for 0xFF block */
    kdi_Fill_u8(blk, USIZE_C(3), U8_C(0xFF));

    status = kdGenMemOpsCountBlocks(&count, buf, USIZE_C(24), blk, USIZE_C(3));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(24)); /* 8 matching blocks × 3 bytes = 24 */

    printf("PASSED\n");
}


void
PartialMatches(void)
{
    u8    buf[16];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "PartialMatches -> ");

    /* Buffer has blocks that partially match but not completely */
    /* Block 0: [1, 2, 3, 4] */
    /* Block 1: [1, 2, 3, 5] - partial match */
    /* Block 2: [1, 2, 9, 4] - partial match */
    /* Block 3: [1, 2, 3, 4] - full match */

    buf[0]  = 1;
    buf[1]  = 2;
    buf[2]  = 3;
    buf[3]  = 4;
    buf[4]  = 1;
    buf[5]  = 2;
    buf[6]  = 3;
    buf[7]  = 5;
    buf[8]  = 1;
    buf[9]  = 2;
    buf[10] = 9;
    buf[11] = 4;
    buf[12] = 1;
    buf[13] = 2;
    buf[14] = 3;
    buf[15] = 4;

    blk[0]  = 1;
    blk[1]  = 2;
    blk[2]  = 3;
    blk[3]  = 4;

    status  = kdGenMemOpsCountBlocks(&count, buf, USIZE_C(16), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(8)); /* 2 matching blocks × 4 bytes = 8 */

    printf("PASSED\n");
}


void
SingleBlockBuffer(void)
{
    u8    buf[4];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleBlockBuffer -> ");

    /* Buffer contains exactly one block */
    buf[0] = 0x12;
    buf[1] = 0x34;
    buf[2] = 0x56;
    buf[3] = 0x78;

    blk[0] = 0x12;
    blk[1] = 0x34;
    blk[2] = 0x56;
    blk[3] = 0x78;

    /* Match */
    status = kdGenMemOpsCountBlocks(&count, buf, USIZE_C(4), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(4)); /* 1 matching block × 4 bytes = 4 */

    /* No match */
    blk[3] = 0x79;
    status = kdGenMemOpsCountBlocks(&count, buf, USIZE_C(4), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    printf("PASSED\n");
}


void
AlternatingBlocks(void)
{
    u8    buf[24];
    u8    blk1[3];
    u8    blk2[3];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "AlternatingBlocks -> ");

    /* Alternating pattern: A, B, A, B, A, B, A, B */
    blk1[0] = 0xAA;
    blk1[1] = 0xAA;
    blk1[2] = 0xAA;
    blk2[0] = 0xBB;
    blk2[1] = 0xBB;
    blk2[2] = 0xBB;

    for (usize i = 0; i < 8; ++i)
    {
        if (i % 2 == 0)
        {
            buf[i * 3]     = 0xAA;
            buf[i * 3 + 1] = 0xAA;
            buf[i * 3 + 2] = 0xAA;
        }
        else
        {
            buf[i * 3]     = 0xBB;
            buf[i * 3 + 1] = 0xBB;
            buf[i * 3 + 2] = 0xBB;
        }
    }

    /* Count A blocks */
    status = kdGenMemOpsCountBlocks(&count, buf, USIZE_C(24), blk1, USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(12)); /* 4 matching blocks × 3 bytes = 12 */

    /* Count B blocks */
    status = kdGenMemOpsCountBlocks(&count, buf, USIZE_C(24), blk2, USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(12)); /* 4 matching blocks × 3 bytes = 12 */

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

    /* Buffer size 33, block size 3 = 11 blocks */
    blk[0] = 0x77;
    blk[1] = 0x88;
    blk[2] = 0x99;

    /* Fill with pattern */
    for (usize i = 0; i < 11; ++i)
    {
        buf[i * 3]     = 0x77;
        buf[i * 3 + 1] = 0x88;
        buf[i * 3 + 2] = 0x99;
    }

    status = kdGenMemOpsCountBlocks(&count, buf, USIZE_C(33), blk, USIZE_C(3));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(33)); /* 11 matching blocks × 3 bytes = 33 */

    printf("PASSED\n");
}


void
SparseMatches(void)
{
    u8    buf[40];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "SparseMatches -> ");

    /* Fill with alternating pattern where target appears sparsely */
    kdi_Fill_u8(buf, USIZE_C(40), U8_C(0x00));

    blk[0]  = 0xFF;
    blk[1]  = 0xFF;
    blk[2]  = 0xFF;
    blk[3]  = 0xFF;

    /* Set blocks 2, 5, 8 to target */
    buf[8]  = 0xFF;
    buf[9]  = 0xFF;
    buf[10] = 0xFF;
    buf[11] = 0xFF;
    buf[20] = 0xFF;
    buf[21] = 0xFF;
    buf[22] = 0xFF;
    buf[23] = 0xFF;
    buf[32] = 0xFF;
    buf[33] = 0xFF;
    buf[34] = 0xFF;
    buf[35] = 0xFF;

    status  = kdGenMemOpsCountBlocks(&count, buf, USIZE_C(40), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(12)); /* 3 matching blocks × 4 bytes = 12 */

    printf("PASSED\n");
}


void
LargeBlockSize(void)
{
    u8    buf[64];
    u8    blk[16];
    usize count;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBlockSize -> ");

    /* Block size 16, buffer size 64 = 4 blocks */
    for (i = 0; i < 16; ++i)
    {
        blk[i] = (u8)i;
    }

    /* Fill buffer with 2 matching blocks and 2 different blocks */
    /* Block 0: matches */
    for (i = 0; i < 16; ++i)
        buf[i] = (u8)i;

    /* Block 1: different */
    kdi_Fill_u8(&buf[16], USIZE_C(16), U8_C(0xFF));

    /* Block 2: matches */
    for (i = 0; i < 16; ++i)
        buf[32 + i] = (u8)i;

    /* Block 3: different */
    kdi_Fill_u8(&buf[48], USIZE_C(16), U8_C(0x00));

    status = kdGenMemOpsCountBlocks(&count, buf, USIZE_C(64), blk, USIZE_C(16));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(32)); /* 2 matching blocks × 16 bytes = 32 */

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
    BlockAlignment();
    SingleByteBlocks();

    U16_CountBlocks();
    U16_MultiByteBlocks();
    U32_CountBlocks();
    U32_MultiBlocks();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_CountBlocks();
    U64_MultiBlocks();
#endif
    Struct_CountBlocks();

    LargeBuffer();
    ConsecutiveMatches();
    ZeroBlocks();
    MaxValueBlocks();
    PartialMatches();
    SingleBlockBuffer();
    AlternatingBlocks();
    OddSizes();
    SparseMatches();
    LargeBlockSize();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
