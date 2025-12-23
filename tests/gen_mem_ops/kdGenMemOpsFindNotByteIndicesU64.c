/**
 * @file kdGenMemOpsFindNotByteIndicesU64.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindNotByteIndicesU64 function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindNotByteIndicesU64 function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT

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
    u64   idxs[16];
    usize found = 55;
    bool  status;
    /* Size in bytes: 16 * 8 = 128 bytes */
    usize idxs_byte_sz = sizeof(idxs);

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* idxs is null -> failure */
    status = GenMemOpsFindNotByteIndicesU64(null, idxs_byte_sz, &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* idxs_sz is zero -> failure */
    status = GenMemOpsFindNotByteIndicesU64(idxs, USIZE_C(0), &found, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* found pointer is null -> failure */
    status = GenMemOpsFindNotByteIndicesU64(idxs, idxs_byte_sz, null, buf, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr is null -> failure */
    status = GenMemOpsFindNotByteIndicesU64(idxs, idxs_byte_sz, &found, null, USIZE_C(16), U8_C(0));
    assert(status == RESULT_FAILURE);

    /* ptr_sz is zero -> failure */
    status = GenMemOpsFindNotByteIndicesU64(idxs, idxs_byte_sz, &found, buf, USIZE_C(0), U8_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
FindNone(void)
{
    u8    buf[16];
    u64   idxs[16];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindNone -> ");

    /* All 0xAA */
    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Find NOT 0xAA. Should find 0. */
    status = GenMemOpsFindNotByteIndicesU64(idxs, sizeof(idxs), &found, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(found == 0);

    printf("PASSED\n");
}


void
FindSome(void)
{
    u8    buf[16];
    u64   idxs[16];
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "FindSome -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* Mismatches at 2, 5, 10 */
    buf[2]  = 0xBB;
    buf[5]  = 0xCC;
    buf[10] = 0xDD;

    /* Find NOT 0xAA. Should find 24. */
    status  = GenMemOpsFindNotByteIndicesU64(idxs, sizeof(idxs), &found, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(found == 24);
    assert(idxs[0] == 2);
    assert(idxs[1] == 5);
    assert(idxs[2] == 10);

    printf("PASSED\n");
}


void
BufferOverflowProtection(void)
{
    u8    buf[16];
    u64   idxs[2]; /* Only space for 2 elements (16 bytes) */
    usize found;
    bool  status;

    printf(LOG_PREFIX_CSTR "BufferOverflowProtection -> ");

    kdi_FillVal(buf, USIZE_C(16), U8_C(0xAA));

    /* 3 Mismatches */
    buf[1] = 0xBB;
    buf[2] = 0xBB;
    buf[3] = 0xBB;

    /* Output buffer size passed is 16 bytes. Capacity = 2. */
    status = GenMemOpsFindNotByteIndicesU64(idxs, sizeof(idxs), &found, buf, USIZE_C(16), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(found == 16);
    assert(idxs[0] == 1);
    assert(idxs[1] == 2);

    printf("PASSED\n");
}


void
LargeBuffer(void)
{
    /* 100KB buffer check */
    static u8 buf[102400];
    u64       idxs[10];
    usize     found;
    bool      status;

    printf(LOG_PREFIX_CSTR "LargeBuffer -> ");

    kdi_FillVal(buf, sizeof(buf), U8_C(0xAA));

    /* Mismatch at index 70000 */
    buf[70000] = 0xBB;

    status     = GenMemOpsFindNotByteIndicesU64(idxs, sizeof(idxs), &found, buf, sizeof(buf), U8_C(0xAA));

    assert(status == RESULT_SUCCESS);
    assert(found == 8);
    assert(idxs[0] == 70000);

    printf("PASSED\n");
}

#endif /* KD_ARCH_64BIT_INT */


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

#if defined KD_ARCH_64BIT_INT || defined ARCH_64BIT_INT
    BasicArguments();
    FindNone();
    FindSome();
    BufferOverflowProtection();
    LargeBuffer();
#else
    printf(LOG_PREFIX_CSTR "SKIPPED (64-bit integers not supported)\n");
#endif

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
