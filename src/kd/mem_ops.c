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
#if defined KD_ARCH_64BIT_INT
kdMemOpsSwap(void* ptr, kd_i64_t len, kd_i64_t idx1, kd_i64_t idx2)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsSwap(void* ptr, kd_i32_t len, kd_i32_t idx1, kd_i32_t idx2)
#endif /* KD_ARCH_64BIT_INT */
{
  if (!ptr || len <= 0 || idx1 < 0 || idx2 < 0 || idx1 >= len || idx2 >= len)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsSwapBlocks_Byte(ptr, idx1, idx2);

  return KD_RESULT_SUCCESS;
}


kd_bool_t
#if defined KD_ARCH_64BIT_INT
kdMemOpsSwapU16(void* ptr, kd_i64_t len, kd_i64_t idx1, kd_i64_t idx2)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsSwapU16(void* ptr, kd_i32_t len, kd_i32_t idx1, kd_i32_t idx2)
#endif /* KD_ARCH_64BIT_INT */
{
  if (!ptr || len <= 0 || idx1 < 0 || idx2 < 0 || idx1 >= len || idx2 >= len)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsSwapBlocks_U16(ptr, idx1 * KD_SZ_U16, idx2 * KD_SZ_U16);

  return KD_RESULT_SUCCESS;
}


kd_bool_t
#if defined KD_ARCH_64BIT_INT
kdMemOpsSwapU32(void* ptr, kd_i64_t len, kd_i64_t idx1, kd_i64_t idx2)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsSwapU32(void* ptr, kd_i32_t len, kd_i32_t idx1, kd_i32_t idx2)
#endif /* KD_ARCH_64BIT_INT */
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
#if defined KD_ARCH_64BIT_INT
kdMemOpsSwapN(void* ptr, kd_i64_t len, kd_i64_t n, kd_i64_t idx1, kd_i64_t idx2)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsSwapN(void* ptr, kd_i32_t len, kd_i32_t n, kd_i32_t idx1, kd_i32_t idx2)
#endif /* KD_ARCH_64BIT_INT */
{
  if (len < 0 || n <= 0 || idx1 < 0 || idx2 < 0)
  {
    return KD_RESULT_FAILURE;
  }
  return kdGenMemOpsSwapBlocks(ptr, len * n, n, idx1 * n, idx2 * n);
}


kd_bool_t
#if defined KD_ARCH_64BIT_INT
kdMemOpsReverse(void* ptr, kd_i64_t len)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsReverse(void* ptr, kd_i32_t len)
#endif /* KD_ARCH_64BIT_INT */
{
  if (!ptr || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsReverseBlocks_Byte(ptr, len);

  return KD_RESULT_SUCCESS;
}


kd_bool_t
#if defined KD_ARCH_64BIT_INT
kdMemOpsReverseU16(void* ptr, kd_i64_t len)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsReverseU16(void* ptr, kd_i32_t len)
#endif /* KD_ARCH_64BIT_INT */
{
  if (!ptr || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsReverseBlocks_U16(ptr, len * KD_SZ_U16);

  return KD_RESULT_SUCCESS;
}


kd_bool_t
#if defined KD_ARCH_64BIT_INT
kdMemOpsReverseU32(void* ptr, kd_i64_t len)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsReverseU32(void* ptr, kd_i32_t len)
#endif /* KD_ARCH_64BIT_INT */
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
#if defined KD_ARCH_64BIT_INT
kdMemOpsReverseN(void* ptr, kd_i64_t len, kd_i64_t n)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsReverseN(void* ptr, kd_i32_t len, kd_i32_t n)
#endif /* KD_ARCH_64BIT_INT */
{
  if (len < 0 || n <= 0)
  {
    return KD_RESULT_FAILURE;
  }
  return kdGenMemOpsReverseBlocks(ptr, len * n, n);
}


kd_bool_t
#if defined KD_ARCH_64BIT_INT
kdMemOpsSet(void* ptr, kd_i64_t len, kd_byte_t val)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsSet(void* ptr, kd_i32_t len, kd_byte_t val)
#endif /* KD_ARCH_64BIT_INT */
{
  if (!ptr || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsSetBlocks_Byte(ptr, len, val);

  return KD_RESULT_SUCCESS;
}


kd_bool_t
#if defined KD_ARCH_64BIT_INT
kdMemOpsSetU16(void* ptr, kd_i64_t len, kd_u16_t val)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsSetU16(void* ptr, kd_i32_t len, kd_u16_t val)
#endif /* KD_ARCH_64BIT_INT */
{
  if (!ptr || len <= 0)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsSetBlocks_U16(ptr, len * KD_SZ_U16, val);

  return KD_RESULT_SUCCESS;
}


kd_bool_t
#if defined KD_ARCH_64BIT_INT
kdMemOpsSetU32(void* ptr, kd_i64_t len, kd_u32_t val)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsSetU32(void* ptr, kd_i32_t len, kd_u32_t val)
#endif /* KD_ARCH_64BIT_INT */
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
#if defined KD_ARCH_64BIT_INT
kdMemOpsSetN(void* ptr, kd_i64_t len, void* nval, kd_i64_t n)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsSetN(void* ptr, kd_i32_t len, void* nval, kd_i32_t n)
#endif /* KD_ARCH_64BIT_INT */
{
  if (len < 0 || n <= 0)
  {
    return KD_RESULT_FAILURE;
  }
  return kdGenMemOpsSetBlocks(ptr, len * n, nval, n);
}


kd_bool_t
#if defined KD_ARCH_64BIT_INT
kdMemOpsCpy(void* dst, void* src, kd_i64_t len)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsCpy(void* dst, void* src, kd_i32_t len)
#endif /* KD_ARCH_64BIT_INT */
{
  return len < 0 ? KD_RESULT_FAILURE : kdGenMemOpsCpy(dst, src, len);
}


kd_bool_t
#if defined KD_ARCH_64BIT_INT
kdMemOpsCpyU16(void* dst, void* src, kd_i64_t len)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsCpyU16(void* dst, void* src, kd_i32_t len)
#endif /* KD_ARCH_64BIT_INT */
{
  return len < 0 ? KD_RESULT_FAILURE : kdGenMemOpsCpy(dst, src, KD_USIZE_C(len) * KD_SZ_U16);
}


kd_bool_t
#if defined KD_ARCH_64BIT_INT
kdMemOpsCpyU32(void* dst, void* src, kd_i64_t len)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsCpyU32(void* dst, void* src, kd_i32_t len)
#endif /* KD_ARCH_64BIT_INT */
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
#if defined KD_ARCH_64BIT_INT
kdMemOpsCpyN(void* dst, void* src, kd_i64_t len, kd_i64_t n)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsCpyN(void* dst, void* src, kd_i32_t len, kd_i32_t n)
#endif /* KD_ARCH_64BIT_INT */
{
  if (len < 0 || n <= 0)
  {
    return KD_RESULT_FAILURE;
  }
  return kdGenMemOpsCpy(dst, src, len * n);
}


kd_bool_t
#if defined KD_ARCH_64BIT_INT
kdMemOpsMove(void* dst, void* src, kd_i64_t len)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsMove(void* dst, void* src, kd_i32_t len)
#endif /* KD_ARCH_64BIT_INT */
{
  return len < 0 ? KD_RESULT_FAILURE : kdGenMemOpsMove(dst, src, len);
}


kd_bool_t
#if defined KD_ARCH_64BIT_INT
kdMemOpsMoveU16(void* dst, void* src, kd_i64_t len)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsMoveU16(void* dst, void* src, kd_i32_t len)
#endif /* KD_ARCH_64BIT_INT */
{
  return len < 0 ? KD_RESULT_FAILURE : kdGenMemOpsMove(dst, src, KD_USIZE_C(len) * KD_SZ_U16);
}


kd_bool_t
#if defined KD_ARCH_64BIT_INT
kdMemOpsMoveU32(void* dst, void* src, kd_i64_t len)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsMoveU32(void* dst, void* src, kd_i32_t len)
#endif /* KD_ARCH_64BIT_INT */
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


kd_bool_t
#if defined KD_ARCH_64BIT_INT
kdMemOpsMoveN(void* dst, void* src, kd_i64_t len, kd_i64_t n)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsMoveN(void* dst, void* src, kd_i32_t len, kd_i32_t n)
#endif /* KD_ARCH_64BIT_INT */
{
  if (len < 0 || n <= 0)
  {
    return KD_RESULT_FAILURE;
  }
  return kdGenMemOpsMove(dst, src, len * n);
}


void*
#if defined KD_ARCH_64BIT_INT
kdMemOpsFind(void* ptr, kd_i64_t len, kd_byte_t item)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsFind(void* ptr, kd_i32_t len, kd_byte_t item)
#endif /* KD_ARCH_64BIT_INT */
{
  if (!ptr || len <= 0)
  {
    return kd_null;
  }

  return kdi_GenMemOpsFindBlockWithIndex_Byte(kd_null, ptr, len, item);
}


void*
#if defined KD_ARCH_64BIT_INT
kdMemOpsFindU16(void* ptr, kd_i64_t len, kd_u16_t item)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsFindU16(void* ptr, kd_i32_t len, kd_u16_t item)
#endif /* KD_ARCH_64BIT_INT */
{
  if (!ptr || len <= 0)
  {
    return kd_null;
  }

  return kdi_GenMemOpsFindBlockWithIndex_U16(kd_null, ptr, len * KD_SZ_U16, item);
}


void*
#if defined KD_ARCH_64BIT_INT
kdMemOpsFindU32(void* ptr, kd_i64_t len, kd_u32_t item)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsFindU32(void* ptr, kd_i32_t len, kd_u32_t item)
#endif /* KD_ARCH_64BIT_INT */
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
#if defined KD_ARCH_64BIT_INT
kdMemOpsFindN(void* ptr, kd_i64_t len, void* nitem, kd_i64_t n)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsFindN(void* ptr, kd_i32_t len, void* nitem, kd_i32_t n)
#endif /* KD_ARCH_64BIT_INT */
{
  if (len < 0 || n <= 0)
  {
    return kd_null;
  }
  return kdGenMemOpsFindBlock(ptr, len * n, nitem, n);
}


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsFindIndex(void* ptr, kd_i64_t len, kd_byte_t item)
#else  /* !defined KD_ARCH_64BIT_INT */
kd_i32_t
kdMemOpsFindIndex(void* ptr, kd_i32_t len, kd_byte_t item)
#endif /* KD_ARCH_64BIT_INT */
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsFindBlockWithIndex_Byte(&idx, ptr, len, item);

#if defined KD_ARCH_64BIT_INT
  return found_ptr ? KD_I64_C(idx) : -1;
#else  /* !defined KD_ARCH_64BIT_INT */
  return found_ptr ? KD_I32_C(idx) : -1;
#endif /* KD_ARCH_64BIT_INT */
}


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsFindIndexU16(void* ptr, kd_i64_t len, kd_u16_t item)
#else  /* !defined KD_ARCH_64BIT_INT */
kd_i32_t
kdMemOpsFindIndexU16(void* ptr, kd_i32_t len, kd_u16_t item)
#endif /* KD_ARCH_64BIT_INT */
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsFindBlockWithIndex_U16(&idx, ptr, len * KD_SZ_U16, item);

#if defined KD_ARCH_64BIT_INT
  return found_ptr ? KD_I64_C(idx / KD_SZ_U16) : -1;
#else  /* !defined KD_ARCH_64BIT_INT */
  return found_ptr ? KD_I32_C(idx / KD_SZ_U16) : -1;
#endif /* KD_ARCH_64BIT_INT */
}


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsFindIndexU32(void* ptr, kd_i64_t len, kd_u32_t item)
#else  /* !defined KD_ARCH_64BIT_INT */
kd_i32_t
kdMemOpsFindIndexU32(void* ptr, kd_i32_t len, kd_u32_t item)
#endif /* KD_ARCH_64BIT_INT */
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsFindBlockWithIndex_U32(&idx, ptr, len * KD_SZ_U32, item);

#if defined KD_ARCH_64BIT_INT
  return found_ptr ? KD_I64_C(idx / KD_SZ_U32) : -1;
#else  /* !defined KD_ARCH_64BIT_INT */
  return found_ptr ? KD_I32_C(idx / KD_SZ_U32) : -1;
#endif /* KD_ARCH_64BIT_INT */
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


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsFindIndexN(void* ptr, kd_i64_t len, void* nitem, kd_i64_t n)
#else  /* !defined KD_ARCH_64BIT_INT */
kd_i32_t
kdMemOpsFindIndexN(void* ptr, kd_i32_t len, void* nitem, kd_i32_t n)
#endif /* KD_ARCH_64BIT_INT */
{
  kd_usize_t idx;

  if (len < 0 || n <= 0)
  {
    return -1;
  }

  return kdGenMemOpsFindBlockIndex(&idx, ptr, len * n, nitem, n) ?
#if defined KD_ARCH_64BIT_INT
                                                                 KD_I64_C(idx / n)
#else  /* !defined KD_ARCH_64BIT_INT */
                                                                 KD_I32_C(idx / n)
#endif /* KD_ARCH_64BIT_INT */
                                                                 : -1;
}


void*
#if defined KD_ARCH_64BIT_INT
kdMemOpsFindLast(void* ptr, kd_i64_t len, kd_byte_t item)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsFindLast(void* ptr, kd_i32_t len, kd_byte_t item)
#endif /* KD_ARCH_64BIT_INT */
{
  if (!ptr || len <= 0)
  {
    return kd_null;
  }

  return kdi_GenMemOpsFindLastBlockWithIndex_Byte(kd_null, ptr, len, item);
}


void*
#if defined KD_ARCH_64BIT_INT
kdMemOpsFindLastU16(void* ptr, kd_i64_t len, kd_u16_t item)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsFindLastU16(void* ptr, kd_i32_t len, kd_u16_t item)
#endif /* KD_ARCH_64BIT_INT */
{
  if (!ptr || len <= 0)
  {
    return kd_null;
  }

  return kdi_GenMemOpsFindLastBlockWithIndex_U16(kd_null, ptr, len * KD_SZ_U16, item);
}


void*
#if defined KD_ARCH_64BIT_INT
kdMemOpsFindLastU32(void* ptr, kd_i64_t len, kd_u32_t item)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsFindLastU32(void* ptr, kd_i32_t len, kd_u32_t item)
#endif /* KD_ARCH_64BIT_INT */
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


void*
#if defined KD_ARCH_64BIT_INT
kdMemOpsFindLastN(void* ptr, kd_i64_t len, void* nitem, kd_i64_t n)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsFindLastN(void* ptr, kd_i32_t len, void* nitem, kd_i32_t n)
#endif /* KD_ARCH_64BIT_INT */
{
  if (len < 0 || n <= 0)
  {
    return kd_null;
  }
  return kdGenMemOpsFindLastBlock(ptr, len * n, nitem, n);
}


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsFindLastIndex(void* ptr, kd_i64_t len, kd_byte_t item)
#else  /* !defined KD_ARCH_64BIT_INT */
kd_i32_t
kdMemOpsFindLastIndex(void* ptr, kd_i32_t len, kd_byte_t item)
#endif /* KD_ARCH_64BIT_INT */
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsFindLastBlockWithIndex_Byte(&idx, ptr, len, item);

#if defined KD_ARCH_64BIT_INT
  return found_ptr ? KD_I64_C(idx) : -1;
#else  /* !defined KD_ARCH_64BIT_INT */
  return found_ptr ? KD_I32_C(idx) : -1;
#endif /* KD_ARCH_64BIT_INT */
}


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsFindLastIndexU16(void* ptr, kd_i64_t len, kd_u16_t item)
#else  /* !defined KD_ARCH_64BIT_INT */
kd_i32_t
kdMemOpsFindLastIndexU16(void* ptr, kd_i32_t len, kd_u16_t item)
#endif /* KD_ARCH_64BIT_INT */
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsFindLastBlockWithIndex_U16(&idx, ptr, len * KD_SZ_U16, item);

#if defined KD_ARCH_64BIT_INT
  return found_ptr ? KD_I64_C(idx / KD_SZ_U16) : -1;
#else  /* !defined KD_ARCH_64BIT_INT */
  return found_ptr ? KD_I32_C(idx / KD_SZ_U16) : -1;
#endif /* KD_ARCH_64BIT_INT */
}


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsFindLastIndexU32(void* ptr, kd_i64_t len, kd_u32_t item)
#else  /* !defined KD_ARCH_64BIT_INT */
kd_i32_t
kdMemOpsFindLastIndexU32(void* ptr, kd_i32_t len, kd_u32_t item)
#endif /* KD_ARCH_64BIT_INT */
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsFindLastBlockWithIndex_U32(&idx, ptr, len * KD_SZ_U32, item);

#if defined KD_ARCH_64BIT_INT
  return found_ptr ? KD_I64_C(idx / KD_SZ_U32) : -1;
#else  /* !defined KD_ARCH_64BIT_INT */
  return found_ptr ? KD_I32_C(idx / KD_SZ_U32) : -1;
#endif /* KD_ARCH_64BIT_INT */
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


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsFindLastIndexN(void* ptr, kd_i64_t len, void* nitem, kd_i64_t n)
#else  /* !defined KD_ARCH_64BIT_INT */
kd_i32_t
kdMemOpsFindLastIndexN(void* ptr, kd_i32_t len, void* nitem, kd_i32_t n)
#endif /* KD_ARCH_64BIT_INT */
{
  kd_usize_t idx;

  if (len < 0 || n <= 0)
  {
    return -1;
  }

  return kdGenMemOpsFindLastBlockIndex(&idx, ptr, len * n, nitem, n) ?
#if defined KD_ARCH_64BIT_INT
                                                                     KD_I64_C(idx / n)
#else  /* !defined KD_ARCH_64BIT_INT */
                                                                     KD_I32_C(idx / n)
#endif /* KD_ARCH_64BIT_INT */
                                                                     : -1;
}


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsFindAll(void* dst, kd_i64_t dst_len, void* ptr, kd_i64_t ptr_len, kd_byte_t item)
#else  /* !defined KD_ARCH_64BIT_INT */
kd_i32_t
kdMemOpsFindAll(void* dst, kd_i32_t dst_len, void* ptr, kd_i32_t ptr_len, kd_byte_t item)
#endif /* KD_ARCH_64BIT_INT */
{
  if (!dst || dst_len <= 0 || !ptr || ptr_len <= 0)
  {
    return 0;
  }
  return
#if defined KD_ARCH_64BIT_INT
    KD_I64_C(kdi_GenMemOpsFindAllBlocksWithIndex_Byte(dst, dst_len, ptr, ptr_len, item));
#else  /* !defined KD_ARCH_64BIT_INT */
    KD_I64_C(kdi_GenMemOpsFindAllBlocksWithIndex_Byte(dst, dst_len, ptr, ptr_len, item));
#endif /* KD_ARCH_64BIT_INT */
}


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsFindAllU16(void* dst, kd_i64_t dst_len, void* ptr, kd_i64_t ptr_len, kd_u16_t item)
#else  /* !defined KD_ARCH_64BIT_INT */
kd_i32_t
kdMemOpsFindAllU16(void* dst, kd_i32_t dst_len, void* ptr, kd_i32_t ptr_len, kd_u16_t item)
#endif /* KD_ARCH_64BIT_INT */
{
  kd_byte_t** dst_ptr  = dst;
  kd_usize_t *idxs_ptr = dst, found_cnt, temp_found_cnt;

  if (!dst || dst_len <= 0 || !ptr || ptr_len <= 0)
  {
    return 0;
  }

  found_cnt      = kdi_GenMemOpsFindAllBlocksWithIndex_U16(dst, dst_len * KD_SZ_U16, ptr, ptr_len * KD_SZ_U16, item);
  temp_found_cnt = found_cnt;

  if (KD_SZ_PTR > KD_SZ_USIZE)
  {
    dst_ptr += found_cnt;
    idxs_ptr += found_cnt;

    while (temp_found_cnt--)
    {
      --dst_ptr;
      --idxs_ptr;
      *dst_ptr = KD_PBYTE_C(ptr) + *idxs_ptr;
    }
  }
  else
  {
    while (temp_found_cnt--)
    {
      *dst_ptr = KD_PBYTE_C(ptr) + *idxs_ptr;
      ++dst_ptr;
      ++idxs_ptr;
    }
  }

  return
#if defined KD_ARCH_64BIT_INT
    KD_I64_C(found_cnt);
#else  /* !defined KD_ARCH_64BIT_INT */
    KD_I32_C(found_cnt);
#endif /* KD_ARCH_64BIT_INT */
}


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsFindAllU32(void* dst, kd_i64_t dst_len, void* ptr, kd_i64_t ptr_len, kd_u32_t item)
#else  /* !defined KD_ARCH_64BIT_INT */
kd_i32_t
kdMemOpsFindAllU32(void* dst, kd_i32_t dst_len, void* ptr, kd_i32_t ptr_len, kd_u32_t item)
#endif /* KD_ARCH_64BIT_INT */
{
  kd_byte_t** dst_ptr  = dst;
  kd_usize_t *idxs_ptr = dst, found_cnt, temp_found_cnt;

  if (!dst || dst_len <= 0 || !ptr || ptr_len <= 0)
  {
    return 0;
  }

  found_cnt      = kdi_GenMemOpsFindAllBlocksWithIndex_U32(dst, dst_len * KD_SZ_U32, ptr, ptr_len * KD_SZ_U32, item);
  temp_found_cnt = found_cnt;

  if (KD_SZ_PTR > KD_SZ_USIZE)
  {
    dst_ptr += found_cnt;
    idxs_ptr += found_cnt;

    while (temp_found_cnt--)
    {
      --dst_ptr;
      --idxs_ptr;
      *dst_ptr = KD_PBYTE_C(ptr) + *idxs_ptr;
    }
  }
  else
  {
    while (temp_found_cnt--)
    {
      *dst_ptr = KD_PBYTE_C(ptr) + *idxs_ptr;
      ++dst_ptr;
      ++idxs_ptr;
    }
  }

  return
#if defined KD_ARCH_64BIT_INT
    KD_I64_C(found_cnt);
#else  /* !defined KD_ARCH_64BIT_INT */
    KD_I32_C(found_cnt);
#endif /* KD_ARCH_64BIT_INT */
}


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsFindAllU64(void* dst, kd_i64_t dst_len, void* ptr, kd_i64_t ptr_len, kd_u64_t item)
{
  kd_byte_t** dst_ptr  = dst;
  kd_usize_t *idxs_ptr = dst, found_cnt, temp_found_cnt;

  if (!dst || dst_len <= 0 || !ptr || ptr_len <= 0)
  {
    return 0;
  }

  found_cnt      = kdi_GenMemOpsFindAllBlocksWithIndex_U64(dst, dst_len * KD_SZ_U64, ptr, ptr_len * KD_SZ_U64, item);
  temp_found_cnt = found_cnt;

  if (KD_SZ_PTR > KD_SZ_USIZE)
  {
    dst_ptr += found_cnt;
    idxs_ptr += found_cnt;

    while (temp_found_cnt--)
    {
      --dst_ptr;
      --idxs_ptr;
      *dst_ptr = KD_PBYTE_C(ptr) + *idxs_ptr;
    }
  }
  else
  {
    while (temp_found_cnt--)
    {
      *dst_ptr = KD_PBYTE_C(ptr) + *idxs_ptr;
      ++dst_ptr;
      ++idxs_ptr;
    }
  }

  return KD_I64_C(found_cnt);
}
#endif /* KD_ARCH_64BIT_INT */


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsFindAllN(void* dst, kd_i64_t dst_len, void* ptr, kd_i64_t ptr_len, void* nitem, kd_i64_t n)
#else  /* !defined KD_ARCH_64BIT_INT */
kd_i32_t
kdMemOpsFindAllN(void* dst, kd_i32_t dst_len, void* ptr, kd_i32_t ptr_len, void* nitem, kd_i32_t n)
#endif /* KD_ARCH_64BIT_INT */
{
  if (dst_len < 0 || ptr_len < 0 || n <= 0)
  {
    return 0;
  }
  return
#if defined KD_ARCH_64BIT_INT
    KD_I64_C(kdGenMemOpsFindAllBlocks(dst, dst_len * n, ptr, ptr_len * n, nitem, n));
#else  /* !defined KD_ARCH_64BIT_INT */
    KD_I32_C(kdGenMemOpsFindAllBlocks(dst, dst_len * n, ptr, ptr_len * n, nitem, n));
#endif /* KD_ARCH_64BIT_INT */
}


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsFindAllIndex(kd_i64_t* idxs, kd_i64_t idxs_len, void* ptr, kd_i64_t ptr_len, kd_byte_t item)
#else  /* !defined KD_ARCH_64BIT_INT */
kd_i32_t
kdMemOpsFindAllIndex(kd_i32_t* idxs, kd_i32_t idxs_len, void* ptr, kd_i32_t ptr_len, kd_byte_t item)
#endif /* KD_ARCH_64BIT_INT */
{
  if (!idxs || idxs_len <= 0 || !ptr || ptr_len <= 0)
  {
    return 0;
  }
  return
#if defined KD_ARCH_64BIT_INT
    KD_I64_C(kdi_GenMemOpsFindAllBlocksWithIndex_Byte(idxs, idxs_len, ptr, ptr_len, item));
#else  /* !defined KD_ARCH_64BIT_INT */
    KD_I32_C(kdi_GenMemOpsFindAllBlocksWithIndex_Byte(idxs, idxs_len, ptr, ptr_len, item));
#endif /* KD_ARCH_64BIT_INT */
}


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsFindAllIndexU16(kd_i64_t* idxs, kd_i64_t idxs_len, void* ptr, kd_i64_t ptr_len, kd_u16_t item)
#else  /* !defined KD_ARCH_64BIT_INT */
kd_i32_t
kdMemOpsFindAllIndexU16(kd_i32_t* idxs, kd_i32_t idxs_len, void* ptr, kd_i32_t ptr_len, kd_u16_t item)
#endif /* KD_ARCH_64BIT_INT */
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
    idxs =
#if defined KD_ARCH_64BIT_INT
      KD_PI64_C((kd_byte_t*)idxs + KD_SZ_USIZE);
#else  /* !defined KD_ARCH_64BIT_INT */
      KD_PI32_C((kd_byte_t*)idxs + KD_SZ_USIZE);
#endif /* KD_ARCH_64BIT_INT */
  }

  return
#if defined KD_ARCH_64BIT_INT
    KD_I64_C(found_cnt);
#else  /* !defined KD_ARCH_64BIT_INT */
    KD_I32_C(found_cnt);
#endif /* KD_ARCH_64BIT_INT */
}


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsFindAllIndexU32(kd_i64_t* idxs, kd_i64_t idxs_len, void* ptr, kd_i64_t ptr_len, kd_u32_t item)
#else  /* !defined KD_ARCH_64BIT_INT */
kd_i32_t
kdMemOpsFindAllIndexU32(kd_i32_t* idxs, kd_i32_t idxs_len, void* ptr, kd_i32_t ptr_len, kd_u32_t item)
#endif /* KD_ARCH_64BIT_INT */
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
    idxs =
#if defined KD_ARCH_64BIT_INT
      KD_PI64_C((kd_byte_t*)idxs + KD_SZ_USIZE);
#else  /* !defined KD_ARCH_64BIT_INT */
      KD_PI32_C((kd_byte_t*)idxs + KD_SZ_USIZE);
#endif /* KD_ARCH_64BIT_INT */
  }

  return
#if defined KD_ARCH_64BIT_INT
    KD_I64_C(found_cnt);
#else  /* !defined KD_ARCH_64BIT_INT */
    KD_I32_C(found_cnt);
#endif /* KD_ARCH_64BIT_INT */
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
    idxs = KD_PI64_C((kd_byte_t*)idxs + KD_SZ_USIZE);
  }

  return KD_I64_C(found_cnt);
}
#endif /* KD_ARCH_64BIT_INT */


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsFindAllIndexN(kd_i64_t* idxs, kd_i64_t idxs_len, void* ptr, kd_i64_t ptr_len, void* nitem, kd_i64_t n)
#else  /* !defined KD_ARCH_64BIT_INT */
kd_i32_t
kdMemOpsFindAllIndexN(kd_i32_t* idxs, kd_i32_t idxs_len, void* ptr, kd_i32_t ptr_len, void* nitem, kd_i32_t n)
#endif /* KD_ARCH_64BIT_INT */
{
  if (idxs_len < 0 || ptr_len < 0 || n <= 0)
  {
    return 0;
  }
  return
#if defined KD_ARCH_64BIT_INT
    KD_I64_C(kdGenMemOpsFindAllBlocksIndex(KD_PUSIZE_C(idxs), idxs_len * KD_SZ_USIZE, ptr, ptr_len * n, nitem, n));
#else  /* !defined KD_ARCH_64BIT_INT */
    KD_I32_C(kdGenMemOpsFindAllBlocksIndex(KD_PUSIZE_C(idxs), idxs_len * KD_SZ_USIZE, ptr, ptr_len * n, nitem, n));
#endif /* KD_ARCH_64BIT_INT */
}


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsCmp(void* ptr1, void* ptr2, kd_i64_t len)
#else  /* !defined KD_ARCH_64BIT_INT */
kd_i32_t
kdMemOpsCmp(void* ptr1, void* ptr2, kd_i32_t len)
#endif /* KD_ARCH_64BIT_INT */
{
  return len < 0 ? 0 : kdGenMemOpsCmp(ptr1, ptr2, len);
}


kd_bool_t
#if defined KD_ARCH_64BIT_INT
kdMemOpsCat(void* dst, kd_i64_t dst_len, void* src1, kd_i64_t src1_len, void* src2, kd_i64_t src2_len)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsCat(void* dst, kd_i32_t dst_len, void* src1, kd_i32_t src1_len, void* src2, kd_i32_t src2_len)
#endif /* KD_ARCH_64BIT_INT */
{
  return dst_len < 0 || src1_len < 0 || src2_len < 0 ? 0 : kdGenMemOpsCat(dst, dst_len, src1, src1_len, src2, src2_len);
}


void*
#if defined KD_ARCH_64BIT_INT
kdMemOpsCompSpn(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsCompSpn(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len)
#endif /* KD_ARCH_64BIT_INT */
{
  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return kd_null;
  }
  return kdi_GenMemOpsBlocksCompSpnWithIndex_Byte(kd_null, ptr, len, keys, keys_len);
}


void*
#if defined KD_ARCH_64BIT_INT
kdMemOpsCompSpnU16(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsCompSpnU16(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len)
#endif /* KD_ARCH_64BIT_INT */
{
  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return kd_null;
  }
  return kdi_GenMemOpsBlocksCompSpnWithIndex_U16(kd_null, ptr, len * KD_SZ_U16, keys, keys_len * KD_SZ_U16);
}


void*
#if defined KD_ARCH_64BIT_INT
kdMemOpsCompSpnU32(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsCompSpnU32(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len)
#endif /* KD_ARCH_64BIT_INT */
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
#if defined KD_ARCH_64BIT_INT
kdMemOpsCompSpnN(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len, kd_i64_t n)
#else  /* !defined KD_ARCH_64BIT_INT */
kdMemOpsCompSpnN(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len, kd_i32_t n)
#endif /* KD_ARCH_64BIT_INT */
{
  if (len < 0 || keys_len < 0 || n <= 0)
  {
    return kd_null;
  }
  return kdGenMemOpsBlocksCompSpn(ptr, len * n, keys, n, keys_len * n);
}


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsCompSpnIndex(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
#else  /* !defined KD_ARCH_64BIT_INT */
kd_i32_t
kdMemOpsCompSpnIndex(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len)
#endif /* KD_ARCH_64BIT_INT */
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsBlocksCompSpnWithIndex_Byte(&idx, ptr, len, keys, keys_len);

  return found_ptr ?
#if defined KD_ARCH_64BIT_INT
                   KD_I64_C(idx)
#else  /* !defined KD_ARCH_64BIT_INT */
                   KD_I32_C(idx)
#endif /* KD_ARCH_64BIT_INT */
                   : -1;
}


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsCompSpnIndexU16(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
#else  /* !defined KD_ARCH_64BIT_INT */
kd_i32_t
kdMemOpsCompSpnIndexU16(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len)
#endif /* KD_ARCH_64BIT_INT */
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsBlocksCompSpnWithIndex_U16(&idx, ptr, len * KD_SZ_U16, keys, keys_len * KD_SZ_U16);

  return found_ptr ?
#if defined KD_ARCH_64BIT_INT
                   KD_I64_C(idx / KD_SZ_U16)
#else  /* !defined KD_ARCH_64BIT_INT */
                   KD_I32_C(idx / KD_SZ_U16)
#endif /* KD_ARCH_64BIT_INT */
                   : -1;
}


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsCompSpnIndexU32(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
#else  /* !defined KD_ARCH_64BIT_INT */
kd_i32_t
kdMemOpsCompSpnIndexU32(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len)
#endif /* KD_ARCH_64BIT_INT */
{
  kd_usize_t idx;
  void*      found_ptr;

  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return -1;
  }

  found_ptr = kdi_GenMemOpsBlocksCompSpnWithIndex_U32(&idx, ptr, len * KD_SZ_U32, keys, keys_len * KD_SZ_U32);

  return found_ptr ?
#if defined KD_ARCH_64BIT_INT
                   KD_I64_C(idx / KD_SZ_U32)
#else  /* !defined KD_ARCH_64BIT_INT */
                   KD_I32_C(idx / KD_SZ_U32)
#endif /* KD_ARCH_64BIT_INT */
                   : -1;
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

  return found_ptr ? KD_I64_C(idx / KD_SZ_U64) : -1;
}
#endif /* KD_ARCH_64BIT_INT */


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsCompSpnIndexN(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len, kd_i64_t n)
#else  /* !defined KD_ARCH_64BIT_INT */
kd_i32_t
kdMemOpsCompSpnIndexN(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len, kd_i32_t n)
#endif /* KD_ARCH_64BIT_INT */
{
  kd_usize_t idx;

  if (len < 0 || keys_len < 0 || n <= 0)
  {
    return -1;
  }

  return kdGenMemOpsBlocksCompSpnIndex(&idx, ptr, len * n, keys, n, keys_len * n) ?
#if defined KD_ARCH_64BIT_INT
                                                                                  KD_I64_C(idx / n)
#else  /* !defined KD_ARCH_64BIT_INT */
                                                                                  KD_I32_C(idx / n)
#endif /* KD_ARCH_64BIT_INT */
                                                                                  : -1;
}


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsSpn(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
#else  /* !defined KD_ARCH_64BIT_INT */
kd_i32_t
kdMemOpsSpn(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len)
#endif /* KD_ARCH_64BIT_INT */
{
  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return 0;
  }
  return kdi_GenMemOpsBlocksSpn_Byte(ptr, len, keys, keys_len);
}


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsSpnU16(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
#else  /* !defined KD_ARCH_64BIT_INT */
kd_i32_t
kdMemOpsSpnU16(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len)
#endif /* KD_ARCH_64BIT_INT */
{
  if (!ptr || !keys || len <= 0 || keys_len <= 0)
  {
    return 0;
  }
  return kdi_GenMemOpsBlocksSpn_U16(ptr, len * KD_SZ_U16, keys, keys_len * KD_SZ_U16) / KD_SZ_U16;
}


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsSpnU32(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len)
#else  /* !defined KD_ARCH_64BIT_INT */
kd_i32_t
kdMemOpsSpnU32(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len)
#endif /* KD_ARCH_64BIT_INT */
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


#if defined KD_ARCH_64BIT_INT
kd_i64_t
kdMemOpsSpnN(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len, kd_i64_t n)
#else  /* !defined KD_ARCH_64BIT_INT */
kd_i32_t
kdMemOpsSpnN(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len, kd_i32_t n)
#endif /* KD_ARCH_64BIT_INT */
{
  if (len < 0 || keys_len < 0 || n <= 0)
  {
    return 0;
  }
  return
#if defined KD_ARCH_64BIT_INT
    KD_I64_C(kdGenMemOpsBlocksSpn(ptr, len * n, keys, n, keys_len * n) / n);
#else  /* !defined KD_ARCH_64BIT_INT */
    KD_I32_C(kdGenMemOpsBlocksSpn(ptr, len * n, keys, n, keys_len * n) / n);
#endif /* KD_ARCH_64BIT_INT */
}
