/**
 * @file kdGenMemOpsFindNotByteIndicesBoundU8.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindNotByteIndicesBoundU8 function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindNotByteIndicesBoundU8 function test"
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
    /* Size in bytes */
    usize idxs_byte_sz = sizeof(idxs);

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* idxs is null -> failure */
    status = GenMemOpsFindNotByteIndicesBoundU8(null, idxs_byte_sz, &found, buf, USIZE_C(16), 0, 16, U8_C(0));
    assert(status == RESULT_FAILURE);

    /* idxs_sz is zero -> failure */
    status = GenMemOpsFindNotByteIndicesBoundU8(idxs, USIZE_C(0), &found, buf, USIZE_C(16), 0, 16, U8_C(0));
    assert(status == RESULT_FAILURE);

    /* found pointer is null -> failure */
    status = GenMemOpsFindNotByteIndicesBoundU8(idxs, idxs_byte_sz, null, buf, USIZE_C(16), 0, 16, U8_C(0));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure */
    status = GenMemOpsFindNotByteIndicesBoundU8(idxs, idxs_byte_sz, &found, null, USIZE_C(16), 0, 16, U8_C(0));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = GenMemOpsFindNotByteIndicesBoundU8(idxs, idxs_byte_sz, &found, buf, USIZE_C(0), 0, 16, U8_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
FindNone(void)
{
    u8    buf[16];
    u8    idxs[16];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNone -> ");

    /* All 0xAA */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Search range [0, 16). Find NOT 0xAA. Should find 0. */
    status = GenMemOpsFindNotByteIndicesBoundU8(idxs, sizeof(idxs), &found, buf, USIZE_C(16), 0, 16, U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    printf("PASSED\n");
}


void
RangeConstraints(void)
{
    u8    buf[32];
    u8    idxs[16];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "RangeConstraints -> ");

    kdi_FillVal(buf, USIZE_C(32), U8_C(0xAA));

    /* Mismatches at 2, 5, 8, 12, 20 */
    buf[2]  = 0xBB;
    buf[5]  = 0xBB;
    buf[8]  = 0xBB;
    buf[12] = 0xBB;
    buf[20] = 0xBB;

    /* Start 4, Count 6.
     * Effective Range: [4, 10).
     * Indices inside: 4, 5, 6, 7, 8, 9.
     * Mismatches inside: 5 and 8.
     * 2 is before. 12 and 20 are after.
     */
    status  = GenMemOpsFindNotByteIndicesBoundU8(idxs, sizeof(idxs), &found, buf, USIZE_C(32), 4, 6, U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    /* 2 indices * 1 byte = 2 bytes */
    assert(found == 2);
    assert(idxs[0] == 5);
    assert(idxs[1] == 8);

    printf("PASSED\n");
}


void
OutputBufferCapacity(void)
{
    u8    buf[16];
    u8    idxs[2]; /* Capacity for 2 indices */
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "OutputBufferCapacity -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* 3 Mismatches in range */
    buf[1] = 0xBB;
    buf[2] = 0xBB;
    buf[3] = 0xBB;

    /* Range [0, 16). Max output 2. */
    status = GenMemOpsFindNotByteIndicesBoundU8(idxs, sizeof(idxs), &found, buf, USIZE_C(16), 0, 16, U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(found == 2);
    assert(idxs[0] == 1);
    assert(idxs[1] == 2);
    /* Index 3 is ignored */

    printf("PASSED\n");
}


void
EndValueClamping(void)
{
    u8    buf[16];
    u8    idxs[16];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "EndValueClamping -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Mismatch at last index 15 */
    buf[15] = 0xBB;

    /* Start 0, Count 100.
     * Clamped to 16. Range [0, 16).
     * Should find index 15.
     */
    status  = GenMemOpsFindNotByteIndicesBoundU8(idxs, sizeof(idxs), &found, buf, USIZE_C(16), 0, 100, U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(found == 1);
    assert(idxs[0] == 15);

    printf("PASSED\n");
}


void
IndexRangeLimit(void)
{
    u8    buf[300];
    u8    idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "IndexRangeLimit -> ");

    kdi_FillVal(buf, USIZE_C(300), U8_C(0xAA));

    /* Mismatch at 10 (Valid u8) */
    buf[10]  = 0xBB;

    /* Mismatch at 250 (Valid u8) */
    buf[250] = 0xBB;

    /* Mismatch at 260 (Invalid u8).
     * 260 fits in 'buf' and is theoretically reachable via bound [0, 300).
     * However, the return type is u8. 260 > 255.
     * The logic must ignore it.
     */
    buf[260] = 0xBB;

    status   = GenMemOpsFindNotByteIndicesBoundU8(idxs, sizeof(idxs), &found, buf, USIZE_C(300), 0, 300, U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    /* Should find exactly 2 indices (10 and 250). */
    assert(found == 2);
    assert(idxs[0] == 10);
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
    RangeConstraints();
    OutputBufferCapacity();
    EndValueClamping();
    IndexRangeLimit();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
