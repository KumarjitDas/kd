/**
 * @file mem.c
 * @author Kumarjit Das
 * @date 2025-05-25
 * @version 0.0.3
 * @brief Main header file of the MEM library.
 */
/**
 * LICENSE: BSD 3-Clause License
 *
 * Copyright (c) 2025, Kumarjit Das.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#define KD_BUILDING_LIB 1
#include "kd/defs.h"
#include "kd/types/fw.h"
#include "kd/mem.h"


/**
 * Windows specific
 */
#if defined KD_OS_WINDOWS

  #include <windows.h>


kd_bool_t
kdMemAlloc(void* dst, kd_usize_t sz)
{
  if (!dst || sz == 0)
  {
    return KD_RESULT_FAILURE;
  }

  HANDLE heap = GetProcessHeap();
  if (!heap)
  {
    return KD_RESULT_FAILURE;
  }

  const byte* ptr = (byte*)HeapAlloc(heap, 0, sz);
  if (!ptr)
  {
    return KD_RESULT_FAILURE;
  }

  const byte** addr_ptr = dst;
  *addr_ptr             = ptr;

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemRealloc(void* dst, kd_usize_t new_sz, void* src, kd_usize_t old_sz)
{
  (void)old_sz;

  if (!dst)
  {
    return KD_RESULT_FAILURE;
  }

  const byte** addr_ptr_dst = dst;
  const byte*  ptr_dst      = *addr_ptr_dst;
  const byte** addr_ptr_src = src;
  const byte*  ptr_src      = src ? *addr_ptr_src : kd_null;

  if (!ptr_src && new_sz == 0)
  {
    return KD_RESULT_FAILURE;
  }

  HANDLE heap = GetProcessHeap();
  if (!heap)
  {
    return KD_RESULT_FAILURE;
  }

  if (!ptr_src && new_sz > 0)
  {
    ptr_dst = HeapAlloc(heap, 0, new_sz);

    if (addr_ptr_src)
    {
      *addr_ptr_src = kd_null;
    }

    *addr_ptr_dst = ptr_dst;

    return KD_RESULT_SUCCESS;
  }

  if (ptr_src && new_sz == 0)
  {
    const kd_bool_t result = HeapFree(heap, 0, (PVOID)ptr_src);
    *addr_ptr_src          = kd_null;
    *addr_ptr_dst          = kd_null;
    return result;
  }

  ptr_dst = HeapReAlloc(heap, 0, (PVOID)ptr_src, new_sz);
  if (!ptr_dst)
  {
    return KD_RESULT_FAILURE;
  }

  if (addr_ptr_src)
  {
    *addr_ptr_src = kd_null;
  }

  *addr_ptr_dst = ptr_dst;

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdFree(void* dst)
{
  if (!dst)
  {
    return KD_RESULT_FAILURE;
  }

  const byte** addr_ptr = dst;
  const byte*  ptr      = *addr_ptr;

  if (!ptr)
  {
    return KD_RESULT_SUCCESS;
  }

  HANDLE heap = GetProcessHeap();
  if (!heap)
  {
    return KD_RESULT_FAILURE;
  }

  const kd_bool_t result = HeapFree(heap, 0, (PVOID)ptr);
  *addr_ptr              = kd_null;

  return result;
}


kd_bool_t
kdMemAllocWithSizeInfo(void* dst, kd_usize_t sz)
{
  if (!dst || sz == 0)
  {
    return KD_RESULT_FAILURE;
  }

  HANDLE heap = GetProcessHeap();
  if (!heap)
  {
    return KD_RESULT_FAILURE;
  }

  const byte* ptr = (byte*)HeapAlloc(heap, 0, sz + KD_SZ_USIZE);
  if (!ptr)
  {
    return KD_RESULT_FAILURE;
  }

  *((kd_usize_t*)ptr)   = sz;
  const byte** addr_ptr = dst;
  *addr_ptr             = ptr + KD_SZ_USIZE;

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemReallocWithSizeInfo(void* dst, kd_usize_t new_sz, void* src, kd_usize_t old_sz)
{
  (void)old_sz;

  if (!dst)
  {
    return KD_RESULT_FAILURE;
  }

  const byte** addr_ptr_dst = dst;
  const byte*  ptr_dst      = *addr_ptr_dst;
  const byte** addr_ptr_src = src;
  byte*        ptr_src      = src ? (byte*)*addr_ptr_src : kd_null;

  if (!ptr_src && new_sz == 0)
  {
    return KD_RESULT_FAILURE;
  }

  HANDLE heap = GetProcessHeap();
  if (!heap)
  {
    return KD_RESULT_FAILURE;
  }

  if (!ptr_src && new_sz > 0)
  {
    ptr_dst                 = HeapAlloc(heap, 0, new_sz + KD_SZ_USIZE);
    *((kd_usize_t*)ptr_dst) = new_sz;

    if (addr_ptr_src)
    {
      *addr_ptr_src = kd_null;
    }

    *addr_ptr_dst = ptr_dst + KD_SZ_USIZE;

    return KD_RESULT_SUCCESS;
  }

  if (ptr_src)
  {
    ptr_src -= KD_SZ_USIZE;
  }

  if (ptr_src && new_sz == 0)
  {
    const kd_bool_t result = HeapFree(heap, 0, ptr_src);
    *addr_ptr_src          = kd_null;
    *addr_ptr_dst          = kd_null;
    return result;
  }

  ptr_dst = HeapReAlloc(heap, 0, ptr_src, new_sz + KD_SZ_USIZE);
  if (!ptr_dst)
  {
    return KD_RESULT_FAILURE;
  }

  *((kd_usize_t*)ptr_dst) = new_sz;

  if (addr_ptr_src)
  {
    *addr_ptr_src = kd_null;
  }

  *addr_ptr_dst = ptr_dst + KD_SZ_USIZE;

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdFreeWithSizeInfo(void* dst)
{
  if (!dst)
  {
    return KD_RESULT_FAILURE;
  }

  const byte** addr_ptr = dst;
  const byte*  ptr      = *addr_ptr;

  if (!ptr)
  {
    return KD_RESULT_FAILURE;
  }

  HANDLE heap = GetProcessHeap();
  if (!heap)
  {
    return KD_RESULT_FAILURE;
  }

  const kd_bool_t result = HeapFree(heap, 0, (PVOID)(ptr - KD_SZ_USIZE));
  *addr_ptr              = kd_null;

  return result;
}


kd_usize_t
kdMemGetAllocSize(void* src)
{
  if (src == kd_null)
  {
    return 0;
  }

  return *((kd_usize_t*)((byte*)src - KD_SZ_USIZE));
}

#else

#endif /* KD_OS_WINDOWS */
