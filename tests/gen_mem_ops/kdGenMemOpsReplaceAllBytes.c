/**
 * @file kdGenMemOpsReplaceAllBytes.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsReplaceAllBytes function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsReplaceAllBytes function test"
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
    u8    buf[16];
    usize count = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* ptr is null -> failure */
    status = GenMemOpsReplaceAllBytes(null, USIZE_C(16), &count, U8_C(0), U8_C(1));
    assert(status == RESULT_FAILURE);

    /* sz is zero -> failure */
    status = GenMemOpsReplaceAllBytes(buf, USIZE_C(0), &count, U8_C(0), U8_C(1));
    assert(status == RESULT_FAILURE);

    /* count is null -> failure */
    status = GenMemOpsReplaceAllBytes(buf, USIZE_C(16), null, U8_C(0), U8_C(1));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ReplaceNone(void)
{
    u8    buf[16];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ReplaceNone -> ");

    /* Init: 0x00 */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Try to find 0xFF. Should find none. */
    status = GenMemOpsReplaceAllBytes(buf, USIZE_C(16), &count, U8_C(0xFF), U8_C(0xAA));

    /* Returns SUCCESS if no error, count should be 0 */
    assert(status == RESULT_SUCCESS);
    assert(count == 0);

    /* Verify unchanged */
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
ReplaceAllOccurrences(void)
{
    u8    buf[16];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ReplaceAllOccurrences -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Set targets at 2, 5, 8, 12 */
    buf[2]  = 0xFF;
    buf[5]  = 0xFF;
    buf[8]  = 0xFF;
    buf[12] = 0xFF;

    /* Replace 0xFF with 0xAA */
    status  = GenMemOpsReplaceAllBytes(buf, USIZE_C(16), &count, U8_C(0xFF), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(count == 4);

    assert(buf[2] == 0xAA);
    assert(buf[5] == 0xAA);
    assert(buf[8] == 0xAA);
    assert(buf[12] == 0xAA);

    assert(buf[0] == 0x00); /* Untouched */

    printf("PASSED\n");
}


void
ReplaceEveryByte(void)
{
    u8    buf[16];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ReplaceEveryByte -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0xFF));

    /* Replace all 0xFF with 0x00 */
    status = GenMemOpsReplaceAllBytes(buf, USIZE_C(16), &count, U8_C(0xFF), U8_C(0x00));

    assert(status == RESULT_SUCCESS);
    assert(count == 16);

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
ReplaceSameValue(void)
{
    u8    buf[8];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ReplaceSameValue -> ");

    kdi_FillVal(buf, USIZE_C(8), U8_C(0x00));
    buf[3] = 0x55;
    buf[6] = 0x55;

    /* Replace 0x55 with 0x55. Should count 2. */
    status = GenMemOpsReplaceAllBytes(buf, USIZE_C(8), &count, U8_C(0x55), U8_C(0x55));

    assert(status == RESULT_SUCCESS);
    assert(count == 2);
    assert(buf[3] == 0x55);
    assert(buf[6] == 0x55);

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    static u8 buf[2000];
    usize     count;
    bool      status;
    usize     i;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    kdi_FillVal(buf, USIZE_C(2000), U8_C(0x00));

    /* Fill every 10th byte with 0x77 */
    for (i = 0; i < 2000; i += 10)
    {
        buf[i] = 0x77;
    }
    /* Total 200 occurrences */

    status = GenMemOpsReplaceAllBytes(buf, USIZE_C(2000), &count, U8_C(0x77), U8_C(0x88));

    assert(status == RESULT_SUCCESS);
    assert(count == 200);

    /* Verify first and last */
    assert(buf[0] == 0x88);
    assert(buf[1990] == 0x88);

    /* Verify intermediate non-targets unchanged */
    assert(buf[1] == 0x00);

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
    ReplaceAllOccurrences();
    ReplaceEveryByte();
    ReplaceSameValue();
    LargeBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
