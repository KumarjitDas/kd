/**
 * @file kdMemRealloc.c
 * @author Kumarjit Das
 * @brief KD_MEM library kdMemRealloc function test.
 * @license BSD 3-Clause License
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
    assert(MemRealloc(&dst, 0, &src, 0) == RESULT_FAILURE);
    assert(MemRealloc(&dst, 69, null, 0) == RESULT_FAILURE);
    assert(MemRealloc(&dst, 69, &src, 0) == RESULT_FAILURE);

    src = null;
    kdMemAlloc(&src, 42);
    assert(src != null);
    assert(MemRealloc(&dst, 0, &src, 42) == RESULT_SUCCESS);
    assert(dst == null);
    assert(src == null);

    src = null;
    kdMemAlloc(&src, 42);
    assert(src != null);
    assert(MemRealloc(&dst, 69, &src, 42) == RESULT_SUCCESS);
    assert(dst != null);
    assert(src == null);
    kdMemFree(&dst, 69);

    printf("PASSED\n");
}

void
ReallocAllocatesWhenSrcNull(void)
{
    u8   *dst;
    void *src_void = null;
    usize old_sz   = 32;
    usize new_sz   = 64;

    printf(LOG_PREFIX_CSTR "ReallocAllocatesWhenSrcNull -> ");

    dst = null;

    assert(MemRealloc(&dst, new_sz, src_void, old_sz) == RESULT_SUCCESS);
    assert(dst != null);

    kdMemFree(&dst, new_sz);

    printf("PASSED\n");
}

void
ReallocAllocatesWhenSrcVarIsNull(void)
{
    u8   *dst;
    u8   *src    = null;
    usize old_sz = 32;
    usize new_sz = 64;

    printf(LOG_PREFIX_CSTR "ReallocAllocatesWhenSrcVarIsNull -> ");

    dst = null;

    assert(MemRealloc(&dst, new_sz, &src, old_sz) == RESULT_SUCCESS);
    assert(dst != null);
    assert(src == null);

    kdMemFree(&dst, new_sz);

    printf("PASSED\n");
}

void
BasicReallocationBytes(void)
{
    u8 *dst, *src;

    printf(LOG_PREFIX_CSTR "BasicReallocationBytes -> ");

    dst = null;

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

    dst = null;

    kdMemAlloc(&src, 1024 * 1);
    assert(MemRealloc(&dst, 1024 * 8, &src, 1024 * 1) == RESULT_SUCCESS);
    assert(src == null);
    assert(dst != null);
    kdMemFree(&dst, 1024 * 8);

    kdMemAlloc(&src, 1024 * 8);
    assert(MemRealloc(&dst, 1024 * 16, &src, 1024 * 8) == RESULT_SUCCESS);
    assert(src == null);
    assert(dst != null);
    kdMemFree(&dst, 1024 * 16);

    kdMemAlloc(&src, 1024 * 16);
    assert(MemRealloc(&dst, 1024 * 32, &src, 1024 * 16) == RESULT_SUCCESS);
    assert(src == null);
    assert(dst != null);
    kdMemFree(&dst, 1024 * 32);

    printf("PASSED\n");
}

void
BasicReallocationMegaBytes(void)
{
    u8 *dst, *src;

    printf(LOG_PREFIX_CSTR "BasicReallocationMegaBytes -> ");

    dst = null;

    kdMemAlloc(&src, 1024 * 1024 * 1);
    assert(MemRealloc(&dst, 1024 * 1024 * 4, &src, 1024 * 1024 * 1) == RESULT_SUCCESS);
    assert(src == null);
    assert(dst != null);
    kdMemFree(&dst, 1024 * 1024 * 4);

    printf("PASSED\n");
}

void
ReallocPreservesContentGrow(void)
{
    u8   *dst, *src;
    usize old_sz = 64;
    usize new_sz = 128;
    usize i;

    printf(LOG_PREFIX_CSTR "ReallocPreservesContentGrow -> ");

    dst = null;
    src = null;

    assert(MemAlloc(&src, old_sz) == RESULT_SUCCESS);
    assert(src != null);

    for (i = 0; i < old_sz; ++i)
    {
        src[i] = (u8)(i + 1U);
    }

    assert(MemRealloc(&dst, new_sz, &src, old_sz) == RESULT_SUCCESS);
    assert(dst != null);
    assert(src == null);

    for (i = 0; i < old_sz; ++i)
    {
        assert(dst[i] == (u8)(i + 1U));
    }

    kdMemFree(&dst, new_sz);

    printf("PASSED\n");
}

void
ReallocPreservesContentShrink(void)
{
    u8   *dst, *src;
    usize old_sz = 128;
    usize new_sz = 64;
    usize i;

    printf(LOG_PREFIX_CSTR "ReallocPreservesContentShrink -> ");

    dst = null;
    src = null;

    assert(MemAlloc(&src, old_sz) == RESULT_SUCCESS);
    assert(src != null);

    for (i = 0; i < old_sz; ++i)
    {
        src[i] = (u8)(i + 3U);
    }

    assert(MemRealloc(&dst, new_sz, &src, old_sz) == RESULT_SUCCESS);
    assert(dst != null);
    assert(src == null);

    for (i = 0; i < new_sz; ++i)
    {
        assert(dst[i] == (u8)(i + 3U));
    }

    kdMemFree(&dst, new_sz);

    printf("PASSED\n");
}

void
ReallocFreeViaZeroNewSize(void)
{
    u8   *dst, *src;
    usize old_sz = 64;

    printf(LOG_PREFIX_CSTR "ReallocFreeViaZeroNewSize -> ");

    dst = PU8_C(0xAA);
    src = null;

    assert(MemAlloc(&src, old_sz) == RESULT_SUCCESS);
    assert(src != null);

    assert(MemRealloc(&dst, 0, &src, old_sz) == RESULT_SUCCESS);
    assert(dst == null);
    assert(src == null);

    printf("PASSED\n");
}

void
ReallocSameDstAndSrcVariable(void)
{
    u8   *ptr;
    usize old_sz = 64;
    usize new_sz = 128;
    usize i;

    printf(LOG_PREFIX_CSTR "ReallocSameDstAndSrcVariable -> ");

    ptr = null;
    assert(MemAlloc(&ptr, old_sz) == RESULT_SUCCESS);
    assert(ptr != null);

    for (i = 0; i < old_sz; ++i)
    {
        ptr[i] = (u8)(i + 5U);
    }

    assert(MemRealloc(&ptr, new_sz, &ptr, old_sz) == RESULT_SUCCESS);
    assert(ptr != null);

    for (i = 0; i < old_sz; ++i)
    {
        assert(ptr[i] == (u8)(i + 5U));
    }

    kdMemFree(&ptr, new_sz);

    printf("PASSED\n");
}

int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("\n" TEST_NAME_CSTR " :: begin\n");

    BasicArguments();

    ReallocAllocatesWhenSrcNull();
    ReallocAllocatesWhenSrcVarIsNull();

    BasicReallocationBytes();
    BasicReallocationKiloBytes();
    BasicReallocationMegaBytes();

    ReallocPreservesContentGrow();
    ReallocPreservesContentShrink();
    ReallocFreeViaZeroNewSize();
    ReallocSameDstAndSrcVariable();

    printf("\n" TEST_NAME_CSTR " :: end\n\n");

    return EXIT_SUCCESS;
}
