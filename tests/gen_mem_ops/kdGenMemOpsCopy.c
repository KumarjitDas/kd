/**
 * @file kdGenMemOpsCopy.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsCopy function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsCopy function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


static bool
kdi_ArraysEqual(const byte *a, const byte *b, usize sz)
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
    byte src[4]      = {1, 2, 3, 4};
    byte dst[4]      = {9, 9, 9, 9};
    byte expected[4] = {9, 9, 9, 9};

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* Null destination */
    assert(GenMemOpsCopy(null, src, 4) == RESULT_FAILURE);

    /* Null source – must fail and not touch destination */
    assert(GenMemOpsCopy(dst, null, 4) == RESULT_FAILURE);
    assert(kdi_ArraysEqual(dst, expected, 4) == RESULT_SUCCESS);

    /* Zero size – must fail and leave destination intact */
    assert(GenMemOpsCopy(dst, src, 0) == RESULT_FAILURE);
    assert(kdi_ArraysEqual(dst, expected, 4) == RESULT_SUCCESS);

    /* Valid arguments */
    assert(GenMemOpsCopy(dst, src, 4) == RESULT_SUCCESS);
    assert(kdi_ArraysEqual(dst, src, 4) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
BasicCopySmallBuffers(void)
{
    byte  src[8];
    byte  dst[8];
    usize i;

    printf(LOG_PREFIX_CSTR "BasicCopySmallBuffers -> ");

    for (i = 0; i < 8; ++i)
    {
        src[i] = (byte)(i + 1);
        dst[i] = U8_C(0xAA);
    }

    assert(GenMemOpsCopy(dst, src, 8) == RESULT_SUCCESS);

    for (i = 0; i < 8; ++i)
    {
        assert(dst[i] == src[i]);
    }

    printf("PASSED\n");
}


void
CopyIntoSubRegion(void)
{
    byte  src[32];
    byte  dst[32];
    usize i;

    printf(LOG_PREFIX_CSTR "CopyIntoSubRegion -> ");

    for (i = 0; i < 32; ++i)
    {
        src[i] = (byte)i;
        dst[i] = U8_C(0xFF);
    }

    /* Copy 10 bytes from src[5] to dst[10] */
    assert(GenMemOpsCopy(dst + 10, src + 5, 10) == RESULT_SUCCESS);

    for (i = 0; i < 10; ++i)
    {
        assert(dst[i] == U8_C(0xFF));
    }

    for (i = 0; i < 10; ++i)
    {
        assert(dst[10 + i] == src[5 + i]);
    }

    for (i = 20; i < 32; ++i)
    {
        assert(dst[i] == U8_C(0xFF));
    }

    printf("PASSED\n");
}


void
SelfCopyNoOp(void)
{
    byte  buf[16];
    byte  expected[16];
    usize i;

    printf(LOG_PREFIX_CSTR "SelfCopyNoOp -> ");

    for (i = 0; i < 16; ++i)
    {
        buf[i]      = (byte)(i * 3u);
        expected[i] = buf[i];
    }

    assert(GenMemOpsCopy(buf, buf, 16) == RESULT_SUCCESS);
    assert(kdi_ArraysEqual(buf, expected, 16) == RESULT_SUCCESS);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    BasicCopySmallBuffers();
    CopyIntoSubRegion();
    SelfCopyNoOp();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
