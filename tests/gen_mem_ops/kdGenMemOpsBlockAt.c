/**
 * @file kdGenMemOpsBlockAt.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsBlockAt function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsBlockAt function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


static bool
kdi_BytesEqual(const byte *a, const byte *b, usize sz)
{
    usize i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        if (a[i] != b[i])
        {
            return RESULT_FAILURE;
        }
    }

    return RESULT_SUCCESS;
}


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
    u8   dst[4];
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* dst is null -> failure */
    status = GenMemOpsBlockAt(null, buf, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure */
    status = GenMemOpsBlockAt(dst, null, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = GenMemOpsBlockAt(dst, buf, USIZE_C(0), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure (cannot have 0-size blocks) */
    status = GenMemOpsBlockAt(dst, buf, USIZE_C(16), USIZE_C(0), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ValidBlockExtraction(void)
{
    u8   buf[16];
    u8   dst[4];
    u8   expected[4];
    bool status;

    printf(LOG_PREFIX_CSTR "ValidBlockExtraction -> ");

    /* Init: 0x00, 0x01 ... 0x0F */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Get Block at Byte Offset 0. Bytes [0..3] */
    expected[0] = 0x00;
    expected[1] = 0x01;
    expected[2] = 0x02;
    expected[3] = 0x03;

    status      = GenMemOpsBlockAt(dst, buf, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, expected, USIZE_C(4)) == RESULT_SUCCESS);

    /* Get Block at Byte Offset 12 (Index 3 if interpreted as block idx). Bytes [12..15] */
    expected[0] = 0x0C;
    expected[1] = 0x0D;
    expected[2] = 0x0E;
    expected[3] = 0x0F;

    status      = GenMemOpsBlockAt(dst, buf, USIZE_C(16), USIZE_C(12), USIZE_C(4));
    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, expected, USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
UnalignedAccess(void)
{
    u8   buf[16];
    u8   dst[4];
    u8   expected[4];
    bool status;

    printf(LOG_PREFIX_CSTR "UnalignedAccess -> ");

    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Get Block at Byte Offset 1. Bytes [1..4]. Unaligned relative to block size 4. */
    /* Values: 0x01, 0x02, 0x03, 0x04 */
    expected[0] = 0x01;
    expected[1] = 0x02;
    expected[2] = 0x03;
    expected[3] = 0x04;

    status      = GenMemOpsBlockAt(dst, buf, USIZE_C(16), USIZE_C(1), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(kdi_BytesEqual(dst, expected, USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
OutOfBounds(void)
{
    u8   buf[10];
    u8   dst[4];
    bool status;

    printf(LOG_PREFIX_CSTR "OutOfBounds -> ");

    kdi_FillSeq(buf, USIZE_C(10), U8_C(0x00));

    /* Block size 4. Total size 10. */

    /* Byte Offset 6. Range [6..9] (size 4). Valid (ends at 10). */
    status = GenMemOpsBlockAt(dst, buf, USIZE_C(10), USIZE_C(6), USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Byte Offset 7. Range [7..10] (size 4). Invalid (ends at 11 > 10). */
    status = GenMemOpsBlockAt(dst, buf, USIZE_C(10), USIZE_C(7), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Byte Offset > Total Size */
    status = GenMemOpsBlockAt(dst, buf, USIZE_C(10), USIZE_C(11), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
U8_BlockExtraction(void)
{
    u8   buf[4];
    u8   dst;
    bool status;

    printf(LOG_PREFIX_CSTR "U8_BlockExtraction -> ");

    /* Init: 1, 2, 3, 4 */
    buf[0] = 1;
    buf[1] = 2;
    buf[2] = 3;
    buf[3] = 4;

    /* Get Block at Byte Offset 1 (value 2) */
    dst    = 0;
    status = GenMemOpsBlockAt(&dst, buf, sizeof(buf), USIZE_C(1), sizeof(u8));

    assert(status == RESULT_SUCCESS);
    assert(dst == 2);

    printf("PASSED\n");
}


void
U16_BlockExtraction(void)
{
    u16  buf[4];
    u16  dst;
    bool status;

    printf(LOG_PREFIX_CSTR "U16_BlockExtraction -> ");

    /* Init: 100, 200, 300, 400 */
    buf[0] = 100;
    buf[1] = 200;
    buf[2] = 300;
    buf[3] = 400;

    /* Get Block at Index 3 -> Byte Offset 3 * sizeof(u16) */
    dst    = 0;
    status = GenMemOpsBlockAt(&dst, buf, sizeof(buf), USIZE_C(3) * sizeof(u16), sizeof(u16));

    assert(status == RESULT_SUCCESS);
    assert(dst == 400);

    printf("PASSED\n");
}


void
U32_BlockExtraction(void)
{
    u32  buf[4];
    u32  dst;
    bool status;

    printf(LOG_PREFIX_CSTR "U32_BlockExtraction -> ");

    /* Init: 10, 20, 30, 40 */
    buf[0] = 10;
    buf[1] = 20;
    buf[2] = 30;
    buf[3] = 40;

    /* Get Block at Index 2 -> Byte Offset 2 * sizeof(u32) */
    dst    = 0;
    status = GenMemOpsBlockAt(&dst, buf, sizeof(buf), USIZE_C(2) * sizeof(u32), sizeof(u32));

    assert(status == RESULT_SUCCESS);
    assert(dst == 30);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_BlockExtraction(void)
{
    u64  buf[3];
    u64  dst;
    bool status;

    printf(LOG_PREFIX_CSTR "U64_BlockExtraction -> ");

    /* Init */
    buf[0] = U64_C(0x1111111111111111);
    buf[1] = U64_C(0x2222222222222222);
    buf[2] = U64_C(0x3333333333333333);

    /* Get Block at Index 1 -> Byte Offset 1 * sizeof(u64) */
    dst    = 0;
    status = GenMemOpsBlockAt(&dst, buf, sizeof(buf), USIZE_C(1) * sizeof(u64), sizeof(u64));

    assert(status == RESULT_SUCCESS);
    assert(dst == U64_C(0x2222222222222222));

    printf("PASSED\n");
}
#endif


/* Struct larger than 64 bits */
typedef struct kdi_LargeStruct
{
    u64 a;
    u64 b;
    u32 c;
    u8  d;
} kdi_LargeStruct;


void
Struct_BlockExtraction(void)
{
    kdi_LargeStruct buf[3];
    kdi_LargeStruct dst;
    bool            status;

    printf(LOG_PREFIX_CSTR "Struct_BlockExtraction -> ");

    /* Init */
    buf[0].a = 1;
    buf[0].b = 1;
    buf[1].a = 0xDEADBEEF;
    buf[1].b = 0xCAFEBABE;
    buf[1].c = 12345;
    buf[1].d = 99;
    buf[2].a = 2;
    buf[2].b = 2;

    /* Get Block 1 -> Byte Offset 1 * sizeof(struct) */
    status   = GenMemOpsBlockAt(&dst, buf, sizeof(buf), USIZE_C(1) * sizeof(kdi_LargeStruct), sizeof(kdi_LargeStruct));

    assert(status == RESULT_SUCCESS);
    assert(dst.a == 0xDEADBEEF);
    assert(dst.b == 0xCAFEBABE);
    assert(dst.c == 12345);
    assert(dst.d == 99);

    /* Verify we didn't get neighboring data */
    assert(dst.a != buf[0].a);
    assert(dst.a != buf[2].a);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    ValidBlockExtraction();
    UnalignedAccess();
    OutOfBounds();

    U8_BlockExtraction();
    U16_BlockExtraction();
    U32_BlockExtraction();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_BlockExtraction();
#endif
    Struct_BlockExtraction();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
