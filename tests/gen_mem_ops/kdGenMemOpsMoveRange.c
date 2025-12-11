/**
 * @file kdGenMemOpsMoveRange.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsMoveRange function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsMoveRange function test"
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
    u8    dst[16];
    u8    src[16];
    u8    dst_orig[16];
    u8    src_orig[16];
    usize moved_sz;
    usize i;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        dst[i]      = U8_C(0xA0 + i);
        src[i]      = U8_C(0x10 + i);
        dst_orig[i] = dst[i];
        src_orig[i] = src[i];
    }

    /* dst_base is null */
    moved_sz = USIZE_C(0xDEAD);
    assert(GenMemOpsMoveRange(null, USIZE_C(16), &moved_sz, src, USIZE_C(16), USIZE_C(0), USIZE_C(0), USIZE_C(8)) == RESULT_FAILURE);
    assert(moved_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(16)) != 0);
    assert(kdi_BytesEqual(src, src_orig, USIZE_C(16)) != 0);

    /* src_base is null */
    moved_sz = USIZE_C(0xBEEF);
    assert(GenMemOpsMoveRange(dst, USIZE_C(16), &moved_sz, null, USIZE_C(16), USIZE_C(0), USIZE_C(0), USIZE_C(8)) == RESULT_FAILURE);
    assert(moved_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(16)) != 0);
    assert(kdi_BytesEqual(src, src_orig, USIZE_C(16)) != 0);

    /* moved_sz is null */
    assert(GenMemOpsMoveRange(dst, USIZE_C(16), null, src, USIZE_C(16), USIZE_C(0), USIZE_C(0), USIZE_C(8)) == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(16)) != 0);
    assert(kdi_BytesEqual(src, src_orig, USIZE_C(16)) != 0);

    /* dst_base_sz == 0 */
    moved_sz = USIZE_C(1234);
    assert(GenMemOpsMoveRange(dst, USIZE_C(0), &moved_sz, src, USIZE_C(16), USIZE_C(0), USIZE_C(0), USIZE_C(8)) == RESULT_FAILURE);
    assert(moved_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(16)) != 0);
    assert(kdi_BytesEqual(src, src_orig, USIZE_C(16)) != 0);

    /* src_base_sz == 0 */
    moved_sz = USIZE_C(5678);
    assert(GenMemOpsMoveRange(dst, USIZE_C(16), &moved_sz, src, USIZE_C(0), USIZE_C(0), USIZE_C(0), USIZE_C(8)) == RESULT_FAILURE);
    assert(moved_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(16)) != 0);
    assert(kdi_BytesEqual(src, src_orig, USIZE_C(16)) != 0);

    /* byte_count == 0 */
    moved_sz = USIZE_C(9999);
    assert(GenMemOpsMoveRange(dst, USIZE_C(16), &moved_sz, src, USIZE_C(16), USIZE_C(0), USIZE_C(0), USIZE_C(0)) == RESULT_FAILURE);
    assert(moved_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(16)) != 0);
    assert(kdi_BytesEqual(src, src_orig, USIZE_C(16)) != 0);

    /* dst_idx out of range (>= dst_base_sz) */
    moved_sz = USIZE_C(42);
    assert(GenMemOpsMoveRange(dst, USIZE_C(16), &moved_sz, src, USIZE_C(16), USIZE_C(16), USIZE_C(0), USIZE_C(4)) == RESULT_FAILURE);
    assert(moved_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(16)) != 0);
    assert(kdi_BytesEqual(src, src_orig, USIZE_C(16)) != 0);

    /* src_idx out of range (>= src_base_sz) */
    moved_sz = USIZE_C(1337);
    assert(GenMemOpsMoveRange(dst, USIZE_C(16), &moved_sz, src, USIZE_C(16), USIZE_C(0), USIZE_C(16), USIZE_C(4)) == RESULT_FAILURE);
    assert(moved_sz == USIZE_C(0));
    assert(kdi_BytesEqual(dst, dst_orig, USIZE_C(16)) != 0);
    assert(kdi_BytesEqual(src, src_orig, USIZE_C(16)) != 0);

    printf("PASSED\n");
}


void
NonOverlappingSimpleRange(void)
{
    u8    dst[16];
    u8    src[16];
    u8    dst_orig[16];
    u8    src_orig[16];
    usize moved_sz;
    usize i;

    printf(LOG_PREFIX_CSTR "NonOverlappingSimpleRange -> ");

    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        dst[i]      = U8_C(0xA0 + i);
        src[i]      = U8_C(0x10 + i);
        dst_orig[i] = dst[i];
        src_orig[i] = src[i];
    }

    /* Move 4 bytes from src[0..3] to dst[4..7] */
    moved_sz = USIZE_C(0);
    assert(GenMemOpsMoveRange(dst, USIZE_C(16), &moved_sz, src, USIZE_C(16), USIZE_C(4), USIZE_C(0), USIZE_C(4)) == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(4));

    /* dst[0..3] unchanged */
    for (i = USIZE_C(0); i < USIZE_C(4); ++i)
    {
        assert(dst[i] == dst_orig[i]);
    }

    /* dst[4..7] now equal src_orig[0..3] */
    for (i = USIZE_C(0); i < USIZE_C(4); ++i)
    {
        assert(dst[4 + i] == src_orig[i]);
    }

    /* dst[8..15] unchanged */
    for (i = USIZE_C(8); i < USIZE_C(16); ++i)
    {
        assert(dst[i] == dst_orig[i]);
    }

    /* src unchanged */
    assert(kdi_BytesEqual(src, src_orig, USIZE_C(16)) != 0);

    printf("PASSED\n");
}


void
ClampedByDstRange(void)
{
    u8    dst[8];
    u8    src[16];
    u8    dst_orig[8];
    u8    src_orig[16];
    usize moved_sz;
    usize i;

    printf(LOG_PREFIX_CSTR "ClampedByDstRange -> ");

    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        dst[i]      = U8_C(0xD0 + i);
        dst_orig[i] = dst[i];
    }

    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        src[i]      = U8_C(0x20 + i);
        src_orig[i] = src[i];
    }

    /* dst_idx = 4, dst_base_sz = 8 => at most 4 bytes can be written
     * src_idx = 0, src_base_sz = 16, byte_count = 16
     * to_copy = min(8-4, 16-0, 16) = 4
     */
    moved_sz = USIZE_C(0);
    assert(GenMemOpsMoveRange(dst, USIZE_C(8), &moved_sz, src, USIZE_C(16), USIZE_C(4), USIZE_C(0), USIZE_C(16)) == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(4));

    /* dst[0..3] unchanged */
    for (i = USIZE_C(0); i < USIZE_C(4); ++i)
    {
        assert(dst[i] == dst_orig[i]);
    }

    /* dst[4..7] == src_orig[0..3] */
    for (i = USIZE_C(0); i < USIZE_C(4); ++i)
    {
        assert(dst[4 + i] == src_orig[i]);
    }

    /* src unchanged */
    assert(kdi_BytesEqual(src, src_orig, USIZE_C(16)) != 0);

    printf("PASSED\n");
}


void
ClampedBySrcRange(void)
{
    u8    dst[16];
    u8    src[8];
    u8    dst_orig[16];
    u8    src_orig[8];
    usize moved_sz;
    usize i;

    printf(LOG_PREFIX_CSTR "ClampedBySrcRange -> ");

    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        dst[i]      = U8_C(0xAA);
        dst_orig[i] = dst[i];
    }

    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        src[i]      = U8_C(0x30 + i);
        src_orig[i] = src[i];
    }

    /* dst_idx = 0, dst_base_sz = 16 => can accept 16 bytes
     * src_idx = 4, src_base_sz = 8 => only 4 bytes available
     * byte_count = 16
     * to_copy = min(16-0, 8-4, 16) = 4
     */
    moved_sz = USIZE_C(0);
    assert(GenMemOpsMoveRange(dst, USIZE_C(16), &moved_sz, src, USIZE_C(8), USIZE_C(0), USIZE_C(4), USIZE_C(16)) == RESULT_SUCCESS);
    assert(moved_sz == USIZE_C(4));

    for (i = USIZE_C(0); i < USIZE_C(4); ++i)
    {
        assert(dst[i] == src_orig[4 + i]);
    }

    for (i = USIZE_C(4); i < USIZE_C(16); ++i)
    {
        assert(dst[i] == dst_orig[i]);
    }

    assert(kdi_BytesEqual(src, src_orig, USIZE_C(8)) != 0);

    printf("PASSED\n");
}


void
OverlappingForwardSameBase(void)
{
    u8    buf[16];
    u8    expected[16];
    usize moved_sz;
    usize i;

    printf(LOG_PREFIX_CSTR "OverlappingForwardSameBase -> ");

    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        buf[i] = U8_C(i + 1);
    }

    /* Move 8 bytes from buf[0..7] to buf[4..11] */
    moved_sz = USIZE_C(0);
    assert(GenMemOpsMoveRange(buf, USIZE_C(16), &moved_sz, buf, USIZE_C(16), USIZE_C(4), USIZE_C(0), USIZE_C(8)) == RESULT_SUCCESS);
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
OverlappingBackwardSameBase(void)
{
    u8    buf[16];
    u8    expected[16];
    usize moved_sz;
    usize i;

    printf(LOG_PREFIX_CSTR "OverlappingBackwardSameBase -> ");

    for (i = USIZE_C(0); i < USIZE_C(16); ++i)
    {
        buf[i] = U8_C(i + 1);
    }

    /* Move 8 bytes from buf[4..11] to buf[0..7] */
    moved_sz = USIZE_C(0);
    assert(GenMemOpsMoveRange(buf, USIZE_C(16), &moved_sz, buf, USIZE_C(16), USIZE_C(0), USIZE_C(4), USIZE_C(8)) == RESULT_SUCCESS);
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
    NonOverlappingSimpleRange();
    ClampedByDstRange();
    ClampedBySrcRange();
    OverlappingForwardSameBase();
    OverlappingBackwardSameBase();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
