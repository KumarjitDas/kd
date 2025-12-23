/**
 * @file kdGenMemOpsReplaceNotByte.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsReplaceNotByte function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsReplaceNotByte function test"
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

    /* ptr is null -> failure */
    status = GenMemOpsReplaceNotByte(null, USIZE_C(16), U8_C(0xAA), U8_C(0xBB));
    assert(status == RESULT_FAILURE);

    /* sz is zero -> failure */
    status = GenMemOpsReplaceNotByte(buf, USIZE_C(0), U8_C(0xAA), U8_C(0xBB));
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

    /* Replace NOT 0xAA with 0xBB.
     * Since all are 0xAA, none should change.
     */
    status = GenMemOpsReplaceNotByte(buf, USIZE_C(16), U8_C(0xAA), U8_C(0xBB));

    assert(status == RESULT_SUCCESS);
    assert(kdi_VerifyVal(buf, USIZE_C(16), U8_C(0xAA)));

    printf("PASSED\n");
}


void
ReplaceFirstOnly(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ReplaceFirstOnly -> ");

    /* Fill with 0xCC */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xCC));

    /* Replace NOT 0xAA with 0xBB.
     * 0xCC != 0xAA.
     * Should replace ONLY the first byte (index 0).
     */
    status = GenMemOpsReplaceNotByte(buf, USIZE_C(16), U8_C(0xAA), U8_C(0xBB));

    assert(status == RESULT_SUCCESS);
    assert(buf[0] == 0xBB);
    /* Verify remainder is untouched */
    assert(buf[1] == 0xCC);
    assert(buf[15] == 0xCC);

    printf("PASSED\n");
}


void
ReplaceMixed(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ReplaceMixed -> ");

    /* Fill with 0xAA */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Set some mismatches at 2, 5, 10 */
    buf[2]  = 0x11;
    buf[5]  = 0x22;
    buf[10] = 0x33;

    /* Replace NOT 0xAA with 0xBB.
     * First mismatch is at index 2.
     * Only index 2 should change to 0xBB.
     * Index 5 and 10 should remain unchanged.
     */
    status  = GenMemOpsReplaceNotByte(buf, USIZE_C(16), U8_C(0xAA), U8_C(0xBB));

    assert(status == RESULT_SUCCESS);
    assert(buf[0] == 0xAA);
    assert(buf[2] == 0xBB);  /* Replaced */
    assert(buf[5] == 0x22);  /* Untouched */
    assert(buf[10] == 0x33); /* Untouched */

    printf("PASSED\n");
}


void
IdentityReplacement(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "IdentityReplacement -> ");

    /* Fill with 0xCC (which is NOT 0xAA) */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xCC));

    /* Replace NOT 0xAA with 0xAA.
     * First byte (0xCC) != 0xAA. Replace with 0xAA.
     * Should stop there.
     */
    status = GenMemOpsReplaceNotByte(buf, USIZE_C(16), U8_C(0xAA), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(buf[0] == 0xAA);
    assert(buf[1] == 0xCC); /* Untouched */

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    static u8 buf[102400];
    bool      status;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    /* Fill with 0xAA */
    kdi_FillVal(buf, sizeof(buf), U8_C(0xAA));

    /* Create mismatches at 70000 and 80000 */
    buf[70000] = 0xCC;
    buf[80000] = 0xDD;

    /* Replace NOT 0xAA with 0xBB */
    status     = GenMemOpsReplaceNotByte(buf, sizeof(buf), U8_C(0xAA), U8_C(0xBB));

    assert(status == RESULT_SUCCESS);
    /* Only the first mismatch (70000) should change */
    assert(buf[70000] == 0xBB);
    assert(buf[80000] == 0xDD); /* Second mismatch remains */

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
    ReplaceFirstOnly();
    ReplaceMixed();
    IdentityReplacement();
    LargeBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
