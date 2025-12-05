/**
 * @file kdMemAlgnGetBackwardPtr.c
 * @author Kumarjit Das
 * @brief KD_MEM_ALGN library kdMemAlgnGetBackwardPtr function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../include/kd/mem_algn.h"


#define LIB_NAME_CSTR   "KD_MEM_ALGN"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdMemAlgnGetBackwardPtr function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
AlignsCorrectlyForGivenOffset(void)
{
    printf(LOG_PREFIX_CSTR "AlignsCorrectlyForGivenOffset -> ");

    assert(MemAlgnGetBackwardPtr(KD_PTR_C(4), 4, 1) == KD_PTR_C(0));
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(5), 4, 1) == KD_PTR_C(4));
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(6), 4, 1) == KD_PTR_C(4));
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(12), 4, 1) == KD_PTR_C(8));

    assert(MemAlgnGetBackwardPtr(KD_PTR_C(4), 4, 2) == KD_PTR_C(0));
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(5), 4, 2) == KD_PTR_C(4));
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(6), 4, 2) == KD_PTR_C(4));
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(12), 4, 2) == KD_PTR_C(8));

    assert(MemAlgnGetBackwardPtr(KD_PTR_C(4), 4, 4) == KD_PTR_C(0));
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(5), 4, 4) == KD_PTR_C(4));
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(6), 4, 4) == KD_PTR_C(4));
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(12), 4, 4) == KD_PTR_C(8));

    assert(MemAlgnGetBackwardPtr(KD_PTR_C(4), 4, 8) == KD_PTR_C(0));
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(5), 4, 8) == KD_PTR_C(4));
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(6), 4, 8) == KD_PTR_C(4));
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(12), 4, 8) == KD_PTR_C(8));

    printf("PASSED\n");
}

void
ZeroOffsetHandledCorrectly(void)
{
    printf(LOG_PREFIX_CSTR "ZeroOffsetHandledCorrectly -> ");

    assert(MemAlgnGetBackwardPtr(KD_PTR_C(4), 4, 0) == KD_PTR_C(0));
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(5), 4, 0) == KD_PTR_C(4));
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(6), 4, 0) == KD_PTR_C(4));
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(12), 4, 0) == KD_PTR_C(8));

    assert(MemAlgnGetBackwardPtr(KD_PTR_C(8), 8, 0) == KD_PTR_C(0));
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(13), 8, 0) == KD_PTR_C(8));
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(14), 8, 0) == KD_PTR_C(8));
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(16), 8, 0) == KD_PTR_C(8));

    printf("PASSED\n");
}

void
AlignmentAndOffsetBoundaries(void)
{
    printf(LOG_PREFIX_CSTR "AlignmentAndOffsetBoundaries -> ");

    assert(MemAlgnGetBackwardPtr(KD_PTR_C(4), 255, 0) == null);
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(5), 4, 23) == null);

    printf("PASSED\n");
}

void
InvalidAlignmentOrOffsetPanicsOrFails(void)
{
    printf(LOG_PREFIX_CSTR "InvalidAlignmentOrOffsetPanicsOrFails -> ");

    assert(MemAlgnGetBackwardPtr(KD_PTR_C(4), 0, 0) == null);
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(5), 3, 0) == null);
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(6), 19, 0) == null);
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(7), 35, 0) == null);

    assert(MemAlgnGetBackwardPtr(KD_PTR_C(4), 4, 3) == null);
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(5), 4, 5) == null);
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(6), 4, 6) == null);
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(7), 4, 7) == null);

    assert(MemAlgnGetBackwardPtr(KD_PTR_C(4), 0, 3) == null);
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(5), 1, 5) == null);
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(6), 19, 6) == null);
    assert(MemAlgnGetBackwardPtr(KD_PTR_C(7), 35, 7) == null);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    AlignsCorrectlyForGivenOffset();
    ZeroOffsetHandledCorrectly();
    AlignmentAndOffsetBoundaries();
    InvalidAlignmentOrOffsetPanicsOrFails();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
