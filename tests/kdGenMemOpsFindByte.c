/**
 * @file kdGenMemOpsFindByte.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindByte function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindByte function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
FindsFirstOccurrence(void)
{
    kd_byte_t ptr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    printf(LOG_PREFIX_CSTR "FindsFirstOccurrence -> ");

    assert(kdGenMemOpsFindByte(ptr, sizeof(ptr), 3) == (ptr + 2));
    assert(kdGenMemOpsFindByte(ptr, sizeof(ptr), 8) == (ptr + 7));

    printf("PASSED\n");
}


void
ReturnsNullIfNotFound(void)
{
    kd_byte_t ptr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    printf(LOG_PREFIX_CSTR "ReturnsNullIfNotFound -> ");

    assert(kdGenMemOpsFindByte(ptr, sizeof(ptr), 0) == kd_null);
    assert(kdGenMemOpsFindByte(ptr, sizeof(ptr), 69) == kd_null);

    printf("PASSED\n");
}


void
HandlesZeroSize(void)
{
    kd_byte_t ptr[16];

    printf(LOG_PREFIX_CSTR "HandlesZeroSize -> ");

    assert(kdGenMemOpsFindByte(kd_null, 0, 69) == kd_null);
    assert(kdGenMemOpsFindByte(ptr, 0, 69) == kd_null);

    printf("PASSED\n");
}


void
HandlesNullPointer(void)
{
    printf(LOG_PREFIX_CSTR "HandlesNullPointer -> ");

    assert(kdGenMemOpsFindByte(kd_null, 16, 69) == kd_null);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");
    printf("Library Version: %s\n\n", KD_GEN_MEM_OPS_VERSION_CSTR);

    FindsFirstOccurrence();
    ReturnsNullIfNotFound();
    HandlesZeroSize();
    HandlesNullPointer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
