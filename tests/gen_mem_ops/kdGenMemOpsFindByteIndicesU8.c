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
#include "../../tests/utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindByteIndicesU8 function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


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
    assert(found == 0);

    /* found pointer is null -> failure */
    status = GenMemOpsFindByteIndicesU8(idxs, USIZE_C(16), null, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindByteIndicesU8(idxs, USIZE_C(16), &found, null, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(found == 0);

    /* idxs_sz is zero -> failure */
    found  = 55;
    status = GenMemOpsFindByteIndicesU8(idxs, USIZE_C(0), &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(found == 0); /* found should be modified to zero on failure */

    /* ptr_sz is zero -> failure */
    found  = 55;
    status = GenMemOpsFindByteIndicesU8(idxs, USIZE_C(16), &found, buf, USIZE_C(0), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(found == 0); /* found should be modified to zero on failure */

    /* idxs_sz > MAX_U8 -> failure */
    found  = 55;
    status = GenMemOpsFindByteIndicesU8(idxs, USIZE_C(256), &found, buf, USIZE_C(16), U8_C(0)); /* 256 is > MAX_U8 (255) */
    assert(status == RESULT_FAILURE);
    assert(found == 0); /* found should be modified to zero on failure */

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

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

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

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

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
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));

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
    kdi_Fill_u8(buf, USIZE_C(300), U8_C(0x00));

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
PtrSizeIndexLimit(void)
{
    u8    buf[300]; /* Buffer larger than valid range */
    u8    idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "PtrSizeIndexLimit -> ");

    /* Init: 0x00, idxs to 99 */
    kdi_Fill_u8(buf, USIZE_C(300), U8_C(0x00));
    kdi_Fill_u8(idxs, USIZE_C(10), U8_C(99));

    /*
     * Test case 1: ptr_sz > MAX_U8 and matches exist both in and out of U8 index range.
     * Valid indices: 0..254
     * Invalid indices: 255+
     */
    buf[254] = 0xFF; /* OK (Max Valid Index) */
    buf[255] = 0xFF; /* Invalid (Out of U8 limit for this API) */
    buf[256] = 0xFF; /* Invalid */

    /* Search 0xFF with ptr_sz > MAX_U8 (300).
     * Should only find index 254. Indices >= 255 are ignored. */
    status   = GenMemOpsFindByteIndicesU8(idxs, USIZE_C(10), &found, buf, USIZE_C(300), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(found == 1);
    assert(idxs[0] == 254);
    assert(idxs[1] == 99); /* Ensure no other index was written */


    /* Test case 2: ptr_sz = MAX_U8 + 1 (256) and multiple matches. */
    kdi_Fill_u8(buf, USIZE_C(300), U8_C(0x00)); /* Reset buffer */
    kdi_Fill_u8(idxs, USIZE_C(10), U8_C(99));   /* Reset idxs array for verification */
    buf[0]   = 0xFF;                            /* valid */
    buf[254] = 0xFF;                            /* valid */
    buf[255] = 0xFF;                            /* invalid due to U8 limit for index value */

    status   = GenMemOpsFindByteIndicesU8(idxs, USIZE_C(10), &found, buf, USIZE_C(256), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(found == 2);
    assert(idxs[0] == 0);
    assert(idxs[1] == 254);
    assert(idxs[2] == 99); /* Ensure no other index was written */


    /* Test case 3: ptr_sz = MAX_U8 (255) to ensure all matches within are found. */
    kdi_Fill_u8(buf, USIZE_C(300), U8_C(0x00)); /* Reset buffer */
    kdi_Fill_u8(idxs, USIZE_C(10), U8_C(99));   /* Reset idxs array for verification */
    buf[0]   = 0xFF;
    buf[100] = 0xFF;
    buf[254] = 0xFF;

    status   = GenMemOpsFindByteIndicesU8(idxs, USIZE_C(10), &found, buf, USIZE_C(255), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(found == 3);
    assert(idxs[0] == 0);
    assert(idxs[1] == 100);
    assert(idxs[2] == 254);
    assert(idxs[3] == 99); /* Ensure no other index was written */

    printf("PASSED\n");
}


void
CombinedLimits(void)
{
    u8    buf[300]; /* Buffer larger than valid range */
    u8    idxs[3];  /* Can hold 3 indices, less than potential matches and MAX_U8 */
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "CombinedLimits -> ");

    /* Init: 0x00, idxs to 99 */
    kdi_Fill_u8(buf, USIZE_C(300), U8_C(0x00));
    kdi_Fill_u8(idxs, USIZE_C(3), U8_C(99));

    /*
     * Set up multiple matches:
     * - Index 0: Should be found
     * - Index 100: Should be found (within idxs capacity if first wasn't enough)
     * - Index 254: Should be found (max U8 index)
     * - Index 255: Should be ignored (out of U8 index range)
     */
    buf[0]   = 0xFF;
    buf[100] = 0xFF;
    buf[254] = 0xFF;
    buf[255] = 0xFF; /* This index is > 254 and should be ignored */

    /* Search for 0xFF. idxs_sz is 3.
     * We expect to find 3 valid indices (0, 100, 254),
     * and stop filling after the 3rd.
     */
    status   = GenMemOpsFindByteIndicesU8(idxs, USIZE_C(3), &found, buf, USIZE_C(300), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(found == 3); /* Should find 3 matches, limited by idxs_sz */
    assert(idxs[0] == 0);
    assert(idxs[1] == 100);
    assert(idxs[2] == 254);
    /* No other values should be written beyond idxs capacity */
    assert(idxs[0] == 0);
    assert(idxs[1] == 100);
    assert(idxs[2] == 254);


    /* Test case 2: idxs capacity less than actual matches, and one is out of U8 range. */
    kdi_Fill_u8(buf, USIZE_C(300), U8_C(0x00)); /* Reset buffer */
    kdi_Fill_u8(idxs, USIZE_C(2), U8_C(99));    /* Reset idxs array, capacity 2 */
    buf[0]   = 0xCC;
    buf[1]   = 0xCC;
    buf[254] = 0xCC;
    buf[255] = 0xCC; /* Should be ignored */

    status   = GenMemOpsFindByteIndicesU8(idxs, USIZE_C(2), &found, buf, USIZE_C(300), U8_C(0xCC));
    assert(status == RESULT_SUCCESS);
    assert(found == 2);
    assert(idxs[0] == 0);
    assert(idxs[1] == 1);
    /* The index 254 match is ignored due to idxs capacity */

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
    kdi_Fill_u8(buf, USIZE_C(255), U8_C(0x77));

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
    PtrSizeIndexLimit(); /* New test for ptr_sz interaction with index limits */
    CombinedLimits();    /* New test for combined index and capacity limits */
    MaxIndicesCount();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
