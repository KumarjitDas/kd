/**
 * @file kdGenMemOpsSetByteAt.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsSetByteAt function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsSetByteAt function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0));

    /* base is null -> failure */
    status = kdGenMemOpsSetByteAt(null, USIZE_C(16), USIZE_C(0), U8_C(0xFF));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = kdGenMemOpsSetByteAt(buf, USIZE_C(0), USIZE_C(0), U8_C(0xFF));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SetAtStart(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "SetAtStart -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0));

    /* Set first byte (index 0) */
    status = kdGenMemOpsSetByteAt(buf, USIZE_C(16), USIZE_C(0), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(buf[0] == U8_C(0xAA));
    /* Verify others untouched */
    assert(buf[1] == U8_C(1));
    assert(buf[2] == U8_C(2));

    printf("PASSED\n");
}


void
SetAtEnd(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "SetAtEnd -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0));

    /* Set last byte (index 15) */
    status = kdGenMemOpsSetByteAt(buf, USIZE_C(16), USIZE_C(15), U8_C(0xBB));

    assert(status == RESULT_SUCCESS);
    assert(buf[15] == U8_C(0xBB));
    /* Verify others untouched */
    assert(buf[13] == U8_C(13));
    assert(buf[14] == U8_C(14));

    printf("PASSED\n");
}


void
SetAtMiddle(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "SetAtMiddle -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0));

    /* Set middle byte (index 8) */
    status = kdGenMemOpsSetByteAt(buf, USIZE_C(16), USIZE_C(8), U8_C(0xCC));

    assert(status == RESULT_SUCCESS);
    assert(buf[8] == U8_C(0xCC));
    /* Verify neighbors untouched */
    assert(buf[7] == U8_C(7));
    assert(buf[9] == U8_C(9));

    printf("PASSED\n");
}


void
IndexOutOfBounds(void)
{
    u8   buf[10];
    bool status;

    printf(LOG_PREFIX_CSTR "IndexOutOfBounds -> ");

    kdi_FillSeq_u8(buf, USIZE_C(10), U8_C(0));

    /* Index == base_sz -> failure */
    status = kdGenMemOpsSetByteAt(buf, USIZE_C(10), USIZE_C(10), U8_C(0xFF));
    assert(status == RESULT_FAILURE);
    /* Verify last byte untouched */
    assert(buf[9] == U8_C(9));

    /* Index > base_sz -> failure */
    status = kdGenMemOpsSetByteAt(buf, USIZE_C(10), USIZE_C(100), U8_C(0xFF));
    assert(status == RESULT_FAILURE);

    /* Index far beyond base_sz -> failure */
    status = kdGenMemOpsSetByteAt(buf, USIZE_C(10), USIZE_C(1000), U8_C(0xFF));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SetAllBytes(void)
{
    u8    buf[8];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "SetAllBytes -> ");

    kdi_Fill_u8(buf, USIZE_C(8), U8_C(0));

    /* Set all bytes to different values */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        status = kdGenMemOpsSetByteAt(buf, USIZE_C(8), i, (u8)(U8_C(0xA0) + (u8)i));
        assert(status == RESULT_SUCCESS);
    }

    /* Verify all bytes set correctly */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        assert(buf[i] == (u8)(U8_C(0xA0) + (u8)i));
    }

    printf("PASSED\n");
}


void
SingleByte(void)
{
    u8   buf[1];
    bool status;

    printf(LOG_PREFIX_CSTR "SingleByte -> ");

    buf[0] = U8_C(0);

    /* Valid set at index 0 */
    status = kdGenMemOpsSetByteAt(buf, USIZE_C(1), USIZE_C(0), U8_C(0x42));
    assert(status == RESULT_SUCCESS);
    assert(buf[0] == U8_C(0x42));

    /* Invalid set at index 1 */
    status = kdGenMemOpsSetByteAt(buf, USIZE_C(1), USIZE_C(1), U8_C(0xFF));
    assert(status == RESULT_FAILURE);
    /* Verify buf[0] unchanged */
    assert(buf[0] == U8_C(0x42));

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    u8   buf[256];
    bool status;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    kdi_FillSeq_u8(buf, USIZE_C(256), U8_C(0));

    /* Set first byte */
    status = kdGenMemOpsSetByteAt(buf, USIZE_C(256), USIZE_C(0), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(buf[0] == U8_C(0xAA));

    /* Set last byte (255) */
    status = kdGenMemOpsSetByteAt(buf, USIZE_C(256), USIZE_C(255), U8_C(0xBB));
    assert(status == RESULT_SUCCESS);
    assert(buf[255] == U8_C(0xBB));

    /* Set middle byte (128) */
    status = kdGenMemOpsSetByteAt(buf, USIZE_C(256), USIZE_C(128), U8_C(0xCC));
    assert(status == RESULT_SUCCESS);
    assert(buf[128] == U8_C(0xCC));

    /* Out of bounds (index 256) */
    status = kdGenMemOpsSetByteAt(buf, USIZE_C(256), USIZE_C(256), U8_C(0xFF));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SetToZero(void)
{
    u8   buf[8];
    bool status;

    printf(LOG_PREFIX_CSTR "SetToZero -> ");

    kdi_Fill_u8(buf, USIZE_C(8), U8_C(0xFF));

    /* Set specific bytes to zero */
    status = kdGenMemOpsSetByteAt(buf, USIZE_C(8), USIZE_C(2), U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(buf[2] == U8_C(0));

    status = kdGenMemOpsSetByteAt(buf, USIZE_C(8), USIZE_C(5), U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(buf[5] == U8_C(0));

    /* Verify others remain 0xFF */
    assert(buf[0] == U8_C(0xFF));
    assert(buf[1] == U8_C(0xFF));
    assert(buf[3] == U8_C(0xFF));

    printf("PASSED\n");
}


void
SetToMax(void)
{
    u8   buf[8];
    bool status;

    printf(LOG_PREFIX_CSTR "SetToMax -> ");

    kdi_Fill_u8(buf, USIZE_C(8), U8_C(0));

    /* Set specific bytes to 0xFF */
    status = kdGenMemOpsSetByteAt(buf, USIZE_C(8), USIZE_C(1), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(buf[1] == U8_C(0xFF));

    status = kdGenMemOpsSetByteAt(buf, USIZE_C(8), USIZE_C(6), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(buf[6] == U8_C(0xFF));

    /* Verify others remain 0 */
    assert(buf[0] == U8_C(0));
    assert(buf[2] == U8_C(0));
    assert(buf[7] == U8_C(0));

    printf("PASSED\n");
}


void
OverwriteMultipleTimes(void)
{
    u8   buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "OverwriteMultipleTimes -> ");

    kdi_Fill_u8(buf, USIZE_C(4), U8_C(0));

    /* Set index 2 to different values multiple times */
    status = kdGenMemOpsSetByteAt(buf, USIZE_C(4), USIZE_C(2), U8_C(0x11));
    assert(status == RESULT_SUCCESS);
    assert(buf[2] == U8_C(0x11));

    status = kdGenMemOpsSetByteAt(buf, USIZE_C(4), USIZE_C(2), U8_C(0x22));
    assert(status == RESULT_SUCCESS);
    assert(buf[2] == U8_C(0x22));

    status = kdGenMemOpsSetByteAt(buf, USIZE_C(4), USIZE_C(2), U8_C(0x33));
    assert(status == RESULT_SUCCESS);
    assert(buf[2] == U8_C(0x33));

    /* Verify neighbors untouched */
    assert(buf[1] == U8_C(0));
    assert(buf[3] == U8_C(0));

    printf("PASSED\n");
}


void
MultipleSets(void)
{
    u8   buf[10];
    bool status;

    printf(LOG_PREFIX_CSTR "MultipleSets -> ");

    kdi_Fill_u8(buf, USIZE_C(10), U8_C(0));

    /* Set multiple bytes in sequence */
    status = kdGenMemOpsSetByteAt(buf, USIZE_C(10), USIZE_C(0), U8_C(10));
    assert(status == RESULT_SUCCESS);

    status = kdGenMemOpsSetByteAt(buf, USIZE_C(10), USIZE_C(3), U8_C(20));
    assert(status == RESULT_SUCCESS);

    status = kdGenMemOpsSetByteAt(buf, USIZE_C(10), USIZE_C(7), U8_C(30));
    assert(status == RESULT_SUCCESS);

    /* Verify all values */
    assert(buf[0] == U8_C(10));
    assert(buf[1] == U8_C(0));
    assert(buf[2] == U8_C(0));
    assert(buf[3] == U8_C(20));
    assert(buf[4] == U8_C(0));
    assert(buf[5] == U8_C(0));
    assert(buf[6] == U8_C(0));
    assert(buf[7] == U8_C(30));
    assert(buf[8] == U8_C(0));
    assert(buf[9] == U8_C(0));

    printf("PASSED\n");
}


void
EdgeValues(void)
{
    u8   buf[5];
    bool status;

    printf(LOG_PREFIX_CSTR "EdgeValues -> ");

    kdi_Fill_u8(buf, USIZE_C(5), U8_C(128));

    /* Set to minimum value (0) */
    status = kdGenMemOpsSetByteAt(buf, USIZE_C(5), USIZE_C(0), U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(buf[0] == U8_C(0));

    /* Set to value 1 */
    status = kdGenMemOpsSetByteAt(buf, USIZE_C(5), USIZE_C(1), U8_C(1));
    assert(status == RESULT_SUCCESS);
    assert(buf[1] == U8_C(1));

    /* Set to value 254 */
    status = kdGenMemOpsSetByteAt(buf, USIZE_C(5), USIZE_C(2), U8_C(254));
    assert(status == RESULT_SUCCESS);
    assert(buf[2] == U8_C(254));

    /* Set to maximum value (255) */
    status = kdGenMemOpsSetByteAt(buf, USIZE_C(5), USIZE_C(3), U8_C(255));
    assert(status == RESULT_SUCCESS);
    assert(buf[3] == U8_C(255));

    /* Verify last untouched */
    assert(buf[4] == U8_C(128));

    printf("PASSED\n");
}


void
SpecificPattern(void)
{
    u8   buf[8];
    bool status;

    printf(LOG_PREFIX_CSTR "SpecificPattern -> ");

    kdi_Fill_u8(buf, USIZE_C(8), U8_C(0));

    /* Create a specific pattern: 0xAA, 0x55, 0xAA, 0x55, ... */
    status = kdGenMemOpsSetByteAt(buf, USIZE_C(8), USIZE_C(0), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);

    status = kdGenMemOpsSetByteAt(buf, USIZE_C(8), USIZE_C(1), U8_C(0x55));
    assert(status == RESULT_SUCCESS);

    status = kdGenMemOpsSetByteAt(buf, USIZE_C(8), USIZE_C(2), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);

    status = kdGenMemOpsSetByteAt(buf, USIZE_C(8), USIZE_C(3), U8_C(0x55));
    assert(status == RESULT_SUCCESS);

    /* Verify pattern */
    assert(buf[0] == U8_C(0xAA));
    assert(buf[1] == U8_C(0x55));
    assert(buf[2] == U8_C(0xAA));
    assert(buf[3] == U8_C(0x55));
    assert(buf[4] == U8_C(0));
    assert(buf[5] == U8_C(0));

    printf("PASSED\n");
}


void
NoSideEffects(void)
{
    u8   buf[10];
    bool status;

    printf(LOG_PREFIX_CSTR "NoSideEffects -> ");

    kdi_FillSeq_u8(buf, USIZE_C(10), U8_C(0));

    /* Set middle byte */
    status = kdGenMemOpsSetByteAt(buf, USIZE_C(10), USIZE_C(5), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);

    /* Verify only index 5 changed */
    assert(buf[0] == U8_C(0));
    assert(buf[1] == U8_C(1));
    assert(buf[2] == U8_C(2));
    assert(buf[3] == U8_C(3));
    assert(buf[4] == U8_C(4));
    assert(buf[5] == U8_C(0xFF));
    assert(buf[6] == U8_C(6));
    assert(buf[7] == U8_C(7));
    assert(buf[8] == U8_C(8));
    assert(buf[9] == U8_C(9));

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    SetAtStart();
    SetAtEnd();
    SetAtMiddle();
    IndexOutOfBounds();
    SetAllBytes();
    SingleByte();
    LargeBuffer();
    SetToZero();
    SetToMax();
    OverwriteMultipleTimes();
    MultipleSets();
    EdgeValues();
    SpecificPattern();
    NoSideEffects();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}