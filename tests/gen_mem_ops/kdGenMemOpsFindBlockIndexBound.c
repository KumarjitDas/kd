/**
 * @file kdGenMemOpsFindBlockIndexBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindBlockIndexBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindBlockIndexBound function test"
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
    status = kdGenMemOpsFindBlockIndexBound(null, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure */
    idx    = 55;
    status = kdGenMemOpsFindBlockIndexBound(&idx, null, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    idx    = 55;
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* begin_idx >= base_sz -> failure */
    idx    = 55;
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(32), USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* end_count_byte is zero -> failure */
    idx    = 55;
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(0), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    idx    = 55;
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* base_sz not divisible by block_sz -> failure */
    idx    = 55;
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(31), USIZE_C(0), USIZE_C(31), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* begin_idx not aligned to block_sz -> failure */
    idx    = 55;
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(3), USIZE_C(29), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Valid arguments - found at index 0 */
    idx    = 55;
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
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

    /* Init: all blocks are [0x00, 0x00, 0x00, 0x00] */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));

    /* Search for [0xFF, 0xFF, 0xFF, 0xFF] in range [0, 32) */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xFF));

    idx    = 999;
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));

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

    /* Search for [0xFF, 0xFF, 0xFF, 0xFF] */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xFF));

    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));

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

    /* Search for [0xFF, 0xFF, 0xFF, 0xFF] */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xFF));

    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));

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

    /* Set target block pattern at various positions */
    /* Block at index 4 */
    buf[4] = 0xAA;
    buf[5] = 0xBB;
    buf[6] = 0xCC;
    buf[7] = 0xDD;

    /* Block at index 12 */
    buf[12] = 0xAA;
    buf[13] = 0xBB;
    buf[14] = 0xCC;
    buf[15] = 0xDD;

    /* Block at index 20 */
    buf[20] = 0xAA;
    buf[21] = 0xBB;
    buf[22] = 0xCC;
    buf[23] = 0xDD;

    blk[0] = 0xAA;
    blk[1] = 0xBB;
    blk[2] = 0xCC;
    blk[3] = 0xDD;

    /* Range [8, 24). Begin_idx=8, end_count_byte=16. Covers blocks at 8, 12, 16, 20.
     * First match at index 12. */
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(8), USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(12));

    /* Range [16, 28). Begin_idx=16, end_count_byte=12. Covers blocks at 16, 20, 24.
     * First match at index 20. */
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(16), USIZE_C(12), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(20));

    /* Range [4, 12). Begin_idx=4, end_count_byte=8. Covers blocks at 4, 8.
     * First match at index 4. */
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(4), USIZE_C(8), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(4));

    /* Range [0, 4). Begin_idx=0, end_count_byte=4. Covers block at 0.
     * No match. */
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(4), blk, USIZE_C(4));
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

    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));

    /* Set last block to target pattern */
    buf[28] = 0xAA;
    buf[29] = 0xBB;
    buf[30] = 0xCC;
    buf[31] = 0xDD;

    blk[0]  = 0xAA;
    blk[1]  = 0xBB;
    blk[2]  = 0xCC;
    blk[3]  = 0xDD;

    /* Requesting 100 bytes starting at 0. Clamps to 32. Range [0, 32). */
    status  = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(100), blk, USIZE_C(4));

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

    /* Init: 0x00 */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));

    /* Set target pattern at indices 4, 12, 20 */
    buf[4]  = 0xFF;
    buf[5]  = 0xEE;
    buf[6]  = 0xDD;
    buf[7]  = 0xCC;

    buf[12] = 0xFF;
    buf[13] = 0xEE;
    buf[14] = 0xDD;
    buf[15] = 0xCC;

    buf[20] = 0xFF;
    buf[21] = 0xEE;
    buf[22] = 0xDD;
    buf[23] = 0xCC;

    blk[0]  = 0xFF;
    blk[1]  = 0xEE;
    blk[2]  = 0xDD;
    blk[3]  = 0xCC;

    /* Range [8, 28). Begin_idx=8, end_count_byte=20. Should skip index 4, find 12 first. */
    status  = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(8), USIZE_C(20), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(12));

    printf("PASSED\n");
}


void
U16_FindBlockIndexBound(void)
{
    u16   buf[8];
    u16   blk[1];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U16_FindBlockIndexBound -> ");

    /* Init: 100, 200, 300, 400, 500, 600, 700, 800 */
    buf[0] = 100;
    buf[1] = 200;
    buf[2] = 300;
    buf[3] = 400;
    buf[4] = 500;
    buf[5] = 600;
    buf[6] = 700;
    buf[7] = 800;

    /* Search for 500 */
    blk[0] = 500;

    /* Range [4, 14). Begin_idx=4 bytes, end_count_byte=10 bytes.
     * Covers indices 2, 3, 4, 5, 6 (bytes 4-13).
     * 500 is at index 4 (byte offset 8). */
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, sizeof(buf), USIZE_C(4), USIZE_C(10), blk, sizeof(u16));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(8));

    /* Search for 200 in range [4, 14). 200 is at byte 2, outside range. */
    blk[0] = 200;
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, sizeof(buf), USIZE_C(4), USIZE_C(10), blk, sizeof(u16));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
U32_FindBlockIndexBound(void)
{
    u32   buf[6];
    u32   blk[1];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_FindBlockIndexBound -> ");

    /* Init: 10, 20, 30, 40, 50, 60 */
    buf[0] = 10;
    buf[1] = 20;
    buf[2] = 30;
    buf[3] = 40;
    buf[4] = 50;
    buf[5] = 60;

    /* Search for 40 */
    blk[0] = 40;

    /* Range [8, 20). Begin_idx=8 bytes, end_count_byte=12 bytes.
     * Covers indices 2, 3, 4 (bytes 8-19).
     * 40 is at index 3 (byte offset 12). */
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, sizeof(buf), USIZE_C(8), USIZE_C(12), blk, sizeof(u32));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(12));

    /* Search for 10 in range [8, 20). 10 is at byte 0, outside range. */
    blk[0] = 10;
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, sizeof(buf), USIZE_C(8), USIZE_C(12), blk, sizeof(u32));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_FindBlockIndexBound(void)
{
    u64   buf[5];
    u64   blk[1];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "U64_FindBlockIndexBound -> ");

    /* Init: A, B, C, D, E */
    buf[0] = U64_C(0x1111111111111111);
    buf[1] = U64_C(0x2222222222222222);
    buf[2] = U64_C(0x3333333333333333);
    buf[3] = U64_C(0x4444444444444444);
    buf[4] = U64_C(0x5555555555555555);

    /* Search for D */
    blk[0] = U64_C(0x4444444444444444);

    /* Range [16, 40). Begin_idx=16 bytes, end_count_byte=24 bytes.
     * Covers indices 2, 3, 4 (bytes 16-39).
     * D is at index 3 (byte offset 24). */
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, sizeof(buf), USIZE_C(16), USIZE_C(24), blk, sizeof(u64));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(24));

    /* Search for A in range [16, 40). A is at byte 0, outside range. */
    blk[0] = U64_C(0x1111111111111111);
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, sizeof(buf), USIZE_C(16), USIZE_C(24), blk, sizeof(u64));
    assert(status == RESULT_FAILURE);

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
Struct_FindBlockIndexBound(void)
{
    kdi_TestStruct buf[5];
    kdi_TestStruct blk;
    usize          idx;
    bool           status;
    usize          sz = sizeof(kdi_TestStruct);

    printf(LOG_PREFIX_CSTR "Struct_FindBlockIndexBound -> ");

    /* Init all to zero */
    kdi_Fill_u8((u8 *)buf, sizeof(buf), 0);

    /* Set target pattern */
    blk.a = 0x12345678;
    blk.b = 0xABCD;
    blk.c = 0xEF;
    blk.d = 0x99;

    /* Set buf[2] to target */
    buf[2] = blk;

    /* Range [sz, 4*sz). Begin_idx=sz, end_count_byte=3*sz.
     * Covers indices 1, 2, 3 (bytes sz to 4*sz-1).
     * Match at index 2 (byte offset 2*sz). */
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, sizeof(buf), sz, USIZE_C(3) * sz, &blk, sz);

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(2) * sz);

    /* Range [0, sz). Begin_idx=0, end_count_byte=sz.
     * Covers index 0 only. No match. */
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, sizeof(buf), USIZE_C(0), sz, &blk, sz);
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
MultiByteBlock(void)
{
    u8    buf[32];
    u8    blk[8];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "MultiByteBlock -> ");

    /* Init: 0x00 */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));

    /* Set 8-byte pattern at index 8 */
    buf[8]  = 0x01;
    buf[9]  = 0x02;
    buf[10] = 0x03;
    buf[11] = 0x04;
    buf[12] = 0x05;
    buf[13] = 0x06;
    buf[14] = 0x07;
    buf[15] = 0x08;

    blk[0]  = 0x01;
    blk[1]  = 0x02;
    blk[2]  = 0x03;
    blk[3]  = 0x04;
    blk[4]  = 0x05;
    blk[5]  = 0x06;
    blk[6]  = 0x07;
    blk[7]  = 0x08;

    /* Range [0, 32). Should find at index 8. */
    status  = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(8));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(8));

    /* Range [16, 32). Begin_idx=16, end_count_byte=16. Block at 8 is outside. */
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(16), USIZE_C(16), blk, USIZE_C(8));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    u8    buf[1024];
    u8    blk[16];
    usize idx;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    /* Init with pattern */
    for (i = 0; i < 1024; ++i)
    {
        buf[i] = (u8)(i % 256);
    }

    /* Create target pattern at index 512 (bytes 512-527) */
    for (i = 0; i < 16; ++i)
    {
        blk[i] = (u8)((512 + i) % 256);
    }

    /* Range [256, 768). Begin_idx=256, end_count_byte=512.
     * Should find pattern at byte 512. */
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(1024), USIZE_C(256), USIZE_C(512), blk, USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(256));

    /* Range [0, 256). Pattern at 512 is outside. */
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(1024), USIZE_C(0), USIZE_C(256), blk, USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    printf("PASSED\n");
}


void
SingleByteBlocks(void)
{
    u8    buf[16];
    u8    blk;
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleByteBlocks -> ");

    /* Init: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 */
    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0));

    /* Search for 7 */
    blk = 7;

    /* Range [4, 12). Begin_idx=4, end_count_byte=8. Covers bytes 4-11.
     * Value 7 is at index 7. */
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(8), &blk, USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(7));

    /* Search for 2 in range [4, 12). Value 2 is at index 2, outside range. */
    blk    = 2;
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(16), USIZE_C(4), USIZE_C(8), &blk, USIZE_C(1));
    assert(status == RESULT_FAILURE);

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

    /* Create alternating pattern: [0xAA]*4, [0x55]*4, [0xAA]*4, [0x55]*4... */
    for (i = 0; i < 32; i += 4)
    {
        kdi_Fill_u8(buf + i, USIZE_C(4), ((i / 4) & 1) ? U8_C(0x55) : U8_C(0xAA));
    }

    /* Search for [0x55]*4 */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0x55));

    /* Range [0, 32). First match at index 4. */
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(4));

    /* Search for [0xAA]*4 in range [8, 24). First match at index 8. */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xAA));
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(8), USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(8));

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

    /* Init: 0x00 */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0x00));

    /* Set pattern [0xFF]*4 at indices 8, 12, 16 (consecutive blocks) */
    kdi_Fill_u8(buf + 8, USIZE_C(12), U8_C(0xFF));

    /* Search for [0xFF]*4 */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xFF));

    /* Range [0, 32). Should find first match at index 8. */
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(0), USIZE_C(32), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(8));

    /* Range [12, 24). Should find match at index 12. */
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(32), USIZE_C(12), USIZE_C(12), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(12));

    printf("PASSED\n");
}


void
OddSizes(void)
{
    u8    buf[33];
    u8    blk[3];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "OddSizes -> ");

    /* Odd buffer size: 33 bytes, block size: 3 bytes (11 blocks) */
    kdi_Fill_u8(buf, USIZE_C(33), U8_C(0x00));

    /* Set pattern at index 15 */
    buf[15] = 0xAA;
    buf[16] = 0xBB;
    buf[17] = 0xCC;

    blk[0]  = 0xAA;
    blk[1]  = 0xBB;
    blk[2]  = 0xCC;

    /* Range [0, 33). Should find at index 15. */
    status  = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(33), USIZE_C(0), USIZE_C(33), blk, USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(15));

    /* Range [18, 33). Begin_idx=18, end_count_byte=15. Pattern at 15 is outside. */
    status = kdGenMemOpsFindBlockIndexBound(&idx, buf, USIZE_C(33), USIZE_C(18), USIZE_C(15), blk, USIZE_C(3));
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
    FindFirst();
    FindLast();
    RangeConstraints();
    EndValueClamping();
    FindMultiple();
    U16_FindBlockIndexBound();
    U32_FindBlockIndexBound();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_FindBlockIndexBound();
#endif
    Struct_FindBlockIndexBound();
    MultiByteBlock();
    LargeBuffer();
    SingleByteBlocks();
    AlternatingBlocks();
    ConsecutiveMatches();
    OddSizes();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
