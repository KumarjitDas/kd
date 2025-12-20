/**
 * @file kdGenMemOpsFindByteIndicesRangeU16.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindByteIndicesRangeU16 function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindByteIndicesRangeU16 function test"
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
    u16   idxs[16];
    usize found = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* idxs pointer is null -> failure */
    status = GenMemOpsFindByteIndicesRangeU16(null, sizeof(idxs), &found, buf, USIZE_C(16), 0, 16, U8_C(0));
    assert(status == RESULT_FAILURE);

    /* found pointer is null -> failure */
    status = GenMemOpsFindByteIndicesRangeU16(idxs, sizeof(idxs), null, buf, USIZE_C(16), 0, 16, U8_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindByteIndicesRangeU16(idxs, sizeof(idxs), &found, null, USIZE_C(16), 0, 16, U8_C(0));
    assert(status == RESULT_FAILURE);

    /* idxs_sz is zero -> success but found=0 */
    found  = 55;
    status = GenMemOpsFindByteIndicesRangeU16(idxs, USIZE_C(0), &found, buf, USIZE_C(16), 0, 16, U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    /* ptr_sz is zero -> success, found=0 */
    found  = 55;
    status = GenMemOpsFindByteIndicesRangeU16(idxs, sizeof(idxs), &found, buf, USIZE_C(0), 0, 0, U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    /* begin > end -> failure */
    status = GenMemOpsFindByteIndicesRangeU16(idxs, sizeof(idxs), &found, buf, USIZE_C(16), 10, 5, U8_C(0));
    assert(status == RESULT_FAILURE);

    /* end > ptr_sz -> failure */
    status = GenMemOpsFindByteIndicesRangeU16(idxs, sizeof(idxs), &found, buf, USIZE_C(16), 0, 17, U8_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
RangeConstraints(void)
{
    u8    buf[16];
    u16   idxs[16];
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
    status  = GenMemOpsFindByteIndicesRangeU16(idxs, sizeof(idxs), &found, buf, USIZE_C(16), 4, 10, U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(found == 2);
    assert(idxs[0] == 5);
    assert(idxs[1] == 8);

    /* Range [5, 8). Should include 5. Exclude 8 (end exclusive). */
    status = GenMemOpsFindByteIndicesRangeU16(idxs, sizeof(idxs), &found, buf, USIZE_C(16), 5, 8, U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(found == 1);
    assert(idxs[0] == 5);

    printf("PASSED\n");
}


void
CapacityLimit(void)
{
    u8    buf[16];
    u16   idxs[2]; /* Capacity 2 elements (4 bytes) */
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "CapacityLimit -> ");

    /* Init 0xAA */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Range [0, 16). Found 16 matches. Capacity 2. */
    status = GenMemOpsFindByteIndicesRangeU16(idxs, sizeof(idxs), &found, buf, USIZE_C(16), 0, 16, U8_C(0xAA));

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
    static u8 buf[70000];
    u16       idxs[10];
    usize     found;
    bool      status;

    printf(LOG_PREFIX_CSTR "IndexValueLimit -> ");

    kdi_FillVal(buf, USIZE_C(70000), U8_C(0x00));

    /* Match at 65534 (Max Valid for U16) */
    buf[65534] = 0xFF;

    /* Match at 65535 (Invalid for U16 index) */
    buf[65535] = 0xFF;

    /* Range [0, 70000) */
    status     = GenMemOpsFindByteIndicesRangeU16(idxs, sizeof(idxs), &found, buf, USIZE_C(70000), 0, 70000, U8_C(0xFF));

    assert(status == RESULT_SUCCESS);

    /* Should only find index 65534 */
    assert(found == 1);
    assert(idxs[0] == 65534);

    printf("PASSED\n");
}


void
RangeStartOffset(void)
{
    /* Test boundary when begin_idx is deep in the buffer */
    static u8 buf[70000];
    u16       idxs[10];
    usize     found;
    bool      status;

    printf(LOG_PREFIX_CSTR "RangeStartOffset -> ");

    kdi_FillVal(buf, USIZE_C(70000), U8_C(0x00));

    /* Match at 60000 */
    buf[60000] = 0x77;

    /* Match at 65530 */
    buf[65530] = 0x77;

    /* Range starts at 50000. Covers 60000 and 65530. */
    status     = GenMemOpsFindByteIndicesRangeU16(idxs, sizeof(idxs), &found, buf, USIZE_C(70000), 50000, 65534, U8_C(0x77));

    assert(status == RESULT_SUCCESS);
    assert(found == 2);
    assert(idxs[0] == 60000);
    assert(idxs[1] == 65530);

    /* Range starts at 65535. Invalid start for U16 storage logic?
     * Actually, if begin_idx >= 65535, any found index would be invalid.
     */
    status = GenMemOpsFindByteIndicesRangeU16(idxs, sizeof(idxs), &found, buf, USIZE_C(70000), 65535, 70000, U8_C(0x77));

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
