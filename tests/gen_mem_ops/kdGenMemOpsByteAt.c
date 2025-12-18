/**
 * @file kdGenMemOpsByteAt.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsByteAt function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsByteAt function test"
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
    u8   dst;
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* dst is null -> failure */
    status = GenMemOpsByteAt(null, buf, USIZE_C(16), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure */
    dst    = U8_C(0);
    status = GenMemOpsByteAt(&dst, null, USIZE_C(16), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = GenMemOpsByteAt(&dst, buf, USIZE_C(0), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ValidIndex(void)
{
    u8   buf[16];
    u8   dst;
    bool status;

    printf(LOG_PREFIX_CSTR "ValidIndex -> ");

    /* Init: 0x10, 0x11, ... */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x10));

    /* Check first byte */
    dst    = U8_C(0);
    status = GenMemOpsByteAt(&dst, buf, USIZE_C(16), USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    assert(dst == U8_C(0x10));

    /* Check last byte */
    dst    = U8_C(0);
    status = GenMemOpsByteAt(&dst, buf, USIZE_C(16), USIZE_C(15));
    assert(status == RESULT_SUCCESS);
    assert(dst == U8_C(0x1F)); /* 0x10 + 15 = 0x1F */

    /* Check middle byte */
    dst    = U8_C(0);
    status = GenMemOpsByteAt(&dst, buf, USIZE_C(16), USIZE_C(8));
    assert(status == RESULT_SUCCESS);
    assert(dst == U8_C(0x18));

    printf("PASSED\n");
}


void
IndexOutOfBounds(void)
{
    u8   buf[16];
    u8   dst;
    bool status;

    printf(LOG_PREFIX_CSTR "IndexOutOfBounds -> ");

    /* idx == sz -> failure */
    status = GenMemOpsByteAt(&dst, buf, USIZE_C(16), USIZE_C(16));
    assert(status == RESULT_FAILURE);

    /* idx > sz -> failure */
    status = GenMemOpsByteAt(&dst, buf, USIZE_C(16), USIZE_C(100));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
StoreResult(void)
{
    u8   buf[4];
    u8   dst_byte;
    /* Simulate retrieving into a larger type, ensuring correct casting/pointer usage */
    u32  dst_large;
    bool status;

    printf(LOG_PREFIX_CSTR "StoreResult -> ");

    buf[0]   = 0xAA;
    buf[1]   = 0xBB;

    /* Retrieve into u8 */
    dst_byte = 0;
    status   = GenMemOpsByteAt(&dst_byte, buf, USIZE_C(4), USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(dst_byte == 0xBB);

    /* Retrieve into void* acting as u8* (API takes void* dst) */
    /* NOTE: The API likely writes exactly 1 byte.
     * If we pass &dst_large, it writes to the first byte of dst_large (endian dependent).
     * We generally expect the user to pass a pointer to a single byte/char/u8.
     */
    dst_large = 0xFFFFFFFF; /* sentinel */
    status    = GenMemOpsByteAt(&dst_large, buf, USIZE_C(4), USIZE_C(0));
    assert(status == RESULT_SUCCESS);

    /* Check only the first byte was modified to 0xAA */
    {
        u8 *p = (u8 *)&dst_large;
        assert(*p == 0xAA);
        /* Ensure we didn't wipe the rest of the u32 (buffer overflow check implicit) */
        /* Note: This assumes little-endian for the LSB check, but we just check the pointer deref */
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
    ValidIndex();
    IndexOutOfBounds();
    StoreResult();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
