/**
 * @file kdGenMemOpsReplaceLastNotBlockBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsReplaceLastNotBlockBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsReplaceLastNotBlockBound function test"
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
    u8   buf[16];
    u8   fblk[4];
    u8   nblk[4];
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* base is null -> failure */
    status = GenMemOpsReplaceLastNotBlockBound(null, USIZE_C(16), 0, 16, fblk, nblk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = GenMemOpsReplaceLastNotBlockBound(buf, USIZE_C(0), 0, 16, fblk, nblk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* find_block is null -> failure */
    status = GenMemOpsReplaceLastNotBlockBound(buf, USIZE_C(16), 0, 16, null, nblk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* new_block is null -> failure */
    status = GenMemOpsReplaceLastNotBlockBound(buf, USIZE_C(16), 0, 16, fblk, null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = GenMemOpsReplaceLastNotBlockBound(buf, USIZE_C(16), 0, 16, fblk, nblk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* block_sz > base_sz -> failure */
    status = GenMemOpsReplaceLastNotBlockBound(buf, USIZE_C(4), 0, 4, fblk, nblk, USIZE_C(16));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ReplaceNone(void)
{
    u8   buf[16];
    u8   fblk[4];
    u8   nblk[4];
    bool status;

    printf(LOG_PREFIX_CSTR "ReplaceNone -> ");

    /* Init matches */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));
    kdi_FillVal(fblk, 4, 0xAA);
    kdi_FillVal(nblk, 4, 0xBB);

    /* Search range [0, 16). All blocks match find_block.
     * None should be replaced.
     */
    status = GenMemOpsReplaceLastNotBlockBound(buf, USIZE_C(16), 0, 16, fblk, nblk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(kdi_VerifyVal(buf, USIZE_C(16), U8_C(0xAA)));

    printf("PASSED\n");
}


void
RangeConstraints(void)
{
    u8   buf[32];
    u8   fblk[4];
    u8   nblk[4];
    bool status;

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

    /* Offset 8: Mismatch (Inside range - LAST inside) */
    kdi_FillVal(buf + 8, 4, 0x33);

    /* Offset 12: Mismatch (Inside range, but after stride check?
     * Range 10. Start 4.
     * Blocks: [4, 8). [8, 12).
     * Block at 12 starts at 12. 12 < 4+10=14? Yes.
     * Wait, count is 10. End is 14.
     * Block at 8 ends at 12. Fits.
     * Block at 12 ends at 16. 16 > 14. Does not fit completely.
     * So Offset 12 should be ignored.
     */
    kdi_FillVal(buf + 12, 4, 0x44);

    /* Search parameters:
     * Start 4. Count 10. End 14.
     * Valid blocks must fit completely within [4, 14).
     * Block 4: [4, 8) -> Fits.
     * Block 8: [8, 12) -> Fits.
     * Block 12: [12, 16) -> Ends at 16 (>14). Ignored.
     *
     * Mismatches inside: 4 and 8.
     * Last one is 8.
     */
    status = GenMemOpsReplaceLastNotBlockBound(buf, USIZE_C(32), 4, 10, fblk, nblk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);

    /* Verify results */
    assert(buf[0] == 0x11); /* Before - Untouched */
    assert(buf[4] == 0x22); /* Earlier inside - Untouched */

    /* Last valid inside (Offset 8) Replaced */
    assert(buf[8] == 0xBB && buf[11] == 0xBB);

    assert(buf[12] == 0x44); /* Outside - Untouched */

    printf("PASSED\n");
}


void
ReplaceLastOnly(void)
{
    u8   buf[16];
    u8   fblk[4];
    u8   nblk[4];
    bool status;

    printf(LOG_PREFIX_CSTR "ReplaceLastOnly -> ");

    /* Init mismatches (0xCC) */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xCC));
    kdi_FillVal(fblk, 4, 0xAA); /* Looking for NOT 0xAA */
    kdi_FillVal(nblk, 4, 0xBB);

    /* Start 0, Stride 4.
     * Offset 0: Mismatch.
     * Offset 4: Mismatch.
     * Offset 8: Mismatch.
     * Offset 12: Mismatch (Last).
     */
    status = GenMemOpsReplaceLastNotBlockBound(buf, USIZE_C(16), 0, 16, fblk, nblk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);

    /* Earlier blocks untouched */
    assert(buf[0] == 0xCC);
    assert(buf[8] == 0xCC);

    /* Last block replaced */
    assert(buf[12] == 0xBB);

    printf("PASSED\n");
}


void
EndValueClamping(void)
{
    u8   buf[32];
    u8   fblk[4];
    u8   nblk[4];
    bool status;

    printf(LOG_PREFIX_CSTR "EndValueClamping -> ");

    kdi_FillVal(buf, USIZE_C(32), U8_C(0xAA));
    kdi_FillVal(fblk, 4, 0xAA);
    kdi_FillVal(nblk, 4, 0xBB);

    /* Mismatch at last valid block index (Offset 28) */
    kdi_FillVal(buf + 28, 4, 0xCC);

    /* Request range [0, 100).
     * Clamped to [0, 32).
     * Should find and replace the block at 28 (Last valid block).
     */
    status = GenMemOpsReplaceLastNotBlockBound(buf, USIZE_C(32), 0, 100, fblk, nblk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(buf[28] == 0xBB);

    printf("PASSED\n");
}


void
ReplaceLastNotBlockBound_U16(void)
{
    u16  buf[10];
    u16  fblk = 0xAAAA;
    u16  nblk = 0xBBBB;
    bool status;
    int  i;

    printf(LOG_PREFIX_CSTR "ReplaceLastNotBlockBound_U16 -> ");

    /* Init matches */
    for (i = 0; i < 10; ++i)
        buf[i] = fblk;

    /* Mismatch at Index 2 (Offset 4) and Index 5 (Offset 10) */
    buf[2] = 0xCCCC;
    buf[5] = 0xDDDD;

    /* Start Offset 4 (Index 2). Count 12 bytes (3 blocks).
     * Indices: 2, 3, 4.
     * Index 2 is mismatch.
     * Index 5 is outside range (Offset 10, Range ends at 16).
     * * So Last Mismatch inside range is Index 2.
     */
    status = GenMemOpsReplaceLastNotBlockBound(buf, sizeof(buf), 4, 12, &fblk, &nblk, sizeof(u16));

    assert(status == RESULT_SUCCESS);
    assert(buf[2] == 0xCCCC); /* Replaced */
    assert(buf[5] == 0xBBBB); /* Untouched (outside) */

    printf("PASSED\n");
}


void
ReplaceLastNotBlockBound_U32(void)
{
    u32  buf[10];
    u32  fblk = 0x11111111;
    u32  nblk = 0x99999999;
    bool status;
    int  i;

    printf(LOG_PREFIX_CSTR "ReplaceLastNotBlockBound_U32 -> ");

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
     * Offset 4 (Index 1) is Mismatch.
     * Offset 16 (Index 4) is Mismatch.
     * Last mismatch is Offset 16.
     */
    status = GenMemOpsReplaceLastNotBlockBound(buf, sizeof(buf), 4, 16, &fblk, &nblk, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    assert(buf[1] == 0x22222222); /* Untouched (Earlier) */
    assert(buf[4] == 0x99999999); /* Replaced (Last) */

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
ReplaceLastNotBlockBound_U64(void)
{
    u64  buf[10];
    u64  fblk = U64_C(0x1111222233334444);
    u64  nblk = U64_C(0x9999999988888888);
    bool status;
    int  i;

    printf(LOG_PREFIX_CSTR "ReplaceLastNotBlockBound_U64 -> ");

    /* Init matches */
    for (i = 0; i < 10; ++i)
        buf[i] = fblk;

    /* Mismatch at Index 2 (Offset 16) */
    buf[2] = U64_C(0xFFFFFFFFFFFFFFFF);

    /* Start Offset 0. Stride 8. */
    status = GenMemOpsReplaceLastNotBlockBound(buf, sizeof(buf), 0, sizeof(buf), &fblk, &nblk, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    assert(buf[2] == nblk); /* Replaced */

    printf("PASSED\n");
}
#endif


void
ReplaceLastNotBlockBound_Struct(void)
{
    typedef struct
    {
        u64 a;
        u64 b;
    } Block;
    Block buf[5];
    Block fblk = {1, 2};
    Block nblk = {9, 9};
    bool  status;
    int   i;

    printf(LOG_PREFIX_CSTR "ReplaceLastNotBlockBound_Struct -> ");

    for (i = 0; i < 5; ++i)
        buf[i] = fblk;

    /* Mismatch at index 1 and 3 */
    buf[1].a = 3;
    buf[3].b = 4;

    /* Start 0, Full Range, Stride sizeof(Block) */
    status   = GenMemOpsReplaceLastNotBlockBound(buf, sizeof(buf), 0, sizeof(buf), &fblk, &nblk, sizeof(Block));

    assert(status == RESULT_SUCCESS);

    /* Index 1 Untouched */
    assert(buf[1].a == 3);

    /* Index 3 (Last mismatch) replaced */
    assert(buf[3].a == 9 && buf[3].b == 9);

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    static u8 buf[102400];
    u8        fblk[10];
    u8        nblk[10];
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
    status = GenMemOpsReplaceLastNotBlockBound(buf, sizeof(buf), 0, sizeof(buf), fblk, nblk, USIZE_C(10));

    assert(status == RESULT_SUCCESS);

    /* First mismatch untouched */
    assert(buf[70000] == 0xCC);

    /* Last mismatch replaced */
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
    ReplaceLastOnly();
    EndValueClamping();

    ReplaceLastNotBlockBound_U16();
    ReplaceLastNotBlockBound_U32();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    ReplaceLastNotBlockBound_U64();
#endif
    ReplaceLastNotBlockBound_Struct();
    LargeBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
