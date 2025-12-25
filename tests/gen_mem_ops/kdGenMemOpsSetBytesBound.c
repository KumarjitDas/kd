/**
 * @file kdGenMemOpsSetBytesBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsSetBytesBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsSetBytesBound function test"
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
     */
    byte  buf[64];
    byte  buf_orig[64];
    usize set_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillVal(buf, USIZE_C(64), U8_C(0xAA));
    kdi_FillVal(buf_orig, USIZE_C(64), U8_C(0xAA));

    /* set_sz pointer is null */
    result = GenMemOpsSetBytesBound(buf, USIZE_C(64), null, USIZE_C(0), USIZE_C(16), U8_C(0xFF));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* base is null */
    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBytesBound(null, USIZE_C(64), &set_sz, USIZE_C(0), USIZE_C(16), U8_C(0xFF));
    assert(result == RESULT_FAILURE);
    assert(set_sz == USIZE_C(0));

    /* base_sz is zero */
    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBytesBound(buf, USIZE_C(0), &set_sz, USIZE_C(0), USIZE_C(16), U8_C(0xFF));
    assert(result == RESULT_FAILURE);
    assert(set_sz == USIZE_C(0));
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* begin_idx out of bounds (equals base_sz) */
    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBytesBound(buf, USIZE_C(64), &set_sz, USIZE_C(64), USIZE_C(16), U8_C(0xFF));
    assert(result == RESULT_FAILURE);
    assert(set_sz == USIZE_C(0));
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* begin_idx out of bounds (greater than base_sz) */
    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBytesBound(buf, USIZE_C(64), &set_sz, USIZE_C(100), USIZE_C(16), U8_C(0xFF));
    assert(result == RESULT_FAILURE);
    assert(set_sz == USIZE_C(0));
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(64)) == RESULT_SUCCESS);

    /* count is zero */
    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBytesBound(buf, USIZE_C(64), &set_sz, USIZE_C(0), USIZE_C(0), U8_C(0xFF));
    assert(result == RESULT_FAILURE);
    assert(set_sz == USIZE_C(0));
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(64)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
ExactFitSet(void)
{
    /*
     * Set buf[10..25] (16 bytes) exactly fits the requested count.
     */
    byte  buf[32];
    byte  buf_orig[32];
    usize set_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "ExactFitSet -> ");

    kdi_FillVal(buf, USIZE_C(32), U8_C(0xAA));
    kdi_FillVal(buf_orig, USIZE_C(32), U8_C(0xAA));

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBytesBound(buf, USIZE_C(32), &set_sz, USIZE_C(10), USIZE_C(16), U8_C(0xFF));

    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(16));

    /* Head (0..9) should remain unchanged */
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(10)) == RESULT_SUCCESS);

    /* Middle (10..25) should be set to 0xFF */
    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        assert(buf[USIZE_C(10) + i] == U8_C(0xFF));
    }

    /* Tail (26..31) should remain unchanged */
    assert(kdi_BytesEqual(buf + USIZE_C(26), buf_orig + USIZE_C(26), USIZE_C(6)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SetAtStart(void)
{
    /*
     * Set bytes starting at index 0.
     */
    byte  buf[32];
    byte  buf_orig[32];
    usize set_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "SetAtStart -> ");

    kdi_FillSeq(buf, USIZE_C(32), U8_C(0x00));
    kdi_FillSeq(buf_orig, USIZE_C(32), U8_C(0x00));

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBytesBound(buf, USIZE_C(32), &set_sz, USIZE_C(0), USIZE_C(12), U8_C(0xCC));

    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(12));

    /* First 12 bytes should be 0xCC */
    for (i = USIZE_C(0); i < USIZE_C(12); ++i)
    {
        assert(buf[i] == U8_C(0xCC));
    }

    /* Remaining bytes should be unchanged */
    assert(kdi_BytesEqual(buf + USIZE_C(12), buf_orig + USIZE_C(12), USIZE_C(20)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SetAtEnd(void)
{
    /*
     * Set bytes at the end of buffer.
     */
    byte  buf[32];
    byte  buf_orig[32];
    usize set_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "SetAtEnd -> ");

    kdi_FillSeq(buf, USIZE_C(32), U8_C(0x20));
    kdi_FillSeq(buf_orig, USIZE_C(32), U8_C(0x20));

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBytesBound(buf, USIZE_C(32), &set_sz, USIZE_C(24), USIZE_C(8), U8_C(0x77));

    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(8));

    /* First 24 bytes should be unchanged */
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(24)) == RESULT_SUCCESS);

    /* Last 8 bytes should be 0x77 */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        assert(buf[USIZE_C(24) + i] == U8_C(0x77));
    }

    printf("PASSED\n");
}


void
TruncationDueToSpace(void)
{
    /*
     * Request to set 20 bytes starting at index 50 in buffer of size 60.
     * Only 10 bytes available, so set_sz should be 10.
     */
    byte  buf[60];
    byte  buf_orig[60];
    usize set_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "TruncationDueToSpace -> ");

    kdi_FillVal(buf, USIZE_C(60), U8_C(0x00));
    kdi_FillVal(buf_orig, USIZE_C(60), U8_C(0x00));

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBytesBound(buf, USIZE_C(60), &set_sz, USIZE_C(50), USIZE_C(20), U8_C(0xAB));

    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(10));

    /* First 50 bytes should be unchanged */
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(50)) == RESULT_SUCCESS);

    /* buf[50..59] should be set to 0xAB */
    for (i = USIZE_C(0); i < USIZE_C(10); ++i)
    {
        assert(buf[USIZE_C(50) + i] == U8_C(0xAB));
    }

    printf("PASSED\n");
}


void
SingleByte(void)
{
    /*
     * Minimal case: set exactly 1 byte.
     */
    byte  buf[10];
    byte  buf_orig[10];
    usize set_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "SingleByte -> ");

    kdi_FillVal(buf, USIZE_C(10), U8_C(0x11));
    kdi_FillVal(buf_orig, USIZE_C(10), U8_C(0x11));

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBytesBound(buf, USIZE_C(10), &set_sz, USIZE_C(5), USIZE_C(1), U8_C(0xEE));

    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(1));
    assert(buf[5] == U8_C(0xEE));

    /* Other bytes should be unchanged */
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(5)) == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf + USIZE_C(6), buf_orig + USIZE_C(6), USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SetToZero(void)
{
    /*
     * Set bytes to zero value.
     */
    byte  buf[16];
    usize set_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "SetToZero -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0xFF));

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBytesBound(buf, USIZE_C(16), &set_sz, USIZE_C(4), USIZE_C(8), U8_C(0x00));

    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(8));

    /* buf[4..11] should be zero */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        assert(buf[USIZE_C(4) + i] == U8_C(0x00));
    }

    printf("PASSED\n");
}


void
SetToAllOnes(void)
{
    /*
     * Set bytes to 0xFF value.
     */
    byte  buf[16];
    usize set_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "SetToAllOnes -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBytesBound(buf, USIZE_C(16), &set_sz, USIZE_C(3), USIZE_C(10), U8_C(0xFF));

    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(10));

    /* buf[3..12] should be 0xFF */
    for (i = USIZE_C(0); i < USIZE_C(10); ++i)
    {
        assert(buf[USIZE_C(3) + i] == U8_C(0xFF));
    }

    printf("PASSED\n");
}


void
LargeBufferSet(void)
{
    /*
     * Set bytes in a large buffer.
     */
    byte  buf[256];
    byte  buf_orig[256];
    usize set_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBufferSet -> ");

    kdi_FillSeq(buf, USIZE_C(256), U8_C(0x00));
    kdi_FillSeq(buf_orig, USIZE_C(256), U8_C(0x00));

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBytesBound(buf, USIZE_C(256), &set_sz, USIZE_C(50), USIZE_C(100), U8_C(0xDD));

    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(100));

    /* First 50 bytes should be unchanged */
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(50)) == RESULT_SUCCESS);

    /* buf[50..149] should be 0xDD */
    for (i = USIZE_C(0); i < USIZE_C(100); ++i)
    {
        assert(buf[USIZE_C(50) + i] == U8_C(0xDD));
    }

    /* Remaining bytes should be unchanged */
    assert(kdi_BytesEqual(buf + USIZE_C(150), buf_orig + USIZE_C(150), USIZE_C(106)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SetEntireBuffer(void)
{
    /*
     * Set all bytes in buffer from start to end.
     */
    byte  buf[32];
    usize set_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "SetEntireBuffer -> ");

    kdi_FillSeq(buf, USIZE_C(32), U8_C(0x10));

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBytesBound(buf, USIZE_C(32), &set_sz, USIZE_C(0), USIZE_C(32), U8_C(0x99));

    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(32));

    /* All bytes should be 0x99 */
    for (i = USIZE_C(0); i < USIZE_C(32); ++i)
    {
        assert(buf[i] == U8_C(0x99));
    }

    printf("PASSED\n");
}


void
SetLastByteOnly(void)
{
    /*
     * Set only the very last byte of buffer.
     */
    byte  buf[20];
    byte  buf_orig[20];
    usize set_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "SetLastByteOnly -> ");

    kdi_FillVal(buf, USIZE_C(20), U8_C(0x55));
    kdi_FillVal(buf_orig, USIZE_C(20), U8_C(0x55));

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBytesBound(buf, USIZE_C(20), &set_sz, USIZE_C(19), USIZE_C(1), U8_C(0xBB));

    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(1));
    assert(buf[19] == U8_C(0xBB));

    /* All other bytes should be unchanged */
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(19)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
ExcessiveCountRequest(void)
{
    /*
     * Request count that far exceeds available space.
     * Should set only what's available.
     */
    byte  buf[20];
    byte  buf_orig[20];
    usize set_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "ExcessiveCountRequest -> ");

    kdi_FillVal(buf, USIZE_C(20), U8_C(0x33));
    kdi_FillVal(buf_orig, USIZE_C(20), U8_C(0x33));

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBytesBound(buf, USIZE_C(20), &set_sz, USIZE_C(15), USIZE_C(1000), U8_C(0x88));

    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(5));

    /* First 15 bytes should be unchanged */
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(15)) == RESULT_SUCCESS);

    /* buf[15..19] should be set (only 5 bytes available) */
    for (i = USIZE_C(0); i < USIZE_C(5); ++i)
    {
        assert(buf[USIZE_C(15) + i] == U8_C(0x88));
    }

    printf("PASSED\n");
}


void
MiddleRegionSet(void)
{
    /*
     * Set bytes in the middle of buffer, leaving head and tail intact.
     */
    byte  buf[50];
    byte  buf_orig[50];
    usize set_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "MiddleRegionSet -> ");

    kdi_FillSeq(buf, USIZE_C(50), U8_C(0x00));
    kdi_FillSeq(buf_orig, USIZE_C(50), U8_C(0x00));

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBytesBound(buf, USIZE_C(50), &set_sz, USIZE_C(20), USIZE_C(15), U8_C(0xF0));

    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(15));

    /* Head (0..19) should be unchanged */
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(20)) == RESULT_SUCCESS);

    /* Middle (20..34) should be 0xF0 */
    for (i = USIZE_C(0); i < USIZE_C(15); ++i)
    {
        assert(buf[USIZE_C(20) + i] == U8_C(0xF0));
    }

    /* Tail (35..49) should be unchanged */
    assert(kdi_BytesEqual(buf + USIZE_C(35), buf_orig + USIZE_C(35), USIZE_C(15)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SetWithVariousValues(void)
{
    /*
     * Set bytes with different values in sequence to verify each works.
     */
    byte  buf[16];
    usize set_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "SetWithVariousValues -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Set with 0x11 */
    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBytesBound(buf, USIZE_C(16), &set_sz, USIZE_C(0), USIZE_C(4), U8_C(0x11));
    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(4));
    assert(buf[0] == U8_C(0x11) && buf[1] == U8_C(0x11) && buf[2] == U8_C(0x11) && buf[3] == U8_C(0x11));

    /* Set with 0x22 */
    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBytesBound(buf, USIZE_C(16), &set_sz, USIZE_C(4), USIZE_C(4), U8_C(0x22));
    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(4));
    assert(buf[4] == U8_C(0x22) && buf[5] == U8_C(0x22) && buf[6] == U8_C(0x22) && buf[7] == U8_C(0x22));

    /* Set with 0x33 */
    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBytesBound(buf, USIZE_C(16), &set_sz, USIZE_C(8), USIZE_C(4), U8_C(0x33));
    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(4));
    assert(buf[8] == U8_C(0x33) && buf[9] == U8_C(0x33) && buf[10] == U8_C(0x33) && buf[11] == U8_C(0x33));

    /* Set with 0x44 */
    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBytesBound(buf, USIZE_C(16), &set_sz, USIZE_C(12), USIZE_C(4), U8_C(0x44));
    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(4));
    assert(buf[12] == U8_C(0x44) && buf[13] == U8_C(0x44) && buf[14] == U8_C(0x44) && buf[15] == U8_C(0x44));

    printf("PASSED\n");
}


void
OnlyOneByteAvailable(void)
{
    /*
     * Buffer has only 1 byte available from begin_idx.
     * Request more but should set only 1.
     */
    byte  buf[16];
    byte  buf_orig[16];
    usize set_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "OnlyOneByteAvailable -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));
    kdi_FillVal(buf_orig, USIZE_C(16), U8_C(0xAA));

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBytesBound(buf, USIZE_C(16), &set_sz, USIZE_C(15), USIZE_C(10), U8_C(0xCC));

    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(1));
    assert(buf[15] == U8_C(0xCC));

    /* All other bytes should be unchanged */
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(15)) == RESULT_SUCCESS);

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
    SingleByte();
    SetToZero();
    SetToAllOnes();
    LargeBufferSet();
    SetEntireBuffer();
    SetLastByteOnly();
    ExcessiveCountRequest();
    MiddleRegionSet();
    SetWithVariousValues();
    OnlyOneByteAvailable();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}