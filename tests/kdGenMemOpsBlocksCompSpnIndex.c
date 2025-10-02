/**
 * @file kdGenMemOpsBlocksCompSpnIndex.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsBlocksCompSpnIndex function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsBlocksCompSpnIndex function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
ReturnsCorrectMatchIndex(void)
{
    kd_usize_t idx;
    kd_i16_t   ptr[]   = {'a', 'b', 'c', 'd', '4', '5', '6', '+', '-', '&', '*', '7', '8', '9', 'e', 'f', 'g', 'h'};
    kd_i16_t   keys1[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    kd_i16_t   keys2[] = {'!', '@', '#', '$', '%', '^', '&', '*', '-', '+'};

    printf(LOG_PREFIX_CSTR "ReturnsCorrectMatchIndex -> ");

    assert(kdGenMemOpsBlocksCompSpnIndex(&idx, ptr, sizeof(ptr), keys1, sizeof(*keys1), sizeof(keys1)) == KD_RESULT_SUCCESS);
    assert(idx == (4 * sizeof(*ptr)));
    assert(kdGenMemOpsBlocksCompSpnIndex(&idx, ptr, sizeof(ptr), keys2, sizeof(*keys2), sizeof(keys2)) == KD_RESULT_SUCCESS);
    assert(idx == (7 * sizeof(*ptr)));

    printf("PASSED\n");
}


void
ReturnsFalseIfAllBlocksMismatch(void)
{
    kd_usize_t idx;
    kd_i16_t   ptr[]  = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k'};
    kd_i16_t   keys[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

    printf(LOG_PREFIX_CSTR "ReturnsFalseIfAllBlocksMismatch -> ");

    assert(kdGenMemOpsBlocksCompSpnIndex(&idx, ptr, sizeof(ptr), keys, sizeof(*keys), sizeof(keys)) == KD_RESULT_FAILURE);

    printf("PASSED\n");
}


void
HandlesZeroBlockSize(void)
{
    kd_usize_t idx;
    kd_i16_t   ptr[16], keys[8];

    printf(LOG_PREFIX_CSTR "HandlesZeroBlockSize -> ");

    assert(kdGenMemOpsBlocksCompSpnIndex(&idx, ptr, 0, keys, 0, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBlocksCompSpnIndex(&idx, ptr, 0, keys, 0, sizeof(keys)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBlocksCompSpnIndex(&idx, ptr, 0, keys, sizeof(*keys), 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBlocksCompSpnIndex(&idx, ptr, sizeof(ptr), keys, 0, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBlocksCompSpnIndex(&idx, ptr, sizeof(ptr), keys, 0, sizeof(keys)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBlocksCompSpnIndex(&idx, ptr, sizeof(ptr), keys, sizeof(*keys), 0) == KD_RESULT_FAILURE);

    printf("PASSED\n");
}


void
HandlesNullPointers(void)
{
    kd_usize_t idx;
    kd_i16_t   ptr[16], keys[8];

    printf(LOG_PREFIX_CSTR "HandlesNullPointers -> ");

    assert(kdGenMemOpsBlocksCompSpnIndex((kd_usize_t *)kd_null, kd_null, sizeof(ptr), kd_null, sizeof(*keys), sizeof(keys)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBlocksCompSpnIndex((kd_usize_t *)kd_null, kd_null, sizeof(ptr), keys, sizeof(*keys), sizeof(keys)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBlocksCompSpnIndex((kd_usize_t *)kd_null, ptr, sizeof(ptr), kd_null, sizeof(*keys), sizeof(keys)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBlocksCompSpnIndex(&idx, kd_null, sizeof(ptr), kd_null, sizeof(*keys), sizeof(keys)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBlocksCompSpnIndex(&idx, kd_null, sizeof(ptr), keys, sizeof(*keys), sizeof(keys)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsBlocksCompSpnIndex(&idx, ptr, sizeof(ptr), kd_null, sizeof(*keys), sizeof(keys)) == KD_RESULT_FAILURE);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");
    printf("Library Version: %s\n\n", KD_GEN_MEM_OPS_VERSION_CSTR);

    ReturnsCorrectMatchIndex();
    ReturnsFalseIfAllBlocksMismatch();
    HandlesZeroBlockSize();
    HandlesNullPointers();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
