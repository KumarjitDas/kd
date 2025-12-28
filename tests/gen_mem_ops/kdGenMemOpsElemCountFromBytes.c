/**
 * @file kdGenMemOpsElemCountFromBytes.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsElemCountFromBytes function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsElemCountFromBytes function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* count pointer is null -> failure */
    status = kdGenMemOpsElemCountFromBytes(null, USIZE_C(100), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* elem_sz is zero -> failure (division by zero protection) */
    count  = USIZE_C(123);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(100), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ExactMultiples(void)
{
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ExactMultiples -> ");

    /* 20 bytes / 4 bytes per elem = 5 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(20), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(5));

    /* 100 bytes / 1 byte per elem = 100 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(100), USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(100));

    /* 64 bytes / 8 bytes per elem = 8 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(64), USIZE_C(8));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(8));

    /* 32 bytes / 2 bytes per elem = 16 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(32), USIZE_C(2));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

    /* 1024 bytes / 16 bytes per elem = 64 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(1024), USIZE_C(16));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(64));

    printf("PASSED\n");
}


void
RemainderBehavior(void)
{
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "RemainderBehavior -> ");

    /* 22 bytes / 4 bytes per elem = 5 elements (remainder 2 bytes ignored) */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(22), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(5));

    /* 3 bytes / 4 bytes per elem = 0 elements */
    count  = USIZE_C(99);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(3), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    /* 15 bytes / 8 bytes per elem = 1 element (remainder 7 bytes) */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(15), USIZE_C(8));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(1));

    /* 99 bytes / 10 bytes per elem = 9 elements (remainder 9 bytes) */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(99), USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(9));

    /* 7 bytes / 8 bytes per elem = 0 elements */
    count  = USIZE_C(999);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(7), USIZE_C(8));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    printf("PASSED\n");
}


void
ZeroBaseSize(void)
{
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ZeroBaseSize -> ");

    /* 0 bytes / 10 bytes per elem -> failure (zero base size not allowed) */
    count  = USIZE_C(1);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(0), USIZE_C(10));
    assert(status == RESULT_FAILURE);

    /* 0 bytes / 1 byte per elem -> failure */
    count  = USIZE_C(5);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(0), USIZE_C(1));
    assert(status == RESULT_FAILURE);

    /* 0 bytes / 4 bytes per elem -> failure */
    count  = USIZE_C(100);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SingleByteElements(void)
{
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleByteElements -> ");

    /* 1 byte / 1 byte per elem = 1 element */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(1), USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(1));

    /* 10 bytes / 1 byte per elem = 10 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(10), USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(10));

    /* 255 bytes / 1 byte per elem = 255 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(255), USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(255));

    /* 1000 bytes / 1 byte per elem = 1000 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(1000), USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(1000));

    printf("PASSED\n");
}


void
CommonElementSizes(void)
{
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CommonElementSizes -> ");

    /* u8 array: 100 bytes / 1 byte = 100 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(100), USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(100));

    /* u16 array: 100 bytes / 2 bytes = 50 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(100), USIZE_C(2));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(50));

    /* u32 array: 100 bytes / 4 bytes = 25 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(100), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(25));

    /* u64 array: 128 bytes / 8 bytes = 16 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(128), USIZE_C(8));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

    /* Pointer array (assuming 8-byte pointers): 400 bytes / 8 bytes = 50 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(400), USIZE_C(8));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(50));

    printf("PASSED\n");
}


void
LargeElementSizes(void)
{
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "LargeElementSizes -> ");

    /* 1000 bytes / 100 bytes per elem = 10 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(1000), USIZE_C(100));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(10));

    /* 5000 bytes / 250 bytes per elem = 20 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(5000), USIZE_C(250));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(20));

    /* 4096 bytes / 512 bytes per elem = 8 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(4096), USIZE_C(512));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(8));

    /* 10000 bytes / 1000 bytes per elem = 10 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(10000), USIZE_C(1000));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(10));

    printf("PASSED\n");
}


void
OddElementSizes(void)
{
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "OddElementSizes -> ");

    /* 99 bytes / 3 bytes per elem = 33 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(99), USIZE_C(3));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(33));

    /* 175 bytes / 5 bytes per elem = 35 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(175), USIZE_C(5));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(35));

    /* 343 bytes / 7 bytes per elem = 49 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(343), USIZE_C(7));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(49));

    /* 117 bytes / 9 bytes per elem = 13 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(117), USIZE_C(9));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(13));

    /* 110 bytes / 11 bytes per elem = 10 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(110), USIZE_C(11));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(10));

    printf("PASSED\n");
}


void
PowerOfTwoSizes(void)
{
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "PowerOfTwoSizes -> ");

    /* 256 bytes / 16 bytes per elem = 16 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(256), USIZE_C(16));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

    /* 512 bytes / 32 bytes per elem = 16 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(512), USIZE_C(32));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

    /* 1024 bytes / 64 bytes per elem = 16 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(1024), USIZE_C(64));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

    /* 2048 bytes / 128 bytes per elem = 16 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(2048), USIZE_C(128));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

    /* 4096 bytes / 256 bytes per elem = 16 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(4096), USIZE_C(256));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

    printf("PASSED\n");
}


void
SingleElement(void)
{
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleElement -> ");

    /* 4 bytes / 4 bytes per elem = 1 element */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(4), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(1));

    /* 8 bytes / 8 bytes per elem = 1 element */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(8), USIZE_C(8));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(1));

    /* 100 bytes / 100 bytes per elem = 1 element */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(100), USIZE_C(100));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(1));

    /* 1024 bytes / 1024 bytes per elem = 1 element */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(1024), USIZE_C(1024));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(1));

    printf("PASSED\n");
}


void
ElementLargerThanBuffer(void)
{
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ElementLargerThanBuffer -> ");

    /* 10 bytes / 20 bytes per elem = 0 elements */
    count  = USIZE_C(99);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(10), USIZE_C(20));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    /* 1 byte / 10 bytes per elem = 0 elements */
    count  = USIZE_C(99);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(1), USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    /* 50 bytes / 100 bytes per elem = 0 elements */
    count  = USIZE_C(99);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(50), USIZE_C(100));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    /* 999 bytes / 1000 bytes per elem = 0 elements */
    count  = USIZE_C(99);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(999), USIZE_C(1000));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    printf("PASSED\n");
}


void
LargeBufferSizes(void)
{
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "LargeBufferSizes -> ");

    /* 10000 bytes / 10 bytes per elem = 1000 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(10000), USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(1000));

    /* 1048576 bytes (1 MB) / 1024 bytes per elem = 1024 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(1048576), USIZE_C(1024));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(1024));

    /* 65536 bytes / 16 bytes per elem = 4096 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(65536), USIZE_C(16));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(4096));

    /* 100000 bytes / 4 bytes per elem = 25000 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(100000), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(25000));

    printf("PASSED\n");
}


void
StructSizes(void)
{
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "StructSizes -> ");

    /* Struct of 12 bytes: 120 bytes / 12 bytes per elem = 10 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(120), USIZE_C(12));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(10));

    /* Struct of 24 bytes: 240 bytes / 24 bytes per elem = 10 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(240), USIZE_C(24));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(10));

    /* Struct of 40 bytes: 400 bytes / 40 bytes per elem = 10 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(400), USIZE_C(40));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(10));

    /* Struct of 48 bytes: 960 bytes / 48 bytes per elem = 20 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(960), USIZE_C(48));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(20));

    printf("PASSED\n");
}


void
BoundaryValues(void)
{
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "BoundaryValues -> ");

    /* base_sz = 1, elem_sz = 1 -> 1 element */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(1), USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(1));

    /* base_sz = 1, elem_sz = 2 -> 0 elements */
    count  = USIZE_C(99);
    status = kdGenMemOpsElemCountFromBytes(&count, USIZE_C(1), USIZE_C(2));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    /* base_sz = MAX_USIZE, elem_sz = 1 -> MAX_USIZE elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, MAX_USIZE, USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(count == MAX_USIZE);

    /* base_sz = MAX_USIZE, elem_sz = MAX_USIZE -> 1 element */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, MAX_USIZE, MAX_USIZE);

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(1));

    /* base_sz = MAX_USIZE / 2, elem_sz = 2 -> MAX_USIZE / 4 elements */
    count  = USIZE_C(0);
    status = kdGenMemOpsElemCountFromBytes(&count, MAX_USIZE / USIZE_C(2), USIZE_C(2));

    assert(status == RESULT_SUCCESS);
    assert(count == MAX_USIZE / USIZE_C(4));

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    ExactMultiples();
    RemainderBehavior();
    ZeroBaseSize();
    SingleByteElements();
    CommonElementSizes();
    LargeElementSizes();
    OddElementSizes();
    PowerOfTwoSizes();
    SingleElement();
    ElementLargerThanBuffer();
    LargeBufferSizes();
    StructSizes();
    BoundaryValues();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
