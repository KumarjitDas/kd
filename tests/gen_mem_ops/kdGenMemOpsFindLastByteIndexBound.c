/**
 * @file kdGenMemOpsFindLastByteIndexBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindLastByteIndexBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>
#include <string.h>   /* For memset */

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h" /* For kdi_Fill_u8, kdi_FillSeq_u8 */


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindLastByteIndexBound function test"
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
    status = kdGenMemOpsFindLastByteIndexBound(NULL, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0xAA));
    assert(status == RESULT_FAILURE);

    /* base is NULL -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, NULL, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0xAA));
    assert(status == RESULT_FAILURE);

    /* begin_idx >= base_sz -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(16), USIZE_C(1), U8_C(0xAA));
    assert(status == RESULT_FAILURE);

    /* end_count_byte is zero -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(0), U8_C(0xAA));
    assert(status == RESULT_FAILURE);

    /* Valid arguments - target found at last possible index within bounds */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(15));

    printf("PASSED\n");
}


void
FindNone(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNone -> ");

    /* Init: 0x00 */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Find 0xFF in range [0, 16) - not present */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
FindFirstInBound(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindFirstInBound -> ");

    /* Init: 0x00 */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Set first byte in range to 0xFF. Search range is [0, 1). */
    buf[0] = 0xFF;

    /* Find Last 0xFF in range [0, 1). Only one byte, so it's the last. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(1), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    printf("PASSED\n");
}


void
FindLastInBound(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindLastInBound -> ");

    /* Init: 0x00 */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Set last byte in range [0, 16) to 0xFF */
    buf[15] = 0xFF;

    /* Find Last 0xFF in range [0, 16). */
    idx     = 999;
    status  = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(15));

    printf("PASSED\n");
}


void
FindMultipleInBound(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindMultipleInBound -> ");

    /* Init: 0x00 */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Set 0xFF at indices 2, 5, 8, 11 */
    buf[2]  = 0xFF;
    buf[5]  = 0xFF;
    buf[8]  = 0xFF;
    buf[11] = 0xFF;

    /* Range [0, 16). Should find last one at 11. */
    idx     = 999;
    status  = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(11));

    /* Range [0, 10). Includes 2, 5, 8. Excludes 11. Should find 8. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(10), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(8));

    /* Range [0, 3). Includes 2. Should find 2. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(3), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(2));

    /* Range [6, 16). Includes 8, 11. Should find 11. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(6), USIZE_C(10), U8_C(0xFF)); /* Range [6, 16) */
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

    /* 1. Find value inside range (Index 6, Value 6) */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(6), U8_C(6)); /* Range [4, 10) */
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(6));

    /* 2. Find value at start of range (Index 4, Value 4) */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(6), U8_C(4)); /* Range [4, 10) */
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(4));

    /* 3. Find value at end of range - 1 (Index 9, Value 9) */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(6), U8_C(9)); /* Range [4, 10) */
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(9));

    /* 4. Find value immediately before range (Index 3, Value 3) -> Fail */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(6), U8_C(3)); /* Range [4, 10) */
    assert(status == RESULT_FAILURE);

    /* 5. Find value immediately after range (Index 10, Value 10) -> Fail */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(6), U8_C(10)); /* Range [4, 10) */
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

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));
    buf[15] = 0xFF;

    /* Requesting 100 bytes starting at 0. Clamps to 16. Range [0, 16). */
    idx     = 999;
    status  = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(100), U8_C(0xFF));

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

    /* Find Last 0xAA in range [0, 32). Last 0xAA is at index 30. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(30));

    /* Find Last 0x55 in range [0, 32). Last 0x55 is at index 31. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), U8_C(0x55));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(31));

    /* Find Last 0xAA in range [1, 10). Begin_idx=1, end_count_byte=9. Indices 1..9.
     * Pattern: 55, AA, 55, AA, 55, AA, 55, AA, 55.
     * Last 0xAA in range is at index 8. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(1), USIZE_C(9), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(8));

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

    /* Find Last value 50 in range [0, 256). Should be at index 50. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(256), USIZE_C(0), USIZE_C(256), U8_C(50));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(50));

    /* Find Last value 50 in range [0, 50). Value 50 is excluded. Should fail. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(256), USIZE_C(0), USIZE_C(50), U8_C(50));
    assert(status == RESULT_FAILURE);

    /* Find Last value 50 in range [0, 51). Includes 50. Should be at index 50. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(256), USIZE_C(0), USIZE_C(51), U8_C(50));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(50));

    /* Find Last value 50 in range [50, 206). Begin_idx=50, end_count_byte=156. Should find at 50. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(256), USIZE_C(50), USIZE_C(156), U8_C(50));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(50));

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

    /* Single byte range [10, 11). Begin_idx=10, end_count_byte=1. Value at 10 is 0x88. */
    idx     = 999;
    status  = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(10), USIZE_C(1), U8_C(0x88));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(10));

    /* Single byte range [11, 12). Begin_idx=11, end_count_byte=1. Value at 11 is 0x99. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(11), USIZE_C(1), U8_C(0x99));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(11));

    /* Single byte range [9, 10). Begin_idx=9, end_count_byte=1. Value at 9 is 0x77. Search 0x88. Fail. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(9), USIZE_C(1), U8_C(0x88));
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

    /* Init with pattern 0..255 repeating */
    for (i = 0; i < 1024; ++i)
    {
        buf[i] = (u8)(i % 256);
    }
    /* Pattern: 0, 1, ..., 255, 0, 1, ... */

    /* Find Last 100 in range [0, 1024).
     * Occurrences are at 100, 356 (100+256), 612 (100+2*256), 868 (100+3*256).
     * Should find 868. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(1024), USIZE_C(0), USIZE_C(1024), U8_C(100));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(868));

    /* Find Last 100 in range [200, 624). Begin_idx=200, end_count_byte=424. Range [200, 624).
     * Occurrences in range: 356. Should find 356. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(1024), USIZE_C(200), USIZE_C(424), U8_C(100));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(612));

    /* Find Last 100 in range [0, 300). Only occurrence is 100. Should find 100. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(1024), USIZE_C(0), USIZE_C(300), U8_C(100));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(100));

    /* Find Last 100 in range [0, 100). Excludes 100. Should fail. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(1024), USIZE_C(0), USIZE_C(100), U8_C(100));
    assert(status == RESULT_FAILURE);


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

    /* Find Last 0xAA in range [0, 16). Should find 0xAA at index 12. */
    idx             = 999;
    status          = kdGenMemOpsFindLastByteIndexBound(&idx, (u8 *)buf, sizeof(buf), USIZE_C(0), USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(12));

    /* Find Last 0xAA in range [0, 12). Excludes 12. Should find 0xAA at index 3. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, (u8 *)buf, sizeof(buf), USIZE_C(0), USIZE_C(12), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(3));

    /* Find Last 0xAA in range [4, 16). Excludes 3. Includes 12. Should find 0xAA at index 12. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, (u8 *)buf, sizeof(buf), USIZE_C(4), USIZE_C(12), U8_C(0xAA)); /* Range [4, 16) */
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(12));


    printf("PASSED\n");
}


void
AllSameValue(void)
{
    u8    buf[32];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "AllSameValue -> ");

    /* All bytes are 0x77 */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x77));

    /* Find Last 0x77 in range [0, 32). Should return index 31. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), U8_C(0x77));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(31));

    /* Find Last 0x77 in range [10, 20). Begin_idx=10, end_count_byte=10. Range [10, 20). Should return 19. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(10), USIZE_C(10), U8_C(0x77));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(19));

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

    /* Fill with 0x00 */
    kdi_Fill_u8(buf, USIZE_C(100), U8_C(0x00));

    /* Set every 10th byte to 0xFF */
    for (i = 0; i < 100; i += 10)
    {
        buf[i] = 0xFF;
    }
    /* Pattern: FF, 00, ..., 00, FF, 00, ..., 00, FF ...
     * Indices with FF: 0, 10, 20, 30, 40, 50, 60, 70, 80, 90. */

    /* Find Last 0xFF in range [0, 100). Should return index 90. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(100), USIZE_C(0), USIZE_C(100), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(90));

    /* Find Last 0xFF in range [0, 85). Excludes 90. Should return index 80. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(100), USIZE_C(0), USIZE_C(85), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(80));

    /* Find Last 0xFF in range [5, 95). Begin_idx=5, end_count_byte=90. Range [5, 95).
     * First in range is 10. Last in range is 90. Should return 90. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(100), USIZE_C(5), USIZE_C(90), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(90));

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

    /* Find Last 0x88 in range [0, 33). */
    idx     = 999;
    status  = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(33), USIZE_C(0), USIZE_C(33), U8_C(0x88));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(32));

    /* Find Last 0x88 in range [0, 32). Excludes 32. Should be at index 17. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(33), USIZE_C(0), USIZE_C(32), U8_C(0x88));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(17));

    /* Find Last 0x88 in range [17, 20). Begin_idx=17, end_count_byte=3. Range [17, 20). Should find at 17. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndexBound(&idx, buf, USIZE_C(33), USIZE_C(17), USIZE_C(3), U8_C(0x88));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(17));

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    FindNone();
    FindFirstInBound();
    FindLastInBound();
    FindMultipleInBound();
    RangeConstraints();
    EndValueClamping();
    AlternatingPattern();
    SequentialValues();
    SmallRange();
    LargeBuffer();
    U32_Buffer();
    AllSameValue();
    SparseMatches();
    OddSizes();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
