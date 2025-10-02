/**
 * @file kdGenMemOpsCmp.c
 * @author Kumarjit Das
 * @brief KD_GEN_MEM_OPS library kdGenMemOpsCmp function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_gen_mem_ops.h"


#define LIB_NAME_CSTR   "KD_GEN_MEM_OPS"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdGenMemOpsCmp function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
ReturnsZeroIfEqual(void)
{
    kd_byte_t ptr1[] = {1, 2, 3, 4, 5};
    kd_byte_t ptr2[] = {1, 2, 3, 4, 5};

    printf(LOG_PREFIX_CSTR "ReturnsZeroIfEqual -> ");

    assert(kdGenMemOpsCmp(ptr1, ptr2, sizeof(ptr1)) == 0);

    printf("PASSED\n");
}


void
ReturnsNegativeIfFirstLess(void)
{
    kd_byte_t ptr1[] = {1, 2, 8, 4, 5};
    kd_byte_t ptr2[] = {1, 2, 3, 4, 5};

    printf(LOG_PREFIX_CSTR "ReturnsNegativeIfFirstLess -> ");

    assert(kdGenMemOpsCmp(ptr1, ptr2, sizeof(ptr1)) == 5);

    printf("PASSED\n");
}


void
ReturnsPositiveIfFirstGreater(void)
{
    kd_byte_t ptr1[] = {1, 2, 3, 4, 5};
    kd_byte_t ptr2[] = {1, 2, 8, 4, 5};

    printf(LOG_PREFIX_CSTR "ReturnsPositiveIfFirstGreater -> ");

    assert(kdGenMemOpsCmp(ptr1, ptr2, sizeof(ptr1)) == -5);

    printf("PASSED\n");
}


void
HandlesNullPointersSafely(void)
{
    kd_byte_t ptr1[16], ptr2[16];

    printf(LOG_PREFIX_CSTR "HandlesNullPointersSafely -> ");

    assert(kdGenMemOpsCmp(kd_null, kd_null, 0) == 0);
    assert(kdGenMemOpsCmp(kd_null, kd_null, sizeof(ptr1)) == 0);
    assert(kdGenMemOpsCmp(kd_null, ptr2, 0) == -1);
    assert(kdGenMemOpsCmp(kd_null, ptr2, sizeof(ptr1)) == -1);
    assert(kdGenMemOpsCmp(ptr1, kd_null, 0) == 1);
    assert(kdGenMemOpsCmp(ptr1, kd_null, sizeof(ptr1)) == 1);
    assert(kdGenMemOpsCmp(ptr1, ptr2, 0) == 0);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");
    printf("Library Version: %s\n\n", KD_GEN_MEM_OPS_VERSION_CSTR);

    ReturnsZeroIfEqual();
    ReturnsNegativeIfFirstLess();
    ReturnsPositiveIfFirstGreater();
    HandlesNullPointersSafely();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
