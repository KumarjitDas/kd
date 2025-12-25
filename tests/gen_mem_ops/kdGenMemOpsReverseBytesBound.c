/**
 * @file kdGenMemOpsReverseBytesBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsReverseBytesBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsReverseBytesBound function test"
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
kdi_VerifySeq(u8 *arr, usize sz, u8 start)
{
    usize i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        if (arr[i] != (u8)(start + (u8)i))
        {
            return RESULT_FAILURE;
        }
    }
    return RESULT_SUCCESS;
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

    /* base is null -> failure */
    status = GenMemOpsReverseBytesBound(null, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ZeroBaseSize(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ZeroBaseSize -> ");

    /* base_sz is zero -> failure (caught by begin_idx >= base_sz when begin_idx >= 0) */
    status = GenMemOpsReverseBytesBound(buf, USIZE_C(0), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ZeroCount(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ZeroCount -> ");

    /* count is zero -> failure (!count check) */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));
    status = GenMemOpsReverseBytesBound(buf, USIZE_C(16), USIZE_C(0), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
BeginIndexOutOfBounds(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BeginIndexOutOfBounds -> ");

    /* begin_idx >= base_sz -> failure */
    status = GenMemOpsReverseBytesBound(buf, USIZE_C(16), USIZE_C(16), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    status = GenMemOpsReverseBytesBound(buf, USIZE_C(16), USIZE_C(20), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ExactFit(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ExactFit -> ");

    /* Init: 0x00 ... 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Reverse entire buffer: begin_idx=0, count=16 */
    status = GenMemOpsReverseBytesBound(buf, USIZE_C(16), USIZE_C(0), USIZE_C(16));
    assert(status == RESULT_SUCCESS);

    /* Expected: 0x0F, 0x0E, ..., 0x00 */
    assert(buf[0] == U8_C(0x0F));
    assert(buf[15] == U8_C(0x00));
    assert(kdi_VerifyReverse(buf, USIZE_C(16), U8_C(0x00)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
CountClamping(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "CountClamping -> ");

    /* Init: 0x00 ... 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Request reverse starting at 12, count 10.
     * Available: 16 - 12 = 4 bytes (indices 12, 13, 14, 15).
     * Should reverse those 4 bytes.
     * Values at 12..15: 0x0C, 0x0D, 0x0E, 0x0F
     * Expected: 0x0F, 0x0E, 0x0D, 0x0C
     */
    status = GenMemOpsReverseBytesBound(buf, USIZE_C(16), USIZE_C(12), USIZE_C(10));
    assert(status == RESULT_SUCCESS);

    /* Check reversed part */
    assert(buf[12] == U8_C(0x0F));
    assert(buf[13] == U8_C(0x0E));
    assert(buf[14] == U8_C(0x0D));
    assert(buf[15] == U8_C(0x0C));

    /* Check untouched parts */
    assert(buf[11] == U8_C(0x0B));
    assert(buf[0] == U8_C(0x00));

    printf("PASSED\n");
}


void
MiddleRegion(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "MiddleRegion -> ");

    /* Init: 0x00 ... 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Reverse middle: start 5, count 4 (indices 5, 6, 7, 8) */
    /* Values: 0x05, 0x06, 0x07, 0x08 */
    /* Expected: 0x08, 0x07, 0x06, 0x05 */
    status = GenMemOpsReverseBytesBound(buf, USIZE_C(16), USIZE_C(5), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Verify pre-range untouched */
    assert(buf[4] == U8_C(0x04));

    /* Verify reversed range */
    assert(buf[5] == U8_C(0x08));
    assert(buf[6] == U8_C(0x07));
    assert(buf[7] == U8_C(0x06));
    assert(buf[8] == U8_C(0x05));

    /* Verify post-range untouched */
    assert(buf[9] == U8_C(0x09));

    printf("PASSED\n");
}


void
SingleByteRegion(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "SingleByteRegion -> ");

    /* Init: 0x00 ... 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Reverse single byte at index 7 */
    status = GenMemOpsReverseBytesBound(buf, USIZE_C(16), USIZE_C(7), USIZE_C(1));
    assert(status == RESULT_SUCCESS);

    /* Single byte reversal doesn't change value */
    assert(buf[7] == U8_C(0x07));

    /* Verify neighbors untouched */
    assert(buf[6] == U8_C(0x06));
    assert(buf[8] == U8_C(0x08));

    printf("PASSED\n");
}


void
TwoByteRegion(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "TwoByteRegion -> ");

    /* Init: 0x00 ... 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Reverse two bytes at indices 3, 4 */
    status = GenMemOpsReverseBytesBound(buf, USIZE_C(16), USIZE_C(3), USIZE_C(2));
    assert(status == RESULT_SUCCESS);

    /* Expected: values swapped */
    assert(buf[3] == U8_C(0x04));
    assert(buf[4] == U8_C(0x03));

    /* Verify neighbors untouched */
    assert(buf[2] == U8_C(0x02));
    assert(buf[5] == U8_C(0x05));

    printf("PASSED\n");
}


void
BeginningRegion(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BeginningRegion -> ");

    /* Init: 0x00 ... 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Reverse first 4 bytes */
    status = GenMemOpsReverseBytesBound(buf, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Expected: 0x03, 0x02, 0x01, 0x00 at start */
    assert(buf[0] == U8_C(0x03));
    assert(buf[1] == U8_C(0x02));
    assert(buf[2] == U8_C(0x01));
    assert(buf[3] == U8_C(0x00));

    /* Verify rest untouched */
    assert(buf[4] == U8_C(0x04));
    assert(buf[15] == U8_C(0x0F));

    printf("PASSED\n");
}


void
EndRegion(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "EndRegion -> ");

    /* Init: 0x00 ... 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Reverse last 4 bytes (indices 12-15) */
    status = GenMemOpsReverseBytesBound(buf, USIZE_C(16), USIZE_C(12), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Expected: 0x0F, 0x0E, 0x0D, 0x0C at end */
    assert(buf[12] == U8_C(0x0F));
    assert(buf[13] == U8_C(0x0E));
    assert(buf[14] == U8_C(0x0D));
    assert(buf[15] == U8_C(0x0C));

    /* Verify rest untouched */
    assert(buf[11] == U8_C(0x0B));
    assert(buf[0] == U8_C(0x00));

    printf("PASSED\n");
}


void
OddSizeRegion(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "OddSizeRegion -> ");

    /* Init: 0x00 ... 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Reverse 5 bytes starting at index 6 (indices 6, 7, 8, 9, 10) */
    /* Values: 0x06, 0x07, 0x08, 0x09, 0x0A */
    /* Expected: 0x0A, 0x09, 0x08, 0x07, 0x06 */
    /* Middle element (0x08 at index 8) stays in place */
    status = GenMemOpsReverseBytesBound(buf, USIZE_C(16), USIZE_C(6), USIZE_C(5));
    assert(status == RESULT_SUCCESS);

    assert(buf[6] == U8_C(0x0A));
    assert(buf[7] == U8_C(0x09));
    assert(buf[8] == U8_C(0x08));
    assert(buf[9] == U8_C(0x07));
    assert(buf[10] == U8_C(0x06));

    /* Verify neighbors */
    assert(buf[5] == U8_C(0x05));
    assert(buf[11] == U8_C(0x0B));

    printf("PASSED\n");
}


void
EvenSizeRegion(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "EvenSizeRegion -> ");

    /* Init: 0x00 ... 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Reverse 6 bytes starting at index 5 (indices 5, 6, 7, 8, 9, 10) */
    /* Values: 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A */
    /* Expected: 0x0A, 0x09, 0x08, 0x07, 0x06, 0x05 */
    status = GenMemOpsReverseBytesBound(buf, USIZE_C(16), USIZE_C(5), USIZE_C(6));
    assert(status == RESULT_SUCCESS);

    assert(buf[5] == U8_C(0x0A));
    assert(buf[6] == U8_C(0x09));
    assert(buf[7] == U8_C(0x08));
    assert(buf[8] == U8_C(0x07));
    assert(buf[9] == U8_C(0x06));
    assert(buf[10] == U8_C(0x05));

    /* Verify neighbors */
    assert(buf[4] == U8_C(0x04));
    assert(buf[11] == U8_C(0x0B));

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    u8    buf[200];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    /* Init: 0..199 (values wrap in u8) */
    kdi_FillSeq(buf, USIZE_C(200), U8_C(0));

    /* Reverse middle section: indices 50-149 (100 bytes) */
    status = GenMemOpsReverseBytesBound(buf, USIZE_C(200), USIZE_C(50), USIZE_C(100));
    assert(status == RESULT_SUCCESS);

    /* Verify pre-range untouched */
    for (i = USIZE_C(0); i < USIZE_C(50); ++i)
    {
        assert(buf[i] == (u8)i);
    }

    /* Verify reversed range */
    for (i = USIZE_C(50); i < USIZE_C(150); ++i)
    {
        assert(buf[i] == (u8)(149 - (i - 50)));
    }

    /* Verify post-range untouched */
    for (i = USIZE_C(150); i < USIZE_C(200); ++i)
    {
        assert(buf[i] == (u8)i);
    }

    printf("PASSED\n");
}


void
DoubleReverse(void)
{
    u8   buf[16];
    u8   original[16];
    bool status;
    usize i;

    printf(LOG_PREFIX_CSTR "DoubleReverse -> ");

    /* Init: 0x00 ... 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Keep copy of original */
    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        original[i] = buf[i];
    }

    /* Reverse middle region twice - should restore */
    status = GenMemOpsReverseBytesBound(buf, USIZE_C(16), USIZE_C(4), USIZE_C(8));
    assert(status == RESULT_SUCCESS);

    status = GenMemOpsReverseBytesBound(buf, USIZE_C(16), USIZE_C(4), USIZE_C(8));
    assert(status == RESULT_SUCCESS);

    /* Verify restored to original */
    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        assert(buf[i] == original[i]);
    }

    printf("PASSED\n");
}


void
AllSameValue(void)
{
    u8   buf[20];
    bool status;
    usize i;

    printf(LOG_PREFIX_CSTR "AllSameValue -> ");

    /* Fill with same value */
    for (i = USIZE_C(0); i < USIZE_C(20); ++i)
    {
        buf[i] = U8_C(0x77);
    }

    /* Reverse a region */
    status = GenMemOpsReverseBytesBound(buf, USIZE_C(20), USIZE_C(5), USIZE_C(10));
    assert(status == RESULT_SUCCESS);

    /* All values should still be 0x77 */
    for (i = USIZE_C(0); i < USIZE_C(20); ++i)
    {
        assert(buf[i] == U8_C(0x77));
    }

    printf("PASSED\n");
}


void
Pattern32Bit(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "Pattern32Bit -> ");

    /* Init buffer */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Set up 32-bit pattern at indices 4-7 */
    buf[4] = U8_C(0x12);
    buf[5] = U8_C(0x34);
    buf[6] = U8_C(0x56);
    buf[7] = U8_C(0x78);

    /* Reverse just those 4 bytes */
    status = GenMemOpsReverseBytesBound(buf, USIZE_C(16), USIZE_C(4), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Expected: reversed */
    assert(buf[4] == U8_C(0x78));
    assert(buf[5] == U8_C(0x56));
    assert(buf[6] == U8_C(0x34));
    assert(buf[7] == U8_C(0x12));

    /* Verify neighbors untouched */
    assert(buf[3] == U8_C(0x03));
    assert(buf[8] == U8_C(0x08));

    printf("PASSED\n");
}


void
Pattern64Bit(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "Pattern64Bit -> ");

    /* Init buffer */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Set up 64-bit pattern at indices 4-11 */
    buf[4] = U8_C(0x11);
    buf[5] = U8_C(0x22);
    buf[6] = U8_C(0x33);
    buf[7] = U8_C(0x44);
    buf[8] = U8_C(0x55);
    buf[9] = U8_C(0x66);
    buf[10] = U8_C(0x77);
    buf[11] = U8_C(0x88);

    /* Reverse those 8 bytes */
    status = GenMemOpsReverseBytesBound(buf, USIZE_C(16), USIZE_C(4), USIZE_C(8));
    assert(status == RESULT_SUCCESS);

    /* Expected: reversed */
    assert(buf[4] == U8_C(0x88));
    assert(buf[5] == U8_C(0x77));
    assert(buf[6] == U8_C(0x66));
    assert(buf[7] == U8_C(0x55));
    assert(buf[8] == U8_C(0x44));
    assert(buf[9] == U8_C(0x33));
    assert(buf[10] == U8_C(0x22));
    assert(buf[11] == U8_C(0x11));

    /* Verify neighbors untouched */
    assert(buf[3] == U8_C(0x03));
    assert(buf[12] == U8_C(0x0C));

    printf("PASSED\n");
}


void
AdjacentRegions(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "AdjacentRegions -> ");

    /* Init: 0x00 ... 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Reverse first half: indices 0-7 */
    /* Values: 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 */
    /* Expected: 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00 */
    status = GenMemOpsReverseBytesBound(buf, USIZE_C(16), USIZE_C(0), USIZE_C(8));
    assert(status == RESULT_SUCCESS);

    /* Reverse second half: indices 8-15 */
    /* Values: 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F */
    /* Expected: 0x0F, 0x0E, 0x0D, 0x0C, 0x0B, 0x0A, 0x09, 0x08 */
    status = GenMemOpsReverseBytesBound(buf, USIZE_C(16), USIZE_C(8), USIZE_C(8));
    assert(status == RESULT_SUCCESS);

    /* Verify first half reversed */
    assert(kdi_VerifyReverse(buf, USIZE_C(8), U8_C(0x00)) == RESULT_SUCCESS);

    /* Verify second half reversed */
    assert(kdi_VerifyReverse(&buf[8], USIZE_C(8), U8_C(0x08)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
VeryLargeCount(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "VeryLargeCount -> ");

    /* Init: 0x00 ... 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Request huge count - should clamp to available space */
    status = GenMemOpsReverseBytesBound(buf, USIZE_C(16), USIZE_C(8), USIZE_C(1000));
    assert(status == RESULT_SUCCESS);

    /* Only indices 8-15 should be reversed */
    /* Values: 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F */
    /* Expected: 0x0F, 0x0E, 0x0D, 0x0C, 0x0B, 0x0A, 0x09, 0x08 */
    assert(buf[8] == U8_C(0x0F));
    assert(buf[9] == U8_C(0x0E));
    assert(buf[10] == U8_C(0x0D));
    assert(buf[11] == U8_C(0x0C));
    assert(buf[12] == U8_C(0x0B));
    assert(buf[13] == U8_C(0x0A));
    assert(buf[14] == U8_C(0x09));
    assert(buf[15] == U8_C(0x08));

    /* Verify beginning untouched */
    assert(kdi_VerifySeq(buf, USIZE_C(8), U8_C(0x00)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    NullPointer();
    ZeroBaseSize();
    ZeroCount();
    BeginIndexOutOfBounds();
    ExactFit();
    CountClamping();
    MiddleRegion();
    SingleByteRegion();
    TwoByteRegion();
    BeginningRegion();
    EndRegion();
    OddSizeRegion();
    EvenSizeRegion();
    LargeBuffer();
    DoubleReverse();
    AllSameValue();
    Pattern32Bit();
    Pattern64Bit();
    AdjacentRegions();
    VeryLargeCount();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}