/**
 * @file kdGenMemOpsFindNotBlockIndicesU8.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindNotBlockIndicesU8 function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindNotBlockIndicesU8 function test"
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
    u8    idxs[16];
    usize found = 55;
    bool  status;
    /* Size in bytes */
    usize idxs_byte_sz = sizeof(idxs);

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* idxs is null -> failure */
    status = GenMemOpsFindNotBlockIndicesU8(null, idxs_byte_sz, &found, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* idxs_sz is zero -> failure */
    status = GenMemOpsFindNotBlockIndicesU8(idxs, USIZE_C(0), &found, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* found pointer is null -> failure */
    status = GenMemOpsFindNotBlockIndicesU8(idxs, idxs_byte_sz, null, buf, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindNotBlockIndicesU8(idxs, idxs_byte_sz, &found, null, USIZE_C(16), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* ptr_sz is zero -> failure */
    status = GenMemOpsFindNotBlockIndicesU8(idxs, idxs_byte_sz, &found, buf, USIZE_C(0), blk, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block is null -> failure */
    status = GenMemOpsFindNotBlockIndicesU8(idxs, idxs_byte_sz, &found, buf, USIZE_C(16), null, USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* block_sz is zero -> failure */
    status = GenMemOpsFindNotBlockIndicesU8(idxs, idxs_byte_sz, &found, buf, USIZE_C(16), blk, USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* block_sz > ptr_sz -> failure */
    status = GenMemOpsFindNotBlockIndicesU8(idxs, idxs_byte_sz, &found, buf, USIZE_C(4), blk, USIZE_C(16));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
FindNone(void)
{
    u8    buf[16];
    u8    blk[4];
    u8    idxs[16];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNone -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));
    kdi_FillVal(blk, 4, 0xAA);

    /* All match. Should find 0 bytes. */
    status = GenMemOpsFindNotBlockIndicesU8(idxs, sizeof(idxs), &found, buf, USIZE_C(16), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    printf("PASSED\n");
}


void
FindSome(void)
{
    u8    buf[32];
    u8    blk[4];
    u8    idxs[16];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindSome -> ");

    /* Init matches */
    kdi_FillVal(buf, USIZE_C(32), U8_C(0xAA));
    kdi_FillVal(blk, 4, 0xAA);

    /* Mismatches at Offset 4 (Index 1) and Offset 20 (Index 5) */
    kdi_FillVal(buf + 4, 4, 0xBB);
    kdi_FillVal(buf + 20, 4, 0xCC);

    /* Should find offsets 4 and 20.
     * Output array is u8. 2 indices found.
     * found (in bytes) = 2 indices * 1 byte/index = 2 bytes.
     */
    status = GenMemOpsFindNotBlockIndicesU8(idxs, sizeof(idxs), &found, buf, USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(found == 2);
    assert(idxs[0] == 4);
    assert(idxs[1] == 20);

    printf("PASSED\n");
}


void
OutputBufferCapacity(void)
{
    u8    buf[32];
    u8    blk[4];
    u8    idxs[2]; /* Capacity for 2 indices (2 bytes) */
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "OutputBufferCapacity -> ");

    kdi_FillVal(buf, USIZE_C(32), U8_C(0xAA));
    kdi_FillVal(blk, 4, 0xAA);

    /* 3 Mismatches: Offset 0, 4, 8 */
    kdi_FillVal(buf, 4, 0xBB);
    kdi_FillVal(buf + 4, 4, 0xBB);
    kdi_FillVal(buf + 8, 4, 0xBB);

    /* Passed size is 2 bytes. Can only hold 2 indices. */
    status = GenMemOpsFindNotBlockIndicesU8(idxs, sizeof(idxs), &found, buf, USIZE_C(32), blk, USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    /* Found size in bytes. 2 filled. */
    assert(found == 2);
    assert(idxs[0] == 0);
    assert(idxs[1] == 4);
    /* Offset 8 is ignored */

    printf("PASSED\n");
}


void
IndexRangeLimit(void)
{
    u8    buf[300];
    u8    blk[10];
    u8    idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "IndexRangeLimit -> ");

    kdi_FillVal(buf, USIZE_C(300), U8_C(0xAA));
    kdi_FillVal(blk, 10, 0xAA);

    /* Mismatch at Offset 10 (Valid u8) */
    kdi_FillVal(buf + 10, 10, 0xBB);

    /* Mismatch at Offset 250 (Valid u8) */
    kdi_FillVal(buf + 250, 10, 0xBB);

    /* Mismatch at Offset 260 (Invalid u8).
     * 260 > 255. Cannot be stored in u8.
     * Should be ignored.
     */
    kdi_FillVal(buf + 260, 10, 0xBB);

    status = GenMemOpsFindNotBlockIndicesU8(idxs, sizeof(idxs), &found, buf, USIZE_C(300), blk, USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    /* Should find exactly 2 indices. 2 indices * 1 byte = 2 bytes. */
    assert(found == 2);
    assert(idxs[0] == 10);
    assert(idxs[1] == 250);

    printf("PASSED\n");
}


void
FindNotBlockIndicesU8_U16(void)
{
    u16   buf[10];
    u16   blk = 0xAAAA;
    u8    idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndicesU8_U16 -> ");

    kdi_FillVal((u8 *)buf, sizeof(buf), 0);
    {
        int i;
        for (i = 0; i < 10; ++i)
            buf[i] = 0xAAAA;
    }

    /* Buffer size is 20 bytes.
     * Mismatches at Index 1 (Offset 2) and Index 8 (Offset 16).
     */
    buf[1] = 0xBBBB;
    buf[8] = 0xCCCC;

    status = GenMemOpsFindNotBlockIndicesU8(idxs, sizeof(idxs), &found, buf, sizeof(buf), &blk, sizeof(u16));

    assert(status == RESULT_SUCCESS);
    /* 2 indices * 1 byte = 2 bytes found */
    assert(found == 2);
    assert(idxs[0] == 2);  /* Offset 2 */
    assert(idxs[1] == 16); /* Offset 16 */

    printf("PASSED\n");
}


void
FindNotBlockIndicesU8_U32(void)
{
    u32   buf[10];
    u32   blk = 0x12345678;
    u8    idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndicesU8_U32 -> ");

    {
        int i;
        for (i = 0; i < 10; ++i)
            buf[i] = 0x12345678;
    }

    /* Mismatch at Index 2 (Offset 8) */
    buf[2] = 0x87654321;

    status = GenMemOpsFindNotBlockIndicesU8(idxs, sizeof(idxs), &found, buf, sizeof(buf), &blk, sizeof(u32));

    assert(status == RESULT_SUCCESS);
    /* 1 index * 1 byte = 1 byte found */
    assert(found == 1);
    assert(idxs[0] == 8); /* Offset 8 */

    printf("PASSED\n");
}


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
void
FindNotBlockIndicesU8_U64(void)
{
    u64   buf[10];
    u64   blk = U64_C(0x1111222233334444);
    u8    idxs[10];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndicesU8_U64 -> ");

    {
        int i;
        for (i = 0; i < 10; ++i)
            buf[i] = blk;
    }

    /* Mismatch at Index 1 (Offset 8) and Index 3 (Offset 24) */
    buf[1] = U64_C(0xFFFFFFFFFFFFFFFF);
    buf[3] = U64_C(0xEEEEEEEEEEEEEEEE);

    status = GenMemOpsFindNotBlockIndicesU8(idxs, sizeof(idxs), &found, buf, sizeof(buf), &blk, sizeof(u64));

    assert(status == RESULT_SUCCESS);
    /* 2 indices * 1 byte = 2 bytes found */
    assert(found == 2);
    assert(idxs[0] == 8);
    assert(idxs[1] == 24);

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
FindNotBlockIndicesU8_Struct(void)
{
    kdi_TestStruct buf[5];
    kdi_TestStruct blk;
    u8             idxs[10];
    usize          found;
    bool           status;
    int            i;

    printf(LOG_PREFIX_CSTR "FindNotBlockIndicesU8_Struct -> ");

    blk.a = 1;
    blk.b = 2;
    blk.c = 3;

    for (i = 0; i < 5; ++i)
        buf[i] = blk;

    /* Mismatch at Index 1 (Offset 24) */
    buf[1].a = 99;

    status   = GenMemOpsFindNotBlockIndicesU8(idxs, sizeof(idxs), &found, buf, sizeof(buf), &blk, sizeof(kdi_TestStruct));

    assert(status == RESULT_SUCCESS);
    /* 1 index * 1 byte = 1 byte found */
    assert(found == 1);
    assert(idxs[0] == 24); /* Offset 24 */

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    FindNone();
    FindSome();
    OutputBufferCapacity();
    IndexRangeLimit();

    FindNotBlockIndicesU8_U16();
    FindNotBlockIndicesU8_U32();
#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    FindNotBlockIndicesU8_U64();
#endif
    FindNotBlockIndicesU8_Struct();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
