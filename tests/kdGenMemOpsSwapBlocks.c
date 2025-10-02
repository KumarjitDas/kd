/**
 * @file kdGenMemOpsSwapBlocks.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsSwapBlocks function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsSwapBlocks function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
SwapBlocksCorrectly(void)
{
    kd_i32_t ptr[] = {1, 2, 6, 4, 5, 3, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    kd_i32_t res[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

    printf(LOG_PREFIX_CSTR "SwapBlocksCorrectly -> ");

    assert(kdGenMemOpsSwapBlocks(ptr, sizeof(ptr), KD_SZ_I32, 2 * KD_SZ_I32, 5 * KD_SZ_I32) == KD_RESULT_SUCCESS);

    for (kd_usize_t i = 0; i < (sizeof(ptr) / KD_SZ_I32); ++i)
    {
        assert(ptr[i] == res[i]);
    }

    printf("PASSED\n");
}


void
ZeroSizeReturnsFalse(void)
{
    printf(LOG_PREFIX_CSTR "ZeroSizeReturnsFalse -> ");

    kd_i32_t ptr[16];

    assert(kdGenMemOpsSwapBlocks(kd_null, 0, 0, 2, 5) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsSwapBlocks(kd_null, 0, KD_SZ_I32, 2 * KD_SZ_I32, 5 * KD_SZ_I32) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsSwapBlocks(kd_null, sizeof(ptr), 0, 2 * KD_SZ_I32, 5 * KD_SZ_I32) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsSwapBlocks(ptr, 0, 0, 2, 5) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsSwapBlocks(ptr, 0, KD_SZ_I32, 2 * KD_SZ_I32, 5 * KD_SZ_I32) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsSwapBlocks(ptr, sizeof(ptr), 0, 2 * KD_SZ_I32, 5 * KD_SZ_I32) == KD_RESULT_FAILURE);

    printf("PASSED\n");
}


void
NullPointerReturnsFalse(void)
{
    printf(LOG_PREFIX_CSTR "NullPointerReturnsFalse -> ");

    assert(kdGenMemOpsSwapBlocks(kd_null, 16, 4, 2, 5) == KD_RESULT_FAILURE);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");
    printf("Library Version: %s\n\n", KD_GEN_MEM_OPS_VERSION_CSTR);

    SwapBlocksCorrectly();
    ZeroSizeReturnsFalse();
    NullPointerReturnsFalse();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
