/**
 * @file kdGenMemOpsCountNotBlocksBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsCountNotBlocksBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsCountNotBlocksBound function test"
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
    usize count = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* count pointer is null -> failure */
    status = GenMemOpsCountNotBlocksBound(null, buf, USIZE_C(16), 0, 16, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure */
    status = GenMemOpsCountNotBlocksBound(&count, null, USIZE_C(16), 0, 16, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = GenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(0), 0, 16, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    status = GenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(16), 0, 16, null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = GenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(16), 0, 16, blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* block_sz > base_sz -> failure */
    status = GenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(4), 0, 16, blk, USIZE_C(16));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
StartAlignment(void)
{
    u8    buf[16];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "StartAlignment -> ");

    /* Block size 4. Start index MUST be aligned. */

    /* Case 1: Start 1 (1 % 4 != 0) -> Failure */
    status = GenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(16), 1, 12, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Case 2: Start 4 (4 % 4 == 0) -> Success (Arg check pass) */
    kdi_FillVal(buf, 16, 0xAA);
    kdi_FillVal(blk, 4, 0xAA);
    status = GenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(16), 4, 12, blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
CountAlignmentRelaxed(void)
{
    u8    buf[16];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountAlignmentRelaxed -> ");

    /* Block size 4. Count need not be aligned.
     * Only full blocks fitting in the range are checked.
     */

    /* Fill buffer with matches (0xAA) */
    kdi_FillVal(buf, 16, 0xAA);
    kdi_FillVal(blk, 4, 0xAA);

    /* Start 0, Count 7.
     * Blocks fit: floor(7 / 4) = 1 block (Offset 0).
     * Offset 4 requires 8 bytes. 7 is not enough.
     */

    /* Case 1: Mismatch at Offset 0. */
    kdi_FillVal(buf, 4, 0xBB);

    status = GenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(16), 0, 7, blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    /* 1 mismatch * 4 bytes = 4 */
    assert(count == 4);

    /* Case 2: Mismatch at Offset 4.
     * Offset 4 is outside the range [0, 7).
     * Offset 0 matches (restored).
     * Total mismatches should be 0.
     */
    kdi_FillVal(buf, 4, 0xAA);     /* Restore 0 */
    kdi_FillVal(buf + 4, 4, 0xBB); /* Mismatch at 4 */

    status = GenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(16), 0, 7, blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(count == 0);

    printf("PASSED\n");
}


void
EndValueClamping(void)
{
    u8    buf[16];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "EndValueClamping -> ");

    /* Fill with matches (0xAA) */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));
    kdi_FillVal(blk, 4, 0xAA);

    /* Set mismatch at last block (Offset 12) */
    kdi_FillVal(buf + 12, 4, 0xBB);

    /* Requesting 100 bytes starting at 0.
     * Clamps to 16. Range [0, 16).
     * Checks Offsets 0, 4, 8, 12.
     */
    status = GenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(16), 0, 100, blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    /* 1 mismatch * 4 bytes = 4 */
    assert(count == 4);

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

    /* All blocks match 0xAA */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));
    kdi_FillVal(blk, 4, 0xAA);

    /* Count NOT 0xAA blocks. Should be 0. */
    status = GenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(16), 0, 16, blk, USIZE_C(4));

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

    /* All blocks are 0x00. Reference is 0xAA. */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));
    kdi_FillVal(blk, 4, 0xAA);

    /* Count NOT 0xAA blocks. All 4 should be counted. */
    status = GenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(16), 0, 16, blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    /* 4 mismatches * 4 bytes = 16 */
    assert(count == 16);

    printf("PASSED\n");
}


void
RangeConstraints(void)
{
    u8    buf[32];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "RangeConstraints -> ");

    /* Fill buffer with matches (0xAA) */
    kdi_FillVal(buf, USIZE_C(32), U8_C(0xAA));
    kdi_FillVal(blk, 4, 0xAA);

    /* Mismatches at 4, 12, 20, 28 */
    kdi_FillVal(buf + 4, 4, 0xBB);
    kdi_FillVal(buf + 12, 4, 0xBB);
    kdi_FillVal(buf + 20, 4, 0xBB);
    kdi_FillVal(buf + 28, 4, 0xBB);

    /* Start 8, Count 16.
     * Effective Range: [8, 24).
     * Offsets checked: 8, 12, 16, 20.
     * 8: Match.
     * 12: Mismatch (Counted).
     * 16: Match.
     * 20: Mismatch (Counted).
     */
    status = GenMemOpsCountNotBlocksBound(&count, buf, USIZE_C(32), 8, 16, blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    /* 2 mismatches * 4 bytes = 8 */
    assert(count == 8);

    printf("PASSED\n");
}


void
CountNotBlocksBound_U16(void)
{
    u16   buf[10];
    u16   blk = 0xAAAA;
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountNotBlocksBound_U16 -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);
    {
        int i;
        for (i = 0; i < 10; ++i)
            buf[i] = 0xAAAA;
    }

    /* Mismatches at Index 2 and 5 */
    buf[2] = 0xBBBB;
    buf[5] = 0xBBBB;
    buf[8] = 0xBBBB; /* Outside range */

    /* Start 4 bytes (Index 2), Count 12 bytes (6 elements).
     * Range [4, 16).
     * Indices: 2, 3, 4, 5, 6, 7.
     * Mismatches in range: 2 and 5.
     */
    status = GenMemOpsCountNotBlocksBound(&count, buf, sizeof(buf), 4, 12, &blk, sizeof(u16));

    assert(status == RESULT_SUCCESS);
    /* 2 mismatches * 2 bytes = 4 */
    assert(count == 4);

    printf("PASSED\n");
}


void
CountNotBlocksBound_U32(void)
{
    u32   buf[10];
    u32   blk = 0x12345678;
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountNotBlocksBound_U32 -> ");

    {
        int i;
        for (i = 0; i < 10; ++i)
            buf[i] = 0x12345678;
    }

    /* Mismatch at Index 1 and 8 */
    buf[1] = 0x99999999;
    buf[8] = 0x88888888;

    /* Start 0, Count 40. All scanned. */
    status = GenMemOpsCountNotBlocksBound(&count, buf, sizeof(buf), 0, 40, &blk, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    /* 2 mismatches * 4 bytes = 8 */
    assert(count == 8);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
CountNotBlocksBound_U64(void)
{
    u64   buf[10];
    u64   blk = U64_C(0x1111222233334444);
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountNotBlocksBound_U64 -> ");

    {
        int i;
        for (i = 0; i < 10; ++i)
            buf[i] = blk;
    }

    /* All match initially.
     * Mismatches at 2 and 4.
     */
    buf[2] = U64_C(0xFFFFFFFFFFFFFFFF);
    buf[4] = U64_C(0xEEEEEEEEEEEEEEEE);

    /* Start 16, Count 64. Range [16, 80).
     * Scans indices 2 through 9.
     * Mismatches at 2 and 4 are inside.
     */
    status = GenMemOpsCountNotBlocksBound(&count, buf, sizeof(buf), 16, 64, &blk, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    /* 2 mismatches * 8 bytes = 16 */
    assert(count == 16);

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
CountNotBlocksBound_Struct(void)
{
    kdi_TestStruct buf[5];
    kdi_TestStruct blk;
    usize          count;
    bool           status;
    int            i;

    printf(LOG_PREFIX_CSTR "CountNotBlocksBound_Struct -> ");

    blk.a = 1;
    blk.b = 2;
    blk.c = 3;

    for (i = 0; i < 5; ++i)
        buf[i] = blk;

    /* Mismatches at Index 1 and 3 */
    buf[1].a = 99;
    buf[3].a = 88;

    /* Start 0, Count 120. */
    status   = GenMemOpsCountNotBlocksBound(&count, buf, sizeof(buf), 0, 120, &blk, sizeof(kdi_TestStruct));

    assert(status == RESULT_SUCCESS);
    /* 2 mismatches * 24 bytes = 48 */
    assert(count == 48);

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    static u8 buf[8000];
    u8        blk[8];
    usize     count;
    bool      status;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    /* Fill with matches (0xAA) */
    kdi_FillVal(buf, sizeof(buf), 0xAA);
    kdi_FillVal(blk, sizeof(blk), 0xAA);

    /* Mismatches at 1000 and 4000 */
    kdi_FillVal(buf + 1000, 8, 0xBB);
    kdi_FillVal(buf + 4000, 8, 0xCC);

    /* Start 0, Count 8000. Range [0, 8000).
     * Should find both mismatches.
     */
    status = GenMemOpsCountNotBlocksBound(&count, buf, sizeof(buf), 0, 8000, blk, sizeof(blk));

    assert(status == RESULT_SUCCESS);
    /* 2 mismatches * 8 bytes = 16 */
    assert(count == 16);

    /* Start 2000, Count 6000. Range [2000, 8000).
     * Excludes 1000. Includes 4000.
     */
    status = GenMemOpsCountNotBlocksBound(&count, buf, sizeof(buf), 2000, 6000, blk, sizeof(blk));
    assert(status == RESULT_SUCCESS);
    /* 1 mismatch * 8 bytes = 8 */
    assert(count == 8);

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
    CountNone();
    CountAll();
    RangeConstraints();

    CountNotBlocksBound_U16();
    CountNotBlocksBound_U32();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    CountNotBlocksBound_U64();
#endif
    CountNotBlocksBound_Struct();
    LargeBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
