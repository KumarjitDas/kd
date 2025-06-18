/**
 * @file gen_arr.c
 * @author Kumarjit Das
 * @date 2025-06-16
 * @since 0.0.11
 * @brief Main source file of the GEN_ARR library.
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
#include "_internal/common.h"
#include "_internal/gen_arr_sn.h"
#include "_internal/gen_mem_ops_sn.h"
#include "kd/gen_mem_ops.h"
#include "kd/mem_ops.h"
#include "kd/gen_arr.h"


void*
kdGenArrCreate(kd_i32_t el_sz, kd_i64_t len, kd_bool_t (*allocator)(void*, kd_usize_t))
{
  kd_usize_t size = (kd_usize_t)len * el_sz;

  if (el_sz <= 0 || len <= 0 || el_sz > len || el_sz > KD_GEN_ARR_MAX_EL_SZ || size > KD_GEN_ARR_MAX_MEM_SZ ||
      size < (kd_usize_t)len || !allocator)
  {
    return kd_null;
  }

  return kdi_GenArrCreate(el_sz, size, allocator);
}


void*
kdGenArrCreateInit(kd_i32_t el_sz, kd_i64_t len, void* val_ptr, kd_bool_t (*allocator)(void*, kd_usize_t))
{
  kd_byte_t* mem;
  kd_usize_t size;
  kd_u8_t    val_u8;
  kd_u16_t   val_u16;
  kd_u32_t   val_u32;
#if defined KD_ARCH_64BIT_INT
  kd_u64_t val_u64;
#endif

  if (!val_ptr)
  {
    return kd_null;
  }

  mem = kdGenArrCreate(el_sz, len, allocator);
  if (!mem)
  {
    return kd_null;
  }

  size = kdi_GenArrGetMemSize(mem);

  switch (el_sz)
  {
    case 1:
      val_u8 = *(kd_u8_t*)val_ptr;
      kdi_GenMemOpsSetBlocks_S8(KD_PU8_C(mem), size, val_u8);
      break;
    case 2:
      val_u16 = *(kd_u16_t*)val_ptr;
      kdi_GenMemOpsSetBlocks_S16(KD_PU16_C(mem), size, val_u16);
      break;
    case 4:
      val_u32 = *(kd_u32_t*)val_ptr;
      kdi_GenMemOpsSetBlocks_S32(KD_PU32_C(mem), size, val_u32);
      break;
#if defined KD_ARCH_64BIT_INT
    case 8:
      val_u64 = *(kd_u64_t*)val_ptr;
      kdi_GenMemOpsSetBlocks_S64(KD_PU64_C(mem), size, val_u64);
      break;
#endif
    default:
      kdi_GenMemOpsSetBlocks_Sn(mem, size, val_ptr, el_sz);
  }

  return mem;
}


void*
kdGenArrCreateFrom(kd_i32_t el_sz, kd_i64_t len, void* src, kd_i64_t src_len, kd_bool_t (*allocator)(void*, kd_usize_t))
{
  kd_byte_t *mem, *dst_ptr, *src_ptr;
  kd_usize_t dst_sz, src_sz;

  if (!src || src_len <= 0)
  {
    return kd_null;
  }

  mem = kdGenArrCreate(el_sz, len, allocator);
  if (!mem)
  {
    return kd_null;
  }

  dst_sz  = kdi_GenArrGetMemSize(mem);
  src_sz  = src_len * el_sz;
  dst_ptr = mem;
  src_ptr = KD_PBYTE_C(src);

  while (dst_sz-- && src_sz--)
  {
    *dst_ptr = *src_ptr;
    ++dst_ptr;
    ++src_ptr;
  }

  return mem;
}


void*
kdGenArrClone(void* arr, kd_bool_t (*allocator)(void*, kd_usize_t))
{
  kd_usize_t mem_sz;
  kd_byte_t *mem, *dst_ptr, *src_ptr;

  if (!arr || !allocator)
  {
    return kd_null;
  }

  mem_sz = kdi_GenArrGetMemSize(arr);

  mem = kdi_GenArrCreate(kdi_GenArrGetElemSize(arr), mem_sz, allocator);
  if (!mem)
  {
    return kd_null;
  }

  dst_ptr = mem;
  src_ptr = arr;

  while (mem_sz--)
  {
    *dst_ptr = *src_ptr;
    ++dst_ptr;
    ++src_ptr;
  }

  return mem;
}


void*
kdGenArrCloneRange(void* arr, kd_i64_t from, kd_i64_t to, kd_bool_t (*allocator)(void*, kd_usize_t))
{
  kd_byte_t *mem, *dst_ptr, *src_ptr;
  kd_u32_t   el_sz;
  kd_usize_t dst_sz, src_sz, from_idx;

  if (!arr || from < 0 || to < 0 || from > to || !allocator)
  {
    return kd_null;
  }

  el_sz  = kdi_GenArrGetElemSize(arr);
  dst_sz = (to - from + 1) * el_sz;

  mem = kdi_GenArrCreate(el_sz, dst_sz, allocator);
  if (!mem)
  {
    return kd_null;
  }

  dst_ptr  = mem;
  from_idx = from * el_sz;
  src_ptr  = KD_PBYTE_C(arr) + from_idx;
  src_sz   = kdi_GenArrGetMemSize(arr) - from_idx;

  while (dst_sz-- && src_sz--)
  {
    *dst_ptr = *src_ptr;
    ++dst_ptr;
    ++src_ptr;
  }

  return KD_PTR_C(mem);
}


kd_bool_t
kdGenArrDestroy(void* arr, kd_bool_t (*deallocator)(void*))
{
  kd_byte_t* mem;

  if (!arr || !deallocator)
  {
    return KD_RESULT_FAILURE;
  }

  mem = KD_PBYTE_C(arr) - KDI_GEN_ARR_HEAD_OFFSET;

  return deallocator(KD_PTR_C(&mem));
}


kd_i32_t
kdGenArrGetElemSize(void* arr)
{
  if (!arr)
  {
    return 0;
  }
  return kdi_GenArrGetElemSize(arr);
}


kd_i64_t
kdGenArrGetMemSize(void* arr)
{
  if (!arr)
  {
    return 0;
  }
  return KD_I64_C(kdi_GenArrGetMemSize(arr));
}


kd_i64_t
kdGenArrGetLen(void* arr)
{
  if (!arr)
  {
    return 0;
  }
  return KD_I64_C(kdi_GenArrGetMemSize(arr) / kdi_GenArrGetElemSize(arr));
}


kd_bool_t
kdGenArrIsLE(void* arr)
{
  if (!arr)
  {
    return kd_false;
  }
  return (*KD_PU32_C(KD_PBYTE_C(arr) - KDI_GEN_ARR_HEAD_OFFSET) & KDI_GEN_ARR_BE_BITMASK) ? kd_false : kd_true;
}


kd_bool_t
kdGenArrIsBE(void* arr)
{
  if (!arr)
  {
    return kd_false;
  }
  return (*KD_PU32_C(KD_PBYTE_C(arr) - KDI_GEN_ARR_HEAD_OFFSET) & KDI_GEN_ARR_BE_BITMASK) ? kd_true : kd_false;
}


void*
kdGenArrGetEnd(void* arr)
{
  if (!arr)
  {
    return kd_null;
  }
  return KD_PTR_C(KD_PBYTE_C(arr) + kdi_GenArrGetMemSize(arr) - kdi_GenArrGetElemSize(arr));
}


kd_bool_t
kdGenArrFill(void* arr, void* val_ptr)
{
  kd_usize_t mem_sz, el_sz;
  kd_u8_t    val_u8;
  kd_u16_t   val_u16;
  kd_u32_t   val_u32;
#if defined KD_ARCH_64BIT_INT
  kd_u64_t val_u64;
#endif

  if (!arr || !val_ptr)
  {
    return KD_RESULT_FAILURE;
  }

  el_sz  = kdi_GenArrGetElemSize(arr);
  mem_sz = kdi_GenArrGetMemSize(arr);

  switch (el_sz)
  {
    case 1:
      val_u8 = *(kd_u8_t*)val_ptr;
      kdi_GenMemOpsSetBlocks_S8(KD_PU8_C(arr), mem_sz, val_u8);
      break;
    case 2:
      val_u16 = *(kd_u16_t*)val_ptr;
      kdi_GenMemOpsSetBlocks_S16(KD_PU16_C(arr), mem_sz, val_u16);
      break;
    case 4:
      val_u32 = *(kd_u32_t*)val_ptr;
      kdi_GenMemOpsSetBlocks_S32(KD_PU32_C(arr), mem_sz, val_u32);
      break;
#if defined KD_ARCH_64BIT_INT
    case 8:
      val_u64 = *(kd_u64_t*)val_ptr;
      kdi_GenMemOpsSetBlocks_S64(KD_PU64_C(arr), mem_sz, val_u64);
      break;
#endif
    default:
      kdi_GenMemOpsSetBlocks_Sn(arr, mem_sz, val_ptr, el_sz);
  }

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdGenArrFillRange(void* arr, kd_i64_t from, kd_i64_t to, void* val_ptr)
{
  kd_usize_t mem_sz, el_sz, from_idx, to_idx;
  kd_byte_t* ptr;
  kd_u8_t    val_u8;
  kd_u16_t   val_u16;
  kd_u32_t   val_u32;
#if defined KD_ARCH_64BIT_INT
  kd_u64_t val_u64;
#endif

  if (!arr || from < 0 || to < 0 || from > to || !val_ptr)
  {
    return KD_RESULT_FAILURE;
  }

  el_sz  = kdi_GenArrGetElemSize(arr);
  mem_sz = kdi_GenArrGetMemSize(arr);
  to_idx = to * el_sz;
  if (to_idx >= mem_sz)
  {
    return KD_RESULT_FAILURE;
  }

  from_idx = from * el_sz;
  mem_sz   = to_idx - from_idx + el_sz;
  ptr      = KD_PBYTE_C(arr) + from_idx;

  switch (el_sz)
  {
    case 1:
      val_u8 = *(kd_u8_t*)val_ptr;
      kdi_GenMemOpsSetBlocks_S8(KD_PU8_C(ptr), mem_sz, val_u8);
      break;
    case 2:
      val_u16 = *(kd_u16_t*)val_ptr;
      kdi_GenMemOpsSetBlocks_S16(KD_PU16_C(ptr), mem_sz, val_u16);
      break;
    case 4:
      val_u32 = *(kd_u32_t*)val_ptr;
      kdi_GenMemOpsSetBlocks_S32(KD_PU32_C(ptr), mem_sz, val_u32);
      break;
#if defined KD_ARCH_64BIT_INT
    case 8:
      val_u64 = *(kd_u64_t*)val_ptr;
      kdi_GenMemOpsSetBlocks_S64(KD_PU64_C(ptr), mem_sz, val_u64);
      break;
#endif
    default:
      kdi_GenMemOpsSetBlocks_Sn(ptr, mem_sz, val_ptr, el_sz);
  }

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdGenArrSet(void* arr, kd_i64_t idx, void* val_ptr)
{
  kd_byte_t *dst_ptr, *src_ptr;
  kd_usize_t el_sz, actual_idx;

  if (!arr || idx < 0 || !val_ptr)
  {
    return KD_RESULT_FAILURE;
  }

  el_sz      = kdi_GenArrGetElemSize(arr);
  actual_idx = idx * el_sz;
  if (actual_idx >= kdi_GenArrGetMemSize(arr))
  {
    return KD_RESULT_FAILURE;
  }

  switch (el_sz)
  {
    case 1:
      *KD_PU8_C(KD_PBYTE_C(arr) + actual_idx) = *KD_PU8_C(val_ptr);
      break;
    case 2:
      *KD_PU16_C(KD_PBYTE_C(arr) + actual_idx) = *KD_PU16_C(val_ptr);
      break;
    case 4:
      *KD_PU32_C(KD_PBYTE_C(arr) + actual_idx) = *KD_PU32_C(val_ptr);
      break;
#if defined KD_ARCH_64BIT_INT
    case 8:
      *KD_PU64_C(KD_PBYTE_C(arr) + actual_idx) = *KD_PU64_C(val_ptr);
      break;
#endif
    default:
      dst_ptr = KD_PBYTE_C(arr) + actual_idx;
      src_ptr = val_ptr;

      while (el_sz--)
      {
        *dst_ptr = *src_ptr;
        ++dst_ptr;
        ++src_ptr;
      }
  }

  return KD_RESULT_SUCCESS;
}


void*
kdGenArrGet(void* arr, kd_i64_t idx)
{
  kd_usize_t el_sz, actual_idx;

  if (!arr || idx < 0)
  {
    return kd_null;
  }

  el_sz      = kdi_GenArrGetElemSize(arr);
  actual_idx = idx * el_sz;

  return actual_idx < kdi_GenArrGetMemSize(arr) ? KD_PTR_C(KD_PBYTE_C(arr) + actual_idx) : kd_null;
}


kd_bool_t
kdGenArrSwap(void* arr, kd_i64_t idx1, kd_i64_t idx2)
{
  kd_byte_t *ptr1, *ptr2;
  kd_usize_t el_sz, mem_sz, actual_idx1, actual_idx2;
  kd_u8_t    temp_u8;
  kd_u16_t   temp_u16;
  kd_u32_t   temp_u32;
#if defined KD_ARCH_64BIT_INT
  kd_u64_t temp_u64;
#endif

  if (!arr || idx1 < 0 || idx2 < 0)
  {
    return KD_RESULT_FAILURE;
  }

  el_sz       = kdi_GenArrGetElemSize(arr);
  mem_sz      = kdi_GenArrGetMemSize(arr);
  actual_idx1 = idx1 * el_sz;
  actual_idx2 = idx2 * el_sz;

  if (actual_idx1 >= mem_sz || actual_idx2 >= mem_sz)
  {
    return KD_RESULT_FAILURE;
  }

  ptr1 = KD_PBYTE_C(arr) + actual_idx1;
  ptr2 = KD_PBYTE_C(arr) + actual_idx2;

  switch (el_sz)
  {
    case 1:
      temp_u8         = *KD_PU8_C(ptr1);
      *KD_PU8_C(ptr1) = *KD_PU8_C(ptr2);
      *KD_PU8_C(ptr2) = temp_u8;
      break;
    case 2:
      temp_u16         = *KD_PU16_C(ptr1);
      *KD_PU16_C(ptr1) = *KD_PU16_C(ptr2);
      *KD_PU16_C(ptr2) = temp_u16;
      break;
    case 4:
      temp_u32         = *KD_PU32_C(ptr1);
      *KD_PU32_C(ptr1) = *KD_PU32_C(ptr2);
      *KD_PU32_C(ptr2) = temp_u32;
      break;
#if defined KD_ARCH_64BIT_INT
    case 8:
      temp_u64         = *KD_PU64_C(ptr1);
      *KD_PU64_C(ptr1) = *KD_PU64_C(ptr2);
      *KD_PU64_C(ptr2) = temp_u64;
      break;
#endif
    default:
      while (el_sz--)
      {
        temp_u8 = *ptr1;
        *ptr1   = *ptr2;
        *ptr2   = temp_u8;
        ++ptr1;
        ++ptr2;
      }
  }

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdGenArrEquals(void* arr1, void* arr2)
{
  kd_byte_t *ptr1, *ptr2;
  kd_usize_t mem_sz;

  if (!arr1 || !arr2)
  {
    return kd_false;
  }

  mem_sz = kdi_GenArrGetMemSize(arr1);

  if (kdi_GenArrGetElemSize(arr1) != kdi_GenArrGetElemSize(arr2) || mem_sz != kdi_GenArrGetMemSize(arr2))
  {
    return kd_false;
  }

  ptr1 = arr1;
  ptr2 = arr2;

  while (mem_sz--)
  {
    if (*ptr1 != *ptr2)
    {
      return kd_false;
    }
    ++ptr1;
    ++ptr2;
  }

  return kd_true;
}


kd_i64_t
kdGenArrGetCount(void* arr, void* val_ptr)
{
  kd_byte_t *ptr, *block;
  kd_usize_t el_sz, temp_el_sz, mem_sz, match_cnt;
  kd_i64_t   count = 0;

  if (!arr || !val_ptr)
  {
    return 0;
  }

  el_sz  = kdi_GenArrGetElemSize(arr);
  mem_sz = kdi_GenArrGetMemSize(arr);

  ptr = arr;

  while (mem_sz)
  {
    switch (el_sz)
    {
      case 1:
        count += *KD_PU8_C(ptr) == *KD_PU8_C(val_ptr);
        ptr += el_sz;
        mem_sz -= el_sz;
        break;
      case 2:
        count += *KD_PU16_C(ptr) == *KD_PU16_C(val_ptr);
        ptr += el_sz;
        mem_sz -= el_sz;
        break;
      case 4:
        count += *KD_PU32_C(ptr) == *KD_PU32_C(val_ptr);
        ptr += el_sz;
        mem_sz -= el_sz;
        break;
#if defined KD_ARCH_64BIT_INT
      case 8:
        count += *KD_PU64_C(ptr) == *KD_PU64_C(val_ptr);
        ptr += el_sz;
        mem_sz -= el_sz;
        break;
#endif
      default:
        match_cnt  = 0;
        temp_el_sz = el_sz;
        block      = val_ptr;

        while (temp_el_sz--)
        {
          match_cnt += *ptr == *block;
          ++ptr;
          ++block;
          --mem_sz;
        }

        count += match_cnt == el_sz;
    }
  }

  return count;
}


kd_i64_t
kdGenArrGetCountRange(void* arr, kd_i64_t from, kd_i64_t to, void* val_ptr)
{
  kd_byte_t *ptr, *block;
  kd_usize_t el_sz, temp_el_sz, mem_sz, match_cnt, from_idx, to_idx;
  kd_i64_t   count = 0;

  if (!arr || from < 0 || to < 0 || from > to || !val_ptr)
  {
    return 0;
  }

  el_sz  = kdi_GenArrGetElemSize(arr);
  mem_sz = kdi_GenArrGetMemSize(arr);
  to_idx = to * el_sz;
  if (to_idx >= mem_sz)
  {
    return 0;
  }

  from_idx = from * el_sz;
  mem_sz   = to_idx - from_idx + el_sz;
  ptr      = KD_PBYTE_C(arr) + from_idx;

  while (mem_sz)
  {
    switch (el_sz)
    {
      case 1:
        count += *KD_PU8_C(ptr) == *KD_PU8_C(val_ptr);
        ptr += el_sz;
        mem_sz -= el_sz;
        break;
      case 2:
        count += *KD_PU16_C(ptr) == *KD_PU16_C(val_ptr);
        ptr += el_sz;
        mem_sz -= el_sz;
        break;
      case 4:
        count += *KD_PU32_C(ptr) == *KD_PU32_C(val_ptr);
        ptr += el_sz;
        mem_sz -= el_sz;
        break;
#if defined KD_ARCH_64BIT_INT
      case 8:
        count += *KD_PU64_C(ptr) == *KD_PU64_C(val_ptr);
        ptr += el_sz;
        mem_sz -= el_sz;
        break;
#endif
      default:
        match_cnt  = 0;
        temp_el_sz = el_sz;
        block      = val_ptr;

        while (temp_el_sz--)
        {
          match_cnt += *ptr == *block;
          ++ptr;
          ++block;
          --mem_sz;
        }

        count += match_cnt == el_sz;
    }
  }

  return count;
}


kd_bool_t
kdGenArrReverse(void* arr)
{
  kd_usize_t el_sz, mem_sz;

  if (!arr)
  {
    return KD_RESULT_FAILURE;
  }

  el_sz  = kdi_GenArrGetElemSize(arr);
  mem_sz = kdi_GenArrGetMemSize(arr);

  switch (el_sz)
  {
    case 1:
      kdi_GenMemOpsReverseBlocks_S8(arr, mem_sz);
      break;
    case 2:
      kdi_GenMemOpsReverseBlocks_S16(arr, mem_sz);
      break;
    case 4:
      kdi_GenMemOpsReverseBlocks_S32(arr, mem_sz);
      break;
#if defined KD_ARCH_64BIT_INT
    case 8:
      kdi_GenMemOpsReverseBlocks_S64(arr, mem_sz);
      break;
#endif
    default:
      kdi_GenMemOpsReverseBlocks_Sn(arr, mem_sz, el_sz);
  }

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdGenArrGetReversed(void* dst_arr, void* src_arr)
{
  kd_byte_t *dst_ptr, *src_ptr;
  kd_usize_t el_sz, dst_mem_sz, src_mem_sz;

  if (!dst_arr || !src_arr)
  {
    return KD_RESULT_FAILURE;
  }

  el_sz = kdi_GenArrGetElemSize(dst_arr);
  if (el_sz != kdi_GenArrGetElemSize(src_arr))
  {
    return KD_RESULT_FAILURE;
  }

  dst_mem_sz = kdi_GenArrGetMemSize(dst_arr);
  src_mem_sz = kdi_GenArrGetMemSize(src_arr);

  dst_ptr = dst_arr;
  src_ptr = src_arr;

  if (dst_mem_sz < src_mem_sz)
  {
    src_ptr += src_mem_sz - dst_mem_sz;
    src_mem_sz = dst_mem_sz;
  }
  else
  {
    dst_mem_sz = src_mem_sz;
  }

  while (src_mem_sz--)
  {
    *dst_ptr = *src_ptr;
    ++dst_ptr;
    ++src_ptr;
  }

  switch (el_sz)
  {
    case 1:
      kdi_GenMemOpsReverseBlocks_S8(KD_PU8_C(dst_arr), dst_mem_sz);
      break;
    case 2:
      kdi_GenMemOpsReverseBlocks_S16(KD_PU16_C(dst_arr), dst_mem_sz);
      break;
    case 4:
      kdi_GenMemOpsReverseBlocks_S32(KD_PU32_C(dst_arr), dst_mem_sz);
      break;
#if defined KD_ARCH_64BIT_INT
    case 8:
      kdi_GenMemOpsReverseBlocks_S64(KD_PU64_C(dst_arr), dst_mem_sz);
      break;
#endif
    default:
      kdi_GenMemOpsReverseBlocks_Sn(KD_PTR_C(dst_arr), dst_mem_sz, el_sz);
  }

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdGenArrGetReversedTo(void* dst, kd_i64_t len, void* src_arr)
{
  kd_usize_t el_sz, dst_sz, src_sz, mem_sz;
  kd_byte_t *dst_ptr, *src_ptr;

  if (!dst || len <= 0 || !src_arr)
  {
    return KD_RESULT_FAILURE;
  }

  el_sz  = kdi_GenArrGetElemSize(src_arr);
  src_sz = kdi_GenArrGetMemSize(src_arr);
  dst_sz = len * el_sz;
  mem_sz = dst_sz < src_sz ? dst_sz : src_sz;

  dst_ptr = dst;
  src_ptr = src_arr;

  while (dst_sz-- && src_sz--)
  {
    *dst_ptr = *src_ptr;
    ++dst_ptr;
    ++src_ptr;
  }

  switch (el_sz)
  {
    case 1:
      kdi_GenMemOpsReverseBlocks_S8(dst, mem_sz);
      break;
    case 2:
      kdi_GenMemOpsReverseBlocks_S16(dst, mem_sz);
      break;
    case 4:
      kdi_GenMemOpsReverseBlocks_S32(dst, mem_sz);
      break;
#if defined KD_ARCH_64BIT_INT
    case 8:
      kdi_GenMemOpsReverseBlocks_S64(dst, mem_sz);
      break;
#endif
    default:
      kdi_GenMemOpsReverseBlocks_Sn(dst, mem_sz, el_sz);
  }

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdGenArrGetReversedFrom(void* dst_arr, void* src, kd_i64_t len)
{
  kd_usize_t el_sz, dst_sz, src_sz;
  kd_byte_t *dst_ptr, *src_ptr;

  if (!dst_arr || !src || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  el_sz  = kdi_GenArrGetElemSize(dst_arr);
  dst_sz = kdi_GenArrGetMemSize(dst_arr);
  src_sz = len * el_sz;

  dst_ptr = dst_arr;
  src_ptr = src;

  if (dst_sz < src_sz)
  {
    src_ptr += src_sz - dst_sz;
    src_sz = dst_sz;
  }
  else
  {
    dst_sz = src_sz;
  }

  while (src_sz--)
  {
    *dst_ptr = *src_ptr;
    ++dst_ptr;
    ++src_ptr;
  }

  switch (el_sz)
  {
    case 1:
      kdi_GenMemOpsReverseBlocks_S8(KD_PU8_C(dst_arr), dst_sz);
      break;
    case 2:
      kdi_GenMemOpsReverseBlocks_S16(KD_PU16_C(dst_arr), dst_sz);
      break;
    case 4:
      kdi_GenMemOpsReverseBlocks_S32(KD_PU32_C(dst_arr), dst_sz);
      break;
#if defined KD_ARCH_64BIT_INT
    case 8:
      kdi_GenMemOpsReverseBlocks_S64(KD_PU64_C(dst_arr), dst_sz);
      break;
#endif
    default:
      kdi_GenMemOpsReverseBlocks_Sn(KD_PTR_C(dst_arr), dst_sz, el_sz);
  }

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdGenArrReverseRange(void* arr, kd_i64_t from, kd_i64_t to)
{
  kd_usize_t el_sz, mem_sz, from_idx, to_idx;
  kd_byte_t* ptr;

  if (!arr || from < 0 || to < 0 || from > to)
  {
    return KD_RESULT_FAILURE;
  }

  el_sz  = kdi_GenArrGetElemSize(arr);
  mem_sz = kdi_GenArrGetMemSize(arr);
  to_idx = to * el_sz;
  if (to_idx > mem_sz)
  {
    return KD_RESULT_FAILURE;
  }

  from_idx = from * el_sz;
  mem_sz   = to_idx - from_idx + el_sz;
  ptr      = KD_PBYTE_C(arr) + from_idx;

  switch (el_sz)
  {
    case 1:
      kdi_GenMemOpsReverseBlocks_S8(KD_PU8_C(ptr), mem_sz);
      break;
    case 2:
      kdi_GenMemOpsReverseBlocks_S16(KD_PU16_C(ptr), mem_sz);
      break;
    case 4:
      kdi_GenMemOpsReverseBlocks_S32(KD_PU32_C(ptr), mem_sz);
      break;
#if defined KD_ARCH_64BIT_INT
    case 8:
      kdi_GenMemOpsReverseBlocks_S64(KD_PU64_C(ptr), mem_sz);
      break;
#endif
    default:
      kdi_GenMemOpsReverseBlocks_Sn(KD_PTR_C(ptr), mem_sz, el_sz);
  }

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdGenArrGetReversedRange(void* dst_arr, kd_i64_t dst_from, void* src_arr, kd_i64_t src_from, kd_i64_t src_to)
{
  kd_byte_t *dst_ptr, *src_ptr, *temp_dst_ptr;
  kd_usize_t el_sz, mem_sz, dst_mem_sz, src_mem_sz, dst_from_idx, src_from_idx, src_to_idx;

  if (!dst_arr || dst_from < 0 || !src_arr || src_from < 0 || src_to < 0 || dst_from > src_to)
  {
    return KD_RESULT_FAILURE;
  }

  el_sz = kdi_GenArrGetElemSize(dst_arr);
  if (el_sz != kdi_GenArrGetElemSize(src_arr))
  {
    return KD_RESULT_FAILURE;
  }

  src_mem_sz = kdi_GenArrGetMemSize(src_arr);
  src_to_idx = src_to * el_sz;
  if (src_to_idx >= src_mem_sz)
  {
    return KD_RESULT_FAILURE;
  }

  dst_mem_sz   = kdi_GenArrGetMemSize(dst_arr);
  dst_from_idx = dst_from * el_sz;
  if (dst_from_idx >= dst_mem_sz)
  {
    return KD_RESULT_FAILURE;
  }

  src_from_idx = src_from * el_sz;
  src_mem_sz   = src_to_idx - src_from_idx + el_sz;
  dst_mem_sz   = dst_mem_sz - dst_from_idx;
  mem_sz       = dst_mem_sz < src_mem_sz ? dst_mem_sz : src_mem_sz;

  dst_ptr      = KD_PBYTE_C(dst_arr) + dst_from_idx;
  src_ptr      = KD_PBYTE_C(src_arr) + src_from_idx;
  temp_dst_ptr = dst_ptr;

  while (dst_mem_sz-- && src_mem_sz--)
  {
    *dst_ptr = *src_ptr;
    ++dst_ptr;
    ++src_ptr;
  }

  switch (el_sz)
  {
    case 1:
      kdi_GenMemOpsReverseBlocks_S8(KD_PU8_C(temp_dst_ptr), mem_sz);
      break;
    case 2:
      kdi_GenMemOpsReverseBlocks_S16(KD_PU16_C(temp_dst_ptr), mem_sz);
      break;
    case 4:
      kdi_GenMemOpsReverseBlocks_S32(KD_PU32_C(temp_dst_ptr), mem_sz);
      break;
#if defined KD_ARCH_64BIT_INT
    case 8:
      kdi_GenMemOpsReverseBlocks_S64(KD_PU64_C(temp_dst_ptr), mem_sz);
      break;
#endif
    default:
      kdi_GenMemOpsReverseBlocks_Sn(KD_PTR_C(temp_dst_ptr), mem_sz, el_sz);
  }

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdGenArrGetReversedRangeFrom(void* dst_arr, kd_i64_t dst_from, void* src, kd_i64_t src_from, kd_i64_t src_to)
{
  kd_usize_t el_sz, dst_sz, src_sz, dst_from_idx, src_from_idx;
  kd_byte_t *dst_ptr, *src_ptr, *temp_dst_ptr;

  if (!dst_arr || dst_from < 0 || !src || src_from < 0 || src_to < 0 || src_from > src_to)
  {
    return KD_RESULT_FAILURE;
  }

  el_sz        = kdi_GenArrGetElemSize(dst_arr);
  dst_sz       = kdi_GenArrGetMemSize(dst_arr);
  dst_from_idx = dst_from * el_sz;
  if (dst_from_idx >= dst_sz)
  {
    return KD_RESULT_FAILURE;
  }

  dst_sz -= dst_from_idx;

  src_from_idx = src_from * el_sz;
  src_sz       = src_to * el_sz - src_from_idx + el_sz;

  dst_ptr      = KD_PBYTE_C(dst_arr) + dst_from_idx;
  src_ptr      = KD_PBYTE_C(src) + src_from_idx;
  temp_dst_ptr = dst_ptr;

  if (dst_sz < src_sz)
  {
    src_ptr += src_sz - dst_sz;
    src_sz = dst_sz;
  }
  else
  {
    dst_sz = src_sz;
  }

  while (src_sz--)
  {
    *dst_ptr = *src_ptr;
    ++dst_ptr;
    ++src_ptr;
  }

  switch (el_sz)
  {
    case 1:
      kdi_GenMemOpsReverseBlocks_S8(KD_PU8_C(temp_dst_ptr), dst_sz);
      break;
    case 2:
      kdi_GenMemOpsReverseBlocks_S16(KD_PU16_C(temp_dst_ptr), dst_sz);
      break;
    case 4:
      kdi_GenMemOpsReverseBlocks_S32(KD_PU32_C(temp_dst_ptr), dst_sz);
      break;
#if defined KD_ARCH_64BIT_INT
    case 8:
      kdi_GenMemOpsReverseBlocks_S64(KD_PU64_C(temp_dst_ptr), dst_sz);
      break;
#endif
    default:
      kdi_GenMemOpsReverseBlocks_Sn(KD_PTR_C(temp_dst_ptr), dst_sz, el_sz);
  }

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdGenArrGetReversedRangeTo(void* dst, kd_i64_t len, void* src_arr, kd_i64_t from, kd_i64_t to)
{
  kd_usize_t el_sz, dst_sz, src_sz, mem_sz, from_idx, to_idx;
  kd_byte_t *dst_ptr, *src_ptr;

  if (!dst || len <= 0 || !src_arr || from < 0 || to < 0 || from > to)
  {
    return KD_RESULT_FAILURE;
  }

  el_sz  = kdi_GenArrGetElemSize(src_arr);
  src_sz = kdi_GenArrGetMemSize(src_arr);
  to_idx = to * el_sz;
  if (to_idx >= src_sz)
  {
    return KD_RESULT_FAILURE;
  }

  from_idx = from * el_sz;
  src_sz   = to_idx - from_idx + el_sz;
  dst_sz   = len * el_sz;
  mem_sz   = dst_sz < src_sz ? dst_sz : src_sz;

  dst_ptr = dst;
  src_ptr = KD_PBYTE_C(src_arr) + from_idx;

  while (dst_sz-- && src_sz--)
  {
    *dst_ptr = *src_ptr;
    ++dst_ptr;
    ++src_ptr;
  }

  switch (el_sz)
  {
    case 1:
      kdi_GenMemOpsReverseBlocks_S8(dst, mem_sz);
      break;
    case 2:
      kdi_GenMemOpsReverseBlocks_S16(dst, mem_sz);
      break;
    case 4:
      kdi_GenMemOpsReverseBlocks_S32(dst, mem_sz);
      break;
#if defined KD_ARCH_64BIT_INT
    case 8:
      kdi_GenMemOpsReverseBlocks_S64(dst, mem_sz);
      break;
#endif
    default:
      kdi_GenMemOpsReverseBlocks_Sn(dst, mem_sz, el_sz);
  }

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdGenArrCpy(void* dst_arr, void* src_arr)
{
  kd_usize_t dst_sz, src_sz;

  if (!dst_arr || !src_arr || kdi_GenArrGetElemSize(dst_arr) != kdi_GenArrGetElemSize(src_arr))
  {
    return KD_RESULT_FAILURE;
  }

  dst_sz = kdi_GenArrGetMemSize(dst_arr);
  src_sz = kdi_GenArrGetMemSize(src_arr);

  kdi_GenMemOpsMove(dst_arr, src_arr, dst_sz < src_sz ? dst_sz : src_sz);

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdGenArrCpyFrom(void* dst_arr, void* src, kd_i64_t len)
{
  kd_usize_t dst_sz, src_sz;

  if (!dst_arr || !src || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  dst_sz = kdi_GenArrGetMemSize(dst_arr);
  src_sz = len * kdi_GenArrGetElemSize(dst_arr);

  kdi_GenMemOpsMove(dst_arr, src, dst_sz < src_sz ? dst_sz : src_sz);

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdGenArrCpyTo(void* dst, kd_i64_t len, void* src_arr)
{
  kd_usize_t dst_sz, src_sz;

  if (!dst || len <= 0 || !src_arr)
  {
    return KD_RESULT_FAILURE;
  }

  src_sz = kdi_GenArrGetMemSize(src_arr);
  dst_sz = len * kdi_GenArrGetElemSize(src_arr);

  kdi_GenMemOpsMove(dst, src_arr, dst_sz < src_sz ? dst_sz : src_sz);

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdGenArrCpyRange(void* dst_arr, kd_i64_t dst_from, void* src_arr, kd_i64_t src_from, kd_i64_t src_to)
{
  kd_usize_t el_sz, dst_sz, src_sz, dst_from_idx, src_from_idx, src_to_idx;

  if (!dst_arr || dst_from < 0 || !src_arr || src_from < 0 || src_to < 0 || src_from > src_to)
  {
    return KD_RESULT_FAILURE;
  }

  el_sz = kdi_GenArrGetElemSize(dst_arr);
  if (el_sz != kdi_GenArrGetElemSize(src_arr))
  {
    return KD_RESULT_FAILURE;
  }

  dst_sz       = kdi_GenArrGetMemSize(dst_arr);
  dst_from_idx = dst_from * el_sz;
  if (dst_from_idx >= dst_sz)
  {
    return KD_RESULT_FAILURE;
  }

  dst_sz -= dst_from_idx;

  src_sz     = kdi_GenArrGetMemSize(src_arr);
  src_to_idx = src_to * el_sz;
  if (src_to_idx >= src_sz)
  {
    return KD_RESULT_FAILURE;
  }

  src_from_idx = src_from * el_sz;
  src_sz       = src_to_idx - src_from_idx + el_sz;

  kdi_GenMemOpsMove(
    KD_PBYTE_C(dst_arr) + dst_from_idx, KD_PBYTE_C(src_arr) + src_from_idx, dst_sz < src_sz ? dst_sz : src_sz
  );

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdGenArrCpyRangeFrom(void* dst_arr, kd_i64_t dst_from, void* src, kd_i64_t src_from, kd_i64_t src_to)
{
  kd_usize_t el_sz, dst_sz, src_sz, dst_from_idx, src_from_idx;

  if (!dst_arr || dst_from < 0 || !src || src_from < 0 || src_to < 0 || src_from > src_to)
  {
    return KD_RESULT_FAILURE;
  }

  el_sz        = kdi_GenArrGetElemSize(dst_arr);
  dst_sz       = kdi_GenArrGetMemSize(dst_arr);
  dst_from_idx = dst_from * el_sz;
  if (dst_from_idx >= dst_sz)
  {
    return KD_RESULT_FAILURE;
  }

  src_from_idx = src_from * el_sz;
  src_sz       = (src_to * el_sz) - src_from_idx + el_sz;

  kdi_GenMemOpsMove(
    KD_PBYTE_C(dst_arr) + dst_from_idx, KD_PBYTE_C(src) + src_from_idx, dst_sz < src_sz ? dst_sz : src_sz
  );

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdGenArrCpyRangeTo(void* dst, kd_i64_t len, void* src_arr, kd_i64_t from, kd_i64_t to)
{
  kd_usize_t el_sz, dst_sz, src_sz, from_idx, to_idx;

  if (!dst || len <= 0 || !src_arr || from < 0 || to < 0 || from > to)
  {
    return KD_RESULT_FAILURE;
  }

  el_sz  = kdi_GenArrGetElemSize(src_arr);
  src_sz = kdi_GenArrGetMemSize(src_arr);
  to_idx = to * el_sz;
  if (to_idx >= src_sz)
  {
    return KD_RESULT_FAILURE;
  }

  from_idx = from * el_sz;
  src_sz   = to_idx - from_idx + el_sz;
  dst_sz   = len * src_sz;

  kdi_GenMemOpsMove(dst, KD_PBYTE_C(src_arr) + from_idx, dst_sz < src_sz ? dst_sz : src_sz);

  return KD_RESULT_SUCCESS;
}


void*
kdGenArrFind(void* arr, void* val_ptr)
{
  kd_usize_t el_sz, mem_sz;
  kd_u8_t    block_val_u8;
  kd_u16_t   block_val_u16;
  kd_u32_t   block_val_u32;
#if defined KD_ARCH_64BIT_INT
  kd_u64_t block_val_u64;
#endif

  if (!arr || !val_ptr)
  {
    return kd_null;
  }

  el_sz  = kdi_GenArrGetElemSize(arr);
  mem_sz = kdi_GenArrGetMemSize(arr);

  switch (el_sz)
  {
    case 1:
      block_val_u8 = *KD_PU8_C(val_ptr);
      return kdi_GenMemOpsFindBlockWithIndex_S8(kd_null, KD_PU8_C(arr), mem_sz, block_val_u8);
    case 2:
      block_val_u16 = *KD_PU16_C(val_ptr);
      return kdi_GenMemOpsFindBlockWithIndex_S16(kd_null, KD_PU16_C(arr), mem_sz, block_val_u16);
    case 4:
      block_val_u32 = *KD_PU32_C(val_ptr);
      return kdi_GenMemOpsFindBlockWithIndex_S32(kd_null, KD_PU32_C(arr), mem_sz, block_val_u32);
#if defined KD_ARCH_64BIT_INT
    case 8:
      block_val_u64 = *KD_PU64_C(val_ptr);
      return kdi_GenMemOpsFindBlockWithIndex_S64(kd_null, KD_PU64_C(arr), mem_sz, block_val_u64);
#endif
    default:;
  }

  return kdi_GenMemOpsFindBlockWithIndex_Sn(kd_null, arr, mem_sz, val_ptr, el_sz);
}


kd_i64_t
kdGenArrFindIndex(void* arr, void* val_ptr)
{
  kd_usize_t el_sz, mem_sz, idx;
  kd_byte_t* found_ptr;
  kd_u8_t    block_val_u8;
  kd_u16_t   block_val_u16;
  kd_u32_t   block_val_u32;
#if defined KD_ARCH_64BIT_INT
  kd_u64_t block_val_u64;
#endif

  if (!arr || !val_ptr)
  {
    return -1;
  }

  el_sz  = kdi_GenArrGetElemSize(arr);
  mem_sz = kdi_GenArrGetMemSize(arr);

  switch (el_sz)
  {
    case 1:
      block_val_u8 = *KD_PU8_C(val_ptr);
      found_ptr    = kdi_GenMemOpsFindBlockWithIndex_S8(&idx, KD_PU8_C(arr), mem_sz, block_val_u8);
      break;
    case 2:
      block_val_u16 = *KD_PU16_C(val_ptr);
      found_ptr     = kdi_GenMemOpsFindBlockWithIndex_S16(&idx, KD_PU16_C(arr), mem_sz, block_val_u16);
      break;
    case 4:
      block_val_u32 = *KD_PU32_C(val_ptr);
      found_ptr     = kdi_GenMemOpsFindBlockWithIndex_S32(&idx, KD_PU32_C(arr), mem_sz, block_val_u32);
      break;
#if defined KD_ARCH_64BIT_INT
    case 8:
      block_val_u64 = *KD_PU64_C(val_ptr);
      found_ptr     = kdi_GenMemOpsFindBlockWithIndex_S64(&idx, KD_PU64_C(arr), mem_sz, block_val_u64);
      break;
#endif
    default:
      found_ptr = kdi_GenMemOpsFindBlockWithIndex_Sn(&idx, arr, mem_sz, val_ptr, el_sz);
  }

  return found_ptr ? KD_I64_C(idx / el_sz) : -1;
}


void*
kdGenArrFindLast(void* arr, void* val_ptr)
{
  kd_usize_t el_sz, mem_sz;
  kd_u8_t    block_val_u8;
  kd_u16_t   block_val_u16;
  kd_u32_t   block_val_u32;
#if defined KD_ARCH_64BIT_INT
  kd_u64_t block_val_u64;
#endif

  if (!arr || !val_ptr)
  {
    return kd_null;
  }

  el_sz  = kdi_GenArrGetElemSize(arr);
  mem_sz = kdi_GenArrGetMemSize(arr);

  switch (el_sz)
  {
    case 1:
      block_val_u8 = *KD_PU8_C(val_ptr);
      return kdi_GenMemOpsFindLastBlockWithIndex_S8(kd_null, KD_PU8_C(arr), mem_sz, block_val_u8);
    case 2:
      block_val_u16 = *KD_PU16_C(val_ptr);
      return kdi_GenMemOpsFindLastBlockWithIndex_S16(kd_null, KD_PU16_C(arr), mem_sz, block_val_u16);
    case 4:
      block_val_u32 = *KD_PU32_C(val_ptr);
      return kdi_GenMemOpsFindLastBlockWithIndex_S32(kd_null, KD_PU32_C(arr), mem_sz, block_val_u32);
#if defined KD_ARCH_64BIT_INT
    case 8:
      block_val_u64 = *KD_PU64_C(val_ptr);
      return kdi_GenMemOpsFindLastBlockWithIndex_S64(kd_null, KD_PU64_C(arr), mem_sz, block_val_u64);
#endif
    default:;
  }

  return kdi_GenMemOpsFindLastBlockWithIndex_Sn(kd_null, arr, mem_sz, val_ptr, el_sz);
}


kd_i64_t
kdGenArrFindLastIndex(void* arr, void* val_ptr)
{
  kd_usize_t el_sz, mem_sz, idx;
  kd_byte_t* found_ptr;
  kd_u8_t    block_val_u8;
  kd_u16_t   block_val_u16;
  kd_u32_t   block_val_u32;
#if defined KD_ARCH_64BIT_INT
  kd_u64_t block_val_u64;
#endif

  if (!arr || !val_ptr)
  {
    return -1;
  }

  el_sz  = kdi_GenArrGetElemSize(arr);
  mem_sz = kdi_GenArrGetMemSize(arr);

  switch (el_sz)
  {
    case 1:
      block_val_u8 = *KD_PU8_C(val_ptr);
      found_ptr    = kdi_GenMemOpsFindLastBlockWithIndex_S8(&idx, KD_PU8_C(arr), mem_sz, block_val_u8);
      break;
    case 2:
      block_val_u16 = *KD_PU16_C(val_ptr);
      found_ptr     = kdi_GenMemOpsFindLastBlockWithIndex_S16(&idx, KD_PU16_C(arr), mem_sz, block_val_u16);
      break;
    case 4:
      block_val_u32 = *KD_PU32_C(val_ptr);
      found_ptr     = kdi_GenMemOpsFindLastBlockWithIndex_S32(&idx, KD_PU32_C(arr), mem_sz, block_val_u32);
      break;
#if defined KD_ARCH_64BIT_INT
    case 8:
      block_val_u64 = *KD_PU64_C(val_ptr);
      found_ptr     = kdi_GenMemOpsFindLastBlockWithIndex_S64(&idx, KD_PU64_C(arr), mem_sz, block_val_u64);
      break;
#endif
    default:
      found_ptr = kdi_GenMemOpsFindLastBlockWithIndex_Sn(&idx, arr, mem_sz, val_ptr, el_sz);
  }

  return found_ptr ? KD_I64_C(idx / el_sz) : -1;
}


kd_i64_t
kdGenArrFindAll(void* dst_arr, void* src_arr, void* val_ptr)
{
  kd_usize_t  el_sz, dst_sz, src_sz, found_cnt, temp_found_cnt, *idxs_ptr;
  kd_byte_t** dst_ptr;
  kd_u8_t     block_val_u8;
  kd_u16_t    block_val_u16;
  kd_u32_t    block_val_u32;
#if defined KD_ARCH_64BIT_INT
  kd_u64_t block_val_u64;
#endif

  if (!dst_arr || !src_arr || !val_ptr || kdi_GenArrGetElemSize(dst_arr) != KD_SZ_PTR)
  {
    return 0;
  }

  el_sz  = kdi_GenArrGetElemSize(src_arr);
  dst_sz = kdi_GenArrGetMemSize(dst_arr);
  src_sz = kdi_GenArrGetMemSize(src_arr);

  switch (el_sz)
  {
    case 1:
      block_val_u8 = *KD_PU8_C(val_ptr);
      found_cnt =
        kdi_GenMemOpsFindAllBlocksWithIndex_S8(KD_PUSIZE_C(dst_arr), dst_sz, KD_PU8_C(src_arr), src_sz, block_val_u8);
      break;
    case 2:
      block_val_u16 = *KD_PU16_C(val_ptr);
      found_cnt     = kdi_GenMemOpsFindAllBlocksWithIndex_S16(
        KD_PUSIZE_C(dst_arr), dst_sz, KD_PU16_C(src_arr), src_sz, block_val_u16
      );
      break;
    case 4:
      block_val_u32 = *KD_PU32_C(val_ptr);
      found_cnt     = kdi_GenMemOpsFindAllBlocksWithIndex_S32(
        KD_PUSIZE_C(dst_arr), dst_sz, KD_PU32_C(src_arr), src_sz, block_val_u32
      );
      break;
#if defined KD_ARCH_64BIT_INT
    case 8:
      block_val_u64 = *KD_PU64_C(val_ptr);
      found_cnt     = kdi_GenMemOpsFindAllBlocksWithIndex_S64(
        KD_PUSIZE_C(dst_arr), dst_sz, KD_PU64_C(src_arr), src_sz, block_val_u64
      );
      break;
#endif
    default:
      found_cnt = kdi_GenMemOpsFindAllBlocksWithIndex_Sn(KD_PUSIZE_C(dst_arr), dst_sz, src_arr, src_sz, val_ptr, el_sz);
  }

  temp_found_cnt = found_cnt;
  dst_ptr        = dst_arr;
  idxs_ptr       = dst_arr;

  while (temp_found_cnt--)
  {
    *dst_ptr = KD_PBYTE_C(src_arr) + *idxs_ptr;
    ++dst_ptr;
    ++idxs_ptr;
  }

  return KD_I64_C(found_cnt);
}


kd_i64_t
kdGenArrFindAllTo(void* dst, kd_i64_t len, void* arr, void* val_ptr)
{
  kd_usize_t  el_sz, dst_sz, src_sz, found_cnt, temp_found_cnt, *idxs_ptr;
  kd_byte_t** dst_ptr;
  kd_u8_t     block_val_u8;
  kd_u16_t    block_val_u16;
  kd_u32_t    block_val_u32;
#if defined KD_ARCH_64BIT_INT
  kd_u64_t block_val_u64;
#endif

  if (!dst || len <= 0 || !arr || !val_ptr)
  {
    return 0;
  }

  el_sz  = kdi_GenArrGetElemSize(arr);
  src_sz = kdi_GenArrGetMemSize(arr);
  dst_sz = len * el_sz;

  switch (el_sz)
  {
    case 1:
      block_val_u8 = *KD_PU8_C(val_ptr);
      found_cnt = kdi_GenMemOpsFindAllBlocksWithIndex_S8(KD_PUSIZE_C(dst), dst_sz, KD_PU8_C(arr), src_sz, block_val_u8);
      break;
    case 2:
      block_val_u16 = *KD_PU16_C(val_ptr);
      found_cnt =
        kdi_GenMemOpsFindAllBlocksWithIndex_S16(KD_PUSIZE_C(dst), dst_sz, KD_PU16_C(arr), src_sz, block_val_u16);
      break;
    case 4:
      block_val_u32 = *KD_PU32_C(val_ptr);
      found_cnt =
        kdi_GenMemOpsFindAllBlocksWithIndex_S32(KD_PUSIZE_C(dst), dst_sz, KD_PU32_C(arr), src_sz, block_val_u32);
      break;
#if defined KD_ARCH_64BIT_INT
    case 8:
      block_val_u64 = *KD_PU64_C(val_ptr);
      found_cnt =
        kdi_GenMemOpsFindAllBlocksWithIndex_S64(KD_PUSIZE_C(dst), dst_sz, KD_PU64_C(arr), src_sz, block_val_u64);
      break;
#endif
    default:
      found_cnt = kdi_GenMemOpsFindAllBlocksWithIndex_Sn(KD_PUSIZE_C(dst), dst_sz, arr, src_sz, val_ptr, el_sz);
  }

  temp_found_cnt = found_cnt;
  dst_ptr        = dst;
  idxs_ptr       = dst;

  while (temp_found_cnt--)
  {
    *dst_ptr = KD_PBYTE_C(arr) + *idxs_ptr;
    ++dst_ptr;
    ++idxs_ptr;
  }

  return KD_I64_C(found_cnt);
}


kd_i64_t
kdGenArrFindAllIndices(void* idx_arr, void* arr, void* val_ptr)
{
  kd_usize_t el_sz, idx_sz, src_sz, found_cnt, temp_found_cnt, *idx_ptr;
  kd_u8_t    block_val_u8;
  kd_u16_t   block_val_u16;
  kd_u32_t   block_val_u32;
#if defined KD_ARCH_64BIT_INT
  kd_u64_t block_val_u64;
#endif

  if (!idx_arr || !arr || !val_ptr || kdi_GenArrGetElemSize(idx_arr) != KD_SZ_PTR)
  {
    return 0;
  }

  el_sz  = kdi_GenArrGetElemSize(arr);
  idx_sz = kdi_GenArrGetMemSize(idx_arr);
  src_sz = kdi_GenArrGetMemSize(arr);

  switch (el_sz)
  {
    case 1:
      block_val_u8 = *KD_PU8_C(val_ptr);
      found_cnt =
        kdi_GenMemOpsFindAllBlocksWithIndex_S8(KD_PUSIZE_C(idx_arr), idx_sz, KD_PU8_C(arr), src_sz, block_val_u8);
      break;
    case 2:
      block_val_u16 = *KD_PU16_C(val_ptr);
      found_cnt =
        kdi_GenMemOpsFindAllBlocksWithIndex_S16(KD_PUSIZE_C(idx_arr), idx_sz, KD_PU16_C(arr), src_sz, block_val_u16);
      break;
    case 4:
      block_val_u32 = *KD_PU32_C(val_ptr);
      found_cnt =
        kdi_GenMemOpsFindAllBlocksWithIndex_S32(KD_PUSIZE_C(idx_arr), idx_sz, KD_PU32_C(arr), src_sz, block_val_u32);
      break;
#if defined KD_ARCH_64BIT_INT
    case 8:
      block_val_u64 = *KD_PU64_C(val_ptr);
      found_cnt =
        kdi_GenMemOpsFindAllBlocksWithIndex_S64(KD_PUSIZE_C(idx_arr), idx_sz, KD_PU64_C(arr), src_sz, block_val_u64);
      break;
#endif
    default:
      found_cnt = kdi_GenMemOpsFindAllBlocksWithIndex_Sn(KD_PUSIZE_C(idx_arr), idx_sz, arr, src_sz, val_ptr, el_sz);
  }

  temp_found_cnt = found_cnt;
  idx_ptr        = idx_arr;

  while (temp_found_cnt--)
  {
    *idx_ptr /= el_sz;
    idx_ptr = KD_PUSIZE_C(KD_PBYTE_C(idx_ptr) + KD_SZ_USIZE);
  }

  return KD_I64_C(found_cnt);
}


kd_i64_t
kdGenArrFindAllIndicesTo(void* idxs, kd_i64_t len, void* arr, void* val_ptr)
{
  kd_usize_t el_sz, idx_sz, src_sz, found_cnt, temp_found_cnt, *idx_ptr;
  kd_u8_t    block_val_u8;
  kd_u16_t   block_val_u16;
  kd_u32_t   block_val_u32;
#if defined KD_ARCH_64BIT_INT
  kd_u64_t block_val_u64;
#endif

  if (!idxs || len <= 0 || !arr || !val_ptr)
  {
    return 0;
  }

  el_sz  = kdi_GenArrGetElemSize(arr);
  src_sz = kdi_GenArrGetMemSize(arr);
  idx_sz = len * el_sz;

  switch (el_sz)
  {
    case 1:
      block_val_u8 = *KD_PU8_C(val_ptr);
      found_cnt =
        kdi_GenMemOpsFindAllBlocksWithIndex_S8(KD_PUSIZE_C(idxs), idx_sz, KD_PU8_C(arr), src_sz, block_val_u8);
      break;
    case 2:
      block_val_u16 = *KD_PU16_C(val_ptr);
      found_cnt =
        kdi_GenMemOpsFindAllBlocksWithIndex_S16(KD_PUSIZE_C(idxs), idx_sz, KD_PU16_C(arr), src_sz, block_val_u16);
      break;
    case 4:
      block_val_u32 = *KD_PU32_C(val_ptr);
      found_cnt =
        kdi_GenMemOpsFindAllBlocksWithIndex_S32(KD_PUSIZE_C(idxs), idx_sz, KD_PU32_C(arr), src_sz, block_val_u32);
      break;
#if defined KD_ARCH_64BIT_INT
    case 8:
      block_val_u64 = *KD_PU64_C(val_ptr);
      found_cnt =
        kdi_GenMemOpsFindAllBlocksWithIndex_S64(KD_PUSIZE_C(idxs), idx_sz, KD_PU64_C(arr), src_sz, block_val_u64);
      break;
#endif
    default:
      found_cnt = kdi_GenMemOpsFindAllBlocksWithIndex_Sn(KD_PUSIZE_C(idxs), idx_sz, arr, src_sz, val_ptr, el_sz);
  }

  temp_found_cnt = found_cnt;
  idx_ptr        = idxs;

  while (temp_found_cnt--)
  {
    *idx_ptr /= el_sz;
    idx_ptr = KD_PUSIZE_C(KD_PBYTE_C(idx_ptr) + KD_SZ_USIZE);
  }

  return KD_I64_C(found_cnt);
}
