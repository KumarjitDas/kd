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


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindNotBlockIndex function test"
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
    usize idx = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* idx pointer is null -> failure */
    status = GenMemOpsFindNotBlockIndex(null, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindNotBlockIndex(&idx, null, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr_sz is zero -> failure */
    status = GenMemOpsFindNotBlockIndex(&idx, buf, USIZE_C(0), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    status = GenMemOpsFindNotBlockIndex(&idx, buf, USIZE_C(16), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = GenMemOpsFindNotBlockIndex(&idx, buf, USIZE_C(16), blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* block_sz > ptr_sz -> failure */
    status = GenMemOpsFindNotBlockIndex(&idx, buf, USIZE_C(4), blk, USIZE_C(16));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SizeAlignment(void)
{
    u8    buf[16];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "SizeAlignment -> ");

    /* ptr_sz (15) is not divisible by block_sz (4) -> Failure */
    status = GenMemOpsFindNotBlockIndex(&idx, buf, USIZE_C(15), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr_sz (16) is divisible by block_sz (4) -> Success (Logic runs) */
    kdi_FillVal(buf, 16, 0xAA);
    kdi_FillVal(blk, 4, 0xAA);

    /* Since all match, it returns FAILURE (Not found), but arg check passed */
    status = GenMemOpsFindNotBlockIndex(&idx, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

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
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));
    /* Block is 0xAA... */
    kdi_FillVal(blk, USIZE_C(4), U8_C(0xAA));

    /* Search for block NOT equal to blk.
     * All blocks match. Should return FAILURE (Not found).
     */
    status = GenMemOpsFindNotBlockIndex(&idx, buf, USIZE_C(16), blk, USIZE_C(4));

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
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));
    kdi_FillVal(blk, USIZE_C(4), U8_C(0xAA));

    /* Change first block (Offset 0) to 0xBB */
    kdi_FillVal(buf, 4, 0xBB);

    /* Search for mismatch */
    status = GenMemOpsFindNotBlockIndex(&idx, buf, USIZE_C(16), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == 0);

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
    kdi_FillVal(buf, USIZE_C(32), U8_C(0xAA));
    kdi_FillVal(blk, USIZE_C(4), U8_C(0xAA));

    /* Change block at offset 12 (Index 3) to 0xCC */
    kdi_FillVal(buf + 12, 4, 0xCC);

    /* Search for mismatch */
    status = GenMemOpsFindNotBlockIndex(&idx, buf, USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    /* Should find offset 12 */
    assert(idx == 12);

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

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    /* Fill all with 0xAAAA */
    {
        int i;
        for (i = 0; i < 10; ++i)
            buf[i] = 0xAAAA;
    }

    /* Set mismatch at element index 5 (Offset 10) */
    buf[5] = 0xBBBB;

    status = GenMemOpsFindNotBlockIndex(&idx, buf, sizeof(buf), &blk, sizeof(u16));

    assert(status == RESULT_SUCCESS);
    /* Index 5 * 2 bytes = Offset 10 */
    assert(idx == 10);

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

    status = GenMemOpsFindNotBlockIndex(&idx, buf, sizeof(buf), &blk, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    /* Index 8 * 4 bytes = Offset 32 */
    assert(idx == 32);

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

    status = GenMemOpsFindNotBlockIndex(&idx, buf, sizeof(buf), &blk, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    /* Index 2 * 8 bytes = Offset 16 */
    assert(idx == 16);

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

    status   = GenMemOpsFindNotBlockIndex(&idx, buf, sizeof(buf), &blk, sizeof(kdi_TestStruct));

    assert(status == RESULT_SUCCESS);
    /* Index 2 * 24 bytes = Offset 48 */
    assert(idx == 48);

    printf("PASSED\n");
}


void
FindNotBlockIndex_LargeArray(void)
{
    /* Use static for large allocation */
    static u8 buf[8000];
    u8        blk[8];
    usize     idx;
    bool      status;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndex_LargeArray -> ");

    /* Block size 8. Total 1000 blocks. */
    kdi_FillVal(buf, sizeof(buf), 0xAA);
    kdi_FillVal(blk, sizeof(blk), 0xAA);

    /* Set mismatch at block index 500 (Offset 4000) */
    kdi_FillVal(buf + 4000, 8, 0xBB);

    status = GenMemOpsFindNotBlockIndex(&idx, buf, sizeof(buf), blk, sizeof(blk));

    assert(status == RESULT_SUCCESS);
    assert(idx == 4000);

    /* Set another mismatch earlier at block index 100 (Offset 800) */
    kdi_FillVal(buf + 800, 8, 0xCC);

    /* Should find the first one (800) */
    status = GenMemOpsFindNotBlockIndex(&idx, buf, sizeof(buf), blk, sizeof(blk));
    assert(status == RESULT_SUCCESS);
    assert(idx == 800);

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
    AllMatch();
    FirstMismatch();
    MiddleMismatch();

    FindNotBlockIndex_U16();
    FindNotBlockIndex_U32();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    FindNotBlockIndex_U64();
#endif
    FindNotBlockIndex_Struct();
    FindNotBlockIndex_LargeArray();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
