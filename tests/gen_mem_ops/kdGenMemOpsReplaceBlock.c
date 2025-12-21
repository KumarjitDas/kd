/**
 * @file kdGenMemOpsReplaceBlock.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsReplaceBlock function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>
#include <string.h> /* For memcmp in verification */

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsReplaceBlock function test"
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

    /* ptr is null -> failure */
    status = GenMemOpsReplaceBlock(null, USIZE_C(16), find_blk, new_blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr_sz is zero -> failure */
    status = GenMemOpsReplaceBlock(buf, USIZE_C(0), find_blk, new_blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* find_block is null -> failure */
    status = GenMemOpsReplaceBlock(buf, USIZE_C(16), null, new_blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* new_block is null -> failure */
    status = GenMemOpsReplaceBlock(buf, USIZE_C(16), find_blk, null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = GenMemOpsReplaceBlock(buf, USIZE_C(16), find_blk, new_blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* block_sz > ptr_sz -> failure */
    status = GenMemOpsReplaceBlock(buf, USIZE_C(16), find_blk, new_blk, USIZE_C(17));
    assert(status == RESULT_FAILURE);

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

    /* Init 0x00 */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Find 0xFF... */
    kdi_FillVal(find_blk, USIZE_C(4), U8_C(0xFF));
    kdi_FillVal(new_blk, USIZE_C(4), U8_C(0xAA));

    status = GenMemOpsReplaceBlock(buf, USIZE_C(16), find_blk, new_blk, USIZE_C(4));

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
ReplaceSingle(void)
{
    u8   buf[16];
    u8   find_blk[4];
    u8   new_blk[4];
    bool status;

    printf(LOG_PREFIX_CSTR "ReplaceSingle -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Set target "AAAA" at offset 4 */
    kdi_FillVal(buf + 4, 4, 0xAA);

    /* Find "AAAA", Replace "BBBB" */
    kdi_FillVal(find_blk, 4, 0xAA);
    kdi_FillVal(new_blk, 4, 0xBB);

    status = GenMemOpsReplaceBlock(buf, USIZE_C(16), find_blk, new_blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);

    /* Verify replacement at offset 4 */
    assert(memcmp(buf + 4, new_blk, 4) == 0);

    /* Verify surrounding bytes unchanged */
    assert(buf[3] == 0x00);
    assert(buf[8] == 0x00);

    printf("PASSED\n");
}


void
ReplaceFirstOfMultiple(void)
{
    u8   buf[16];
    u8   find_blk[2];
    u8   new_blk[2];
    bool status;

    printf(LOG_PREFIX_CSTR "ReplaceFirstOfMultiple -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Targets at offset 2, 6, 10 */
    kdi_FillVal(buf + 2, 2, 0xFF);
    kdi_FillVal(buf + 6, 2, 0xFF);
    kdi_FillVal(buf + 10, 2, 0xFF);

    kdi_FillVal(find_blk, 2, 0xFF);
    kdi_FillVal(new_blk, 2, 0xEE);

    /* Replace First */
    status = GenMemOpsReplaceBlock(buf, USIZE_C(16), find_blk, new_blk, USIZE_C(2));

    assert(status == RESULT_SUCCESS);

    /* Verify first occurrence (offset 2) replaced */
    assert(memcmp(buf + 2, new_blk, 2) == 0);

    /* Verify subsequent occurrences (6, 10) unchanged */
    assert(memcmp(buf + 6, find_blk, 2) == 0);
    assert(memcmp(buf + 10, find_blk, 2) == 0);

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

    /* Case 1: Start of buffer */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));
    kdi_FillVal(buf, 2, 0x11); /* Offset 0 */

    kdi_FillVal(find_blk, 2, 0x11);
    kdi_FillVal(new_blk, 2, 0x99);

    status = GenMemOpsReplaceBlock(buf, USIZE_C(16), find_blk, new_blk, USIZE_C(2));
    assert(status == RESULT_SUCCESS);
    assert(memcmp(buf, new_blk, 2) == 0);

    /* Case 2: End of buffer */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));
    kdi_FillVal(buf + 14, 2, 0x22); /* Offset 14 */

    kdi_FillVal(find_blk, 2, 0x22);
    kdi_FillVal(new_blk, 2, 0x88);

    status = GenMemOpsReplaceBlock(buf, USIZE_C(16), find_blk, new_blk, USIZE_C(2));
    assert(status == RESULT_SUCCESS);
    assert(memcmp(buf + 14, new_blk, 2) == 0);

    printf("PASSED\n");
}


void
ReplaceSameValue(void)
{
    u8   buf[8];
    u8   val[2];
    bool status;

    printf(LOG_PREFIX_CSTR "ReplaceSameValue -> ");

    kdi_FillVal(buf, USIZE_C(8), U8_C(0x00));
    kdi_FillVal(buf + 2, 2, 0x55);

    kdi_FillVal(val, 2, 0x55);

    /* Replace 0x5555 with 0x5555 */
    status = GenMemOpsReplaceBlock(buf, USIZE_C(8), val, val, USIZE_C(2));

    assert(status == RESULT_SUCCESS);
    assert(memcmp(buf + 2, val, 2) == 0);

    printf("PASSED\n");
}


void
ReplaceBlock_U16(void)
{
    u16  buf[10];
    u16  find_blk = 0xAAAA;
    u16  new_blk  = 0xBBBB;
    bool status;

    printf(LOG_PREFIX_CSTR "ReplaceBlock_U16 -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    /* Set target at index 2 */
    buf[2] = 0xAAAA;
    /* Another at index 5 */
    buf[5] = 0xAAAA;

    status = GenMemOpsReplaceBlock(buf, sizeof(buf), &find_blk, &new_blk, sizeof(u16));

    assert(status == RESULT_SUCCESS);

    /* Verify index 2 replaced */
    assert(buf[2] == 0xBBBB);

    /* Verify index 5 unchanged (since replace replaces only the first) */
    assert(buf[5] == 0xAAAA);

    printf("PASSED\n");
}


void
ReplaceBlock_U32(void)
{
    u32  buf[10];
    u32  find_blk = 0x12345678;
    u32  new_blk  = 0x98765432;
    bool status;

    printf(LOG_PREFIX_CSTR "ReplaceBlock_U32 -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    buf[3] = 0x12345678;

    status = GenMemOpsReplaceBlock(buf, sizeof(buf), &find_blk, &new_blk, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    assert(buf[3] == 0x98765432);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
ReplaceBlock_U64(void)
{
    u64  buf[10];
    u64  find_blk = U64_C(0x1111222233334444);
    u64  new_blk  = U64_C(0xAAAABBBBCCCCDDDD);
    bool status;

    printf(LOG_PREFIX_CSTR "ReplaceBlock_U64 -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    buf[1] = find_blk;

    status = GenMemOpsReplaceBlock(buf, sizeof(buf), &find_blk, &new_blk, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    assert(buf[1] == new_blk);

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
ReplaceBlock_Struct(void)
{
    /* Struct size 24 bytes (> 64-bit) */
    kdi_TestStruct buf[5];
    kdi_TestStruct find_blk;
    kdi_TestStruct new_blk;
    bool           status;

    printf(LOG_PREFIX_CSTR "ReplaceBlock_Struct -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    /* Setup find block */
    find_blk.a = 0x11;
    find_blk.b = 0x22;
    find_blk.c = 0x33;

    /* Setup new block */
    new_blk.a  = 0xAA;
    new_blk.b  = 0xBB;
    new_blk.c  = 0xCC;

    /* Place target at index 1 */
    buf[1]     = find_blk;

    status     = GenMemOpsReplaceBlock(buf, sizeof(buf), &find_blk, &new_blk, sizeof(kdi_TestStruct));

    assert(status == RESULT_SUCCESS);

    /* Verify replacement via memcmp */
    assert(memcmp(&buf[1], &new_blk, sizeof(kdi_TestStruct)) == 0);

    /* Verify index 0 untouched */
    {
        kdi_TestStruct zero;
        memset(&zero, 0, sizeof(zero));
        assert(memcmp(&buf[0], &zero, sizeof(kdi_TestStruct)) == 0);
    }

    printf("PASSED\n");
}


void
PartialMatchIgnored(void)
{
    u8   buf[10];
    u8   find_blk[3];
    u8   new_blk[3];
    bool status;

    printf(LOG_PREFIX_CSTR "PartialMatchIgnored -> ");

    /* Buffer: 11 22 00 ... */
    kdi_FillVal(buf, USIZE_C(10), U8_C(0x00));
    buf[0]      = 0x11;
    buf[1]      = 0x22;
    /* buf[2] is 0x00 */

    /* Find: 11 22 33 */
    find_blk[0] = 0x11;
    find_blk[1] = 0x22;
    find_blk[2] = 0x33;
    kdi_FillVal(new_blk, 3, 0x99);

    status = GenMemOpsReplaceBlock(buf, USIZE_C(10), find_blk, new_blk, USIZE_C(3));

    assert(status == RESULT_SUCCESS);

    /* Buffer should remain unchanged */
    assert(buf[0] == 0x11);
    assert(buf[1] == 0x22);
    assert(buf[2] == 0x00);

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

    /* Set targets at 100, 1000 */
    kdi_FillVal(buf + 100, 5, 0x77);
    kdi_FillVal(buf + 1000, 5, 0x77);

    kdi_FillVal(find_blk, 5, 0x77);
    kdi_FillVal(new_blk, 5, 0x88);

    /* Replace first occurrence */
    status = GenMemOpsReplaceBlock(buf, USIZE_C(2000), find_blk, new_blk, USIZE_C(5));

    assert(status == RESULT_SUCCESS);

    /* Verify 100 changed */
    assert(memcmp(buf + 100, new_blk, 5) == 0);

    /* Verify 1000 unchanged */
    assert(memcmp(buf + 1000, find_blk, 5) == 0);

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
    ReplaceSingle();
    ReplaceFirstOfMultiple();
    ReplaceAtBoundaries();
    ReplaceSameValue();

    ReplaceBlock_U16();
    ReplaceBlock_U32();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    ReplaceBlock_U64();
#endif
    ReplaceBlock_Struct();

    PartialMatchIgnored();
    LargeBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
