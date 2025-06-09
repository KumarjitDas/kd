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
kdMemOpsSwap(void* ptr, kd_i64_t len, kd_i64_t idx1, kd_i64_t idx2)
{
  if (!ptr || len <= 0 || idx1 < 0 || idx2 < 0 || idx1 >= len || idx2 >= len)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsSwapBlocks_Byte(ptr, idx1, idx2);

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsSwapU16(void* ptr, kd_i64_t len, kd_i64_t idx1, kd_i64_t idx2)
{
  if (!ptr || len <= 0 || idx1 < 0 || idx2 < 0 || idx1 >= len || idx2 >= len)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsSwapBlocks_U16(ptr, idx1 * KD_SZ_U16, idx2 * KD_SZ_U16);

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsSwapU32(void* ptr, kd_i64_t len, kd_i64_t idx1, kd_i64_t idx2)
{
  if (!ptr || len <= 0 || idx1 < 0 || idx2 < 0 || idx1 >= len || idx2 >= len)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsSwapBlocks_U32(ptr, idx1 * KD_SZ_U32, idx2 * KD_SZ_U32);

  return KD_RESULT_SUCCESS;
}


#if defined KD_ARCH_64BIT_INT
kd_bool_t
kdMemOpsSwapU64(void* ptr, kd_i64_t len, kd_i64_t idx1, kd_i64_t idx2)
{
  if (!ptr || len <= 0 || idx1 < 0 || idx2 < 0 || idx1 >= len || idx2 >= len)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsSwapBlocks_U64(ptr, idx1 * KD_SZ_U64, idx2 * KD_SZ_U64);

  return KD_RESULT_SUCCESS;
}
#endif /* KD_ARCH_64BIT_INT */


kd_bool_t
kdMemOpsReverse(void* ptr, kd_i64_t len)
{
  if (!ptr || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsReverseBlocks_Byte(ptr, len);

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsReverseU16(void* ptr, kd_i64_t len)
{
  if (!ptr || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsReverseBlocks_U16(ptr, len * KD_SZ_U16);

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsReverseU32(void* ptr, kd_i64_t len)
{
  if (!ptr || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsReverseBlocks_U32(ptr, len * KD_SZ_U32);

  return KD_RESULT_SUCCESS;
}


#if defined KD_ARCH_64BIT_INT
kd_bool_t
kdMemOpsReverseU64(void* ptr, kd_i64_t len)
{
  if (!ptr || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsReverseBlocks_U64(ptr, len * KD_SZ_U64);

  return KD_RESULT_SUCCESS;
}
#endif /* KD_ARCH_64BIT_INT */


kd_bool_t
kdMemOpsSet(void* ptr, kd_i64_t len, kd_byte_t val)
{
  if (!ptr || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsSetBlocks_Byte(ptr, len, val);

  return KD_RESULT_SUCCESS;
}


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
kdMemOpsCpy(void* dst, void* src, kd_i64_t len)
{
  return len < 0 ? KD_RESULT_FAILURE : kdGenMemOpsCpy(dst, src, len);
}


kd_bool_t
kdMemOpsCpyU16(void* dst, void* src, kd_i64_t len)
{
  return len < 0 ? KD_RESULT_FAILURE : kdGenMemOpsCpy(dst, src, KD_USIZE_C(len) * KD_SZ_U16);
}


kd_bool_t
kdMemOpsCpyU32(void* dst, void* src, kd_i64_t len)
{
  return len < 0 ? KD_RESULT_FAILURE : kdGenMemOpsCpy(dst, src, KD_USIZE_C(len) * KD_SZ_U32);
}


#if defined KD_ARCH_64BIT_INT
kd_bool_t
kdMemOpsCpyU64(void* dst, void* src, kd_i64_t len)
{
  return len < 0 ? KD_RESULT_FAILURE : kdGenMemOpsCpy(dst, src, KD_USIZE_C(len) * KD_SZ_U64);
}
#endif /* KD_ARCH_64BIT_INT */


kd_bool_t
kdMemOpsMove(void* dst, void* src, kd_i64_t len)
{
  return len < 0 ? KD_RESULT_FAILURE : kdGenMemOpsMove(dst, src, len);
}


kd_bool_t
kdMemOpsMoveU16(void* dst, void* src, kd_i64_t len)
{
  return len < 0 ? KD_RESULT_FAILURE : kdGenMemOpsMove(dst, src, KD_USIZE_C(len) * KD_SZ_U16);
}


kd_bool_t
kdMemOpsMoveU32(void* dst, void* src, kd_i64_t len)
{
  return len < 0 ? KD_RESULT_FAILURE : kdGenMemOpsMove(dst, src, KD_USIZE_C(len) * KD_SZ_U32);
}


#if defined KD_ARCH_64BIT_INT
kd_bool_t
kdMemOpsMoveU64(void* dst, void* src, kd_i64_t len)
{
  return len < 0 ? KD_RESULT_FAILURE : kdGenMemOpsMove(dst, src, KD_USIZE_C(len) * KD_SZ_U64);
}
#endif /* KD_ARCH_64BIT_INT */


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

  return found_ptr ? KD_I64_C(idx) : -1;
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

  return found_ptr ? KD_I64_C(idx / KD_SZ_U16) : -1;
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

  return found_ptr ? KD_I64_C(idx / KD_SZ_U32) : -1;
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

  found_ptr = kdi_GenMemOpsFindBlockWithIndex_U64(&idx, ptr, len * KD_SZ_U64, item);

  return found_ptr ? KD_I64_C(idx / KD_SZ_U64) : -1;
}
#endif /* KD_ARCH_64BIT_INT */


void*
kdMemOpsFindLastU16(void* ptr, kd_i64_t len, kd_u16_t item)
{
  if (!ptr || len <= 0)
  {
    return kd_null;
  }

  return kdi_GenMemOpsFindLastBlockWithIndex_U16(kd_null, ptr, len * KD_SZ_U16, item);
}


void*
kdMemOpsFindLastU32(void* ptr, kd_i64_t len, kd_u32_t item)
{
  if (!ptr || len <= 0)
  {
    return kd_null;
  }

  return kdi_GenMemOpsFindLastBlockWithIndex_U32(kd_null, ptr, len * KD_SZ_U32, item);
}


#if defined KD_ARCH_64BIT_INT
void*
kdMemOpsFindLastU64(void* ptr, kd_i64_t len, kd_u64_t item)
{
  if (!ptr || len <= 0)
  {
    return kd_null;
  }

  return kdi_GenMemOpsFindLastBlockWithIndex_U64(kd_null, ptr, len * KD_SZ_U64, item);
}
#endif /* KD_ARCH_64BIT_INT */


kd_i64_t
kdMemOpsFindLastIndex(void* ptr, kd_i64_t len, kd_byte_t item)
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsFindLastBlockWithIndex_Byte(&idx, ptr, len, item);

  return found_ptr ? KD_I64_C(idx) : -1;
}


kd_i64_t
kdMemOpsFindLastIndexU16(void* ptr, kd_i64_t len, kd_u16_t item)
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsFindLastBlockWithIndex_U16(&idx, ptr, len * KD_SZ_U16, item);

  return found_ptr ? KD_I64_C(idx / KD_SZ_U16) : -1;
}


kd_i64_t
kdMemOpsFindLastIndexU32(void* ptr, kd_i64_t len, kd_u32_t item)
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsFindLastBlockWithIndex_U32(&idx, ptr, len * KD_SZ_U32, item);

  return found_ptr ? KD_I64_C(idx / KD_SZ_U32) : -1;
}


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsFindLastIndexU64(void* ptr, kd_i64_t len, kd_u64_t item)
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsFindLastBlockWithIndex_U64(&idx, ptr, len * KD_SZ_U64, item);

  return found_ptr ? KD_I64_C(idx / KD_SZ_U64) : -1;
}
#endif /* KD_ARCH_64BIT_INT */


kd_i64_t
kdMemOpsFindAll(void* dst, kd_i64_t dst_len, void* ptr, kd_i64_t ptr_len, kd_byte_t item)
{
  if (dst_len < 0 || ptr_len < 0)
  {
    return 0;
  }
  return KD_I64_C(kdGenMemOpsFindAllBytes(dst, dst_len, ptr, ptr_len, item));
}


kd_i64_t
kdMemOpsFindAllU16(void* dst, kd_i64_t dst_len, void* ptr, kd_i64_t ptr_len, kd_u16_t item)
{
  if (dst_len < 0 || ptr_len < 0)
  {
    return 0;
  }
  return KD_I64_C(kdGenMemOpsFindAllBlocks(dst, dst_len * KD_SZ_U16, ptr, ptr_len * KD_SZ_U16, &item, KD_SZ_U16));
}


kd_i64_t
kdMemOpsFindAllU32(void* dst, kd_i64_t dst_len, void* ptr, kd_i64_t ptr_len, kd_u32_t item)
{
  if (dst_len < 0 || ptr_len < 0)
  {
    return 0;
  }
  return KD_I64_C(kdGenMemOpsFindAllBlocks(dst, dst_len * KD_SZ_U32, ptr, ptr_len * KD_SZ_U32, &item, KD_SZ_U32));
}


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsFindAllU64(void* dst, kd_i64_t dst_len, void* ptr, kd_i64_t ptr_len, kd_u64_t item)
{
  if (dst_len < 0 || ptr_len < 0)
  {
    return 0;
  }
  return KD_I64_C(kdGenMemOpsFindAllBlocks(dst, dst_len * KD_SZ_U64, ptr, ptr_len * KD_SZ_U64, &item, KD_SZ_U64));
}
#endif /* KD_ARCH_64BIT_INT */


kd_i64_t
kdMemOpsFindAllIndex(kd_i64_t* idxs, kd_i64_t idxs_len, void* ptr, kd_i64_t ptr_len, kd_byte_t item)
{
  if (!idxs || idxs_len <= 0 || !ptr || ptr_len <= 0)
  {
    return 0;
  }
  return KD_I64_C(kdi_GenMemOpsFindAllBlocksWithIndex_Byte(idxs, idxs_len, ptr, ptr_len, item));
}


kd_i64_t
kdMemOpsFindAllIndexU16(kd_i64_t* idxs, kd_i64_t idxs_len, void* ptr, kd_i64_t ptr_len, kd_u16_t item)
{
  kd_usize_t found_cnt, temp_found_cnt;

  if (!idxs || idxs_len <= 0 || !ptr || ptr_len <= 0)
  {
    return 0;
  }

  found_cnt = kdi_GenMemOpsFindAllBlocksWithIndex_U16(idxs, idxs_len * KD_SZ_USIZE, ptr, ptr_len * KD_SZ_U16, item);
  temp_found_cnt = found_cnt;

  while (temp_found_cnt--)
  {
    *idxs /= KD_SZ_U16;
    idxs = (kd_i64_t*)((kd_byte_t*)idxs + KD_SZ_USIZE);
  }

  return KD_I64_C(found_cnt);
}


kd_i64_t
kdMemOpsFindAllIndexU32(kd_i64_t* idxs, kd_i64_t idxs_len, void* ptr, kd_i64_t ptr_len, kd_u32_t item)
{
  kd_usize_t found_cnt, temp_found_cnt;

  if (!idxs || idxs_len <= 0 || !ptr || ptr_len <= 0)
  {
    return 0;
  }

  found_cnt = kdi_GenMemOpsFindAllBlocksWithIndex_U32(idxs, idxs_len * KD_SZ_USIZE, ptr, ptr_len * KD_SZ_U32, item);
  temp_found_cnt = found_cnt;

  while (temp_found_cnt--)
  {
    *idxs /= KD_SZ_U32;
    idxs = (kd_i64_t*)((kd_byte_t*)idxs + KD_SZ_USIZE);
  }

  return KD_I64_C(found_cnt);
}


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsFindAllIndexU64(kd_i64_t* idxs, kd_i64_t idxs_len, void* ptr, kd_i64_t ptr_len, kd_u64_t item)
{
  kd_usize_t found_cnt, temp_found_cnt;

  if (!idxs || idxs_len <= 0 || !ptr || ptr_len <= 0)
  {
    return 0;
  }

  found_cnt = kdi_GenMemOpsFindAllBlocksWithIndex_U64(idxs, idxs_len * KD_SZ_USIZE, ptr, ptr_len * KD_SZ_U64, item);
  temp_found_cnt = found_cnt;

  while (temp_found_cnt--)
  {
    *idxs /= KD_SZ_U64;
    idxs = (kd_i64_t*)((kd_byte_t*)idxs + KD_SZ_USIZE);
  }

  return KD_I64_C(found_cnt);
}
#endif /* KD_ARCH_64BIT_INT */


kd_i32_t
kdMemOpsCmp(void* ptr1, void* ptr2, kd_i64_t len)
{
  return len < 0 ? 0 : kdGenMemOpsCmp(ptr1, ptr2, len);
}


kd_bool_t
kdMemOpsCat(void* dst, kd_i64_t dst_len, void* src1, kd_i64_t src1_len, void* src2, kd_i64_t src2_len)
{
  return dst_len < 0 || src1_len < 0 || src2_len < 0 ? 0 : kdGenMemOpsCat(dst, dst_len, src1, src1_len, src2, src2_len);
}


void*
kdMemOpsCompSpn(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
{
  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return kd_null;
  }
  return kdi_GenMemOpsBlocksCompSpnWithIndex_Byte(kd_null, ptr, len, keys, keys_len);
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
kdMemOpsSpn(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
{
  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return 0;
  }
  return kdi_GenMemOpsBlocksSpn_Byte(ptr, len, keys, keys_len);
}


kd_i64_t
kdMemOpsSpnU16(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
{
  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return 0;
  }
  return kdi_GenMemOpsBlocksSpn_U16(ptr, len * KD_SZ_U16, keys, keys_len * KD_SZ_U16) / KD_SZ_U16;
}


kd_i64_t
kdMemOpsSpnU32(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
{
  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return 0;
  }
  return kdi_GenMemOpsBlocksSpn_U32(ptr, len * KD_SZ_U32, keys, keys_len * KD_SZ_U32) / KD_SZ_U32;
}


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsSpnU64(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
{
  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return 0;
  }
  return kdi_GenMemOpsBlocksSpn_U64(ptr, len * KD_SZ_U64, keys, keys_len * KD_SZ_U64) / KD_SZ_U64;
}
#endif /* KD_ARCH_64BIT_INT */
