/**
 * @file kdGenMemOpsFindNotBlockIndicesU64.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindNotBlockIndicesU64 function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindNotBlockIndicesU64 function test"
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
    status = GenMemOpsFindNotBlockIndicesU64(null, idxs_byte_sz, &found, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* idxs_sz is zero -> failure */
    status = GenMemOpsFindNotBlockIndicesU64(idxs, USIZE_C(0), &found, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* found pointer is null -> failure */
    status = GenMemOpsFindNotBlockIndicesU64(idxs, idxs_byte_sz, null, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindNotBlockIndicesU64(idxs, idxs_byte_sz, &found, null, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr_sz is zero -> failure */
    status = GenMemOpsFindNotBlockIndicesU64(idxs, idxs_byte_sz, &found, buf, USIZE_C(0), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    status = GenMemOpsFindNotBlockIndicesU64(idxs, idxs_byte_sz, &found, buf, USIZE_C(16), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = GenMemOpsFindNotBlockIndicesU64(idxs, idxs_byte_sz, &found, buf, USIZE_C(16), blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* block_sz > ptr_sz -> failure */
    status = GenMemOpsFindNotBlockIndicesU64(idxs, idxs_byte_sz, &found, buf, USIZE_C(4), blk, USIZE_C(16));
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

    /* All match. Should find 0 bytes. */
    status = GenMemOpsFindNotBlockIndicesU64(idxs, sizeof(idxs), &found, buf, USIZE_C(16), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(found == 0);

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

    /* 3 Mismatches: Offset 0, 4, 8 */
    kdi_FillVal(buf, 4, 0xBB);
    kdi_FillVal(buf + 4, 4, 0xBB);
    kdi_FillVal(buf + 8, 4, 0xBB);

    /* Passed size is 16 bytes. Can only hold 2 indices. */
    status = GenMemOpsFindNotBlockIndicesU64(idxs, sizeof(idxs), &found, buf, USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    /* Found size in bytes. 2 filled * 8 bytes = 16 bytes. */
    assert(found == 16);
    assert(idxs[0] == 0);
    assert(idxs[1] == 4);
    /* Offset 8 is ignored */

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    /* 100KB buffer check.
     * Validates that logic works for offsets > 65535.
     */
    static u8 buf[102400];
    u8        blk[10];
    u64       idxs[10];
    usize     found;
    bool      status;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    kdi_FillVal(buf, sizeof(buf), U8_C(0xAA));
    kdi_FillVal(blk, 10, 0xAA);

    /* Mismatch at Offset 70000 */
    kdi_FillVal(buf + 70000, 10, 0xBB);

    status = GenMemOpsFindNotBlockIndicesU64(idxs, sizeof(idxs), &found, buf, sizeof(buf), blk, USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    /* 1 index * 8 bytes = 8 bytes found */
    assert(found == 8);
    assert(idxs[0] == 70000);

    printf("PASSED\n");
}


void
FindNotBlockIndicesU64_U8(void)
{
    u8    buf[10];
    u8    blk = 0xAA;
    u64   idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndicesU64_U8 -> ");

    kdi_FillVal(buf, sizeof(buf), 0xAA);

    /* Mismatch at Offset 5 and 8 */
    buf[5] = 0xBB;
    buf[8] = 0xCC;

    status = GenMemOpsFindNotBlockIndicesU64(idxs, sizeof(idxs), &found, buf, sizeof(buf), &blk, sizeof(u8));

    assert(status == RESULT_SUCCESS);
    /* 2 indices * 8 bytes = 16 bytes found */
    assert(found == 16);
    assert(idxs[0] == 5);
    assert(idxs[1] == 8);

    printf("PASSED\n");
}


void
FindNotBlockIndicesU64_U16(void)
{
    u16   buf[10];
    u16   blk = 0xAAAA;
    u64   idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndicesU64_U16 -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);
    {
        int i;
        for (i = 0; i < 10; ++i)
            buf[i] = 0xAAAA;
    }

    /* Mismatches at Index 1 (Offset 2) and Index 8 (Offset 16) */
    buf[1] = 0xBBBB;
    buf[8] = 0xCCCC;

    status = GenMemOpsFindNotBlockIndicesU64(idxs, sizeof(idxs), &found, buf, sizeof(buf), &blk, sizeof(u16));

    assert(status == RESULT_SUCCESS);
    /* 2 indices * 8 bytes = 16 bytes found */
    assert(found == 16);
    assert(idxs[0] == 2);
    assert(idxs[1] == 16);

    printf("PASSED\n");
}


void
FindNotBlockIndicesU64_U32(void)
{
    u32   buf[10];
    u32   blk = 0x12345678;
    u64   idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndicesU64_U32 -> ");

    {
        int i;
        for (i = 0; i < 10; ++i)
            buf[i] = 0x12345678;
    }

    /* Mismatches at Index 2 (Offset 8) and Index 5 (Offset 20) */
    buf[2] = 0x87654321;
    buf[5] = 0x99999999;

    status = GenMemOpsFindNotBlockIndicesU64(idxs, sizeof(idxs), &found, buf, sizeof(buf), &blk, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    /* 2 indices * 8 bytes = 16 bytes found */
    assert(found == 16);
    assert(idxs[0] == 8);
    assert(idxs[1] == 20);

    printf("PASSED\n");
}


void
FindNotBlockIndicesU64_U64(void)
{
    u64   buf[10];
    u64   blk = U64_C(0x1111222233334444);
    u64   idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndicesU64_U64 -> ");

    {
        int i;
        for (i = 0; i < 10; ++i)
            buf[i] = blk;
    }

    /* Mismatch at Index 1 (Offset 8) and Index 3 (Offset 24) */
    buf[1] = U64_C(0xFFFFFFFFFFFFFFFF);
    buf[3] = U64_C(0xEEEEEEEEEEEEEEEE);

    status = GenMemOpsFindNotBlockIndicesU64(idxs, sizeof(idxs), &found, buf, sizeof(buf), &blk, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    /* 2 indices * 8 bytes = 16 bytes found */
    assert(found == 16);
    assert(idxs[0] == 8);
    assert(idxs[1] == 24);

    printf("PASSED\n");
}


void
FindNotBlockIndicesU64_Struct(void)
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

    printf(LOG_PREFIX_CSTR "FindNotBlockIndicesU64_Struct -> ");

    blk.a = 1;
    blk.b = 2;
    blk.c = 3;

    for (i = 0; i < 5; ++i)
        buf[i] = blk;

    /* Mismatch at Index 1 (Offset 24) */
    buf[1].a = 99;

    status   = GenMemOpsFindNotBlockIndicesU64(idxs, sizeof(idxs), &found, buf, sizeof(buf), &blk, sizeof(TestStruct));

    assert(status == RESULT_SUCCESS);
    /* 1 index * 8 bytes = 8 bytes found */
    assert(found == 8);
    assert(idxs[0] == 24); /* Offset 24 */

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
    OutputBufferCapacity();
    LargeBuffer();

    FindNotBlockIndicesU64_U8();
    FindNotBlockIndicesU64_U16();
    FindNotBlockIndicesU64_U32();
    FindNotBlockIndicesU64_U64();
    FindNotBlockIndicesU64_Struct();
#else
    printf(LOG_PREFIX_CSTR "SKIPPED (64-bit integers not supported)\n");
#endif

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
