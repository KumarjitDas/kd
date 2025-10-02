/**
 * @file kdGenMemOpsFindAllByteIndicesU64.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsFindAllByteIndicesU64 function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsFindAllByteIndicesU64 function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


#if defined KD_ARCH_64BIT_INT

void
FindsAllOccurrences(void)
{
    kd_byte_t ptr[] = {1, 2, 3, 2, 5, 2, 7, 3, 9, 10};
    kd_u64_t  idxs[8];

    printf(LOG_PREFIX_CSTR "FindsAllOccurrences -> ");

    assert(kdGenMemOpsFindAllByteIndicesU64(idxs, sizeof(idxs), ptr, sizeof(ptr), 2) == 3);
    assert(idxs[0] == 1);
    assert(idxs[1] == 3);
    assert(idxs[2] == 5);
    assert(kdGenMemOpsFindAllByteIndicesU64(idxs, sizeof(idxs), ptr, sizeof(ptr), 3) == 2);
    assert(idxs[0] == 2);
    assert(idxs[1] == 7);

    printf("PASSED\n");
}


void
ReturnsZeroIfNotFound(void)
{
    kd_byte_t ptr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    kd_u64_t  idxs[8];

    printf(LOG_PREFIX_CSTR "ReturnsZeroIfNotFound -> ");

    assert(kdGenMemOpsFindAllByteIndicesU64(idxs, sizeof(idxs), ptr, sizeof(ptr), 0) == 0);
    assert(kdGenMemOpsFindAllByteIndicesU64(idxs, sizeof(idxs), ptr, sizeof(ptr), 69) == 0);

    printf("PASSED\n");
}


void
HandlesZeroSize(void)
{
    kd_byte_t ptr[16];
    kd_u64_t  idxs[8];

    printf(LOG_PREFIX_CSTR "HandlesZeroSize -> ");

    assert(kdGenMemOpsFindAllByteIndicesU64(idxs, 0, ptr, 0, 69) == 0);
    assert(kdGenMemOpsFindAllByteIndicesU64(idxs, 0, ptr, sizeof(ptr), 69) == 0);
    assert(kdGenMemOpsFindAllByteIndicesU64(idxs, sizeof(idxs), ptr, 0, 69) == 0);

    printf("PASSED\n");
}


void
HandlesNullPointer(void)
{
    kd_byte_t ptr[16];
    kd_u64_t  idxs[8];

    printf(LOG_PREFIX_CSTR "HandlesNullPointer -> ");

    assert(kdGenMemOpsFindAllByteIndicesU64((kd_u64_t *)kd_null, 8, kd_null, 16, 69) == 0);
    assert(kdGenMemOpsFindAllByteIndicesU64((kd_u64_t *)kd_null, 8, ptr, 16, 69) == 0);
    assert(kdGenMemOpsFindAllByteIndicesU64(idxs, 8, kd_null, 16, 69) == 0);

    printf("PASSED\n");
}

#endif /* KD_ARCH_64BIT_INT */


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

#if defined KD_ARCH_64BIT_INT
    printf("\n" TEST_NAME_CSTR " :: begin\n");
    printf("Library Version: %s\n\n", KD_GEN_MEM_OPS_VERSION_CSTR);

    FindsAllOccurrences();
    ReturnsZeroIfNotFound();
    HandlesZeroSize();
    HandlesNullPointer();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");
#endif /* KD_ARCH_64BIT_INT */

    return KD_EXIT_SUCCESS;
}
