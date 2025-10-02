/**
 * @file kdGenMemOpsBlocksSpn.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsBlocksSpn function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsBlocksSpn function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
ReturnsFullSizeIfAllBlocksMatch(void)
{
    kd_i16_t ptr[]  = {'6', '9', '4', '2', '0'};
    kd_i16_t keys[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

    printf(LOG_PREFIX_CSTR "ReturnsFullSizeIfAllBlocksMatch -> ");

    assert(kdGenMemOpsBlocksSpn(ptr, sizeof(ptr), keys, sizeof(*keys), sizeof(keys)) == sizeof(ptr));

    printf("PASSED\n");
}


void
ReturnsCorrectPrefixBlockSpan(void)
{
    kd_i16_t ptr[]  = {'1', '2', '9', 't', 'h'};
    kd_i16_t keys[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

    printf(LOG_PREFIX_CSTR "ReturnsCorrectPrefixBlockSpan -> ");

    assert(kdGenMemOpsBlocksSpn(ptr, sizeof(ptr), keys, sizeof(*keys), sizeof(keys)) == (3 * sizeof(*ptr)));

    printf("PASSED\n");
}


void
ReturnsZeroIfPrefixNotFound(void)
{
    kd_i16_t ptr[]  = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k'};
    kd_i16_t keys[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

    printf(LOG_PREFIX_CSTR "ReturnsZeroIfPrefixNotFound -> ");

    assert(kdGenMemOpsBlocksSpn(ptr, sizeof(ptr), keys, sizeof(*keys), sizeof(keys)) == 0);

    printf("PASSED\n");
}


void
HandlesZeroBlockSize(void)
{
    kd_i16_t ptr[16], keys[8];

    printf(LOG_PREFIX_CSTR "HandlesZeroBlockSize -> ");

    assert(kdGenMemOpsBlocksSpn(ptr, 0, keys, 0, 0) == 0);
    assert(kdGenMemOpsBlocksSpn(ptr, 0, keys, 0, sizeof(keys)) == 0);
    assert(kdGenMemOpsBlocksSpn(ptr, 0, keys, sizeof(*keys), 0) == 0);
    assert(kdGenMemOpsBlocksSpn(ptr, sizeof(ptr), keys, 0, 0) == 0);
    assert(kdGenMemOpsBlocksSpn(ptr, sizeof(ptr), keys, 0, sizeof(keys)) == 0);
    assert(kdGenMemOpsBlocksSpn(ptr, sizeof(ptr), keys, sizeof(*keys), 0) == 0);

    printf("PASSED\n");
}


void
HandlesNullPointers(void)
{
    kd_i16_t ptr[16], keys[8];

    printf(LOG_PREFIX_CSTR "HandlesNullPointers -> ");

    assert(kdGenMemOpsBlocksSpn(kd_null, sizeof(ptr), kd_null, sizeof(*keys), sizeof(keys)) == 0);
    assert(kdGenMemOpsBlocksSpn(kd_null, sizeof(ptr), keys, sizeof(*keys), sizeof(keys)) == 0);
    assert(kdGenMemOpsBlocksSpn(ptr, sizeof(ptr), kd_null, sizeof(*keys), sizeof(keys)) == 0);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");
    printf("Library Version: %s\n\n", KD_GEN_MEM_OPS_VERSION_CSTR);

    ReturnsFullSizeIfAllBlocksMatch();
    ReturnsCorrectPrefixBlockSpan();
    ReturnsZeroIfPrefixNotFound();
    HandlesZeroBlockSize();
    HandlesNullPointers();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
