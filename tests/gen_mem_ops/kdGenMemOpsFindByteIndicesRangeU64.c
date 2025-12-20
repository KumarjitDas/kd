/**
 * @file kdGenMemOpsFindByteIndicesRangeU64.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindByteIndicesRangeU64 function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindByteIndicesRangeU64 function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


/* Helper to fill memory */
static void
kdi_FillVal(u8 *dst, usize sz, u8 val)
{
    usize i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        dst[i] = val;
    }
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT || 1
/* Assuming 64-bit support is available */

void
BasicArguments(void)
{
    u8    buf[16];
    u64   idxs[16];
    usize found = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* idxs pointer is null -> failure */
    status = GenMemOpsFindByteIndicesRangeU64(null, sizeof(idxs), &found, buf, USIZE_C(16), 0, 16, U8_C(0));
    assert(status == RESULT_FAILURE);

    /* found pointer is null -> failure */
    status = GenMemOpsFindByteIndicesRangeU64(idxs, sizeof(idxs), null, buf, USIZE_C(16), 0, 16, U8_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindByteIndicesRangeU64(idxs, sizeof(idxs), &found, null, USIZE_C(16), 0, 16, U8_C(0));
    assert(status == RESULT_FAILURE);

    /* idxs_sz is zero -> success but found=0 */
    found  = 55;
    status = GenMemOpsFindByteIndicesRangeU64(idxs, USIZE_C(0), &found, buf, USIZE_C(16), 0, 16, U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    /* ptr_sz is zero -> success, found=0 */
    found  = 55;
    status = GenMemOpsFindByteIndicesRangeU64(idxs, sizeof(idxs), &found, buf, USIZE_C(0), 0, 0, U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    /* idxs_sz smaller than sizeof(u64) -> success but found=0 */
    status = GenMemOpsFindByteIndicesRangeU64(idxs, USIZE_C(7), &found, buf, USIZE_C(16), 0, 16, U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    /* begin > end -> failure */
    status = GenMemOpsFindByteIndicesRangeU64(idxs, sizeof(idxs), &found, buf, USIZE_C(16), 10, 5, U8_C(0));
    assert(status == RESULT_FAILURE);

    /* end > ptr_sz -> failure */
    status = GenMemOpsFindByteIndicesRangeU64(idxs, sizeof(idxs), &found, buf, USIZE_C(16), 0, 17, U8_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
RangeConstraints(void)
{
    u8    buf[32];
    u64   idxs[16];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "RangeConstraints -> ");

    /* Init 0x00 */
    kdi_FillVal(buf, USIZE_C(32), U8_C(0x00));

    /* Set 0xFF at indices 5, 15, 25, 30 */
    buf[5]  = 0xFF;
    buf[15] = 0xFF;
    buf[25] = 0xFF;
    buf[30] = 0xFF;

    /* Range [10, 28). Should include 15 and 25. Exclude 5 and 30. */
    status  = GenMemOpsFindByteIndicesRangeU64(idxs, sizeof(idxs), &found, buf, USIZE_C(32), 10, 28, U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(found == 2);
    assert(idxs[0] == U64_C(15));
    assert(idxs[1] == U64_C(25));

    /* Range [15, 25). Should include 15. Exclude 25 (end exclusive). */
    status = GenMemOpsFindByteIndicesRangeU64(idxs, sizeof(idxs), &found, buf, USIZE_C(32), 15, 25, U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(found == 1);
    assert(idxs[0] == U64_C(15));

    printf("PASSED\n");
}


void
CapacityLimit(void)
{
    u8    buf[32];
    u64   idxs[2]; /* Capacity 2 elements (16 bytes) */
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "CapacityLimit -> ");

    /* Init 0xAA */
    kdi_FillVal(buf, USIZE_C(32), U8_C(0xAA));

    /* Range [0, 32). Found 32 matches. Capacity 2. */
    status = GenMemOpsFindByteIndicesRangeU64(idxs, sizeof(idxs), &found, buf, USIZE_C(32), 0, 32, U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(found == 2);
    assert(idxs[0] == U64_C(0));
    assert(idxs[1] == U64_C(1));

    printf("PASSED\n");
}


void
LargeCount(void)
{
    /* Use static for larger buffer */
    static u8  buf[2000];
    static u64 idxs[2000];
    usize      found;
    bool       status;
    usize      i;

    printf(LOG_PREFIX_CSTR "LargeCount -> ");

    kdi_FillVal(buf, USIZE_C(2000), U8_C(0x77));

    /* Find all 2000 items in range [0, 2000) */
    status = GenMemOpsFindByteIndicesRangeU64(idxs, sizeof(idxs), &found, buf, USIZE_C(2000), 0, 2000, U8_C(0x77));

    assert(status == RESULT_SUCCESS);
    assert(found == 2000);

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

#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT || 1
    BasicArguments();
    RangeConstraints();
    CapacityLimit();
    LargeCount();
#else
    printf("Skipping U64 tests: Architecture does not support 64-bit integers.\n");
#endif

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
