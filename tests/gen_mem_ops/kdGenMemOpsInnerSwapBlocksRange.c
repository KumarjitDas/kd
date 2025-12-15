/**
 * @file kdGenMemOpsInnerSwapBlocksRange.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsInnerSwapBlocksRange function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsInnerSwapBlocksRange function test"
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

    /* base is null -> failure */
    result = GenMemOpsInnerSwapBlocksRange(null, USIZE_C(16), USIZE_C(0), USIZE_C(4), USIZE_C(4));
    assert(result == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    result = GenMemOpsInnerSwapBlocksRange(buf, USIZE_C(0), USIZE_C(0), USIZE_C(4), USIZE_C(4));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(16)) == RESULT_SUCCESS);

    /* block_sz is zero -> failure */
    result = GenMemOpsInnerSwapBlocksRange(buf, USIZE_C(16), USIZE_C(0), USIZE_C(4), USIZE_C(0));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
IndicesOutOfBounds(void)
{
    byte buf[16];
    byte buf_orig[16];
    bool result;

    printf(LOG_PREFIX_CSTR "IndicesOutOfBounds -> ");

    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x20));
    kdi_FillSeq(buf_orig, USIZE_C(16), U8_C(0x20));

    /* idx_1 + block_sz > base_sz */
    /* 13 + 4 = 17 > 16 */
    result = GenMemOpsInnerSwapBlocksRange(buf, USIZE_C(16), USIZE_C(13), USIZE_C(0), USIZE_C(4));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(16)) == RESULT_SUCCESS);

    /* idx_2 + block_sz > base_sz */
    /* 14 + 4 = 18 > 16 */
    result = GenMemOpsInnerSwapBlocksRange(buf, USIZE_C(16), USIZE_C(0), USIZE_C(14), USIZE_C(4));
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

    /* Swap element 0 (offset 0) and element 3 (offset 3 * 2 = 6) */
    /* Expected: 0x4444, 0x2222, 0x3333, 0x1111 */
    expected[0] = U16_C(0x4444);
    expected[1] = U16_C(0x2222);
    expected[2] = U16_C(0x3333);
    expected[3] = U16_C(0x1111);

    result      = GenMemOpsInnerSwapBlocksRange(buf, sizeof(buf), USIZE_C(0), USIZE_C(3) * sizeof(u16), sizeof(u16));

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

    /* Init */
    buf[0]      = U32_C(0x11111111);
    buf[1]      = U32_C(0x22222222);
    buf[2]      = U32_C(0x33333333);
    buf[3]      = U32_C(0x44444444);

    /* Swap element 1 (offset 4) and element 2 (offset 8) */
    expected[0] = U32_C(0x11111111);
    expected[1] = U32_C(0x33333333);
    expected[2] = U32_C(0x22222222);
    expected[3] = U32_C(0x44444444);

    result      = GenMemOpsInnerSwapBlocksRange(buf, sizeof(buf), USIZE_C(1) * sizeof(u32), USIZE_C(2) * sizeof(u32), sizeof(u32));

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

    /* Swap element 0 (offset 0) and element 3 (offset 24) */
    expected[0] = U64_C(0x4444444444444444);
    expected[1] = U64_C(0x2222222222222222);
    expected[2] = U64_C(0x3333333333333333);
    expected[3] = U64_C(0x1111111111111111);

    result      = GenMemOpsInnerSwapBlocksRange(buf, sizeof(buf), USIZE_C(0), USIZE_C(3) * sizeof(u64), sizeof(u64));

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
} TestStruct; /* Size 9 (padded) */


void
SwapStructBlocks(void)
{
    TestStruct buf[4];
    TestStruct expected[4];
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
    buf[3].a    = 4;
    buf[3].b    = 40;
    buf[3].c    = 240;

    /* Swap index 1 (offset 1*sizeof) and index 3 (offset 3*sizeof) */
    expected[0] = buf[0]; /* Unchanged */
    expected[1] = buf[3]; /* Swapped */
    expected[2] = buf[2]; /* Unchanged */
    expected[3] = buf[1]; /* Swapped */

    result      = GenMemOpsInnerSwapBlocksRange(buf, sizeof(buf), USIZE_C(1) * sizeof(TestStruct), USIZE_C(3) * sizeof(TestStruct), sizeof(TestStruct));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SwapSameIndex(void)
{
    byte buf[16];
    byte expected[16];
    bool result;

    printf(LOG_PREFIX_CSTR "SwapSameIndex -> ");

    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x70));
    kdi_FillSeq(expected, USIZE_C(16), U8_C(0x70));

    /* Swap index 4 with 4 (byte offsets) */
    result = GenMemOpsInnerSwapBlocksRange(buf, USIZE_C(16), USIZE_C(4), USIZE_C(4), USIZE_C(4));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    IndicesOutOfBounds();

    SwapU16Blocks();
    SwapU32Blocks();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    SwapU64Blocks();
#endif
    SwapStructBlocks();

    SwapSameIndex();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
