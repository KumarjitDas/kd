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


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsInsertBlockAt function test"
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
BasicArguments(void)
{
    u8    buf[16];
    u8    src[4];
    usize len = 0;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));
    kdi_FillSeq(src, USIZE_C(4), U8_C(0xFF));

    /* base is null -> failure */
    status = GenMemOpsInsertBlockAt(null, USIZE_C(16), &len, USIZE_C(0), src, USIZE_C(4), false);
    assert(status == RESULT_FAILURE);

    /* base_elems pointer is null -> failure */
    status = GenMemOpsInsertBlockAt(buf, USIZE_C(16), null, USIZE_C(0), src, USIZE_C(4), false);
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    status = GenMemOpsInsertBlockAt(buf, USIZE_C(16), &len, USIZE_C(0), null, USIZE_C(4), false);
    assert(status == RESULT_FAILURE);

    /* base_cap is zero -> failure */
    status = GenMemOpsInsertBlockAt(buf, USIZE_C(0), &len, USIZE_C(0), src, USIZE_C(4), false);
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = GenMemOpsInsertBlockAt(buf, USIZE_C(16), &len, USIZE_C(0), src, USIZE_C(0), false);
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

    /* Init src: 0xAA */
    src[0] = 0xAA;
    src[1] = 0xAA;
    src[2] = 0xAA;
    src[3] = 0xAA;

    status = GenMemOpsInsertBlockAt(buf, USIZE_C(16), &len, USIZE_C(0), src, USIZE_C(4), false);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(4));

    assert(buf[0] == 0xAA);
    assert(buf[1] == 0xAA);
    assert(buf[2] == 0xAA);
    assert(buf[3] == 0xAA);

    printf("PASSED\n");
}


void
InsertHead(void)
{
    u8    buf[32];
    u8    src[4];
    usize len = 12;
    bool  status;

    printf(LOG_PREFIX_CSTR "InsertHead -> ");

    /* Init [01.., 02.., 03..] */
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

    /* Src: 0xFF */
    src[0]  = 0xFF;
    src[1]  = 0xFF;
    src[2]  = 0xFF;
    src[3]  = 0xFF;

    status  = GenMemOpsInsertBlockAt(buf, USIZE_C(16), &len, USIZE_C(0), src, USIZE_C(4), false);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(16));

    /* Check new head */
    assert(buf[0] == 0xFF);
    /* Check shifted */
    assert(buf[4] == 1);
    assert(buf[8] == 2);
    assert(buf[12] == 3);

    printf("PASSED\n");
}


void
InsertTail(void)
{
    u8    buf[16];
    u8    src[4];
    usize len = 8;
    bool  status;

    printf(LOG_PREFIX_CSTR "InsertTail -> ");

    kdi_FillSeq(buf, USIZE_C(8), U8_C(0x10));
    src[0] = 0xFF;
    src[1] = 0xFF;
    src[2] = 0xFF;
    src[3] = 0xFF;

    /* Insert at Offset 8 */
    status = GenMemOpsInsertBlockAt(buf, USIZE_C(16), &len, USIZE_C(8), src, USIZE_C(4), false);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(12));

    assert(buf[0] == 0x10);
    assert(buf[8] == 0xFF);

    printf("PASSED\n");
}


void
InsertMiddle(void)
{
    u8    buf[16];
    u8    src[4];
    usize len = 8;
    bool  status;

    printf(LOG_PREFIX_CSTR "InsertMiddle -> ");

    buf[0] = 1;
    buf[1] = 1;
    buf[2] = 1;
    buf[3] = 1;
    buf[4] = 2;
    buf[5] = 2;
    buf[6] = 2;
    buf[7] = 2;

    src[0] = 0xFF;
    src[1] = 0xFF;
    src[2] = 0xFF;
    src[3] = 0xFF;

    /* Insert at Offset 4 */
    status = GenMemOpsInsertBlockAt(buf, USIZE_C(16), &len, USIZE_C(4), src, USIZE_C(4), false);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(12));

    assert(buf[0] == 1);
    assert(buf[4] == 0xFF);
    assert(buf[8] == 2);

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

    buf[0] = 1;
    buf[1] = 2;
    buf[2] = 3;
    buf[3] = 4;

    status = GenMemOpsInsertBlockAt(buf, USIZE_C(16), &len, USIZE_C(0), &src, sizeof(u32), false);

    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(16));
    assert(buf[0] == 1);

    printf("PASSED\n");
}


void
BufferFull_Truncate(void)
{
    u32   buf[4];
    u32   src = 99;
    usize len = 16;
    u32   expected[4];
    bool  status;

    printf(LOG_PREFIX_CSTR "BufferFull_Truncate -> ");

    buf[0]      = 1;
    buf[1]      = 2;
    buf[2]      = 3;
    buf[3]      = 4;

    /* Insert at offset 4 (index 1) */
    /* Expect: 1, 99, 2, 3 (4 truncated) */
    expected[0] = 1;
    expected[1] = 99;
    expected[2] = 2;
    expected[3] = 3;

    status      = GenMemOpsInsertBlockAt(buf, USIZE_C(16), &len, USIZE_C(4), &src, sizeof(u32), true);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(16));
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
OutOfBounds(void)
{
    u32   buf[4];
    u32   src = 99;
    usize len = 8; /* 2 elems */
    bool  status;

    printf(LOG_PREFIX_CSTR "OutOfBounds -> ");

    buf[0] = 1;
    buf[1] = 2;

    /* Insert at offset 12 (index 3). Gap at index 2 (offset 8). */
    status = GenMemOpsInsertBlockAt(buf, USIZE_C(16), &len, USIZE_C(12), &src, sizeof(u32), false);

    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(8));

    printf("PASSED\n");
}


void
U16_Insert(void)
{
    u16   buf[4];
    u16   src = 999;
    usize len = 6; /* 3 elements: 100, 200, 300 */
    usize cap = 8;
    bool  status;

    printf(LOG_PREFIX_CSTR "U16_Insert -> ");

    buf[0] = 100;
    buf[1] = 200;
    buf[2] = 300;

    /* Insert 999 at Index 1 (Offset 2 bytes) */
    /* Expect: 100, 999, 200, 300 */
    status = GenMemOpsInsertBlockAt(buf, cap, &len, sizeof(u16) * 1, &src, sizeof(u16), false);

    assert(status == RESULT_SUCCESS);
    assert(len == 8);
    assert(buf[0] == 100);
    assert(buf[1] == 999);
    assert(buf[2] == 200);
    assert(buf[3] == 300);

    printf("PASSED\n");
}


void
U32_Insert(void)
{
    u32   buf[4];
    u32   src = 55;
    usize len = 8; /* 2 elements: 10, 20 */
    usize cap = 16;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_Insert -> ");

    buf[0] = 10;
    buf[1] = 20;

    /* Insert 55 at Index 0 (Offset 0 bytes) */
    /* Expect: 55, 10, 20 */
    status = GenMemOpsInsertBlockAt(buf, cap, &len, 0, &src, sizeof(u32), false);

    assert(status == RESULT_SUCCESS);
    assert(len == 12);
    assert(buf[0] == 55);
    assert(buf[1] == 10);
    assert(buf[2] == 20);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_Insert(void)
{
    u64   buf[4];
    u64   src = U64_C(0x9999999999999999);
    usize len = 16; /* 2 elements */
    usize cap = 32;
    bool  status;

    printf(LOG_PREFIX_CSTR "U64_Insert -> ");

    buf[0] = U64_C(0x1111111111111111);
    buf[1] = U64_C(0x2222222222222222);

    /* Insert at Index 1 (Offset 8 bytes) */
    /* Expect: 11.., 99.., 22.. */
    status = GenMemOpsInsertBlockAt(buf, cap, &len, sizeof(u64) * 1, &src, sizeof(u64), false);

    assert(status == RESULT_SUCCESS);
    assert(len == 24);
    assert(buf[0] == U64_C(0x1111111111111111));
    assert(buf[1] == U64_C(0x9999999999999999));
    assert(buf[2] == U64_C(0x2222222222222222));

    printf("PASSED\n");
}
#endif


typedef struct kdi_LargeStruct
{
    u64 a;
    u64 b;
    u32 c;
    u8  d;
} kdi_LargeStruct;


void
Struct_Insert(void)
{
    kdi_LargeStruct buf[3];
    kdi_LargeStruct src;
    usize           len;
    usize           elem_sz = sizeof(kdi_LargeStruct);
    usize           cap     = 3 * sizeof(kdi_LargeStruct);
    bool            status;

    printf(LOG_PREFIX_CSTR "Struct_Insert -> ");

    /* Init: 2 elements used */
    len      = 2 * elem_sz;
    buf[0].a = 0;
    buf[0].b = 0;
    buf[1].a = 1;
    buf[1].b = 1;

    /* Src */
    src.a    = 0xDEADBEEF;
    src.b    = 0xCAFEBABE;
    src.c    = 123;
    src.d    = 1;

    /* Insert at Offset = elem_sz (Index 1). [S0, S_NEW, S1] */
    status   = GenMemOpsInsertBlockAt(buf, cap, &len, elem_sz, &src, elem_sz, false);

    assert(status == RESULT_SUCCESS);
    assert(len == 3 * elem_sz);

    assert(buf[0].a == 0);

    assert(buf[1].a == 0xDEADBEEF);
    assert(buf[1].b == 0xCAFEBABE);

    assert(buf[2].a == 1);

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
    InsertHead();
    InsertTail();
    InsertMiddle();
    BufferFull_NoTruncate();
    BufferFull_Truncate();
    OutOfBounds();

    U16_Insert();
    U32_Insert();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_Insert();
#endif
    Struct_Insert();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
