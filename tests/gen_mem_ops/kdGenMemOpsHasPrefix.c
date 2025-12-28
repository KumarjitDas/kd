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
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsHasPrefix function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
ResultNull(void)
{
    u8   buf[16];
    u8   prefix[4];
    bool status;

    printf(LOG_PREFIX_CSTR "ResultNull -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x10));
    kdi_FillSeq_u8(prefix, USIZE_C(4), U8_C(0x10));

    /* result pointer is null -> failure */
    status = kdGenMemOpsHasPrefix(null, buf, USIZE_C(16), prefix, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
PtrNull(void)
{
    u8   prefix[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "PtrNull -> ");

    kdi_FillSeq_u8(prefix, USIZE_C(4), U8_C(0x10));

    /* ptr is null (with non-zero size) -> failure */
    status = kdGenMemOpsHasPrefix(&result, null, USIZE_C(16), prefix, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
PrefixNull(void)
{
    u8   buf[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "PrefixNull -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x10));

    /* prefix is null (with non-zero size) -> failure */
    status = kdGenMemOpsHasPrefix(&result, buf, USIZE_C(16), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
PtrSizeZero(void)
{
    u8   buf[16];
    u8   prefix[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "PtrSizeZero -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x10));
    kdi_FillSeq_u8(prefix, USIZE_C(4), U8_C(0x10));

    /* ptr_sz is zero -> failure */
    status = kdGenMemOpsHasPrefix(&result, buf, USIZE_C(0), prefix, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
PrefixSizeZero(void)
{
    u8   buf[16];
    u8   prefix[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "PrefixSizeZero -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x10));
    kdi_FillSeq_u8(prefix, USIZE_C(4), U8_C(0x10));

    /* prefix_sz is zero -> failure */
    status = kdGenMemOpsHasPrefix(&result, buf, USIZE_C(16), prefix, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
PrefixMatches(void)
{
    u8   buf[16];
    u8   prefix[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "PrefixMatches -> ");

    /* buf: 0x10, 0x11, 0x12, 0x13, 0x14... */
    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x10));
    /* prefix: 0x10, 0x11, 0x12, 0x13 */
    kdi_FillSeq_u8(prefix, USIZE_C(4), U8_C(0x10));

    result = false;
    status = kdGenMemOpsHasPrefix(&result, buf, USIZE_C(16), prefix, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
PrefixMismatchAtStart(void)
{
    u8   buf[16];
    u8   prefix[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "PrefixMismatchAtStart -> ");

    /* buf: 0x10, 0x11, 0x12, 0x13... */
    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x10));
    /* prefix: 0x10, 0x11, 0x12, 0x13 */
    kdi_FillSeq_u8(prefix, USIZE_C(4), U8_C(0x10));

    /* Change first byte of prefix */
    prefix[0] = U8_C(0xFF);

    result = true;
    status = kdGenMemOpsHasPrefix(&result, buf, USIZE_C(16), prefix, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
PrefixMismatchAtEnd(void)
{
    u8   buf[16];
    u8   prefix[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "PrefixMismatchAtEnd -> ");

    /* buf: 0x10, 0x11, 0x12, 0x13... */
    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x10));
    /* prefix: 0x10, 0x11, 0x12, 0x13 */
    kdi_FillSeq_u8(prefix, USIZE_C(4), U8_C(0x10));

    /* Change last byte of prefix */
    prefix[3] = U8_C(0xFF);

    result = true;
    status = kdGenMemOpsHasPrefix(&result, buf, USIZE_C(16), prefix, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
PrefixMismatchAtMiddle(void)
{
    u8   buf[16];
    u8   prefix[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "PrefixMismatchAtMiddle -> ");

    /* buf: 0x10, 0x11, 0x12, 0x13... */
    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x10));
    /* prefix: 0x10, 0x11, 0x12, 0x13 */
    kdi_FillSeq_u8(prefix, USIZE_C(4), U8_C(0x10));

    /* Change middle byte of prefix */
    prefix[2] = U8_C(0xFF);

    result = true;
    status = kdGenMemOpsHasPrefix(&result, buf, USIZE_C(16), prefix, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
PrefixTooLong(void)
{
    u8   buf[4];
    u8   prefix[5];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "PrefixTooLong -> ");

    kdi_FillSeq_u8(buf, USIZE_C(4), U8_C(0x10));
    kdi_FillSeq_u8(prefix, USIZE_C(5), U8_C(0x10));

    /* prefix_sz > ptr_sz -> cannot be a prefix */
    result = true;
    status = kdGenMemOpsHasPrefix(&result, buf, USIZE_C(4), prefix, USIZE_C(5));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
FullMatch(void)
{
    u8   buf[16];
    u8   prefix[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "FullMatch -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x55));
    kdi_FillSeq_u8(prefix, USIZE_C(16), U8_C(0x55));

    /* Buffer and prefix are identical (same size) */
    result = false;
    status = kdGenMemOpsHasPrefix(&result, buf, USIZE_C(16), prefix, USIZE_C(16));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
SingleBytePrefix(void)
{
    u8   buf[16];
    u8   prefix;
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "SingleBytePrefix -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x10));
    prefix = U8_C(0x10);

    /* Single byte prefix that matches */
    result = false;
    status = kdGenMemOpsHasPrefix(&result, buf, USIZE_C(16), &prefix, USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Single byte prefix that doesn't match */
    prefix = U8_C(0xFF);
    result = true;
    status = kdGenMemOpsHasPrefix(&result, buf, USIZE_C(16), &prefix, USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
MatchButNotPrefix(void)
{
    u8   buf[16];
    u8   prefix[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "MatchButNotPrefix -> ");

    /* buf: 0x00, 0x01, 0x02, 0x03, 0x04... */
    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x00));

    /* prefix: 0x01, 0x02, 0x03, 0x04 (matches buf at offset 1, not at 0) */
    kdi_FillSeq_u8(prefix, USIZE_C(4), U8_C(0x01));

    result = true;
    status = kdGenMemOpsHasPrefix(&result, buf, USIZE_C(16), prefix, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
AllZerosPrefix(void)
{
    u8   buf[16];
    u8   prefix[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "AllZerosPrefix -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));
    kdi_Fill_u8(prefix, USIZE_C(4), U8_C(0x00));

    result = false;
    status = kdGenMemOpsHasPrefix(&result, buf, USIZE_C(16), prefix, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
AllOnesPrefix(void)
{
    u8   buf[16];
    u8   prefix[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "AllOnesPrefix -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xFF));
    kdi_Fill_u8(prefix, USIZE_C(4), U8_C(0xFF));

    result = false;
    status = kdGenMemOpsHasPrefix(&result, buf, USIZE_C(16), prefix, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
LargePrefix(void)
{
    u8    buf[256];
    u8    prefix[100];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargePrefix -> ");

    /* Fill with sequential values */
    for (i = 0; i < 256; ++i)
    {
        buf[i] = (u8)i;
    }
    for (i = 0; i < 100; ++i)
    {
        prefix[i] = (u8)i;
    }

    result = false;
    status = kdGenMemOpsHasPrefix(&result, buf, USIZE_C(256), prefix, USIZE_C(100));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
OddPrefixSizes(void)
{
    u8   buf[16];
    u8   prefix[7];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "OddPrefixSizes -> ");

    /* Prefix size 1 */
    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x10));
    prefix[0] = U8_C(0x10);
    result    = false;
    status    = kdGenMemOpsHasPrefix(&result, buf, USIZE_C(16), prefix, USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Prefix size 3 */
    kdi_FillSeq_u8(prefix, USIZE_C(3), U8_C(0x10));
    result = false;
    status = kdGenMemOpsHasPrefix(&result, buf, USIZE_C(16), prefix, USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Prefix size 5 */
    kdi_FillSeq_u8(prefix, USIZE_C(5), U8_C(0x10));
    result = false;
    status = kdGenMemOpsHasPrefix(&result, buf, USIZE_C(16), prefix, USIZE_C(5));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Prefix size 7 */
    kdi_FillSeq_u8(prefix, USIZE_C(7), U8_C(0x10));
    result = false;
    status = kdGenMemOpsHasPrefix(&result, buf, USIZE_C(16), prefix, USIZE_C(7));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
U16Prefix(void)
{
    u16  buf[16];
    u16  prefix[4];
    bool result;
    bool status;
    usize i;

    printf(LOG_PREFIX_CSTR "U16Prefix -> ");

    /* Fill buffer */
    for (i = 0; i < 16; ++i)
    {
        buf[i] = (u16)(0x1000 + i);
    }

    /* Fill prefix with first 4 values */
    for (i = 0; i < 4; ++i)
    {
        prefix[i] = (u16)(0x1000 + i);
    }

    result = false;
    status = kdGenMemOpsHasPrefix(&result, buf, sizeof(buf), prefix, sizeof(prefix));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
U32Prefix(void)
{
    u32  buf[16];
    u32  prefix[4];
    bool result;
    bool status;
    usize i;

    printf(LOG_PREFIX_CSTR "U32Prefix -> ");

    /* Fill buffer */
    for (i = 0; i < 16; ++i)
    {
        buf[i] = (u32)(0x10000000 + i);
    }

    /* Fill prefix with first 4 values */
    for (i = 0; i < 4; ++i)
    {
        prefix[i] = (u32)(0x10000000 + i);
    }

    result = false;
    status = kdGenMemOpsHasPrefix(&result, buf, sizeof(buf), prefix, sizeof(prefix));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    ResultNull();
    PtrNull();
    PrefixNull();
    PtrSizeZero();
    PrefixSizeZero();
    PrefixMatches();
    PrefixMismatchAtStart();
    PrefixMismatchAtEnd();
    PrefixMismatchAtMiddle();
    PrefixTooLong();
    FullMatch();
    SingleBytePrefix();
    MatchButNotPrefix();
    AllZerosPrefix();
    AllOnesPrefix();
    LargePrefix();
    OddPrefixSizes();
    U16Prefix();
    U32Prefix();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}