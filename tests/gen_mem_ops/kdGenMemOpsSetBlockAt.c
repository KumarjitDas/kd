/**
 * @file kdGenMemOpsSetBlockAt.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsSetBlockAt function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsSetBlockAt function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8   buf[16];
    u8   src[4];
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0));
    kdi_Fill_u8(src, USIZE_C(4), U8_C(0xFF));

    /* base is null -> failure */
    status = kdGenMemOpsSetBlockAt(null, USIZE_C(16), USIZE_C(0), src, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(16), USIZE_C(0), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(0), USIZE_C(0), src, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(16), USIZE_C(0), src, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SetBlockAtStart(void)
{
    u8   buf[16];
    u8   src[4];
    bool status;

    printf(LOG_PREFIX_CSTR "SetBlockAtStart -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0));
    kdi_Fill_u8(src, USIZE_C(4), U8_C(0xFF));

    /* Set block at index 0, block size 4 (0 % 4 == 0, aligned) */
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(16), USIZE_C(0), src, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(buf[0] == U8_C(0xFF));
    assert(buf[1] == U8_C(0xFF));
    assert(buf[2] == U8_C(0xFF));
    assert(buf[3] == U8_C(0xFF));
    /* Verify rest untouched */
    assert(buf[4] == U8_C(4));
    assert(buf[5] == U8_C(5));

    printf("PASSED\n");
}


void
SetBlockAtMiddle(void)
{
    u8   buf[16];
    u8   src[4];
    bool status;

    printf(LOG_PREFIX_CSTR "SetBlockAtMiddle -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0));
    kdi_Fill_u8(src, USIZE_C(4), U8_C(0xAA));

    /* Set block at byte index 4, block size 4 (4 % 4 == 0, aligned) */
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(16), USIZE_C(4), src, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    /* Verify before untouched */
    assert(buf[3] == U8_C(3));
    /* Verify block set */
    assert(buf[4] == U8_C(0xAA));
    assert(buf[5] == U8_C(0xAA));
    assert(buf[6] == U8_C(0xAA));
    assert(buf[7] == U8_C(0xAA));
    /* Verify after untouched */
    assert(buf[8] == U8_C(8));

    printf("PASSED\n");
}


void
SetBlockAtEnd(void)
{
    u8   buf[16];
    u8   src[4];
    bool status;

    printf(LOG_PREFIX_CSTR "SetBlockAtEnd -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0));
    kdi_Fill_u8(src, USIZE_C(4), U8_C(0xBB));

    /* Set block at byte index 12, block size 4 (12 % 4 == 0, aligned) */
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(16), USIZE_C(12), src, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    /* Verify before untouched */
    assert(buf[11] == U8_C(11));
    /* Verify block set */
    assert(buf[12] == U8_C(0xBB));
    assert(buf[13] == U8_C(0xBB));
    assert(buf[14] == U8_C(0xBB));
    assert(buf[15] == U8_C(0xBB));

    printf("PASSED\n");
}


void
IndexOutOfBounds(void)
{
    u8   buf[16];
    u8   src[4];
    bool status;

    printf(LOG_PREFIX_CSTR "IndexOutOfBounds -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0));
    kdi_Fill_u8(src, USIZE_C(4), U8_C(0xFF));

    /* Valid: byte index 12, block size 4 -> range [12..15] (12 % 4 == 0) */
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(16), USIZE_C(12), src, USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Invalid: byte index 16, block size 4 -> starts at boundary (16 % 4 == 0 but out of bounds) */
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(16), USIZE_C(16), src, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Invalid: byte index 20, block size 4 -> beyond buffer (20 % 4 == 0) */
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(16), USIZE_C(20), src, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
UnalignedIndex(void)
{
    u8   buf[16];
    u8   src[4];
    bool status;

    printf(LOG_PREFIX_CSTR "UnalignedIndex -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0));
    kdi_Fill_u8(src, USIZE_C(4), U8_C(0xFF));

    /* Invalid: byte index 1, block size 4 (1 % 4 != 0, unaligned) */
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(16), USIZE_C(1), src, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Invalid: byte index 3, block size 4 (3 % 4 != 0, unaligned) */
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(16), USIZE_C(3), src, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Invalid: byte index 5, block size 4 (5 % 4 != 0, unaligned) */
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(16), USIZE_C(5), src, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Verify buffer unchanged */
    assert(buf[0] == U8_C(0));
    assert(buf[1] == U8_C(1));

    printf("PASSED\n");
}


void
SingleByteBlock(void)
{
    u8   buf[8];
    u8   val;
    bool status;

    printf(LOG_PREFIX_CSTR "SingleByteBlock -> ");

    kdi_FillSeq_u8(buf, USIZE_C(8), U8_C(10));

    /* Set single byte at index 0 (0 % 1 == 0, aligned) */
    val    = U8_C(0xFF);
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(8), USIZE_C(0), &val, USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(buf[0] == U8_C(0xFF));
    assert(buf[1] == U8_C(11));

    /* Set single byte at index 3 (3 % 1 == 0, aligned) */
    val    = U8_C(0xAA);
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(8), USIZE_C(3), &val, USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(buf[3] == U8_C(0xAA));
    assert(buf[2] == U8_C(12));

    /* Set single byte at index 7 (7 % 1 == 0, aligned) */
    val    = U8_C(0xBB);
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(8), USIZE_C(7), &val, USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(buf[7] == U8_C(0xBB));

    printf("PASSED\n");
}


void
LargeBlock(void)
{
    u8   buf[64];
    u8   src[32];
    bool status;

    printf(LOG_PREFIX_CSTR "LargeBlock -> ");

    kdi_FillSeq_u8(buf, USIZE_C(64), U8_C(0));
    kdi_Fill_u8(src, USIZE_C(32), U8_C(0xFF));

    /* Set 32-byte block at index 0 (0 % 32 == 0, aligned) */
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(64), USIZE_C(0), src, USIZE_C(32));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(&buf[0], src, USIZE_C(32)) == RESULT_SUCCESS);
    assert(buf[32] == U8_C(32));

    /* Set 32-byte block at index 32 (32 % 32 == 0, aligned) */
    kdi_Fill_u8(src, USIZE_C(32), U8_C(0xAA));
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(64), USIZE_C(32), src, USIZE_C(32));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(&buf[32], src, USIZE_C(32)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
U8_BlockSet(void)
{
    u8   buf[8];
    u8   val;
    bool status;

    printf(LOG_PREFIX_CSTR "U8_BlockSet -> ");

    buf[0] = U8_C(10);
    buf[1] = U8_C(20);
    buf[2] = U8_C(30);
    buf[3] = U8_C(40);
    buf[4] = U8_C(50);
    buf[5] = U8_C(60);
    buf[6] = U8_C(70);
    buf[7] = U8_C(80);

    /* Set element at byte index 0 (0 % 1 == 0, aligned) */
    val    = U8_C(100);
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(8), USIZE_C(0), &val, sizeof(u8));
    assert(status == RESULT_SUCCESS);
    assert(buf[0] == U8_C(100));
    assert(buf[1] == U8_C(20));

    /* Set element at byte index 3 (3 % 1 == 0, aligned) */
    val    = U8_C(200);
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(8), USIZE_C(3), &val, sizeof(u8));
    assert(status == RESULT_SUCCESS);
    assert(buf[3] == U8_C(200));

    /* Set element at byte index 7 (7 % 1 == 0, aligned) */
    val    = U8_C(255);
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(8), USIZE_C(7), &val, sizeof(u8));
    assert(status == RESULT_SUCCESS);
    assert(buf[7] == U8_C(255));

    printf("PASSED\n");
}


void
U16_BlockSet(void)
{
    u16  buf[4];
    u16  val;
    bool status;

    printf(LOG_PREFIX_CSTR "U16_BlockSet -> ");

    buf[0] = U16_C(100);
    buf[1] = U16_C(200);
    buf[2] = U16_C(300);
    buf[3] = U16_C(400);

    /* Set element at byte index 0 (element 0, 0 % 2 == 0, aligned) */
    val    = U16_C(1000);
    status = kdGenMemOpsSetBlockAt(buf, sizeof(buf), USIZE_C(0), &val, sizeof(u16));
    assert(status == RESULT_SUCCESS);
    assert(buf[0] == U16_C(1000));
    assert(buf[1] == U16_C(200));

    /* Set element at byte index sizeof(u16)*2 (element 2, aligned to sizeof(u16)) */
    val    = U16_C(2000);
    status = kdGenMemOpsSetBlockAt(buf, sizeof(buf), USIZE_C(2) * sizeof(u16), &val, sizeof(u16));
    assert(status == RESULT_SUCCESS);
    assert(buf[2] == U16_C(2000));

    /* Set element at byte index sizeof(u16)*3 (element 3, aligned to sizeof(u16)) */
    val    = U16_C(3000);
    status = kdGenMemOpsSetBlockAt(buf, sizeof(buf), USIZE_C(3) * sizeof(u16), &val, sizeof(u16));
    assert(status == RESULT_SUCCESS);
    assert(buf[3] == U16_C(3000));

    printf("PASSED\n");
}


void
U32_BlockSet(void)
{
    u32  buf[5];
    u32  val;
    bool status;

    printf(LOG_PREFIX_CSTR "U32_BlockSet -> ");

    buf[0] = U32_C(1000);
    buf[1] = U32_C(2000);
    buf[2] = U32_C(3000);
    buf[3] = U32_C(4000);
    buf[4] = U32_C(5000);

    /* Set element at byte index 0 (element 0, 0 % 4 == 0, aligned) */
    val    = U32_C(10000);
    status = kdGenMemOpsSetBlockAt(buf, sizeof(buf), USIZE_C(0), &val, sizeof(u32));
    assert(status == RESULT_SUCCESS);
    assert(buf[0] == U32_C(10000));
    assert(buf[1] == U32_C(2000));

    /* Set element at byte index sizeof(u32)*2 (element 2, aligned to sizeof(u32)) */
    val    = U32_C(20000);
    status = kdGenMemOpsSetBlockAt(buf, sizeof(buf), USIZE_C(2) * sizeof(u32), &val, sizeof(u32));
    assert(status == RESULT_SUCCESS);
    assert(buf[2] == U32_C(20000));

    /* Set element at byte index sizeof(u32)*4 (element 4, aligned to sizeof(u32)) */
    val    = U32_C(30000);
    status = kdGenMemOpsSetBlockAt(buf, sizeof(buf), USIZE_C(4) * sizeof(u32), &val, sizeof(u32));
    assert(status == RESULT_SUCCESS);
    assert(buf[4] == U32_C(30000));

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_BlockSet(void)
{
    u64  buf[3];
    u64  val;
    bool status;

    printf(LOG_PREFIX_CSTR "U64_BlockSet -> ");

    buf[0] = U64_C(0x1111111111111111);
    buf[1] = U64_C(0x2222222222222222);
    buf[2] = U64_C(0x3333333333333333);

    /* Set element at byte index 0 (element 0, 0 % 8 == 0, aligned) */
    val    = U64_C(0xAAAAAAAAAAAAAAAA);
    status = kdGenMemOpsSetBlockAt(buf, sizeof(buf), USIZE_C(0), &val, sizeof(u64));
    assert(status == RESULT_SUCCESS);
    assert(buf[0] == U64_C(0xAAAAAAAAAAAAAAAA));
    assert(buf[1] == U64_C(0x2222222222222222));

    /* Set element at byte index sizeof(u64)*1 (element 1, aligned to sizeof(u64)) */
    val    = U64_C(0xBBBBBBBBBBBBBBBB);
    status = kdGenMemOpsSetBlockAt(buf, sizeof(buf), USIZE_C(1) * sizeof(u64), &val, sizeof(u64));
    assert(status == RESULT_SUCCESS);
    assert(buf[1] == U64_C(0xBBBBBBBBBBBBBBBB));

    /* Set element at byte index sizeof(u64)*2 (element 2, aligned to sizeof(u64)) */
    val    = U64_C(0xCCCCCCCCCCCCCCCC);
    status = kdGenMemOpsSetBlockAt(buf, sizeof(buf), USIZE_C(2) * sizeof(u64), &val, sizeof(u64));
    assert(status == RESULT_SUCCESS);
    assert(buf[2] == U64_C(0xCCCCCCCCCCCCCCCC));

    printf("PASSED\n");
}
#endif


typedef struct kdi_TestStruct
{
    u32 a;
    u32 b;
    u16 c;
    u8  d;
} kdi_TestStruct;


void
Struct_BlockSet(void)
{
    kdi_TestStruct buf[3];
    kdi_TestStruct val;
    bool           status;

    printf(LOG_PREFIX_CSTR "Struct_BlockSet -> ");

    /* Initialize buffer */
    buf[0].a = U32_C(10);
    buf[0].b = U32_C(20);
    buf[0].c = U16_C(30);
    buf[0].d = U8_C(40);

    buf[1].a = U32_C(50);
    buf[1].b = U32_C(60);
    buf[1].c = U16_C(70);
    buf[1].d = U8_C(80);

    buf[2].a = U32_C(90);
    buf[2].b = U32_C(100);
    buf[2].c = U16_C(110);
    buf[2].d = U8_C(120);

    /* Set element at byte index 0 (struct 0, 0 % sizeof(struct) == 0, aligned) */
    val.a  = U32_C(0xDEADBEEF);
    val.b  = U32_C(0xCAFEBABE);
    val.c  = U16_C(12345);
    val.d  = U8_C(99);
    status = kdGenMemOpsSetBlockAt(buf, sizeof(buf), USIZE_C(0), &val, sizeof(kdi_TestStruct));
    assert(status == RESULT_SUCCESS);
    assert(buf[0].a == U32_C(0xDEADBEEF));
    assert(buf[0].b == U32_C(0xCAFEBABE));
    assert(buf[0].c == U16_C(12345));
    assert(buf[0].d == U8_C(99));
    assert(buf[1].a == U32_C(50));

    /* Set element at byte index sizeof(struct)*2 (struct 2, aligned to sizeof(struct)) */
    val.a  = U32_C(111);
    val.b  = U32_C(222);
    val.c  = U16_C(333);
    val.d  = U8_C(255);
    status = kdGenMemOpsSetBlockAt(buf, sizeof(buf), USIZE_C(2) * sizeof(kdi_TestStruct), &val, sizeof(kdi_TestStruct));
    assert(status == RESULT_SUCCESS);
    assert(buf[2].a == U32_C(111));
    assert(buf[2].b == U32_C(222));
    assert(buf[2].c == U16_C(333));
    assert(buf[2].d == U8_C(255));
    assert(buf[1].a == U32_C(50));

    printf("PASSED\n");
}


void
OddBlockSizes(void)
{
    u8   buf[30];
    u8   src[3];
    bool status;

    printf(LOG_PREFIX_CSTR "OddBlockSizes -> ");

    kdi_FillSeq_u8(buf, USIZE_C(30), U8_C(0));
    kdi_Fill_u8(src, USIZE_C(3), U8_C(0xFF));

    /* Block size 3 at index 0 (0 % 3 == 0, aligned) */
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(30), USIZE_C(0), src, USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(&buf[0], src, USIZE_C(3)) == RESULT_SUCCESS);
    assert(buf[3] == U8_C(3));

    /* Block size 3 at index 6 (6 % 3 == 0, aligned) */
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(30), USIZE_C(6), src, USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(&buf[6], src, USIZE_C(3)) == RESULT_SUCCESS);
    assert(buf[5] == U8_C(5));

    /* Block size 3 at index 27 (27 % 3 == 0, last valid, aligned) */
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(30), USIZE_C(27), src, USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(&buf[27], src, USIZE_C(3)) == RESULT_SUCCESS);

    /* Block size 3 at index 30 (30 % 3 == 0, aligned but out of bounds) */
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(30), USIZE_C(30), src, USIZE_C(3));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
BlockSize5(void)
{
    u8   buf[40];
    u8   src[5];
    bool status;

    printf(LOG_PREFIX_CSTR "BlockSize5 -> ");

    kdi_FillSeq_u8(buf, USIZE_C(40), U8_C(0));
    kdi_Fill_u8(src, USIZE_C(5), U8_C(0xAA));

    /* Block size 5 at index 0 (0 % 5 == 0, aligned) */
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(40), USIZE_C(0), src, USIZE_C(5));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(&buf[0], src, USIZE_C(5)) == RESULT_SUCCESS);
    assert(buf[5] == U8_C(5));

    /* Block size 5 at index 10 (10 % 5 == 0, aligned) */
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(40), USIZE_C(10), src, USIZE_C(5));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(&buf[10], src, USIZE_C(5)) == RESULT_SUCCESS);
    assert(buf[9] == U8_C(9));

    /* Block size 5 at index 35 (35 % 5 == 0, last valid, aligned) */
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(40), USIZE_C(35), src, USIZE_C(5));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(&buf[35], src, USIZE_C(5)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
FullBufferBlock(void)
{
    u8   buf[16];
    u8   src[16];
    bool status;

    printf(LOG_PREFIX_CSTR "FullBufferBlock -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0));
    kdi_Fill_u8(src, USIZE_C(16), U8_C(0x55));

    /* Set entire buffer as one block (0 % 16 == 0, aligned) */
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(16), USIZE_C(0), src, USIZE_C(16));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, src, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
AllZeroBlock(void)
{
    u8   buf[12];
    u8   src[4];
    bool status;

    printf(LOG_PREFIX_CSTR "AllZeroBlock -> ");

    kdi_Fill_u8(buf, USIZE_C(12), U8_C(0xFF));
    kdi_Fill_u8(src, USIZE_C(4), U8_C(0));

    /* Set 4-byte block at index 0 (0 % 4 == 0, aligned) */
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(12), USIZE_C(0), src, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(buf[0] == U8_C(0));
    assert(buf[1] == U8_C(0));
    assert(buf[2] == U8_C(0));
    assert(buf[3] == U8_C(0));
    assert(buf[4] == U8_C(0xFF));

    /* Set 4-byte block at index 8 (8 % 4 == 0, aligned) */
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(12), USIZE_C(8), src, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(buf[8] == U8_C(0));
    assert(buf[9] == U8_C(0));
    assert(buf[10] == U8_C(0));
    assert(buf[11] == U8_C(0));

    printf("PASSED\n");
}


void
AllOnesBlock(void)
{
    u8   buf[12];
    u8   src[4];
    bool status;

    printf(LOG_PREFIX_CSTR "AllOnesBlock -> ");

    kdi_Fill_u8(buf, USIZE_C(12), U8_C(0));
    kdi_Fill_u8(src, USIZE_C(4), U8_C(0xFF));

    /* Set 4-byte block at index 4 (4 % 4 == 0, aligned) */
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(12), USIZE_C(4), src, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(buf[4] == U8_C(0xFF));
    assert(buf[5] == U8_C(0xFF));
    assert(buf[6] == U8_C(0xFF));
    assert(buf[7] == U8_C(0xFF));
    assert(buf[3] == U8_C(0));
    assert(buf[8] == U8_C(0));

    printf("PASSED\n");
}


void
MultipleSets(void)
{
    u8   buf[16];
    u8   src[4];
    bool status;

    printf(LOG_PREFIX_CSTR "MultipleSets -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0));

    /* Set multiple blocks, all aligned */
    kdi_Fill_u8(src, USIZE_C(4), U8_C(0x11));
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(16), USIZE_C(0), src, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(&buf[0], src, USIZE_C(4)) == RESULT_SUCCESS);

    kdi_Fill_u8(src, USIZE_C(4), U8_C(0x22));
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(16), USIZE_C(4), src, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(&buf[4], src, USIZE_C(4)) == RESULT_SUCCESS);

    kdi_Fill_u8(src, USIZE_C(4), U8_C(0x33));
    status = kdGenMemOpsSetBlockAt(buf, USIZE_C(16), USIZE_C(8), src, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(&buf[8], src, USIZE_C(4)) == RESULT_SUCCESS);

    /* Verify all blocks set correctly */
    assert(buf[0] == U8_C(0x11));
    assert(buf[4] == U8_C(0x22));
    assert(buf[8] == U8_C(0x33));

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    SetBlockAtStart();
    SetBlockAtMiddle();
    SetBlockAtEnd();
    IndexOutOfBounds();
    UnalignedIndex();
    SingleByteBlock();
    LargeBlock();
    U8_BlockSet();
    U16_BlockSet();
    U32_BlockSet();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_BlockSet();
#endif
    Struct_BlockSet();
    OddBlockSizes();
    BlockSize5();
    FullBufferBlock();
    AllZeroBlock();
    AllOnesBlock();
    MultipleSets();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}