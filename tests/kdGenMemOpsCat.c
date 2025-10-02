/**
 * @file kdGenMemOpsCat.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsCat function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsCat function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
ConcatenatesBothSources(void)
{
    kd_byte_t dst[16];
    kd_byte_t src1[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    kd_byte_t src2[8] = {9, 10, 11, 12, 13, 14, 15, 16};
    kd_byte_t res[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

    printf(LOG_PREFIX_CSTR "ConcatenatesBothSources -> ");

    assert(kdGenMemOpsCat(dst, sizeof(dst), src1, sizeof(src1), src2, sizeof(src2)) == KD_RESULT_SUCCESS);

    for (kd_usize_t i = 0; i < sizeof(dst); ++i)
    {
        assert(dst[i] == res[i]);
    }

    printf("PASSED\n");
}


void
HandlesNullPointers(void)
{
    kd_byte_t dst[16], src1[8], src2[8];

    printf(LOG_PREFIX_CSTR "HandlesNullPointers -> ");

    assert(kdGenMemOpsCat(kd_null, 0, kd_null, 0, kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, 0, kd_null, 0, kd_null, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, 0, kd_null, 0, src2, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, 0, kd_null, 0, src2, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, 0, kd_null, sizeof(src1), kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, 0, kd_null, sizeof(src1), kd_null, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, 0, kd_null, sizeof(src1), src2, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, 0, kd_null, sizeof(src1), src2, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, 0, src1, 0, kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, 0, src1, 0, kd_null, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, 0, src1, 0, src2, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, 0, src1, 0, src2, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, 0, src1, sizeof(src1), kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, 0, src1, sizeof(src1), kd_null, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, 0, src1, sizeof(src1), src2, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, 0, src1, sizeof(src1), src2, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, sizeof(dst), kd_null, 0, kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, sizeof(dst), kd_null, 0, kd_null, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, sizeof(dst), kd_null, 0, src2, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, sizeof(dst), kd_null, 0, src2, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, sizeof(dst), kd_null, sizeof(src1), kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, sizeof(dst), kd_null, sizeof(src1), kd_null, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, sizeof(dst), kd_null, sizeof(src1), src2, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, sizeof(dst), kd_null, sizeof(src1), src2, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, sizeof(dst), src1, 0, kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, sizeof(dst), src1, 0, kd_null, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, sizeof(dst), src1, 0, src2, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, sizeof(dst), src1, 0, src2, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, sizeof(dst), src1, sizeof(src1), kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, sizeof(dst), src1, sizeof(src1), kd_null, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, sizeof(dst), src1, sizeof(src1), src2, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(kd_null, sizeof(dst), src1, sizeof(src1), src2, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, 0, kd_null, 0, kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, 0, kd_null, 0, kd_null, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, 0, kd_null, 0, src2, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, 0, kd_null, 0, src2, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, 0, kd_null, sizeof(src1), kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, 0, kd_null, sizeof(src1), kd_null, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, 0, kd_null, sizeof(src1), src2, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, 0, kd_null, sizeof(src1), src2, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, 0, src1, 0, kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, 0, src1, 0, kd_null, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, 0, src1, 0, src2, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, 0, src1, 0, src2, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, 0, src1, sizeof(src1), kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, 0, src1, sizeof(src1), kd_null, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, 0, src1, sizeof(src1), src2, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, 0, src1, sizeof(src1), src2, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, sizeof(dst), kd_null, 0, kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, sizeof(dst), kd_null, 0, kd_null, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, sizeof(dst), kd_null, 0, src2, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, sizeof(dst), kd_null, 0, src2, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, sizeof(dst), kd_null, sizeof(src1), kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, sizeof(dst), kd_null, sizeof(src1), kd_null, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, sizeof(dst), kd_null, sizeof(src1), src2, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, sizeof(dst), kd_null, sizeof(src1), src2, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, sizeof(dst), src1, 0, kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, sizeof(dst), src1, 0, kd_null, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, sizeof(dst), src1, 0, src2, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, sizeof(dst), src1, 0, src2, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, sizeof(dst), src1, sizeof(src1), kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, sizeof(dst), src1, sizeof(src1), kd_null, sizeof(src2)) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsCat(dst, sizeof(dst), src1, sizeof(src1), src2, 0) == KD_RESULT_FAILURE);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");
    printf("Library Version: %s\n\n", KD_GEN_MEM_OPS_VERSION_CSTR);

    ConcatenatesBothSources();
    HandlesNullPointers();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
