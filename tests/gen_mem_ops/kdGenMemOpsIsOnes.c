/**
 * @file kdGenMemOpsIsOnes.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsIsOnes function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsIsOnes function test"
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
    status = GenMemOpsIsOnes(null, buf, USIZE_C(16));
    assert(status == RESULT_FAILURE);

    /* ptr is null (with non-zero size) -> failure */
    status = GenMemOpsIsOnes(&is_ones, null, USIZE_C(16));
    assert(status == RESULT_FAILURE);

    /* sz is zero -> success (trivial: empty buffer) */
    is_ones = RESULT_NOT_EQUALS; /* reset */
    status  = GenMemOpsIsOnes(&is_ones, buf, USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    assert(is_ones == RESULT_EQUALS);

    printf("PASSED\n");
}


void
BufferIsAllOnes(void)
{
    u8   buf[16];
    bool is_ones;
    bool status;

    printf(LOG_PREFIX_CSTR "BufferIsAllOnes -> ");

    /* Fill with all ones (0xFF) */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xFF));

    is_ones = RESULT_NOT_EQUALS;
    status  = GenMemOpsIsOnes(&is_ones, buf, USIZE_C(16));

    assert(status == RESULT_SUCCESS);
    assert(is_ones == RESULT_EQUALS);

    printf("PASSED\n");
}


void
BufferIsNotAllOnes(void)
{
    u8   buf[16];
    bool is_ones;
    bool status;

    printf(LOG_PREFIX_CSTR "BufferIsNotAllOnes -> ");

    /* Fill with all ones */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xFF));

    /* Set middle byte to 0xFE (11111110 binary) */
    buf[8]  = U8_C(0xFE);

    is_ones = RESULT_EQUALS;
    status  = GenMemOpsIsOnes(&is_ones, buf, USIZE_C(16));

    assert(status == RESULT_SUCCESS);
    assert(is_ones == RESULT_NOT_EQUALS);

    /* Test with all zeros */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));
    status = GenMemOpsIsOnes(&is_ones, buf, USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(is_ones == RESULT_NOT_EQUALS);

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
    buf[0] = U8_C(0x7F);
    status = GenMemOpsIsOnes(&is_ones, buf, USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(is_ones == RESULT_NOT_EQUALS);

    /* Reset */
    buf[0]  = U8_C(0xFF);

    /* Last byte is not 0xFF */
    buf[15] = U8_C(0x00);
    status  = GenMemOpsIsOnes(&is_ones, buf, USIZE_C(16));
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
    BufferIsAllOnes();
    BufferIsNotAllOnes();
    EdgeCases();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
