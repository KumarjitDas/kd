/**
 * @file kdGenMemOpsFindLastNotBlockIndex.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindLastNotBlockIndex function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindLastNotBlockIndex function test"
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
    status = GenMemOpsFindLastNotBlockIndex(null, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindLastNotBlockIndex(&idx, null, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr_sz is zero -> failure */
    status = GenMemOpsFindLastNotBlockIndex(&idx, buf, USIZE_C(0), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    status = GenMemOpsFindLastNotBlockIndex(&idx, buf, USIZE_C(16), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = GenMemOpsFindLastNotBlockIndex(&idx, buf, USIZE_C(16), blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* block_sz > ptr_sz -> failure */
    status = GenMemOpsFindLastNotBlockIndex(&idx, buf, USIZE_C(4), blk, USIZE_C(16));
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
    status = GenMemOpsFindLastNotBlockIndex(&idx, buf, USIZE_C(15), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr_sz (16) is divisible by block_sz (4) -> Success (Logic runs) */
    kdi_FillVal(buf, 16, 0xAA);
    kdi_FillVal(blk, 4, 0xAA);

    /* Since all match, it returns FAILURE (Not found), but arg check passed */
    status = GenMemOpsFindLastNotBlockIndex(&idx, buf, USIZE_C(16), blk, USIZE_C(4));
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
    status = GenMemOpsFindLastNotBlockIndex(&idx, buf, USIZE_C(16), blk, USIZE_C(4));

    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
SingleMismatchLast(void)
{
    u8    buf[16];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleMismatchLast -> ");

    /* Fill with 0xAA */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));
    kdi_FillVal(blk, USIZE_C(4), U8_C(0xAA));

    /* Change last block (Offset 12) to 0xBB */
    kdi_FillVal(buf + 12, 4, 0xBB);

    /* Search for last mismatch */
    status = GenMemOpsFindLastNotBlockIndex(&idx, buf, USIZE_C(16), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(idx == 12);

    printf("PASSED\n");
}


void
SingleMismatchFirst(void)
{
    u8    buf[16];
    u8    blk[4];
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleMismatchFirst -> ");

    /* Fill with 0xAA */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));
    kdi_FillVal(blk, USIZE_C(4), U8_C(0xAA));

    /* Change first block (Offset 0) to 0xBB */
    kdi_FillVal(buf, 4, 0xBB);

    /* Search for last mismatch */
    status = GenMemOpsFindLastNotBlockIndex(&idx, buf, USIZE_C(16), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    /* Only mismatch is at 0, so it is the "last" one found scanning backwards too */
    assert(idx == 0);

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
    kdi_FillVal(buf, USIZE_C(32), U8_C(0xAA));
    kdi_FillVal(blk, USIZE_C(4), U8_C(0xAA));

    /* Mismatches at Offset 4 (Index 1) and Offset 20 (Index 5) */
    kdi_FillVal(buf + 4, 4, 0xBB);
    kdi_FillVal(buf + 20, 4, 0xCC);

    /* Search for last mismatch */
    status = GenMemOpsFindLastNotBlockIndex(&idx, buf, USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    /* Should find the one at Offset 20 */
    assert(idx == 20);

    printf("PASSED\n");
}


void
FindLastNotBlockIndex_U16(void)
{
    u16   buf[10];
    u16   blk = 0xAAAA;
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindLastNotBlockIndex_U16 -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    {
        int i;
        for (i = 0; i < 10; ++i)
            buf[i] = 0xAAAA;
    }

    /* Set mismatch at element index 2 (Offset 4) and 8 (Offset 16) */
    buf[2] = 0xBBBB;
    buf[8] = 0xCCCC;

    status = GenMemOpsFindLastNotBlockIndex(&idx, buf, sizeof(buf), &blk, sizeof(u16));

    assert(status == RESULT_SUCCESS);
    /* Last mismatch is index 8 -> Offset 16 */
    assert(idx == 16);

    printf("PASSED\n");
}


void
FindLastNotBlockIndex_U32(void)
{
    u32   buf[10];
    u32   blk = 0x12345678;
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindLastNotBlockIndex_U32 -> ");

    {
        int i;
        for (i = 0; i < 10; ++i)
            buf[i] = 0x12345678;
    }

    /* Mismatch at Index 1 (Offset 4) and Index 5 (Offset 20) */
    buf[1] = 0x87654321;
    buf[5] = 0x99999999;

    status = GenMemOpsFindLastNotBlockIndex(&idx, buf, sizeof(buf), &blk, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    /* Last mismatch is Index 5 -> Offset 20 */
    assert(idx == 20);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
FindLastNotBlockIndex_U64(void)
{
    u64   buf[10];
    u64   blk = U64_C(0x1111222233334444);
    usize idx;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindLastNotBlockIndex_U64 -> ");

    {
        int i;
        for (i = 0; i < 10; ++i)
            buf[i] = blk;
    }

    /* Mismatch at Index 9 (Offset 72) */
    buf[9] = U64_C(0xFFFFFFFFFFFFFFFF);

    status = GenMemOpsFindLastNotBlockIndex(&idx, buf, sizeof(buf), &blk, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    /* Last mismatch is Index 9 -> Offset 72 */
    assert(idx == 72);

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
FindLastNotBlockIndex_Struct(void)
{
    kdi_TestStruct buf[5];
    kdi_TestStruct blk;
    usize          idx;
    bool           status;
    int            i;

    printf(LOG_PREFIX_CSTR "FindLastNotBlockIndex_Struct -> ");

    blk.a = 1;
    blk.b = 2;
    blk.c = 3;

    for (i = 0; i < 5; ++i)
        buf[i] = blk;

    /* Mismatch at Index 1 (Offset 24) and Index 3 (Offset 72) */
    buf[1].a = 99;
    buf[3].c = 88;

    status   = GenMemOpsFindLastNotBlockIndex(&idx, buf, sizeof(buf), &blk, sizeof(kdi_TestStruct));

    assert(status == RESULT_SUCCESS);
    /* Last mismatch is Index 3 -> Offset 72 */
    assert(idx == 72);

    printf("PASSED\n");
}


void
FindLastNotBlockIndex_LargeArray(void)
{
    static u8 buf[8000];
    u8        blk[8];
    usize     idx;
    bool      status;

    printf(LOG_PREFIX_CSTR "FindLastNotBlockIndex_LargeArray -> ");

    kdi_FillVal(buf, sizeof(buf), 0xAA);
    kdi_FillVal(blk, sizeof(blk), 0xAA);

    /* Mismatch at Offset 800 and Offset 4000 */
    kdi_FillVal(buf + 800, 8, 0xBB);
    kdi_FillVal(buf + 4000, 8, 0xCC);

    status = GenMemOpsFindLastNotBlockIndex(&idx, buf, sizeof(buf), blk, sizeof(blk));

    assert(status == RESULT_SUCCESS);
    /* Should find the last one (4000) */
    assert(idx == 4000);

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
    SingleMismatchLast();
    SingleMismatchFirst();
    MultipleMismatches();

    FindLastNotBlockIndex_U16();
    FindLastNotBlockIndex_U32();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    FindLastNotBlockIndex_U64();
#endif
    FindLastNotBlockIndex_Struct();
    FindLastNotBlockIndex_LargeArray();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
