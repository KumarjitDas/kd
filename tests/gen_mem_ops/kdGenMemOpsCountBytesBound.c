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
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsCountBytesBound function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8    buf[16];
    usize count = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* count pointer is null -> failure */
    status = kdGenMemOpsCountBytesBound(null, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountBytesBound(&count, null, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* begin_idx >= base_sz -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(16), USIZE_C(16), USIZE_C(10), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* end_count is zero -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(16), USIZE_C(0), USIZE_C(0), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* Valid arguments - count all zeros in full range */
    count  = 55;
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

    printf("PASSED\n");
}


void
CountNone(void)
{
    u8    buf[16];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountNone -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Search for 0xFF in range [0, 16) - none exist */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    printf("PASSED\n");
}


void
CountAll(void)
{
    u8    buf[16];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountAll -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));

    /* Search for 0xAA in full range - all match */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

    printf("PASSED\n");
}


void
CountSubrange(void)
{
    u8    buf[20];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountSubrange -> ");

    /* Fill: 0x00 except positions 5, 8, 12, 15 = 0xFF */
    kdi_Fill_u8(buf, USIZE_C(20), U8_C(0x00));
    buf[5]  = 0xFF;
    buf[8]  = 0xFF;
    buf[12] = 0xFF;
    buf[15] = 0xFF;

    /* Range [4, 10) - indices 4,5,6,7,8,9 - matches at 5,8 = 2 */
    status  = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(20), USIZE_C(4), USIZE_C(6), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(2));

    /* Range [10, 18) - indices 10-17 - match at 12,15 = 2 */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(20), USIZE_C(10), USIZE_C(8), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(2));

    /* Range [0, 4) - indices 0,1,2,3 - no matches */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(20), USIZE_C(0), USIZE_C(4), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    printf("PASSED\n");
}


void
ClampedEndCount(void)
{
    u8    buf[16];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ClampedEndCount -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xBB));

    /* Request 100 bytes starting at 0, should clamp to 16 */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(16), USIZE_C(0), USIZE_C(100), U8_C(0xBB));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

    /* Request 20 bytes starting at 10, should clamp to 6 (indices 10-15) */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(16), USIZE_C(10), USIZE_C(20), U8_C(0xBB));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(6));

    printf("PASSED\n");
}


void
SingleByte(void)
{
    u8    buf[16];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleByte -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));
    buf[7] = 0xFF;

    /* Range [7, 8) - single byte match */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(16), USIZE_C(7), USIZE_C(1), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(1));

    /* Range [6, 7) - single byte no match */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(16), USIZE_C(6), USIZE_C(1), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    printf("PASSED\n");
}


void
EdgeIndices(void)
{
    u8    buf[16];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "EdgeIndices -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));
    buf[0]  = 0xFF;
    buf[15] = 0xFF;

    /* Range [0, 1) - first byte only */
    status  = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(16), USIZE_C(0), USIZE_C(1), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(1));

    /* Range [15, 16) - last byte only */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(16), USIZE_C(15), USIZE_C(1), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(1));

    /* Range [0, 16) - both edges */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(2));

    printf("PASSED\n");
}


void
AlternatingPattern(void)
{
    u8    buf[32];
    usize count;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "AlternatingPattern -> ");

    /* Alternating 0xAA, 0x55 */
    for (i = 0; i < 32; ++i)
    {
        buf[i] = (i & 1) ? 0x55 : 0xAA;
    }

    /* Range [0, 32) - count 0xAA (even indices) = 16 */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

    /* Range [5, 15) - indices 5-14 (10 bytes) - 5 are 0xAA (6,8,10,12,14) */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(32), USIZE_C(5), USIZE_C(10), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(5));

    printf("PASSED\n");
}


void
ConsecutiveMatches(void)
{
    u8    buf[32];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ConsecutiveMatches -> ");

    /* First 16 bytes are 0xBB, last 16 bytes are 0xCC */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xBB));
    kdi_Fill_u8(buf + 16, USIZE_C(16), U8_C(0xCC));

    /* Range [4, 20) - includes last 12 of 0xBB and first 4 of 0xCC */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(32), USIZE_C(4), USIZE_C(16), U8_C(0xBB));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(12));

    /* Range [4, 20) - count 0xCC */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(32), USIZE_C(4), USIZE_C(16), U8_C(0xCC));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(4));

    printf("PASSED\n");
}


void
ZeroValues(void)
{
    u8    buf[32];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ZeroValues -> ");

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));

    /* Full range */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(32));

    /* Subrange [10, 20) */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(32), USIZE_C(10), USIZE_C(10), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(10));

    printf("PASSED\n");
}


void
MaxByteValues(void)
{
    u8    buf[32];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "MaxByteValues -> ");

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xFF));

    /* Full range */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(32));

    /* Subrange [8, 24) */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(32), USIZE_C(8), USIZE_C(16), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

    printf("PASSED\n");
}


void
SparseMatches(void)
{
    u8    buf[100];
    usize count;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "SparseMatches -> ");

    kdi_Fill_u8(buf, USIZE_C(100), U8_C(0x00));

    /* Set every 10th byte to 0xFF */
    for (i = 0; i < 100; i += 10)
    {
        buf[i] = 0xFF;
    }

    /* Range [0, 100) - 10 matches */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(100), USIZE_C(0), USIZE_C(100), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(10));

    /* Range [25, 75) - matches at 30, 40, 50, 60, 70 = 5 */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(100), USIZE_C(25), USIZE_C(50), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(5));

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    u8    buf[1024];
    usize count;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    /* Pattern: repeating 0-255 */
    for (i = 0; i < 1024; ++i)
    {
        buf[i] = (u8)(i % 256);
    }

    /* Count byte value 0 in range [0, 1024) - appears at 0, 256, 512, 768 = 4 */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(1024), USIZE_C(0), USIZE_C(1024), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(4));

    /* Count byte value 100 in range [50, 600) - appears at 100, 356 = 2 */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(1024), USIZE_C(50), USIZE_C(550), U8_C(100));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(2));

    printf("PASSED\n");
}


void
MiddleSubrange(void)
{
    u8    buf[64];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "MiddleSubrange -> ");

    kdi_Fill_u8(buf, USIZE_C(64), U8_C(0x11));
    kdi_Fill_u8(buf + 20, USIZE_C(24), U8_C(0x22));

    /* Range [16, 48) - first 4 are 0x11, middle 24 are 0x22, last 4 are 0x11 */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(64), USIZE_C(16), USIZE_C(32), U8_C(0x22));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(24));

    /* Count 0x11 in same range */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(64), USIZE_C(16), USIZE_C(32), U8_C(0x11));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(8));

    printf("PASSED\n");
}


void
OverlappingRanges(void)
{
    u8    buf[32];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "OverlappingRanges -> ");

    /* Pattern: first 10 = 0xAA, next 12 = 0xBB, last 10 = 0xAA */
    kdi_Fill_u8(buf, USIZE_C(10), U8_C(0xAA));
    kdi_Fill_u8(buf + 10, USIZE_C(12), U8_C(0xBB));
    kdi_Fill_u8(buf + 22, USIZE_C(10), U8_C(0xAA));

    /* Range [5, 17) - last 5 of first AA region + first 7 of BB region */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(32), USIZE_C(5), USIZE_C(12), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(5));

    /* Range [15, 27) - last 7 of BB region + first 5 of last AA region */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(32), USIZE_C(15), USIZE_C(12), U8_C(0xBB));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(7));

    printf("PASSED\n");
}


void
OddSizes(void)
{
    u8    buf[37];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "OddSizes -> ");

    kdi_Fill_u8(buf, USIZE_C(37), U8_C(0x77));

    /* Range [3, 34) - 31 bytes */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(37), USIZE_C(3), USIZE_C(31), U8_C(0x77));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(31));

    /* Range [17, 30) - 13 bytes */
    status = kdGenMemOpsCountBytesBound(&count, buf, USIZE_C(37), USIZE_C(17), USIZE_C(13), U8_C(0x77));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(13));

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    CountNone();
    CountAll();
    CountSubrange();
    ClampedEndCount();
    SingleByte();
    EdgeIndices();
    AlternatingPattern();
    ConsecutiveMatches();
    ZeroValues();
    MaxByteValues();
    SparseMatches();
    LargeBuffer();
    MiddleSubrange();
    OverlappingRanges();
    OddSizes();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}