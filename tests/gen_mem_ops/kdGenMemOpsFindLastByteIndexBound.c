/**
 * @file kdGenMemOpsFindLastByteIndexRange.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindLastByteIndexRange function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindLastByteIndexRange function test"
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


static void
kdi_FillVal(u8 *dst, usize sz, u8 val)
{
    usize i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        dst[i] = val;
    }
}


void
BasicArguments(void)
{
    u8    buf[16];
    usize idx = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* idx pointer is null -> failure */
    status = GenMemOpsFindLastByteIndexRange(null, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindLastByteIndexRange(&idx, null, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* sz is zero -> failure */
    status = GenMemOpsFindLastByteIndexRange(&idx, buf, USIZE_C(0), USIZE_C(0), USIZE_C(0), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* begin_idx > end -> failure (invalid range) */
    status = GenMemOpsFindLastByteIndexRange(&idx, buf, USIZE_C(16), USIZE_C(5), USIZE_C(4), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* end > base_sz -> failure (out of bounds) */
    status = GenMemOpsFindLastByteIndexRange(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(17), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* begin_idx == end -> failure (empty range) */
    status = GenMemOpsFindLastByteIndexRange(&idx, buf, USIZE_C(16), USIZE_C(5), USIZE_C(5), U8_C(0));
    assert(status == RESULT_FAILURE);

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
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0));

    /* Range [4, 10). Indices 4..9. Values 4..9. */

    /* 1. Find value inside range (Index 6, Value 6) */
    status = GenMemOpsFindLastByteIndexRange(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(10), U8_C(6));
    assert(status == RESULT_SUCCESS);
    assert(idx == 6);

    /* 2. Find value at start of range (Index 4, Value 4) */
    status = GenMemOpsFindLastByteIndexRange(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(10), U8_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == 4);

    /* 3. Find value at end of range - 1 (Index 9, Value 9) */
    status = GenMemOpsFindLastByteIndexRange(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(10), U8_C(9));
    assert(status == RESULT_SUCCESS);
    assert(idx == 9);

    /* 4. Find value immediately before range (Index 3, Value 3) -> Fail */
    status = GenMemOpsFindLastByteIndexRange(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(10), U8_C(3));
    assert(status == RESULT_FAILURE);

    /* 5. Find value immediately after range (Index 10, Value 10) -> Fail */
    status = GenMemOpsFindLastByteIndexRange(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(10), U8_C(10));
    assert(status == RESULT_FAILURE);

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
    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Set 0xFF at indices 2, 5, 8 */
    buf[2] = 0xFF;
    buf[5] = 0xFF;
    buf[8] = 0xFF;

    /* Range [0, 16). Should find last one at 8. */
    status = GenMemOpsFindLastByteIndexRange(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(idx == 8);

    /* Range [0, 8). Includes 2, 5. Excludes 8. Should find 5. */
    status = GenMemOpsFindLastByteIndexRange(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(8), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(idx == 5);

    /* Range [0, 3). Includes 2. Should find 2. */
    status = GenMemOpsFindLastByteIndexRange(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(3), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(idx == 2);

    printf("PASSED\n");
}


void
U32_FindLastByteRange(void)
{
    u32   buf[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_FindLastByteRange -> ");

    /* Init: 0 */
    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    /* Set bytes at index 3 and 12 to 0xAA */
    ((u8 *)buf)[3]  = 0xAA; /* In u32[0] */
    ((u8 *)buf)[12] = 0xAA; /* In u32[3] */

    /* Range [0, 16). Should find 12. */
    status          = GenMemOpsFindLastByteIndexRange(&idx, buf, sizeof(buf), USIZE_C(0), sizeof(buf), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == 12);

    /* Range [0, 12). Excludes 12. Should find 3. */
    status = GenMemOpsFindLastByteIndexRange(&idx, buf, sizeof(buf), USIZE_C(0), USIZE_C(12), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == 3);

    printf("PASSED\n");
}


void
LargeArray_FindLastRange(void)
{
    u8    buf[100];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "LargeArray_FindLastRange -> ");

    /* Init: 0..99 */
    kdi_FillSeq(buf, USIZE_C(100), U8_C(0));

    /* Duplicate value 50 at index 90 */
    buf[90] = 50;

    /* Range [0, 100). 50 exists at 50 and 90. Should find 90. */
    status  = GenMemOpsFindLastByteIndexRange(&idx, buf, USIZE_C(100), USIZE_C(0), USIZE_C(100), U8_C(50));
    assert(status == RESULT_SUCCESS);
    assert(idx == 90);

    /* Range [0, 90). Excludes 90. Should find 50. */
    status = GenMemOpsFindLastByteIndexRange(&idx, buf, USIZE_C(100), USIZE_C(0), USIZE_C(90), U8_C(50));
    assert(status == RESULT_SUCCESS);
    assert(idx == 50);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    RangeConstraints();
    FindMultiple();
    U32_FindLastByteRange();
    LargeArray_FindLastRange();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
