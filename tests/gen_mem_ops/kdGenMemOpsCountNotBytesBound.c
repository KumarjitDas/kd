/**
 * @file kdGenMemOpsCountNotBytesBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsCountNotBytesBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsCountNotBytesBound function test"
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
    usize count = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* count pointer is null -> failure */
    status = GenMemOpsCountNotBytesBound(null, buf, USIZE_C(16), 0, 16, U8_C(0));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure */
    status = GenMemOpsCountNotBytesBound(&count, null, USIZE_C(16), 0, 16, U8_C(0));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = GenMemOpsCountNotBytesBound(&count, buf, USIZE_C(0), 0, 16, U8_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
EndValueClamping(void)
{
    u8    buf[16];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "EndValueClamping -> ");

    /* Fill with 0xAA (Match) */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Set mismatch at last index 15 */
    buf[15] = 0xBB;

    /* Requesting 100 bytes starting at 0.
     * Clamps to 16. Range [0, 16).
     * Counting NOT 0xAA.
     */
    status  = GenMemOpsCountNotBytesBound(&count, buf, USIZE_C(16), 0, 100, U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    /* Should count the 1 mismatch at index 15 */
    assert(count == 1);

    printf("PASSED\n");
}


void
CountNone(void)
{
    u8    buf[16];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountNone -> ");

    /* Fill with 0xAA */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Search for NOT 0xAA.
     * All are 0xAA, so mismatch count is 0.
     */
    status = GenMemOpsCountNotBytesBound(&count, buf, USIZE_C(16), 0, 16, U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(count == 0);

    printf("PASSED\n");
}


void
CountAll(void)
{
    u8    buf[16];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountAll -> ");

    /* Fill with 0xBB */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xBB));

    /* Search for NOT 0xAA.
     * All are 0xBB, so all are mismatches.
     */
    status = GenMemOpsCountNotBytesBound(&count, buf, USIZE_C(16), 0, 16, U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(count == 16);

    printf("PASSED\n");
}


void
RangeConstraints(void)
{
    u8    buf[16];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "RangeConstraints -> ");

    /* Fill with 0xAA (Match) */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Set mismatches (NOT 0xAA) at 2, 5, 8, 12 */
    buf[2]  = 0xBB;
    buf[5]  = 0xBB;
    buf[8]  = 0xBB;
    buf[12] = 0xBB;

    /* Start 4, Count 6. Range [4, 10).
     * Indices inside: 4, 5, 6, 7, 8, 9.
     * Mismatches inside: 5, 8.
     * Total 2.
     */
    status  = GenMemOpsCountNotBytesBound(&count, buf, USIZE_C(16), 4, 6, U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(count == 2);

    printf("PASSED\n");
}


void
CountAtBoundaries(void)
{
    u8    buf[16];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountAtBoundaries -> ");

    /* Fill with 0xAA (Match) */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Mismatches */
    buf[4] = 0xBB; /* At start of range */
    buf[7] = 0xBB; /* At end of range */
    buf[8] = 0xBB; /* Outside range */

    /* Range [4, 8) */
    status = GenMemOpsCountNotBytesBound(&count, buf, USIZE_C(16), 4, 4, U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(count == 2); /* 4 and 7 */

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    static u8 buf[2000];
    usize     count;
    bool      status;
    usize     i;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    /* Fill with 0x00 */
    kdi_FillVal(buf, USIZE_C(2000), U8_C(0x00));

    /* Fill every 10th byte with 0x77 (Mismatch) */
    for (i = 0; i < 2000; i += 10)
    {
        buf[i] = 0x77;
    }

    /* Start 500, Count 1000. Range [500, 1500).
     * Counting NOT 0x00.
     * Indices 500, 510... 1490 are mismatches.
     * Total 100 matches.
     */
    status = GenMemOpsCountNotBytesBound(&count, buf, USIZE_C(2000), 500, 1000, U8_C(0x00));

    assert(status == RESULT_SUCCESS);
    assert(count == 100);

    /* Start 1900, Count 500. Range [1900, 2000) (Clamped).
     * Indices 1900, 1910... 1990. 10 matches.
     */
    status = GenMemOpsCountNotBytesBound(&count, buf, USIZE_C(2000), 1900, 500, U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == 10);

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
    CountNone();
    CountAll();
    RangeConstraints();
    CountAtBoundaries();
    LargeBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
