/**
 * @file kdGenMemOpsCountNotBytes.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsCountNotBytes function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsCountNotBytes function test"
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
    usize count = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* count pointer is null -> failure */
    status = GenMemOpsCountNotBytes(null, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsCountNotBytes(&count, null, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* sz is zero -> success, count should be 0 */
    count  = 55;
    status = GenMemOpsCountNotBytes(&count, buf, USIZE_C(0), U8_C(0));
    assert(status == RESULT_SUCCESS);
    assert(count == 0);

    printf("PASSED\n");
}


void
CountNone(void)
{
    u8    buf[16];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountNone -> ");

    /* Init all with 0xAA */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Count NOT 0xAA. Should be 0. */
    count  = 999;
    status = GenMemOpsCountNotBytes(&count, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(count == 0);

    printf("PASSED\n");
}


void
CountAll(void)
{
    u8    buf[16];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountAll -> ");

    /* Init all with 0xAA */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Count NOT 0xFF. Should be 16. */
    count  = 0;
    status = GenMemOpsCountNotBytes(&count, buf, USIZE_C(16), U8_C(0xFF));

    assert(status == RESULT_SUCCESS);
    assert(count == 16);

    printf("PASSED\n");
}


void
CountMixed(void)
{
    u8    buf[10];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountMixed -> ");

    /* Pattern: 0, 1, 2, 0, 1, 2, 0, 1, 2, 0 */
    buf[0] = 0;
    buf[1] = 1;
    buf[2] = 2;
    buf[3] = 0;
    buf[4] = 1;
    buf[5] = 2;
    buf[6] = 0;
    buf[7] = 1;
    buf[8] = 2;
    buf[9] = 0;

    /* Count NOT 0x00. */
    /* Total 10. 0x00 appears 4 times. NOT 0x00 should be 6. */
    status = GenMemOpsCountNotBytes(&count, buf, USIZE_C(10), U8_C(0x00));
    assert(status == RESULT_SUCCESS);
    assert(count == 6);

    printf("PASSED\n");
}


void
U32_CountNotBytes(void)
{
    u32   buf[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_CountNotBytes -> ");

    /* Init: 0x00000000 */
    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    /* Set specific bytes to 0xAA */
    ((u8 *)buf)[0] = 0xAA;
    ((u8 *)buf)[7] = 0xAA;
    ((u8 *)buf)[8] = 0xAA;

    /* Count NOT 0x00. */
    /* Total 16 bytes. 0x00s = 13. Not 0x00 (0xAA) = 3. */
    status         = GenMemOpsCountNotBytes(&count, buf, sizeof(buf), U8_C(0x00));

    assert(status == RESULT_SUCCESS);
    assert(count == 3);

    /* Count NOT 0xAA */
    /* Total 16. 0xAAs = 3. Not 0xAA = 13. */
    status = GenMemOpsCountNotBytes(&count, buf, sizeof(buf), U8_C(0xAA));
    assert(status == RESULT_SUCCESS);
    assert(count == 13);

    printf("PASSED\n");
}


void
LargeArray_Count(void)
{
    u8    buf[100];
    usize count;
    bool  status;
    usize i;

    printf(LOG_PREFIX_CSTR "LargeArray_Count -> ");

    /* Init: 0..99 */
    kdi_FillSeq(buf, USIZE_C(100), U8_C(0));

    /* Count NOT 50 */
    /* 50 appears exactly once. Not 50 should be 99. */
    status = GenMemOpsCountNotBytes(&count, buf, USIZE_C(100), U8_C(50));
    assert(status == RESULT_SUCCESS);
    assert(count == 99);

    /* Set first 50 bytes to 0xFF */
    for (i = 0; i < 50; ++i)
        buf[i] = 0xFF;

    /* Count NOT 0xFF */
    /* 0xFF appears 50 times. Not 0xFF appears 50 times (indices 50..99). */
    status = GenMemOpsCountNotBytes(&count, buf, USIZE_C(100), U8_C(0xFF));
    assert(status == RESULT_SUCCESS);
    assert(count == 50);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    CountNone();
    CountAll();
    CountMixed();
    U32_CountNotBytes();
    LargeArray_Count();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
