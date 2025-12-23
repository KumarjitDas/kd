/**
 * @file kdGenMemOpsReplaceLastNotByte.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsReplaceLastNotByte function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsReplaceLastNotByte function test"
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
    status = GenMemOpsReplaceLastNotByte(null, USIZE_C(16), U8_C(0xAA), U8_C(0xBB));
    assert(status == RESULT_FAILURE);

    /* sz is zero -> failure */
    status = GenMemOpsReplaceLastNotByte(buf, USIZE_C(0), U8_C(0xAA), U8_C(0xBB));
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

    /* Replace Last NOT 0xAA with 0xBB.
     * All are 0xAA, so no mismatch exists.
     */
    status = GenMemOpsReplaceLastNotByte(buf, USIZE_C(16), U8_C(0xAA), U8_C(0xBB));

    assert(status == RESULT_SUCCESS);
    assert(kdi_VerifyVal(buf, USIZE_C(16), U8_C(0xAA)));

    printf("PASSED\n");
}


void
ReplaceLastOnly(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ReplaceLastOnly -> ");

    /* Fill with 0xCC (All mismatch 0xAA) */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xCC));

    /* Replace Last NOT 0xAA with 0xBB.
     * Indices 0 to 15 are all mismatches.
     * The last one is index 15.
     */
    status = GenMemOpsReplaceLastNotByte(buf, USIZE_C(16), U8_C(0xAA), U8_C(0xBB));

    assert(status == RESULT_SUCCESS);

    /* Index 15 replaced */
    assert(buf[15] == 0xBB);

    /* Earlier mismatches (0-14) untouched */
    assert(buf[0] == 0xCC);
    assert(buf[14] == 0xCC);

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

    /* Set mismatches at 2, 5, 10 */
    buf[2]  = 0x11;
    buf[5]  = 0x22;
    buf[10] = 0x33;

    /* Replace Last NOT 0xAA with 0xBB.
     * Mismatches at 2, 5, 10.
     * Last one is 10.
     */
    status  = GenMemOpsReplaceLastNotByte(buf, USIZE_C(16), U8_C(0xAA), U8_C(0xBB));

    assert(status == RESULT_SUCCESS);

    assert(buf[2] == 0x11);  /* Untouched */
    assert(buf[5] == 0x22);  /* Untouched */
    assert(buf[10] == 0xBB); /* Replaced */

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

    /* Replace Last NOT 0xAA with 0xBB */
    status     = GenMemOpsReplaceLastNotByte(buf, sizeof(buf), U8_C(0xAA), U8_C(0xBB));

    assert(status == RESULT_SUCCESS);

    assert(buf[70000] == 0xCC); /* Untouched */
    assert(buf[80000] == 0xBB); /* Last mismatch replaced */

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
    ReplaceLastOnly();
    ReplaceMixed();
    LargeBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
