/**
 * @file kdGenMemOpsReplaceAllBlocksBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsReplaceAllBlocksBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>
#include <string.h> /* For memcmp */

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsReplaceAllBlocksBound function test"
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
    u8    find_blk[4];
    u8    new_blk[4];
    usize count = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* base is null -> failure */
    status = GenMemOpsReplaceAllBlocksBound(null, USIZE_C(16), 0, 16, &count, find_blk, new_blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = GenMemOpsReplaceAllBlocksBound(buf, USIZE_C(0), 0, 0, &count, find_blk, new_blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* count pointer is null -> failure */
    status = GenMemOpsReplaceAllBlocksBound(buf, USIZE_C(16), 0, 16, null, find_blk, new_blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* find_block is null -> failure */
    status = GenMemOpsReplaceAllBlocksBound(buf, USIZE_C(16), 0, 16, &count, null, new_blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* new_block is null -> failure */
    status = GenMemOpsReplaceAllBlocksBound(buf, USIZE_C(16), 0, 16, &count, find_blk, null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = GenMemOpsReplaceAllBlocksBound(buf, USIZE_C(16), 0, 16, &count, find_blk, new_blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* block_sz > base_sz -> failure */
    status = GenMemOpsReplaceAllBlocksBound(buf, USIZE_C(16), 0, 16, &count, find_blk, new_blk, USIZE_C(17));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
StartAlignment(void)
{
    u8    buf[16];
    u8    find_blk[4];
    u8    new_blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "StartAlignment -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));
    kdi_FillVal(find_blk, 4, 0xAA);
    kdi_FillVal(new_blk, 4, 0xBB);

    /* Block size 4. Start index MUST be a multiple of 4. */

    /* Case 1: Start index 1 (Not divisible by 4) -> Failure */
    status = GenMemOpsReplaceAllBlocksBound(buf, USIZE_C(16), 1, 12, &count, find_blk, new_blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Case 2: Start index 2 (Not divisible by 4) -> Failure */
    status = GenMemOpsReplaceAllBlocksBound(buf, USIZE_C(16), 2, 12, &count, find_blk, new_blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Case 3: Start index 4 (Divisible by 4) -> Success */
    status = GenMemOpsReplaceAllBlocksBound(buf, USIZE_C(16), 4, 12, &count, find_blk, new_blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
RangeAlignment(void)
{
    u8    buf[16];
    u8    find_blk[4];
    u8    new_blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "RangeAlignment -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));
    kdi_FillVal(find_blk, 4, 0xAA);
    kdi_FillVal(new_blk, 4, 0xBB);

    /* Case 1: Count 5 (Not divisible by 4) -> Success */
    status = GenMemOpsReplaceAllBlocksBound(buf, USIZE_C(16), 0, 5, &count, find_blk, new_blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Case 2: Count 6 (Not divisible by 4) -> Success */
    status = GenMemOpsReplaceAllBlocksBound(buf, USIZE_C(16), 0, 6, &count, find_blk, new_blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Case 3: Count 4 (Divisible by 4) -> Success */
    status = GenMemOpsReplaceAllBlocksBound(buf, USIZE_C(16), 0, 4, &count, find_blk, new_blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
EndValueClamping(void)
{
    u8    buf[16];
    u8    find_blk[4];
    u8    new_blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "EndValueClamping -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Target at last valid block position: Offset 12 */
    kdi_FillVal(buf + 12, 4, 0xAA);

    kdi_FillVal(find_blk, 4, 0xAA);
    kdi_FillVal(new_blk, 4, 0xBB);

    /* Requesting count 100 bytes starting at 0.
     * 100 > base_sz (16).
     * Should be clamped to 16.
     * 16 % 4 == 0. Valid alignment.
     * Effective Range: [0, 16).
     */
    status = GenMemOpsReplaceAllBlocksBound(buf, USIZE_C(16), 0, 100, &count, find_blk, new_blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);

    /* Should find the block at 12 */
    /* 1 block replaced * 4 bytes = 4 */
    assert(count == 4);
    assert(memcmp(buf + 12, new_blk, 4) == 0);

    printf("PASSED\n");
}


void
ReplaceNone(void)
{
    u8    buf[16];
    u8    find_blk[4];
    u8    new_blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ReplaceNone -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    kdi_FillVal(find_blk, USIZE_C(4), U8_C(0xFF));
    kdi_FillVal(new_blk, USIZE_C(4), U8_C(0xAA));

    /* Start 0, Count 16. Range [0, 16). */
    status = GenMemOpsReplaceAllBlocksBound(buf, USIZE_C(16), 0, 16, &count, find_blk, new_blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == 0);

    /* Verify unchanged */
    {
        usize i;
        for (i = 0; i < 16; ++i)
        {
            assert(buf[i] == 0x00);
        }
    }

    printf("PASSED\n");
}


void
RangeConstraints(void)
{
    u8    buf[32];
    u8    find_blk[4];
    u8    new_blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "RangeConstraints -> ");

    kdi_FillVal(buf, USIZE_C(32), U8_C(0x00));

    /* Targets at aligned offsets: 4, 12, 20, 28 */
    kdi_FillVal(buf + 4, 4, 0xAA);
    kdi_FillVal(buf + 12, 4, 0xAA);
    kdi_FillVal(buf + 20, 4, 0xAA);
    kdi_FillVal(buf + 28, 4, 0xAA);

    kdi_FillVal(find_blk, 4, 0xAA);
    kdi_FillVal(new_blk, 4, 0xBB);

    /* Start 8, Count 16.
     * Effective Range: [8, 24).
     * Scan steps (Block 4): 8, 12, 16, 20.
     * Check 8: No Match.
     * Check 12: Match. Replace.
     * Check 16: No Match.
     * Check 20: Match. Replace.
     */
    status = GenMemOpsReplaceAllBlocksBound(buf, USIZE_C(32), 8, 16, &count, find_blk, new_blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    /* 2 blocks * 4 bytes = 8 bytes */
    assert(count == 8);

    /* Verify replacements */
    assert(memcmp(buf + 12, new_blk, 4) == 0);
    assert(memcmp(buf + 20, new_blk, 4) == 0);

    /* Verify exclusions */
    assert(memcmp(buf + 4, find_blk, 4) == 0);  /* Before range */
    assert(memcmp(buf + 28, find_blk, 4) == 0); /* After range */

    printf("PASSED\n");
}


void
ReplaceAtBoundaries(void)
{
    u8    buf[16];
    u8    find_blk[4];
    u8    new_blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ReplaceAtBoundaries -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    kdi_FillVal(find_blk, 4, 0xAA);
    kdi_FillVal(new_blk, 4, 0xBB);

    /* Offset 0 */
    kdi_FillVal(buf, 4, 0xAA);
    /* Offset 4 */
    kdi_FillVal(buf + 4, 4, 0xAA);
    /* Offset 8 */
    kdi_FillVal(buf + 8, 4, 0xAA);

    /* Start 0, Count 8. Range [0, 8).
     * Scan steps: 0, 4.
     */
    status = GenMemOpsReplaceAllBlocksBound(buf, USIZE_C(16), 0, 8, &count, find_blk, new_blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    /* 2 blocks * 4 bytes = 8 bytes */
    assert(count == 8);

    assert(memcmp(buf, new_blk, 4) == 0);
    assert(memcmp(buf + 4, new_blk, 4) == 0);
    assert(memcmp(buf + 8, find_blk, 4) == 0); /* Untouched (Excluded) */

    printf("PASSED\n");
}


void
UnalignedMatchIgnored(void)
{
    u8    buf[10];
    u8    find_blk[2];
    u8    new_blk[2];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "UnalignedMatchIgnored -> ");

    kdi_FillVal(buf, USIZE_C(10), U8_C(0x00));

    /* Target at offset 3 */
    buf[3]      = 0xAA;
    buf[4]      = 0xBB;

    find_blk[0] = 0xAA;
    find_blk[1] = 0xBB;
    kdi_FillVal(new_blk, 2, 0x99);

    /* Start 0, Count 6. Range [0, 6).
     * Scan steps (Block 2): 0, 2, 4.
     * Actual block is at 3.
     * 3 is NOT in the set {0, 2, 4}.
     * It will be skipped.
     */
    status = GenMemOpsReplaceAllBlocksBound(buf, USIZE_C(10), 0, 6, &count, find_blk, new_blk, USIZE_C(2));

    assert(status == RESULT_SUCCESS);
    assert(count == 0);
    assert(memcmp(buf + 3, find_blk, 2) == 0); /* Unchanged */

    printf("PASSED\n");
}


void
ReplaceAllBlocksBound_U16(void)
{
    u16   buf[10];
    u16   find_blk = 0xAAAA;
    u16   new_blk  = 0xBBBB;
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ReplaceAllBlocksBound_U16 -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    buf[1] = 0xAAAA;
    buf[3] = 0xAAAA;
    buf[5] = 0xAAAA;

    /* Start 2 bytes (Index 1), Count 6 bytes (3 elements).
     * Block size 2. Start 2 is aligned. Count 6 is aligned.
     * Range [2, 8).
     * Scan steps: 2 (Index 1), 4 (Index 2), 6 (Index 3).
     * Match at Index 1? Yes. Replace.
     * Match at Index 2? No.
     * Match at Index 3? Yes. Replace.
     */
    status = GenMemOpsReplaceAllBlocksBound(buf, sizeof(buf), 2, 6, &count, &find_blk, &new_blk, sizeof(u16));

    assert(status == RESULT_SUCCESS);
    /* 2 blocks * 2 bytes = 4 */
    assert(count == 4);

    assert(buf[1] == 0xBBBB);
    assert(buf[3] == 0xBBBB);
    assert(buf[5] == 0xAAAA); /* Outside range */

    printf("PASSED\n");
}


void
ReplaceAllBlocksBound_U32(void)
{
    u32   buf[10];
    u32   find_blk = 0x12345678;
    u32   new_blk  = 0x87654321;
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ReplaceAllBlocksBound_U32 -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    buf[0] = find_blk;
    buf[1] = find_blk;

    /* Start 0, Count 80.
     * 80 > Base Size (40). Clamped to 40.
     * 40 % 4 == 0. Valid.
     */
    status = GenMemOpsReplaceAllBlocksBound(buf, sizeof(buf), 0, 80, &count, &find_blk, &new_blk, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    /* 2 blocks * 4 bytes = 8 */
    assert(count == 8);

    assert(buf[0] == new_blk);
    assert(buf[1] == new_blk);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
ReplaceAllBlocksBound_U64(void)
{
    u64   buf[10];
    u64   find_blk = U64_C(0x1111222233334444);
    u64   new_blk  = U64_C(0xAAAABBBBCCCCDDDD);
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ReplaceAllBlocksBound_U64 -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    buf[2] = find_blk;
    buf[4] = find_blk;

    /* Start 16 (Index 2), Count 100.
     * 100 > Base Size (80). Clamped to 80.
     * 80 % 8 == 0. Valid.
     */
    status = GenMemOpsReplaceAllBlocksBound(buf, sizeof(buf), 16, 100, &count, &find_blk, &new_blk, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    /* 2 blocks * 8 bytes = 16 */
    assert(count == 16);

    assert(buf[2] == new_blk);
    assert(buf[4] == new_blk);

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
ReplaceAllBlocksBound_Struct(void)
{
    /* Struct 24 bytes. */
    kdi_TestStruct buf[5];
    kdi_TestStruct find_blk;
    kdi_TestStruct new_blk;
    usize          count;
    bool           status;

    printf(LOG_PREFIX_CSTR "ReplaceAllBlocksBound_Struct -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    find_blk.a = 1;
    find_blk.b = 2;
    find_blk.c = 3;
    new_blk.a  = 9;
    new_blk.b  = 8;
    new_blk.c  = 7;

    buf[1]     = find_blk; /* Offset 24 */
    buf[2]     = find_blk; /* Offset 48 */

    /* Start 24, Count 48.
     * Range [24, 72).
     * Includes Offset 24.
     * Includes Offset 48.
     */
    status     = GenMemOpsReplaceAllBlocksBound(buf, sizeof(buf), 24, 48, &count, &find_blk, &new_blk, sizeof(kdi_TestStruct));

    assert(status == RESULT_SUCCESS);

    /* 2 blocks * 24 bytes = 48 bytes */
    assert(count == 48);

    assert(memcmp(&buf[1], &new_blk, sizeof(kdi_TestStruct)) == 0);
    assert(memcmp(&buf[2], &new_blk, sizeof(kdi_TestStruct)) == 0);

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    static u8 buf[2000];
    u8        find_blk[5];
    u8        new_blk[5];
    usize     count;
    bool      status;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    kdi_FillVal(buf, USIZE_C(2000), U8_C(0x00));

    kdi_FillVal(buf + 100, 5, 0x77);
    kdi_FillVal(buf + 1000, 5, 0x77);

    kdi_FillVal(find_blk, 5, 0x77);
    kdi_FillVal(new_blk, 5, 0x88);

    /* Start 500, Count 1000.
     * Range [500, 1500).
     * Excludes 100.
     * Includes 1000.
     */
    status = GenMemOpsReplaceAllBlocksBound(buf, USIZE_C(2000), 500, 1000, &count, find_blk, new_blk, USIZE_C(5));

    assert(status == RESULT_SUCCESS);
    /* 1 block * 5 bytes = 5 */
    assert(count == 5);

    assert(memcmp(buf + 1000, new_blk, 5) == 0);
    assert(memcmp(buf + 100, find_blk, 5) == 0);

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
    RangeAlignment();
    EndValueClamping();
    ReplaceNone();
    RangeConstraints();
    ReplaceAtBoundaries();
    UnalignedMatchIgnored();

    ReplaceAllBlocksBound_U16();
    ReplaceAllBlocksBound_U32();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    ReplaceAllBlocksBound_U64();
#endif
    ReplaceAllBlocksBound_Struct();

    LargeBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
