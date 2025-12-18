/**
 * @file kdGenMemOpsSetBlockAt.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsSetBlockAt function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsSetBlockAt function test"
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
    u8   buf[16];
    u8   src[4];
    bool status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));
    kdi_FillVal(src, USIZE_C(4), U8_C(0xFF));

    /* base is null -> failure */
    status = GenMemOpsSetBlockAt(null, USIZE_C(16), USIZE_C(0), src, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    status = GenMemOpsSetBlockAt(buf, USIZE_C(16), USIZE_C(0), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = GenMemOpsSetBlockAt(buf, USIZE_C(0), USIZE_C(0), src, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure (cannot set 0-size block) */
    status = GenMemOpsSetBlockAt(buf, USIZE_C(16), USIZE_C(0), src, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ValidBlockSet(void)
{
    u8   buf[16];
    u8   src[4];
    bool status;

    printf(LOG_PREFIX_CSTR "ValidBlockSet -> ");

    /* Init Buf: 0x00, 0x01, ... */
    kdi_FillSeq(buf, USIZE_C(16), U8_C(0x00));

    /* Init Src: All 0xFF */
    kdi_FillVal(src, USIZE_C(4), U8_C(0xFF));

    /* Set block at Byte Offset 0 */
    status = GenMemOpsSetBlockAt(buf, USIZE_C(16), USIZE_C(0), src, USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Check result: [FF, FF, FF, FF, 04, 05...] */
    assert(buf[0] == 0xFF);
    assert(buf[1] == 0xFF);
    assert(buf[2] == 0xFF);
    assert(buf[3] == 0xFF);
    assert(buf[4] == 0x04); /* Untouched (from FillSeq) */

    /* Set block at Byte Offset 12 (Index 3 for 4-byte blocks) */
    status = GenMemOpsSetBlockAt(buf, USIZE_C(16), USIZE_C(12), src, USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Check result: [..., 0B, FF, FF, FF, FF] */
    assert(buf[11] == 0x0B); /* Untouched */
    assert(buf[12] == 0xFF);
    assert(buf[13] == 0xFF);
    assert(buf[14] == 0xFF);
    assert(buf[15] == 0xFF);

    printf("PASSED\n");
}


void
OutOfBounds(void)
{
    u8   buf[10];
    u8   src[4];
    bool status;

    printf(LOG_PREFIX_CSTR "OutOfBounds -> ");

    kdi_FillSeq(buf, USIZE_C(10), U8_C(0x00));
    kdi_FillVal(src, USIZE_C(4), U8_C(0xFF));

    /* Byte Offset 6. Range [6..9] (size 4). Valid (ends at 10). */
    status = GenMemOpsSetBlockAt(buf, USIZE_C(10), USIZE_C(6), src, USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    /* Verify write occurred */
    assert(buf[6] == 0xFF);
    assert(buf[9] == 0xFF);

    /* Byte Offset 7. Range [7..10] (size 4). Invalid (ends at 11 > 10). */
    status = GenMemOpsSetBlockAt(buf, USIZE_C(10), USIZE_C(7), src, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Verify previous write not corrupted / no OOB write happened */
    assert(buf[9] == 0xFF);

    printf("PASSED\n");
}


void
UnalignedAccess(void)
{
    u8   buf[16];
    u8   src[4];
    bool status;

    printf(LOG_PREFIX_CSTR "UnalignedAccess -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));
    kdi_FillVal(src, USIZE_C(4), U8_C(0xAA));

    /* Set at Byte Offset 1. Overwrites indices 1, 2, 3, 4. */
    status = GenMemOpsSetBlockAt(buf, USIZE_C(16), USIZE_C(1), src, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(buf[0] == 0x00);
    assert(buf[1] == 0xAA);
    assert(buf[2] == 0xAA);
    assert(buf[3] == 0xAA);
    assert(buf[4] == 0xAA);
    assert(buf[5] == 0x00);

    printf("PASSED\n");
}


void
U8_BlockSet(void)
{
    u8   buf[4];
    u8   val;
    bool status;

    printf(LOG_PREFIX_CSTR "U8_BlockSet -> ");

    kdi_FillSeq(buf, USIZE_C(4), U8_C(0x00)); /* 0, 1, 2, 3 */
    val    = 0xFF;

    /* Set index 1 to 0xFF */
    status = GenMemOpsSetBlockAt(buf, sizeof(buf), USIZE_C(1), &val, sizeof(u8));

    assert(status == RESULT_SUCCESS);
    assert(buf[0] == 0x00);
    assert(buf[1] == 0xFF);
    assert(buf[2] == 0x02);

    printf("PASSED\n");
}


void
U16_BlockSet(void)
{
    u16  buf[4];
    u16  val;
    bool status;

    printf(LOG_PREFIX_CSTR "U16_BlockSet -> ");

    /* Init: 0, 0, 0, 0 */
    buf[0] = 0;
    buf[1] = 0;
    buf[2] = 0;
    buf[3] = 0;
    val    = 0xFFFF;

    /* Set at Byte Offset 2 * sizeof(u16) (Index 2) */
    status = GenMemOpsSetBlockAt(buf, sizeof(buf), USIZE_C(2) * sizeof(u16), &val, sizeof(u16));

    assert(status == RESULT_SUCCESS);
    assert(buf[1] == 0);
    assert(buf[2] == 0xFFFF);
    assert(buf[3] == 0);

    printf("PASSED\n");
}


void
U32_BlockSet(void)
{
    u32  buf[4];
    u32  val;
    bool status;

    printf(LOG_PREFIX_CSTR "U32_BlockSet -> ");

    /* Init */
    buf[0] = 0;
    buf[1] = 0;
    buf[2] = 0;
    buf[3] = 0;
    val    = 0x12345678;

    /* Set at Byte Offset 1 * sizeof(u32) (Index 1) */
    status = GenMemOpsSetBlockAt(buf, sizeof(buf), USIZE_C(1) * sizeof(u32), &val, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    assert(buf[0] == 0);
    assert(buf[1] == 0x12345678);
    assert(buf[2] == 0);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_BlockSet(void)
{
    u64  buf[3];
    u64  val;
    bool status;

    printf(LOG_PREFIX_CSTR "U64_BlockSet -> ");

    /* Init */
    buf[0] = 0;
    buf[1] = 0;
    buf[2] = 0;
    val    = U64_C(0xFEEDFACECAFEBABE);

    /* Set at Byte Offset 1 * sizeof(u64) */
    status = GenMemOpsSetBlockAt(buf, sizeof(buf), USIZE_C(1) * sizeof(u64), &val, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    assert(buf[0] == 0);
    assert(buf[1] == U64_C(0xFEEDFACECAFEBABE));
    assert(buf[2] == 0);

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
Struct_BlockSet(void)
{
    kdi_LargeStruct buf[3];
    kdi_LargeStruct src;
    bool            status;

    printf(LOG_PREFIX_CSTR "Struct_BlockSet -> ");

    /* Init buffer */
    buf[0].a = 0;
    buf[0].b = 0;
    buf[1].a = 0;
    buf[1].b = 0;
    buf[2].a = 0;
    buf[2].b = 0;

    /* Init source */
    src.a    = 0xDEADBEEF;
    src.b    = 0xCAFEBABE;
    src.c    = 12345;
    src.d    = 77;

    /* Set at Byte Offset 1 * sizeof(struct) (Index 1) */
    status   = GenMemOpsSetBlockAt(buf, sizeof(buf), USIZE_C(1) * sizeof(kdi_LargeStruct), &src, sizeof(kdi_LargeStruct));

    assert(status == RESULT_SUCCESS);

    /* Verify Index 1 set */
    assert(buf[1].a == 0xDEADBEEF);
    assert(buf[1].b == 0xCAFEBABE);
    assert(buf[1].c == 12345);
    assert(buf[1].d == 77);

    /* Verify neighbors untouched */
    assert(buf[0].a == 0);
    assert(buf[2].a == 0);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    ValidBlockSet();
    OutOfBounds();
    UnalignedAccess();

    U8_BlockSet();
    U16_BlockSet();
    U32_BlockSet();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_BlockSet();
#endif
    Struct_BlockSet();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
