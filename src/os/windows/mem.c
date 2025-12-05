/**
 * @file mem.c
 * @author Kumarjit Das
 * @version 0.0.1
 * @brief Source file for Windows OS specific functionalities of KD_MEM library.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 * @since 0.0.1
 */


#define BUILDING_LIB 1
#include "./mem.h"

#undef EXIT_SUCCESS
#undef EXIT_FAILURE
#undef CDECL

#include <windows.h>


bool
kdi_windows_MemAlloc(void *dst, usize sz)
{
    HANDLE heap;
    byte  *ptr;

    if (!dst)
    {
        return KD_RESULT_FAILURE;
    }

    *(byte **)dst = null;

    if (!sz)
    {
        return KD_RESULT_FAILURE;
    }

    heap = GetProcessHeap();
    if (!heap)
    {
        return KD_RESULT_FAILURE;
    }

    ptr = HeapAlloc(heap, 0, sz);

    if (!ptr)
    {
        return KD_RESULT_FAILURE;
    }

    *(byte **)dst = ptr;

    return KD_RESULT_SUCCESS;
}


bool
kdi_windows_MemFree(void *dst, usize sz)
{
    HANDLE heap;
    byte **dst_adr = dst;

    if (!dst_adr || !*dst_adr || !sz)
    {
        return KD_RESULT_FAILURE;
    }

    heap = GetProcessHeap();
    if (!heap)
    {
        return KD_RESULT_FAILURE;
    }

    if (!HeapFree(heap, 0, *dst_adr))
    {
        return KD_RESULT_FAILURE;
    }

    *dst_adr = null;

    return KD_RESULT_SUCCESS;
}


bool
kdi_windows_MemRealloc(void *dst, usize new_sz, void *src, usize old_sz)
{
    HANDLE heap;
    byte **dst_adr = dst, **src_adr = src, *temp_ptr, *ptr = null;

    if (!dst_adr || !old_sz)
    {
        return KD_RESULT_FAILURE;
    }

    temp_ptr = src_adr ? *src_adr : null;

    heap     = GetProcessHeap();
    if (!heap)
    {
        return KD_RESULT_FAILURE;
    }

    if (temp_ptr)
    {
        if (!new_sz)
        {
            if (!HeapFree(heap, 0, temp_ptr))
            {
                return KD_RESULT_FAILURE;
            }

            *dst_adr = null;

            if (src_adr)
            {
                *src_adr = null;
            }

            return KD_RESULT_SUCCESS;
        }

        ptr = HeapReAlloc(heap, 0, temp_ptr, new_sz);

        if (!ptr)
        {
            return KD_RESULT_FAILURE;
        }
    }
    else if (new_sz)
    {
        ptr = HeapAlloc(heap, 0, new_sz);

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
}
