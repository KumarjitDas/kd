/**
 * @file kdGenMemOpsIsBytes.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsIsBytes function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsIsBytes function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
ResultNull(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ResultNull -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* result pointer is null -> failure */
    status = kdGenMemOpsIsBytes(null, buf, USIZE_C(16), U8_C(0x00));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
PtrNull(void)
{
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "PtrNull -> ");

    /* ptr is null (with non-zero size) -> failure */
    status = kdGenMemOpsIsBytes(&result, null, USIZE_C(16), U8_C(0x00));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SizeZero(void)
{
    u8   buf[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "SizeZero -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xFF));

    /* sz is zero -> failure */
    status = kdGenMemOpsIsBytes(&result, buf, USIZE_C(0), U8_C(0xFF));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
BufferIsAllTargetByte_Zeros(void)
{
    u8   buf[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "BufferIsAllTargetByte_Zeros -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    result = false;
    status = kdGenMemOpsIsBytes(&result, buf, USIZE_C(16), U8_C(0x00));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
BufferIsAllTargetByte_Ones(void)
{
    u8   buf[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "BufferIsAllTargetByte_Ones -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xFF));

    result = false;
    status = kdGenMemOpsIsBytes(&result, buf, USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
BufferIsAllTargetByte_CustomValue(void)
{
    u8   buf[32];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "BufferIsAllTargetByte_CustomValue -> ");

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x42));

    result = false;
    status = kdGenMemOpsIsBytes(&result, buf, USIZE_C(32), U8_C(0x42));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
BufferIsNotAllTargetByte_DifferentAtStart(void)
{
    u8   buf[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "BufferIsNotAllTargetByte_DifferentAtStart -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));

    /* Set first byte to different value */
    buf[0] = U8_C(0xBB);

    result = true;
    status = kdGenMemOpsIsBytes(&result, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
BufferIsNotAllTargetByte_DifferentAtEnd(void)
{
    u8   buf[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "BufferIsNotAllTargetByte_DifferentAtEnd -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));

    /* Set last byte to different value */
    buf[15] = U8_C(0xBB);

    result = true;
    status = kdGenMemOpsIsBytes(&result, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
BufferIsNotAllTargetByte_DifferentAtMiddle(void)
{
    u8   buf[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "BufferIsNotAllTargetByte_DifferentAtMiddle -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));

    /* Set middle byte to different value */
    buf[8] = U8_C(0xBB);

    result = true;
    status = kdGenMemOpsIsBytes(&result, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
SingleByte_Match(void)
{
    u8   val;
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "SingleByte_Match -> ");

    val    = U8_C(0x77);
    result = false;
    status = kdGenMemOpsIsBytes(&result, &val, USIZE_C(1), U8_C(0x77));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
SingleByte_NoMatch(void)
{
    u8   val;
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "SingleByte_NoMatch -> ");

    val    = U8_C(0x77);
    result = true;
    status = kdGenMemOpsIsBytes(&result, &val, USIZE_C(1), U8_C(0x88));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
LargeBuffer_AllMatch(void)
{
    u8    buf[256];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffer_AllMatch -> ");

    /* Fill with target byte */
    for (i = 0; i < 256; ++i)
    {
        buf[i] = U8_C(0x5A);
    }

    result = false;
    status = kdGenMemOpsIsBytes(&result, buf, USIZE_C(256), U8_C(0x5A));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
LargeBuffer_OneMismatch(void)
{
    u8    buf[256];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffer_OneMismatch -> ");

    /* Fill with target byte */
    for (i = 0; i < 256; ++i)
    {
        buf[i] = U8_C(0x5A);
    }

    /* Change one byte */
    buf[128] = U8_C(0x5B);

    result = true;
    status = kdGenMemOpsIsBytes(&result, buf, USIZE_C(256), U8_C(0x5A));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
AllDifferentValues(void)
{
    u8   buf[8];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "AllDifferentValues -> ");

    /* Fill with sequential values (no byte matches the target) */
    kdi_FillSeq_u8(buf, USIZE_C(8), U8_C(0x00));

    result = true;
    status = kdGenMemOpsIsBytes(&result, buf, USIZE_C(8), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
VariousTargetBytes(void)
{
    u8   buf[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "VariousTargetBytes -> ");

    /* Test with 0x00 */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));
    result = false;
    status = kdGenMemOpsIsBytes(&result, buf, USIZE_C(16), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Test with 0xFF */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xFF));
    result = false;
    status = kdGenMemOpsIsBytes(&result, buf, USIZE_C(16), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Test with 0x01 */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x01));
    result = false;
    status = kdGenMemOpsIsBytes(&result, buf, USIZE_C(16), U8_C(0x01));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Test with 0x7F */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x7F));
    result = false;
    status = kdGenMemOpsIsBytes(&result, buf, USIZE_C(16), U8_C(0x7F));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Test with 0x80 */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x80));
    result = false;
    status = kdGenMemOpsIsBytes(&result, buf, USIZE_C(16), U8_C(0x80));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
OddSizes(void)
{
    u8   buf[20];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "OddSizes -> ");

    /* Size 1 */
    kdi_Fill_u8(buf, USIZE_C(1), U8_C(0x11));
    result = false;
    status = kdGenMemOpsIsBytes(&result, buf, USIZE_C(1), U8_C(0x11));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Size 3 */
    kdi_Fill_u8(buf, USIZE_C(3), U8_C(0x22));
    result = false;
    status = kdGenMemOpsIsBytes(&result, buf, USIZE_C(3), U8_C(0x22));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Size 5 */
    kdi_Fill_u8(buf, USIZE_C(5), U8_C(0x33));
    result = false;
    status = kdGenMemOpsIsBytes(&result, buf, USIZE_C(5), U8_C(0x33));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Size 7 */
    kdi_Fill_u8(buf, USIZE_C(7), U8_C(0x44));
    result = false;
    status = kdGenMemOpsIsBytes(&result, buf, USIZE_C(7), U8_C(0x44));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Size 9 */
    kdi_Fill_u8(buf, USIZE_C(9), U8_C(0x55));
    result = false;
    status = kdGenMemOpsIsBytes(&result, buf, USIZE_C(9), U8_C(0x55));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Size 11 */
    kdi_Fill_u8(buf, USIZE_C(11), U8_C(0x66));
    result = false;
    status = kdGenMemOpsIsBytes(&result, buf, USIZE_C(11), U8_C(0x66));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
PartialMatch(void)
{
    u8   buf[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "PartialMatch -> ");

    /* Fill first half with target byte, second half with different byte */
    kdi_Fill_u8(buf, USIZE_C(8), U8_C(0xAA));
    kdi_Fill_u8(&buf[8], USIZE_C(8), U8_C(0xBB));

    /* Should return false - not all bytes match */
    result = true;
    status = kdGenMemOpsIsBytes(&result, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    ResultNull();
    PtrNull();
    SizeZero();
    BufferIsAllTargetByte_Zeros();
    BufferIsAllTargetByte_Ones();
    BufferIsAllTargetByte_CustomValue();
    BufferIsNotAllTargetByte_DifferentAtStart();
    BufferIsNotAllTargetByte_DifferentAtEnd();
    BufferIsNotAllTargetByte_DifferentAtMiddle();
    SingleByte_Match();
    SingleByte_NoMatch();
    LargeBuffer_AllMatch();
    LargeBuffer_OneMismatch();
    AllDifferentValues();
    VariousTargetBytes();
    OddSizes();
    PartialMatch();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}