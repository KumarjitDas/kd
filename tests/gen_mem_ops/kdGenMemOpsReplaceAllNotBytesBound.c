/**
 * @file kdGenMemOpsReplaceAllNotBytesBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsReplaceAllNotBytesBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsReplaceAllNotBytesBound function test"
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
    u8    buf[16];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* base is null -> failure */
    status = GenMemOpsReplaceAllNotBytesBound(null, USIZE_C(16), 0, 16, &count, U8_C(0xAA), U8_C(0xBB));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = GenMemOpsReplaceAllNotBytesBound(buf, USIZE_C(0), 0, 16, &count, U8_C(0xAA), U8_C(0xBB));
    assert(status == RESULT_FAILURE);

    /* count is null -> failure */
    status = GenMemOpsReplaceAllNotBytesBound(buf, USIZE_C(16), 0, 16, null, U8_C(0xAA), U8_C(0xBB));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ReplaceNone(void)
{
    u8    buf[16];
    usize count = 555;
    bool  status;

    printf(LOG_PREFIX_CSTR "ReplaceNone -> ");

    /* Fill with 0xAA */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Range [0, 16). Find NOT 0xAA.
     * All are 0xAA, so no replacements.
     */
    status = GenMemOpsReplaceAllNotBytesBound(buf, USIZE_C(16), 0, 16, &count, U8_C(0xAA), U8_C(0xBB));

    assert(status == RESULT_SUCCESS);
    assert(count == 0);
    assert(kdi_VerifyVal(buf, USIZE_C(16), U8_C(0xAA)));

    printf("PASSED\n");
}


void
ReplaceAllInsideRange(void)
{
    u8    buf[16];
    usize count = 0;
    bool  status;

    printf(LOG_PREFIX_CSTR "ReplaceAllInsideRange -> ");

    /* Fill with 0xCC (Mismatch 0xAA) */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xCC));

    /* Range [4, 8) -> Count 4.
     * Indices 4, 5, 6, 7 should be replaced.
     */
    status = GenMemOpsReplaceAllNotBytesBound(buf, USIZE_C(16), 4, 4, &count, U8_C(0xAA), U8_C(0xBB));

    assert(status == RESULT_SUCCESS);
    assert(count == 4);

    /* Verify replacements inside range */
    assert(buf[4] == 0xBB && buf[7] == 0xBB);

    /* Verify outside range untouched */
    assert(buf[3] == 0xCC);
    assert(buf[8] == 0xCC);

    printf("PASSED\n");
}


void
RangeConstraints(void)
{
    u8    buf[32];
    usize count = 0;
    bool  status;

    printf(LOG_PREFIX_CSTR "RangeConstraints -> ");

    /* Fill with 0xAA */
    kdi_FillVal(buf, USIZE_C(32), U8_C(0xAA));

    /* Create mismatches (Not 0xAA) */
    buf[2]  = 0xBB; /* Before range */
    buf[5]  = 0xBB; /* Inside range */
    buf[8]  = 0xBB; /* Inside range */
    buf[20] = 0xBB; /* After range */

    /* Range: Start 4, Count 6 -> [4, 10).
     * Indices inside: 4, 5, 6, 7, 8, 9.
     * Mismatches inside: 5 and 8.
     * Expect 2 replacements.
     */
    status  = GenMemOpsReplaceAllNotBytesBound(buf, USIZE_C(32), 4, 6, &count, U8_C(0xAA), U8_C(0xCC));

    assert(status == RESULT_SUCCESS);
    assert(count == 2);

    /* Check results */
    assert(buf[2] == 0xBB);  /* Untouched */
    assert(buf[5] == 0xCC);  /* Replaced */
    assert(buf[8] == 0xCC);  /* Replaced */
    assert(buf[20] == 0xBB); /* Untouched */

    printf("PASSED\n");
}


void
EndValueClamping(void)
{
    u8    buf[16];
    usize count = 0;
    bool  status;

    printf(LOG_PREFIX_CSTR "EndValueClamping -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Mismatch at last index 15 and 14 */
    buf[14] = 0xBB;
    buf[15] = 0xBB;

    /* Start 10, Count 100.
     * Clamped to [10, 16).
     * Should find mismatches at 14 and 15.
     */
    status  = GenMemOpsReplaceAllNotBytesBound(buf, USIZE_C(16), 10, 100, &count, U8_C(0xAA), U8_C(0xCC));

    assert(status == RESULT_SUCCESS);
    assert(count == 2);
    assert(buf[14] == 0xCC);
    assert(buf[15] == 0xCC);

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    static u8 buf[70000];
    usize     count = 0;
    bool      status;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    kdi_FillVal(buf, sizeof(buf), U8_C(0xAA));

    /* Mismatches at 65530 and 65540 */
    buf[65530] = 0xBB;
    buf[65540] = 0xBB;

    /* Range [65000, 70000).
     * Both mismatches are inside.
     */
    status     = GenMemOpsReplaceAllNotBytesBound(buf, sizeof(buf), 65000, 5000, &count, U8_C(0xAA), U8_C(0xCC));

    assert(status == RESULT_SUCCESS);
    assert(count == 2);
    assert(buf[65530] == 0xCC);
    assert(buf[65540] == 0xCC);

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
    ReplaceAllInsideRange();
    RangeConstraints();
    EndValueClamping();
    LargeBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
