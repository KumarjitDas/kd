/**
 * @file kdGenMemOpsFindNotByteIndexBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindNotByteIndexBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindNotByteIndexBound function test"
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
    u8    buf[16];
    usize idx = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* idx pointer is null -> failure */
    status = GenMemOpsFindNotByteIndexBound(null, buf, USIZE_C(16), 0, 16, U8_C(0));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure */
    status = GenMemOpsFindNotByteIndexBound(&idx, null, USIZE_C(16), 0, 16, U8_C(0));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = GenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(0), 0, 16, U8_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
EndValueClamping(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "EndValueClamping -> ");

    /* Fill with 0xAA */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Set mismatch at last index 15 */
    buf[15] = 0xBB;

    /* Requesting 100 bytes starting at 0.
     * 'end_count' is 100. Base size is 16.
     * Logic should clamp the search to 16.
     * Effective Range: [0, 16).
     */
    status  = GenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(16), 0, 100, U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    /* Should find the mismatch at 15 */
    assert(idx == 15);

    printf("PASSED\n");
}


void
AllMatch(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "AllMatch -> ");

    /* Fill with 0xAA */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Range [0, 16). Search for NOT 0xAA.
     * All are 0xAA. Should fail to find any mismatch.
     */
    status = GenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(16), 0, 16, U8_C(0xAA));

    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
RangeConstraints(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "RangeConstraints -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Mismatches at 2, 5, 8, 12 */
    buf[2]  = 0xBB;
    buf[5]  = 0xBB;
    buf[8]  = 0xBB;
    buf[12] = 0xBB;

    /* Start 4, Count 6.
     * Effective Range: [4, 10).
     * Should find index 5 (First mismatch in range).
     * Index 2 (before) ignored.
     * Index 12 (after) ignored.
     */
    status  = GenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(16), 4, 6, U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(idx == 5);

    printf("PASSED\n");
}


void
FindNotAtBoundaries(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNotAtBoundaries -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Mismatch at start of range (4) */
    buf[4] = 0xBB;

    /* Range [4, 8) */
    status = GenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(16), 4, 4, U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == 4);

    /* Reset buffer */
    buf[4] = 0xAA;

    /* Mismatch at end of range (7) */
    buf[7] = 0xBB;

    /* Range [4, 8) */
    status = GenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(16), 4, 4, U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == 7);

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    static u8 buf[2000];
    usize     idx;
    bool      status;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    /* Fill with 0x00 */
    kdi_FillVal(buf, USIZE_C(2000), U8_C(0x00));

    /* Set mismatch at 1500 */
    buf[1500] = 0xFF;

    /* Start 500, Count 1100. Range [500, 1600).
     * 1500 is inside.
     */
    status    = GenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(2000), 500, 1100, U8_C(0x00));

    assert(status == RESULT_SUCCESS);
    assert(idx == 1500);

    /* Test Clamping: Start 1900, Count 500.
     * Clamps to 2000. Range [1900, 2000).
     * All are 0x00 (match). Should fail to find NOT 0x00.
     */
    status = GenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(2000), 1900, 500, U8_C(0x00));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    EndValueClamping();
    AllMatch();
    RangeConstraints();
    FindNotAtBoundaries();
    LargeBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
