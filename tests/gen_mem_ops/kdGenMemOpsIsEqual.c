/**
 * @file kdGenMemOpsIsEqual.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsIsEqual function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsIsEqual function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
ResultNull(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool status;

    printf(LOG_PREFIX_CSTR "ResultNull -> ");

    /* result is null -> failure */
    status = GenMemOpsIsEqual(null, buf1, buf2, USIZE_C(8));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
Ptr1Null(void)
{
    u8   buf2[8];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "Ptr1Null -> ");

    /* ptr_1 is null -> failure */
    status = GenMemOpsIsEqual(&result, null, buf2, USIZE_C(8));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
Ptr2Null(void)
{
    u8   buf1[8];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "Ptr2Null -> ");

    /* ptr_2 is null -> failure */
    status = GenMemOpsIsEqual(&result, buf1, null, USIZE_C(8));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
BothPtrsNull(void)
{
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "BothPtrsNull -> ");

    /* Both pointers null -> failure */
    status = GenMemOpsIsEqual(&result, null, null, USIZE_C(8));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SizeZero(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "SizeZero -> ");

    /* sz is zero -> failure */
    status = GenMemOpsIsEqual(&result, buf1, buf2, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
EqualBuffers(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "EqualBuffers -> ");

    /* Init: both with same sequence */
    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x00));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x00));

    status = GenMemOpsIsEqual(&result, buf1, buf2, USIZE_C(8));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
DifferentBuffers(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "DifferentBuffers -> ");

    /* Init: different sequences */
    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x00));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x10));

    status = GenMemOpsIsEqual(&result, buf1, buf2, USIZE_C(8));
    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
DifferentAtStart(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "DifferentAtStart -> ");

    /* Init: same except first byte */
    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x00));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x00));
    buf2[0] = U8_C(0xFF);

    status  = GenMemOpsIsEqual(&result, buf1, buf2, USIZE_C(8));
    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
DifferentAtEnd(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "DifferentAtEnd -> ");

    /* Init: same except last byte */
    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x00));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x00));
    buf2[7] = U8_C(0xFF);

    status  = GenMemOpsIsEqual(&result, buf1, buf2, USIZE_C(8));
    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
DifferentAtMiddle(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "DifferentAtMiddle -> ");

    /* Init: same except middle byte */
    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x00));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x00));
    buf2[4] = U8_C(0xFF);

    status  = GenMemOpsIsEqual(&result, buf1, buf2, USIZE_C(8));
    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
SamePointer(void)
{
    u8   buf[8];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "SamePointer -> ");

    /* Compare buffer with itself */
    kdi_FillSeq_u8(buf, USIZE_C(8), U8_C(0x00));

    status = GenMemOpsIsEqual(&result, buf, buf, USIZE_C(8));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
AllZeros(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "AllZeros -> ");

    /* Both buffers all zeros */
    kdi_Fill_u8(buf1, USIZE_C(16), U8_C(0x00));
    kdi_Fill_u8(buf2, USIZE_C(16), U8_C(0x00));

    status = GenMemOpsIsEqual(&result, buf1, buf2, USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
AllOnes(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "AllOnes -> ");

    /* Both buffers all 0xFF */
    kdi_Fill_u8(buf1, USIZE_C(16), U8_C(0xFF));
    kdi_Fill_u8(buf2, USIZE_C(16), U8_C(0xFF));

    status = GenMemOpsIsEqual(&result, buf1, buf2, USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
SingleByte(void)
{
    u8   val1, val2;
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "SingleByte -> ");

    /* Compare single byte - equal */
    val1   = U8_C(0x42);
    val2   = U8_C(0x42);
    status = GenMemOpsIsEqual(&result, &val1, &val2, USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Compare single byte - different */
    val1   = U8_C(0x42);
    val2   = U8_C(0x43);
    status = GenMemOpsIsEqual(&result, &val1, &val2, USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
U16_Equal(void)
{
    u16  buf1[4];
    u16  buf2[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "U16_Equal -> ");

    buf1[0] = U16_C(0x1111);
    buf1[1] = U16_C(0x2222);
    buf1[2] = U16_C(0x3333);
    buf1[3] = U16_C(0x4444);

    buf2[0] = U16_C(0x1111);
    buf2[1] = U16_C(0x2222);
    buf2[2] = U16_C(0x3333);
    buf2[3] = U16_C(0x4444);

    status  = GenMemOpsIsEqual(&result, buf1, buf2, sizeof(buf1));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
U16_Different(void)
{
    u16  buf1[4];
    u16  buf2[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "U16_Different -> ");

    buf1[0] = U16_C(0x1111);
    buf1[1] = U16_C(0x2222);
    buf1[2] = U16_C(0x3333);
    buf1[3] = U16_C(0x4444);

    buf2[0] = U16_C(0x1111);
    buf2[1] = U16_C(0x2222);
    buf2[2] = U16_C(0x3334);
    buf2[3] = U16_C(0x4444);

    status  = GenMemOpsIsEqual(&result, buf1, buf2, sizeof(buf1));
    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
U32_Equal(void)
{
    u32  buf1[3];
    u32  buf2[3];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "U32_Equal -> ");

    buf1[0] = U32_C(0x12345678);
    buf1[1] = U32_C(0xABCDEF01);
    buf1[2] = U32_C(0xDEADBEEF);

    buf2[0] = U32_C(0x12345678);
    buf2[1] = U32_C(0xABCDEF01);
    buf2[2] = U32_C(0xDEADBEEF);

    status  = GenMemOpsIsEqual(&result, buf1, buf2, sizeof(buf1));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
U32_Different(void)
{
    u32  buf1[3];
    u32  buf2[3];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "U32_Different -> ");

    buf1[0] = U32_C(0x12345678);
    buf1[1] = U32_C(0xABCDEF01);
    buf1[2] = U32_C(0xDEADBEEF);

    buf2[0] = U32_C(0x12345678);
    buf2[1] = U32_C(0xABCDEF02);
    buf2[2] = U32_C(0xDEADBEEF);

    status  = GenMemOpsIsEqual(&result, buf1, buf2, sizeof(buf1));
    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_Equal(void)
{
    u64  buf1[3];
    u64  buf2[3];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "U64_Equal -> ");

    buf1[0] = U64_C(0x123456789ABCDEF0);
    buf1[1] = U64_C(0xFEDCBA9876543210);
    buf1[2] = U64_C(0xDEADBEEFCAFEBABE);

    buf2[0] = U64_C(0x123456789ABCDEF0);
    buf2[1] = U64_C(0xFEDCBA9876543210);
    buf2[2] = U64_C(0xDEADBEEFCAFEBABE);

    status  = GenMemOpsIsEqual(&result, buf1, buf2, sizeof(buf1));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
U64_Different(void)
{
    u64  buf1[3];
    u64  buf2[3];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "U64_Different -> ");

    buf1[0] = U64_C(0x123456789ABCDEF0);
    buf1[1] = U64_C(0xFEDCBA9876543210);
    buf1[2] = U64_C(0xDEADBEEFCAFEBABE);

    buf2[0] = U64_C(0x123456789ABCDEF0);
    buf2[1] = U64_C(0xFEDCBA9876543211);
    buf2[2] = U64_C(0xDEADBEEFCAFEBABE);

    status  = GenMemOpsIsEqual(&result, buf1, buf2, sizeof(buf1));
    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}
#endif


typedef struct kdi_TestStruct
{
    u32 a;
    u16 b;
    u8  c;
    u8  d;
} kdi_TestStruct;


void
Struct_Equal(void)
{
    kdi_TestStruct s1, s2;
    bool           result;
    bool           status;

    printf(LOG_PREFIX_CSTR "Struct_Equal -> ");

    s1.a   = U32_C(100);
    s1.b   = U16_C(200);
    s1.c   = U8_C(50);
    s1.d   = U8_C(75);

    s2.a   = U32_C(100);
    s2.b   = U16_C(200);
    s2.c   = U8_C(50);
    s2.d   = U8_C(75);

    status = GenMemOpsIsEqual(&result, &s1, &s2, sizeof(kdi_TestStruct));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
Struct_Different(void)
{
    kdi_TestStruct s1, s2;
    bool           result;
    bool           status;

    printf(LOG_PREFIX_CSTR "Struct_Different -> ");

    s1.a   = U32_C(100);
    s1.b   = U16_C(200);
    s1.c   = U8_C(50);
    s1.d   = U8_C(75);

    s2.a   = U32_C(100);
    s2.b   = U16_C(200);
    s2.c   = U8_C(51);
    s2.d   = U8_C(75);

    status = GenMemOpsIsEqual(&result, &s1, &s2, sizeof(kdi_TestStruct));
    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
LargeBuffer_Equal(void)
{
    u8    buf1[256];
    u8    buf2[256];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffer_Equal -> ");

    /* Fill with same pattern */
    for (i = 0; i < 256; ++i)
    {
        buf1[i] = (u8)i;
        buf2[i] = (u8)i;
    }

    status = GenMemOpsIsEqual(&result, buf1, buf2, USIZE_C(256));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
LargeBuffer_Different(void)
{
    u8    buf1[256];
    u8    buf2[256];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffer_Different -> ");

    /* Fill with same pattern */
    for (i = 0; i < 256; ++i)
    {
        buf1[i] = (u8)i;
        buf2[i] = (u8)i;
    }

    /* Change one byte in middle */
    buf2[128] = U8_C(0xFF);

    status    = GenMemOpsIsEqual(&result, buf1, buf2, USIZE_C(256));
    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    ResultNull();
    Ptr1Null();
    Ptr2Null();
    BothPtrsNull();
    SizeZero();
    EqualBuffers();
    DifferentBuffers();
    DifferentAtStart();
    DifferentAtEnd();
    DifferentAtMiddle();
    SamePointer();
    AllZeros();
    AllOnes();
    SingleByte();

    U16_Equal();
    U16_Different();
    U32_Equal();
    U32_Different();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_Equal();
    U64_Different();
#endif

    Struct_Equal();
    Struct_Different();
    LargeBuffer_Equal();
    LargeBuffer_Different();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
