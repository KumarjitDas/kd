/**
 * @file kdGenMemOpsSetBytes.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsSetBytes function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsSetBytes function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
SetsAllBytesCorrectly(void)
{
    kd_byte_t ptr[16];

    printf(LOG_PREFIX_CSTR "SetsAllBytesCorrectly -> ");

    assert(kdGenMemOpsSetBytes(ptr, sizeof(ptr), 69) == KD_RESULT_SUCCESS);

    for (kd_usize_t i = 0; i < sizeof(ptr); ++i)
    {
        assert(ptr[i] == KD_BYTE_C(69));
    }

    printf("PASSED\n");
}


void
ZeroSizeReturnsFalse(void)
{
    kd_byte_t ptr[16];

    printf(LOG_PREFIX_CSTR "ZeroSizeReturnsFalse -> ");

    assert(kdGenMemOpsSetBytes(kd_null, 0, 69) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsSetBytes(ptr, 0, 69) == KD_RESULT_FAILURE);

    printf("PASSED\n");
}


void
NullPointerReturnsFalse(void)
{
    printf(LOG_PREFIX_CSTR "NullPointerReturnsFalse -> ");

    assert(kdGenMemOpsSetBytes(kd_null, 16, 69) == KD_RESULT_FAILURE);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");
    printf("Library Version: %s\n\n", KD_GEN_MEM_OPS_VERSION_CSTR);

    SetsAllBytesCorrectly();
    ZeroSizeReturnsFalse();
    NullPointerReturnsFalse();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
