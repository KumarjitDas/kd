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
    result = kdGenMemOpsCheckBounds(USIZE_C(10), USIZE_C(0), USIZE_C(5));
    assert(result == true);

    /* 2. Middle of buffer */
    /* Total: 10, Offset: 2, Size: 5 -> Valid (ends at 7) */
    result = kdGenMemOpsCheckBounds(USIZE_C(10), USIZE_C(2), USIZE_C(5));
    assert(result == true);

    /* 3. Exact fit */
    /* Total: 10, Offset: 5, Size: 5 -> Valid (ends at 10) */
    result = kdGenMemOpsCheckBounds(USIZE_C(10), USIZE_C(5), USIZE_C(5));
    assert(result == true);

    /* 4. Full buffer */
    /* Total: 10, Offset: 0, Size: 10 -> Valid */
    result = kdGenMemOpsCheckBounds(USIZE_C(10), USIZE_C(0), USIZE_C(10));
    assert(result == true);

    /* 5. Near end of buffer */
    /* Total: 100, Offset: 95, Size: 5 -> Valid (ends at 100) */
    result = kdGenMemOpsCheckBounds(USIZE_C(100), USIZE_C(95), USIZE_C(5));
    assert(result == true);

    /* 6. Single byte at start */
    /* Total: 10, Offset: 0, Size: 1 -> Valid */
    result = kdGenMemOpsCheckBounds(USIZE_C(10), USIZE_C(0), USIZE_C(1));
    assert(result == true);

    /* 7. Single byte at end */
    /* Total: 10, Offset: 9, Size: 1 -> Valid (ends at 10) */
    result = kdGenMemOpsCheckBounds(USIZE_C(10), USIZE_C(9), USIZE_C(1));
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
    result = kdGenMemOpsCheckBounds(USIZE_C(10), USIZE_C(11), USIZE_C(1));
    assert(result == false);

    /* 2. Offset == Total (Size > 0) */
    /* Total: 10, Offset: 10, Size: 1 -> Invalid */
    result = kdGenMemOpsCheckBounds(USIZE_C(10), USIZE_C(10), USIZE_C(1));
    assert(result == false);

    /* 3. Offset valid, Size too large */
    /* Total: 10, Offset: 0, Size: 11 -> Invalid */
    result = kdGenMemOpsCheckBounds(USIZE_C(10), USIZE_C(0), USIZE_C(11));
    assert(result == false);

    /* 4. Offset valid, Range exceeds total */
    /* Total: 10, Offset: 8, Size: 3 -> Invalid (ends at 11) */
    result = kdGenMemOpsCheckBounds(USIZE_C(10), USIZE_C(8), USIZE_C(3));
    assert(result == false);

    /* 5. Offset far beyond total */
    /* Total: 10, Offset: 100, Size: 1 -> Invalid */
    result = kdGenMemOpsCheckBounds(USIZE_C(10), USIZE_C(100), USIZE_C(1));
    assert(result == false);

    /* 6. Size far beyond total */
    /* Total: 10, Offset: 0, Size: 100 -> Invalid */
    result = kdGenMemOpsCheckBounds(USIZE_C(10), USIZE_C(0), USIZE_C(100));
    assert(result == false);

    /* 7. Offset and Size both moderate but sum exceeds */
    /* Total: 10, Offset: 6, Size: 5 -> Invalid (ends at 11) */
    result = kdGenMemOpsCheckBounds(USIZE_C(10), USIZE_C(6), USIZE_C(5));
    assert(result == false);

    printf("PASSED\n");
}


void
ZeroSizeEdgeCases(void)
{
    bool result;

    printf(LOG_PREFIX_CSTR "ZeroSizeEdgeCases -> ");

    /* 1. Size is 0, Offset inside -> Invalid */
    /* Total: 10, Offset: 5, Size: 0 */
    result = kdGenMemOpsCheckBounds(USIZE_C(10), USIZE_C(5), USIZE_C(0));
    assert(result == false);

    /* 2. Size is 0, Offset at end -> Invalid */
    /* Total: 10, Offset: 10, Size: 0 */
    result = kdGenMemOpsCheckBounds(USIZE_C(10), USIZE_C(10), USIZE_C(0));
    assert(result == false);

    /* 3. Size is 0, Offset beyond end -> Invalid */
    /* Total: 10, Offset: 11, Size: 0 */
    result = kdGenMemOpsCheckBounds(USIZE_C(10), USIZE_C(11), USIZE_C(0));
    assert(result == false);

    /* 4. Size is 0, Offset at start -> Invalid */
    /* Total: 10, Offset: 0, Size: 0 */
    result = kdGenMemOpsCheckBounds(USIZE_C(10), USIZE_C(0), USIZE_C(0));
    assert(result == false);

    /* 5. All zeros -> Invalid (cannot have zero total) */
    /* Total: 0, Offset: 0, Size: 0 */
    result = kdGenMemOpsCheckBounds(USIZE_C(0), USIZE_C(0), USIZE_C(0));
    assert(result == false);

    printf("PASSED\n");
}


void
ZeroTotalSize(void)
{
    bool result;

    printf(LOG_PREFIX_CSTR "ZeroTotalSize -> ");

    /* Total is 0, Offset is 0, Size is 0 -> Invalid (zero total not allowed) */
    result = kdGenMemOpsCheckBounds(USIZE_C(0), USIZE_C(0), USIZE_C(0));
    assert(result == false);

    /* Total is 0, Offset is 0, Size > 0 -> Invalid */
    result = kdGenMemOpsCheckBounds(USIZE_C(0), USIZE_C(0), USIZE_C(1));
    assert(result == false);

    /* Total is 0, Offset > 0, Size is 0 -> Invalid */
    result = kdGenMemOpsCheckBounds(USIZE_C(0), USIZE_C(1), USIZE_C(0));
    assert(result == false);

    /* Total is 0, Offset > 0, Size > 0 -> Invalid */
    result = kdGenMemOpsCheckBounds(USIZE_C(0), USIZE_C(1), USIZE_C(1));
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

    result = kdGenMemOpsCheckBounds(USIZE_C(100), MAX_USIZE - USIZE_C(5), USIZE_C(10));
    assert(result == false);

    /* Offset + Size = exactly MAX_USIZE + 1 (wraps to 0) */
    /* Total: 100, Offset: MAX_USIZE, Size: 1 */
    result = kdGenMemOpsCheckBounds(USIZE_C(100), MAX_USIZE, USIZE_C(1));
    assert(result == false);

    /* Both Offset and Size are large, sum wraps */
    /* Total: 1000, Offset: MAX_USIZE / 2, Size: MAX_USIZE / 2 + 100 */
    result = kdGenMemOpsCheckBounds(USIZE_C(1000), MAX_USIZE / USIZE_C(2), MAX_USIZE / USIZE_C(2) + USIZE_C(100));
    assert(result == false);

    /* Offset is MAX_USIZE, Size is 0 -> Invalid (offset beyond any valid range) */
    result = kdGenMemOpsCheckBounds(USIZE_C(100), MAX_USIZE, USIZE_C(0));
    assert(result == false);

    printf("PASSED\n");
}


void
LargeValidValues(void)
{
    bool result;

    printf(LOG_PREFIX_CSTR "LargeValidValues -> ");

    /* Large total, valid access near the end */
    /* Total: MAX_USIZE, Offset: MAX_USIZE - 100, Size: 50 -> Valid */
    result = kdGenMemOpsCheckBounds(MAX_USIZE, MAX_USIZE - USIZE_C(100), USIZE_C(50));
    assert(result == true);

    /* Large total, valid access at the very end */
    /* Total: MAX_USIZE, Offset: MAX_USIZE - 1, Size: 1 -> Valid */
    result = kdGenMemOpsCheckBounds(MAX_USIZE, MAX_USIZE - USIZE_C(1), USIZE_C(1));
    assert(result == true);

    /* Full range of MAX_USIZE */
    /* Total: MAX_USIZE, Offset: 0, Size: MAX_USIZE -> Valid */
    result = kdGenMemOpsCheckBounds(MAX_USIZE, USIZE_C(0), MAX_USIZE);
    assert(result == true);

    /* Large total, access in the middle */
    /* Total: MAX_USIZE / 2, Offset: MAX_USIZE / 4, Size: MAX_USIZE / 8 -> Valid */
    result = kdGenMemOpsCheckBounds(MAX_USIZE / USIZE_C(2), MAX_USIZE / USIZE_C(4), MAX_USIZE / USIZE_C(8));
    assert(result == true);

    printf("PASSED\n");
}


void
LargeInvalidValues(void)
{
    bool result;

    printf(LOG_PREFIX_CSTR "LargeInvalidValues -> ");

    /* Large total, invalid access beyond end */
    /* Total: MAX_USIZE, Offset: MAX_USIZE - 10, Size: 20 -> Invalid */
    result = kdGenMemOpsCheckBounds(MAX_USIZE, MAX_USIZE - USIZE_C(10), USIZE_C(20));
    assert(result == false);

    /* Offset at MAX_USIZE (beyond any buffer) */
    /* Total: MAX_USIZE, Offset: MAX_USIZE, Size: 1 -> Invalid */
    result = kdGenMemOpsCheckBounds(MAX_USIZE, MAX_USIZE, USIZE_C(1));
    assert(result == false);

    /* Size is MAX_USIZE, but offset is non-zero */
    /* Total: MAX_USIZE, Offset: 1, Size: MAX_USIZE -> Invalid (wraps) */
    result = kdGenMemOpsCheckBounds(MAX_USIZE, USIZE_C(1), MAX_USIZE);
    assert(result == false);

    /* Large offset and size combination */
    /* Total: MAX_USIZE / 2, Offset: MAX_USIZE / 2, Size: 1 -> Invalid */
    result = kdGenMemOpsCheckBounds(MAX_USIZE / USIZE_C(2), MAX_USIZE / USIZE_C(2), USIZE_C(1));
    assert(result == false);

    printf("PASSED\n");
}


void
BoundaryConditions(void)
{
    bool result;

    printf(LOG_PREFIX_CSTR "BoundaryConditions -> ");

    /* Offset + Size = Total exactly -> Valid */
    /* Total: 100, Offset: 50, Size: 50 */
    result = kdGenMemOpsCheckBounds(USIZE_C(100), USIZE_C(50), USIZE_C(50));
    assert(result == true);

    /* Offset + Size = Total + 1 -> Invalid */
    /* Total: 100, Offset: 50, Size: 51 */
    result = kdGenMemOpsCheckBounds(USIZE_C(100), USIZE_C(50), USIZE_C(51));
    assert(result == false);

    /* Offset = Total - 1, Size = 1 -> Valid */
    /* Total: 100, Offset: 99, Size: 1 */
    result = kdGenMemOpsCheckBounds(USIZE_C(100), USIZE_C(99), USIZE_C(1));
    assert(result == true);

    /* Offset = Total - 1, Size = 2 -> Invalid */
    /* Total: 100, Offset: 99, Size: 2 */
    result = kdGenMemOpsCheckBounds(USIZE_C(100), USIZE_C(99), USIZE_C(2));
    assert(result == false);

    /* Offset = 0, Size = Total -> Valid */
    /* Total: 100, Offset: 0, Size: 100 */
    result = kdGenMemOpsCheckBounds(USIZE_C(100), USIZE_C(0), USIZE_C(100));
    assert(result == true);

    /* Offset = 0, Size = Total + 1 -> Invalid */
    /* Total: 100, Offset: 0, Size: 101 */
    result = kdGenMemOpsCheckBounds(USIZE_C(100), USIZE_C(0), USIZE_C(101));
    assert(result == false);

    printf("PASSED\n");
}


void
CommonUseCases(void)
{
    bool result;

    printf(LOG_PREFIX_CSTR "CommonUseCases -> ");

    /* Array bounds check: accessing element at index */
    /* Array of 10 elements, each 4 bytes, accessing element 5 */
    /* Total: 40, Offset: 20 (5*4), Size: 4 */
    result = kdGenMemOpsCheckBounds(USIZE_C(40), USIZE_C(20), USIZE_C(4));
    assert(result == true);

    /* Array bounds check: accessing last element */
    /* Total: 40, Offset: 36 (9*4), Size: 4 */
    result = kdGenMemOpsCheckBounds(USIZE_C(40), USIZE_C(36), USIZE_C(4));
    assert(result == true);

    /* Array bounds check: accessing beyond last element */
    /* Total: 40, Offset: 40 (10*4), Size: 4 */
    result = kdGenMemOpsCheckBounds(USIZE_C(40), USIZE_C(40), USIZE_C(4));
    assert(result == false);

    /* String buffer check: reading substring */
    /* Buffer of 256 bytes, reading 10 bytes starting at offset 100 */
    result = kdGenMemOpsCheckBounds(USIZE_C(256), USIZE_C(100), USIZE_C(10));
    assert(result == true);

    /* Packet buffer check: reading header */
    /* Packet of 1500 bytes, reading 20-byte header at start */
    result = kdGenMemOpsCheckBounds(USIZE_C(1500), USIZE_C(0), USIZE_C(20));
    assert(result == true);

    /* Memory region check: mapping a page */
    /* Total: 4096 (page size), Offset: 0, Size: 4096 */
    result = kdGenMemOpsCheckBounds(USIZE_C(4096), USIZE_C(0), USIZE_C(4096));
    assert(result == true);

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
    ZeroTotalSize();
    IntegerOverflow();
    LargeValidValues();
    LargeInvalidValues();
    BoundaryConditions();
    CommonUseCases();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
