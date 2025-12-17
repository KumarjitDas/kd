/**
 * @file kdGenMemOpsHasSuffix.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsHasSuffix function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsHasSuffix function test"
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
    u8   buf[16];
    u8   suf[4];
    bool has_suffix;
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x10));
    kdi_FillSeq(suf, USIZE_C(4), U8_C(0x10));

    /* result pointer is null -> failure */
    status = GenMemOpsHasSuffix(null, buf, USIZE_C(16), suf, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr is null (and size > 0) -> failure */
    status = GenMemOpsHasSuffix(&has_suffix, null, USIZE_C(16), suf, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* suffix is null (and size > 0) -> failure */
    status = GenMemOpsHasSuffix(&has_suffix, buf, USIZE_C(16), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* suffix_sz is zero -> success (empty set is always a suffix) */
    has_suffix = false;
    status     = GenMemOpsHasSuffix(&has_suffix, buf, USIZE_C(16), suf, USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    assert(has_suffix == true);

    /* ptr_sz is zero, suffix_sz is zero -> success */
    has_suffix = false;
    status     = GenMemOpsHasSuffix(&has_suffix, buf, USIZE_C(0), suf, USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    assert(has_suffix == true);

    printf("PASSED\n");
}


void
SuffixMatches(void)
{
    u8   buf[16];
    u8   suf[4];
    bool has_suffix;
    bool status;

    printf(LOG_PREFIX_CSTR "SuffixMatches -> ");

    /* buf: 0x10, 0x11 ... 0x1F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x10));

    /* Suffix should match last 4 bytes of buf: 0x1C, 0x1D, 0x1E, 0x1F */
    /* Start value = 0x10 + (16 - 4) = 0x1C */
    kdi_FillSeq(suf, USIZE_C(4), U8_C(0x1C));

    has_suffix = false;
    status     = GenMemOpsHasSuffix(&has_suffix, buf, USIZE_C(16), suf, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(has_suffix == true);

    printf("PASSED\n");
}


void
SuffixMismatchContent(void)
{
    u8   buf[16];
    u8   suf[4];
    bool has_suffix;
    bool status;

    printf(LOG_PREFIX_CSTR "SuffixMismatchContent -> ");

    /* buf: 0x10 ... 0x1F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x10));

    /* Expected Suffix: 0x1C ... 0x1F */
    kdi_FillSeq(suf, USIZE_C(4), U8_C(0x1C));

    /* Corrupt the suffix (e.g. last byte) */
    suf[3]     = U8_C(0x00);

    has_suffix = true;
    status     = GenMemOpsHasSuffix(&has_suffix, buf, USIZE_C(16), suf, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(has_suffix == false);

    printf("PASSED\n");
}


void
SuffixTooLong(void)
{
    u8   buf[4];
    u8   suf[5];
    bool has_suffix;
    bool status;

    printf(LOG_PREFIX_CSTR "SuffixTooLong -> ");

    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x10));
    kdi_FillSeq(suf, USIZE_C(5), U8_C(0x10));

    /* Suffix length > Ptr length -> Cannot be a suffix */
    has_suffix = true;
    status     = GenMemOpsHasSuffix(&has_suffix, buf, USIZE_C(4), suf, USIZE_C(5));

    assert(status == RESULT_SUCCESS);
    assert(has_suffix == false);

    printf("PASSED\n");
}


void
FullMatch(void)
{
    u8   buf[16];
    u8   suf[16];
    bool has_suffix;
    bool status;

    printf(LOG_PREFIX_CSTR "FullMatch -> ");

    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x55));
    kdi_FillSeq(suf, USIZE_C(16), U8_C(0x55));

    /* Pointer and Suffix are identical and same size */
    has_suffix = false;
    status     = GenMemOpsHasSuffix(&has_suffix, buf, USIZE_C(16), suf, USIZE_C(16));

    assert(status == RESULT_SUCCESS);
    assert(has_suffix == true);

    printf("PASSED\n");
}


void
MatchButNotSuffix(void)
{
    u8   buf[16];
    u8   suf[4];
    bool has_suffix;
    bool status;

    printf(LOG_PREFIX_CSTR "MatchButNotSuffix -> ");

    /* buf: 0x10 ... 0x1F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x10));

    /* suf: 0x10, 0x11, 0x12, 0x13 */
    /* This matches the BEGINNING of buf (prefix), but not the END */
    kdi_FillSeq(suf, USIZE_C(4), U8_C(0x10));

    has_suffix = true;
    status     = GenMemOpsHasSuffix(&has_suffix, buf, USIZE_C(16), suf, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(has_suffix == false);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    SuffixMatches();
    SuffixMismatchContent();
    SuffixTooLong();
    FullMatch();
    MatchButNotSuffix();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
