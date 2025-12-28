/**
 * @file kdGenMemOpsCountNotBytes.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsCountNotBytes function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsCountNotBytes function test"
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
    status = kdGenMemOpsCountNotBytes(null, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountNotBytes(&count, null, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* sz is zero -> failure, count should be zeroed */
    count  = 55;
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(0), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(count == USIZE_C(0));

    /* Valid arguments */
    count  = 55;
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(16), U8_C(0x00));
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

    /* Init all with 0xAA */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));

    /* Count NOT 0xAA. Should be 0. */
    count  = 999;
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(16), U8_C(0xAA));

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

    /* Init all with 0xAA */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));

    /* Count NOT 0xFF. Should be 16. */
    count  = 0;
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(16), U8_C(0xFF));

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

    /* Count NOT 0x00. Should be 1 (only index 7). */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(16), U8_C(0x00));

    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(1));

    /* Count NOT 0xFF. Should be 15. */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(16), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(15));

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

    /* Count NOT 0x00. */
    /* Total 10. 0x00 appears 4 times. NOT 0x00 should be 6. */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(10), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(6));

    /* Count NOT 0x01. Should be 7. */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(10), U8_C(0x01));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(7));

    /* Count NOT 0x03. None match 0x03, so all are NOT 0x03. */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(10), U8_C(0x03));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(10));

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

    /* Count NOT 0x00. Should be 0. */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(32), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    /* Count NOT 0x01. All are 0x00, so all are NOT 0x01. */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(32), U8_C(0x01));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(32));

    /* Set half to 0xFF */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xFF));

    /* Count NOT 0x00. First 16 are 0xFF (NOT 0x00), last 16 are 0x00. */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(32), U8_C(0x00));
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

    /* Count NOT 0xFF. Should be 0. */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(32), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    /* Set some to different values */
    buf[0]  = 0x00;
    buf[15] = 0x7F;
    buf[31] = 0xFE;

    /* Count NOT 0xFF. Should be 3. */
    status  = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(32), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(3));

    /* Count NOT 0x00. Only index 0 is 0x00. */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(32), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(31));

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

    /* Count NOT 0xAA (should be 0x55 bytes, 16 of them) */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(32), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

    /* Count NOT 0x55 (should be 0xAA bytes, 16 of them) */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(32), U8_C(0x55));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

    /* Count NOT 0x00 (none are 0x00, so all are NOT 0x00) */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(32), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(32));

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

    /* Each value appears exactly once, so NOT that value = 255 */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(256), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(255));

    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(256), U8_C(0x7F));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(255));

    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(256), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(255));

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
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(1), U8_C(0x42));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    /* Single byte buffer - no match */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(1), U8_C(0x43));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(1));

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

    /* Count NOT 0x00. Value 0 appears at indices: 0, 256, 512, 768 = 4 times.
     * So NOT 0x00 = 1024 - 4 = 1020. */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(1024), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(1020));

    /* Count NOT 100. Value 100 appears 4 times, so NOT 100 = 1020. */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(1024), U8_C(100));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(1020));

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

    /* Set specific bytes to 0xAA */
    ((u8 *)buf)[0]  = 0xAA;
    ((u8 *)buf)[7]  = 0xAA;
    ((u8 *)buf)[8]  = 0xAA;
    ((u8 *)buf)[15] = 0xAA;

    /* Count NOT 0x00. 4 bytes are 0xAA (NOT 0x00). */
    status          = kdGenMemOpsCountNotBytes(&count, buf, sizeof(buf), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(4));

    /* Count NOT 0xAA. 4 bytes are 0xAA, so 12 are NOT 0xAA. */
    status = kdGenMemOpsCountNotBytes(&count, buf, sizeof(buf), U8_C(0xAA));
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

    /* Set first and last byte to 0xFF */
    buf[0]  = 0xFF;
    buf[15] = 0xFF;

    /* Count NOT 0x00. Should be 2 (first and last). */
    status  = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(16), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(2));

    /* Count NOT 0xFF. Middle 14 bytes are NOT 0xFF. */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(16), U8_C(0xFF));
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

    /* Count NOT 0xFF (12 out of 30 are 0x00) */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(30), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(12));

    /* Count NOT 0x00 (18 out of 30 are 0xFF) */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(30), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(18));

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

    /* Count NOT 0xBB (last 16 are NOT 0xBB) */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(32), U8_C(0xBB));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(16));

    /* Count NOT 0xCC (first 16 are NOT 0xCC) */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(32), U8_C(0xCC));
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

    /* Count NOT 0xFF (90 are NOT 0xFF) */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(100), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(90));

    /* Count NOT 0x00 (10 are NOT 0x00) */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(100), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(10));

    printf("PASSED\n");
}


void
OddSizes(void)
{
    u8    buf[33];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "OddSizes -> ");

    /* Odd size: 33 bytes, fill with 0x77 */
    kdi_Fill_u8(buf, USIZE_C(33), U8_C(0x77));

    /* Count NOT 0x77. Should be 0. */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(33), U8_C(0x77));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    /* Count NOT 0x00. Should be 33. */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(33), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(33));

    /* Size 17 */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(17), U8_C(0x77));
    assert(status == RESULT_SUCCESS);
    assert(count == USIZE_C(0));

    /* Size 7 */
    status = kdGenMemOpsCountNotBytes(&count, buf, USIZE_C(7), U8_C(0x00));
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
    U32_Buffer();
    CountAtBoundaries();
    RepeatingGroups();
    ConsecutiveMatches();
    SparseMatches();
    OddSizes();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}