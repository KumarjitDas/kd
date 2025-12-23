/**
 * @file kdGenMemOpsFindNotByteIndicesU16.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindNotByteIndicesU16 function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindNotByteIndicesU16 function test"
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
    /* idxs array is 16 elements * 2 bytes = 32 bytes */
    usize idxs_byte_sz = sizeof(idxs);

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* idxs is null -> failure */
    status = GenMemOpsFindNotByteIndicesU16(null, idxs_byte_sz, &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* idxs_sz is zero -> failure */
    status = GenMemOpsFindNotByteIndicesU16(idxs, USIZE_C(0), &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* found pointer is null -> failure */
    status = GenMemOpsFindNotByteIndicesU16(idxs, idxs_byte_sz, null, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindNotByteIndicesU16(idxs, idxs_byte_sz, &found, null, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr_sz is zero -> failure */
    status = GenMemOpsFindNotByteIndicesU16(idxs, idxs_byte_sz, &found, buf, USIZE_C(0), U8_C(0));
    assert(status == RESULT_FAILURE);

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

    /* All 0xAA */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Find NOT 0xAA. Should find 0. */
    status = GenMemOpsFindNotByteIndicesU16(idxs, sizeof(idxs), &found, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    printf("PASSED\n");
}


void
FindSome(void)
{
    u8    buf[16];
    u16   idxs[16];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindSome -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Mismatches at 2, 5, 10 */
    buf[2]  = 0xBB;
    buf[5]  = 0xCC;
    buf[10] = 0xDD;

    /* Find NOT 0xAA. Should find 6. */
    status  = GenMemOpsFindNotByteIndicesU16(idxs, sizeof(idxs), &found, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(found == 6);
    assert(idxs[0] == 2);
    assert(idxs[1] == 5);
    assert(idxs[2] == 10);

    printf("PASSED\n");
}


void
BufferOverflowProtection(void)
{
    u8    buf[16];
    u16   idxs[2]; /* Only space for 2 elements */
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "BufferOverflowProtection -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* 3 Mismatches */
    buf[1] = 0xBB;
    buf[2] = 0xBB;
    buf[3] = 0xBB;

    /* Output buffer size passed is 4 bytes (2 * sizeof(u16)).
     * The logic must detect this can only hold 2 items.
     */
    status = GenMemOpsFindNotByteIndicesU16(idxs, sizeof(idxs), &found, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(found == 4);
    assert(idxs[0] == 1);
    assert(idxs[1] == 2);

    printf("PASSED\n");
}


void
IndexRangeLimit(void)
{
    /* Use static to avoid stack overflow on some systems */
    static u8 buf[70000];
    u16       idxs[10];
    usize     found;
    bool      status;

    printf(LOG_PREFIX_CSTR "IndexRangeLimit -> ");

    kdi_FillVal(buf, USIZE_C(70000), U8_C(0xAA));

    /* Mismatch at index 65000 (Valid for u16: Max 65535) */
    buf[65000] = 0xBB;

    /* Mismatch at index 66000 (Invalid for u16).
     * The buffer is valid (70000 bytes).
     * The scan finds a mismatch at 66000.
     * 66000 > 65535, so it cannot be stored in u16.
     * It should be ignored.
     */
    buf[66000] = 0xBB;

    status     = GenMemOpsFindNotByteIndicesU16(idxs, sizeof(idxs), &found, buf, 70000, U8_C(0xAA));

    assert(status == RESULT_SUCCESS);

    /* Should find exactly 1 index (65000). 66000 is ignored. */
    assert(found == 2);
    assert(idxs[0] == 65000);

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
    FindSome();
    BufferOverflowProtection();
    IndexRangeLimit();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
