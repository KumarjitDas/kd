/**
 * @file kdGenMemOpsGetOffsetChecked.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsGetOffsetChecked function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../../include/kd/gen_mem_ops.h"
#include "../utils.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsGetOffsetChecked function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8    buf[16];
    void *out_ptr;
    bool  status;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    /* dst_addr is null -> failure */
    status = kdGenMemOpsGetOffsetChecked(null, buf, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base is null (and base_sz > 0) -> failure */
    out_ptr = null;
    status  = kdGenMemOpsGetOffsetChecked(&out_ptr, null, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(out_ptr == null); /* Should remain untouched on failure */

    /* base_sz is zero, but trying to access with sz > 0 -> failure */
    out_ptr = null;
    status  = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(0), USIZE_C(0), USIZE_C(1));
    assert(status == RESULT_FAILURE);

    /* base_sz is zero, offset > 0 -> failure */
    out_ptr = null;
    status  = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(0), USIZE_C(1), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ValidOffset(void)
{
    u8    buf[16];
    void *out_ptr;
    bool  status;

    printf(LOG_PREFIX_CSTR "ValidOffset -> ");

    kdi_FillSeq_u8(buf, USIZE_C(16), U8_C(0));

    /* Offset 4, Size 4 -> Valid (4+4 <= 16) */
    out_ptr = null;
    status  = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(16), USIZE_C(4), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(out_ptr == (void *)&buf[4]);

    /* Offset 0, Size 16 -> Valid (full buffer) */
    out_ptr = null;
    status  = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16));

    assert(status == RESULT_SUCCESS);
    assert(out_ptr == (void *)&buf[0]);

    /* Offset 8, Size 8 -> Valid (second half) */
    out_ptr = null;
    status  = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(16), USIZE_C(8), USIZE_C(8));

    assert(status == RESULT_SUCCESS);
    assert(out_ptr == (void *)&buf[8]);

    /* Offset 15, Size 1 -> Valid (last byte) */
    out_ptr = null;
    status  = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(16), USIZE_C(15), USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(out_ptr == (void *)&buf[15]);

    printf("PASSED\n");
}


void
OutOfBounds(void)
{
    u8    buf[16];
    void *out_ptr;
    bool  status;

    printf(LOG_PREFIX_CSTR "OutOfBounds -> ");

    /* Offset + Size > Base Size */
    /* 12 + 5 = 17 > 16 */
    out_ptr = PTR_C(USIZE_C(0xDEADBEEF)); /* sentinel */
    status  = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(16), USIZE_C(12), USIZE_C(5));

    assert(status == RESULT_FAILURE);

    /* Offset > Base Size */
    status = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(16), USIZE_C(17), USIZE_C(1));
    assert(status == RESULT_FAILURE);

    /* Offset == Base Size (with Size > 0) */
    status = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(16), USIZE_C(16), USIZE_C(1));
    assert(status == RESULT_FAILURE);

    /* Size far exceeds buffer */
    status = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(16), USIZE_C(0), USIZE_C(100));
    assert(status == RESULT_FAILURE);

    /* Offset far exceeds buffer */
    status = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(16), USIZE_C(100), USIZE_C(1));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ZeroSizeElement(void)
{
    u8    buf[16];
    void *out_ptr;
    bool  status;

    printf(LOG_PREFIX_CSTR "ZeroSizeElement -> ");

    /* Offset 16 (End of buffer), Size 0 -> Invalid (One past last element pointer) */
    out_ptr = null;
    status  = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(16), USIZE_C(16), USIZE_C(0));

    assert(status == RESULT_FAILURE);
    assert(out_ptr == null);

    /* Offset 0, Size 0 -> Invalid (start of buffer) */
    out_ptr = null;
    status  = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(16), USIZE_C(0), USIZE_C(0));

    assert(status == RESULT_FAILURE);
    assert(out_ptr == null);

    /* Offset 8, Size 0 -> Invalid (middle of buffer) */
    out_ptr = null;
    status  = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(16), USIZE_C(8), USIZE_C(0));

    assert(status == RESULT_FAILURE);
    assert(out_ptr == null);

    /* Offset 17, Size 0 -> Invalid (Beyond end) */
    status = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(16), USIZE_C(17), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
ZeroBaseSize(void)
{
    u8    buf[16];
    void *out_ptr;
    bool  status;

    printf(LOG_PREFIX_CSTR "ZeroBaseSize -> ");

    /* base_sz = 0, offset = 0, sz = 0 -> Invalid (zero base size not allowed) */
    out_ptr = null;
    status  = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(0), USIZE_C(0), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    /* base_sz = 0, offset = 0, sz > 0 -> Invalid */
    out_ptr = null;
    status  = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(0), USIZE_C(0), USIZE_C(1));
    assert(status == RESULT_FAILURE);

    /* base_sz = 0, offset > 0, sz = 0 -> Invalid */
    out_ptr = null;
    status  = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(0), USIZE_C(1), USIZE_C(0));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
IntegerOverflow(void)
{
    u8    buf[100];
    void *out_ptr;
    bool  status;

    printf(LOG_PREFIX_CSTR "IntegerOverflow -> ");

    /* Offset + Size wraps around */
    /* Offset: MAX_USIZE, Size: 1. Sum = 0 < 100. Should fail. */
    status = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(100), MAX_USIZE, USIZE_C(1));
    assert(status == RESULT_FAILURE);

    /* Offset: MAX_USIZE - 5, Size: 10. Sum wraps. Should fail. */
    status = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(100), MAX_USIZE - USIZE_C(5), USIZE_C(10));
    assert(status == RESULT_FAILURE);

    /* Offset: MAX_USIZE / 2, Size: MAX_USIZE / 2 + 50. Sum wraps. Should fail. */
    status = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(100), MAX_USIZE / USIZE_C(2), MAX_USIZE / USIZE_C(2) + USIZE_C(50));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
LargeBuffers(void)
{
    u8    buf[512];
    void *out_ptr;
    bool  status;

    printf(LOG_PREFIX_CSTR "LargeBuffers -> ");

    kdi_FillSeq_u8(buf, USIZE_C(512), U8_C(0));

    /* Large buffer, access near end */
    out_ptr = null;
    status  = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(512), USIZE_C(400), USIZE_C(100));

    assert(status == RESULT_SUCCESS);
    assert(out_ptr == (void *)&buf[400]);

    /* Large buffer, access at start */
    out_ptr = null;
    status  = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(512), USIZE_C(0), USIZE_C(512));

    assert(status == RESULT_SUCCESS);
    assert(out_ptr == (void *)&buf[0]);

    /* Large buffer, access single byte in middle */
    out_ptr = null;
    status  = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(512), USIZE_C(256), USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(out_ptr == (void *)&buf[256]);

    /* Large buffer, access beyond end */
    status = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(512), USIZE_C(500), USIZE_C(20));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
BoundaryConditions(void)
{
    u8    buf[100];
    void *out_ptr;
    bool  status;

    printf(LOG_PREFIX_CSTR "BoundaryConditions -> ");

    kdi_FillSeq_u8(buf, USIZE_C(100), U8_C(0));

    /* Offset + Size = base_sz exactly -> Valid */
    out_ptr = null;
    status  = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(100), USIZE_C(50), USIZE_C(50));

    assert(status == RESULT_SUCCESS);
    assert(out_ptr == (void *)&buf[50]);

    /* Offset + Size = base_sz + 1 -> Invalid */
    status = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(100), USIZE_C(50), USIZE_C(51));
    assert(status == RESULT_FAILURE);

    /* Offset = base_sz - 1, Size = 1 -> Valid (last byte) */
    out_ptr = null;
    status  = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(100), USIZE_C(99), USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(out_ptr == (void *)&buf[99]);

    /* Offset = base_sz - 1, Size = 2 -> Invalid */
    status = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(100), USIZE_C(99), USIZE_C(2));
    assert(status == RESULT_FAILURE);

    /* Offset = base_sz, Size = 0 -> Invalid (one-past-end) */
    out_ptr = null;
    status  = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(100), USIZE_C(100), USIZE_C(0));

    assert(status == RESULT_FAILURE);
    assert(out_ptr == null);

    /* Offset = base_sz, Size > 0 -> Invalid */
    status = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(100), USIZE_C(100), USIZE_C(1));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
PointerArithmetic(void)
{
    u8    buf[100];
    void *out_ptr;
    bool  status;
    u8   *expected;

    printf(LOG_PREFIX_CSTR "PointerArithmetic -> ");

    kdi_FillSeq_u8(buf, USIZE_C(100), U8_C(0));

    /* Verify pointer arithmetic is correct for various offsets */

    /* Offset 0 */
    out_ptr  = null;
    expected = &buf[0];
    status   = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(100), USIZE_C(0), USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(out_ptr == (void *)expected);

    /* Offset 25 */
    out_ptr  = null;
    expected = &buf[25];
    status   = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(100), USIZE_C(25), USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(out_ptr == (void *)expected);

    /* Offset 50 */
    out_ptr  = null;
    expected = &buf[50];
    status   = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(100), USIZE_C(50), USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(out_ptr == (void *)expected);

    /* Offset 90 (near end) */
    out_ptr  = null;
    expected = &buf[90];
    status   = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(100), USIZE_C(90), USIZE_C(10));

    assert(status == RESULT_SUCCESS);
    assert(out_ptr == (void *)expected);

    /* Offset 99 (last byte) */
    out_ptr  = null;
    expected = &buf[99];
    status   = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(100), USIZE_C(99), USIZE_C(1));

    assert(status == RESULT_SUCCESS);
    assert(out_ptr == (void *)expected);

    printf("PASSED\n");
}


void
CommonUseCases(void)
{
    u8    buf[256];
    void *out_ptr;
    bool  status;

    printf(LOG_PREFIX_CSTR "CommonUseCases -> ");

    kdi_FillSeq_u8(buf, USIZE_C(256), U8_C(0));

    /* Array element access: accessing element 10 of u32 array */
    /* Element size: 4 bytes, Index: 10, Offset: 40 */
    out_ptr = null;
    status  = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(256), USIZE_C(40), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(out_ptr == (void *)&buf[40]);

    /* Struct member access: accessing member at offset 16 */
    out_ptr = null;
    status  = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(256), USIZE_C(16), USIZE_C(8));

    assert(status == RESULT_SUCCESS);
    assert(out_ptr == (void *)&buf[16]);

    /* Packet parsing: reading header (20 bytes at start) */
    out_ptr = null;
    status  = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(256), USIZE_C(0), USIZE_C(20));

    assert(status == RESULT_SUCCESS);
    assert(out_ptr == (void *)&buf[0]);

    /* Packet parsing: reading payload after header */
    out_ptr = null;
    status  = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(256), USIZE_C(20), USIZE_C(100));

    assert(status == RESULT_SUCCESS);
    assert(out_ptr == (void *)&buf[20]);

    /* String operation: accessing substring at offset 50 */
    out_ptr = null;
    status  = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(256), USIZE_C(50), USIZE_C(30));

    assert(status == RESULT_SUCCESS);
    assert(out_ptr == (void *)&buf[50]);

    printf("PASSED\n");
}


void
SingleByteAccess(void)
{
    u8    buf[10];
    void *out_ptr;
    bool  status;

    printf(LOG_PREFIX_CSTR "SingleByteAccess -> ");

    kdi_FillSeq_u8(buf, USIZE_C(10), U8_C(0));

    /* Access each byte individually */
    for (usize i = USIZE_C(0); i < USIZE_C(10); ++i)
    {
        out_ptr = null;
        status  = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(10), i, USIZE_C(1));

        assert(status == RESULT_SUCCESS);
        assert(out_ptr == (void *)&buf[i]);
    }

    /* Try to access one beyond */
    status = kdGenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(10), USIZE_C(10), USIZE_C(1));
    assert(status == RESULT_FAILURE);

    printf("PASSED\n");
}


void
MultipleCallsSameBuffer(void)
{
    u8    buf[64];
    void *ptr1;
    void *ptr2;
    void *ptr3;
    bool  status;

    printf(LOG_PREFIX_CSTR "MultipleCallsSameBuffer -> ");

    kdi_FillSeq_u8(buf, USIZE_C(64), U8_C(0));

    /* Get multiple offsets from the same buffer */
    ptr1   = null;
    status = kdGenMemOpsGetOffsetChecked(&ptr1, buf, USIZE_C(64), USIZE_C(0), USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(ptr1 == (void *)&buf[0]);

    ptr2   = null;
    status = kdGenMemOpsGetOffsetChecked(&ptr2, buf, USIZE_C(64), USIZE_C(16), USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(ptr2 == (void *)&buf[16]);

    ptr3   = null;
    status = kdGenMemOpsGetOffsetChecked(&ptr3, buf, USIZE_C(64), USIZE_C(32), USIZE_C(16));
    assert(status == RESULT_SUCCESS);
    assert(ptr3 == (void *)&buf[32]);

    /* Verify pointers are correctly spaced */
    assert((u8 *)ptr2 - (u8 *)ptr1 == 16);
    assert((u8 *)ptr3 - (u8 *)ptr2 == 16);
    assert((u8 *)ptr3 - (u8 *)ptr1 == 32);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();
    ValidOffset();
    OutOfBounds();
    ZeroSizeElement();
    ZeroBaseSize();
    IntegerOverflow();
    LargeBuffers();
    BoundaryConditions();
    PointerArithmetic();
    CommonUseCases();
    SingleByteAccess();
    MultipleCallsSameBuffer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
