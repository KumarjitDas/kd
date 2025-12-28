/**
 * @file kdGenMemOpsFindByteIndexBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindByteIndexBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindByteIndexBound function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8    buf[16];
    usize idx = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* idx pointer is null -> failure */
    status = kdGenMemOpsFindByteIndexBound(null, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure */
    idx    = 55;
    status = kdGenMemOpsFindByteIndexBound(&idx, null, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* begin_idx >= base_sz -> failure */
    idx    = 55;
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(16), USIZE_C(10), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* end_count is zero -> failure */
    idx    = 55;
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(0), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* Valid arguments - found at index 0 */
    idx    = 55;
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    printf("PASSED\n");
}


void
FindNone(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNone -> ");

    /* Init: 0x00 */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Find 0xFF in range [0, 16) - not present */
    idx    = 999;
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
FindFirst(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindFirst -> ");

    /* Init: 0x00 */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Set first byte in range */
    buf[0] = 0xFF;

    /* Find 0xFF in range [0, 16) */
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    printf("PASSED\n");
}


void
FindLast(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindLast -> ");

    /* Init: 0x00 */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Set last byte in range */
    buf[15] = 0xFF;

    /* Find 0xFF in range [0, 16) */
    status  = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(15));

    printf("PASSED\n");
}


void
RangeConstraints(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "RangeConstraints -> ");

    /* Init: 0, 1, 2, ... 15 */
    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0));

    /* Range [4, 10). Begin_idx=4, end_count=6. Indices 4..9. Values 4..9. */

    /* Find value inside range (Index 6, Value 6) */
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(6), U8_C(6));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(6));

    /* Find value at start of range (Index 4, Value 4) */
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(6), U8_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(4));

    /* Find value at end of range - 1 (Index 9, Value 9) */
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(6), U8_C(9));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(9));

    /* Find value immediately before range (Index 3, Value 3) -> Should Fail */
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(6), U8_C(3));
    assert(status == RESULT_FAILURE);

    /* Find value immediately after range (Index 10, Value 10) -> Should Fail */
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(6), U8_C(10));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
EndValueClamping(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "EndValueClamping -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));
    buf[15] = 0xFF;

    /* Requesting 100 bytes starting at 0. Clamps to 16. Range [0, 16). */
    status  = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(100), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(15));

    printf("PASSED\n");
}


void
FindMultiple(void)
{
    u8    buf[16];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindMultiple -> ");

    /* Init: 0x00 */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Set 0xFF at indices 2, 5, 8 */
    buf[2] = 0xFF;
    buf[5] = 0xFF;
    buf[8] = 0xFF;

    /* Range [3, 9). Begin_idx=3, end_count=6. Covers indices 3..8. */
    /* Should find FIRST occurrence in range at index 5. */
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(3), USIZE_C(6), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(5));

    printf("PASSED\n");
}


void
AlternatingPattern(void)
{
    u8    buf[32];
    usize idx;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "AlternatingPattern -> ");

    /* Alternating 0xAA, 0x55 */
    for (i = 0; i < 32; ++i)
    {
        buf[i] = (i & 1) ? 0x55 : 0xAA;
    }

    /* Find 0xAA in range [0, 32). Should return 0 (even index). */
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    /* Find 0x55 in range [0, 32). Should return 1 (odd index). */
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), U8_C(0x55));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(1));

    /* Find 0xAA in range [1, 10). Begin_idx=1, end_count=9. Indices 1..9. */
    /* First 0xAA in range is at index 2. */
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(1), USIZE_C(9), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(2));

    printf("PASSED\n");
}


void
SequentialValues(void)
{
    u8    buf[256];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "SequentialValues -> ");

    /* Init: 0..255 */
    kdi_FillSeq_u8(buf, USIZE_C(256), U8_C(0x00));

    /* Find value 50 in range [0, 256). Should be at index 50. */
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(256), USIZE_C(0), USIZE_C(256), U8_C(50));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(50));

    /* Find value 50 in range [0, 50). Should fail (50 is at boundary, excluded). */
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(256), USIZE_C(0), USIZE_C(50), U8_C(50));
    assert(status == RESULT_FAILURE);

    /* Find value 50 in range [50, 206). Begin_idx=50, end_count=156. Should find at 50. */
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(256), USIZE_C(50), USIZE_C(156), U8_C(50));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(50));

    printf("PASSED\n");
}


void
SmallRange(void)
{
    u8    buf[32];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "SmallRange -> ");

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x77));
    buf[10] = 0x88;

    /* Single byte range [10, 11). Begin_idx=10, end_count=1. */
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(10), USIZE_C(1), U8_C(0x88));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(10));

    /* Single byte range [9, 10). Begin_idx=9, end_count=1. */
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(9), USIZE_C(1), U8_C(0x88));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    u8    buf[1024];
    usize idx;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    /* Init with pattern */
    for (i = 0; i < 1024; ++i)
    {
        buf[i] = (u8)(i % 256);
    }

    /* Find value 100 in range [0, 1024). First occurrence at index 100. */
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(1024), USIZE_C(0), USIZE_C(1024), U8_C(100));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(100));

    /* Find value 100 in range [200, 624). Begin_idx=200, end_count=424. */
    /* Next occurrence is at 356 (100 + 256). */
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(1024), USIZE_C(200), USIZE_C(424), U8_C(100));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(356));

    printf("PASSED\n");
}


void
U32_Buffer(void)
{
    u32   buf[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_Buffer -> ");

    /* Init: 0x00000000 */
    kdi_Fill_u8((u8 *)buf, sizeof(buf), 0);

    /* Set bytes at index 3 and 12 to 0xAA */
    ((u8 *)buf)[3]  = 0xAA;
    ((u8 *)buf)[12] = 0xAA;

    /* Search Range [4, 16). Begin_idx=4, end_count=12. Skips index 3. Should find 12. */
    status          = kdGenMemOpsFindByteIndexBound(&idx, buf, sizeof(buf), USIZE_C(4), USIZE_C(12), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(12));

    /* Search Range [0, 4). Begin_idx=0, end_count=4. Should find 3. */
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, sizeof(buf), USIZE_C(0), USIZE_C(4), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(3));

    printf("PASSED\n");
}


void
AllSameValue(void)
{
    u8    buf[32];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "AllSameValue -> ");

    /* All bytes are 0x77 */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x77));

    /* Find 0x77 in range [0, 32). Should return index 0 (first). */
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), U8_C(0x77));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    /* Find 0x77 in range [10, 20). Begin_idx=10, end_count=10. Should return 10. */
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(10), USIZE_C(10), U8_C(0x77));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(10));

    printf("PASSED\n");
}


void
SparseMatches(void)
{
    u8    buf[100];
    usize idx;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "SparseMatches -> ");

    /* Fill with 0x00 */
    kdi_Fill_u8(buf, USIZE_C(100), U8_C(0x00));

    /* Set every 10th byte to 0xFF */
    for (i = 0; i < 100; i += 10)
    {
        buf[i] = 0xFF;
    }

    /* Find 0xFF in range [0, 100). Should return index 0. */
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(100), USIZE_C(0), USIZE_C(100), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    /* Find 0xFF in range [5, 95). Begin_idx=5, end_count=90. First in range is 10. */
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(100), USIZE_C(5), USIZE_C(90), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(10));

    printf("PASSED\n");
}


void
OddSizes(void)
{
    u8    buf[33];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "OddSizes -> ");

    /* Odd size: 33 bytes */
    kdi_Fill_u8(buf, USIZE_C(33), U8_C(0x77));
    buf[17] = 0x88;

    /* Find 0x88 in range [0, 33). */
    status  = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(33), USIZE_C(0), USIZE_C(33), U8_C(0x88));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(17));

    /* Find 0x88 in range [0, 17). Begin_idx=0, end_count=17. Should fail. */
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(33), USIZE_C(0), USIZE_C(17), U8_C(0x88));
    assert(status == RESULT_FAILURE);

    /* Find 0x88 in range [17, 20). Begin_idx=17, end_count=3. Should find at 17. */
    status = kdGenMemOpsFindByteIndexBound(&idx, buf, USIZE_C(33), USIZE_C(17), USIZE_C(3), U8_C(0x88));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(17));

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    FindNone();
    FindFirst();
    FindLast();
    RangeConstraints();
    EndValueClamping();
    FindMultiple();
    AlternatingPattern();
    SequentialValues();
    SmallRange();
    LargeBuffer();
    U32_Buffer();
    AllSameValue();
    SparseMatches();
    OddSizes();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}