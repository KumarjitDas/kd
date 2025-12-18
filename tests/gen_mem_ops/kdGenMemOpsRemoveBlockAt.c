/**
 * @file kdGenMemOpsRemoveBlockAt.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsRemoveBlockAt function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsRemoveBlockAt function test"
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
    u8    buf[16];
    usize len = 4;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* base is null -> failure */
    status = GenMemOpsRemoveBlockAt(null, USIZE_C(16), &len, USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_elems pointer is null -> failure */
    status = GenMemOpsRemoveBlockAt(buf, USIZE_C(16), null, USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_cap is zero -> failure */
    status = GenMemOpsRemoveBlockAt(buf, USIZE_C(0), &len, USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = GenMemOpsRemoveBlockAt(buf, USIZE_C(16), &len, USIZE_C(0), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
RemoveHead(void)
{
    u8    buf[16];
    usize len = 12;
    bool  status;

    printf(LOG_PREFIX_CSTR "RemoveHead -> ");

    /* Init: Block 0 (0x01..), Block 1 (0x02..), Block 2 (0x03..) */
    buf[0]  = 1;
    buf[1]  = 1;
    buf[2]  = 1;
    buf[3]  = 1;
    buf[4]  = 2;
    buf[5]  = 2;
    buf[6]  = 2;
    buf[7]  = 2;
    buf[8]  = 3;
    buf[9]  = 3;
    buf[10] = 3;
    buf[11] = 3;

    /* Remove Block at Offset 0 (Size 4) */
    status  = GenMemOpsRemoveBlockAt(buf, USIZE_C(16), &len, USIZE_C(0), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(8));

    /* Verify shift: Block 1 moved to 0, Block 2 moved to 4 */
    assert(buf[0] == 2);
    assert(buf[1] == 2);
    assert(buf[4] == 3);
    assert(buf[5] == 3);

    printf("PASSED\n");
}


void
RemoveTail(void)
{
    u8    buf[16];
    usize len = 12;
    bool  status;

    printf(LOG_PREFIX_CSTR "RemoveTail -> ");

    /* Init: 0x01.., 0x02.., 0x03.. */
    buf[0] = 1;
    buf[4] = 2;
    buf[8] = 3; /* abbreviated init */

    /* Remove Block at Offset 8 (Last block) */
    status = GenMemOpsRemoveBlockAt(buf, USIZE_C(16), &len, USIZE_C(8), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(8));

    /* Verify head untouched */
    assert(buf[0] == 1);
    assert(buf[4] == 2);

    /* Verify tail is logically gone (though data might remain in memory, len is updated) */
    /* Implementation might zero out or leave garbage, we only check len and valid region */

    printf("PASSED\n");
}


void
RemoveMiddle(void)
{
    u8    buf[16];
    usize len = 12;
    bool  status;

    printf(LOG_PREFIX_CSTR "RemoveMiddle -> ");

    /* Init: Block 0 (1), Block 1 (2), Block 2 (3) */
    buf[0]  = 1;
    buf[1]  = 1;
    buf[2]  = 1;
    buf[3]  = 1;
    buf[4]  = 2;
    buf[5]  = 2;
    buf[6]  = 2;
    buf[7]  = 2;
    buf[8]  = 3;
    buf[9]  = 3;
    buf[10] = 3;
    buf[11] = 3;

    /* Remove Block at Offset 4 (Block 1) */
    status  = GenMemOpsRemoveBlockAt(buf, USIZE_C(16), &len, USIZE_C(4), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(8));

    /* Verify: [1, 1, 1, 1, 3, 3, 3, 3] */
    assert(buf[0] == 1);
    assert(buf[4] == 3);

    printf("PASSED\n");
}


void
RemoveSingleBlock(void)
{
    u8    buf[16];
    usize len = 4;
    bool  status;

    printf(LOG_PREFIX_CSTR "RemoveSingleBlock -> ");

    buf[0] = 0xAA;

    /* Remove Offset 0 */
    status = GenMemOpsRemoveBlockAt(buf, USIZE_C(16), &len, USIZE_C(0), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(len == USIZE_C(0));

    printf("PASSED\n");
}


void
RemoveFromEmpty(void)
{
    u8    buf[16];
    usize len = 0;
    bool  status;

    printf(LOG_PREFIX_CSTR "RemoveFromEmpty -> ");

    status = GenMemOpsRemoveBlockAt(buf, USIZE_C(16), &len, USIZE_C(0), USIZE_C(4));

    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(0));

    printf("PASSED\n");
}


void
OutOfBounds(void)
{
    u8    buf[16];
    usize len = 8;
    bool  status;

    printf(LOG_PREFIX_CSTR "OutOfBounds -> ");

    /* Remove at Offset 8. Valid data is [0..7]. Offset 8 is out of bounds. */
    status = GenMemOpsRemoveBlockAt(buf, USIZE_C(16), &len, USIZE_C(8), USIZE_C(4));

    assert(status == RESULT_FAILURE);
    assert(len == USIZE_C(8));

    /* Remove at Offset 5 (Valid start, but size 4 goes to 9 > 8). Partial overlap beyond len. */
    status = GenMemOpsRemoveBlockAt(buf, USIZE_C(16), &len, USIZE_C(5), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
U16_Remove(void)
{
    u16   buf[4];
    usize len = 6; /* 3 elements (bytes 0..5) */
    usize cap = 8;
    bool  status;

    printf(LOG_PREFIX_CSTR "U16_Remove -> ");

    /* Init: 100, 200, 300 */
    buf[0] = 100;
    buf[1] = 200;
    buf[2] = 300;

    /* Remove Index 1 (Offset 2 bytes). Value 200. */
    /* Expect: 100, 300 */
    status = GenMemOpsRemoveBlockAt(buf, cap, &len, USIZE_C(1) * sizeof(u16), sizeof(u16));

    assert(status == RESULT_SUCCESS);
    assert(len == 4);
    assert(buf[0] == 100);
    assert(buf[1] == 300);

    printf("PASSED\n");
}


void
U32_Remove(void)
{
    u32   buf[4];
    usize len = 12; /* 3 elements */
    usize cap = 16;
    bool  status;

    printf(LOG_PREFIX_CSTR "U32_Remove -> ");

    /* Init: 10, 20, 30 */
    buf[0] = 10;
    buf[1] = 20;
    buf[2] = 30;

    /* Remove Index 0 (Offset 0 bytes). Value 10. */
    /* Expect: 20, 30 */
    status = GenMemOpsRemoveBlockAt(buf, cap, &len, 0, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    assert(len == 8);
    assert(buf[0] == 20);
    assert(buf[1] == 30);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
U64_Remove(void)
{
    u64   buf[4];
    usize len = 24; /* 3 elements */
    usize cap = 32;
    bool  status;

    printf(LOG_PREFIX_CSTR "U64_Remove -> ");

    /* Init: 1, 2, 3 */
    buf[0] = 1;
    buf[1] = 2;
    buf[2] = 3;

    /* Remove Index 2 (Offset 16 bytes). Value 3. */
    /* Expect: 1, 2 */
    status = GenMemOpsRemoveBlockAt(buf, cap, &len, USIZE_C(2) * sizeof(u64), sizeof(u64));

    assert(status == RESULT_SUCCESS);
    assert(len == 16);
    assert(buf[0] == 1);
    assert(buf[1] == 2);

    printf("PASSED\n");
}
#endif


typedef struct kdi_LargeStruct
{
    u64 a;
    u64 b;
    u32 c;
    u8  d;
} kdi_LargeStruct;


void
Struct_Remove(void)
{
    kdi_LargeStruct buf[3];
    usize           elem_sz = sizeof(kdi_LargeStruct);
    usize           cap     = 3 * elem_sz;
    usize           len     = 3 * elem_sz;
    bool            status;

    printf(LOG_PREFIX_CSTR "Struct_Remove -> ");

    /* Init: [S0, S1, S2] */
    buf[0].a = 0;
    buf[1].a = 1;
    buf[2].a = 2;

    /* Remove Index 1 (Offset elem_sz). S1. */
    /* Expect: [S0, S2] */
    status   = GenMemOpsRemoveBlockAt(buf, cap, &len, elem_sz, elem_sz);

    assert(status == RESULT_SUCCESS);
    assert(len == 2 * elem_sz);

    assert(buf[0].a == 0);
    /* Index 1 now holds S2 */
    assert(buf[1].a == 2);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    RemoveHead();
    RemoveTail();
    RemoveMiddle();
    RemoveSingleBlock();
    RemoveFromEmpty();
    OutOfBounds();

    U16_Remove();
    U32_Remove();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    U64_Remove();
#endif
    Struct_Remove();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
