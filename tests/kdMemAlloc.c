/**
 * @file kdMemAlloc.c
 * @author Kumarjit Das
 * @brief KD_MEM library kdMemAlloc function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_mem.h"


#define LIB_NAME_CSTR   "KD_MEM"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdMemAlloc function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    kd_u8_t *ptr;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    assert(kdMemAlloc(kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdMemAlloc(kd_null, 4200) == KD_RESULT_FAILURE);
    assert(kdMemAlloc(kd_null, 69) == KD_RESULT_FAILURE);

    assert(kdMemAlloc(&ptr, 0) == KD_RESULT_FAILURE);
    assert(ptr == kd_null);

    assert(kdMemAlloc(&ptr, 6900) == KD_RESULT_SUCCESS);
    assert(ptr != kd_null);

    printf("PASSED\n");
}


void
BasicAllocationBytes(void)
{
    kd_u8_t *ptr;

    printf(LOG_PREFIX_CSTR "BasicAllocationBytes -> ");

    assert(kdMemAlloc(&ptr, 1) == KD_RESULT_SUCCESS);
    assert(ptr != kd_null);

    assert(kdMemAlloc(&ptr, 64) == KD_RESULT_SUCCESS);
    assert(ptr != kd_null);

    assert(kdMemAlloc(&ptr, 128) == KD_RESULT_SUCCESS);
    assert(ptr != kd_null);

    assert(kdMemAlloc(&ptr, 256) == KD_RESULT_SUCCESS);
    assert(ptr != kd_null);

    assert(kdMemAlloc(&ptr, 512) == KD_RESULT_SUCCESS);
    assert(ptr != kd_null);

    assert(kdMemAlloc(&ptr, 1024) == KD_RESULT_SUCCESS);
    assert(ptr != kd_null);

    printf("PASSED\n");
}


void
BasicAllocationKiloBytes(void)
{
    kd_u8_t *ptr;

    printf(LOG_PREFIX_CSTR "BasicAllocationKiloBytes -> ");

    assert(kdMemAlloc(&ptr, 1024 * 1) == KD_RESULT_SUCCESS);
    assert(ptr != kd_null);

    assert(kdMemAlloc(&ptr, 1024 * 64) == KD_RESULT_SUCCESS);
    assert(ptr != kd_null);

    assert(kdMemAlloc(&ptr, 1024 * 128) == KD_RESULT_SUCCESS);
    assert(ptr != kd_null);

    assert(kdMemAlloc(&ptr, 1024 * 256) == KD_RESULT_SUCCESS);
    assert(ptr != kd_null);

    assert(kdMemAlloc(&ptr, 1024 * 512) == KD_RESULT_SUCCESS);
    assert(ptr != kd_null);

    assert(kdMemAlloc(&ptr, 1024 * 1024) == KD_RESULT_SUCCESS);
    assert(ptr != kd_null);

    printf("PASSED\n");
}


void
BasicAllocationMegaBytes(void)
{
    kd_u8_t *ptr;

    printf(LOG_PREFIX_CSTR "BasicAllocationMegaBytes -> ");

    assert(kdMemAlloc(&ptr, 1024 * 1024 * 1) == KD_RESULT_SUCCESS);
    assert(ptr != kd_null);

    assert(kdMemAlloc(&ptr, 1024 * 1024 * 64) == KD_RESULT_SUCCESS);
    assert(ptr != kd_null);

    assert(kdMemAlloc(&ptr, 1024 * 1024 * 128) == KD_RESULT_SUCCESS);
    assert(ptr != kd_null);

    assert(kdMemAlloc(&ptr, 1024 * 1024 * 256) == KD_RESULT_SUCCESS);
    assert(ptr != kd_null);

    assert(kdMemAlloc(&ptr, 1024 * 1024 * 512) == KD_RESULT_SUCCESS);
    assert(ptr != kd_null);

    assert(kdMemAlloc(&ptr, 1024 * 1024 * 1024) == KD_RESULT_SUCCESS);
    assert(ptr != kd_null);

    printf("PASSED\n");
}


void
BasicMultipleSequentialAllocationsBytes(void)
{
    kd_u8_t *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9, *ptr10, *ptr11;

    printf(LOG_PREFIX_CSTR "BasicMultipleSequentialAllocationsBytes -> ");

    assert(kdMemAlloc(&ptr1, 1) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr2, 64) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr3, 128) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr4, 256) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr5, 32) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr6, 512) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr7, 32) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr8, 256) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr9, 128) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr10, 64) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr11, 1) == KD_RESULT_SUCCESS);

    assert(ptr1 != kd_null);
    assert(ptr2 != kd_null);
    assert(ptr3 != kd_null);
    assert(ptr4 != kd_null);
    assert(ptr5 != kd_null);
    assert(ptr6 != kd_null);
    assert(ptr7 != kd_null);
    assert(ptr8 != kd_null);
    assert(ptr9 != kd_null);
    assert(ptr10 != kd_null);
    assert(ptr11 != kd_null);

    printf("PASSED\n");
}


void
BasicMultipleSequentialAllocationsKiloBytes(void)
{
    kd_u8_t *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9, *ptr10, *ptr11;

    printf(LOG_PREFIX_CSTR "BasicMultipleSequentialAllocationsKiloBytes -> ");

    assert(kdMemAlloc(&ptr1, 1024 * 1) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr2, 1024 * 64) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr3, 1024 * 128) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr4, 1024 * 256) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr5, 1024 * 32) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr6, 1024 * 512) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr7, 1024 * 32) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr8, 1024 * 256) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr9, 1024 * 128) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr10, 1024 * 64) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr11, 1024 * 1) == KD_RESULT_SUCCESS);

    assert(ptr1 != kd_null);
    assert(ptr2 != kd_null);
    assert(ptr3 != kd_null);
    assert(ptr4 != kd_null);
    assert(ptr5 != kd_null);
    assert(ptr6 != kd_null);
    assert(ptr7 != kd_null);
    assert(ptr8 != kd_null);
    assert(ptr9 != kd_null);
    assert(ptr10 != kd_null);
    assert(ptr11 != kd_null);

    printf("PASSED\n");
}


void
BasicMultipleSequentialAllocationsMegaBytes(void)
{
    kd_u8_t *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9, *ptr10, *ptr11;

    printf(LOG_PREFIX_CSTR "BasicMultipleSequentialAllocationsMegaBytes -> ");

    assert(kdMemAlloc(&ptr1, 1024 * 1024 * 1) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr2, 1024 * 1024 * 64) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr3, 1024 * 1024 * 128) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr4, 1024 * 1024 * 256) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr5, 1024 * 1024 * 32) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr6, 1024 * 1024 * 512) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr7, 1024 * 1024 * 32) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr8, 1024 * 1024 * 256) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr9, 1024 * 1024 * 128) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr10, 1024 * 1024 * 64) == KD_RESULT_SUCCESS);
    assert(kdMemAlloc(&ptr11, 1024 * 1024 * 1) == KD_RESULT_SUCCESS);

    assert(ptr1 != kd_null);
    assert(ptr2 != kd_null);
    assert(ptr3 != kd_null);
    assert(ptr4 != kd_null);
    assert(ptr5 != kd_null);
    assert(ptr6 != kd_null);
    assert(ptr7 != kd_null);
    assert(ptr8 != kd_null);
    assert(ptr9 != kd_null);
    assert(ptr10 != kd_null);
    assert(ptr11 != kd_null);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");
    printf("Library Version: %s\n\n", KD_MEM_VERSION_CSTR);

    BasicArguments();

    BasicAllocationBytes();
    BasicAllocationKiloBytes();
    BasicAllocationMegaBytes();

    BasicMultipleSequentialAllocationsBytes();
    BasicMultipleSequentialAllocationsKiloBytes();
    BasicMultipleSequentialAllocationsMegaBytes();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
