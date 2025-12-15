/**
 * @file kdGenMemOpsSwapBlocks.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsSwapBlocks function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsSwapBlocks function test"
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
kdi_FillSeq(byte *dst, usize sz, byte start)
{
    usize i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        dst[i] = (byte)(start + (byte)i);
    }
}


void
BasicArguments(void)
{
    byte buf1[8];
    byte buf2[8];
    byte buf_orig[8];
    bool result;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    kdi_FillSeq(buf1, USIZE_C(8), U8_C(0x10));
    kdi_FillSeq(buf2, USIZE_C(8), U8_C(0x20));
    kdi_FillSeq(buf_orig, USIZE_C(8), U8_C(0x10));

    /* ptr_1 is null -> failure */
    result = GenMemOpsSwapBlocks(null, buf2, USIZE_C(4));
    assert(result == RESULT_FAILURE);

    /* ptr_2 is null -> failure */
    result = GenMemOpsSwapBlocks(buf1, null, USIZE_C(4));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf1, buf_orig, USIZE_C(8)) == RESULT_SUCCESS);

    /* block_sz is zero -> failure */
    result = GenMemOpsSwapBlocks(buf1, buf2, USIZE_C(0));
    assert(result == RESULT_FAILURE);
    assert(kdi_BytesEqual(buf1, buf_orig, USIZE_C(8)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
U16_Blocks_AreSwappedCorrectly(void)
{
    u16  a = U16_C(0x1111);
    u16  b = U16_C(0x2222);
    bool result;

    printf(LOG_PREFIX_CSTR "U16_Blocks_AreSwappedCorrectly -> ");

    result = GenMemOpsSwapBlocks(&a, &b, sizeof(u16));

    assert(result == RESULT_SUCCESS);
    assert(a == U16_C(0x2222));
    assert(b == U16_C(0x1111));

    printf("PASSED\n");
}


void
U32_Blocks_AreSwappedCorrectly(void)
{
    u32  a = U32_C(0x11111111);
    u32  b = U32_C(0x22222222);
    bool result;

    printf(LOG_PREFIX_CSTR "U32_Blocks_AreSwappedCorrectly -> ");

    result = GenMemOpsSwapBlocks(&a, &b, sizeof(u32));

    assert(result == RESULT_SUCCESS);
    assert(a == U32_C(0x22222222));
    assert(b == U32_C(0x11111111));

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_Blocks_AreSwappedCorrectly(void)
{
    u64  a = U64_C(0x1111111111111111);
    u64  b = U64_C(0x2222222222222222);
    bool result;

    printf(LOG_PREFIX_CSTR "U64_Blocks_AreSwappedCorrectly -> ");

    result = GenMemOpsSwapBlocks(&a, &b, sizeof(u64));

    assert(result == RESULT_SUCCESS);
    assert(a == U64_C(0x2222222222222222));
    assert(b == U64_C(0x1111111111111111));

    printf("PASSED\n");
}
#endif


typedef struct kdi_BigStruct
{
    u32 a;
    u32 b;
    u8  c;
} kdi_BigStruct;


void
Struct_Blocks_AreSwappedCorrectly(void)
{
    kdi_BigStruct s1, s2;
    kdi_BigStruct e1, e2;
    bool          result;

    printf(LOG_PREFIX_CSTR "Struct_Blocks_AreSwappedCorrectly -> ");

    s1.a   = U32_C(1);
    s1.b   = U32_C(10);
    s1.c   = U8_C(100);
    s2.a   = U32_C(2);
    s2.b   = U32_C(20);
    s2.c   = U8_C(200);

    /* Expected: s1 takes s2's initial values, s2 takes s1's */
    e1     = s2;
    e2     = s1;

    result = GenMemOpsSwapBlocks(&s1, &s2, sizeof(kdi_BigStruct));

    assert(result == RESULT_SUCCESS);
    /* Check byte-for-byte equality */
    assert(kdi_BytesEqual((byte *)&s1, (byte *)&e1, sizeof(kdi_BigStruct)) == RESULT_SUCCESS);
    assert(kdi_BytesEqual((byte *)&s2, (byte *)&e2, sizeof(kdi_BigStruct)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
Self_Swap_Is_NoOp(void)
{
    byte buf[8];
    byte expected[8];
    bool result;

    printf(LOG_PREFIX_CSTR "Self_Swap_Is_NoOp -> ");

    kdi_FillSeq(buf, USIZE_C(8), U8_C(0x55));
    kdi_FillSeq(expected, USIZE_C(8), U8_C(0x55));

    /* Swapping a block with itself (same address) is a no-op */
    result = GenMemOpsSwapBlocks(buf, buf, USIZE_C(8));

    assert(result == RESULT_SUCCESS);
    assert(kdi_BytesEqual(buf, expected, USIZE_C(8)) == RESULT_SUCCESS);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();

    U16_Blocks_AreSwappedCorrectly();
    U32_Blocks_AreSwappedCorrectly();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_Blocks_AreSwappedCorrectly();
#endif
    Struct_Blocks_AreSwappedCorrectly();

    Self_Swap_Is_NoOp();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
