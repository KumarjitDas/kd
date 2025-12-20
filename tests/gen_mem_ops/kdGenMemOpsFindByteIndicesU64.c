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


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindByteIndicesU64 function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT || 1
/* Assuming U64 is available based on function existence */

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
    u64   idxs[16];
    usize found = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* idxs pointer is null -> failure */
    status = GenMemOpsFindByteIndicesU64(null, sizeof(idxs), &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* found pointer is null -> failure */
    status = GenMemOpsFindByteIndicesU64(idxs, sizeof(idxs), null, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindByteIndicesU64(idxs, sizeof(idxs), &found, null, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* idxs_sz is zero -> success but found=0 */
    found  = 55;
    status = GenMemOpsFindByteIndicesU64(idxs, USIZE_C(0), &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    /* ptr_sz is zero -> success, found=0 */
    found  = 55;
    status = GenMemOpsFindByteIndicesU64(idxs, sizeof(idxs), &found, buf, USIZE_C(0), U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    /* idxs_sz is smaller than sizeof(u64) (e.g. 7 bytes) -> success but found=0 */
    /* Cannot store even a single u64 index */
    found  = 55;
    status = GenMemOpsFindByteIndicesU64(idxs, USIZE_C(7), &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(found == 0);

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

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    status = GenMemOpsFindByteIndicesU64(idxs, sizeof(idxs), &found, buf, USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    printf("PASSED\n");
}


void
FindMatches(void)
{
    u8    buf[32];
    u64   idxs[32];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindMatches -> ");

    kdi_FillVal(buf, USIZE_C(32), U8_C(0x00));

    /* Matches at 0, 10, 20, 30 */
    buf[0]  = 0xFF;
    buf[10] = 0xFF;
    buf[20] = 0xFF;
    buf[30] = 0xFF;

    status  = GenMemOpsFindByteIndicesU64(idxs, sizeof(idxs), &found, buf, USIZE_C(32), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(found == 4);

    assert(idxs[0] == U64_C(0));
    assert(idxs[1] == U64_C(10));
    assert(idxs[2] == U64_C(20));
    assert(idxs[3] == U64_C(30));

    printf("PASSED\n");
}


void
CapacityLimit(void)
{
    u8    buf[32];
    u64   idxs[3]; /* Capacity for 3 elements = 24 bytes */
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "CapacityLimit -> ");

    /* Init: 0xAA */
    kdi_FillVal(buf, USIZE_C(32), U8_C(0xAA));

    /* Buffer has 32 matches. Capacity is 3 elements (24 bytes). */
    status = GenMemOpsFindByteIndicesU64(idxs, sizeof(idxs), &found, buf, USIZE_C(32), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(found == 3);

    assert(idxs[0] == U64_C(0));
    assert(idxs[1] == U64_C(1));
    assert(idxs[2] == U64_C(2));

    printf("PASSED\n");
}


void
LargeCount(void)
{
    /* Use static for larger buffers */
    static u8  buf[2000];
    static u64 idxs[2000];
    usize      found;
    bool       status;
    usize      i;

    printf(LOG_PREFIX_CSTR "LargeCount -> ");

    /* Fill matching values 0..1999 */
    kdi_FillVal(buf, USIZE_C(2000), U8_C(0x77));

    status = GenMemOpsFindByteIndicesU64(idxs, sizeof(idxs), &found, buf, USIZE_C(2000), U8_C(0x77));

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
    FindNone();
    FindMatches();
    CapacityLimit();
    LargeCount();
#else
    printf("Skipping U64 tests: Architecture does not support 64-bit integers.\n");
#endif

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
