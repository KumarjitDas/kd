/**
 * @file kdGenMemOpsFindByteIndexRange.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindByteIndexRange function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindByteIndexRange function test"
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
    status = GenMemOpsFindByteIndexRange(null, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindByteIndexRange(&idx, null, USIZE_C(16), USIZE_C(0), USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* sz is zero -> failure */
    status = GenMemOpsFindByteIndexRange(&idx, buf, USIZE_C(0), USIZE_C(0), USIZE_C(0), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* begin_idx > end -> failure (invalid range) */
    status = GenMemOpsFindByteIndexRange(&idx, buf, USIZE_C(16), USIZE_C(5), USIZE_C(4), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* end > base_sz -> failure (out of bounds) */
    status = GenMemOpsFindByteIndexRange(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(17), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* begin_idx == end -> failure (empty range, cannot find anything) */
    status = GenMemOpsFindByteIndexRange(&idx, buf, USIZE_C(16), USIZE_C(5), USIZE_C(5), U8_C(0));
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
    status = GenMemOpsFindByteIndexRange(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(10), U8_C(6));
    assert(status == RESULT_SUCCESS);
    assert(idx == 6);

    /* 2. Find value at start of range (Index 4, Value 4) */
    status = GenMemOpsFindByteIndexRange(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(10), U8_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == 4);

    /* 3. Find value at end of range - 1 (Index 9, Value 9) */
    status = GenMemOpsFindByteIndexRange(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(10), U8_C(9));
    assert(status == RESULT_SUCCESS);
    assert(idx == 9);

    /* 4. Find value immediately before range (Index 3, Value 3) -> Should Fail */
    status = GenMemOpsFindByteIndexRange(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(10), U8_C(3));
    assert(status == RESULT_FAILURE);

    /* 5. Find value immediately after range (Index 10, Value 10) -> Should Fail */
    status = GenMemOpsFindByteIndexRange(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(10), U8_C(10));
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

    /* Range [3, 9). Covers indices 5 and 8. Should find 5. */
    status = GenMemOpsFindByteIndexRange(&idx, buf, USIZE_C(16), USIZE_C(3), USIZE_C(9), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(idx == 5);

    printf("PASSED\n");
}


void
U32_FindByteRange(void)
{
    u32   buf[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_FindByteRange -> ");

    /* Init: 0 */
    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    /* Set bytes at index 3 and 12 to 0xAA */
    ((u8 *)buf)[3]  = 0xAA; /* In u32[0] */
    ((u8 *)buf)[12] = 0xAA; /* In u32[3] */

    /* Search Range [4, 16). Skips index 3. Should find 12. */
    status          = GenMemOpsFindByteIndexRange(&idx, buf, sizeof(buf), USIZE_C(4), sizeof(buf), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(idx == 12);

    /* Search Range [0, 4). Should find 3. */
    status = GenMemOpsFindByteIndexRange(&idx, buf, sizeof(buf), USIZE_C(0), USIZE_C(4), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(idx == 3);

    printf("PASSED\n");
}


void
LargeArray_FindRange(void)
{
    u8    buf[100];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "LargeArray_FindRange -> ");

    /* Init: 0..99 */
    kdi_FillSeq(buf, USIZE_C(100), U8_C(0));

    /* Search for 50 in range [0, 50). Value 50 is at index 50 (excluded). */
    status = GenMemOpsFindByteIndexRange(&idx, buf, USIZE_C(100), USIZE_C(0), USIZE_C(50), U8_C(50));
    assert(status == RESULT_FAILURE);

    /* Search for 50 in range [0, 51). */
    status = GenMemOpsFindByteIndexRange(&idx, buf, USIZE_C(100), USIZE_C(0), USIZE_C(51), U8_C(50));
    assert(status == RESULT_SUCCESS);
    assert(idx == 50);

    /* Search for 50 in range [50, 100). */
    status = GenMemOpsFindByteIndexRange(&idx, buf, USIZE_C(100), USIZE_C(50), USIZE_C(100), U8_C(50));
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
    U32_FindByteRange();
    LargeArray_FindRange();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
