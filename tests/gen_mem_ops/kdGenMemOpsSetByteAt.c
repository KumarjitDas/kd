/**
 * @file kdGenMemOpsSetByteAt.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsSetByteAt function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsSetByteAt function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


static void
kdi_FillSeq(u8 *dst, usize sz, u8 start)
{
    usize i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        dst[i] = (u8)(start + (u8)i);
    }
}


void
BasicArguments(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* base is null -> failure */
    status = GenMemOpsSetByteAt(null, USIZE_C(16), USIZE_C(0), U8_C(0xFF));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = GenMemOpsSetByteAt(buf, USIZE_C(0), USIZE_C(0), U8_C(0xFF));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ValidSet(void)
{
    u8   buf[16];
    bool status;

    printf(LOG_PREFIX_CSTR "ValidSet -> ");

    /* Init: 0x00 */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Set first byte (Index 0) */
    status = GenMemOpsSetByteAt(buf, USIZE_C(16), USIZE_C(0), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(buf[0] == U8_C(0xAA));

    /* Set last byte (Index 15) */
    status = GenMemOpsSetByteAt(buf, USIZE_C(16), USIZE_C(15), U8_C(0xBB));
    assert(status == RESULT_SUCCESS);
    assert(buf[15] == U8_C(0xBB));

    /* Set middle byte (Index 8) */
    status = GenMemOpsSetByteAt(buf, USIZE_C(16), USIZE_C(8), U8_C(0xCC));
    assert(status == RESULT_SUCCESS);
    assert(buf[8] == U8_C(0xCC));

    /* Verify others untouched */
    assert(buf[1] == U8_C(0x01));
    assert(buf[7] == U8_C(0x07));

    printf("PASSED\n");
}


void
OutOfBounds(void)
{
    u8   buf[10];
    bool status;

    printf(LOG_PREFIX_CSTR "OutOfBounds -> ");

    kdi_FillSeq(buf, USIZE_C(10), U8_C(0x00));

    /* Index == Size (10) -> Failure */
    status = GenMemOpsSetByteAt(buf, USIZE_C(10), USIZE_C(10), U8_C(0xFF));
    assert(status == RESULT_FAILURE);
    /* Verify last byte untouched */
    assert(buf[9] == U8_C(0x09));

    /* Index > Size -> Failure */
    status = GenMemOpsSetByteAt(buf, USIZE_C(10), USIZE_C(100), U8_C(0xFF));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
TypePunningSafety(void)
{
    u32  val;
    bool status;

    printf(LOG_PREFIX_CSTR "TypePunningSafety -> ");

    /* Init: 0x00000000 */
    val    = 0;

    /* Set byte at offset 0 to 0x12 */
    status = GenMemOpsSetByteAt(&val, sizeof(u32), USIZE_C(0), U8_C(0x12));
    assert(status == RESULT_SUCCESS);

    /* Verify via pointer */
    {
        u8 *p = (u8 *)&val;
        assert(p[0] == U8_C(0x12));
    }

    /* Set byte at offset 3 to 0x34 */
    status = GenMemOpsSetByteAt(&val, sizeof(u32), USIZE_C(3), U8_C(0x34));
    assert(status == RESULT_SUCCESS);

    {
        u8 *p = (u8 *)&val;
        assert(p[3] == U8_C(0x34));
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
    ValidSet();
    OutOfBounds();
    TypePunningSafety();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
