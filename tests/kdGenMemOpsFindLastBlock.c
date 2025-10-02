/**
 * @file kdGenMemOpsFindLastBlock.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindLastBlock function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindLastBlock function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
FindsFirstMatchingBlock(void)
{
    kd_i16_t arr[] = {1, 2, 3, 8, 5, 6, 3, 8, 9, 10};
    kd_i16_t val1  = 3;
    kd_i16_t val2  = 8;

    printf(LOG_PREFIX_CSTR "FindsFirstMatchingBlock -> ");

    assert(kdGenMemOpsFindLastBlock(arr, sizeof(arr), &val1, sizeof(val1)) == (arr + 6));
    assert(kdGenMemOpsFindLastBlock(arr, sizeof(arr), &val2, sizeof(val2)) == (arr + 7));

    printf("PASSED\n");
}


void
ReturnsNullIfNoMatch(void)
{
    kd_i16_t arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    kd_i16_t val1  = 0;
    kd_i16_t val2  = 11;

    printf(LOG_PREFIX_CSTR "ReturnsNullIfNoMatch -> ");

    assert(kdGenMemOpsFindLastBlock(arr, sizeof(arr), &val1, sizeof(val1)) == kd_null);
    assert(kdGenMemOpsFindLastBlock(arr, sizeof(arr), &val2, sizeof(val2)) == kd_null);

    printf("PASSED\n");
}


void
ZeroBlockSizeReturnsNull(void)
{
    kd_i16_t  val;
    kd_byte_t ptr[16];

    printf(LOG_PREFIX_CSTR "ZeroBlockSizeReturnsNull -> ");

    assert(kdGenMemOpsFindLastBlock(kd_null, 0, kd_null, 0) == kd_null);
    assert(kdGenMemOpsFindLastBlock(kd_null, 0, kd_null, sizeof(val)) == kd_null);
    assert(kdGenMemOpsFindLastBlock(kd_null, sizeof(ptr), kd_null, 0) == kd_null);
    assert(kdGenMemOpsFindLastBlock(kd_null, 0, &val, 0) == kd_null);
    assert(kdGenMemOpsFindLastBlock(kd_null, 0, &val, sizeof(val)) == kd_null);
    assert(kdGenMemOpsFindLastBlock(kd_null, sizeof(ptr), &val, 0) == kd_null);
    assert(kdGenMemOpsFindLastBlock(ptr, 0, kd_null, 0) == kd_null);
    assert(kdGenMemOpsFindLastBlock(ptr, 0, kd_null, sizeof(val)) == kd_null);
    assert(kdGenMemOpsFindLastBlock(ptr, sizeof(ptr), kd_null, 0) == kd_null);
    assert(kdGenMemOpsFindLastBlock(ptr, 0, &val, 0) == kd_null);
    assert(kdGenMemOpsFindLastBlock(ptr, 0, &val, sizeof(val)) == kd_null);
    assert(kdGenMemOpsFindLastBlock(ptr, sizeof(ptr), &val, 0) == kd_null);

    printf("PASSED\n");
}


void
HandlesNullPointer(void)
{
    kd_i16_t  val;
    kd_byte_t ptr[16];

    printf(LOG_PREFIX_CSTR "HandlesNullPointer -> ");

    assert(kdGenMemOpsFindLastBlock(kd_null, sizeof(ptr), kd_null, sizeof(val)) == kd_null);
    assert(kdGenMemOpsFindLastBlock(kd_null, sizeof(ptr), &val, sizeof(val)) == kd_null);
    assert(kdGenMemOpsFindLastBlock(ptr, sizeof(ptr), kd_null, sizeof(val)) == kd_null);

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
    ReturnsNullIfNoMatch();
    ZeroBlockSizeReturnsNull();
    HandlesNullPointer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
