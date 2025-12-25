/**
 * @file kdGenMemOpsFindBlockIndexRange.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindBlockIndexRange function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindBlockIndexRange function test"
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
    status = GenMemOpsFindBlockIndexRange(null, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindBlockIndexRange(&idx, null, USIZE_C(16), USIZE_C(0), USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    status = GenMemOpsFindBlockIndexRange(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr_sz is zero -> failure */
    status = GenMemOpsFindBlockIndexRange(&idx, buf, USIZE_C(0), USIZE_C(0), USIZE_C(0), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = GenMemOpsFindBlockIndexRange(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* begin_idx > end -> failure */
    status = GenMemOpsFindBlockIndexRange(&idx, buf, USIZE_C(16), USIZE_C(5), USIZE_C(4), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* end > ptr_sz -> failure */
    status = GenMemOpsFindBlockIndexRange(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(17), blk, USIZE_C(4));
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

    /* Set distinct values for blocks */
    /* Block 0 */ kdi_FillVal(buf + 0, 4, 0xAA);
    /* Block 1 */ kdi_FillVal(buf + 4, 4, 0xBB);
    /* Block 2 */ kdi_FillVal(buf + 8, 4, 0xCC);
    /* Block 3 */ kdi_FillVal(buf + 12, 4, 0xDD);

    /* Search Range [4, 12). Includes Block 1 and Block 2. Excludes Block 3. */

    /* 1. Find Block 1 (Start of Range) */
    kdi_FillVal(blk, 4, 0xBB);
    status = GenMemOpsFindBlockIndexRange(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(12), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == 4);

    /* 2. Find Block 2 (End of Range - block_sz) */
    kdi_FillVal(blk, 4, 0xCC);
    status = GenMemOpsFindBlockIndexRange(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(12), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == 8);

    /* 3. Find Block 0 (Before Range) -> Fail */
    kdi_FillVal(blk, 4, 0xAA);
    status = GenMemOpsFindBlockIndexRange(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(12), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* 4. Find Block 3 (At/After End of Range limit) -> Fail */
    kdi_FillVal(blk, 4, 0xDD);
    status = GenMemOpsFindBlockIndexRange(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(12), blk, USIZE_C(4));
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

    /* Range [4, 16). Should skip index 2. Find index 6. */
    status  = GenMemOpsFindBlockIndexRange(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(16), blk, USIZE_C(2));

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

    /* Case 1: Start at 0. Blocks checked: [0,1], [2,3]... */
    /* Index 2 holds [2,3]. Should find. */
    status = GenMemOpsFindBlockIndexRange(&idx, buf, USIZE_C(10), USIZE_C(0), USIZE_C(6), blk, USIZE_C(2));
    assert(status == RESULT_SUCCESS);
    assert(idx == 2);

    /* Case 2: Start at 1. Blocks checked: [1,2], [3,4]... */
    /* Index 2 is unaligned relative to start index 1. Should fail. */
    status = GenMemOpsFindBlockIndexRange(&idx, buf, USIZE_C(10), USIZE_C(1), USIZE_C(6), blk, USIZE_C(2));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
U16_FindBlockRange(void)
{
    u16   buf[6];
    u16   blk[1];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U16_FindBlockRange -> ");

    /* Indices: 0, 1, 2, 3, 4, 5 */
    /* Values: 100, 200, 300, 400, 500, 600 */
    buf[0] = 100;
    buf[1] = 200;
    buf[2] = 300;
    buf[3] = 400;
    buf[4] = 500;
    buf[5] = 600;

    /* Search 400 (Index 3, Offset 6) */
    blk[0] = 400;

    /* Range [2*sizeof(u16), 5*sizeof(u16)) -> [4, 10) bytes. */
    /* Covers indices 2, 3, 4 (Values 300, 400, 500) */
    status = GenMemOpsFindBlockIndexRange(&idx, buf, sizeof(buf), 2 * sizeof(u16), 5 * sizeof(u16), blk, sizeof(u16));

    assert(status == RESULT_SUCCESS);
    assert(idx == 3 * sizeof(u16)); /* Offset 6 */

    /* Search 100 (Index 0). Before range. */
    blk[0] = 100;
    status = GenMemOpsFindBlockIndexRange(&idx, buf, sizeof(buf), 2 * sizeof(u16), 5 * sizeof(u16), blk, sizeof(u16));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
U32_FindBlockRange(void)
{
    u32   buf[5];
    u32   blk[1];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_FindBlockRange -> ");

    /* Init: 10, 20, 30, 40, 50 */
    buf[0] = 10;
    buf[1] = 20;
    buf[2] = 30;
    buf[3] = 40;
    buf[4] = 50;

    /* Search 40 */
    blk[0] = 40;

    /* Range: [sizeof(u32), 5*sizeof(u32)) => Indices 1..4 */
    /* 40 is at Index 3 (Offset 12). */
    status = GenMemOpsFindBlockIndexRange(&idx, buf, sizeof(buf), sizeof(u32), sizeof(buf), blk, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    assert(idx == 12);

    /* Search 10 (Index 0). Outside Range start. */
    blk[0] = 10;
    status = GenMemOpsFindBlockIndexRange(&idx, buf, sizeof(buf), sizeof(u32), sizeof(buf), blk, sizeof(u32));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_FindBlockRange(void)
{
    u64   buf[4];
    u64   blk[1];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U64_FindBlockRange -> ");

    /* Init: A, B, C, D */
    buf[0] = U64_C(0x1111111111111111);
    buf[1] = U64_C(0x2222222222222222);
    buf[2] = U64_C(0x3333333333333333);
    buf[3] = U64_C(0x4444444444444444);

    /* Search C (Index 2, Offset 16) */
    blk[0] = U64_C(0x3333333333333333);

    /* Range [8, 32). Indices 1, 2, 3. */
    status = GenMemOpsFindBlockIndexRange(&idx, buf, sizeof(buf), sizeof(u64), 4 * sizeof(u64), blk, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    assert(idx == 16);

    /* Search A (Index 0). Outside Range. */
    blk[0] = U64_C(0x1111111111111111);
    status = GenMemOpsFindBlockIndexRange(&idx, buf, sizeof(buf), sizeof(u64), 4 * sizeof(u64), blk, sizeof(u64));
    assert(status == RESULT_FAILURE);

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
Struct_FindBlockRange(void)
{
    kdi_LargeStruct buf[4];
    kdi_LargeStruct blk;
    usize           idx;
    bool            status;
    usize           sz = sizeof(kdi_LargeStruct);

    printf(LOG_PREFIX_CSTR "Struct_FindBlockRange -> ");

    /* Target */
    blk.a    = 1;
    blk.b    = 2;
    blk.c    = 3;
    blk.d    = 4;

    /* Init Buf */
    buf[0].a = 0; /* ... */
    buf[1]   = blk;
    buf[2].a = 0; /* ... */
    buf[3]   = blk;

    /* Range: [2*sz, 4*sz). Covers S2, S3. */
    /* Should find S3 (Index 3). Skip S1. */
    status   = GenMemOpsFindBlockIndexRange(&idx, buf, sizeof(buf), 2 * sz, 4 * sz, &blk, sz);

    assert(status == RESULT_SUCCESS);
    assert(idx == 3 * sz);

    printf("PASSED\n");
}


void
LargeArray_FindRange(void)
{
    u8    buf[100];
    u8    blk[5];
    usize idx;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeArray_FindRange -> ");

    /* Init: 0..99 */
    for (i = 0; i < 100; ++i)
        buf[i] = (u8)i;

    /* Search Block: 50..54 */
    blk[0] = 50;
    blk[1] = 51;
    blk[2] = 52;
    blk[3] = 53;
    blk[4] = 54;

    /* Range [0, 50). Block starts at 50, which is == End. Should Fail. */
    status = GenMemOpsFindBlockIndexRange(&idx, buf, USIZE_C(100), USIZE_C(0), USIZE_C(50), blk, USIZE_C(5));
    assert(status == RESULT_FAILURE);

    /* Range [0, 55). Block [50..54] fits. Should Find. */
    status = GenMemOpsFindBlockIndexRange(&idx, buf, USIZE_C(100), USIZE_C(0), USIZE_C(55), blk, USIZE_C(5));
    assert(status == RESULT_SUCCESS);
    assert(idx == 50);

    /* Range [25, 100).
     * Start index 25 is aligned with 50 relative to block size 5 (25 + 5*5 = 50).
     * Should Find.
     */
    status = GenMemOpsFindBlockIndexRange(&idx, buf, USIZE_C(100), USIZE_C(25), USIZE_C(100), blk, USIZE_C(5));
    assert(status == RESULT_SUCCESS);
    assert(idx == 50);

    /* Range [26, 100).
     * Start index 26.
     * Checks: 26, 31, 36, 41, 46, 51...
     * Block is at 50. 50 is unaligned relative to 26 (step 5). Should Fail.
     */
    status = GenMemOpsFindBlockIndexRange(&idx, buf, USIZE_C(100), USIZE_C(26), USIZE_C(100), blk, USIZE_C(5));
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

    U16_FindBlockRange();
    U32_FindBlockRange();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_FindBlockRange();
#endif
    Struct_FindBlockRange();
    LargeArray_FindRange();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
