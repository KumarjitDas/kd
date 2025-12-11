/**
 * @file kdGenMemOpsCopyRange.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsCopyRange function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsCopyRange function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


static bool
kdi_BytesEqual(const byte *a, const byte *b, usize sz)
{
    usize i;

    for (i = 0; i < sz; ++i)
    {
        if (a[i] != b[i])
        {
            return RESULT_FAILURE;
        }
    }

    return RESULT_SUCCESS;
}


void
BasicArguments(void)
{
    byte  src[16];
    byte  dst[16];
    byte  dst_snapshot[16];
    usize i;
    usize copied_sz;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    for (i = 0; i < 16; ++i)
    {
        src[i]          = (byte)(i + 1);
        dst[i]          = U8_C(0xAA);
        dst_snapshot[i] = dst[i];
    }

    /* Null dst_base */
    copied_sz = USIZE_C(1234);
    assert(GenMemOpsCopyRange(null, 16, &copied_sz, src, 16, 0, 0, 8) == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_snapshot, 16) == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(0));

    /* Null src_base */
    copied_sz = USIZE_C(5678);
    assert(GenMemOpsCopyRange(dst, 16, &copied_sz, null, 16, 0, 0, 8) == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_snapshot, 16) == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(0));

    /* Null copied_sz */
    for (i = 0; i < 16; ++i)
    {
        dst[i] = dst_snapshot[i] = U8_C(0xBB);
    }
    assert(GenMemOpsCopyRange(dst, 16, null, src, 16, 0, 0, 8) == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_snapshot, 16) == RESULT_SUCCESS);

    /* Zero dst_base_sz */
    for (i = 0; i < 16; ++i)
    {
        dst[i] = dst_snapshot[i] = U8_C(0xCC);
    }
    copied_sz = USIZE_C(9999);
    assert(GenMemOpsCopyRange(dst, 0, &copied_sz, src, 16, 0, 0, 8) == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_snapshot, 16) == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(0));

    /* Zero src_base_sz */
    for (i = 0; i < 16; ++i)
    {
        dst[i] = dst_snapshot[i] = U8_C(0xDD);
    }
    copied_sz = USIZE_C(9999);
    assert(GenMemOpsCopyRange(dst, 16, &copied_sz, src, 0, 0, 0, 8) == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_snapshot, 16) == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(0));

    /* Zero byte_count */
    for (i = 0; i < 16; ++i)
    {
        dst[i] = dst_snapshot[i] = U8_C(0xEE);
    }
    copied_sz = USIZE_C(9999);
    assert(GenMemOpsCopyRange(dst, 16, &copied_sz, src, 16, 0, 0, 0) == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_snapshot, 16) == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(0));

    /* dst_idx out of bounds */
    for (i = 0; i < 16; ++i)
    {
        dst[i] = dst_snapshot[i] = U8_C(0xF0);
    }
    copied_sz = USIZE_C(9999);
    assert(GenMemOpsCopyRange(dst, 16, &copied_sz, src, 16, 16, 0, 4) == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_snapshot, 16) == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(0));

    /* src_idx out of bounds */
    for (i = 0; i < 16; ++i)
    {
        dst[i] = dst_snapshot[i] = U8_C(0xF1);
    }
    copied_sz = USIZE_C(9999);
    assert(GenMemOpsCopyRange(dst, 16, &copied_sz, src, 16, 0, 16, 4) == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_snapshot, 16) == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(0));

    printf("PASSED\n");
}


void
ExactInBoundsCopy(void)
{
    byte  src[16];
    byte  dst[16];
    usize i;
    usize copied_sz;

    printf(LOG_PREFIX_CSTR "ExactInBoundsCopy -> ");

    for (i = 0; i < 16; ++i)
    {
        src[i] = (byte)(0x10u + i); /* 0x10..0x1F */
        dst[i] = U8_C(0xAA);
    }

    copied_sz = USIZE_C(0);
    assert(GenMemOpsCopyRange(dst, 16, &copied_sz, src, 16, 0, 0, 16) == RESULT_SUCCESS);

    assert(copied_sz == USIZE_C(16));
    assert(kdi_BytesEqual(dst, src, 16) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
DstShorterThanSrcOrByteCount(void)
{
    byte  src[16];
    byte  dst[8];
    usize i;
    usize copied_sz;

    printf(LOG_PREFIX_CSTR "DstShorterThanSrcOrByteCount -> ");

    for (i = 0; i < 16; ++i)
    {
        src[i] = (byte)(0x20u + i); /* 0x20..0x2F */
    }
    for (i = 0; i < 8; ++i)
    {
        dst[i] = U8_C(0xBB);
    }

    /* byte_count > dst span; should clamp to dst span */
    copied_sz = USIZE_C(0);
    assert(GenMemOpsCopyRange(dst, 8, &copied_sz, src, 16, 0, 0, 16) == RESULT_SUCCESS);

    /* min(dst_base_sz - dst_idx, src_base_sz - src_idx, byte_count)
       = min(8, 16, 16) = 8 */
    assert(copied_sz == USIZE_C(8));

    for (i = 0; i < 8; ++i)
    {
        assert(dst[i] == src[i]);
    }

    printf("PASSED\n");
}


void
SrcShorterThanDstOrByteCount(void)
{
    byte  src[8];
    byte  dst[16];
    usize i;
    usize copied_sz;

    printf(LOG_PREFIX_CSTR "SrcShorterThanDstOrByteCount -> ");

    for (i = 0; i < 8; ++i)
    {
        src[i] = (byte)(0x30u + i); /* 0x30..0x37 */
    }
    for (i = 0; i < 16; ++i)
    {
        dst[i] = U8_C(0xCC);
    }

    /* byte_count > src span; should clamp to src span */
    copied_sz = USIZE_C(0);
    assert(GenMemOpsCopyRange(dst, 16, &copied_sz, src, 8, 0, 0, 16) == RESULT_SUCCESS);

    /* min(16, 8, 16) = 8 */
    assert(copied_sz == USIZE_C(8));

    for (i = 0; i < 8; ++i)
    {
        assert(dst[i] == src[i]);
    }
    for (i = 8; i < 16; ++i)
    {
        assert(dst[i] == U8_C(0xCC));
    }

    printf("PASSED\n");
}


void
OffsetIndicesWithClamping(void)
{
    byte  src[32];
    byte  dst[32];
    usize i;
    usize copied_sz;

    printf(LOG_PREFIX_CSTR "OffsetIndicesWithClamping -> ");

    for (i = 0; i < 32; ++i)
    {
        src[i] = (byte)(0x40u + i); /* 0x40..0x5F */
        dst[i] = U8_C(0xAA);
    }

    /* Strict in-bounds case, no clamping needed */
    copied_sz = USIZE_C(0);
    assert(GenMemOpsCopyRange(dst, 32, &copied_sz, src, 32, 4, 2, 8) == RESULT_SUCCESS);

    /* min(32-4=28, 32-2=30, 8) = 8 */
    assert(copied_sz == USIZE_C(8));

    for (i = 0; i < 4; ++i)
    {
        assert(dst[i] == U8_C(0xAA));
    }
    for (i = 0; i < 8; ++i)
    {
        assert(dst[4 + i] == src[2 + i]);
    }

    /* Case that clamps by dst end */
    for (i = 0; i < 32; ++i)
    {
        dst[i] = U8_C(0xBB);
    }

    copied_sz = USIZE_C(0);
    assert(GenMemOpsCopyRange(dst, 32, &copied_sz, src, 32, 28, 10, 16) == RESULT_SUCCESS);

    /* dst span from idx 28: 4 bytes; src span from idx 10: 22; byte_count 16.
       min(4, 22, 16) = 4 */
    assert(copied_sz == USIZE_C(4));

    for (i = 0; i < 28; ++i)
    {
        assert(dst[i] == U8_C(0xBB));
    }
    for (i = 0; i < 4; ++i)
    {
        assert(dst[28 + i] == src[10 + i]);
    }

    /* Case that clamps by src end */
    for (i = 0; i < 32; ++i)
    {
        dst[i] = U8_C(0xCC);
    }

    copied_sz = USIZE_C(0);
    assert(GenMemOpsCopyRange(dst, 32, &copied_sz, src, 32, 0, 30, 16) == RESULT_SUCCESS);

    /* dst span from idx 0: 32; src span from idx 30: 2; byte_count 16.
       min(32, 2, 16) = 2 */
    assert(copied_sz == USIZE_C(2));

    assert(dst[0] == src[30]);
    assert(dst[1] == src[31]);
    for (i = 2; i < 32; ++i)
    {
        assert(dst[i] == U8_C(0xCC));
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
    ExactInBoundsCopy();
    DstShorterThanSrcOrByteCount();
    SrcShorterThanDstOrByteCount();
    OffsetIndicesWithClamping();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
