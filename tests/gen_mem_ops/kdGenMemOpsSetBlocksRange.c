/**
 * @file kdGenMemOpsSetBlocksRange.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsSetBlocksRange function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsSetBlocksRange function test"
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
kdi_FillSeqBytes(byte *dst, usize sz, byte start)
{
    usize i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        dst[i] = (byte)(start + (byte)i);
    }
}


static void
kdi_BuildExpectedRepeatRange(byte *expected, usize expected_sz, usize begin_idx, usize set_sz, const byte *block, usize block_sz)
{
    usize i;

    for (i = USIZE_C(0); i < set_sz && i < expected_sz; ++i)
    {
        expected[begin_idx + i] = block[i % block_sz];
    }
}


/* ---------------------------------------------------------------------------------------------- */
/* Tests */
/* ---------------------------------------------------------------------------------------------- */

void
BasicArguments_AlwaysZeroesSetSz(void)
{
    byte  buf[32];
    byte  orig[32];
    byte  block4[4];
    usize set_sz;

    printf(LOG_PREFIX_CSTR "BasicArguments_AlwaysZeroesSetSz -> ");

    kdi_FillSeqBytes(buf, USIZE_C(32), U8_C(0x10));
    kdi_FillSeqBytes(orig, USIZE_C(32), U8_C(0x10));

    block4[0] = U8_C(0xDE);
    block4[1] = U8_C(0xAD);
    block4[2] = U8_C(0xBE);
    block4[3] = U8_C(0xEF);

    /* set_sz addr is required; function must zero it even on failure */
    set_sz    = USIZE_C(0xDEAD);
    assert(GenMemOpsSetBlocksRange(null, USIZE_C(32), &set_sz, USIZE_C(0), USIZE_C(8), block4, USIZE_C(4)) == RESULT_FAILURE);
    assert(set_sz == USIZE_C(0));
    assert(kdi_BytesEqual(buf, orig, USIZE_C(32)) == RESULT_SUCCESS);

    set_sz = USIZE_C(0xDEAD);
    assert(GenMemOpsSetBlocksRange(buf, USIZE_C(0), &set_sz, USIZE_C(0), USIZE_C(8), block4, USIZE_C(4)) == RESULT_FAILURE);
    assert(set_sz == USIZE_C(0));
    assert(kdi_BytesEqual(buf, orig, USIZE_C(32)) == RESULT_SUCCESS);

    set_sz = USIZE_C(0xDEAD);
    assert(GenMemOpsSetBlocksRange(buf, USIZE_C(32), null, USIZE_C(0), USIZE_C(8), block4, USIZE_C(4)) == RESULT_FAILURE);
    /* can't assert set_sz (null), but dst must remain unchanged */
    assert(kdi_BytesEqual(buf, orig, USIZE_C(32)) == RESULT_SUCCESS);

    set_sz = USIZE_C(0xDEAD);
    assert(GenMemOpsSetBlocksRange(buf, USIZE_C(32), &set_sz, USIZE_C(0), USIZE_C(8), null, USIZE_C(4)) == RESULT_FAILURE);
    assert(set_sz == USIZE_C(0));
    assert(kdi_BytesEqual(buf, orig, USIZE_C(32)) == RESULT_SUCCESS);

    set_sz = USIZE_C(0xDEAD);
    assert(GenMemOpsSetBlocksRange(buf, USIZE_C(32), &set_sz, USIZE_C(0), USIZE_C(8), block4, USIZE_C(0)) == RESULT_FAILURE);
    assert(set_sz == USIZE_C(0));
    assert(kdi_BytesEqual(buf, orig, USIZE_C(32)) == RESULT_SUCCESS);

    /* byte_count == 0 => failure (per your general rule) */
    set_sz = USIZE_C(0xDEAD);
    assert(GenMemOpsSetBlocksRange(buf, USIZE_C(32), &set_sz, USIZE_C(0), USIZE_C(0), block4, USIZE_C(4)) == RESULT_FAILURE);
    assert(set_sz == USIZE_C(0));
    assert(kdi_BytesEqual(buf, orig, USIZE_C(32)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
BeginIdxOutOfBounds_Fails_AndSetSzZero(void)
{
    byte  buf[16];
    byte  orig[16];
    byte  block2[2];
    usize set_sz;

    printf(LOG_PREFIX_CSTR "BeginIdxOutOfBounds_Fails_AndSetSzZero -> ");

    kdi_FillSeqBytes(buf, USIZE_C(16), U8_C(0x20));
    kdi_FillSeqBytes(orig, USIZE_C(16), U8_C(0x20));
    block2[0] = U8_C(0xAB);
    block2[1] = U8_C(0xCD);

    set_sz    = USIZE_C(0xBEEF);
    assert(GenMemOpsSetBlocksRange(buf, USIZE_C(16), &set_sz, USIZE_C(16), USIZE_C(1), block2, USIZE_C(2)) == RESULT_FAILURE);
    assert(set_sz == USIZE_C(0));
    assert(kdi_BytesEqual(buf, orig, USIZE_C(16)) == RESULT_SUCCESS);

    set_sz = USIZE_C(0xBEEF);
    assert(GenMemOpsSetBlocksRange(buf, USIZE_C(16), &set_sz, USIZE_C(100), USIZE_C(4), block2, USIZE_C(2)) == RESULT_FAILURE);
    assert(set_sz == USIZE_C(0));
    assert(kdi_BytesEqual(buf, orig, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SetsExactRange_MultipleOfBlockSize(void)
{
    byte  buf[32];
    byte  expected[32];
    byte  block4[4];
    usize set_sz;

    printf(LOG_PREFIX_CSTR "SetsExactRange_MultipleOfBlockSize -> ");

    kdi_FillSeqBytes(buf, USIZE_C(32), U8_C(0x10));
    kdi_FillSeqBytes(expected, USIZE_C(32), U8_C(0x10));

    block4[0] = U8_C(0x01);
    block4[1] = U8_C(0x02);
    block4[2] = U8_C(0x03);
    block4[3] = U8_C(0x04);

    set_sz    = USIZE_C(0x1234);
    assert(GenMemOpsSetBlocksRange(buf, USIZE_C(32), &set_sz, USIZE_C(8), USIZE_C(16), block4, USIZE_C(4)) == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(16));

    kdi_BuildExpectedRepeatRange(expected, USIZE_C(32), USIZE_C(8), USIZE_C(16), block4, USIZE_C(4));
    assert(kdi_BytesEqual(buf, expected, USIZE_C(32)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SetsClampedRange_WhenByteCountTooLarge(void)
{
    byte  buf[32];
    byte  expected[32];
    byte  block3[3];
    usize set_sz;

    printf(LOG_PREFIX_CSTR "SetsClampedRange_WhenByteCountTooLarge -> ");

    kdi_FillSeqBytes(buf, USIZE_C(32), U8_C(0xA0));
    kdi_FillSeqBytes(expected, USIZE_C(32), U8_C(0xA0));

    block3[0] = U8_C(0xAA);
    block3[1] = U8_C(0xBB);
    block3[2] = U8_C(0xCC);

    /* begin=20, remaining=12, request 100 => set only 12 */
    set_sz    = USIZE_C(0x9999);
    assert(GenMemOpsSetBlocksRange(buf, USIZE_C(32), &set_sz, USIZE_C(20), USIZE_C(100), block3, USIZE_C(3)) == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(12));

    kdi_BuildExpectedRepeatRange(expected, USIZE_C(32), USIZE_C(20), USIZE_C(12), block3, USIZE_C(3));
    assert(kdi_BytesEqual(buf, expected, USIZE_C(32)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
SetsPartialTail_Correctly_WhenNotMultipleOfBlockSize(void)
{
    byte  buf[24];
    byte  expected[24];
    byte  block8[8];
    usize set_sz;

    printf(LOG_PREFIX_CSTR "SetsPartialTail_Correctly_WhenNotMultipleOfBlockSize -> ");

    kdi_FillSeqBytes(buf, USIZE_C(24), U8_C(0x11));
    kdi_FillSeqBytes(expected, USIZE_C(24), U8_C(0x11));

    block8[0] = U8_C(0x10);
    block8[1] = U8_C(0x20);
    block8[2] = U8_C(0x30);
    block8[3] = U8_C(0x40);
    block8[4] = U8_C(0x50);
    block8[5] = U8_C(0x60);
    block8[6] = U8_C(0x70);
    block8[7] = U8_C(0x80);

    /* Set 13 bytes (not multiple of 8) starting at 5 */
    set_sz    = USIZE_C(0x7777);
    assert(GenMemOpsSetBlocksRange(buf, USIZE_C(24), &set_sz, USIZE_C(5), USIZE_C(13), block8, USIZE_C(8)) == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(13));

    kdi_BuildExpectedRepeatRange(expected, USIZE_C(24), USIZE_C(5), USIZE_C(13), block8, USIZE_C(8));
    assert(kdi_BytesEqual(buf, expected, USIZE_C(24)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


/* ------------------------------ */
/* Block-type coverage (u16/u32/u64/struct) */
/* ------------------------------ */

typedef struct kdi_BigStruct
{
    u32 a;
    u32 b;
    u32 c;
    u32 d;
    u16 e;
    u16 f;
} kdi_BigStruct;


void
U16_Range_IsRepeatedCorrectly(void)
{
    u16   buf[20];
    byte  expected_bytes[sizeof(buf)];
    u16   block2[2];
    usize set_sz;

    printf(LOG_PREFIX_CSTR "U16_Range_IsRepeatedCorrectly -> ");

    block2[0] = U16_C(0x1122);
    block2[1] = U16_C(0xA0B0);

    kdi_FillSeqBytes((byte *)buf, USIZE_C(sizeof(buf)), U8_C(0x3A));
    kdi_FillSeqBytes(expected_bytes, USIZE_C(sizeof(buf)), U8_C(0x3A));

    /* begin at byte 6, set 19 bytes (clamps within buffer), repeat block bytes */
    set_sz = USIZE_C(0xAAAA);
    assert(GenMemOpsSetBlocksRange(buf, USIZE_C(sizeof(buf)), &set_sz, USIZE_C(6), USIZE_C(19), block2, USIZE_C(sizeof(block2))) == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(19));

    kdi_BuildExpectedRepeatRange(expected_bytes, USIZE_C(sizeof(buf)), USIZE_C(6), USIZE_C(19), (const byte *)block2, USIZE_C(sizeof(block2)));
    assert(kdi_BytesEqual((const byte *)buf, expected_bytes, USIZE_C(sizeof(buf))) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
U32_Range_IsRepeatedCorrectly(void)
{
    u32   buf[16];
    byte  expected_bytes[sizeof(buf)];
    u32   block3[3];
    usize set_sz;

    printf(LOG_PREFIX_CSTR "U32_Range_IsRepeatedCorrectly -> ");

    block3[0] = U32_C(0x11223344);
    block3[1] = U32_C(0xAABBCCDD);
    block3[2] = U32_C(0x0F1E2D3C);

    kdi_FillSeqBytes((byte *)buf, USIZE_C(sizeof(buf)), U8_C(0x70));
    kdi_FillSeqBytes(expected_bytes, USIZE_C(sizeof(buf)), U8_C(0x70));

    /* begin at byte 4, request 1000 => clamp to remaining */
    set_sz = USIZE_C(0xBBBB);
    assert(GenMemOpsSetBlocksRange(buf, USIZE_C(sizeof(buf)), &set_sz, USIZE_C(4), USIZE_C(1000), block3, USIZE_C(sizeof(block3))) == RESULT_SUCCESS);
    assert(set_sz == (USIZE_C(sizeof(buf)) - USIZE_C(4)));

    kdi_BuildExpectedRepeatRange(expected_bytes, USIZE_C(sizeof(buf)), USIZE_C(4), set_sz, (const byte *)block3, USIZE_C(sizeof(block3)));
    assert(kdi_BytesEqual((const byte *)buf, expected_bytes, USIZE_C(sizeof(buf))) == RESULT_SUCCESS);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_Range_IsRepeatedCorrectly(void)
{
    u64   buf[10];
    byte  expected_bytes[sizeof(buf)];
    u64   block2[2];
    usize set_sz;

    printf(LOG_PREFIX_CSTR "U64_Range_IsRepeatedCorrectly -> ");

    block2[0] = U64_C(0x1122334455667788);
    block2[1] = U64_C(0xAABBCCDDEEFF0011);

    kdi_FillSeqBytes((byte *)buf, USIZE_C(sizeof(buf)), U8_C(0x19));
    kdi_FillSeqBytes(expected_bytes, USIZE_C(sizeof(buf)), U8_C(0x19));

    /* begin at byte 9, set 17 bytes */
    set_sz = USIZE_C(0xCCCC);
    assert(GenMemOpsSetBlocksRange(buf, USIZE_C(sizeof(buf)), &set_sz, USIZE_C(9), USIZE_C(17), block2, USIZE_C(sizeof(block2))) == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(17));

    kdi_BuildExpectedRepeatRange(expected_bytes, USIZE_C(sizeof(buf)), USIZE_C(9), USIZE_C(17), (const byte *)block2, USIZE_C(sizeof(block2)));
    assert(kdi_BytesEqual((const byte *)buf, expected_bytes, USIZE_C(sizeof(buf))) == RESULT_SUCCESS);

    printf("PASSED\n");
}
#endif


void
Struct_Range_IsRepeatedCorrectly(void)
{
    kdi_BigStruct buf[6];
    byte          expected_bytes[sizeof(buf)];
    kdi_BigStruct block2[2];
    usize         set_sz;

    printf(LOG_PREFIX_CSTR "Struct_Range_IsRepeatedCorrectly -> ");

    block2[0].a = U32_C(0x01020304);
    block2[0].b = U32_C(0x11121314);
    block2[0].c = U32_C(0x21222324);
    block2[0].d = U32_C(0x31323334);
    block2[0].e = U16_C(0x4546);
    block2[0].f = U16_C(0x6768);

    block2[1].a = U32_C(0xA1A2A3A4);
    block2[1].b = U32_C(0xB1B2B3B4);
    block2[1].c = U32_C(0xC1C2C3C4);
    block2[1].d = U32_C(0xD1D2D3D4);
    block2[1].e = U16_C(0xE5E6);
    block2[1].f = U16_C(0xF7F8);

    kdi_FillSeqBytes((byte *)buf, USIZE_C(sizeof(buf)), U8_C(0x5C));
    kdi_FillSeqBytes(expected_bytes, USIZE_C(sizeof(buf)), U8_C(0x5C));

    /* begin at byte 3, set 41 bytes */
    set_sz = USIZE_C(0xDDDD);
    assert(GenMemOpsSetBlocksRange(buf, USIZE_C(sizeof(buf)), &set_sz, USIZE_C(3), USIZE_C(41), block2, USIZE_C(sizeof(block2))) == RESULT_SUCCESS);
    assert(set_sz == USIZE_C(41));

    kdi_BuildExpectedRepeatRange(expected_bytes, USIZE_C(sizeof(buf)), USIZE_C(3), USIZE_C(41), (const byte *)block2, USIZE_C(sizeof(block2)));
    assert(kdi_BytesEqual((const byte *)buf, expected_bytes, USIZE_C(sizeof(buf))) == RESULT_SUCCESS);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments_AlwaysZeroesSetSz();
    BeginIdxOutOfBounds_Fails_AndSetSzZero();

    SetsExactRange_MultipleOfBlockSize();
    SetsClampedRange_WhenByteCountTooLarge();
    SetsPartialTail_Correctly_WhenNotMultipleOfBlockSize();

    U16_Range_IsRepeatedCorrectly();
    U32_Range_IsRepeatedCorrectly();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_Range_IsRepeatedCorrectly();
#endif
    Struct_Range_IsRepeatedCorrectly();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
