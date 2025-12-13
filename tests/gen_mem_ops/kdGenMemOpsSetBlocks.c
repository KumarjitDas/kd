/**
 * @file kdGenMemOpsSetBlocks.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsSetBlocks function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsSetBlocks function test"
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


/* Verifies dst[0..dst_sz) is block repeated. The last partial chunk (if any) must match block prefix. */
static bool
kdi_IsRepeatedBlockBytes(const byte *dst, usize dst_sz, const byte *block, usize block_sz)
{
    usize i;

    if (!dst || !dst_sz || !block || !block_sz)
    {
        return RESULT_FAILURE;
    }

    for (i = USIZE_C(0); i < dst_sz; ++i)
    {
        if (dst[i] != block[i % block_sz])
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


/* Build expected buffer = repeating block bytes. */
static void
kdi_BuildExpectedRepeat(byte *expected, usize expected_sz, const byte *block, usize block_sz)
{
    usize i;

    for (i = USIZE_C(0); i < expected_sz; ++i)
    {
        expected[i] = block[i % block_sz];
    }
}


/* ---------------------------------------------------------------------------------------------- */
/* Tests */
/* ---------------------------------------------------------------------------------------------- */

void
BasicArguments(void)
{
    byte buf[16];
    byte orig[16];
    byte block4[4];
    bool result;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillSeqBytes(buf, USIZE_C(16), U8_C(0x10));
    kdi_FillSeqBytes(orig, USIZE_C(16), U8_C(0x10));
    kdi_FillSeqBytes(block4, USIZE_C(4), U8_C(0xA0));

    /* dst is null => failure */
    result = GenMemOpsSetBlocks(null, USIZE_C(16), block4, USIZE_C(4));
    assert(result == RESULT_FAILURE);

    /* block is null => failure, dst unchanged */
    result = GenMemOpsSetBlocks(buf, USIZE_C(16), null, USIZE_C(4));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf, orig, USIZE_C(16)) == RESULT_SUCCESS);

    /* dst_sz == 0 => failure, dst unchanged */
    result = GenMemOpsSetBlocks(buf, USIZE_C(0), block4, USIZE_C(4));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf, orig, USIZE_C(16)) == RESULT_SUCCESS);

    /* block_sz == 0 => failure, dst unchanged */
    result = GenMemOpsSetBlocks(buf, USIZE_C(16), block4, USIZE_C(0));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf, orig, USIZE_C(16)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
Bytes_ExactMultipleOfBlockSize(void)
{
    byte buf[16];
    byte block4[4];
    bool result;

    printf(LOG_PREFIX_CSTR "Bytes_ExactMultipleOfBlockSize -> ");

    kdi_FillSeqBytes(buf, USIZE_C(16), U8_C(0x00));
    block4[0] = U8_C(0xDE);
    block4[1] = U8_C(0xAD);
    block4[2] = U8_C(0xBE);
    block4[3] = U8_C(0xEF);

    result    = GenMemOpsSetBlocks(buf, USIZE_C(16), block4, USIZE_C(4));
    assert(result == RESULT_SUCCESS);
    assert(kdi_IsRepeatedBlockBytes(buf, USIZE_C(16), block4, USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
Bytes_NonMultipleOfBlockSize_PartialTailMatchesPrefix(void)
{
    byte buf[10];
    byte block4[4];
    bool result;

    printf(LOG_PREFIX_CSTR "Bytes_NonMultipleOfBlockSize_PartialTailMatchesPrefix -> ");

    kdi_FillSeqBytes(buf, USIZE_C(10), U8_C(0x55));
    block4[0] = U8_C(0x11);
    block4[1] = U8_C(0x22);
    block4[2] = U8_C(0x33);
    block4[3] = U8_C(0x44);

    result    = GenMemOpsSetBlocks(buf, USIZE_C(10), block4, USIZE_C(4));
    assert(result == RESULT_SUCCESS);
    assert(kdi_IsRepeatedBlockBytes(buf, USIZE_C(10), block4, USIZE_C(4)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
Bytes_BlockSizeLargerThanDstSize_OnlyPrefixIsCopied(void)
{
    byte buf[6];
    byte block8[8];
    bool result;

    printf(LOG_PREFIX_CSTR "Bytes_BlockSizeLargerThanDstSize_OnlyPrefixIsCopied -> ");

    kdi_FillSeqBytes(buf, USIZE_C(6), U8_C(0x77));

    block8[0] = U8_C(0x01);
    block8[1] = U8_C(0x02);
    block8[2] = U8_C(0x03);
    block8[3] = U8_C(0x04);
    block8[4] = U8_C(0x05);
    block8[5] = U8_C(0x06);
    block8[6] = U8_C(0x07);
    block8[7] = U8_C(0x08);

    result    = GenMemOpsSetBlocks(buf, USIZE_C(6), block8, USIZE_C(8));
    assert(result == RESULT_SUCCESS);
    assert(kdi_IsRepeatedBlockBytes(buf, USIZE_C(6), block8, USIZE_C(8)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


/* ------------------------------ */
/* Block-type coverage (u16/u32/u64/struct) */
/* ------------------------------ */

void
U16_Blocks_AreRepeatedCorrectly(void)
{
    u16  buf[13];
    u16  block2[2];
    byte expected_bytes[sizeof(buf)];
    bool result;

    printf(LOG_PREFIX_CSTR "U16_Blocks_AreRepeatedCorrectly -> ");

    block2[0] = U16_C(0x1122);
    block2[1] = U16_C(0xA0B0);

    /* Fill dst with non-zero junk first */
    kdi_FillSeqBytes((byte *)buf, USIZE_C(sizeof(buf)), U8_C(0x33));

    result = GenMemOpsSetBlocks(buf, USIZE_C(sizeof(buf)), block2, USIZE_C(sizeof(block2)));
    assert(result == RESULT_SUCCESS);

    kdi_BuildExpectedRepeat(expected_bytes, USIZE_C(sizeof(buf)), (const byte *)block2, USIZE_C(sizeof(block2)));
    assert(kdi_BytesEqual((const byte *)buf, expected_bytes, USIZE_C(sizeof(buf))) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
U32_Blocks_AreRepeatedCorrectly(void)
{
    u32  buf[11];
    u32  block3[3];
    byte expected_bytes[sizeof(buf)];
    bool result;

    printf(LOG_PREFIX_CSTR "U32_Blocks_AreRepeatedCorrectly -> ");

    block3[0] = U32_C(0x11223344);
    block3[1] = U32_C(0xAABBCCDD);
    block3[2] = U32_C(0x0F1E2D3C);

    kdi_FillSeqBytes((byte *)buf, USIZE_C(sizeof(buf)), U8_C(0x77));

    result = GenMemOpsSetBlocks(buf, USIZE_C(sizeof(buf)), block3, USIZE_C(sizeof(block3)));
    assert(result == RESULT_SUCCESS);

    kdi_BuildExpectedRepeat(expected_bytes, USIZE_C(sizeof(buf)), (const byte *)block3, USIZE_C(sizeof(block3)));
    assert(kdi_BytesEqual((const byte *)buf, expected_bytes, USIZE_C(sizeof(buf))) == RESULT_SUCCESS);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_Blocks_AreRepeatedCorrectly(void)
{
    u64  buf[9];
    u64  block2[2];
    byte expected_bytes[sizeof(buf)];
    bool result;

    printf(LOG_PREFIX_CSTR "U64_Blocks_AreRepeatedCorrectly -> ");

    block2[0] = U64_C(0x1122334455667788);
    block2[1] = U64_C(0xAABBCCDDEEFF0011);

    kdi_FillSeqBytes((byte *)buf, USIZE_C(sizeof(buf)), U8_C(0x19));

    result = GenMemOpsSetBlocks(buf, USIZE_C(sizeof(buf)), block2, USIZE_C(sizeof(block2)));
    assert(result == RESULT_SUCCESS);

    kdi_BuildExpectedRepeat(expected_bytes, USIZE_C(sizeof(buf)), (const byte *)block2, USIZE_C(sizeof(block2)));
    assert(kdi_BytesEqual((const byte *)buf, expected_bytes, USIZE_C(sizeof(buf))) == RESULT_SUCCESS);

    printf("PASSED\n");
}
#endif


typedef struct kdi_BigStruct
{
    u32 a;
    u32 b;
    u32 c;
    u32 d;
    u16 e;
    u16 f;
} kdi_BigStruct; /* 20 bytes (>= 8 always, > 4 always) */


void
Struct_Blocks_AreRepeatedCorrectly(void)
{
    kdi_BigStruct buf[7];
    kdi_BigStruct block2[2];
    byte          expected_bytes[sizeof(buf)];
    bool          result;

    printf(LOG_PREFIX_CSTR "Struct_Blocks_AreRepeatedCorrectly -> ");

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

    result = GenMemOpsSetBlocks(buf, USIZE_C(sizeof(buf)), block2, USIZE_C(sizeof(block2)));
    assert(result == RESULT_SUCCESS);

    kdi_BuildExpectedRepeat(expected_bytes, USIZE_C(sizeof(buf)), (const byte *)block2, USIZE_C(sizeof(block2)));
    assert(kdi_BytesEqual((const byte *)buf, expected_bytes, USIZE_C(sizeof(buf))) == RESULT_SUCCESS);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();

    Bytes_ExactMultipleOfBlockSize();
    Bytes_NonMultipleOfBlockSize_PartialTailMatchesPrefix();
    Bytes_BlockSizeLargerThanDstSize_OnlyPrefixIsCopied();

    U16_Blocks_AreRepeatedCorrectly();
    U32_Blocks_AreRepeatedCorrectly();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_Blocks_AreRepeatedCorrectly();
#endif
    Struct_Blocks_AreRepeatedCorrectly();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
