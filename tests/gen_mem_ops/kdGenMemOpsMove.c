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
kdi_BytesEqual(const u8 *a, const u8 *b, usize n)
{
    usize i;

    for (i = 0; i < n; ++i)
    {
        if (a[i] != b[i])
        {
            return false;
        }
    }

    return true;
}


void
BasicArguments(void)
{
    u8    src[8];
    u8    dst[8];
    u8    orig_src[8];
    u8    orig_dst[8];
    usize i;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* init patterns */
    for (i = 0; i < 8; ++i)
    {
        src[i]      = U8_C(0x10 + i);
        dst[i]      = U8_C(0xA0 + i);
        orig_src[i] = src[i];
        orig_dst[i] = dst[i];
    }

    /* dst is null */
    assert(GenMemOpsMove(null, src, USIZE_C(8)) == RESULT_FAILURE);
    /* src must remain unchanged */
    assert(kdi_BytesEqual(src, orig_src, USIZE_C(8)) == true);

    /* src is null */
    assert(GenMemOpsMove(dst, null, USIZE_C(8)) == RESULT_FAILURE);
    /* dst must remain unchanged */
    assert(kdi_BytesEqual(dst, orig_dst, USIZE_C(8)) == true);

    /* size is zero */
    assert(GenMemOpsMove(dst, src, USIZE_C(0)) == RESULT_FAILURE);
    /* both remain unchanged */
    assert(kdi_BytesEqual(src, orig_src, USIZE_C(8)) == true);
    assert(kdi_BytesEqual(dst, orig_dst, USIZE_C(8)) == true);

    /* src == dst is allowed and should succeed as a no-op move */
    for (i = 0; i < 8; ++i)
    {
        dst[i] = U8_C(0x40 + i);
    }
    assert(GenMemOpsMove(dst, dst, USIZE_C(8)) == RESULT_SUCCESS);
    /* buffer must be unchanged */
    for (i = 0; i < 8; ++i)
    {
        assert(dst[i] == U8_C(0x40 + i));
    }

    printf("PASSED\n");
}


void
NonOverlappingMove(void)
{
    u8    src[8];
    u8    dst[8];
    u8    expected_src[8];
    u8    expected_dst[8];
    usize i;

    printf(LOG_PREFIX_CSTR "NonOverlappingMove -> ");

    for (i = 0; i < 8; ++i)
    {
        src[i]          = U8_C(0x01 + i); /* 0x01 .. 0x08 */
        dst[i]          = U8_C(0xAA);     /* sentinel */
        expected_src[i] = src[i];
        expected_dst[i] = src[i];         /* we expect dst to become equal to src */
    }

    assert(GenMemOpsMove(dst, src, USIZE_C(8)) == RESULT_SUCCESS);

    /* src should remain unchanged */
    assert(kdi_BytesEqual(src, expected_src, USIZE_C(8)) == true);
    /* dst should now equal src */
    assert(kdi_BytesEqual(dst, expected_dst, USIZE_C(8)) == true);

    printf("PASSED\n");
}


void
OverlappingMoveForward(void)
{
    u8    buf[16];
    u8    expected[16];
    usize i;

    printf(LOG_PREFIX_CSTR "OverlappingMoveForward -> ");

    /* buf = 1,2,3,...,16 */
    for (i = 0; i < 16; ++i)
    {
        buf[i] = U8_C(i + 1);
    }

    /* memmove-like behaviour: dst > src, copy from end */
    /* GenMemOpsMove(buf + 4, buf, 8) */
    assert(GenMemOpsMove(buf + 4, buf, USIZE_C(8)) == RESULT_SUCCESS);

    /* expected result (memmove semantics):
     * original: [ 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16 ]
     * move 8 bytes from [0..7] to [4..11]:
     * final:    [ 1,  2,  3,  4,  1,  2,  3,  4,  5,  6,  7,  8, 13, 14, 15, 16 ]
     */
    expected[0]  = U8_C(1);
    expected[1]  = U8_C(2);
    expected[2]  = U8_C(3);
    expected[3]  = U8_C(4);
    expected[4]  = U8_C(1);
    expected[5]  = U8_C(2);
    expected[6]  = U8_C(3);
    expected[7]  = U8_C(4);
    expected[8]  = U8_C(5);
    expected[9]  = U8_C(6);
    expected[10] = U8_C(7);
    expected[11] = U8_C(8);
    expected[12] = U8_C(13);
    expected[13] = U8_C(14);
    expected[14] = U8_C(15);
    expected[15] = U8_C(16);

    for (i = 0; i < 16; ++i)
    {
        assert(buf[i] == expected[i]);
    }

    printf("PASSED\n");
}


void
OverlappingMoveBackward(void)
{
    u8    buf[16];
    u8    expected[16];
    usize i;

    printf(LOG_PREFIX_CSTR "OverlappingMoveBackward -> ");

    /* buf = 1,2,3,...,16 */
    for (i = 0; i < 16; ++i)
    {
        buf[i] = U8_C(i + 1);
    }

    /* memmove-like behaviour: dst < src, copy from start */
    /* GenMemOpsMove(buf, buf + 4, 8) */
    assert(GenMemOpsMove(buf, buf + 4, USIZE_C(8)) == RESULT_SUCCESS);

    /* expected result (memmove semantics):
     * original: [ 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16 ]
     * move 8 bytes from [4..11] to [0..7]:
     * final:    [ 5,  6,  7,  8,  9, 10, 11, 12,  9, 10, 11, 12, 13, 14, 15, 16 ]
     */
    expected[0]  = U8_C(5);
    expected[1]  = U8_C(6);
    expected[2]  = U8_C(7);
    expected[3]  = U8_C(8);
    expected[4]  = U8_C(9);
    expected[5]  = U8_C(10);
    expected[6]  = U8_C(11);
    expected[7]  = U8_C(12);
    expected[8]  = U8_C(9);
    expected[9]  = U8_C(10);
    expected[10] = U8_C(11);
    expected[11] = U8_C(12);
    expected[12] = U8_C(13);
    expected[13] = U8_C(14);
    expected[14] = U8_C(15);
    expected[15] = U8_C(16);

    for (i = 0; i < 16; ++i)
    {
        assert(buf[i] == expected[i]);
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
    NonOverlappingMove();
    OverlappingMoveForward();
    OverlappingMoveBackward();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
