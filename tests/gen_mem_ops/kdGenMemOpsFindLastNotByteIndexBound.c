/**
 * @file kdGenMemOpsFindLastNotByteIndexBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindLastNotByteIndexBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>
#include <string.h> /* For memset */

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h" /* For kdi_Fill_u8, kdi_FillSeq_u8 */


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindLastNotByteIndexBound function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8    buf[16];
    usize idx = 999;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_Fill_u8(buf, sizeof(buf), U8_C(0xAA));

    /* idx pointer is NULL -> failure */
    status = kdGenMemOpsFindLastNotByteIndexBound(NULL, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0xAA));
    assert(status == RESULT_FAILURE);

    /* base is NULL -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, NULL, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0xAA));
    assert(status == RESULT_FAILURE);

    /* begin_idx >= base_sz -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(16), USIZE_C(1), U8_C(0xAA));
    assert(status == RESULT_FAILURE);

    /* end_count_byte is zero -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(0), U8_C(0xAA));
    assert(status == RESULT_FAILURE);

    /* Valid arguments - searching for NOT 0xAA in a buffer of 0xAA and 0xBB.
     * Find 0xBB (last element). */
    buf[15] = 0xBB;
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(15));

    printf("PASSED\n");
}


void
AllMatchTarget(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "AllMatchTarget -> ");

    /* Fill buffer with 0xAA */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));

    /* Range [0, 16). Search for NOT 0xAA.
     * All are 0xAA. Should fail to find any mismatch.
     */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SingleMismatchLastInBound(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleMismatchLastInBound -> ");

    /* Fill with 0xAA */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));

    /* Set last byte in range [0, 16) to 0xBB */
    buf[15] = 0xBB;

    /* Search for NOT 0xAA in range [0, 16). Should find index 15. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(15));

    printf("PASSED\n");
}


void
SingleMismatchFirstInBound(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleMismatchFirstInBound -> ");

    /* Fill with 0xAA */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));

    /* Set first byte in range [0, 16) to 0xBB */
    buf[0] = 0xBB;

    /* Search for NOT 0xAA in range [0, 16). Should find index 0. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    printf("PASSED\n");
}


void
MultipleMismatchesInBound(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "MultipleMismatchesInBound -> ");

    /* Fill with 0xAA */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));

    /* Mismatches at 2, 5, 8, 11 */
    buf[2]  = 0xBB;
    buf[5]  = 0xCC;
    buf[8]  = 0xDD;
    buf[11] = 0xEE;

    /* Search for last NOT 0xAA in range [0, 16). Should find the LAST one (index 11). */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(11));

    /* Search for last NOT 0xAA in range [0, 10). Excludes 11. Should find 8. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(10), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(8));

    /* Search for last NOT 0xAA in range [6, 16). Includes 8, 11. Should find 11. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(6), USIZE_C(10), U8_C(0xAA)); /* Range [6, 16) */
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(11));

    printf("PASSED\n");
}


void
RangeConstraints(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "RangeConstraints -> ");

    /* Init: 0, 1, 2, ... 15 */
    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0));

    /* Range [4, 10). Indices 4..9. Values 4..9. */

    /* Find Last NOT 4 in range [4, 10).
     * Values in range: 4, 5, 6, 7, 8, 9.
     * Last NOT 4 is 9 at index 9. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(6), U8_C(4)); /* Range [4, 10) */
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(9));

    /* Find Last NOT 9 in range [4, 10).
     * Values in range: 4, 5, 6, 7, 8, 9.
     * Last NOT 9 is 8 at index 8. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(6), U8_C(9)); /* Range [4, 10) */
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(8));

    /* Create a range where all values match the target to test failure. */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xBB)); /* All 0xBB */
    /* Range [4, 10). All 0xBB. Search for NOT 0xBB. Should fail. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(6), U8_C(0xBB)); /* Range [4, 10) */
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

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));
    buf[15] = 0xFF;

    /* Requesting 100 bytes starting at 0. Clamps to 16. Range [0, 16).
     * Find Last NOT 0xAA. 0xAA at 0..14. 0xFF at 15. Last mismatch is at 15. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(100), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(15));

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
    /* Buffer pattern: AA, 55, AA, 55, ..., AA, 55 */
    for (i = 0; i < 32; ++i)
    {
        buf[i] = (i & 1) ? U8_C(0x55) : U8_C(0xAA);
    }

    /* Find Last NOT 0xAA in range [0, 32). Last 0x55 is at index 31. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(31));

    /* Find Last NOT 0x55 in range [0, 32). Last 0xAA is at index 30. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), U8_C(0x55));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(30));

    /* Find Last NOT 0xAA in range [1, 10). Begin_idx=1, end_count_byte=9. Indices 1..9.
     * Pattern in range: 55, AA, 55, AA, 55, AA, 55, AA, 55.
     * Last NOT 0xAA in range is 0x55 at index 9. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(1), USIZE_C(9), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(9));

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

    /* Find Last NOT 0 in range [0, 256). Last is 255 at index 255. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(256), USIZE_C(0), USIZE_C(256), U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(255));

    /* Find Last NOT 255 in range [0, 256). Last is 254 at index 254. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(256), USIZE_C(0), USIZE_C(256), U8_C(255));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(254));
    
    /* Find Last NOT 100 in range [0, 256). Last is 255 at index 255. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(256), USIZE_C(0), USIZE_C(256), U8_C(100));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(255));

    /* Find Last NOT 100 in range [0, 100). Excludes 100. Last is 99 at index 99. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(256), USIZE_C(0), USIZE_C(100), U8_C(100));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(99));

    printf("PASSED\n");
}


void
SmallRange(void)
{
    u8    buf[32];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "SmallRange -> ");

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x77));
    buf[10] = 0x88;
    buf[11] = 0x99;

    /* Single byte range [10, 11). Begin_idx=10, end_count_byte=1. Value at 10 is 0x88.
     * Search NOT 0x77. Should find 0x88 at index 10. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(10), USIZE_C(1), U8_C(0x77));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(10));

    /* Single byte range [9, 10). Begin_idx=9, end_count_byte=1. Value at 9 is 0x77.
     * Search NOT 0x77. Should fail. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(9), USIZE_C(1), U8_C(0x77));
    assert(status == RESULT_FAILURE);

    /* Single byte range [11, 12). Begin_idx=11, end_count_byte=1. Value at 11 is 0x99.
     * Search NOT 0x88. Should find 0x99 at index 11. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(11), USIZE_C(1), U8_C(0x88));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(11));

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

    /* Find Last NOT 0xCC in range [0, 1024). Should find 0xFF at index 900. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(1024), USIZE_C(0), USIZE_C(1024), U8_C(0xCC));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(900));

    /* Find Last NOT 0xCC in range [0, 800). Excludes 900. Should find 0xEE at index 500. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(1024), USIZE_C(0), USIZE_C(800), U8_C(0xCC));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(500));

    /* Now, fill with sequential values (0..255 repeating) */
    for (i = 0; i < 1024; ++i)
    {
        buf[i] = (u8)(i % 256);
    }
    /* Pattern: 0, 1, ..., 255, 0, 1, ... */

    /* Find Last NOT 0 in range [0, 1024). Last byte is 255 at index 1023. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(1024), USIZE_C(0), USIZE_C(1024), U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(1023)); /* Value at 1023 is (1023 % 256) = 255, which is not 0. */

    /* Find Last NOT 255 in range [0, 1024). Last byte is 254 at index 1022. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(1024), USIZE_C(0), USIZE_C(1024), U8_C(255));
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

    /* Set bytes at index 3 and 12 to 0xAA */
    ((u8 *)buf)[3]  = 0xAA; /* Last byte of buf[0] */
    ((u8 *)buf)[12] = 0xAA; /* First byte of buf[3] */

    /* Find Last NOT 0x00 in range [0, 16). Should find 0xAA at index 12. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, (u8 *)buf, sizeof(buf), USIZE_C(0), USIZE_C(16), U8_C(0x00));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(12));

    /* Find Last NOT 0x00 in range [0, 12). Excludes 12. Should find 0xAA at index 3. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, (u8 *)buf, sizeof(buf), USIZE_C(0), USIZE_C(12), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(3));

    /* Find Last NOT 0xAA in range [0, 16). Last 0x00 is at index 15. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, (u8 *)buf, sizeof(buf), USIZE_C(0), USIZE_C(16), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(15)); /* Last byte (index 15) is 0x00, which is not 0xAA */

    printf("PASSED\n");
}


void
SparseMismatches(void)
{
    u8    buf[100];
    usize idx;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "SparseMismatches -> ");

    /* Fill with 0xAA */
    kdi_Fill_u8(buf, USIZE_C(100), U8_C(0xAA));

    /* Set every 10th byte to 0xBB */
    for (i = 0; i < 100; i += 10)
    {
        buf[i] = 0xBB;
    }
    /* Pattern: BB, AA, ..., AA, BB, AA, ..., AA, BB ...
     * Indices with 0xBB: 0, 10, 20, ..., 90. */

    /* Find Last NOT 0xAA in range [0, 100). Should return index 90 (last 0xBB). */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(100), USIZE_C(0), USIZE_C(100), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(90));

    /* Find Last NOT 0xAA in range [0, 85). Excludes 90. Should return index 80. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(100), USIZE_C(0), USIZE_C(85), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(80));

    /* Find Last NOT 0xBB in range [0, 100). Should return index 99 (last 0xAA). */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(100), USIZE_C(0), USIZE_C(100), U8_C(0xBB));
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

    /* Find Last NOT 0x77 in range [0, 33). Should be at index 32 (last 0x88). */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(33), USIZE_C(0), USIZE_C(33), U8_C(0x77));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(32));

    /* Find Last NOT 0x77 in range [0, 32). Excludes 32. Should be at index 17. */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(33), USIZE_C(0), USIZE_C(32), U8_C(0x77));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(17));

    /* Find Last NOT 0x88 in range [0, 33). Should be at index 31 (last 0x77). */
    idx    = 999;
    status = kdGenMemOpsFindLastNotByteIndexBound(&idx, buf, USIZE_C(33), USIZE_C(0), USIZE_C(33), U8_C(0x88));
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
    AllMatchTarget();
    SingleMismatchLastInBound();
    SingleMismatchFirstInBound();
    MultipleMismatchesInBound();
    RangeConstraints();
    EndValueClamping();
    AlternatingPattern();
    SequentialValues();
    SmallRange();
    LargeBuffer();
    U32_Buffer();
    SparseMismatches();
    OddSizes();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
