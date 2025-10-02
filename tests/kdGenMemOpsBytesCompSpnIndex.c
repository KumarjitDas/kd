/**
 * @file kdGenMemOpsBytesCompSpnIndex.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsBytesCompSpnIndex function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsBytesCompSpnIndex function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
ReturnsCorrectIndex(void)
{
    kd_usize_t idx;
    char       str[]   = "abcd456+-&*789efgh";
    char       keys1[] = "1234567890";
    char       keys2[] = "!@#$%^&*-+";

    printf(LOG_PREFIX_CSTR "ReturnsCorrectIndex -> ");

    assert(kdGenMemOpsBytesCompSpnIndex(&idx, str, sizeof(str) - 1, keys1, sizeof(keys1) - 1) == KD_RESULT_SUCCESS);
    assert(idx == 4);
    assert(kdGenMemOpsBytesCompSpnIndex(&idx, str, sizeof(str) - 1, keys2, sizeof(keys2) - 1) == KD_RESULT_SUCCESS);
    assert(idx == 7);

    printf("PASSED\n");
}


void
ReturnsFalseIfAllMismatch(void)
{
    kd_usize_t idx;
    char       str[]  = "abcdefghijk";
    char       keys[] = "1234567890";

    printf(LOG_PREFIX_CSTR "ReturnsFalseIfAllMismatch -> ");

    assert(kdGenMemOpsBytesCompSpnIndex(&idx, str, sizeof(str) - 1, keys, sizeof(keys) - 1) == KD_RESULT_FAILURE);

    printf("PASSED\n");
}


void
HandlesNullPointerOrIndex(void)
{
    kd_usize_t idx;
    kd_byte_t  ptr[16], keys[8];

    printf(LOG_PREFIX_CSTR "HandlesNullPointerOrIndex -> ");

    assert(kdGenMemOpsBytesCompSpnIndex((kd_usize_t *)kd_null, kd_null, 0, kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex((kd_usize_t *)kd_null, kd_null, 0, kd_null, sizeof(keys)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex((kd_usize_t *)kd_null, kd_null, 0, keys, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex((kd_usize_t *)kd_null, kd_null, 0, keys, sizeof(keys)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex((kd_usize_t *)kd_null, kd_null, sizeof(ptr), kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex((kd_usize_t *)kd_null, kd_null, sizeof(ptr), kd_null, sizeof(keys)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex((kd_usize_t *)kd_null, kd_null, sizeof(ptr), keys, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex((kd_usize_t *)kd_null, kd_null, sizeof(ptr), keys, sizeof(keys)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex((kd_usize_t *)kd_null, ptr, 0, kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex((kd_usize_t *)kd_null, ptr, 0, kd_null, sizeof(keys)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex((kd_usize_t *)kd_null, ptr, 0, keys, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex((kd_usize_t *)kd_null, ptr, 0, keys, sizeof(keys)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex((kd_usize_t *)kd_null, ptr, sizeof(ptr), kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex((kd_usize_t *)kd_null, ptr, sizeof(ptr), kd_null, sizeof(keys)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex((kd_usize_t *)kd_null, ptr, sizeof(ptr), keys, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex(&idx, kd_null, 0, kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex(&idx, kd_null, 0, kd_null, sizeof(keys)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex(&idx, kd_null, 0, keys, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex(&idx, kd_null, 0, keys, sizeof(keys)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex(&idx, kd_null, sizeof(ptr), kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex(&idx, kd_null, sizeof(ptr), kd_null, sizeof(keys)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex(&idx, kd_null, sizeof(ptr), keys, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex(&idx, kd_null, sizeof(ptr), keys, sizeof(keys)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex(&idx, ptr, 0, kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex(&idx, ptr, 0, kd_null, sizeof(keys)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex(&idx, ptr, 0, keys, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex(&idx, ptr, 0, keys, sizeof(keys)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex(&idx, ptr, sizeof(ptr), kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex(&idx, ptr, sizeof(ptr), kd_null, sizeof(keys)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBytesCompSpnIndex(&idx, ptr, sizeof(ptr), keys, 0) == KD_RESULT_FAILURE);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");
    printf("Library Version: %s\n\n", KD_GEN_MEM_OPS_VERSION_CSTR);

    ReturnsCorrectIndex();
    ReturnsFalseIfAllMismatch();
    HandlesNullPointerOrIndex();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
