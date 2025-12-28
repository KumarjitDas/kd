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
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsInsertByteAt function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8    buf[16];
    usize len = 0;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0));

    /* base is null -> failure */
    status = kdGenMemOpsInsertByteAt(null, USIZE_C(16), &len, USIZE_C(0), U8_C(0), false);
    assert(status == RESULT_FAILURE);

    /* base_elems pointer is null -> failure */
    status = kdGenMemOpsInsertByteAt(buf, USIZE_C(16), null, USIZE_C(0), U8_C(0), false);
    assert(status == RESULT_FAILURE);

    /* base_cap is zero -> failure */
    status = kdGenMemOpsInsertByteAt(buf, USIZE_C(0), &len, USIZE_C(0), U8_C(0), false);
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

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0));

    /* Insert at index 0 into empty buffer */
    status = kdGenMemOpsInsertByteAt(buf, USIZE_C(16), &len, USIZE_C(0), U8_C(0xAA), false);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(1));
    assert(buf[0] == U8_C(0xAA));

    printf("PASSED\n");
}


void
InsertAtStart(void)
{
    u8    buf[16];
    usize len = 4;
    bool  status;

    printf(LOG_PREFIX_CSTR "InsertAtStart -> ");

    /* Init: 0x01, 0x02, 0x03, 0x04 */
    buf[0] = U8_C(0x01);
    buf[1] = U8_C(0x02);
    buf[2] = U8_C(0x03);
    buf[3] = U8_C(0x04);

    /* Insert 0xAA at index 0 */
    /* Expected: 0xAA, 0x01, 0x02, 0x03, 0x04 */
    status = kdGenMemOpsInsertByteAt(buf, USIZE_C(16), &len, USIZE_C(0), U8_C(0xAA), false);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(5));
    assert(buf[0] == U8_C(0xAA));
    assert(buf[1] == U8_C(0x01));
    assert(buf[2] == U8_C(0x02));
    assert(buf[3] == U8_C(0x03));
    assert(buf[4] == U8_C(0x04));

    printf("PASSED\n");
}


void
InsertAtEnd(void)
{
    u8    buf[16];
    usize len = 4;
    bool  status;

    printf(LOG_PREFIX_CSTR "InsertAtEnd -> ");

    /* Init: 0x01, 0x02, 0x03, 0x04 */
    buf[0] = U8_C(0x01);
    buf[1] = U8_C(0x02);
    buf[2] = U8_C(0x03);
    buf[3] = U8_C(0x04);

    /* Insert 0xAA at index 4 (append) */
    /* Expected: 0x01, 0x02, 0x03, 0x04, 0xAA */
    status = kdGenMemOpsInsertByteAt(buf, USIZE_C(16), &len, USIZE_C(4), U8_C(0xAA), false);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(5));
    assert(buf[0] == U8_C(0x01));
    assert(buf[1] == U8_C(0x02));
    assert(buf[2] == U8_C(0x03));
    assert(buf[3] == U8_C(0x04));
    assert(buf[4] == U8_C(0xAA));

    printf("PASSED\n");
}


void
InsertAtMiddle(void)
{
    u8    buf[16];
    usize len = 4;
    bool  status;

    printf(LOG_PREFIX_CSTR "InsertAtMiddle -> ");

    /* Init: 0x01, 0x02, 0x03, 0x04 */
    buf[0] = U8_C(0x01);
    buf[1] = U8_C(0x02);
    buf[2] = U8_C(0x03);
    buf[3] = U8_C(0x04);

    /* Insert 0xAA at index 2 */
    /* Expected: 0x01, 0x02, 0xAA, 0x03, 0x04 */
    status = kdGenMemOpsInsertByteAt(buf, USIZE_C(16), &len, USIZE_C(2), U8_C(0xAA), false);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(5));
    assert(buf[0] == U8_C(0x01));
    assert(buf[1] == U8_C(0x02));
    assert(buf[2] == U8_C(0xAA));
    assert(buf[3] == U8_C(0x03));
    assert(buf[4] == U8_C(0x04));

    printf("PASSED\n");
}


void
BufferFull_NoTruncate(void)
{
    u8    buf[4];
    usize len = 4;
    bool  status;

    printf(LOG_PREFIX_CSTR "BufferFull_NoTruncate -> ");

    kdi_FillSeq_u8(buf, USIZE_C(4), U8_C(0x01));

    /* Try to insert when len == cap, truncate = false */
    status = kdGenMemOpsInsertByteAt(buf, USIZE_C(4), &len, USIZE_C(0), U8_C(0xAA), false);

    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(4));
    /* Buffer should remain unchanged */
    assert(buf[0] == U8_C(0x01));
    assert(buf[1] == U8_C(0x02));

    printf("PASSED\n");
}


void
BufferFull_Truncate(void)
{
    u8    buf[4];
    usize len = 4;
    bool  status;

    printf(LOG_PREFIX_CSTR "BufferFull_Truncate -> ");

    /* Init: 0x01, 0x02, 0x03, 0x04 */
    buf[0] = U8_C(0x01);
    buf[1] = U8_C(0x02);
    buf[2] = U8_C(0x03);
    buf[3] = U8_C(0x04);

    /* Insert at index 1, truncate = true */
    /* Shift right: 0x01, 0xAA, 0x02, 0x03 (0x04 falls off) */
    status = kdGenMemOpsInsertByteAt(buf, USIZE_C(4), &len, USIZE_C(1), U8_C(0xAA), true);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(4));
    assert(buf[0] == U8_C(0x01));
    assert(buf[1] == U8_C(0xAA));
    assert(buf[2] == U8_C(0x02));
    assert(buf[3] == U8_C(0x03));

    printf("PASSED\n");
}


void
IndexOutOfBounds(void)
{
    u8    buf[16];
    usize len = 4;
    bool  status;

    printf(LOG_PREFIX_CSTR "IndexOutOfBounds -> ");

    kdi_FillSeq_u8(buf, USIZE_C(4), U8_C(0x01));

    /* Insert at index 5 (gap at index 4) - not allowed */
    status = kdGenMemOpsInsertByteAt(buf, USIZE_C(16), &len, USIZE_C(5), U8_C(0xAA), false);

    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(4));

    /* Insert at index far beyond len */
    status = kdGenMemOpsInsertByteAt(buf, USIZE_C(16), &len, USIZE_C(100), U8_C(0xAA), false);
    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(4));

    printf("PASSED\n");
}


void
MultipleInserts(void)
{
    u8    buf[16];
    usize len = 0;
    bool  status;

    printf(LOG_PREFIX_CSTR "MultipleInserts -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0));

    /* Build sequence: 10, 20, 30 */
    status = kdGenMemOpsInsertByteAt(buf, USIZE_C(16), &len, USIZE_C(0), U8_C(10), false);
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(1));
    assert(buf[0] == U8_C(10));

    status = kdGenMemOpsInsertByteAt(buf, USIZE_C(16), &len, USIZE_C(1), U8_C(20), false);
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(2));
    assert(buf[1] == U8_C(20));

    status = kdGenMemOpsInsertByteAt(buf, USIZE_C(16), &len, USIZE_C(2), U8_C(30), false);
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(3));
    assert(buf[2] == U8_C(30));

    printf("PASSED\n");
}


void
InsertZeroValue(void)
{
    u8    buf[8];
    usize len = 3;
    bool  status;

    printf(LOG_PREFIX_CSTR "InsertZeroValue -> ");

    buf[0] = U8_C(1);
    buf[1] = U8_C(2);
    buf[2] = U8_C(3);

    /* Insert 0 at index 1 */
    status = kdGenMemOpsInsertByteAt(buf, USIZE_C(8), &len, USIZE_C(1), U8_C(0), false);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(4));
    assert(buf[0] == U8_C(1));
    assert(buf[1] == U8_C(0));
    assert(buf[2] == U8_C(2));
    assert(buf[3] == U8_C(3));

    printf("PASSED\n");
}


void
InsertMaxValue(void)
{
    u8    buf[8];
    usize len = 3;
    bool  status;

    printf(LOG_PREFIX_CSTR "InsertMaxValue -> ");

    buf[0] = U8_C(1);
    buf[1] = U8_C(2);
    buf[2] = U8_C(3);

    /* Insert 0xFF at index 1 */
    status = kdGenMemOpsInsertByteAt(buf, USIZE_C(8), &len, USIZE_C(1), U8_C(0xFF), false);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(4));
    assert(buf[0] == U8_C(1));
    assert(buf[1] == U8_C(0xFF));
    assert(buf[2] == U8_C(2));
    assert(buf[3] == U8_C(3));

    printf("PASSED\n");
}


void
TruncateAtStart(void)
{
    u8    buf[4];
    usize len = 4;
    bool  status;

    printf(LOG_PREFIX_CSTR "TruncateAtStart -> ");

    buf[0] = U8_C(1);
    buf[1] = U8_C(2);
    buf[2] = U8_C(3);
    buf[3] = U8_C(4);

    /* Insert at index 0 with truncate */
    /* Expected: 0xAA, 1, 2, 3 (4 falls off) */
    status = kdGenMemOpsInsertByteAt(buf, USIZE_C(4), &len, USIZE_C(0), U8_C(0xAA), true);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(4));
    assert(buf[0] == U8_C(0xAA));
    assert(buf[1] == U8_C(1));
    assert(buf[2] == U8_C(2));
    assert(buf[3] == U8_C(3));

    printf("PASSED\n");
}


void
TruncateAtEnd(void)
{
    u8    buf[4];
    usize len = 4;
    bool  status;

    printf(LOG_PREFIX_CSTR "TruncateAtEnd -> ");

    buf[0] = U8_C(1);
    buf[1] = U8_C(2);
    buf[2] = U8_C(3);
    buf[3] = U8_C(4);

    /* Insert at index 3 with truncate */
    /* Expected: 1, 2, 3, 0xAA (4 falls off) */
    status = kdGenMemOpsInsertByteAt(buf, USIZE_C(4), &len, USIZE_C(3), U8_C(0xAA), true);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(4));
    assert(buf[0] == U8_C(1));
    assert(buf[1] == U8_C(2));
    assert(buf[2] == U8_C(3));
    assert(buf[3] == U8_C(0xAA));

    printf("PASSED\n");
}


void
SingleByteCapacity(void)
{
    u8    buf[1];
    usize len = 0;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleByteCapacity -> ");

    buf[0] = U8_C(0);

    /* Insert into single-byte buffer */
    status = kdGenMemOpsInsertByteAt(buf, USIZE_C(1), &len, USIZE_C(0), U8_C(0x42), false);

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(1));
    assert(buf[0] == U8_C(0x42));

    /* Try to insert again (buffer full) */
    status = kdGenMemOpsInsertByteAt(buf, USIZE_C(1), &len, USIZE_C(0), U8_C(0x99), false);
    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(1));
    assert(buf[0] == U8_C(0x42));

    /* Insert with truncate */
    status = kdGenMemOpsInsertByteAt(buf, USIZE_C(1), &len, USIZE_C(0), U8_C(0x99), true);
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(1));
    assert(buf[0] == U8_C(0x99));

    printf("PASSED\n");
}


void
FillToCapacity(void)
{
    u8    buf[8];
    usize len = 0;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "FillToCapacity -> ");

    kdi_Fill_u8(buf, USIZE_C(8), U8_C(0));

    /* Fill buffer to capacity */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        status = kdGenMemOpsInsertByteAt(buf, USIZE_C(8), &len, i, (u8)(U8_C(10) + (u8)i), false);
        assert(status == RESULT_SUCCESS);
        assert(len == i + USIZE_C(1));
    }

    /* Verify all values */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        assert(buf[i] == (u8)(U8_C(10) + (u8)i));
    }

    /* Try to insert one more (should fail) */
    status = kdGenMemOpsInsertByteAt(buf, USIZE_C(8), &len, USIZE_C(0), U8_C(0xFF), false);
    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(8));

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    u8    buf[256];
    usize len = 0;
    bool  status;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    kdi_Fill_u8(buf, USIZE_C(256), U8_C(0));

    /* Insert at start */
    status = kdGenMemOpsInsertByteAt(buf, USIZE_C(256), &len, USIZE_C(0), U8_C(0xAA), false);
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(1));
    assert(buf[0] == U8_C(0xAA));

    /* Fill with some values */
    len = USIZE_C(100);
    kdi_FillSeq_u8(buf, USIZE_C(100), U8_C(0));

    /* Insert in middle of large buffer */
    status = kdGenMemOpsInsertByteAt(buf, USIZE_C(256), &len, USIZE_C(50), U8_C(0xBB), false);
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(101));
    assert(buf[50] == U8_C(0xBB));

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
    InsertAtStart();
    InsertAtEnd();
    InsertAtMiddle();
    BufferFull_NoTruncate();
    BufferFull_Truncate();
    IndexOutOfBounds();
    MultipleInserts();
    InsertZeroValue();
    InsertMaxValue();
    TruncateAtStart();
    TruncateAtEnd();
    SingleByteCapacity();
    FillToCapacity();
    LargeBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}