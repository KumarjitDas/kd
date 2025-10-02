/**
 * @file kdGenMemOpsBlocksCompSpn.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsBlocksCompSpn function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsBlocksCompSpn function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
FindsFirstMatchingBlock(void)
{
    kd_i16_t ptr[]   = {'a', 'b', 'c', 'd', '4', '5', '6', '+', '-', '&', '*', '7', '8', '9', 'e', 'f', 'g', 'h'};
    kd_i16_t keys1[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    kd_i16_t keys2[] = {'!', '@', '#', '$', '%', '^', '&', '*', '-', '+'};

    printf(LOG_PREFIX_CSTR "FindsFirstMatchingBlock -> ");

    assert(kdGenMemOpsBlocksCompSpn(ptr, sizeof(ptr), keys1, sizeof(*keys1), sizeof(keys1)) == (ptr + 4));
    assert(kdGenMemOpsBlocksCompSpn(ptr, sizeof(ptr), keys2, sizeof(*keys2), sizeof(keys2)) == (ptr + 7));

    printf("PASSED\n");
}


void
ReturnsNullIfAllMismatch(void)
{
    kd_i16_t ptr[]  = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k'};
    kd_i16_t keys[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

    printf(LOG_PREFIX_CSTR "ReturnsNullIfAllMismatch -> ");

    assert(kdGenMemOpsBlocksCompSpn(ptr, sizeof(ptr), keys, sizeof(*keys), sizeof(keys)) == kd_null);

    printf("PASSED\n");
}


void
HandlesZeroBlockSize(void)
{
    kd_i16_t ptr[16], keys[8];

    printf(LOG_PREFIX_CSTR "HandlesZeroBlockSize -> ");

    assert(kdGenMemOpsBlocksCompSpn(ptr, 0, keys, 0, 0) == kd_null);
    assert(kdGenMemOpsBlocksCompSpn(ptr, 0, keys, 0, sizeof(keys)) == kd_null);
    assert(kdGenMemOpsBlocksCompSpn(ptr, 0, keys, sizeof(*keys), 0) == kd_null);
    assert(kdGenMemOpsBlocksCompSpn(ptr, sizeof(ptr), keys, 0, 0) == kd_null);
    assert(kdGenMemOpsBlocksCompSpn(ptr, sizeof(ptr), keys, 0, sizeof(keys)) == kd_null);
    assert(kdGenMemOpsBlocksCompSpn(ptr, sizeof(ptr), keys, sizeof(*keys), 0) == kd_null);

    printf("PASSED\n");
}


void
HandlesNullPointers(void)
{
    kd_i16_t ptr[16], keys[8];

    printf(LOG_PREFIX_CSTR "HandlesNullPointers -> ");

    assert(kdGenMemOpsBlocksCompSpn(kd_null, sizeof(ptr), kd_null, sizeof(*keys), sizeof(keys)) == kd_null);
    assert(kdGenMemOpsBlocksCompSpn(kd_null, sizeof(ptr), keys, sizeof(*keys), sizeof(keys)) == kd_null);
    assert(kdGenMemOpsBlocksCompSpn(ptr, sizeof(ptr), kd_null, sizeof(*keys), sizeof(keys)) == kd_null);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");
    printf("Library Version: %s\n\n", KD_GEN_MEM_OPS_VERSION_CSTR);

    FindsFirstMatchingBlock();
    ReturnsNullIfAllMismatch();
    HandlesZeroBlockSize();
    HandlesNullPointers();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
