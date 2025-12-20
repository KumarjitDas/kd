/**
 * @file kdGenMemOpsFindByteIndicesU8.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindByteIndicesU8 function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindByteIndicesU8 function test"
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
    status = GenMemOpsFindByteIndicesU8(null, USIZE_C(16), &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* found pointer is null -> failure */
    status = GenMemOpsFindByteIndicesU8(idxs, USIZE_C(16), null, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindByteIndicesU8(idxs, USIZE_C(16), &found, null, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* idxs_sz is zero -> success but found=0 */
    found  = 55;
    status = GenMemOpsFindByteIndicesU8(idxs, USIZE_C(0), &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    /* ptr_sz is zero -> success, found=0 */
    found  = 55;
    status = GenMemOpsFindByteIndicesU8(idxs, USIZE_C(16), &found, buf, USIZE_C(0), U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(found == 0);

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

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Search for 0xFF */
    status = GenMemOpsFindByteIndicesU8(idxs, USIZE_C(16), &found, buf, USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    printf("PASSED\n");
}


void
FindMatches(void)
{
    u8    buf[16];
    u8    idxs[16];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindMatches -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Set 0xFF at indices 0, 5, 10, 15 */
    buf[0]  = 0xFF;
    buf[5]  = 0xFF;
    buf[10] = 0xFF;
    buf[15] = 0xFF;

    status  = GenMemOpsFindByteIndicesU8(idxs, USIZE_C(16), &found, buf, USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(found == 4);

    assert(idxs[0] == 0);
    assert(idxs[1] == 5);
    assert(idxs[2] == 10);
    assert(idxs[3] == 15);

    printf("PASSED\n");
}


void
CapacityLimit(void)
{
    u8    buf[16];
    u8    idxs[2]; /* Can only hold 2 indices */
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "CapacityLimit -> ");

    /* Init: 0xAA */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Search 0xAA. Buffer has 16 matches. Capacity is 2. */
    status = GenMemOpsFindByteIndicesU8(idxs, USIZE_C(2), &found, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    /* Should stop filling after 2 */
    assert(found == 2);

    assert(idxs[0] == 0);
    assert(idxs[1] == 1);

    printf("PASSED\n");
}


void
IndexValueLimit(void)
{
    u8    buf[300]; /* Buffer larger than valid range */
    u8    idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "IndexValueLimit -> ");

    /* Init: 0x00 */
    kdi_FillVal(buf, USIZE_C(300), U8_C(0x00));

    /* Boundary Check:
     * Valid indices: 0..254
     * Invalid indices: 255+
     */

    buf[254] = 0xFF; /* OK (Max Valid Index) */
    buf[255] = 0xFF; /* Invalid (Out of U8 limit for this API) */
    buf[256] = 0xFF; /* Invalid */

    /* Search 0xFF */
    status   = GenMemOpsFindByteIndicesU8(idxs, USIZE_C(10), &found, buf, USIZE_C(300), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);

    /* Should only find index 254. Indices >= 255 are ignored. */
    assert(found == 1);

    assert(idxs[0] == 254);

    printf("PASSED\n");
}


void
MaxIndicesCount(void)
{
    /* Max valid size is 255 (Indices 0..254) */
    u8    buf[255];
    u8    idxs[255];
    usize found;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "MaxIndicesCount -> ");

    /* Fill matching values 0..254 */
    kdi_FillVal(buf, USIZE_C(255), U8_C(0x77));

    /* Capacity 255. Buffer size 255. */
    status = GenMemOpsFindByteIndicesU8(idxs, USIZE_C(255), &found, buf, USIZE_C(255), U8_C(0x77));

    assert(status == RESULT_SUCCESS);
    assert(found == 255);

    /* Verify first and last */
    assert(idxs[0] == 0);
    assert(idxs[254] == 254);

    /* Check sequence */
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
    IndexValueLimit();
    MaxIndicesCount();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
