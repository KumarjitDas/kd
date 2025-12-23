/**
 * @file kdGenMemOpsReplaceNotByteBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsReplaceNotByteBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsReplaceNotByteBound function test"
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


static bool
kdi_VerifyVal(const u8 *ptr, usize sz, u8 val)
{
    usize i;
    for (i = USIZE_C(0); i < sz; ++i)
    {
        if (ptr[i] != val)
            return false;
    }
    return true;
}


void
BasicArguments(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* base is null -> failure */
    status = GenMemOpsReplaceNotByteBound(null, USIZE_C(16), 0, 16, U8_C(0xAA), U8_C(0xBB));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = GenMemOpsReplaceNotByteBound(buf, USIZE_C(0), 0, 16, U8_C(0xAA), U8_C(0xBB));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ReplaceNone(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ReplaceNone -> ");

    /* Fill with 0xAA */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Range [0, 16). Find NOT 0xAA.
     * All are 0xAA, so no replacement.
     */
    status = GenMemOpsReplaceNotByteBound(buf, USIZE_C(16), 0, 16, U8_C(0xAA), U8_C(0xBB));

    assert(status == RESULT_SUCCESS);
    assert(kdi_VerifyVal(buf, USIZE_C(16), U8_C(0xAA)));

    printf("PASSED\n");
}


void
RangeConstraints(void)
{
    u8   buf[32];
    bool status;

    printf(LOG_PREFIX_CSTR "RangeConstraints -> ");

    /* Fill with 0xAA */
    kdi_FillVal(buf, USIZE_C(32), U8_C(0xAA));

    /* Create mismatches (Not 0xAA) */
    buf[2]  = 0xBB; /* Before range */
    buf[5]  = 0xBB; /* First inside range */
    buf[8]  = 0xBB; /* Second inside range */
    buf[20] = 0xBB; /* After range */

    /* Range: Start 4, Count 6 -> [4, 10).
     * Indices inside: 4, 5, 6, 7, 8, 9.
     * Mismatches inside: 5 and 8.
     * * Should find first mismatch at 5 and replace with 0xCC.
     * 2 should be ignored.
     * 8 should be ignored (stop after first).
     * 20 should be ignored.
     */
    status  = GenMemOpsReplaceNotByteBound(buf, USIZE_C(32), 4, 6, U8_C(0xAA), U8_C(0xCC));

    assert(status == RESULT_SUCCESS);

    /* Check results */
    assert(buf[2] == 0xBB);  /* Untouched */
    assert(buf[5] == 0xCC);  /* Replaced */
    assert(buf[8] == 0xBB);  /* Untouched (only first replaced) */
    assert(buf[20] == 0xBB); /* Untouched */

    printf("PASSED\n");
}


void
EndValueClamping(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "EndValueClamping -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Mismatch at last index 15 */
    buf[15] = 0xBB;

    /* Start 10, Count 100.
     * Clamped to [10, 16).
     * Should find mismatch at 15.
     */
    status  = GenMemOpsReplaceNotByteBound(buf, USIZE_C(16), 10, 100, U8_C(0xAA), U8_C(0xCC));

    assert(status == RESULT_SUCCESS);
    assert(buf[15] == 0xCC);

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    static u8 buf[70000];
    bool      status;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    kdi_FillVal(buf, sizeof(buf), U8_C(0xAA));

    /* Mismatch at 65530 and 65540 */
    buf[65530] = 0xBB;
    buf[65540] = 0xBB;

    /* Range [65000, 70000).
     * Should replace first mismatch at 65530.
     */
    status     = GenMemOpsReplaceNotByteBound(buf, sizeof(buf), 65000, 5000, U8_C(0xAA), U8_C(0xCC));

    assert(status == RESULT_SUCCESS);
    assert(buf[65530] == 0xCC);
    assert(buf[65540] == 0xBB); /* Second remains */

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    ReplaceNone();
    RangeConstraints();
    EndValueClamping();
    LargeBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
