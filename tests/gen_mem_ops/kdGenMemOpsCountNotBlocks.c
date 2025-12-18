/**
 * @file kdGenMemOpsCountNotBlocks.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsCountNotBlocks function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsCountNotBlocks function test"
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
    u8    blk[4];
    usize count = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* count pointer is null -> failure */
    status = GenMemOpsCountNotBlocks(null, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsCountNotBlocks(&count, null, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    status = GenMemOpsCountNotBlocks(&count, buf, USIZE_C(16), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr_sz is zero -> success, count 0 */
    count  = 55;
    status = GenMemOpsCountNotBlocks(&count, buf, USIZE_C(0), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(count == 0);

    /* block_sz is zero -> failure */
    status = GenMemOpsCountNotBlocks(&count, buf, USIZE_C(16), blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
CountNone(void)
{
    u8    buf[16];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountNone -> ");

    /* Init buffer with 0xAA */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Block is 0xAA */
    kdi_FillVal(blk, USIZE_C(4), U8_C(0xAA));

    /* Count NOT Block (0xAA). Every block is 0xAA, so count should be 0. */
    status = GenMemOpsCountNotBlocks(&count, buf, USIZE_C(16), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == 0);

    printf("PASSED\n");
}


void
CountAll(void)
{
    u8    buf[16];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountAll -> ");

    /* Init buffer with 0x00 */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Block is 0xFF */
    kdi_FillVal(blk, USIZE_C(4), U8_C(0xFF));

    /* Count NOT Block (0xFF). All blocks are 0x00. Count should be 16/4 = 4. */
    status = GenMemOpsCountNotBlocks(&count, buf, USIZE_C(16), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == 4);

    printf("PASSED\n");
}


void
CountMixed(void)
{
    u8    buf[12];
    u8    blk[2];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountMixed -> ");

    /* Block size 2. Total 6 blocks. */
    /* Blocks: [1,2], [3,4], [1,2], [5,6], [1,2], [7,8] */
    buf[0]  = 1;
    buf[1]  = 2; /* Match */
    buf[2]  = 3;
    buf[3]  = 4; /* No Match */
    buf[4]  = 1;
    buf[5]  = 2; /* Match */
    buf[6]  = 5;
    buf[7]  = 6; /* No Match */
    buf[8]  = 1;
    buf[9]  = 2; /* Match */
    buf[10] = 7;
    buf[11] = 8; /* No Match */

    /* Target: [1,2] */
    blk[0]  = 1;
    blk[1]  = 2;

    /* Count NOT [1,2]. Should be 3 ([3,4], [5,6], [7,8]). */
    status  = GenMemOpsCountNotBlocks(&count, buf, USIZE_C(12), blk, USIZE_C(2));

    assert(status == RESULT_SUCCESS);
    assert(count == 3);

    printf("PASSED\n");
}


void
U16_CountNotBlocks(void)
{
    u16   buf[6];
    u16   blk[1];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "U16_CountNotBlocks -> ");

    /* Blocks: 100, 200, 100, 300, 100, 400 */
    buf[0] = 100;
    buf[1] = 200;
    buf[2] = 100;
    buf[3] = 300;
    buf[4] = 100;
    buf[5] = 400;

    /* Target: 100 */
    blk[0] = 100;

    /* Count NOT 100. Should be 3 (200, 300, 400). */
    status = GenMemOpsCountNotBlocks(&count, buf, sizeof(buf), blk, sizeof(u16));

    assert(status == RESULT_SUCCESS);
    assert(count == 3);

    printf("PASSED\n");
}


void
U32_CountNotBlocks(void)
{
    u32   buf[6];
    u32   blk[2];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_CountNotBlocks -> ");

    /* Block Size: 2 * u32 */
    /* Block 0: [10, 20] (Match) */
    /* Block 1: [99, 99] (No Match) */
    /* Block 2: [10, 20] (Match) */
    buf[0] = 10;
    buf[1] = 20;
    buf[2] = 99;
    buf[3] = 99;
    buf[4] = 10;
    buf[5] = 20;

    /* Target: [10, 20] */
    blk[0] = 10;
    blk[1] = 20;

    /* Count NOT [10, 20]. Should be 1 ([99, 99]). */
    status = GenMemOpsCountNotBlocks(&count, buf, sizeof(buf), blk, sizeof(u32) * 2);

    assert(status == RESULT_SUCCESS);
    assert(count == 1);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_CountNotBlocks(void)
{
    u64   buf[3];
    u64   blk[1];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "U64_CountNotBlocks -> ");

    /* Blocks: A, B, A */
    buf[0] = U64_C(0xAAAAAAAAAAAAAAAA);
    buf[1] = U64_C(0xBBBBBBBBBBBBBBBB);
    buf[2] = U64_C(0xAAAAAAAAAAAAAAAA);

    /* Target: A */
    blk[0] = U64_C(0xAAAAAAAAAAAAAAAA);

    /* Count NOT A. Should be 1 (B). */
    status = GenMemOpsCountNotBlocks(&count, buf, sizeof(buf), blk, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    assert(count == 1);

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
Struct_CountNotBlocks(void)
{
    kdi_LargeStruct buf[4];
    kdi_LargeStruct blk;
    usize           count;
    bool            status;

    printf(LOG_PREFIX_CSTR "Struct_CountNotBlocks -> ");

    /* Target: A */
    blk.a    = 1;
    blk.b    = 2;
    blk.c    = 3;
    blk.d    = 4;

    /* Buffer: A, B, A, C */
    /* Index 0: A */
    buf[0]   = blk;
    /* Index 1: B */
    buf[1].a = 99;
    buf[1].b = 99;
    buf[1].c = 99;
    buf[1].d = 99;
    /* Index 2: A */
    buf[2]   = blk;
    /* Index 3: C */
    buf[3].a = 88;
    buf[3].b = 88;
    buf[3].c = 88;
    buf[3].d = 88;

    /* Count NOT A. Should be 2 (B, C). */
    status   = GenMemOpsCountNotBlocks(&count, buf, sizeof(buf), &blk, sizeof(kdi_LargeStruct));

    assert(status == RESULT_SUCCESS);
    assert(count == 2);

    printf("PASSED\n");
}


void
LargeArray_Count(void)
{
    u8    buf[100];
    u8    blk[5];
    usize count;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeArray_Count -> ");

    /* Init: 1, 2, 3, 4, 5 repeating */
    for (i = 0; i < 100; ++i)
        buf[i] = (u8)((i % 5) + 1);

    /* Target: 1, 2, 3, 4, 5 */
    blk[0] = 1;
    blk[1] = 2;
    blk[2] = 3;
    blk[3] = 4;
    blk[4] = 5;

    /* Every block matches. Count NOT should be 0. */
    status = GenMemOpsCountNotBlocks(&count, buf, USIZE_C(100), blk, USIZE_C(5));
    assert(status == RESULT_SUCCESS);
    assert(count == 0);

    /* Change one block (Indices 5..9) to 0x00 */
    kdi_FillVal(buf + 5, USIZE_C(5), U8_C(0x00));

    /* Now we have 1 non-matching block. */
    status = GenMemOpsCountNotBlocks(&count, buf, USIZE_C(100), blk, USIZE_C(5));
    assert(status == RESULT_SUCCESS);
    assert(count == 1);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    CountNone();
    CountAll();
    CountMixed();

    U16_CountNotBlocks();
    U32_CountNotBlocks();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_CountNotBlocks();
#endif
    Struct_CountNotBlocks();
    LargeArray_Count();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
