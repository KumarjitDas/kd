/**
 * @file kdGenMemOpsMove.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsMove function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsMove function test"
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
kdi_FillSeq(byte *dst, usize sz, byte start)
{
    usize i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        dst[i] = (byte)(start + (byte)i);
    }
}


static void
kdi_FillVal(byte *dst, usize sz, byte val)
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
    /*
     * Test NULL pointer validation and zero-size parameter.
     * Failures should not modify destination.
     */
    byte src[8];
    byte dst[8];
    byte dst_orig[8];
    bool result;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillSeq(src, USIZE_C(8), U8_C(0x10));
    kdi_FillVal(dst, USIZE_C(8), U8_C(0xAA));
    kdi_FillVal(dst_orig, USIZE_C(8), U8_C(0xAA));

    /* dst is null */
    result = GenMemOpsMove(null, src, USIZE_C(8));
    assert(result == RESULT_FAILURE);

    /* src is null */
    result = GenMemOpsMove(dst, null, USIZE_C(8));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(8)) == RESULT_SUCCESS);

    /* sz is zero */
    result = GenMemOpsMove(dst, src, USIZE_C(0));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(8)) == RESULT_SUCCESS);

    /* Valid arguments */
    result = GenMemOpsMove(dst, src, USIZE_C(8));
    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, src, USIZE_C(8)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SingleByteMove(void)
{
    /*
     * Minimal case: move exactly 1 byte.
     */
    byte src[1];
    byte dst[1];
    bool result;

    printf(LOG_PREFIX_CSTR "SingleByteMove -> ");

    src[0] = U8_C(0x77);
    dst[0] = U8_C(0x00);

    result = GenMemOpsMove(dst, src, USIZE_C(1));

    assert(result == RESULT_SUCCESS);
    assert(dst[0] == U8_C(0x77));

    printf("PASSED\n");
}


void
NonOverlappingMove(void)
{
    /*
     * Move between non-overlapping regions (like copy).
     */
    byte src[16];
    byte dst[16];
    bool result;

    printf(LOG_PREFIX_CSTR "NonOverlappingMove -> ");

    kdi_FillSeq(src, USIZE_C(16), U8_C(0x20));
    kdi_FillVal(dst, USIZE_C(16), U8_C(0x00));

    result = GenMemOpsMove(dst, src, USIZE_C(16));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, src, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
OverlappingMoveForward(void)
{
    /*
     * Move within same buffer where dst > src (forward/right shift).
     * buf: [0,1,2,3,4,5,6,7,8,9]
     * Move buf[0..4] to buf[3..7]
     * Result: [0,1,2,0,1,2,3,4,8,9]
     */
    byte  buf[10];
    byte  expected[10];
    bool  result;

    printf(LOG_PREFIX_CSTR "OverlappingMoveForward -> ");

    kdi_FillSeq(buf, USIZE_C(10), U8_C(0x00));

    /* Build expected result */
    expected[0] = U8_C(0x00);
    expected[1] = U8_C(0x01);
    expected[2] = U8_C(0x02);
    expected[3] = U8_C(0x00);
    expected[4] = U8_C(0x01);
    expected[5] = U8_C(0x02);
    expected[6] = U8_C(0x03);
    expected[7] = U8_C(0x04);
    expected[8] = U8_C(0x08);
    expected[9] = U8_C(0x09);

    result = GenMemOpsMove(buf + USIZE_C(3), buf, USIZE_C(5));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(10)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
OverlappingMoveBackward(void)
{
    /*
     * Move within same buffer where dst < src (backward/left shift).
     * buf: [0,1,2,3,4,5,6,7,8,9]
     * Move buf[3..7] to buf[1..5]
     * Result: [0,3,4,5,6,7,6,7,8,9]
     */
    byte  buf[10];
    byte  expected[10];
    bool  result;

    printf(LOG_PREFIX_CSTR "OverlappingMoveBackward -> ");

    kdi_FillSeq(buf, USIZE_C(10), U8_C(0x00));

    /* Build expected result */
    expected[0] = U8_C(0x00);
    expected[1] = U8_C(0x03);
    expected[2] = U8_C(0x04);
    expected[3] = U8_C(0x05);
    expected[4] = U8_C(0x06);
    expected[5] = U8_C(0x07);
    expected[6] = U8_C(0x06);
    expected[7] = U8_C(0x07);
    expected[8] = U8_C(0x08);
    expected[9] = U8_C(0x09);

    result = GenMemOpsMove(buf + USIZE_C(1), buf + USIZE_C(3), USIZE_C(5));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(10)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
OverlappingMovePartial(void)
{
    /*
     * Partial overlap: only some bytes overlap.
     * buf: [A,B,C,D,E,F,G,H]
     * Move buf[2..5] to buf[4..7]
     * Result: [A,B,C,D,C,D,E,F]
     */
    byte  buf[8];
    byte  expected[8];
    bool  result;

    printf(LOG_PREFIX_CSTR "OverlappingMovePartial -> ");

    buf[0] = U8_C(0xA0);
    buf[1] = U8_C(0xB0);
    buf[2] = U8_C(0xC0);
    buf[3] = U8_C(0xD0);
    buf[4] = U8_C(0xE0);
    buf[5] = U8_C(0xF0);
    buf[6] = U8_C(0x10);
    buf[7] = U8_C(0x20);

    expected[0] = U8_C(0xA0);
    expected[1] = U8_C(0xB0);
    expected[2] = U8_C(0xC0);
    expected[3] = U8_C(0xD0);
    expected[4] = U8_C(0xC0);
    expected[5] = U8_C(0xD0);
    expected[6] = U8_C(0xE0);
    expected[7] = U8_C(0xF0);

    result = GenMemOpsMove(buf + USIZE_C(4), buf + USIZE_C(2), USIZE_C(4));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(8)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SelfMoveIdenticalPointers(void)
{
    /*
     * Move where dst and src are identical (no-op but should succeed).
     */
    byte  buf[16];
    byte  buf_orig[16];
    bool  result;

    printf(LOG_PREFIX_CSTR "SelfMoveIdenticalPointers -> ");

    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x30));
    kdi_FillSeq(buf_orig, USIZE_C(16), U8_C(0x30));

    result = GenMemOpsMove(buf, buf, USIZE_C(16));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, buf_orig, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
LargeBufferMove(void)
{
    /*
     * Move large non-overlapping buffers.
     */
    byte src[256];
    byte dst[256];
    bool result;

    printf(LOG_PREFIX_CSTR "LargeBufferMove -> ");

    kdi_FillSeq(src, USIZE_C(256), U8_C(0x00));
    kdi_FillVal(dst, USIZE_C(256), U8_C(0xFF));

    result = GenMemOpsMove(dst, src, USIZE_C(256));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, src, USIZE_C(256)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
LargeOverlappingMove(void)
{
    /*
     * Large overlapping move within same buffer.
     * buf size: 200 bytes
     * Move buf[10..109] to buf[50..149]
     */
    byte  buf[200];
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeOverlappingMove -> ");

    kdi_FillSeq(buf, USIZE_C(200), U8_C(0x00));

    result = GenMemOpsMove(buf + USIZE_C(50), buf + USIZE_C(10), USIZE_C(100));

    assert(result == RESULT_SUCCESS);

    /* Verify moved region */
    for (i = USIZE_C(0); i < USIZE_C(100); ++i)
    {
        assert(buf[USIZE_C(50) + i] == (byte)(U8_C(0x0A) + (byte)i));
    }

    printf("PASSED\n");
}


void
AllZerosMove(void)
{
    /*
     * Move buffer of all zeros.
     */
    byte src[16];
    byte dst[16];
    bool result;

    printf(LOG_PREFIX_CSTR "AllZerosMove -> ");

    kdi_FillVal(src, USIZE_C(16), U8_C(0x00));
    kdi_FillVal(dst, USIZE_C(16), U8_C(0xFF));

    result = GenMemOpsMove(dst, src, USIZE_C(16));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, src, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
AllOnesMove(void)
{
    /*
     * Move buffer of all 0xFF bytes.
     */
    byte src[16];
    byte dst[16];
    bool result;

    printf(LOG_PREFIX_CSTR "AllOnesMove -> ");

    kdi_FillVal(src, USIZE_C(16), U8_C(0xFF));
    kdi_FillVal(dst, USIZE_C(16), U8_C(0x00));

    result = GenMemOpsMove(dst, src, USIZE_C(16));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, src, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
AlternatingPatternMove(void)
{
    /*
     * Move buffer with alternating byte pattern.
     */
    byte  src[32];
    byte  dst[32];
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "AlternatingPatternMove -> ");

    kdi_FillVal(dst, USIZE_C(32), U8_C(0x00));

    for (i = USIZE_C(0); i < USIZE_C(32); ++i)
    {
        src[i] = (i & USIZE_C(1)) ? U8_C(0xAA) : U8_C(0x55);
    }

    result = GenMemOpsMove(dst, src, USIZE_C(32));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, src, USIZE_C(32)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
OddSizeMove(void)
{
    /*
     * Move buffers with odd size.
     */
    byte src[19];
    byte dst[19];
    bool result;

    printf(LOG_PREFIX_CSTR "OddSizeMove -> ");

    kdi_FillSeq(src, USIZE_C(19), U8_C(0x40));
    kdi_FillVal(dst, USIZE_C(19), U8_C(0x00));

    result = GenMemOpsMove(dst, src, USIZE_C(19));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, src, USIZE_C(19)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
OverlappingMoveOneByteOffset(void)
{
    /*
     * Overlapping move with minimal 1-byte offset.
     * buf: [0,1,2,3,4,5,6,7]
     * Move buf[0..6] to buf[1..7]
     * Result: [0,0,1,2,3,4,5,6]
     */
    byte  buf[8];
    byte  expected[8];
    bool  result;
    usize i;

    printf(LOG_PREFIX_CSTR "OverlappingMoveOneByteOffset -> ");

    kdi_FillSeq(buf, USIZE_C(8), U8_C(0x00));

    for (i = USIZE_C(0); i < USIZE_C(7); ++i)
    {
        expected[i + USIZE_C(1)] = (byte)i;
    }
    expected[0] = U8_C(0x00);

    result = GenMemOpsMove(buf + USIZE_C(1), buf, USIZE_C(7));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(8)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    SingleByteMove();
    NonOverlappingMove();
    OverlappingMoveForward();
    OverlappingMoveBackward();
    OverlappingMovePartial();
    SelfMoveIdenticalPointers();
    LargeBufferMove();
    LargeOverlappingMove();
    AllZerosMove();
    AllOnesMove();
    AlternatingPatternMove();
    OddSizeMove();
    OverlappingMoveOneByteOffset();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
