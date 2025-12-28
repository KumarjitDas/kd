/**
 * @file kdGenMemOpsFindNotBlockIndexBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindNotBlockIndexBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindNotBlockIndexBound function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0x00));

    /* idx pointer is null -> failure */
    status = kdGenMemOpsFindNotBlockIndexBound(null, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure */
    idx    = 55;
    status = kdGenMemOpsFindNotBlockIndexBound(&idx, null, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    idx    = 55;
    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* begin_idx >= base_sz -> failure */
    idx    = 55;
    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(32), USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* end_count_byte is zero -> failure */
    idx    = 55;
    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(0), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    idx    = 55;
    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* base_sz not divisible by block_sz -> failure */
    idx    = 55;
    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(31), USIZE_C(0), USIZE_C(31), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* begin_idx not aligned to block_sz -> failure */
    idx    = 55;
    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(3), USIZE_C(29), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Valid arguments - Find NOT 0xFF in 0x00 buffer. Match at 0. */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xFF));
    idx    = 55;
    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    printf("PASSED\n");
}


void
FindNone(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNone -> ");

    /* Init: all blocks are [0xFF, 0xFF, 0xFF, 0xFF] */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xFF));

    /* Search for NOT [0xFF, 0xFF, 0xFF, 0xFF] in range [0, 32) */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xFF));

    idx    = 999;
    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
FindFirst(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindFirst -> ");

    /* Init: 0x00 */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));

    /* Set first block to [0xFF, 0xFF, 0xFF, 0xFF] */
    kdi_Fill_u8(buf, USIZE_C(4), U8_C(0xFF));

    /* Search for NOT [0x00, 0x00, 0x00, 0x00] */
    /* All are 0x00 except first which is 0xFF. Match 0xFF at 0. */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0x00));

    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    printf("PASSED\n");
}


void
FindLast(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindLast -> ");

    /* Init: 0x00 */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));

    /* Set last block to [0xFF, 0xFF, 0xFF, 0xFF] */
    kdi_Fill_u8(buf + 28, USIZE_C(4), U8_C(0xFF));

    /* Search for NOT [0x00, 0x00, 0x00, 0x00] */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0x00));

    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(28));

    printf("PASSED\n");
}


void
RangeConstraints(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "RangeConstraints -> ");

    /* Init: 0x00 */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));

    /* Set some blocks to 0xFF */
    /* Block at 8 (idx 2) */
    kdi_Fill_u8(buf + 8, USIZE_C(4), U8_C(0xFF));
    /* Block at 20 (idx 5) */
    kdi_Fill_u8(buf + 20, USIZE_C(4), U8_C(0xFF));

    /* Target: NOT 0x00 */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0x00));

    /* Range [0, 32). Should find 8. */
    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(8));

    /* Range [12, 28). Begin_idx=12 (idx 3). End count 16 bytes.
     * Blocks at 12, 16, 20, 24.
     * 12 is 0x00.
     * 16 is 0x00.
     * 20 is 0xFF. Match 20. */
    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(12), USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(20));

    /* Range [8, 12). Block at 8 is 0xFF. Match 8. */
    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(8), USIZE_C(4), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(8));

    /* Range [12, 20). Blocks at 12, 16. Both 0x00. Fail. */
    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(12), USIZE_C(8), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
EndValueClamping(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "EndValueClamping -> ");

    /* Init 0x00 */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));
    /* Last block 0xFF */
    kdi_Fill_u8(buf + 28, USIZE_C(4), U8_C(0xFF));

    /* Target NOT 0x00 */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0x00));

    /* Request 100 bytes. Clamps to 32. Range [0, 32). Match 28. */
    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(100), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(28));

    printf("PASSED\n");
}


void
FindMultiple(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindMultiple -> ");

    /* Init 0x00 */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));

    /* Set 0xFF at 4, 12, 20 */
    kdi_Fill_u8(buf + 4, USIZE_C(4), U8_C(0xFF));
    kdi_Fill_u8(buf + 12, USIZE_C(4), U8_C(0xFF));
    kdi_Fill_u8(buf + 20, USIZE_C(4), U8_C(0xFF));

    /* Target NOT 0x00 */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0x00));

    /* Range [8, 24). Covers 8, 12, 16, 20.
     * 8: 00 (skip)
     * 12: FF (match) */
    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(8), USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(12));

    printf("PASSED\n");
}


void
U16_FindNotBlockIndexBound(void)
{
    u16   buf[8];
    u16   blk[1];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U16_FindNotBlockIndexBound -> ");

    /* Init: 100, 200, 300, 400, 500, 600, 700, 800 */
    buf[0] = 100;
    buf[1] = 200;
    buf[2] = 300;
    buf[3] = 400;
    buf[4] = 500;
    buf[5] = 600;
    buf[6] = 700;
    buf[7] = 800;

    /* Search for NOT 100 */
    blk[0] = 100;

    /* Range [0, 16).
     * 0: 100 == 100.
     * 1 (offset 2): 200 != 100. Match 2. */
    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, sizeof(buf), USIZE_C(0), sizeof(buf), blk, sizeof(u16));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(2));

    /* Search for NOT 300 in range [4, 10). Covers 2, 3, 4 (4-9).
     * Offset 4 (idx 2): 300 == 300.
     * Offset 6 (idx 3): 400 != 300. Match 6. */
    blk[0] = 300;
    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, sizeof(buf), USIZE_C(4), USIZE_C(6), blk, sizeof(u16));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(6));

    printf("PASSED\n");
}


void
U32_FindNotBlockIndexBound(void)
{
    u32   buf[6];
    u32   blk[1];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_FindNotBlockIndexBound -> ");

    /* Init: 10, 20, 30, 40, 50, 60 */
    buf[0] = 10;
    buf[1] = 20;
    buf[2] = 30;
    buf[3] = 40;
    buf[4] = 50;
    buf[5] = 60;

    /* Search for NOT 10.
     * 0: 10 == 10.
     * 1 (offset 4): 20 != 10. Match 4. */
    blk[0] = 10;
    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, sizeof(buf), USIZE_C(0), sizeof(buf), blk, sizeof(u32));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(4));

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_FindNotBlockIndexBound(void)
{
    u64   buf[5];
    u64   blk[1];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U64_FindNotBlockIndexBound -> ");

    /* Init: A, B, C, D, E */
    buf[0] = U64_C(0x1111111111111111);
    buf[1] = U64_C(0x2222222222222222);
    buf[2] = U64_C(0x3333333333333333);
    buf[3] = U64_C(0x4444444444444444);
    buf[4] = U64_C(0x5555555555555555);

    /* Search for NOT A.
     * 0: A == A.
     * 1 (offset 8): B != A. Match 8. */
    blk[0] = U64_C(0x1111111111111111);
    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, sizeof(buf), USIZE_C(0), sizeof(buf), blk, sizeof(u64));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(8));

    printf("PASSED\n");
}
#endif


typedef struct kdi_TestStruct
{
    u32 a;
    u16 b;
    u8  c;
    u8  d;
} kdi_TestStruct;


void
Struct_FindNotBlockIndexBound(void)
{
    kdi_TestStruct buf[5];
    kdi_TestStruct blk;
    usize          idx;
    bool           status;
    usize          sz = sizeof(kdi_TestStruct);

    printf(LOG_PREFIX_CSTR "Struct_FindNotBlockIndexBound -> ");

    /* Init all to zero */
    kdi_Fill_u8((u8 *)buf, sizeof(buf), 0);

    /* Set target pattern to match (zero struct) */
    kdi_Fill_u8((u8 *)&blk, sizeof(blk), 0);

    /* Set buf[2] to something else */
    buf[2].a = 0x12345678;

    /* Search for NOT zero-struct.
     * 0: Zero == Zero.
     * 1: Zero == Zero.
     * 2: NonZero != Zero. Match 2*sz. */
    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, sizeof(buf), USIZE_C(0), sizeof(buf), &blk, sz);

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(2) * sz);

    printf("PASSED\n");
}


void
MultiByteBlock(void)
{
    u8    buf[30];
    u8    blk[3];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "MultiByteBlock -> ");

    /* Block size 3. Buffer 30. 10 blocks. */
    /* Init to 0x00 */
    kdi_Fill_u8(buf, USIZE_C(30), U8_C(0x00));

    /* Set 4th block (offset 9) to 0xFF */
    kdi_Fill_u8(buf + 9, USIZE_C(3), U8_C(0xFF));

    /* Search for NOT 0x00 block */
    kdi_Fill_u8(blk, USIZE_C(3), U8_C(0x00));

    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(30), USIZE_C(0), USIZE_C(30), blk, USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(9));

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    u8    buf[1024];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    /* Init 0x00 */
    kdi_Fill_u8(buf, USIZE_C(1024), U8_C(0x00));

    /* Set offset 512 to 0xFF */
    kdi_Fill_u8(buf + 512, USIZE_C(4), U8_C(0xFF));

    /* Search NOT 0x00 */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0x00));

    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(1024), USIZE_C(0), USIZE_C(1024), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(512));

    printf("PASSED\n");
}


void
SingleByteBlocks(void)
{
    u8    buf[16];
    u8    blk[1];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleByteBlocks -> ");

    /* Init 0x00 */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));
    /* Set index 5 to 0xFF */
    buf[5] = 0xFF;

    /* Search NOT 0x00 */
    blk[0] = 0x00;

    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16), blk, USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(5));

    printf("PASSED\n");
}


void
AlternatingBlocks(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "AlternatingBlocks -> ");

    /* Alternating 0xAA (block A) and 0x55 (block B) */
    /* Block size 4. */
    for (i = 0; i < 32; i++) {
        buf[i] = ((i / 4) % 2 == 0) ? 0xAA : 0x55;
    }

    /* Blocks:
     * 0: AA AA AA AA
     * 4: 55 55 55 55
     * 8: AA AA AA AA
     * 12: 55 55 55 55
     * ...
     */

    /* Search NOT AA... */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xAA));
    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    /* 0 matches AA. 4 does not. Match 4. */
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(4));

    /* Search NOT 55... */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0x55));
    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    /* 0 is AA != 55. Match 0. */
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    printf("PASSED\n");
}


void
ConsecutiveMatches(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "ConsecutiveMatches -> ");

    /* Init 0x00 */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));

    /* Set 4, 8 to 0xFF */
    kdi_Fill_u8(buf + 4, USIZE_C(4), U8_C(0xFF));
    kdi_Fill_u8(buf + 8, USIZE_C(4), U8_C(0xFF));

    /* Search NOT 0x00 */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0x00));

    /* Start at 0. Match 4. */
    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(4));

    /* Start at 4. Match 4. */
    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(4), USIZE_C(28), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(4));

    /* Start at 8. Match 8. */
    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(8), USIZE_C(24), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(8));

    printf("PASSED\n");
}


void
OddSizes(void)
{
    u8    buf[42];
    u8    blk[3];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "OddSizes -> ");

    /* Block size 3. */
    /* Init 0x00 */
    kdi_Fill_u8(buf, USIZE_C(42), U8_C(0x00));

    /* Set block at 15 (idx 5) to 0xFF */
    kdi_Fill_u8(buf + 15, USIZE_C(3), U8_C(0xFF));

    /* Search NOT 0x00 */
    kdi_Fill_u8(blk, USIZE_C(3), U8_C(0x00));

    /* Range [0, 30). Covers 0, 3, 6, 9, 12, 15, 18, 21, 24, 27.
     * 15 is 0xFF. Match 15. */
    status = kdGenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(42), USIZE_C(0), USIZE_C(30), blk, USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(15));

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
    U16_FindNotBlockIndexBound();
    U32_FindNotBlockIndexBound();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_FindNotBlockIndexBound();
#endif
    Struct_FindNotBlockIndexBound();
    MultiByteBlock();
    LargeBuffer();
    SingleByteBlocks();
    AlternatingBlocks();
    ConsecutiveMatches();
    OddSizes();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
