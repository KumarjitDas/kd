/**
 * @file kdGenMemOpsFindByteIndicesRangeU8.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindByteIndicesRangeU8 function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindByteIndicesRangeU8 function test"
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
    u8    idxs[16];
    usize found = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* idxs pointer is null -> failure */
    status = GenMemOpsFindByteIndicesRangeU8(null, sizeof(idxs), &found, buf, USIZE_C(16), 0, 16, U8_C(0));
    assert(status == RESULT_FAILURE);

    /* found pointer is null -> failure */
    status = GenMemOpsFindByteIndicesRangeU8(idxs, sizeof(idxs), null, buf, USIZE_C(16), 0, 16, U8_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindByteIndicesRangeU8(idxs, sizeof(idxs), &found, null, USIZE_C(16), 0, 16, U8_C(0));
    assert(status == RESULT_FAILURE);

    /* idxs_sz is zero -> success but found=0 */
    found  = 55;
    status = GenMemOpsFindByteIndicesRangeU8(idxs, USIZE_C(0), &found, buf, USIZE_C(16), 0, 16, U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    /* ptr_sz is zero -> success, found=0 */
    found  = 55;
    status = GenMemOpsFindByteIndicesRangeU8(idxs, sizeof(idxs), &found, buf, USIZE_C(0), 0, 0, U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    /* begin > end -> failure */
    status = GenMemOpsFindByteIndicesRangeU8(idxs, sizeof(idxs), &found, buf, USIZE_C(16), 10, 5, U8_C(0));
    assert(status == RESULT_FAILURE);

    /* end > ptr_sz -> failure */
    status = GenMemOpsFindByteIndicesRangeU8(idxs, sizeof(idxs), &found, buf, USIZE_C(16), 0, 17, U8_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
RangeConstraints(void)
{
    u8    buf[16];
    u8    idxs[16];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "RangeConstraints -> ");

    /* Init 0x00 */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Set 0xFF at indices 2, 5, 8, 12 */
    buf[2]  = 0xFF;
    buf[5]  = 0xFF;
    buf[8]  = 0xFF;
    buf[12] = 0xFF;

    /* Range [4, 10). Should include 5 and 8. Exclude 2 and 12. */
    status  = GenMemOpsFindByteIndicesRangeU8(idxs, sizeof(idxs), &found, buf, USIZE_C(16), 4, 10, U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(found == 2);
    assert(idxs[0] == 5);
    assert(idxs[1] == 8);

    /* Range [5, 8). Should include 5. Exclude 8 (end exclusive). */
    status = GenMemOpsFindByteIndicesRangeU8(idxs, sizeof(idxs), &found, buf, USIZE_C(16), 5, 8, U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(found == 1);
    assert(idxs[0] == 5);

    printf("PASSED\n");
}


void
CapacityLimit(void)
{
    u8    buf[16];
    u8    idxs[2]; /* Capacity 2 */
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "CapacityLimit -> ");

    /* Init 0xAA */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Range [0, 16). Found 16 matches. Capacity 2. */
    status = GenMemOpsFindByteIndicesRangeU8(idxs, sizeof(idxs), &found, buf, USIZE_C(16), 0, 16, U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(found == 2);
    assert(idxs[0] == 0);
    assert(idxs[1] == 1);

    printf("PASSED\n");
}


void
IndexValueLimit(void)
{
    /* Use static for large buffer */
    static u8 buf[300];
    u8        idxs[10];
    usize     found;
    bool      status;

    printf(LOG_PREFIX_CSTR "IndexValueLimit -> ");

    kdi_FillVal(buf, USIZE_C(300), U8_C(0x00));

    /* 1. Match at 254 (Max Valid for U8) */
    buf[254] = 0xFF;

    /* 2. Match at 255 (Invalid for U8 index) */
    buf[255] = 0xFF;

    /* Range [0, 300) */
    status   = GenMemOpsFindByteIndicesRangeU8(idxs, sizeof(idxs), &found, buf, USIZE_C(300), 0, 300, U8_C(0xFF));

    assert(status == RESULT_SUCCESS);

    /* Should only find index 254 */
    assert(found == 1);
    assert(idxs[0] == 254);

    printf("PASSED\n");
}


void
RangeStartOffset(void)
{
    /* Test boundary when begin_idx is near 254 */
    static u8 buf[300];
    u8        idxs[10];
    usize     found;
    bool      status;

    printf(LOG_PREFIX_CSTR "RangeStartOffset -> ");

    kdi_FillVal(buf, USIZE_C(300), U8_C(0x00));

    /* Match at 250 */
    buf[250] = 0x77;
    /* Match at 255 (Invalid) */
    buf[255] = 0x77;

    /* Range starts at 200. Covers 250 and 255. */
    status   = GenMemOpsFindByteIndicesRangeU8(idxs, sizeof(idxs), &found, buf, USIZE_C(300), 200, 300, U8_C(0x77));

    assert(status == RESULT_SUCCESS);
    assert(found == 1);
    assert(idxs[0] == 250);

    /* Range starts at 255. All indices >= 255 are invalid for U8 storage. */
    status = GenMemOpsFindByteIndicesRangeU8(idxs, sizeof(idxs), &found, buf, USIZE_C(300), 255, 300, U8_C(0x77));

    assert(status == RESULT_SUCCESS);
    assert(found == 0);

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
    IndexValueLimit();
    RangeStartOffset();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
