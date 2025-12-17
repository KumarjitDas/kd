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
    status = GenMemOpsGetOffsetChecked(null, buf, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);

    /* base is null (and base_sz > 0) -> failure */
    out_ptr = null;
    status  = GenMemOpsGetOffsetChecked(&out_ptr, null, USIZE_C(16), USIZE_C(0), USIZE_C(4));
    assert(status == RESULT_FAILURE);
    assert(out_ptr == null); /* Should remain untouched on failure */

    /* base_sz is zero -> failure (cannot offset into empty) unless sz=0 and offset=0?
     * Usually checked bounds strict fails on size 0 buffer if offset+sz > 0.
     * If offset=0, sz=0, it might be allowed (one-past-end logic).
     */
    out_ptr = null;
    status  = GenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(0), USIZE_C(1), USIZE_C(0));
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

    /* Offset 4, Size 4 -> Valid (4+4 <= 16) */
    out_ptr = null;
    status  = GenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(16), USIZE_C(4), USIZE_C(4));

    assert(status == RESULT_SUCCESS);
    assert(out_ptr == (void *)&buf[4]);

    /* Offset 0, Size 16 -> Valid */
    out_ptr = null;
    status  = GenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(16), USIZE_C(0), USIZE_C(16));

    assert(status == RESULT_SUCCESS);
    assert(out_ptr == (void *)&buf[0]);

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
    status  = GenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(16), USIZE_C(12), USIZE_C(5));

    assert(status == RESULT_FAILURE);
    /* Ensure out_ptr is not updated (or set to null, depending on impl, but usually untouched or safe-nulled) */
    /* Assuming safe implementation might touch it or not, checking failure is key */

    /* Offset > Base Size */
    status = GenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(16), USIZE_C(17), USIZE_C(1));
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

    /* Offset 16 (End of buffer), Size 0 -> Valid (One past last element pointer) */
    out_ptr = null;
    status  = GenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(16), USIZE_C(16), USIZE_C(0));

    assert(status == RESULT_SUCCESS);
    assert(out_ptr == (void *)&buf[16]); /* One past end */

    /* Offset 17, Size 0 -> Invalid (Beyond end) */
    status = GenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(16), USIZE_C(17), USIZE_C(0));
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
    status = GenMemOpsGetOffsetChecked(&out_ptr, buf, USIZE_C(100), MAX_USIZE, USIZE_C(1));
    assert(status == RESULT_FAILURE);

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
    IntegerOverflow();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
