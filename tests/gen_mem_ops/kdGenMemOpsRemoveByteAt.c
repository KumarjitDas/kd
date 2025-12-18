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


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsRemoveByteAt function test"
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


void
BasicArguments(void)
{
    u8    buf[16];
    usize len = 4;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* base is null -> failure */
    status = GenMemOpsRemoveByteAt(null, USIZE_C(16), &len, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* base_elems pointer is null -> failure */
    status = GenMemOpsRemoveByteAt(buf, USIZE_C(16), null, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* base_cap is zero -> failure */
    /* Note: even if len=0, valid cap usually required by API sanity check,
     * but strictly speaking remove only depends on len.
     * Assuming standard checks verify non-null base implies >0 cap or valid ptr.
     */
    status = GenMemOpsRemoveByteAt(buf, USIZE_C(0), &len, USIZE_C(0));
    assert(status == RESULT_FAILURE);

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
    kdi_FillSeq(buf, USIZE_C(5), U8_C(0x00));

    /* Remove at Index 0 */
    /* Expected: 0x01, 0x02, 0x03, 0x04 */
    expected[0] = 0x01;
    expected[1] = 0x02;
    expected[2] = 0x03;
    expected[3] = 0x04;

    status      = GenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(0));

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
    kdi_FillSeq(buf, USIZE_C(5), U8_C(0x00));

    /* Remove at Index 4 (Last element) */
    /* Expected: 0x00, 0x01, 0x02, 0x03 */
    expected[0] = 0x00;
    expected[1] = 0x01;
    expected[2] = 0x02;
    expected[3] = 0x03;

    status      = GenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(4));

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
    kdi_FillSeq(buf, USIZE_C(5), U8_C(0x00));

    /* Remove at Index 2 (Value 0x02) */
    /* Expected: 0x00, 0x01, 0x03, 0x04 */
    expected[0] = 0x00;
    expected[1] = 0x01;
    expected[2] = 0x03;
    expected[3] = 0x04;

    status      = GenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(2));

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

    /* Remove index 0 */
    status = GenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(0));

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

    /* Remove from empty -> Failure */
    status = GenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(0));

    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(0));

    printf("PASSED\n");
}


void
OutOfBounds(void)
{
    u8    buf[16];
    usize len = 4;
    bool  status;

    printf(LOG_PREFIX_CSTR "OutOfBounds -> ");

    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x00));

    /* Remove at Index 4 (Len is 4, valid indices 0..3) */
    status = GenMemOpsRemoveByteAt(buf, USIZE_C(16), &len, USIZE_C(4));

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
    RemoveHead();
    RemoveTail();
    RemoveMiddle();
    RemoveSingleElement();
    RemoveFromEmpty();
    OutOfBounds();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
