/**
 * @file kdGenMemOpsIsOnesRange.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsIsOnesRange function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsIsOnesRange function test"
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
    bool is_ones;
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0xFF));

    /* result pointer is null -> failure */
    status = GenMemOpsIsOnesRange(null, buf, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure */
    status = GenMemOpsIsOnesRange(&is_ones, null, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = GenMemOpsIsOnesRange(&is_ones, buf, USIZE_C(0), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* byte_count is zero -> success (trivial vacuous truth) */
    is_ones = RESULT_NOT_EQUALS; /* reset to false */
    status  = GenMemOpsIsOnesRange(&is_ones, buf, USIZE_C(16), USIZE_C(0), USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    assert(is_ones == RESULT_EQUALS);

    printf("PASSED\n");
}


void
CountClamping(void)
{
    u8   buf[16];
    bool is_ones;
    bool status;

    printf(LOG_PREFIX_CSTR "CountClamping -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0xFF));

    /* begin_idx + byte_count > base_sz */
    /* 14 + 4 = 18 > 16. Should clamp to 16-14=2 bytes (indices 14, 15) */

    /* Case 1: All relevant bytes are 0xFF */
    is_ones = RESULT_NOT_EQUALS;
    status  = GenMemOpsIsOnesRange(&is_ones, buf, USIZE_C(16), USIZE_C(14), USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(is_ones == RESULT_EQUALS);

    /* Case 2: One of the relevant bytes is not 0xFF */
    buf[15] = U8_C(0x00);
    is_ones = RESULT_EQUALS;
    status  = GenMemOpsIsOnesRange(&is_ones, buf, USIZE_C(16), USIZE_C(14), USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(is_ones == RESULT_NOT_EQUALS);

    printf("PASSED\n");
}


void
IndicesOutOfBounds(void)
{
    u8   buf[16];
    bool is_ones;
    bool status;

    printf(LOG_PREFIX_CSTR "IndicesOutOfBounds -> ");

    /* begin_idx >= base_sz */
    status = GenMemOpsIsOnesRange(&is_ones, buf, USIZE_C(16), USIZE_C(16), USIZE_C(1));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
RangeIsAllOnes(void)
{
    u8   buf[16];
    bool is_ones;
    bool status;

    printf(LOG_PREFIX_CSTR "RangeIsAllOnes -> ");

    /* Fill buffer with 0xFF */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xFF));

    /* Check full range */
    is_ones = RESULT_NOT_EQUALS;
    status  = GenMemOpsIsOnesRange(&is_ones, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16));

    assert(status == RESULT_SUCCESS);
    assert(is_ones == RESULT_EQUALS);

    /* Check sub-range */
    is_ones = RESULT_NOT_EQUALS;
    status  = GenMemOpsIsOnesRange(&is_ones, buf, USIZE_C(16), USIZE_C(4), USIZE_C(8));

    assert(status == RESULT_SUCCESS);
    assert(is_ones == RESULT_EQUALS);

    printf("PASSED\n");
}


void
RangeIsNotAllOnes(void)
{
    u8   buf[16];
    bool is_ones;
    bool status;

    printf(LOG_PREFIX_CSTR "RangeIsNotAllOnes -> ");

    /* Fill with 0xFF */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xFF));

    /* Set a byte in the middle to something else (e.g. 0xFE or 0x00) */
    buf[8]  = U8_C(0xFE);

    /* Check range covering the dirty byte */
    is_ones = RESULT_EQUALS;
    status  = GenMemOpsIsOnesRange(&is_ones, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16));

    assert(status == RESULT_SUCCESS);
    assert(is_ones == RESULT_NOT_EQUALS);

    /* Check range covering ONLY ones (before the dirty byte) */
    is_ones = RESULT_NOT_EQUALS;
    status  = GenMemOpsIsOnesRange(&is_ones, buf, USIZE_C(16), USIZE_C(0), USIZE_C(8));

    assert(status == RESULT_SUCCESS);
    assert(is_ones == RESULT_EQUALS);

    /* Check range covering ONLY ones (after the dirty byte) */
    is_ones = RESULT_NOT_EQUALS;
    status  = GenMemOpsIsOnesRange(&is_ones, buf, USIZE_C(16), USIZE_C(9), USIZE_C(7));

    assert(status == RESULT_SUCCESS);
    assert(is_ones == RESULT_EQUALS);

    printf("PASSED\n");
}


void
EdgeCases(void)
{
    u8   buf[16];
    bool is_ones;
    bool status;

    printf(LOG_PREFIX_CSTR "EdgeCases -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0xFF));

    /* First byte is not 0xFF */
    buf[0] = U8_C(0x00);
    status = GenMemOpsIsOnesRange(&is_ones, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(is_ones == RESULT_NOT_EQUALS);

    /* Reset */
    buf[0]  = U8_C(0xFF);

    /* Last byte is not 0xFF */
    buf[15] = U8_C(0x00);
    status  = GenMemOpsIsOnesRange(&is_ones, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(is_ones == RESULT_NOT_EQUALS);

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
    RangeIsAllOnes();
    RangeIsNotAllOnes();
    EdgeCases();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
