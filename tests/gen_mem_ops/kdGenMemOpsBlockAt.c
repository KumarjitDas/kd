/**
 * @file kdGenMemOpsBlockAt.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsBlockAt function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsBlockAt function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8   buf[16];
    u8   dst[4];
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0));

    /* dst is null -> failure */
    status = kdGenMemOpsBlockAt(null, buf, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure */
    status = kdGenMemOpsBlockAt(dst, null, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = kdGenMemOpsBlockAt(dst, buf, USIZE_C(0), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = kdGenMemOpsBlockAt(dst, buf, USIZE_C(16), USIZE_C(0), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ValidBlockAtStart(void)
{
    u8   buf[16];
    u8   dst[4];
    bool status;

    printf(LOG_PREFIX_CSTR "ValidBlockAtStart -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0));

    /* Get block at index 0, block size 4 (0 % 4 == 0, aligned) */
    status = kdGenMemOpsBlockAt(dst, buf, USIZE_C(16), USIZE_C(0), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, &buf[0], USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
ValidBlockAtMiddle(void)
{
    u8   buf[16];
    u8   dst[4];
    bool status;

    printf(LOG_PREFIX_CSTR "ValidBlockAtMiddle -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0));

    /* Get block at byte index 4, block size 4 (4 % 4 == 0, aligned) */
    status = kdGenMemOpsBlockAt(dst, buf, USIZE_C(16), USIZE_C(4), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, &buf[4], USIZE_C(4)) == RESULT_SUCCESS);

    /* Get block at byte index 8, block size 4 (8 % 4 == 0, aligned) */
    status = kdGenMemOpsBlockAt(dst, buf, USIZE_C(16), USIZE_C(8), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, &buf[8], USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
ValidBlockAtEnd(void)
{
    u8   buf[16];
    u8   dst[4];
    bool status;

    printf(LOG_PREFIX_CSTR "ValidBlockAtEnd -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0));

    /* Get block at byte index 12, block size 4 (12 % 4 == 0, aligned) */
    status = kdGenMemOpsBlockAt(dst, buf, USIZE_C(16), USIZE_C(12), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, &buf[12], USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
IndexOutOfBounds(void)
{
    u8   buf[16];
    u8   dst[4];
    bool status;

    printf(LOG_PREFIX_CSTR "IndexOutOfBounds -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0));

    /* Valid: byte index 12, block size 4 -> range [12..15] (12 % 4 == 0) */
    status = kdGenMemOpsBlockAt(dst, buf, USIZE_C(16), USIZE_C(12), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Invalid: byte index 16, block size 4 -> starts at boundary (16 % 4 == 0 but out of bounds) */
    status = kdGenMemOpsBlockAt(dst, buf, USIZE_C(16), USIZE_C(16), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Invalid: byte index 20, block size 4 -> beyond buffer (20 % 4 == 0) */
    status = kdGenMemOpsBlockAt(dst, buf, USIZE_C(16), USIZE_C(20), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
UnalignedIndex(void)
{
    u8   buf[16];
    u8   dst[4];
    bool status;

    printf(LOG_PREFIX_CSTR "UnalignedIndex -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0));

    /* Invalid: byte index 1, block size 4 (1 % 4 != 0, unaligned) */
    status = kdGenMemOpsBlockAt(dst, buf, USIZE_C(16), USIZE_C(1), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Invalid: byte index 3, block size 4 (3 % 4 != 0, unaligned) */
    status = kdGenMemOpsBlockAt(dst, buf, USIZE_C(16), USIZE_C(3), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Invalid: byte index 5, block size 4 (5 % 4 != 0, unaligned) */
    status = kdGenMemOpsBlockAt(dst, buf, USIZE_C(16), USIZE_C(5), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SingleByteBlock(void)
{
    u8   buf[8];
    u8   dst;
    bool status;

    printf(LOG_PREFIX_CSTR "SingleByteBlock -> ");

    kdi_FillSeq_u8(buf, USIZE_C(8), U8_C(10));

    /* Get single byte at index 0 (0 % 1 == 0, aligned) */
    dst    = U8_C(0);
    status = kdGenMemOpsBlockAt(&dst, buf, USIZE_C(8), USIZE_C(0), USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(dst == U8_C(10));

    /* Get single byte at index 3 (3 % 1 == 0, aligned) */
    dst    = U8_C(0);
    status = kdGenMemOpsBlockAt(&dst, buf, USIZE_C(8), USIZE_C(3), USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(dst == U8_C(13));

    /* Get single byte at index 7 (7 % 1 == 0, aligned) */
    dst    = U8_C(0);
    status = kdGenMemOpsBlockAt(&dst, buf, USIZE_C(8), USIZE_C(7), USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(dst == U8_C(17));

    printf("PASSED\n");
}


void
LargeBlock(void)
{
    u8   buf[64];
    u8   dst[32];
    bool status;

    printf(LOG_PREFIX_CSTR "LargeBlock -> ");

    kdi_FillSeq_u8(buf, USIZE_C(64), U8_C(0));

    /* Get 32-byte block at index 0 (0 % 32 == 0, aligned) */
    status = kdGenMemOpsBlockAt(dst, buf, USIZE_C(64), USIZE_C(0), USIZE_C(32));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, &buf[0], USIZE_C(32)) == RESULT_SUCCESS);

    /* Get 32-byte block at index 32 (32 % 32 == 0, aligned) */
    status = kdGenMemOpsBlockAt(dst, buf, USIZE_C(64), USIZE_C(32), USIZE_C(32));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, &buf[32], USIZE_C(32)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
U8_BlockExtraction(void)
{
    u8   buf[8];
    u8   dst;
    bool status;

    printf(LOG_PREFIX_CSTR "U8_BlockExtraction -> ");

    buf[0] = U8_C(10);
    buf[1] = U8_C(20);
    buf[2] = U8_C(30);
    buf[3] = U8_C(40);
    buf[4] = U8_C(50);
    buf[5] = U8_C(60);
    buf[6] = U8_C(70);
    buf[7] = U8_C(80);

    /* Get element at byte index 0 (0 % 1 == 0, aligned) */
    dst    = U8_C(0);
    status = kdGenMemOpsBlockAt(&dst, buf, USIZE_C(8), USIZE_C(0), sizeof(u8));
    assert(status == RESULT_SUCCESS);
    assert(dst == U8_C(10));

    /* Get element at byte index 3 (3 % 1 == 0, aligned) */
    dst    = U8_C(0);
    status = kdGenMemOpsBlockAt(&dst, buf, USIZE_C(8), USIZE_C(3), sizeof(u8));
    assert(status == RESULT_SUCCESS);
    assert(dst == U8_C(40));

    /* Get element at byte index 7 (7 % 1 == 0, aligned) */
    dst    = U8_C(0);
    status = kdGenMemOpsBlockAt(&dst, buf, USIZE_C(8), USIZE_C(7), sizeof(u8));
    assert(status == RESULT_SUCCESS);
    assert(dst == U8_C(80));

    printf("PASSED\n");
}


void
U16_BlockExtraction(void)
{
    u16  buf[4];
    u16  dst;
    bool status;

    printf(LOG_PREFIX_CSTR "U16_BlockExtraction -> ");

    buf[0] = U16_C(100);
    buf[1] = U16_C(200);
    buf[2] = U16_C(300);
    buf[3] = U16_C(400);

    /* Get element at byte index 0 (element 0, 0 % 2 == 0, aligned) */
    dst    = U16_C(0);
    status = kdGenMemOpsBlockAt(&dst, buf, sizeof(buf), USIZE_C(0), sizeof(u16));
    assert(status == RESULT_SUCCESS);
    assert(dst == U16_C(100));

    /* Get element at byte index sizeof(u16)*2 (element 2, aligned to sizeof(u16)) */
    dst    = U16_C(0);
    status = kdGenMemOpsBlockAt(&dst, buf, sizeof(buf), USIZE_C(2) * sizeof(u16), sizeof(u16));
    assert(status == RESULT_SUCCESS);
    assert(dst == U16_C(300));

    /* Get element at byte index sizeof(u16)*3 (element 3, aligned to sizeof(u16)) */
    dst    = U16_C(0);
    status = kdGenMemOpsBlockAt(&dst, buf, sizeof(buf), USIZE_C(3) * sizeof(u16), sizeof(u16));
    assert(status == RESULT_SUCCESS);
    assert(dst == U16_C(400));

    printf("PASSED\n");
}


void
U32_BlockExtraction(void)
{
    u32  buf[5];
    u32  dst;
    bool status;

    printf(LOG_PREFIX_CSTR "U32_BlockExtraction -> ");

    buf[0] = U32_C(1000);
    buf[1] = U32_C(2000);
    buf[2] = U32_C(3000);
    buf[3] = U32_C(4000);
    buf[4] = U32_C(5000);

    /* Get element at byte index 0 (element 0, 0 % 4 == 0, aligned) */
    dst    = U32_C(0);
    status = kdGenMemOpsBlockAt(&dst, buf, sizeof(buf), USIZE_C(0), sizeof(u32));
    assert(status == RESULT_SUCCESS);
    assert(dst == U32_C(1000));

    /* Get element at byte index sizeof(u32)*2 (element 2, aligned to sizeof(u32)) */
    dst    = U32_C(0);
    status = kdGenMemOpsBlockAt(&dst, buf, sizeof(buf), USIZE_C(2) * sizeof(u32), sizeof(u32));
    assert(status == RESULT_SUCCESS);
    assert(dst == U32_C(3000));

    /* Get element at byte index sizeof(u32)*4 (element 4, aligned to sizeof(u32)) */
    dst    = U32_C(0);
    status = kdGenMemOpsBlockAt(&dst, buf, sizeof(buf), USIZE_C(4) * sizeof(u32), sizeof(u32));
    assert(status == RESULT_SUCCESS);
    assert(dst == U32_C(5000));

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_BlockExtraction(void)
{
    u64  buf[3];
    u64  dst;
    bool status;

    printf(LOG_PREFIX_CSTR "U64_BlockExtraction -> ");

    buf[0] = U64_C(0x1111111111111111);
    buf[1] = U64_C(0x2222222222222222);
    buf[2] = U64_C(0x3333333333333333);

    /* Get element at byte index 0 (element 0, 0 % 8 == 0, aligned) */
    dst    = U64_C(0);
    status = kdGenMemOpsBlockAt(&dst, buf, sizeof(buf), USIZE_C(0), sizeof(u64));
    assert(status == RESULT_SUCCESS);
    assert(dst == U64_C(0x1111111111111111));

    /* Get element at byte index sizeof(u64)*1 (element 1, aligned to sizeof(u64)) */
    dst    = U64_C(0);
    status = kdGenMemOpsBlockAt(&dst, buf, sizeof(buf), USIZE_C(1) * sizeof(u64), sizeof(u64));
    assert(status == RESULT_SUCCESS);
    assert(dst == U64_C(0x2222222222222222));

    /* Get element at byte index sizeof(u64)*2 (element 2, aligned to sizeof(u64)) */
    dst    = U64_C(0);
    status = kdGenMemOpsBlockAt(&dst, buf, sizeof(buf), USIZE_C(2) * sizeof(u64), sizeof(u64));
    assert(status == RESULT_SUCCESS);
    assert(dst == U64_C(0x3333333333333333));

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
Struct_BlockExtraction(void)
{
    kdi_TestStruct buf[3];
    kdi_TestStruct dst;
    bool           status;

    printf(LOG_PREFIX_CSTR "Struct_BlockExtraction -> ");

    /* Initialize struct array */
    buf[0].a = U32_C(10);
    buf[0].b = U32_C(20);
    buf[0].c = U16_C(30);
    buf[0].d = U8_C(40);

    buf[1].a = U32_C(0xDEADBEEF);
    buf[1].b = U32_C(0xCAFEBABE);
    buf[1].c = U16_C(12345);
    buf[1].d = U8_C(99);

    buf[2].a = U32_C(100);
    buf[2].b = U32_C(200);
    buf[2].c = U16_C(300);
    buf[2].d = U8_C(255);

    /* Get element at byte index 0 (struct 0, 0 % sizeof(struct) == 0, aligned) */
    status   = kdGenMemOpsBlockAt(&dst, buf, sizeof(buf), USIZE_C(0), sizeof(kdi_TestStruct));
    assert(status == RESULT_SUCCESS);
    assert(dst.a == U32_C(10));
    assert(dst.b == U32_C(20));
    assert(dst.c == U16_C(30));
    assert(dst.d == U8_C(40));

    /* Get element at byte index sizeof(struct)*1 (struct 1, aligned to sizeof(struct)) */
    status = kdGenMemOpsBlockAt(&dst, buf, sizeof(buf), USIZE_C(1) * sizeof(kdi_TestStruct), sizeof(kdi_TestStruct));
    assert(status == RESULT_SUCCESS);
    assert(dst.a == U32_C(0xDEADBEEF));
    assert(dst.b == U32_C(0xCAFEBABE));
    assert(dst.c == U16_C(12345));
    assert(dst.d == U8_C(99));

    /* Get element at byte index sizeof(struct)*2 (struct 2, aligned to sizeof(struct)) */
    status = kdGenMemOpsBlockAt(&dst, buf, sizeof(buf), USIZE_C(2) * sizeof(kdi_TestStruct), sizeof(kdi_TestStruct));
    assert(status == RESULT_SUCCESS);
    assert(dst.a == U32_C(100));
    assert(dst.b == U32_C(200));
    assert(dst.c == U16_C(300));
    assert(dst.d == U8_C(255));

    printf("PASSED\n");
}


void
OddBlockSizes(void)
{
    u8   buf[30];
    u8   dst[3];
    bool status;

    printf(LOG_PREFIX_CSTR "OddBlockSizes -> ");

    kdi_FillSeq_u8(buf, USIZE_C(30), U8_C(0));

    /* Block size 3 at index 0 (0 % 3 == 0, aligned) */
    status = kdGenMemOpsBlockAt(dst, buf, USIZE_C(30), USIZE_C(0), USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, &buf[0], USIZE_C(3)) == RESULT_SUCCESS);

    /* Block size 3 at index 6 (6 % 3 == 0, aligned) */
    status = kdGenMemOpsBlockAt(dst, buf, USIZE_C(30), USIZE_C(6), USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, &buf[6], USIZE_C(3)) == RESULT_SUCCESS);

    /* Block size 3 at index 27 (27 % 3 == 0, last valid, aligned) */
    status = kdGenMemOpsBlockAt(dst, buf, USIZE_C(30), USIZE_C(27), USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, &buf[27], USIZE_C(3)) == RESULT_SUCCESS);

    /* Block size 3 at index 30 (30 % 3 == 0, aligned but out of bounds) */
    status = kdGenMemOpsBlockAt(dst, buf, USIZE_C(30), USIZE_C(30), USIZE_C(3));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
BlockSize5(void)
{
    u8   buf[40];
    u8   dst[5];
    bool status;

    printf(LOG_PREFIX_CSTR "BlockSize5 -> ");

    kdi_FillSeq_u8(buf, USIZE_C(40), U8_C(0));

    /* Block size 5 at index 0 (0 % 5 == 0, aligned) */
    status = kdGenMemOpsBlockAt(dst, buf, USIZE_C(40), USIZE_C(0), USIZE_C(5));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, &buf[0], USIZE_C(5)) == RESULT_SUCCESS);

    /* Block size 5 at index 10 (10 % 5 == 0, aligned) */
    status = kdGenMemOpsBlockAt(dst, buf, USIZE_C(40), USIZE_C(10), USIZE_C(5));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, &buf[10], USIZE_C(5)) == RESULT_SUCCESS);

    /* Block size 5 at index 35 (35 % 5 == 0, last valid, aligned) */
    status = kdGenMemOpsBlockAt(dst, buf, USIZE_C(40), USIZE_C(35), USIZE_C(5));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, &buf[35], USIZE_C(5)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
FullBufferBlock(void)
{
    u8   buf[16];
    u8   dst[16];
    bool status;

    printf(LOG_PREFIX_CSTR "FullBufferBlock -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x50));

    /* Get entire buffer as one block (0 % 16 == 0, aligned) */
    status = kdGenMemOpsBlockAt(dst, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, buf, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
AllZeroBlock(void)
{
    u8   buf[12];
    u8   dst[4];
    bool status;

    printf(LOG_PREFIX_CSTR "AllZeroBlock -> ");

    kdi_Fill_u8(buf, USIZE_C(12), U8_C(0));

    /* Get 4-byte block at index 0 (0 % 4 == 0, aligned) */
    status = kdGenMemOpsBlockAt(dst, buf, USIZE_C(12), USIZE_C(0), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(dst[0] == U8_C(0));
    assert(dst[1] == U8_C(0));
    assert(dst[2] == U8_C(0));
    assert(dst[3] == U8_C(0));

    /* Get 4-byte block at index 8 (8 % 4 == 0, aligned) */
    status = kdGenMemOpsBlockAt(dst, buf, USIZE_C(12), USIZE_C(8), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(dst[0] == U8_C(0));
    assert(dst[1] == U8_C(0));
    assert(dst[2] == U8_C(0));
    assert(dst[3] == U8_C(0));

    printf("PASSED\n");
}


void
AllOnesBlock(void)
{
    u8   buf[12];
    u8   dst[4];
    bool status;

    printf(LOG_PREFIX_CSTR "AllOnesBlock -> ");

    kdi_Fill_u8(buf, USIZE_C(12), U8_C(0xFF));

    /* Get 4-byte block at index 4 (4 % 4 == 0, aligned) */
    status = kdGenMemOpsBlockAt(dst, buf, USIZE_C(12), USIZE_C(4), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(dst[0] == U8_C(0xFF));
    assert(dst[1] == U8_C(0xFF));
    assert(dst[2] == U8_C(0xFF));
    assert(dst[3] == U8_C(0xFF));

    printf("PASSED\n");
}


void
MultipleCallsSameBuffer(void)
{
    u8   buf[16];
    u8   dst1[4];
    u8   dst2[4];
    u8   dst3[4];
    bool status;

    printf(LOG_PREFIX_CSTR "MultipleCallsSameBuffer -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0));

    /* Extract multiple blocks from same buffer, all aligned */
    /* Index 0 (0 % 4 == 0, aligned) */
    status = kdGenMemOpsBlockAt(dst1, buf, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Index 4 (4 % 4 == 0, aligned) */
    status = kdGenMemOpsBlockAt(dst2, buf, USIZE_C(16), USIZE_C(4), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Index 8 (8 % 4 == 0, aligned) */
    status = kdGenMemOpsBlockAt(dst3, buf, USIZE_C(16), USIZE_C(8), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Verify each block */
    assert(kdi_BytesEqual(dst1, &buf[0], USIZE_C(4)) == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst2, &buf[4], USIZE_C(4)) == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst3, &buf[8], USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
OverwriteDestination(void)
{
    u8   buf[12];
    u8   dst[4];
    bool status;

    printf(LOG_PREFIX_CSTR "OverwriteDestination -> ");

    kdi_FillSeq_u8(buf, USIZE_C(12), U8_C(10));

    /* Fill destination with sentinel values */
    kdi_Fill_u8(dst, USIZE_C(4), U8_C(0xFF));

    /* Extract block at index 4 (4 % 4 == 0, aligned), should overwrite destination */
    status = kdGenMemOpsBlockAt(dst, buf, USIZE_C(12), USIZE_C(4), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(dst[0] == U8_C(14)); /* 10 + 4 */
    assert(dst[1] == U8_C(15)); /* 10 + 5 */
    assert(dst[2] == U8_C(16)); /* 10 + 6 */
    assert(dst[3] == U8_C(17)); /* 10 + 7 */

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    ValidBlockAtStart();
    ValidBlockAtMiddle();
    ValidBlockAtEnd();
    IndexOutOfBounds();
    UnalignedIndex();
    SingleByteBlock();
    LargeBlock();
    U8_BlockExtraction();
    U16_BlockExtraction();
    U32_BlockExtraction();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_BlockExtraction();
#endif
    Struct_BlockExtraction();
    OddBlockSizes();
    BlockSize5();
    FullBufferBlock();
    AllZeroBlock();
    AllOnesBlock();
    MultipleCallsSameBuffer();
    OverwriteDestination();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
