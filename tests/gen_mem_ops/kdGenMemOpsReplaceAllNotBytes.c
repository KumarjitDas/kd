/**
 * @file kdGenMemOpsReplaceAllNotBytes.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsReplaceAllNotBytes function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsReplaceAllNotBytes function test"
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

    /* ptr is null -> failure */
    status = GenMemOpsReplaceAllNotBytes(null, USIZE_C(16), &count, U8_C(0xAA), U8_C(0xBB));
    assert(status == RESULT_FAILURE);

    /* sz is zero -> failure */
    status = GenMemOpsReplaceAllNotBytes(buf, USIZE_C(0), &count, U8_C(0xAA), U8_C(0xBB));
    assert(status == RESULT_FAILURE);

    /* count is null -> failure */
    status = GenMemOpsReplaceAllNotBytes(buf, USIZE_C(16), null, U8_C(0xAA), U8_C(0xBB));
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

    /* Replace Not 0xAA with 0xBB.
     * All are 0xAA. No replacements should occur.
     */
    status = GenMemOpsReplaceAllNotBytes(buf, USIZE_C(16), &count, U8_C(0xAA), U8_C(0xBB));

    assert(status == RESULT_SUCCESS);
    assert(count == 0);
    assert(kdi_VerifyVal(buf, USIZE_C(16), U8_C(0xAA)));

    printf("PASSED\n");
}


void
ReplaceAll(void)
{
    u8    buf[16];
    usize count = 0;
    bool  status;

    printf(LOG_PREFIX_CSTR "ReplaceAll -> ");

    /* Fill with 0xCC (which is Not 0xAA) */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xCC));

    /* Replace Not 0xAA with 0xBB.
     * All 0xCC should become 0xBB.
     */
    status = GenMemOpsReplaceAllNotBytes(buf, USIZE_C(16), &count, U8_C(0xAA), U8_C(0xBB));

    assert(status == RESULT_SUCCESS);
    assert(count == 16);
    assert(kdi_VerifyVal(buf, USIZE_C(16), U8_C(0xBB)));

    printf("PASSED\n");
}


void
ReplaceMixed(void)
{
    u8    buf[16];
    usize count = 0;
    bool  status;

    printf(LOG_PREFIX_CSTR "ReplaceMixed -> ");

    /* Fill with matches (0xAA) */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Create mismatches at 2, 5, 10 */
    buf[2]  = 0x11;
    buf[5]  = 0x22;
    buf[10] = 0x33;

    /* Replace Not 0xAA with 0xBB */
    status  = GenMemOpsReplaceAllNotBytes(buf, USIZE_C(16), &count, U8_C(0xAA), U8_C(0xBB));

    assert(status == RESULT_SUCCESS);
    assert(count == 3);

    /* Verify replacements */
    assert(buf[2] == 0xBB);
    assert(buf[5] == 0xBB);
    assert(buf[10] == 0xBB);

    /* Verify non-replacements (indices that were 0xAA) */
    assert(buf[0] == 0xAA);
    assert(buf[15] == 0xAA);

    printf("PASSED\n");
}


void
IdentityReplacement(void)
{
    u8    buf[16];
    usize count = 0;
    bool  status;

    printf(LOG_PREFIX_CSTR "IdentityReplacement -> ");

    /* Fill with 0xCC */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xCC));

    /* Replace Not 0xAA with 0xAA.
     * 0xCC != 0xAA -> Replaced with 0xAA.
     * Result: Buffer becomes all 0xAA.
     */
    status = GenMemOpsReplaceAllNotBytes(buf, USIZE_C(16), &count, U8_C(0xAA), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(count == 16);
    assert(kdi_VerifyVal(buf, USIZE_C(16), U8_C(0xAA)));

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    static u8 buf[102400];
    usize     count = 0;
    bool      status;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    /* Fill with 0xAA */
    kdi_FillVal(buf, sizeof(buf), U8_C(0xAA));

    /* Set 1000 mismatches */
    {
        usize i;
        for (i = 0; i < 1000; ++i)
        {
            buf[i * 10] = 0xCC; /* Indices 0, 10, 20... */
        }
    }

    /* Replace Not 0xAA with 0xBB */
    status = GenMemOpsReplaceAllNotBytes(buf, sizeof(buf), &count, U8_C(0xAA), U8_C(0xBB));

    assert(status == RESULT_SUCCESS);
    assert(count == 1000);
    assert(buf[0] == 0xBB);
    assert(buf[10] == 0xBB);
    assert(buf[1] == 0xAA); /* Untouched */

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
    ReplaceAll();
    ReplaceMixed();
    IdentityReplacement();
    LargeBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
