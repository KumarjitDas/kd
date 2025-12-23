/**
 * @file kdGenMemOpsReplaceAllNotBlocks.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsReplaceAllNotBlocks function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsReplaceAllNotBlocks function test"
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

    /* ptr is null -> failure */
    status = GenMemOpsReplaceAllNotBlocks(null, USIZE_C(16), &count, fblk, nblk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr_sz is zero -> failure */
    status = GenMemOpsReplaceAllNotBlocks(buf, USIZE_C(0), &count, fblk, nblk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* byte_count is null -> failure */
    status = GenMemOpsReplaceAllNotBlocks(buf, USIZE_C(16), null, fblk, nblk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* find_block is null -> failure */
    status = GenMemOpsReplaceAllNotBlocks(buf, USIZE_C(16), &count, null, nblk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* new_block is null -> failure */
    status = GenMemOpsReplaceAllNotBlocks(buf, USIZE_C(16), &count, fblk, null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = GenMemOpsReplaceAllNotBlocks(buf, USIZE_C(16), &count, fblk, nblk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* block_sz > ptr_sz -> failure */
    status = GenMemOpsReplaceAllNotBlocks(buf, USIZE_C(4), &count, fblk, nblk, USIZE_C(16));
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

    /* All blocks match find_block. None should be replaced. */
    status = GenMemOpsReplaceAllNotBlocks(buf, USIZE_C(16), &count, fblk, nblk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == 0);
    assert(kdi_VerifyVal(buf, USIZE_C(16), U8_C(0xAA)));

    printf("PASSED\n");
}


void
ReplaceAll(void)
{
    u8    buf[16];
    u8    fblk[4];
    u8    nblk[4];
    usize count = 0;
    bool  status;

    printf(LOG_PREFIX_CSTR "ReplaceAll -> ");

    /* Init mismatches (buf=0xCC, find=0xAA) */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xCC));
    kdi_FillVal(fblk, 4, 0xAA);
    kdi_FillVal(nblk, 4, 0xBB);

    /* All blocks mismatch. All should be replaced.
     * Total size 16 bytes. Block size 4.
     * 4 blocks replaced * 4 bytes/block = 16 bytes.
     */
    status = GenMemOpsReplaceAllNotBlocks(buf, USIZE_C(16), &count, fblk, nblk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == 16);
    assert(kdi_VerifyVal(buf, USIZE_C(16), U8_C(0xBB)));

    printf("PASSED\n");
}


void
ReplaceMixed(void)
{
    u8    buf[32];
    u8    fblk[4];
    u8    nblk[4];
    usize count = 0;
    bool  status;

    printf(LOG_PREFIX_CSTR "ReplaceMixed -> ");

    /* Init matches (0xAA) */
    kdi_FillVal(buf, USIZE_C(32), U8_C(0xAA));
    kdi_FillVal(fblk, 4, 0xAA);
    kdi_FillVal(nblk, 4, 0xBB);

    /* Create mismatches at Block Index 1 (Offset 4) and Block Index 3 (Offset 12) */
    kdi_FillVal(buf + 4, 4, 0xCC);  /* Mismatch 1 */
    kdi_FillVal(buf + 12, 4, 0xDD); /* Mismatch 2 */

    /* Should replace Offset 4 and Offset 12 with nblk (0xBB).
     * 2 blocks * 4 bytes = 8 bytes replaced.
     */
    status = GenMemOpsReplaceAllNotBlocks(buf, USIZE_C(32), &count, fblk, nblk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == 8);

    /* Block 0 (Offset 0) Match -> Untouched */
    assert(buf[0] == 0xAA);

    /* Block 1 (Offset 4) Mismatch -> Replaced */
    assert(buf[4] == 0xBB && buf[7] == 0xBB);

    /* Block 2 (Offset 8) Match -> Untouched */
    assert(buf[8] == 0xAA);

    /* Block 3 (Offset 12) Mismatch -> Replaced */
    assert(buf[12] == 0xBB && buf[15] == 0xBB);

    printf("PASSED\n");
}


void
ReplaceAllNotBlocks_U16(void)
{
    u16   buf[10];
    u16   fblk  = 0xAAAA;
    u16   nblk  = 0xBBBB;
    usize count = 0;
    bool  status;
    int   i;

    printf(LOG_PREFIX_CSTR "ReplaceAllNotBlocks_U16 -> ");

    /* Init matches */
    for (i = 0; i < 10; ++i)
        buf[i] = fblk;

    /* Mismatches at index 2 and 5 */
    buf[2] = 0xCCCC;
    buf[5] = 0xDDDD;

    status = GenMemOpsReplaceAllNotBlocks(buf, sizeof(buf), &count, &fblk, &nblk, sizeof(u16));

    assert(status == RESULT_SUCCESS);
    /* 2 blocks * 2 bytes = 4 bytes */
    assert(count == 4);
    assert(buf[2] == 0xBBBB);
    assert(buf[5] == 0xBBBB);
    assert(buf[0] == 0xAAAA);

    printf("PASSED\n");
}


void
ReplaceAllNotBlocks_U32(void)
{
    u32   buf[10];
    u32   fblk  = 0x11111111;
    u32   nblk  = 0x99999999;
    usize count = 0;
    bool  status;
    int   i;

    printf(LOG_PREFIX_CSTR "ReplaceAllNotBlocks_U32 -> ");

    /* Init matches */
    for (i = 0; i < 10; ++i)
        buf[i] = fblk;

    /* Mismatches at index 2 and 5 */
    buf[2] = 0x22222222;
    buf[5] = 0x55555555;

    status = GenMemOpsReplaceAllNotBlocks(buf, sizeof(buf), &count, &fblk, &nblk, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    /* 2 blocks * 4 bytes = 8 bytes */
    assert(count == 8);
    assert(buf[2] == 0x99999999);
    assert(buf[5] == 0x99999999);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
ReplaceAllNotBlocks_U64(void)
{
    u64   buf[10];
    u64   fblk  = U64_C(0x1111222233334444);
    u64   nblk  = U64_C(0x9999999988888888);
    usize count = 0;
    bool  status;
    int   i;

    printf(LOG_PREFIX_CSTR "ReplaceAllNotBlocks_U64 -> ");

    /* Init matches */
    for (i = 0; i < 10; ++i)
        buf[i] = fblk;

    /* Mismatches at index 1, 3, 5 */
    buf[1] = U64_C(0xFFFFFFFFFFFFFFFF);
    buf[3] = U64_C(0xEEEEEEEEEEEEEEEE);
    buf[5] = U64_C(0xDDDDDDDDDDDDDDDD);

    status = GenMemOpsReplaceAllNotBlocks(buf, sizeof(buf), &count, &fblk, &nblk, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    /* 3 blocks * 8 bytes = 24 bytes */
    assert(count == 24);
    assert(buf[1] == nblk);
    assert(buf[3] == nblk);
    assert(buf[5] == nblk);

    printf("PASSED\n");
}
#endif


void
ReplaceAllNotBlocks_Struct(void)
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

    printf(LOG_PREFIX_CSTR "ReplaceAllNotBlocks_Struct -> ");

    for (i = 0; i < 5; ++i)
        buf[i] = fblk;

    /* Mismatch at index 1 and 3 */
    buf[1].a = 3;
    buf[3].b = 4;

    status   = GenMemOpsReplaceAllNotBlocks(buf, sizeof(buf), &count, &fblk, &nblk, sizeof(Block));

    assert(status == RESULT_SUCCESS);
    /* 2 blocks * 16 bytes = 32 bytes */
    assert(count == 32);

    assert(buf[1].a == 9 && buf[1].b == 9);
    assert(buf[3].a == 9 && buf[3].b == 9);
    assert(buf[0].a == 1 && buf[0].b == 2);

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

    status = GenMemOpsReplaceAllNotBlocks(buf, sizeof(buf), &count, fblk, nblk, USIZE_C(10));

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
    ReplaceAll();
    ReplaceMixed();

    ReplaceAllNotBlocks_U16();
    ReplaceAllNotBlocks_U32();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    ReplaceAllNotBlocks_U64();
#endif
    ReplaceAllNotBlocks_Struct();
    LargeBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
