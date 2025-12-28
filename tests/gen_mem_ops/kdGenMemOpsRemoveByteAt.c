/**
 * @file kdGenMemOpsRemoveByteAt.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsRemoveByteAt function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsRemoveByteAt function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8    buf[16];
    usize len = 4;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillSeq_u8(buf, USIZE_C(4), U8_C(0x00));

    /* base is null -> failure */
    status = kdGenMemOpsRemoveByteAt(null, USIZE_C(16), &len, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* base_elems pointer is null -> failure */
    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(16), null, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* idx >= base_cap -> failure */
    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(16));
    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(4));

    /* idx >= *base_elems -> failure */
    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(4));

    printf("PASSED\n");
}


void
RemoveHead(void)
{
    u8    buf[16];
    usize len = 5;
    u8    expected[4];
    bool  status;

    printf(LOG_PREFIX_CSTR "RemoveHead -> ");

    /* Init: 0x00, 0x01, 0x02, 0x03, 0x04 */
    kdi_FillSeq_u8(buf, USIZE_C(5), U8_C(0x00));

    /* Remove at Index 0 */
    /* Expected: 0x01, 0x02, 0x03, 0x04 */
    expected[0] = 0x01;
    expected[1] = 0x02;
    expected[2] = 0x03;
    expected[3] = 0x04;

    status      = kdGenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(0));

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(4));
    assert(kdi_BytesEqual(buf, expected, USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
RemoveTail(void)
{
    u8    buf[16];
    usize len = 5;
    u8    expected[4];
    bool  status;

    printf(LOG_PREFIX_CSTR "RemoveTail -> ");

    /* Init: 0x00, 0x01, 0x02, 0x03, 0x04 */
    kdi_FillSeq_u8(buf, USIZE_C(5), U8_C(0x00));

    /* Remove at Index 4 (Last element) */
    /* Expected: 0x00, 0x01, 0x02, 0x03 */
    expected[0] = 0x00;
    expected[1] = 0x01;
    expected[2] = 0x02;
    expected[3] = 0x03;

    status      = kdGenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(4));
    assert(kdi_BytesEqual(buf, expected, USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
RemoveMiddle(void)
{
    u8    buf[16];
    usize len = 5;
    u8    expected[4];
    bool  status;

    printf(LOG_PREFIX_CSTR "RemoveMiddle -> ");

    /* Init: 0x00, 0x01, 0x02, 0x03, 0x04 */
    kdi_FillSeq_u8(buf, USIZE_C(5), U8_C(0x00));

    /* Remove at Index 2 (Value 0x02) */
    /* Expected: 0x00, 0x01, 0x03, 0x04 */
    expected[0] = 0x00;
    expected[1] = 0x01;
    expected[2] = 0x03;
    expected[3] = 0x04;

    status      = kdGenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(2));

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(4));
    assert(kdi_BytesEqual(buf, expected, USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
RemoveSingleElement(void)
{
    u8    buf[16];
    usize len = 1;
    bool  status;

    printf(LOG_PREFIX_CSTR "RemoveSingleElement -> ");

    buf[0] = 0xAA;

    /* Remove index 0 from single-element buffer */
    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(0));

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(0));

    printf("PASSED\n");
}


void
RemoveFromEmpty(void)
{
    u8    buf[16];
    usize len = 0;
    bool  status;

    printf(LOG_PREFIX_CSTR "RemoveFromEmpty -> ");

    /* Remove from empty -> Failure (idx >= *base_elems) */
    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(0));

    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(0));

    printf("PASSED\n");
}


void
OutOfBounds(void)
{
    u8    buf[16];
    usize len = 4;
    u8    original[4];
    bool  status;

    printf(LOG_PREFIX_CSTR "OutOfBounds -> ");

    kdi_FillSeq_u8(buf, USIZE_C(4), U8_C(0x00));
    kdi_FillSeq_u8(original, USIZE_C(4), U8_C(0x00));

    /* Remove at Index 4 (Len is 4, valid indices 0..3) */
    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(4));
    assert(kdi_BytesEqual(buf, original, USIZE_C(4)) == RESULT_SUCCESS);

    /* Remove at Index 100 (Way out of bounds) */
    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(100));
    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(4));
    assert(kdi_BytesEqual(buf, original, USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
EdgeCases(void)
{
    u8    buf[16];
    usize len;
    bool  status;

    printf(LOG_PREFIX_CSTR "EdgeCases -> ");

    /* Test 1: idx >= base_cap boundary check */
    /* idx=16, base_cap=16, idx >= base_cap -> failure */
    len    = 10;
    kdi_FillSeq_u8(buf, USIZE_C(10), U8_C(0x00));
    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(16));
    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(10));

    /* Test 2: idx == *base_elems boundary check */
    /* idx=10, len=10, idx >= len -> failure */
    len    = 10;
    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(10));
    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(10));

    /* Test 3: Remove at max valid index (len-1) */
    /* idx=9, len=10, should succeed */
    len    = 10;
    kdi_FillSeq_u8(buf, USIZE_C(10), U8_C(0x00));
    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(9));
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(9));
    assert(buf[8] == 0x08);

    /* Test 4: Large buffer, remove near capacity limit */
    len    = 16;
    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x00));
    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(15));
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(15));
    assert(buf[14] == 0x0E);

    /* Test 5: Buffer at capacity, remove first element */
    len    = 16;
    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x00));
    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(15));
    assert(buf[0] == 0x01);

    printf("PASSED\n");
}


void
MultipleRemovals(void)
{
    u8    buf[16];
    usize len = 8;
    u8    expected[5];
    bool  status;

    printf(LOG_PREFIX_CSTR "MultipleRemovals -> ");

    /* Init: 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 */
    kdi_FillSeq_u8(buf, USIZE_C(8), U8_C(0x00));

    /* Remove at Index 2 (value 0x02) */
    /* Result: 0x00, 0x01, 0x03, 0x04, 0x05, 0x06, 0x07 */
    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(2));
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(7));
    assert(buf[2] == 0x03);

    /* Remove at Index 0 (value 0x00) */
    /* Result: 0x01, 0x03, 0x04, 0x05, 0x06, 0x07 */
    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(6));
    assert(buf[0] == 0x01);

    /* Remove at Index 5 (last element, value 0x07) */
    /* Result: 0x01, 0x03, 0x04, 0x05, 0x06 */
    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(5));
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(5));

    /* Verify final state: 0x01, 0x03, 0x04, 0x05, 0x06 */
    expected[0] = 0x01;
    expected[1] = 0x03;
    expected[2] = 0x04;
    expected[3] = 0x05;
    expected[4] = 0x06;
    assert(kdi_BytesEqual(buf, expected, USIZE_C(5)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
DataIntegrity(void)
{
    u8    buf[32];
    usize len = 10;
    bool  status;

    printf(LOG_PREFIX_CSTR "DataIntegrity -> ");

    /* Fill with distinct pattern to verify no corruption */
    buf[0] = 0xAA;
    buf[1] = 0xBB;
    buf[2] = 0xCC;
    buf[3] = 0xDD;
    buf[4] = 0xEE;
    buf[5] = 0xFF;
    buf[6] = 0x11;
    buf[7] = 0x22;
    buf[8] = 0x33;
    buf[9] = 0x44;

    /* Remove middle element (index 5, value 0xFF) */
    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(32), &len, USIZE_C(5));
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(9));

    /* Verify data integrity: elements before removal point unchanged */
    assert(buf[0] == 0xAA);
    assert(buf[1] == 0xBB);
    assert(buf[2] == 0xCC);
    assert(buf[3] == 0xDD);
    assert(buf[4] == 0xEE);

    /* Verify data integrity: elements after removal point shifted correctly */
    assert(buf[5] == 0x11);
    assert(buf[6] == 0x22);
    assert(buf[7] == 0x33);
    assert(buf[8] == 0x44);

    printf("PASSED\n");
}


void
SequentialRemovals(void)
{
    u8    buf[32];
    usize len = 16;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "SequentialRemovals -> ");

    /* Init: 0x00..0x0F */
    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Remove all even-indexed elements from the end backwards */
    /* This tests removing without changing indices of elements to be removed */
    for (i = 7; i > 0; --i)
    {
        status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(32), &len, i * 2);
        assert(status == RESULT_SUCCESS);
    }
    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(32), &len, USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(8));

    /* Verify odd elements remain: 0x01, 0x03, 0x05, 0x07, 0x09, 0x0B, 0x0D, 0x0F */
    assert(buf[0] == 0x01);
    assert(buf[1] == 0x03);
    assert(buf[2] == 0x05);
    assert(buf[3] == 0x07);
    assert(buf[4] == 0x09);
    assert(buf[5] == 0x0B);
    assert(buf[6] == 0x0D);
    assert(buf[7] == 0x0F);

    printf("PASSED\n");
}


void
AlternatingPattern(void)
{
    u8    buf[32];
    usize len = 16;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "AlternatingPattern -> ");

    /* Init alternating pattern: 0xAA, 0x55, 0xAA, 0x55... */
    for (i = 0; i < 16; ++i)
    {
        buf[i] = (i & 1) ? 0x55 : 0xAA;
    }

    /* Remove first element repeatedly to shift entire buffer */
    for (i = 0; i < 8; ++i)
    {
        status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(32), &len, USIZE_C(0));
        assert(status == RESULT_SUCCESS);
        assert(len == (16 - i - 1));
    }

    /* Verify remaining 8 elements: 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55 */
    assert(len == USIZE_C(8));
    for (i = 0; i < 8; ++i)
    {
        assert(buf[i] == ((i & 1) ? 0x55 : 0xAA));
    }

    printf("PASSED\n");
}


void
RemoveUntilEmpty(void)
{
    u8    buf[8];
    usize len = 5;
    bool  status;

    printf(LOG_PREFIX_CSTR "RemoveUntilEmpty -> ");

    kdi_FillSeq_u8(buf, USIZE_C(5), U8_C(0x00));

    /* Remove all elements one by one from the tail */
    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(8), &len, USIZE_C(4));
    assert(status == RESULT_SUCCESS && len == USIZE_C(4));

    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(8), &len, USIZE_C(3));
    assert(status == RESULT_SUCCESS && len == USIZE_C(3));

    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(8), &len, USIZE_C(2));
    assert(status == RESULT_SUCCESS && len == USIZE_C(2));

    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(8), &len, USIZE_C(1));
    assert(status == RESULT_SUCCESS && len == USIZE_C(1));

    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(8), &len, USIZE_C(0));
    assert(status == RESULT_SUCCESS && len == USIZE_C(0));

    /* Try to remove from empty buffer */
    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(8), &len, USIZE_C(0));
    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(0));

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    u8    buf[256];
    usize len = 256;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    /* Init: 0x00..0xFF */
    kdi_FillSeq_u8(buf, USIZE_C(256), U8_C(0x00));

    /* Remove element at index 128 */
    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(256), &len, USIZE_C(128));
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(255));

    /* Verify elements before index 128 are unchanged */
    for (i = 0; i < 128; ++i)
    {
        assert(buf[i] == (u8)i);
    }

    /* Verify elements after index 128 are shifted left by 1 */
    for (i = 128; i < 255; ++i)
    {
        assert(buf[i] == (u8)(i + 1));
    }

    printf("PASSED\n");
}


void
StressTest(void)
{
    u8    buf[128];
    usize len = 100;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "StressTest -> ");

    kdi_FillSeq_u8(buf, USIZE_C(100), U8_C(0x00));

    /* Remove every 5th element from the tail backward */
    /* This avoids index shift issues during iteration */
    for (i = 95; i > 0; i -= 5)
    {
        if (i < len)
        {
            status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(128), &len, i);
            assert(status == RESULT_SUCCESS);
        }
    }

    /* Verify buffer is shorter */
    assert(len < USIZE_C(100));

    /* Verify no corruption by checking sequence continuity */
    /* (allowing for gaps where elements were removed) */
    for (i = 1; i < len; ++i)
    {
        /* Each element should be greater than previous (with possible gaps) */
        assert(buf[i] > buf[i - 1]);
    }

    printf("PASSED\n");
}


void
BoundaryShiftTest(void)
{
    u8    buf[16];
    usize len;
    bool  status;

    printf(LOG_PREFIX_CSTR "BoundaryShiftTest -> ");

    /* Test 1: Remove when len == base_cap */
    len = 16;
    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0xA0));
    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(15));
    assert(buf[0] == 0xA1);

    /* Test 2: Remove when len == base_cap - 1 */
    len = 15;
    kdi_FillSeq_u8(buf, USIZE_C(15), U8_C(0xB0));
    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(14));
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(14));
    assert(buf[13] == 0xBD);

    /* Test 3: Remove when len == 2 */
    len    = 2;
    buf[0] = 0xC0;
    buf[1] = 0xC1;
    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(1));
    assert(buf[0] == 0xC0);

    printf("PASSED\n");
}


void
ZeroByteValues(void)
{
    u8    buf[16];
    usize len = 8;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "ZeroByteValues -> ");

    /* Fill buffer with all zeros */
    kdi_Fill_u8(buf, USIZE_C(8), U8_C(0x00));

    /* Remove middle element */
    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(7));

    /* Verify all remaining elements are still zero */
    for (i = 0; i < 7; ++i)
    {
        assert(buf[i] == 0x00);
    }

    printf("PASSED\n");
}


void
MaxByteValues(void)
{
    u8    buf[16];
    usize len = 8;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "MaxByteValues -> ");

    /* Fill buffer with all 0xFF */
    kdi_Fill_u8(buf, USIZE_C(8), U8_C(0xFF));

    /* Remove first element */
    status = kdGenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(7));

    /* Verify all remaining elements are still 0xFF */
    for (i = 0; i < 7; ++i)
    {
        assert(buf[i] == 0xFF);
    }

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    RemoveHead();
    RemoveTail();
    RemoveMiddle();
    RemoveSingleElement();
    RemoveFromEmpty();
    OutOfBounds();
    EdgeCases();
    MultipleRemovals();
    DataIntegrity();
    SequentialRemovals();
    AlternatingPattern();
    RemoveUntilEmpty();
    LargeBuffer();
    StressTest();
    BoundaryShiftTest();
    ZeroByteValues();
    MaxByteValues();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}