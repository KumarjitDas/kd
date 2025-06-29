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
kdMemOpsSwapU8(void *ptr, kd_word_t len, kd_word_t idx1, kd_word_t idx2)
{
  if (!ptr || len <= 0 || idx1 >= len || idx2 >= len)
  {
    return KD_RESULT_FAILURE;
  }

  idx1 += idx1 < 0 ? len : 0;
  idx2 += idx2 < 0 ? len : 0;

  kdi_GenMemOpsSwapBlocks_U8(ptr, idx1, idx2);

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsSwapU16(void *ptr, kd_word_t len, kd_word_t idx1, kd_word_t idx2)
{
  if (!ptr || len <= 0 || idx1 >= len || idx2 >= len)
  {
    return KD_RESULT_FAILURE;
  }

  idx1 += idx1 < 0 ? len : 0;
  idx2 += idx2 < 0 ? len : 0;

  kdi_GenMemOpsSwapBlocks_U16(ptr, KD_USIZE_C(idx1) * KD_SZ_U16, KD_USIZE_C(idx2) * KD_SZ_U16);

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsSwapU32(void *ptr, kd_word_t len, kd_word_t idx1, kd_word_t idx2)
{
  if (!ptr || len <= 0 || idx1 >= len || idx2 >= len)
  {
    return KD_RESULT_FAILURE;
  }

  idx1 += idx1 < 0 ? len : 0;
  idx2 += idx2 < 0 ? len : 0;

  kdi_GenMemOpsSwapBlocks_U32(ptr, KD_USIZE_C(idx1) * KD_SZ_U32, KD_USIZE_C(idx2) * KD_SZ_U32);

  return KD_RESULT_SUCCESS;
}


#if defined KD_ARCH_64BIT_INT
kd_bool_t
kdMemOpsSwapU64(void *ptr, kd_word_t len, kd_word_t idx1, kd_word_t idx2)
{
  if (!ptr || len <= 0 || idx1 >= len || idx2 >= len)
  {
    return KD_RESULT_FAILURE;
  }

  idx1 += idx1 < 0 ? len : 0;
  idx2 += idx2 < 0 ? len : 0;

  kdi_GenMemOpsSwapBlocks_U64(ptr, KD_USIZE_C(idx1) * KD_SZ_U64, KD_USIZE_C(idx2) * KD_SZ_U64);

  return KD_RESULT_SUCCESS;
}
#endif /* KD_ARCH_64BIT_INT */


kd_bool_t
kdMemOpsSwapN(void *ptr, kd_word_t len, kd_word_t n, kd_word_t idx1, kd_word_t idx2)
{
  if (len < 0 || n <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  idx1 += idx1 < 0 ? len : 0;
  idx2 += idx2 < 0 ? len : 0;

  return kdGenMemOpsSwapBlocks(ptr, KD_USIZE_C(len) * n, n, KD_USIZE_C(idx1) * n, KD_USIZE_C(idx2) * n);
}


kd_bool_t
kdMemOpsReverseU8(void *ptr, kd_word_t len)
{
  if (!ptr || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsReverseBlocks_U8(ptr, len);

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsReverseU16(void *ptr, kd_word_t len)
{
  if (!ptr || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsReverseBlocks_U16(ptr, KD_USIZE_C(len) * KD_SZ_U16);

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsReverseU32(void *ptr, kd_word_t len)
{
  if (!ptr || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsReverseBlocks_U32(ptr, KD_USIZE_C(len) * KD_SZ_U32);

  return KD_RESULT_SUCCESS;
}


#if defined KD_ARCH_64BIT_INT
kd_bool_t
kdMemOpsReverseU64(void *ptr, kd_word_t len)
{
  if (!ptr || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsReverseBlocks_U64(ptr, KD_USIZE_C(len) * KD_SZ_U64);

  return KD_RESULT_SUCCESS;
}
#endif /* KD_ARCH_64BIT_INT */


kd_bool_t
kdMemOpsReverseN(void *ptr, kd_word_t len, kd_word_t n)
{
  return (len < 0 || n <= 0) ? KD_RESULT_FAILURE : kdGenMemOpsReverseBlocks(ptr, KD_USIZE_C(len) * n, n);
}


kd_bool_t
kdMemOpsSetU8(void *ptr, kd_word_t len, kd_byte_t val)
{
  if (!ptr || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsSetBlocks_U8(ptr, len, val);

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsSetU16(void *ptr, kd_word_t len, kd_u16_t val)
{
  if (!ptr || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsSetBlocks_U16(ptr, KD_USIZE_C(len) * KD_SZ_U16, val);

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsSetU32(void *ptr, kd_word_t len, kd_u32_t val)
{
  if (!ptr || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsSetBlocks_U32(ptr, KD_USIZE_C(len) * KD_SZ_U32, val);

  return KD_RESULT_SUCCESS;
}


#if defined KD_ARCH_64BIT_INT
kd_bool_t
kdMemOpsSetU64(void *ptr, kd_word_t len, kd_u64_t val)
{
  if (!ptr || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsSetBlocks_U64(ptr, KD_USIZE_C(len) * KD_SZ_U64, val);

  return KD_RESULT_SUCCESS;
}
#endif /* KD_ARCH_64BIT_INT */


kd_bool_t
kdMemOpsSetN(void *ptr, kd_word_t len, void *nval, kd_word_t n)
{
  return (len < 0 || n <= 0) ? KD_RESULT_FAILURE : kdGenMemOpsSetBlocks(ptr, KD_USIZE_C(len) * n, nval, n);
}


kd_bool_t
kdMemOpsCpyU8(void *dst, void *src, kd_word_t len)
{
  return len < 0 ? KD_RESULT_FAILURE : kdGenMemOpsCpy(dst, src, len);
}


kd_bool_t
kdMemOpsCpyU16(void *dst, void *src, kd_word_t len)
{
  return len < 0 ? KD_RESULT_FAILURE : kdGenMemOpsCpy(dst, src, KD_USIZE_C(len) * KD_SZ_U16);
}


kd_bool_t
kdMemOpsCpyU32(void *dst, void *src, kd_word_t len)
{
  return len < 0 ? KD_RESULT_FAILURE : kdGenMemOpsCpy(dst, src, KD_USIZE_C(len) * KD_SZ_U32);
}


#if defined KD_ARCH_64BIT_INT
kd_bool_t
kdMemOpsCpyU64(void *dst, void *src, kd_word_t len)
{
  return len < 0 ? KD_RESULT_FAILURE : kdGenMemOpsCpy(dst, src, KD_USIZE_C(len) * KD_SZ_U64);
}
#endif /* KD_ARCH_64BIT_INT */


kd_bool_t
kdMemOpsCpyN(void *dst, void *src, kd_word_t len, kd_word_t n)
{
  return (len < 0 || n <= 0) ? KD_RESULT_FAILURE : kdGenMemOpsCpy(dst, src, KD_USIZE_C(len) * n);
}


kd_bool_t
kdMemOpsMoveU8(void *dst, void *src, kd_word_t len)
{
  return len < 0 ? KD_RESULT_FAILURE : kdGenMemOpsMove(dst, src, len);
}


kd_bool_t
kdMemOpsMoveU16(void *dst, void *src, kd_word_t len)
{
  return len < 0 ? KD_RESULT_FAILURE : kdGenMemOpsMove(dst, src, KD_USIZE_C(len) * KD_SZ_U16);
}


kd_bool_t
kdMemOpsMoveU32(void *dst, void *src, kd_word_t len)
{
  return len < 0 ? KD_RESULT_FAILURE : kdGenMemOpsMove(dst, src, KD_USIZE_C(len) * KD_SZ_U32);
}


#if defined KD_ARCH_64BIT_INT
kd_bool_t
kdMemOpsMoveU64(void *dst, void *src, kd_word_t len)
{
  return len < 0 ? KD_RESULT_FAILURE : kdGenMemOpsMove(dst, src, KD_USIZE_C(len) * KD_SZ_U64);
}
#endif /* KD_ARCH_64BIT_INT */


kd_bool_t
kdMemOpsMoveN(void *dst, void *src, kd_word_t len, kd_word_t n)
{
  return (len < 0 || n <= 0) ? KD_RESULT_FAILURE : kdGenMemOpsMove(dst, src, KD_USIZE_C(len) * n);
}


void *
kdMemOpsFindU8(void *ptr, kd_word_t len, kd_byte_t item)
{
  return (!ptr || len <= 0) ? kd_null : kdi_GenMemOpsFindBlockWithIndex_U8(kd_null, ptr, len, item);
}


void *
kdMemOpsFindU16(void *ptr, kd_word_t len, kd_u16_t item)
{
  return (!ptr || len <= 0) ? kd_null : kdi_GenMemOpsFindBlockWithIndex_U16(kd_null, ptr, KD_USIZE_C(len) * KD_SZ_U16, item);
}


void *
kdMemOpsFindU32(void *ptr, kd_word_t len, kd_u32_t item)
{
  return (!ptr || len <= 0) ? kd_null : kdi_GenMemOpsFindBlockWithIndex_U32(kd_null, ptr, KD_USIZE_C(len) * KD_SZ_U32, item);
}


#if defined KD_ARCH_64BIT_INT
void *
kdMemOpsFindU64(void *ptr, kd_word_t len, kd_u64_t item)
{
  return (!ptr || len <= 0) ? kd_null : kdi_GenMemOpsFindBlockWithIndex_U64(kd_null, ptr, KD_USIZE_C(len) * KD_SZ_U64, item);
}
#endif /* KD_ARCH_64BIT_INT */


void *
kdMemOpsFindN(void *ptr, kd_word_t len, void *nitem, kd_word_t n)
{
  return (!ptr || len <= 0 || n < 0) ? kd_null : kdGenMemOpsFindBlock(ptr, KD_USIZE_C(len) * n, nitem, n);
}


kd_word_t
kdMemOpsFindIndexU8(void *ptr, kd_word_t len, kd_byte_t item)
{
  kd_usize_t idx;
  return (ptr && len > 0 && kdi_GenMemOpsFindBlockWithIndex_U8(&idx, ptr, len, item)) ? KD_WORD_C(idx) : -1;
}


kd_word_t
kdMemOpsFindIndexU16(void *ptr, kd_word_t len, kd_u16_t item)
{
  kd_usize_t idx;
  return (ptr && len > 0 && kdi_GenMemOpsFindBlockWithIndex_U16(&idx, ptr, KD_USIZE_C(len) * KD_SZ_U16, item)) ? KD_WORD_C(idx / KD_SZ_U16) : -1;
}


kd_word_t
kdMemOpsFindIndexU32(void *ptr, kd_word_t len, kd_u32_t item)
{
  kd_usize_t idx;
  return (ptr && len > 0 && kdi_GenMemOpsFindBlockWithIndex_U32(&idx, ptr, KD_USIZE_C(len) * KD_SZ_U32, item)) ? KD_WORD_C(idx / KD_SZ_U32) : -1;
}


#if defined KD_ARCH_64BIT_INT
kd_word_t
kdMemOpsFindIndexU64(void *ptr, kd_word_t len, kd_u64_t item)
{
  kd_usize_t idx;
  return (ptr && len > 0 && kdi_GenMemOpsFindBlockWithIndex_U64(&idx, ptr, KD_USIZE_C(len) * KD_SZ_U64, item)) ? KD_WORD_C(idx / KD_SZ_U64) : -1;
}
#endif /* KD_ARCH_64BIT_INT */


kd_word_t
kdMemOpsFindIndexN(void *ptr, kd_word_t len, void *nitem, kd_word_t n)
{
  kd_usize_t idx;
  return (ptr && len > 0 && n > 0 && kdGenMemOpsFindBlockIndex(&idx, ptr, KD_USIZE_C(len) * n, nitem, n)) ? KD_WORD_C(idx / n) : -1;
}


void *
kdMemOpsFindLastU8(void *ptr, kd_word_t len, kd_byte_t item)
{
  return (!ptr || len <= 0) ? kd_null : kdi_GenMemOpsFindLastBlockWithIndex_U8(kd_null, ptr, len, item);
}


void *
kdMemOpsFindLastU16(void *ptr, kd_word_t len, kd_u16_t item)
{
  return (!ptr || len <= 0) ? kd_null : kdi_GenMemOpsFindLastBlockWithIndex_U16(kd_null, ptr, KD_USIZE_C(len) * KD_SZ_U16, item);
}


void *
kdMemOpsFindLastU32(void *ptr, kd_word_t len, kd_u32_t item)
{
  return (!ptr || len <= 0) ? kd_null : kdi_GenMemOpsFindLastBlockWithIndex_U32(kd_null, ptr, KD_USIZE_C(len) * KD_SZ_U32, item);
}


#if defined KD_ARCH_64BIT_INT
void *
kdMemOpsFindLastU64(void *ptr, kd_word_t len, kd_u64_t item)
{
  return (!ptr || len <= 0) ? kd_null : kdi_GenMemOpsFindLastBlockWithIndex_U64(kd_null, ptr, KD_USIZE_C(len) * KD_SZ_U64, item);
}
#endif /* KD_ARCH_64BIT_INT */


void *
kdMemOpsFindLastN(void *ptr, kd_word_t len, void *nitem, kd_word_t n)
{
  return (!ptr || len < 0 || n < 0) ? kd_null : kdGenMemOpsFindLastBlock(ptr, KD_USIZE_C(len) * n, nitem, n);
}


kd_word_t
kdMemOpsFindLastIndexU8(void *ptr, kd_word_t len, kd_byte_t item)
{
  kd_usize_t idx;
  return (ptr && len > 0 && kdi_GenMemOpsFindLastBlockWithIndex_U8(&idx, ptr, len, item)) ? KD_WORD_C(idx) : -1;
}


kd_word_t
kdMemOpsFindLastIndexU16(void *ptr, kd_word_t len, kd_u16_t item)
{
  kd_usize_t idx;
  return (ptr && len > 0 && kdi_GenMemOpsFindLastBlockWithIndex_U16(&idx, ptr, KD_USIZE_C(len) * KD_SZ_U16, item)) ? KD_WORD_C(idx / KD_SZ_U16) : -1;
}


kd_word_t
kdMemOpsFindLastIndexU32(void *ptr, kd_word_t len, kd_u32_t item)
{
  kd_usize_t idx;
  return (ptr && len > 0 && kdi_GenMemOpsFindLastBlockWithIndex_U32(&idx, ptr, KD_USIZE_C(len) * KD_SZ_U32, item)) ? KD_WORD_C(idx / KD_SZ_U32) : -1;
}


#if defined KD_ARCH_64BIT_INT
kd_word_t
kdMemOpsFindLastIndexU64(void *ptr, kd_word_t len, kd_u64_t item)
{
  kd_usize_t idx;
  return (ptr && len > 0 && kdi_GenMemOpsFindLastBlockWithIndex_U64(&idx, ptr, KD_USIZE_C(len) * KD_SZ_U64, item)) ? KD_WORD_C(idx / KD_SZ_U64) : -1;
}
#endif /* KD_ARCH_64BIT_INT */


kd_word_t
kdMemOpsFindLastIndexN(void *ptr, kd_word_t len, void *nitem, kd_word_t n)
{
  kd_usize_t idx;
  return (len > 0 && n > 0 && kdGenMemOpsFindLastBlockIndex(&idx, ptr, KD_USIZE_C(len) * n, nitem, n)) ? KD_WORD_C(idx / n) : -1;
}


kd_word_t
kdMemOpsFindAllU8(void *dst, kd_word_t dst_len, void *ptr, kd_word_t ptr_len, kd_byte_t item)
{
  return (!dst || dst_len <= 0 || !ptr || ptr_len <= 0) ? 0 : KD_WORD_C(kdi_GenMemOpsFindAllBlocks_U8(dst, KD_USIZE_C(dst_len) * KD_SZ_U8, ptr, KD_USIZE_C(ptr_len) * KD_SZ_U8, item));
}


kd_word_t
kdMemOpsFindAllU16(void *dst, kd_word_t dst_len, void *ptr, kd_word_t ptr_len, kd_u16_t item)
{
  return (!dst || dst_len <= 0 || !ptr || ptr_len <= 0) ? 0 : KD_WORD_C(kdi_GenMemOpsFindAllBlocks_U16(dst, KD_USIZE_C(dst_len) * KD_SZ_U16, ptr, KD_USIZE_C(ptr_len) * KD_SZ_U16, item));
}


kd_word_t
kdMemOpsFindAllU32(void *dst, kd_word_t dst_len, void *ptr, kd_word_t ptr_len, kd_u32_t item)
{
  return (!dst || dst_len <= 0 || !ptr || ptr_len <= 0) ? 0 : KD_WORD_C(kdi_GenMemOpsFindAllBlocks_U32(dst, KD_USIZE_C(dst_len) * KD_SZ_U32, ptr, KD_USIZE_C(ptr_len) * KD_SZ_U32, item));
}


#if defined KD_ARCH_64BIT_INT
kd_word_t
kdMemOpsFindAllU64(void *dst, kd_word_t dst_len, void *ptr, kd_word_t ptr_len, kd_u64_t item)
{
  return (!dst || dst_len <= 0 || !ptr || ptr_len <= 0) ? 0 : KD_WORD_C(kdi_GenMemOpsFindAllBlocks_U64(dst, KD_USIZE_C(dst_len) * KD_SZ_U64, ptr, KD_USIZE_C(ptr_len) * KD_SZ_U64, item));
}
#endif /* KD_ARCH_64BIT_INT */


kd_word_t
kdMemOpsFindAllN(void *dst, kd_word_t dst_len, void *ptr, kd_word_t ptr_len, void *nitem, kd_word_t n)
{
  return (dst_len < 0 || ptr_len < 0 || n <= 0) ? 0 : KD_WORD_C(kdGenMemOpsFindAllBlocks(dst, KD_USIZE_C(dst_len) * n, ptr, KD_USIZE_C(ptr_len) * n, nitem, n));
}


kd_word_t
kdMemOpsFindAllIndicesU8(void *idxs, enum kd_eltype_t idx_type, kd_word_t idxs_len, void *ptr, kd_word_t ptr_len, kd_byte_t item)
{
  if (!idxs || idxs_len <= 0 || !ptr || ptr_len <= 0)
  {
    return 0;
  }

  idx_type = idx_type <= 0 ? KD_ELTYPE_WORD : idx_type;

  switch (idx_type)
  {
    case KD_ELTYPE_BYTE:
    case KD_ELTYPE_I8:
    case KD_ELTYPE_U8:
    case KD_ELTYPE_IMIN:
    case KD_ELTYPE_UMIN:
      return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U8_Idx8(idxs, idxs_len, ptr, ptr_len, item, kd_true));

    case KD_ELTYPE_I16:
    case KD_ELTYPE_U16:
      return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U8_Idx16(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U16, ptr, ptr_len, item, kd_true));

    case KD_ELTYPE_I32:
    case KD_ELTYPE_U32:
    case KD_ELTYPE_BOOL:
    case KD_ELTYPE_CHR:
      return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U8_Idx32(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U32, ptr, ptr_len, item, kd_true));

#if defined KD_ARCH_64BIT_INT
    case KD_ELTYPE_I64:
    case KD_ELTYPE_U64:
#endif
    case KD_ELTYPE_UMAX:
    case KD_ELTYPE_IMAX:
    case KD_ELTYPE_WORD:
    case KD_ELTYPE_USIZE:
    case KD_ELTYPE_PTR:
#if defined KD_ARCH_64BIT_INT
      return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U8_Idx64(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U64, ptr, ptr_len, item, kd_true));
#else
      return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U8_Idx32(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U32, ptr, ptr_len, item, kd_true));
#endif

    default:;
  }

  return 0;
}


kd_word_t
kdMemOpsFindAllIndicesU16(void *idxs, enum kd_eltype_t idx_type, kd_word_t idxs_len, void *ptr, kd_word_t ptr_len, kd_u16_t item)
{
  if (!idxs || idxs_len <= 0 || !ptr || ptr_len <= 0)
  {
    return 0;
  }

  idx_type = idx_type <= 0 ? KD_ELTYPE_WORD : idx_type;

  switch (idx_type)
  {
    case KD_ELTYPE_BYTE:
    case KD_ELTYPE_I8:
    case KD_ELTYPE_U8:
    case KD_ELTYPE_IMIN:
    case KD_ELTYPE_UMIN:
      return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U16_Idx8(idxs, idxs_len, ptr, KD_USIZE_C(ptr_len) * KD_SZ_S16, item, kd_true));

    case KD_ELTYPE_I16:
    case KD_ELTYPE_U16:
      return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U16_Idx16(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U16, ptr, KD_USIZE_C(ptr_len) * KD_SZ_S16, item, kd_true));

    case KD_ELTYPE_I32:
    case KD_ELTYPE_U32:
    case KD_ELTYPE_BOOL:
    case KD_ELTYPE_CHR:
      return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U16_Idx32(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U32, ptr, KD_USIZE_C(ptr_len) * KD_SZ_S16, item, kd_true));

#if defined KD_ARCH_64BIT_INT
    case KD_ELTYPE_I64:
    case KD_ELTYPE_U64:
#endif
    case KD_ELTYPE_UMAX:
    case KD_ELTYPE_IMAX:
    case KD_ELTYPE_WORD:
    case KD_ELTYPE_USIZE:
    case KD_ELTYPE_PTR:
#if defined KD_ARCH_64BIT_INT
      return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U16_Idx64(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U64, ptr, KD_USIZE_C(ptr_len) * KD_SZ_S16, item, kd_true));
#else
      return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U16_Idx32(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U32, ptr, KD_USIZE_C(ptr_len) * KD_SZ_S16, item, kd_true));
#endif

    default:;
  }

  return 0;
}


kd_word_t
kdMemOpsFindAllIndicesU32(void *idxs, enum kd_eltype_t idx_type, kd_word_t idxs_len, void *ptr, kd_word_t ptr_len, kd_u32_t item)
{
  if (!idxs || idxs_len <= 0 || !ptr || ptr_len <= 0)
  {
    return 0;
  }

  idx_type = idx_type <= 0 ? KD_ELTYPE_WORD : idx_type;

  switch (idx_type)
  {
    case KD_ELTYPE_BYTE:
    case KD_ELTYPE_I8:
    case KD_ELTYPE_U8:
    case KD_ELTYPE_IMIN:
    case KD_ELTYPE_UMIN:
      return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U32_Idx8(idxs, idxs_len, ptr, KD_USIZE_C(ptr_len) * KD_SZ_S32, item, kd_true));

    case KD_ELTYPE_I16:
    case KD_ELTYPE_U16:
      return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U32_Idx16(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U16, ptr, KD_USIZE_C(ptr_len) * KD_SZ_S32, item, kd_true));

    case KD_ELTYPE_I32:
    case KD_ELTYPE_U32:
    case KD_ELTYPE_BOOL:
    case KD_ELTYPE_CHR:
      return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U32_Idx32(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U32, ptr, KD_USIZE_C(ptr_len) * KD_SZ_S32, item, kd_true));

#if defined KD_ARCH_64BIT_INT
    case KD_ELTYPE_I64:
    case KD_ELTYPE_U64:
#endif
    case KD_ELTYPE_UMAX:
    case KD_ELTYPE_IMAX:
    case KD_ELTYPE_WORD:
    case KD_ELTYPE_USIZE:
    case KD_ELTYPE_PTR:
#if defined KD_ARCH_64BIT_INT
      return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U32_Idx64(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U64, ptr, KD_USIZE_C(ptr_len) * KD_SZ_S32, item, kd_true));
#else
      return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U32_Idx32(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U32, ptr, KD_USIZE_C(ptr_len) * KD_SZ_S32, item, kd_true));
#endif

    default:;
  }

  return 0;
}


#if defined KD_ARCH_64BIT_INT
kd_word_t
kdMemOpsFindAllIndicesU64(void *idxs, enum kd_eltype_t idx_type, kd_word_t idxs_len, void *ptr, kd_word_t ptr_len, kd_u64_t item)
{
  if (!idxs || idxs_len <= 0 || !ptr || ptr_len <= 0)
  {
    return 0;
  }

  idx_type = idx_type <= 0 ? KD_ELTYPE_WORD : idx_type;

  switch (idx_type)
  {
    case KD_ELTYPE_BYTE:
    case KD_ELTYPE_I8:
    case KD_ELTYPE_U8:
    case KD_ELTYPE_IMIN:
    case KD_ELTYPE_UMIN:
      return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U64_Idx8(idxs, idxs_len, ptr, KD_USIZE_C(ptr_len) * KD_SZ_S64, item, kd_true));

    case KD_ELTYPE_I16:
    case KD_ELTYPE_U16:
      return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U64_Idx16(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U16, ptr, KD_USIZE_C(ptr_len) * KD_SZ_S64, item, kd_true));

    case KD_ELTYPE_I32:
    case KD_ELTYPE_U32:
    case KD_ELTYPE_BOOL:
    case KD_ELTYPE_CHR:
      return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U64_Idx32(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U32, ptr, KD_USIZE_C(ptr_len) * KD_SZ_S64, item, kd_true));

    case KD_ELTYPE_I64:
    case KD_ELTYPE_U64:
    case KD_ELTYPE_UMAX:
    case KD_ELTYPE_IMAX:
    case KD_ELTYPE_WORD:
    case KD_ELTYPE_USIZE:
    case KD_ELTYPE_PTR:
      return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U64_Idx64(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U64, ptr, KD_USIZE_C(ptr_len) * KD_SZ_S64, item, kd_true));

    default:;
  }

  return 0;
}
#endif /* KD_ARCH_64BIT_INT */


kd_word_t
kdMemOpsFindAllIndicesN(void *idxs, enum kd_eltype_t idx_type, kd_word_t idxs_len, void *ptr, kd_word_t ptr_len, void *nitem, kd_word_t n)
{
  if (!idxs || idxs_len <= 0 || !ptr || ptr_len <= 0 || !nitem || n <= 0)
  {
    return 0;
  }

  idx_type = idx_type <= 0 ? KD_ELTYPE_WORD : idx_type;

  switch (idx_type)
  {
    case KD_ELTYPE_BYTE:
    case KD_ELTYPE_I8:
    case KD_ELTYPE_U8:
    case KD_ELTYPE_IMIN:
    case KD_ELTYPE_UMIN:
      return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_Sn_Idx8(idxs, idxs_len, ptr, KD_USIZE_C(ptr_len) * n, nitem, n, kd_true));

    case KD_ELTYPE_I16:
    case KD_ELTYPE_U16:
      return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_Sn_Idx16(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U16, ptr, KD_USIZE_C(ptr_len) * n, nitem, n, kd_true));

    case KD_ELTYPE_I32:
    case KD_ELTYPE_U32:
    case KD_ELTYPE_BOOL:
    case KD_ELTYPE_CHR:
      return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_Sn_Idx32(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U32, ptr, KD_USIZE_C(ptr_len) * n, nitem, n, kd_true));

#if defined KD_ARCH_64BIT_INT
    case KD_ELTYPE_I64:
    case KD_ELTYPE_U64:
#endif
    case KD_ELTYPE_UMAX:
    case KD_ELTYPE_IMAX:
    case KD_ELTYPE_WORD:
    case KD_ELTYPE_USIZE:
    case KD_ELTYPE_PTR:
#if defined KD_ARCH_64BIT_INT
      return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_Sn_Idx64(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U64, ptr, KD_USIZE_C(ptr_len) * n, nitem, n, kd_true));
#else
      return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_Sn_Idx32(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U32, ptr, KD_USIZE_C(ptr_len) * n, nitem, n, kd_true));
#endif

    default:;
  }

  return 0;
}


kd_word_t
kdMemOpsCmpU8(void *ptr1, void *ptr2, kd_word_t len)
{
  return len < 0 ? 0 : kdGenMemOpsCmp(ptr1, ptr2, len);
}


kd_word_t
kdMemOpsCmpU16(void *ptr1, void *ptr2, kd_word_t len)
{
  return len < 0 ? 0 : kdGenMemOpsCmp(ptr1, ptr2, KD_USIZE_C(len) * KD_SZ_U16);
}


kd_word_t
kdMemOpsCmpU32(void *ptr1, void *ptr2, kd_word_t len)
{
  return len < 0 ? 0 : kdGenMemOpsCmp(ptr1, ptr2, KD_USIZE_C(len) * KD_SZ_U32);
}


#if defined KD_ARCH_64BIT_INT
kd_word_t
kdMemOpsCmpU64(void *ptr1, void *ptr2, kd_word_t len)
{
  return len < 0 ? 0 : kdGenMemOpsCmp(ptr1, ptr2, KD_USIZE_C(len) * KD_SZ_U64);
}
#endif


kd_word_t
kdMemOpsCmpN(void *ptr1, void *ptr2, kd_word_t len, kd_word_t n)
{
  return len < 0 || n <= 0 ? 0 : kdGenMemOpsCmp(ptr1, ptr2, KD_USIZE_C(len) * n);
}


kd_bool_t
kdMemOpsCatU8(void *dst, kd_word_t dst_len, void *src1, kd_word_t src1_len, void *src2, kd_word_t src2_len)
{
  return dst_len < 0 || src1_len < 0 || src2_len < 0 ? 0 : kdGenMemOpsCat(dst, dst_len, src1, src1_len, src2, src2_len);
}


kd_bool_t
kdMemOpsCatU16(void *dst, kd_word_t dst_len, void *src1, kd_word_t src1_len, void *src2, kd_word_t src2_len)
{
  return dst_len < 0 || src1_len < 0 || src2_len < 0 ? 0 : kdGenMemOpsCat(dst, KD_USIZE_C(dst_len) * KD_SZ_U16, src1, KD_USIZE_C(src1_len) * KD_SZ_U16, src2, KD_USIZE_C(src2_len) * KD_SZ_U16);
}


kd_bool_t
kdMemOpsCatU32(void *dst, kd_word_t dst_len, void *src1, kd_word_t src1_len, void *src2, kd_word_t src2_len)
{
  return dst_len < 0 || src1_len < 0 || src2_len < 0 ? 0 : kdGenMemOpsCat(dst, KD_USIZE_C(dst_len) * KD_SZ_U32, src1, KD_USIZE_C(src1_len) * KD_SZ_U32, src2, KD_USIZE_C(src2_len) * KD_SZ_U32);
}


#if defined KD_ARCH_64BIT_INT
kd_bool_t
kdMemOpsCatU64(void *dst, kd_word_t dst_len, void *src1, kd_word_t src1_len, void *src2, kd_word_t src2_len)
{
  return dst_len < 0 || src1_len < 0 || src2_len < 0 ? 0 : kdGenMemOpsCat(dst, KD_USIZE_C(dst_len) * KD_SZ_U64, src1, KD_USIZE_C(src1_len) * KD_SZ_U64, src2, KD_USIZE_C(src2_len) * KD_SZ_U64);
}
#endif


kd_bool_t
kdMemOpsCatN(void *dst, kd_word_t dst_len, void *src1, kd_word_t src1_len, void *src2, kd_word_t src2_len, kd_word_t n)
{
  return dst_len < 0 || src1_len < 0 || src2_len < 0 ? 0 : kdGenMemOpsCat(dst, KD_USIZE_C(dst_len) * n, src1, KD_USIZE_C(src1_len) * n, src2, KD_USIZE_C(src2_len) * n);
}


void *
kdMemOpsCompSpnU8(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len)
{
  return (!ptr || !keys || len <= 0 || keys_len <= 0) ? kd_null : kdi_GenMemOpsBlocksCompSpnWithIndex_U8(kd_null, ptr, len, keys, keys_len);
}


void *
kdMemOpsCompSpnU16(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len)
{
  return (!ptr || !keys || len <= 0 || keys_len <= 0) ? kd_null : kdi_GenMemOpsBlocksCompSpnWithIndex_U16(kd_null, ptr, KD_USIZE_C(len) * KD_SZ_U16, keys, KD_USIZE_C(keys_len) * KD_SZ_U16);
}


void *
kdMemOpsCompSpnU32(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len)
{
  return (!ptr || !keys || len <= 0 || keys_len <= 0) ? kd_null : kdi_GenMemOpsBlocksCompSpnWithIndex_U32(kd_null, ptr, KD_USIZE_C(len) * KD_SZ_U32, keys, KD_USIZE_C(keys_len) * KD_SZ_U32);
}


#if defined KD_ARCH_64BIT_INT
void *
kdMemOpsCompSpnU64(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len)
{
  return (!ptr || !keys || len <= 0 || keys_len <= 0) ? kd_null : kdi_GenMemOpsBlocksCompSpnWithIndex_U64(kd_null, ptr, KD_USIZE_C(len) * KD_SZ_U64, keys, KD_USIZE_C(keys_len) * KD_SZ_U64);
}
#endif /* KD_ARCH_64BIT_INT */


void *
kdMemOpsCompSpnN(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len, kd_word_t n)
{
  return (len < 0 || keys_len < 0 || n <= 0) ? kd_null : kdGenMemOpsBlocksCompSpn(ptr, KD_USIZE_C(len) * n, keys, n, KD_USIZE_C(keys_len) * n);
}


kd_word_t
kdMemOpsCompSpnIndexU8(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len)
{
  kd_usize_t idx;
  return (ptr && len > 0 && keys && keys_len >= 0 && kdi_GenMemOpsBlocksCompSpnWithIndex_U8(&idx, ptr, len, keys, keys_len)) ? KD_WORD_C(idx) : -1;
}


kd_word_t
kdMemOpsCompSpnIndexU16(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len)
{
  kd_usize_t idx;
  return (ptr && len > 0 && keys && keys_len >= 0 && kdi_GenMemOpsBlocksCompSpnWithIndex_U16(&idx, ptr, KD_USIZE_C(len) * KD_SZ_U16, keys, KD_USIZE_C(keys_len) * KD_SZ_U16)) ? KD_WORD_C(idx / KD_SZ_U16) : -1;
}


kd_word_t
kdMemOpsCompSpnIndexU32(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len)
{
  kd_usize_t idx;
  return (ptr && len > 0 && keys && keys_len >= 0 && kdi_GenMemOpsBlocksCompSpnWithIndex_U32(&idx, ptr, KD_USIZE_C(len) * KD_SZ_U32, keys, KD_USIZE_C(keys_len) * KD_SZ_U32)) ? KD_WORD_C(idx / KD_SZ_U32) : -1;
}


#if defined KD_ARCH_64BIT_INT
kd_word_t
kdMemOpsCompSpnIndexU64(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len)
{
  kd_usize_t idx;
  return (ptr && len > 0 && keys && keys_len >= 0 && kdi_GenMemOpsBlocksCompSpnWithIndex_U64(&idx, ptr, KD_USIZE_C(len) * KD_SZ_U64, keys, KD_USIZE_C(keys_len) * KD_SZ_U64)) ? KD_WORD_C(idx / KD_SZ_U64) : -1;
}
#endif /* KD_ARCH_64BIT_INT */


kd_word_t
kdMemOpsCompSpnIndexN(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len, kd_word_t n)
{
  kd_usize_t idx;
  return (len > 0 && keys_len > 0 && n > 0 && kdGenMemOpsBlocksCompSpnIndex(&idx, ptr, KD_USIZE_C(len) * n, keys, n, KD_USIZE_C(keys_len) * n)) ? KD_WORD_C(idx / n) : -1;
}


kd_word_t
kdMemOpsSpnU8(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len)
{
  return (!ptr || !keys || len <= 0 || keys_len <= 0) ? 0 : KD_WORD_C(kdi_GenMemOpsBlocksSpn_U8(ptr, len, keys, keys_len));
}


kd_word_t
kdMemOpsSpnU16(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len)
{
  return (!ptr || !keys || len <= 0 || keys_len <= 0) ? 0 : KD_WORD_C(kdi_GenMemOpsBlocksSpn_U16(ptr, KD_USIZE_C(len) * KD_SZ_U16, keys, KD_USIZE_C(keys_len) * KD_SZ_U16) / KD_SZ_U16);
}


kd_word_t
kdMemOpsSpnU32(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len)
{
  return (!ptr || !keys || len <= 0 || keys_len <= 0) ? 0 : KD_WORD_C(kdi_GenMemOpsBlocksSpn_U32(ptr, KD_USIZE_C(len) * KD_SZ_U32, keys, KD_USIZE_C(keys_len) * KD_SZ_U32) / KD_SZ_U32);
}


#if defined KD_ARCH_64BIT_INT
kd_word_t
kdMemOpsSpnU64(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len)
{
  return (!ptr || !keys || len <= 0 || keys_len <= 0) ? 0 : KD_WORD_C(kdi_GenMemOpsBlocksSpn_U64(ptr, KD_USIZE_C(len) * KD_SZ_U64, keys, KD_USIZE_C(keys_len) * KD_SZ_U64) / KD_SZ_U64);
}
#endif /* KD_ARCH_64BIT_INT */


kd_word_t
kdMemOpsSpnN(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len, kd_word_t n)
{
  return (len < 0 || keys_len < 0 || n <= 0) ? 0 : KD_WORD_C(kdGenMemOpsBlocksSpn(ptr, KD_USIZE_C(len) * n, keys, n, KD_USIZE_C(keys_len) * n) / n);
}
