/**
 * @file kdGenMemOpsFindBlockIndex.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindBlockIndex function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindBlockIndex function test"
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
    status = GenMemOpsFindBlockIndex(null, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindBlockIndex(&idx, null, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    status = GenMemOpsFindBlockIndex(&idx, buf, USIZE_C(16), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr_sz is zero -> failure */
    status = GenMemOpsFindBlockIndex(&idx, buf, USIZE_C(0), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = GenMemOpsFindBlockIndex(&idx, buf, USIZE_C(16), blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
FindNone(void)
{
    u8    buf[16];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNone -> ");

    /* Init: 0x00 */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Search for 0x01.. */
    kdi_FillVal(blk, USIZE_C(4), U8_C(0x01));

    status = GenMemOpsFindBlockIndex(&idx, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Search for block larger than buffer */
    status = GenMemOpsFindBlockIndex(&idx, buf, USIZE_C(16), blk, USIZE_C(20));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
FindSimple(void)
{
    u8    buf[8];
    u8    blk[2];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindSimple -> ");

    /* Block Size: 2 */
    /* Blocks: [00,00], [01,02], [00,00], [03,04] */
    kdi_FillVal(buf, USIZE_C(8), U8_C(0x00));

    /* Block 1 (Offset 2) */
    buf[2] = 0x01;
    buf[3] = 0x02;
    /* Block 3 (Offset 6) */
    buf[6] = 0x03;
    buf[7] = 0x04;

    /* Search: 01 02 */
    blk[0] = 0x01;
    blk[1] = 0x02;

    status = GenMemOpsFindBlockIndex(&idx, buf, USIZE_C(8), blk, USIZE_C(2));

    assert(status == RESULT_SUCCESS);
    assert(idx == 2);

    printf("PASSED\n");
}


void
FindMultiple(void)
{
    u8    buf[8];
    u8    blk[2];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindMultiple -> ");

    /* Block Size 2 */
    /* Buffer: [01,02], [00,00], [01,02], [00,00] */
    kdi_FillVal(buf, USIZE_C(8), U8_C(0x00));

    buf[0] = 0x01;
    buf[1] = 0x02; /* Block 0 */
    buf[4] = 0x01;
    buf[5] = 0x02; /* Block 2 */

    blk[0] = 0x01;
    blk[1] = 0x02;

    /* Should find first occurrence (Block 0, Offset 0) */
    status = GenMemOpsFindBlockIndex(&idx, buf, USIZE_C(8), blk, USIZE_C(2));

    assert(status == RESULT_SUCCESS);
    assert(idx == 0);

    printf("PASSED\n");
}


void
UnalignedMatchFail(void)
{
    u8    buf[4];
    u8    blk[2];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "UnalignedMatchFail -> ");

    /* Buffer: 0x01, 0x02, 0x03, 0x04 */
    buf[0] = 1;
    buf[1] = 2;
    buf[2] = 3;
    buf[3] = 4;

    /* Block Size: 2 */
    /* Block 0: [1, 2] */
    /* Block 1: [3, 4] */

    /* Search for: 2, 3 */
    /* Sequence exists at offset 1, but it crosses block boundaries. */
    blk[0] = 2;
    blk[1] = 3;

    status = GenMemOpsFindBlockIndex(&idx, buf, USIZE_C(4), blk, USIZE_C(2));

    /* Should fail because it is not a discrete block */
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
U16_FindBlock(void)
{
    u16   buf[4];
    u16   blk[1];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U16_FindBlock -> ");

    /* Blocks: [100], [200], [300], [400] */
    buf[0] = 100;
    buf[1] = 200;
    buf[2] = 300;
    buf[3] = 400;

    /* Search 300 (Block 2) */
    blk[0] = 300;

    status = GenMemOpsFindBlockIndex(&idx, buf, sizeof(buf), blk, sizeof(u16));

    assert(status == RESULT_SUCCESS);
    /* Index 2 * 2 bytes = 4 */
    assert(idx == 4);

    printf("PASSED\n");
}


void
U32_FindBlock(void)
{
    u32   buf[4];
    u32   blk[1];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_FindBlock -> ");

    /* Blocks: [10], [20], [30], [40] */
    buf[0] = 10;
    buf[1] = 20;
    buf[2] = 30;
    buf[3] = 40;

    /* Search 30 */
    blk[0] = 30;

    status = GenMemOpsFindBlockIndex(&idx, buf, sizeof(buf), blk, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    /* Index 2 * 4 bytes = 8 */
    assert(idx == 8);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_FindBlock(void)
{
    u64   buf[3];
    u64   blk[1];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U64_FindBlock -> ");

    /* Blocks: A, B, C */
    buf[0] = U64_C(0xAAAAAAAAAAAAAAAA);
    buf[1] = U64_C(0xBBBBBBBBBBBBBBBB);
    buf[2] = U64_C(0xCCCCCCCCCCCCCCCC);

    /* Search B (Block 1) */
    blk[0] = U64_C(0xBBBBBBBBBBBBBBBB);

    status = GenMemOpsFindBlockIndex(&idx, buf, sizeof(buf), blk, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    /* Index 1 * 8 bytes = 8 */
    assert(idx == 8);

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
Struct_FindBlock(void)
{
    kdi_LargeStruct buf[3];
    kdi_LargeStruct blk;
    usize           idx;
    bool            status;

    printf(LOG_PREFIX_CSTR "Struct_FindBlock -> ");

    /* Target: S_TARGET */
    blk.a    = 1;
    blk.b    = 2;
    blk.c    = 3;
    blk.d    = 4;

    /* Buffer: S0, S_TARGET, S2 */
    buf[0].a = 99;
    buf[0].b = 99;
    buf[0].c = 99;
    buf[0].d = 99;

    buf[1]   = blk;

    buf[2].a = 88;
    buf[2].b = 88;
    buf[2].c = 88;
    buf[2].d = 88;

    status   = GenMemOpsFindBlockIndex(&idx, buf, sizeof(buf), &blk, sizeof(kdi_LargeStruct));

    assert(status == RESULT_SUCCESS);
    /* Index 1 * sizeof(struct) */
    assert(idx == sizeof(kdi_LargeStruct));

    printf("PASSED\n");
}


void
LargeArray_Find(void)
{
    u8    buf[100];
    u8    blk[5];
    usize idx;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeArray_Find -> ");

    /* Init: 0..99 */
    for (i = 0; i < 100; ++i)
        buf[i] = (u8)i;

    /* Block Size: 5 */
    /* Blocks start at 0, 5, 10, ... */

    /* Search for Block 10 (Indices 50..54) */
    /* Values: 50, 51, 52, 53, 54 */
    blk[0] = 50;
    blk[1] = 51;
    blk[2] = 52;
    blk[3] = 53;
    blk[4] = 54;

    status = GenMemOpsFindBlockIndex(&idx, buf, USIZE_C(100), blk, USIZE_C(5));

    assert(status == RESULT_SUCCESS);
    /* Block 10 starts at offset 50 */
    assert(idx == 50);

    /* Search for unaligned sequence (Indices 51..55) */
    /* Values: 51, 52, 53, 54, 55 */
    /* This crosses from Block 10 to Block 11. Should fail. */
    blk[0] = 51;
    blk[1] = 52;
    blk[2] = 53;
    blk[3] = 54;
    blk[4] = 55;

    status = GenMemOpsFindBlockIndex(&idx, buf, USIZE_C(100), blk, USIZE_C(5));
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
    FindNone();
    FindSimple();
    FindMultiple();
    UnalignedMatchFail();

    U16_FindBlock();
    U32_FindBlock();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_FindBlock();
#endif
    Struct_FindBlock();
    LargeArray_Find();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
