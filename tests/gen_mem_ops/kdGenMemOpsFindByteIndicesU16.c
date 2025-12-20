/**
 * @file kdGenMemOpsFindByteIndicesU16.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindByteIndicesU16 function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindByteIndicesU16 function test"
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
    status = GenMemOpsFindByteIndicesU16(null, sizeof(idxs), &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* found pointer is null -> failure */
    status = GenMemOpsFindByteIndicesU16(idxs, sizeof(idxs), null, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindByteIndicesU16(idxs, sizeof(idxs), &found, null, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* idxs_sz is zero -> success but found=0 */
    found  = 55;
    status = GenMemOpsFindByteIndicesU16(idxs, USIZE_C(0), &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    /* ptr_sz is zero -> success, found=0 */
    found  = 55;
    status = GenMemOpsFindByteIndicesU16(idxs, sizeof(idxs), &found, buf, USIZE_C(0), U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    /* idxs_sz is smaller than sizeof(u16) (e.g. 1 byte) -> success but found=0 */
    /* Cannot store even a single u16 index */
    found  = 55;
    status = GenMemOpsFindByteIndicesU16(idxs, USIZE_C(1), &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    printf("PASSED\n");
}


void
FindNone(void)
{
    u8    buf[16];
    u16   idxs[16];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNone -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    status = GenMemOpsFindByteIndicesU16(idxs, sizeof(idxs), &found, buf, USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    printf("PASSED\n");
}


void
FindMatches(void)
{
    u8    buf[16];
    u16   idxs[16];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindMatches -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    /* Matches at 0, 5, 10 */
    buf[0]  = 0xFF;
    buf[5]  = 0xFF;
    buf[10] = 0xFF;

    status  = GenMemOpsFindByteIndicesU16(idxs, sizeof(idxs), &found, buf, USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(found == 3);

    assert(idxs[0] == 0);
    assert(idxs[1] == 5);
    assert(idxs[2] == 10);

    printf("PASSED\n");
}


void
CapacityLimit(void)
{
    u8    buf[16];
    u16   idxs[2]; /* Capacity for 2 elements = 4 bytes */
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "CapacityLimit -> ");

    /* Init: 0xAA */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Buffer has 16 matches. Capacity is 2 elements (4 bytes). */
    status = GenMemOpsFindByteIndicesU16(idxs, sizeof(idxs), &found, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(found == 2);

    assert(idxs[0] == 0);
    assert(idxs[1] == 1);

    printf("PASSED\n");
}


void
IndexValueLimit(void)
{
    /* Use static to avoid large stack allocation */
    static u8 buf[70000];
    u16       idxs[10];
    usize     found;
    bool      status;

    printf(LOG_PREFIX_CSTR "IndexValueLimit -> ");

    kdi_FillVal(buf, USIZE_C(70000), U8_C(0x00));

    /* * Valid range for U16 API logic: 0..65534
     * Invalid: >= 65535
     */

    buf[65534] = 0xFF; /* OK (Max Valid) */
    buf[65535] = 0xFF; /* Invalid (Out of bounds for U16 logic) */
    buf[65536] = 0xFF; /* Invalid */

    status     = GenMemOpsFindByteIndicesU16(idxs, sizeof(idxs), &found, buf, USIZE_C(70000), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);

    /* Should only find index 65534 */
    assert(found == 1);
    assert(idxs[0] == 65534);

    printf("PASSED\n");
}


void
MaxIndicesCount(void)
{
    /* Max valid size is 65535 (Indices 0..65534) */
    static u8  buf[65535];
    static u16 idxs[65535];
    usize      found;
    bool       status;
    usize      i;

    printf(LOG_PREFIX_CSTR "MaxIndicesCount -> ");

    /* Fill matching values */
    kdi_FillVal(buf, USIZE_C(65535), U8_C(0x77));

    /* sizeof(idxs) is 65535 * 2 bytes */
    status = GenMemOpsFindByteIndicesU16(idxs, sizeof(idxs), &found, buf, USIZE_C(65535), U8_C(0x77));

    assert(status == RESULT_SUCCESS);
    assert(found == 65535);

    /* Verify first and last */
    assert(idxs[0] == 0);
    assert(idxs[65534] == 65534);

    /* Check sequence */
    for (i = 0; i < 65535; ++i)
    {
        if (idxs[i] != (u16)i)
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
