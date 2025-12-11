/**
 * @file kdGenMemOpsCopyRegion.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsCopyRegion function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */

#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsCopyRegion function test"
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

    /* Null dst */
    copied_sz = USIZE_C(1234);
    assert(GenMemOpsCopyRegion(null, 16, &copied_sz, src, 16) == RESULT_FAILURE);
    /* dst unchanged; copied_sz becomes 0 */
    assert(kdi_BytesEqual(dst, dst_snapshot, 16) == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(0));

    /* Null src */
    copied_sz = USIZE_C(5678);
    assert(GenMemOpsCopyRegion(dst, 16, &copied_sz, null, 16) == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_snapshot, 16) == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(0));

    /* Null copied_sz */
    for (i = 0; i < 16; ++i)
    {
        dst[i] = dst_snapshot[i] = U8_C(0xBB);
    }
    assert(GenMemOpsCopyRegion(dst, 16, null, src, 16) == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_snapshot, 16) == RESULT_SUCCESS);

    /* Zero dst_sz */
    for (i = 0; i < 16; ++i)
    {
        dst[i] = dst_snapshot[i] = U8_C(0xCC);
    }
    copied_sz = USIZE_C(9999);
    assert(GenMemOpsCopyRegion(dst, 0, &copied_sz, src, 16) == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_snapshot, 16) == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(0));

    /* Zero src_sz */
    for (i = 0; i < 16; ++i)
    {
        dst[i] = dst_snapshot[i] = U8_C(0xDD);
    }
    copied_sz = USIZE_C(9999);
    assert(GenMemOpsCopyRegion(dst, 16, &copied_sz, src, 0) == RESULT_FAILURE);
    assert(kdi_BytesEqual(dst, dst_snapshot, 16) == RESULT_SUCCESS);
    assert(copied_sz == USIZE_C(0));

    printf("PASSED\n");
}


void
SrcSmallerThanDst(void)
{
    byte  src[8];
    byte  dst[16];
    usize i;
    usize copied_sz;

    printf(LOG_PREFIX_CSTR "SrcSmallerThanDst -> ");

    for (i = 0; i < 8; ++i)
    {
        src[i] = (byte)(0x10u + i); /* 0x10..0x17 */
    }
    for (i = 0; i < 16; ++i)
    {
        dst[i] = U8_C(0xAA);
    }

    copied_sz = USIZE_C(0);
    assert(GenMemOpsCopyRegion(dst, 16, &copied_sz, src, 8) == RESULT_SUCCESS);

    /* Should copy min(dst_sz, src_sz) = 8 bytes */
    assert(copied_sz == USIZE_C(8));

    /* First 8 bytes equal src */
    for (i = 0; i < 8; ++i)
    {
        assert(dst[i] == src[i]);
    }

    /* Remaining bytes unchanged */
    for (i = 8; i < 16; ++i)
    {
        assert(dst[i] == U8_C(0xAA));
    }

    printf("PASSED\n");
}


void
DstSmallerThanSrc(void)
{
    byte  src[16];
    byte  dst[8];
    usize i;
    usize copied_sz;

    printf(LOG_PREFIX_CSTR "DstSmallerThanSrc -> ");

    for (i = 0; i < 16; ++i)
    {
        src[i] = (byte)(0x20u + i); /* 0x20..0x2F */
    }
    for (i = 0; i < 8; ++i)
    {
        dst[i] = U8_C(0xBB);
    }

    copied_sz = USIZE_C(0);
    assert(GenMemOpsCopyRegion(dst, 8, &copied_sz, src, 16) == RESULT_SUCCESS);

    /* Should copy min(dst_sz, src_sz) = 8 bytes */
    assert(copied_sz == USIZE_C(8));

    for (i = 0; i < 8; ++i)
    {
        assert(dst[i] == src[i]);
    }

    printf("PASSED\n");
}


void
ExactSizeCopy(void)
{
    byte  src[16];
    byte  dst[16];
    usize i;
    usize copied_sz;

    printf(LOG_PREFIX_CSTR "ExactSizeCopy -> ");

    for (i = 0; i < 16; ++i)
    {
        src[i] = (byte)(0x30u + i); /* 0x30..0x3F */
        dst[i] = U8_C(0xCC);
    }

    copied_sz = USIZE_C(0);
    assert(GenMemOpsCopyRegion(dst, 16, &copied_sz, src, 16) == RESULT_SUCCESS);

    assert(copied_sz == USIZE_C(16));
    assert(kdi_BytesEqual(dst, src, 16) == RESULT_SUCCESS);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    SrcSmallerThanDst();
    DstSmallerThanSrc();
    ExactSizeCopy();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
