/**
 * @file kdGenMemOpsCountBlocks.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsCountBlocks function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsCountBlocks function test"
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
    status = GenMemOpsCountBlocks(null, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsCountBlocks(&count, null, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    status = GenMemOpsCountBlocks(&count, buf, USIZE_C(16), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr_sz is zero -> success, count 0 */
    count  = 55;
    status = GenMemOpsCountBlocks(&count, buf, USIZE_C(0), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(count == 0);

    /* block_sz is zero -> failure */
    status = GenMemOpsCountBlocks(&count, buf, USIZE_C(16), blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
CountNone(void)
{
    u8    buf[16];
    u8    blk[2];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountNone -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));
    blk[0] = 0x01;
    blk[1] = 0x02;

    status = GenMemOpsCountBlocks(&count, buf, USIZE_C(16), blk, USIZE_C(2));

    assert(status == RESULT_SUCCESS);
    assert(count == 0);

    /* Search for block larger than buffer */
    status = GenMemOpsCountBlocks(&count, buf, USIZE_C(16), blk, USIZE_C(20));
    assert(status == RESULT_SUCCESS);
    assert(count == 0);

    printf("PASSED\n");
}


void
CountSimple(void)
{
    u8    buf[10];
    u8    blk[2];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountSimple -> ");

    /* * Buffer size 10. Block size 2. Total 5 blocks.
     * Block 0 (0-1): 00 00
     * Block 1 (2-3): 01 02 (Match)
     * Block 2 (4-5): 00 00
     * Block 3 (6-7): 01 02 (Match)
     * Block 4 (8-9): 00 00
     */
    kdi_FillVal(buf, USIZE_C(10), U8_C(0x00));
    buf[2] = 0x01;
    buf[3] = 0x02;
    buf[6] = 0x01;
    buf[7] = 0x02;

    blk[0] = 0x01;
    blk[1] = 0x02;

    status = GenMemOpsCountBlocks(&count, buf, USIZE_C(10), blk, USIZE_C(2));

    assert(status == RESULT_SUCCESS);
    assert(count == 2);

    printf("PASSED\n");
}


void
EdgeCases(void)
{
    u8    buf[4];
    u8    blk[2];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "EdgeCases -> ");

    /* Buffer: 1, 2, 3, 4 */
    buf[0] = 1;
    buf[1] = 2;
    buf[2] = 3;
    buf[3] = 4;

    /* * Block Size: 2.
     * Block 0: [1, 2]
     * Block 1: [3, 4]
     */

    /* Search 1, 2 (Aligned Block 0) -> Found */
    blk[0] = 1;
    blk[1] = 2;
    status = GenMemOpsCountBlocks(&count, buf, USIZE_C(4), blk, USIZE_C(2));
    assert(status == RESULT_SUCCESS);
    assert(count == 1);

    /* Search 3, 4 (Aligned Block 1) -> Found */
    blk[0] = 3;
    blk[1] = 4;
    status = GenMemOpsCountBlocks(&count, buf, USIZE_C(4), blk, USIZE_C(2));
    assert(status == RESULT_SUCCESS);
    assert(count == 1);

    /* Search 2, 3 (Unaligned - crosses block boundary) -> Not Found */
    blk[0] = 2;
    blk[1] = 3;
    status = GenMemOpsCountBlocks(&count, buf, USIZE_C(4), blk, USIZE_C(2));
    assert(status == RESULT_SUCCESS);
    assert(count == 0);

    /* Exact Match (ptr_sz == block_sz) */
    status = GenMemOpsCountBlocks(&count, buf, USIZE_C(4), buf, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(count == 1);

    printf("PASSED\n");
}


void
U16_CountBlocks(void)
{
    u16   buf[6];
    u16   blk[1];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "U16_CountBlocks -> ");

    /* * Block size = sizeof(u16) = 2 bytes.
     * Blocks: [100], [200], [100], [300], [100], [400]
     */
    buf[0] = 100;
    buf[1] = 200;
    buf[2] = 100;
    buf[3] = 300;
    buf[4] = 100;
    buf[5] = 400;

    blk[0] = 100;

    status = GenMemOpsCountBlocks(&count, buf, sizeof(buf), blk, sizeof(u16));

    assert(status == RESULT_SUCCESS);
    assert(count == 3);

    printf("PASSED\n");
}


void
U32_CountBlocks(void)
{
    u32   buf[6]; /* Size adjusted to be multiple of block size (2*u32) */
    u32   blk[2];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_CountBlocks -> ");

    /* * Block size = 2 * sizeof(u32) = 8 bytes.
     * Buffer size = 6 * 4 = 24 bytes.
     * Block 0: [10, 20]
     * Block 1: [99, 99]
     * Block 2: [10, 20]
     */
    buf[0] = 10;
    buf[1] = 20;
    buf[2] = 99;
    buf[3] = 99;
    buf[4] = 10;
    buf[5] = 20;

    blk[0] = 10;
    blk[1] = 20;

    status = GenMemOpsCountBlocks(&count, buf, sizeof(buf), blk, sizeof(u32) * 2);

    assert(status == RESULT_SUCCESS);
    assert(count == 2);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_CountBlocks(void)
{
    u64   buf[3];
    u64   blk[1];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "U64_CountBlocks -> ");

    /* * Block size = sizeof(u64).
     * Block 0: A
     * Block 1: B
     * Block 2: A
     */
    buf[0] = U64_C(0xAAAAAAAAAAAAAAAA);
    buf[1] = U64_C(0xBBBBBBBBBBBBBBBB);
    buf[2] = U64_C(0xAAAAAAAAAAAAAAAA);

    blk[0] = U64_C(0xAAAAAAAAAAAAAAAA);

    status = GenMemOpsCountBlocks(&count, buf, sizeof(buf), blk, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    assert(count == 2);

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
Struct_CountBlocks(void)
{
    kdi_LargeStruct buf[4];
    kdi_LargeStruct blk;
    usize           count;
    bool            status;

    printf(LOG_PREFIX_CSTR "Struct_CountBlocks -> ");

    /* Target: A */
    blk.a    = 1;
    blk.b    = 2;
    blk.c    = 3;
    blk.d    = 4;

    /* * Block size = sizeof(struct).
     * Block 0: A
     * Block 1: B
     * Block 2: A
     * Block 3: C
     */
    buf[0]   = blk;

    buf[1].a = 99;
    buf[1].b = 99;
    buf[1].c = 99;
    buf[1].d = 99;

    buf[2]   = blk;

    buf[3].a = 88;
    buf[3].b = 88;
    buf[3].c = 88;
    buf[3].d = 88;

    status   = GenMemOpsCountBlocks(&count, buf, sizeof(buf), &blk, sizeof(kdi_LargeStruct));

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

    /* Init: 0..99 */
    kdi_FillSeq(buf, USIZE_C(100), U8_C(0));

    /* * Block Size 5.
     * Blocks start at 0, 5, 10, ...
     * Search for: 10, 11, 12, 13, 14
     * This corresponds exactly to the block starting at index 10.
     */
    blk[0] = 10;
    blk[1] = 11;
    blk[2] = 12;
    blk[3] = 13;
    blk[4] = 14;

    status = GenMemOpsCountBlocks(&count, buf, USIZE_C(100), blk, USIZE_C(5));
    assert(status == RESULT_SUCCESS);
    assert(count == 1);

    /* Fill buffer with repeating pattern: 1,2,3,4,5... */
    for (i = 0; i < 100; ++i)
        buf[i] = (u8)((i % 5) + 1);

    /* Search for 1,2,3,4,5 */
    blk[0] = 1;
    blk[1] = 2;
    blk[2] = 3;
    blk[3] = 4;
    blk[4] = 5;

    /* * Pattern repeats every 5 bytes.
     * Buffer 100 bytes / Block 5 bytes = 20 aligned blocks.
     */
    status = GenMemOpsCountBlocks(&count, buf, USIZE_C(100), blk, USIZE_C(5));
    assert(status == RESULT_SUCCESS);
    assert(count == 20);

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
    CountSimple();
    EdgeCases();

    U16_CountBlocks();
    U32_CountBlocks();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_CountBlocks();
#endif
    Struct_CountBlocks();
    LargeArray_Count();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
