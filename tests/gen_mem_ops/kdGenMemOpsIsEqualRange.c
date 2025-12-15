/**
 * @file kdGenMemOpsIsEqualRange.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsIsEqualRange function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsIsEqualRange function test"
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
    u8   buf1[16];
    u8   buf2[16];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillSeq(buf1, USIZE_C(16), U8_C(0x10));
    kdi_FillSeq(buf2, USIZE_C(16), U8_C(0x10));

    /* result pointer is null -> failure */
    status = GenMemOpsIsEqualRange(null, buf1, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_1 is null -> failure */
    status = GenMemOpsIsEqualRange(&is_equal, null, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_2 is null -> failure */
    status = GenMemOpsIsEqualRange(&is_equal, buf1, USIZE_C(16), USIZE_C(0), null, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_1_sz is zero -> failure */
    status = GenMemOpsIsEqualRange(&is_equal, buf1, USIZE_C(0), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_2_sz is zero -> failure */
    status = GenMemOpsIsEqualRange(&is_equal, buf1, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(0), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* byte_count is zero -> success (trivial equality) */
    is_equal = RESULT_NOT_EQUALS; /* reset */
    status   = GenMemOpsIsEqualRange(&is_equal, buf1, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == RESULT_EQUALS);

    printf("PASSED\n");
}


void
CountClamping(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "CountClamping -> ");

    /* Fill buffers with identical data */
    kdi_FillSeq(buf1, USIZE_C(16), U8_C(0x00));
    kdi_FillSeq(buf2, USIZE_C(16), U8_C(0x00));

    /* * Request 10 bytes starting from index 14.
     * buf1: 16 - 14 = 2 bytes available.
     * buf2: 16 - 14 = 2 bytes available.
     * Clamped count = 2.
     * Content matches at 14 and 15.
     */
    is_equal = RESULT_NOT_EQUALS;
    status   = GenMemOpsIsEqualRange(&is_equal, buf1, USIZE_C(16), USIZE_C(14), buf2, USIZE_C(16), USIZE_C(14), USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(is_equal == RESULT_EQUALS);

    /* * Asymmetric Clamping
     * Request 10 bytes.
     * buf1 start 14 (2 bytes avail: 14, 15).
     * buf2 start 0  (16 bytes avail).
     * Common intersection = 2 bytes.
     * Compare buf1[14..15] with buf2[0..1].
     * buf1[14]=0x0E, buf2[0]=0x00 -> Mismatch.
     */
    is_equal = RESULT_EQUALS;
    status   = GenMemOpsIsEqualRange(&is_equal, buf1, USIZE_C(16), USIZE_C(14), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(is_equal == RESULT_NOT_EQUALS);

    printf("PASSED\n");
}


void
IndicesOutOfBounds(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "IndicesOutOfBounds -> ");

    /* base_1_idx >= base_1_sz */
    status = GenMemOpsIsEqualRange(&is_equal, buf1, USIZE_C(16), USIZE_C(16), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_2_idx >= base_2_sz */
    status = GenMemOpsIsEqualRange(&is_equal, buf1, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(16), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
RangesMatch(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "RangesMatch -> ");

    /* Fill identical sequences */
    kdi_FillSeq(buf1, USIZE_C(16), U8_C(0x10));
    kdi_FillSeq(buf2, USIZE_C(16), U8_C(0x10));

    /* Identical ranges */
    is_equal = RESULT_NOT_EQUALS;
    status   = GenMemOpsIsEqualRange(&is_equal, buf1, USIZE_C(16), USIZE_C(4), buf2, USIZE_C(16), USIZE_C(4), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(is_equal == RESULT_EQUALS);

    /* Different indices, but content happens to match (e.g. if we filled with const value) */
    /* Let's verify mismatch for seq pattern: buf1[4]=0x14, buf2[5]=0x15 -> Mismatch */
    is_equal = RESULT_EQUALS;
    status   = GenMemOpsIsEqualRange(&is_equal, buf1, USIZE_C(16), USIZE_C(4), buf2, USIZE_C(16), USIZE_C(5), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(is_equal == RESULT_NOT_EQUALS);

    printf("PASSED\n");
}


void
RangesDoNotMatch(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "RangesDoNotMatch -> ");

    kdi_FillSeq(buf1, USIZE_C(16), U8_C(0x10));
    kdi_FillSeq(buf2, USIZE_C(16), U8_C(0x10));

    /* Create mismatch in buf2 at index 6 */
    buf2[6]  = U8_C(0xFF);

    /* Compare range [4..7] (size 4) */
    is_equal = RESULT_EQUALS;
    status   = GenMemOpsIsEqualRange(&is_equal, buf1, USIZE_C(16), USIZE_C(4), buf2, USIZE_C(16), USIZE_C(4), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(is_equal == RESULT_NOT_EQUALS);

    /* Compare range [0..3] (size 4) -> Should match (before dirty byte) */
    is_equal = RESULT_NOT_EQUALS;
    status   = GenMemOpsIsEqualRange(&is_equal, buf1, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(is_equal == RESULT_EQUALS);

    printf("PASSED\n");
}


void
OverlappingRangesSameBuffer(void)
{
    u8   buf[16];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "OverlappingRangesSameBuffer -> ");

    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00)); /* 0, 1, 2, 3... */

    /* Compare index 0 vs index 0 (identity) */
    is_equal = RESULT_NOT_EQUALS;
    status   = GenMemOpsIsEqualRange(&is_equal, buf, USIZE_C(16), USIZE_C(0), buf, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == RESULT_EQUALS);

    /* Compare index 0 vs index 1 (0,1,2,3 vs 1,2,3,4) -> Not Equal */
    is_equal = RESULT_EQUALS;
    status   = GenMemOpsIsEqualRange(&is_equal, buf, USIZE_C(16), USIZE_C(0), buf, USIZE_C(16), USIZE_C(1), USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == RESULT_NOT_EQUALS);

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
    RangesMatch();
    RangesDoNotMatch();
    OverlappingRangesSameBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
