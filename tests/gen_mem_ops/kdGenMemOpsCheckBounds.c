/**
 * @file kdGenMemOpsCheckBounds.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsCheckBounds function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsCheckBounds function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
ValidBounds(void)
{
    bool result;

    printf(LOG_PREFIX_CSTR "ValidBounds -> ");

    /* 1. Start of buffer */
    /* Total: 10, Offset: 0, Size: 5 -> Valid (ends at 5) */
    result = GenMemOpsCheckBounds(USIZE_C(10), USIZE_C(0), USIZE_C(5));
    assert(result == true);

    /* 2. Middle of buffer */
    /* Total: 10, Offset: 2, Size: 5 -> Valid (ends at 7) */
    result = GenMemOpsCheckBounds(USIZE_C(10), USIZE_C(2), USIZE_C(5));
    assert(result == true);

    /* 3. Exact fit */
    /* Total: 10, Offset: 5, Size: 5 -> Valid (ends at 10) */
    result = GenMemOpsCheckBounds(USIZE_C(10), USIZE_C(5), USIZE_C(5));
    assert(result == true);

    /* 4. Full buffer */
    /* Total: 10, Offset: 0, Size: 10 -> Valid */
    result = GenMemOpsCheckBounds(USIZE_C(10), USIZE_C(0), USIZE_C(10));
    assert(result == true);

    printf("PASSED\n");
}


void
InvalidBounds(void)
{
    bool result;

    printf(LOG_PREFIX_CSTR "InvalidBounds -> ");

    /* 1. Offset > Total */
    /* Total: 10, Offset: 11, Size: 1 -> Invalid */
    result = GenMemOpsCheckBounds(USIZE_C(10), USIZE_C(11), USIZE_C(1));
    assert(result == false);

    /* 2. Offset == Total (Size > 0) */
    /* Total: 10, Offset: 10, Size: 1 -> Invalid */
    result = GenMemOpsCheckBounds(USIZE_C(10), USIZE_C(10), USIZE_C(1));
    assert(result == false);

    /* 3. Offset valid, Size too large */
    /* Total: 10, Offset: 0, Size: 11 -> Invalid */
    result = GenMemOpsCheckBounds(USIZE_C(10), USIZE_C(0), USIZE_C(11));
    assert(result == false);

    /* 4. Offset valid, Range exceeds total */
    /* Total: 10, Offset: 8, Size: 3 -> Invalid (ends at 11) */
    result = GenMemOpsCheckBounds(USIZE_C(10), USIZE_C(8), USIZE_C(3));
    assert(result == false);

    printf("PASSED\n");
}


void
ZeroSizeEdgeCases(void)
{
    bool result;

    printf(LOG_PREFIX_CSTR "ZeroSizeEdgeCases -> ");

    /* 1. Size is 0, Offset inside -> Valid */
    /* Total: 10, Offset: 5, Size: 0 */
    result = GenMemOpsCheckBounds(USIZE_C(10), USIZE_C(5), USIZE_C(0));
    assert(result == true);

    /* 2. Size is 0, Offset at end -> Valid */
    /* Total: 10, Offset: 10, Size: 0 */
    result = GenMemOpsCheckBounds(USIZE_C(10), USIZE_C(10), USIZE_C(0));
    assert(result == true);

    /* 3. Size is 0, Offset beyond end -> Invalid */
    /* Total: 10, Offset: 11, Size: 0 */
    result = GenMemOpsCheckBounds(USIZE_C(10), USIZE_C(11), USIZE_C(0));
    assert(result == false);

    printf("PASSED\n");
}


void
IntegerOverflow(void)
{
    bool result;

    printf(LOG_PREFIX_CSTR "IntegerOverflow -> ");

    /* Test potential wrap-around if implementation does (offset + sz) check blindly */

    /* Offset + Size wraps around to be < Total, but mathematically > Total */
    /* Total: 100 */
    /* Offset: MAX_USIZE - 5 */
    /* Size: 10 */
    /* Sum wraps to 4 (if overflow not checked), which is < 100 */

    result = GenMemOpsCheckBounds(USIZE_C(100), MAX_USIZE - USIZE_C(5), USIZE_C(10));
    assert(result == false);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    ValidBounds();
    InvalidBounds();
    ZeroSizeEdgeCases();
    IntegerOverflow();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
