/**
 * @file kdGenMemOpsFindBlockIndex.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindBlockIndex function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindBlockIndex function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
ReturnsCorrectIndexIfBlockFound(void)
{
    kd_usize_t idx;
    kd_i16_t   arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    kd_i16_t   val1  = 3;
    kd_i16_t   val2  = 8;

    printf(LOG_PREFIX_CSTR "ReturnsCorrectIndexIfBlockFound -> ");

    assert(kdGenMemOpsFindBlockIndex(&idx, arr, sizeof(arr), &val1, sizeof(val1)) == KD_RESULT_SUCCESS);
    assert(idx == (2 * sizeof(val1)));
    assert(kdGenMemOpsFindBlockIndex(&idx, arr, sizeof(arr), &val2, sizeof(val2)) == KD_RESULT_SUCCESS);
    assert(idx == (7 * sizeof(val2)));

    printf("PASSED\n");
}


void
ReturnsFalseIfBlockNotFound(void)
{
    kd_usize_t idx;
    kd_i16_t   arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    kd_i16_t   val1  = 0;
    kd_i16_t   val2  = 11;

    printf(LOG_PREFIX_CSTR "ReturnsFalseIfBlockNotFound -> ");

    assert(kdGenMemOpsFindBlockIndex(&idx, arr, sizeof(arr), &val1, sizeof(val1)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsFindBlockIndex(&idx, arr, sizeof(arr), &val2, sizeof(val2)) == KD_RESULT_FAILURE);

    printf("PASSED\n");
}


void
HandlesZeroBlockSize(void)
{
    kd_usize_t idx;
    kd_i16_t   val;
    kd_byte_t  ptr[16];

    printf(LOG_PREFIX_CSTR "HandlesZeroBlockSize -> ");

    assert(kdGenMemOpsFindBlockIndex(&idx, kd_null, 0, kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsFindBlockIndex(&idx, kd_null, 0, kd_null, sizeof(val)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsFindBlockIndex(&idx, kd_null, sizeof(ptr), kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsFindBlockIndex(&idx, kd_null, 0, &val, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsFindBlockIndex(&idx, kd_null, 0, &val, sizeof(val)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsFindBlockIndex(&idx, kd_null, sizeof(ptr), &val, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsFindBlockIndex(&idx, ptr, 0, kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsFindBlockIndex(&idx, ptr, 0, kd_null, sizeof(val)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsFindBlockIndex(&idx, ptr, sizeof(ptr), kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsFindBlockIndex(&idx, ptr, 0, &val, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsFindBlockIndex(&idx, ptr, 0, &val, sizeof(val)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsFindBlockIndex(&idx, ptr, sizeof(ptr), &val, 0) == KD_RESULT_FAILURE);

    printf("PASSED\n");
}


void
HandlesNullPointerOrIndex(void)
{
    kd_usize_t idx;
    kd_i16_t   val;
    kd_byte_t  ptr[16];

    printf(LOG_PREFIX_CSTR "HandlesNullPointerOrIndex -> ");

    assert(kdGenMemOpsFindBlockIndex((kd_usize_t *)kd_null, kd_null, sizeof(ptr), kd_null, sizeof(val)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsFindBlockIndex((kd_usize_t *)kd_null, kd_null, sizeof(ptr), &val, sizeof(val)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsFindBlockIndex((kd_usize_t *)kd_null, ptr, sizeof(ptr), kd_null, sizeof(val)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsFindBlockIndex((kd_usize_t *)kd_null, ptr, sizeof(ptr), &val, sizeof(val)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsFindBlockIndex(&idx, kd_null, sizeof(ptr), kd_null, sizeof(val)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsFindBlockIndex(&idx, kd_null, sizeof(ptr), &val, sizeof(val)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsFindBlockIndex(&idx, ptr, sizeof(ptr), kd_null, sizeof(val)) == KD_RESULT_FAILURE);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");
    printf("Library Version: %s\n\n", KD_GEN_MEM_OPS_VERSION_CSTR);

    ReturnsCorrectIndexIfBlockFound();
    ReturnsFalseIfBlockNotFound();
    HandlesZeroBlockSize();
    HandlesNullPointerOrIndex();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
