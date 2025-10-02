/**
 * @file kdGenMemOpsFindByteIndex.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindByteIndex function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindByteIndex function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
ReturnsCorrectIndexIfFound(void)
{
    kd_usize_t idx;
    kd_byte_t  ptr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    printf(LOG_PREFIX_CSTR "ReturnsCorrectIndexIfFound -> ");

    assert(kdGenMemOpsFindByteIndex(&idx, ptr, sizeof(ptr), 3) == KD_RESULT_SUCCESS);
    assert(idx == 2);
    assert(kdGenMemOpsFindByteIndex(&idx, ptr, sizeof(ptr), 8) == KD_RESULT_SUCCESS);
    assert(idx == 7);

    printf("PASSED\n");
}


void
ReturnsFalseIfNotFound(void)
{
    kd_usize_t idx;
    kd_byte_t  ptr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    printf(LOG_PREFIX_CSTR "ReturnsFalseIfNotFound -> ");

    assert(kdGenMemOpsFindByteIndex(&idx, ptr, sizeof(ptr), 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsFindByteIndex(&idx, ptr, sizeof(ptr), 11) == KD_RESULT_FAILURE);

    printf("PASSED\n");
}


void
HandlesNullPointerOrIndexPointer(void)
{
    kd_usize_t idx;
    kd_byte_t  ptr[16];

    printf(LOG_PREFIX_CSTR "HandlesNullPointerOrIndexPointer -> ");

    assert(kdGenMemOpsFindByteIndex((kd_usize_t *)kd_null, kd_null, 0, 69) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsFindByteIndex((kd_usize_t *)kd_null, kd_null, sizeof(ptr), 69) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsFindByteIndex((kd_usize_t *)kd_null, ptr, 0, 69) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsFindByteIndex((kd_usize_t *)kd_null, ptr, sizeof(ptr), 69) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsFindByteIndex(&idx, kd_null, 0, 69) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsFindByteIndex(&idx, kd_null, sizeof(ptr), 69) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsFindByteIndex(&idx, ptr, 0, 69) == KD_RESULT_FAILURE);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");
    printf("Library Version: %s\n\n", KD_GEN_MEM_OPS_VERSION_CSTR);

    ReturnsCorrectIndexIfFound();
    ReturnsFalseIfNotFound();
    HandlesNullPointerOrIndexPointer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
