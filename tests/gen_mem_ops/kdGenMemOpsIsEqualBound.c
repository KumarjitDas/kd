/**
 * @file kdGenMemOpsIsEqualBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsIsEqualBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsIsEqualBound function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(16), U8_C(0x10));
    kdi_FillSeq_u8(buf2, USIZE_C(16), U8_C(0x10));

    /* result pointer is null -> failure */
    status = kdGenMemOpsIsEqualBound(null, buf1, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_1 is null -> failure */
    status = kdGenMemOpsIsEqualBound(&is_equal, null, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_2 is null -> failure */
    status = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(16), USIZE_C(0), null, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_1_sz is zero -> failure */
    status = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(0), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_2_sz is zero -> failure */
    status = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(0), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* byte_count is zero -> failure (!byte_count check) */
    status = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
CountClamping(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "CountClamping -> ");

    /* Fill buffers with identical data */
    kdi_FillSeq_u8(buf1, USIZE_C(16), U8_C(0x00));
    kdi_FillSeq_u8(buf2, USIZE_C(16), U8_C(0x00));

    /* * Request 10 bytes starting from index 14.
     * buf1: 16 - 14 = 2 bytes available.
     * buf2: 16 - 14 = 2 bytes available.
     * Clamped count = 2.
     * Content matches at 14 and 15.
     */
    is_equal = false;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(16), USIZE_C(14), buf2, USIZE_C(16), USIZE_C(14), USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(is_equal == true);

    /* * Asymmetric Clamping
     * Request 10 bytes.
     * buf1 start 14 (2 bytes avail: 14, 15).
     * buf2 start 0  (16 bytes avail).
     * Common intersection = 2 bytes.
     * Compare buf1[14..15] with buf2[0..1].
     * buf1[14]=0x0E, buf2[0]=0x00 -> Mismatch.
     */
    is_equal = true;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(16), USIZE_C(14), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(is_equal == false);

    printf("PASSED\n");
}


void
IndicesOutOfBounds(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "IndicesOutOfBounds -> ");

    /* base_1_idx >= base_1_sz */
    status = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(16), USIZE_C(16), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_2_idx >= base_2_sz */
    status = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(16), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
RangesMatch(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "RangesMatch -> ");

    /* Fill identical sequences */
    kdi_FillSeq_u8(buf1, USIZE_C(16), U8_C(0x10));
    kdi_FillSeq_u8(buf2, USIZE_C(16), U8_C(0x10));

    /* Identical ranges */
    is_equal = false;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(16), USIZE_C(4), buf2, USIZE_C(16), USIZE_C(4), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(is_equal == true);

    /* Different indices, but content happens to match (e.g. if we filled with const value) */
    /* Let's verify mismatch for seq pattern: buf1[4]=0x14, buf2[5]=0x15 -> Mismatch */
    is_equal = true;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(16), USIZE_C(4), buf2, USIZE_C(16), USIZE_C(5), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(is_equal == false);

    printf("PASSED\n");
}


void
RangesDoNotMatch(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "RangesDoNotMatch -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(16), U8_C(0x10));
    kdi_FillSeq_u8(buf2, USIZE_C(16), U8_C(0x10));

    /* Create mismatch in buf2 at index 6 */
    buf2[6]  = U8_C(0xFF);

    /* Compare range [4..7] (size 4) */
    is_equal = true;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(16), USIZE_C(4), buf2, USIZE_C(16), USIZE_C(4), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(is_equal == false);

    /* Compare range [0..3] (size 4) -> Should match (before dirty byte) */
    is_equal = false;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(is_equal == true);

    printf("PASSED\n");
}


void
OverlappingRangesSameBuffer(void)
{
    u8   buf[16];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "OverlappingRangesSameBuffer -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x00)); /* 0, 1, 2, 3... */

    /* Compare index 0 vs index 0 (identity) */
    is_equal = false;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf, USIZE_C(16), USIZE_C(0), buf, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == true);

    /* Compare index 0 vs index 1 (0,1,2,3 vs 1,2,3,4) -> Not Equal */
    is_equal = true;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf, USIZE_C(16), USIZE_C(0), buf, USIZE_C(16), USIZE_C(1), USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == false);

    printf("PASSED\n");
}


void
ArbitraryByteCounts(void)
{
    u8   buf1[20];
    u8   buf2[20];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "ArbitraryByteCounts -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(20), U8_C(0x00));
    kdi_FillSeq_u8(buf2, USIZE_C(20), U8_C(0x00));

    /* Odd byte count (1 byte) */
    is_equal = false;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(20), USIZE_C(5), buf2, USIZE_C(20), USIZE_C(5), USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == true);

    /* Odd byte count (3 bytes) */
    is_equal = false;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(20), USIZE_C(2), buf2, USIZE_C(20), USIZE_C(2), USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == true);

    /* Odd byte count (5 bytes) */
    is_equal = false;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(20), USIZE_C(10), buf2, USIZE_C(20), USIZE_C(10), USIZE_C(5));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == true);

    /* Odd byte count (7 bytes) */
    is_equal = false;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(20), USIZE_C(0), buf2, USIZE_C(20), USIZE_C(0), USIZE_C(7));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == true);

    /* Non-power-of-2 count (6 bytes) */
    is_equal = false;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(20), USIZE_C(3), buf2, USIZE_C(20), USIZE_C(3), USIZE_C(6));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == true);

    /* Non-power-of-2 count (9 bytes) */
    is_equal = false;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(20), USIZE_C(1), buf2, USIZE_C(20), USIZE_C(1), USIZE_C(9));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == true);

    /* Non-power-of-2 count (11 bytes) */
    is_equal = false;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(20), USIZE_C(7), buf2, USIZE_C(20), USIZE_C(7), USIZE_C(11));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == true);

    /* Odd count with mismatch (3 bytes, different at byte 1) */
    buf2[8] = U8_C(0xFF);
    is_equal = true;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(20), USIZE_C(7), buf2, USIZE_C(20), USIZE_C(7), USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == false);

    /* Restore buf2 */
    buf2[8] = U8_C(0x08);

    /* Non-power-of-2 count with mismatch (6 bytes, different at byte 3) */
    buf2[5] = U8_C(0xFF);
    is_equal = true;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(20), USIZE_C(2), buf2, USIZE_C(20), USIZE_C(2), USIZE_C(6));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == false);

    printf("PASSED\n");
}


void
SingleByte(void)
{
    u8   buf1[8];
    u8   buf2[8];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "SingleByte -> ");

    kdi_FillSeq_u8(buf1, USIZE_C(8), U8_C(0x00));
    kdi_FillSeq_u8(buf2, USIZE_C(8), U8_C(0x00));

    /* Compare single byte at index 3 - equal */
    is_equal = false;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(8), USIZE_C(3), buf2, USIZE_C(8), USIZE_C(3), USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == true);

    /* Compare single byte at different indices - different values */
    is_equal = true;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(8), USIZE_C(2), buf2, USIZE_C(8), USIZE_C(5), USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == false);

    /* Modify and compare single byte */
    buf2[4] = U8_C(0xFF);
    is_equal = true;
    status  = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(8), USIZE_C(4), buf2, USIZE_C(8), USIZE_C(4), USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == false);

    printf("PASSED\n");
}


void
AllZeros(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "AllZeros -> ");

    /* Both buffers all zeros */
    kdi_Fill_u8(buf1, USIZE_C(16), U8_C(0x00));
    kdi_Fill_u8(buf2, USIZE_C(16), U8_C(0x00));

    /* Compare entire range */
    is_equal = false;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == true);

    /* Compare sub-range */
    is_equal = false;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(16), USIZE_C(5), buf2, USIZE_C(16), USIZE_C(8), USIZE_C(7));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == true);

    printf("PASSED\n");
}


void
AllOnes(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "AllOnes -> ");

    /* Both buffers all 0xFF */
    kdi_Fill_u8(buf1, USIZE_C(16), U8_C(0xFF));
    kdi_Fill_u8(buf2, USIZE_C(16), U8_C(0xFF));

    /* Compare entire range */
    is_equal = false;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(16), USIZE_C(0), buf2, USIZE_C(16), USIZE_C(0), USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == true);

    /* Compare sub-range */
    is_equal = false;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(16), USIZE_C(3), buf2, USIZE_C(16), USIZE_C(9), USIZE_C(5));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == true);

    printf("PASSED\n");
}


void
U16_Equal(void)
{
    u16  buf1[8];
    u16  buf2[8];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "U16_Equal -> ");

    buf1[0] = U16_C(0x1111);
    buf1[1] = U16_C(0x2222);
    buf1[2] = U16_C(0x3333);
    buf1[3] = U16_C(0x4444);
    buf1[4] = U16_C(0x5555);
    buf1[5] = U16_C(0x6666);
    buf1[6] = U16_C(0x7777);
    buf1[7] = U16_C(0x8888);

    buf2[0] = U16_C(0x1111);
    buf2[1] = U16_C(0x2222);
    buf2[2] = U16_C(0x3333);
    buf2[3] = U16_C(0x4444);
    buf2[4] = U16_C(0x5555);
    buf2[5] = U16_C(0x6666);
    buf2[6] = U16_C(0x7777);
    buf2[7] = U16_C(0x8888);

    /* Compare 3 u16 elements (6 bytes) starting at byte index 4 */
    is_equal = false;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, sizeof(buf1), USIZE_C(4), buf2, sizeof(buf2), USIZE_C(4), USIZE_C(6));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == true);

    printf("PASSED\n");
}


void
U16_Different(void)
{
    u16  buf1[8];
    u16  buf2[8];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "U16_Different -> ");

    buf1[0] = U16_C(0x1111);
    buf1[1] = U16_C(0x2222);
    buf1[2] = U16_C(0x3333);
    buf1[3] = U16_C(0x4444);
    buf1[4] = U16_C(0x5555);
    buf1[5] = U16_C(0x6666);
    buf1[6] = U16_C(0x7777);
    buf1[7] = U16_C(0x8888);

    buf2[0] = U16_C(0x1111);
    buf2[1] = U16_C(0x2222);
    buf2[2] = U16_C(0x3333);
    buf2[3] = U16_C(0x4445);
    buf2[4] = U16_C(0x5555);
    buf2[5] = U16_C(0x6666);
    buf2[6] = U16_C(0x7777);
    buf2[7] = U16_C(0x8888);

    /* Compare range that includes the different value */
    is_equal = true;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, sizeof(buf1), USIZE_C(4), buf2, sizeof(buf2), USIZE_C(4), USIZE_C(8));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == false);

    printf("PASSED\n");
}


void
U32_Equal(void)
{
    u32  buf1[6];
    u32  buf2[6];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "U32_Equal -> ");

    buf1[0] = U32_C(0x12345678);
    buf1[1] = U32_C(0xABCDEF01);
    buf1[2] = U32_C(0xDEADBEEF);
    buf1[3] = U32_C(0xCAFEBABE);
    buf1[4] = U32_C(0xFEEDFACE);
    buf1[5] = U32_C(0xBADDCAFE);

    buf2[0] = U32_C(0x12345678);
    buf2[1] = U32_C(0xABCDEF01);
    buf2[2] = U32_C(0xDEADBEEF);
    buf2[3] = U32_C(0xCAFEBABE);
    buf2[4] = U32_C(0xFEEDFACE);
    buf2[5] = U32_C(0xBADDCAFE);

    /* Compare 2 u32 elements (8 bytes) starting at byte index 8 */
    is_equal = false;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, sizeof(buf1), USIZE_C(8), buf2, sizeof(buf2), USIZE_C(8), USIZE_C(8));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == true);

    printf("PASSED\n");
}


void
U32_Different(void)
{
    u32  buf1[6];
    u32  buf2[6];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "U32_Different -> ");

    buf1[0] = U32_C(0x12345678);
    buf1[1] = U32_C(0xABCDEF01);
    buf1[2] = U32_C(0xDEADBEEF);
    buf1[3] = U32_C(0xCAFEBABE);
    buf1[4] = U32_C(0xFEEDFACE);
    buf1[5] = U32_C(0xBADDCAFE);

    buf2[0] = U32_C(0x12345678);
    buf2[1] = U32_C(0xABCDEF02);
    buf2[2] = U32_C(0xDEADBEEF);
    buf2[3] = U32_C(0xCAFEBABE);
    buf2[4] = U32_C(0xFEEDFACE);
    buf2[5] = U32_C(0xBADDCAFE);

    /* Compare range that includes the different value */
    is_equal = true;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, sizeof(buf1), USIZE_C(0), buf2, sizeof(buf2), USIZE_C(0), USIZE_C(12));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == false);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_Equal(void)
{
    u64  buf1[5];
    u64  buf2[5];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "U64_Equal -> ");

    buf1[0] = U64_C(0x123456789ABCDEF0);
    buf1[1] = U64_C(0xFEDCBA9876543210);
    buf1[2] = U64_C(0xDEADBEEFCAFEBABE);
    buf1[3] = U64_C(0xFEEDFACEBADDCAFE);
    buf1[4] = U64_C(0x0123456789ABCDEF);

    buf2[0] = U64_C(0x123456789ABCDEF0);
    buf2[1] = U64_C(0xFEDCBA9876543210);
    buf2[2] = U64_C(0xDEADBEEFCAFEBABE);
    buf2[3] = U64_C(0xFEEDFACEBADDCAFE);
    buf2[4] = U64_C(0x0123456789ABCDEF);

    /* Compare 2 u64 elements (16 bytes) starting at byte index 16 */
    is_equal = false;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, sizeof(buf1), USIZE_C(16), buf2, sizeof(buf2), USIZE_C(16), USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == true);

    printf("PASSED\n");
}


void
U64_Different(void)
{
    u64  buf1[5];
    u64  buf2[5];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "U64_Different -> ");

    buf1[0] = U64_C(0x123456789ABCDEF0);
    buf1[1] = U64_C(0xFEDCBA9876543210);
    buf1[2] = U64_C(0xDEADBEEFCAFEBABE);
    buf1[3] = U64_C(0xFEEDFACEBADDCAFE);
    buf1[4] = U64_C(0x0123456789ABCDEF);

    buf2[0] = U64_C(0x123456789ABCDEF0);
    buf2[1] = U64_C(0xFEDCBA9876543211);
    buf2[2] = U64_C(0xDEADBEEFCAFEBABE);
    buf2[3] = U64_C(0xFEEDFACEBADDCAFE);
    buf2[4] = U64_C(0x0123456789ABCDEF);

    /* Compare range that includes the different value */
    is_equal = true;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, sizeof(buf1), USIZE_C(8), buf2, sizeof(buf2), USIZE_C(8), USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == false);

    printf("PASSED\n");
}
#endif


typedef struct kdi_TestStruct
{
    u32 a;
    u16 b;
    u8  c;
    u8  d;
} kdi_TestStruct;


void
Struct_Equal(void)
{
    kdi_TestStruct s1, s2;
    bool           is_equal;
    bool           status;

    printf(LOG_PREFIX_CSTR "Struct_Equal -> ");

    s1.a = U32_C(100);
    s1.b = U16_C(200);
    s1.c = U8_C(50);
    s1.d = U8_C(75);

    s2.a = U32_C(100);
    s2.b = U16_C(200);
    s2.c = U8_C(50);
    s2.d = U8_C(75);

    /* Compare entire struct */
    is_equal = false;
    status   = kdGenMemOpsIsEqualBound(&is_equal, &s1, sizeof(kdi_TestStruct), USIZE_C(0), &s2, sizeof(kdi_TestStruct), USIZE_C(0), sizeof(kdi_TestStruct));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == true);

    printf("PASSED\n");
}


void
Struct_Different(void)
{
    kdi_TestStruct s1, s2;
    bool           is_equal;
    bool           status;

    printf(LOG_PREFIX_CSTR "Struct_Different -> ");

    s1.a = U32_C(100);
    s1.b = U16_C(200);
    s1.c = U8_C(50);
    s1.d = U8_C(75);

    s2.a = U32_C(100);
    s2.b = U16_C(200);
    s2.c = U8_C(51);
    s2.d = U8_C(75);

    /* Compare entire struct */
    is_equal = true;
    status   = kdGenMemOpsIsEqualBound(&is_equal, &s1, sizeof(kdi_TestStruct), USIZE_C(0), &s2, sizeof(kdi_TestStruct), USIZE_C(0), sizeof(kdi_TestStruct));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == false);

    printf("PASSED\n");
}


void
LargeBuffer_Equal(void)
{
    u8    buf1[256];
    u8    buf2[256];
    bool  is_equal;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffer_Equal -> ");

    /* Fill with same pattern */
    for (i = 0; i < 256; ++i)
    {
        buf1[i] = (u8)i;
        buf2[i] = (u8)i;
    }

    /* Compare large range (200 bytes starting at index 50) */
    is_equal = false;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(256), USIZE_C(50), buf2, USIZE_C(256), USIZE_C(50), USIZE_C(200));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == true);

    printf("PASSED\n");
}


void
LargeBuffer_Different(void)
{
    u8    buf1[256];
    u8    buf2[256];
    bool  is_equal;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffer_Different -> ");

    /* Fill with same pattern */
    for (i = 0; i < 256; ++i)
    {
        buf1[i] = (u8)i;
        buf2[i] = (u8)i;
    }

    /* Change one byte in the comparison range */
    buf2[100] = U8_C(0xFF);

    /* Compare range that includes the changed byte */
    is_equal = true;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(256), USIZE_C(50), buf2, USIZE_C(256), USIZE_C(50), USIZE_C(100));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == false);

    printf("PASSED\n");
}


void
DifferentAtStart(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "DifferentAtStart -> ");

    /* Init: same except first byte of range */
    kdi_FillSeq_u8(buf1, USIZE_C(16), U8_C(0x00));
    kdi_FillSeq_u8(buf2, USIZE_C(16), U8_C(0x00));
    buf2[5] = U8_C(0xFF);

    /* Compare range starting at index 5 */
    is_equal = true;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(16), USIZE_C(5), buf2, USIZE_C(16), USIZE_C(5), USIZE_C(8));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == false);

    printf("PASSED\n");
}


void
DifferentAtEnd(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "DifferentAtEnd -> ");

    /* Init: same except last byte of range */
    kdi_FillSeq_u8(buf1, USIZE_C(16), U8_C(0x00));
    kdi_FillSeq_u8(buf2, USIZE_C(16), U8_C(0x00));
    buf2[11] = U8_C(0xFF);

    /* Compare range from index 4 to 11 (8 bytes) */
    is_equal = true;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(16), USIZE_C(4), buf2, USIZE_C(16), USIZE_C(4), USIZE_C(8));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == false);

    printf("PASSED\n");
}


void
DifferentAtMiddle(void)
{
    u8   buf1[16];
    u8   buf2[16];
    bool is_equal;
    bool status;

    printf(LOG_PREFIX_CSTR "DifferentAtMiddle -> ");

    /* Init: same except middle byte of range */
    kdi_FillSeq_u8(buf1, USIZE_C(16), U8_C(0x00));
    kdi_FillSeq_u8(buf2, USIZE_C(16), U8_C(0x00));
    buf2[8] = U8_C(0xFF);

    /* Compare range from index 4 to 11 (8 bytes), difference at middle */
    is_equal = true;
    status   = kdGenMemOpsIsEqualBound(&is_equal, buf1, USIZE_C(16), USIZE_C(4), buf2, USIZE_C(16), USIZE_C(4), USIZE_C(8));
    assert(status == RESULT_SUCCESS);
    assert(is_equal == false);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    CountClamping();
    IndicesOutOfBounds();
    RangesMatch();
    RangesDoNotMatch();
    OverlappingRangesSameBuffer();
    ArbitraryByteCounts();
    SingleByte();
    AllZeros();
    AllOnes();
    U16_Equal();
    U16_Different();
    U32_Equal();
    U32_Different();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_Equal();
    U64_Different();
#endif
    Struct_Equal();
    Struct_Different();
    LargeBuffer_Equal();
    LargeBuffer_Different();
    DifferentAtStart();
    DifferentAtEnd();
    DifferentAtMiddle();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
