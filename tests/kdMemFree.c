/**
 * @file kdMemFree.c
 * @author Kumarjit Das
 * @brief KD_MEM library kdMemFree function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_mem.h"


#define LIB_NAME_CSTR   "KD_MEM"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdMemFree function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    kd_u8_t *ptr = KD_PU8_C(42069);

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    assert(kdMemFree(kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdMemFree(kd_null, 4200) == KD_RESULT_FAILURE);
    assert(kdMemFree(kd_null, 69) == KD_RESULT_FAILURE);

    assert(kdMemFree(&ptr, 0) == KD_RESULT_FAILURE);
    assert(ptr != kd_null);

    kdMemAlloc(&ptr, 6900);
    assert(kdMemFree(&ptr, 6900) == KD_RESULT_SUCCESS);
    assert(ptr == kd_null);

    printf("PASSED\n");
}


void
BasicDeallocationBytes(void)
{
    kd_u8_t *ptr;

    printf(LOG_PREFIX_CSTR "BasicDeallocationBytes -> ");

    kdMemAlloc(&ptr, 1);
    assert(kdMemFree(&ptr, 1) == KD_RESULT_SUCCESS);
    assert(ptr == kd_null);

    kdMemAlloc(&ptr, 64);
    assert(kdMemFree(&ptr, 64) == KD_RESULT_SUCCESS);
    assert(ptr == kd_null);

    kdMemAlloc(&ptr, 128);
    assert(kdMemFree(&ptr, 128) == KD_RESULT_SUCCESS);
    assert(ptr == kd_null);

    kdMemAlloc(&ptr, 256);
    assert(kdMemFree(&ptr, 256) == KD_RESULT_SUCCESS);
    assert(ptr == kd_null);

    kdMemAlloc(&ptr, 512);
    assert(kdMemFree(&ptr, 512) == KD_RESULT_SUCCESS);
    assert(ptr == kd_null);

    kdMemAlloc(&ptr, 1024);
    assert(kdMemFree(&ptr, 1024) == KD_RESULT_SUCCESS);
    assert(ptr == kd_null);

    printf("PASSED\n");
}


void
BasicDeallocationKiloBytes(void)
{
    kd_u8_t *ptr;

    printf(LOG_PREFIX_CSTR "BasicDeallocationKiloBytes -> ");

    kdMemAlloc(&ptr, 1024 * 1);
    assert(kdMemFree(&ptr, 1024 * 1) == KD_RESULT_SUCCESS);
    assert(ptr == kd_null);

    kdMemAlloc(&ptr, 1024 * 64);
    assert(kdMemFree(&ptr, 1024 * 64) == KD_RESULT_SUCCESS);
    assert(ptr == kd_null);

    kdMemAlloc(&ptr, 1024 * 128);
    assert(kdMemFree(&ptr, 1024 * 128) == KD_RESULT_SUCCESS);
    assert(ptr == kd_null);

    kdMemAlloc(&ptr, 1024 * 256);
    assert(kdMemFree(&ptr, 1024 * 256) == KD_RESULT_SUCCESS);
    assert(ptr == kd_null);

    kdMemAlloc(&ptr, 1024 * 512);
    assert(kdMemFree(&ptr, 1024 * 512) == KD_RESULT_SUCCESS);
    assert(ptr == kd_null);

    kdMemAlloc(&ptr, 1024 * 1024);
    assert(kdMemFree(&ptr, 1024 * 1024) == KD_RESULT_SUCCESS);
    assert(ptr == kd_null);

    printf("PASSED\n");
}


void
BasicDeallocationMegaBytes(void)
{
    kd_u8_t *ptr;

    printf(LOG_PREFIX_CSTR "BasicDeallocationMegaBytes -> ");

    kdMemAlloc(&ptr, 1024 * 1024 * 1);
    assert(kdMemFree(&ptr, 1024 * 1024 * 1) == KD_RESULT_SUCCESS);
    assert(ptr == kd_null);

    kdMemAlloc(&ptr, 1024 * 1024 * 64);
    assert(kdMemFree(&ptr, 1024 * 1024 * 64) == KD_RESULT_SUCCESS);
    assert(ptr == kd_null);

    kdMemAlloc(&ptr, 1024 * 1024 * 128);
    assert(kdMemFree(&ptr, 1024 * 1024 * 128) == KD_RESULT_SUCCESS);
    assert(ptr == kd_null);

    kdMemAlloc(&ptr, 1024 * 1024 * 256);
    assert(kdMemFree(&ptr, 1024 * 1024 * 256) == KD_RESULT_SUCCESS);
    assert(ptr == kd_null);

    kdMemAlloc(&ptr, 1024 * 1024 * 512);
    assert(kdMemFree(&ptr, 1024 * 1024 * 512) == KD_RESULT_SUCCESS);
    assert(ptr == kd_null);

    kdMemAlloc(&ptr, 1024 * 1024 * 1024);
    assert(kdMemFree(&ptr, 1024 * 1024 * 1024) == KD_RESULT_SUCCESS);
    assert(ptr == kd_null);

    printf("PASSED\n");
}


void
BasicMultipleSequentialDeallocationsBytes(void)
{
    kd_u8_t *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9, *ptr10, *ptr11;

    printf(LOG_PREFIX_CSTR "BasicMultipleSequentialDeallocationsBytes -> ");

    kdMemAlloc(&ptr1, 1);
    kdMemAlloc(&ptr2, 64);
    kdMemAlloc(&ptr3, 128);
    kdMemAlloc(&ptr4, 256);
    kdMemAlloc(&ptr5, 32);
    kdMemAlloc(&ptr6, 512);
    kdMemAlloc(&ptr7, 32);
    kdMemAlloc(&ptr8, 256);
    kdMemAlloc(&ptr9, 128);
    kdMemAlloc(&ptr10, 64);
    kdMemAlloc(&ptr11, 1);

    assert(kdMemFree(&ptr1, 1) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr2, 64) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr3, 128) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr4, 256) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr5, 32) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr6, 512) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr7, 32) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr8, 256) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr9, 128) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr10, 64) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr11, 1) == KD_RESULT_SUCCESS);

    assert(ptr1 == kd_null);
    assert(ptr2 == kd_null);
    assert(ptr3 == kd_null);
    assert(ptr4 == kd_null);
    assert(ptr5 == kd_null);
    assert(ptr6 == kd_null);
    assert(ptr7 == kd_null);
    assert(ptr8 == kd_null);
    assert(ptr9 == kd_null);
    assert(ptr10 == kd_null);
    assert(ptr11 == kd_null);

    printf("PASSED\n");
}


void
BasicMultipleSequentialDeallocationsKiloBytes(void)
{
    kd_u8_t *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9, *ptr10, *ptr11;

    printf(LOG_PREFIX_CSTR "BasicMultipleSequentialDeallocationsKiloBytes -> ");

    kdMemAlloc(&ptr1, 1024 * 1);
    kdMemAlloc(&ptr2, 1024 * 64);
    kdMemAlloc(&ptr3, 1024 * 128);
    kdMemAlloc(&ptr4, 1024 * 256);
    kdMemAlloc(&ptr5, 1024 * 32);
    kdMemAlloc(&ptr6, 1024 * 512);
    kdMemAlloc(&ptr7, 1024 * 32);
    kdMemAlloc(&ptr8, 1024 * 256);
    kdMemAlloc(&ptr9, 1024 * 128);
    kdMemAlloc(&ptr10, 1024 * 64);
    kdMemAlloc(&ptr11, 1024 * 1);

    assert(kdMemFree(&ptr1, 1024 * 1) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr2, 1024 * 64) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr3, 1024 * 128) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr4, 1024 * 256) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr5, 1024 * 32) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr6, 1024 * 512) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr7, 1024 * 32) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr8, 1024 * 256) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr9, 1024 * 128) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr10, 1024 * 64) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr11, 1024 * 1) == KD_RESULT_SUCCESS);

    assert(ptr1 == kd_null);
    assert(ptr2 == kd_null);
    assert(ptr3 == kd_null);
    assert(ptr4 == kd_null);
    assert(ptr5 == kd_null);
    assert(ptr6 == kd_null);
    assert(ptr7 == kd_null);
    assert(ptr8 == kd_null);
    assert(ptr9 == kd_null);
    assert(ptr10 == kd_null);
    assert(ptr11 == kd_null);

    printf("PASSED\n");
}


void
BasicMultipleSequentialDeallocationsMegaBytes(void)
{
    kd_u8_t *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9, *ptr10, *ptr11;

    printf(LOG_PREFIX_CSTR "BasicMultipleSequentialDeallocationsMegaBytes -> ");

    kdMemAlloc(&ptr1, 1024 * 1024 * 1);
    kdMemAlloc(&ptr2, 1024 * 1024 * 64);
    kdMemAlloc(&ptr3, 1024 * 1024 * 128);
    kdMemAlloc(&ptr4, 1024 * 1024 * 256);
    kdMemAlloc(&ptr5, 1024 * 1024 * 32);
    kdMemAlloc(&ptr6, 1024 * 1024 * 512);
    kdMemAlloc(&ptr7, 1024 * 1024 * 32);
    kdMemAlloc(&ptr8, 1024 * 1024 * 256);
    kdMemAlloc(&ptr9, 1024 * 1024 * 128);
    kdMemAlloc(&ptr10, 1024 * 1024 * 64);
    kdMemAlloc(&ptr11, 1024 * 1024 * 1);

    assert(kdMemFree(&ptr1, 1024 * 1024 * 1) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr2, 1024 * 1024 * 64) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr3, 1024 * 1024 * 128) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr4, 1024 * 1024 * 256) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr5, 1024 * 1024 * 32) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr6, 1024 * 1024 * 512) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr7, 1024 * 1024 * 32) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr8, 1024 * 1024 * 256) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr9, 1024 * 1024 * 128) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr10, 1024 * 1024 * 64) == KD_RESULT_SUCCESS);
    assert(kdMemFree(&ptr11, 1024 * 1024 * 1) == KD_RESULT_SUCCESS);

    assert(ptr1 == kd_null);
    assert(ptr2 == kd_null);
    assert(ptr3 == kd_null);
    assert(ptr4 == kd_null);
    assert(ptr5 == kd_null);
    assert(ptr6 == kd_null);
    assert(ptr7 == kd_null);
    assert(ptr8 == kd_null);
    assert(ptr9 == kd_null);
    assert(ptr10 == kd_null);
    assert(ptr11 == kd_null);

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

    BasicDeallocationBytes();
    BasicDeallocationKiloBytes();
    BasicDeallocationMegaBytes();

    BasicMultipleSequentialDeallocationsBytes();
    BasicMultipleSequentialDeallocationsKiloBytes();
    BasicMultipleSequentialDeallocationsMegaBytes();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
