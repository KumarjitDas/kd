/**
 * @file kdGenMemOpsSetBlocks.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsSetBlocks function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsSetBlocks function test"
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


static void
kdi_FillVal(byte *dst, usize sz, byte val)
{
    usize i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        dst[i] = val;
    }
}


void
BasicArguments(void)
{
    /*
     * Test NULL pointer validation and zero-size parameters.
     * All failure cases should leave destination unchanged.
     * Note: dst_sz and block_sz are in bytes and must be aligned to block_sz.
     */
    byte dst[32];
    byte block[4];
    byte dst_orig[32];
    bool result;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillVal(dst, USIZE_C(32), U8_C(0xAA));
    kdi_FillVal(dst_orig, USIZE_C(32), U8_C(0xAA));
    block[0] = U8_C(0x11);
    block[1] = U8_C(0x22);
    block[2] = U8_C(0x33);
    block[3] = U8_C(0x44);

    /* dst is null */
    result = GenMemOpsSetBlocks(null, USIZE_C(32), block, USIZE_C(4));
    assert(result == RESULT_FAILURE);

    /* block is null */
    result = GenMemOpsSetBlocks(dst, USIZE_C(32), null, USIZE_C(4));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* dst_sz is zero */
    result = GenMemOpsSetBlocks(dst, USIZE_C(0), block, USIZE_C(4));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* block_sz is zero */
    result = GenMemOpsSetBlocks(dst, USIZE_C(32), block, USIZE_C(0));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* dst_sz not aligned to block_sz */
    result = GenMemOpsSetBlocks(dst, USIZE_C(33), block, USIZE_C(4));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(32)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SingleBlockSet(void)
{
    /*
     * Minimal case: set exactly 1 block (4 bytes).
     */
    byte  dst[4];
    byte  block[4];
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "SingleBlockSet -> ");

    kdi_FillVal(dst, USIZE_C(4), U8_C(0x00));
    block[0] = U8_C(0xAA);
    block[1] = U8_C(0xBB);
    block[2] = U8_C(0xCC);
    block[3] = U8_C(0xDD);

    result = GenMemOpsSetBlocks(dst, USIZE_C(4), block, USIZE_C(4));

    assert(result == RESULT_SUCCESS);
    for (i = USIZE_C(0); i < USIZE_C(4); ++i)
    {
        assert(dst[i] == block[i]);
    }

    printf("PASSED\n");
}


void
MultipleBlocks_U8(void)
{
    /*
     * Set multiple 1-byte blocks.
     */
    byte  dst[8];
    byte  block[1];
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "MultipleBlocks_U8 -> ");

    kdi_FillVal(dst, USIZE_C(8), U8_C(0x00));
    block[0] = U8_C(0x77);

    result = GenMemOpsSetBlocks(dst, USIZE_C(8), block, USIZE_C(1));

    assert(result == RESULT_SUCCESS);
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        assert(dst[i] == U8_C(0x77));
    }

    printf("PASSED\n");
}


void
MultipleBlocks_U16(void)
{
    /*
     * Set multiple 2-byte blocks.
     * dst_sz = 16 bytes = 8 blocks of 2 bytes each.
     */
    u16  dst[8];
    u16  block;
    bool result;
    usize i;

    printf(LOG_PREFIX_CSTR "MultipleBlocks_U16 -> ");

    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        dst[i] = U16_C(0x0000);
    }

    block = U16_C(0xABCD);

    result = GenMemOpsSetBlocks(dst, USIZE_C(16), &block, USIZE_C(2));

    assert(result == RESULT_SUCCESS);
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        assert(dst[i] == U16_C(0xABCD));
    }

    printf("PASSED\n");
}


void
MultipleBlocks_U32(void)
{
    /*
     * Set multiple 4-byte blocks.
     * dst_sz = 32 bytes = 8 blocks of 4 bytes each.
     */
    u32  dst[8];
    u32  block;
    bool result;
    usize i;

    printf(LOG_PREFIX_CSTR "MultipleBlocks_U32 -> ");

    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        dst[i] = U32_C(0x00000000);
    }

    block = U32_C(0x12345678);

    result = GenMemOpsSetBlocks(dst, USIZE_C(32), &block, USIZE_C(4));

    assert(result == RESULT_SUCCESS);
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        assert(dst[i] == U32_C(0x12345678));
    }

    printf("PASSED\n");
}


void
MultipleBlocks_U64(void)
{
    /*
     * Set multiple 8-byte blocks.
     * dst_sz = 64 bytes = 8 blocks of 8 bytes each.
     */
#if defined KD_ARCH_64BIT_INT
    u64  dst[8];
    u64  block;
    bool result;
    usize i;

    printf(LOG_PREFIX_CSTR "MultipleBlocks_U64 -> ");

    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        dst[i] = U64_C(0x0000000000000000);
    }

    block = U64_C(0x123456789ABCDEF0);

    result = GenMemOpsSetBlocks(dst, USIZE_C(64), &block, USIZE_C(8));

    assert(result == RESULT_SUCCESS);
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        assert(dst[i] == U64_C(0x123456789ABCDEF0));
    }

    printf("PASSED\n");
#else
    printf(LOG_PREFIX_CSTR "MultipleBlocks_U64 -> SKIPPED (no 64-bit int support)\n");
#endif
}


void
CustomBlockSize_3Bytes(void)
{
    /*
     * Set blocks with non-standard size (3 bytes).
     * dst_sz = 15 bytes = 5 blocks of 3 bytes each.
     */
    byte  dst[15];
    byte  block[3];
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "CustomBlockSize_3Bytes -> ");

    kdi_FillVal(dst, USIZE_C(15), U8_C(0x00));
    block[0] = U8_C(0xAA);
    block[1] = U8_C(0xBB);
    block[2] = U8_C(0xCC);

    result = GenMemOpsSetBlocks(dst, USIZE_C(15), block, USIZE_C(3));

    assert(result == RESULT_SUCCESS);
    for (i = USIZE_C(0); i < USIZE_C(5); ++i)
    {
        assert(dst[i * USIZE_C(3) + USIZE_C(0)] == U8_C(0xAA));
        assert(dst[i * USIZE_C(3) + USIZE_C(1)] == U8_C(0xBB));
        assert(dst[i * USIZE_C(3) + USIZE_C(2)] == U8_C(0xCC));
    }

    printf("PASSED\n");
}


void
CustomBlockSize_5Bytes(void)
{
    /*
     * Set blocks with 5-byte size.
     * dst_sz = 20 bytes = 4 blocks of 5 bytes each.
     */
    byte  dst[20];
    byte  block[5];
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "CustomBlockSize_5Bytes -> ");

    kdi_FillVal(dst, USIZE_C(20), U8_C(0xFF));
    block[0] = U8_C(0x11);
    block[1] = U8_C(0x22);
    block[2] = U8_C(0x33);
    block[3] = U8_C(0x44);
    block[4] = U8_C(0x55);

    result = GenMemOpsSetBlocks(dst, USIZE_C(20), block, USIZE_C(5));

    assert(result == RESULT_SUCCESS);
    for (i = USIZE_C(0); i < USIZE_C(4); ++i)
    {
        assert(dst[i * USIZE_C(5) + USIZE_C(0)] == U8_C(0x11));
        assert(dst[i * USIZE_C(5) + USIZE_C(1)] == U8_C(0x22));
        assert(dst[i * USIZE_C(5) + USIZE_C(2)] == U8_C(0x33));
        assert(dst[i * USIZE_C(5) + USIZE_C(3)] == U8_C(0x44));
        assert(dst[i * USIZE_C(5) + USIZE_C(4)] == U8_C(0x55));
    }

    printf("PASSED\n");
}


void
LargeBufferWithSmallBlock(void)
{
    /*
     * Large destination with small block size.
     * dst_sz = 128 bytes, block_sz = 2 bytes -> 64 blocks.
     */
    byte  dst[128];
    byte  block[2];
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBufferWithSmallBlock -> ");

    kdi_FillVal(dst, USIZE_C(128), U8_C(0x00));
    block[0] = U8_C(0xEE);
    block[1] = U8_C(0xFF);

    result = GenMemOpsSetBlocks(dst, USIZE_C(128), block, USIZE_C(2));

    assert(result == RESULT_SUCCESS);
    for (i = USIZE_C(0); i < USIZE_C(64); ++i)
    {
        assert(dst[i * USIZE_C(2) + USIZE_C(0)] == U8_C(0xEE));
        assert(dst[i * USIZE_C(2) + USIZE_C(1)] == U8_C(0xFF));
    }

    printf("PASSED\n");
}


void
LargeBufferWithLargeBlock(void)
{
    /*
     * Large destination with large block size.
     * dst_sz = 160 bytes, block_sz = 16 bytes -> 10 blocks.
     */
    byte  dst[160];
    byte  block[16];
    bool  result;
    usize i, j;

    printf(LOG_PREFIX_CSTR "LargeBufferWithLargeBlock -> ");

    kdi_FillVal(dst, USIZE_C(160), U8_C(0x00));
    kdi_FillSeq(block, USIZE_C(16), U8_C(0x10));

    result = GenMemOpsSetBlocks(dst, USIZE_C(160), block, USIZE_C(16));

    assert(result == RESULT_SUCCESS);
    for (i = USIZE_C(0); i < USIZE_C(10); ++i)
    {
        for (j = USIZE_C(0); j < USIZE_C(16); ++j)
        {
            assert(dst[i * USIZE_C(16) + j] == block[j]);
        }
    }

    printf("PASSED\n");
}


void
AllZerosBlock(void)
{
    /*
     * Set blocks where block contains all zeros.
     */
    byte  dst[16];
    byte  block[4];
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "AllZerosBlock -> ");

    kdi_FillVal(dst, USIZE_C(16), U8_C(0xFF));
    kdi_FillVal(block, USIZE_C(4), U8_C(0x00));

    result = GenMemOpsSetBlocks(dst, USIZE_C(16), block, USIZE_C(4));

    assert(result == RESULT_SUCCESS);
    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        assert(dst[i] == U8_C(0x00));
    }

    printf("PASSED\n");
}


void
AllOnesBlock(void)
{
    /*
     * Set blocks where block contains all 0xFF.
     */
    byte  dst[16];
    byte  block[4];
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "AllOnesBlock -> ");

    kdi_FillVal(dst, USIZE_C(16), U8_C(0x00));
    kdi_FillVal(block, USIZE_C(4), U8_C(0xFF));

    result = GenMemOpsSetBlocks(dst, USIZE_C(16), block, USIZE_C(4));

    assert(result == RESULT_SUCCESS);
    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        assert(dst[i] == U8_C(0xFF));
    }

    printf("PASSED\n");
}


void
SequentialPatternBlock(void)
{
    /*
     * Block contains sequential pattern.
     */
    byte  dst[24];
    byte  block[6];
    bool  result;
    usize i, j;

    printf(LOG_PREFIX_CSTR "SequentialPatternBlock -> ");

    kdi_FillVal(dst, USIZE_C(24), U8_C(0x00));
    kdi_FillSeq(block, USIZE_C(6), U8_C(0x00));

    result = GenMemOpsSetBlocks(dst, USIZE_C(24), block, USIZE_C(6));

    assert(result == RESULT_SUCCESS);
    for (i = USIZE_C(0); i < USIZE_C(4); ++i)
    {
        for (j = USIZE_C(0); j < USIZE_C(6); ++j)
        {
            assert(dst[i * USIZE_C(6) + j] == (byte)j);
        }
    }

    printf("PASSED\n");
}


void
AlternatingPatternBlock(void)
{
    /*
     * Block contains alternating byte pattern.
     */
    byte  dst[16];
    byte  block[4];
    bool  result;
    usize i, j;

    printf(LOG_PREFIX_CSTR "AlternatingPatternBlock -> ");

    kdi_FillVal(dst, USIZE_C(16), U8_C(0x00));
    block[0] = U8_C(0xAA);
    block[1] = U8_C(0x55);
    block[2] = U8_C(0xAA);
    block[3] = U8_C(0x55);

    result = GenMemOpsSetBlocks(dst, USIZE_C(16), block, USIZE_C(4));

    assert(result == RESULT_SUCCESS);
    for (i = USIZE_C(0); i < USIZE_C(4); ++i)
    {
        for (j = USIZE_C(0); j < USIZE_C(4); ++j)
        {
            assert(dst[i * USIZE_C(4) + j] == block[j]);
        }
    }

    printf("PASSED\n");
}


void
MismatchedAlignment(void)
{
    /*
     * dst_sz not aligned to block_sz should fail.
     * dst_sz = 17 bytes, block_sz = 4 bytes (17 % 4 != 0).
     */
    byte  dst[17];
    byte  block[4];
    byte  dst_orig[17];
    bool  result;

    printf(LOG_PREFIX_CSTR "MismatchedAlignment -> ");

    kdi_FillVal(dst, USIZE_C(17), U8_C(0xAA));
    kdi_FillVal(dst_orig, USIZE_C(17), U8_C(0xAA));
    kdi_FillVal(block, USIZE_C(4), U8_C(0xFF));

    result = GenMemOpsSetBlocks(dst, USIZE_C(17), block, USIZE_C(4));

    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(17)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    SingleBlockSet();
    MultipleBlocks_U8();
    MultipleBlocks_U16();
    MultipleBlocks_U32();
    MultipleBlocks_U64();
    CustomBlockSize_3Bytes();
    CustomBlockSize_5Bytes();
    LargeBufferWithSmallBlock();
    LargeBufferWithLargeBlock();
    AllZerosBlock();
    AllOnesBlock();
    SequentialPatternBlock();
    AlternatingPatternBlock();
    MismatchedAlignment();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}