/**
 * @file kdGenMemOpsFindBlockIndicesU64.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindBlockIndicesU64 function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindBlockIndicesU64 function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


/* Helper to fill memory */
static void
kdi_FillVal(u8 *dst, usize sz, u8 val)
{
    usize i;
    for (i = USIZE_C(0); i < sz; ++i)
    {
        dst[i] = val;
    }
}

#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT || 1
/* Assuming 64-bit support is available */


void
BasicArguments(void)
{
    u8    buf[16];
    u8    blk[4];
    u64   idxs[16];
    usize found = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* idxs pointer is null -> failure */
    status = GenMemOpsFindBlockIndicesU64(null, sizeof(idxs), &found, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* found pointer is null -> failure */
    status = GenMemOpsFindBlockIndicesU64(idxs, sizeof(idxs), null, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindBlockIndicesU64(idxs, sizeof(idxs), &found, null, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    status = GenMemOpsFindBlockIndicesU64(idxs, sizeof(idxs), &found, buf, USIZE_C(16), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* idxs_sz is zero -> success but found=0 */
    found  = 55;
    status = GenMemOpsFindBlockIndicesU64(idxs, USIZE_C(0), &found, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    /* ptr_sz is zero -> success, found=0 */
    status = GenMemOpsFindBlockIndicesU64(idxs, sizeof(idxs), &found, buf, USIZE_C(0), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    /* block_sz is zero -> failure */
    status = GenMemOpsFindBlockIndicesU64(idxs, sizeof(idxs), &found, buf, USIZE_C(16), blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* idxs_sz smaller than sizeof(u64) -> success but found=0 */
    status = GenMemOpsFindBlockIndicesU64(idxs, USIZE_C(7), &found, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    printf("PASSED\n");
}


void
FindNone(void)
{
    u8    buf[16];
    u8    blk[4];
    u64   idxs[16];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNone -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));
    kdi_FillVal(blk, USIZE_C(4), U8_C(0xFF));

    status = GenMemOpsFindBlockIndicesU64(idxs, sizeof(idxs), &found, buf, USIZE_C(16), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    printf("PASSED\n");
}


void
FindMatches(void)
{
    u8    buf[16];
    u8    blk[2];
    u64   idxs[16];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindMatches -> ");

    /* Block Size: 2 */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Set matches at Block 0 (Offset 0) and Block 2 (Offset 4) */
    buf[0] = 0xAA;
    buf[1] = 0xBB;
    buf[4] = 0xAA;
    buf[5] = 0xBB;

    blk[0] = 0xAA;
    blk[1] = 0xBB;

    status = GenMemOpsFindBlockIndicesU64(idxs, sizeof(idxs), &found, buf, USIZE_C(16), blk, USIZE_C(2));

    assert(status == RESULT_SUCCESS);

    /* Found 2 blocks. Total bytes = 2 * 2 = 4. */
    assert(found == 4);

    assert(idxs[0] == 0);
    assert(idxs[1] == 4);

    printf("PASSED\n");
}


void
CapacityLimit(void)
{
    u8    buf[16];
    u8    blk[2];
    u64   idxs[2]; /* Capacity for 2 matches (16 bytes) */
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "CapacityLimit -> ");

    /* Fill buffer with repeating pattern AA BB */
    {
        usize i;
        for (i = 0; i < 16; i += 2)
        {
            buf[i]     = 0xAA;
            buf[i + 1] = 0xBB;
        }
    }

    blk[0] = 0xAA;
    blk[1] = 0xBB;

    status = GenMemOpsFindBlockIndicesU64(idxs, sizeof(idxs), &found, buf, USIZE_C(16), blk, USIZE_C(2));

    assert(status == RESULT_SUCCESS);

    /* Capacity limit hit. 2 blocks found. Total bytes = 4. */
    assert(found == 4);

    assert(idxs[0] == 0);
    assert(idxs[1] == 2);

    printf("PASSED\n");
}


void
UnalignedMatchFail(void)
{
    u8    buf[4];
    u8    blk[2];
    u64   idxs[4];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "UnalignedMatchFail -> ");

    /* Buffer: 01 02 03 04 */
    buf[0] = 1;
    buf[1] = 2;
    buf[2] = 3;
    buf[3] = 4;

    /* Search: 2 3 (Offset 1, unaligned) */
    blk[0] = 2;
    blk[1] = 3;

    status = GenMemOpsFindBlockIndicesU64(idxs, sizeof(idxs), &found, buf, USIZE_C(4), blk, USIZE_C(2));

    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    printf("PASSED\n");
}


void
LargeCount(void)
{
    /* Use static for larger buffer */
    static u8  buf[2000];
    static u64 idxs[2000];
    u8         blk[1];
    usize      found;
    bool       status;
    usize      i;

    printf(LOG_PREFIX_CSTR "LargeCount -> ");

    /* Fill matching values 0..1999 */
    kdi_FillVal(buf, USIZE_C(2000), U8_C(0x77));
    blk[0] = 0x77;

    status = GenMemOpsFindBlockIndicesU64(idxs, sizeof(idxs), &found, buf, USIZE_C(2000), blk, USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(found == 2000);

    assert(idxs[0] == 0);
    assert(idxs[1999] == 1999);

    /* Verify sequence */
    for (i = 0; i < 2000; ++i)
    {
        if (idxs[i] != (u64)i)
        {
            printf("Mismatch at %zu\n", i);
            assert(kd_false);
        }
    }

    printf("PASSED\n");
}


void
U16_FindBlockIndices(void)
{
    /* 1000 items * 2 bytes = 2000 bytes */
    static u16 buf[1000];
    u16        blk[1];
    u64        idxs[10];
    usize      found;
    bool       status;

    printf(LOG_PREFIX_CSTR "U16_FindBlockIndices -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);
    blk[0]   = 0xAAAA;

    /* Match at Index 2 (Offset 4) */
    buf[2]   = 0xAAAA;

    /* Match at Index 999 (Offset 1998) */
    buf[999] = 0xAAAA;

    status   = GenMemOpsFindBlockIndicesU64(idxs, sizeof(idxs), &found, buf, sizeof(buf), blk, sizeof(u16));

    assert(status == RESULT_SUCCESS);

    /* Found 2 blocks. Total bytes = 2 * 2 = 4. */
    assert(found == 4);

    assert(idxs[0] == 4);
    assert(idxs[1] == 1998);

    printf("PASSED\n");
}


void
U32_FindBlockIndices(void)
{
    /* 1000 items * 4 bytes = 4000 bytes */
    static u32 buf[1000];
    u32        blk[1];
    u64        idxs[10];
    usize      found;
    bool       status;

    printf(LOG_PREFIX_CSTR "U32_FindBlockIndices -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);
    blk[0]   = 0xBBBBBBBB;

    /* Match at Index 1 (Offset 4) */
    buf[1]   = 0xBBBBBBBB;

    /* Match at Index 999 (Offset 3996) */
    buf[999] = 0xBBBBBBBB;

    status   = GenMemOpsFindBlockIndicesU64(idxs, sizeof(idxs), &found, buf, sizeof(buf), blk, sizeof(u32));

    assert(status == RESULT_SUCCESS);

    /* Found 2 blocks. Total bytes = 8. */
    assert(found == 8);

    assert(idxs[0] == 4);
    assert(idxs[1] == 3996);

    printf("PASSED\n");
}


void
U64_FindBlockIndices(void)
{
    /* 500 items * 8 bytes = 4000 bytes */
    static u64 buf[500];
    u64        blk[1];
    u64        idxs[10];
    usize      found;
    bool       status;

    printf(LOG_PREFIX_CSTR "U64_FindBlockIndices -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);
    blk[0]   = U64_C(0xCCCCCCCCCCCCCCCC);

    /* Match at Index 1 (Offset 8) */
    buf[1]   = blk[0];

    /* Match at Index 499 (Offset 3992) */
    buf[499] = blk[0];

    status   = GenMemOpsFindBlockIndicesU64(idxs, sizeof(idxs), &found, buf, sizeof(buf), blk, sizeof(u64));

    assert(status == RESULT_SUCCESS);

    /* Found 2 blocks. Total bytes = 16. */
    assert(found == 16);

    assert(idxs[0] == 8);
    assert(idxs[1] == 3992);

    printf("PASSED\n");
}


/* Struct larger than 64-bit */
typedef struct kdi_TestStruct
{
    u64 a;
    u64 b;
    u64 c;
} kdi_TestStruct;


void
Struct_FindBlockIndices(void)
{
    /* Struct Size 24 bytes. */
    /* 100 items * 24 = 2400 bytes */
    static kdi_TestStruct buf[100];
    kdi_TestStruct        blk;
    u64                   idxs[10];
    usize                 found;
    bool                  status;
    usize                 sz = sizeof(kdi_TestStruct);

    printf(LOG_PREFIX_CSTR "Struct_FindBlockIndices -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    blk.a   = 0x1111111111111111;
    blk.b   = 0x2222222222222222;
    blk.c   = 0x3333333333333333;

    /* Match at Index 0 (Offset 0) */
    buf[0]  = blk;

    /* Match at Index 99 (Offset 2376) */
    buf[99] = blk;

    status  = GenMemOpsFindBlockIndicesU64(idxs, sizeof(idxs), &found, buf, sizeof(buf), &blk, sz);

    assert(status == RESULT_SUCCESS);

    /* Found 2 blocks. Total bytes = 2 * 24 = 48. */
    assert(found == 48);

    assert(idxs[0] == 0);
    assert(idxs[1] == 2376);

    printf("PASSED\n");
}
#endif /* KD_ARCH_64BIT_INT */


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT || 1
    BasicArguments();
    FindNone();
    FindMatches();
    CapacityLimit();
    UnalignedMatchFail();
    LargeCount();

    U16_FindBlockIndices();
    U32_FindBlockIndices();
    U64_FindBlockIndices();
    Struct_FindBlockIndices();
#else
    printf("Skipping U64 tests: Architecture does not support 64-bit integers.\n");
#endif

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
