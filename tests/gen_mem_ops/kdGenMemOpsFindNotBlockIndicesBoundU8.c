/**
 * @file kdGenMemOpsFindNotBlockIndicesBoundU8.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindNotBlockIndicesBoundU8 function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindNotBlockIndicesBoundU8 function test"
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
    u8    idxs[16];
    usize found = 55;
    bool  status;
    usize idxs_sz = sizeof(idxs);

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* idxs is null -> failure */
    status = GenMemOpsFindNotBlockIndicesBoundU8(null, idxs_sz, &found, buf, USIZE_C(16), 0, 16, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* idxs_sz is zero -> failure */
    status = GenMemOpsFindNotBlockIndicesBoundU8(idxs, USIZE_C(0), &found, buf, USIZE_C(16), 0, 16, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* found pointer is null -> failure */
    status = GenMemOpsFindNotBlockIndicesBoundU8(idxs, idxs_sz, null, buf, USIZE_C(16), 0, 16, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure */
    status = GenMemOpsFindNotBlockIndicesBoundU8(idxs, idxs_sz, &found, null, USIZE_C(16), 0, 16, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = GenMemOpsFindNotBlockIndicesBoundU8(idxs, idxs_sz, &found, buf, USIZE_C(0), 0, 16, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    status = GenMemOpsFindNotBlockIndicesBoundU8(idxs, idxs_sz, &found, buf, USIZE_C(16), 0, 16, null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = GenMemOpsFindNotBlockIndicesBoundU8(idxs, idxs_sz, &found, buf, USIZE_C(16), 0, 16, blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* block_sz > base_sz -> failure */
    status = GenMemOpsFindNotBlockIndicesBoundU8(idxs, idxs_sz, &found, buf, USIZE_C(4), 0, 4, blk, USIZE_C(16));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
FindNone(void)
{
    u8    buf[16];
    u8    blk[4];
    u8    idxs[16];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNone -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));
    kdi_FillVal(blk, 4, 0xAA);

    /* Search range [0, 16). All match. Should find 0 bytes. */
    status = GenMemOpsFindNotBlockIndicesBoundU8(idxs, sizeof(idxs), &found, buf, USIZE_C(16), 0, 16, blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    printf("PASSED\n");
}


void
AlignmentAndStride(void)
{
    u8    buf[32];
    u8    blk[4];
    u8    idxs[16];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "AlignmentAndStride -> ");

    /* Init matches */
    kdi_FillVal(buf, USIZE_C(32), U8_C(0xAA));
    kdi_FillVal(blk, 4, 0xAA);

    /* * Search parameters:
     * begin_idx = 4 (Start offset)
     * block_sz  = 4 (Stride)
     * end_count = 12 (Range length)
     * Range: [4, 16)
     *
     * Expected checks at aligned offsets:
     * 1. 4  (Aligned)
     * 2. 8  (Aligned)
     * 3. 12 (Aligned)
     */

    /* Mismatch at Offset 4 (Valid check) */
    kdi_FillVal(buf + 4, 4, 0xBB);

    /* Mismatch at Offset 8 (Valid check) */
    kdi_FillVal(buf + 8, 4, 0xBB);

    /* Mismatch at Offset 6 (Unaligned stride).
     * Should NOT be detected because check jumps from 4 to 8.
     */
    kdi_FillVal(buf + 6, 4, 0xCC);

    /* Mismatch at Offset 0 (Before range). Should be ignored. */
    kdi_FillVal(buf, 4, 0xBB);

    status = GenMemOpsFindNotBlockIndicesBoundU8(idxs, sizeof(idxs), &found, buf, USIZE_C(32), 4, 12, blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    /* 2 indices * 1 byte = 2 bytes */
    assert(found == 2);
    assert(idxs[0] == 4);
    assert(idxs[1] == 8);

    printf("PASSED\n");
}


void
OutputBufferCapacity(void)
{
    u8    buf[32];
    u8    blk[4];
    u8    idxs[2]; /* Capacity for 2 indices */
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "OutputBufferCapacity -> ");

    kdi_FillVal(buf, USIZE_C(32), U8_C(0xAA));
    kdi_FillVal(blk, 4, 0xAA);

    /* Mismatches at 0, 4, 8 (All aligned 4-byte blocks) */
    kdi_FillVal(buf, 4, 0xBB);
    kdi_FillVal(buf + 4, 4, 0xBB);
    kdi_FillVal(buf + 8, 4, 0xBB);

    /* Search Range [0, 32). Max output 2. */
    status = GenMemOpsFindNotBlockIndicesBoundU8(idxs, sizeof(idxs), &found, buf, USIZE_C(32), 0, 32, blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    /* Found 2 bytes (2 indices) */
    assert(found == 2);
    assert(idxs[0] == 0);
    assert(idxs[1] == 4);
    /* Offset 8 is ignored */

    printf("PASSED\n");
}


void
IndexRangeLimit(void)
{
    u8    buf[300];
    u8    blk[10];
    u8    idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "IndexRangeLimit -> ");

    kdi_FillVal(buf, USIZE_C(300), U8_C(0xAA));
    kdi_FillVal(blk, 10, 0xAA);

    /* Mismatch at Offset 10 (Valid u8, aligned) */
    kdi_FillVal(buf + 10, 10, 0xBB);

    /* Mismatch at Offset 250 (Valid u8, aligned) */
    kdi_FillVal(buf + 250, 10, 0xBB);

    /* Mismatch at Offset 260 (Invalid u8, > 255).
     * Even though it is within the bounds [0, 300),
     * the output array type u8 cannot hold 260.
     * It should be ignored.
     */
    kdi_FillVal(buf + 260, 10, 0xBB);

    status = GenMemOpsFindNotBlockIndicesBoundU8(idxs, sizeof(idxs), &found, buf, USIZE_C(300), 0, 300, blk, USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    /* Should find exactly 2 indices */
    assert(found == 2);
    assert(idxs[0] == 10);
    assert(idxs[1] == 250);

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    /* 100KB buffer test.
     * Verifies that the stride logic works across large distances
     * and high offsets are correctly ignored by u8 output.
     */
    static u8 buf[102400];
    u8        blk[10];
    u8        idxs[10];
    usize     found;
    bool      status;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    kdi_FillVal(buf, sizeof(buf), U8_C(0xAA));
    kdi_FillVal(blk, 10, 0xAA);

    /* Mismatch at low index 100 (Valid u8, aligned) */
    kdi_FillVal(buf + 100, 10, 0xBB);

    /* Mismatch at high index 70000 (Invalid u8) */
    kdi_FillVal(buf + 70000, 10, 0xBB);

    /* Search entire buffer. Stride 10. */
    status = GenMemOpsFindNotBlockIndicesBoundU8(idxs, sizeof(idxs), &found, buf, sizeof(buf), 0, sizeof(buf), blk, USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    /* Should find only index 100 */
    assert(found == 1);
    assert(idxs[0] == 100);

    printf("PASSED\n");
}


void
FindNotBlockIndicesBoundU8_U8(void)
{
    u8    buf[10];
    u8    blk = 0xAA;
    u8    idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndicesBoundU8_U8 -> ");

    kdi_FillVal(buf, sizeof(buf), 0xAA);

    /* Mismatch at Offset 2 and Offset 5 */
    buf[2] = 0xBB;
    buf[5] = 0xCC;

    /* Block size 1 (byte). Stride 1.
     * Search Range [1, 7). 2 and 5 are inside.
     */
    status = GenMemOpsFindNotBlockIndicesBoundU8(idxs, sizeof(idxs), &found, buf, sizeof(buf), 1, 6, &blk, sizeof(u8));

    assert(status == RESULT_SUCCESS);
    assert(found == 2);
    assert(idxs[0] == 2);
    assert(idxs[1] == 5);

    printf("PASSED\n");
}


void
FindNotBlockIndicesBoundU8_U16(void)
{
    u16   buf[10];
    u16   blk = 0xAAAA;
    u8    idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndicesBoundU8_U16 -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);
    {
        int i;
        for (i = 0; i < 10; ++i)
            buf[i] = 0xAAAA;
    }

    /* Mismatches at Index 1 (Offset 2) and Index 8 (Offset 16) */
    buf[1] = 0xBBBB;
    buf[8] = 0xCCCC;

    /* Stride 2. Start 0. Count 20.
     * Checks offsets: 0, 2, 4, ... 18.
     */
    status = GenMemOpsFindNotBlockIndicesBoundU8(idxs, sizeof(idxs), &found, buf, sizeof(buf), 0, 20, &blk, sizeof(u16));

    assert(status == RESULT_SUCCESS);
    assert(found == 2);
    assert(idxs[0] == 2);
    assert(idxs[1] == 16);

    printf("PASSED\n");
}


void
FindNotBlockIndicesBoundU8_U32(void)
{
    u32   buf[10];
    u32   blk = 0x12345678;
    u8    idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndicesBoundU8_U32 -> ");

    {
        int i;
        for (i = 0; i < 10; ++i)
            buf[i] = 0x12345678;
    }

    /* Buffer size 40 bytes.
     * Mismatches at Index 2 (Offset 8) and Index 5 (Offset 20).
     */
    buf[2] = 0x87654321;
    buf[5] = 0x99999999;

    /* Search Range: Start Offset 4, Count 24. Range [4, 28).
     * Block Size (Stride): 4.
     * Checks: 4, 8, 12, 16, 20, 24.
     *
     * Offset 8 is checked -> Mismatch.
     * Offset 20 is checked -> Mismatch.
     */
    status = GenMemOpsFindNotBlockIndicesBoundU8(idxs, sizeof(idxs), &found, buf, sizeof(buf), 4, 24, &blk, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    /* 2 indices * 1 byte = 2 bytes */
    assert(found == 2);
    assert(idxs[0] == 8);
    assert(idxs[1] == 20);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
FindNotBlockIndicesBoundU8_U64(void)
{
    u64   buf[10];
    u64   blk = U64_C(0x1111222233334444);
    u8    idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndicesBoundU8_U64 -> ");

    {
        int i;
        for (i = 0; i < 10; ++i)
            buf[i] = blk;
    }

    /* Mismatch at Index 1 (Offset 8) and Index 3 (Offset 24) */
    buf[1] = U64_C(0xFFFFFFFFFFFFFFFF);
    buf[3] = U64_C(0xEEEEEEEEEEEEEEEE);

    /* Stride 8. Start 0. */
    status = GenMemOpsFindNotBlockIndicesBoundU8(idxs, sizeof(idxs), &found, buf, sizeof(buf), 0, sizeof(buf), &blk, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    assert(found == 2);
    assert(idxs[0] == 8);
    assert(idxs[1] == 24);

    printf("PASSED\n");
}
#endif


void
FindNotBlockIndicesBoundU8_Struct(void)
{
    typedef struct
    {
        u64 a;
        u64 b;
        u64 c;
    } TestStruct;

    TestStruct buf[5];
    TestStruct blk;
    u8         idxs[10];
    usize      found;
    bool       status;
    int        i;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndicesBoundU8_Struct -> ");

    blk.a = 1;
    blk.b = 2;
    blk.c = 3;

    for (i = 0; i < 5; ++i)
        buf[i] = blk;

    /* Mismatch at Index 1.
     * Struct size = 24 bytes.
     * Offset = 24.
     */
    buf[1].a = 99;

    /* Stride 24. Start 0. */
    status   = GenMemOpsFindNotBlockIndicesBoundU8(idxs, sizeof(idxs), &found, buf, sizeof(buf), 0, sizeof(buf), &blk, sizeof(TestStruct));

    assert(status == RESULT_SUCCESS);
    assert(found == 1);
    assert(idxs[0] == 24);

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
    AlignmentAndStride();
    OutputBufferCapacity();
    IndexRangeLimit();
    LargeBuffer();

    FindNotBlockIndicesBoundU8_U8();
    FindNotBlockIndicesBoundU8_U16();
    FindNotBlockIndicesBoundU8_U32();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    FindNotBlockIndicesBoundU8_U64();
#endif
    FindNotBlockIndicesBoundU8_Struct();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
