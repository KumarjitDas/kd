/**
 * @file kdGenMemOpsRegionContains.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsRegionContains function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsRegionContains function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8   buf[32];
    bool contains;
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* result pointer is null -> failure */
    status = GenMemOpsRegionContains(null, &buf[0], USIZE_C(20), &buf[5], USIZE_C(5));
    assert(status == RESULT_FAILURE);

    /* base is null (and size > 0) -> failure */
    status = GenMemOpsRegionContains(&contains, null, USIZE_C(20), &buf[5], USIZE_C(5));
    assert(status == RESULT_FAILURE);

    /* ptr is null (and size > 0) -> failure */
    status = GenMemOpsRegionContains(&contains, &buf[0], USIZE_C(20), null, USIZE_C(5));
    assert(status == RESULT_FAILURE);

    /* ptr_sz is zero -> success (empty set is a subset of any set) */
    contains = false; /* reset */
    status   = GenMemOpsRegionContains(&contains, &buf[0], USIZE_C(20), &buf[5], USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    assert(contains == true);

    /* base_sz is zero, ptr_sz > 0 -> success (cannot contain anything) */
    contains = true; /* reset */
    status   = GenMemOpsRegionContains(&contains, &buf[0], USIZE_C(0), &buf[0], USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(contains == false);

    printf("PASSED\n");
}


void
FullyContained(void)
{
    u8   buf[32];
    bool contains;
    bool status;

    printf(LOG_PREFIX_CSTR "FullyContained -> ");

    /* Base: 0..19 (size 20) */
    /* Ptr:  5..14 (size 10) */
    /* Ptr is strictly inside Base */
    contains = false;
    status   = GenMemOpsRegionContains(&contains, &buf[0], USIZE_C(20), &buf[5], USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(contains == true);

    printf("PASSED\n");
}


void
ExactMatch(void)
{
    u8   buf[32];
    bool contains;
    bool status;

    printf(LOG_PREFIX_CSTR "ExactMatch -> ");

    /* Base: 5..14 (size 10) */
    /* Ptr:  5..14 (size 10) */
    contains = false;
    status   = GenMemOpsRegionContains(&contains, &buf[5], USIZE_C(10), &buf[5], USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(contains == true);

    printf("PASSED\n");
}


void
NotContained_Overflow(void)
{
    u8   buf[32];
    bool contains;
    bool status;

    printf(LOG_PREFIX_CSTR "NotContained_Overflow -> ");

    /* Base: 0..9 (size 10) */
    /* Ptr:  5..14 (size 10) */
    /* Ptr starts inside Base, but extends beyond it */
    contains = true;
    status   = GenMemOpsRegionContains(&contains, &buf[0], USIZE_C(10), &buf[5], USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(contains == false);

    printf("PASSED\n");
}


void
NotContained_Disjoint(void)
{
    u8   buf[32];
    bool contains;
    bool status;

    printf(LOG_PREFIX_CSTR "NotContained_Disjoint -> ");

    /* Base: 0..9 (size 10) */
    /* Ptr:  20..24 (size 5) */
    /* Completely outside */
    contains = true;
    status   = GenMemOpsRegionContains(&contains, &buf[0], USIZE_C(10), &buf[20], USIZE_C(5));

    assert(status == RESULT_SUCCESS);
    assert(contains == false);

    /* Ptr is before Base */
    /* Base: 10..19 */
    /* Ptr:  0..4 */
    contains = true;
    status   = GenMemOpsRegionContains(&contains, &buf[10], USIZE_C(10), &buf[0], USIZE_C(5));

    assert(status == RESULT_SUCCESS);
    assert(contains == false);

    printf("PASSED\n");
}


void
NotContained_PtrLarger(void)
{
    u8   buf[32];
    bool contains;
    bool status;

    printf(LOG_PREFIX_CSTR "NotContained_PtrLarger -> ");

    /* Base: 0..9 (size 10) */
    /* Ptr:  0..10 (size 11) */
    /* Ptr is larger than Base, impossible to contain */
    contains = true;
    status   = GenMemOpsRegionContains(&contains, &buf[0], USIZE_C(10), &buf[0], USIZE_C(11));

    assert(status == RESULT_SUCCESS);
    assert(contains == false);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    FullyContained();
    ExactMatch();
    NotContained_Overflow();
    NotContained_Disjoint();
    NotContained_PtrLarger();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
