/**
 * @file kdMemAlgnGetOffsetPtr.c
 * @author Kumarjit Das
 * @brief KD_MEM_ALGN library kdMemAlgnGetOffsetPtr function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_mem_algn.h"


#define LIB_NAME_CSTR   "KD_MEM_ALGN"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdMemAlgnGetOffsetPtr function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


static kd_u8_t ptr[1024];

void
AlignsAndStoresOffsetCorrectly(void)
{
    printf(LOG_PREFIX_CSTR "AlignsAndStoresOffsetCorrectly -> ");

    assert(KD_PU8_C(kdMemAlgnGetOffsetPtr(ptr + 123, 4, 1)) != kd_null);
    assert(KD_PU8_C(kdMemAlgnGetOffsetPtr(ptr + 345, 4, 4)) != kd_null);

    printf("PASSED\n");
}

void
InvalidInputsHandled(void)
{
    printf(LOG_PREFIX_CSTR "InvalidInputsHandled -> ");

    assert(kdMemAlgnGetOffsetPtr(ptr + 123, 4, 3) == kd_null);
    assert(kdMemAlgnGetOffsetPtr(ptr + 234, 4, 6) == kd_null);
    assert(kdMemAlgnGetOffsetPtr(ptr + 456, 8, 3) == kd_null);
    assert(kdMemAlgnGetOffsetPtr(ptr + 678, 5, 0) == kd_null);
    assert(kdMemAlgnGetOffsetPtr(ptr + 890, 11, 1) == kd_null);
    assert(kdMemAlgnGetOffsetPtr(ptr + 012, 23, 4) == kd_null);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");
    printf("Library Version: %s\n\n", KD_MEM_ALGN_VERSION_CSTR);

    AlignsAndStoresOffsetCorrectly();
    InvalidInputsHandled();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
