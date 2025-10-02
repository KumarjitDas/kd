/**
 * @file kdGenMemOpsFindAllBlockIndicesU16.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindAllBlockIndicesU16 function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindAllBlockIndicesU16 function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
FindsAllOccurrences(void)
{
    kd_i32_t ptr[] = {1, 2, 3, 2, 5, 2, 7, 3, 9, 10};
    kd_u16_t idxs[8];
    kd_i32_t val1 = 2;
    kd_i32_t val2 = 3;

    printf(LOG_PREFIX_CSTR "FindsAllOccurrences -> ");

    assert(kdGenMemOpsFindAllBlockIndicesU16(idxs, sizeof(idxs), ptr, sizeof(ptr), &val1, sizeof(val1)) == 3);
    assert(idxs[0] == (1 * sizeof(val1)));
    assert(idxs[1] == (3 * sizeof(val1)));
    assert(idxs[2] == (5 * sizeof(val1)));
    assert(kdGenMemOpsFindAllBlockIndicesU16(idxs, sizeof(idxs), ptr, sizeof(ptr), &val2, sizeof(val2)) == 2);
    assert(idxs[0] == (2 * sizeof(val2)));
    assert(idxs[1] == (7 * sizeof(val2)));

    printf("PASSED\n");
}


void
ReturnsZeroIfNotFound(void)
{
    kd_i32_t ptr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    kd_u16_t idxs[8];
    kd_i32_t val1 = 0;
    kd_i32_t val2 = 11;

    printf(LOG_PREFIX_CSTR "ReturnsZeroIfNotFound -> ");

    assert(kdGenMemOpsFindAllBlockIndicesU16(idxs, sizeof(idxs), ptr, sizeof(ptr), &val1, sizeof(val1)) == 0);
    assert(kdGenMemOpsFindAllBlockIndicesU16(idxs, sizeof(idxs), ptr, sizeof(ptr), &val2, sizeof(val2)) == 0);

    printf("PASSED\n");
}


void
HandlesZeroSize(void)
{
    kd_i32_t ptr[16];
    kd_u16_t idxs[8];
    kd_i32_t val = 6969;

    printf(LOG_PREFIX_CSTR "HandlesZeroSize -> ");

    assert(kdGenMemOpsFindAllBlockIndicesU16(idxs, 0, ptr, 0, &val, 0) == 0);
    assert(kdGenMemOpsFindAllBlockIndicesU16(idxs, 0, ptr, 0, &val, sizeof(val)) == 0);
    assert(kdGenMemOpsFindAllBlockIndicesU16(idxs, 0, ptr, sizeof(ptr), &val, 0) == 0);
    assert(kdGenMemOpsFindAllBlockIndicesU16(idxs, 0, ptr, sizeof(ptr), &val, sizeof(val)) == 0);
    assert(kdGenMemOpsFindAllBlockIndicesU16(idxs, sizeof(idxs), ptr, 0, &val, 0) == 0);
    assert(kdGenMemOpsFindAllBlockIndicesU16(idxs, sizeof(idxs), ptr, 0, &val, sizeof(val)) == 0);
    assert(kdGenMemOpsFindAllBlockIndicesU16(idxs, sizeof(idxs), ptr, sizeof(ptr), &val, 0) == 0);

    printf("PASSED\n");
}


void
HandlesNullPointer(void)
{
    kd_i32_t ptr[16];
    kd_u16_t idxs[8];
    kd_i32_t val = 6969;

    printf(LOG_PREFIX_CSTR "HandlesNullPointer -> ");

    assert(kdGenMemOpsFindAllBlockIndicesU16((kd_u16_t *)kd_null, sizeof(idxs), kd_null, sizeof(ptr), kd_null, sizeof(val)) == 0);
    assert(kdGenMemOpsFindAllBlockIndicesU16((kd_u16_t *)kd_null, sizeof(idxs), kd_null, sizeof(ptr), &val, sizeof(val)) == 0);
    assert(kdGenMemOpsFindAllBlockIndicesU16((kd_u16_t *)kd_null, sizeof(idxs), ptr, sizeof(ptr), kd_null, sizeof(val)) == 0);
    assert(kdGenMemOpsFindAllBlockIndicesU16((kd_u16_t *)kd_null, sizeof(idxs), ptr, sizeof(ptr), &val, sizeof(val)) == 0);
    assert(kdGenMemOpsFindAllBlockIndicesU16(idxs, sizeof(idxs), kd_null, sizeof(ptr), kd_null, sizeof(val)) == 0);
    assert(kdGenMemOpsFindAllBlockIndicesU16(idxs, sizeof(idxs), kd_null, sizeof(ptr), &val, sizeof(val)) == 0);
    assert(kdGenMemOpsFindAllBlockIndicesU16(idxs, sizeof(idxs), ptr, sizeof(ptr), kd_null, sizeof(val)) == 0);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");
    printf("Library Version: %s\n\n", KD_GEN_MEM_OPS_VERSION_CSTR);

    FindsAllOccurrences();
    ReturnsZeroIfNotFound();
    HandlesZeroSize();
    HandlesNullPointer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
