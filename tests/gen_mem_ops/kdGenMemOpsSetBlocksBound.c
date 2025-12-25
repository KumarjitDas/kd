/**
 * @file kdGenMemOpsSetBlocksBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsSetBlocksBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsSetBlocksBound function test"
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
     * Test NULL pointer validation, zero-size parameters, and out-of-bounds indices.
     * All failure cases should set set_sz to 0 (if pointer valid)
     * and leave buffer unchanged.
     * Note: base_sz, begin_idx, and block_sz must be aligned to block_sz.
     * byte_count can be any value (doesn't need alignment).
     */
    byte  buf[64];
    byte  block[4];
    byte  buf_orig[64];
    usize set_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillVal(buf, USIZE_C(64), U8_C(0xAA));
    kdi_FillVal(buf_orig, USIZE_C(64), U8_C(0xAA));
    block[0] = U8_C(0x11);
    block[1] = U8_C(0x22);
    block[2] = U8_C(0x33);
    block[3] = U8_C(0x44);

    /* set_sz pointer is null */
    result = GenMemOpsSetBlocksBound(buf, USIZE_C(64), null, USIZE_C(0), USIZE_C(16), block, USIZE_C(4));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* base is null */
    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBlocksBound(null, USIZE_C(64), &set_sz, USIZE_C(0), USIZE_C(16), block, USIZE_C(4));
    assert(result == RESULT_FAILURE);
    assert(set_sz == USIZE_C(0));

    /* block is null */
    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBlocksBound(buf, USIZE_C(64), &set_sz, USIZE_C(0), USIZE_C(16), null, USIZE_C(4));
    assert(result == RESULT_FAILURE);
    assert(set_sz == USIZE_C(0));
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* base_sz is zero */
    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBlocksBound(buf, USIZE_C(0), &set_sz, USIZE_C(0), USIZE_C(16), block, USIZE_C(4));
    assert(result == RESULT_FAILURE);
    assert(set_sz == USIZE_C(0));
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* block_sz is zero */
    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBlocksBound(buf, USIZE_C(64), &set_sz, USIZE_C(0), USIZE_C(16), block, USIZE_C(0));
    assert(result == RESULT_FAILURE);
    assert(set_sz == USIZE_C(0));
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* begin_idx out of bounds (equals base_sz) */
    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBlocksBound(buf, USIZE_C(64), &set_sz, USIZE_C(64), USIZE_C(16), block, USIZE_C(4));
    assert(result == RESULT_FAILURE);
    assert(set_sz == USIZE_C(0));
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* begin_idx out of bounds (greater than base_sz) */
    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBlocksBound(buf, USIZE_C(64), &set_sz, USIZE_C(100), USIZE_C(16), block, USIZE_C(4));
    assert(result == RESULT_FAILURE);
    assert(set_sz == USIZE_C(0));
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* byte_count is zero */
    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBlocksBound(buf, USIZE_C(64), &set_sz, USIZE_C(0), USIZE_C(0), block, USIZE_C(4));
    assert(result == RESULT_FAILURE);
    assert(set_sz == USIZE_C(0));
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* base_sz not aligned to block_sz */
    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBlocksBound(buf, USIZE_C(65), &set_sz, USIZE_C(0), USIZE_C(16), block, USIZE_C(4));
    assert(result == RESULT_FAILURE);
    assert(set_sz == USIZE_C(0));
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* begin_idx not aligned to block_sz */
    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBlocksBound(buf, USIZE_C(64), &set_sz, USIZE_C(3), USIZE_C(16), block, USIZE_C(4));
    assert(result == RESULT_FAILURE);
    assert(set_sz == USIZE_C(0));
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(64)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
ExactFitSet(void)
{
    /*
     * Set buf[16..31] (16 bytes = 4 blocks of 4 bytes each) exactly fits the requested byte_count.
     */
    byte  buf[64];
    byte  buf_orig[64];
    byte  block[4];
    usize set_sz;
    bool  result;
    usize i, j;

    printf(LOG_PREFIX_CSTR "ExactFitSet -> ");

    kdi_FillVal(buf, USIZE_C(64), U8_C(0xAA));
    kdi_FillVal(buf_orig, USIZE_C(64), U8_C(0xAA));
    block[0] = U8_C(0x11);
    block[1] = U8_C(0x22);
    block[2] = U8_C(0x33);
    block[3] = U8_C(0x44);

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBlocksBound(buf, USIZE_C(64), &set_sz, USIZE_C(16), USIZE_C(16), block, USIZE_C(4));

    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(16));

    /* Head (0..15) should remain unchanged */
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(16)) == RESULT_SUCCESS);

    /* Middle (16..31) should be filled with block pattern (4 blocks) */
    for (i = USIZE_C(0); i < USIZE_C(4); ++i)
    {
        for (j = USIZE_C(0); j < USIZE_C(4); ++j)
        {
            assert(buf[USIZE_C(16) + i * USIZE_C(4) + j] == block[j]);
        }
    }

    /* Tail (32..63) should remain unchanged */
    assert(kdi_BytesEqual(buf + USIZE_C(32), buf_orig + USIZE_C(32), USIZE_C(32)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SetAtStart(void)
{
    /*
     * Set blocks starting at index 0.
     */
    u32   buf[8];
    u32   buf_orig[8];
    u32   block;
    usize set_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "SetAtStart -> ");

    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        buf[i]      = U32_C(0xAAAAAAAA);
        buf_orig[i] = U32_C(0xAAAAAAAA);
    }

    block = U32_C(0x12345678);

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBlocksBound(buf, USIZE_C(32), &set_sz, USIZE_C(0), USIZE_C(12), &block, USIZE_C(4));

    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(12));

    /* First 3 blocks (12 bytes) should be set */
    for (i = USIZE_C(0); i < USIZE_C(3); ++i)
    {
        assert(buf[i] == U32_C(0x12345678));
    }

    /* Remaining blocks should be unchanged */
    for (i = USIZE_C(3); i < USIZE_C(8); ++i)
    {
        assert(buf[i] == buf_orig[i]);
    }

    printf("PASSED\n");
}


void
SetAtEnd(void)
{
    /*
     * Set blocks at the end of buffer.
     */
    u16   buf[16];
    u16   buf_orig[16];
    u16   block;
    usize set_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "SetAtEnd -> ");

    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        buf[i]      = U16_C(0xFFFF);
        buf_orig[i] = U16_C(0xFFFF);
    }

    block = U16_C(0xABCD);

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBlocksBound(buf, USIZE_C(32), &set_sz, USIZE_C(24), USIZE_C(8), &block, USIZE_C(2));

    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(8));

    /* First 12 blocks should be unchanged */
    for (i = USIZE_C(0); i < USIZE_C(12); ++i)
    {
        assert(buf[i] == buf_orig[i]);
    }

    /* Last 4 blocks (8 bytes) should be set */
    for (i = USIZE_C(12); i < USIZE_C(16); ++i)
    {
        assert(buf[i] == U16_C(0xABCD));
    }

    printf("PASSED\n");
}


void
TruncationDueToSpace(void)
{
    /*
     * Request to set 20 bytes starting at index 52 in buffer of size 64.
     * Only 12 bytes available (3 blocks of 4 bytes each).
     */
    byte  buf[64];
    byte  buf_orig[64];
    byte  block[4];
    usize set_sz;
    bool  result;
    usize i, j;

    printf(LOG_PREFIX_CSTR "TruncationDueToSpace -> ");

    kdi_FillVal(buf, USIZE_C(64), U8_C(0x00));
    kdi_FillVal(buf_orig, USIZE_C(64), U8_C(0x00));
    kdi_FillSeq(block, USIZE_C(4), U8_C(0xF0));

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBlocksBound(buf, USIZE_C(64), &set_sz, USIZE_C(52), USIZE_C(20), block, USIZE_C(4));

    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(12));

    /* First 52 bytes should be unchanged */
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(52)) == RESULT_SUCCESS);

    /* buf[52..63] should be set (3 blocks of 4 bytes) */
    for (i = USIZE_C(0); i < USIZE_C(3); ++i)
    {
        for (j = USIZE_C(0); j < USIZE_C(4); ++j)
        {
            assert(buf[USIZE_C(52) + i * USIZE_C(4) + j] == block[j]);
        }
    }

    printf("PASSED\n");
}


void
SingleBlockSet(void)
{
    /*
     * Minimal case: set exactly 1 block at specific offset.
     */
    u32   buf[8];
    u32   buf_orig[8];
    u32   block;
    usize set_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "SingleBlockSet -> ");

    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        buf[i]      = U32_C(0x11111111);
        buf_orig[i] = U32_C(0x11111111);
    }

    block = U32_C(0xDEADBEEF);

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBlocksBound(buf, USIZE_C(32), &set_sz, USIZE_C(20), USIZE_C(4), &block, USIZE_C(4));

    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(4));

    /* Only buf[5] should be set */
    for (i = USIZE_C(0); i < USIZE_C(5); ++i)
    {
        assert(buf[i] == buf_orig[i]);
    }
    assert(buf[5] == U32_C(0xDEADBEEF));
    for (i = USIZE_C(6); i < USIZE_C(8); ++i)
    {
        assert(buf[i] == buf_orig[i]);
    }

    printf("PASSED\n");
}


void
LargeBufferSet(void)
{
    /*
     * Set blocks in a large buffer.
     * buf_sz = 256 bytes, set 100 bytes (25 blocks of 4 bytes) starting at index 80.
     */
    byte  buf[256];
    byte  buf_orig[256];
    byte  block[4];
    usize set_sz;
    bool  result;
    usize i, j;

    printf(LOG_PREFIX_CSTR "LargeBufferSet -> ");

    kdi_FillSeq(buf, USIZE_C(256), U8_C(0x00));
    kdi_FillSeq(buf_orig, USIZE_C(256), U8_C(0x00));
    block[0] = U8_C(0xAA);
    block[1] = U8_C(0xBB);
    block[2] = U8_C(0xCC);
    block[3] = U8_C(0xDD);

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBlocksBound(buf, USIZE_C(256), &set_sz, USIZE_C(80), USIZE_C(100), block, USIZE_C(4));

    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(100));

    /* First 80 bytes should be unchanged */
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(80)) == RESULT_SUCCESS);

    /* buf[80..179] should be set (25 blocks) */
    for (i = USIZE_C(0); i < USIZE_C(25); ++i)
    {
        for (j = USIZE_C(0); j < USIZE_C(4); ++j)
        {
            assert(buf[USIZE_C(80) + i * USIZE_C(4) + j] == block[j]);
        }
    }

    /* Remaining bytes should be unchanged */
    assert(kdi_BytesEqual(buf + USIZE_C(180), buf_orig + USIZE_C(180), USIZE_C(76)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SetEntireBuffer(void)
{
    /*
     * Set all blocks in buffer from start to end.
     */
    u16   buf[16];
    u16   block;
    usize set_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "SetEntireBuffer -> ");

    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        buf[i] = U16_C(0x0000);
    }

    block = U16_C(0x9876);

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBlocksBound(buf, USIZE_C(32), &set_sz, USIZE_C(0), USIZE_C(32), &block, USIZE_C(2));

    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(32));

    /* All blocks should be set */
    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        assert(buf[i] == U16_C(0x9876));
    }

    printf("PASSED\n");
}


void
SetLastBlockOnly(void)
{
    /*
     * Set only the very last block of buffer.
     */
    u32   buf[10];
    u32   buf_orig[10];
    u32   block;
    usize set_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "SetLastBlockOnly -> ");

    for (i = USIZE_C(0); i < USIZE_C(10); ++i)
    {
        buf[i]      = U32_C(0x55555555);
        buf_orig[i] = U32_C(0x55555555);
    }

    block = U32_C(0xFFEEDDCC);

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBlocksBound(buf, USIZE_C(40), &set_sz, USIZE_C(36), USIZE_C(4), &block, USIZE_C(4));

    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(4));

    /* All except last block should be unchanged */
    for (i = USIZE_C(0); i < USIZE_C(9); ++i)
    {
        assert(buf[i] == buf_orig[i]);
    }
    assert(buf[9] == U32_C(0xFFEEDDCC));

    printf("PASSED\n");
}


void
ExcessiveByteCountRequest(void)
{
    /*
     * Request byte_count that far exceeds available space.
     * Should set only what's available.
     */
    byte  buf[32];
    byte  buf_orig[32];
    byte  block[4];
    usize set_sz;
    bool  result;
    usize i, j;

    printf(LOG_PREFIX_CSTR "ExcessiveByteCountRequest -> ");

    kdi_FillVal(buf, USIZE_C(32), U8_C(0x33));
    kdi_FillVal(buf_orig, USIZE_C(32), U8_C(0x33));
    kdi_FillSeq(block, USIZE_C(4), U8_C(0x80));

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBlocksBound(buf, USIZE_C(32), &set_sz, USIZE_C(20), USIZE_C(1000), block, USIZE_C(4));

    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(12));

    /* First 20 bytes should be unchanged */
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(20)) == RESULT_SUCCESS);

    /* buf[20..31] should be set (3 blocks, only 12 bytes available) */
    for (i = USIZE_C(0); i < USIZE_C(3); ++i)
    {
        for (j = USIZE_C(0); j < USIZE_C(4); ++j)
        {
            assert(buf[USIZE_C(20) + i * USIZE_C(4) + j] == block[j]);
        }
    }

    printf("PASSED\n");
}


void
MiddleRegionSet(void)
{
    /*
     * Set blocks in the middle of buffer, leaving head and tail intact.
     */
    byte  buf[64];
    byte  buf_orig[64];
    byte  block[4];
    usize set_sz;
    bool  result;
    usize i, j;

    printf(LOG_PREFIX_CSTR "MiddleRegionSet -> ");

    kdi_FillSeq(buf, USIZE_C(64), U8_C(0x00));
    kdi_FillSeq(buf_orig, USIZE_C(64), U8_C(0x00));
    block[0] = U8_C(0x11);
    block[1] = U8_C(0x22);
    block[2] = U8_C(0x33);
    block[3] = U8_C(0x44);

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBlocksBound(buf, USIZE_C(64), &set_sz, USIZE_C(24), USIZE_C(20), block, USIZE_C(4));

    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(20));

    /* Head (0..23) should be unchanged */
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(24)) == RESULT_SUCCESS);

    /* Middle (24..43) should be set (5 blocks) */
    for (i = USIZE_C(0); i < USIZE_C(5); ++i)
    {
        for (j = USIZE_C(0); j < USIZE_C(4); ++j)
        {
            assert(buf[USIZE_C(24) + i * USIZE_C(4) + j] == block[j]);
        }
    }

    /* Tail (44..63) should be unchanged */
    assert(kdi_BytesEqual(buf + USIZE_C(44), buf_orig + USIZE_C(44), USIZE_C(20)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
CustomBlockSize_3Bytes(void)
{
    /*
     * Set blocks with non-standard size (3 bytes).
     * buf_sz = 30 bytes, set 15 bytes (5 blocks) starting at index 9.
     */
    byte  buf[30];
    byte  buf_orig[30];
    byte  block[3];
    usize set_sz;
    bool  result;
    usize i, j;

    printf(LOG_PREFIX_CSTR "CustomBlockSize_3Bytes -> ");

    kdi_FillVal(buf, USIZE_C(30), U8_C(0xFF));
    kdi_FillVal(buf_orig, USIZE_C(30), U8_C(0xFF));
    block[0] = U8_C(0xAA);
    block[1] = U8_C(0xBB);
    block[2] = U8_C(0xCC);

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBlocksBound(buf, USIZE_C(30), &set_sz, USIZE_C(9), USIZE_C(15), block, USIZE_C(3));

    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(15));

    /* First 9 bytes should be unchanged */
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(9)) == RESULT_SUCCESS);

    /* buf[9..23] should be set (5 blocks) */
    for (i = USIZE_C(0); i < USIZE_C(5); ++i)
    {
        for (j = USIZE_C(0); j < USIZE_C(3); ++j)
        {
            assert(buf[USIZE_C(9) + i * USIZE_C(3) + j] == block[j]);
        }
    }

    /* Remaining bytes should be unchanged */
    assert(kdi_BytesEqual(buf + USIZE_C(24), buf_orig + USIZE_C(24), USIZE_C(6)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
ByteCountNotAlignedToBlock(void)
{
    /*
     * byte_count = 18 bytes, block_sz = 4 bytes.
     * 18 / 4 = 4 blocks (16 bytes), with 2 bytes truncated.
     * Should set only complete blocks (16 bytes).
     */
    byte  buf[32];
    byte  buf_orig[32];
    byte  block[4];
    usize set_sz;
    bool  result;
    usize i, j;

    printf(LOG_PREFIX_CSTR "ByteCountNotAlignedToBlock -> ");

    kdi_FillVal(buf, USIZE_C(32), U8_C(0x00));
    kdi_FillVal(buf_orig, USIZE_C(32), U8_C(0x00));
    block[0] = U8_C(0x12);
    block[1] = U8_C(0x34);
    block[2] = U8_C(0x56);
    block[3] = U8_C(0x78);

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBlocksBound(buf, USIZE_C(32), &set_sz, USIZE_C(8), USIZE_C(18), block, USIZE_C(4));

    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(16));

    /* First 8 bytes should be unchanged */
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(8)) == RESULT_SUCCESS);

    /* buf[8..23] should be set (4 blocks = 16 bytes) */
    for (i = USIZE_C(0); i < USIZE_C(4); ++i)
    {
        for (j = USIZE_C(0); j < USIZE_C(4); ++j)
        {
            assert(buf[USIZE_C(8) + i * USIZE_C(4) + j] == block[j]);
        }
    }

    /* Remaining bytes should be unchanged */
    assert(kdi_BytesEqual(buf + USIZE_C(24), buf_orig + USIZE_C(24), USIZE_C(8)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
OnlyOneBlockAvailable(void)
{
    /*
     * Buffer has only 1 block (4 bytes) available from begin_idx.
     * Request more but should set only 1 block.
     */
    byte  buf[32];
    byte  buf_orig[32];
    byte  block[4];
    usize set_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "OnlyOneBlockAvailable -> ");

    kdi_FillVal(buf, USIZE_C(32), U8_C(0xAA));
    kdi_FillVal(buf_orig, USIZE_C(32), U8_C(0xAA));
    block[0] = U8_C(0xCC);
    block[1] = U8_C(0xDD);
    block[2] = U8_C(0xEE);
    block[3] = U8_C(0xFF);

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBlocksBound(buf, USIZE_C(32), &set_sz, USIZE_C(28), USIZE_C(20), block, USIZE_C(4));

    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(4));

    /* All except last block should be unchanged */
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(28)) == RESULT_SUCCESS);

    /* buf[28..31] should be set (only 1 block available) */
    for (i = USIZE_C(0); i < USIZE_C(4); ++i)
    {
        assert(buf[USIZE_C(28) + i] == block[i]);
    }

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    ExactFitSet();
    SetAtStart();
    SetAtEnd();
    TruncationDueToSpace();
    SingleBlockSet();
    LargeBufferSet();
    SetEntireBuffer();
    SetLastBlockOnly();
    ExcessiveByteCountRequest();
    MiddleRegionSet();
    CustomBlockSize_3Bytes();
    ByteCountNotAlignedToBlock();
    OnlyOneBlockAvailable();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}