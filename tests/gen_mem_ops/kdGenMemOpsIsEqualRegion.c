/**
 * @file kdGenMemOpsIsEqualRegion.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsIsEqualRegion function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsIsEqualRegion function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
ResultNull(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool status;

    printf(LOG_PREFIX_CSTR "ResultNull -> ");

    /* result is null -> failure */
    status = GenMemOpsIsEqualRegion(null, buf1, USIZE_C(8), buf2, USIZE_C(8));
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
    status = GenMemOpsIsEqualRegion(&result, null, USIZE_C(8), buf2, USIZE_C(8));
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
    status = GenMemOpsIsEqualRegion(&result, buf1, USIZE_C(8), null, USIZE_C(8));
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
    status = GenMemOpsIsEqualRegion(&result, null, USIZE_C(8), null, USIZE_C(8));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
Ptr1SizeZero(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "Ptr1SizeZero -> ");

    /* ptr_1_sz is zero -> failure */
    status = GenMemOpsIsEqualRegion(&result, buf1, USIZE_C(0), buf2, USIZE_C(8));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
Ptr2SizeZero(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "Ptr2SizeZero -> ");

    /* ptr_2_sz is zero -> failure */
    status = GenMemOpsIsEqualRegion(&result, buf1, USIZE_C(8), buf2, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
BothSizesZero(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "BothSizesZero -> ");

    /* Both sizes zero -> failure */
    status = GenMemOpsIsEqualRegion(&result, buf1, USIZE_C(0), buf2, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
EqualSameSizes(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "EqualSameSizes -> ");

    /* Init: both with same sequence */
    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x00));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x00));

    status = GenMemOpsIsEqualRegion(&result, buf1, USIZE_C(8), buf2, USIZE_C(8));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
DifferentSameSizes(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "DifferentSameSizes -> ");

    /* Init: different sequences */
    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x00));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x10));

    status = GenMemOpsIsEqualRegion(&result, buf1, USIZE_C(8), buf2, USIZE_C(8));
    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
DifferentSizes_NotEqual(void)
{
    u8   buf1[8];
    u8   buf2[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "DifferentSizes_NotEqual -> ");

    /* Different sizes -> cannot be equal */
    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x00));
    kdi_FillSeq_u8(buf2, USIZE_C(16), U8_C(0x00));

    status = GenMemOpsIsEqualRegion(&result, buf1, USIZE_C(8), buf2, USIZE_C(16));
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

    status = GenMemOpsIsEqualRegion(&result, buf, USIZE_C(8), buf, USIZE_C(8));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
OverlappingRegions_Equal(void)
{
    u8   buf[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "OverlappingRegions_Equal -> ");

    /* Fill with repeating pattern */
    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Compare buf[0..7] with buf[0..7] (same region) */
    status = GenMemOpsIsEqualRegion(&result, &buf[0], USIZE_C(8), &buf[0], USIZE_C(8));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
OverlappingRegions_Different(void)
{
    u8   buf[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "OverlappingRegions_Different -> ");

    /* Fill with sequential values */
    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Compare buf[0..3] with buf[4..7] (different values) */
    status = GenMemOpsIsEqualRegion(&result, &buf[0], USIZE_C(4), &buf[4], USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(result == false);

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

    status = GenMemOpsIsEqualRegion(&result, buf1, USIZE_C(16), buf2, USIZE_C(16));
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

    status = GenMemOpsIsEqualRegion(&result, buf1, USIZE_C(16), buf2, USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
U16_EqualSameSize(void)
{
    u16  buf1[4];
    u16  buf2[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "U16_EqualSameSize -> ");

    buf1[0] = U16_C(0x1111);
    buf1[1] = U16_C(0x2222);
    buf1[2] = U16_C(0x3333);
    buf1[3] = U16_C(0x4444);

    buf2[0] = U16_C(0x1111);
    buf2[1] = U16_C(0x2222);
    buf2[2] = U16_C(0x3333);
    buf2[3] = U16_C(0x4444);

    status  = GenMemOpsIsEqualRegion(&result, buf1, sizeof(buf1), buf2, sizeof(buf2));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
U16_DifferentSizes(void)
{
    u16  buf1[4];
    u16  buf2[6];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "U16_DifferentSizes -> ");

    buf1[0] = U16_C(0x1111);
    buf1[1] = U16_C(0x2222);
    buf1[2] = U16_C(0x3333);
    buf1[3] = U16_C(0x4444);

    buf2[0] = U16_C(0x1111);
    buf2[1] = U16_C(0x2222);
    buf2[2] = U16_C(0x3333);
    buf2[3] = U16_C(0x4444);
    buf2[4] = U16_C(0x5555);
    buf2[5] = U16_C(0x6666);

    /* Different sizes -> not equal */
    status  = GenMemOpsIsEqualRegion(&result, buf1, sizeof(buf1), buf2, sizeof(buf2));
    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
U32_EqualSameSize(void)
{
    u32  buf1[3];
    u32  buf2[3];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "U32_EqualSameSize -> ");

    buf1[0] = U32_C(0x12345678);
    buf1[1] = U32_C(0xABCDEF01);
    buf1[2] = U32_C(0xDEADBEEF);

    buf2[0] = U32_C(0x12345678);
    buf2[1] = U32_C(0xABCDEF01);
    buf2[2] = U32_C(0xDEADBEEF);

    status  = GenMemOpsIsEqualRegion(&result, buf1, sizeof(buf1), buf2, sizeof(buf2));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
U32_DifferentValues(void)
{
    u32  buf1[3];
    u32  buf2[3];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "U32_DifferentValues -> ");

    buf1[0] = U32_C(0x12345678);
    buf1[1] = U32_C(0xABCDEF01);
    buf1[2] = U32_C(0xDEADBEEF);

    buf2[0] = U32_C(0x12345678);
    buf2[1] = U32_C(0xABCDEF02);
    buf2[2] = U32_C(0xDEADBEEF);

    status  = GenMemOpsIsEqualRegion(&result, buf1, sizeof(buf1), buf2, sizeof(buf2));
    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_EqualSameSize(void)
{
    u64  buf1[3];
    u64  buf2[3];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "U64_EqualSameSize -> ");

    buf1[0] = U64_C(0x123456789ABCDEF0);
    buf1[1] = U64_C(0xFEDCBA9876543210);
    buf1[2] = U64_C(0xDEADBEEFCAFEBABE);

    buf2[0] = U64_C(0x123456789ABCDEF0);
    buf2[1] = U64_C(0xFEDCBA9876543210);
    buf2[2] = U64_C(0xDEADBEEFCAFEBABE);

    status  = GenMemOpsIsEqualRegion(&result, buf1, sizeof(buf1), buf2, sizeof(buf2));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
U64_DifferentSizes(void)
{
    u64  buf1[3];
    u64  buf2[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "U64_DifferentSizes -> ");

    buf1[0] = U64_C(0x123456789ABCDEF0);
    buf1[1] = U64_C(0xFEDCBA9876543210);
    buf1[2] = U64_C(0xDEADBEEFCAFEBABE);

    buf2[0] = U64_C(0x123456789ABCDEF0);
    buf2[1] = U64_C(0xFEDCBA9876543210);
    buf2[2] = U64_C(0xDEADBEEFCAFEBABE);
    buf2[3] = U64_C(0x0000000000000000);

    /* Different sizes -> not equal */
    status  = GenMemOpsIsEqualRegion(&result, buf1, sizeof(buf1), buf2, sizeof(buf2));
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
Struct_EqualSameSize(void)
{
    kdi_TestStruct s1, s2;
    bool           result;
    bool           status;

    printf(LOG_PREFIX_CSTR "Struct_EqualSameSize -> ");

    s1.a   = U32_C(100);
    s1.b   = U16_C(200);
    s1.c   = U8_C(50);
    s1.d   = U8_C(75);

    s2.a   = U32_C(100);
    s2.b   = U16_C(200);
    s2.c   = U8_C(50);
    s2.d   = U8_C(75);

    status = GenMemOpsIsEqualRegion(&result, &s1, sizeof(kdi_TestStruct), &s2, sizeof(kdi_TestStruct));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
Struct_DifferentValues(void)
{
    kdi_TestStruct s1, s2;
    bool           result;
    bool           status;

    printf(LOG_PREFIX_CSTR "Struct_DifferentValues -> ");

    s1.a   = U32_C(100);
    s1.b   = U16_C(200);
    s1.c   = U8_C(50);
    s1.d   = U8_C(75);

    s2.a   = U32_C(100);
    s2.b   = U16_C(200);
    s2.c   = U8_C(51);
    s2.d   = U8_C(75);

    status = GenMemOpsIsEqualRegion(&result, &s1, sizeof(kdi_TestStruct), &s2, sizeof(kdi_TestStruct));
    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
LargeBuffers_Equal(void)
{
    u8    buf1[256];
    u8    buf2[256];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffers_Equal -> ");

    /* Fill with same pattern */
    for (i = 0; i < 256; ++i)
    {
        buf1[i] = (u8)i;
        buf2[i] = (u8)i;
    }

    status = GenMemOpsIsEqualRegion(&result, buf1, USIZE_C(256), buf2, USIZE_C(256));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
LargeBuffers_DifferentSizes(void)
{
    u8    buf1[256];
    u8    buf2[512];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffers_DifferentSizes -> ");

    /* Fill with same pattern */
    for (i = 0; i < 256; ++i)
    {
        buf1[i] = (u8)i;
        buf2[i] = (u8)i;
    }
    for (i = 256; i < 512; ++i)
    {
        buf2[i] = (u8)(i - 256);
    }

    /* Different sizes -> not equal */
    status = GenMemOpsIsEqualRegion(&result, buf1, USIZE_C(256), buf2, USIZE_C(512));
    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
LargeBuffers_DifferentValues(void)
{
    u8    buf1[256];
    u8    buf2[256];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffers_DifferentValues -> ");

    /* Fill with same pattern */
    for (i = 0; i < 256; ++i)
    {
        buf1[i] = (u8)i;
        buf2[i] = (u8)i;
    }

    /* Change one byte */
    buf2[128] = U8_C(0xFF);

    status    = GenMemOpsIsEqualRegion(&result, buf1, USIZE_C(256), buf2, USIZE_C(256));
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
    Ptr1SizeZero();
    Ptr2SizeZero();
    BothSizesZero();
    EqualSameSizes();
    DifferentSameSizes();
    DifferentSizes_NotEqual();
    SamePointer();
    OverlappingRegions_Equal();
    OverlappingRegions_Different();
    AllZeros();
    AllOnes();

    U16_EqualSameSize();
    U16_DifferentSizes();
    U32_EqualSameSize();
    U32_DifferentValues();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_EqualSameSize();
    U64_DifferentSizes();
#endif

    Struct_EqualSameSize();
    Struct_DifferentValues();
    LargeBuffers_Equal();
    LargeBuffers_DifferentSizes();
    LargeBuffers_DifferentValues();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
