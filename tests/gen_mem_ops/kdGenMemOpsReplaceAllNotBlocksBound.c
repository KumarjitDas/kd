/**
 * @file kdGenMemOpsReplaceAllNotBlocksBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsReplaceAllNotBlocksBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsReplaceAllNotBlocksBound function test"
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


static bool
kdi_VerifyVal(const u8 *ptr, usize sz, u8 val)
{
    usize i;
    for (i = USIZE_C(0); i < sz; ++i)
    {
        if (ptr[i] != val)
            return false;
    }
    return true;
}


void
BasicArguments(void)
{
    u8    buf[16];
    u8    fblk[4];
    u8    nblk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* base is null -> failure */
    status = GenMemOpsReplaceAllNotBlocksBound(null, USIZE_C(16), 0, 16, &count, fblk, nblk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = GenMemOpsReplaceAllNotBlocksBound(buf, USIZE_C(0), 0, 16, &count, fblk, nblk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* byte_count is null -> failure */
    status = GenMemOpsReplaceAllNotBlocksBound(buf, USIZE_C(16), 0, 16, null, fblk, nblk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* find_block is null -> failure */
    status = GenMemOpsReplaceAllNotBlocksBound(buf, USIZE_C(16), 0, 16, &count, null, nblk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* new_block is null -> failure */
    status = GenMemOpsReplaceAllNotBlocksBound(buf, USIZE_C(16), 0, 16, &count, fblk, null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = GenMemOpsReplaceAllNotBlocksBound(buf, USIZE_C(16), 0, 16, &count, fblk, nblk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* block_sz > base_sz -> failure */
    status = GenMemOpsReplaceAllNotBlocksBound(buf, USIZE_C(4), 0, 4, &count, fblk, nblk, USIZE_C(16));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ReplaceNone(void)
{
    u8    buf[16];
    u8    fblk[4];
    u8    nblk[4];
    usize count = 555;
    bool  status;

    printf(LOG_PREFIX_CSTR "ReplaceNone -> ");

    /* Init matches */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));
    kdi_FillVal(fblk, 4, 0xAA);
    kdi_FillVal(nblk, 4, 0xBB);

    /* Search range [0, 16). All blocks match find_block.
     * None should be replaced.
     */
    status = GenMemOpsReplaceAllNotBlocksBound(buf, USIZE_C(16), 0, 16, &count, fblk, nblk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == 0);
    assert(kdi_VerifyVal(buf, USIZE_C(16), U8_C(0xAA)));

    printf("PASSED\n");
}


void
RangeConstraints(void)
{
    u8    buf[32];
    u8    fblk[4];
    u8    nblk[4];
    usize count = 0;
    bool  status;

    printf(LOG_PREFIX_CSTR "RangeConstraints -> ");

    /* Init matches (0xAA) */
    kdi_FillVal(buf, USIZE_C(32), U8_C(0xAA));
    kdi_FillVal(fblk, 4, 0xAA);
    kdi_FillVal(nblk, 4, 0xBB);

    /* Create mismatches (Not 0xAA) */
    /* Offset 0: Mismatch (Before range) */
    kdi_FillVal(buf, 4, 0x11);

    /* Offset 4: Mismatch (Inside range) */
    kdi_FillVal(buf + 4, 4, 0x22);

    /* Offset 8: Mismatch (Inside range) */
    kdi_FillVal(buf + 8, 4, 0x33);

    /* Offset 12: Mismatch (Inside range check, but let's see)
     * Start 4. Count 10. Range [4, 14).
     * Block 4: [4, 8) -> fits.
     * Block 8: [8, 12) -> fits.
     * Block 12: [12, 16) -> Ends at 16 > 14. Should be IGNORED.
     */
    kdi_FillVal(buf + 12, 4, 0x44);

    /* Offset 20: Mismatch (After range) */
    kdi_FillVal(buf + 20, 4, 0x55);

    /* Search parameters:
     * Start 4, Count 10. Range [4, 14).
     * Valid Blocks: 4, 8.
     * Both are mismatches.
     * Expect 2 blocks replaced * 4 bytes = 8 bytes count.
     */
    status = GenMemOpsReplaceAllNotBlocksBound(buf, USIZE_C(32), 4, 10, &count, fblk, nblk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == 8);

    /* Verify results */
    assert(buf[0] == 0x11);                    /* Before - Untouched */

    assert(buf[4] == 0xBB && buf[7] == 0xBB);  /* Replaced */
    assert(buf[8] == 0xBB && buf[11] == 0xBB); /* Replaced */

    assert(buf[12] == 0x44);                   /* Partial overlap/Outside - Untouched */
    assert(buf[20] == 0x55);                   /* Outside - Untouched */

    printf("PASSED\n");
}


void
EndValueClamping(void)
{
    u8    buf[32];
    u8    fblk[4];
    u8    nblk[4];
    usize count = 0;
    bool  status;

    printf(LOG_PREFIX_CSTR "EndValueClamping -> ");

    kdi_FillVal(buf, USIZE_C(32), U8_C(0xAA));
    kdi_FillVal(fblk, 4, 0xAA);
    kdi_FillVal(nblk, 4, 0xBB);

    /* Mismatches at last valid blocks: Offset 24 and 28 */
    kdi_FillVal(buf + 24, 4, 0xCC);
    kdi_FillVal(buf + 28, 4, 0xDD);

    /* Request range [0, 100).
     * Clamped to [0, 32).
     * Should find and replace blocks at 24 and 28.
     */
    status = GenMemOpsReplaceAllNotBlocksBound(buf, USIZE_C(32), 0, 100, &count, fblk, nblk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    /* 2 blocks * 4 bytes = 8 bytes */
    assert(count == 8);
    assert(buf[24] == 0xBB);
    assert(buf[28] == 0xBB);

    printf("PASSED\n");
}


void
ReplaceAllNotBlocksBound_U16(void)
{
    u16   buf[10];
    u16   fblk  = 0xAAAA;
    u16   nblk  = 0xBBBB;
    usize count = 0;
    bool  status;
    int   i;

    printf(LOG_PREFIX_CSTR "ReplaceAllNotBlocksBound_U16 -> ");

    /* Init matches */
    for (i = 0; i < 10; ++i)
        buf[i] = fblk;

    /* Mismatches at Index 2 (Offset 4) and Index 5 (Offset 10) */
    buf[2] = 0xCCCC;
    buf[6] = 0xDDDD;

    /* Start Offset 4 (Index 2). Count 12 bytes (3 blocks).
     * Indices: 2, 3, 4.
     * Index 2 is mismatch -> Replaced.
     * Index 3 matches -> Untouched.
     * Index 4 matches -> Untouched.
     * Index 5 is outside range (Offset 10, Range ends at 16).
     */
    status = GenMemOpsReplaceAllNotBlocksBound(buf, sizeof(buf), 4, 8, &count, &fblk, &nblk, sizeof(u16));

    assert(status == RESULT_SUCCESS);
    /* 1 block * 2 bytes = 2 bytes */
    assert(count == 2);

    assert(buf[2] == 0xBBBB); /* Replaced */
    assert(buf[6] == 0xDDDD); /* Untouched (outside) */

    printf("PASSED\n");
}


void
ReplaceAllNotBlocksBound_U32(void)
{
    u32   buf[10];
    u32   fblk  = 0x11111111;
    u32   nblk  = 0x99999999;
    usize count = 0;
    bool  status;
    int   i;

    printf(LOG_PREFIX_CSTR "ReplaceAllNotBlocksBound_U32 -> ");

    /* Init matches */
    for (i = 0; i < 10; ++i)
        buf[i] = fblk;

    /* Mismatch at Index 1 (Offset 4) and Index 4 (Offset 16) */
    buf[1] = 0x22222222;
    buf[4] = 0x55555555;

    /* Start Offset 4. Count 16 bytes.
     * Range [4, 20).
     * Stride 4.
     * Checks offsets: 4, 8, 12, 16.
     *
     * Offset 4 (Index 1) is Mismatch -> Replaced.
     * Offset 8 (Index 2) Match -> Untouched.
     * Offset 12 (Index 3) Match -> Untouched.
     * Offset 16 (Index 4) is Mismatch -> Replaced.
     */
    status = GenMemOpsReplaceAllNotBlocksBound(buf, sizeof(buf), 4, 16, &count, &fblk, &nblk, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    /* 2 blocks * 4 bytes = 8 bytes */
    assert(count == 8);

    assert(buf[1] == 0x99999999); /* Replaced */
    assert(buf[4] == 0x99999999); /* Replaced */

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
ReplaceAllNotBlocksBound_U64(void)
{
    u64   buf[10];
    u64   fblk  = U64_C(0x1111222233334444);
    u64   nblk  = U64_C(0x9999999988888888);
    usize count = 0;
    bool  status;
    int   i;

    printf(LOG_PREFIX_CSTR "ReplaceAllNotBlocksBound_U64 -> ");

    /* Init matches */
    for (i = 0; i < 10; ++i)
        buf[i] = fblk;

    /* Mismatch at Index 2 (Offset 16) and Index 3 (Offset 24) */
    buf[2] = U64_C(0xFFFFFFFFFFFFFFFF);
    buf[3] = U64_C(0xEEEEEEEEEEEEEEEE);

    /* Start Offset 0. Stride 8. Full range. */
    status = GenMemOpsReplaceAllNotBlocksBound(buf, sizeof(buf), 0, sizeof(buf), &count, &fblk, &nblk, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    /* 2 blocks * 8 bytes = 16 bytes */
    assert(count == 16);

    assert(buf[2] == nblk);
    assert(buf[3] == nblk);

    printf("PASSED\n");
}
#endif


void
ReplaceAllNotBlocksBound_Struct(void)
{
    typedef struct
    {
        u64 a;
        u64 b;
    } Block;
    Block buf[5];
    Block fblk  = {1, 2};
    Block nblk  = {9, 9};
    usize count = 0;
    bool  status;
    int   i;

    printf(LOG_PREFIX_CSTR "ReplaceAllNotBlocksBound_Struct -> ");

    for (i = 0; i < 5; ++i)
        buf[i] = fblk;

    /* Mismatch at index 1 and 3 */
    buf[1].a = 3;
    buf[3].b = 4;

    /* Start 0, Full Range, Stride sizeof(Block) */
    status   = GenMemOpsReplaceAllNotBlocksBound(buf, sizeof(buf), 0, sizeof(buf), &count, &fblk, &nblk, sizeof(Block));

    assert(status == RESULT_SUCCESS);
    /* 2 blocks * 16 bytes = 32 bytes */
    assert(count == 32);

    /* Index 1 Replaced */
    assert(buf[1].a == 9 && buf[1].b == 9);

    /* Index 3 Replaced */
    assert(buf[3].a == 9 && buf[3].b == 9);

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    static u8 buf[102400];
    u8        fblk[10];
    u8        nblk[10];
    usize     count = 0;
    bool      status;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    /* Init matches */
    kdi_FillVal(buf, sizeof(buf), U8_C(0xAA));
    kdi_FillVal(fblk, 10, 0xAA);
    kdi_FillVal(nblk, 10, 0xBB);

    /* Mismatches at Offset 70000 and 80000 */
    kdi_FillVal(buf + 70000, 10, 0xCC);
    kdi_FillVal(buf + 80000, 10, 0xDD);

    /* Range [0, Full), Stride 10 */
    status = GenMemOpsReplaceAllNotBlocksBound(buf, sizeof(buf), 0, sizeof(buf), &count, fblk, nblk, USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    /* 2 blocks * 10 bytes = 20 bytes */
    assert(count == 20);

    /* Both mismatches replaced */
    assert(buf[70000] == 0xBB);
    assert(buf[80000] == 0xBB);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    ReplaceNone();
    RangeConstraints();
    EndValueClamping();

    ReplaceAllNotBlocksBound_U16();
    ReplaceAllNotBlocksBound_U32();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    ReplaceAllNotBlocksBound_U64();
#endif
    ReplaceAllNotBlocksBound_Struct();
    LargeBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
