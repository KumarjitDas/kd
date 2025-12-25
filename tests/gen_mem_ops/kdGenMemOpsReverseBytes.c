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


static bool
kdi_VerifyReverse(u8 *arr, usize sz, u8 start)
{
    usize i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        if (arr[i] != (u8)(start + (u8)(sz - 1 - i)))
        {
            return RESULT_FAILURE;
        }
    }
    return RESULT_SUCCESS;
}


void
NullPointer(void)
{
    bool status;

    printf(LOG_PREFIX_CSTR "NullPointer -> ");

    /* ptr is null -> failure */
    status = GenMemOpsReverseBytes(null, USIZE_C(16));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ZeroSize(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ZeroSize -> ");

    /* sz is zero -> failure */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));
    status = GenMemOpsReverseBytes(buf, USIZE_C(0));
    assert(status == RESULT_FAILURE);
    /* Verify buffer untouched */
    assert(buf[0] == U8_C(0x00));
    assert(buf[15] == U8_C(0x0F));

    printf("PASSED\n");
}


void
SingleByte(void)
{
    u8   buf[1];
    bool status;

    printf(LOG_PREFIX_CSTR "SingleByte -> ");

    buf[0] = U8_C(0xAA);

    /* Reversing 1 byte -> No change, success */
    status = GenMemOpsReverseBytes(buf, USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(buf[0] == U8_C(0xAA));

    printf("PASSED\n");
}


void
TwoBytes(void)
{
    u8   buf[2];
    bool status;

    printf(LOG_PREFIX_CSTR "TwoBytes -> ");

    buf[0] = U8_C(0x12);
    buf[1] = U8_C(0x34);

    status = GenMemOpsReverseBytes(buf, USIZE_C(2));
    assert(status == RESULT_SUCCESS);

    /* Expected: 0x34, 0x12 */
    assert(buf[0] == U8_C(0x34));
    assert(buf[1] == U8_C(0x12));

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
EightBytes(void)
{
    u8   buf[8];
    bool status;

    printf(LOG_PREFIX_CSTR "EightBytes -> ");

    /* Init: 0x10, 0x11, ..., 0x17 */
    kdi_FillSeq(buf, USIZE_C(8), U8_C(0x10));

    status = GenMemOpsReverseBytes(buf, USIZE_C(8));
    assert(status == RESULT_SUCCESS);

    /* Expected: 0x17, 0x16, ..., 0x10 */
    assert(kdi_VerifyReverse(buf, USIZE_C(8), U8_C(0x10)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SixteenBytes(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "SixteenBytes -> ");

    /* Init: 0x00, 0x01, ..., 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    status = GenMemOpsReverseBytes(buf, USIZE_C(16));
    assert(status == RESULT_SUCCESS);

    /* Expected: 0x0F, 0x0E, ..., 0x00 */
    assert(buf[0] == U8_C(0x0F));
    assert(buf[15] == U8_C(0x00));
    assert(kdi_VerifyReverse(buf, USIZE_C(16), U8_C(0x00)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    u8    buf[100];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    /* Init: 0..99 */
    kdi_FillSeq(buf, USIZE_C(100), U8_C(0));

    status = GenMemOpsReverseBytes(buf, USIZE_C(100));
    assert(status == RESULT_SUCCESS);

    /* Check first and last */
    assert(buf[0] == U8_C(99));
    assert(buf[99] == U8_C(0));

    /* Verify all elements */
    for (i = USIZE_C(0); i < USIZE_C(100); ++i)
    {
        assert(buf[i] == (u8)(99 - i));
    }

    printf("PASSED\n");
}


void
DoubleReverse(void)
{
    u8   buf[8];
    bool status;
    u8   original[8];
    usize i;

    printf(LOG_PREFIX_CSTR "DoubleReverse -> ");

    /* Init: 0x20, 0x21, ..., 0x27 */
    kdi_FillSeq(buf, USIZE_C(8), U8_C(0x20));

    /* Keep copy of original */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        original[i] = buf[i];
    }

    /* Reverse once */
    status = GenMemOpsReverseBytes(buf, USIZE_C(8));
    assert(status == RESULT_SUCCESS);

    /* Reverse again - should restore original */
    status = GenMemOpsReverseBytes(buf, USIZE_C(8));
    assert(status == RESULT_SUCCESS);

    /* Verify restored to original */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        assert(buf[i] == original[i]);
    }

    printf("PASSED\n");
}


void
AllSameValue(void)
{
    u8   buf[10];
    bool status;
    usize i;

    printf(LOG_PREFIX_CSTR "AllSameValue -> ");

    /* Fill with same value */
    for (i = USIZE_C(0); i < USIZE_C(10); ++i)
    {
        buf[i] = U8_C(0x55);
    }

    status = GenMemOpsReverseBytes(buf, USIZE_C(10));
    assert(status == RESULT_SUCCESS);

    /* All values should still be 0x55 */
    for (i = USIZE_C(0); i < USIZE_C(10); ++i)
    {
        assert(buf[i] == U8_C(0x55));
    }

    printf("PASSED\n");
}


void
Pattern32Bit(void)
{
    u8   buf[4];
    bool status;

    printf(LOG_PREFIX_CSTR "Pattern32Bit -> ");

    /* 32-bit value 0x12345678 in little-endian byte order */
    buf[0] = U8_C(0x78);
    buf[1] = U8_C(0x56);
    buf[2] = U8_C(0x34);
    buf[3] = U8_C(0x12);

    status = GenMemOpsReverseBytes(buf, USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Reversed: becomes big-endian representation */
    assert(buf[0] == U8_C(0x12));
    assert(buf[1] == U8_C(0x34));
    assert(buf[2] == U8_C(0x56));
    assert(buf[3] == U8_C(0x78));

    printf("PASSED\n");
}


void
Pattern64Bit(void)
{
    u8   buf[8];
    bool status;

    printf(LOG_PREFIX_CSTR "Pattern64Bit -> ");

    /* 64-bit pattern */
    buf[0] = U8_C(0x11);
    buf[1] = U8_C(0x22);
    buf[2] = U8_C(0x33);
    buf[3] = U8_C(0x44);
    buf[4] = U8_C(0x55);
    buf[5] = U8_C(0x66);
    buf[6] = U8_C(0x77);
    buf[7] = U8_C(0x88);

    status = GenMemOpsReverseBytes(buf, USIZE_C(8));
    assert(status == RESULT_SUCCESS);

    /* Reversed */
    assert(buf[0] == U8_C(0x88));
    assert(buf[1] == U8_C(0x77));
    assert(buf[2] == U8_C(0x66));
    assert(buf[3] == U8_C(0x55));
    assert(buf[4] == U8_C(0x44));
    assert(buf[5] == U8_C(0x33));
    assert(buf[6] == U8_C(0x22));
    assert(buf[7] == U8_C(0x11));

    printf("PASSED\n");
}


void
LargeEvenBuffer(void)
{
    u8    buf[256];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeEvenBuffer -> ");

    /* Init with wrapping values */
    for (i = USIZE_C(0); i < USIZE_C(256); ++i)
    {
        buf[i] = (u8)i;
    }

    status = GenMemOpsReverseBytes(buf, USIZE_C(256));
    assert(status == RESULT_SUCCESS);

    /* Verify reversed */
    for (i = USIZE_C(0); i < USIZE_C(256); ++i)
    {
        assert(buf[i] == (u8)(255 - i));
    }

    printf("PASSED\n");
}


void
LargeOddBuffer(void)
{
    u8    buf[255];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeOddBuffer -> ");

    /* Init */
    for (i = USIZE_C(0); i < USIZE_C(255); ++i)
    {
        buf[i] = (u8)i;
    }

    status = GenMemOpsReverseBytes(buf, USIZE_C(255));
    assert(status == RESULT_SUCCESS);

    /* Verify reversed */
    for (i = USIZE_C(0); i < USIZE_C(255); ++i)
    {
        assert(buf[i] == (u8)(254 - i));
    }

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    NullPointer();
    ZeroSize();
    SingleByte();
    TwoBytes();
    EvenSizeReverse();
    OddSizeReverse();
    EightBytes();
    SixteenBytes();
    LargeBuffer();
    DoubleReverse();
    AllSameValue();
    Pattern32Bit();
    Pattern64Bit();
    LargeEvenBuffer();
    LargeOddBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
