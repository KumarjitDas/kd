/**
 * @file kdGenMemOpsInnerSwapBlocks.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsInnerSwapBlocks function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsInnerSwapBlocks function test"
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
kdi_FillSeq(byte *dst, usize sz, byte start)
{
    usize i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        dst[i] = (byte)(start + (byte)i);
    }
}


void
BasicArguments(void)
{
    byte buf[16];
    byte buf_orig[16];
    bool result;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x10));
    kdi_FillSeq(buf_orig, USIZE_C(16), U8_C(0x10));

    /* ptr is null -> failure */
    result = GenMemOpsInnerSwapBlocks(null, USIZE_C(0), USIZE_C(4), USIZE_C(4));
    assert(result == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    result = GenMemOpsInnerSwapBlocks(buf, USIZE_C(0), USIZE_C(4), USIZE_C(0));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SwapU16Blocks(void)
{
    u16  buf[4];
    u16  expected[4];
    bool result;

    printf(LOG_PREFIX_CSTR "SwapU16Blocks -> ");

    /* Init: 0x1111, 0x2222, 0x3333, 0x4444 */
    buf[0]      = U16_C(0x1111);
    buf[1]      = U16_C(0x2222);
    buf[2]      = U16_C(0x3333);
    buf[3]      = U16_C(0x4444);

    /* Swap element 0 (offset 0) and element 2 (offset 2 * 2 = 4) */
    /* Expected: 0x3333, 0x2222, 0x1111, 0x4444 */
    expected[0] = U16_C(0x3333);
    expected[1] = U16_C(0x2222);
    expected[2] = U16_C(0x1111);
    expected[3] = U16_C(0x4444);

    result      = GenMemOpsInnerSwapBlocks(buf, USIZE_C(0), USIZE_C(2) * sizeof(u16), sizeof(u16));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SwapU32Blocks(void)
{
    u32  buf[4];
    u32  expected[4];
    bool result;

    printf(LOG_PREFIX_CSTR "SwapU32Blocks -> ");

    /* Init: 0x11111111, 0x22222222, 0x33333333, 0x44444444 */
    buf[0]      = U32_C(0x11111111);
    buf[1]      = U32_C(0x22222222);
    buf[2]      = U32_C(0x33333333);
    buf[3]      = U32_C(0x44444444);

    /* Swap element 0 (offset 0) and element 2 (offset 2 * 4 = 8) */
    /* Expected: 0x33333333, 0x22222222, 0x11111111, 0x44444444 */
    expected[0] = U32_C(0x33333333);
    expected[1] = U32_C(0x22222222);
    expected[2] = U32_C(0x11111111);
    expected[3] = U32_C(0x44444444);

    result      = GenMemOpsInnerSwapBlocks(buf, USIZE_C(0), USIZE_C(2) * sizeof(u32), sizeof(u32));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
SwapU64Blocks(void)
{
    u64  buf[4];
    u64  expected[4];
    bool result;

    printf(LOG_PREFIX_CSTR "SwapU64Blocks -> ");

    /* Init */
    buf[0]      = U64_C(0x1111111111111111);
    buf[1]      = U64_C(0x2222222222222222);
    buf[2]      = U64_C(0x3333333333333333);
    buf[3]      = U64_C(0x4444444444444444);

    /* Swap element 1 (offset 8) and element 3 (offset 24) */
    expected[0] = U64_C(0x1111111111111111);
    expected[1] = U64_C(0x4444444444444444);
    expected[2] = U64_C(0x3333333333333333);
    expected[3] = U64_C(0x2222222222222222);

    result      = GenMemOpsInnerSwapBlocks(buf, USIZE_C(1) * sizeof(u64), USIZE_C(3) * sizeof(u64), sizeof(u64));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}
#endif


typedef struct TestStruct
{
    u32 a;
    u32 b;
    u8  c;
} TestStruct; /* Size 9 (padded to 12 likely, but we use sizeof) */


void
SwapStructBlocks(void)
{
    TestStruct buf[3];
    TestStruct expected[3];
    bool       result;

    printf(LOG_PREFIX_CSTR "SwapStructBlocks -> ");

    /* Init */
    buf[0].a    = 1;
    buf[0].b    = 10;
    buf[0].c    = 100;
    buf[1].a    = 2;
    buf[1].b    = 20;
    buf[1].c    = 200;
    buf[2].a    = 3;
    buf[2].b    = 30;
    buf[2].c    = 220;

    /* Expected: Swap index 1 (offset 1*sizeof) and index 2 (offset 2*sizeof) */
    expected[0] = buf[0]; /* Unchanged */
    expected[1] = buf[2]; /* Swapped */
    expected[2] = buf[1]; /* Swapped */

    result      = GenMemOpsInnerSwapBlocks(buf, USIZE_C(1) * sizeof(TestStruct), USIZE_C(2) * sizeof(TestStruct), sizeof(TestStruct));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SwapSameIndex_IsNoOp(void)
{
    byte buf[16];
    byte expected[16];
    bool result;

    printf(LOG_PREFIX_CSTR "SwapSameIndex_IsNoOp -> ");

    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x50));
    kdi_FillSeq(expected, USIZE_C(16), U8_C(0x50));

    /* Swap index 4 with 4 (byte offsets) */
    result = GenMemOpsInnerSwapBlocks(buf, USIZE_C(4), USIZE_C(4), USIZE_C(4));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SwapAdjacentBlocks(void)
{
    byte buf[8];
    byte expected[8];
    bool result;

    printf(LOG_PREFIX_CSTR "SwapAdjacentBlocks -> ");

    /* Init: 0x00..0x07 */
    kdi_FillSeq(buf, USIZE_C(8), U8_C(0x00));

    /* Block size 2. Swap index 0 (bytes 0-1) and index 1 (bytes 2-3) */
    /* Original: 00 01 | 02 03 | 04 05 06 07 */
    /* Expected: 02 03 | 00 01 | 04 05 06 07 */
    expected[0] = 0x02;
    expected[1] = 0x03;
    expected[2] = 0x00;
    expected[3] = 0x01;
    expected[4] = 0x04;
    expected[5] = 0x05;
    expected[6] = 0x06;
    expected[7] = 0x07;

    result      = GenMemOpsInnerSwapBlocks(buf, USIZE_C(0), USIZE_C(2), USIZE_C(2));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(8)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();

    SwapU16Blocks();
    SwapU32Blocks();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    SwapU64Blocks();
#endif
    SwapStructBlocks();

    SwapSameIndex_IsNoOp();
    SwapAdjacentBlocks();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
