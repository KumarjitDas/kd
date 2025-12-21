/**
 * @file kdGenMemOpsReplaceAllBytesBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsReplaceAllBytesBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsReplaceAllBytesBound function test"
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

    /* base is null -> failure */
    /* Params: base, base_sz, begin_idx, count, count_ptr, find, new */
    status = GenMemOpsReplaceAllBytesBound(null, USIZE_C(16), 0, 16, &count, U8_C(0), U8_C(1));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = GenMemOpsReplaceAllBytesBound(buf, USIZE_C(0), 0, 0, &count, U8_C(0), U8_C(1));
    assert(status == RESULT_FAILURE);

    /* count pointer is null -> failure */
    status = GenMemOpsReplaceAllBytesBound(buf, USIZE_C(16), 0, 16, null, U8_C(0), U8_C(1));
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

    /* Target at last index 15 */
    buf[15] = 0xFF;

    /* Requesting 100 bytes starting at 0.
     * 'end' (count) is 100. Base size is 16.
     * 100 > 16, so it should be clamped to 16.
     * Effective Range: [0, 16).
     */
    status  = GenMemOpsReplaceAllBytesBound(buf, USIZE_C(16), 0, 100, &count, U8_C(0xFF), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);

    /* Should find the item at index 15 */
    assert(count == 1);
    assert(buf[15] == 0xAA);

    printf("PASSED\n");
}


void
ReplaceNone(void)
{
    u8    buf[16];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ReplaceNone -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Start 0, Count 16. Range [0, 16). Try to find 0xFF. */
    status = GenMemOpsReplaceAllBytesBound(buf, USIZE_C(16), 0, 16, &count, U8_C(0xFF), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(count == 0);

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

    /* Start 4, Count 6.
     * Effective Range: [4, 4+6) = [4, 10).
     * Should replace indices 5 and 8.
     * Excludes 2 (before).
     * Excludes 12 (after).
     */
    status  = GenMemOpsReplaceAllBytesBound(buf, USIZE_C(16), 4, 6, &count, U8_C(0xFF), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(count == 2);

    assert(buf[5] == 0xAA);
    assert(buf[8] == 0xAA);

    assert(buf[2] == 0xFF);  /* Untouched */
    assert(buf[12] == 0xFF); /* Untouched */

    printf("PASSED\n");
}


void
ReplaceAtBoundaries(void)
{
    u8    buf[16];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ReplaceAtBoundaries -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    buf[4] = 0xFF; /* At begin */
    buf[7] = 0xFF; /* Just before end of range */
    buf[8] = 0xFF; /* At end of range (Excluded) */

    /* Start 4, Count 4. Range [4, 8). */
    status = GenMemOpsReplaceAllBytesBound(buf, USIZE_C(16), 4, 4, &count, U8_C(0xFF), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(count == 2);

    assert(buf[4] == 0xAA);
    assert(buf[7] == 0xAA);
    assert(buf[8] == 0xFF);

    printf("PASSED\n");
}


void
ReplaceSameValue(void)
{
    u8    buf[8];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ReplaceSameValue -> ");

    kdi_FillVal(buf, USIZE_C(8), U8_C(0x00));
    buf[3] = 0x55;
    buf[5] = 0x55;

    /* Start 0, Count 8. Replace 0x55 with 0x55. */
    status = GenMemOpsReplaceAllBytesBound(buf, USIZE_C(8), 0, 8, &count, U8_C(0x55), U8_C(0x55));

    assert(status == RESULT_SUCCESS);
    assert(count == 2);
    assert(buf[3] == 0x55);
    assert(buf[5] == 0x55);

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
    /* Indices: 0, 10, ... 100, ... 1000 ... 1990 */

    /* Start 500, Count 1000.
     * Range [500, 1500).
     * First included index: 500.
     * Last included index: 1490.
     * (1490 - 500) / 10 + 1 = 990/10 + 1 = 100 items.
     */
    status = GenMemOpsReplaceAllBytesBound(buf, USIZE_C(2000), 500, 1000, &count, U8_C(0x77), U8_C(0x88));

    assert(status == RESULT_SUCCESS);
    assert(count == 100);

    assert(buf[500] == 0x88);
    assert(buf[1490] == 0x88);

    /* Verify boundaries outside */
    assert(buf[490] == 0x77);
    assert(buf[1500] == 0x77);

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
    ReplaceNone();
    RangeConstraints();
    ReplaceAtBoundaries();
    ReplaceSameValue();
    LargeBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
