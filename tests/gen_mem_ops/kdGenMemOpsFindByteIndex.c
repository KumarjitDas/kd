/**
 * @file kdGenMemOpsFindByteIndex.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindByteIndex function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindByteIndex function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8    buf[16];
    usize idx = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* idx pointer is null -> failure */
    status = kdGenMemOpsFindByteIndex(null, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    idx    = 55;
    status = kdGenMemOpsFindByteIndex(&idx, null, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* sz is zero -> failure */
    idx    = 55;
    status = kdGenMemOpsFindByteIndex(&idx, buf, USIZE_C(0), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* Valid arguments - found at index 0 */
    idx    = 55;
    status = kdGenMemOpsFindByteIndex(&idx, buf, USIZE_C(16), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

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

    /* Find 0xFF - not present */
    idx    = 999;
    status = kdGenMemOpsFindByteIndex(&idx, buf, USIZE_C(16), U8_C(0xFF));

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

    /* Set first byte */
    buf[0] = 0xFF;

    /* Find 0xFF */
    status = kdGenMemOpsFindByteIndex(&idx, buf, USIZE_C(16), U8_C(0xFF));

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

    /* Set last byte */
    buf[15] = 0xFF;

    /* Find 0xFF */
    status  = kdGenMemOpsFindByteIndex(&idx, buf, USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(15));

    printf("PASSED\n");
}


void
FindMiddle(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindMiddle -> ");

    /* Init: 0x00 */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Set middle byte */
    buf[7] = 0xFF;

    /* Find 0xFF */
    status = kdGenMemOpsFindByteIndex(&idx, buf, USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(7));

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

    /* Set at 5, 10, 15 */
    buf[5]  = 0xFF;
    buf[10] = 0xFF;
    buf[15] = 0xFF;

    /* Find 0xFF. Should return FIRST occurrence (Index 5). */
    status  = kdGenMemOpsFindByteIndex(&idx, buf, USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(5));

    printf("PASSED\n");
}


void
FindZero(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindZero -> ");

    /* Fill with non-zero */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));

    /* Set one zero byte */
    buf[9] = 0x00;

    /* Find 0x00 */
    status = kdGenMemOpsFindByteIndex(&idx, buf, USIZE_C(16), U8_C(0x00));

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

    /* Find 0xAA (even indices). Should return 0. */
    status = kdGenMemOpsFindByteIndex(&idx, buf, USIZE_C(32), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    /* Find 0x55 (odd indices). Should return 1. */
    status = kdGenMemOpsFindByteIndex(&idx, buf, USIZE_C(32), U8_C(0x55));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(1));

    /* Find 0xBB (not present). */
    status = kdGenMemOpsFindByteIndex(&idx, buf, USIZE_C(32), U8_C(0xBB));
    assert(status == RESULT_FAILURE);

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

    /* Find value 50. Should be at index 50. */
    status = kdGenMemOpsFindByteIndex(&idx, buf, USIZE_C(256), U8_C(50));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(50));

    /* Find value 0. Should be at index 0. */
    status = kdGenMemOpsFindByteIndex(&idx, buf, USIZE_C(256), U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    /* Find value 255. Should be at index 255. */
    status = kdGenMemOpsFindByteIndex(&idx, buf, USIZE_C(256), U8_C(255));
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

    /* Single byte buffer - match */
    buf[0] = 0x42;
    status = kdGenMemOpsFindByteIndex(&idx, buf, USIZE_C(1), U8_C(0x42));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    /* Single byte buffer - no match */
    status = kdGenMemOpsFindByteIndex(&idx, buf, USIZE_C(1), U8_C(0x43));
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

    /* Init with pattern */
    for (i = 0; i < 1024; ++i)
    {
        buf[i] = (u8)(i % 256);
    }

    /* Find value 100. First occurrence at index 100. */
    status = kdGenMemOpsFindByteIndex(&idx, buf, USIZE_C(1024), U8_C(100));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(100));

    /* Find value 0. First occurrence at index 0. */
    status = kdGenMemOpsFindByteIndex(&idx, buf, USIZE_C(1024), U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    printf("PASSED\n");
}


void
U16_Buffer(void)
{
    u16   buf[8];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U16_Buffer -> ");

    /* Fill with u16 values, but find bytes within them */
    buf[0] = 0x1122;
    buf[1] = 0x3344;
    buf[2] = 0x2211;
    buf[3] = 0x4433;
    buf[4] = 0x1122;
    buf[5] = 0x3344;
    buf[6] = 0x2211;
    buf[7] = 0x4433;

    /* Find byte 0x22 (appears in different positions depending on endianness) */
    status = kdGenMemOpsFindByteIndex(&idx, buf, sizeof(buf), U8_C(0x22));
    assert(status == RESULT_SUCCESS);
    /* Index depends on endianness, but should find it */

    /* Find byte 0xFF (not present) */
    status = kdGenMemOpsFindByteIndex(&idx, buf, sizeof(buf), U8_C(0xFF));
    assert(status == RESULT_FAILURE);

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

    /* Set byte at offset 7 to 0xAA */
    ((u8 *)buf)[7] = 0xAA;

    /* Find 0xAA */
    status         = kdGenMemOpsFindByteIndex(&idx, buf, sizeof(buf), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(7));

    /* Find 0xBB (not present) */
    status = kdGenMemOpsFindByteIndex(&idx, buf, sizeof(buf), U8_C(0xBB));
    assert(status == RESULT_FAILURE);

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

    /* Find 0x77. Should return index 0 (first occurrence). */
    status = kdGenMemOpsFindByteIndex(&idx, buf, USIZE_C(32), U8_C(0x77));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    /* Find 0x88 (not present). */
    status = kdGenMemOpsFindByteIndex(&idx, buf, USIZE_C(32), U8_C(0x88));
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

    /* Find 0xFF. Should return index 0 (first occurrence). */
    status = kdGenMemOpsFindByteIndex(&idx, buf, USIZE_C(100), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    /* Find 0x00. Should return index 1 (first non-sparse). */
    status = kdGenMemOpsFindByteIndex(&idx, buf, USIZE_C(100), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(1));

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

    /* Find 0x88 */
    status  = kdGenMemOpsFindByteIndex(&idx, buf, USIZE_C(33), U8_C(0x88));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(17));

    /* Size 17 */
    status = kdGenMemOpsFindByteIndex(&idx, buf, USIZE_C(17), U8_C(0x88));
    assert(status == RESULT_FAILURE);

    /* Size 7 */
    status = kdGenMemOpsFindByteIndex(&idx, buf, USIZE_C(7), U8_C(0x77));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

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
    FindMiddle();
    FindMultiple();
    FindZero();
    AlternatingPattern();
    SequentialValues();
    SmallBuffer();
    LargeBuffer();
    U16_Buffer();
    U32_Buffer();
    AllSameValue();
    SparseMatches();
    OddSizes();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}