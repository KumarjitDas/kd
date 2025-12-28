/**
 * @file kdGenMemOpsIsBytesBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsIsBytesBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsIsBytesBound function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8   buf[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));

    /* result pointer is null -> failure */
    status = kdGenMemOpsIsBytesBound(null, buf, USIZE_C(16), USIZE_C(0), USIZE_C(4), U8_C(0xAA));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure */
    status = kdGenMemOpsIsBytesBound(&result, null, USIZE_C(16), USIZE_C(0), USIZE_C(4), U8_C(0xAA));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(0), USIZE_C(0), USIZE_C(4), U8_C(0xAA));
    assert(status == RESULT_FAILURE);

    /* byte_count is zero -> failure (!byte_count check) */
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(16), USIZE_C(0), USIZE_C(0), U8_C(0xAA));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
BeginIndexOutOfBounds(void)
{
    u8   buf[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "BeginIndexOutOfBounds -> ");

    /* begin_idx >= base_sz */
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(16), USIZE_C(16), USIZE_C(4), U8_C(0xAA));
    assert(status == RESULT_FAILURE);

    /* begin_idx > base_sz */
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(16), USIZE_C(20), USIZE_C(4), U8_C(0xAA));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
RangeIsAllTargetByte_Zeros(void)
{
    u8   buf[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "RangeIsAllTargetByte_Zeros -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Check entire buffer */
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Check sub-range */
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(16), USIZE_C(4), USIZE_C(8), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
RangeIsAllTargetByte_Ones(void)
{
    u8   buf[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "RangeIsAllTargetByte_Ones -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xFF));

    /* Check entire buffer */
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Check sub-range */
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(16), USIZE_C(5), USIZE_C(7), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
RangeIsAllTargetByte_CustomValue(void)
{
    u8   buf[32];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "RangeIsAllTargetByte_CustomValue -> ");

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x42));

    /* Check entire buffer */
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), U8_C(0x42));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Check sub-range */
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(32), USIZE_C(10), USIZE_C(15), U8_C(0x42));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
RangeIsNotAllTargetByte_DifferentAtStart(void)
{
    u8   buf[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "RangeIsNotAllTargetByte_DifferentAtStart -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));

    /* Set first byte of range to different value */
    buf[4] = U8_C(0xBB);

    result = true;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(16), USIZE_C(4), USIZE_C(8), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
RangeIsNotAllTargetByte_DifferentAtEnd(void)
{
    u8   buf[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "RangeIsNotAllTargetByte_DifferentAtEnd -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));

    /* Set last byte of range to different value (range is [4..11]) */
    buf[11] = U8_C(0xBB);

    result = true;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(16), USIZE_C(4), USIZE_C(8), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
RangeIsNotAllTargetByte_DifferentAtMiddle(void)
{
    u8   buf[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "RangeIsNotAllTargetByte_DifferentAtMiddle -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));

    /* Set middle byte of range to different value */
    buf[8] = U8_C(0xBB);

    result = true;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(16), USIZE_C(4), USIZE_C(8), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
SingleByte_Match(void)
{
    u8   buf[8];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "SingleByte_Match -> ");

    kdi_FillSeq_u8(buf, USIZE_C(8), U8_C(0x00));

    /* Check single byte at index 3 (value 0x03) */
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(8), USIZE_C(3), USIZE_C(1), U8_C(0x03));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
SingleByte_NoMatch(void)
{
    u8   buf[8];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "SingleByte_NoMatch -> ");

    kdi_FillSeq_u8(buf, USIZE_C(8), U8_C(0x00));

    /* Check single byte at index 3 (value 0x03) against 0xFF */
    result = true;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(8), USIZE_C(3), USIZE_C(1), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
CountClamping(void)
{
    u8   buf[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "CountClamping -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x5A));

    /* Request 100 bytes starting from index 14.
     * Available = 16 - 14 = 2 bytes (indices 14, 15).
     * Clamped count = 2.
     * Both bytes are 0x5A, should match.
     */
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(16), USIZE_C(14), USIZE_C(100), U8_C(0x5A));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Modify one of the clamped bytes */
    buf[15] = U8_C(0x5B);

    result = true;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(16), USIZE_C(14), USIZE_C(100), U8_C(0x5A));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
LargeBuffer_AllMatch(void)
{
    u8    buf[256];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffer_AllMatch -> ");

    /* Fill with target byte */
    for (i = 0; i < 256; ++i)
    {
        buf[i] = U8_C(0x7E);
    }

    /* Check large range (200 bytes starting at index 50) */
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(256), USIZE_C(50), USIZE_C(200), U8_C(0x7E));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
LargeBuffer_OneMismatch(void)
{
    u8    buf[256];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffer_OneMismatch -> ");

    /* Fill with target byte */
    for (i = 0; i < 256; ++i)
    {
        buf[i] = U8_C(0x7E);
    }

    /* Change one byte in the range */
    buf[100] = U8_C(0x7F);

    /* Check range that includes the changed byte */
    result = true;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(256), USIZE_C(50), USIZE_C(100), U8_C(0x7E));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
PartialBufferMatch(void)
{
    u8   buf[32];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "PartialBufferMatch -> ");

    /* Fill entire buffer with mixed values */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));
    kdi_Fill_u8(&buf[16], USIZE_C(16), U8_C(0xBB));

    /* Check first half - should match */
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(32), USIZE_C(0), USIZE_C(16), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Check second half - should match */
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(32), USIZE_C(16), USIZE_C(16), U8_C(0xBB));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Check entire buffer against 0xAA - should not match */
    result = true;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
VariousTargetBytes(void)
{
    u8   buf[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "VariousTargetBytes -> ");

    /* Test with 0x00 */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(16), USIZE_C(2), USIZE_C(10), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Test with 0xFF */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xFF));
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(16), USIZE_C(3), USIZE_C(8), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Test with 0x01 */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x01));
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(16), USIZE_C(1), USIZE_C(12), U8_C(0x01));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Test with 0x7F */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x7F));
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0x7F));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Test with 0x80 */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x80));
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(16), USIZE_C(5), USIZE_C(6), U8_C(0x80));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
ArbitraryByteCounts(void)
{
    u8   buf[20];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "ArbitraryByteCounts -> ");

    kdi_Fill_u8(buf, USIZE_C(20), U8_C(0xCC));

    /* Odd byte count (1 byte) */
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(20), USIZE_C(5), USIZE_C(1), U8_C(0xCC));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Odd byte count (3 bytes) */
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(20), USIZE_C(2), USIZE_C(3), U8_C(0xCC));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Odd byte count (5 bytes) */
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(20), USIZE_C(10), USIZE_C(5), U8_C(0xCC));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Odd byte count (7 bytes) */
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(20), USIZE_C(0), USIZE_C(7), U8_C(0xCC));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Non-power-of-2 count (6 bytes) */
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(20), USIZE_C(3), USIZE_C(6), U8_C(0xCC));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Non-power-of-2 count (9 bytes) */
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(20), USIZE_C(1), USIZE_C(9), U8_C(0xCC));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Non-power-of-2 count (11 bytes) */
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(20), USIZE_C(7), USIZE_C(11), U8_C(0xCC));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Odd count with mismatch (3 bytes) */
    buf[8] = U8_C(0xDD);
    result = true;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(20), USIZE_C(7), USIZE_C(3), U8_C(0xCC));
    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
BufferOutsideRange(void)
{
    u8   buf[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "BufferOutsideRange -> ");

    /* Fill buffer with different values in different regions */
    kdi_Fill_u8(&buf[0], USIZE_C(4), U8_C(0xAA));
    kdi_Fill_u8(&buf[4], USIZE_C(8), U8_C(0xBB));
    kdi_Fill_u8(&buf[12], USIZE_C(4), U8_C(0xCC));

    /* Check middle region (should be all 0xBB) */
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(16), USIZE_C(4), USIZE_C(8), U8_C(0xBB));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Verify outside region is not affected */
    assert(buf[0] == U8_C(0xAA));
    assert(buf[3] == U8_C(0xAA));
    assert(buf[12] == U8_C(0xCC));
    assert(buf[15] == U8_C(0xCC));

    printf("PASSED\n");
}


void
ConsecutiveRanges(void)
{
    u8   buf[32];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "ConsecutiveRanges -> ");

    /* Set up buffer with different values in consecutive ranges */
    kdi_Fill_u8(&buf[0], USIZE_C(8), U8_C(0x11));
    kdi_Fill_u8(&buf[8], USIZE_C(8), U8_C(0x22));
    kdi_Fill_u8(&buf[16], USIZE_C(8), U8_C(0x33));
    kdi_Fill_u8(&buf[24], USIZE_C(8), U8_C(0x44));

    /* Check first range */
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(32), USIZE_C(0), USIZE_C(8), U8_C(0x11));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Check second range */
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(32), USIZE_C(8), USIZE_C(8), U8_C(0x22));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Check third range */
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(32), USIZE_C(16), USIZE_C(8), U8_C(0x33));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Check fourth range */
    result = false;
    status = kdGenMemOpsIsBytesBound(&result, buf, USIZE_C(32), USIZE_C(24), USIZE_C(8), U8_C(0x44));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    BeginIndexOutOfBounds();
    RangeIsAllTargetByte_Zeros();
    RangeIsAllTargetByte_Ones();
    RangeIsAllTargetByte_CustomValue();
    RangeIsNotAllTargetByte_DifferentAtStart();
    RangeIsNotAllTargetByte_DifferentAtEnd();
    RangeIsNotAllTargetByte_DifferentAtMiddle();
    SingleByte_Match();
    SingleByte_NoMatch();
    CountClamping();
    LargeBuffer_AllMatch();
    LargeBuffer_OneMismatch();
    PartialBufferMatch();
    VariousTargetBytes();
    ArbitraryByteCounts();
    BufferOutsideRange();
    ConsecutiveRanges();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}