/**
 * @file kdGenMemOpsSwapBlocksRange.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsSwapBlocksRange function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsSwapBlocksRange function test"
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
    byte buf1[16];
    byte buf2[16];
    byte buf_orig[16];
    bool result;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillSeq(buf1, USIZE_C(16), U8_C(0x10));
    kdi_FillSeq(buf2, USIZE_C(16), U8_C(0x20));
    kdi_FillSeq(buf_orig, USIZE_C(16), U8_C(0x10));

    /* base_1 is null -> failure */
    result = GenMemOpsSwapBlocksRange(null, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(result == RESULT_FAILURE);

    /* base_2 is null -> failure */
    result = GenMemOpsSwapBlocksRange(buf1, USIZE_C(16), USIZE_C(0), null, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf1, buf_orig, USIZE_C(16)) == RESULT_SUCCESS);

    /* base_1_sz is zero -> failure */
    result = GenMemOpsSwapBlocksRange(buf1, USIZE_C(0), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf1, buf_orig, USIZE_C(16)) == RESULT_SUCCESS);

    /* base_2_sz is zero -> failure */
    result = GenMemOpsSwapBlocksRange(buf1, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(0), USIZE_C(0), USIZE_C(4));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf1, buf_orig, USIZE_C(16)) == RESULT_SUCCESS);

    /* block_sz is zero -> failure */
    result = GenMemOpsSwapBlocksRange(buf1, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(0));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf1, buf_orig, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
IndicesOutOfBounds(void)
{
    byte buf1[16];
    byte buf2[16];
    byte buf_orig[16];
    bool result;

    printf(LOG_PREFIX_CSTR "IndicesOutOfBounds -> ");

    kdi_FillSeq(buf1, USIZE_C(16), U8_C(0x30));
    kdi_FillSeq(buf2, USIZE_C(16), U8_C(0x40));
    kdi_FillSeq(buf_orig, USIZE_C(16), U8_C(0x30));

    /* idx_1 + block_sz > base_1_sz */
    /* 13 + 4 = 17 > 16 */
    result = GenMemOpsSwapBlocksRange(buf1, USIZE_C(16), USIZE_C(13), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf1, buf_orig, USIZE_C(16)) == RESULT_SUCCESS);

    /* idx_2 + block_sz > base_2_sz */
    /* 14 + 4 = 18 > 16 */
    result = GenMemOpsSwapBlocksRange(buf1, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(14), USIZE_C(4));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf1, buf_orig, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
U16_Blocks_AreSwappedCorrectly(void)
{
    u16  buf[4];
    u16  expected[4];
    bool result;

    printf(LOG_PREFIX_CSTR "U16_Blocks_AreSwappedCorrectly -> ");

    /* Init: 0x1111, 0x2222, 0x3333, 0x4444 */
    buf[0]      = U16_C(0x1111);
    buf[1]      = U16_C(0x2222);
    buf[2]      = U16_C(0x3333);
    buf[3]      = U16_C(0x4444);

    /* Swap element 0 (offset 0) and element 3 (offset 3 * 2 = 6) within the same buffer */
    /* Expected: 0x4444, 0x2222, 0x3333, 0x1111 */
    expected[0] = U16_C(0x4444);
    expected[1] = U16_C(0x2222);
    expected[2] = U16_C(0x3333);
    expected[3] = U16_C(0x1111);

    result      = GenMemOpsSwapBlocksRange(buf, sizeof(buf), USIZE_C(0), buf, sizeof(buf), USIZE_C(3) * sizeof(u16), sizeof(u16));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
U32_Blocks_AreSwappedCorrectly(void)
{
    u32  buf1[2];
    u32  buf2[2];
    u32  exp1[2];
    u32  exp2[2];
    bool result;

    printf(LOG_PREFIX_CSTR "U32_Blocks_AreSwappedCorrectly -> ");

    /* buf1: 0x11111111, 0x22222222 */
    buf1[0] = U32_C(0x11111111);
    buf1[1] = U32_C(0x22222222);

    /* buf2: 0x33333333, 0x44444444 */
    buf2[0] = U32_C(0x33333333);
    buf2[1] = U32_C(0x44444444);

    /* Swap buf1[1] (offset 4) with buf2[0] (offset 0) */
    exp1[0] = U32_C(0x11111111);
    exp1[1] = U32_C(0x33333333); /* Swapped */

    exp2[0] = U32_C(0x22222222); /* Swapped */
    exp2[1] = U32_C(0x44444444);

    result  = GenMemOpsSwapBlocksRange(buf1, sizeof(buf1), USIZE_C(1) * sizeof(u32), buf2, sizeof(buf2), USIZE_C(0), sizeof(u32));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf1, (byte *)exp1, sizeof(buf1)) == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf2, (byte *)exp2, sizeof(buf2)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_Blocks_AreSwappedCorrectly(void)
{
    u64  buf[4];
    u64  expected[4];
    bool result;

    printf(LOG_PREFIX_CSTR "U64_Blocks_AreSwappedCorrectly -> ");

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

    result      = GenMemOpsSwapBlocksRange(buf, sizeof(buf), USIZE_C(0), buf, sizeof(buf), USIZE_C(3) * sizeof(u64), sizeof(u64));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}
#endif


typedef struct kdi_BigStruct
{
    u32 a;
    u32 b;
    u8  c;
} kdi_BigStruct;


void
Struct_Blocks_AreSwappedCorrectly(void)
{
    kdi_BigStruct buf[3];
    kdi_BigStruct expected[3];
    bool          result;

    printf(LOG_PREFIX_CSTR "Struct_Blocks_AreSwappedCorrectly -> ");

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

    /* Swap index 0 (offset 0) and index 2 (offset 2 * sizeof) */
    expected[0] = buf[2]; /* Swapped */
    expected[1] = buf[1]; /* Unchanged */
    expected[2] = buf[0]; /* Swapped */

    result      = GenMemOpsSwapBlocksRange(buf, sizeof(buf), USIZE_C(0), buf, sizeof(buf), USIZE_C(2) * sizeof(kdi_BigStruct), sizeof(kdi_BigStruct));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)buf, (byte *)expected, sizeof(buf)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SwapSameBufferSameIndex(void)
{
    byte buf[16];
    byte expected[16];
    bool result;

    printf(LOG_PREFIX_CSTR "SwapSameBufferSameIndex -> ");

    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x70));
    kdi_FillSeq(expected, USIZE_C(16), U8_C(0x70));

    /* Swap index 2 with 2 (offset 8, size 4) */
    result = GenMemOpsSwapBlocksRange(buf, USIZE_C(16), USIZE_C(8), buf, USIZE_C(16), USIZE_C(8), USIZE_C(4));

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

    U16_Blocks_AreSwappedCorrectly();
    U32_Blocks_AreSwappedCorrectly();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_Blocks_AreSwappedCorrectly();
#endif
    Struct_Blocks_AreSwappedCorrectly();

    SwapSameBufferSameIndex();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
