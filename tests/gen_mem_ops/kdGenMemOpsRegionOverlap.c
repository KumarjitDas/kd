/**
 * @file kdGenMemOpsRegionOverlap.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsRegionOverlap function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsRegionOverlap function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8   buf[32];
    bool overlap;
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* result pointer is null -> failure */
    status = GenMemOpsRegionOverlap(null, &buf[0], USIZE_C(10), &buf[10], USIZE_C(10));
    assert(status == RESULT_FAILURE);

    /* ptr_1 is null (and sz > 0) -> failure */
    status = GenMemOpsRegionOverlap(&overlap, null, USIZE_C(10), &buf[10], USIZE_C(10));
    assert(status == RESULT_FAILURE);

    /* ptr_2 is null (and sz > 0) -> failure */
    status = GenMemOpsRegionOverlap(&overlap, &buf[0], USIZE_C(10), null, USIZE_C(10));
    assert(status == RESULT_FAILURE);

    /* ptr_1_sz is zero -> success, no overlap possible */
    overlap = true; /* reset */
    status  = GenMemOpsRegionOverlap(&overlap, &buf[0], USIZE_C(0), &buf[10], USIZE_C(10));
    assert(status == RESULT_SUCCESS);
    assert(overlap == false);

    /* ptr_2_sz is zero -> success, no overlap possible */
    overlap = true; /* reset */
    status  = GenMemOpsRegionOverlap(&overlap, &buf[0], USIZE_C(10), &buf[10], USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    assert(overlap == false);

    printf("PASSED\n");
}


void
DisjointRegions(void)
{
    u8   buf[32];
    bool overlap;
    bool status;

    printf(LOG_PREFIX_CSTR "DisjointRegions -> ");

    /* Region 1: 0..9 (size 10) */
    /* Region 2: 20..29 (size 10) */
    overlap = true;
    status  = GenMemOpsRegionOverlap(&overlap, &buf[0], USIZE_C(10), &buf[20], USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(overlap == false);

    printf("PASSED\n");
}


void
TouchingRegions(void)
{
    u8   buf[32];
    bool overlap;
    bool status;

    printf(LOG_PREFIX_CSTR "TouchingRegions -> ");

    /* Region 1: 0..9 (size 10) */
    /* Region 2: 10..19 (size 10) */
    /* They touch at index 10 (End of R1 is Start of R2), but do not share any byte */
    overlap = true;
    status  = GenMemOpsRegionOverlap(&overlap, &buf[0], USIZE_C(10), &buf[10], USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(overlap == false);

    /* Reverse order check */
    overlap = true;
    status  = GenMemOpsRegionOverlap(&overlap, &buf[10], USIZE_C(10), &buf[0], USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(overlap == false);

    printf("PASSED\n");
}


void
PartialOverlap(void)
{
    u8   buf[32];
    bool overlap;
    bool status;

    printf(LOG_PREFIX_CSTR "PartialOverlap -> ");

    /* Region 1: 0..9 (size 10) */
    /* Region 2: 5..14 (size 10) */
    /* Overlap on indices 5,6,7,8,9 */
    overlap = false;
    status  = GenMemOpsRegionOverlap(&overlap, &buf[0], USIZE_C(10), &buf[5], USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(overlap == true);

    printf("PASSED\n");
}


void
EnclosedOverlap(void)
{
    u8   buf[32];
    bool overlap;
    bool status;

    printf(LOG_PREFIX_CSTR "EnclosedOverlap -> ");

    /* Region 1: 0..19 (size 20) */
    /* Region 2: 5..14 (size 10) */
    /* Region 2 is fully inside Region 1 */
    overlap = false;
    status  = GenMemOpsRegionOverlap(&overlap, &buf[0], USIZE_C(20), &buf[5], USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(overlap == true);

    printf("PASSED\n");
}


void
IdenticalRegions(void)
{
    u8   buf[32];
    bool overlap;
    bool status;

    printf(LOG_PREFIX_CSTR "IdenticalRegions -> ");

    /* Region 1: 5..14 */
    /* Region 2: 5..14 */
    overlap = false;
    status  = GenMemOpsRegionOverlap(&overlap, &buf[5], USIZE_C(10), &buf[5], USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(overlap == true);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    DisjointRegions();
    TouchingRegions();
    PartialOverlap();
    EnclosedOverlap();
    IdenticalRegions();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
