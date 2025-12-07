/**
 * @file kdMemAlloc.c
 * @author Kumarjit Das
 * @brief KD_MEM library kdMemAlloc function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/mem.h"


#define LIB_NAME_CSTR   "KD_MEM"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdMemAlloc function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8 *ptr;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    assert(MemAlloc(null, 0) == RESULT_FAILURE);
    assert(MemAlloc(null, 4200) == RESULT_FAILURE);
    assert(MemAlloc(null, 69) == RESULT_FAILURE);

    ptr = PU8_C(0xAA);
    assert(MemAlloc(&ptr, 0) == RESULT_FAILURE);
    assert(ptr == null);

    ptr = null;
    assert(MemAlloc(&ptr, 6900) == RESULT_SUCCESS);
    assert(ptr != null);
    assert(MemFree(&ptr, 6900) == RESULT_SUCCESS);
    assert(ptr == null);

    printf("PASSED\n");
}

void
BasicAllocationBytes(void)
{
    u8 *ptr;

    printf(LOG_PREFIX_CSTR "BasicAllocationBytes -> ");

    ptr = null;
    assert(MemAlloc(&ptr, 1) == RESULT_SUCCESS);
    assert(ptr != null);
    assert(MemFree(&ptr, 1) == RESULT_SUCCESS);
    assert(ptr == null);

    assert(MemAlloc(&ptr, 64) == RESULT_SUCCESS);
    assert(ptr != null);
    assert(MemFree(&ptr, 64) == RESULT_SUCCESS);
    assert(ptr == null);

    assert(MemAlloc(&ptr, 128) == RESULT_SUCCESS);
    assert(ptr != null);
    assert(MemFree(&ptr, 128) == RESULT_SUCCESS);
    assert(ptr == null);

    assert(MemAlloc(&ptr, 256) == RESULT_SUCCESS);
    assert(ptr != null);
    assert(MemFree(&ptr, 256) == RESULT_SUCCESS);
    assert(ptr == null);

    assert(MemAlloc(&ptr, 512) == RESULT_SUCCESS);
    assert(ptr != null);
    assert(MemFree(&ptr, 512) == RESULT_SUCCESS);
    assert(ptr == null);

    assert(MemAlloc(&ptr, 1024) == RESULT_SUCCESS);
    assert(ptr != null);
    assert(MemFree(&ptr, 1024) == RESULT_SUCCESS);
    assert(ptr == null);

    printf("PASSED\n");
}

void
BasicAllocationKiloBytes(void)
{
    u8 *ptr;

    printf(LOG_PREFIX_CSTR "BasicAllocationKiloBytes -> ");

    assert(MemAlloc(&ptr, 1024 * 1) == RESULT_SUCCESS);
    assert(ptr != null);
    assert(MemFree(&ptr, 1024 * 1) == RESULT_SUCCESS);
    assert(ptr == null);

    assert(MemAlloc(&ptr, 1024 * 16) == RESULT_SUCCESS);
    assert(ptr != null);
    assert(MemFree(&ptr, 1024 * 16) == RESULT_SUCCESS);
    assert(ptr == null);

    assert(MemAlloc(&ptr, 1024 * 64) == RESULT_SUCCESS);
    assert(ptr != null);
    assert(MemFree(&ptr, 1024 * 64) == RESULT_SUCCESS);
    assert(ptr == null);

    assert(MemAlloc(&ptr, 1024 * 128) == RESULT_SUCCESS);
    assert(ptr != null);
    assert(MemFree(&ptr, 1024 * 128) == RESULT_SUCCESS);
    assert(ptr == null);

    printf("PASSED\n");
}

void
BasicAllocationMegaBytes(void)
{
    u8 *ptr;

    printf(LOG_PREFIX_CSTR "BasicAllocationMegaBytes -> ");

    assert(MemAlloc(&ptr, 1024 * 1024 * 1) == RESULT_SUCCESS);
    assert(ptr != null);
    assert(MemFree(&ptr, 1024 * 1024 * 1) == RESULT_SUCCESS);
    assert(ptr == null);

    assert(MemAlloc(&ptr, 1024 * 1024 * 4) == RESULT_SUCCESS);
    assert(ptr != null);
    assert(MemFree(&ptr, 1024 * 1024 * 4) == RESULT_SUCCESS);
    assert(ptr == null);

    assert(MemAlloc(&ptr, 1024 * 1024 * 16) == RESULT_SUCCESS);
    assert(ptr != null);
    assert(MemFree(&ptr, 1024 * 1024 * 16) == RESULT_SUCCESS);
    assert(ptr == null);

    printf("PASSED\n");
}

void
BasicMultipleSequentialAllocationsBytes(void)
{
    u8 *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9, *ptr10, *ptr11;

    printf(LOG_PREFIX_CSTR "BasicMultipleSequentialAllocationsBytes -> ");

    assert(MemAlloc(&ptr1, 1) == RESULT_SUCCESS);
    assert(MemAlloc(&ptr2, 64) == RESULT_SUCCESS);
    assert(MemAlloc(&ptr3, 128) == RESULT_SUCCESS);
    assert(MemAlloc(&ptr4, 256) == RESULT_SUCCESS);
    assert(MemAlloc(&ptr5, 32) == RESULT_SUCCESS);
    assert(MemAlloc(&ptr6, 512) == RESULT_SUCCESS);
    assert(MemAlloc(&ptr7, 32) == RESULT_SUCCESS);
    assert(MemAlloc(&ptr8, 256) == RESULT_SUCCESS);
    assert(MemAlloc(&ptr9, 128) == RESULT_SUCCESS);
    assert(MemAlloc(&ptr10, 64) == RESULT_SUCCESS);
    assert(MemAlloc(&ptr11, 1) == RESULT_SUCCESS);

    assert(ptr1 != null);
    assert(ptr2 != null);
    assert(ptr3 != null);
    assert(ptr4 != null);
    assert(ptr5 != null);
    assert(ptr6 != null);
    assert(ptr7 != null);
    assert(ptr8 != null);
    assert(ptr9 != null);
    assert(ptr10 != null);
    assert(ptr11 != null);

    assert(MemFree(&ptr1, 1) == RESULT_SUCCESS);
    assert(MemFree(&ptr2, 64) == RESULT_SUCCESS);
    assert(MemFree(&ptr3, 128) == RESULT_SUCCESS);
    assert(MemFree(&ptr4, 256) == RESULT_SUCCESS);
    assert(MemFree(&ptr5, 32) == RESULT_SUCCESS);
    assert(MemFree(&ptr6, 512) == RESULT_SUCCESS);
    assert(MemFree(&ptr7, 32) == RESULT_SUCCESS);
    assert(MemFree(&ptr8, 256) == RESULT_SUCCESS);
    assert(MemFree(&ptr9, 128) == RESULT_SUCCESS);
    assert(MemFree(&ptr10, 64) == RESULT_SUCCESS);
    assert(MemFree(&ptr11, 1) == RESULT_SUCCESS);

    printf("PASSED\n");
}

void
BasicMultipleSequentialAllocationsKiloBytes(void)
{
    u8 *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9, *ptr10, *ptr11;

    printf(LOG_PREFIX_CSTR "BasicMultipleSequentialAllocationsKiloBytes -> ");

    assert(MemAlloc(&ptr1, 1024 * 1) == RESULT_SUCCESS);
    assert(MemAlloc(&ptr2, 1024 * 8) == RESULT_SUCCESS);
    assert(MemAlloc(&ptr3, 1024 * 16) == RESULT_SUCCESS);
    assert(MemAlloc(&ptr4, 1024 * 32) == RESULT_SUCCESS);
    assert(MemAlloc(&ptr5, 1024 * 4) == RESULT_SUCCESS);
    assert(MemAlloc(&ptr6, 1024 * 64) == RESULT_SUCCESS);
    assert(MemAlloc(&ptr7, 1024 * 4) == RESULT_SUCCESS);
    assert(MemAlloc(&ptr8, 1024 * 32) == RESULT_SUCCESS);
    assert(MemAlloc(&ptr9, 1024 * 16) == RESULT_SUCCESS);
    assert(MemAlloc(&ptr10, 1024 * 8) == RESULT_SUCCESS);
    assert(MemAlloc(&ptr11, 1024 * 1) == RESULT_SUCCESS);

    assert(ptr1 != null);
    assert(ptr2 != null);
    assert(ptr3 != null);
    assert(ptr4 != null);
    assert(ptr5 != null);
    assert(ptr6 != null);
    assert(ptr7 != null);
    assert(ptr8 != null);
    assert(ptr9 != null);
    assert(ptr10 != null);
    assert(ptr11 != null);

    assert(MemFree(&ptr1, 1024 * 1) == RESULT_SUCCESS);
    assert(MemFree(&ptr2, 1024 * 8) == RESULT_SUCCESS);
    assert(MemFree(&ptr3, 1024 * 16) == RESULT_SUCCESS);
    assert(MemFree(&ptr4, 1024 * 32) == RESULT_SUCCESS);
    assert(MemFree(&ptr5, 1024 * 4) == RESULT_SUCCESS);
    assert(MemFree(&ptr6, 1024 * 64) == RESULT_SUCCESS);
    assert(MemFree(&ptr7, 1024 * 4) == RESULT_SUCCESS);
    assert(MemFree(&ptr8, 1024 * 32) == RESULT_SUCCESS);
    assert(MemFree(&ptr9, 1024 * 16) == RESULT_SUCCESS);
    assert(MemFree(&ptr10, 1024 * 8) == RESULT_SUCCESS);
    assert(MemFree(&ptr11, 1024 * 1) == RESULT_SUCCESS);

    printf("PASSED\n");
}

void
AllocationWriteReadSanity(void)
{
    u8   *ptr;
    usize i;
    usize sz = 256;

    printf(LOG_PREFIX_CSTR "AllocationWriteReadSanity -> ");

    assert(MemAlloc(&ptr, sz) == RESULT_SUCCESS);
    assert(ptr != null);

    for (i = 0; i < sz; ++i)
    {
        ptr[i] = (u8)(i & 0xFF);
    }

    for (i = 0; i < sz; ++i)
    {
        assert(ptr[i] == (u8)(i & 0xFF));
    }

    assert(MemFree(&ptr, sz) == RESULT_SUCCESS);
    assert(ptr == null);

    printf("PASSED\n");
}

int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();

    BasicAllocationBytes();
    BasicAllocationKiloBytes();
    BasicAllocationMegaBytes();

    BasicMultipleSequentialAllocationsBytes();
    BasicMultipleSequentialAllocationsKiloBytes();

    AllocationWriteReadSanity();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
