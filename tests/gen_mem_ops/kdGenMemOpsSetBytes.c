/**
 * @file kdGenMemOpsSetBytes.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsSetBytes function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsSetBytes function test"
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

    /* dst is null, dst_sz non-zero -> failure, nothing to check about memory */
    result = GenMemOpsSetBytes(null, USIZE_C(8), U8_C(0xAA));
    assert(result == RESULT_FAILURE);

    /* dst non-null, dst_sz == 0 -> failure, buffer must remain unchanged */
    result = GenMemOpsSetBytes(buf, USIZE_C(0), U8_C(0xAA));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
FullBufferSet(void)
{
    byte buf[32];
    byte expected[32];
    bool result;

    printf(LOG_PREFIX_CSTR "FullBufferSet -> ");

    kdi_FillSeq(buf, USIZE_C(32), U8_C(0x00));

    /* expected: all bytes set to 0xAA */
    {
        usize i;
        for (i = USIZE_C(0); i < USIZE_C(32); ++i)
        {
            expected[i] = U8_C(0xAA);
        }
    }

    result = GenMemOpsSetBytes(buf, USIZE_C(32), U8_C(0xAA));
    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(32)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
PartialRangeViaPointerArithmetic(void)
{
    byte  buf[24];
    byte  buf_orig[24];
    byte  expected[24];
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "PartialRangeViaPointerArithmetic -> ");

    /* buf = 0x10,0x11,... */
    kdi_FillSeq(buf, USIZE_C(24), U8_C(0x10));
    kdi_FillSeq(buf_orig, USIZE_C(24), U8_C(0x10));

    /* We will set bytes [4..15] (12 bytes) to 0xFF using a non-base pointer: buf + 4 */
    for (i = USIZE_C(0); i < USIZE_C(24); ++i)
    {
        if (i >= USIZE_C(4) && i < USIZE_C(16))
        {
            expected[i] = U8_C(0xFF);
        }
        else
        {
            expected[i] = buf_orig[i];
        }
    }

    result = GenMemOpsSetBytes(buf + 4, USIZE_C(12), U8_C(0xFF));
    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(24)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
DifferentValues(void)
{
    byte  buf[8];
    byte  expected0[8];
    byte  expectedFF[8];
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "DifferentValues -> ");

    kdi_FillSeq(buf, USIZE_C(8), U8_C(0x33));

    /* expected0: all zeros */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        expected0[i] = U8_C(0x00);
    }

    /* expectedFF: all 0xFF */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        expectedFF[i] = U8_C(0xFF);
    }

    /* set to 0x00 */
    result = GenMemOpsSetBytes(buf, USIZE_C(8), U8_C(0x00));
    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected0, USIZE_C(8)) == RESULT_SUCCESS);

    /* set to 0xFF */
    result = GenMemOpsSetBytes(buf, USIZE_C(8), U8_C(0xFF));
    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expectedFF, USIZE_C(8)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    FullBufferSet();
    PartialRangeViaPointerArithmetic();
    DifferentValues();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
