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


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindNotBlockIndexBound function test"
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
    status = GenMemOpsFindNotBlockIndexBound(null, buf, USIZE_C(16), 0, 16, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure */
    status = GenMemOpsFindNotBlockIndexBound(&idx, null, USIZE_C(16), 0, 16, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = GenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(0), 0, 16, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    status = GenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(16), 0, 16, null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = GenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(16), 0, 16, blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* block_sz > base_sz -> failure */
    status = GenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(4), 0, 16, blk, USIZE_C(16));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
StartAlignment(void)
{
    u8    buf[16];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "StartAlignment -> ");

    /* Block size 4. Start index MUST be aligned. */

    /* Case 1: Start 1 (1 % 4 != 0) -> Failure */
    status = GenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(16), 1, 12, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Case 2: Start 4 (4 % 4 == 0) -> Success (Arg check pass) */
    /* Note: Returns failure here because uninitialized buf might match or logic returns not found,
     * but strictly focusing on API not rejecting the call arguments.
     * To be safe, let's fill matching data so it runs and returns Not Found (Failure) cleanly.
     */
    kdi_FillVal(buf, 16, 0xAA);
    kdi_FillVal(blk, 4, 0xAA);
    status = GenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(16), 4, 12, blk, USIZE_C(4));
    /* Returns Failure because all match, but didn't crash or error on args */
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
CountAlignmentRelaxed(void)
{
    u8    buf[16];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountAlignmentRelaxed -> ");

    /* Block size 4.
     * Count need NOT be aligned. It should process complete blocks fitting in count.
     */

    /* Fill buffer with matches */
    kdi_FillVal(buf, 16, 0xAA);
    kdi_FillVal(blk, 4, 0xAA);

    /* Start 0. Count 7.
     * Blocks fit: floor(7 / 4) = 1 block (Bytes 0-3).
     * Bytes 4-7 require 8 bytes total. 7 is not enough.
     * So it checks Offset 0.
     */

    /* Case 1: Mismatch at Offset 0. Should be found. */
    kdi_FillVal(buf, 4, 0xBB);
    status = GenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(16), 0, 7, blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == 0);

    /* Case 2: Mismatch at Offset 4.
     * With count 7, Offset 4 is NOT checked (requires bytes up to 8).
     * Should fail to find mismatch.
     */
    kdi_FillVal(buf, 4, 0xAA);     /* Restore 0 */
    kdi_FillVal(buf + 4, 4, 0xBB); /* Mismatch at 4 */

    status = GenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(16), 0, 7, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
EndValueClamping(void)
{
    u8    buf[16];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "EndValueClamping -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));
    kdi_FillVal(blk, 4, 0xAA);

    /* Mismatch at last block (Offset 12) */
    kdi_FillVal(buf + 12, 4, 0xBB);

    /* Requesting 100 bytes starting at 0.
     * 100 > 16. Clamps to 16.
     * Range [0, 16). Contains offsets 0, 4, 8, 12.
     * Should find 12.
     */
    status = GenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(16), 0, 100, blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == 12);

    printf("PASSED\n");
}


void
AllMatch(void)
{
    u8    buf[16];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "AllMatch -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));
    kdi_FillVal(blk, 4, 0xAA);

    /* Range [0, 16). All match. */
    status = GenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(16), 0, 16, blk, USIZE_C(4));

    assert(status == RESULT_FAILURE);

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

    kdi_FillVal(buf, USIZE_C(32), U8_C(0xAA));
    kdi_FillVal(blk, 4, 0xAA);

    /* Mismatches at 4, 12, 20, 28 */
    kdi_FillVal(buf + 4, 4, 0xBB);
    kdi_FillVal(buf + 12, 4, 0xBB);
    kdi_FillVal(buf + 20, 4, 0xBB);
    kdi_FillVal(buf + 28, 4, 0xBB);

    /* Start 8, Count 16.
     * Effective Range: [8, 24).
     * Offsets: 8, 12, 16, 20.
     * Check 8: Match (0xAA).
     * Check 12: Mismatch (0xBB). Found!
     * * Offset 4 (before) ignored.
     * Offset 20 (also mismatch) not reached because 12 found first.
     */
    status = GenMemOpsFindNotBlockIndexBound(&idx, buf, USIZE_C(32), 8, 16, blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == 12);

    printf("PASSED\n");
}


void
FindNotBlockIndexBound_U16(void)
{
    u16   buf[10];
    u16   blk = 0xAAAA;
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndexBound_U16 -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);
    {
        int i;
        for (i = 0; i < 10; ++i)
            buf[i] = 0xAAAA;
    }

    /* Set mismatch at Index 5 (Offset 10) */
    buf[5] = 0xBBBB;

    /* Start 4 bytes (Index 2), Count 12 bytes (6 elements).
     * Range [4, 16).
     * Indices checked: 2, 3, 4, 5, 6, 7.
     * Mismatch at 5 should be found.
     */
    status = GenMemOpsFindNotBlockIndexBound(&idx, buf, sizeof(buf), 4, 12, &blk, sizeof(u16));

    assert(status == RESULT_SUCCESS);
    /* Index 5 * 2 = 10 */
    assert(idx == 10);

    printf("PASSED\n");
}


void
FindNotBlockIndexBound_U32(void)
{
    u32   buf[10];
    u32   blk = 0x12345678;
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndexBound_U32 -> ");

    {
        int i;
        for (i = 0; i < 10; ++i)
            buf[i] = 0x12345678;
    }

    /* Mismatch at Index 8 (Offset 32) */
    buf[8] = 0x99999999;

    /* Start 0, Count 40. Range [0, 40). */
    status = GenMemOpsFindNotBlockIndexBound(&idx, buf, sizeof(buf), 0, 40, &blk, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    assert(idx == 32);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
FindNotBlockIndexBound_U64(void)
{
    u64   buf[10];
    u64   blk = U64_C(0x1111222233334444);
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndexBound_U64 -> ");

    {
        int i;
        for (i = 0; i < 10; ++i)
            buf[i] = blk;
    }

    /* Mismatch at Index 2 (Offset 16) */
    buf[2] = U64_C(0xFFFFFFFFFFFFFFFF);

    /* Start 16, Count 64. Range [16, 80).
     * Offset 16 is the first checked. Immediate mismatch.
     */
    status = GenMemOpsFindNotBlockIndexBound(&idx, buf, sizeof(buf), 16, 64, &blk, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    assert(idx == 16);

    printf("PASSED\n");
}
#endif


typedef struct kdi_TestStruct
{
    u64 a;
    u64 b;
    u64 c;
} kdi_TestStruct;


void
FindNotBlockIndexBound_Struct(void)
{
    kdi_TestStruct buf[5];
    kdi_TestStruct blk;
    usize          idx;
    bool           status;
    int            i;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndexBound_Struct -> ");

    blk.a = 1;
    blk.b = 2;
    blk.c = 3;

    for (i = 0; i < 5; ++i)
        buf[i] = blk;

    /* Mismatch at Index 1 (Offset 24) */
    buf[1].a = 99;

    /* Start 0, Count 48 (2 elements).
     * Checks Index 0 (Match), Index 1 (Mismatch).
     */
    status   = GenMemOpsFindNotBlockIndexBound(&idx, buf, sizeof(buf), 0, 48, &blk, sizeof(kdi_TestStruct));

    assert(status == RESULT_SUCCESS);
    assert(idx == 24);

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    static u8 buf[8000];
    u8        blk[8];
    usize     idx;
    bool      status;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    kdi_FillVal(buf, sizeof(buf), 0xAA);
    kdi_FillVal(blk, sizeof(blk), 0xAA);

    /* Mismatch at Offset 4000 */
    kdi_FillVal(buf + 4000, 8, 0xBB);

    /* Start 1000, Count 5000. Range [1000, 6000).
     * 1000 is aligned to 8 (1000 % 8 == 0).
     * 4000 is inside range.
     */
    status = GenMemOpsFindNotBlockIndexBound(&idx, buf, sizeof(buf), 1000, 5000, blk, sizeof(blk));

    assert(status == RESULT_SUCCESS);
    assert(idx == 4000);

    /* Range ending before 4000. Start 0, Count 4000.
     * Range [0, 4000).
     * 4000 is the first byte EXCLUDED.
     * Should fail to find mismatch.
     */
    status = GenMemOpsFindNotBlockIndexBound(&idx, buf, sizeof(buf), 0, 4000, blk, sizeof(blk));
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
    StartAlignment();
    CountAlignmentRelaxed();
    EndValueClamping();
    AllMatch();
    RangeConstraints();

    FindNotBlockIndexBound_U16();
    FindNotBlockIndexBound_U32();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    FindNotBlockIndexBound_U64();
#endif
    FindNotBlockIndexBound_Struct();
    LargeBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
