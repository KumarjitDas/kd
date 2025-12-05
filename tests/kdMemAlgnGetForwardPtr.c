/**
 * @file kdMemAlgnGetForwardPtr.c
 * @author Kumarjit Das
 * @brief KD_MEM_ALGN library kdMemAlgnGetForwardPtr function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../include/kd/mem_algn.h"


#define LIB_NAME_CSTR   "KD_MEM_ALGN"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdMemAlgnGetForwardPtr function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
AlignsCorrectlyForGivenOffset(void)
{
    printf(LOG_PREFIX_CSTR "AlignsCorrectlyForGivenOffset -> ");

    assert(MemAlgnGetForwardPtr(PTR_C(4), 4, 1) == PTR_C(8));
    assert(MemAlgnGetForwardPtr(PTR_C(5), 4, 1) == PTR_C(8));
    assert(MemAlgnGetForwardPtr(PTR_C(6), 4, 1) == PTR_C(8));
    assert(MemAlgnGetForwardPtr(PTR_C(7), 4, 1) == PTR_C(12));

    assert(MemAlgnGetForwardPtr(PTR_C(4), 4, 2) == PTR_C(8));
    assert(MemAlgnGetForwardPtr(PTR_C(5), 4, 2) == PTR_C(8));
    assert(MemAlgnGetForwardPtr(PTR_C(6), 4, 2) == PTR_C(12));
    assert(MemAlgnGetForwardPtr(PTR_C(7), 4, 2) == PTR_C(12));

    assert(MemAlgnGetForwardPtr(PTR_C(4), 4, 4) == PTR_C(12));
    assert(MemAlgnGetForwardPtr(PTR_C(5), 4, 4) == PTR_C(12));
    assert(MemAlgnGetForwardPtr(PTR_C(6), 4, 4) == PTR_C(12));
    assert(MemAlgnGetForwardPtr(PTR_C(7), 4, 4) == PTR_C(12));

    assert(MemAlgnGetForwardPtr(PTR_C(4), 4, 8) == PTR_C(16));
    assert(MemAlgnGetForwardPtr(PTR_C(5), 4, 8) == PTR_C(16));
    assert(MemAlgnGetForwardPtr(PTR_C(6), 4, 8) == PTR_C(16));
    assert(MemAlgnGetForwardPtr(PTR_C(7), 4, 8) == PTR_C(16));

    printf("PASSED\n");
}

void
ZeroOffsetHandledCorrectly(void)
{
    printf(LOG_PREFIX_CSTR "ZeroOffsetHandledCorrectly -> ");

    assert(MemAlgnGetForwardPtr(PTR_C(4), 4, 0) == PTR_C(8));
    assert(MemAlgnGetForwardPtr(PTR_C(5), 4, 0) == PTR_C(8));
    assert(MemAlgnGetForwardPtr(PTR_C(6), 4, 0) == PTR_C(8));
    assert(MemAlgnGetForwardPtr(PTR_C(7), 4, 0) == PTR_C(8));

    assert(MemAlgnGetForwardPtr(PTR_C(4), 8, 0) == PTR_C(8));
    assert(MemAlgnGetForwardPtr(PTR_C(5), 8, 0) == PTR_C(8));
    assert(MemAlgnGetForwardPtr(PTR_C(6), 8, 0) == PTR_C(8));
    assert(MemAlgnGetForwardPtr(PTR_C(7), 8, 0) == PTR_C(8));

    assert(MemAlgnGetForwardPtr(PTR_C(13), 16, 0) == PTR_C(16));
    assert(MemAlgnGetForwardPtr(PTR_C(15), 16, 0) == PTR_C(16));
    assert(MemAlgnGetForwardPtr(PTR_C(18), 16, 0) == PTR_C(32));
    assert(MemAlgnGetForwardPtr(PTR_C(21), 16, 0) == PTR_C(32));
    assert(MemAlgnGetForwardPtr(PTR_C(35), 16, 0) == PTR_C(48));

    printf("PASSED\n");
}

void
AlignmentAndOffsetBoundaries(void)
{
    printf(LOG_PREFIX_CSTR "AlignmentAndOffsetBoundaries -> ");

    assert(MemAlgnGetForwardPtr(PTR_C(4), 255, 0) == null);
    assert(MemAlgnGetForwardPtr(PTR_C(5), 4, 23) == null);

    printf("PASSED\n");
}

void
InvalidAlignmentOrOffsetPanicsOrFails(void)
{
    printf(LOG_PREFIX_CSTR "InvalidAlignmentOrOffsetPanicsOrFails -> ");

    assert(MemAlgnGetForwardPtr(PTR_C(4), 0, 0) == null);
    assert(MemAlgnGetForwardPtr(PTR_C(5), 3, 0) == null);
    assert(MemAlgnGetForwardPtr(PTR_C(6), 19, 0) == null);
    assert(MemAlgnGetForwardPtr(PTR_C(7), 35, 0) == null);

    assert(MemAlgnGetForwardPtr(PTR_C(4), 4, 3) == null);
    assert(MemAlgnGetForwardPtr(PTR_C(5), 4, 5) == null);
    assert(MemAlgnGetForwardPtr(PTR_C(6), 4, 6) == null);
    assert(MemAlgnGetForwardPtr(PTR_C(7), 4, 7) == null);

    assert(MemAlgnGetForwardPtr(PTR_C(4), 0, 3) == null);
    assert(MemAlgnGetForwardPtr(PTR_C(5), 1, 5) == null);
    assert(MemAlgnGetForwardPtr(PTR_C(6), 19, 6) == null);
    assert(MemAlgnGetForwardPtr(PTR_C(7), 35, 7) == null);

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

    return EXIT_SUCCESS;
}
