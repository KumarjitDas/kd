/**
 * @file kdGenMemOpsFindNotByteIndexBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindNotByteIndexBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindNotByteIndexBound function test"
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
    status = kdGenMemOpsFindNotByteIndexBound(null, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure */
    idx    = 55;
    status = kdGenMemOpsFindNotByteIndexBound(&idx, null, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* begin_idx >= base_sz -> failure */
    idx    = 55;
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(16), USIZE_C(10), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* end_count is zero -> failure */
    idx    = 55;
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(0), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* Valid arguments - searching for NOT 0xFF in 0x00 buffer -> found at index 0 */
    idx    = 55;
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0xFF));
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

    /* Find NOT 0x00 in range [0, 16) - all are 0x00, so not present */
    idx    = 999;
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0x00));

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

    /* Set first byte in range to 0xFF */
    buf[0] = 0xFF;

    /* Find NOT 0x00 in range [0, 16). Index 0 is 0xFF (!= 0x00). */
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0x00));

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

    /* Set last byte in range to 0xFF */
    buf[15] = 0xFF;

    /* Find NOT 0x00 in range [0, 16). Indices 0..14 are 0x00. Index 15 is 0xFF. */
    status  = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0x00));

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

    /* Find NOT 4 inside range.
     * Index 4 has value 4 (== 4). Skip.
     * Index 5 has value 5 (!= 4). Match at 5. */
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(6), U8_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(5));

    /* Find NOT 6 inside range.
     * Index 4 has value 4 (!= 6). Match at 4. */
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(6), U8_C(6));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(4));

    /* Find NOT 3 inside range.
     * Range starts at 4. Value at 4 is 4 (!= 3). Match at 4. */
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(6), U8_C(3));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(4));
    
    /* To test failure in range, we need a range where all values equal the item. */
    /* Let's construct a buffer with a constant region. */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));
    /* Range [4, 10) are all 0xAA. Find NOT 0xAA should fail. */
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(6), U8_C(0xAA));
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

    /* Requesting 100 bytes starting at 0. Clamps to 16. Range [0, 16).
     * Find NOT 0x00. 0..14 are 0x00. 15 is 0xFF. Match 15. */
    status  = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(100), U8_C(0x00));

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

    /* Init: 0xFF */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xFF));

    /* Set 0x00 at indices 2, 5, 8 */
    buf[2] = 0x00;
    buf[5] = 0x00;
    buf[8] = 0x00;

    /* Range [3, 9). Begin_idx=3, end_count=6. Covers indices 3..8.
     * Values at 3,4 are 0xFF. Value at 5 is 0x00.
     * Find NOT 0xFF.
     * 3: FF == FF.
     * 4: FF == FF.
     * 5: 00 != FF. Match 5. */
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(16), USIZE_C(3), USIZE_C(6), U8_C(0xFF));

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
    /* 0:AA, 1:55, 2:AA, 3:55 ... */
    for (i = 0; i < 32; ++i)
    {
        buf[i] = (i & 1) ? 0x55 : 0xAA;
    }

    /* Find NOT 0xAA in range [0, 32).
     * 0: AA == AA.
     * 1: 55 != AA. Match 1 (odd index). */
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(1));

    /* Find NOT 0x55 in range [0, 32).
     * 0: AA != 55. Match 0 (even index). */
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), U8_C(0x55));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    /* Find NOT 0xAA in range [1, 10).
     * 1: 55 != AA. Match 1. */
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(1), USIZE_C(9), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(1));
    
    /* Find NOT 0xAA in range [2, 10).
     * 2: AA == AA.
     * 3: 55 != AA. Match 3. */
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(2), USIZE_C(8), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(3));

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

    /* Find NOT 0 in range [0, 256).
     * 0: 0 == 0.
     * 1: 1 != 0. Match 1. */
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(256), USIZE_C(0), USIZE_C(256), U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(1));

    /* Find NOT 50 in range [50, 206).
     * 50: 50 == 50.
     * 51: 51 != 50. Match 51. */
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(256), USIZE_C(50), USIZE_C(156), U8_C(50));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(51));

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

    /* Single byte range [10, 11). Value is 0x88.
     * Find NOT 0x77.
     * 10: 88 != 77. Match 10. */
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(10), USIZE_C(1), U8_C(0x77));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(10));

    /* Single byte range [9, 10). Value is 0x77.
     * Find NOT 0x77.
     * 9: 77 == 77. Fail. */
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(9), USIZE_C(1), U8_C(0x77));
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

    /* Init with pattern 0..255 repeated */
    for (i = 0; i < 1024; ++i)
    {
        buf[i] = (u8)(i % 256);
    }

    /* Find NOT 0 in range [0, 1024).
     * 0: 0 == 0.
     * 1: 1 != 0. Match 1. */
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(1024), USIZE_C(0), USIZE_C(1024), U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(1));

    /* Find NOT 100 in range [200, 624).
     * Index 200 value is 200 (200%256). 200 != 100. Match 200. */
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(1024), USIZE_C(200), USIZE_C(424), U8_C(100));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(200));

    /* Check where match is NOT immediate.
     * At index 356 (100 + 256), value is 100.
     * Search range [356, ...). Find NOT 100.
     * 356: 100 == 100.
     * 357: 101 != 100. Match 357. */
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(1024), USIZE_C(356), USIZE_C(100), U8_C(100));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(357));

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

    /* Search Range [4, 16). Find NOT 0x00.
     * 4..11 are 0x00.
     * 12 is 0xAA. Match 12. */
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, sizeof(buf), USIZE_C(4), USIZE_C(12), U8_C(0x00));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(12));

    /* Search Range [0, 4). Find NOT 0x00.
     * 0..2 are 0x00.
     * 3 is 0xAA. Match 3. */
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, sizeof(buf), USIZE_C(0), USIZE_C(4), U8_C(0x00));
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

    /* Find NOT 0x77 in range [0, 32). Should fail. */
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), U8_C(0x77));
    assert(status == RESULT_FAILURE);

    /* Find NOT 0x88 in range [0, 32).
     * 0: 77 != 88. Match 0. */
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), U8_C(0x88));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

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

    /* Find NOT 0x00.
     * 0: FF != 00. Match 0. */
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(100), USIZE_C(0), USIZE_C(100), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    /* Find NOT 0x00 in range [5, 95).
     * 5..9 are 00.
     * 10 is FF. Match 10. */
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(100), USIZE_C(5), USIZE_C(90), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(10));

    /* Find NOT 0xFF in range [0, 100).
     * 0: FF == FF.
     * 1: 00 != FF. Match 1. */
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(100), USIZE_C(0), USIZE_C(100), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(1));

    printf("PASSED\n");
}


void
OddSizes(void)
{
    u8    buf[33];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "OddSizes -> ");

    /* Odd size: 33 bytes. Fill 0x77. */
    kdi_Fill_u8(buf, USIZE_C(33), U8_C(0x77));
    /* Set 17 to 0x88 */
    buf[17] = 0x88;

    /* Find NOT 0x77 in range [0, 33).
     * 17 is 88 != 77. Match 17. */
    status  = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(33), USIZE_C(0), USIZE_C(33), U8_C(0x77));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(17));

    /* Find NOT 0x77 in range [0, 17). All are 77. Fail. */
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(33), USIZE_C(0), USIZE_C(17), U8_C(0x77));
    assert(status == RESULT_FAILURE);

    /* Find NOT 0x77 in range [17, 20).
     * 17: 88 != 77. Match 17. */
    status = kdGenMemOpsFindNotByteIndexBound(&idx, buf, USIZE_C(33), USIZE_C(17), USIZE_C(3), U8_C(0x77));
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