/**
 * @file kdGenMemOpsCountBytesBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsCountBytesBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsCountBytesBound function test"
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
    status = GenMemOpsCountBytesBound(null, buf, USIZE_C(16), 0, 16, U8_C(0));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure */
    status = GenMemOpsCountBytesBound(&count, null, USIZE_C(16), 0, 16, U8_C(0));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = GenMemOpsCountBytesBound(&count, buf, USIZE_C(0), 0, 16, U8_C(0));
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

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Set target at last index 15 */
    buf[15] = 0xFF;

    /* Requesting 100 bytes starting at 0.
     * Clamps to 16. Range [0, 16).
     */
    status  = GenMemOpsCountBytesBound(&count, buf, USIZE_C(16), 0, 100, U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
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

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Search for 0xFF. None exist. */
    status = GenMemOpsCountBytesBound(&count, buf, USIZE_C(16), 0, 16, U8_C(0xFF));

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

    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Search for 0xAA. All exist. */
    status = GenMemOpsCountBytesBound(&count, buf, USIZE_C(16), 0, 16, U8_C(0xAA));

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

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Targets at 2, 5, 8, 12 */
    buf[2]  = 0xFF;
    buf[5]  = 0xFF;
    buf[8]  = 0xFF;
    buf[12] = 0xFF;

    /* Start 4, Count 6. Range [4, 10).
     * Indices inside: 4, 5, 6, 7, 8, 9.
     * Matches at 5 and 8. Total 2.
     */
    status  = GenMemOpsCountBytesBound(&count, buf, USIZE_C(16), 4, 6, U8_C(0xFF));

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

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    buf[4] = 0xFF;
    buf[7] = 0xFF;
    buf[8] = 0xFF; /* Outside */

    /* Range [4, 8) */
    status = GenMemOpsCountBytesBound(&count, buf, USIZE_C(16), 4, 4, U8_C(0xFF));

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

    kdi_FillVal(buf, USIZE_C(2000), U8_C(0x00));

    /* Fill every 10th byte with 0x77 */
    for (i = 0; i < 2000; i += 10)
    {
        buf[i] = 0x77;
    }

    /* Start 500, Count 1000. Range [500, 1500).
     * (1490 - 500) / 10 + 1 = 100 matches.
     */
    status = GenMemOpsCountBytesBound(&count, buf, USIZE_C(2000), 500, 1000, U8_C(0x77));

    assert(status == RESULT_SUCCESS);
    assert(count == 100);

    /* Start 1900, Count 500. Range [1900, 2000) (Clamped).
     * 1900, 1910 ... 1990. 10 matches.
     */
    status = GenMemOpsCountBytesBound(&count, buf, USIZE_C(2000), 1900, 500, U8_C(0x77));
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
