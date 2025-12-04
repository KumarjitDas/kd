/**
 * @file kdMemOpsSwapN.c
 * @author Kumarjit Das
 * @brief KD_MEM_OPS library kdMemOpsSwapN function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_mem_ops.h"


#define LIB_NAME_CSTR   "KD_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdMemOpsSwapN function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
SwapBlocksCorrectly(void)
{
    kd_i32_t   ptr[] = {1, 2, 6, 4, 5, 3, 7, 8, 9, 10};
    kd_i32_t   res[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    kd_usize_t len   = sizeof(ptr) / KD_SZ_I32;

    printf(LOG_PREFIX_CSTR "SwapBlocksCorrectly -> ");

    assert(kdMemOpsSwapI32(ptr, len, 2, 5) == KD_RESULT_SUCCESS);

    for (kd_usize_t i = 0; i < (sizeof(ptr) / KD_SZ_I32); ++i)
    {
        assert(ptr[i] == res[i]);
    }

    printf("PASSED\n");
}


void
ZeroSizeReturnsFalse(void)
{
    kd_i32_t ptr[16];

    printf(LOG_PREFIX_CSTR "ZeroSizeReturnsFalse -> ");

    assert(kdMemOpsSwapI16(kd_null, 0, 2, 5) == KD_RESULT_FAILURE);
    assert(kdMemOpsSwapI16(kd_null, KD_SZ_I32, 2 * KD_SZ_I32, 5 * KD_SZ_I32) == KD_RESULT_FAILURE);
    assert(kdMemOpsSwapI16(kd_null, 0, 2 * KD_SZ_I32, 5 * KD_SZ_I32) == KD_RESULT_FAILURE);
    assert(kdMemOpsSwapI32(ptr, 0, 2, 5) == KD_RESULT_FAILURE);
    assert(kdMemOpsSwapI32(ptr, KD_SZ_I32, 2 * KD_SZ_I32, 5 * KD_SZ_I32) == KD_RESULT_FAILURE);
    assert(kdMemOpsSwapI32(ptr, 0, 2 * KD_SZ_I32, 5 * KD_SZ_I32) == KD_RESULT_FAILURE);

    printf("PASSED\n");
}


void
NullPointerReturnsFalse(void)
{
    printf(LOG_PREFIX_CSTR "NullPointerReturnsFalse -> ");

    assert(kdMemOpsSwapI16(kd_null, 4, 2, 5) == KD_RESULT_FAILURE);
    assert(kdMemOpsSwapI32(kd_null, 4, 2, 5) == KD_RESULT_FAILURE);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");
    printf("Library Version: %s\n\n", KD_MEM_OPS_VERSION_CSTR);

    SwapBlocksCorrectly();
    ZeroSizeReturnsFalse();
    NullPointerReturnsFalse();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
