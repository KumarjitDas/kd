/**
 * @file kdGenMemOpsReplaceLastByteRange.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsReplaceLastByteRange function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsReplaceLastByteRange function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


static void
kdi_FillVal(u8 *dst, usize sz, u8 val)
{
    usize i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        dst[i] = val;
    }
}


void
BasicArguments(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* base is null -> failure */
    status = GenMemOpsReplaceLastByteRange(null, USIZE_C(16), 0, 16, U8_C(0), U8_C(1));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = GenMemOpsReplaceLastByteRange(buf, USIZE_C(0), 0, 0, U8_C(0), U8_C(1));
    assert(status == RESULT_FAILURE);

    /* begin > end -> failure */
    status = GenMemOpsReplaceLastByteRange(buf, USIZE_C(16), 10, 5, U8_C(0), U8_C(1));
    assert(status == RESULT_FAILURE);

    /* end > base_sz -> failure */
    status = GenMemOpsReplaceLastByteRange(buf, USIZE_C(16), 0, 17, U8_C(0), U8_C(1));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ReplaceNone(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ReplaceNone -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Search range [0, 16). Try to find 0xFF. */
    status = GenMemOpsReplaceLastByteRange(buf, USIZE_C(16), 0, 16, U8_C(0xFF), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);

    /* Verify unchanged */
    {
        usize i;
        for (i = 0; i < 16; ++i)
        {
            assert(buf[i] == 0x00);
        }
    }

    printf("PASSED\n");
}


void
RangeConstraints(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "RangeConstraints -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Set targets at 2, 5, 8, 12 */
    buf[2]  = 0xFF;
    buf[5]  = 0xFF;
    buf[8]  = 0xFF;
    buf[12] = 0xFF;

    /* Range [4, 10). Should see indices 5 and 8.
     * Logic replaces LAST occurrence in range.
     * Should replace index 8.
     * Index 2 (before range) ignored.
     * Index 5 (inside but not last) ignored.
     * Index 12 (after range) ignored.
     */
    status  = GenMemOpsReplaceLastByteRange(buf, USIZE_C(16), 4, 10, U8_C(0xFF), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);

    assert(buf[8] == 0xAA);  /* Replaced */
    assert(buf[5] == 0xFF);  /* Untouched (Previous match) */
    assert(buf[2] == 0xFF);  /* Untouched (Out of range) */
    assert(buf[12] == 0xFF); /* Untouched (Out of range) */

    printf("PASSED\n");
}


void
ReplaceAtRangeBoundaries(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ReplaceAtRangeBoundaries -> ");

    /* Case 1: Target at 'begin' */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));
    buf[4] = 0xFF;

    /* Range [4, 8). Only one occurrence at start. */
    status = GenMemOpsReplaceLastByteRange(buf, USIZE_C(16), 4, 8, U8_C(0xFF), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(buf[4] == 0xAA);

    /* Case 2: Target just before 'end' */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));
    buf[7] = 0xFF;

    /* Range [4, 8). Last valid index is 7. */
    status = GenMemOpsReplaceLastByteRange(buf, USIZE_C(16), 4, 8, U8_C(0xFF), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(buf[7] == 0xAA);

    /* Case 3: Multiple inside, one at end boundary */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));
    buf[5] = 0xFF;
    buf[7] = 0xFF;

    /* Range [4, 8). Should replace 7 (Last). */
    status = GenMemOpsReplaceLastByteRange(buf, USIZE_C(16), 4, 8, U8_C(0xFF), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(buf[7] == 0xAA);
    assert(buf[5] == 0xFF);

    printf("PASSED\n");
}


void
ReplaceSameValue(void)
{
    u8   buf[8];
    bool status;

    printf(LOG_PREFIX_CSTR "ReplaceSameValue -> ");

    kdi_FillVal(buf, USIZE_C(8), U8_C(0x00));
    buf[6] = 0x55;

    /* Range [0, 8). Replace 0x55 with 0x55. */
    status = GenMemOpsReplaceLastByteRange(buf, USIZE_C(8), 0, 8, U8_C(0x55), U8_C(0x55));

    assert(status == RESULT_SUCCESS);
    assert(buf[6] == 0x55);

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    static u8 buf[2000];
    bool      status;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    kdi_FillVal(buf, USIZE_C(2000), U8_C(0x00));

    /* Targets at 100, 1000, 1499, 1999 */
    buf[100]  = 0x77;
    buf[1000] = 0x77;
    buf[1499] = 0x77;
    buf[1999] = 0x77;

    /* Range [500, 1500).
     * Includes 1000.
     * Includes 1499.
     * Should replace 1499 (Last in range).
     */
    status    = GenMemOpsReplaceLastByteRange(buf, USIZE_C(2000), 500, 1500, U8_C(0x77), U8_C(0x88));

    assert(status == RESULT_SUCCESS);

    /* Verify 1499 changed */
    assert(buf[1499] == 0x88);

    /* Verify 1000 unchanged */
    assert(buf[1000] == 0x77);

    /* Verify outside range unchanged */
    assert(buf[100] == 0x77);
    assert(buf[1999] == 0x77);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    ReplaceNone();
    RangeConstraints();
    ReplaceAtRangeBoundaries();
    ReplaceSameValue();
    LargeBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
