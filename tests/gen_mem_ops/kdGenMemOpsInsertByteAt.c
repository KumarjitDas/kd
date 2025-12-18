/**
 * @file kdGenMemOpsInsertByteAt.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsInsertByteAt function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsInsertByteAt function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


static bool
kdi_BytesEqual(const byte *a, const byte *b, usize sz)
{
    usize i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        if (a[i] != b[i])
        {
            return RESULT_FAILURE;
        }
    }

    return RESULT_SUCCESS;
}


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
    usize len = 0;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* base is null -> failure */
    status = GenMemOpsInsertByteAt(null, USIZE_C(16), &len, USIZE_C(0), U8_C(0), false);
    assert(status == RESULT_FAILURE);

    /* base_elems pointer is null -> failure */
    status = GenMemOpsInsertByteAt(buf, USIZE_C(16), null, USIZE_C(0), U8_C(0), false);
    assert(status == RESULT_FAILURE);

    /* base_cap is zero -> failure (cannot insert into 0-capacity buffer) */
    status = GenMemOpsInsertByteAt(buf, USIZE_C(0), &len, USIZE_C(0), U8_C(0), false);
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
InsertIntoEmpty(void)
{
    u8    buf[16];
    usize len = 0;
    bool  status;

    printf(LOG_PREFIX_CSTR "InsertIntoEmpty -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    status = GenMemOpsInsertByteAt(buf, USIZE_C(16), &len, USIZE_C(0), U8_C(0xAA), false);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(1));
    assert(buf[0] == U8_C(0xAA));

    printf("PASSED\n");
}


void
InsertHead(void)
{
    u8    buf[16];
    usize len = 4;
    u8    expected[5];
    bool  status;

    printf(LOG_PREFIX_CSTR "InsertHead -> ");

    /* Init: 0x01, 0x02, 0x03, 0x04 */
    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x01));

    /* Insert 0xAA at index 0 */
    /* Expected: 0xAA, 0x01, 0x02, 0x03, 0x04 */
    expected[0] = 0xAA;
    expected[1] = 0x01;
    expected[2] = 0x02;
    expected[3] = 0x03;
    expected[4] = 0x04;

    status      = GenMemOpsInsertByteAt(buf, USIZE_C(16), &len, USIZE_C(0), U8_C(0xAA), false);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(5));
    assert(kdi_BytesEqual(buf, expected, USIZE_C(5)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
InsertTail(void)
{
    u8    buf[16];
    usize len = 4;
    u8    expected[5];
    bool  status;

    printf(LOG_PREFIX_CSTR "InsertTail -> ");

    /* Init: 0x01, 0x02, 0x03, 0x04 */
    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x01));

    /* Insert 0xAA at index 4 (Append) */
    /* Expected: 0x01, 0x02, 0x03, 0x04, 0xAA */
    expected[0] = 0x01;
    expected[1] = 0x02;
    expected[2] = 0x03;
    expected[3] = 0x04;
    expected[4] = 0xAA;

    status      = GenMemOpsInsertByteAt(buf, USIZE_C(16), &len, USIZE_C(4), U8_C(0xAA), false);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(5));
    assert(kdi_BytesEqual(buf, expected, USIZE_C(5)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
InsertMiddle(void)
{
    u8    buf[16];
    usize len = 4;
    u8    expected[5];
    bool  status;

    printf(LOG_PREFIX_CSTR "InsertMiddle -> ");

    /* Init: 0x01, 0x02, 0x03, 0x04 */
    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x01));

    /* Insert 0xAA at index 2 */
    /* Expected: 0x01, 0x02, 0xAA, 0x03, 0x04 */
    expected[0] = 0x01;
    expected[1] = 0x02;
    expected[2] = 0xAA;
    expected[3] = 0x03;
    expected[4] = 0x04;

    status      = GenMemOpsInsertByteAt(buf, USIZE_C(16), &len, USIZE_C(2), U8_C(0xAA), false);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(5));
    assert(kdi_BytesEqual(buf, expected, USIZE_C(5)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
BufferFull_NoTruncate(void)
{
    u8    buf[4];
    usize len = 4;
    bool  status;

    printf(LOG_PREFIX_CSTR "BufferFull_NoTruncate -> ");

    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x01));

    /* Try to insert when len == cap, truncate = false */
    status = GenMemOpsInsertByteAt(buf, USIZE_C(4), &len, USIZE_C(0), U8_C(0xAA), false);

    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(4));
    /* Buffer should remain unchanged */
    assert(buf[0] == 0x01);

    printf("PASSED\n");
}


void
BufferFull_Truncate(void)
{
    u8    buf[4];
    usize len = 4;
    u8    expected[4];
    bool  status;

    printf(LOG_PREFIX_CSTR "BufferFull_Truncate -> ");

    /* Init: 0x01, 0x02, 0x03, 0x04 */
    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x01));

    /* Insert at index 1, truncate = true.
     * Shift right: 0x01, 0xAA, 0x02, 0x03 (0x04 falls off)
     */
    expected[0] = 0x01;
    expected[1] = 0xAA;
    expected[2] = 0x02;
    expected[3] = 0x03;

    status      = GenMemOpsInsertByteAt(buf, USIZE_C(4), &len, USIZE_C(1), U8_C(0xAA), true);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(4)); /* Length stays maxed at cap */
    assert(kdi_BytesEqual(buf, expected, USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
OutOfBounds(void)
{
    u8    buf[16];
    usize len = 4;
    bool  status;

    printf(LOG_PREFIX_CSTR "OutOfBounds -> ");

    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x01));

    /* Insert at index 5 (Gap at index 4). Standard Insert does not allow gaps. */
    status = GenMemOpsInsertByteAt(buf, USIZE_C(16), &len, USIZE_C(5), U8_C(0xAA), false);

    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(4));

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    InsertIntoEmpty();
    InsertHead();
    InsertTail();
    InsertMiddle();
    BufferFull_NoTruncate();
    BufferFull_Truncate();
    OutOfBounds();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
