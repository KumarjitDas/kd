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
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsCountNotBytesBound function test"
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
    status = kdGenMemOpsCountNotBytesBound(null, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountNotBytesBound(&count, null, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* begin_idx >= base_sz -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountNotBytesBound(&count, buf, USIZE_C(16), USIZE_C(16), USIZE_C(10), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* end_count is zero -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountNotBytesBound(&count, buf, USIZE_C(16), USIZE_C(0), USIZE_C(0), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* Valid arguments - count NOT 0x00 in full range */
    count  = 55;
    status = kdGenMemOpsCountNotBytesBound(&count, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

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

    /* Search for NOT 0x00 in range [0, 16) - all are 0x00, so count = 0 */
    status = kdGenMemOpsCountNotBytesBound(&count, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0x00));

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

    /* Search for NOT 0xFF in range [0, 16) - all are 0xAA, so all are NOT 0xFF */
    status = kdGenMemOpsCountNotBytesBound(&count, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

    printf("PASSED\n");
}


void
CountSingle(void)
{
    u8    buf[16];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountSingle -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));
    buf[7] = 0xFF;

    /* Count NOT 0x00 in range [0, 16). Only index 7 is NOT 0x00. */
    status = kdGenMemOpsCountNotBytesBound(&count, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0x00));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(1));

    printf("PASSED\n");
}


void
RangeConstraints(void)
{
    u8    buf[32];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "RangeConstraints -> ");

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xAA));

    /* Set mismatches at 2, 5, 8, 12, 20, 28 */
    buf[2]  = 0xBB;
    buf[5]  = 0xBB;
    buf[8]  = 0xBB;
    buf[12] = 0xBB;
    buf[20] = 0xBB;
    buf[28] = 0xBB;

    /* Range [4, 14). Indices 4..13. Mismatches inside: 5, 8, 12. Count = 3. */
    status  = kdGenMemOpsCountNotBytesBound(&count, buf, USIZE_C(32), USIZE_C(4), USIZE_C(10), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(3));

    /* Range [10, 30). Indices 10..29. Mismatches inside: 12, 20, 28. Count = 3. */
    status = kdGenMemOpsCountNotBytesBound(&count, buf, USIZE_C(32), USIZE_C(10), USIZE_C(20), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(3));

    printf("PASSED\n");
}


void
EndValueClamping(void)
{
    u8    buf[16];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "EndValueClamping -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));
    buf[15] = 0xBB;

    /* Requesting 100 bytes starting at 0, clamps to 16. Range [0, 16). */
    status  = kdGenMemOpsCountNotBytesBound(&count, buf, USIZE_C(16), USIZE_C(0), USIZE_C(100), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(1));

    printf("PASSED\n");
}


void
CountAtBoundaries(void)
{
    u8    buf[16];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountAtBoundaries -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));

    buf[4] = 0xBB; /* At start of range */
    buf[7] = 0xBB; /* At end of range */
    buf[8] = 0xBB; /* Outside range */

    /* Range [4, 8) */
    status = kdGenMemOpsCountNotBytesBound(&count, buf, USIZE_C(16), USIZE_C(4), USIZE_C(4), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(2)); /* 4 and 7 */

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

    /* Count NOT 0xAA in range [0, 32). Half are 0x55 (NOT 0xAA). */
    status = kdGenMemOpsCountNotBytesBound(&count, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

    /* Count NOT 0x55 in range [10, 20). */
    /* Indices 10, 12, 14, 16, 18 are 0xAA (NOT 0x55). Count = 5. */
    status = kdGenMemOpsCountNotBytesBound(&count, buf, USIZE_C(32), USIZE_C(10), USIZE_C(10), U8_C(0x55));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(5));

    printf("PASSED\n");
}


void
SequentialValues(void)
{
    u8    buf[256];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "SequentialValues -> ");

    kdi_FillSeq_u8(buf, USIZE_C(256), U8_C(0x00));

    /* Count NOT 128 in range [100, 200). Value 128 appears once, so 99 are NOT 128. */
    status = kdGenMemOpsCountNotBytesBound(&count, buf, USIZE_C(256), USIZE_C(100), USIZE_C(100), U8_C(128));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(99));

    /* Count NOT 50 in range [0, 100). Value 50 appears once, so 99 are NOT 50. */
    status = kdGenMemOpsCountNotBytesBound(&count, buf, USIZE_C(256), USIZE_C(0), USIZE_C(100), U8_C(50));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(99));

    printf("PASSED\n");
}


void
SmallRange(void)
{
    u8    buf[32];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "SmallRange -> ");

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x77));
    buf[10] = 0x88;

    /* Single byte range [10, 11) */
    status = kdGenMemOpsCountNotBytesBound(&count, buf, USIZE_C(32), USIZE_C(10), USIZE_C(1), U8_C(0x77));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(1));

    /* Single byte range [9, 10) */
    status = kdGenMemOpsCountNotBytesBound(&count, buf, USIZE_C(32), USIZE_C(9), USIZE_C(1), U8_C(0x77));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

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

    for (i = 0; i < 1024; ++i)
    {
        buf[i] = (u8)(i % 256);
    }

    /* Count NOT 0x00 in range [0, 1024). Value 0 appears at 0, 256, 512, 768 = 4 times.
     * So NOT 0x00 = 1020. */
    status = kdGenMemOpsCountNotBytesBound(&count, buf, USIZE_C(1024), USIZE_C(0), USIZE_C(1024), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(1020));

    /* Count NOT 100 in range [500, 800). Value 100 appears at 100, 356, 612, 868.
     * In range [500, 800): only 612 is in range. So NOT 100 = 299. */
    status = kdGenMemOpsCountNotBytesBound(&count, buf, USIZE_C(1024), USIZE_C(500), USIZE_C(300), U8_C(100));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(299));

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

    /* Count NOT 0x00 in range [0, 100). 10 bytes are 0xFF (NOT 0x00). */
    status = kdGenMemOpsCountNotBytesBound(&count, buf, USIZE_C(100), USIZE_C(0), USIZE_C(100), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(10));

    /* Count NOT 0xFF in range [25, 75). Indices 30, 40, 50, 60, 70 are 0xFF.
     * So 5 are 0xFF, 45 are NOT 0xFF. */
    status = kdGenMemOpsCountNotBytesBound(&count, buf, USIZE_C(100), USIZE_C(25), USIZE_C(50), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(45));

    printf("PASSED\n");
}


void
ConsecutiveMatches(void)
{
    u8    buf[32];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ConsecutiveMatches -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xBB));
    kdi_Fill_u8(buf + 16, USIZE_C(16), U8_C(0xCC));

    /* Count NOT 0xBB in range [0, 32). Last 16 are NOT 0xBB. */
    status = kdGenMemOpsCountNotBytesBound(&count, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), U8_C(0xBB));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

    /* Count NOT 0xCC in range [10, 30). Range covers indices 10..29.
     * Indices 10..15 are 0xBB (NOT 0xCC), indices 16..29 are 0xCC.
     * So 6 are NOT 0xCC. */
    status = kdGenMemOpsCountNotBytesBound(&count, buf, USIZE_C(32), USIZE_C(10), USIZE_C(20), U8_C(0xCC));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(6));

    printf("PASSED\n");
}


void
RepeatingGroups(void)
{
    u8    buf[30];
    usize count;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "RepeatingGroups -> ");

    /* Pattern: 0xFF, 0xFF, 0xFF, 0x00, 0x00 (repeating) */
    for (i = 0; i < 30; i += 5)
    {
        buf[i]     = 0xFF;
        buf[i + 1] = 0xFF;
        buf[i + 2] = 0xFF;
        buf[i + 3] = 0x00;
        buf[i + 4] = 0x00;
    }

    /* Count NOT 0xFF in range [0, 30). 12 bytes are 0x00 (NOT 0xFF). */
    status = kdGenMemOpsCountNotBytesBound(&count, buf, USIZE_C(30), USIZE_C(0), USIZE_C(30), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(12));

    /* Count NOT 0x00 in range [5, 20). Pattern covers 3 complete groups.
     * 9 are 0xFF (NOT 0x00), 6 are 0x00. */
    status = kdGenMemOpsCountNotBytesBound(&count, buf, USIZE_C(30), USIZE_C(5), USIZE_C(15), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(9));

    printf("PASSED\n");
}


void
OddSizes(void)
{
    u8    buf[33];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "OddSizes -> ");

    kdi_Fill_u8(buf, USIZE_C(33), U8_C(0x77));

    /* Count NOT 0x77 in range [0, 33). None are NOT 0x77. */
    status = kdGenMemOpsCountNotBytesBound(&count, buf, USIZE_C(33), USIZE_C(0), USIZE_C(33), U8_C(0x77));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    /* Count NOT 0x00 in range [0, 17). All are 0x77 (NOT 0x00). */
    status = kdGenMemOpsCountNotBytesBound(&count, buf, USIZE_C(33), USIZE_C(0), USIZE_C(17), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(17));

    /* Count NOT 0x77 in range [20, 27). All are 0x77. */
    status = kdGenMemOpsCountNotBytesBound(&count, buf, USIZE_C(33), USIZE_C(20), USIZE_C(7), U8_C(0x77));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

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
    CountSingle();
    RangeConstraints();
    EndValueClamping();
    CountAtBoundaries();
    AlternatingPattern();
    SequentialValues();
    SmallRange();
    LargeBuffer();
    SparseMatches();
    ConsecutiveMatches();
    RepeatingGroups();
    OddSizes();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}