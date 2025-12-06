/**
 * @file mem.c
 * @author Kumarjit Das
 * @version 0.0.1
 * @brief Main source file of the KD_MEM library.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 * @since 0.0.1
 */


#define BUILDING_LIB 1
#include "../include/kd/mem.h"

#if defined OS_WINDOWS && (defined OS_WIN32 || defined OS_WIN64)
    #include "./os/windows/mem.h"
#else
    #undef EXIT_SUCCESS
    #undef EXIT_FAILURE
    #undef CDECL

    #include <stdlib.h>
#endif


bool
MemAlloc(void *dst_addr, usize sz)
{
#if defined OS_WINDOWS
    return kdi_windows_MemAlloc(dst_addr, sz);
#else
    byte *ptr;

    if (!dst_addr)
    {
        return KD_RESULT_FAILURE;
    }

    *(byte **)dst_addr = null;

    if (!sz)
    {
        return KD_RESULT_FAILURE;
    }

    ptr = malloc(sz);
    if (!ptr)
    {
        return KD_RESULT_FAILURE;
    }

    *(byte **)dst_addr = ptr;

    return KD_RESULT_SUCCESS;
#endif
}


bool
MemFree(void *dst_addr, usize sz)
{
#if defined OS_WINDOWS
    return kdi_windows_MemFree(dst_addr, sz);
#else
    byte **solid_dst_adr = dst_addr;

    if (!solid_dst_adr || !*solid_dst_adr || !sz)
    {
        return KD_RESULT_FAILURE;
    }

    free(*solid_dst_adr);

    *solid_dst_adr = null;

    return KD_RESULT_SUCCESS;
#endif
}


bool
MemRealloc(void *dst_addr, usize new_sz, void *src, usize old_sz)
{
#if defined OS_WINDOWS
    return kdi_windows_MemRealloc(dst_addr, new_sz, src, old_sz);
#else
    byte **solid_dst_adr = dst_addr, **src_adr = src, *temp_ptr, *ptr = null;

    if (!solid_dst_adr || !old_sz)
    {
        return KD_RESULT_FAILURE;
    }

    temp_ptr = src_adr ? *src_adr : null;

    if (temp_ptr)
    {
        if (!new_sz)
        {
            free(temp_ptr);

            *solid_dst_adr = null;

            if (src_adr && src_adr != solid_dst_adr)
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

    *solid_dst_adr = ptr;

    if (src_adr && src_adr != solid_dst_adr)
    {
        *src_adr = null;
    }

    return KD_RESULT_SUCCESS;
#endif
}
