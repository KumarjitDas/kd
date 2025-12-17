/**
 * @file kdGenMemOpsHasPrefix.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsHasPrefix function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsHasPrefix function test"
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
    u8   pre[4];
    bool has_prefix;
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x10));
    kdi_FillSeq(pre, USIZE_C(4), U8_C(0x10));

    /* result pointer is null -> failure */
    status = GenMemOpsHasPrefix(null, buf, USIZE_C(16), pre, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr is null (and size > 0) -> failure */
    status = GenMemOpsHasPrefix(&has_prefix, null, USIZE_C(16), pre, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* prefix is null (and size > 0) -> failure */
    status = GenMemOpsHasPrefix(&has_prefix, buf, USIZE_C(16), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* prefix_sz is zero -> success (empty set is always a prefix) */
    has_prefix = false;
    status     = GenMemOpsHasPrefix(&has_prefix, buf, USIZE_C(16), pre, USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    assert(has_prefix == true);

    /* ptr_sz is zero, prefix_sz is zero -> success */
    has_prefix = false;
    status     = GenMemOpsHasPrefix(&has_prefix, buf, USIZE_C(0), pre, USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    assert(has_prefix == true);

    printf("PASSED\n");
}


void
PrefixMatches(void)
{
    u8   buf[16];
    u8   pre[4];
    bool has_prefix;
    bool status;

    printf(LOG_PREFIX_CSTR "PrefixMatches -> ");

    /* buf: 10, 11, 12, 13, 14... */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x10));
    /* pre: 10, 11, 12, 13 */
    kdi_FillSeq(pre, USIZE_C(4), U8_C(0x10));

    has_prefix = false;
    status     = GenMemOpsHasPrefix(&has_prefix, buf, USIZE_C(16), pre, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(has_prefix == true);

    printf("PASSED\n");
}


void
PrefixMismatchContent(void)
{
    u8   buf[16];
    u8   pre[4];
    bool has_prefix;
    bool status;

    printf(LOG_PREFIX_CSTR "PrefixMismatchContent -> ");

    /* buf: 10, 11, 12, 13... */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x10));
    /* pre: 10, 11, 12, 13 */
    kdi_FillSeq(pre, USIZE_C(4), U8_C(0x10));

    /* Change last byte of prefix */
    pre[3]     = U8_C(0xFF);

    has_prefix = true;
    status     = GenMemOpsHasPrefix(&has_prefix, buf, USIZE_C(16), pre, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(has_prefix == false);

    printf("PASSED\n");
}


void
PrefixTooLong(void)
{
    u8   buf[4];
    u8   pre[5];
    bool has_prefix;
    bool status;

    printf(LOG_PREFIX_CSTR "PrefixTooLong -> ");

    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x10));
    kdi_FillSeq(pre, USIZE_C(5), U8_C(0x10));

    /* Prefix length > Ptr length -> Cannot be a prefix */
    has_prefix = true;
    status     = GenMemOpsHasPrefix(&has_prefix, buf, USIZE_C(4), pre, USIZE_C(5));

    assert(status == RESULT_SUCCESS);
    assert(has_prefix == false);

    printf("PASSED\n");
}


void
FullMatch(void)
{
    u8   buf[16];
    u8   pre[16];
    bool has_prefix;
    bool status;

    printf(LOG_PREFIX_CSTR "FullMatch -> ");

    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x55));
    kdi_FillSeq(pre, USIZE_C(16), U8_C(0x55));

    /* Pointer and Prefix are identical and same size */
    has_prefix = false;
    status     = GenMemOpsHasPrefix(&has_prefix, buf, USIZE_C(16), pre, USIZE_C(16));

    assert(status == RESULT_SUCCESS);
    assert(has_prefix == true);

    printf("PASSED\n");
}


void
MatchButNotPrefix(void)
{
    u8   buf[16];
    u8   pre[4];
    bool has_prefix;
    bool status;

    printf(LOG_PREFIX_CSTR "MatchButNotPrefix -> ");

    /* buf: 00, 01, 02, 03, 04... */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* pre: 01, 02, 03, 04 (Matches buf at offset 1, but not at 0) */
    kdi_FillSeq(pre, USIZE_C(4), U8_C(0x01));

    has_prefix = true;
    status     = GenMemOpsHasPrefix(&has_prefix, buf, USIZE_C(16), pre, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(has_prefix == false);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    PrefixMatches();
    PrefixMismatchContent();
    PrefixTooLong();
    FullMatch();
    MatchButNotPrefix();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
