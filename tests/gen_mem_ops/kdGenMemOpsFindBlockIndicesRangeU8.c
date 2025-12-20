/**
 * @file kdGenMemOpsFindBlockIndicesRangeU8.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindBlockIndicesRangeU8 function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindBlockIndicesRangeU8 function test"
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
    status = GenMemOpsFindBlockIndicesRangeU8(null, USIZE_C(16), &found, buf, USIZE_C(16), 0, 16, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* found pointer is null -> failure */
    status = GenMemOpsFindBlockIndicesRangeU8(idxs, USIZE_C(16), null, buf, USIZE_C(16), 0, 16, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindBlockIndicesRangeU8(idxs, USIZE_C(16), &found, null, USIZE_C(16), 0, 16, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    status = GenMemOpsFindBlockIndicesRangeU8(idxs, USIZE_C(16), &found, buf, USIZE_C(16), 0, 16, null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* idxs_sz is zero -> success but found=0 */
    found  = 55;
    status = GenMemOpsFindBlockIndicesRangeU8(idxs, USIZE_C(0), &found, buf, USIZE_C(16), 0, 16, blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    /* ptr_sz is zero -> success, found=0 */
    status = GenMemOpsFindBlockIndicesRangeU8(idxs, USIZE_C(16), &found, buf, USIZE_C(0), 0, 0, blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    /* block_sz is zero -> failure */
    status = GenMemOpsFindBlockIndicesRangeU8(idxs, USIZE_C(16), &found, buf, USIZE_C(16), 0, 16, blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* begin > end -> failure */
    status = GenMemOpsFindBlockIndicesRangeU8(idxs, USIZE_C(16), &found, buf, USIZE_C(16), 10, 5, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* end > ptr_sz -> failure */
    status = GenMemOpsFindBlockIndicesRangeU8(idxs, USIZE_C(16), &found, buf, USIZE_C(16), 0, 17, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
RangeConstraints(void)
{
    u8    buf[32];
    u8    blk[4];
    u8    idxs[16];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "RangeConstraints -> ");

    /* Init 0x00 */
    kdi_FillVal(buf, USIZE_C(32), U8_C(0x00));

    /* Block size 4. */
    /* Place blocks at offsets: 0, 4, 8, 12, 16, 20, 24, 28 */
    kdi_FillVal(blk, USIZE_C(4), U8_C(0xAA));

    kdi_FillVal(buf + 4, 4, 0xAA);  /* Offset 4 */
    kdi_FillVal(buf + 8, 4, 0xAA);  /* Offset 8 */
    kdi_FillVal(buf + 12, 4, 0xAA); /* Offset 12 */
    kdi_FillVal(buf + 16, 4, 0xAA); /* Offset 16 */
    kdi_FillVal(buf + 20, 4, 0xAA); /* Offset 20 */

    /* Range [8, 20).
     * Includes start index 8.
     * Includes 12.
     * Excludes 4 (before range).
     * Includes 16 (16 is valid start, 16+4=20, fits?).
     * Wait, Range is [begin, end).
     * Block at 16 occupies [16, 20). If end is 20, then bytes 0..19 are valid.
     * A block starting at 16 (bytes 16,17,18,19) fits perfectly within [8, 20).
     * Block at 20 occupies [20, 24). Starts at end. Should be excluded.
     */

    status = GenMemOpsFindBlockIndicesRangeU8(idxs, USIZE_C(16), &found, buf, USIZE_C(32), 8, 20, blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);

    /* Found 3 blocks (8, 12, 16). Total size = 3 * 4 = 12. */
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
    u8    idxs[2]; /* Capacity 2 indices */
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
    status = GenMemOpsFindBlockIndicesRangeU8(idxs, USIZE_C(2), &found, buf, USIZE_C(16), 0, 16, blk, USIZE_C(2));

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
    u8    idxs[4];
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
     * Offsets checked relative to 1 with step 2: 1, 3, 5...
     * Actual block is at 2.
     * 2 is unaligned relative to start 1 (modulo 2).
     * Should fail.
     */
    status = GenMemOpsFindBlockIndicesRangeU8(idxs, USIZE_C(4), &found, buf, USIZE_C(8), 1, 6, blk, USIZE_C(2));

    assert(status == RESULT_FAILURE);
    assert(found == 0);

    /* Range starts at 0. [0, 6).
     * Offsets checked: 0, 2, 4...
     * Block at 2 is aligned. Should find.
     */
    status = GenMemOpsFindBlockIndicesRangeU8(idxs, USIZE_C(4), &found, buf, USIZE_C(8), 0, 6, blk, USIZE_C(2));
    assert(status == RESULT_SUCCESS);
    assert(found == 2);
    assert(idxs[0] == 2);

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
    kdi_FillVal(blk, USIZE_C(5), U8_C(0xFF));

    /* Match at Offset 250 (Valid index <= 254) */
    kdi_FillVal(buf + 250, 5, 0xFF);

    /* Match at Offset 255 (Invalid index > 254) */
    kdi_FillVal(buf + 255, 5, 0xFF);

    /* Range [0, 300) */
    status = GenMemOpsFindBlockIndicesRangeU8(idxs, USIZE_C(10), &found, buf, USIZE_C(300), 0, 300, blk, USIZE_C(5));

    assert(status == RESULT_SUCCESS);

    /* Only index 250 should be found. Total bytes = 5. */
    assert(found == 5);
    assert(idxs[0] == 250);

    printf("PASSED\n");
}


void
U16_FindBlockIndicesRange(void)
{
    /* Buffer < 255 bytes (127 * 2 = 254) */
    u16   buf[127];
    u16   blk[1];
    u8    idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "U16_FindBlockIndicesRange -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);
    blk[0]   = 0xAAAA;

    /* Match at Index 2 (Offset 4) */
    buf[2]   = 0xAAAA;
    /* Match at Index 50 (Offset 100) */
    buf[50]  = 0xAAAA;
    /* Match at Index 126 (Offset 252) */
    buf[126] = 0xAAAA;

    /* Range in bytes: [10, 200).
     * Includes Offset 100.
     * Excludes Offset 4 (before).
     * Excludes Offset 252 (after).
     */
    status   = GenMemOpsFindBlockIndicesRangeU8(idxs, USIZE_C(10), &found, buf, sizeof(buf), 10, 200, blk, sizeof(u16));

    assert(status == RESULT_SUCCESS);

    /* Found 1 block (Offset 100). Total bytes = 2. */
    assert(found == 2);
    assert(idxs[0] == 100);

    printf("PASSED\n");
}


void
U32_FindBlockIndicesRange(void)
{
    /* Buffer < 255 bytes (63 * 4 = 252) */
    u32   buf[63];
    u32   blk[1];
    u8    idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_FindBlockIndicesRange -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);
    blk[0]  = 0xBBBBBBBB;

    /* Offset 4 */
    buf[1]  = 0xBBBBBBBB;
    /* Offset 248 (Index 62) */
    buf[62] = 0xBBBBBBBB;

    /* Range [0, 252). Includes both. */
    status  = GenMemOpsFindBlockIndicesRangeU8(idxs, USIZE_C(10), &found, buf, sizeof(buf), 0, 252, blk, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    assert(found == 8);
    assert(idxs[0] == 4);
    assert(idxs[1] == 248);

    /* Range [0, 100). Includes only offset 4. */
    status = GenMemOpsFindBlockIndicesRangeU8(idxs, USIZE_C(10), &found, buf, sizeof(buf), 0, 100, blk, sizeof(u32));
    assert(status == RESULT_SUCCESS);
    assert(found == 4);
    assert(idxs[0] == 4);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_FindBlockIndicesRange(void)
{
    /* Buffer < 255 bytes (30 * 8 = 240) */
    u64   buf[30];
    u64   blk[1];
    u8    idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "U64_FindBlockIndicesRange -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);
    blk[0] = U64_C(0xCCCCCCCCCCCCCCCC);

    /* Offset 8 */
    buf[1] = blk[0];
    /* Offset 16 */
    buf[2] = blk[0];

    /* Range [16, 240).
     * Start index 16.
     * Offset 16 is aligned (16 == 16). Included.
     * Offset 8 is before. Excluded.
     */
    status = GenMemOpsFindBlockIndicesRangeU8(idxs, USIZE_C(10), &found, buf, sizeof(buf), 16, 240, blk, sizeof(u64));

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
    /* Struct 24 bytes. 10 items = 240 bytes. */
    kdi_TestStruct buf[10];
    kdi_TestStruct blk;
    u8             idxs[10];
    usize          found;
    bool           status;
    usize          sz = sizeof(kdi_TestStruct);

    printf(LOG_PREFIX_CSTR "Struct_FindBlockIndicesRange -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    blk.a  = 0x1111111111111111;
    blk.b  = 0x2222222222222222;
    blk.c  = 0x3333333333333333;

    /* Match at 0 */
    buf[0] = blk;
    /* Match at 24 (Index 1) */
    buf[1] = blk;
    /* Match at 216 (Index 9) */
    buf[9] = blk;

    /* Range [24, 240).
     * Includes 24.
     * Includes 216.
     * Excludes 0.
     */
    status = GenMemOpsFindBlockIndicesRangeU8(idxs, USIZE_C(10), &found, buf, sizeof(buf), 24, 240, &blk, sz);

    assert(status == RESULT_SUCCESS);

    /* Found 2 blocks (24, 216). Total bytes = 48. */
    assert(found == 48);
    assert(idxs[0] == 24);
    assert(idxs[1] == 216);

    printf("PASSED\n");
}


void
LargeArray_FindBlockIndicesRange(void)
{
    /* Buffer 500 bytes. */
    u8    buf[500];
    u8    blk[5];
    u8    idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "LargeArray_FindBlockIndicesRange -> ");

    kdi_FillVal(buf, sizeof(buf), 0);
    kdi_FillVal(blk, sizeof(blk), 0xEE);

    /* Match at 100 */
    kdi_FillVal(buf + 100, 5, 0xEE);
    /* Match at 250 */
    kdi_FillVal(buf + 250, 5, 0xEE);

    /* Range [50, 200). Includes 100. Excludes 250. */
    status = GenMemOpsFindBlockIndicesRangeU8(idxs, USIZE_C(10), &found, buf, sizeof(buf), 50, 200, blk, 5);

    assert(status == RESULT_SUCCESS);
    assert(found == 5);
    assert(idxs[0] == 100);

    /* Range [200, 300). Includes 250. */
    /* Start index 200. 250 is aligned relative to 200 (diff 50, mod 5 == 0). */
    status = GenMemOpsFindBlockIndicesRangeU8(idxs, USIZE_C(10), &found, buf, sizeof(buf), 200, 300, blk, 5);

    assert(status == RESULT_SUCCESS);
    assert(found == 5);
    assert(idxs[0] == 250);

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
