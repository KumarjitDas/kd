/**
 * @file kdGenMemOpsIsEqualRegion.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsIsEqualRegion function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsIsEqualRegion function test"
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
    u8   buf1[16];
    u8   buf2[16];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillSeq(buf1, USIZE_C(16), U8_C(0x10));
    kdi_FillSeq(buf2, USIZE_C(16), U8_C(0x20));

    /* result pointer is null -> failure */
    status = GenMemOpsIsEqualRegion(null, buf1, USIZE_C(16), buf2, USIZE_C(16));
    assert(status == RESULT_FAILURE);

    /* ptr_1 is null (with non-zero size) -> failure */
    status = GenMemOpsIsEqualRegion(&is_equal, null, USIZE_C(16), buf2, USIZE_C(16));
    assert(status == RESULT_FAILURE);

    /* ptr_2 is null (with non-zero size) -> failure */
    status = GenMemOpsIsEqualRegion(&is_equal, buf1, USIZE_C(16), null, USIZE_C(16));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SizesDiffer(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "SizesDiffer -> ");

    /* Content doesn't matter if sizes differ, but fill them anyway */
    kdi_FillSeq(buf1, USIZE_C(16), U8_C(0x00));
    kdi_FillSeq(buf2, USIZE_C(16), U8_C(0x00));

    /* Compare 16 bytes vs 15 bytes */
    is_equal = RESULT_EQUALS;
    status   = GenMemOpsIsEqualRegion(&is_equal, buf1, USIZE_C(16), buf2, USIZE_C(15));

    assert(status == RESULT_SUCCESS);
    assert(is_equal == RESULT_NOT_EQUALS);

    printf("PASSED\n");
}


void
SizesMatch_ContentDiffers(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "SizesMatch_ContentDiffers -> ");

    kdi_FillSeq(buf1, USIZE_C(16), U8_C(0x55));
    kdi_FillSeq(buf2, USIZE_C(16), U8_C(0x55));

    /* Create mismatch */
    buf2[10] = U8_C(0xFF);

    is_equal = RESULT_EQUALS;
    status   = GenMemOpsIsEqualRegion(&is_equal, buf1, USIZE_C(16), buf2, USIZE_C(16));

    assert(status == RESULT_SUCCESS);
    assert(is_equal == RESULT_NOT_EQUALS);

    printf("PASSED\n");
}


void
SizesMatch_ContentMatches(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "SizesMatch_ContentMatches -> ");

    kdi_FillSeq(buf1, USIZE_C(16), U8_C(0x77));
    kdi_FillSeq(buf2, USIZE_C(16), U8_C(0x77));

    is_equal = RESULT_NOT_EQUALS;
    status   = GenMemOpsIsEqualRegion(&is_equal, buf1, USIZE_C(16), buf2, USIZE_C(16));

    assert(status == RESULT_SUCCESS);
    assert(is_equal == RESULT_EQUALS);

    printf("PASSED\n");
}


void
ZeroLengthRegions(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "ZeroLengthRegions -> ");

    /* 0 vs 0 -> Should be Equal */
    is_equal = RESULT_NOT_EQUALS;
    status   = GenMemOpsIsEqualRegion(&is_equal, buf1, USIZE_C(0), buf2, USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == RESULT_EQUALS);

    /* 0 vs 1 -> Should be Not Equal */
    is_equal = RESULT_EQUALS;
    status   = GenMemOpsIsEqualRegion(&is_equal, buf1, USIZE_C(0), buf2, USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == RESULT_NOT_EQUALS);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    SizesDiffer();
    SizesMatch_ContentDiffers();
    SizesMatch_ContentMatches();
    ZeroLengthRegions();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
