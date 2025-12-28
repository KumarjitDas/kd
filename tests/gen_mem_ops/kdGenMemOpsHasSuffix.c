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
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsHasSuffix function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
ResultNull(void)
{
    u8   buf[16];
    u8   suffix[4];
    bool status;

    printf(LOG_PREFIX_CSTR "ResultNull -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x10));
    kdi_FillSeq_u8(suffix, USIZE_C(4), U8_C(0x1C));

    /* result pointer is null -> failure */
    status = kdGenMemOpsHasSuffix(null, buf, USIZE_C(16), suffix, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
PtrNull(void)
{
    u8   suffix[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "PtrNull -> ");

    kdi_FillSeq_u8(suffix, USIZE_C(4), U8_C(0x10));

    /* ptr is null (with non-zero size) -> failure */
    status = kdGenMemOpsHasSuffix(&result, null, USIZE_C(16), suffix, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SuffixNull(void)
{
    u8   buf[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "SuffixNull -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x10));

    /* suffix is null (with non-zero size) -> failure */
    status = kdGenMemOpsHasSuffix(&result, buf, USIZE_C(16), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
PtrSizeZero(void)
{
    u8   buf[16];
    u8   suffix[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "PtrSizeZero -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x10));
    kdi_FillSeq_u8(suffix, USIZE_C(4), U8_C(0x10));

    /* ptr_sz is zero -> failure */
    status = kdGenMemOpsHasSuffix(&result, buf, USIZE_C(0), suffix, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SuffixSizeZero(void)
{
    u8   buf[16];
    u8   suffix[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "SuffixSizeZero -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x10));
    kdi_FillSeq_u8(suffix, USIZE_C(4), U8_C(0x10));

    /* suffix_sz is zero -> failure */
    status = kdGenMemOpsHasSuffix(&result, buf, USIZE_C(16), suffix, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SuffixMatches(void)
{
    u8   buf[16];
    u8   suffix[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "SuffixMatches -> ");

    /* buf: 0x10, 0x11, 0x12, 0x13, 0x14, ..., 0x1F */
    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x10));
    /* suffix: 0x1C, 0x1D, 0x1E, 0x1F (last 4 bytes of buf) */
    kdi_FillSeq_u8(suffix, USIZE_C(4), U8_C(0x1C));

    result = false;
    status = kdGenMemOpsHasSuffix(&result, buf, USIZE_C(16), suffix, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
SuffixMismatchAtStart(void)
{
    u8   buf[16];
    u8   suffix[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "SuffixMismatchAtStart -> ");

    /* buf: 0x10, 0x11, 0x12, 0x13, ..., 0x1F */
    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x10));
    /* suffix: 0x1C, 0x1D, 0x1E, 0x1F */
    kdi_FillSeq_u8(suffix, USIZE_C(4), U8_C(0x1C));

    /* Change first byte of suffix */
    suffix[0] = U8_C(0xFF);

    result = true;
    status = kdGenMemOpsHasSuffix(&result, buf, USIZE_C(16), suffix, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
SuffixMismatchAtEnd(void)
{
    u8   buf[16];
    u8   suffix[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "SuffixMismatchAtEnd -> ");

    /* buf: 0x10, 0x11, 0x12, 0x13, ..., 0x1F */
    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x10));
    /* suffix: 0x1C, 0x1D, 0x1E, 0x1F */
    kdi_FillSeq_u8(suffix, USIZE_C(4), U8_C(0x1C));

    /* Change last byte of suffix */
    suffix[3] = U8_C(0xFF);

    result = true;
    status = kdGenMemOpsHasSuffix(&result, buf, USIZE_C(16), suffix, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
SuffixMismatchAtMiddle(void)
{
    u8   buf[16];
    u8   suffix[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "SuffixMismatchAtMiddle -> ");

    /* buf: 0x10, 0x11, 0x12, 0x13, ..., 0x1F */
    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x10));
    /* suffix: 0x1C, 0x1D, 0x1E, 0x1F */
    kdi_FillSeq_u8(suffix, USIZE_C(4), U8_C(0x1C));

    /* Change middle byte of suffix */
    suffix[2] = U8_C(0xFF);

    result = true;
    status = kdGenMemOpsHasSuffix(&result, buf, USIZE_C(16), suffix, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
SuffixTooLong(void)
{
    u8   buf[4];
    u8   suffix[5];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "SuffixTooLong -> ");

    kdi_FillSeq_u8(buf, USIZE_C(4), U8_C(0x10));
    kdi_FillSeq_u8(suffix, USIZE_C(5), U8_C(0x10));

    /* suffix_sz > ptr_sz -> cannot be a suffix */
    result = true;
    status = kdGenMemOpsHasSuffix(&result, buf, USIZE_C(4), suffix, USIZE_C(5));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
FullMatch(void)
{
    u8   buf[16];
    u8   suffix[16];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "FullMatch -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x55));
    kdi_FillSeq_u8(suffix, USIZE_C(16), U8_C(0x55));

    /* Buffer and suffix are identical (same size) */
    result = false;
    status = kdGenMemOpsHasSuffix(&result, buf, USIZE_C(16), suffix, USIZE_C(16));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
SingleByteSuffix(void)
{
    u8   buf[16];
    u8   suffix;
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "SingleByteSuffix -> ");

    /* buf: 0x10, 0x11, ..., 0x1F */
    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x10));
    suffix = U8_C(0x1F); /* Last byte */

    /* Single byte suffix that matches */
    result = false;
    status = kdGenMemOpsHasSuffix(&result, buf, USIZE_C(16), &suffix, USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Single byte suffix that doesn't match */
    suffix = U8_C(0x10); /* First byte, not last */
    result = true;
    status = kdGenMemOpsHasSuffix(&result, buf, USIZE_C(16), &suffix, USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
MatchButNotSuffix(void)
{
    u8   buf[16];
    u8   suffix[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "MatchButNotSuffix -> ");

    /* buf: 0x00, 0x01, 0x02, 0x03, 0x04, ..., 0x0F */
    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x00));

    /* suffix: 0x0B, 0x0C, 0x0D, 0x0E (matches at offset 11, not at end) */
    kdi_FillSeq_u8(suffix, USIZE_C(4), U8_C(0x0B));

    result = true;
    status = kdGenMemOpsHasSuffix(&result, buf, USIZE_C(16), suffix, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == false);

    printf("PASSED\n");
}


void
AllZerosSuffix(void)
{
    u8   buf[16];
    u8   suffix[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "AllZerosSuffix -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));
    kdi_Fill_u8(suffix, USIZE_C(4), U8_C(0x00));

    result = false;
    status = kdGenMemOpsHasSuffix(&result, buf, USIZE_C(16), suffix, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
AllOnesSuffix(void)
{
    u8   buf[16];
    u8   suffix[4];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "AllOnesSuffix -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xFF));
    kdi_Fill_u8(suffix, USIZE_C(4), U8_C(0xFF));

    result = false;
    status = kdGenMemOpsHasSuffix(&result, buf, USIZE_C(16), suffix, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
LargeSuffix(void)
{
    u8    buf[256];
    u8    suffix[100];
    bool  result;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeSuffix -> ");

    /* Fill with sequential values */
    for (i = 0; i < 256; ++i)
    {
        buf[i] = (u8)i;
    }
    /* Last 100 bytes: 156..255 */
    for (i = 0; i < 100; ++i)
    {
        suffix[i] = (u8)(156 + i);
    }

    result = false;
    status = kdGenMemOpsHasSuffix(&result, buf, USIZE_C(256), suffix, USIZE_C(100));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
OddSuffixSizes(void)
{
    u8   buf[16];
    u8   suffix[7];
    bool result;
    bool status;

    printf(LOG_PREFIX_CSTR "OddSuffixSizes -> ");

    /* Suffix size 1 */
    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x10));
    suffix[0] = U8_C(0x1F); /* Last byte */
    result    = false;
    status    = kdGenMemOpsHasSuffix(&result, buf, USIZE_C(16), suffix, USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Suffix size 3 */
    kdi_FillSeq_u8(suffix, USIZE_C(3), U8_C(0x1D)); /* Last 3 bytes */
    result = false;
    status = kdGenMemOpsHasSuffix(&result, buf, USIZE_C(16), suffix, USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Suffix size 5 */
    kdi_FillSeq_u8(suffix, USIZE_C(5), U8_C(0x1B)); /* Last 5 bytes */
    result = false;
    status = kdGenMemOpsHasSuffix(&result, buf, USIZE_C(16), suffix, USIZE_C(5));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    /* Suffix size 7 */
    kdi_FillSeq_u8(suffix, USIZE_C(7), U8_C(0x19)); /* Last 7 bytes */
    result = false;
    status = kdGenMemOpsHasSuffix(&result, buf, USIZE_C(16), suffix, USIZE_C(7));
    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
U16Suffix(void)
{
    u16  buf[16];
    u16  suffix[4];
    bool result;
    bool status;
    usize i;

    printf(LOG_PREFIX_CSTR "U16Suffix -> ");

    /* Fill buffer */
    for (i = 0; i < 16; ++i)
    {
        buf[i] = (u16)(0x1000 + i);
    }

    /* Fill suffix with last 4 values */
    for (i = 0; i < 4; ++i)
    {
        suffix[i] = (u16)(0x1000 + 12 + i);
    }

    result = false;
    status = kdGenMemOpsHasSuffix(&result, buf, sizeof(buf), suffix, sizeof(suffix));

    assert(status == RESULT_SUCCESS);
    assert(result == true);

    printf("PASSED\n");
}


void
U32Suffix(void)
{
    u32  buf[16];
    u32  suffix[4];
    bool result;
    bool status;
    usize i;

    printf(LOG_PREFIX_CSTR "U32Suffix -> ");

    /* Fill buffer */
    for (i = 0; i < 16; ++i)
    {
        buf[i] = (u32)(0x10000000 + i);
    }

    /* Fill suffix with last 4 values */
    for (i = 0; i < 4; ++i)
    {
        suffix[i] = (u32)(0x10000000 + 12 + i);
    }

    result = false;
    status = kdGenMemOpsHasSuffix(&result, buf, sizeof(buf), suffix, sizeof(suffix));

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
    SuffixNull();
    PtrSizeZero();
    SuffixSizeZero();
    SuffixMatches();
    SuffixMismatchAtStart();
    SuffixMismatchAtEnd();
    SuffixMismatchAtMiddle();
    SuffixTooLong();
    FullMatch();
    SingleByteSuffix();
    MatchButNotSuffix();
    AllZerosSuffix();
    AllOnesSuffix();
    LargeSuffix();
    OddSuffixSizes();
    U16Suffix();
    U32Suffix();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}