/**
 * @file kdGenMemOpsFindLastBlockIndex.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindLastBlockIndex function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindLastBlockIndex function test"
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
    status = GenMemOpsFindLastBlockIndex(null, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindLastBlockIndex(&idx, null, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    status = GenMemOpsFindLastBlockIndex(&idx, buf, USIZE_C(16), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr_sz is zero -> failure */
    status = GenMemOpsFindLastBlockIndex(&idx, buf, USIZE_C(0), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = GenMemOpsFindLastBlockIndex(&idx, buf, USIZE_C(16), blk, USIZE_C(0));
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

    status = GenMemOpsFindLastBlockIndex(&idx, buf, USIZE_C(16), blk, USIZE_C(4));
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
    /* Blocks: [00,00], [01,02], [00,00], [00,00] */
    kdi_FillVal(buf, USIZE_C(8), U8_C(0x00));

    /* Block 1 (Offset 2) */
    buf[2] = 0x01;
    buf[3] = 0x02;

    /* Search: 01 02 */
    blk[0] = 0x01;
    blk[1] = 0x02;

    status = GenMemOpsFindLastBlockIndex(&idx, buf, USIZE_C(8), blk, USIZE_C(2));

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

    /* Should find LAST occurrence (Block 2, Offset 4) */
    status = GenMemOpsFindLastBlockIndex(&idx, buf, USIZE_C(8), blk, USIZE_C(2));

    assert(status == RESULT_SUCCESS);
    assert(idx == 4);

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

    status = GenMemOpsFindLastBlockIndex(&idx, buf, USIZE_C(4), blk, USIZE_C(2));

    /* Should fail because it is not a discrete block */
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
U16_FindLastBlock(void)
{
    u16   buf[6];
    u16   blk[1];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U16_FindLastBlock -> ");

    /* Blocks: [100], [200], [100], [300], [100], [400] */
    /* Indices: 0,    1,     2,     3,     4,     5     */
    buf[0] = 100;
    buf[1] = 200;
    buf[2] = 100;
    buf[3] = 300;
    buf[4] = 100;
    buf[5] = 400;

    /* Search 100 */
    blk[0] = 100;

    /* Should find last occurrence at Index 4 (Offset 8) */
    status = GenMemOpsFindLastBlockIndex(&idx, buf, sizeof(buf), blk, sizeof(u16));

    assert(status == RESULT_SUCCESS);
    assert(idx == 4 * sizeof(u16));

    printf("PASSED\n");
}


void
U32_FindLastBlock(void)
{
    u32   buf[6];
    u32   blk[1];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_FindLastBlock -> ");

    /* Blocks: [10], [20], [10], [30], [10], [40] */
    buf[0] = 10;
    buf[1] = 20;
    buf[2] = 10;
    buf[3] = 30;
    buf[4] = 10;
    buf[5] = 40;

    /* Search 10 */
    blk[0] = 10;

    /* Should find last occurrence at Index 4 (Offset 16) */
    status = GenMemOpsFindLastBlockIndex(&idx, buf, sizeof(buf), blk, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    assert(idx == 4 * sizeof(u32));

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_FindLastBlock(void)
{
    u64   buf[3];
    u64   blk[1];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U64_FindLastBlock -> ");

    /* Blocks: A, B, A */
    buf[0] = U64_C(0xAAAAAAAAAAAAAAAA);
    buf[1] = U64_C(0xBBBBBBBBBBBBBBBB);
    buf[2] = U64_C(0xAAAAAAAAAAAAAAAA);

    /* Search A (Last occurrence at Index 2) */
    blk[0] = U64_C(0xAAAAAAAAAAAAAAAA);

    status = GenMemOpsFindLastBlockIndex(&idx, buf, sizeof(buf), blk, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    /* Index 2 * 8 bytes = 16 */
    assert(idx == 16);

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
Struct_FindLastBlock(void)
{
    kdi_LargeStruct buf[3];
    kdi_LargeStruct blk;
    usize           idx;
    bool            status;

    printf(LOG_PREFIX_CSTR "Struct_FindLastBlock -> ");

    /* Target: S_TARGET */
    blk.a    = 1;
    blk.b    = 2;
    blk.c    = 3;
    blk.d    = 4;

    /* Buffer: S_TARGET, S_OTHER, S_TARGET */
    buf[0]   = blk;

    buf[1].a = 99;
    buf[1].b = 99;
    buf[1].c = 99;
    buf[1].d = 99;

    buf[2]   = blk;

    status   = GenMemOpsFindLastBlockIndex(&idx, buf, sizeof(buf), &blk, sizeof(kdi_LargeStruct));

    assert(status == RESULT_SUCCESS);
    /* Index 2 * sizeof(struct) */
    assert(idx == 2 * sizeof(kdi_LargeStruct));

    printf("PASSED\n");
}


void
LargeArray_FindLast(void)
{
    u8    buf[100];
    u8    blk[5];
    usize idx;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeArray_FindLast -> ");

    /* Init: 0..99 */
    for (i = 0; i < 100; ++i)
        buf[i] = (u8)i;

    /* Force a repeat of block 10 (50..54) at block 18 (90..94) */
    /* Original at 90 is 90,91,92,93,94. We overwrite it. */
    buf[90] = 50;
    buf[91] = 51;
    buf[92] = 52;
    buf[93] = 53;
    buf[94] = 54;

    /* Search for 50..54 */
    blk[0]  = 50;
    blk[1]  = 51;
    blk[2]  = 52;
    blk[3]  = 53;
    blk[4]  = 54;

    status  = GenMemOpsFindLastBlockIndex(&idx, buf, USIZE_C(100), blk, USIZE_C(5));

    assert(status == RESULT_SUCCESS);
    /* Should find the one at 90 (Block 18), not 50 (Block 10) */
    assert(idx == 90);

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

    U16_FindLastBlock();
    U32_FindLastBlock();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_FindLastBlock();
#endif
    Struct_FindLastBlock();
    LargeArray_FindLast();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
