/**
 * @file kdGenMemOpsReverseBytesRange.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsReverseBytesRange function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsReverseBytesRange function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


static void
kdi_FillSeq(u8 *dst, usize sz, u8 start)
{
    usize i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        dst[i] = (u8)(start + (u8)i);
    }
}


void
BasicArguments(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* base is null -> failure */
    status = GenMemOpsReverseBytesRange(null, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = GenMemOpsReverseBytesRange(buf, USIZE_C(0), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* count is zero -> success (trivial, nothing changes) */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));
    status = GenMemOpsReverseBytesRange(buf, USIZE_C(16), USIZE_C(0), USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    assert(buf[0] == U8_C(0x00));

    printf("PASSED\n");
}


void
CountClamping(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "CountClamping -> ");

    /* Init: 0x00 ... 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Request reverse starting at 12, count 10.
     * Available: 16 - 12 = 4 bytes (indices 12, 13, 14, 15).
     * Should reverse those 4 bytes.
     * Values at 12..15: 0x0C, 0x0D, 0x0E, 0x0F
     * Expected: 0x0F, 0x0E, 0x0D, 0x0C
     */
    status = GenMemOpsReverseBytesRange(buf, USIZE_C(16), USIZE_C(12), USIZE_C(10));

    assert(status == RESULT_SUCCESS);

    /* Check reversed part */
    assert(buf[12] == U8_C(0x0F));
    assert(buf[13] == U8_C(0x0E));
    assert(buf[14] == U8_C(0x0D));
    assert(buf[15] == U8_C(0x0C));

    /* Check untouched part (index 11) */
    assert(buf[11] == U8_C(0x0B));

    printf("PASSED\n");
}


void
IndicesOutOfBounds(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "IndicesOutOfBounds -> ");

    /* begin_idx >= base_sz -> failure */
    status = GenMemOpsReverseBytesRange(buf, USIZE_C(16), USIZE_C(16), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
RangeReverse(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "RangeReverse -> ");

    /* Init: 0x00 ... 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Reverse middle: start 5, count 4 (indices 5, 6, 7, 8) */
    /* Values: 05, 06, 07, 08 */
    /* Expect: 08, 07, 06, 05 */
    status = GenMemOpsReverseBytesRange(buf, USIZE_C(16), USIZE_C(5), USIZE_C(4));

    assert(status == RESULT_SUCCESS);

    /* Verify Pre-range */
    assert(buf[4] == U8_C(0x04));

    /* Verify Range */
    assert(buf[5] == U8_C(0x08));
    assert(buf[6] == U8_C(0x07));
    assert(buf[7] == U8_C(0x06));
    assert(buf[8] == U8_C(0x05));

    /* Verify Post-range */
    assert(buf[9] == U8_C(0x09));

    printf("PASSED\n");
}


void
FullBuffer(void)
{
    u8   buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "FullBuffer -> ");

    /* Equivalent to full reverse */
    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x01)); /* 1, 2, 3, 4 */

    status = GenMemOpsReverseBytesRange(buf, USIZE_C(4), USIZE_C(0), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(buf[0] == U8_C(0x04));
    assert(buf[3] == U8_C(0x01));

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    CountClamping();
    IndicesOutOfBounds();
    RangeReverse();
    FullBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
