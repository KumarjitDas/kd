/**
 * @file kdGenMemOpsSetBytesRange.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsSetBytesRange function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsSetBytesRange function test"
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
    byte  buf[16];
    byte  buf_orig[16];
    usize set_sz;
    bool  result;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x10));
    kdi_FillSeq(buf_orig, USIZE_C(16), U8_C(0x10));

    /* set_sz is null -> immediate failure, buffer unchanged, we cannot inspect set_sz */
    result = GenMemOpsSetBytesRange(buf, USIZE_C(16), null, USIZE_C(0), USIZE_C(8), U8_C(0xAA));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(16)) == RESULT_SUCCESS);

    /* base is null -> failure, *set_sz must be 0 */
    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBytesRange(null, USIZE_C(16), &set_sz, USIZE_C(0), USIZE_C(8), U8_C(0xAA));
    assert(result == RESULT_FAILURE);
    assert(set_sz == USIZE_C(0));

    /* base_sz == 0 -> failure, buffer unchanged, *set_sz == 0 */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x20));
    kdi_FillSeq(buf_orig, USIZE_C(16), U8_C(0x20));

    set_sz = USIZE_C(0xBEEF);
    result = GenMemOpsSetBytesRange(buf, USIZE_C(0), &set_sz, USIZE_C(0), USIZE_C(8), U8_C(0xAA));
    assert(result == RESULT_FAILURE);
    assert(set_sz == USIZE_C(0));
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(16)) == RESULT_SUCCESS);

    /* begin_idx >= base_sz -> failure, *set_sz == 0, buffer unchanged */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x30));
    kdi_FillSeq(buf_orig, USIZE_C(16), U8_C(0x30));

    set_sz = USIZE_C(0xCAFE);
    result = GenMemOpsSetBytesRange(
        buf,
        USIZE_C(16),
        &set_sz,
        USIZE_C(16), /* begin_idx == base_sz -> OOB */
        USIZE_C(4),
        U8_C(0xAA)
    );
    assert(result == RESULT_FAILURE);
    assert(set_sz == USIZE_C(0));
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(16)) == RESULT_SUCCESS);

    /* count == 0 -> failure, *set_sz == 0, buffer unchanged */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x40));
    kdi_FillSeq(buf_orig, USIZE_C(16), U8_C(0x40));

    set_sz = USIZE_C(0x1234);
    result = GenMemOpsSetBytesRange(buf, USIZE_C(16), &set_sz, USIZE_C(4), USIZE_C(0), U8_C(0xAA));
    assert(result == RESULT_FAILURE);
    assert(set_sz == USIZE_C(0));
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
InBoundsSetMiddleRange(void)
{
    byte  buf[16];
    byte  expected[16];
    usize set_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "InBoundsSetMiddleRange -> ");

    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x10));

    /* expected: bytes [4..9] set to 0xAA, others unchanged */
    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        if (i >= USIZE_C(4) && i < USIZE_C(10))
        {
            expected[i] = U8_C(0xAA);
        }
        else
        {
            expected[i] = (byte)(U8_C(0x10) + (byte)i);
        }
    }

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBytesRange(buf, USIZE_C(16), &set_sz, USIZE_C(4), USIZE_C(6), U8_C(0xAA));
    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(6));
    assert(kdi_BytesEqual(buf, expected, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
ClampedAtEndOfBuffer(void)
{
    byte  buf[16];
    byte  expected[16];
    usize set_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "ClampedAtEndOfBuffer -> ");

    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x50));

    /* begin_idx = 12, count = 10, base_sz = 16 -> we can only set 4 bytes */
    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        if (i >= USIZE_C(12))
        {
            expected[i] = U8_C(0xBB);
        }
        else
        {
            expected[i] = (byte)(U8_C(0x50) + (byte)i);
        }
    }

    set_sz = USIZE_C(0xDEAD);
    result = GenMemOpsSetBytesRange(buf, USIZE_C(16), &set_sz, USIZE_C(12), USIZE_C(10), U8_C(0xBB));
    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(4)); /* clamped to remaining bytes */
    assert(kdi_BytesEqual(buf, expected, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SetFromNonZeroBeginIdx(void)
{
    byte  buf[12];
    byte  expected[12];
    usize set_sz;
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "SetFromNonZeroBeginIdx -> ");

    kdi_FillSeq(buf, USIZE_C(12), U8_C(0x70));

    /* begin_idx = 3, count = 5, base_sz = 12 -> bytes [3..7] set */
    for (i = USIZE_C(0); i < USIZE_C(12); ++i)
    {
        if (i >= USIZE_C(3) && i < USIZE_C(8))
        {
            expected[i] = U8_C(0x01);
        }
        else
        {
            expected[i] = (byte)(U8_C(0x70) + (byte)i);
        }
    }

    set_sz = USIZE_C(0xBEEF);
    result = GenMemOpsSetBytesRange(buf, USIZE_C(12), &set_sz, USIZE_C(3), USIZE_C(5), U8_C(0x01));
    assert(result == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(5));
    assert(kdi_BytesEqual(buf, expected, USIZE_C(12)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    InBoundsSetMiddleRange();
    ClampedAtEndOfBuffer();
    SetFromNonZeroBeginIdx();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
