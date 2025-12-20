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


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindLastByteIndex function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


static void
kdi_FillSeq(u8 *dst, usize sz, u8 start)
{
    usize i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        dst[i] = (u8)(start + (u8)i);
    }
}


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
    status = GenMemOpsFindLastByteIndex(null, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindLastByteIndex(&idx, null, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* sz is zero -> failure */
    status = GenMemOpsFindLastByteIndex(&idx, buf, USIZE_C(0), U8_C(0));
    assert(status == RESULT_FAILURE);

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
    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Find 0xFF */
    status = GenMemOpsFindLastByteIndex(&idx, buf, USIZE_C(16), U8_C(0xFF));

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
    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Set only first byte */
    buf[0] = 0xFF;

    /* Find Last 0xFF (Only one exists at 0) */
    status = GenMemOpsFindLastByteIndex(&idx, buf, USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(idx == 0);

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
    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Set only last byte */
    buf[15] = 0xFF;

    /* Find Last 0xFF */
    status  = GenMemOpsFindLastByteIndex(&idx, buf, USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(idx == 15);

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
    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Set 0xFF at indices 2, 5, 10 */
    buf[2]  = 0xFF;
    buf[5]  = 0xFF;
    buf[10] = 0xFF;

    /* Find Last 0xFF. Should return index 10. */
    status  = GenMemOpsFindLastByteIndex(&idx, buf, USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(idx == 10);

    printf("PASSED\n");
}


void
U32_FindLastByte(void)
{
    u32   buf[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_FindLastByte -> ");

    /* Init: 0x00 */
    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    /* Set byte at offset 3 and 12 to 0xAA */
    ((u8 *)buf)[3]  = 0xAA; /* In u32[0] */
    ((u8 *)buf)[12] = 0xAA; /* In u32[3] */

    /* Find Last 0xAA */
    status          = GenMemOpsFindLastByteIndex(&idx, buf, sizeof(buf), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(idx == 12);

    printf("PASSED\n");
}


void
LargeArray_FindLast(void)
{
    u8    buf[100];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "LargeArray_FindLast -> ");

    /* Init: 0..99 */
    kdi_FillSeq(buf, USIZE_C(100), U8_C(0));

    /* Set repeats manually to test "Last" logic */
    buf[10] = 50;
    buf[50] = 50; /* Index 50 holds value 50 by init, ensuring it is there */
    buf[80] = 50;

    /* Find Last 50. Should be index 80. */
    status  = GenMemOpsFindLastByteIndex(&idx, buf, USIZE_C(100), U8_C(50));
    assert(status == RESULT_SUCCESS);
    assert(idx == 80);

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
    U32_FindLastByte();
    LargeArray_FindLast();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
