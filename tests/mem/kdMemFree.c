/**
 * @file kdMemFree.c
 * @author Kumarjit Das
 * @brief KD_MEM library kdMemFree function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/mem.h"


#define LIB_NAME_CSTR   "KD_MEM"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdMemFree function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8 *ptr = PU8_C(42069);

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    assert(MemFree(null, 0) == RESULT_FAILURE);
    assert(MemFree(null, 4200) == RESULT_FAILURE);
    assert(MemFree(null, 69) == RESULT_FAILURE);

    assert(MemFree(&ptr, 0) == RESULT_FAILURE);
    assert(ptr != null);

    ptr = null;
    assert(MemAlloc(&ptr, 6900) == RESULT_SUCCESS);
    assert(ptr != null);
    assert(MemFree(&ptr, 6900) == RESULT_SUCCESS);
    assert(ptr == null);

    printf("PASSED\n");
}

void
FreeNullPointer(void)
{
    u8 *ptr = null;

    printf(LOG_PREFIX_CSTR "FreeNullPointer -> ");

    assert(MemFree(&ptr, 16) == RESULT_FAILURE);
    assert(ptr == null);

    printf("PASSED\n");
}

void
DoubleFree(void)
{
    u8 *ptr;

    printf(LOG_PREFIX_CSTR "DoubleFree -> ");

    assert(MemAlloc(&ptr, 128) == RESULT_SUCCESS);
    assert(ptr != null);

    assert(MemFree(&ptr, 128) == RESULT_SUCCESS);
    assert(ptr == null);

    assert(MemFree(&ptr, 128) == RESULT_FAILURE);
    assert(ptr == null);

    printf("PASSED\n");
}

void
BasicDeallocationBytes(void)
{
    u8 *ptr;

    printf(LOG_PREFIX_CSTR "BasicDeallocationBytes -> ");

    MemAlloc(&ptr, 1);
    assert(MemFree(&ptr, 1) == RESULT_SUCCESS);
    assert(ptr == null);

    MemAlloc(&ptr, 64);
    assert(MemFree(&ptr, 64) == RESULT_SUCCESS);
    assert(ptr == null);

    MemAlloc(&ptr, 128);
    assert(MemFree(&ptr, 128) == RESULT_SUCCESS);
    assert(ptr == null);

    MemAlloc(&ptr, 256);
    assert(MemFree(&ptr, 256) == RESULT_SUCCESS);
    assert(ptr == null);

    MemAlloc(&ptr, 512);
    assert(MemFree(&ptr, 512) == RESULT_SUCCESS);
    assert(ptr == null);

    MemAlloc(&ptr, 1024);
    assert(MemFree(&ptr, 1024) == RESULT_SUCCESS);
    assert(ptr == null);

    printf("PASSED\n");
}

void
BasicDeallocationKiloBytes(void)
{
    u8 *ptr;

    printf(LOG_PREFIX_CSTR "BasicDeallocationKiloBytes -> ");

    MemAlloc(&ptr, 1024 * 1);
    assert(MemFree(&ptr, 1024 * 1) == RESULT_SUCCESS);
    assert(ptr == null);

    MemAlloc(&ptr, 1024 * 16);
    assert(MemFree(&ptr, 1024 * 16) == RESULT_SUCCESS);
    assert(ptr == null);

    MemAlloc(&ptr, 1024 * 64);
    assert(MemFree(&ptr, 1024 * 64) == RESULT_SUCCESS);
    assert(ptr == null);

    MemAlloc(&ptr, 1024 * 128);
    assert(MemFree(&ptr, 1024 * 128) == RESULT_SUCCESS);
    assert(ptr == null);

    printf("PASSED\n");
}

void
BasicDeallocationMegaBytes(void)
{
    u8 *ptr;

    printf(LOG_PREFIX_CSTR "BasicDeallocationMegaBytes -> ");

    MemAlloc(&ptr, 1024 * 1024 * 1);
    assert(MemFree(&ptr, 1024 * 1024 * 1) == RESULT_SUCCESS);
    assert(ptr == null);

    MemAlloc(&ptr, 1024 * 1024 * 4);
    assert(MemFree(&ptr, 1024 * 1024 * 4) == RESULT_SUCCESS);
    assert(ptr == null);

    printf("PASSED\n");
}

void
BasicMultipleSequentialDeallocationsBytes(void)
{
    u8 *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9, *ptr10, *ptr11;

    printf(LOG_PREFIX_CSTR "BasicMultipleSequentialDeallocationsBytes -> ");

    MemAlloc(&ptr1, 1);
    MemAlloc(&ptr2, 64);
    MemAlloc(&ptr3, 128);
    MemAlloc(&ptr4, 256);
    MemAlloc(&ptr5, 32);
    MemAlloc(&ptr6, 512);
    MemAlloc(&ptr7, 32);
    MemAlloc(&ptr8, 256);
    MemAlloc(&ptr9, 128);
    MemAlloc(&ptr10, 64);
    MemAlloc(&ptr11, 1);

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

    assert(ptr1 == null);
    assert(ptr2 == null);
    assert(ptr3 == null);
    assert(ptr4 == null);
    assert(ptr5 == null);
    assert(ptr6 == null);
    assert(ptr7 == null);
    assert(ptr8 == null);
    assert(ptr9 == null);
    assert(ptr10 == null);
    assert(ptr11 == null);

    printf("PASSED\n");
}

void
BasicMultipleSequentialDeallocationsKiloBytes(void)
{
    u8 *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9, *ptr10, *ptr11;

    printf(LOG_PREFIX_CSTR "BasicMultipleSequentialDeallocationsKiloBytes -> ");

    MemAlloc(&ptr1, 1024 * 1);
    MemAlloc(&ptr2, 1024 * 8);
    MemAlloc(&ptr3, 1024 * 16);
    MemAlloc(&ptr4, 1024 * 32);
    MemAlloc(&ptr5, 1024 * 4);
    MemAlloc(&ptr6, 1024 * 64);
    MemAlloc(&ptr7, 1024 * 4);
    MemAlloc(&ptr8, 1024 * 32);
    MemAlloc(&ptr9, 1024 * 16);
    MemAlloc(&ptr10, 1024 * 8);
    MemAlloc(&ptr11, 1024 * 1);

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

    assert(ptr1 == null);
    assert(ptr2 == null);
    assert(ptr3 == null);
    assert(ptr4 == null);
    assert(ptr5 == null);
    assert(ptr6 == null);
    assert(ptr7 == null);
    assert(ptr8 == null);
    assert(ptr9 == null);
    assert(ptr10 == null);
    assert(ptr11 == null);

    printf("PASSED\n");
}

int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    FreeNullPointer();
    DoubleFree();

    BasicDeallocationBytes();
    BasicDeallocationKiloBytes();
    BasicDeallocationMegaBytes();

    BasicMultipleSequentialDeallocationsBytes();
    BasicMultipleSequentialDeallocationsKiloBytes();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
