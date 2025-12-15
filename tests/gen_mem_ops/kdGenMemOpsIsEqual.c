/**
 * @file kdGenMemOpsIsEqual.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsIsEqual function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsIsEqual function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


static void
kdi_FillSeq(u8 *dst, usize sz, u8 start)
{
    usize i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        dst[i] = (u8)(start + (u8)i);
    }
}


void
BasicArguments(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillSeq(buf1, USIZE_C(16), U8_C(0x10));
    kdi_FillSeq(buf2, USIZE_C(16), U8_C(0x20));

    /* result pointer is null -> failure */
    status = GenMemOpsIsEqual(null, buf1, buf2, USIZE_C(16));
    assert(status == RESULT_FAILURE);

    /* ptr_1 is null -> failure */
    status = GenMemOpsIsEqual(&is_equal, null, buf2, USIZE_C(16));
    assert(status == RESULT_FAILURE);

    /* ptr_2 is null -> failure */
    status = GenMemOpsIsEqual(&is_equal, buf1, null, USIZE_C(16));
    assert(status == RESULT_FAILURE);

    /* sz is zero -> success (trivial equality) */
    is_equal = RESULT_NOT_EQUALS; /* reset */
    status   = GenMemOpsIsEqual(&is_equal, buf1, buf2, USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == RESULT_EQUALS);

    /* ptr_1 == ptr_2 -> success (optimization check) */
    is_equal = RESULT_NOT_EQUALS; /* reset */
    status   = GenMemOpsIsEqual(&is_equal, buf1, buf1, USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == RESULT_EQUALS);

    printf("PASSED\n");
}


void
BuffersMatch(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "BuffersMatch -> ");

    /* Fill identical content */
    kdi_FillSeq(buf1, USIZE_C(16), U8_C(0x55));
    kdi_FillSeq(buf2, USIZE_C(16), U8_C(0x55));

    is_equal = RESULT_FAILURE;
    status   = GenMemOpsIsEqual(&is_equal, buf1, buf2, USIZE_C(16));

    assert(status == RESULT_SUCCESS);
    assert(is_equal == RESULT_EQUALS);

    printf("PASSED\n");
}


void
BuffersDoNotMatch(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "BuffersDoNotMatch -> ");

    kdi_FillSeq(buf1, USIZE_C(16), U8_C(0x55));
    kdi_FillSeq(buf2, USIZE_C(16), U8_C(0x55));

    /* Create mismatch at index 10 */
    buf2[10] = U8_C(0xFF);

    is_equal = RESULT_SUCCESS;
    status   = GenMemOpsIsEqual(&is_equal, buf1, buf2, USIZE_C(16));

    assert(status == RESULT_SUCCESS);
    assert(is_equal == RESULT_NOT_EQUALS);

    printf("PASSED\n");
}


void
PartialMatch(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "PartialMatch -> ");

    kdi_FillSeq(buf1, USIZE_C(16), U8_C(0xAA));
    kdi_FillSeq(buf2, USIZE_C(16), U8_C(0xAA));

    /* Mismatch at last byte */
    buf2[15] = U8_C(0xBB);

    /* Check first 15 bytes -> Should be Equal */
    is_equal = RESULT_FAILURE;
    status   = GenMemOpsIsEqual(&is_equal, buf1, buf2, USIZE_C(15));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == RESULT_EQUALS);

    /* Check all 16 bytes -> Should Not Be Equal */
    is_equal = RESULT_SUCCESS;
    status   = GenMemOpsIsEqual(&is_equal, buf1, buf2, USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == RESULT_NOT_EQUALS);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    BuffersMatch();
    BuffersDoNotMatch();
    PartialMatch();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
