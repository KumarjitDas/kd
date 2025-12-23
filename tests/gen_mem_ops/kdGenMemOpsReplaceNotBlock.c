/**
 * @file kdGenMemOpsReplaceNotBlock.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsReplaceNotBlock function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsReplaceNotBlock function test"
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

    /* ptr is null -> failure */
    status = GenMemOpsReplaceNotBlock(null, USIZE_C(16), fblk, nblk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr_sz is zero -> failure */
    status = GenMemOpsReplaceNotBlock(buf, USIZE_C(0), fblk, nblk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* find_block is null -> failure */
    status = GenMemOpsReplaceNotBlock(buf, USIZE_C(16), null, nblk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* new_block is null -> failure */
    status = GenMemOpsReplaceNotBlock(buf, USIZE_C(16), fblk, null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = GenMemOpsReplaceNotBlock(buf, USIZE_C(16), fblk, nblk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* block_sz > ptr_sz -> failure */
    status = GenMemOpsReplaceNotBlock(buf, USIZE_C(4), fblk, nblk, USIZE_C(16));
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

    /* All blocks match find_block. None should be replaced. */
    status = GenMemOpsReplaceNotBlock(buf, USIZE_C(16), fblk, nblk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(kdi_VerifyVal(buf, USIZE_C(16), U8_C(0xAA)));

    printf("PASSED\n");
}


void
ReplaceFirstOnly(void)
{
    u8   buf[16];
    u8   fblk[4];
    u8   nblk[4];
    bool status;

    printf(LOG_PREFIX_CSTR "ReplaceFirstOnly -> ");

    /* Init mismatches (buf=0xCC, find=0xAA) */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xCC));
    kdi_FillVal(fblk, 4, 0xAA);
    kdi_FillVal(nblk, 4, 0xBB);

    /* All blocks mismatch.
     * ONLY the first block (Offset 0) should be replaced with nblk (0xBB).
     */
    status = GenMemOpsReplaceNotBlock(buf, USIZE_C(16), fblk, nblk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);

    /* First block replaced */
    assert(buf[0] == 0xBB && buf[1] == 0xBB && buf[2] == 0xBB && buf[3] == 0xBB);

    /* Subsequent blocks untouched (still 0xCC) */
    assert(buf[4] == 0xCC);
    assert(buf[15] == 0xCC);

    printf("PASSED\n");
}


void
ReplaceMixed(void)
{
    u8   buf[32];
    u8   fblk[4];
    u8   nblk[4];
    bool status;

    printf(LOG_PREFIX_CSTR "ReplaceMixed -> ");

    /* Init matches (0xAA) */
    kdi_FillVal(buf, USIZE_C(32), U8_C(0xAA));
    kdi_FillVal(fblk, 4, 0xAA);
    kdi_FillVal(nblk, 4, 0xBB);

    /* Create mismatches at Block Index 1 (Offset 4) and Block Index 3 (Offset 12) */
    kdi_FillVal(buf + 4, 4, 0xCC);  /* Mismatch 1 */
    kdi_FillVal(buf + 12, 4, 0xDD); /* Mismatch 2 */

    /* Should find first mismatch at Offset 4 and replace with nblk (0xBB).
     * Offset 12 should remain 0xDD.
     */
    status = GenMemOpsReplaceNotBlock(buf, USIZE_C(32), fblk, nblk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);

    /* Block 0 (Offset 0) Match -> Untouched */
    assert(buf[0] == 0xAA);

    /* Block 1 (Offset 4) Mismatch -> Replaced with 0xBB */
    assert(buf[4] == 0xBB && buf[7] == 0xBB);

    /* Block 2 (Offset 8) Match -> Untouched */
    assert(buf[8] == 0xAA);

    /* Block 3 (Offset 12) Mismatch -> Ignored (only first replaced) */
    assert(buf[12] == 0xDD);

    printf("PASSED\n");
}


void
ReplaceNotBlock_U16(void)
{
    u16  buf[10];
    u16  fblk = 0xAAAA;
    u16  nblk = 0xBBBB;
    bool status;
    int  i;

    printf(LOG_PREFIX_CSTR "ReplaceNotBlock_U16 -> ");

    /* Init matches */
    for (i = 0; i < 10; ++i)
        buf[i] = fblk;

    /* Mismatches at index 2 and 5 */
    buf[2] = 0xCCCC;
    buf[5] = 0xDDDD;

    status = GenMemOpsReplaceNotBlock(buf, sizeof(buf), &fblk, &nblk, sizeof(u16));

    assert(status == RESULT_SUCCESS);
    /* Index 2 (first mismatch) replaced */
    assert(buf[2] == 0xBBBB);
    /* Index 5 (second mismatch) untouched */
    assert(buf[5] == 0xDDDD);

    printf("PASSED\n");
}


void
ReplaceNotBlock_U32(void)
{
    u32  buf[10];
    u32  fblk = 0x11111111;
    u32  nblk = 0x99999999;
    bool status;
    int  i;

    printf(LOG_PREFIX_CSTR "ReplaceNotBlock_U32 -> ");

    /* Init matches */
    for (i = 0; i < 10; ++i)
        buf[i] = fblk;

    /* Mismatches at index 2 and 5 */
    buf[2] = 0x22222222;
    buf[5] = 0x55555555;

    status = GenMemOpsReplaceNotBlock(buf, sizeof(buf), &fblk, &nblk, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    /* Index 2 replaced */
    assert(buf[2] == 0x99999999);
    /* Index 5 untouched */
    assert(buf[5] == 0x55555555);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
ReplaceNotBlock_U64(void)
{
    u64  buf[10];
    u64  fblk = U64_C(0x1111222233334444);
    u64  nblk = U64_C(0x9999999988888888);
    bool status;
    int  i;

    printf(LOG_PREFIX_CSTR "ReplaceNotBlock_U64 -> ");

    /* Init matches */
    for (i = 0; i < 10; ++i)
        buf[i] = fblk;

    /* Mismatches at index 1 and 3 */
    buf[1] = U64_C(0xFFFFFFFFFFFFFFFF);
    buf[3] = U64_C(0xEEEEEEEEEEEEEEEE);

    status = GenMemOpsReplaceNotBlock(buf, sizeof(buf), &fblk, &nblk, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    /* Index 1 (first mismatch) replaced */
    assert(buf[1] == nblk);
    /* Index 3 (second mismatch) untouched */
    assert(buf[3] == U64_C(0xEEEEEEEEEEEEEEEE));

    printf("PASSED\n");
}
#endif


void
ReplaceNotBlock_Struct(void)
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

    printf(LOG_PREFIX_CSTR "ReplaceNotBlock_Struct -> ");

    for (i = 0; i < 5; ++i)
        buf[i] = fblk;

    /* Mismatch at index 1 */
    buf[1].a = 3;

    /* Mismatch at index 3 */
    buf[3].b = 4;

    status   = GenMemOpsReplaceNotBlock(buf, sizeof(buf), &fblk, &nblk, sizeof(Block));

    assert(status == RESULT_SUCCESS);

    /* Index 1 replaced */
    assert(buf[1].a == 9 && buf[1].b == 9);

    /* Index 3 untouched */
    assert(buf[3].a == 1 && buf[3].b == 4);

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

    status = GenMemOpsReplaceNotBlock(buf, sizeof(buf), fblk, nblk, USIZE_C(10));

    assert(status == RESULT_SUCCESS);

    /* First mismatch replaced */
    assert(buf[70000] == 0xBB);

    /* Second mismatch untouched */
    assert(buf[80000] == 0xDD);

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
    ReplaceFirstOnly();
    ReplaceMixed();

    ReplaceNotBlock_U16();
    ReplaceNotBlock_U32();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    ReplaceNotBlock_U64();
#endif
    ReplaceNotBlock_Struct();
    LargeBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
