/**
 * @file kdGenMemOpsReverseBlocks.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsReverseBlocks function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsReverseBlocks function test"
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
NullPointer(void)
{
    bool status;

    printf(LOG_PREFIX_CSTR "NullPointer -> ");

    /* ptr is null -> failure */
    status = GenMemOpsReverseBlocks(null, USIZE_C(16), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ZeroBlockSize(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ZeroBlockSize -> ");

    /* block_sz is zero -> failure */
    status = GenMemOpsReverseBlocks(buf, USIZE_C(16), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ZeroPtrSize(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ZeroPtrSize -> ");

    /* ptr_sz is zero -> success (0 % block_sz = 0, no check for !ptr_sz) */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));
    status = GenMemOpsReverseBlocks(buf, USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Verify buffer untouched */
    assert(buf[0] == U8_C(0x00));
    assert(buf[15] == U8_C(0x0F));

    printf("PASSED\n");
}


void
PtrSizeMisaligned(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "PtrSizeMisaligned -> ");

    /* ptr_sz not aligned to block_sz -> failure */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* ptr_sz=10, block_sz=4: 10 % 4 = 2, not aligned */
    status = GenMemOpsReverseBlocks(buf, USIZE_C(10), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr_sz=15, block_sz=2: 15 % 2 = 1, not aligned */
    status = GenMemOpsReverseBlocks(buf, USIZE_C(15), USIZE_C(2));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
PtrSizeLessThanBlockSize(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "PtrSizeLessThanBlockSize -> ");

    /* ptr_sz < block_sz -> fails alignment check (ptr_sz % block_sz != 0 when ptr_sz < block_sz) */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* ptr_sz=2, block_sz=4: 2 % 4 = 2, not aligned -> failure */
    status = GenMemOpsReverseBlocks(buf, USIZE_C(2), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr_sz=3, block_sz=4: 3 % 4 = 3, not aligned -> failure */
    status = GenMemOpsReverseBlocks(buf, USIZE_C(3), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr_sz=1, block_sz=2: 1 % 2 = 1, not aligned -> failure */
    status = GenMemOpsReverseBlocks(buf, USIZE_C(1), USIZE_C(2));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
BlockSizeOne(void)
{
    u8   buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "BlockSizeOne -> ");

    /* Block size 1 = Byte Reverse */
    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x01)); /* 1, 2, 3, 4 */

    status = GenMemOpsReverseBlocks(buf, USIZE_C(4), USIZE_C(1));
    assert(status == RESULT_SUCCESS);

    /* Expected: 4, 3, 2, 1 */
    assert(buf[0] == U8_C(0x04));
    assert(buf[1] == U8_C(0x03));
    assert(buf[2] == U8_C(0x02));
    assert(buf[3] == U8_C(0x01));

    printf("PASSED\n");
}


void
SingleBlock(void)
{
    u8   buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "SingleBlock -> ");

    /* Only 1 block -> no change */
    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x10));

    status = GenMemOpsReverseBlocks(buf, USIZE_C(4), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Should remain unchanged */
    assert(buf[0] == U8_C(0x10));
    assert(buf[1] == U8_C(0x11));
    assert(buf[2] == U8_C(0x12));
    assert(buf[3] == U8_C(0x13));

    printf("PASSED\n");
}


void
TwoBlocks_Size2(void)
{
    u8   buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "TwoBlocks_Size2 -> ");

    /* 2 blocks of size 2 */
    buf[0] = U8_C(0x11);
    buf[1] = U8_C(0x12);
    buf[2] = U8_C(0x21);
    buf[3] = U8_C(0x22);

    status = GenMemOpsReverseBlocks(buf, USIZE_C(4), USIZE_C(2));
    assert(status == RESULT_SUCCESS);

    /* Expected: blocks swapped */
    assert(buf[0] == U8_C(0x21));
    assert(buf[1] == U8_C(0x22));
    assert(buf[2] == U8_C(0x11));
    assert(buf[3] == U8_C(0x12));

    printf("PASSED\n");
}


void
TwoBlocks_Size4(void)
{
    u8   buf[8];
    bool status;

    printf(LOG_PREFIX_CSTR "TwoBlocks_Size4 -> ");

    /* 2 blocks of size 4 */
    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x10));     /* Block 0: 0x10-0x13 */
    kdi_FillSeq(&buf[4], USIZE_C(4), U8_C(0x20)); /* Block 1: 0x20-0x23 */

    status = GenMemOpsReverseBlocks(buf, USIZE_C(8), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Expected: blocks swapped */
    assert(buf[0] == U8_C(0x20));
    assert(buf[1] == U8_C(0x21));
    assert(buf[2] == U8_C(0x22));
    assert(buf[3] == U8_C(0x23));
    assert(buf[4] == U8_C(0x10));
    assert(buf[5] == U8_C(0x11));
    assert(buf[6] == U8_C(0x12));
    assert(buf[7] == U8_C(0x13));

    printf("PASSED\n");
}


void
ThreeBlocks_Size2(void)
{
    u8   buf[6];
    bool status;

    printf(LOG_PREFIX_CSTR "ThreeBlocks_Size2 -> ");

    /* 3 blocks of size 2: [A][B][C] */
    buf[0] = U8_C(0xA0);
    buf[1] = U8_C(0xA1);
    buf[2] = U8_C(0xB0);
    buf[3] = U8_C(0xB1);
    buf[4] = U8_C(0xC0);
    buf[5] = U8_C(0xC1);

    status = GenMemOpsReverseBlocks(buf, USIZE_C(6), USIZE_C(2));
    assert(status == RESULT_SUCCESS);

    /* Expected: [C][B][A] - middle block stays in place */
    assert(buf[0] == U8_C(0xC0));
    assert(buf[1] == U8_C(0xC1));
    assert(buf[2] == U8_C(0xB0));
    assert(buf[3] == U8_C(0xB1));
    assert(buf[4] == U8_C(0xA0));
    assert(buf[5] == U8_C(0xA1));

    printf("PASSED\n");
}


void
FourBlocks_Size2(void)
{
    u8   buf[8];
    bool status;

    printf(LOG_PREFIX_CSTR "FourBlocks_Size2 -> ");

    /* 4 blocks of size 2: [A][B][C][D] */
    kdi_FillSeq(buf, USIZE_C(8), U8_C(0x00)); /* 00,01,02,03,04,05,06,07 */

    status = GenMemOpsReverseBlocks(buf, USIZE_C(8), USIZE_C(2));
    assert(status == RESULT_SUCCESS);

    /* Expected: [D][C][B][A] -> 06,07,04,05,02,03,00,01 */
    assert(buf[0] == U8_C(0x06));
    assert(buf[1] == U8_C(0x07));
    assert(buf[2] == U8_C(0x04));
    assert(buf[3] == U8_C(0x05));
    assert(buf[4] == U8_C(0x02));
    assert(buf[5] == U8_C(0x03));
    assert(buf[6] == U8_C(0x00));
    assert(buf[7] == U8_C(0x01));

    printf("PASSED\n");
}


void
U16_Blocks_TwoBlocks(void)
{
    u16  buf[2];
    bool status;

    printf(LOG_PREFIX_CSTR "U16_Blocks_TwoBlocks -> ");

    buf[0] = U16_C(0x1111);
    buf[1] = U16_C(0x2222);

    status = GenMemOpsReverseBlocks(buf, sizeof(buf), sizeof(u16));
    assert(status == RESULT_SUCCESS);

    assert(buf[0] == U16_C(0x2222));
    assert(buf[1] == U16_C(0x1111));

    printf("PASSED\n");
}


void
U16_Blocks_FourBlocks(void)
{
    u16  buf[4];
    u16  expected[4];
    bool result;

    printf(LOG_PREFIX_CSTR "U16_Blocks_FourBlocks -> ");

    /* Init: 0x1111, 0x2222, 0x3333, 0x4444 */
    buf[0]      = U16_C(0x1111);
    buf[1]      = U16_C(0x2222);
    buf[2]      = U16_C(0x3333);
    buf[3]      = U16_C(0x4444);

    /* Expected: 0x4444, 0x3333, 0x2222, 0x1111 */
    expected[0] = U16_C(0x4444);
    expected[1] = U16_C(0x3333);
    expected[2] = U16_C(0x2222);
    expected[3] = U16_C(0x1111);

    result      = GenMemOpsReverseBlocks(buf, sizeof(buf), sizeof(u16));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
U16_Blocks_EightBlocks(void)
{
    u16   buf[8];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "U16_Blocks_EightBlocks -> ");

    /* Init: 0, 1, 2, 3, 4, 5, 6, 7 */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        buf[i] = (u16)i;
    }

    status = GenMemOpsReverseBlocks(buf, sizeof(buf), sizeof(u16));
    assert(status == RESULT_SUCCESS);

    /* Expected: 7, 6, 5, 4, 3, 2, 1, 0 */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        assert(buf[i] == (u16)(7 - i));
    }

    printf("PASSED\n");
}


void
U32_Blocks_ThreeBlocks(void)
{
    u32  buf[3];
    u32  expected[3];
    bool result;

    printf(LOG_PREFIX_CSTR "U32_Blocks_ThreeBlocks -> ");

    /* Init: A, B, C */
    buf[0]      = U32_C(0xAAAAAAAA);
    buf[1]      = U32_C(0xBBBBBBBB);
    buf[2]      = U32_C(0xCCCCCCCC);

    /* Expected: C, B, A */
    expected[0] = U32_C(0xCCCCCCCC);
    expected[1] = U32_C(0xBBBBBBBB);
    expected[2] = U32_C(0xAAAAAAAA);

    result      = GenMemOpsReverseBlocks(buf, sizeof(buf), sizeof(u32));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
U32_Blocks_FiveBlocks(void)
{
    u32   buf[5];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "U32_Blocks_FiveBlocks -> ");

    /* Init: 10, 20, 30, 40, 50 */
    for (i = USIZE_C(0); i < USIZE_C(5); ++i)
    {
        buf[i] = (u32)((i + 1) * 10);
    }

    status = GenMemOpsReverseBlocks(buf, sizeof(buf), sizeof(u32));
    assert(status == RESULT_SUCCESS);

    /* Expected: 50, 40, 30, 20, 10 */
    for (i = USIZE_C(0); i < USIZE_C(5); ++i)
    {
        assert(buf[i] == (u32)((5 - i) * 10));
    }

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_Blocks_TwoBlocks(void)
{
    u64  buf[2];
    bool status;

    printf(LOG_PREFIX_CSTR "U64_Blocks_TwoBlocks -> ");

    buf[0] = U64_C(0x1111111111111111);
    buf[1] = U64_C(0x2222222222222222);

    status = GenMemOpsReverseBlocks(buf, sizeof(buf), sizeof(u64));
    assert(status == RESULT_SUCCESS);

    assert(buf[0] == U64_C(0x2222222222222222));
    assert(buf[1] == U64_C(0x1111111111111111));

    printf("PASSED\n");
}


void
U64_Blocks_FourBlocks(void)
{
    u64  buf[4];
    u64  expected[4];
    bool result;

    printf(LOG_PREFIX_CSTR "U64_Blocks_FourBlocks -> ");

    /* Init: 1, 2, 3, 4 */
    buf[0]      = U64_C(0x1111111111111111);
    buf[1]      = U64_C(0x2222222222222222);
    buf[2]      = U64_C(0x3333333333333333);
    buf[3]      = U64_C(0x4444444444444444);

    /* Expected: 4, 3, 2, 1 */
    expected[0] = U64_C(0x4444444444444444);
    expected[1] = U64_C(0x3333333333333333);
    expected[2] = U64_C(0x2222222222222222);
    expected[3] = U64_C(0x1111111111111111);

    result      = GenMemOpsReverseBlocks(buf, sizeof(buf), sizeof(u64));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
U64_Blocks_SixBlocks(void)
{
    u64   buf[6];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "U64_Blocks_SixBlocks -> ");

    /* Init: 0, 10, 20, 30, 40, 50 */
    for (i = USIZE_C(0); i < USIZE_C(6); ++i)
    {
        buf[i] = (u64)(i * 10);
    }

    status = GenMemOpsReverseBlocks(buf, sizeof(buf), sizeof(u64));
    assert(status == RESULT_SUCCESS);

    /* Expected: 50, 40, 30, 20, 10, 0 */
    for (i = USIZE_C(0); i < USIZE_C(6); ++i)
    {
        assert(buf[i] == (u64)((5 - i) * 10));
    }

    printf("PASSED\n");
}
#endif


typedef struct kdi_SmallStruct
{
    u32 a;
    u32 b;
    u8  c;
} kdi_SmallStruct;


void
Struct_Blocks_TwoBlocks(void)
{
    kdi_SmallStruct buf[2];
    bool            status;

    printf(LOG_PREFIX_CSTR "Struct_Blocks_TwoBlocks -> ");

    /* Init: S0, S1 */
    buf[0].a = 1;
    buf[0].b = 10;
    buf[0].c = 100;
    buf[1].a = 2;
    buf[1].b = 20;
    buf[1].c = 200;

    status   = GenMemOpsReverseBlocks(buf, sizeof(buf), sizeof(kdi_SmallStruct));
    assert(status == RESULT_SUCCESS);

    /* Expected: S1, S0 */
    assert(buf[0].a == 2);
    assert(buf[0].b == 20);
    assert(buf[0].c == 200);
    assert(buf[1].a == 1);
    assert(buf[1].b == 10);
    assert(buf[1].c == 100);

    printf("PASSED\n");
}


void
Struct_Blocks_ThreeBlocks(void)
{
    kdi_SmallStruct buf[3];
    kdi_SmallStruct expected[3];
    bool            result;

    printf(LOG_PREFIX_CSTR "Struct_Blocks_ThreeBlocks -> ");

    /* Init: S0, S1, S2 */
    buf[0].a    = 1;
    buf[0].b    = 10;
    buf[0].c    = 100;
    buf[1].a    = 2;
    buf[1].b    = 20;
    buf[1].c    = 200;
    buf[2].a    = 3;
    buf[2].b    = 30;
    buf[2].c    = 220;

    /* Expected: S2, S1, S0 */
    expected[0] = buf[2];
    expected[1] = buf[1];
    expected[2] = buf[0];

    result      = GenMemOpsReverseBlocks(buf, sizeof(buf), sizeof(kdi_SmallStruct));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
BlockSizeExceedsPtrSize(void)
{
    u8   buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "BlockSizeExceedsPtrSize -> ");

    /* block_sz > ptr_sz -> 0 blocks -> failure */
    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x00));

    status = GenMemOpsReverseBlocks(buf, USIZE_C(4), USIZE_C(8));
    assert(status == RESULT_FAILURE);

    /* Buffer should be unchanged */
    assert(buf[0] == U8_C(0x00));
    assert(buf[1] == U8_C(0x01));
    assert(buf[2] == U8_C(0x02));
    assert(buf[3] == U8_C(0x03));

    printf("PASSED\n");
}


void
BlockSizeEqualsPtrSize(void)
{
    u8   buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "BlockSizeEqualsPtrSize -> ");

    /* block_sz == ptr_sz -> 1 block -> no change */
    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x00));

    status = GenMemOpsReverseBlocks(buf, USIZE_C(4), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Buffer should be unchanged */
    assert(buf[0] == U8_C(0x00));
    assert(buf[1] == U8_C(0x01));
    assert(buf[2] == U8_C(0x02));
    assert(buf[3] == U8_C(0x03));

    printf("PASSED\n");
}


void
LargeBuffer_ManyBlocks(void)
{
    u8   buf[64];
    bool status;

    printf(LOG_PREFIX_CSTR "LargeBuffer_ManyBlocks -> ");

    /* Init: 0..63 */
    kdi_FillSeq(buf, USIZE_C(64), U8_C(0));

    /* 16 blocks of size 4 */
    status = GenMemOpsReverseBlocks(buf, USIZE_C(64), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Verify first block (now contains last block) */
    assert(buf[0] == U8_C(60));
    assert(buf[1] == U8_C(61));
    assert(buf[2] == U8_C(62));
    assert(buf[3] == U8_C(63));

    /* Verify last block (now contains first block) */
    assert(buf[60] == U8_C(0));
    assert(buf[61] == U8_C(1));
    assert(buf[62] == U8_C(2));
    assert(buf[63] == U8_C(3));

    /* Verify middle blocks swapped correctly */
    /* Block at index 4 (bytes 16-19) should contain block 11 (bytes 44-47) */
    assert(buf[16] == U8_C(44));
    assert(buf[17] == U8_C(45));
    assert(buf[18] == U8_C(46));
    assert(buf[19] == U8_C(47));

    printf("PASSED\n");
}


void
DoubleReverse(void)
{
    u8    buf[16];
    u8    original[16];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "DoubleReverse -> ");

    /* Init: 0x00 ... 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Keep copy of original */
    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        original[i] = buf[i];
    }

    /* Reverse once */
    status = GenMemOpsReverseBlocks(buf, USIZE_C(16), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Reverse again - should restore */
    status = GenMemOpsReverseBlocks(buf, USIZE_C(16), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Verify restored to original */
    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        assert(buf[i] == original[i]);
    }

    printf("PASSED\n");
}


void
AllBlocksSameValue(void)
{
    u32   buf[8];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "AllBlocksSameValue -> ");

    /* Fill all blocks with same value */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        buf[i] = U32_C(0x12345678);
    }

    status = GenMemOpsReverseBlocks(buf, sizeof(buf), sizeof(u32));
    assert(status == RESULT_SUCCESS);

    /* All values should still be the same */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        assert(buf[i] == U32_C(0x12345678));
    }

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    NullPointer();
    ZeroBlockSize();
    ZeroPtrSize();
    PtrSizeMisaligned();
    PtrSizeLessThanBlockSize();
    BlockSizeOne();
    SingleBlock();
    TwoBlocks_Size2();
    TwoBlocks_Size4();
    ThreeBlocks_Size2();
    FourBlocks_Size2();
    U16_Blocks_TwoBlocks();
    U16_Blocks_FourBlocks();
    U16_Blocks_EightBlocks();
    U32_Blocks_ThreeBlocks();
    U32_Blocks_FiveBlocks();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_Blocks_TwoBlocks();
    U64_Blocks_FourBlocks();
    U64_Blocks_SixBlocks();
#endif
    Struct_Blocks_TwoBlocks();
    Struct_Blocks_ThreeBlocks();
    BlockSizeExceedsPtrSize();
    BlockSizeEqualsPtrSize();
    LargeBuffer_ManyBlocks();
    DoubleReverse();
    AllBlocksSameValue();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
