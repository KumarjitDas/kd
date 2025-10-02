/**
 * @file kdGenMemOpsReverseBytes.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsReverseBytes function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsReverseBytes function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
ReversesAllBytesCorrectly(void)
{
    kd_byte_t ptr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    kd_byte_t res[] = {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    printf(LOG_PREFIX_CSTR "ReversesAllBytesCorrectly -> ");

    assert(kdGenMemOpsReverseBytes(ptr, sizeof(ptr)) == KD_RESULT_SUCCESS);

    for (kd_usize_t i = 0; i < sizeof(ptr); ++i)
    {
        assert(ptr[i] == res[i]);
    }

    printf("PASSED\n");
}


void
ZeroSizeReturnsFalse(void)
{
    kd_byte_t ptr[16];

    printf(LOG_PREFIX_CSTR "ZeroSizeReturnsFalse -> ");

    assert(kdGenMemOpsReverseBytes(kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsReverseBytes(ptr, 0) == KD_RESULT_FAILURE);

    printf("PASSED\n");
}


void
NullPointerReturnsFalse(void)
{
    printf(LOG_PREFIX_CSTR "NullPointerReturnsFalse -> ");

    assert(kdGenMemOpsReverseBytes(kd_null, 16) == KD_RESULT_FAILURE);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");
    printf("Library Version: %s\n\n", KD_GEN_MEM_OPS_VERSION_CSTR);

    ReversesAllBytesCorrectly();
    ZeroSizeReturnsFalse();
    NullPointerReturnsFalse();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
