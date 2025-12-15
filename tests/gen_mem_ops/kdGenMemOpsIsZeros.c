/**
 * @file kdGenMemOpsIsZeros.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsIsZeros function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsIsZeros function test"
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
    status = GenMemOpsIsZeros(null, buf, USIZE_C(16));
    assert(status == RESULT_FAILURE);

    /* ptr is null (with non-zero size) -> failure */
    status = GenMemOpsIsZeros(&is_zeros, null, USIZE_C(16));
    assert(status == RESULT_FAILURE);

    /* sz is zero -> success (trivial: empty buffer is all zeros) */
    is_zeros = RESULT_NOT_EQUALS; /* reset */
    status   = GenMemOpsIsZeros(&is_zeros, buf, USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    assert(is_zeros == RESULT_EQUALS);

    printf("PASSED\n");
}


void
BufferIsAllZeros(void)
{
    u8   buf[16];
    bool is_zeros;
    bool status;

    printf(LOG_PREFIX_CSTR "BufferIsAllZeros -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    is_zeros = RESULT_NOT_EQUALS;
    status   = GenMemOpsIsZeros(&is_zeros, buf, USIZE_C(16));

    assert(status == RESULT_SUCCESS);
    assert(is_zeros == RESULT_EQUALS);

    printf("PASSED\n");
}


void
BufferIsNotAllZeros(void)
{
    u8   buf[16];
    bool is_zeros;
    bool status;

    printf(LOG_PREFIX_CSTR "BufferIsNotAllZeros -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Set middle byte to non-zero */
    buf[8]   = U8_C(0x01);

    is_zeros = RESULT_EQUALS;
    status   = GenMemOpsIsZeros(&is_zeros, buf, USIZE_C(16));

    assert(status == RESULT_SUCCESS);
    assert(is_zeros == RESULT_NOT_EQUALS);

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

    /* First byte non-zero */
    buf[0] = U8_C(0xFF);
    status = GenMemOpsIsZeros(&is_zeros, buf, USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(is_zeros == RESULT_NOT_EQUALS);

    /* Reset */
    buf[0]  = U8_C(0x00);

    /* Last byte non-zero */
    buf[15] = U8_C(0xFF);
    status  = GenMemOpsIsZeros(&is_zeros, buf, USIZE_C(16));
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
    BufferIsAllZeros();
    BufferIsNotAllZeros();
    EdgeCases();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
