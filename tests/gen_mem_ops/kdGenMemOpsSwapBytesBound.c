/**
 * @file kdGenMemOpsSwapBytesBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsSwapBytesBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsSwapBytesBound function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "





void
Base1Null(void)
{
    u8   buf2[8];
    bool status;

    printf(LOG_PREFIX_CSTR "Base1Null -> ");

    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x00));

    /* base_1 is null -> failure */
    status = GenMemOpsSwapBytesBound(null, USIZE_C(8), USIZE_C(0), buf2, USIZE_C(8), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* Verify buf2 unchanged */
    assert(buf2[0] == U8_C(0x00));

    printf("PASSED\n");
}


void
Base2Null(void)
{
    u8   buf1[8];
    bool status;

    printf(LOG_PREFIX_CSTR "Base2Null -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x00));

    /* base_2 is null -> failure */
    status = GenMemOpsSwapBytesBound(buf1, USIZE_C(8), USIZE_C(0), null, USIZE_C(8), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* Verify buf1 unchanged */
    assert(buf1[0] == U8_C(0x00));

    printf("PASSED\n");
}


void
BothBasesNull(void)
{
    bool status;

    printf(LOG_PREFIX_CSTR "BothBasesNull -> ");

    /* Both bases null -> failure */
    status = GenMemOpsSwapBytesBound(null, USIZE_C(8), USIZE_C(0), null, USIZE_C(8), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
Base1SizeZero(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool status;

    printf(LOG_PREFIX_CSTR "Base1SizeZero -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x10));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x20));

    /* base_1_sz is zero -> failure */
    status = GenMemOpsSwapBytesBound(buf1, USIZE_C(0), USIZE_C(0), buf2, USIZE_C(8), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* Verify buffers unchanged */
    assert(buf1[0] == U8_C(0x10));
    assert(buf2[0] == U8_C(0x20));

    printf("PASSED\n");
}


void
Base2SizeZero(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool status;

    printf(LOG_PREFIX_CSTR "Base2SizeZero -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x10));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x20));

    /* base_2_sz is zero -> failure */
    status = GenMemOpsSwapBytesBound(buf1, USIZE_C(8), USIZE_C(0), buf2, USIZE_C(0), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* Verify buffers unchanged */
    assert(buf1[0] == U8_C(0x10));
    assert(buf2[0] == U8_C(0x20));

    printf("PASSED\n");
}


void
BothSizesZero(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool status;

    printf(LOG_PREFIX_CSTR "BothSizesZero -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x10));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x20));

    /* Both sizes zero -> failure */
    status = GenMemOpsSwapBytesBound(buf1, USIZE_C(0), USIZE_C(0), buf2, USIZE_C(0), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* Verify buffers unchanged */
    assert(buf1[0] == U8_C(0x10));
    assert(buf2[0] == U8_C(0x20));

    printf("PASSED\n");
}


void
Base1IdxOutOfBounds(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool status;

    printf(LOG_PREFIX_CSTR "Base1IdxOutOfBounds -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x00));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x10));

    /* base_1_idx >= base_1_sz -> failure */
    status = GenMemOpsSwapBytesBound(buf1, USIZE_C(8), USIZE_C(8), buf2, USIZE_C(8), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    status = GenMemOpsSwapBytesBound(buf1, USIZE_C(8), USIZE_C(10), buf2, USIZE_C(8), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* Verify buffers unchanged */
    assert(buf1[0] == U8_C(0x00));
    assert(buf2[0] == U8_C(0x10));

    printf("PASSED\n");
}


void
Base2IdxOutOfBounds(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool status;

    printf(LOG_PREFIX_CSTR "Base2IdxOutOfBounds -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x00));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x10));

    /* base_2_idx >= base_2_sz -> failure */
    status = GenMemOpsSwapBytesBound(buf1, USIZE_C(8), USIZE_C(0), buf2, USIZE_C(8), USIZE_C(8));
    assert(status == RESULT_FAILURE);

    status = GenMemOpsSwapBytesBound(buf1, USIZE_C(8), USIZE_C(0), buf2, USIZE_C(8), USIZE_C(12));
    assert(status == RESULT_FAILURE);

    /* Verify buffers unchanged */
    assert(buf1[0] == U8_C(0x00));
    assert(buf2[0] == U8_C(0x10));

    printf("PASSED\n");
}


void
BothIndicesOutOfBounds(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool status;

    printf(LOG_PREFIX_CSTR "BothIndicesOutOfBounds -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x00));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x10));

    /* Both indices out of bounds -> failure */
    status = GenMemOpsSwapBytesBound(buf1, USIZE_C(8), USIZE_C(10), buf2, USIZE_C(8), USIZE_C(12));
    assert(status == RESULT_FAILURE);

    /* Verify buffers unchanged */
    assert(buf1[0] == U8_C(0x00));
    assert(buf2[0] == U8_C(0x10));

    printf("PASSED\n");
}


void
SwapDifferentBuffers(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapDifferentBuffers -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x10));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x20));

    /* Swap buf1[0] with buf2[0] */
    status = GenMemOpsSwapBytesBound(buf1, USIZE_C(8), USIZE_C(0), buf2, USIZE_C(8), USIZE_C(0));
    assert(status == RESULT_SUCCESS);

    /* Verify swap */
    assert(buf1[0] == U8_C(0x20));
    assert(buf2[0] == U8_C(0x10));

    /* Verify rest unchanged */
    assert(buf1[1] == U8_C(0x11));
    assert(buf2[1] == U8_C(0x21));

    printf("PASSED\n");
}


void
SwapSameBufferDifferentIndices(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapSameBufferDifferentIndices -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Swap buf[3] with buf[10] (same buffer) */
    status = GenMemOpsSwapBytesBound(buf, USIZE_C(16), USIZE_C(3), buf, USIZE_C(16), USIZE_C(10));
    assert(status == RESULT_SUCCESS);

    /* Verify swap */
    assert(buf[3] == U8_C(0x0A));
    assert(buf[10] == U8_C(0x03));

    /* Verify neighbors unchanged */
    assert(buf[2] == U8_C(0x02));
    assert(buf[4] == U8_C(0x04));
    assert(buf[9] == U8_C(0x09));
    assert(buf[11] == U8_C(0x0B));

    printf("PASSED\n");
}


void
SwapSameBufferSameIndex(void)
{
    u8   buf[8];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapSameBufferSameIndex -> ");

    kdi_FillSeq_u8(buf, USIZE_C(8), U8_C(0x00));

    /* Swap buf[5] with buf[5] (same location) -> success, no change */
    status = GenMemOpsSwapBytesBound(buf, USIZE_C(8), USIZE_C(5), buf, USIZE_C(8), USIZE_C(5));
    assert(status == RESULT_SUCCESS);

    /* Value should remain unchanged */
    assert(buf[5] == U8_C(0x05));

    /* Verify entire buffer unchanged */
    assert(buf[0] == U8_C(0x00));
    assert(buf[7] == U8_C(0x07));

    printf("PASSED\n");
}


void
SwapFirstElements(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapFirstElements -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0xA0));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0xB0));

    /* Swap first elements */
    status = GenMemOpsSwapBytesBound(buf1, USIZE_C(8), USIZE_C(0), buf2, USIZE_C(8), USIZE_C(0));
    assert(status == RESULT_SUCCESS);

    assert(buf1[0] == U8_C(0xB0));
    assert(buf2[0] == U8_C(0xA0));

    printf("PASSED\n");
}


void
SwapLastElements(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapLastElements -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x10));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x20));

    /* Swap last elements */
    status = GenMemOpsSwapBytesBound(buf1, USIZE_C(8), USIZE_C(7), buf2, USIZE_C(8), USIZE_C(7));
    assert(status == RESULT_SUCCESS);

    assert(buf1[7] == U8_C(0x27));
    assert(buf2[7] == U8_C(0x17));

    /* Verify rest unchanged */
    assert(buf1[6] == U8_C(0x16));
    assert(buf2[6] == U8_C(0x26));

    printf("PASSED\n");
}


void
SwapMiddleElements(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapMiddleElements -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(16), U8_C(0x00));
    kdi_FillSeq_u8(buf2, USIZE_C(16), U8_C(0x10));

    /* Swap middle elements */
    status = GenMemOpsSwapBytesBound(buf1, USIZE_C(16), USIZE_C(7), buf2, USIZE_C(16), USIZE_C(8));
    assert(status == RESULT_SUCCESS);

    assert(buf1[7] == U8_C(0x18));
    assert(buf2[8] == U8_C(0x07));

    /* Verify neighbors unchanged */
    assert(buf1[6] == U8_C(0x06));
    assert(buf1[8] == U8_C(0x08));
    assert(buf2[7] == U8_C(0x17));
    assert(buf2[9] == U8_C(0x19));

    printf("PASSED\n");
}


void
SwapDifferentSizedBuffers(void)
{
    u8   buf1[16];
    u8   buf2[8];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapDifferentSizedBuffers -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(16), U8_C(0x00));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x20));

    /* Swap buf1[10] with buf2[5] */
    status = GenMemOpsSwapBytesBound(buf1, USIZE_C(16), USIZE_C(10), buf2, USIZE_C(8), USIZE_C(5));
    assert(status == RESULT_SUCCESS);

    assert(buf1[10] == U8_C(0x25));
    assert(buf2[5] == U8_C(0x0A));

    printf("PASSED\n");
}


void
DoubleSwap(void)
{
    u8   buf1[8];
    u8   buf2[8];
    u8   orig1, orig2;
    bool status;

    printf(LOG_PREFIX_CSTR "DoubleSwap -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x30));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x40));

    orig1 = buf1[3];
    orig2 = buf2[5];

    /* Swap once */
    status = GenMemOpsSwapBytesBound(buf1, USIZE_C(8), USIZE_C(3), buf2, USIZE_C(8), USIZE_C(5));
    assert(status == RESULT_SUCCESS);

    /* Swap again - should restore */
    status = GenMemOpsSwapBytesBound(buf1, USIZE_C(8), USIZE_C(3), buf2, USIZE_C(8), USIZE_C(5));
    assert(status == RESULT_SUCCESS);

    /* Should be back to original */
    assert(buf1[3] == orig1);
    assert(buf2[5] == orig2);

    printf("PASSED\n");
}


void
SwapZeroAndNonZero(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapZeroAndNonZero -> ");

    buf1[0] = U8_C(0x00);
    buf2[0] = U8_C(0xFF);

    status = GenMemOpsSwapBytesBound(buf1, USIZE_C(8), USIZE_C(0), buf2, USIZE_C(8), USIZE_C(0));
    assert(status == RESULT_SUCCESS);

    assert(buf1[0] == U8_C(0xFF));
    assert(buf2[0] == U8_C(0x00));

    printf("PASSED\n");
}


void
SwapSameValues(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapSameValues -> ");

    kdi_Fill_u8(buf1, USIZE_C(8), U8_C(0x77));
    kdi_Fill_u8(buf2, USIZE_C(8), U8_C(0x77));

    status = GenMemOpsSwapBytesBound(buf1, USIZE_C(8), USIZE_C(3), buf2, USIZE_C(8), USIZE_C(5));
    assert(status == RESULT_SUCCESS);

    /* Both should still be 0x77 */
    assert(buf1[3] == U8_C(0x77));
    assert(buf2[5] == U8_C(0x77));

    printf("PASSED\n");
}


void
MultipleSwaps(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool status;

    printf(LOG_PREFIX_CSTR "MultipleSwaps -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x00));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x10));

    /* Swap buf1[0] with buf2[0] */
    status = GenMemOpsSwapBytesBound(buf1, USIZE_C(8), USIZE_C(0), buf2, USIZE_C(8), USIZE_C(0));
    assert(status == RESULT_SUCCESS);

    /* Swap buf1[1] with buf2[1] */
    status = GenMemOpsSwapBytesBound(buf1, USIZE_C(8), USIZE_C(1), buf2, USIZE_C(8), USIZE_C(1));
    assert(status == RESULT_SUCCESS);

    /* Swap buf1[2] with buf2[2] */
    status = GenMemOpsSwapBytesBound(buf1, USIZE_C(8), USIZE_C(2), buf2, USIZE_C(8), USIZE_C(2));
    assert(status == RESULT_SUCCESS);

    /* Verify swaps */
    assert(buf1[0] == U8_C(0x10));
    assert(buf1[1] == U8_C(0x11));
    assert(buf1[2] == U8_C(0x12));
    assert(buf2[0] == U8_C(0x00));
    assert(buf2[1] == U8_C(0x01));
    assert(buf2[2] == U8_C(0x02));

    /* Verify rest unchanged */
    assert(buf1[3] == U8_C(0x03));
    assert(buf2[3] == U8_C(0x13));

    printf("PASSED\n");
}


void
SwapAdjacentIndicesSameBuffer(void)
{
    u8   buf[8];
    bool status;

    printf(LOG_PREFIX_CSTR "SwapAdjacentIndicesSameBuffer -> ");

    kdi_FillSeq_u8(buf, USIZE_C(8), U8_C(0x00));

    /* Swap buf[3] with buf[4] (adjacent) */
    status = GenMemOpsSwapBytesBound(buf, USIZE_C(8), USIZE_C(3), buf, USIZE_C(8), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Verify swap */
    assert(buf[3] == U8_C(0x04));
    assert(buf[4] == U8_C(0x03));

    /* Verify neighbors unchanged */
    assert(buf[2] == U8_C(0x02));
    assert(buf[5] == U8_C(0x05));

    printf("PASSED\n");
}


void
LargeBuffers(void)
{
    u8    buf1[100];
    u8    buf2[100];
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffers -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(100), U8_C(0));
    kdi_FillSeq_u8(buf2, USIZE_C(100), U8_C(100));

    /* Swap buf1[50] with buf2[75] */
    status = GenMemOpsSwapBytesBound(buf1, USIZE_C(100), USIZE_C(50), buf2, USIZE_C(100), USIZE_C(75));
    assert(status == RESULT_SUCCESS);

    /* Verify swap */
    assert(buf1[50] == U8_C(175));
    assert(buf2[75] == U8_C(50));

    /* Verify rest unchanged */
    for (i = USIZE_C(0); i < USIZE_C(50); ++i)
    {
        assert(buf1[i] == (u8)i);
    }
    for (i = USIZE_C(51); i < USIZE_C(100); ++i)
    {
        assert(buf1[i] == (u8)i);
    }
    for (i = USIZE_C(0); i < USIZE_C(75); ++i)
    {
        assert(buf2[i] == (u8)(100 + i));
    }
    for (i = USIZE_C(76); i < USIZE_C(100); ++i)
    {
        assert(buf2[i] == (u8)(100 + i));
    }

    printf("PASSED\n");
}


void
BoundaryIndices(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BoundaryIndices -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(16), U8_C(0x00));
    kdi_FillSeq_u8(buf2, USIZE_C(16), U8_C(0x20));

    /* Swap first of buf1 with last of buf2 */
    status = GenMemOpsSwapBytesBound(buf1, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(15));
    assert(status == RESULT_SUCCESS);

    assert(buf1[0] == U8_C(0x2F));
    assert(buf2[15] == U8_C(0x00));

    /* Swap last of buf1 with first of buf2 */
    status = GenMemOpsSwapBytesBound(buf1, USIZE_C(16), USIZE_C(15), buf2, USIZE_C(16), USIZE_C(0));
    assert(status == RESULT_SUCCESS);

    assert(buf1[15] == U8_C(0x20));
    assert(buf2[0] == U8_C(0x0F));

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    Base1Null();
    Base2Null();
    BothBasesNull();
    Base1SizeZero();
    Base2SizeZero();
    BothSizesZero();
    Base1IdxOutOfBounds();
    Base2IdxOutOfBounds();
    BothIndicesOutOfBounds();
    SwapDifferentBuffers();
    SwapSameBufferDifferentIndices();
    SwapSameBufferSameIndex();
    SwapFirstElements();
    SwapLastElements();
    SwapMiddleElements();
    SwapDifferentSizedBuffers();
    DoubleSwap();
    SwapZeroAndNonZero();
    SwapSameValues();
    MultipleSwaps();
    SwapAdjacentIndicesSameBuffer();
    LargeBuffers();
    BoundaryIndices();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
