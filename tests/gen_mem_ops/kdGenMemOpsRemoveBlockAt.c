/**
 * @file kdGenMemOpsRemoveBlockAt.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsRemoveBlockAt function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsRemoveBlockAt function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8    buf[16];
    usize len = 8;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillSeq_u8(buf, USIZE_C(8), U8_C(0x00));

    /* base is null -> failure */
    status = kdGenMemOpsRemoveBlockAt(null, USIZE_C(16), &len, USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_elems pointer is null -> failure */
    status = kdGenMemOpsRemoveBlockAt(buf, USIZE_C(16), null, USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = kdGenMemOpsRemoveBlockAt(buf, USIZE_C(16), &len, USIZE_C(0), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* Valid arguments */
    len    = 8;
    status = kdGenMemOpsRemoveBlockAt(buf, USIZE_C(16), &len, USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(4));

    printf("PASSED\n");
}


void
RemoveHead(void)
{
    u8    buf[16];
    usize len = 12;
    bool  status;

    printf(LOG_PREFIX_CSTR "RemoveHead -> ");

    /* Init: Block 0 (0x01..), Block 1 (0x02..), Block 2 (0x03..) */
    buf[0]  = 1;
    buf[1]  = 1;
    buf[2]  = 1;
    buf[3]  = 1;
    buf[4]  = 2;
    buf[5]  = 2;
    buf[6]  = 2;
    buf[7]  = 2;
    buf[8]  = 3;
    buf[9]  = 3;
    buf[10] = 3;
    buf[11] = 3;

    /* Remove Block at Offset 0 (Size 4) */
    status  = kdGenMemOpsRemoveBlockAt(buf, USIZE_C(16), &len, USIZE_C(0), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(8));

    /* Verify shift: Block 1 moved to 0, Block 2 moved to 4 */
    assert(buf[0] == 2);
    assert(buf[1] == 2);
    assert(buf[4] == 3);
    assert(buf[5] == 3);

    printf("PASSED\n");
}


void
RemoveTail(void)
{
    u8    buf[16];
    usize len = 12;
    bool  status;

    printf(LOG_PREFIX_CSTR "RemoveTail -> ");

    /* Init: 0x01.., 0x02.., 0x03.. */
    buf[0]  = 1;
    buf[1]  = 1;
    buf[2]  = 1;
    buf[3]  = 1;
    buf[4]  = 2;
    buf[5]  = 2;
    buf[6]  = 2;
    buf[7]  = 2;
    buf[8]  = 3;
    buf[9]  = 3;
    buf[10] = 3;
    buf[11] = 3;

    /* Remove Block at Offset 8 (Last block) */
    status  = kdGenMemOpsRemoveBlockAt(buf, USIZE_C(16), &len, USIZE_C(8), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(8));

    /* Verify head untouched */
    assert(buf[0] == 1);
    assert(buf[4] == 2);

    printf("PASSED\n");
}


void
RemoveMiddle(void)
{
    u8    buf[16];
    usize len = 12;
    bool  status;

    printf(LOG_PREFIX_CSTR "RemoveMiddle -> ");

    /* Init: Block 0 (1), Block 1 (2), Block 2 (3) */
    buf[0]  = 1;
    buf[1]  = 1;
    buf[2]  = 1;
    buf[3]  = 1;
    buf[4]  = 2;
    buf[5]  = 2;
    buf[6]  = 2;
    buf[7]  = 2;
    buf[8]  = 3;
    buf[9]  = 3;
    buf[10] = 3;
    buf[11] = 3;

    /* Remove Block at Offset 4 (Block 1) */
    status  = kdGenMemOpsRemoveBlockAt(buf, USIZE_C(16), &len, USIZE_C(4), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(8));

    /* Verify: [1, 1, 1, 1, 3, 3, 3, 3] */
    assert(buf[0] == 1);
    assert(buf[4] == 3);

    printf("PASSED\n");
}


void
RemoveSingleBlock(void)
{
    u8    buf[16];
    usize len = 4;
    bool  status;

    printf(LOG_PREFIX_CSTR "RemoveSingleBlock -> ");

    buf[0] = 0xAA;
    buf[1] = 0xAB;
    buf[2] = 0xAC;
    buf[3] = 0xAD;

    /* Remove Offset 0 */
    status = kdGenMemOpsRemoveBlockAt(buf, USIZE_C(16), &len, USIZE_C(0), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(0));

    printf("PASSED\n");
}


void
RemoveFromEmpty(void)
{
    u8    buf[16];
    usize len = 0;
    bool  status;

    printf(LOG_PREFIX_CSTR "RemoveFromEmpty -> ");

    status = kdGenMemOpsRemoveBlockAt(buf, USIZE_C(16), &len, USIZE_C(0), USIZE_C(4));

    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(0));

    printf("PASSED\n");
}


void
OutOfBounds(void)
{
    u8    buf[16];
    usize len = 8;
    bool  status;

    printf(LOG_PREFIX_CSTR "OutOfBounds -> ");

    kdi_FillSeq_u8(buf, USIZE_C(8), U8_C(0x00));

    /* Remove at Offset 8. Valid data is [0..7]. Offset 8 is out of bounds. */
    status = kdGenMemOpsRemoveBlockAt(buf, USIZE_C(16), &len, USIZE_C(8), USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(8));

    /* Remove at Offset 4. Valid but idx + block_sz = 8 which equals len (boundary) */
    len    = 8;
    status = kdGenMemOpsRemoveBlockAt(buf, USIZE_C(16), &len, USIZE_C(4), USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(4));

    /* Remove beyond capacity */
    len    = 8;
    status = kdGenMemOpsRemoveBlockAt(buf, USIZE_C(16), &len, USIZE_C(20), USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(8));

    printf("PASSED\n");
}


void
AlignmentChecks(void)
{
    u8    buf[16];
    usize len = 12;
    bool  status;

    printf(LOG_PREFIX_CSTR "AlignmentChecks -> ");

    kdi_FillSeq_u8(buf, USIZE_C(12), U8_C(0x00));

    /* Test 1: base_cap not aligned to block_sz */
    /* base_cap=15, block_sz=4, 15 % 4 = 3, not aligned -> failure */
    status = kdGenMemOpsRemoveBlockAt(buf, USIZE_C(15), &len, USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(12));

    /* Test 2: *base_elems not aligned to block_sz */
    /* len=11, block_sz=4, 11 % 4 = 3, not aligned -> failure */
    len    = 11;
    status = kdGenMemOpsRemoveBlockAt(buf, USIZE_C(16), &len, USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(11));

    /* Test 3: idx not aligned to block_sz */
    /* idx=5, block_sz=4, 5 % 4 = 1, not aligned -> failure */
    len    = 12;
    status = kdGenMemOpsRemoveBlockAt(buf, USIZE_C(16), &len, USIZE_C(5), USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(12));

    /* Test 4: idx + block_sz > base_cap (strict boundary check) */
    /* idx=12, block_sz=8, idx+block_sz=20 > base_cap=16 -> failure */
    len    = 16;
    status = kdGenMemOpsRemoveBlockAt(buf, USIZE_C(16), &len, USIZE_C(12), USIZE_C(8));
    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(16));

    /* Test 5: All aligned correctly -> success */
    len    = 12;
    status = kdGenMemOpsRemoveBlockAt(buf, USIZE_C(16), &len, USIZE_C(4), USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(8));

    printf("PASSED\n");
}


void
U8_Remove(void)
{
    u8    buf[16];
    usize len = 8;
    bool  status;

    printf(LOG_PREFIX_CSTR "U8_Remove -> ");

    /* Init: 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80 */
    buf[0] = 0x10;
    buf[1] = 0x20;
    buf[2] = 0x30;
    buf[3] = 0x40;
    buf[4] = 0x50;
    buf[5] = 0x60;
    buf[6] = 0x70;
    buf[7] = 0x80;

    /* Remove at Index 3 (Value 0x40) */
    /* Expected: 0x10, 0x20, 0x30, 0x50, 0x60, 0x70, 0x80 */
    status = kdGenMemOpsRemoveBlockAt(buf, USIZE_C(16), &len, USIZE_C(3), USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(7));
    assert(buf[0] == 0x10);
    assert(buf[1] == 0x20);
    assert(buf[2] == 0x30);
    assert(buf[3] == 0x50);
    assert(buf[4] == 0x60);
    assert(buf[5] == 0x70);
    assert(buf[6] == 0x80);

    printf("PASSED\n");
}


void
U16_Remove(void)
{
    u16   buf[8];
    usize len = 8; /* 4 elements */
    usize cap = 16;
    bool  status;

    printf(LOG_PREFIX_CSTR "U16_Remove -> ");

    /* Init: 100, 200, 300, 400 */
    buf[0] = 100;
    buf[1] = 200;
    buf[2] = 300;
    buf[3] = 400;

    /* Remove Index 1 (Offset 2 bytes). Value 200. */
    /* Expect: 100, 300, 400 */
    status = kdGenMemOpsRemoveBlockAt(buf, cap, &len, USIZE_C(1) * sizeof(u16), sizeof(u16));

    assert(status == RESULT_SUCCESS);
    assert(len == 6);
    assert(buf[0] == 100);
    assert(buf[1] == 300);
    assert(buf[2] == 400);

    printf("PASSED\n");
}


void
U32_Remove(void)
{
    u32   buf[8];
    usize len = 16; /* 4 elements */
    usize cap = 32;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_Remove -> ");

    /* Init: 1000, 2000, 3000, 4000 */
    buf[0] = 1000;
    buf[1] = 2000;
    buf[2] = 3000;
    buf[3] = 4000;

    /* Remove Index 0 (Offset 0 bytes). Value 1000. */
    /* Expect: 2000, 3000, 4000 */
    status = kdGenMemOpsRemoveBlockAt(buf, cap, &len, 0, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    assert(len == 12);
    assert(buf[0] == 2000);
    assert(buf[1] == 3000);
    assert(buf[2] == 4000);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_Remove(void)
{
    u64   buf[8];
    usize len = 32; /* 4 elements */
    usize cap = 64;
    bool  status;

    printf(LOG_PREFIX_CSTR "U64_Remove -> ");

    /* Init: 111, 222, 333, 444 */
    buf[0] = 111;
    buf[1] = 222;
    buf[2] = 333;
    buf[3] = 444;

    /* Remove Index 2 (Offset 16 bytes). Value 333. */
    /* Expect: 111, 222, 444 */
    status = kdGenMemOpsRemoveBlockAt(buf, cap, &len, USIZE_C(2) * sizeof(u64), sizeof(u64));

    assert(status == RESULT_SUCCESS);
    assert(len == 24);
    assert(buf[0] == 111);
    assert(buf[1] == 222);
    assert(buf[2] == 444);

    printf("PASSED\n");
}
#endif


typedef struct kdi_SmallStruct
{
    u32 x;
    u32 y;
} kdi_SmallStruct;


typedef struct kdi_LargeStruct
{
    u64 a;
    u64 b;
    u32 c;
    u8  d;
} kdi_LargeStruct;


void
Struct_Remove(void)
{
    kdi_LargeStruct buf[4];
    usize           elem_sz = sizeof(kdi_LargeStruct);
    usize           cap     = 4 * elem_sz;
    usize           len     = 3 * elem_sz;
    bool            status;

    printf(LOG_PREFIX_CSTR "Struct_Remove -> ");

    /* Init: [S0, S1, S2] */
    buf[0].a = 10;
    buf[0].b = 11;
    buf[0].c = 12;
    buf[0].d = 13;

    buf[1].a = 20;
    buf[1].b = 21;
    buf[1].c = 22;
    buf[1].d = 23;

    buf[2].a = 30;
    buf[2].b = 31;
    buf[2].c = 32;
    buf[2].d = 33;

    /* Remove Index 1 (Offset elem_sz). S1. */
    /* Expect: [S0, S2] */
    status   = kdGenMemOpsRemoveBlockAt(buf, cap, &len, elem_sz, elem_sz);

    assert(status == RESULT_SUCCESS);
    assert(len == 2 * elem_sz);

    assert(buf[0].a == 10 && buf[0].b == 11 && buf[0].c == 12 && buf[0].d == 13);
    /* Index 1 now holds S2 */
    assert(buf[1].a == 30 && buf[1].b == 31 && buf[1].c == 32 && buf[1].d == 33);

    printf("PASSED\n");
}


void
MultipleRemovals(void)
{
    u8    buf[32];
    usize len = 20;
    bool  status;

    printf(LOG_PREFIX_CSTR "MultipleRemovals -> ");

    /* Init: 5 blocks of size 4 (0x00..0x00, 0x11..0x11, 0x22..0x22, 0x33..0x33, 0x44..0x44) */
    buf[0]  = 0x00;
    buf[1]  = 0x00;
    buf[2]  = 0x00;
    buf[3]  = 0x00;
    buf[4]  = 0x11;
    buf[5]  = 0x11;
    buf[6]  = 0x11;
    buf[7]  = 0x11;
    buf[8]  = 0x22;
    buf[9]  = 0x22;
    buf[10] = 0x22;
    buf[11] = 0x22;
    buf[12] = 0x33;
    buf[13] = 0x33;
    buf[14] = 0x33;
    buf[15] = 0x33;
    buf[16] = 0x44;
    buf[17] = 0x44;
    buf[18] = 0x44;
    buf[19] = 0x44;

    /* Remove block at offset 8 (0x22 block) */
    /* Result: 0x00, 0x11, 0x33, 0x44 */
    status  = kdGenMemOpsRemoveBlockAt(buf, USIZE_C(32), &len, USIZE_C(8), USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(16));
    assert(buf[8] == 0x33);

    /* Remove block at offset 0 (0x00 block) */
    /* Result: 0x11, 0x33, 0x44 */
    status = kdGenMemOpsRemoveBlockAt(buf, USIZE_C(32), &len, USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(12));
    assert(buf[0] == 0x11);
    assert(buf[4] == 0x33);

    /* Remove last block at offset 8 (0x44 block) */
    /* Result: 0x11, 0x33 */
    status = kdGenMemOpsRemoveBlockAt(buf, USIZE_C(32), &len, USIZE_C(8), USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(8));

    /* Verify final state */
    assert(buf[0] == 0x11);
    assert(buf[4] == 0x33);

    printf("PASSED\n");
}


void
DataIntegrity(void)
{
    u8    buf[48];
    usize len = 24;
    bool  status;

    printf(LOG_PREFIX_CSTR "DataIntegrity -> ");

    /* Fill with distinct pattern blocks (6 blocks of size 4) */
    buf[0]  = 0xAA;
    buf[1]  = 0xAB;
    buf[2]  = 0xAC;
    buf[3]  = 0xAD;
    buf[4]  = 0xBA;
    buf[5]  = 0xBB;
    buf[6]  = 0xBC;
    buf[7]  = 0xBD;
    buf[8]  = 0xCA;
    buf[9]  = 0xCB;
    buf[10] = 0xCC;
    buf[11] = 0xCD;
    buf[12] = 0xDA;
    buf[13] = 0xDB;
    buf[14] = 0xDC;
    buf[15] = 0xDD;
    buf[16] = 0xEA;
    buf[17] = 0xEB;
    buf[18] = 0xEC;
    buf[19] = 0xED;
    buf[20] = 0xFA;
    buf[21] = 0xFB;
    buf[22] = 0xFC;
    buf[23] = 0xFD;

    /* Remove block at offset 8 (0xCA block) */
    status  = kdGenMemOpsRemoveBlockAt(buf, USIZE_C(48), &len, USIZE_C(8), USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(20));

    /* Verify blocks before removal point are unchanged */
    assert(buf[0] == 0xAA && buf[1] == 0xAB && buf[2] == 0xAC && buf[3] == 0xAD);
    assert(buf[4] == 0xBA && buf[5] == 0xBB && buf[6] == 0xBC && buf[7] == 0xBD);

    /* Verify blocks after removal point shifted correctly */
    assert(buf[8] == 0xDA && buf[9] == 0xDB && buf[10] == 0xDC && buf[11] == 0xDD);
    assert(buf[12] == 0xEA && buf[13] == 0xEB && buf[14] == 0xEC && buf[15] == 0xED);
    assert(buf[16] == 0xFA && buf[17] == 0xFB && buf[18] == 0xFC && buf[19] == 0xFD);

    printf("PASSED\n");
}


void
MixedBlockSizes(void)
{
    u8    buf8[32];
    u16   buf16[16];
    usize len8, len16;
    bool  status;

    printf(LOG_PREFIX_CSTR "MixedBlockSizes -> ");

    /* Test block size 1 (byte) */
    len8 = 10;
    kdi_FillSeq_u8(buf8, USIZE_C(10), U8_C(0x00));
    status = kdGenMemOpsRemoveBlockAt(buf8, USIZE_C(32), &len8, USIZE_C(5), USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(len8 == USIZE_C(9));
    assert(buf8[5] == 0x06);

    /* Test block size 2 (u16) */
    len16    = 8; /* 4 u16 elements = 8 bytes */
    buf16[0] = 100;
    buf16[1] = 200;
    buf16[2] = 300;
    buf16[3] = 400;
    status   = kdGenMemOpsRemoveBlockAt(buf16, USIZE_C(32), &len16, USIZE_C(4), USIZE_C(2));
    assert(status == RESULT_SUCCESS);
    assert(len16 == USIZE_C(6));
    assert(buf16[0] == 100);
    assert(buf16[1] == 200);
    assert(buf16[2] == 400);

    printf("PASSED\n");
}


void
LargeBlockRemoval(void)
{
    byte  buf[128];
    usize len = 96; /* 3 blocks of size 32 */
    usize i;
    bool  status;

    printf(LOG_PREFIX_CSTR "LargeBlockRemoval -> ");

    /* Fill blocks with distinct patterns */
    for (i = 0; i < 32; ++i)
        buf[i] = 0x01;
    for (i = 32; i < 64; ++i)
        buf[i] = 0x02;
    for (i = 64; i < 96; ++i)
        buf[i] = 0x03;

    /* Remove middle block (offset 32, size 32) */
    status = kdGenMemOpsRemoveBlockAt(buf, USIZE_C(128), &len, USIZE_C(32), USIZE_C(32));
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(64));

    /* Verify first block unchanged */
    assert(buf[0] == 0x01);
    assert(buf[31] == 0x01);

    /* Verify third block moved to second position */
    assert(buf[32] == 0x03);
    assert(buf[63] == 0x03);

    printf("PASSED\n");
}


void
RemoveUntilEmpty(void)
{
    u8    buf[16];
    usize len = 12;
    bool  status;

    printf(LOG_PREFIX_CSTR "RemoveUntilEmpty -> ");

    /* Init: 3 blocks of size 4 */
    kdi_Fill_u8(&buf[0], USIZE_C(4), U8_C(0xAA));
    kdi_Fill_u8(&buf[4], USIZE_C(4), U8_C(0xBB));
    kdi_Fill_u8(&buf[8], USIZE_C(4), U8_C(0xCC));

    /* Remove from tail */
    status = kdGenMemOpsRemoveBlockAt(buf, USIZE_C(16), &len, USIZE_C(8), USIZE_C(4));
    assert(status == RESULT_SUCCESS && len == USIZE_C(8));

    status = kdGenMemOpsRemoveBlockAt(buf, USIZE_C(16), &len, USIZE_C(4), USIZE_C(4));
    assert(status == RESULT_SUCCESS && len == USIZE_C(4));

    status = kdGenMemOpsRemoveBlockAt(buf, USIZE_C(16), &len, USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_SUCCESS && len == USIZE_C(0));

    /* Try to remove from empty buffer */
    status = kdGenMemOpsRemoveBlockAt(buf, USIZE_C(16), &len, USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(0));

    printf("PASSED\n");
}


void
SequentialRemovals(void)
{
    u32   buf[16];
    usize len = 32; /* 8 u32 elements */
    usize cap = 64;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "SequentialRemovals -> ");

    /* Init: 1, 2, 3, 4, 5, 6, 7, 8 */
    for (i = 0; i < 8; ++i)
    {
        buf[i] = (u32)(i + 1);
    }

    /* Remove every other element from the end */
    status = kdGenMemOpsRemoveBlockAt(buf, cap, &len, USIZE_C(6) * sizeof(u32), sizeof(u32));
    assert(status == RESULT_SUCCESS && len == USIZE_C(28));
    assert(buf[6] == 8);

    status = kdGenMemOpsRemoveBlockAt(buf, cap, &len, USIZE_C(4) * sizeof(u32), sizeof(u32));
    assert(status == RESULT_SUCCESS && len == USIZE_C(24));
    assert(buf[4] == 6);

    status = kdGenMemOpsRemoveBlockAt(buf, cap, &len, USIZE_C(2) * sizeof(u32), sizeof(u32));
    assert(status == RESULT_SUCCESS && len == USIZE_C(20));
    assert(buf[2] == 4);

    status = kdGenMemOpsRemoveBlockAt(buf, cap, &len, USIZE_C(0) * sizeof(u32), sizeof(u32));
    assert(status == RESULT_SUCCESS && len == USIZE_C(16));
    assert(buf[0] == 2);

    /* Remaining: 2, 4, 6, 8 */
    assert(buf[0] == 2 && buf[1] == 4 && buf[2] == 6 && buf[3] == 8);

    printf("PASSED\n");
}


void
StressTest(void)
{
    u16   buf[64];
    usize len = 64 * sizeof(u16); /* 64 elements */
    usize cap = 64 * sizeof(u16);
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "StressTest -> ");

    /* Init: 0, 1, 2, ..., 63 */
    for (i = 0; i < 64; ++i)
    {
        buf[i] = (u16)i;
    }

    /* Remove every 8th element from high indices */
    for (i = 7; i > 0; --i)
    {
        usize idx = i * 8 * sizeof(u16);
        if (idx < len)
        {
            status = kdGenMemOpsRemoveBlockAt(buf, cap, &len, idx, sizeof(u16));
            assert(status == RESULT_SUCCESS);
        }
    }

    /* Verify buffer is shorter */
    assert(len < (64 * sizeof(u16)));

    /* Verify remaining elements are in ascending order */
    for (i = 1; i < (len / sizeof(u16)); ++i)
    {
        assert(buf[i] > buf[i - 1]);
    }

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    RemoveHead();
    RemoveTail();
    RemoveMiddle();
    RemoveSingleBlock();
    RemoveFromEmpty();
    OutOfBounds();
    AlignmentChecks();

    U8_Remove();
    U16_Remove();
    U32_Remove();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_Remove();
#endif
    Struct_Remove();

    MultipleRemovals();
    DataIntegrity();
    MixedBlockSizes();
    LargeBlockRemoval();
    RemoveUntilEmpty();
    SequentialRemovals();
    StressTest();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
