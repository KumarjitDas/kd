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
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsByteAt function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8   buf[16];
    u8   dst;
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x10));

    /* dst is null -> failure */
    status = kdGenMemOpsByteAt(null, buf, USIZE_C(16), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure */
    dst    = U8_C(0);
    status = kdGenMemOpsByteAt(&dst, null, USIZE_C(16), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = kdGenMemOpsByteAt(&dst, buf, USIZE_C(0), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ValidIndexFirstByte(void)
{
    u8   buf[16];
    u8   dst;
    bool status;

    printf(LOG_PREFIX_CSTR "ValidIndexFirstByte -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x10));

    /* Check first byte (index 0) */
    dst    = U8_C(0);
    status = kdGenMemOpsByteAt(&dst, buf, USIZE_C(16), USIZE_C(0));

    assert(status == RESULT_SUCCESS);
    assert(dst == U8_C(0x10));

    printf("PASSED\n");
}


void
ValidIndexLastByte(void)
{
    u8   buf[16];
    u8   dst;
    bool status;

    printf(LOG_PREFIX_CSTR "ValidIndexLastByte -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x10));

    /* Check last byte (index 15) */
    dst    = U8_C(0);
    status = kdGenMemOpsByteAt(&dst, buf, USIZE_C(16), USIZE_C(15));

    assert(status == RESULT_SUCCESS);
    assert(dst == U8_C(0x1F)); /* 0x10 + 15 = 0x1F */

    printf("PASSED\n");
}


void
ValidIndexMiddle(void)
{
    u8   buf[16];
    u8   dst;
    bool status;

    printf(LOG_PREFIX_CSTR "ValidIndexMiddle -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x10));

    /* Check middle byte */
    dst    = U8_C(0);
    status = kdGenMemOpsByteAt(&dst, buf, USIZE_C(16), USIZE_C(8));

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

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0x10));

    /* idx == base_sz -> failure */
    dst    = U8_C(0xFF);
    status = kdGenMemOpsByteAt(&dst, buf, USIZE_C(16), USIZE_C(16));
    assert(status == RESULT_FAILURE);

    /* idx > base_sz -> failure */
    dst    = U8_C(0xFF);
    status = kdGenMemOpsByteAt(&dst, buf, USIZE_C(16), USIZE_C(100));
    assert(status == RESULT_FAILURE);

    /* idx far beyond base_sz -> failure */
    dst    = U8_C(0xFF);
    status = kdGenMemOpsByteAt(&dst, buf, USIZE_C(16), USIZE_C(1000));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
AllBytesSequential(void)
{
    u8   buf[10];
    u8   dst;
    bool status;
    usize i;

    printf(LOG_PREFIX_CSTR "AllBytesSequential -> ");

    kdi_FillSeq_u8(buf, USIZE_C(10), U8_C(0xA0));

    /* Retrieve all bytes sequentially */
    for (i = USIZE_C(0); i < USIZE_C(10); ++i)
    {
        dst    = U8_C(0);
        status = kdGenMemOpsByteAt(&dst, buf, USIZE_C(10), i);

        assert(status == RESULT_SUCCESS);
        assert(dst == (u8)(U8_C(0xA0) + (u8)i));
    }

    printf("PASSED\n");
}


void
SingleByte(void)
{
    u8   buf[1];
    u8   dst;
    bool status;

    printf(LOG_PREFIX_CSTR "SingleByte -> ");

    buf[0] = U8_C(0x42);

    /* Valid access at index 0 */
    dst    = U8_C(0);
    status = kdGenMemOpsByteAt(&dst, buf, USIZE_C(1), USIZE_C(0));

    assert(status == RESULT_SUCCESS);
    assert(dst == U8_C(0x42));

    /* Invalid access at index 1 */
    dst    = U8_C(0);
    status = kdGenMemOpsByteAt(&dst, buf, USIZE_C(1), USIZE_C(1));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    u8   buf[256];
    u8   dst;
    bool status;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    kdi_FillSeq_u8(buf, USIZE_C(256), U8_C(0));

    /* Check first byte */
    dst    = U8_C(0xFF);
    status = kdGenMemOpsByteAt(&dst, buf, USIZE_C(256), USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    assert(dst == U8_C(0));

    /* Check last byte (255) */
    dst    = U8_C(0);
    status = kdGenMemOpsByteAt(&dst, buf, USIZE_C(256), USIZE_C(255));
    assert(status == RESULT_SUCCESS);
    assert(dst == U8_C(255));

    /* Check middle byte (128) */
    dst    = U8_C(0);
    status = kdGenMemOpsByteAt(&dst, buf, USIZE_C(256), USIZE_C(128));
    assert(status == RESULT_SUCCESS);
    assert(dst == U8_C(128));

    /* Out of bounds (index 256) */
    dst    = U8_C(0);
    status = kdGenMemOpsByteAt(&dst, buf, USIZE_C(256), USIZE_C(256));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
AllZeros(void)
{
    u8   buf[8];
    u8   dst;
    bool status;
    usize i;

    printf(LOG_PREFIX_CSTR "AllZeros -> ");

    kdi_Fill_u8(buf, USIZE_C(8), U8_C(0));

    /* Check all bytes are zero */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        dst    = U8_C(0xFF);
        status = kdGenMemOpsByteAt(&dst, buf, USIZE_C(8), i);

        assert(status == RESULT_SUCCESS);
        assert(dst == U8_C(0));
    }

    printf("PASSED\n");
}


void
AllOnes(void)
{
    u8   buf[8];
    u8   dst;
    bool status;
    usize i;

    printf(LOG_PREFIX_CSTR "AllOnes -> ");

    kdi_Fill_u8(buf, USIZE_C(8), U8_C(0xFF));

    /* Check all bytes are 0xFF */
    for (i = USIZE_C(0); i < USIZE_C(8); ++i)
    {
        dst    = U8_C(0);
        status = kdGenMemOpsByteAt(&dst, buf, USIZE_C(8), i);

        assert(status == RESULT_SUCCESS);
        assert(dst == U8_C(0xFF));
    }

    printf("PASSED\n");
}


void
SpecificValues(void)
{
    u8   buf[5];
    u8   dst;
    bool status;

    printf(LOG_PREFIX_CSTR "SpecificValues -> ");

    buf[0] = U8_C(10);
    buf[1] = U8_C(20);
    buf[2] = U8_C(30);
    buf[3] = U8_C(40);
    buf[4] = U8_C(50);

    /* Check each specific value */
    dst    = U8_C(0);
    status = kdGenMemOpsByteAt(&dst, buf, USIZE_C(5), USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    assert(dst == U8_C(10));

    dst    = U8_C(0);
    status = kdGenMemOpsByteAt(&dst, buf, USIZE_C(5), USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(dst == U8_C(20));

    dst    = U8_C(0);
    status = kdGenMemOpsByteAt(&dst, buf, USIZE_C(5), USIZE_C(2));
    assert(status == RESULT_SUCCESS);
    assert(dst == U8_C(30));

    dst    = U8_C(0);
    status = kdGenMemOpsByteAt(&dst, buf, USIZE_C(5), USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(dst == U8_C(40));

    dst    = U8_C(0);
    status = kdGenMemOpsByteAt(&dst, buf, USIZE_C(5), USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(dst == U8_C(50));

    printf("PASSED\n");
}


void
OverwriteDestination(void)
{
    u8   buf[4];
    u8   dst;
    bool status;

    printf(LOG_PREFIX_CSTR "OverwriteDestination -> ");

    buf[0] = U8_C(0xAA);
    buf[1] = U8_C(0xBB);
    buf[2] = U8_C(0xCC);
    buf[3] = U8_C(0xDD);

    /* Set dst to sentinel value */
    dst    = U8_C(0x99);
    status = kdGenMemOpsByteAt(&dst, buf, USIZE_C(4), USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(dst == U8_C(0xBB)); /* Overwritten */

    /* Try again with different sentinel */
    dst    = U8_C(0x11);
    status = kdGenMemOpsByteAt(&dst, buf, USIZE_C(4), USIZE_C(3));

    assert(status == RESULT_SUCCESS);
    assert(dst == U8_C(0xDD));

    printf("PASSED\n");
}


void
MultipleCalls(void)
{
    u8   buf[6];
    u8   dst1;
    u8   dst2;
    u8   dst3;
    bool status;

    printf(LOG_PREFIX_CSTR "MultipleCalls -> ");

    kdi_FillSeq_u8(buf, USIZE_C(6), U8_C(100));

    /* Retrieve multiple bytes in sequence */
    dst1   = U8_C(0);
    status = kdGenMemOpsByteAt(&dst1, buf, USIZE_C(6), USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    assert(dst1 == U8_C(100));

    dst2   = U8_C(0);
    status = kdGenMemOpsByteAt(&dst2, buf, USIZE_C(6), USIZE_C(2));
    assert(status == RESULT_SUCCESS);
    assert(dst2 == U8_C(102));

    dst3   = U8_C(0);
    status = kdGenMemOpsByteAt(&dst3, buf, USIZE_C(6), USIZE_C(5));
    assert(status == RESULT_SUCCESS);
    assert(dst3 == U8_C(105));

    /* Verify all values are correct */
    assert(dst1 == U8_C(100));
    assert(dst2 == U8_C(102));
    assert(dst3 == U8_C(105));

    printf("PASSED\n");
}


void
EdgeValues(void)
{
    u8   buf[4];
    u8   dst;
    bool status;

    printf(LOG_PREFIX_CSTR "EdgeValues -> ");

    buf[0] = U8_C(0);
    buf[1] = U8_C(1);
    buf[2] = U8_C(254);
    buf[3] = U8_C(255);

    /* Min value */
    dst    = U8_C(0xFF);
    status = kdGenMemOpsByteAt(&dst, buf, USIZE_C(4), USIZE_C(0));
    assert(status == RESULT_SUCCESS);
    assert(dst == U8_C(0));

    /* Min + 1 */
    dst    = U8_C(0);
    status = kdGenMemOpsByteAt(&dst, buf, USIZE_C(4), USIZE_C(1));
    assert(status == RESULT_SUCCESS);
    assert(dst == U8_C(1));

    /* Max - 1 */
    dst    = U8_C(0);
    status = kdGenMemOpsByteAt(&dst, buf, USIZE_C(4), USIZE_C(2));
    assert(status == RESULT_SUCCESS);
    assert(dst == U8_C(254));

    /* Max value */
    dst    = U8_C(0);
    status = kdGenMemOpsByteAt(&dst, buf, USIZE_C(4), USIZE_C(3));
    assert(status == RESULT_SUCCESS);
    assert(dst == U8_C(255));

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    ValidIndexFirstByte();
    ValidIndexLastByte();
    ValidIndexMiddle();
    IndexOutOfBounds();
    AllBytesSequential();
    SingleByte();
    LargeBuffer();
    AllZeros();
    AllOnes();
    SpecificValues();
    OverwriteDestination();
    MultipleCalls();
    EdgeValues();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}