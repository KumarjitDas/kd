/**
 * @file kdGenMemOpsFindLastBlockIndexRange.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindLastBlockIndexRange function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindLastBlockIndexRange function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


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
    u8    blk[4];
    usize idx = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* idx pointer is null -> failure */
    status = GenMemOpsFindLastBlockIndexRange(null, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindLastBlockIndexRange(&idx, null, USIZE_C(16), USIZE_C(0), USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    status = GenMemOpsFindLastBlockIndexRange(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr_sz is zero -> failure */
    status = GenMemOpsFindLastBlockIndexRange(&idx, buf, USIZE_C(0), USIZE_C(0), USIZE_C(0), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = GenMemOpsFindLastBlockIndexRange(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* begin_idx > end -> failure */
    status = GenMemOpsFindLastBlockIndexRange(&idx, buf, USIZE_C(16), USIZE_C(5), USIZE_C(4), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* end > ptr_sz -> failure */
    status = GenMemOpsFindLastBlockIndexRange(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(17), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
RangeConstraints(void)
{
    u8    buf[16];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "RangeConstraints -> ");

    /* Block Size: 4 */
    /* Blocks at indices: 0, 4, 8, 12 */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Set distinct values */
    kdi_FillVal(buf + 0, 4, 0xAA);  /* Block 0 */
    kdi_FillVal(buf + 4, 4, 0xBB);  /* Block 1 */
    kdi_FillVal(buf + 8, 4, 0xCC);  /* Block 2 */
    kdi_FillVal(buf + 12, 4, 0xDD); /* Block 3 */

    /* Range [4, 12). Includes Block 1 and Block 2. Excludes Block 3. */

    /* 1. Find Block 2 (Last within range) */
    kdi_FillVal(blk, 4, 0xCC);
    status = GenMemOpsFindLastBlockIndexRange(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(12), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == 8);

    /* 2. Find Block 1 (First within range) */
    kdi_FillVal(blk, 4, 0xBB);
    status = GenMemOpsFindLastBlockIndexRange(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(12), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == 4);

    /* 3. Find Block 3 (After/At end of range) -> Fail */
    kdi_FillVal(blk, 4, 0xDD);
    status = GenMemOpsFindLastBlockIndexRange(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(12), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
FindMultiple(void)
{
    u8    buf[16];
    u8    blk[2];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindMultiple -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Target: 0xFF, 0xFF */
    /* Occurrences at: 2, 6, 10 */
    buf[2]  = 0xFF;
    buf[3]  = 0xFF;
    buf[6]  = 0xFF;
    buf[7]  = 0xFF;
    buf[10] = 0xFF;
    buf[11] = 0xFF;

    blk[0]  = 0xFF;
    blk[1]  = 0xFF;

    /* Range [4, 16). Should find 10. */
    status  = GenMemOpsFindLastBlockIndexRange(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(16), blk, USIZE_C(2));
    assert(status == RESULT_SUCCESS);
    assert(idx == 10);

    /* Range [4, 10). Excludes 10. Should find 6. */
    status = GenMemOpsFindLastBlockIndexRange(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(10), blk, USIZE_C(2));
    assert(status == RESULT_SUCCESS);
    assert(idx == 6);

    printf("PASSED\n");
}


void
AlignmentRelativeToStart(void)
{
    u8    buf[10];
    u8    blk[2];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "AlignmentRelativeToStart -> ");

    /* Buffer: 0, 1, 2, 3, 4, 5 */
    buf[0] = 0;
    buf[1] = 1;
    buf[2] = 2;
    buf[3] = 3;
    buf[4] = 4;
    buf[5] = 5;

    /* Block Size 2. Target: 2, 3 */
    blk[0] = 2;
    blk[1] = 3;

    /* Start 0. Blocks: [0,1], [2,3], [4,5]. [2,3] is aligned. */
    status = GenMemOpsFindLastBlockIndexRange(&idx, buf, USIZE_C(10), USIZE_C(0), USIZE_C(6), blk, USIZE_C(2));
    assert(status == RESULT_SUCCESS);
    assert(idx == 2);

    /* Start 1. Blocks: [1,2], [3,4]. [2,3] is unaligned relative to 1. */
    status = GenMemOpsFindLastBlockIndexRange(&idx, buf, USIZE_C(10), USIZE_C(1), USIZE_C(6), blk, USIZE_C(2));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
U16_FindLastBlockRange(void)
{
    u16   buf[6];
    u16   blk[1];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U16_FindLastBlockRange -> ");

    /* Blocks: 100, 200, 100, 300, 100, 400 */
    buf[0] = 100;
    buf[1] = 200;
    buf[2] = 100;
    buf[3] = 300;
    buf[4] = 100;
    buf[5] = 400;

    /* Search 100 */
    blk[0] = 100;

    /* Range [0, 6*sz) -> Full range. Should find last 100 at Index 4. */
    status = GenMemOpsFindLastBlockIndexRange(&idx, buf, sizeof(buf), 0, sizeof(buf), blk, sizeof(u16));
    assert(status == RESULT_SUCCESS);
    assert(idx == 4 * sizeof(u16));

    /* Range [0, 4*sz). Excludes Index 4. Should find 100 at Index 2. */
    status = GenMemOpsFindLastBlockIndexRange(&idx, buf, sizeof(buf), 0, 4 * sizeof(u16), blk, sizeof(u16));
    assert(status == RESULT_SUCCESS);
    assert(idx == 2 * sizeof(u16));

    printf("PASSED\n");
}


void
U32_FindLastBlockRange(void)
{
    u32   buf[5];
    u32   blk[1];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_FindLastBlockRange -> ");

    /* Blocks: 10, 20, 10, 30, 40 */
    buf[0] = 10;
    buf[1] = 20;
    buf[2] = 10;
    buf[3] = 30;
    buf[4] = 40;

    /* Search 10 */
    blk[0] = 10;

    /* Range [0, 5*sz) -> Indices 0..4 */
    /* Last 10 is at Index 2 (Offset 8) */
    status = GenMemOpsFindLastBlockIndexRange(&idx, buf, sizeof(buf), 0, sizeof(buf), blk, sizeof(u32));
    assert(status == RESULT_SUCCESS);
    assert(idx == 8);

    /* Range [0, 2*sz) -> Indices 0, 1 */
    /* Last 10 is at Index 0 */
    status = GenMemOpsFindLastBlockIndexRange(&idx, buf, sizeof(buf), 0, 2 * sizeof(u32), blk, sizeof(u32));
    assert(status == RESULT_SUCCESS);
    assert(idx == 0);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_FindLastBlockRange(void)
{
    u64   buf[4];
    u64   blk[1];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U64_FindLastBlockRange -> ");

    /* Blocks: A, B, A, C */
    buf[0] = U64_C(0xAA);
    buf[1] = U64_C(0xBB);
    buf[2] = U64_C(0xAA);
    buf[3] = U64_C(0xCC);

    /* Search A */
    blk[0] = U64_C(0xAA);

    /* Range [0, 4*sz). Last A at Index 2 (Offset 16) */
    status = GenMemOpsFindLastBlockIndexRange(&idx, buf, sizeof(buf), 0, sizeof(buf), blk, sizeof(u64));
    assert(status == RESULT_SUCCESS);
    assert(idx == 16);

    /* Range [0, 2*sz). Last A at Index 0 */
    status = GenMemOpsFindLastBlockIndexRange(&idx, buf, sizeof(buf), 0, 2 * sizeof(u64), blk, sizeof(u64));
    assert(status == RESULT_SUCCESS);
    assert(idx == 0);

    printf("PASSED\n");
}
#endif


typedef struct kdi_LargeStruct
{
    u64 a;
    u64 b;
    u32 c;
    u8  d;
} kdi_LargeStruct;


void
Struct_FindLastBlockRange(void)
{
    kdi_LargeStruct buf[4];
    kdi_LargeStruct blk;
    usize           idx;
    bool            status;
    usize           sz = sizeof(kdi_LargeStruct);

    printf(LOG_PREFIX_CSTR "Struct_FindLastBlockRange -> ");

    /* Target */
    blk.a    = 1;
    blk.b    = 2;
    blk.c    = 3;
    blk.d    = 4;

    /* Init Buf: S_TARGET, S_OTHER, S_TARGET, S_OTHER */
    buf[0]   = blk;
    buf[1].a = 99;
    buf[1].b = 99;
    buf[2]   = blk;
    buf[3].a = 88;
    buf[3].b = 88;

    /* Range [0, 4*sz). Last at Index 2 (Offset 2*sz) */
    status   = GenMemOpsFindLastBlockIndexRange(&idx, buf, sizeof(buf), 0, sizeof(buf), &blk, sz);
    assert(status == RESULT_SUCCESS);
    assert(idx == 2 * sz);

    /* Range [0, 2*sz). Last at Index 0 */
    status = GenMemOpsFindLastBlockIndexRange(&idx, buf, sizeof(buf), 0, 2 * sz, &blk, sz);
    assert(status == RESULT_SUCCESS);
    assert(idx == 0);

    printf("PASSED\n");
}


void
LargeArray_FindLastRange(void)
{
    u8    buf[100];
    u8    blk[5];
    usize idx;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeArray_FindLastRange -> ");

    /* Init: 0..99 */
    for (i = 0; i < 100; ++i)
        buf[i] = (u8)i;

    /* Block: 50..54 */
    blk[0]  = 50;
    blk[1]  = 51;
    blk[2]  = 52;
    blk[3]  = 53;
    blk[4]  = 54;

    /* Create duplicate at 90..94 */
    buf[90] = 50;
    buf[91] = 51;
    buf[92] = 52;
    buf[93] = 53;
    buf[94] = 54;

    /* Range [0, 100). Should find last occurrence at 90. */
    status  = GenMemOpsFindLastBlockIndexRange(&idx, buf, USIZE_C(100), USIZE_C(0), USIZE_C(100), blk, USIZE_C(5));
    assert(status == RESULT_SUCCESS);
    assert(idx == 90);

    /* Range [0, 90). Excludes 90. Should find 50. */
    status = GenMemOpsFindLastBlockIndexRange(&idx, buf, USIZE_C(100), USIZE_C(0), USIZE_C(90), blk, USIZE_C(5));
    assert(status == RESULT_SUCCESS);
    assert(idx == 50);

    /* Range [25, 100). Start at 25 (aligned to 50 relative to block 5).
     * Should find 90.
     */
    status = GenMemOpsFindLastBlockIndexRange(&idx, buf, USIZE_C(100), USIZE_C(25), USIZE_C(100), blk, USIZE_C(5));
    assert(status == RESULT_SUCCESS);
    assert(idx == 90);

    /* Range [26, 100). Start at 26 (unaligned). Should fail to find 50 or 90. */
    status = GenMemOpsFindLastBlockIndexRange(&idx, buf, USIZE_C(100), USIZE_C(26), USIZE_C(100), blk, USIZE_C(5));
    assert(status == RESULT_FAILURE);

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
    AlignmentRelativeToStart();

    U16_FindLastBlockRange();
    U32_FindLastBlockRange();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_FindLastBlockRange();
#endif
    Struct_FindLastBlockRange();
    LargeArray_FindLastRange();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
