/**
 * @file kdMemAlgnGetHeadPtr.c
 * @author Kumarjit Das
 * @brief KD_MEM_ALGN library kdMemAlgnGetHeadPtr function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_mem_algn.h"


#define LIB_NAME_CSTR   "KD_MEM_ALGN"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdMemAlgnGetHeadPtr function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


static kd_u8_t ptr[1024];

void
ReturnsOriginalPointerFromOffsetPtr(void)
{
    printf(LOG_PREFIX_CSTR "ReturnsOriginalPointerFromOffsetPtr -> ");

    kd_u8_t *off;

    off = KD_PU8_C(kdMemAlgnGetOffsetPtr(ptr + 123, 4, 1));
    assert(kdMemAlgnGetHeadPtr(off, 1) == (ptr + 123));

    off = KD_PU8_C(kdMemAlgnGetOffsetPtr(ptr + 456, 4, 2));
    assert(kdMemAlgnGetHeadPtr(off, 2) == (ptr + 456));

    off = KD_PU8_C(kdMemAlgnGetOffsetPtr(ptr + 789, 8, 4));
    assert(kdMemAlgnGetHeadPtr(off, 4) == (ptr + 789));

    printf("PASSED\n");
}

void
InvalidInputsHandled(void)
{
    printf(LOG_PREFIX_CSTR "InvalidInputsHandled -> ");

    assert(kdMemAlgnGetHeadPtr(kd_null, 1) == kd_null);
    assert(kdMemAlgnGetHeadPtr(ptr + 123, 3) == kd_null);
    assert(kdMemAlgnGetHeadPtr(ptr + 234, 5) == kd_null);
    assert(kdMemAlgnGetHeadPtr(ptr + 456, 6) == kd_null);
    assert(kdMemAlgnGetHeadPtr(ptr + 678, 7) == kd_null);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");
    printf("Library Version: %s\n\n", KD_MEM_ALGN_VERSION_CSTR);

    ReturnsOriginalPointerFromOffsetPtr();
    InvalidInputsHandled();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
