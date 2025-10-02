/**
 * @file kdGenMemOpsBytesSpn.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsBytesSpn function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsBytesSpn function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
ReturnsFullSizeIfAllMatch(void)
{
    char str[]  = "69420";
    char keys[] = "1234567890";

    printf(LOG_PREFIX_CSTR "ReturnsFullSizeIfAllMatch -> ");

    assert(kdGenMemOpsBytesSpn(str, sizeof(str) - 1, keys, sizeof(keys) - 1) == (sizeof(str) - 1));

    printf("PASSED\n");
}


void
ReturnsCorrectPrefixLength(void)
{
    char str[]  = "129th";
    char keys[] = "1234567890";

    printf(LOG_PREFIX_CSTR "ReturnsCorrectPrefixLength -> ");

    assert(kdGenMemOpsBytesSpn(str, sizeof(str) - 1, keys, sizeof(keys) - 1) == 3);

    printf("PASSED\n");
}


void
ReturnsZeroIfPrefixNotFound(void)
{
    char str[]  = "abcdefghijk";
    char keys[] = "1234567890";

    printf(LOG_PREFIX_CSTR "ReturnsZeroIfPrefixNotFound -> ");

    assert(kdGenMemOpsBytesSpn(str, sizeof(str) - 1, keys, sizeof(keys) - 1) == 0);

    printf("PASSED\n");
}


void
HandlesEmptyOrNull(void)
{
    kd_byte_t ptr[16], keys[8];

    printf(LOG_PREFIX_CSTR "HandlesEmptyOrNull -> ");

    assert(kdGenMemOpsBytesSpn(kd_null, 0, kd_null, 0) == 0);
    assert(kdGenMemOpsBytesSpn(kd_null, 0, kd_null, sizeof(keys)) == 0);
    assert(kdGenMemOpsBytesSpn(kd_null, 0, keys, 0) == 0);
    assert(kdGenMemOpsBytesSpn(kd_null, 0, keys, sizeof(keys)) == 0);
    assert(kdGenMemOpsBytesSpn(kd_null, sizeof(ptr), kd_null, 0) == 0);
    assert(kdGenMemOpsBytesSpn(kd_null, sizeof(ptr), kd_null, sizeof(keys)) == 0);
    assert(kdGenMemOpsBytesSpn(kd_null, sizeof(ptr), keys, 0) == 0);
    assert(kdGenMemOpsBytesSpn(kd_null, sizeof(ptr), keys, sizeof(keys)) == 0);
    assert(kdGenMemOpsBytesSpn(ptr, 0, kd_null, 0) == 0);
    assert(kdGenMemOpsBytesSpn(ptr, 0, kd_null, sizeof(keys)) == 0);
    assert(kdGenMemOpsBytesSpn(ptr, 0, keys, 0) == 0);
    assert(kdGenMemOpsBytesSpn(ptr, 0, keys, sizeof(keys)) == 0);
    assert(kdGenMemOpsBytesSpn(ptr, sizeof(ptr), kd_null, 0) == 0);
    assert(kdGenMemOpsBytesSpn(ptr, sizeof(ptr), kd_null, sizeof(keys)) == 0);
    assert(kdGenMemOpsBytesSpn(ptr, sizeof(ptr), keys, 0) == 0);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");
    printf("Library Version: %s\n\n", KD_GEN_MEM_OPS_VERSION_CSTR);

    ReturnsFullSizeIfAllMatch();
    ReturnsCorrectPrefixLength();
    ReturnsZeroIfPrefixNotFound();
    HandlesEmptyOrNull();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
