/**
 * @file kdGenMemOpsInsertBlockAt.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsInsertBlockAt function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsInsertBlockAt function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8    buf[16];
    u8    src[4];
    usize len = 0;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0));
    kdi_FillSeq_u8(src, USIZE_C(4), U8_C(0xFF));

    /* base is null -> failure */
    status = kdGenMemOpsInsertBlockAt(null, USIZE_C(16), &len, USIZE_C(0), src, USIZE_C(4), false);
    assert(status == RESULT_FAILURE);

    /* base_elems pointer is null -> failure */
    status = kdGenMemOpsInsertBlockAt(buf, USIZE_C(16), null, USIZE_C(0), src, USIZE_C(4), false);
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    status = kdGenMemOpsInsertBlockAt(buf, USIZE_C(16), &len, USIZE_C(0), null, USIZE_C(4), false);
    assert(status == RESULT_FAILURE);

    /* base_cap is zero -> failure */
    status = kdGenMemOpsInsertBlockAt(buf, USIZE_C(0), &len, USIZE_C(0), src, USIZE_C(4), false);
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = kdGenMemOpsInsertBlockAt(buf, USIZE_C(16), &len, USIZE_C(0), src, USIZE_C(0), false);
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
InsertIntoEmpty(void)
{
    u8    buf[16];
    u8    src[4];
    usize len = 0;
    bool  status;

    printf(LOG_PREFIX_CSTR "InsertIntoEmpty -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0));
    kdi_Fill_u8(src, USIZE_C(4), U8_C(0xAA));

    /* Insert at index 0 (0 % 4 == 0, aligned) */
    status = kdGenMemOpsInsertBlockAt(buf, USIZE_C(16), &len, USIZE_C(0), src, USIZE_C(4), false);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(4));
    assert(kdi_BytesEqual(buf, src, USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
InsertAtStart(void)
{
    u8    buf[32];
    u8    src[4];
    usize len = 12;
    bool  status;

    printf(LOG_PREFIX_CSTR "InsertAtStart -> ");

    /* Init: [01, 01, 01, 01], [02, 02, 02, 02], [03, 03, 03, 03] */
    kdi_Fill_u8(&buf[0], USIZE_C(4), U8_C(1));
    kdi_Fill_u8(&buf[4], USIZE_C(4), U8_C(2));
    kdi_Fill_u8(&buf[8], USIZE_C(4), U8_C(3));

    kdi_Fill_u8(src, USIZE_C(4), U8_C(0xFF));

    /* Insert at index 0 (0 % 4 == 0, aligned) */
    status = kdGenMemOpsInsertBlockAt(buf, USIZE_C(32), &len, USIZE_C(0), src, USIZE_C(4), false);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(16));
    /* Check new head */
    assert(buf[0] == U8_C(0xFF));
    assert(buf[1] == U8_C(0xFF));
    /* Check shifted blocks */
    assert(buf[4] == U8_C(1));
    assert(buf[8] == U8_C(2));
    assert(buf[12] == U8_C(3));

    printf("PASSED\n");
}


void
InsertAtEnd(void)
{
    u8    buf[16];
    u8    src[4];
    usize len = 8;
    bool  status;

    printf(LOG_PREFIX_CSTR "InsertAtEnd -> ");

    kdi_FillSeq_u8(buf, USIZE_C(8), U8_C(0x10));
    kdi_Fill_u8(src, USIZE_C(4), U8_C(0xFF));

    /* Insert at index 8 (8 % 4 == 0, aligned, append) */
    status = kdGenMemOpsInsertBlockAt(buf, USIZE_C(16), &len, USIZE_C(8), src, USIZE_C(4), false);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(12));
    assert(buf[0] == U8_C(0x10));
    assert(buf[7] == U8_C(0x17));
    assert(buf[8] == U8_C(0xFF));
    assert(buf[11] == U8_C(0xFF));

    printf("PASSED\n");
}


void
InsertAtMiddle(void)
{
    u8    buf[16];
    u8    src[4];
    usize len = 8;
    bool  status;

    printf(LOG_PREFIX_CSTR "InsertAtMiddle -> ");

    kdi_Fill_u8(&buf[0], USIZE_C(4), U8_C(1));
    kdi_Fill_u8(&buf[4], USIZE_C(4), U8_C(2));
    kdi_Fill_u8(src, USIZE_C(4), U8_C(0xFF));

    /* Insert at index 4 (4 % 4 == 0, aligned) */
    status = kdGenMemOpsInsertBlockAt(buf, USIZE_C(16), &len, USIZE_C(4), src, USIZE_C(4), false);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(12));
    assert(buf[0] == U8_C(1));
    assert(buf[4] == U8_C(0xFF));
    assert(buf[8] == U8_C(2));

    printf("PASSED\n");
}


void
IndexOutOfBounds(void)
{
    u8    buf[16];
    u8    src[4];
    usize len = 8;
    bool  status;

    printf(LOG_PREFIX_CSTR "IndexOutOfBounds -> ");

    kdi_Fill_u8(buf, USIZE_C(8), U8_C(1));
    kdi_Fill_u8(src, USIZE_C(4), U8_C(0xFF));

    /* Valid: insert at index 8 (8 % 4 == 0, aligned, append) */
    status = kdGenMemOpsInsertBlockAt(buf, USIZE_C(16), &len, USIZE_C(8), src, USIZE_C(4), false);
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(12));

    /* Invalid: insert at index 16 (gap at 12) */
    status = kdGenMemOpsInsertBlockAt(buf, USIZE_C(16), &len, USIZE_C(16), src, USIZE_C(4), false);
    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(12));

    printf("PASSED\n");
}


void
UnalignedIndex(void)
{
    u8    buf[16];
    u8    src[4];
    usize len = 8;
    bool  status;

    printf(LOG_PREFIX_CSTR "UnalignedIndex -> ");

    kdi_Fill_u8(buf, USIZE_C(8), U8_C(1));
    kdi_Fill_u8(src, USIZE_C(4), U8_C(0xFF));

    /* Invalid: index 1 (1 % 4 != 0, unaligned) */
    status = kdGenMemOpsInsertBlockAt(buf, USIZE_C(16), &len, USIZE_C(1), src, USIZE_C(4), false);
    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(8));

    /* Invalid: index 2 (2 % 4 != 0, unaligned) */
    status = kdGenMemOpsInsertBlockAt(buf, USIZE_C(16), &len, USIZE_C(2), src, USIZE_C(4), false);
    assert(status == RESULT_FAILURE);

    /* Invalid: index 6 (6 % 4 != 0, unaligned) */
    status = kdGenMemOpsInsertBlockAt(buf, USIZE_C(16), &len, USIZE_C(6), src, USIZE_C(4), false);
    assert(status == RESULT_FAILURE);

    /* Verify buffer unchanged */
    assert(buf[0] == U8_C(1));

    printf("PASSED\n");
}


void
BufferFull_NoTruncate(void)
{
    u32   buf[4];
    u32   src = 99;
    usize len = 16;
    bool  status;

    printf(LOG_PREFIX_CSTR "BufferFull_NoTruncate -> ");

    buf[0] = U32_C(1);
    buf[1] = U32_C(2);
    buf[2] = U32_C(3);
    buf[3] = U32_C(4);

    /* Try to insert when buffer full (16 % 4 == 0, aligned but full) */
    status = kdGenMemOpsInsertBlockAt(buf, USIZE_C(16), &len, USIZE_C(0), &src, sizeof(u32), false);

    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(16));
    assert(buf[0] == U32_C(1));

    printf("PASSED\n");
}


void
BufferFull_Truncate(void)
{
    u32   buf[4];
    u32   src = 99;
    usize len = 16;
    bool  status;

    printf(LOG_PREFIX_CSTR "BufferFull_Truncate -> ");

    buf[0] = U32_C(1);
    buf[1] = U32_C(2);
    buf[2] = U32_C(3);
    buf[3] = U32_C(4);

    /* Insert at index 4 (4 % 4 == 0, aligned) with truncate */
    /* Expect: 1, 99, 2, 3 (4 truncated) */
    status = kdGenMemOpsInsertBlockAt(buf, USIZE_C(16), &len, USIZE_C(4), &src, sizeof(u32), true);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(16));
    assert(buf[0] == U32_C(1));
    assert(buf[1] == U32_C(99));
    assert(buf[2] == U32_C(2));
    assert(buf[3] == U32_C(3));

    printf("PASSED\n");
}


void
SingleByteBlock(void)
{
    u8    buf[8];
    u8    val;
    usize len = 4;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleByteBlock -> ");

    kdi_FillSeq_u8(buf, USIZE_C(4), U8_C(10));

    /* Insert single byte at index 2 (2 % 1 == 0, aligned) */
    val    = U8_C(0xFF);
    status = kdGenMemOpsInsertBlockAt(buf, USIZE_C(8), &len, USIZE_C(2), &val, USIZE_C(1), false);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(5));
    assert(buf[0] == U8_C(10));
    assert(buf[1] == U8_C(11));
    assert(buf[2] == U8_C(0xFF));
    assert(buf[3] == U8_C(12));
    assert(buf[4] == U8_C(13));

    printf("PASSED\n");
}


void
U8_BlockInsert(void)
{
    u8    buf[8];
    u8    val;
    usize len = 4;
    bool  status;

    printf(LOG_PREFIX_CSTR "U8_BlockInsert -> ");

    buf[0] = U8_C(10);
    buf[1] = U8_C(20);
    buf[2] = U8_C(30);
    buf[3] = U8_C(40);

    /* Insert at index 0 (0 % 1 == 0, aligned) */
    val    = U8_C(5);
    status = kdGenMemOpsInsertBlockAt(buf, USIZE_C(8), &len, USIZE_C(0), &val, sizeof(u8), false);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(5));
    assert(buf[0] == U8_C(5));
    assert(buf[1] == U8_C(10));
    assert(buf[2] == U8_C(20));

    printf("PASSED\n");
}


void
U16_BlockInsert(void)
{
    u16   buf[6];
    u16   val;
    usize len = 6;
    bool  status;

    printf(LOG_PREFIX_CSTR "U16_BlockInsert -> ");

    buf[0] = U16_C(100);
    buf[1] = U16_C(200);
    buf[2] = U16_C(300);

    /* Insert at index sizeof(u16)*1 (aligned to sizeof(u16)) */
    val    = U16_C(999);
    status = kdGenMemOpsInsertBlockAt(buf, USIZE_C(12), &len, sizeof(u16) * USIZE_C(1), &val, sizeof(u16), false);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(8));
    assert(buf[0] == U16_C(100));
    assert(buf[1] == U16_C(999));
    assert(buf[2] == U16_C(200));
    assert(buf[3] == U16_C(300));

    printf("PASSED\n");
}


void
U32_BlockInsert(void)
{
    u32   buf[6];
    u32   val;
    usize len = 8;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_BlockInsert -> ");

    buf[0] = U32_C(10);
    buf[1] = U32_C(20);

    /* Insert at index 0 (0 % 4 == 0, aligned) */
    val    = U32_C(5);
    status = kdGenMemOpsInsertBlockAt(buf, USIZE_C(24), &len, USIZE_C(0), &val, sizeof(u32), false);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(12));
    assert(buf[0] == U32_C(5));
    assert(buf[1] == U32_C(10));
    assert(buf[2] == U32_C(20));

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_BlockInsert(void)
{
    u64   buf[4];
    u64   val;
    usize len = 16;
    bool  status;

    printf(LOG_PREFIX_CSTR "U64_BlockInsert -> ");

    buf[0] = U64_C(0x1111111111111111);
    buf[1] = U64_C(0x2222222222222222);

    /* Insert at index sizeof(u64)*1 (aligned to sizeof(u64)) */
    val    = U64_C(0x9999999999999999);
    status = kdGenMemOpsInsertBlockAt(buf, USIZE_C(32), &len, sizeof(u64) * USIZE_C(1), &val, sizeof(u64), false);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(24));
    assert(buf[0] == U64_C(0x1111111111111111));
    assert(buf[1] == U64_C(0x9999999999999999));
    assert(buf[2] == U64_C(0x2222222222222222));

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
Struct_BlockInsert(void)
{
    kdi_TestStruct buf[4];
    kdi_TestStruct val;
    usize          len;
    usize          elem_sz = sizeof(kdi_TestStruct);
    usize          cap     = 4 * sizeof(kdi_TestStruct);
    bool           status;

    printf(LOG_PREFIX_CSTR "Struct_BlockInsert -> ");

    /* Init: 2 elements used */
    len      = 2 * elem_sz;
    buf[0].a = U32_C(10);
    buf[0].b = U32_C(20);
    buf[0].c = U16_C(30);
    buf[0].d = U8_C(40);

    buf[1].a = U32_C(50);
    buf[1].b = U32_C(60);
    buf[1].c = U16_C(70);
    buf[1].d = U8_C(80);

    /* Prepare value to insert */
    val.a    = U32_C(0xDEADBEEF);
    val.b    = U32_C(0xCAFEBABE);
    val.c    = U16_C(12345);
    val.d    = U8_C(99);

    /* Insert at index elem_sz (aligned to sizeof(struct)) */
    status   = kdGenMemOpsInsertBlockAt(buf, cap, &len, elem_sz, &val, elem_sz, false);

    assert(status == RESULT_SUCCESS);
    assert(len == 3 * elem_sz);
    assert(buf[0].a == U32_C(10));
    assert(buf[1].a == U32_C(0xDEADBEEF));
    assert(buf[1].b == U32_C(0xCAFEBABE));
    assert(buf[1].c == U16_C(12345));
    assert(buf[1].d == U8_C(99));
    assert(buf[2].a == U32_C(50));

    printf("PASSED\n");
}


void
OddBlockSizes(void)
{
    u8    buf[30];
    u8    src[3];
    usize len = 12;
    bool  status;

    printf(LOG_PREFIX_CSTR "OddBlockSizes -> ");

    kdi_FillSeq_u8(buf, USIZE_C(12), U8_C(0));
    kdi_Fill_u8(src, USIZE_C(3), U8_C(0xFF));

    /* Block size 3, insert at index 6 (6 % 3 == 0, aligned) */
    status = kdGenMemOpsInsertBlockAt(buf, USIZE_C(30), &len, USIZE_C(6), src, USIZE_C(3), false);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(15));
    assert(buf[5] == U8_C(5));
    assert(buf[6] == U8_C(0xFF));
    assert(buf[7] == U8_C(0xFF));
    assert(buf[8] == U8_C(0xFF));
    assert(buf[9] == U8_C(6));

    printf("PASSED\n");
}


void
BlockSize5(void)
{
    u8    buf[40];
    u8    src[5];
    usize len = 10;
    bool  status;

    printf(LOG_PREFIX_CSTR "BlockSize5 -> ");

    kdi_FillSeq_u8(buf, USIZE_C(10), U8_C(0));
    kdi_Fill_u8(src, USIZE_C(5), U8_C(0xAA));

    /* Block size 5, insert at index 5 (5 % 5 == 0, aligned) */
    status = kdGenMemOpsInsertBlockAt(buf, USIZE_C(40), &len, USIZE_C(5), src, USIZE_C(5), false);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(15));
    assert(buf[4] == U8_C(4));
    assert(buf[5] == U8_C(0xAA));
    assert(buf[9] == U8_C(0xAA));
    assert(buf[10] == U8_C(5));

    printf("PASSED\n");
}


void
MultipleInserts(void)
{
    u32   buf[8];
    u32   val;
    usize len = 0;
    bool  status;

    printf(LOG_PREFIX_CSTR "MultipleInserts -> ");

    kdi_Fill_u8((u8 *)buf, USIZE_C(32), U8_C(0));

    /* Build: 10, 20, 30 */
    val    = U32_C(10);
    status = kdGenMemOpsInsertBlockAt(buf, USIZE_C(32), &len, USIZE_C(0), &val, sizeof(u32), false);
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(4));

    val    = U32_C(20);
    status = kdGenMemOpsInsertBlockAt(buf, USIZE_C(32), &len, USIZE_C(4), &val, sizeof(u32), false);
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(8));

    val    = U32_C(30);
    status = kdGenMemOpsInsertBlockAt(buf, USIZE_C(32), &len, USIZE_C(8), &val, sizeof(u32), false);
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(12));

    /* Verify */
    assert(buf[0] == U32_C(10));
    assert(buf[1] == U32_C(20));
    assert(buf[2] == U32_C(30));

    printf("PASSED\n");
}


void
TruncateAtStart(void)
{
    u32   buf[4];
    u32   val;
    usize len = 16;
    bool  status;

    printf(LOG_PREFIX_CSTR "TruncateAtStart -> ");

    buf[0] = U32_C(1);
    buf[1] = U32_C(2);
    buf[2] = U32_C(3);
    buf[3] = U32_C(4);

    /* Insert at index 0 with truncate */
    /* Expect: 99, 1, 2, 3 (4 falls off) */
    val    = U32_C(99);
    status = kdGenMemOpsInsertBlockAt(buf, USIZE_C(16), &len, USIZE_C(0), &val, sizeof(u32), true);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(16));
    assert(buf[0] == U32_C(99));
    assert(buf[1] == U32_C(1));
    assert(buf[2] == U32_C(2));
    assert(buf[3] == U32_C(3));

    printf("PASSED\n");
}


void
TruncateAtMiddle(void)
{
    u32   buf[4];
    u32   val;
    usize len = 16;
    bool  status;

    printf(LOG_PREFIX_CSTR "TruncateAtMiddle -> ");

    buf[0] = U32_C(1);
    buf[1] = U32_C(2);
    buf[2] = U32_C(3);
    buf[3] = U32_C(4);

    /* Insert at index 8 (index 2) with truncate */
    /* Expect: 1, 2, 99, 3 (4 falls off) */
    val    = U32_C(99);
    status = kdGenMemOpsInsertBlockAt(buf, USIZE_C(16), &len, USIZE_C(8), &val, sizeof(u32), true);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(16));
    assert(buf[0] == U32_C(1));
    assert(buf[1] == U32_C(2));
    assert(buf[2] == U32_C(99));
    assert(buf[3] == U32_C(3));

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    InsertIntoEmpty();
    InsertAtStart();
    InsertAtEnd();
    InsertAtMiddle();
    IndexOutOfBounds();
    UnalignedIndex();
    BufferFull_NoTruncate();
    BufferFull_Truncate();
    SingleByteBlock();
    U8_BlockInsert();
    U16_BlockInsert();
    U32_BlockInsert();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_BlockInsert();
#endif
    Struct_BlockInsert();
    OddBlockSizes();
    BlockSize5();
    MultipleInserts();
    TruncateAtStart();
    TruncateAtMiddle();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
