/**
 * @file kdGenMemOpsFindAllBytes.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindAllBytes function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindAllBytes function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
FindsAllOccurrences(void)
{
    kd_byte_t  ptr[] = {1, 2, 3, 2, 5, 2, 7, 3, 9, 10};
    kd_byte_t *found_ptrs[8];

    printf(LOG_PREFIX_CSTR "FindsAllOccurrences -> ");

    assert(kdGenMemOpsFindAllBytes(found_ptrs, sizeof(found_ptrs), ptr, sizeof(ptr), 2) == 3);
    assert(found_ptrs[0] == (ptr + 1));
    assert(found_ptrs[1] == (ptr + 3));
    assert(found_ptrs[2] == (ptr + 5));
    assert(kdGenMemOpsFindAllBytes(found_ptrs, sizeof(found_ptrs), ptr, sizeof(ptr), 3) == 2);
    assert(found_ptrs[0] == (ptr + 2));
    assert(found_ptrs[1] == (ptr + 7));

    printf("PASSED\n");
}


void
ReturnsZeroIfNotFound(void)
{
    kd_byte_t  ptr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    kd_byte_t *found_ptrs[8];

    printf(LOG_PREFIX_CSTR "ReturnsZeroIfNotFound -> ");

    assert(kdGenMemOpsFindAllBytes(found_ptrs, sizeof(found_ptrs), ptr, sizeof(ptr), 0) == 0);
    assert(kdGenMemOpsFindAllBytes(found_ptrs, sizeof(found_ptrs), ptr, sizeof(ptr), 69) == 0);

    printf("PASSED\n");
}


void
HandlesZeroSize(void)
{
    kd_byte_t  ptr[16];
    kd_byte_t *found_ptrs[8];

    printf(LOG_PREFIX_CSTR "HandlesZeroSize -> ");

    assert(kdGenMemOpsFindAllBytes(found_ptrs, 0, ptr, 0, 69) == 0);
    assert(kdGenMemOpsFindAllBytes(found_ptrs, 0, ptr, sizeof(ptr), 69) == 0);
    assert(kdGenMemOpsFindAllBytes(found_ptrs, sizeof(found_ptrs), ptr, 0, 69) == 0);

    printf("PASSED\n");
}


void
HandlesNullPointer(void)
{
    kd_byte_t  ptr[16];
    kd_byte_t *found_ptrs[8];

    printf(LOG_PREFIX_CSTR "HandlesNullPointer -> ");

    assert(kdGenMemOpsFindAllBytes(kd_null, 8, kd_null, 16, 69) == 0);
    assert(kdGenMemOpsFindAllBytes(kd_null, 8, ptr, 16, 69) == 0);
    assert(kdGenMemOpsFindAllBytes(found_ptrs, 8, kd_null, 16, 69) == 0);

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
