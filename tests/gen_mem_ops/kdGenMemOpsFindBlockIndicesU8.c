/**
 * @file kdGenMemOpsFindBlockIndicesU8.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindBlockIndicesU8 function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindBlockIndicesU8 function test"
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
    u8    idxs[16];
    usize found = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* idxs pointer is null -> failure */
    status = GenMemOpsFindBlockIndicesU8(null, USIZE_C(16), &found, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* found pointer is null -> failure */
    status = GenMemOpsFindBlockIndicesU8(idxs, USIZE_C(16), null, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindBlockIndicesU8(idxs, USIZE_C(16), &found, null, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    status = GenMemOpsFindBlockIndicesU8(idxs, USIZE_C(16), &found, buf, USIZE_C(16), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* idxs_sz is zero -> success but found=0 */
    found  = 55;
    status = GenMemOpsFindBlockIndicesU8(idxs, USIZE_C(0), &found, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    /* ptr_sz is zero -> success, found=0 */
    status = GenMemOpsFindBlockIndicesU8(idxs, USIZE_C(16), &found, buf, USIZE_C(0), blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    /* block_sz is zero -> failure */
    status = GenMemOpsFindBlockIndicesU8(idxs, USIZE_C(16), &found, buf, USIZE_C(16), blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
FindNone(void)
{
    u8    buf[16];
    u8    blk[4];
    u8    idxs[16];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNone -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));
    kdi_FillVal(blk, USIZE_C(4), U8_C(0xFF));

    status = GenMemOpsFindBlockIndicesU8(idxs, USIZE_C(16), &found, buf, USIZE_C(16), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    printf("PASSED\n");
}


void
FindMatches(void)
{
    u8    buf[16];
    u8    blk[2];
    u8    idxs[16];
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

    /* Target: AA BB */
    blk[0] = 0xAA;
    blk[1] = 0xBB;

    status = GenMemOpsFindBlockIndicesU8(idxs, USIZE_C(16), &found, buf, USIZE_C(16), blk, USIZE_C(2));

    assert(status == RESULT_SUCCESS);

    /* Found 2 blocks. Total bytes found = 2 * 2 = 4. */
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
    u8    idxs[2]; /* Capacity for 2 matches */
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "CapacityLimit -> ");

    /* Fill buffer with repeating pattern AA BB */
    /* 16 bytes / 2 bytes = 8 matches available */
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

    /* Capacity is 2 indices. */
    status = GenMemOpsFindBlockIndicesU8(idxs, USIZE_C(2), &found, buf, USIZE_C(16), blk, USIZE_C(2));

    assert(status == RESULT_SUCCESS);

    /* Found 2 blocks (limited by capacity). Total bytes = 2 * 2 = 4. */
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
    u8    idxs[4];
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

    status = GenMemOpsFindBlockIndicesU8(idxs, USIZE_C(4), &found, buf, USIZE_C(4), blk, USIZE_C(2));

    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    printf("PASSED\n");
}


void
IndexValueLimit(void)
{
    u8    buf[300];
    u8    blk[5];
    u8    idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "IndexValueLimit -> ");

    kdi_FillVal(buf, USIZE_C(300), U8_C(0x00));

    /* Block Size 5 */
    kdi_FillVal(blk, USIZE_C(5), U8_C(0xFF));

    /* 1. Match at Offset 250 (Index 250 <= 254). Valid. */
    /* Ends at 255. Fits within first 256 bytes. */
    kdi_FillVal(buf + 250, USIZE_C(5), U8_C(0xFF));

    /* 2. Match at Offset 255 (Index 255 > 254). Invalid Index for U8. */
    kdi_FillVal(buf + 255, USIZE_C(5), U8_C(0xFF));

    status = GenMemOpsFindBlockIndicesU8(idxs, USIZE_C(10), &found, buf, USIZE_C(300), blk, USIZE_C(5));

    assert(status == RESULT_SUCCESS);

    /* Should only find the one at 250. Total bytes = 1 * 5 = 5. */
    assert(found == 5);
    assert(idxs[0] == 250);

    printf("PASSED\n");
}


void
MaxIndicesCount(void)
{
    /* Block size 1. Indices 0..254 */
    u8    buf[255];
    u8    blk[1];
    u8    idxs[255];
    usize found;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "MaxIndicesCount -> ");

    kdi_FillVal(buf, USIZE_C(255), U8_C(0x77));
    blk[0] = 0x77;

    status = GenMemOpsFindBlockIndicesU8(idxs, USIZE_C(255), &found, buf, USIZE_C(255), blk, USIZE_C(1));

    assert(status == RESULT_SUCCESS);

    /* Found 255 blocks. Total bytes = 255 * 1 = 255. */
    assert(found == 255);

    assert(idxs[0] == 0);
    assert(idxs[254] == 254);

    for (i = 0; i < 255; ++i)
    {
        if (idxs[i] != (u8)i)
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
    /* Reduce buffer to < 255 bytes. */
    /* 127 items * 2 bytes = 254 bytes. */
    u16   buf[127];
    u16   blk[1];
    u8    idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "U16_FindBlockIndices -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);
    blk[0]   = 0xAAAA;

    /* Match at Index 2 (Offset 4) */
    buf[2]   = 0xAAAA;

    /* Match at Index 126 (Last element). Offset 126 * 2 = 252. */
    /* Block occupies bytes 252, 253. Valid. */
    buf[126] = 0xAAAA;

    status   = GenMemOpsFindBlockIndicesU8(idxs, USIZE_C(10), &found, buf, sizeof(buf), blk, sizeof(u16));

    assert(status == RESULT_SUCCESS);

    /* Found 2 blocks. Total bytes = 2 * sizeof(u16) = 4. */
    assert(found == 4);

    assert(idxs[0] == 4);
    assert(idxs[1] == 252);

    printf("PASSED\n");
}


void
U32_FindBlockIndices(void)
{
    /* Reduce buffer to < 255 bytes. */
    /* 63 items * 4 bytes = 252 bytes. */
    u32   buf[63];
    u32   blk[1];
    u8    idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_FindBlockIndices -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);
    blk[0]  = 0xBBBBBBBB;

    /* Match at Index 1 (Offset 4) */
    buf[1]  = 0xBBBBBBBB;

    /* Match at Index 62 (Last element). Offset 62 * 4 = 248. */
    /* Block occupies 248..251. Valid. */
    buf[62] = 0xBBBBBBBB;

    status  = GenMemOpsFindBlockIndicesU8(idxs, USIZE_C(10), &found, buf, sizeof(buf), blk, sizeof(u32));

    assert(status == RESULT_SUCCESS);

    /* Found 2 blocks. Total bytes = 2 * sizeof(u32) = 8. */
    assert(found == 8);

    assert(idxs[0] == 4);
    assert(idxs[1] == 248);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_FindBlockIndices(void)
{
    /* Reduce buffer to < 255 bytes. */
    /* 31 items * 8 bytes = 248 bytes. */
    u64   buf[31];
    u64   blk[1];
    u8    idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "U64_FindBlockIndices -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);
    blk[0]  = U64_C(0xCCCCCCCCCCCCCCCC);

    /* Match at Index 1 (Offset 8) */
    buf[1]  = blk[0];

    /* Match at Index 30 (Last element). Offset 30 * 8 = 240. */
    /* Block occupies 240..247. Valid. */
    buf[30] = blk[0];

    status  = GenMemOpsFindBlockIndicesU8(idxs, USIZE_C(10), &found, buf, sizeof(buf), blk, sizeof(u64));

    assert(status == RESULT_SUCCESS);

    /* Found 2 blocks. Total bytes = 2 * sizeof(u64) = 16. */
    assert(found == 16);

    assert(idxs[0] == 8);
    assert(idxs[1] == 240);

    printf("PASSED\n");
}
#endif


/* Struct larger than 64-bit (24 bytes) */
typedef struct kdi_TestStruct
{
    u64 a;
    u64 b;
    u64 c;
} kdi_TestStruct;


void
Struct_FindBlockIndices(void)
{
    /* 10 items * 24 bytes = 240 bytes. */
    kdi_TestStruct buf[10];
    kdi_TestStruct blk;
    u8             idxs[10];
    usize          found;
    bool           status;
    usize          sz = sizeof(kdi_TestStruct);

    printf(LOG_PREFIX_CSTR "Struct_FindBlockIndices -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    blk.a  = 0x1111111111111111;
    blk.b  = 0x2222222222222222;
    blk.c  = 0x3333333333333333;

    /* Match at Index 0 (Offset 0) */
    buf[0] = blk;

    /* Match at Index 9 (Offset 216). 216 + 24 = 240. Valid. */
    buf[9] = blk;

    status = GenMemOpsFindBlockIndicesU8(idxs, USIZE_C(10), &found, buf, sizeof(buf), &blk, sz);

    assert(status == RESULT_SUCCESS);

    /* Found 2 blocks. Total bytes = 2 * 24 = 48. */
    assert(found == 48);

    assert(idxs[0] == 0);
    assert(idxs[1] == 216);

    printf("PASSED\n");
}


void
LargeArray_FindBlockIndices(void)
{
    u8    buf[500];
    u8    blk[5];
    u8    idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "LargeArray_FindBlockIndices -> ");

    kdi_FillVal(buf, sizeof(buf), 0);
    kdi_FillVal(blk, sizeof(blk), 0xEE);

    /* Match at offset 100 */
    kdi_FillVal(buf + 100, 5, 0xEE);

    /* Match at offset 250. 250 + 5 = 255. Valid <= 256 bytes range. */
    kdi_FillVal(buf + 250, 5, 0xEE);

    /* Match at offset 300 (Invalid > 254) */
    kdi_FillVal(buf + 300, 5, 0xEE);

    status = GenMemOpsFindBlockIndicesU8(idxs, USIZE_C(10), &found, buf, sizeof(buf), blk, 5);

    assert(status == RESULT_SUCCESS);

    /* Found 2 blocks. Total bytes = 2 * 5 = 10. */
    assert(found == 10);

    assert(idxs[0] == 100);
    assert(idxs[1] == 250);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    FindNone();
    FindMatches();
    CapacityLimit();
    UnalignedMatchFail();
    IndexValueLimit();
    MaxIndicesCount();

    U16_FindBlockIndices();
    U32_FindBlockIndices();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_FindBlockIndices();
#endif
    Struct_FindBlockIndices();
    LargeArray_FindBlockIndices();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
