/**
 * @file kdGenMemOpsFindByteIndicesU64.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindByteIndicesU64 function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../../include/kd/fixed_width.h" /* For MAX_U64, SZ_U64 */
#include "../../tests/utils.h"            /* For kdi_Fill_u8 */


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindByteIndicesU64 function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT

void
BasicArguments(void)
{
    u8    buf[16];
    u64   idxs[16];
    usize found = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* idxs pointer is null -> failure */
    status = GenMemOpsFindByteIndicesU64(null, sizeof(idxs), &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(found == 0); /* found should be modified to zero on failure */

    /* found pointer is null -> failure */
    status = GenMemOpsFindByteIndicesU64(idxs, sizeof(idxs), null, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindByteIndicesU64(idxs, sizeof(idxs), &found, null, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(found == 0); /* found should be modified to zero on failure */

    /* idxs_sz is zero -> failure */
    found  = 55;
    status = GenMemOpsFindByteIndicesU64(idxs, USIZE_C(0), &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(found == 0); /* found should be modified to zero on failure */

    /* ptr_sz is zero -> failure */
    found  = 55;
    status = GenMemOpsFindByteIndicesU64(idxs, sizeof(idxs), &found, buf, USIZE_C(0), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(found == 0); /* found should be modified to zero on failure */

    /* idxs_sz is smaller than sizeof(u64) (e.g. 7 bytes) -> failure */
    /* Cannot store even a single u64 index */
    found  = 55;
    status = GenMemOpsFindByteIndicesU64(idxs, USIZE_C(7), &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(found == 0);

    /* idxs_sz not aligned by sizeof(u64) (e.g., 9 bytes) -> failure */
    /* Cannot store u64 indices in unaligned space */
    found  = 55;
    status = GenMemOpsFindByteIndicesU64(idxs, USIZE_C(9), &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(found == 0); /* found should be modified to zero on failure */

    /* idxs_sz implies capacity > MAX_U64 elements -> failure */
    /* If MAX_U64 is very large, this test checks for overflow in capacity calculation. */
    found  = 55;
    status = GenMemOpsFindByteIndicesU64(idxs, ((usize)MAX_U64 + 1) * SZ_U64, &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);
    assert(found == 0); /* found should be modified to zero on failure */

    printf("PASSED\n");
}


void
FindNone(void)
{
    u8    buf[16];
    u64   idxs[16];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNone -> ");

    kdi_Fill_u8(buf, USIZE_C(16), U8_C(0x00));

    status = GenMemOpsFindByteIndicesU64(idxs, sizeof(idxs), &found, buf, USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    printf("PASSED\n");
}


void
FindMatches(void)
{
    u8    buf[64];
    u64   idxs[64];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindMatches -> ");

    kdi_Fill_u8(buf, USIZE_C(64), U8_C(0x00));

    /* Matches at 0, 15, 30, 45, 60 */
    buf[0]  = 0xFF;
    buf[15] = 0xFF;
    buf[30] = 0xFF;
    buf[45] = 0xFF;
    buf[60] = 0xFF;

    status  = GenMemOpsFindByteIndicesU64(idxs, sizeof(idxs), &found, buf, USIZE_C(64), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(found == 5 * SZ_U64);

    assert(idxs[0] == U64_C(0));
    assert(idxs[1] == U64_C(15));
    assert(idxs[2] == U64_C(30));
    assert(idxs[3] == U64_C(45));
    assert(idxs[4] == U64_C(60));

    printf("PASSED\n");
}


void
CapacityLimit(void)
{
    u8    buf[64];
    u64   idxs[3]; /* Capacity for 3 elements = 24 bytes */
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "CapacityLimit -> ");

    /* Init: 0xAA */
    kdi_Fill_u8(buf, USIZE_C(64), U8_C(0xAA));

    /* Buffer has 64 matches. Capacity is 3 elements (24 bytes). */
    status = GenMemOpsFindByteIndicesU64(idxs, sizeof(idxs), &found, buf, USIZE_C(64), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(found == 3 * SZ_U64);

    assert(idxs[0] == U64_C(0));
    assert(idxs[1] == U64_C(1));
    assert(idxs[2] == U64_C(2));

    printf("PASSED\n");
}


void
IndexValueLimit(void)
{
    u8    buf[2048]; /* Using a fixed-size buffer to test index storage within its bounds. */
    u64   idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "IndexValueLimit -> ");

    /* Init: 0x00 */
    kdi_Fill_u8(buf, sizeof(buf), U8_C(0x00));

    /*
     * Valid range for U64 API logic: 0..MAX_U64.
     * Since MAX_U64 is extremely large, we focus on testing the function's ability
     * to correctly find and store valid indices within a realistically sized buffer.
     * Indices are correctly stored as u64.
     */

    /* Place matches within the buffer. These indices are well within MAX_U64. */
    buf[0]    = 0xFF;
    buf[1024] = 0xFF;
    buf[2047] = 0xFF; /* Last byte of the buffer */

    /* Search for 0xFF within the actual buffer size. */
    status    = GenMemOpsFindByteIndicesU64(idxs, sizeof(idxs), &found, buf, sizeof(buf), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    /* Should find 3 matches, as all are within the buffer and idxs capacity. */
    assert(found == 3 * SZ_U64);
    assert(idxs[0] == U64_C(0));
    assert(idxs[1] == U64_C(1024));
    assert(idxs[2] == U64_C(2047));

    printf("PASSED\n");
}


void
PtrSizeIndexLimit(void)
{
    u8    buf[2048]; /* Smaller buffer */
    u64   idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "PtrSizeIndexLimit -> ");

    /* Init: 0x00, idxs to 99 */
    kdi_Fill_u8(buf, sizeof(buf), U8_C(0x00));
    kdi_Fill_u8((u8 *)idxs, sizeof(idxs), U8_C(99)); /* Fill as bytes for verification */

    /*
     * Test case 1: ptr_sz covers only a part of the buffer.
     * Matches outside ptr_sz should not be found.
     */
    buf[100] = 0xFF; /* Should be found */
    buf[200] = 0xFF; /* Should be found */
    buf[300] = 0xFF; /* Should NOT be found (ptr_sz = 250) */

    status   = GenMemOpsFindByteIndicesU64(idxs, sizeof(idxs), &found, buf, USIZE_C(250), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(found == 2 * SZ_U64);
    assert(idxs[0] == U64_C(100));
    assert(idxs[1] == U64_C(200));


    /* Test case 2: ptr_sz equals buffer size, testing matches within buffer.
     */
    kdi_Fill_u8(buf, sizeof(buf), U8_C(0x00));       /* Reset buffer */
    kdi_Fill_u8((u8 *)idxs, sizeof(idxs), U8_C(99)); /* Reset idxs array for verification */
    buf[0]    = 0xFF;                                /* valid */
    buf[1000] = 0xFF;                                /* valid */

    status    = GenMemOpsFindByteIndicesU64(idxs, sizeof(idxs), &found, buf, sizeof(buf), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(found == 2 * SZ_U64);
    assert(idxs[0] == U64_C(0));
    assert(idxs[1] == U64_C(1000));


    /* Test case 3: ptr_sz is a specific value smaller than buffer size, filling idxs capacity. */
    kdi_Fill_u8(buf, sizeof(buf), U8_C(0x00));       /* Reset buffer */
    kdi_Fill_u8((u8 *)idxs, sizeof(idxs), U8_C(99)); /* Reset idxs array for verification */
    buf[0] = 0xFF;
    buf[1] = 0xFF;
    buf[2] = 0xFF;
    buf[3] = 0xFF;
    buf[4] = 0xFF;

    status = GenMemOpsFindByteIndicesU64(idxs, USIZE_C(5) * SZ_U64, &found, buf, sizeof(buf), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(found == 5 * SZ_U64);
    assert(idxs[0] == U64_C(0));
    assert(idxs[1] == U64_C(1));
    assert(idxs[2] == U64_C(2));
    assert(idxs[3] == U64_C(3));
    assert(idxs[4] == U64_C(4));

    printf("PASSED\n");
}


void
CombinedLimits(void)
{
    u8    buf[2048]; /* Smaller buffer */
    u64   idxs[3];   /* Can hold 3 indices */
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "CombinedLimits -> ");

    /* Init: 0x00, idxs to 99 */
    kdi_Fill_u8(buf, sizeof(buf), U8_C(0x00));
    kdi_Fill_u8((u8 *)idxs, sizeof(idxs), U8_C(99)); /* Fill as bytes */

    /*
     * Set up multiple matches:
     * - Index 0: Should be found
     * - Index 100: Should be found
     * - Index 200: Should be found (max idxs capacity)
     * - Index 300: Should be ignored due to idxs capacity limit
     */
    buf[0]   = 0xFF;
    buf[100] = 0xFF;
    buf[200] = 0xFF;
    buf[300] = 0xFF; /* This will be found in the buffer, but idxs capacity is 3. */

    /* Search for 0xFF. ptr_sz covers the whole buffer.
     * idxs capacity is 3 elements. We expect to find 3 valid indices (0, 100, 200),
     * and stop filling after the 3rd.
     */
    status   = GenMemOpsFindByteIndicesU64(idxs, sizeof(idxs), &found, buf, sizeof(buf), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(found == 3 * SZ_U64); /* Should find 3 matches, limited by idxs_sz capacity */
    assert(idxs[0] == U64_C(0));
    assert(idxs[1] == U64_C(100));
    assert(idxs[2] == U64_C(200));

    /* Test case 2: idxs capacity less than actual matches, and ptr_sz limits search. */
    kdi_Fill_u8(buf, sizeof(buf), U8_C(0x00));              /* Reset buffer */
    kdi_Fill_u8((u8 *)idxs, USIZE_C(2) * SZ_U64, U8_C(99)); /* Reset idxs array, capacity for 2 elements */
    buf[0] = 0xCC;
    buf[1] = 0xCC;
    buf[2] = 0xCC;                                          /* This match exists but ptr_sz will limit it, or idxs capacity */

    status = GenMemOpsFindByteIndicesU64(idxs, USIZE_C(2) * SZ_U64, &found, buf, USIZE_C(2), U8_C(0xCC));
    assert(status == RESULT_SUCCESS);
    assert(found == 2 * SZ_U64);
    assert(idxs[0] == U64_C(0));
    assert(idxs[1] == U64_C(1));
    /* The index 2 match is ignored due to ptr_sz limit of 2, not idxs capacity */

    printf("PASSED\n");
}


void
MaxIndicesCount(void)
{
    /* Max valid size for a buffer is limited by memory, but idxs array itself can hold
     * up to its allocated byte size / SZ_U64 elements.
     * We'll test with a reasonable large number (2000 elements) that fully fills the idxs array.
     */
    u8    buf[2000];
    u64   idxs[2000];
    usize found;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "MaxIndicesCount -> ");

    /* Fill matching values 0..1999 */
    kdi_Fill_u8(buf, USIZE_C(2000), U8_C(0x77));

    status = GenMemOpsFindByteIndicesU64(idxs, sizeof(idxs), &found, buf, USIZE_C(2000), U8_C(0x77));

    assert(status == RESULT_SUCCESS);
    assert(found == 2000 * SZ_U64);

    assert(idxs[0] == U64_C(0));
    assert(idxs[1999] == U64_C(1999));

    /* Verify sequence */
    for (i = 0; i < 2000; ++i)
    {
        if (idxs[i] != (u64)i)
        {
            printf("Mismatch at %zu\n", i);
            assert(kd_false);
        }
    }

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
    FindMatches();
    CapacityLimit();
    IndexValueLimit();
    PtrSizeIndexLimit();
    CombinedLimits();
    MaxIndicesCount();
#else
    printf("Skipping U64 tests: Architecture does not support 64-bit integers.\\n");
#endif

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
