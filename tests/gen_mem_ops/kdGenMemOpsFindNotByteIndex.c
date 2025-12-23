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


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindNotByteIndex function test"
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
    usize idx = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* idx pointer is null -> failure */
    status = GenMemOpsFindNotByteIndex(null, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindNotByteIndex(&idx, null, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* sz is zero -> failure */
    status = GenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(0), U8_C(0));
    assert(status == RESULT_FAILURE);

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
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Search for byte NOT equal to 0xAA.
     * Since all are 0xAA, this should fail.
     */
    status = GenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(16), U8_C(0xAA));

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
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Change first byte to 0xBB */
    buf[0] = 0xBB;

    /* Search for NOT 0xAA. Should find index 0. */
    status = GenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(idx == 0);

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
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Change last byte to 0xBB */
    buf[15] = 0xBB;

    /* Search for NOT 0xAA. Should find index 15. */
    status  = GenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(idx == 15);

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
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Change middle byte */
    buf[8] = 0xBB;

    /* Search for NOT 0xAA. */
    status = GenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(idx == 8);

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
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Mismatches at 2, 5, 10 */
    buf[2]  = 0xBB;
    buf[5]  = 0xCC;
    buf[10] = 0xDD;

    /* Search for NOT 0xAA. Should find the FIRST one (index 2). */
    status  = GenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(idx == 2);

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    static u8 buf[2000];
    usize     idx;
    bool      status;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    /* Fill with 0x00 */
    kdi_FillVal(buf, USIZE_C(2000), U8_C(0x00));

    /* Set a non-zero value at 1500 */
    buf[1500] = 0xFF;

    /* Search for NOT 0x00. */
    status    = GenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(2000), U8_C(0x00));

    assert(status == RESULT_SUCCESS);
    assert(idx == 1500);

    /* Search for NOT 0xFF. Should find index 0 (since buf[0] is 0x00, which is != 0xFF). */
    status = GenMemOpsFindNotByteIndex(&idx, buf, USIZE_C(2000), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(idx == 0);

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
    LargeBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
