/**
 * @file kdGenMemOpsCpy.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsCpy function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsCpy function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
CopiesBytesCorrectly(void)
{
    kd_byte_t ptr1[] = {1, 2, 3, 4, 5};
    kd_byte_t ptr2[sizeof(ptr1)];

    printf(LOG_PREFIX_CSTR "CopiesBytesCorrectly -> ");

    assert(kdGenMemOpsCpy(ptr2, ptr1, sizeof(ptr1)) == KD_RESULT_SUCCESS);

    for (kd_usize_t i = 0; i < sizeof(ptr1); ++i)
    {
        assert(ptr1[i] == ptr2[i]);
    }

    printf("PASSED\n");
}


void
HandlesZeroSize(void)
{
    kd_byte_t ptr[32];

    printf(LOG_PREFIX_CSTR "HandlesZeroSize -> ");

    assert(kdGenMemOpsCpy(kd_null, kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCpy(kd_null, ptr, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCpy(ptr, kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCpy(ptr, ptr, 0) == KD_RESULT_FAILURE);

    printf("PASSED\n");
}


void
HandlesNullPointers(void)
{
    kd_byte_t ptr[32];

    printf(LOG_PREFIX_CSTR "HandlesNullPointers -> ");

    assert(kdGenMemOpsCpy(kd_null, kd_null, 32) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCpy(kd_null, ptr, 32) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCpy(ptr, kd_null, 32) == KD_RESULT_FAILURE);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");
    printf("Library Version: %s\n\n", KD_GEN_MEM_OPS_VERSION_CSTR);

    CopiesBytesCorrectly();
    HandlesZeroSize();
    HandlesNullPointers();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
