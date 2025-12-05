/**
 * @file kdMemAlgnGetOffsetPtr.c
 * @author Kumarjit Das
 * @brief KD_MEM_ALGN library kdMemAlgnGetOffsetPtr function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../include/kd/mem_algn.h"


#define LIB_NAME_CSTR   "KD_MEM_ALGN"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdMemAlgnGetOffsetPtr function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


static u8 ptr[1024];

void
AlignsAndStoresOffsetCorrectly(void)
{
    printf(LOG_PREFIX_CSTR "AlignsAndStoresOffsetCorrectly -> ");

    assert(PU8_C(MemAlgnGetOffsetPtr(ptr + 123, 4, 1)) != null);
    assert(PU8_C(MemAlgnGetOffsetPtr(ptr + 345, 4, 4)) != null);

    printf("PASSED\n");
}

void
InvalidInputsHandled(void)
{
    printf(LOG_PREFIX_CSTR "InvalidInputsHandled -> ");

    assert(MemAlgnGetOffsetPtr(ptr + 123, 4, 3) == null);
    assert(MemAlgnGetOffsetPtr(ptr + 234, 4, 6) == null);
    assert(MemAlgnGetOffsetPtr(ptr + 456, 8, 3) == null);
    assert(MemAlgnGetOffsetPtr(ptr + 678, 5, 0) == null);
    assert(MemAlgnGetOffsetPtr(ptr + 890, 11, 1) == null);
    assert(MemAlgnGetOffsetPtr(ptr + 012, 23, 4) == null);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    AlignsAndStoresOffsetCorrectly();
    InvalidInputsHandled();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
