/**
 * @file kdGenMemOpsFindLastByteIndex.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindLastByteIndex function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"

#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindLastByteIndex function test"
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
    status = kdGenMemOpsFindLastByteIndex(null, buf, USIZE_C(16), U8_C(0xAA));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndex(&idx, null, USIZE_C(16), U8_C(0xAA));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndex(&idx, buf, USIZE_C(0), U8_C(0xAA));
    assert(status == RESULT_FAILURE);

    /* Valid arguments - target found at last possible index */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndex(&idx, buf, USIZE_C(16), U8_C(0xAA));
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

    /* Find 0xFF (not present) */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndex(&idx, buf, USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
FindFirst(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindFirst -> ");

    /* Init: 0x00 */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Set first byte in range */
    buf[0] = 0xFF;

    /* Find Last 0xFF (only one exists at index 0) */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndex(&idx, buf, USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    printf("PASSED\n");
}


void
FindLast(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindLast -> ");

    /* Init: 0x00 */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Set last byte in range */
    buf[15] = 0xFF;

    /* Find Last 0xFF */
    idx     = 999;
    status  = kdGenMemOpsFindLastByteIndex(&idx, buf, USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(15));

    printf("PASSED\n");
}


void
FindMultiple(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindMultiple -> ");

    /* Init: 0x00 */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Set 0xFF at indices 2, 5, 8 */
    buf[2] = 0xFF;
    buf[5] = 0xFF;
    buf[8] = 0xFF;

    /* Find Last 0xFF. Should return index 8. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndex(&idx, buf, USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(8));

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

    /* Find Last 0xAA in range [0, 32). Should return 30 (last even index). */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndex(&idx, buf, USIZE_C(32), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(30));

    /* Find Last 0x55 in range [0, 32). Should return 31 (last odd index). */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndex(&idx, buf, USIZE_C(32), U8_C(0x55));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(31));

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

    /* Find Last value 50 in range [0, 256). Should be at index 50. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndex(&idx, buf, USIZE_C(256), U8_C(50));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(50));

    /* Find Last value 255 in range [0, 256). Should be at index 255. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndex(&idx, buf, USIZE_C(256), U8_C(255));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(255));

    /* Find Last value 0 in range [0, 256). Should be at index 0 (if 0 is only once). */
    /* This case is tricky because 0 appears only once. The test must accurately reflect this. */
    /* If the buffer is 0,1,2...255, then 0 is only at index 0. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndex(&idx, buf, USIZE_C(256), U8_C(0));
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

    /* Single byte buffer */
    buf[0] = 0xAA;

    /* Find 0xAA */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndex(&idx, buf, USIZE_C(1), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    /* Find 0xBB (not present) */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndex(&idx, buf, USIZE_C(1), U8_C(0xBB));
    assert(status == RESULT_FAILURE);

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

    /* Init with pattern 0..255 repeating */
    for (i = 0; i < 1024; ++i)
    {
        buf[i] = (u8)(i % 256);
    }

    /* Find Last 100.
     * Occurrences are at 100, 356 (100+256), 612 (100+2*256), 868 (100+3*256).
     * Should find 868. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndex(&idx, buf, USIZE_C(1024), U8_C(100));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(868));

    /* Find Last 255.
     * Occurrences are at 255, 511, 767, 1023.
     * Should find 1023. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndex(&idx, buf, USIZE_C(1024), U8_C(255));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(1023));

    printf("PASSED\n");
}


void
U32_Buffer(void)
{
    u32   buf[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_Buffer -> ");

    /* Init: 0x00000000 */
    kdi_Fill_u8((u8 *)buf, sizeof(buf), 0);

    /* Set bytes at index 3 and 12 to 0xAA */
    ((u8 *)buf)[3]  = 0xAA;
    ((u8 *)buf)[12] = 0xAA;

    /* Find Last 0xAA */
    idx             = 999;
    status          = kdGenMemOpsFindLastByteIndex(&idx, buf, sizeof(buf), U8_C(0xAA));

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
    status = kdGenMemOpsFindLastByteIndex(&idx, buf, USIZE_C(32), U8_C(0x77));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(31));

    /* Find Last 0x00 (not present) */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndex(&idx, buf, USIZE_C(32), U8_C(0x00));
    assert(status == RESULT_FAILURE);

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


    /* Find Last 0xFF in range [0, 100). Should return index 90. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndex(&idx, buf, USIZE_C(100), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(90));

    /* Find Last 0x00 in range [0, 100). Should return index 99. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndex(&idx, buf, USIZE_C(100), U8_C(0x00));
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

    /* Odd size: 33 bytes */
    kdi_Fill_u8(buf, USIZE_C(33), U8_C(0x77));
    buf[5]  = 0x88;
    buf[17] = 0x88;
    buf[32] = 0x88;

    /* Find Last 0x88 in range [0, 33). */
    idx     = 999;
    status  = kdGenMemOpsFindLastByteIndex(&idx, buf, USIZE_C(33), U8_C(0x88));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(32));

    /* Find Last 0x77 in range [0, 33). Should be at index 31. */
    idx    = 999;
    status = kdGenMemOpsFindLastByteIndex(&idx, buf, USIZE_C(33), U8_C(0x77));
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
    FindNone();
    FindFirst();
    FindLast();
    FindMultiple();
    AlternatingPattern();
    SequentialValues();
    SmallBuffer();
    LargeBuffer();
    U32_Buffer();
    AllSameValue();
    SparseMatches();
    OddSizes();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
