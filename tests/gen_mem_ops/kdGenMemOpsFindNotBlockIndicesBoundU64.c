/**
 * @file kdGenMemOpsFindNotBlockIndicesBoundU64.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindNotBlockIndicesBoundU64 function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindNotBlockIndicesBoundU64 function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT

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
    u64   idxs[16];
    usize found = 55;
    bool  status;
    /* Size in bytes: 16 * 8 = 128 bytes */
    usize idxs_byte_sz = sizeof(idxs);

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* idxs is null -> failure */
    status = GenMemOpsFindNotBlockIndicesBoundU64(null, idxs_byte_sz, &found, buf, USIZE_C(16), 0, 16, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* idxs_sz is zero -> failure */
    status = GenMemOpsFindNotBlockIndicesBoundU64(idxs, USIZE_C(0), &found, buf, USIZE_C(16), 0, 16, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* found pointer is null -> failure */
    status = GenMemOpsFindNotBlockIndicesBoundU64(idxs, idxs_byte_sz, null, buf, USIZE_C(16), 0, 16, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure */
    status = GenMemOpsFindNotBlockIndicesBoundU64(idxs, idxs_byte_sz, &found, null, USIZE_C(16), 0, 16, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = GenMemOpsFindNotBlockIndicesBoundU64(idxs, idxs_byte_sz, &found, buf, USIZE_C(0), 0, 16, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    status = GenMemOpsFindNotBlockIndicesBoundU64(idxs, idxs_byte_sz, &found, buf, USIZE_C(16), 0, 16, null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = GenMemOpsFindNotBlockIndicesBoundU64(idxs, idxs_byte_sz, &found, buf, USIZE_C(16), 0, 16, blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* block_sz > base_sz -> failure */
    status = GenMemOpsFindNotBlockIndicesBoundU64(idxs, idxs_byte_sz, &found, buf, USIZE_C(4), 0, 4, blk, USIZE_C(16));
    assert(status == RESULT_FAILURE);

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

    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));
    kdi_FillVal(blk, 4, 0xAA);

    /* Search range [0, 16). All match. Should find 0 bytes. */
    status = GenMemOpsFindNotBlockIndicesBoundU64(idxs, sizeof(idxs), &found, buf, USIZE_C(16), 0, 16, blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    printf("PASSED\n");
}


void
AlignmentAndStride(void)
{
    u8    buf[32];
    u8    blk[4];
    u64   idxs[16];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "AlignmentAndStride -> ");

    /* Init matches */
    kdi_FillVal(buf, USIZE_C(32), U8_C(0xAA));
    kdi_FillVal(blk, 4, 0xAA);

    /* * Search parameters:
     * begin_idx = 4
     * block_sz  = 4
     * end_count = 12
     * Range: [4, 16)
     * Stride Checks: 4, 8, 12
     */

    /* Mismatch at Offset 4 (Aligned) */
    kdi_FillVal(buf + 4, 4, 0xBB);

    /* Mismatch at Offset 8 (Aligned) */
    kdi_FillVal(buf + 8, 4, 0xBB);

    /* Mismatch at Offset 6 (Unaligned).
     * Start 4, Stride 4 -> checks 4, 8...
     * 6 is skipped.
     */
    kdi_FillVal(buf + 6, 4, 0xCC);

    /* Mismatch at Offset 0 (Before range). Ignored. */
    kdi_FillVal(buf, 4, 0xBB);

    status = GenMemOpsFindNotBlockIndicesBoundU64(idxs, sizeof(idxs), &found, buf, USIZE_C(32), 4, 12, blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    /* 2 indices * 8 bytes = 16 bytes */
    assert(found == 16);
    assert(idxs[0] == 4);
    assert(idxs[1] == 8);

    printf("PASSED\n");
}


void
OutputBufferCapacity(void)
{
    u8    buf[32];
    u8    blk[4];
    u64   idxs[2]; /* Capacity for 2 indices (16 bytes) */
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "OutputBufferCapacity -> ");

    kdi_FillVal(buf, USIZE_C(32), U8_C(0xAA));
    kdi_FillVal(blk, 4, 0xAA);

    /* Mismatches at 0, 4, 8 (All aligned 4-byte blocks) */
    kdi_FillVal(buf, 4, 0xBB);
    kdi_FillVal(buf + 4, 4, 0xBB);
    kdi_FillVal(buf + 8, 4, 0xBB);

    /* Search Range [0, 32). Max output 2 indices. */
    status = GenMemOpsFindNotBlockIndicesBoundU64(idxs, sizeof(idxs), &found, buf, USIZE_C(32), 0, 32, blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    /* Found 2 indices * 8 bytes = 16 bytes */
    assert(found == 16);
    assert(idxs[0] == 0);
    assert(idxs[1] == 4);
    /* Offset 8 is ignored */

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    /* 100KB buffer test.
     * Verifies handling of indices > 65535.
     */
    static u8 buf[102400];
    u8        blk[10];
    u64       idxs[10];
    usize     found;
    bool      status;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    kdi_FillVal(buf, sizeof(buf), U8_C(0xAA));
    kdi_FillVal(blk, 10, 0xAA);

    /* Mismatch at Offset 70000 (Valid u64, Aligned stride 10) */
    kdi_FillVal(buf + 70000, 10, 0xBB);

    status = GenMemOpsFindNotBlockIndicesBoundU64(idxs, sizeof(idxs), &found, buf, sizeof(buf), 0, sizeof(buf), blk, USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    /* Should find exactly 1 index (70000) * 8 bytes = 8 bytes */
    assert(found == 8);
    assert(idxs[0] == 70000);

    printf("PASSED\n");
}


void
EndValueClamping(void)
{
    u8    buf[32];
    u8    blk[4];
    u64   idxs[16];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "EndValueClamping -> ");

    kdi_FillVal(buf, USIZE_C(32), U8_C(0xAA));
    kdi_FillVal(blk, 4, 0xAA);

    /* Mismatch at last valid index.
     * Block size 4. Last valid start index = 32 - 4 = 28.
     */
    kdi_FillVal(buf + 28, 4, 0xBB);

    /* Request range [0, 100).
     * Should be clamped to [0, 32).
     */
    status = GenMemOpsFindNotBlockIndicesBoundU64(idxs, sizeof(idxs), &found, buf, USIZE_C(32), 0, 100, blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    /* 1 index * 8 bytes = 8 bytes */
    assert(found == 8);
    assert(idxs[0] == 28);

    printf("PASSED\n");
}


void
FindNotBlockIndicesBoundU64_U8(void)
{
    u8    buf[10];
    u8    blk = 0xAA;
    u64   idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndicesBoundU64_U8 -> ");

    kdi_FillVal(buf, sizeof(buf), 0xAA);

    /* Mismatch at Offset 2 and Offset 5 */
    buf[2] = 0xBB;
    buf[5] = 0xCC;

    /* Stride 1. Range [1, 7). 2 and 5 are inside. */
    status = GenMemOpsFindNotBlockIndicesBoundU64(idxs, sizeof(idxs), &found, buf, sizeof(buf), 1, 6, &blk, sizeof(u8));

    assert(status == RESULT_SUCCESS);
    /* 2 indices * 8 bytes = 16 bytes */
    assert(found == 16);
    assert(idxs[0] == 2);
    assert(idxs[1] == 5);

    printf("PASSED\n");
}


void
FindNotBlockIndicesBoundU64_U16(void)
{
    u16   buf[10];
    u16   blk = 0xAAAA;
    u64   idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndicesBoundU64_U16 -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);
    {
        int i;
        for (i = 0; i < 10; ++i)
            buf[i] = 0xAAAA;
    }

    /* Mismatches at Index 1 (Offset 2) and Index 8 (Offset 16) */
    buf[1] = 0xBBBB;
    buf[8] = 0xCCCC;

    /* Stride 2. Start 0. */
    status = GenMemOpsFindNotBlockIndicesBoundU64(idxs, sizeof(idxs), &found, buf, sizeof(buf), 0, 20, &blk, sizeof(u16));

    assert(status == RESULT_SUCCESS);
    /* 2 indices * 8 bytes = 16 bytes */
    assert(found == 16);
    assert(idxs[0] == 2);
    assert(idxs[1] == 16);

    printf("PASSED\n");
}


void
FindNotBlockIndicesBoundU64_U32(void)
{
    u32   buf[10];
    u32   blk = 0x12345678;
    u64   idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndicesBoundU64_U32 -> ");

    {
        int i;
        for (i = 0; i < 10; ++i)
            buf[i] = 0x12345678;
    }

    /* Buffer size 40 bytes.
     * Mismatches at Index 2 (Offset 8) and Index 5 (Offset 20).
     */
    buf[2] = 0x87654321;
    buf[5] = 0x99999999;

    /* Search Range: Start Offset 4, Count 24. Range [4, 28).
     * Block Size (Stride): 4.
     * Checks: 4, 8, 12, 16, 20, 24.
     */
    status = GenMemOpsFindNotBlockIndicesBoundU64(idxs, sizeof(idxs), &found, buf, sizeof(buf), 4, 24, &blk, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    /* 2 indices * 8 bytes = 16 bytes */
    assert(found == 16);
    assert(idxs[0] == 8);
    assert(idxs[1] == 20);

    printf("PASSED\n");
}


void
FindNotBlockIndicesBoundU64_U64(void)
{
    u64   buf[10];
    u64   blk = U64_C(0x1111222233334444);
    u64   idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndicesBoundU64_U64 -> ");

    {
        int i;
        for (i = 0; i < 10; ++i)
            buf[i] = blk;
    }

    /* Mismatch at Index 1 (Offset 8) and Index 3 (Offset 24) */
    buf[1] = U64_C(0xFFFFFFFFFFFFFFFF);
    buf[3] = U64_C(0xEEEEEEEEEEEEEEEE);

    /* Stride 8. Start 0. */
    status = GenMemOpsFindNotBlockIndicesBoundU64(idxs, sizeof(idxs), &found, buf, sizeof(buf), 0, sizeof(buf), &blk, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    /* 2 indices * 8 bytes = 16 bytes */
    assert(found == 16);
    assert(idxs[0] == 8);
    assert(idxs[1] == 24);

    printf("PASSED\n");
}


void
FindNotBlockIndicesBoundU64_Struct(void)
{
    typedef struct
    {
        u64 a;
        u64 b;
        u64 c;
    } TestStruct;

    TestStruct buf[5];
    TestStruct blk;
    u64        idxs[10];
    usize      found;
    bool       status;
    int        i;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndicesBoundU64_Struct -> ");

    blk.a = 1;
    blk.b = 2;
    blk.c = 3;

    for (i = 0; i < 5; ++i)
        buf[i] = blk;

    /* Mismatch at Index 1.
     * Struct size = 24 bytes.
     * Offset = 24.
     */
    buf[1].a = 99;

    /* Stride 24. Start 0. */
    status   = GenMemOpsFindNotBlockIndicesBoundU64(idxs, sizeof(idxs), &found, buf, sizeof(buf), 0, sizeof(buf), &blk, sizeof(TestStruct));

    assert(status == RESULT_SUCCESS);
    /* 1 index * 8 bytes = 8 bytes */
    assert(found == 8);
    assert(idxs[0] == 24);

    printf("PASSED\n");
}

#endif /* KD_ARCH_64BIT_INT */


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    BasicArguments();
    FindNone();
    AlignmentAndStride();
    OutputBufferCapacity();
    LargeBuffer();
    EndValueClamping();

    FindNotBlockIndicesBoundU64_U8();
    FindNotBlockIndicesBoundU64_U16();
    FindNotBlockIndicesBoundU64_U32();
    FindNotBlockIndicesBoundU64_U64();
    FindNotBlockIndicesBoundU64_Struct();
#else
    printf(LOG_PREFIX_CSTR "SKIPPED (64-bit integers not supported)\n");
#endif

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
