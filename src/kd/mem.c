/**
 * @file mem.c
 * @author Kumarjit Das
 * @date 2025-05-25
 * @since 0.0.3
 * @brief Main source file of the MEM library.
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
#include "kd/mem.h"
#include "_os_utils/mem.h"


kd_bool_t
kdMemAlloc(void *dst, kd_usize_t sz)
{
  kd_byte_t *ptr;

  if (!dst || sz == 0)
  {
    if (dst)
    {
      *(kd_byte_t **)dst = kd_null;
    }

    return KD_RESULT_FAILURE;
  }

  ptr = kdi_MemAlloc(sz);
  if (!ptr)
  {
    return KD_RESULT_FAILURE;
  }

  *(kd_byte_t **)dst = ptr;

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemRealloc(void *dst, kd_usize_t new_sz, void *src, kd_usize_t old_sz)
{
  kd_byte_t **dst_adr = dst, **src_adr, *temp_ptr, *ptr = kd_null;

  (void)old_sz;

  if (!dst_adr)
  {
    return KD_RESULT_FAILURE;
  }

  *dst_adr = kd_null;
  src_adr  = src;
  temp_ptr = src ? *src_adr : kd_null;

  if (temp_ptr)
  {
    *src_adr = kd_null;

    if (!new_sz)
    {
      return kdi_MemFree(temp_ptr);
    }

    ptr = kdi_MemRealloc(temp_ptr, new_sz);
    if (!ptr)
    {
      return KD_RESULT_FAILURE;
    }
  }
  else if (new_sz)
  {
    ptr = kdi_MemAlloc(new_sz);
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

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemFree(void *dst)
{
  kd_byte_t **dst_adr = dst;

  if (!dst_adr || !*dst_adr || !kdi_MemFree(*dst_adr))
  {
    return KD_RESULT_FAILURE;
  }

  *dst_adr = kd_null;

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemAllocWithSizeInfo(void *dst, kd_usize_t sz)
{
  kd_byte_t *ptr;

  if (!dst || sz == 0)
  {
    if (dst)
    {
      *(kd_byte_t **)dst = kd_null;
    }

    return KD_RESULT_FAILURE;
  }

  ptr = kdi_MemAllocWithSizeInfo(sz);
  if (!ptr)
  {
    return KD_RESULT_FAILURE;
  }

  *(kd_byte_t **)dst = ptr;

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemReallocWithSizeInfo(void *dst, kd_usize_t new_sz, void *src, kd_usize_t old_sz)
{
  kd_byte_t **dst_adr = dst, **src_adr, *temp_ptr, *ptr = kd_null;

  (void)old_sz;

  if (!dst_adr)
  {
    return KD_RESULT_FAILURE;
  }

  *dst_adr = kd_null;
  src_adr  = src;
  temp_ptr = src ? *src_adr : kd_null;

  if (temp_ptr)
  {
    *src_adr = kd_null;

    if (!new_sz)
    {
      return kdi_MemFreeWithSizeInfo(temp_ptr);
    }

    ptr = kdi_MemReallocWithSizeInfo(temp_ptr, new_sz);
    if (!ptr)
    {
      return KD_RESULT_FAILURE;
    }
  }
  else if (new_sz)
  {
    ptr = kdi_MemAllocWithSizeInfo(new_sz);
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

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemFreeWithSizeInfo(void *dst)
{
  kd_byte_t **dst_adr = dst;

  if (!dst_adr || !*dst_adr || !kdi_MemFreeWithSizeInfo(*dst_adr))
  {
    return KD_RESULT_FAILURE;
  }

  *dst_adr = kd_null;

  return KD_RESULT_SUCCESS;
}


kd_usize_t
kdMemGetAllocSize(void *src)
{
  if (!src)
  {
    return KD_RESULT_FAILURE;
  }

  return kdi_MemGetAllocSize(src);
}
