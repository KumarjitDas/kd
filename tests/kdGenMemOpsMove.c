/**
 * @file kdGenMemOpsMove.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsMove function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsMove function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
MovesBytesCorrectly(void)
{
    kd_byte_t ptr1[] = {1, 2, 3, 4, 5};
    kd_byte_t ptr2[sizeof(ptr1)];

    printf(LOG_PREFIX_CSTR "MovesBytesCorrectly -> ");

    assert(kdGenMemOpsMove(ptr2, ptr1, sizeof(ptr1)) == KD_RESULT_SUCCESS);

    for (kd_usize_t i = 0; i < sizeof(ptr1); ++i)
    {
        assert(ptr1[i] == ptr2[i]);
    }

    printf("PASSED\n");
}


void
OverlappingRegionsHandledProperly(void)
{
    kd_byte_t  main_ptr[] = {69, 69, 1, 2, 3, 4, 5, 69, 69, 69, 69};
    kd_byte_t *ptr1       = main_ptr + 2;
    kd_byte_t *ptr2       = main_ptr + 4;
    kd_byte_t  res1[]     = {69, 69, 1, 2, 1, 2, 3, 4, 5, 69, 69};
    kd_byte_t  res2[]     = {69, 69, 1, 2, 3, 4, 5, 4, 5, 69, 69};

    printf(LOG_PREFIX_CSTR "OverlappingRegionsHandledProperly -> ");

    assert(kdGenMemOpsMove(ptr2, ptr1, 5) == KD_RESULT_SUCCESS);

    for (kd_usize_t i = 0; i < sizeof(main_ptr); ++i)
    {
        assert(main_ptr[i] == res1[i]);
    }

    ptr1 = main_ptr + 4;
    ptr2 = main_ptr + 2;

    assert(kdGenMemOpsMove(ptr2, ptr1, 5) == KD_RESULT_SUCCESS);

    for (kd_usize_t i = 0; i < sizeof(main_ptr); ++i)
    {
        assert(main_ptr[i] == res2[i]);
    }

    printf("PASSED\n");
}


void
HandlesZeroSize(void)
{
    kd_byte_t ptr[32];

    printf(LOG_PREFIX_CSTR "HandlesZeroSize -> ");

    assert(kdGenMemOpsMove(kd_null, kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsMove(kd_null, ptr, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsMove(ptr, kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsMove(ptr, ptr, 0) == KD_RESULT_FAILURE);

    printf("PASSED\n");
}


void
HandlesNullPointers(void)
{
    kd_byte_t ptr[32];

    printf(LOG_PREFIX_CSTR "HandlesNullPointers -> ");

    assert(kdGenMemOpsMove(kd_null, kd_null, 32) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsMove(kd_null, ptr, 32) == KD_RESULT_FAILURE);
    assert(kdGenMemOpsMove(ptr, kd_null, 32) == KD_RESULT_FAILURE);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");
    printf("Library Version: %s\n\n", KD_GEN_MEM_OPS_VERSION_CSTR);

    MovesBytesCorrectly();
    OverlappingRegionsHandledProperly();
    HandlesZeroSize();
    HandlesNullPointers();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
