/**
 * @file kdGenMemOpsBytesCompSpn.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsBytesCompSpn function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsBytesCompSpn function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
FindsFirstMatch(void)
{
    char str[]   = "abcd456+-&*789efgh";
    char keys1[] = "1234567890";
    char keys2[] = "!@#$%^&*-+";

    printf(LOG_PREFIX_CSTR "FindsFirstMatch -> ");

    assert(kdGenMemOpsBytesCompSpn(str, sizeof(str) - 1, keys1, sizeof(keys1) - 1) == (str + 4));
    assert(kdGenMemOpsBytesCompSpn(str, sizeof(str) - 1, keys2, sizeof(keys2) - 1) == (str + 7));

    printf("PASSED\n");
}


void
ReturnsNullIfAllMismatch(void)
{
    char str[]  = "abcdefghijk";
    char keys[] = "1234567890";

    printf(LOG_PREFIX_CSTR "ReturnsNullIfAllMismatch -> ");

    assert(kdGenMemOpsBytesCompSpn(str, sizeof(str) - 1, keys, sizeof(keys) - 1) == kd_null);

    printf("PASSED\n");
}


void
HandlesNullPointers(void)
{
    kd_byte_t ptr[16], keys[8];

    printf(LOG_PREFIX_CSTR "HandlesNullPointers -> ");

    assert(kdGenMemOpsBytesCompSpn(kd_null, 0, kd_null, 0) == kd_null);
    assert(kdGenMemOpsBytesCompSpn(kd_null, 0, kd_null, sizeof(keys)) == kd_null);
    assert(kdGenMemOpsBytesCompSpn(kd_null, 0, keys, 0) == kd_null);
    assert(kdGenMemOpsBytesCompSpn(kd_null, 0, keys, sizeof(keys)) == kd_null);
    assert(kdGenMemOpsBytesCompSpn(kd_null, sizeof(ptr), kd_null, 0) == kd_null);
    assert(kdGenMemOpsBytesCompSpn(kd_null, sizeof(ptr), kd_null, sizeof(keys)) == kd_null);
    assert(kdGenMemOpsBytesCompSpn(kd_null, sizeof(ptr), keys, 0) == kd_null);
    assert(kdGenMemOpsBytesCompSpn(kd_null, sizeof(ptr), keys, sizeof(keys)) == kd_null);
    assert(kdGenMemOpsBytesCompSpn(ptr, 0, kd_null, 0) == kd_null);
    assert(kdGenMemOpsBytesCompSpn(ptr, 0, kd_null, sizeof(keys)) == kd_null);
    assert(kdGenMemOpsBytesCompSpn(ptr, 0, keys, 0) == kd_null);
    assert(kdGenMemOpsBytesCompSpn(ptr, 0, keys, sizeof(keys)) == kd_null);
    assert(kdGenMemOpsBytesCompSpn(ptr, sizeof(ptr), kd_null, 0) == kd_null);
    assert(kdGenMemOpsBytesCompSpn(ptr, sizeof(ptr), kd_null, sizeof(keys)) == kd_null);
    assert(kdGenMemOpsBytesCompSpn(ptr, sizeof(ptr), keys, 0) == kd_null);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");
    printf("Library Version: %s\n\n", KD_GEN_MEM_OPS_VERSION_CSTR);

    FindsFirstMatch();
    ReturnsNullIfAllMismatch();
    HandlesNullPointers();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
