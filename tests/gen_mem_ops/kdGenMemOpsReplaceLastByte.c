/**
 * @file kdGenMemOpsReplaceLastByte.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsReplaceLastByte function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsReplaceLastByte function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


static void
kdi_FillVal(u8 *dst, usize sz, u8 val)
{
    usize i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        dst[i] = val;
    }
}


void
BasicArguments(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* ptr is null -> failure */
    status = GenMemOpsReplaceLastByte(null, USIZE_C(16), U8_C(0), U8_C(1));
    assert(status == RESULT_FAILURE);

    /* sz is zero -> failure */
    status = GenMemOpsReplaceLastByte(buf, USIZE_C(0), U8_C(0), U8_C(1));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ReplaceNone(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ReplaceNone -> ");

    /* Init: 0x00 */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Try to replace 0xFF (not present) with 0xAA */
    status = GenMemOpsReplaceLastByte(buf, USIZE_C(16), U8_C(0xFF), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);

    /* Verify buffer is unchanged */
    {
        usize i;
        for (i = 0; i < 16; ++i)
        {
            assert(buf[i] == 0x00);
        }
    }

    printf("PASSED\n");
}


void
ReplaceSingle(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ReplaceSingle -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Set target at index 5 */
    buf[5] = 0xFF;

    /* Replace 0xFF with 0xAA */
    status = GenMemOpsReplaceLastByte(buf, USIZE_C(16), U8_C(0xFF), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(buf[5] == 0xAA);

    printf("PASSED\n");
}


void
ReplaceLastOfMultiple(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ReplaceLastOfMultiple -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Targets at 2, 5, 8 */
    buf[2] = 0xFF;
    buf[5] = 0xFF;
    buf[8] = 0xFF;

    /* Replace Last 0xFF with 0xAA. Should be index 8. */
    status = GenMemOpsReplaceLastByte(buf, USIZE_C(16), U8_C(0xFF), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);

    /* Check Last is replaced */
    assert(buf[8] == 0xAA);

    /* Check previous ones are untouched */
    assert(buf[2] == 0xFF);
    assert(buf[5] == 0xFF);

    printf("PASSED\n");
}


void
ReplaceAtBoundaries(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ReplaceAtBoundaries -> ");

    /* Case 1: Last index */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));
    buf[15] = 0xFF;

    status  = GenMemOpsReplaceLastByte(buf, USIZE_C(16), U8_C(0xFF), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(buf[15] == 0xAA);

    /* Case 2: First index (only occurrence) */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));
    buf[0] = 0xFF;

    status = GenMemOpsReplaceLastByte(buf, USIZE_C(16), U8_C(0xFF), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(buf[0] == 0xAA);

    printf("PASSED\n");
}


void
ReplaceSameValue(void)
{
    u8   buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "ReplaceSameValue -> ");

    kdi_FillVal(buf, USIZE_C(4), U8_C(0x00));
    buf[3] = 0x55;

    /* Replace 0x55 with 0x55.
     * Logic should find it and write it (or just return success).
     */
    status = GenMemOpsReplaceLastByte(buf, USIZE_C(4), U8_C(0x55), U8_C(0x55));

    assert(status == RESULT_SUCCESS);
    assert(buf[3] == 0x55);

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    static u8 buf[2000];
    bool      status;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    kdi_FillVal(buf, USIZE_C(2000), U8_C(0x00));

    /* Set targets at 100, 1000, 1999 */
    buf[100]  = 0x77;
    buf[1000] = 0x77;
    buf[1999] = 0x77;

    /* Replace last 0x77 with 0x88 */
    status    = GenMemOpsReplaceLastByte(buf, USIZE_C(2000), U8_C(0x77), U8_C(0x88));

    assert(status == RESULT_SUCCESS);

    /* Verify 1999 changed */
    assert(buf[1999] == 0x88);

    /* Verify others unchanged */
    assert(buf[100] == 0x77);
    assert(buf[1000] == 0x77);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    ReplaceNone();
    ReplaceSingle();
    ReplaceLastOfMultiple();
    ReplaceAtBoundaries();
    ReplaceSameValue();
    LargeBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
