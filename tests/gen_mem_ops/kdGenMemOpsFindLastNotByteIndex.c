/**
 * @file kdGenMemOpsFindLastNotByteIndex.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindLastNotByteIndex function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>
#include <string.h> /* For memset */

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h" /* For kdi_Fill_u8, kdi_FillSeq_u8 */


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindLastNotByteIndex function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8    buf[16];
    usize idx = 999;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_Fill_u8(buf, sizeof(buf), U8_C(0xAA));

    /* idx pointer is null -> failure */
    status = kdGenMemOpsFindLastNotByteIndex(NULL, buf, USIZE_C(16), U8_C(0xBB));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndex(&idx, NULL, USIZE_C(16), U8_C(0xBB));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndex(&idx, buf, USIZE_C(0), U8_C(0xBB));
    assert(status == RESULT_FAILURE);

    /* Valid arguments - searching for NOT 0xAA in a buffer of 0xAA and 0xBB.
     * Find 0xBB (last element). */
    buf[15] = 0xBB;
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndex(&idx, buf, USIZE_C(16), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(15));

    printf("PASSED\n");
}


void
AllMatch(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "AllMatch -> ");

    /* Fill buffer with 0xAA */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));

    /* Search for last byte NOT equal to 0xAA.
     * Since all are 0xAA, this should fail.
     */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndex(&idx, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SingleMismatchLast(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleMismatchLast -> ");

    /* Fill with 0xAA */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));

    /* Change last byte to 0xBB */
    buf[15] = 0xBB;

    /* Search for NOT 0xAA. Should find index 15. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndex(&idx, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(15));

    printf("PASSED\n");
}


void
SingleMismatchFirst(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleMismatchFirst -> ");

    /* Fill with 0xAA */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));

    /* Change first byte to 0xBB */
    buf[0] = 0xBB;

    /* Search for NOT 0xAA. Should find index 0 (as it's the last when scanning backwards too). */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndex(&idx, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    printf("PASSED\n");
}


void
MultipleMismatches(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "MultipleMismatches -> ");

    /* Fill with 0xAA */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));

    /* Mismatches at 2, 5, 10 */
    buf[2]  = 0xBB;
    buf[5]  = 0xCC;
    buf[10] = 0xDD;

    /* Search for last NOT 0xAA. Should find the LAST one (index 10). */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndex(&idx, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(10));

    printf("PASSED\n");
}


void
AlternatingPattern(void)
{
    u8    buf[32];
    usize idx;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "AlternatingPattern -> ");

    /* Alternating 0xAA, 0x55 */
    for (i = 0; i < 32; ++i)
    {
        buf[i] = (i & 1) ? U8_C(0x55) : U8_C(0xAA);
    }
    /* Buffer pattern: AA, 55, AA, 55, ... , AA, 55 */

    /* Find Last NOT 0xAA. Last 0x55 is at index 31. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndex(&idx, buf, USIZE_C(32), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(31));

    /* Find Last NOT 0x55. Last 0xAA is at index 30. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndex(&idx, buf, USIZE_C(32), U8_C(0x55));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(30));

    printf("PASSED\n");
}


void
SequentialValues(void)
{
    u8    buf[256];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "SequentialValues -> ");

    /* Init: 0..255 */
    kdi_FillSeq_u8(buf, USIZE_C(256), U8_C(0x00));
    /* Buffer: 0, 1, 2, ..., 255 */

    /* Find Last NOT 0. Last is 255 at index 255. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndex(&idx, buf, USIZE_C(256), U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(255));

    /* Find Last NOT 255. Last is 254 at index 254. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndex(&idx, buf, USIZE_C(256), U8_C(255));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(254));

    /* Find Last NOT 100. Last is 255 at index 255. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndex(&idx, buf, USIZE_C(256), U8_C(100));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(255));


    printf("PASSED\n");
}


void
SmallBuffer(void)
{
    u8    buf[1];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "SmallBuffer -> ");

    /* Single byte buffer */
    buf[0] = 0xAA;

    /* Find NOT 0xBB. Should find 0xAA at index 0. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndex(&idx, buf, USIZE_C(1), U8_C(0xBB));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    /* Find NOT 0xAA. Should fail. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndex(&idx, buf, USIZE_C(1), U8_C(0xAA));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    static u8 buf[1024]; /* Static to avoid stack overflow for large array */
    usize     idx;
    bool      status;
    usize     i;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    /* Init with target pattern */
    kdi_Fill_u8(buf, USIZE_C(1024), U8_C(0xCC));

    /* Set some non-matching values at specific points */
    buf[100] = 0xDD;
    buf[500] = 0xEE;
    buf[900] = 0xFF; /* This should be the last one found */

    /* Find Last NOT 0xCC. Should find 0xFF at index 900. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndex(&idx, buf, USIZE_C(1024), U8_C(0xCC));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(900));

    /* Fill buffer with sequential values (0..255 repeating) */
    for (i = 0; i < 1024; ++i)
    {
        buf[i] = (u8)(i % 256);
    }
    /* Pattern: 0, 1, ..., 255, 0, 1, ... */

    /* Find Last NOT 0. Last byte is 255 at index 1023. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndex(&idx, buf, USIZE_C(1024), U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(1023)); /* Value at 1023 is (1023 % 256) = 255, which is not 0. */

    /* Find Last NOT 255. Last byte is 254 at index 1022. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndex(&idx, buf, USIZE_C(1024), U8_C(255));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(1022)); /* Value at 1022 is (1022 % 256) = 254, which is not 255. */


    printf("PASSED\n");
}


void
U32_Buffer(void)
{
    u32   buf[4]; /* 16 bytes total */
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_Buffer -> ");

    /* Init: 0x00000000 */
    kdi_Fill_u8((u8 *)buf, sizeof(buf), 0);

    /* Set byte at offset 3 and 12 to 0xAA */
    ((u8 *)buf)[3]  = 0xAA; /* Last byte of buf[0] */
    ((u8 *)buf)[12] = 0xAA; /* First byte of buf[3] */

    /* Find Last NOT 0x00. Should find 0xAA at index 12. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndex(&idx, (u8 *)buf, sizeof(buf), U8_C(0x00));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(12));

    /* Find Last NOT 0xAA. Should find 0x00 at index 15. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndex(&idx, (u8 *)buf, sizeof(buf), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(15)); /* Last byte (index 15) is 0x00, which is not 0xAA */


    printf("PASSED\n");
}


void
SparseMatches(void)
{
    u8    buf[100];
    usize idx;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "SparseMatches -> ");

    /* Fill with 0xAA */
    kdi_Fill_u8(buf, USIZE_C(100), U8_C(0xAA));

    /* Set every 10th byte to 0xBB */
    for (i = 0; i < 100; i += 10)
    {
        buf[i] = 0xBB;
    }
    /* Pattern: BB, AA, ..., AA, BB, AA, ..., AA, BB ...
     * Indices with 0xBB: 0, 10, 20, ..., 90. */

    /* Find Last NOT 0xAA. Should return index 90 (last 0xBB). */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndex(&idx, buf, USIZE_C(100), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(90));

    /* Find Last NOT 0xBB. Should return index 99 (last 0xAA). */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndex(&idx, buf, USIZE_C(100), U8_C(0xBB));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(99));

    printf("PASSED\n");
}


void
OddSizes(void)
{
    u8    buf[33];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "OddSizes -> ");

    /* Odd size: 33 bytes. Fill with 0x77. */
    kdi_Fill_u8(buf, USIZE_C(33), U8_C(0x77));
    buf[5]  = 0x88;
    buf[17] = 0x88;
    buf[32] = 0x88; /* Last byte */

    /* Find Last NOT 0x77. Should be at index 32 (last 0x88). */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndex(&idx, buf, USIZE_C(33), U8_C(0x77));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(32));

    /* Find Last NOT 0x88. Should be at index 31 (last 0x77). */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndex(&idx, buf, USIZE_C(33), U8_C(0x88));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(31));

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    AllMatch();
    SingleMismatchLast();
    SingleMismatchFirst();
    MultipleMismatches();
    AlternatingPattern();
    SequentialValues();
    SmallBuffer();
    LargeBuffer();
    U32_Buffer();
    SparseMatches();
    OddSizes();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
