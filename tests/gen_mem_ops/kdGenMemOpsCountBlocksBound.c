/**
 * @file kdGenMemOpsCountBlocksBound.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsCountBlocksBound function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsCountBlocksBound function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


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
    u8    blk[4];
    usize count = 55;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* count pointer is null -> failure */
    status = GenMemOpsCountBlocksBound(null, buf, USIZE_C(16), 0, 16, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base is null -> failure */
    status = GenMemOpsCountBlocksBound(&count, null, USIZE_C(16), 0, 16, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero -> failure */
    status = GenMemOpsCountBlocksBound(&count, buf, USIZE_C(0), 0, 16, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    status = GenMemOpsCountBlocksBound(&count, buf, USIZE_C(16), 0, 16, null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = GenMemOpsCountBlocksBound(&count, buf, USIZE_C(16), 0, 16, blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* block_sz > base_sz -> failure */
    status = GenMemOpsCountBlocksBound(&count, buf, USIZE_C(4), 0, 16, blk, USIZE_C(16));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
StartAlignment(void)
{
    u8    buf[16];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "StartAlignment -> ");

    /* Block size 4. Start index MUST be aligned. */

    /* Case 1: Start 1 (1 % 4 != 0) -> Failure */
    status = GenMemOpsCountBlocksBound(&count, buf, USIZE_C(16), 1, 12, blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* Case 2: Start 4 (4 % 4 == 0) -> Success (Arg check pass) */
    kdi_FillVal(buf, 16, 0x00);
    kdi_FillVal(blk, 4, 0xAA);
    status = GenMemOpsCountBlocksBound(&count, buf, USIZE_C(16), 4, 12, blk, USIZE_C(4));
    assert(status == RESULT_SUCCESS);

    printf("PASSED\n");
}


void
CountAlignmentRelaxed(void)
{
    u8    buf[16];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountAlignmentRelaxed -> ");

    /* Block size 4. Count need not be aligned. */

    kdi_FillVal(buf, 16, 0xAA);
    kdi_FillVal(blk, 4, 0xAA);

    /* Start 0, Count 7.
     * Blocks fit: floor(7 / 4) = 1 block (Offset 0).
     * Offset 4 requires 8 bytes. 7 is not enough.
     */
    status = GenMemOpsCountBlocksBound(&count, buf, USIZE_C(16), 0, 7, blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    /* 1 match * 4 bytes = 4 */
    assert(count == 4);

    printf("PASSED\n");
}


void
EndValueClamping(void)
{
    u8    buf[16];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "EndValueClamping -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));
    kdi_FillVal(blk, 4, 0xAA);

    /* Requesting 100 bytes starting at 0.
     * Clamps to 16. Range [0, 16).
     * 4 blocks fit (0, 4, 8, 12).
     */
    status = GenMemOpsCountBlocksBound(&count, buf, USIZE_C(16), 0, 100, blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    /* 4 matches * 4 bytes = 16 */
    assert(count == 16);

    printf("PASSED\n");
}


void
CountNone(void)
{
    u8    buf[16];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountNone -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0x00));
    kdi_FillVal(blk, 4, 0xAA);

    status = GenMemOpsCountBlocksBound(&count, buf, USIZE_C(16), 0, 16, blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(count == 0);

    printf("PASSED\n");
}


void
RangeConstraints(void)
{
    u8    buf[32];
    u8    blk[4];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "RangeConstraints -> ");

    kdi_FillVal(buf, USIZE_C(32), U8_C(0x00));
    kdi_FillVal(blk, 4, 0xAA);

    /* Targets at 4, 12, 20, 28 */
    kdi_FillVal(buf + 4, 4, 0xAA);
    kdi_FillVal(buf + 12, 4, 0xAA);
    kdi_FillVal(buf + 20, 4, 0xAA);
    kdi_FillVal(buf + 28, 4, 0xAA);

    /* Start 8, Count 16.
     * Effective Range: [8, 24).
     * Offsets: 8, 12, 16, 20.
     * Matches at 12 and 20.
     */
    status = GenMemOpsCountBlocksBound(&count, buf, USIZE_C(32), 8, 16, blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    /* 2 matches * 4 bytes = 8 */
    assert(count == 8);

    printf("PASSED\n");
}


void
UnalignedMatchIgnored(void)
{
    u8    buf[10];
    u8    blk[2];
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "UnalignedMatchIgnored -> ");

    kdi_FillVal(buf, USIZE_C(10), U8_C(0x00));

    /* Target at offset 3 */
    buf[3] = 0xAA;
    buf[4] = 0xBB;

    blk[0] = 0xAA;
    blk[1] = 0xBB;

    /* Start 0, Count 6.
     * Scans 0, 2, 4.
     * Match at 3 is unaligned (3 % 2 != 0).
     */
    status = GenMemOpsCountBlocksBound(&count, buf, USIZE_C(10), 0, 6, blk, USIZE_C(2));

    assert(status == RESULT_SUCCESS);
    assert(count == 0);

    printf("PASSED\n");
}


void
CountBlocksBound_U16(void)
{
    u16   buf[10];
    u16   blk = 0xAAAA;
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountBlocksBound_U16 -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    buf[2] = 0xAAAA;
    buf[5] = 0xAAAA;
    buf[8] = 0xAAAA;

    /* Start 4 bytes (Index 2), Count 12 bytes (6 elements).
     * Range [4, 16).
     * Indices: 2, 3, 4, 5, 6, 7.
     * Matches at 2 and 5.
     */
    status = GenMemOpsCountBlocksBound(&count, buf, sizeof(buf), 4, 12, &blk, sizeof(u16));

    assert(status == RESULT_SUCCESS);
    /* 2 matches * 2 bytes = 4 */
    assert(count == 4);

    printf("PASSED\n");
}


void
CountBlocksBound_U32(void)
{
    u32   buf[10];
    u32   blk = 0x12345678;
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountBlocksBound_U32 -> ");

    {
        int i;
        for (i = 0; i < 10; ++i)
            buf[i] = 0x12345678;
    }

    /* Start 0, Count 40. All 10 match. */
    status = GenMemOpsCountBlocksBound(&count, buf, sizeof(buf), 0, 40, &blk, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    /* 10 matches * 4 bytes = 40 */
    assert(count == 40);

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
CountBlocksBound_U64(void)
{
    u64   buf[10];
    u64   blk = U64_C(0x1111222233334444);
    usize count;
    bool  status;

    printf(LOG_PREFIX_CSTR "CountBlocksBound_U64 -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    buf[2] = blk;
    buf[4] = blk;

    /* Start 16, Count 64. Range [16, 80).
     * Indices 2 through 9.
     * Matches at 2 and 4.
     */
    status = GenMemOpsCountBlocksBound(&count, buf, sizeof(buf), 16, 64, &blk, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    /* 2 matches * 8 bytes = 16 */
    assert(count == 16);

    printf("PASSED\n");
}
#endif


typedef struct kdi_TestStruct
{
    u64 a;
    u64 b;
    u64 c;
} kdi_TestStruct;


void
CountBlocksBound_Struct(void)
{
    kdi_TestStruct buf[5];
    kdi_TestStruct blk;
    usize          count;
    bool           status;

    printf(LOG_PREFIX_CSTR "CountBlocksBound_Struct -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);

    blk.a  = 1;
    blk.b  = 2;
    blk.c  = 3;

    buf[1] = blk; /* Offset 24 */
    buf[3] = blk; /* Offset 72 */

    /* Start 0, Count 120 (5 elements).
     * Matches at 1 and 3.
     */
    status = GenMemOpsCountBlocksBound(&count, buf, sizeof(buf), 0, 120, &blk, sizeof(kdi_TestStruct));

    assert(status == RESULT_SUCCESS);
    /* 2 matches * 24 bytes = 48 */
    assert(count == 48);

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    static u8 buf[8000];
    u8        blk[8];
    usize     count;
    bool      status;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    kdi_FillVal(buf, sizeof(buf), 0x00);
    kdi_FillVal(blk, sizeof(blk), 0xAA);

    /* Matches at 1000 and 4000 */
    kdi_FillVal(buf + 1000, 8, 0xAA);
    kdi_FillVal(buf + 4000, 8, 0xAA);

    /* Start 0, Count 8000. Range [0, 8000).
     * Should find both.
     */
    status = GenMemOpsCountBlocksBound(&count, buf, sizeof(buf), 0, 8000, blk, sizeof(blk));

    assert(status == RESULT_SUCCESS);
    /* 2 matches * 8 bytes = 16 */
    assert(count == 16);

    /* Start 2000, Count 6000. Range [2000, 8000).
     * Excludes 1000. Includes 4000.
     */
    status = GenMemOpsCountBlocksBound(&count, buf, sizeof(buf), 2000, 6000, blk, sizeof(blk));
    assert(status == RESULT_SUCCESS);
    /* 1 match * 8 bytes = 8 */
    assert(count == 8);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    StartAlignment();
    CountAlignmentRelaxed();
    EndValueClamping();
    CountNone();
    RangeConstraints();
    UnalignedMatchIgnored();

    CountBlocksBound_U16();
    CountBlocksBound_U32();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    CountBlocksBound_U64();
#endif
    CountBlocksBound_Struct();
    LargeBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
