/**
 * @file kdGenMemOpsFindBlockIndicesRangeU16.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindBlockIndicesRangeU16 function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindBlockIndicesRangeU16 function test"
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
    u16   idxs[16];
    usize found = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* idxs pointer is null -> failure */
    status = GenMemOpsFindBlockIndicesRangeU16(null, sizeof(idxs), &found, buf, USIZE_C(16), 0, 16, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* found pointer is null -> failure */
    status = GenMemOpsFindBlockIndicesRangeU16(idxs, sizeof(idxs), null, buf, USIZE_C(16), 0, 16, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindBlockIndicesRangeU16(idxs, sizeof(idxs), &found, null, USIZE_C(16), 0, 16, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    status = GenMemOpsFindBlockIndicesRangeU16(idxs, sizeof(idxs), &found, buf, USIZE_C(16), 0, 16, null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* idxs_sz is zero -> success but found=0 */
    found  = 55;
    status = GenMemOpsFindBlockIndicesRangeU16(idxs, USIZE_C(0), &found, buf, USIZE_C(16), 0, 16, blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    /* ptr_sz is zero -> success, found=0 */
    status = GenMemOpsFindBlockIndicesRangeU16(idxs, sizeof(idxs), &found, buf, USIZE_C(0), 0, 0, blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    /* block_sz is zero -> failure */
    status = GenMemOpsFindBlockIndicesRangeU16(idxs, sizeof(idxs), &found, buf, USIZE_C(16), 0, 16, blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* begin > end -> failure */
    status = GenMemOpsFindBlockIndicesRangeU16(idxs, sizeof(idxs), &found, buf, USIZE_C(16), 10, 5, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* end > ptr_sz -> failure */
    status = GenMemOpsFindBlockIndicesRangeU16(idxs, sizeof(idxs), &found, buf, USIZE_C(16), 0, 17, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
RangeConstraints(void)
{
    u8    buf[32];
    u8    blk[4];
    u16   idxs[16];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "RangeConstraints -> ");

    /* Init 0x00 */
    kdi_FillVal(buf, USIZE_C(32), U8_C(0x00));

    /* Block size 4. */
    kdi_FillVal(blk, USIZE_C(4), U8_C(0xAA));

    kdi_FillVal(buf + 4, 4, 0xAA);  /* Offset 4 */
    kdi_FillVal(buf + 8, 4, 0xAA);  /* Offset 8 */
    kdi_FillVal(buf + 12, 4, 0xAA); /* Offset 12 */
    kdi_FillVal(buf + 16, 4, 0xAA); /* Offset 16 */
    kdi_FillVal(buf + 20, 4, 0xAA); /* Offset 20 */

    /* Range [8, 20).
     * Includes 8.
     * Includes 12.
     * Includes 16 (Block [16..19] fits in [8..20)).
     * Excludes 4 (before).
     * Excludes 20 (starts at end).
     */
    status = GenMemOpsFindBlockIndicesRangeU16(idxs, sizeof(idxs), &found, buf, USIZE_C(32), 8, 20, blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);

    /* Found 3 blocks. Total size = 3 * 4 = 12. */
    assert(found == 12);

    assert(idxs[0] == 8);
    assert(idxs[1] == 12);
    assert(idxs[2] == 16);

    printf("PASSED\n");
}


void
CapacityLimit(void)
{
    u8    buf[16];
    u8    blk[2];
    u16   idxs[2]; /* Capacity 2 elements (4 bytes) */
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "CapacityLimit -> ");

    /* Fill repeating 0xAA 0xBB */
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

    /* Range [0, 16). 8 blocks exist. Capacity 2. */
    status = GenMemOpsFindBlockIndicesRangeU16(idxs, sizeof(idxs), &found, buf, USIZE_C(16), 0, 16, blk, USIZE_C(2));

    assert(status == RESULT_SUCCESS);

    /* Found 2 blocks. Total bytes = 2 * 2 = 4. */
    assert(found == 4);

    assert(idxs[0] == 0);
    assert(idxs[1] == 2);

    printf("PASSED\n");
}


void
UnalignedMatchFail(void)
{
    u8    buf[8];
    u8    blk[2];
    u16   idxs[4];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "UnalignedMatchFail -> ");

    /* Buffer: 0, 1, 2, 3... */
    buf[0] = 0;
    buf[1] = 1;
    buf[2] = 2;
    buf[3] = 3;
    buf[4] = 4;
    buf[5] = 5;

    /* Block: 2, 3 (Offset 2) */
    blk[0] = 2;
    blk[1] = 3;

    /* Range starts at 1. [1, 6).
     * Offsets checked: 1, 3, 5...
     * Offset 2 is unaligned relative to start 1. Fail.
     */
    status = GenMemOpsFindBlockIndicesRangeU16(idxs, sizeof(idxs), &found, buf, USIZE_C(8), 1, 6, blk, USIZE_C(2));

    assert(status == RESULT_FAILURE);
    assert(found == 0);

    /* Range starts at 0. [0, 6).
     * Offsets checked: 0, 2, 4...
     * Offset 2 is aligned. Pass.
     */
    status = GenMemOpsFindBlockIndicesRangeU16(idxs, sizeof(idxs), &found, buf, USIZE_C(8), 0, 6, blk, USIZE_C(2));
    assert(status == RESULT_SUCCESS);
    assert(found == 2);
    assert(idxs[0] == 2);

    printf("PASSED\n");
}


void
IndexValueLimit(void)
{
    /* Use static for large buffer */
    static u8 buf[70000];
    u8        blk[5];
    u16       idxs[10];
    usize     found;
    bool      status;

    printf(LOG_PREFIX_CSTR "IndexValueLimit -> ");

    kdi_FillVal(buf, USIZE_C(70000), U8_C(0x00));
    kdi_FillVal(blk, USIZE_C(5), U8_C(0xFF));

    /* Match at Offset 65530. (65530 + 5 = 65535).
     * 65530 <= 65534. Valid.
     */
    kdi_FillVal(buf + 65530, 5, 0xFF);

    /* Match at Offset 65535. (Invalid index > 65534). */
    kdi_FillVal(buf + 65535, 5, 0xFF);

    /* Range [0, 70000) */
    status = GenMemOpsFindBlockIndicesRangeU16(idxs, sizeof(idxs), &found, buf, USIZE_C(70000), 0, 70000, blk, USIZE_C(5));

    assert(status == RESULT_SUCCESS);

    /* Only index 65530 found. Total bytes = 5. */
    assert(found == 5);
    assert(idxs[0] == 65530);

    printf("PASSED\n");
}


void
U16_FindBlockIndicesRange(void)
{
    /* Buffer < 65535 bytes (32000 * 2 = 64000) */
    static u16 buf[32000];
    u16        blk[1];
    u16        idxs[10];
    usize      found;
    bool       status;

    printf(LOG_PREFIX_CSTR "U16_FindBlockIndicesRange -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);
    blk[0]     = 0xAAAA;

    /* Match at Index 2 (Offset 4) */
    buf[2]     = 0xAAAA;
    /* Match at Index 30000 (Offset 60000) */
    buf[30000] = 0xAAAA;
    /* Match at Index 31000 (Offset 62000) */
    buf[31000] = 0xAAAA;

    /* Range [10, 61000).
     * Includes Offset 60000.
     * Excludes Offset 4 (before).
     * Excludes Offset 62000 (after).
     */
    status     = GenMemOpsFindBlockIndicesRangeU16(idxs, sizeof(idxs), &found, buf, sizeof(buf), 10, 61000, blk, sizeof(u16));

    assert(status == RESULT_SUCCESS);

    /* Found 1 block. Total bytes = 2. */
    assert(found == 2);
    assert(idxs[0] == 60000);

    printf("PASSED\n");
}


void
U32_FindBlockIndicesRange(void)
{
    /* Buffer < 65535 bytes (16000 * 4 = 64000) */
    static u32 buf[16000];
    u32        blk[1];
    u16        idxs[10];
    usize      found;
    bool       status;

    printf(LOG_PREFIX_CSTR "U32_FindBlockIndicesRange -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);
    blk[0]     = 0xBBBBBBBB;

    /* Offset 4 */
    buf[1]     = 0xBBBBBBBB;
    /* Offset 63996 (Index 15999) */
    buf[15999] = 0xBBBBBBBB;

    /* Range [0, 64000). Includes both. */
    status     = GenMemOpsFindBlockIndicesRangeU16(idxs, sizeof(idxs), &found, buf, sizeof(buf), 0, 64000, blk, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    assert(found == 8);
    assert(idxs[0] == 4);
    assert(idxs[1] == 63996);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_FindBlockIndicesRange(void)
{
    /* Buffer < 65535 bytes (8000 * 8 = 64000) */
    static u64 buf[8000];
    u64        blk[1];
    u16        idxs[10];
    usize      found;
    bool       status;

    printf(LOG_PREFIX_CSTR "U64_FindBlockIndicesRange -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);
    blk[0] = U64_C(0xCCCCCCCCCCCCCCCC);

    /* Offset 8 */
    buf[1] = blk[0];
    /* Offset 16 */
    buf[2] = blk[0];

    /* Range [16, 64000).
     * Start index 16.
     * Offset 16 is aligned (16 == 16). Included.
     * Offset 8 is before. Excluded.
     */
    status = GenMemOpsFindBlockIndicesRangeU16(idxs, sizeof(idxs), &found, buf, sizeof(buf), 16, 64000, blk, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    assert(found == 8);
    assert(idxs[0] == 16);

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
Struct_FindBlockIndicesRange(void)
{
    /* Struct 24 bytes. 2700 items = 64800 bytes. */
    static kdi_TestStruct buf[2700];
    kdi_TestStruct        blk;
    u16                   idxs[10];
    usize                 found;
    bool                  status;
    usize                 sz = sizeof(kdi_TestStruct);

    printf(LOG_PREFIX_CSTR "Struct_FindBlockIndicesRange -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    blk.a     = 0x1111111111111111;
    blk.b     = 0x2222222222222222;
    blk.c     = 0x3333333333333333;

    /* Match at 0 */
    buf[0]    = blk;
    /* Match at 24 (Index 1) */
    buf[1]    = blk;
    /* Match at 64776 (Index 2699) */
    buf[2699] = blk;

    /* Range [24, 64800).
     * Includes 24.
     * Includes 64776.
     * Excludes 0.
     */
    status    = GenMemOpsFindBlockIndicesRangeU16(idxs, sizeof(idxs), &found, buf, sizeof(buf), 24, 64800, &blk, sz);

    assert(status == RESULT_SUCCESS);

    /* Found 2 blocks (24, 64776). Total bytes = 48. */
    assert(found == 48);
    assert(idxs[0] == 24);
    assert(idxs[1] == 64776);

    printf("PASSED\n");
}


void
LargeArray_FindBlockIndicesRange(void)
{
    /* Buffer > 65535. */
    static u8 buf[70000];
    u8        blk[5];
    u16       idxs[10];
    usize     found;
    bool      status;

    printf(LOG_PREFIX_CSTR "LargeArray_FindBlockIndicesRange -> ");

    kdi_FillVal(buf, sizeof(buf), 0);
    kdi_FillVal(blk, sizeof(blk), 0xEE);

    /* Match at 100 */
    kdi_FillVal(buf + 100, 5, 0xEE);
    /* Match at 65530 */
    kdi_FillVal(buf + 65530, 5, 0xEE);

    /* Range [50, 65534).
     * Includes 100.
     * Includes 65530 (since block [65530..65534] ends at 65535).
     * Wait, Range [begin, end) -> [50, 65534).
     * Block at 65530 occupies [65530, 65535).
     * This exceeds 'end' (65534). Should be excluded.
     */
    status = GenMemOpsFindBlockIndicesRangeU16(idxs, sizeof(idxs), &found, buf, sizeof(buf), 50, 65534, blk, 5);

    assert(status == RESULT_SUCCESS);
    assert(found == 5);
    assert(idxs[0] == 100);

    /* Range [60000, 70000).
     * Includes 65530.
     * 65530 is valid index.
     * Block fits in range.
     */
    status = GenMemOpsFindBlockIndicesRangeU16(idxs, sizeof(idxs), &found, buf, sizeof(buf), 60000, 70000, blk, 5);

    assert(status == RESULT_SUCCESS);
    assert(found == 5);
    assert(idxs[0] == 65530);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    RangeConstraints();
    CapacityLimit();
    UnalignedMatchFail();
    IndexValueLimit();

    U16_FindBlockIndicesRange();
    U32_FindBlockIndicesRange();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_FindBlockIndicesRange();
#endif
    Struct_FindBlockIndicesRange();
    LargeArray_FindBlockIndicesRange();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
