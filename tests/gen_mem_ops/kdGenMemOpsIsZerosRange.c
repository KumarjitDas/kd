/**
 * @file kdGenMemOpsIsZerosRange.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsIsZerosRange function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsIsZerosRange function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


static void
kdi_FillVal(u8 *dst, usize sz, u8 val)
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
    u8   buf[16];
    bool is_zeros;
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* result pointer is null -> failure */
    status = GenMemOpsIsZerosRange(null, buf, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure */
    status = GenMemOpsIsZerosRange(&is_zeros, null, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = GenMemOpsIsZerosRange(&is_zeros, buf, USIZE_C(0), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* byte_count is zero -> success (trivial vacuous truth: empty range is all zeros) */
    is_zeros = RESULT_NOT_EQUALS; /* reset to false */
    status   = GenMemOpsIsZerosRange(&is_zeros, buf, USIZE_C(16), USIZE_C(0), USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    assert(is_zeros == RESULT_EQUALS);

    printf("PASSED\n");
}


void
CountClamping(void)
{
    u8   buf[16];
    bool is_zeros;
    bool status;

    printf(LOG_PREFIX_CSTR "CountClamping -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* begin_idx + byte_count > base_sz */
    /* 14 + 4 = 18 > 16. Should clamp to 16-14=2 bytes (indices 14, 15) */

    /* Case 1: All relevant bytes are zero */
    is_zeros = RESULT_NOT_EQUALS;
    status   = GenMemOpsIsZerosRange(&is_zeros, buf, USIZE_C(16), USIZE_C(14), USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(is_zeros == RESULT_EQUALS);

    /* Case 2: One of the relevant bytes is non-zero */
    buf[15]  = U8_C(0xFF);
    is_zeros = RESULT_EQUALS;
    status   = GenMemOpsIsZerosRange(&is_zeros, buf, USIZE_C(16), USIZE_C(14), USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(is_zeros == RESULT_NOT_EQUALS);

    printf("PASSED\n");
}


void
IndicesOutOfBounds(void)
{
    u8   buf[16];
    bool is_zeros;
    bool status;

    printf(LOG_PREFIX_CSTR "IndicesOutOfBounds -> ");

    /* begin_idx > base_sz */
    /* Start index itself is invalid, should still fail */
    status = GenMemOpsIsZerosRange(&is_zeros, buf, USIZE_C(16), USIZE_C(17), USIZE_C(1));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
RangeIsAllZeros(void)
{
    u8   buf[16];
    bool is_zeros;
    bool status;

    printf(LOG_PREFIX_CSTR "RangeIsAllZeros -> ");

    /* Fill buffer with zeros */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Check full range */
    is_zeros = RESULT_NOT_EQUALS;
    status   = GenMemOpsIsZerosRange(&is_zeros, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16));

    assert(status == RESULT_SUCCESS);
    assert(is_zeros == RESULT_EQUALS);

    /* Check sub-range */
    is_zeros = RESULT_NOT_EQUALS;
    status   = GenMemOpsIsZerosRange(&is_zeros, buf, USIZE_C(16), USIZE_C(4), USIZE_C(8));

    assert(status == RESULT_SUCCESS);
    assert(is_zeros == RESULT_EQUALS);

    printf("PASSED\n");
}


void
RangeIsNotAllZeros(void)
{
    u8   buf[16];
    bool is_zeros;
    bool status;

    printf(LOG_PREFIX_CSTR "RangeIsNotAllZeros -> ");

    /* Fill with zeros */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Set a byte in the middle to non-zero */
    buf[8]   = U8_C(0x01);

    /* Check range covering the non-zero byte */
    is_zeros = RESULT_EQUALS;
    status   = GenMemOpsIsZerosRange(&is_zeros, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16));

    assert(status == RESULT_SUCCESS);
    assert(is_zeros == RESULT_NOT_EQUALS);

    /* Check range covering ONLY zeros (before the dirty byte) */
    is_zeros = RESULT_NOT_EQUALS;
    status   = GenMemOpsIsZerosRange(&is_zeros, buf, USIZE_C(16), USIZE_C(0), USIZE_C(8));

    assert(status == RESULT_SUCCESS);
    assert(is_zeros == RESULT_EQUALS);

    /* Check range covering ONLY zeros (after the dirty byte) */
    is_zeros = RESULT_NOT_EQUALS;
    status   = GenMemOpsIsZerosRange(&is_zeros, buf, USIZE_C(16), USIZE_C(9), USIZE_C(7));

    assert(status == RESULT_SUCCESS);
    assert(is_zeros == RESULT_EQUALS);

    printf("PASSED\n");
}


void
EdgeCases(void)
{
    u8   buf[16];
    bool is_zeros;
    bool status;

    printf(LOG_PREFIX_CSTR "EdgeCases -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* First byte is non-zero */
    buf[0] = U8_C(0xFF);
    status = GenMemOpsIsZerosRange(&is_zeros, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(is_zeros == RESULT_NOT_EQUALS);

    /* Reset */
    buf[0]  = U8_C(0x00);

    /* Last byte is non-zero */
    buf[15] = U8_C(0xFF);
    status  = GenMemOpsIsZerosRange(&is_zeros, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(is_zeros == RESULT_NOT_EQUALS);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    CountClamping();
    IndicesOutOfBounds();
    RangeIsAllZeros();
    RangeIsNotAllZeros();
    EdgeCases();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
