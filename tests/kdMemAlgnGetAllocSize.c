/**
 * @file kdMemAlgnGetAllocSize.c
 * @author Kumarjit Das
 * @brief KD_MEM_ALGN library kdMemAlgnGetAllocSize function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../include/kd/mem_algn.h"


#define LIB_NAME_CSTR   "KD_MEM_ALGN"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdMemAlgnGetAllocSize function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
ValidPowerOfTwoAlignmentAndOffset(void)
{
    printf(LOG_PREFIX_CSTR "ValidPowerOfTwoAlignmentAndOffset -> ");

    assert(MemAlgnGetAllocSize(1, 1, 1) == 3);
    assert(MemAlgnGetAllocSize(16, 4, 8) == 28);
    assert(MemAlgnGetAllocSize(16, 8, 4) == 28);

    printf("PASSED\n");
}

void
ZeroOffsetIsHandledCorrectly(void)
{
    printf(LOG_PREFIX_CSTR "ZeroOffsetIsHandledCorrectly -> ");

    assert(MemAlgnGetAllocSize(0, 4, 0) == 0);
    assert(MemAlgnGetAllocSize(16, 4, 0) == 20);
    assert(MemAlgnGetAllocSize(32, 8, 0) == 40);

    printf("PASSED\n");
}

void
MaxAlignmentAndOffsetLimits(void)
{
    printf(LOG_PREFIX_CSTR "MaxAlignmentAndOffsetLimits -> ");

    assert(MemAlgnGetAllocSize(16, 128, 8) == 152);
    assert(MemAlgnGetAllocSize(16, 255, 8) == 0);
    assert(MemAlgnGetAllocSize(16, 64, 16) == 0);
    assert(MemAlgnGetAllocSize(16, 255, 32) == 0);

    printf("PASSED\n");
}

void
InvalidZeroAlignment(void)
{
    printf(LOG_PREFIX_CSTR "InvalidZeroAlignment -> ");

    assert(MemAlgnGetAllocSize(16, 0, 4) == 0);
    assert(MemAlgnGetAllocSize(16, 0, 8) == 0);

    printf("PASSED\n");
}

void
InvalidNonPowerOfTwoAlignment(void)
{
    printf(LOG_PREFIX_CSTR "InvalidNonPowerOfTwoAlignment -> ");

    assert(MemAlgnGetAllocSize(1, 3, 1) == 0);
    assert(MemAlgnGetAllocSize(16, 5, 8) == 0);
    assert(MemAlgnGetAllocSize(16, 11, 4) == 0);

    printf("PASSED\n");
}

void
InvalidOffsetExceedsLimit(void)
{
    printf(LOG_PREFIX_CSTR "InvalidOffsetExceedsLimit -> ");

    assert(MemAlgnGetAllocSize(1, 1, 128) == 0);
    assert(MemAlgnGetAllocSize(16, 4, 64) == 0);
    assert(MemAlgnGetAllocSize(16, 8, 128) == 0);

    printf("PASSED\n");
}

void
InvalidNonPowerOfTwoOffset(void)
{
    printf(LOG_PREFIX_CSTR "InvalidNonPowerOfTwoOffset -> ");

    assert(MemAlgnGetAllocSize(1, 1, 3) == 0);
    assert(MemAlgnGetAllocSize(16, 4, 5) == 0);
    assert(MemAlgnGetAllocSize(16, 8, 6) == 0);
    assert(MemAlgnGetAllocSize(16, 8, 7) == 0);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    ValidPowerOfTwoAlignmentAndOffset();
    ZeroOffsetIsHandledCorrectly();
    MaxAlignmentAndOffsetLimits();
    InvalidZeroAlignment();
    InvalidNonPowerOfTwoAlignment();
    InvalidOffsetExceedsLimit();
    InvalidNonPowerOfTwoOffset();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
