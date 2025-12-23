/**
 * @file kdGenMemOpsFindNotByteIndicesU8.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindNotByteIndicesU8 function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindNotByteIndicesU8 function test"
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

    /* idxs is null -> failure */
    status = GenMemOpsFindNotByteIndicesU8(null, USIZE_C(16), &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* idxs_sz is zero -> failure */
    status = GenMemOpsFindNotByteIndicesU8(idxs, USIZE_C(0), &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* found pointer is null -> failure */
    status = GenMemOpsFindNotByteIndicesU8(idxs, USIZE_C(16), null, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindNotByteIndicesU8(idxs, USIZE_C(16), &found, null, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr_sz is zero -> failure */
    status = GenMemOpsFindNotByteIndicesU8(idxs, USIZE_C(16), &found, buf, USIZE_C(0), U8_C(0));
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
    kdi_FillVal(idxs, USIZE_C(16), U8_C(0));

    /* Find NOT 0xAA. Should find 0. */
    status = GenMemOpsFindNotByteIndicesU8(idxs, USIZE_C(16), &found, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    printf("PASSED\n");
}


void
FindSome(void)
{
    u8    buf[16];
    u8    idxs[16];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindSome -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Mismatches at 2, 5, 10 */
    buf[2]  = 0xBB;
    buf[5]  = 0xCC;
    buf[10] = 0xDD;

    /* Find NOT 0xAA. Should find 3. */
    status  = GenMemOpsFindNotByteIndicesU8(idxs, USIZE_C(16), &found, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(found == 3);
    assert(idxs[0] == 2);
    assert(idxs[1] == 5);
    assert(idxs[2] == 10);

    printf("PASSED\n");
}


void
BufferOverflowProtection(void)
{
    u8    buf[16];
    u8    idxs[2]; /* Only space for 2 indices */
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "BufferOverflowProtection -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* 3 Mismatches */
    buf[1] = 0xBB;
    buf[2] = 0xBB;
    buf[3] = 0xBB;

    /* Output buffer size is 2. Should stop after filling 2. */
    status = GenMemOpsFindNotByteIndicesU8(idxs, USIZE_C(2), &found, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(found == 2);
    assert(idxs[0] == 1);
    assert(idxs[1] == 2);
    /* Index 3 is ignored because output buffer is full */

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

    /* Mismatch at index 10 (Valid for u8) */
    buf[10]  = 0xBB;

    /* Mismatch at index 250 (Valid for u8) */
    buf[250] = 0xBB;

    /* Mismatch at index 260 (Invalid for u8).
     * Since size is clamped to MAX_U8 (255), the effective range is [0, 255).
     * Index 260 is outside this range and should be ignored.
     */
    buf[260] = 0xBB;

    status   = GenMemOpsFindNotByteIndicesU8(idxs, 10, &found, buf, 300, U8_C(0xAA));

    assert(status == RESULT_SUCCESS);

    /* Should find exactly 2 indices (10 and 250). 260 is ignored. */
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
    FindSome();
    BufferOverflowProtection();
    IndexRangeLimit();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
