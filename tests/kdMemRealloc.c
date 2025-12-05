/**
 * @file kdMemRealloc.c
 * @author Kumarjit Das
 * @brief KD_MEM library kdMemRealloc function test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include <assert.h>

#include "../include/kd/mem.h"


#define LIB_NAME_CSTR   "KD_MEM"
#define TEST_NAME_CSTR  LIB_NAME_CSTR " library kdMemRealloc function test"
#define LOG_PREFIX_CSTR "[" LIB_NAME_CSTR "] "


void
BasicArguments(void)
{
    u8 *dst, *src;

    printf(LOG_PREFIX_CSTR "BasicArguments -> ");

    assert(MemRealloc(null, 0, null, 0) == RESULT_FAILURE);
    assert(MemRealloc(null, 0, null, 42) == RESULT_FAILURE);
    assert(MemRealloc(null, 0, &src, 0) == RESULT_FAILURE);
    assert(MemRealloc(null, 0, &src, 42) == RESULT_FAILURE);
    assert(MemRealloc(null, 69, null, 0) == RESULT_FAILURE);
    assert(MemRealloc(null, 69, null, 42) == RESULT_FAILURE);
    assert(MemRealloc(null, 69, &src, 0) == RESULT_FAILURE);
    assert(MemRealloc(null, 69, &src, 42) == RESULT_FAILURE);
    assert(MemRealloc(&dst, 0, null, 0) == RESULT_FAILURE);
    assert(MemRealloc(&dst, 0, null, 42) == RESULT_FAILURE);
    assert(MemRealloc(&dst, 0, &src, 0) == RESULT_FAILURE);

    kdMemAlloc(&src, 42);
    assert(MemRealloc(&dst, 0, &src, 42) == RESULT_SUCCESS);
    assert(dst == null);
    assert(src == null);

    kdMemAlloc(&src, 42);
    assert(MemRealloc(&dst, 69, &src, 42) == RESULT_SUCCESS);
    assert(dst != null);
    assert(src == null);
    kdMemFree(&dst, 69);

    printf("PASSED\n");
}


void
BasicReallocationBytes(void)
{
    u8 *dst, *src;

    printf(LOG_PREFIX_CSTR "BasicReallocationBytes -> ");

    kdMemAlloc(&src, 1);
    assert(MemRealloc(&dst, 64, &src, 1) == RESULT_SUCCESS);
    assert(src == null);
    assert(dst != null);
    kdMemFree(&dst, 64);

    kdMemAlloc(&src, 64);
    assert(MemRealloc(&dst, 128, &src, 64) == RESULT_SUCCESS);
    assert(src == null);
    assert(dst != null);
    kdMemFree(&dst, 128);

    kdMemAlloc(&src, 128);
    assert(MemRealloc(&dst, 256, &src, 128) == RESULT_SUCCESS);
    assert(src == null);
    assert(dst != null);
    kdMemFree(&dst, 256);

    kdMemAlloc(&src, 256);
    assert(MemRealloc(&dst, 512, &src, 256) == RESULT_SUCCESS);
    assert(src == null);
    assert(dst != null);
    kdMemFree(&dst, 512);

    kdMemAlloc(&src, 512);
    assert(MemRealloc(&dst, 1024, &src, 512) == RESULT_SUCCESS);
    assert(src == null);
    assert(dst != null);
    kdMemFree(&dst, 1024);

    printf("PASSED\n");
}


void
BasicReallocationKiloBytes(void)
{
    u8 *dst, *src;

    printf(LOG_PREFIX_CSTR "BasicReallocationKiloBytes -> ");

    kdMemAlloc(&src, 1024 * 1);
    assert(MemRealloc(&dst, 1024 * 64, &src, 1024 * 1) == RESULT_SUCCESS);
    assert(src == null);
    assert(dst != null);
    kdMemFree(&dst, 1024 * 64);

    kdMemAlloc(&src, 1024 * 64);
    assert(MemRealloc(&dst, 1024 * 128, &src, 1024 * 64) == RESULT_SUCCESS);
    assert(src == null);
    assert(dst != null);
    kdMemFree(&dst, 1024 * 128);

    kdMemAlloc(&src, 1024 * 128);
    assert(MemRealloc(&dst, 1024 * 256, &src, 1024 * 128) == RESULT_SUCCESS);
    assert(src == null);
    assert(dst != null);
    kdMemFree(&dst, 1024 * 256);

    kdMemAlloc(&src, 1024 * 256);
    assert(MemRealloc(&dst, 1024 * 512, &src, 1024 * 256) == RESULT_SUCCESS);
    assert(src == null);
    assert(dst != null);
    kdMemFree(&dst, 1024 * 512);

    kdMemAlloc(&src, 1024 * 512);
    assert(MemRealloc(&dst, 1024 * 1024, &src, 1024 * 512) == RESULT_SUCCESS);
    assert(src == null);
    assert(dst != null);
    kdMemFree(&dst, 1024 * 1024);

    printf("PASSED\n");
}


void
BasicReallocationMegaBytes(void)
{
    u8 *dst, *src;

    printf(LOG_PREFIX_CSTR "BasicReallocationMegaBytes -> ");

    kdMemAlloc(&src, 1024 * 1024 * 1);
    assert(MemRealloc(&dst, 1024 * 1024 * 64, &src, 1024 * 1024 * 1) == RESULT_SUCCESS);
    assert(src == null);
    assert(dst != null);
    kdMemFree(&dst, 1024 * 1024 * 64);

    kdMemAlloc(&src, 1024 * 1024 * 64);
    assert(MemRealloc(&dst, 1024 * 1024 * 128, &src, 1024 * 1024 * 64) == RESULT_SUCCESS);
    assert(src == null);
    assert(dst != null);
    kdMemFree(&dst, 1024 * 1024 * 128);

    kdMemAlloc(&src, 1024 * 1024 * 128);
    assert(MemRealloc(&dst, 1024 * 1024 * 256, &src, 1024 * 1024 * 128) == RESULT_SUCCESS);
    assert(src == null);
    assert(dst != null);
    kdMemFree(&dst, 1024 * 1024 * 256);

    kdMemAlloc(&src, 1024 * 1024 * 256);
    assert(MemRealloc(&dst, 1024 * 1024 * 512, &src, 1024 * 1024 * 256) == RESULT_SUCCESS);
    assert(src == null);
    assert(dst != null);
    kdMemFree(&dst, 1024 * 1024 * 512);

    kdMemAlloc(&src, 1024 * 1024 * 512);
    assert(MemRealloc(&dst, 1024 * 1024 * 1024, &src, 1024 * 1024 * 512) == RESULT_SUCCESS);
    assert(src == null);
    assert(dst != null);
    kdMemFree(&dst, 1024 * 1024 * 1024);

    printf("PASSED\n");
}


void
BasicMultipleSequentialReallocationsBytes(void)
{
    u8 *dst1, *dst2, *dst3, *dst4, *dst5, *dst6, *dst7, *dst8, *dst9, *dst10, *dst11;
    u8 *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9, *ptr10, *ptr11;

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

    assert(MemRealloc(&dst1, 2 * 1, &ptr1, 1) == RESULT_SUCCESS);
    assert(MemRealloc(&dst2, 2 * 64, &ptr2, 64) == RESULT_SUCCESS);
    assert(MemRealloc(&dst3, 2 * 128, &ptr3, 128) == RESULT_SUCCESS);
    assert(MemRealloc(&dst4, 2 * 256, &ptr4, 256) == RESULT_SUCCESS);
    assert(MemRealloc(&dst5, 2 * 32, &ptr5, 32) == RESULT_SUCCESS);
    assert(MemRealloc(&dst6, 2 * 512, &ptr6, 512) == RESULT_SUCCESS);
    assert(MemRealloc(&dst7, 2 * 32, &ptr7, 32) == RESULT_SUCCESS);
    assert(MemRealloc(&dst8, 2 * 256, &ptr8, 256) == RESULT_SUCCESS);
    assert(MemRealloc(&dst9, 2 * 128, &ptr9, 128) == RESULT_SUCCESS);
    assert(MemRealloc(&dst10, 2 * 64, &ptr10, 64) == RESULT_SUCCESS);
    assert(MemRealloc(&dst11, 2 * 1, &ptr11, 1) == RESULT_SUCCESS);

    assert(dst1 != null);
    assert(dst2 != null);
    assert(dst3 != null);
    assert(dst4 != null);
    assert(dst5 != null);
    assert(dst6 != null);
    assert(dst7 != null);
    assert(dst8 != null);
    assert(dst9 != null);
    assert(dst10 != null);
    assert(dst11 != null);

    assert(ptr1 == null);
    assert(ptr2 == null);
    assert(ptr3 == null);
    assert(ptr4 == null);
    assert(ptr5 == null);
    assert(ptr6 == null);
    assert(ptr7 == null);
    assert(ptr8 == null);
    assert(ptr9 == null);
    assert(ptr10 == null);
    assert(ptr11 == null);

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
    u8 *dst1, *dst2, *dst3, *dst4, *dst5, *dst6, *dst7, *dst8, *dst9, *dst10, *dst11;
    u8 *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9, *ptr10, *ptr11;

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

    assert(MemRealloc(&dst1, 1024 * 1, &ptr1, 1) == RESULT_SUCCESS);
    assert(MemRealloc(&dst2, 1024 * 64, &ptr2, 64) == RESULT_SUCCESS);
    assert(MemRealloc(&dst3, 1024 * 128, &ptr3, 128) == RESULT_SUCCESS);
    assert(MemRealloc(&dst4, 1024 * 256, &ptr4, 256) == RESULT_SUCCESS);
    assert(MemRealloc(&dst5, 1024 * 32, &ptr5, 32) == RESULT_SUCCESS);
    assert(MemRealloc(&dst6, 1024 * 512, &ptr6, 512) == RESULT_SUCCESS);
    assert(MemRealloc(&dst7, 1024 * 32, &ptr7, 32) == RESULT_SUCCESS);
    assert(MemRealloc(&dst8, 1024 * 256, &ptr8, 256) == RESULT_SUCCESS);
    assert(MemRealloc(&dst9, 1024 * 128, &ptr9, 128) == RESULT_SUCCESS);
    assert(MemRealloc(&dst10, 1024 * 64, &ptr10, 64) == RESULT_SUCCESS);
    assert(MemRealloc(&dst11, 1024 * 1, &ptr11, 1) == RESULT_SUCCESS);

    assert(dst1 != null);
    assert(dst2 != null);
    assert(dst3 != null);
    assert(dst4 != null);
    assert(dst5 != null);
    assert(dst6 != null);
    assert(dst7 != null);
    assert(dst8 != null);
    assert(dst9 != null);
    assert(dst10 != null);
    assert(dst11 != null);

    assert(ptr1 == null);
    assert(ptr2 == null);
    assert(ptr3 == null);
    assert(ptr4 == null);
    assert(ptr5 == null);
    assert(ptr6 == null);
    assert(ptr7 == null);
    assert(ptr8 == null);
    assert(ptr9 == null);
    assert(ptr10 == null);
    assert(ptr11 == null);

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
    u8 *dst1, *dst2, *dst3, *dst4, *dst5, *dst6, *dst7, *dst8, *dst9, *dst10, *dst11;
    u8 *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9, *ptr10, *ptr11;

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

    assert(MemRealloc(&dst1, 1024 * 1024 * 1, &ptr1, 1) == RESULT_SUCCESS);
    assert(MemRealloc(&dst2, 1024 * 1024 * 64, &ptr2, 64) == RESULT_SUCCESS);
    assert(MemRealloc(&dst3, 1024 * 1024 * 128, &ptr3, 128) == RESULT_SUCCESS);
    assert(MemRealloc(&dst4, 1024 * 1024 * 256, &ptr4, 256) == RESULT_SUCCESS);
    assert(MemRealloc(&dst5, 1024 * 1024 * 32, &ptr5, 32) == RESULT_SUCCESS);
    assert(MemRealloc(&dst6, 1024 * 1024 * 512, &ptr6, 512) == RESULT_SUCCESS);
    assert(MemRealloc(&dst7, 1024 * 1024 * 32, &ptr7, 32) == RESULT_SUCCESS);
    assert(MemRealloc(&dst8, 1024 * 1024 * 256, &ptr8, 256) == RESULT_SUCCESS);
    assert(MemRealloc(&dst9, 1024 * 1024 * 128, &ptr9, 128) == RESULT_SUCCESS);
    assert(MemRealloc(&dst10, 1024 * 1024 * 64, &ptr10, 64) == RESULT_SUCCESS);
    assert(MemRealloc(&dst11, 1024 * 1024 * 1, &ptr11, 1) == RESULT_SUCCESS);

    assert(dst1 != null);
    assert(dst2 != null);
    assert(dst3 != null);
    assert(dst4 != null);
    assert(dst5 != null);
    assert(dst6 != null);
    assert(dst7 != null);
    assert(dst8 != null);
    assert(dst9 != null);
    assert(dst10 != null);
    assert(dst11 != null);

    assert(ptr1 == null);
    assert(ptr2 == null);
    assert(ptr3 == null);
    assert(ptr4 == null);
    assert(ptr5 == null);
    assert(ptr6 == null);
    assert(ptr7 == null);
    assert(ptr8 == null);
    assert(ptr9 == null);
    assert(ptr10 == null);
    assert(ptr11 == null);

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

    BasicArguments();

    BasicReallocationBytes();
    BasicReallocationKiloBytes();
    BasicReallocationMegaBytes();

    BasicMultipleSequentialReallocationsBytes();
    BasicMultipleSequentialReallocationsKiloBytes();
    BasicMultipleSequentialReallocationsMegaBytes();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
