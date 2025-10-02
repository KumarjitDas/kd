/**
 * @file kdGenMemOpsFindAllByteIndices.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindAllByteIndices function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindAllByteIndices function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
FindsAllOccurrences(void)
{
    kd_byte_t  ptr[] = {1, 2, 3, 2, 5, 2, 7, 3, 9, 10};
    kd_usize_t idxs[8];

    printf(LOG_PREFIX_CSTR "FindsAllOccurrences -> ");

    assert(kdGenMemOpsFindAllByteIndices(idxs, sizeof(idxs), ptr, sizeof(ptr), 2) == 3);
    assert(idxs[0] == 1);
    assert(idxs[1] == 3);
    assert(idxs[2] == 5);
    assert(kdGenMemOpsFindAllByteIndices(idxs, sizeof(idxs), ptr, sizeof(ptr), 3) == 2);
    assert(idxs[0] == 2);
    assert(idxs[1] == 7);

    printf("PASSED\n");
}


void
ReturnsZeroIfNotFound(void)
{
    kd_byte_t  ptr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    kd_usize_t idxs[8];

    printf(LOG_PREFIX_CSTR "ReturnsZeroIfNotFound -> ");

    assert(kdGenMemOpsFindAllByteIndices(idxs, sizeof(idxs), ptr, sizeof(ptr), 0) == 0);
    assert(kdGenMemOpsFindAllByteIndices(idxs, sizeof(idxs), ptr, sizeof(ptr), 69) == 0);

    printf("PASSED\n");
}


void
HandlesZeroSize(void)
{
    kd_byte_t  ptr[16];
    kd_usize_t idxs[8];

    printf(LOG_PREFIX_CSTR "HandlesZeroSize -> ");

    assert(kdGenMemOpsFindAllByteIndices(idxs, 0, ptr, 0, 69) == 0);
    assert(kdGenMemOpsFindAllByteIndices(idxs, 0, ptr, sizeof(ptr), 69) == 0);
    assert(kdGenMemOpsFindAllByteIndices(idxs, sizeof(idxs), ptr, 0, 69) == 0);

    printf("PASSED\n");
}


void
HandlesNullPointer(void)
{
    kd_byte_t  ptr[16];
    kd_usize_t idxs[8];

    printf(LOG_PREFIX_CSTR "HandlesNullPointer -> ");

    assert(kdGenMemOpsFindAllByteIndices((kd_usize_t *)kd_null, 8, kd_null, 16, 69) == 0);
    assert(kdGenMemOpsFindAllByteIndices((kd_usize_t *)kd_null, 8, ptr, 16, 69) == 0);
    assert(kdGenMemOpsFindAllByteIndices(idxs, 8, kd_null, 16, 69) == 0);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");
    printf("Library Version: %s\n\n", KD_GEN_MEM_OPS_VERSION_CSTR);

    FindsAllOccurrences();
    ReturnsZeroIfNotFound();
    HandlesZeroSize();
    HandlesNullPointer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
