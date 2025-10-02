/**
 * @file kdGenMemOpsFindLastByte.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindLastByte function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindLastByte function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
FindsLastOccurrence(void)
{
    kd_byte_t ptr[] = {1, 2, 3, 8, 5, 6, 3, 8, 9, 10};

    printf(LOG_PREFIX_CSTR "FindsLastOccurrence -> ");

    assert(kdGenMemOpsFindLastByte(ptr, sizeof(ptr), 3) == (ptr + 6));
    assert(kdGenMemOpsFindLastByte(ptr, sizeof(ptr), 8) == (ptr + 7));

    printf("PASSED\n");
}


void
ReturnsNullIfNotFound(void)
{
    kd_byte_t ptr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    printf(LOG_PREFIX_CSTR "ReturnsNullIfNotFound -> ");

    assert(kdGenMemOpsFindLastByte(ptr, sizeof(ptr), 0) == kd_null);
    assert(kdGenMemOpsFindLastByte(ptr, sizeof(ptr), 69) == kd_null);

    printf("PASSED\n");
}


void
HandlesZeroSize(void)
{
    kd_byte_t ptr[16];

    printf(LOG_PREFIX_CSTR "HandlesZeroSize -> ");

    assert(kdGenMemOpsFindLastByte(kd_null, 0, 69) == kd_null);
    assert(kdGenMemOpsFindLastByte(ptr, 0, 69) == kd_null);

    printf("PASSED\n");
}


void
HandlesNullPointer(void)
{
    printf(LOG_PREFIX_CSTR "HandlesNullPointer -> ");

    assert(kdGenMemOpsFindLastByte(kd_null, 16, 69) == kd_null);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");
    printf("Library Version: %s\n\n", KD_GEN_MEM_OPS_VERSION_CSTR);

    FindsLastOccurrence();
    ReturnsNullIfNotFound();
    HandlesZeroSize();
    HandlesNullPointer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
