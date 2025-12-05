/**
 * @file kdMemAlgnGetHeadPtr.c
 * @author Kumarjit Das
 * @brief KD_MEM_ALGN library kdMemAlgnGetHeadPtr function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../include/kd/mem_algn.h"


#define LIB_NAME_CSTR   "KD_MEM_ALGN"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdMemAlgnGetHeadPtr function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


static u8 ptr[1024];

void
ReturnsOriginalPointerFromOffsetPtr(void)
{
    printf(LOG_PREFIX_CSTR "ReturnsOriginalPointerFromOffsetPtr -> ");

    u8 *off;

    off = KD_PU8_C(MemAlgnGetOffsetPtr(ptr + 123, 4, 1));
    assert(MemAlgnGetHeadPtr(off, 1) == (ptr + 123));

    off = KD_PU8_C(MemAlgnGetOffsetPtr(ptr + 456, 4, 2));
    assert(MemAlgnGetHeadPtr(off, 2) == (ptr + 456));

    off = KD_PU8_C(MemAlgnGetOffsetPtr(ptr + 789, 8, 4));
    assert(MemAlgnGetHeadPtr(off, 4) == (ptr + 789));

    printf("PASSED\n");
}

void
InvalidInputsHandled(void)
{
    printf(LOG_PREFIX_CSTR "InvalidInputsHandled -> ");

    assert(MemAlgnGetHeadPtr(null, 1) == null);
    assert(MemAlgnGetHeadPtr(ptr + 123, 3) == null);
    assert(MemAlgnGetHeadPtr(ptr + 234, 5) == null);
    assert(MemAlgnGetHeadPtr(ptr + 456, 6) == null);
    assert(MemAlgnGetHeadPtr(ptr + 678, 7) == null);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    ReturnsOriginalPointerFromOffsetPtr();
    InvalidInputsHandled();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
