/**
 * @file kdGenMemOpsCountBytes.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsCountBytes function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsCountBytes function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8    buf[16];
    usize count = 55; /* Init with garbage */
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* count pointer is null -> failure */
    status = kdGenMemOpsCountBytes(null, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountBytes(&count, null, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* sz is zero -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(0), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* Valid arguments */
    count  = 55;
    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(16), U8_C(0x00));
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

    /* Init with 0x00 */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Count 0xFF */
    count  = 999;
    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(16), U8_C(0xFF));

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

    /* Init with 0xAA */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));

    /* Count 0xAA */
    count  = 0;
    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(16), U8_C(0xAA));

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

    /* Init with 0x00, set one byte to 0xFF */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));
    buf[7] = 0xFF;

    /* Count 0xFF */
    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(1));

    printf("PASSED\n");
}


void
CountMixed(void)
{
    u8    buf[10];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountMixed -> ");

    /* Pattern: 0, 1, 2, 0, 1, 2, 0, 1, 2, 0 */
    buf[0] = 0;
    buf[1] = 1;
    buf[2] = 2;
    buf[3] = 0;
    buf[4] = 1;
    buf[5] = 2;
    buf[6] = 0;
    buf[7] = 1;
    buf[8] = 2;
    buf[9] = 0;

    /* Count 0x00. Should appear 4 times. */
    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(10), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(4));

    /* Count 0x01. Should appear 3 times. */
    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(10), U8_C(0x01));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(3));

    /* Count 0x02. Should appear 3 times. */
    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(10), U8_C(0x02));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(3));

    /* Count 0x03. Should appear 0 times. */
    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(10), U8_C(0x03));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    printf("PASSED\n");
}


void
CountZeros(void)
{
    u8    buf[32];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountZeros -> ");

    /* All zeros */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));

    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(32), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(32));

    /* Set half to non-zero */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xFF));

    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(32), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

    printf("PASSED\n");
}


void
CountMaxByte(void)
{
    u8    buf[32];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountMaxByte -> ");

    /* All 0xFF */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xFF));

    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(32), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(32));

    /* Set some to different values */
    buf[0]  = 0x00;
    buf[15] = 0x7F;
    buf[31] = 0xFE;

    status  = kdGenMemOpsCountBytes(&count, buf, USIZE_C(32), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(29));

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

    /* Count 0xAA (even indices) */
    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(32), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

    /* Count 0x55 (odd indices) */
    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(32), U8_C(0x55));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

    printf("PASSED\n");
}


void
SequentialValues(void)
{
    u8    buf[256];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "SequentialValues -> ");

    /* Init: 0..255 */
    kdi_FillSeq_u8(buf, USIZE_C(256), U8_C(0x00));

    /* Each value appears exactly once */
    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(256), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(1));

    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(256), U8_C(0x7F));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(1));

    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(256), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(1));

    printf("PASSED\n");
}


void
SmallBuffer(void)
{
    u8    buf[1];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "SmallBuffer -> ");

    /* Single byte buffer - match */
    buf[0] = 0x42;
    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(1), U8_C(0x42));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(1));

    /* Single byte buffer - no match */
    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(1), U8_C(0x43));
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

    /* Init with pattern */
    for (i = 0; i < 1024; ++i)
    {
        buf[i] = (u8)(i % 256);
    }

    /* Count specific value that appears multiple times */
    /* Value 0 appears at indices: 0, 256, 512, 768 = 4 times */
    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(1024), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(4));

    /* Value 100 appears at indices: 100, 356, 612, 868 = 4 times */
    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(1024), U8_C(100));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(4));

    printf("PASSED\n");
}


void
U16_Buffer(void)
{
    u16   buf[8];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "U16_Buffer -> ");

    /* Fill with u16 values, but count bytes within them */
    buf[0] = 0x1122;
    buf[1] = 0x3344;
    buf[2] = 0x2211;
    buf[3] = 0x4433;
    buf[4] = 0x1122;
    buf[5] = 0x3344;
    buf[6] = 0x2211;
    buf[7] = 0x4433;

    /* Count byte 0x22 (appears in different positions depending on endianness) */
    /* We don't know endianness, but we know total count */
    status = kdGenMemOpsCountBytes(&count, buf, sizeof(buf), U8_C(0x22));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(4)); /* 2 in buf[0], 2 in buf[4] */

    /* Count byte 0x11 */
    status = kdGenMemOpsCountBytes(&count, buf, sizeof(buf), U8_C(0x11));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(4)); /* 2 in buf[2], 2 in buf[6] */

    printf("PASSED\n");
}


void
U32_Buffer(void)
{
    u32   buf[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_Buffer -> ");

    /* Init: 0x00000000 */
    kdi_Fill_u8((u8 *)buf, sizeof(buf), 0);

    /* Set specific bytes */
    ((u8 *)buf)[0]  = 0xAA;
    ((u8 *)buf)[7]  = 0xAA;
    ((u8 *)buf)[8]  = 0xAA;
    ((u8 *)buf)[15] = 0xAA;

    /* Count 0xAA */
    status          = kdGenMemOpsCountBytes(&count, buf, sizeof(buf), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(4));

    /* Count 0x00 (total 16 bytes, 4 are 0xAA, so 12 are 0x00) */
    status = kdGenMemOpsCountBytes(&count, buf, sizeof(buf), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(12));

    printf("PASSED\n");
}


void
CountAtBoundaries(void)
{
    u8    buf[16];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountAtBoundaries -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Set first and last byte */
    buf[0]  = 0xFF;
    buf[15] = 0xFF;

    status  = kdGenMemOpsCountBytes(&count, buf, USIZE_C(16), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(2));

    /* Count zeros */
    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(16), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(14));

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

    /* Count 0xFF (18 out of 30) */
    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(30), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(18));

    /* Count 0x00 (12 out of 30) */
    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(30), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(12));

    printf("PASSED\n");
}


void
PartialBuffer(void)
{
    u8    buf[32];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "PartialBuffer -> ");

    /* Fill entire buffer */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xAA));

    /* But only count first 10 bytes */
    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(10), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(10));

    /* Modify bytes beyond count range, should not affect result */
    buf[20] = 0x00;
    buf[25] = 0x00;
    buf[31] = 0x00;

    status  = kdGenMemOpsCountBytes(&count, buf, USIZE_C(10), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(10));

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

    /* Count consecutive 0xBB */
    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(32), U8_C(0xBB));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

    /* Count consecutive 0xCC */
    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(32), U8_C(0xCC));
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

    /* Fill with 0x00 */
    kdi_Fill_u8(buf, USIZE_C(100), U8_C(0x00));

    /* Set every 10th byte to 0xFF */
    for (i = 0; i < 100; i += 10)
    {
        buf[i] = 0xFF;
    }

    /* Count sparse 0xFF (10 matches) */
    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(100), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(10));

    /* Count dense 0x00 (90 matches) */
    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(100), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(90));

    printf("PASSED\n");
}


void
OddSizes(void)
{
    u8    buf[33];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "OddSizes -> ");

    /* Odd size: 33 bytes */
    kdi_Fill_u8(buf, USIZE_C(33), U8_C(0x77));

    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(33), U8_C(0x77));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(33));

    /* Size 17 */
    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(17), U8_C(0x77));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(17));

    /* Size 7 */
    status = kdGenMemOpsCountBytes(&count, buf, USIZE_C(7), U8_C(0x77));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(7));

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
    CountMixed();
    CountZeros();
    CountMaxByte();
    AlternatingPattern();
    SequentialValues();
    SmallBuffer();
    LargeBuffer();
    U16_Buffer();
    U32_Buffer();
    CountAtBoundaries();
    RepeatingGroups();
    PartialBuffer();
    ConsecutiveMatches();
    SparseMatches();
    OddSizes();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
