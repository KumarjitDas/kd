/**
 * @file mem.c
 * @author Kumarjit Das
 * @version 0.0.1
 * @brief Main source file of the KD_MEM library.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 * @since 0.0.1
 */


#define KD_BUILDING_LIB 1
#include "../include/kd/mem.h"

#if defined KD_OS_WINDOWS && (defined KD_OS_WIN32 || defined KD_OS_WIN64)
    #include "./os/windows/mem.h"
#else
    #include <stdlib.h>
#endif


bool
MemAlloc(void *dst, usize sz)
{
#if defined KD_OS_WINDOWS
    return kdi_windows_MemAlloc(dst, sz);
#else
    byte *ptr;

    if (!dst)
    {
        return KD_RESULT_FAILURE;
    }

    *(byte **)dst = null;

    if (!sz)
    {
        return KD_RESULT_FAILURE;
    }

    ptr = malloc(sz);
    if (!ptr)
    {
        return KD_RESULT_FAILURE;
    }

    *(byte **)dst = ptr;

    return KD_RESULT_SUCCESS;
#endif
}


bool
MemFree(void *dst, usize sz)
{
#if defined KD_OS_WINDOWS
    return kdi_windows_MemFree(dst, sz);
#else
    byte **dst_adr = dst;

    if (!dst_adr || !*dst_adr || !sz)
    {
        return KD_RESULT_FAILURE;
    }

    free(*dst_adr);

    *dst_adr = null;

    return KD_RESULT_SUCCESS;
#endif
}


bool
MemRealloc(void *dst, usize new_sz, void *src, usize old_sz)
{
#if defined KD_OS_WINDOWS
    return kdi_windows_MemRealloc(dst, new_sz, src, old_sz);
#else
    byte **dst_adr = dst, **src_adr = src, *temp_ptr, *ptr = null;

    if (!dst_adr || !old_sz)
    {
        return KD_RESULT_FAILURE;
    }

    temp_ptr = src_adr ? *src_adr : null;

    if (temp_ptr)
    {
        if (!new_sz)
        {
            free(temp_ptr);

            *dst_adr = null;

            if (src_adr)
            {
                *src_adr = null;
            }

            return KD_RESULT_SUCCESS;
        }

        ptr = realloc(temp_ptr, new_sz);
        if (!ptr)
        {
            return KD_RESULT_FAILURE;
        }
    }
    else if (new_sz)
    {
        ptr = malloc(new_sz);
        if (!ptr)
        {
            return KD_RESULT_FAILURE;
        }
    }
    else
    {
        return KD_RESULT_FAILURE;
    }

    *dst_adr = ptr;

    if (src_adr)
    {
        *src_adr = null;
    }

    return KD_RESULT_SUCCESS;
#endif
}
