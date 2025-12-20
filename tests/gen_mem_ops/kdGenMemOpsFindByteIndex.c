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


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindByteIndex function test"
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
    status = GenMemOpsFindByteIndex(null, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindByteIndex(&idx, null, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* sz is zero -> failure (cannot find in empty buffer) */
    status = GenMemOpsFindByteIndex(&idx, buf, USIZE_C(0), U8_C(0));
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
    status = GenMemOpsFindByteIndex(&idx, buf, USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_FAILURE);
    /* Idx behavior on failure undefined or unchanged, but API usually returns failure */

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

    /* Set first byte */
    buf[0] = 0xFF;

    /* Find 0xFF */
    status = GenMemOpsFindByteIndex(&idx, buf, USIZE_C(16), U8_C(0xFF));

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

    /* Set last byte */
    buf[15] = 0xFF;

    /* Find 0xFF */
    status  = GenMemOpsFindByteIndex(&idx, buf, USIZE_C(16), U8_C(0xFF));

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

    /* Set at 5 and 10 */
    buf[5]  = 0xFF;
    buf[10] = 0xFF;

    /* Find 0xFF. Should return first occurrence (Index 5). */
    status  = GenMemOpsFindByteIndex(&idx, buf, USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(idx == 5);

    printf("PASSED\n");
}


void
U32_FindByte(void)
{
    u32   buf[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_FindByte -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    /* Set byte at offset 7 to 0xAA */
    ((u8 *)buf)[7] = 0xAA;

    /* Find 0xAA */
    status         = GenMemOpsFindByteIndex(&idx, buf, sizeof(buf), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(idx == 7);

    printf("PASSED\n");
}


void
LargeArray_Find(void)
{
    u8    buf[100];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "LargeArray_Find -> ");

    /* Init: 0..99 */
    kdi_FillSeq(buf, USIZE_C(100), U8_C(0));

    /* Find value 50. Should be at index 50. */
    status = GenMemOpsFindByteIndex(&idx, buf, USIZE_C(100), U8_C(50));
    assert(status == RESULT_SUCCESS);
    assert(idx == 50);

    /* Find value 99. Should be at index 99. */
    status = GenMemOpsFindByteIndex(&idx, buf, USIZE_C(100), U8_C(99));
    assert(status == RESULT_SUCCESS);
    assert(idx == 99);

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
    U32_FindByte();
    LargeArray_Find();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
