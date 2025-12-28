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
    status = kdGenMemOpsRegionContains(null, &buf[0], USIZE_C(20), &buf[5], USIZE_C(5));
    assert(status == RESULT_FAILURE);

    /* base is null (and size > 0) -> failure */
    status = kdGenMemOpsRegionContains(&contains, null, USIZE_C(20), &buf[5], USIZE_C(5));
    assert(status == RESULT_FAILURE);

    /* ptr is null (and size > 0) -> failure */
    status = kdGenMemOpsRegionContains(&contains, &buf[0], USIZE_C(20), null, USIZE_C(5));
    assert(status == RESULT_FAILURE);

    /* ptr_sz is zero -> failure */
    status = kdGenMemOpsRegionContains(&contains, &buf[0], USIZE_C(20), &buf[5], USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = kdGenMemOpsRegionContains(&contains, &buf[0], USIZE_C(0), &buf[0], USIZE_C(1));
    assert(status == RESULT_FAILURE);

    /* Both sizes zero -> failure */
    status = kdGenMemOpsRegionContains(&contains, &buf[0], USIZE_C(0), &buf[0], USIZE_C(0));
    assert(status == RESULT_FAILURE);

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
    status   = kdGenMemOpsRegionContains(&contains, &buf[0], USIZE_C(20), &buf[5], USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(contains == true);

    /* Ptr at the start of Base */
    contains = false;
    status   = kdGenMemOpsRegionContains(&contains, &buf[0], USIZE_C(20), &buf[0], USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(contains == true);

    /* Ptr at the end of Base */
    contains = false;
    status   = kdGenMemOpsRegionContains(&contains, &buf[0], USIZE_C(20), &buf[10], USIZE_C(10));

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
    status   = kdGenMemOpsRegionContains(&contains, &buf[5], USIZE_C(10), &buf[5], USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(contains == true);

    /* Base and Ptr are the same starting point, same size */
    contains = false;
    status   = kdGenMemOpsRegionContains(&contains, &buf[0], USIZE_C(32), &buf[0], USIZE_C(32));

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
    status   = kdGenMemOpsRegionContains(&contains, &buf[0], USIZE_C(10), &buf[5], USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(contains == false);

    /* Ptr starts at the last byte of Base */
    contains = true;
    status   = kdGenMemOpsRegionContains(&contains, &buf[0], USIZE_C(10), &buf[9], USIZE_C(2));

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
    status   = kdGenMemOpsRegionContains(&contains, &buf[0], USIZE_C(10), &buf[20], USIZE_C(5));

    assert(status == RESULT_SUCCESS);
    assert(contains == false);

    /* Ptr is before Base */
    /* Base: 10..19 */
    /* Ptr:  0..4 */
    contains = true;
    status   = kdGenMemOpsRegionContains(&contains, &buf[10], USIZE_C(10), &buf[0], USIZE_C(5));

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
    status   = kdGenMemOpsRegionContains(&contains, &buf[0], USIZE_C(10), &buf[0], USIZE_C(11));

    assert(status == RESULT_SUCCESS);
    assert(contains == false);

    /* Base: 5..14 (size 10) */
    /* Ptr:  0..14 (size 15) */
    /* Ptr extends before Base starts */
    contains = true;
    status   = kdGenMemOpsRegionContains(&contains, &buf[5], USIZE_C(10), &buf[0], USIZE_C(15));

    assert(status == RESULT_SUCCESS);
    assert(contains == false);

    printf("PASSED\n");
}


void
SingleByte(void)
{
    u8   buf[32];
    bool contains;
    bool status;

    printf(LOG_PREFIX_CSTR "SingleByte -> ");

    /* Base: 0..9 (size 10) */
    /* Ptr: single byte at index 5 */
    contains = false;
    status   = kdGenMemOpsRegionContains(&contains, &buf[0], USIZE_C(10), &buf[5], USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(contains == true);

    /* Base: single byte at index 5 */
    /* Ptr: single byte at index 5 (same) */
    contains = false;
    status   = kdGenMemOpsRegionContains(&contains, &buf[5], USIZE_C(1), &buf[5], USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(contains == true);

    /* Base: single byte at index 5 */
    /* Ptr: single byte at index 6 (different) */
    contains = true;
    status   = kdGenMemOpsRegionContains(&contains, &buf[5], USIZE_C(1), &buf[6], USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(contains == false);

    /* Base: 0..9 (size 10) */
    /* Ptr: single byte at index 0 (start of base) */
    contains = false;
    status   = kdGenMemOpsRegionContains(&contains, &buf[0], USIZE_C(10), &buf[0], USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(contains == true);

    /* Base: 0..9 (size 10) */
    /* Ptr: single byte at index 9 (end of base) */
    contains = false;
    status   = kdGenMemOpsRegionContains(&contains, &buf[0], USIZE_C(10), &buf[9], USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(contains == true);

    /* Base: 0..9 (size 10) */
    /* Ptr: single byte at index 10 (just beyond base) */
    contains = true;
    status   = kdGenMemOpsRegionContains(&contains, &buf[0], USIZE_C(10), &buf[10], USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(contains == false);

    printf("PASSED\n");
}


void
LargeRegions(void)
{
    u8   buf1[512];
    u8   buf2[512];
    bool contains;
    bool status;

    printf(LOG_PREFIX_CSTR "LargeRegions -> ");

    /* Large base containing large ptr */
    contains = false;
    status   = kdGenMemOpsRegionContains(&contains, buf1, USIZE_C(512), &buf1[100], USIZE_C(200));

    assert(status == RESULT_SUCCESS);
    assert(contains == true);

    /* Two separate large buffers -> not contained */
    contains = true;
    status   = kdGenMemOpsRegionContains(&contains, buf1, USIZE_C(512), buf2, USIZE_C(512));

    assert(status == RESULT_SUCCESS);
    assert(contains == false);

    /* Large base, ptr extends beyond */
    contains = true;
    status   = kdGenMemOpsRegionContains(&contains, &buf1[0], USIZE_C(400), &buf1[300], USIZE_C(200));

    assert(status == RESULT_SUCCESS);
    assert(contains == false);

    printf("PASSED\n");
}


void
BoundaryConditions(void)
{
    u8   buf[100];
    bool contains;
    bool status;

    printf(LOG_PREFIX_CSTR "BoundaryConditions -> ");

    /* Ptr at the exact end boundary of Base */
    /* Base: 0..49 (size 50) */
    /* Ptr: 49..49 (size 1, last byte of base) */
    contains = false;
    status   = kdGenMemOpsRegionContains(&contains, &buf[0], USIZE_C(50), &buf[49], USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(contains == true);

    /* Ptr starts at end boundary (beyond base) */
    /* Base: 0..49 (size 50) */
    /* Ptr: 50..50 (size 1, just beyond) */
    contains = true;
    status   = kdGenMemOpsRegionContains(&contains, &buf[0], USIZE_C(50), &buf[50], USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(contains == false);

    /* Adjacent regions - base then ptr */
    /* Base: 0..49 (size 50) */
    /* Ptr: 50..59 (size 10, adjacent after base) */
    contains = true;
    status   = kdGenMemOpsRegionContains(&contains, &buf[0], USIZE_C(50), &buf[50], USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(contains == false);

    /* Ptr ends at exact boundary of base */
    /* Base: 10..59 (size 50) */
    /* Ptr: 50..59 (size 10, ends at base end) */
    contains = false;
    status   = kdGenMemOpsRegionContains(&contains, &buf[10], USIZE_C(50), &buf[50], USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(contains == true);

    printf("PASSED\n");
}


void
PointerArithmetic(void)
{
    u8   buf[100];
    bool contains;
    bool status;

    printf(LOG_PREFIX_CSTR "PointerArithmetic -> ");

    /* Verify contains checks actual pointer ranges, not just relative positions */
    /* Base: 20..39 (size 20) */
    /* Ptr: 25..29 (size 5, inside) */
    contains = false;
    status   = kdGenMemOpsRegionContains(&contains, &buf[20], USIZE_C(20), &buf[25], USIZE_C(5));

    assert(status == RESULT_SUCCESS);
    assert(contains == true);

    /* Base: 20..39 (size 20) */
    /* Ptr: 15..19 (size 5, before base) */
    contains = true;
    status   = kdGenMemOpsRegionContains(&contains, &buf[20], USIZE_C(20), &buf[15], USIZE_C(5));

    assert(status == RESULT_SUCCESS);
    assert(contains == false);

    /* Base: 20..39 (size 20) */
    /* Ptr: 40..44 (size 5, after base) */
    contains = true;
    status   = kdGenMemOpsRegionContains(&contains, &buf[20], USIZE_C(20), &buf[40], USIZE_C(5));

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
    SingleByte();
    LargeRegions();
    BoundaryConditions();
    PointerArithmetic();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
