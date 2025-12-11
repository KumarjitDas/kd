/**
 * @file kdGenMemOpsMoveRegion.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsMoveRegion function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsMoveRegion function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


static int
kdi_BytesEqual(const u8 *a, const u8 *b, usize n)
{
    usize i;

    for (i = USIZE_C(0); i < n; ++i)
    {
        if (a[i] != b[i])
        {
            return 0;
        }
    }

    return 1;
}


void
BasicArguments(void)
{
    u8    dst[8];
    u8    src[8];
    u8    dst_orig[8];
    u8    src_orig[8];
    usize moved_sz;
    usize i;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        dst[i]      = U8_C(0xA0 + i);
        src[i]      = U8_C(0x10 + i);
        dst_orig[i] = dst[i];
        src_orig[i] = src[i];
    }

    /* dst is null: moved_sz must be set to 0 on failure */
    moved_sz = USIZE_C(0xDEAD);
    assert(GenMemOpsMoveRegion(null, USIZE_C(8), &moved_sz, src, USIZE_C(8)) == RESULT_FAILURE);
    assert(moved_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(8)) != 0);
    assert(kdi_BytesEqual(src, src_orig, USIZE_C(8)) != 0);

    /* src is null: moved_sz must be 0 */
    moved_sz = USIZE_C(0xBEEF);
    assert(GenMemOpsMoveRegion(dst, USIZE_C(8), &moved_sz, null, USIZE_C(8)) == RESULT_FAILURE);
    assert(moved_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(8)) != 0);
    assert(kdi_BytesEqual(src, src_orig, USIZE_C(8)) != 0);

    /* moved_sz is null: must fail, buffers unchanged */
    assert(GenMemOpsMoveRegion(dst, USIZE_C(8), null, src, USIZE_C(8)) == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(8)) != 0);
    assert(kdi_BytesEqual(src, src_orig, USIZE_C(8)) != 0);

    /* dst_sz == 0: moved_sz forced to 0 */
    moved_sz = USIZE_C(1234);
    assert(GenMemOpsMoveRegion(dst, USIZE_C(0), &moved_sz, src, USIZE_C(8)) == RESULT_FAILURE);
    assert(moved_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(8)) != 0);
    assert(kdi_BytesEqual(src, src_orig, USIZE_C(8)) != 0);

    /* src_sz == 0: moved_sz forced to 0 */
    moved_sz = USIZE_C(5678);
    assert(GenMemOpsMoveRegion(dst, USIZE_C(8), &moved_sz, src, USIZE_C(0)) == RESULT_FAILURE);
    assert(moved_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(8)) != 0);
    assert(kdi_BytesEqual(src, src_orig, USIZE_C(8)) != 0);

    printf("PASSED\n");
}


void
NonOverlappingEqualSizes(void)
{
    u8    dst[8];
    u8    src[8];
    u8    src_orig[8];
    usize moved_sz;
    usize i;

    printf(LOG_PREFIX_CSTR "NonOverlappingEqualSizes -> ");

    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        dst[i]      = U8_C(0xAA);
        src[i]      = U8_C(0x10 + i);
        src_orig[i] = src[i];
    }

    moved_sz = USIZE_C(0);
    assert(GenMemOpsMoveRegion(dst, USIZE_C(8), &moved_sz, src, USIZE_C(8)) == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(8));

    /* dst now equals src_orig */
    assert(kdi_BytesEqual(dst, src_orig, USIZE_C(8)) != 0);

    /* src unchanged: "move" here is memmove-style, not destructive */
    assert(kdi_BytesEqual(src, src_orig, USIZE_C(8)) != 0);

    printf("PASSED\n");
}


void
ClampedByDstSize(void)
{
    u8    dst[4];
    u8    src[8];
    u8    dst_orig[4];
    u8    src_orig[8];
    usize moved_sz;
    usize i;

    printf(LOG_PREFIX_CSTR "ClampedByDstSize -> ");

    for (i = USIZE_C(0); i < USIZE_C(4); ++i)
    {
        dst[i]      = U8_C(0xA0 + i);
        dst_orig[i] = dst[i];
    }

    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        src[i]      = U8_C(0x20 + i);
        src_orig[i] = src[i];
    }

    /* dst_sz < src_sz => moved size = dst_sz */
    moved_sz = USIZE_C(0);
    assert(GenMemOpsMoveRegion(dst, USIZE_C(4), &moved_sz, src, USIZE_C(8)) == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(4));

    /* dst now has first 4 bytes of src_orig */
    for (i = USIZE_C(0); i < USIZE_C(4); ++i)
    {
        assert(dst[i] == src_orig[i]);
    }

    /* src unchanged */
    assert(kdi_BytesEqual(src, src_orig, USIZE_C(8)) != 0);

    printf("PASSED\n");
}


void
ClampedBySrcSize(void)
{
    u8    dst[8];
    u8    src[4];
    u8    dst_orig[8];
    u8    src_orig[4];
    usize moved_sz;
    usize i;

    printf(LOG_PREFIX_CSTR "ClampedBySrcSize -> ");

    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        dst[i]      = U8_C(0xAA);
        dst_orig[i] = dst[i];
    }

    for (i = USIZE_C(0); i < USIZE_C(4); ++i)
    {
        src[i]      = U8_C(0x30 + i);
        src_orig[i] = src[i];
    }

    /* src_sz < dst_sz => moved size = src_sz */
    moved_sz = USIZE_C(0);
    assert(GenMemOpsMoveRegion(dst, USIZE_C(8), &moved_sz, src, USIZE_C(4)) == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(4));

    /* first 4 bytes of dst now equal src_orig */
    for (i = USIZE_C(0); i < USIZE_C(4); ++i)
    {
        assert(dst[i] == src_orig[i]);
    }

    /* remaining dst bytes unchanged */
    for (i = USIZE_C(4); i < USIZE_C(8); ++i)
    {
        assert(dst[i] == dst_orig[i]);
    }

    /* src unchanged */
    assert(kdi_BytesEqual(src, src_orig, USIZE_C(4)) != 0);

    printf("PASSED\n");
}


void
OverlappingForwardSameBuffer(void)
{
    u8    buf[16];
    u8    expected[16];
    usize moved_sz;
    usize i;

    printf(LOG_PREFIX_CSTR "OverlappingForwardSameBuffer -> ");

    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        buf[i] = U8_C(i + 1);
    }

    /* memmove-style: move 8 bytes from buf[0..7] to buf[4..11]
     * dst = buf + 4, dst_sz = 8
     * src = buf + 0, src_sz = 8
     */
    moved_sz = USIZE_C(0);
    assert(GenMemOpsMoveRegion(buf + 4, USIZE_C(8), &moved_sz, buf + 0, USIZE_C(8)) == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(8));

    /* expected:
     * original: [ 1, 2, 3, 4, 5, 6, 7, 8,  9,10,11,12,13,14,15,16 ]
     * final:    [ 1, 2, 3, 4, 1, 2, 3, 4,  5, 6, 7, 8,13,14,15,16 ]
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

    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        assert(buf[i] == expected[i]);
    }

    printf("PASSED\n");
}


void
OverlappingBackwardSameBuffer(void)
{
    u8    buf[16];
    u8    expected[16];
    usize moved_sz;
    usize i;

    printf(LOG_PREFIX_CSTR "OverlappingBackwardSameBuffer -> ");

    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        buf[i] = U8_C(i + 1);
    }

    /* memmove-style: move 8 bytes from buf[4..11] to buf[0..7]
     * dst = buf + 0, dst_sz = 8
     * src = buf + 4, src_sz = 8
     */
    moved_sz = USIZE_C(0);
    assert(GenMemOpsMoveRegion(buf + 0, USIZE_C(8), &moved_sz, buf + 4, USIZE_C(8)) == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(8));

    /* expected:
     * original: [ 1, 2, 3, 4, 5, 6, 7, 8,  9,10,11,12,13,14,15,16 ]
     * final:    [ 5, 6, 7, 8, 9,10,11,12,  9,10,11,12,13,14,15,16 ]
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

    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
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
    NonOverlappingEqualSizes();
    ClampedByDstSize();
    ClampedBySrcSize();
    OverlappingForwardSameBuffer();
    OverlappingBackwardSameBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
