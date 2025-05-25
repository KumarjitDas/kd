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
#include "kd.h"

#include "types.h"
#include "mem.h"


/**
 * Windows specific
 */
#if defined KD_OS_WINDOWS
#include <windows.h>
#else
#include <stdlib.h>
#endif

#if defined TYPES_64BIT_INTEGER
#define KD__OFFSET_SIZE SZ_U64
typedef u64 kd__usize;
#else
#define KD__OFFSET_SIZE SZ_U32
typedef u32 kd__usize;
#endif  /* USE_64BIT */


#if defined KD_OS_WINDOWS

bool
#if defined USE_64BIT
kdAlloc(void* dst, u64 sz)
#else
kdAlloc(void* dst, u32 sz)
#endif  /* USE_64BIT */
{
  if (!dst || sz == 0)
  {
    return RESULT_FAILURE;
  }

  HANDLE heap = GetProcessHeap();
  if (!heap)
  {
    return RESULT_FAILURE;
  }

  const byte* ptr = (byte*) HeapAlloc(heap, 0, sz);
  if (!ptr)
  {
    return RESULT_FAILURE;
  }

  const byte** addr_ptr = dst;
  *addr_ptr             = ptr;

  return RESULT_SUCCESS;
}


bool
#if defined USE_64BIT
kdRealloc(void* dst, u64 new_sz, void* src, u64 old_sz)
#else
kdRealloc(void* dst, u32 new_sz, void* src, u32 old_sz)
#endif  /* USE_64BIT */
{
  (void) old_sz;

  if (!dst)
  {
    return RESULT_FAILURE;
  }

  const byte** addr_ptr_dst = dst;
  const byte*  ptr_dst      = *addr_ptr_dst;
  const byte** addr_ptr_src = src;
  const byte*  ptr_src      = src ? *addr_ptr_src : null;

  if (!ptr_src && new_sz == 0)
  {
    return RESULT_FAILURE;
  }

  HANDLE heap = GetProcessHeap();
  if (!heap)
  {
    return RESULT_FAILURE;
  }

  if (!ptr_src && new_sz > 0)
  {
    ptr_dst = HeapAlloc(heap, 0, new_sz);

    if (addr_ptr_src)
    {
      *addr_ptr_src = null;
    }

    *addr_ptr_dst = ptr_dst;

    return RESULT_SUCCESS;
  }

  if (ptr_src && new_sz == 0)
  {
    const bool result = HeapFree(heap, 0, (LPVOID) ptr_src);
    *addr_ptr_src     = null;
    *addr_ptr_dst     = null;
    return result;
  }

  ptr_dst = HeapReAlloc(heap, 0, (LPVOID) ptr_src, new_sz);
  if (!ptr_dst)
  {
    return RESULT_FAILURE;
  }

  if (addr_ptr_src)
  {
    *addr_ptr_src = null;
  }

  *addr_ptr_dst = ptr_dst;

  return RESULT_SUCCESS;
}


bool kdFree(void* dst)
{
  if (!dst)
  {
    return RESULT_FAILURE;
  }

  const byte** addr_ptr = dst;
  const byte*  ptr      = *addr_ptr;

  if (!ptr)
  {
    return RESULT_SUCCESS;
  }

  HANDLE heap = GetProcessHeap();
  if (!heap)
  {
    return RESULT_FAILURE;
  }

  const bool result = HeapFree(heap, 0, (LPVOID) ptr);
  *addr_ptr         = null;

  return result;
}


bool
#if defined USE_64BIT
kdAllocWithSizeInfo(void* dst, u64 sz)
#else
kdAllocWithSizeInfo(void* dst, u32 sz)
#endif  /* USE_64BIT */
{
  if (!dst || sz == 0)
  {
    return RESULT_FAILURE;
  }

  HANDLE heap = GetProcessHeap();
  if (!heap)
  {
    return RESULT_FAILURE;
  }

  const byte* ptr = (byte*) HeapAlloc(heap, 0, sz + KD__OFFSET_SIZE);
  if (!ptr)
  {
    return RESULT_FAILURE;
  }

  *((kd__usize*) ptr)   = sz;
  const byte** addr_ptr = dst;
  *addr_ptr             = ptr + KD__OFFSET_SIZE;

  return RESULT_SUCCESS;
}


bool
#if defined USE_64BIT
kdReallocWithSizeInfo(void* dst, u64 new_sz, void* src, u64 old_sz)
#else
kdReallocWithSizeInfo(void* dst, u32 new_sz, void* src, u32 old_sz)
#endif  /* USE_64BIT */
{
  (void) old_sz;

  if (!dst)
  {
    return RESULT_FAILURE;
  }

  const byte** addr_ptr_dst = dst;
  const byte*  ptr_dst      = *addr_ptr_dst;
  const byte** addr_ptr_src = src;
  byte*        ptr_src      = src ? (byte*) *addr_ptr_src : null;

  if (!ptr_src && new_sz == 0)
  {
    return RESULT_FAILURE;
  }

  HANDLE heap = GetProcessHeap();
  if (!heap)
  {
    return RESULT_FAILURE;
  }

  if (!ptr_src && new_sz > 0)
  {
    ptr_dst                 = HeapAlloc(heap, 0, new_sz + KD__OFFSET_SIZE);
    *((kd__usize*) ptr_dst) = new_sz;

    if (addr_ptr_src)
    {
      *addr_ptr_src = null;
    }

    *addr_ptr_dst = ptr_dst + KD__OFFSET_SIZE;

    return RESULT_SUCCESS;
  }

  ptr_src -= KD__OFFSET_SIZE;

  if (ptr_src && new_sz == 0)
  {
    const bool result = HeapFree(heap, 0, ptr_src);
    *addr_ptr_src     = null;
    *addr_ptr_dst     = null;
    return result;
  }

  ptr_dst = HeapReAlloc(heap, 0, ptr_src, new_sz + KD__OFFSET_SIZE);
  if (!ptr_dst)
  {
    return RESULT_FAILURE;
  }

  *((kd__usize*) ptr_dst) = new_sz;

  if (addr_ptr_src)
  {
    *addr_ptr_src = null;
  }

  *addr_ptr_dst = ptr_dst + KD__OFFSET_SIZE;

  return RESULT_SUCCESS;
}


bool kdFreeWithSizeInfo(void* dst)
{
  if (!dst)
  {
    return RESULT_FAILURE;
  }

  const byte** addr_ptr = dst;
  const byte*  ptr      = *addr_ptr;

  if (!ptr)
  {
    return RESULT_FAILURE;
  }

  HANDLE heap = GetProcessHeap();
  if (!heap)
  {
    return RESULT_FAILURE;
  }

  const bool result = HeapFree(heap, 0, (LPVOID) (ptr - KD__OFFSET_SIZE));
  *addr_ptr         = null;

  return result;
}


#if defined USE_64BIT
u64
#else
u32
#endif  /* USE_64BIT */
kdGetAllocSize(void* src)
{
  if (src == null)
  {
    return 0;
  }

  return *((kd__usize*) ((byte*) src - KD__OFFSET_SIZE));
}

#endif
