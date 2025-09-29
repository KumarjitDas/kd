/**
 * @file kdMemRealloc.c
 * @author Kumarjit Das
 * @brief KD_MEM library kdMemRealloc function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "kd.h"
#include "kd_mem.h"


#define LIB_NAME_CSTR   "KD_MEM"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdMemRealloc function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    kd_u8_t *dst, *src;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    assert(kdMemRealloc(kd_null, 0, kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdMemRealloc(kd_null, 0, kd_null, 42) == KD_RESULT_FAILURE);
    assert(kdMemRealloc(kd_null, 0, &src, 0) == KD_RESULT_FAILURE);
    assert(kdMemRealloc(kd_null, 0, &src, 42) == KD_RESULT_FAILURE);
    assert(kdMemRealloc(kd_null, 69, kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdMemRealloc(kd_null, 69, kd_null, 42) == KD_RESULT_FAILURE);
    assert(kdMemRealloc(kd_null, 69, &src, 0) == KD_RESULT_FAILURE);
    assert(kdMemRealloc(kd_null, 69, &src, 42) == KD_RESULT_FAILURE);
    assert(kdMemRealloc(&dst, 0, kd_null, 0) == KD_RESULT_FAILURE);
    assert(kdMemRealloc(&dst, 0, kd_null, 42) == KD_RESULT_FAILURE);
    assert(kdMemRealloc(&dst, 0, &src, 0) == KD_RESULT_FAILURE);

    kdMemAlloc(&src, 42);
    assert(kdMemRealloc(&dst, 0, &src, 42) == KD_RESULT_SUCCESS);
    assert(dst == kd_null);
    assert(src == kd_null);

    kdMemAlloc(&src, 42);
    assert(kdMemRealloc(&dst, 69, &src, 42) == KD_RESULT_SUCCESS);
    assert(dst != kd_null);
    assert(src == kd_null);
    kdMemFree(&dst, 69);

    printf("PASSED\n");
}


void
BasicReallocationBytes(void)
{
    kd_u8_t *dst, *src;

    printf(LOG_PREFIX_CSTR "BasicReallocationBytes -> ");

    kdMemAlloc(&src, 1);
    assert(kdMemRealloc(&dst, 64, &src, 1) == KD_RESULT_SUCCESS);
    assert(src == kd_null);
    assert(dst != kd_null);
    kdMemFree(&dst, 64);

    kdMemAlloc(&src, 64);
    assert(kdMemRealloc(&dst, 128, &src, 64) == KD_RESULT_SUCCESS);
    assert(src == kd_null);
    assert(dst != kd_null);
    kdMemFree(&dst, 128);

    kdMemAlloc(&src, 128);
    assert(kdMemRealloc(&dst, 256, &src, 128) == KD_RESULT_SUCCESS);
    assert(src == kd_null);
    assert(dst != kd_null);
    kdMemFree(&dst, 256);

    kdMemAlloc(&src, 256);
    assert(kdMemRealloc(&dst, 512, &src, 256) == KD_RESULT_SUCCESS);
    assert(src == kd_null);
    assert(dst != kd_null);
    kdMemFree(&dst, 512);

    kdMemAlloc(&src, 512);
    assert(kdMemRealloc(&dst, 1024, &src, 512) == KD_RESULT_SUCCESS);
    assert(src == kd_null);
    assert(dst != kd_null);
    kdMemFree(&dst, 1024);

    printf("PASSED\n");
}


void
BasicReallocationKiloBytes(void)
{
    kd_u8_t *dst, *src;

    printf(LOG_PREFIX_CSTR "BasicReallocationKiloBytes -> ");

    kdMemAlloc(&src, 1024 * 1);
    assert(kdMemRealloc(&dst, 1024 * 64, &src, 1024 * 1) == KD_RESULT_SUCCESS);
    assert(src == kd_null);
    assert(dst != kd_null);
    kdMemFree(&dst, 1024 * 64);

    kdMemAlloc(&src, 1024 * 64);
    assert(kdMemRealloc(&dst, 1024 * 128, &src, 1024 * 64) == KD_RESULT_SUCCESS);
    assert(src == kd_null);
    assert(dst != kd_null);
    kdMemFree(&dst, 1024 * 128);

    kdMemAlloc(&src, 1024 * 128);
    assert(kdMemRealloc(&dst, 1024 * 256, &src, 1024 * 128) == KD_RESULT_SUCCESS);
    assert(src == kd_null);
    assert(dst != kd_null);
    kdMemFree(&dst, 1024 * 256);

    kdMemAlloc(&src, 1024 * 256);
    assert(kdMemRealloc(&dst, 1024 * 512, &src, 1024 * 256) == KD_RESULT_SUCCESS);
    assert(src == kd_null);
    assert(dst != kd_null);
    kdMemFree(&dst, 1024 * 512);

    kdMemAlloc(&src, 1024 * 512);
    assert(kdMemRealloc(&dst, 1024 * 1024, &src, 1024 * 512) == KD_RESULT_SUCCESS);
    assert(src == kd_null);
    assert(dst != kd_null);
    kdMemFree(&dst, 1024 * 1024);

    printf("PASSED\n");
}


void
BasicReallocationMegaBytes(void)
{
    kd_u8_t *dst, *src;

    printf(LOG_PREFIX_CSTR "BasicReallocationMegaBytes -> ");

    kdMemAlloc(&src, 1024 * 1024 * 1);
    assert(kdMemRealloc(&dst, 1024 * 1024 * 64, &src, 1024 * 1024 * 1) == KD_RESULT_SUCCESS);
    assert(src == kd_null);
    assert(dst != kd_null);
    kdMemFree(&dst, 1024 * 1024 * 64);

    kdMemAlloc(&src, 1024 * 1024 * 64);
    assert(kdMemRealloc(&dst, 1024 * 1024 * 128, &src, 1024 * 1024 * 64) == KD_RESULT_SUCCESS);
    assert(src == kd_null);
    assert(dst != kd_null);
    kdMemFree(&dst, 1024 * 1024 * 128);

    kdMemAlloc(&src, 1024 * 1024 * 128);
    assert(kdMemRealloc(&dst, 1024 * 1024 * 256, &src, 1024 * 1024 * 128) == KD_RESULT_SUCCESS);
    assert(src == kd_null);
    assert(dst != kd_null);
    kdMemFree(&dst, 1024 * 1024 * 256);

    kdMemAlloc(&src, 1024 * 1024 * 256);
    assert(kdMemRealloc(&dst, 1024 * 1024 * 512, &src, 1024 * 1024 * 256) == KD_RESULT_SUCCESS);
    assert(src == kd_null);
    assert(dst != kd_null);
    kdMemFree(&dst, 1024 * 1024 * 512);

    kdMemAlloc(&src, 1024 * 1024 * 512);
    assert(kdMemRealloc(&dst, 1024 * 1024 * 1024, &src, 1024 * 1024 * 512) == KD_RESULT_SUCCESS);
    assert(src == kd_null);
    assert(dst != kd_null);
    kdMemFree(&dst, 1024 * 1024 * 1024);

    printf("PASSED\n");
}


void
BasicMultipleSequentialReallocationsBytes(void)
{
    kd_u8_t *dst1, *dst2, *dst3, *dst4, *dst5, *dst6, *dst7, *dst8, *dst9, *dst10, *dst11;
    kd_u8_t *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9, *ptr10, *ptr11;

    printf(LOG_PREFIX_CSTR "BasicMultipleSequentialReallocationsBytes -> ");

    kdMemAlloc(&ptr1, 1);
    kdMemAlloc(&ptr2, 64);
    kdMemAlloc(&ptr3, 128);
    kdMemAlloc(&ptr4, 256);
    kdMemAlloc(&ptr5, 32);
    kdMemAlloc(&ptr6, 512);
    kdMemAlloc(&ptr7, 32);
    kdMemAlloc(&ptr8, 256);
    kdMemAlloc(&ptr9, 128);
    kdMemAlloc(&ptr10, 64);
    kdMemAlloc(&ptr11, 1);

    assert(kdMemRealloc(&dst1, 2 * 1, &ptr1, 1) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst2, 2 * 64, &ptr2, 64) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst3, 2 * 128, &ptr3, 128) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst4, 2 * 256, &ptr4, 256) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst5, 2 * 32, &ptr5, 32) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst6, 2 * 512, &ptr6, 512) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst7, 2 * 32, &ptr7, 32) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst8, 2 * 256, &ptr8, 256) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst9, 2 * 128, &ptr9, 128) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst10, 2 * 64, &ptr10, 64) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst11, 2 * 1, &ptr11, 1) == KD_RESULT_SUCCESS);

    assert(dst1 != kd_null);
    assert(dst2 != kd_null);
    assert(dst3 != kd_null);
    assert(dst4 != kd_null);
    assert(dst5 != kd_null);
    assert(dst6 != kd_null);
    assert(dst7 != kd_null);
    assert(dst8 != kd_null);
    assert(dst9 != kd_null);
    assert(dst10 != kd_null);
    assert(dst11 != kd_null);

    assert(ptr1 == kd_null);
    assert(ptr2 == kd_null);
    assert(ptr3 == kd_null);
    assert(ptr4 == kd_null);
    assert(ptr5 == kd_null);
    assert(ptr6 == kd_null);
    assert(ptr7 == kd_null);
    assert(ptr8 == kd_null);
    assert(ptr9 == kd_null);
    assert(ptr10 == kd_null);
    assert(ptr11 == kd_null);

    kdMemFree(&dst1, 2 * 1);
    kdMemFree(&dst2, 2 * 64);
    kdMemFree(&dst3, 2 * 128);
    kdMemFree(&dst4, 2 * 256);
    kdMemFree(&dst5, 2 * 32);
    kdMemFree(&dst6, 2 * 512);
    kdMemFree(&dst7, 2 * 32);
    kdMemFree(&dst8, 2 * 256);
    kdMemFree(&dst9, 2 * 128);
    kdMemFree(&dst10, 2 * 64);
    kdMemFree(&dst11, 2 * 1);

    printf("PASSED\n");
}


void
BasicMultipleSequentialReallocationsKiloBytes(void)
{
    kd_u8_t *dst1, *dst2, *dst3, *dst4, *dst5, *dst6, *dst7, *dst8, *dst9, *dst10, *dst11;
    kd_u8_t *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9, *ptr10, *ptr11;

    printf(LOG_PREFIX_CSTR "BasicMultipleSequentialReallocationsKiloBytes -> ");

    kdMemAlloc(&ptr1, 1);
    kdMemAlloc(&ptr2, 64);
    kdMemAlloc(&ptr3, 128);
    kdMemAlloc(&ptr4, 256);
    kdMemAlloc(&ptr5, 32);
    kdMemAlloc(&ptr6, 512);
    kdMemAlloc(&ptr7, 32);
    kdMemAlloc(&ptr8, 256);
    kdMemAlloc(&ptr9, 128);
    kdMemAlloc(&ptr10, 64);
    kdMemAlloc(&ptr11, 1);

    assert(kdMemRealloc(&dst1, 1024 * 1, &ptr1, 1) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst2, 1024 * 64, &ptr2, 64) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst3, 1024 * 128, &ptr3, 128) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst4, 1024 * 256, &ptr4, 256) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst5, 1024 * 32, &ptr5, 32) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst6, 1024 * 512, &ptr6, 512) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst7, 1024 * 32, &ptr7, 32) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst8, 1024 * 256, &ptr8, 256) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst9, 1024 * 128, &ptr9, 128) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst10, 1024 * 64, &ptr10, 64) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst11, 1024 * 1, &ptr11, 1) == KD_RESULT_SUCCESS);

    assert(dst1 != kd_null);
    assert(dst2 != kd_null);
    assert(dst3 != kd_null);
    assert(dst4 != kd_null);
    assert(dst5 != kd_null);
    assert(dst6 != kd_null);
    assert(dst7 != kd_null);
    assert(dst8 != kd_null);
    assert(dst9 != kd_null);
    assert(dst10 != kd_null);
    assert(dst11 != kd_null);

    assert(ptr1 == kd_null);
    assert(ptr2 == kd_null);
    assert(ptr3 == kd_null);
    assert(ptr4 == kd_null);
    assert(ptr5 == kd_null);
    assert(ptr6 == kd_null);
    assert(ptr7 == kd_null);
    assert(ptr8 == kd_null);
    assert(ptr9 == kd_null);
    assert(ptr10 == kd_null);
    assert(ptr11 == kd_null);

    kdMemFree(&dst1, 1024 * 1);
    kdMemFree(&dst2, 1024 * 64);
    kdMemFree(&dst3, 1024 * 128);
    kdMemFree(&dst4, 1024 * 256);
    kdMemFree(&dst5, 1024 * 32);
    kdMemFree(&dst6, 1024 * 512);
    kdMemFree(&dst7, 1024 * 32);
    kdMemFree(&dst8, 1024 * 256);
    kdMemFree(&dst9, 1024 * 128);
    kdMemFree(&dst10, 1024 * 64);
    kdMemFree(&dst11, 1024 * 1);

    printf("PASSED\n");
}


void
BasicMultipleSequentialReallocationsMegaBytes(void)
{
    kd_u8_t *dst1, *dst2, *dst3, *dst4, *dst5, *dst6, *dst7, *dst8, *dst9, *dst10, *dst11;
    kd_u8_t *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9, *ptr10, *ptr11;

    printf(LOG_PREFIX_CSTR "BasicMultipleSequentialReallocationsMegaBytes -> ");

    kdMemAlloc(&ptr1, 1);
    kdMemAlloc(&ptr2, 64);
    kdMemAlloc(&ptr3, 128);
    kdMemAlloc(&ptr4, 256);
    kdMemAlloc(&ptr5, 32);
    kdMemAlloc(&ptr6, 512);
    kdMemAlloc(&ptr7, 32);
    kdMemAlloc(&ptr8, 256);
    kdMemAlloc(&ptr9, 128);
    kdMemAlloc(&ptr10, 64);
    kdMemAlloc(&ptr11, 1);

    assert(kdMemRealloc(&dst1, 1024 * 1024 * 1, &ptr1, 1) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst2, 1024 * 1024 * 64, &ptr2, 64) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst3, 1024 * 1024 * 128, &ptr3, 128) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst4, 1024 * 1024 * 256, &ptr4, 256) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst5, 1024 * 1024 * 32, &ptr5, 32) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst6, 1024 * 1024 * 512, &ptr6, 512) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst7, 1024 * 1024 * 32, &ptr7, 32) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst8, 1024 * 1024 * 256, &ptr8, 256) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst9, 1024 * 1024 * 128, &ptr9, 128) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst10, 1024 * 1024 * 64, &ptr10, 64) == KD_RESULT_SUCCESS);
    assert(kdMemRealloc(&dst11, 1024 * 1024 * 1, &ptr11, 1) == KD_RESULT_SUCCESS);

    assert(dst1 != kd_null);
    assert(dst2 != kd_null);
    assert(dst3 != kd_null);
    assert(dst4 != kd_null);
    assert(dst5 != kd_null);
    assert(dst6 != kd_null);
    assert(dst7 != kd_null);
    assert(dst8 != kd_null);
    assert(dst9 != kd_null);
    assert(dst10 != kd_null);
    assert(dst11 != kd_null);

    assert(ptr1 == kd_null);
    assert(ptr2 == kd_null);
    assert(ptr3 == kd_null);
    assert(ptr4 == kd_null);
    assert(ptr5 == kd_null);
    assert(ptr6 == kd_null);
    assert(ptr7 == kd_null);
    assert(ptr8 == kd_null);
    assert(ptr9 == kd_null);
    assert(ptr10 == kd_null);
    assert(ptr11 == kd_null);

    kdMemFree(&dst1, 1024 * 1024 * 1);
    kdMemFree(&dst2, 1024 * 1024 * 64);
    kdMemFree(&dst3, 1024 * 1024 * 128);
    kdMemFree(&dst4, 1024 * 1024 * 256);
    kdMemFree(&dst5, 1024 * 1024 * 32);
    kdMemFree(&dst6, 1024 * 1024 * 512);
    kdMemFree(&dst7, 1024 * 1024 * 32);
    kdMemFree(&dst8, 1024 * 1024 * 256);
    kdMemFree(&dst9, 1024 * 1024 * 128);
    kdMemFree(&dst10, 1024 * 1024 * 64);
    kdMemFree(&dst11, 1024 * 1024 * 1);

    printf("PASSED\n");
}


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");
    printf("Library Version: %s\n\n", KD_MEM_VERSION_CSTR);

    BasicArguments();

    BasicReallocationBytes();
    BasicReallocationKiloBytes();
    BasicReallocationMegaBytes();

    BasicMultipleSequentialReallocationsBytes();
    BasicMultipleSequentialReallocationsKiloBytes();
    BasicMultipleSequentialReallocationsMegaBytes();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return KD_EXIT_SUCCESS;
}
