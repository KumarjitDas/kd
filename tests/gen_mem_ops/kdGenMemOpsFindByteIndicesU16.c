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
#include "../../include/kd/fixed_width.h"
#include "../../tests/utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindByteIndicesU16 function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8    buf[16];
    u16   idxs[16];
    usize found = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* idxs pointer is null -> failure */
    status = GenMemOpsFindByteIndicesU16(null, USIZE_C(16) * SZ_U16, &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(found == 0);

    /* found pointer is null -> failure */
    status = GenMemOpsFindByteIndicesU16(idxs, USIZE_C(16) * SZ_U16, null, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindByteIndicesU16(idxs, USIZE_C(16) * SZ_U16, &found, null, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(found == 0);

    /* idxs_sz is zero -> failure */
    found  = 55;
    status = GenMemOpsFindByteIndicesU16(idxs, USIZE_C(0), &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(found == 0);

    /* ptr_sz is zero -> failure */
    found  = 55;
    status = GenMemOpsFindByteIndicesU16(idxs, USIZE_C(16) * SZ_U16, &found, buf, USIZE_C(0), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(found == 0);

    /* idxs_sz is smaller than sizeof(u16) (e.g. 1 byte) -> failure */
    /* Cannot store even a single u16 index */
    found  = 55;
    status = GenMemOpsFindByteIndicesU16(idxs, USIZE_C(1), &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(found == 0);

    /* idxs_sz not aligned by sizeof(u16) (e.g., 3 bytes) -> failure */
    /* Cannot store u16 indices in unaligned space */
    found  = 55;
    status = GenMemOpsFindByteIndicesU16(idxs, USIZE_C(3), &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(found == 0); /* found should be modified to zero on failure */

    /* idxs_sz implies capacity > MAX_U16 (0xFFFF) elements -> failure */
    /* For example, if idxs_sz = (MAX_U16 + 1) * SZ_U16 */
    found  = 55;
    status = GenMemOpsFindByteIndicesU16(idxs, USIZE_C(65536) * SZ_U16, &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(found == 0); /* found should be modified to zero on failure */

    /* idxs_sz = MAX_U16 (65535) bytes -> failure due to misalignment */
    found  = 55;
    status = GenMemOpsFindByteIndicesU16(idxs, MAX_U16, &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(found == 0); /* found should be modified to zero on failure */

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

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    status = GenMemOpsFindByteIndicesU16(idxs, USIZE_C(16) * SZ_U16, &found, buf, USIZE_C(16), U8_C(0xFF));

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

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    /* Matches at 0, 5, 10 */
    buf[0]  = 0xFF;
    buf[5]  = 0xFF;
    buf[10] = 0xFF;

    status  = GenMemOpsFindByteIndicesU16(idxs, USIZE_C(16) * SZ_U16, &found, buf, USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(found == 3 * SZ_U16);

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
    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0xAA));

    /* Buffer has 16 matches. Capacity is 2 elements = 4 bytes. */
    status = GenMemOpsFindByteIndicesU16(idxs, USIZE_C(2) * SZ_U16, &found, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(found == 2 * SZ_U16);

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

    kdi_Fill_u8(buf, USIZE_C(70000), U8_C(0x00));

    /* Valid range for U16 API logic: 0..MAX_U16 */
    /* An index value of MAX_U16 (65535) is considered valid. */

    buf[MAX_U16]     = 0xFF; /* OK (Max Valid U16 Index) */
    buf[MAX_U16 + 1] = 0xFF; /* Invalid (Out of bounds for U16 logic) */
    buf[MAX_U16 + 2] = 0xFF; /* Invalid */

    status           = GenMemOpsFindByteIndicesU16(idxs, USIZE_C(10) * SZ_U16, &found, buf, USIZE_C(70000), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);

    /* Should only find index MAX_U16 (65535) */
    assert(found == 1 * SZ_U16);
    assert(idxs[0] == MAX_U16);

    printf("PASSED\n");
}


void
MaxIndicesCount(void)
{
    /* Max possible U16 index value is MAX_U16 (65535).
     * Max valid idxs_sz (bytes) not exceeding MAX_U16 and aligned by SZ_U16 is (MAX_U16 - 1).
     * This allows for (MAX_U16 - 1) / SZ_U16 = 32767 elements (indices 0 to 32766).
     */
    static u8  buf[MAX_U16 + 1];             /* buf needs to be MAX_U16 + 1 bytes to enable searching up to index MAX_U16 */
    static u16 idxs[(MAX_U16 - 1) / SZ_U16]; /* idxs array can store (MAX_U16 - 1) / SZ_U16 elements */
    usize      found;
    bool       status;
    usize      i;
    usize      max_elements_capacity = (MAX_U16 - 1) / SZ_U16;

    printf(LOG_PREFIX_CSTR "MaxIndicesCount -> ");

    /* Fill matching values for all indices that can be stored */
    kdi_Fill_u8(buf, USIZE_C(MAX_U16 + 1), U8_C(0x00)); /* Clear buffer for size MAX_U16 + 1 */
    for (i = 0; i < max_elements_capacity; ++i)
    {
        buf[i] = U8_C(0x77);
    }
    /* Add some matches beyond what idxs can store, but within ptr_sz and U16 index range */
    /* This tests that the function stops filling idxs array when capacity is reached,
     * not when potential matches run out. */
    if (MAX_U16 >= max_elements_capacity + 10)
    {
        buf[max_elements_capacity + 10] = U8_C(0x77); /* Should not be found due to idxs_sz capacity limit */
    }
    if (MAX_U16 > max_elements_capacity)
    {
        buf[MAX_U16] = U8_C(0x77); /* This match exists but cannot be stored due to idxs_sz capacity */
    }


    /* idxs_sz is (MAX_U16 - 1) bytes, which is the maximum aligned size not exceeding MAX_U16. */
    status = GenMemOpsFindByteIndicesU16(idxs, USIZE_C(MAX_U16 - 1), &found, buf, USIZE_C(MAX_U16 + 1), U8_C(0x77));

    assert(status == RESULT_SUCCESS);
    assert(found == max_elements_capacity * SZ_U16);

    /* Verify first and last index actually stored */
    assert(idxs[0] == 0);
    assert(idxs[max_elements_capacity - 1] == (u16)(max_elements_capacity - 1)); /* Last index stored */

    /* Check sequence of stored indices */
    for (i = 0; i < max_elements_capacity; ++i) /* Iterate up to max_elements_capacity - 1 */
    {
        if (idxs[i] != (u16)i)
        {
            printf("Mismatch at %zu\\n", i);
            assert(kd_false);
        }
    }

    printf("PASSED\n");
}


void
PtrSizeIndexLimit(void)
{
    static u8 buf[70000]; /* Buffer larger than valid range for U16 indices */
    u16       idxs[10];
    usize     found;
    bool      status;

    printf(LOG_PREFIX_CSTR "PtrSizeIndexLimit -> ");

    /* Init: 0x00, idxs to 99 */
    kdi_Fill_u8(buf, USIZE_C(70000), U8_C(0x00));
    kdi_Fill_u8((u8 *)idxs, sizeof(idxs), U8_C(99)); /* Fill as bytes */

    /*
     * Test case 1: ptr_sz > MAX_U16_INDEX and matches exist both in and out of U16 index range.
     * Valid indices for U16: 0..MAX_U16
     * Invalid indices: MAX_U16 + 1+
     */
    buf[MAX_U16]     = 0xFF; /* OK (Max Valid U16 Index) */
    buf[MAX_U16 + 1] = 0xFF; /* Invalid (Out of U16 limit for this API) */
    buf[MAX_U16 + 2] = 0xFF; /* Invalid */

    /* Search 0xFF with ptr_sz > MAX_U16_INDEX (70000).
     * Should only find index MAX_U16. Indices > MAX_U16 are ignored. */
    status           = GenMemOpsFindByteIndicesU16(idxs, USIZE_C(10) * SZ_U16, &found, buf, USIZE_C(70000), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(found == 1 * SZ_U16);
    assert(idxs[0] == MAX_U16);


    /* Test case 2: ptr_sz = MAX_U16 + 1 (65536) and multiple matches. */
    kdi_Fill_u8(buf, USIZE_C(70000), U8_C(0x00));            /* Reset buffer */
    kdi_Fill_u8((u8 *)idxs, USIZE_C(10) * SZ_U16, U8_C(99)); /* Reset idxs array for verification */
    buf[0]           = 0xFF;                                 /* valid */
    buf[MAX_U16]     = 0xFF;                                 /* valid */
    buf[MAX_U16 + 1] = 0xFF;                                 /* invalid due to U16 limit for index value */

    status           = GenMemOpsFindByteIndicesU16(idxs, USIZE_C(10) * SZ_U16, &found, buf, USIZE_C(MAX_U16 + 1), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(found == 2 * SZ_U16);
    assert(idxs[0] == 0);
    assert(idxs[1] == MAX_U16);


    /* Test case 3: ptr_sz = MAX_U16 + 1 (65535 + 1 = 65536) to ensure all matches within are found. */
    kdi_Fill_u8(buf, USIZE_C(70000), U8_C(0x00));            /* Reset buffer */
    kdi_Fill_u8((u8 *)idxs, USIZE_C(10) * SZ_U16, U8_C(99)); /* Reset idxs array for verification */
    buf[0]       = 0xFF;
    buf[10000]   = 0xFF;
    buf[MAX_U16] = 0xFF;

    status       = GenMemOpsFindByteIndicesU16(idxs, USIZE_C(10) * SZ_U16, &found, buf, USIZE_C(MAX_U16 + 1), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(found == 3 * SZ_U16);
    assert(idxs[0] == 0);
    assert(idxs[1] == 10000);
    assert(idxs[2] == MAX_U16);

    printf("PASSED\n");
}


void
CombinedLimits(void)
{
    static u8 buf[70000]; /* Buffer larger than valid range for U16 indices */
    u16       idxs[3];    /* Can hold 3 indices, less than potential matches and MAX_U16 */
    usize     found;
    bool      status;

    printf(LOG_PREFIX_CSTR "CombinedLimits -> ");

    /* Init: 0x00, idxs to 99 */
    kdi_Fill_u8(buf, USIZE_C(70000), U8_C(0x00));
    kdi_Fill_u8((u8 *)idxs, USIZE_C(3) * SZ_U16, U8_C(99)); /* Fill as bytes */

    /*
     * Set up multiple matches:
     * - Index 0: Should be found
     * - Index 10000: Should be found
     * - Index MAX_U16: Should be found (max U16 index)
     * - Index MAX_U16 + 1: Should be ignored (out of U16 index range)
     * - Index 66000: Should be ignored (out of U16 index range)
     */
    buf[0]           = 0xFF;
    buf[10000]       = 0xFF;
    buf[MAX_U16]     = 0xFF;
    buf[MAX_U16 + 1] = 0xFF; /* This index is > MAX_U16 and should be ignored */
    buf[66000]       = 0xFF; /* This index is > MAX_U16 and should be ignored */

    /* Search for 0xFF. idxs capacity is 3 elements = 6 bytes.\
     * We expect to find 3 valid indices (0, 10000, 65534),\
     * and stop filling after the 3rd.\
     */
    status           = GenMemOpsFindByteIndicesU16(idxs, USIZE_C(3) * SZ_U16, &found, buf, USIZE_C(70000), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(found == 3 * SZ_U16); /* Should find 3 matches, limited by idxs_sz capacity */
    assert(idxs[0] == 0);
    assert(idxs[1] == 10000);
    assert(idxs[2] == MAX_U16);
    /* No other values should be written beyond idxs capacity */
    assert(idxs[0] == 0);
    assert(idxs[1] == 10000);
    assert(idxs[2] == MAX_U16);

    /* Test case 2: idxs capacity less than actual matches, and some are out of U16 range. */
    kdi_Fill_u8(buf, USIZE_C(70000), U8_C(0x00));           /* Reset buffer */
    kdi_Fill_u8((u8 *)idxs, USIZE_C(2) * SZ_U16, U8_C(99)); /* Reset idxs array, capacity for 2 elements */
    buf[0]           = 0xCC;
    buf[1]           = 0xCC;
    buf[MAX_U16]     = 0xCC;
    buf[MAX_U16 + 1] = 0xCC; /* Should be ignored */
    buf[66000]       = 0xCC; /* Should be ignored */

    status           = GenMemOpsFindByteIndicesU16(idxs, USIZE_C(2) * SZ_U16, &found, buf, USIZE_C(70000), U8_C(0xCC));
    assert(status == RESULT_SUCCESS);
    assert(found == 2 * SZ_U16);
    assert(idxs[0] == 0);
    assert(idxs[1] == 1);
    /* The index MAX_U16 match is ignored due to idxs capacity */

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
    PtrSizeIndexLimit();
    CombinedLimits();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
