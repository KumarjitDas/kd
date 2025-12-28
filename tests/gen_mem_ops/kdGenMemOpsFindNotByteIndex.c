/**
 * @file kdGenMemOpsFindNotByteIndex.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindNotByteIndex function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindNotByteIndex function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8    buf[16];
    usize idx = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));

    /* idx pointer is null -> failure */
    status = kdGenMemOpsFindNotByteIndex(null, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    idx    = 55;
    status = kdGenMemOpsFindNotByteIndex(&idx, null, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* sz is zero -> failure */
    idx    = 55;
    status = kdGenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(0), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* Valid arguments - found at index 0 (0xAA is NOT 0x00) */
    idx    = 55;
    status = kdGenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(16), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

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

    /* Search for byte NOT equal to 0xAA.
     * Since all are 0xAA, this should fail.
     */
    idx    = 999;
    status = kdGenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
FirstMismatch(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FirstMismatch -> ");

    /* Fill with 0xAA */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));

    /* Change first byte to 0xBB */
    buf[0] = 0xBB;

    /* Search for NOT 0xAA. Should find index 0. */
    status = kdGenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    printf("PASSED\n");
}


void
LastMismatch(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "LastMismatch -> ");

    /* Fill with 0xAA */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));

    /* Change last byte to 0xBB */
    buf[15] = 0xBB;

    /* Search for NOT 0xAA. Should find index 15. */
    status  = kdGenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(15));

    printf("PASSED\n");
}


void
MiddleMismatch(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "MiddleMismatch -> ");

    /* Fill with 0xAA */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));

    /* Change middle byte */
    buf[8] = 0xBB;

    /* Search for NOT 0xAA. */
    status = kdGenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(8));

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

    /* Search for NOT 0xAA. Should find the FIRST one (index 2). */
    status  = kdGenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(2));

    printf("PASSED\n");
}


void
FindNotZero(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNotZero -> ");

    /* Fill with zeros */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Set one non-zero byte */
    buf[9] = 0xFF;

    /* Search for NOT 0x00. Should find index 9. */
    status = kdGenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(16), U8_C(0x00));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(9));

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
        buf[i] = (i & 1) ? 0x55 : 0xAA;
    }

    /* Find NOT 0xAA (should return first 0x55 at index 1). */
    status = kdGenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(32), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(1));

    /* Find NOT 0x55 (should return first 0xAA at index 0). */
    status = kdGenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(32), U8_C(0x55));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    /* Find NOT 0x00 (neither are 0x00, so should return index 0). */
    status = kdGenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(32), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

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

    /* Find NOT 0. Should be at index 1 (value is 1). */
    status = kdGenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(256), U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(1));

    /* Find NOT 128. Should be at index 0 (value is 0). */
    status = kdGenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(256), U8_C(128));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    /* Find NOT 255. Should be at index 0 (value is 0). */
    status = kdGenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(256), U8_C(255));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    printf("PASSED\n");
}


void
SmallBuffer(void)
{
    u8    buf[1];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "SmallBuffer -> ");

    /* Single byte buffer - match */
    buf[0] = 0x42;
    status = kdGenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(1), U8_C(0x42));
    assert(status == RESULT_FAILURE);

    /* Single byte buffer - no match */
    status = kdGenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(1), U8_C(0x43));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    u8    buf[1024];
    usize idx;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    /* Init with pattern */
    for (i = 0; i < 1024; ++i)
    {
        buf[i] = (u8)(i % 256);
    }

    /* Find NOT 0. First non-zero is at index 1. */
    status = kdGenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(1024), U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(1));

    /* Find NOT 100. First non-100 is at index 0 (value is 0). */
    status = kdGenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(1024), U8_C(100));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

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

    /* Find NOT 0x77. Should fail (all match). */
    status = kdGenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(32), U8_C(0x77));
    assert(status == RESULT_FAILURE);

    /* Find NOT 0x88. Should return index 0 (all are NOT 0x88). */
    status = kdGenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(32), U8_C(0x88));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

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

    /* Find NOT 0xFF. Should return index 1 (first 0x00 after initial 0xFF). */
    status = kdGenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(100), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(1));

    /* Find NOT 0x00. Should return index 0 (first 0xFF). */
    status = kdGenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(100), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    printf("PASSED\n");
}


void
U32_Buffer(void)
{
    u32   buf[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_Buffer -> ");

    /* Init: 0xAAAAAAAA */
    kdi_Fill_u8((u8 *)buf, sizeof(buf), 0xAA);

    /* Set byte at offset 7 to 0xBB */
    ((u8 *)buf)[7] = 0xBB;

    /* Find NOT 0xAA */
    status         = kdGenMemOpsFindNotByteIndex(&idx, buf, sizeof(buf), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(7));

    printf("PASSED\n");
}


void
ConsecutiveMatches(void)
{
    u8    buf[32];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "ConsecutiveMatches -> ");

    /* First 16 bytes are 0xBB, last 16 bytes are 0xCC */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xBB));
    kdi_Fill_u8(buf + 16, USIZE_C(16), U8_C(0xCC));

    /* Find NOT 0xBB. Should return index 16 (first 0xCC). */
    status = kdGenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(32), U8_C(0xBB));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(16));

    /* Find NOT 0xCC. Should return index 0 (first 0xBB). */
    status = kdGenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(32), U8_C(0xCC));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    printf("PASSED\n");
}


void
OddSizes(void)
{
    u8    buf[33];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "OddSizes -> ");

    /* Odd size: 33 bytes */
    kdi_Fill_u8(buf, USIZE_C(33), U8_C(0x77));

    /* Set one different byte */
    buf[17] = 0x88;

    /* Find NOT 0x77 */
    status  = kdGenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(33), U8_C(0x77));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(17));

    /* Size 17 - mismatch is at index 17, which is out of range */
    status = kdGenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(17), U8_C(0x77));
    assert(status == RESULT_FAILURE);

    /* Size 20 - mismatch is at index 17, which is in range */
    status = kdGenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(20), U8_C(0x77));
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
    AllMatch();
    FirstMismatch();
    LastMismatch();
    MiddleMismatch();
    MultipleMismatches();
    FindNotZero();
    AlternatingPattern();
    SequentialValues();
    SmallBuffer();
    LargeBuffer();
    AllSameValue();
    SparseMatches();
    U32_Buffer();
    ConsecutiveMatches();
    OddSizes();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}