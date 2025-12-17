/**
 * @file kdGenMemOpsReverseBytes.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsReverseBytes function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsReverseBytes function test"
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


void
BasicArguments(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* ptr is null -> failure */
    status = GenMemOpsReverseBytes(null, USIZE_C(16));
    assert(status == RESULT_FAILURE);

    /* dst_sz is zero -> success (trivial, nothing done) */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));
    status = GenMemOpsReverseBytes(buf, USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    /* Verify buffer untouched */
    assert(buf[0] == 0x00);

    printf("PASSED\n");
}


void
EvenSizeReverse(void)
{
    u8   buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "EvenSizeReverse -> ");

    /* Init: 0x01, 0x02, 0x03, 0x04 */
    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x01));

    status = GenMemOpsReverseBytes(buf, USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Expected: 0x04, 0x03, 0x02, 0x01 */
    assert(buf[0] == U8_C(0x04));
    assert(buf[1] == U8_C(0x03));
    assert(buf[2] == U8_C(0x02));
    assert(buf[3] == U8_C(0x01));

    printf("PASSED\n");
}


void
OddSizeReverse(void)
{
    u8   buf[5];
    bool status;

    printf(LOG_PREFIX_CSTR "OddSizeReverse -> ");

    /* Init: 0x01, 0x02, 0x03, 0x04, 0x05 */
    kdi_FillSeq(buf, USIZE_C(5), U8_C(0x01));

    status = GenMemOpsReverseBytes(buf, USIZE_C(5));
    assert(status == RESULT_SUCCESS);

    /* Expected: 0x05, 0x04, 0x03, 0x02, 0x01 */
    /* Middle element (0x03 at index 2) should remain in place */
    assert(buf[0] == U8_C(0x05));
    assert(buf[1] == U8_C(0x04));
    assert(buf[2] == U8_C(0x03));
    assert(buf[3] == U8_C(0x02));
    assert(buf[4] == U8_C(0x01));

    printf("PASSED\n");
}


void
SingleByte(void)
{
    u8   buf[1];
    bool status;

    printf(LOG_PREFIX_CSTR "SingleByte -> ");

    buf[0] = U8_C(0xAA);

    /* Reversing 1 byte -> No change */
    status = GenMemOpsReverseBytes(buf, USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(buf[0] == U8_C(0xAA));

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    u8    buf[100];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    /* 0..99 */
    kdi_FillSeq(buf, USIZE_C(100), U8_C(0));

    status = GenMemOpsReverseBytes(buf, USIZE_C(100));
    assert(status == RESULT_SUCCESS);

    /* Check first and last */
    assert(buf[0] == U8_C(99));
    assert(buf[99] == U8_C(0));

    /* Verify all */
    for (i = 0; i < 100; ++i)
    {
        assert(buf[i] == (u8)(99 - i));
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
    EvenSizeReverse();
    OddSizeReverse();
    SingleByte();
    LargeBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
