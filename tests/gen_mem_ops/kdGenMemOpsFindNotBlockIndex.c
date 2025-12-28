/**
 * @file kdGenMemOpsFindNotBlockIndex.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindNotBlockIndex function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindNotBlockIndex function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8    buf[16];
    u8    blk[4];
    usize idx = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xFF));

    /* idx pointer is null -> failure */
    status = kdGenMemOpsFindNotBlockIndex(null, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    idx    = 55;
    status = kdGenMemOpsFindNotBlockIndex(&idx, null, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr_sz is zero -> failure */
    idx    = 55;
    status = kdGenMemOpsFindNotBlockIndex(&idx, buf, USIZE_C(0), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    idx    = 55;
    status = kdGenMemOpsFindNotBlockIndex(&idx, buf, USIZE_C(16), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    idx    = 55;
    status = kdGenMemOpsFindNotBlockIndex(&idx, buf, USIZE_C(16), blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* block_sz > ptr_sz -> failure */
    idx    = 55;
    status = kdGenMemOpsFindNotBlockIndex(&idx, buf, USIZE_C(4), blk, USIZE_C(16));
    assert(status == RESULT_FAILURE);

    /* ptr_sz not divisible by block_sz -> failure */
    idx    = 55;
    status = kdGenMemOpsFindNotBlockIndex(&idx, buf, USIZE_C(15), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Valid arguments - found at offset 0 (0x00 block is NOT 0xFF block) */
    idx    = 55;
    status = kdGenMemOpsFindNotBlockIndex(&idx, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

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

    /* Fill buffer with 0xAA */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));
    /* Block is 0xAA... */
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xAA));

    /* Search for block NOT equal to blk.
     * All blocks match. Should return FAILURE (Not found).
     */
    idx    = 999;
    status = kdGenMemOpsFindNotBlockIndex(&idx, buf, USIZE_C(16), blk, USIZE_C(4));

    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
FirstMismatch(void)
{
    u8    buf[16];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FirstMismatch -> ");

    /* Fill with 0xAA */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xAA));

    /* Change first block (Offset 0) to 0xBB */
    kdi_Fill_u8(buf, USIZE_C(4), U8_C(0xBB));

    /* Search for mismatch */
    status = kdGenMemOpsFindNotBlockIndex(&idx, buf, USIZE_C(16), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    printf("PASSED\n");
}


void
LastMismatch(void)
{
    u8    buf[16];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "LastMismatch -> ");

    /* Fill with 0xAA */
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xAA));

    /* Change last block (Offset 12) to 0xBB */
    kdi_Fill_u8(buf + 12, USIZE_C(4), U8_C(0xBB));

    /* Search for mismatch */
    status = kdGenMemOpsFindNotBlockIndex(&idx, buf, USIZE_C(16), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(12));

    printf("PASSED\n");
}


void
MiddleMismatch(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "MiddleMismatch -> ");

    /* Fill with 0xAA */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xAA));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xAA));

    /* Change block at offset 12 (Block index 3) to 0xCC */
    kdi_Fill_u8(buf + 12, USIZE_C(4), U8_C(0xCC));

    /* Search for mismatch */
    status = kdGenMemOpsFindNotBlockIndex(&idx, buf, USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    /* Should find offset 12 */
    assert(idx == USIZE_C(12));

    printf("PASSED\n");
}


void
MultipleMismatches(void)
{
    u8    buf[32];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "MultipleMismatches -> ");

    /* Fill with 0xAA */
    kdi_Fill_u8(buf, USIZE_C(32), U8_C(0xAA));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0xAA));

    /* Change blocks at offsets 4, 16, 24 to different values */
    kdi_Fill_u8(buf + 4, USIZE_C(4), U8_C(0xBB));
    kdi_Fill_u8(buf + 16, USIZE_C(4), U8_C(0xCC));
    kdi_Fill_u8(buf + 24, USIZE_C(4), U8_C(0xDD));

    /* Search for mismatch. Should find FIRST one at offset 4. */
    status = kdGenMemOpsFindNotBlockIndex(&idx, buf, USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(4));

    printf("PASSED\n");
}


void
SingleByteBlocks(void)
{
    u8    buf[10];
    u8    blk = 0x42;
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleByteBlocks -> ");

    /* Pattern: 0x42, 0x42, 0x99, 0x42, 0x42, 0x99, 0x42, 0x99, 0x42, 0x42 */
    kdi_Fill_u8(buf, USIZE_C(10), U8_C(0x42));
    buf[2] = 0x99;
    buf[5] = 0x99;
    buf[7] = 0x99;

    /* Find NOT 0x42. Should return FIRST mismatch at offset 2. */
    status = kdGenMemOpsFindNotBlockIndex(&idx, buf, USIZE_C(10), &blk, USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(2));

    printf("PASSED\n");
}


void
FindNotBlockIndex_U16(void)
{
    u16   buf[10];
    u16   blk = 0xAAAA;
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndex_U16 -> ");

    kdi_Fill_u8((u8 *)buf, sizeof(buf), 0);

    /* Fill all with 0xAAAA */
    {
        int i;
        for (i = 0; i < 10; ++i)
            buf[i] = 0xAAAA;
    }

    /* Set mismatch at element index 5 (Offset 10) */
    buf[5] = 0xBBBB;

    status = kdGenMemOpsFindNotBlockIndex(&idx, buf, sizeof(buf), &blk, sizeof(u16));

    assert(status == RESULT_SUCCESS);
    /* Index 5 * 2 bytes = Offset 10 */
    assert(idx == USIZE_C(10));

    printf("PASSED\n");
}


void
FindNotBlockIndex_U16_MultiByteBlocks(void)
{
    u16   buf[8];
    u16   blk[2];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndex_U16_MultiByteBlocks -> ");

    /* 4 blocks of 2 u16s each */
    blk[0] = 10;
    blk[1] = 20;

    /* Fill all with matching blocks */
    buf[0] = 10;
    buf[1] = 20;
    buf[2] = 10;
    buf[3] = 20;
    buf[4] = 10;
    buf[5] = 20;
    buf[6] = 10;
    buf[7] = 20;

    /* Change block at offset 8 (element indices 4-5) */
    buf[4] = 99;
    buf[5] = 99;

    /* Should find mismatch at offset 8 */
    status = kdGenMemOpsFindNotBlockIndex(&idx, buf, sizeof(buf), blk, sizeof(u16) * 2);

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(8));

    printf("PASSED\n");
}


void
FindNotBlockIndex_U32(void)
{
    u32   buf[10];
    u32   blk = 0x12345678;
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndex_U32 -> ");

    /* Fill all with target */
    {
        int i;
        for (i = 0; i < 10; ++i)
            buf[i] = 0x12345678;
    }

    /* Set mismatch at element index 8 (Offset 32) */
    buf[8] = 0x87654321;

    status = kdGenMemOpsFindNotBlockIndex(&idx, buf, sizeof(buf), &blk, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    /* Index 8 * 4 bytes = Offset 32 */
    assert(idx == USIZE_C(32));

    printf("PASSED\n");
}


void
FindNotBlockIndex_U32_MultiBlocks(void)
{
    u32   buf[6];
    u32   blk[2];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndex_U32_MultiBlocks -> ");

    /* 3 blocks of 2 u32s each */
    blk[0] = 10;
    blk[1] = 20;

    /* Fill all with matching blocks */
    buf[0] = 10;
    buf[1] = 20;
    buf[2] = 10;
    buf[3] = 20;
    buf[4] = 10;
    buf[5] = 20;

    /* Change first block (element indices 0-1) */
    buf[0] = 88;
    buf[1] = 88;

    /* Should find mismatch at offset 0 */
    status = kdGenMemOpsFindNotBlockIndex(&idx, buf, sizeof(buf), blk, sizeof(u32) * 2);

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(0));

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
FindNotBlockIndex_U64(void)
{
    u64   buf[10];
    u64   blk = U64_C(0x1111222233334444);
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndex_U64 -> ");

    /* Fill all with target */
    {
        int i;
        for (i = 0; i < 10; ++i)
            buf[i] = blk;
    }

    /* Set mismatch at element index 2 (Offset 16) */
    buf[2] = U64_C(0x9999888877776666);

    status = kdGenMemOpsFindNotBlockIndex(&idx, buf, sizeof(buf), &blk, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    /* Index 2 * 8 bytes = Offset 16 */
    assert(idx == USIZE_C(16));

    printf("PASSED\n");
}


void
FindNotBlockIndex_U64_MultiBlocks(void)
{
    u64   buf[6];
    u64   blk[2];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndex_U64_MultiBlocks -> ");

    /* 3 blocks of 2 u64s each */
    blk[0] = U64_C(0x1111111111111111);
    blk[1] = U64_C(0x2222222222222222);

    /* Fill all with matching blocks */
    buf[0] = U64_C(0x1111111111111111);
    buf[1] = U64_C(0x2222222222222222);
    buf[2] = U64_C(0x1111111111111111);
    buf[3] = U64_C(0x2222222222222222);
    buf[4] = U64_C(0x1111111111111111);
    buf[5] = U64_C(0x2222222222222222);

    /* Change middle block (element indices 2-3, offset 16) */
    buf[2] = U64_C(0x9999999999999999);
    buf[3] = U64_C(0x8888888888888888);

    /* Should find mismatch at offset 16 */
    status = kdGenMemOpsFindNotBlockIndex(&idx, buf, sizeof(buf), blk, sizeof(u64) * 2);

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(16));

    printf("PASSED\n");
}
#endif


typedef struct kdi_SmallStruct
{
    u32 a;
    u16 b;
} kdi_SmallStruct;


typedef struct kdi_TestStruct
{
    u64 a;
    u64 b;
    u64 c;
} kdi_TestStruct;


void
FindNotBlockIndex_Struct(void)
{
    kdi_TestStruct buf[5];
    kdi_TestStruct blk;
    usize          idx;
    bool           status;
    int            i;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndex_Struct -> ");

    /* Init struct */
    blk.a = 1;
    blk.b = 2;
    blk.c = 3;

    /* Fill buffer with matching structs */
    for (i = 0; i < 5; ++i)
    {
        buf[i] = blk;
    }

    /* Mismatch at element index 2 (Offset 48: 2 * 24) */
    buf[2].c = 99;

    status   = kdGenMemOpsFindNotBlockIndex(&idx, buf, sizeof(buf), &blk, sizeof(kdi_TestStruct));

    assert(status == RESULT_SUCCESS);
    /* Index 2 * 24 bytes = Offset 48 */
    assert(idx == USIZE_C(48));

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    /* Use static for large allocation */
    static u8 buf[8000];
    u8        blk[8];
    usize     idx;
    bool      status;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    /* Block size 8. Total 1000 blocks. */
    kdi_Fill_u8(buf, sizeof(buf), 0xAA);
    kdi_Fill_u8(blk, sizeof(blk), 0xAA);

    /* Set mismatch at block index 500 (Offset 4000) */
    kdi_Fill_u8(buf + 4000, USIZE_C(8), U8_C(0xBB));

    status = kdGenMemOpsFindNotBlockIndex(&idx, buf, sizeof(buf), blk, sizeof(blk));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(4000));

    /* Set another mismatch earlier at block index 100 (Offset 800) */
    kdi_Fill_u8(buf + 800, USIZE_C(8), U8_C(0xCC));

    /* Should find the FIRST one (800) */
    status = kdGenMemOpsFindNotBlockIndex(&idx, buf, sizeof(buf), blk, sizeof(blk));
    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(800));

    printf("PASSED\n");
}


void
AllSameBlocks(void)
{
    u8    buf[20];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "AllSameBlocks -> ");

    /* All blocks are [0x77, 0x77, 0x77, 0x77] */
    kdi_Fill_u8(buf, USIZE_C(20), U8_C(0x77));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0x77));

    /* Should fail (all match) */
    status = kdGenMemOpsFindNotBlockIndex(&idx, buf, USIZE_C(20), blk, USIZE_C(4));

    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ZeroBlocks(void)
{
    u8    buf[20];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "ZeroBlocks -> ");

    /* All blocks are [0x00, 0x00, 0x00, 0x00] except one */
    kdi_Fill_u8(buf, USIZE_C(20), U8_C(0x00));
    kdi_Fill_u8(blk, USIZE_C(4), U8_C(0x00));

    /* Set one block to non-zero */
    kdi_Fill_u8(buf + 8, USIZE_C(4), U8_C(0xFF));

    /* Should find at offset 8 */
    status = kdGenMemOpsFindNotBlockIndex(&idx, buf, USIZE_C(20), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(8));

    printf("PASSED\n");
}


void
AlternatingBlocks(void)
{
    u8    buf[24];
    u8    blk[3];
    usize idx;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "AlternatingBlocks -> ");

    /* Pattern: [A,A,A], [B,B,B], [A,A,A], [B,B,B], ... */
    for (i = 0; i < 8; ++i)
    {
        kdi_Fill_u8(buf + i * 3, USIZE_C(3), (i % 2 == 0) ? U8_C(0xAA) : U8_C(0xBB));
    }

    /* Search for NOT [A,A,A] */
    kdi_Fill_u8(blk, USIZE_C(3), U8_C(0xAA));

    /* Should find first [B,B,B] block at offset 3 */
    status = kdGenMemOpsFindNotBlockIndex(&idx, buf, USIZE_C(24), blk, USIZE_C(3));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(3));

    printf("PASSED\n");
}


void
OddSizes(void)
{
    u8    buf[33];
    u8    blk[3];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "OddSizes -> ");

    /* 11 blocks of size 3 */
    kdi_Fill_u8(buf, USIZE_C(33), U8_C(0x77));
    kdi_Fill_u8(blk, USIZE_C(3), U8_C(0x77));

    /* Set one block to different value at offset 15 */
    kdi_Fill_u8(buf + 15, USIZE_C(3), U8_C(0x88));

    /* Should find at offset 15 */
    status = kdGenMemOpsFindNotBlockIndex(&idx, buf, USIZE_C(33), blk, USIZE_C(3));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(15));

    printf("PASSED\n");
}


void
LargeBlockSize(void)
{
    u8    buf[256];
    u8    blk[32];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "LargeBlockSize -> ");

    /* 8 blocks of size 32 */
    kdi_Fill_u8(buf, USIZE_C(256), U8_C(0x55));
    kdi_Fill_u8(blk, USIZE_C(32), U8_C(0x55));

    /* Set block at offset 128 to different value */
    kdi_Fill_u8(buf + 128, USIZE_C(32), U8_C(0xAA));

    /* Should find at offset 128 */
    status = kdGenMemOpsFindNotBlockIndex(&idx, buf, USIZE_C(256), blk, USIZE_C(32));

    assert(status == RESULT_SUCCESS);
    assert(idx == USIZE_C(128));

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    AllMatch();
    FirstMismatch();
    LastMismatch();
    MiddleMismatch();
    MultipleMismatches();
    SingleByteBlocks();
    FindNotBlockIndex_U16();
    FindNotBlockIndex_U16_MultiByteBlocks();
    FindNotBlockIndex_U32();
    FindNotBlockIndex_U32_MultiBlocks();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    FindNotBlockIndex_U64();
    FindNotBlockIndex_U64_MultiBlocks();
#endif
    FindNotBlockIndex_Struct();
    LargeBuffer();
    AllSameBlocks();
    ZeroBlocks();
    AlternatingBlocks();
    OddSizes();
    LargeBlockSize();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}