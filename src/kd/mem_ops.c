/**
 * @file mem_ops.c
 * @author Kumarjit Das
 * @date 2025-06-03
 * @since 0.0.9
 * @brief Main source file of the MEM_OPS library.
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
#include "_internal/gen_mem_ops_sn.h"
#include "kd/gen_mem_ops.h"
#include "kd/mem_ops.h"


kd_bool_t
kdMemOpsSetU16(void* ptr, kd_i64_t len, kd_u16_t val)
{
  if (!ptr || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsSetBlocks_U16(ptr, len * KD_SZ_U16, val);

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsSetU32(void* ptr, kd_i64_t len, kd_u32_t val)
{
  if (!ptr || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsSetBlocks_U32(ptr, len * KD_SZ_U32, val);

  return KD_RESULT_SUCCESS;
}


#if defined KD_ARCH_64BIT_INT
kd_bool_t
kdMemOpsSetU64(void* ptr, kd_i64_t len, kd_u64_t val)
{
  if (!ptr || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsSetBlocks_U64(ptr, len * KD_SZ_U64, val);

  return KD_RESULT_SUCCESS;
}
#endif /* KD_ARCH_64BIT_INT */


kd_bool_t
kdMemOpsSetUmin(void* ptr, kd_i64_t len, kd_umin_t val)
{
  if (!ptr || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsSetBlocks_Umin(ptr, len * KD_SZ_UMIN, val);

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsSetUmax(void* ptr, kd_i64_t len, kd_umax_t val)
{
  if (!ptr || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsSetBlocks_Umax(ptr, len * KD_SZ_UMAX, val);

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsSetUsize(void* ptr, kd_i64_t len, kd_usize_t val)
{
  if (!ptr || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsSetBlocks_Usize(ptr, len * KD_SZ_USIZE, val);

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsSetChr(void* ptr, kd_i64_t len, kd_chr_t val)
{
  if (!ptr || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsSetBlocks_Chr(ptr, len * KD_SZ_CHR, val);

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsSetBool(void* ptr, kd_i64_t len, kd_bool_t val)
{
  if (!ptr || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsSetBlocks_Bool(ptr, len * KD_SZ_U32, (kd_u32_t)val);

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsSetPtr(void* ptr, kd_i64_t len, void* val)
{
  if (!ptr || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsSetBlocks_Ptr(ptr, len * KD_SZ_U64, val);

  return KD_RESULT_SUCCESS;
}


void*
kdMemOpsFindU16(void* ptr, kd_i64_t len, kd_u16_t item)
{
  if (!ptr || len <= 0)
  {
    return kd_null;
  }

  return kdi_GenMemOpsFindBlockWithIndex_U16(kd_null, ptr, len * KD_SZ_U16, item);
}


void*
kdMemOpsFindU32(void* ptr, kd_i64_t len, kd_u32_t item)
{
  if (!ptr || len <= 0)
  {
    return kd_null;
  }

  return kdi_GenMemOpsFindBlockWithIndex_U32(kd_null, ptr, len * KD_SZ_U32, item);
}


#if defined KD_ARCH_64BIT_INT
void*
kdMemOpsFindU64(void* ptr, kd_i64_t len, kd_u64_t item)
{
  if (!ptr || len <= 0)
  {
    return kd_null;
  }

  return kdi_GenMemOpsFindBlockWithIndex_U64(kd_null, ptr, len * KD_SZ_U64, item);
}
#endif /* KD_ARCH_64BIT_INT */


void*
kdMemOpsFindUmin(void* ptr, kd_i64_t len, kd_umin_t item)
{
  if (!ptr || len <= 0)
  {
    return kd_null;
  }

  return kdi_GenMemOpsFindBlockWithIndex_Umin(kd_null, ptr, len * KD_SZ_UMIN, item);
}


void*
kdMemOpsFindUmax(void* ptr, kd_i64_t len, kd_umax_t item)
{
  if (!ptr || len <= 0)
  {
    return kd_null;
  }

  return kdi_GenMemOpsFindBlockWithIndex_Umax(kd_null, ptr, len * KD_SZ_UMAX, item);
}


void*
kdMemOpsFindUsize(void* ptr, kd_i64_t len, kd_usize_t item)
{
  if (!ptr || len <= 0)
  {
    return kd_null;
  }

  return kdi_GenMemOpsFindBlockWithIndex_Usize(kd_null, ptr, len * KD_SZ_USIZE, item);
}


void*
kdMemOpsFindChr(void* ptr, kd_i64_t len, kd_chr_t item)
{
  if (!ptr || len <= 0)
  {
    return kd_null;
  }

  return kdi_GenMemOpsFindBlockWithIndex_Chr(kd_null, ptr, len * KD_SZ_CHR, item);
}


void*
kdMemOpsFindBool(void* ptr, kd_i64_t len, kd_bool_t item)
{
  if (!ptr || len <= 0)
  {
    return kd_null;
  }

  return kdi_GenMemOpsFindBlockWithIndex_Bool(kd_null, ptr, len * KD_SZ_BOOL, item);
}


void*
kdMemOpsFindPtr(void* ptr, kd_i64_t len, void* item)
{
  if (!ptr || len <= 0)
  {
    return kd_null;
  }

  return kdi_GenMemOpsFindBlockWithIndex_Ptr(kd_null, ptr, len * KD_SZ_PTR, item);
}


kd_i64_t
kdMemOpsFindIndex(void* ptr, kd_i64_t len, kd_byte_t item)
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsFindBlockWithIndex_Byte(&idx, ptr, len, item);

  return found_ptr ? (kd_i64_t)idx : -1;
}


kd_i64_t
kdMemOpsFindIndexU16(void* ptr, kd_i64_t len, kd_u16_t item)
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsFindBlockWithIndex_U16(&idx, ptr, len * KD_SZ_U16, item);

  return found_ptr ? (kd_i64_t)(idx / KD_SZ_U16) : -1;
}


kd_i64_t
kdMemOpsFindIndexU32(void* ptr, kd_i64_t len, kd_u32_t item)
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsFindBlockWithIndex_U32(&idx, ptr, len * KD_SZ_U32, item);

  return found_ptr ? (kd_i64_t)(idx / KD_SZ_U32) : -1;
}


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsFindIndexU64(void* ptr, kd_i64_t len, kd_u64_t item)
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsFindBlockWithIndex_S64(&idx, ptr, len * KD_SZ_U64, item);

  return found_ptr ? (kd_i64_t)(idx / KD_SZ_U64) : -1;
}
#endif /* KD_ARCH_64BIT_INT */


kd_i64_t
kdMemOpsFindIndexUmin(void* ptr, kd_i64_t len, kd_umin_t item)
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsFindBlockWithIndex_Umin(&idx, ptr, len * KD_SZ_UMIN, item);

  return found_ptr ? (kd_i64_t)(idx / KD_SZ_UMIN) : -1;
}


kd_i64_t
kdMemOpsFindIndexUmax(void* ptr, kd_i64_t len, kd_umax_t item)
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsFindBlockWithIndex_Umax(&idx, ptr, len * KD_SZ_UMAX, item);

  return found_ptr ? (kd_i64_t)(idx / KD_SZ_UMAX) : -1;
}


kd_i64_t
kdMemOpsFindIndexUsize(void* ptr, kd_i64_t len, kd_usize_t item)
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsFindBlockWithIndex_Usize(&idx, ptr, len * KD_SZ_USIZE, item);

  return found_ptr ? (kd_i64_t)(idx / KD_SZ_USIZE) : -1;
}


kd_i64_t
kdMemOpsFindIndexChr(void* ptr, kd_i64_t len, kd_chr_t item)
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsFindBlockWithIndex_Chr(&idx, ptr, len * KD_SZ_CHR, item);

  return found_ptr ? (kd_i64_t)(idx / KD_SZ_CHR) : -1;
}


kd_i64_t
kdMemOpsFindIndexBool(void* ptr, kd_i64_t len, kd_bool_t item)
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsFindBlockWithIndex_Bool(&idx, ptr, len * KD_SZ_BOOL, item);

  return found_ptr ? (kd_i64_t)(idx / KD_SZ_BOOL) : -1;
}


kd_i64_t
kdMemOpsFindIndexPtr(void* ptr, kd_i64_t len, void* item)
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsFindBlockWithIndex_Ptr(&idx, ptr, len * KD_SZ_PTR, item);

  return found_ptr ? (kd_i64_t)(idx / KD_SZ_PTR) : -1;
}


void*
kdMemOpsCompSpnU16(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
{
  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return kd_null;
  }

  return kdi_GenMemOpsBlocksCompSpnWithIndex_U16(kd_null, ptr, len * KD_SZ_U16, keys, keys_len * KD_SZ_U16);
}


void*
kdMemOpsCompSpnU32(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
{
  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return kd_null;
  }

  return kdi_GenMemOpsBlocksCompSpnWithIndex_U32(kd_null, ptr, len * KD_SZ_U32, keys, keys_len * KD_SZ_U32);
}


#if defined KD_ARCH_64BIT_INT
void*
kdMemOpsCompSpnU64(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
{
  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return kd_null;
  }

  return kdi_GenMemOpsBlocksCompSpnWithIndex_U64(kd_null, ptr, len * KD_SZ_U64, keys, keys_len * KD_SZ_U64);
}
#endif /* KD_ARCH_64BIT_INT */


void*
kdMemOpsCompSpnUmin(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
{
  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return kd_null;
  }

  return kdi_GenMemOpsBlocksCompSpnWithIndex_Umin(kd_null, ptr, len * KD_SZ_UMIN, keys, keys_len * KD_SZ_UMIN);
}


void*
kdMemOpsCompSpnUmax(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
{
  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return kd_null;
  }

  return kdi_GenMemOpsBlocksCompSpnWithIndex_Umax(kd_null, ptr, len * KD_SZ_UMAX, keys, keys_len * KD_SZ_UMAX);
}


void*
kdMemOpsCompSpnUsize(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
{
  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return kd_null;
  }

  return kdi_GenMemOpsBlocksCompSpnWithIndex_Usize(kd_null, ptr, len * KD_SZ_USIZE, keys, keys_len * KD_SZ_USIZE);
}


void*
kdMemOpsCompSpnChr(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
{
  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return kd_null;
  }

  return kdi_GenMemOpsBlocksCompSpnWithIndex_Chr(kd_null, ptr, len * KD_SZ_CHR, keys, keys_len * KD_SZ_CHR);
}


void*
kdMemOpsCompSpnBool(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
{
  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return kd_null;
  }

  return kdi_GenMemOpsBlocksCompSpnWithIndex_Bool(kd_null, ptr, len * KD_SZ_BOOL, keys, keys_len * KD_SZ_BOOL);
}


void*
kdMemOpsCompSpnPtr(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
{
  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return kd_null;
  }

  return kdi_GenMemOpsBlocksCompSpnWithIndex_Ptr(kd_null, ptr, len * KD_SZ_PTR, keys, keys_len * KD_SZ_PTR);
}


kd_i64_t
kdMemOpsCompSpnIndex(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsBlocksCompSpnWithIndex_Byte(&idx, ptr, len, keys, keys_len);

  return found_ptr ? (kd_i64_t)idx : -1;
}


kd_i64_t
kdMemOpsCompSpnIndexU16(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsBlocksCompSpnWithIndex_U16(&idx, ptr, len * KD_SZ_U16, keys, keys_len * KD_SZ_U16);

  return found_ptr ? (kd_i64_t)(idx / KD_SZ_U16) : -1;
}


kd_i64_t
kdMemOpsCompSpnIndexU32(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsBlocksCompSpnWithIndex_U32(&idx, ptr, len * KD_SZ_U32, keys, keys_len * KD_SZ_U32);

  return found_ptr ? (kd_i64_t)(idx / KD_SZ_U32) : -1;
}


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsCompSpnIndexU64(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsBlocksCompSpnWithIndex_U64(&idx, ptr, len * KD_SZ_U64, keys, keys_len * KD_SZ_U64);

  return found_ptr ? (kd_i64_t)(idx / KD_SZ_U64) : -1;
}
#endif /* KD_ARCH_64BIT_INT */


kd_i64_t
kdMemOpsCompSpnIndexUmin(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsBlocksCompSpnWithIndex_Umin(&idx, ptr, len * KD_SZ_UMIN, keys, keys_len * KD_SZ_UMIN);

  return found_ptr ? (kd_i64_t)(idx / KD_SZ_UMIN) : -1;
}


kd_i64_t
kdMemOpsCompSpnIndexUmax(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsBlocksCompSpnWithIndex_Umax(&idx, ptr, len * KD_SZ_UMAX, keys, keys_len * KD_SZ_UMAX);

  return found_ptr ? (kd_i64_t)(idx / KD_SZ_UMAX) : -1;
}


kd_i64_t
kdMemOpsCompSpnIndexUsize(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsBlocksCompSpnWithIndex_Usize(&idx, ptr, len * KD_SZ_USIZE, keys, keys_len * KD_SZ_USIZE);

  return found_ptr ? (kd_i64_t)(idx / KD_SZ_USIZE) : -1;
}


kd_i64_t
kdMemOpsCompSpnIndexChr(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsBlocksCompSpnWithIndex_Chr(&idx, ptr, len * KD_SZ_CHR, keys, keys_len * KD_SZ_CHR);

  return found_ptr ? (kd_i64_t)(idx / KD_SZ_CHR) : -1;
}


kd_i64_t
kdMemOpsCompSpnIndexBool(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsBlocksCompSpnWithIndex_Bool(&idx, ptr, len * KD_SZ_BOOL, keys, keys_len * KD_SZ_BOOL);

  return found_ptr ? (kd_i64_t)(idx / KD_SZ_BOOL) : -1;
}


kd_i64_t
kdMemOpsCompSpnIndexPtr(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsBlocksCompSpnWithIndex_Ptr(&idx, ptr, len * KD_SZ_PTR, keys, keys_len * KD_SZ_PTR);

  return found_ptr ? (kd_i64_t)(idx / KD_SZ_PTR) : -1;
}
