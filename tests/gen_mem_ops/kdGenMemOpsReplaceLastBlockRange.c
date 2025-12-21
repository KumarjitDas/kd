/**
 * @file kdGenMemOpsReplaceLastBlockRange.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsReplaceLastBlockRange function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>
#include <string.h> /* For memcmp */

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsReplaceLastBlockRange function test"
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
    u8   buf[16];
    u8   find_blk[4];
    u8   new_blk[4];
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* base is null -> failure */
    status = GenMemOpsReplaceLastBlockRange(null, USIZE_C(16), 0, 16, find_blk, new_blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = GenMemOpsReplaceLastBlockRange(buf, USIZE_C(0), 0, 0, find_blk, new_blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* find_block is null -> failure */
    status = GenMemOpsReplaceLastBlockRange(buf, USIZE_C(16), 0, 16, null, new_blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* new_block is null -> failure */
    status = GenMemOpsReplaceLastBlockRange(buf, USIZE_C(16), 0, 16, find_blk, null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = GenMemOpsReplaceLastBlockRange(buf, USIZE_C(16), 0, 16, find_blk, new_blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* block_sz > base_sz -> failure */
    status = GenMemOpsReplaceLastBlockRange(buf, USIZE_C(16), 0, 16, find_blk, new_blk, USIZE_C(17));
    assert(status == RESULT_FAILURE);

    /* begin > end -> failure */
    status = GenMemOpsReplaceLastBlockRange(buf, USIZE_C(16), 10, 5, find_blk, new_blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* end > base_sz -> failure */
    status = GenMemOpsReplaceLastBlockRange(buf, USIZE_C(16), 0, 17, find_blk, new_blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
StartAlignment(void)
{
    u8   buf[16];
    u8   find_blk[4];
    u8   new_blk[4];
    bool status;

    printf(LOG_PREFIX_CSTR "StartAlignment -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));
    kdi_FillVal(find_blk, 4, 0xAA);
    kdi_FillVal(new_blk, 4, 0xBB);

    /* Block size 4 */

    /* Case 1: Start index 1 (Not divisible by 4) -> Failure */
    status = GenMemOpsReplaceLastBlockRange(buf, USIZE_C(16), 1, 13, find_blk, new_blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Case 2: Start index 2 (Not divisible by 4) -> Failure */
    status = GenMemOpsReplaceLastBlockRange(buf, USIZE_C(16), 2, 14, find_blk, new_blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Case 3: Start index 3 (Not divisible by 4) -> Failure */
    status = GenMemOpsReplaceLastBlockRange(buf, USIZE_C(16), 3, 15, find_blk, new_blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Case 4: Start index 4 (Divisible by 4) -> Success */
    status = GenMemOpsReplaceLastBlockRange(buf, USIZE_C(16), 4, 16, find_blk, new_blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
RangeAlignment(void)
{
    u8   buf[16];
    u8   find_blk[4];
    u8   new_blk[4];
    bool status;

    printf(LOG_PREFIX_CSTR "RangeAlignment -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));
    kdi_FillVal(find_blk, 4, 0xAA);
    kdi_FillVal(new_blk, 4, 0xBB);

    /* Block size 4 */

    /* Case 1: Length 5 (Not divisible by 4) -> Failure */
    status = GenMemOpsReplaceLastBlockRange(buf, USIZE_C(16), 0, 5, find_blk, new_blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Case 2: Length 6 (Not divisible by 4) -> Failure */
    status = GenMemOpsReplaceLastBlockRange(buf, USIZE_C(16), 0, 6, find_blk, new_blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Case 3: Length 4 (Divisible by 4) -> Success */
    status = GenMemOpsReplaceLastBlockRange(buf, USIZE_C(16), 4, 8, find_blk, new_blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
ReplaceNone(void)
{
    u8   buf[16];
    u8   find_blk[4];
    u8   new_blk[4];
    bool status;

    printf(LOG_PREFIX_CSTR "ReplaceNone -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    kdi_FillVal(find_blk, USIZE_C(4), U8_C(0xFF));
    kdi_FillVal(new_blk, USIZE_C(4), U8_C(0xAA));

    status = GenMemOpsReplaceLastBlockRange(buf, USIZE_C(16), 0, 16, find_blk, new_blk, USIZE_C(4));

    /* Returns SUCCESS if valid args but nothing found/replaced */
    assert(status == RESULT_SUCCESS);

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
    u8   buf[32];
    u8   find_blk[4];
    u8   new_blk[4];
    bool status;

    printf(LOG_PREFIX_CSTR "RangeConstraints -> ");

    kdi_FillVal(buf, USIZE_C(32), U8_C(0x00));

    /* Targets at 4, 12, 20, 28 */
    kdi_FillVal(buf + 4, 4, 0xAA);
    kdi_FillVal(buf + 12, 4, 0xAA);
    kdi_FillVal(buf + 20, 4, 0xAA);
    kdi_FillVal(buf + 28, 4, 0xAA);

    kdi_FillVal(find_blk, 4, 0xAA);
    kdi_FillVal(new_blk, 4, 0xBB);

    /* Range [8, 24).
     * Includes offset 12.
     * Includes offset 20.
     * Excludes 4 (before).
     * Excludes 28 (after).
     *
     * Should replace the LAST one found in range: Offset 20.
     */
    status = GenMemOpsReplaceLastBlockRange(buf, USIZE_C(32), 8, 24, find_blk, new_blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);

    /* Verify 20 is replaced */
    assert(memcmp(buf + 20, new_blk, 4) == 0);

    /* Verify others are unchanged */
    assert(memcmp(buf + 4, find_blk, 4) == 0);
    assert(memcmp(buf + 12, find_blk, 4) == 0); /* 12 was in range but was not the last */
    assert(memcmp(buf + 28, find_blk, 4) == 0);

    printf("PASSED\n");
}


void
ReplaceAtBoundaries(void)
{
    u8   buf[16];
    u8   find_blk[2];
    u8   new_blk[2];
    bool status;

    printf(LOG_PREFIX_CSTR "ReplaceAtBoundaries -> ");

    /* Case 1: Target at 'begin' */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));
    kdi_FillVal(buf + 4, 2, 0xAA);

    kdi_FillVal(find_blk, 2, 0xAA);
    kdi_FillVal(new_blk, 2, 0xBB);

    /* Range [4, 10). Length 6. Only one match at start. */
    status = GenMemOpsReplaceLastBlockRange(buf, USIZE_C(16), 4, 10, find_blk, new_blk, USIZE_C(2));
    assert(status == RESULT_SUCCESS);
    assert(memcmp(buf + 4, new_blk, 2) == 0);

    /* Case 2: Target just before 'end' */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));
    /* Range [4, 10). Steps: 4, 6, 8. Target at 8. */
    kdi_FillVal(buf + 8, 2, 0xAA);

    status = GenMemOpsReplaceLastBlockRange(buf, USIZE_C(16), 4, 10, find_blk, new_blk, USIZE_C(2));
    assert(status == RESULT_SUCCESS);
    assert(memcmp(buf + 8, new_blk, 2) == 0);

    printf("PASSED\n");
}


void
UnalignedMatchFail(void)
{
    u8   buf[10];
    u8   find_blk[2];
    u8   new_blk[2];
    bool status;

    printf(LOG_PREFIX_CSTR "UnalignedMatchFail -> ");

    /* Buffer: 00 11 22 33 ... */
    kdi_FillVal(buf, USIZE_C(10), U8_C(0x00));

    /* Target at offset 3 */
    buf[3]      = 0xAA;
    buf[4]      = 0xBB;

    find_blk[0] = 0xAA;
    find_blk[1] = 0xBB;
    kdi_FillVal(new_blk, 2, 0x99);

    /* Range [0, 6). Length 6 (Multiple of 2). Valid.
     * Offsets checked: 0, 2, 4.
     * Actual block at 3.
     * 3 is unaligned relative to start 0 (3%2 != 0).
     * Should fail to find/replace.
     */
    status = GenMemOpsReplaceLastBlockRange(buf, USIZE_C(10), 0, 6, find_blk, new_blk, USIZE_C(2));

    assert(status == RESULT_SUCCESS);          /* Call OK */
    assert(memcmp(buf + 3, find_blk, 2) == 0); /* Unchanged */

    printf("PASSED\n");
}


void
ReplaceLastBlockRange_U16(void)
{
    u16  buf[20];
    u16  find_blk = 0xAAAA;
    u16  new_blk  = 0xBBBB;
    bool status;

    printf(LOG_PREFIX_CSTR "ReplaceLastBlockRange_U16 -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    /* Targets at index 2 (offset 4), 5 (offset 10), 8 (offset 16) */
    buf[2] = 0xAAAA;
    buf[5] = 0xAAAA;
    buf[8] = 0xAAAA;

    /* Range [4, 14). Length 10 (Multiple of 2).
     * Includes offset 4 (Index 2).
     * Includes offset 10 (Index 5).
     * Excludes offset 16 (Index 8).
     *
     * Last match inside range is Index 5.
     */
    status = GenMemOpsReplaceLastBlockRange(buf, sizeof(buf), 4, 14, &find_blk, &new_blk, sizeof(u16));

    assert(status == RESULT_SUCCESS);

    /* Verify index 5 replaced */
    assert(buf[5] == 0xBBBB);

    /* Verify index 2 unchanged (valid but not last) */
    assert(buf[2] == 0xAAAA);
    /* Verify index 8 unchanged (out of range) */
    assert(buf[8] == 0xAAAA);

    printf("PASSED\n");
}


void
ReplaceLastBlockRange_U32(void)
{
    u32  buf[20];
    u32  find_blk = 0x11223344;
    u32  new_blk  = 0x99887766;
    bool status;

    printf(LOG_PREFIX_CSTR "ReplaceLastBlockRange_U32 -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    /* Target at index 3 (offset 12) */
    buf[3]  = find_blk;
    /* Target at index 10 (offset 40) */
    buf[10] = find_blk;

    /* Range [0, 80). Length 80 (Multiple of 4). Replace last. */
    status  = GenMemOpsReplaceLastBlockRange(buf, sizeof(buf), 0, 80, &find_blk, &new_blk, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    assert(buf[10] == new_blk); /* Last */
    assert(buf[3] == find_blk); /* First */

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
ReplaceLastBlockRange_U64(void)
{
    u64  buf[20];
    u64  find_blk = U64_C(0xAAABBBCCCDDDEEE);
    u64  new_blk  = U64_C(0x111222333444555);
    bool status;

    printf(LOG_PREFIX_CSTR "ReplaceLastBlockRange_U64 -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    buf[2] = find_blk;
    buf[4] = find_blk;

    /* Range [16, 96). Length 80 (Multiple of 8).
     * Index 2 is offset 16. Fits.
     * Index 4 is offset 32. Fits.
     * Replace last -> Index 4.
     */
    status = GenMemOpsReplaceLastBlockRange(buf, sizeof(buf), 16, 96, &find_blk, &new_blk, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    assert(buf[4] == new_blk);
    assert(buf[2] == find_blk);

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
ReplaceLastBlockRange_Struct(void)
{
    /* Struct 24 bytes. */
    kdi_TestStruct buf[10];
    kdi_TestStruct find_blk;
    kdi_TestStruct new_blk;
    bool           status;

    printf(LOG_PREFIX_CSTR "ReplaceLastBlockRange_Struct -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    find_blk.a = 1;
    find_blk.b = 2;
    find_blk.c = 3;
    new_blk.a  = 9;
    new_blk.b  = 8;
    new_blk.c  = 7;

    /* Index 1 (Offset 24) */
    buf[1]     = find_blk;
    /* Index 2 (Offset 48) */
    buf[2]     = find_blk;

    /* Range [24, 240). Length 216. Aligned.
     * Includes both. Replace last (Index 2).
     */
    status     = GenMemOpsReplaceLastBlockRange(buf, sizeof(buf), 24, 240, &find_blk, &new_blk, sizeof(kdi_TestStruct));

    assert(status == RESULT_SUCCESS);

    assert(memcmp(&buf[2], &new_blk, sizeof(kdi_TestStruct)) == 0);
    assert(memcmp(&buf[1], &find_blk, sizeof(kdi_TestStruct)) == 0);

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    static u8 buf[2000];
    u8        find_blk[5];
    u8        new_blk[5];
    bool      status;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    kdi_FillVal(buf, USIZE_C(2000), U8_C(0x00));

    kdi_FillVal(buf + 100, 5, 0x77);
    kdi_FillVal(buf + 1000, 5, 0x77);

    kdi_FillVal(find_blk, 5, 0x77);
    kdi_FillVal(new_blk, 5, 0x88);

    /* Range [50, 1500). Length 1450 (Multiple of 5).
     * Includes 100.
     * Includes 1000.
     * Replace Last -> 1000.
     */
    status = GenMemOpsReplaceLastBlockRange(buf, USIZE_C(2000), 50, 1500, find_blk, new_blk, USIZE_C(5));

    assert(status == RESULT_SUCCESS);
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
    ReplaceNone();
    RangeConstraints();
    ReplaceAtBoundaries();
    UnalignedMatchFail();

    ReplaceLastBlockRange_U16();
    ReplaceLastBlockRange_U32();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    ReplaceLastBlockRange_U64();
#endif
    ReplaceLastBlockRange_Struct();

    LargeBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
