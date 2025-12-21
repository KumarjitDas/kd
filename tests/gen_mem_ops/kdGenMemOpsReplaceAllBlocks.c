/**
 * @file kdGenMemOpsReplaceAllBlocks.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsReplaceAllBlocks function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>
#include <string.h> /* For memcmp */

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsReplaceAllBlocks function test"
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

    /* ptr is null -> failure */
    status = GenMemOpsReplaceAllBlocks(null, USIZE_C(16), &count, find_blk, new_blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* sz is zero -> failure */
    status = GenMemOpsReplaceAllBlocks(buf, USIZE_C(0), &count, find_blk, new_blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* count is null -> failure */
    status = GenMemOpsReplaceAllBlocks(buf, USIZE_C(16), null, find_blk, new_blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* find_block is null -> failure */
    status = GenMemOpsReplaceAllBlocks(buf, USIZE_C(16), &count, null, new_blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* new_block is null -> failure */
    status = GenMemOpsReplaceAllBlocks(buf, USIZE_C(16), &count, find_blk, null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = GenMemOpsReplaceAllBlocks(buf, USIZE_C(16), &count, find_blk, new_blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* block_sz > sz -> failure */
    status = GenMemOpsReplaceAllBlocks(buf, USIZE_C(16), &count, find_blk, new_blk, USIZE_C(17));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SizeAlignment(void)
{
    u8    buf[16];
    u8    find_blk[4];
    u8    new_blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "SizeAlignment -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));
    kdi_FillVal(find_blk, 4, 0xAA);
    kdi_FillVal(new_blk, 4, 0xBB);

    /* Block size 4 */

    /* Case 1: Size 15 (Not divisible by 4) -> Failure */
    status = GenMemOpsReplaceAllBlocks(buf, USIZE_C(15), &count, find_blk, new_blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Case 2: Size 16 (Divisible by 4) -> Success */
    status = GenMemOpsReplaceAllBlocks(buf, USIZE_C(16), &count, find_blk, new_blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);

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
    kdi_FillVal(find_blk, 4, 0xFF);
    kdi_FillVal(new_blk, 4, 0xAA);

    status = GenMemOpsReplaceAllBlocks(buf, USIZE_C(16), &count, find_blk, new_blk, USIZE_C(4));

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
ReplaceMultipleOccurrences(void)
{
    u8    buf[32];
    u8    find_blk[4];
    u8    new_blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ReplaceMultipleOccurrences -> ");

    kdi_FillVal(buf, USIZE_C(32), U8_C(0x00));

    /* Targets at 0, 8, 16 */
    /* Offsets must be aligned to block_sz (4): 0, 4, 8, 12... */
    kdi_FillVal(buf, 4, 0xAA);      /* Offset 0 */
    kdi_FillVal(buf + 8, 4, 0xAA);  /* Offset 8 */
    kdi_FillVal(buf + 16, 4, 0xAA); /* Offset 16 */

    kdi_FillVal(find_blk, 4, 0xAA);
    kdi_FillVal(new_blk, 4, 0xBB);

    status = GenMemOpsReplaceAllBlocks(buf, USIZE_C(32), &count, find_blk, new_blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);

    /* 3 blocks replaced. Total bytes = 3 * 4 = 12 */
    assert(count == 12);

    /* Verify replacements */
    assert(memcmp(buf, new_blk, 4) == 0);
    assert(memcmp(buf + 8, new_blk, 4) == 0);
    assert(memcmp(buf + 16, new_blk, 4) == 0);

    /* Verify untouched gaps */
    assert(buf[4] == 0x00);
    assert(buf[12] == 0x00);

    printf("PASSED\n");
}


void
ReplaceAllConsecutive(void)
{
    u8    buf[16];
    u8    find_blk[2];
    u8    new_blk[2];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ReplaceAllConsecutive -> ");

    /* Fill entirely with target block */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    kdi_FillVal(find_blk, 2, 0xAA);
    kdi_FillVal(new_blk, 2, 0xBB);

    /* Size 16. Block 2. Total 8 blocks. */
    status = GenMemOpsReplaceAllBlocks(buf, USIZE_C(16), &count, find_blk, new_blk, USIZE_C(2));

    assert(status == RESULT_SUCCESS);

    /* 8 blocks * 2 bytes = 16 bytes replaced */
    assert(count == 16);

    /* Verify all bytes are 0xBB */
    {
        usize i;
        for (i = 0; i < 16; ++i)
        {
            assert(buf[i] == 0xBB);
        }
    }

    printf("PASSED\n");
}


void
UnalignedMatchIgnored(void)
{
    u8    buf[12];
    u8    find_blk[4];
    u8    new_blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "UnalignedMatchIgnored -> ");

    /* Block size 4. Alignment steps: 0, 4, 8. */
    kdi_FillVal(buf, USIZE_C(12), U8_C(0x00));

    /* Place target at offset 2 (Unaligned) */
    kdi_FillVal(buf + 2, 4, 0xAA);

    kdi_FillVal(find_blk, 4, 0xAA);
    kdi_FillVal(new_blk, 4, 0xBB);

    status = GenMemOpsReplaceAllBlocks(buf, USIZE_C(12), &count, find_blk, new_blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);

    /* Should replace 0 bytes because match is not aligned */
    assert(count == 0);

    /* Verify buffer unchanged */
    assert(memcmp(buf + 2, find_blk, 4) == 0);

    printf("PASSED\n");
}


void
ReplaceAllBlocks_U16(void)
{
    u16   buf[10];
    u16   find_blk = 0xAAAA;
    u16   new_blk  = 0xBBBB;
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ReplaceAllBlocks_U16 -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    buf[1] = 0xAAAA;
    buf[3] = 0xAAAA;
    buf[9] = 0xAAAA;

    status = GenMemOpsReplaceAllBlocks(buf, sizeof(buf), &count, &find_blk, &new_blk, sizeof(u16));

    assert(status == RESULT_SUCCESS);

    /* 3 blocks * 2 bytes = 6 bytes */
    assert(count == 6);

    assert(buf[1] == 0xBBBB);
    assert(buf[3] == 0xBBBB);
    assert(buf[9] == 0xBBBB);

    printf("PASSED\n");
}


void
ReplaceAllBlocks_U32(void)
{
    u32   buf[10];
    u32   find_blk = 0x12345678;
    u32   new_blk  = 0x87654321;
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ReplaceAllBlocks_U32 -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    buf[0] = find_blk;
    buf[5] = find_blk;

    status = GenMemOpsReplaceAllBlocks(buf, sizeof(buf), &count, &find_blk, &new_blk, sizeof(u32));

    assert(status == RESULT_SUCCESS);

    /* 2 blocks * 4 bytes = 8 bytes */
    assert(count == 8);

    assert(buf[0] == new_blk);
    assert(buf[5] == new_blk);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
ReplaceAllBlocks_U64(void)
{
    u64   buf[10];
    u64   find_blk = U64_C(0x1111222233334444);
    u64   new_blk  = U64_C(0xAAAABBBBCCCCDDDD);
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "ReplaceAllBlocks_U64 -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    buf[2] = find_blk;
    buf[4] = find_blk;
    buf[8] = find_blk;

    status = GenMemOpsReplaceAllBlocks(buf, sizeof(buf), &count, &find_blk, &new_blk, sizeof(u64));

    assert(status == RESULT_SUCCESS);

    /* 3 blocks * 8 bytes = 24 bytes */
    assert(count == 24);

    assert(buf[2] == new_blk);
    assert(buf[4] == new_blk);
    assert(buf[8] == new_blk);

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
ReplaceAllBlocks_Struct(void)
{
    /* Struct 24 bytes. */
    kdi_TestStruct buf[5];
    kdi_TestStruct find_blk;
    kdi_TestStruct new_blk;
    usize          count;
    bool           status;

    printf(LOG_PREFIX_CSTR "ReplaceAllBlocks_Struct -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    find_blk.a = 1;
    find_blk.b = 2;
    find_blk.c = 3;
    new_blk.a  = 9;
    new_blk.b  = 8;
    new_blk.c  = 7;

    buf[0]     = find_blk;
    buf[4]     = find_blk;

    status     = GenMemOpsReplaceAllBlocks(buf, sizeof(buf), &count, &find_blk, &new_blk, sizeof(kdi_TestStruct));

    assert(status == RESULT_SUCCESS);

    /* 2 blocks * 24 bytes = 48 bytes */
    assert(count == 48);

    assert(memcmp(&buf[0], &new_blk, sizeof(kdi_TestStruct)) == 0);
    assert(memcmp(&buf[4], &new_blk, sizeof(kdi_TestStruct)) == 0);

    /* Middle untouched */
    {
        kdi_TestStruct zero;
        memset(&zero, 0, sizeof(zero));
        assert(memcmp(&buf[2], &zero, sizeof(kdi_TestStruct)) == 0);
    }

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    SizeAlignment();
    ReplaceNone();
    ReplaceMultipleOccurrences();
    ReplaceAllConsecutive();
    UnalignedMatchIgnored();

    ReplaceAllBlocks_U16();
    ReplaceAllBlocks_U32();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    ReplaceAllBlocks_U64();
#endif
    ReplaceAllBlocks_Struct();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
