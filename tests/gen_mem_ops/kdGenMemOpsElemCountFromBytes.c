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

    /* sz_addr is null -> failure */
    status = GenMemOpsElemCountFromBytes(null, USIZE_C(100), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* elem_sz is zero -> failure (division by zero protection) */
    count  = USIZE_C(123);
    status = GenMemOpsElemCountFromBytes(&count, USIZE_C(100), USIZE_C(0));
    assert(status == RESULT_FAILURE);
    /* verify count wasn't touched or is safe (implementation dependent, but checking failure is key) */

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
    status = GenMemOpsElemCountFromBytes(&count, USIZE_C(20), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(5));

    /* 100 bytes / 1 byte per elem = 100 elements */
    count  = USIZE_C(0);
    status = GenMemOpsElemCountFromBytes(&count, USIZE_C(100), USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(100));

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
    status = GenMemOpsElemCountFromBytes(&count, USIZE_C(22), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(5));

    /* 3 bytes / 4 bytes per elem = 0 elements */
    count  = USIZE_C(99);
    status = GenMemOpsElemCountFromBytes(&count, USIZE_C(3), USIZE_C(4));

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

    /* 0 bytes / 10 bytes per elem = 0 elements */
    count  = USIZE_C(1);
    status = GenMemOpsElemCountFromBytes(&count, USIZE_C(0), USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

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

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
