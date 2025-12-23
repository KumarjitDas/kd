/**
 * @file kdGenMemOpsFindLastNotByteIndex.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindLastNotByteIndex function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindLastNotByteIndex function test"
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
    status = GenMemOpsFindLastNotByteIndex(null, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindLastNotByteIndex(&idx, null, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* sz is zero -> failure */
    status = GenMemOpsFindLastNotByteIndex(&idx, buf, USIZE_C(0), U8_C(0));
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

    /* Search for last byte NOT equal to 0xAA.
     * Since all are 0xAA, this should fail.
     */
    status = GenMemOpsFindLastNotByteIndex(&idx, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SingleMismatchLast(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleMismatchLast -> ");

    /* Fill with 0xAA */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Change last byte to 0xBB */
    buf[15] = 0xBB;

    /* Search for NOT 0xAA. Should find index 15. */
    status  = GenMemOpsFindLastNotByteIndex(&idx, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(idx == 15);

    printf("PASSED\n");
}


void
SingleMismatchFirst(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleMismatchFirst -> ");

    /* Fill with 0xAA */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Change first byte to 0xBB */
    buf[0] = 0xBB;

    /* Search for NOT 0xAA. Should find index 0. */
    status = GenMemOpsFindLastNotByteIndex(&idx, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(idx == 0);

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

    /* Search for last NOT 0xAA. Should find the LAST one (index 10). */
    status  = GenMemOpsFindLastNotByteIndex(&idx, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(idx == 10);

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

    /* Set a non-zero value at 500 and 1500 */
    buf[500]  = 0xFF;
    buf[1500] = 0xFF;

    /* Search for NOT 0x00. Should find 1500 (Last mismatch). */
    status    = GenMemOpsFindLastNotByteIndex(&idx, buf, USIZE_C(2000), U8_C(0x00));

    assert(status == RESULT_SUCCESS);
    assert(idx == 1500);

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
    SingleMismatchLast();
    SingleMismatchFirst();
    MultipleMismatches();
    LargeBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
