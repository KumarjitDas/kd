/**
 * @file kdGenMemOpsSetBlocks.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsSetBlocks function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsSetBlocks function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
FillsMemoryWithBlockPattern(void)
{
    kd_i16_t arr[16];
    kd_i16_t val = 69;

    printf(LOG_PREFIX_CSTR "FillsMemoryWithBlockPattern -> ");

    assert(kdGenMemOpsSetBlocks(arr, sizeof(arr), &val, sizeof(val)) == KD_RESULT_SUCCESS);

    for (kd_usize_t i = 0; i < (sizeof(arr) / sizeof(*arr)); ++i)
    {
        assert(arr[i] == 69);
    }

    printf("PASSED\n");
}


void
ZeroSizeReturnsFalse(void)
{
    kd_byte_t ptr[16];

    printf(LOG_PREFIX_CSTR "ZeroSizeReturnsFalse -> ");

    assert(kdGenMemOpsSetBlocks(kd_null, 0, ptr, 8) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsSetBlocks(ptr, 0, ptr, 8) == KD_RESULT_FAILURE);

    printf("PASSED\n");
}


void
ZeroBlockSizeReturnsFalse(void)
{
    kd_byte_t ptr[16];

    printf(LOG_PREFIX_CSTR "ZeroBlockSizeReturnsFalse -> ");

    assert(kdGenMemOpsSetBlocks(ptr, sizeof(ptr), kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsSetBlocks(ptr, sizeof(ptr), ptr, 0) == KD_RESULT_FAILURE);

    printf("PASSED\n");
}


void
NullPointerReturnsFalse(void)
{
    kd_byte_t ptr[16];

    printf(LOG_PREFIX_CSTR "NullPointerReturnsFalse -> ");

    assert(kdGenMemOpsSetBlocks(kd_null, 16, kd_null, 8) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsSetBlocks(kd_null, 16, ptr, 8) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsSetBlocks(ptr, 16, kd_null, 8) == KD_RESULT_FAILURE);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");
    printf("Library Version: %s\n\n", KD_GEN_MEM_OPS_VERSION_CSTR);

    FillsMemoryWithBlockPattern();
    ZeroSizeReturnsFalse();
    ZeroBlockSizeReturnsFalse();
    NullPointerReturnsFalse();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
