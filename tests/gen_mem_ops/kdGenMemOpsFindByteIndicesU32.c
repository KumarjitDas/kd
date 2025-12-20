/**
 * @file kdGenMemOpsFindByteIndicesU32.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindByteIndicesU32 function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindByteIndicesU32 function test"
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
    u32   idxs[16];
    usize found = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* idxs pointer is null -> failure */
    status = GenMemOpsFindByteIndicesU32(null, sizeof(idxs), &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* found pointer is null -> failure */
    status = GenMemOpsFindByteIndicesU32(idxs, sizeof(idxs), null, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindByteIndicesU32(idxs, sizeof(idxs), &found, null, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* idxs_sz is zero -> success but found=0 */
    found  = 55;
    status = GenMemOpsFindByteIndicesU32(idxs, USIZE_C(0), &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    /* ptr_sz is zero -> success, found=0 */
    found  = 55;
    status = GenMemOpsFindByteIndicesU32(idxs, sizeof(idxs), &found, buf, USIZE_C(0), U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    /* idxs_sz is smaller than sizeof(u32) (e.g. 3 bytes) -> success but found=0 */
    found  = 55;
    status = GenMemOpsFindByteIndicesU32(idxs, USIZE_C(3), &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    printf("PASSED\n");
}


void
FindNone(void)
{
    u8    buf[16];
    u32   idxs[16];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNone -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));

    status = GenMemOpsFindByteIndicesU32(idxs, sizeof(idxs), &found, buf, USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    printf("PASSED\n");
}


void
FindMatches(void)
{
    u8    buf[32];
    u32   idxs[32];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindMatches -> ");

    kdi_FillVal(buf, USIZE_C(32), U8_C(0x00));

    /* Matches at 0, 10, 20, 30 */
    buf[0]  = 0xFF;
    buf[10] = 0xFF;
    buf[20] = 0xFF;
    buf[30] = 0xFF;

    status  = GenMemOpsFindByteIndicesU32(idxs, sizeof(idxs), &found, buf, USIZE_C(32), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(found == 4);

    assert(idxs[0] == 0);
    assert(idxs[1] == 10);
    assert(idxs[2] == 20);
    assert(idxs[3] == 30);

    printf("PASSED\n");
}


void
CapacityLimit(void)
{
    u8    buf[32];
    u32   idxs[3]; /* Capacity for 3 elements = 12 bytes */
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "CapacityLimit -> ");

    /* Init: 0xAA */
    kdi_FillVal(buf, USIZE_C(32), U8_C(0xAA));

    /* Buffer has 32 matches. Capacity is 3 elements (12 bytes). */
    status = GenMemOpsFindByteIndicesU32(idxs, sizeof(idxs), &found, buf, USIZE_C(32), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(found == 3);

    assert(idxs[0] == 0);
    assert(idxs[1] == 1);
    assert(idxs[2] == 2);

    printf("PASSED\n");
}


void
LargeCount(void)
{
    /* Use static for larger buffers */
    static u8  buf[2000];
    static u32 idxs[2000];
    usize      found;
    bool       status;
    usize      i;

    printf(LOG_PREFIX_CSTR "LargeCount -> ");

    /* Fill matching values 0..1999 */
    kdi_FillVal(buf, USIZE_C(2000), U8_C(0x77));

    status = GenMemOpsFindByteIndicesU32(idxs, sizeof(idxs), &found, buf, USIZE_C(2000), U8_C(0x77));

    assert(status == RESULT_SUCCESS);
    assert(found == 2000);

    assert(idxs[0] == 0);
    assert(idxs[1999] == 1999);

    /* Verify sequence */
    for (i = 0; i < 2000; ++i)
    {
        if (idxs[i] != (u32)i)
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
    LargeCount();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
