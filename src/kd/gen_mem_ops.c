/**
 * @file gen_mem_ops.c
 * @author Kumarjit Das
 * @date 2025-06-02
 * @since 0.0.7
 * @brief Main source file of the GEN_MEM_OPS library.
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
#include "kd/gen_mem_ops.h"
#include "_internal/gen_mem_ops_sn.h"


kd_bool_t
kdGenMemOpsSetBytes(void* ptr, kd_usize_t sz, kd_byte_t val)
{
  if (!ptr || !sz)
  {
    return KD_RESULT_FAILURE;
  }

  kdi_GenMemOpsSetBlocks_S8(ptr, sz, val);

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdGenMemOpsSetBlocks(void* ptr, kd_usize_t sz, void* block, kd_usize_t block_sz)
{
  kd_u8_t  block_val_u8;
  kd_u16_t block_val_u16;
  kd_u32_t block_val_u32;
#if defined KD_ARCH_64BIT_INT
  kd_u64_t block_val_u64;
#endif

  if (!ptr || !sz || !block || !block_sz)
  {
    return KD_RESULT_FAILURE;
  }

  switch (block_sz)
  {
    case 1:
      block_val_u8 = *(kd_u8_t*)block;
      kdi_GenMemOpsSetBlocks_S8(ptr, sz, block_val_u8);
      break;
    case 2:
      block_val_u16 = *(kd_u16_t*)block;
      kdi_GenMemOpsSetBlocks_S16(ptr, sz, block_val_u16);
      break;
    case 4:
      block_val_u32 = *(kd_u32_t*)block;
      kdi_GenMemOpsSetBlocks_S32(ptr, sz, block_val_u32);
      break;
#if defined KD_ARCH_64BIT_INT
    case 8:
      block_val_u64 = *(kd_u64_t*)block;
      kdi_GenMemOpsSetBlocks_S64(ptr, sz, block_val_u64);
      break;
#endif
    default:
      kdi_GenMemOpsSetBlocks_Sn(ptr, sz, block, block_sz);
  }

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdGenMemOpsCpy(void* dst, void* src, kd_usize_t sz)
{
  kd_byte_t *dst_ptr, *src_ptr;

  if (!dst || !src || !sz)
  {
    return KD_RESULT_FAILURE;
  }

  dst_ptr = dst;
  src_ptr = (kd_byte_t*)src;

  while (sz--)
  {
    *dst_ptr = *src_ptr;
    ++dst_ptr;
    ++src_ptr;
  }

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdGenMemOpsMove(void* dst, void* src, kd_usize_t sz)
{
  kd_byte_t *dst_ptr, *src_ptr;

  if (!dst || !src || !sz)
  {
    return KD_RESULT_FAILURE;
  }

  if ((kd_byte_t*)dst <= (kd_byte_t*)src)
  {
    dst_ptr = dst;
    src_ptr = (kd_byte_t*)src;

    while (sz--)
    {
      *dst_ptr = *src_ptr;
      ++dst_ptr;
      ++src_ptr;
    }

    return KD_RESULT_SUCCESS;
  }

  dst_ptr = (kd_byte_t*)dst + sz - 1;
  src_ptr = (kd_byte_t*)src + sz - 1;

  while (sz--)
  {
    *dst_ptr = *src_ptr;
    --dst_ptr;
    --src_ptr;
  }

  return KD_RESULT_SUCCESS;
}


void*
kdGenMemOpsFindByte(void* ptr, kd_usize_t sz, kd_byte_t item)
{
  if (!ptr || !sz)
  {
    return kd_null;
  }

  return kdi_GenMemOpsFindBlockWithIndex_S8(kd_null, ptr, sz, item);
}


kd_bool_t
kdGenMemOpsFindByteIndex(kd_usize_t* idx_ptr, void* ptr, kd_usize_t sz, kd_byte_t item)
{
  void* found_ptr;

  if (!idx_ptr || !ptr || !sz)
  {
    return KD_RESULT_FAILURE;
  }

  found_ptr = kdi_GenMemOpsFindBlockWithIndex_S8(idx_ptr, ptr, sz, item);

  return found_ptr ? KD_RESULT_SUCCESS : KD_RESULT_FAILURE;
}


void*
kdGenMemOpsFindBlock(void* ptr, kd_usize_t sz, void* block, kd_usize_t block_sz)
{
  kd_u8_t  block_val_u8;
  kd_u16_t block_val_u16;
  kd_u32_t block_val_u32;
#if defined KD_ARCH_64BIT_INT
  kd_u64_t block_val_u64;
#endif

  if (!ptr || !sz || !block || !block_sz)
  {
    return kd_null;
  }

  switch (block_sz)
  {
    case 1:
      block_val_u8 = *(kd_u8_t*)block;
      return kdi_GenMemOpsFindBlockWithIndex_S8(kd_null, ptr, sz, block_val_u8);
    case 2:
      block_val_u16 = *(kd_u16_t*)block;
      return kdi_GenMemOpsFindBlockWithIndex_S16(kd_null, ptr, sz, block_val_u16);
    case 4:
      block_val_u32 = *(kd_u32_t*)block;
      return kdi_GenMemOpsFindBlockWithIndex_S32(kd_null, ptr, sz, block_val_u32);
#if defined KD_ARCH_64BIT_INT
    case 8:
      block_val_u64 = *(kd_u64_t*)block;
      return kdi_GenMemOpsFindBlockWithIndex_S64(kd_null, ptr, sz, block_val_u64);
#endif
    default:;
  }

  return kdi_GenMemOpsFindBlockWithIndex_Sn(kd_null, ptr, sz, block, block_sz);
}


kd_bool_t
kdGenMemOpsFindBlockIndex(kd_usize_t* idx_ptr, void* ptr, kd_usize_t sz, void* block, kd_usize_t block_sz)
{
  void*    found_ptr;
  kd_u8_t  block_val_u8;
  kd_u16_t block_val_u16;
  kd_u32_t block_val_u32;
#if defined KD_ARCH_64BIT_INT
  kd_u64_t block_val_u64;
#endif

  if (!idx_ptr || !ptr || !sz || !block || !block_sz)
  {
    return KD_RESULT_FAILURE;
  }

  switch (block_sz)
  {
    case 1:
      block_val_u8 = *(kd_u8_t*)block;
      found_ptr    = kdi_GenMemOpsFindBlockWithIndex_S8(idx_ptr, ptr, sz, block_val_u8);
      break;
    case 2:
      block_val_u16 = *(kd_u16_t*)block;
      found_ptr     = kdi_GenMemOpsFindBlockWithIndex_S16(idx_ptr, ptr, sz, block_val_u16);
      break;
    case 4:
      block_val_u32 = *(kd_u32_t*)block;
      found_ptr     = kdi_GenMemOpsFindBlockWithIndex_S32(idx_ptr, ptr, sz, block_val_u32);
      break;
#if defined KD_ARCH_64BIT_INT
    case 8:
      block_val_u64 = *(kd_u64_t*)block;
      found_ptr     = kdi_GenMemOpsFindBlockWithIndex_S64(idx_ptr, ptr, sz, block_val_u64);
      break;
#endif
    default:;
      found_ptr = kdi_GenMemOpsFindBlockWithIndex_Sn(idx_ptr, ptr, sz, block, block_sz);
  }

  return found_ptr ? KD_RESULT_SUCCESS : KD_RESULT_FAILURE;
}


kd_i32_t
kdGenMemOpsCmp(void* ptr1, void* ptr2, kd_usize_t sz)
{
  kd_byte_t *src1_ptr, *src2_ptr;

  if (!sz)
  {
    return (ptr1 && ptr2) ? 0 : ptr1 ? 1 : ptr2 ? -1 : 0;
  }

  if (!ptr1 || !ptr2)
  {
    return ptr1 ? 1 : ptr2 ? -1 : 0;
  }

  src1_ptr = ptr1;
  src2_ptr = ptr2;

  while ((*src1_ptr == *src2_ptr) && sz--)
  {
    ++src1_ptr;
    ++src2_ptr;
  }

  return !sz ? 0 : *src1_ptr - *src2_ptr;
}


kd_bool_t
kdGenMemOpsCat(void* dst, kd_usize_t sz, void* src1, kd_usize_t sz1, void* src2, kd_usize_t sz2)
{
  kd_byte_t *dst_ptr, *src1_ptr, *src2_ptr;

  if (!dst || !src1 || !src2 || !sz || !sz1 || !sz2)
  {
    return KD_RESULT_FAILURE;
  }

  dst_ptr  = dst;
  src1_ptr = src1;
  src2_ptr = src2;

  while (sz1-- && sz--)
  {
    *dst_ptr = *src1_ptr;
    ++dst_ptr;
    ++src1_ptr;
  }

  while (sz2-- && sz--)
  {
    *dst_ptr = *src2_ptr;
    ++dst_ptr;
    ++src2_ptr;
  }

  return KD_RESULT_SUCCESS;
}


void*
kdGenMemOpsBytesCompSpn(void* ptr, kd_usize_t sz, void* keys, kd_usize_t keys_sz)
{
  if (!ptr || !sz || !keys || !keys_sz)
  {
    return kd_null;
  }

  return kdi_GenMemOpsBlocksCompSpnWithIndex_S8(kd_null, ptr, sz, keys, keys_sz);
}


kd_bool_t
kdGenMemOpsBytesCompSpnIndex(kd_usize_t* idx_ptr, void* ptr, kd_usize_t sz, void* keys, kd_usize_t keys_sz)
{
  kd_byte_t* found_ptr;

  if (!idx_ptr || !ptr || !sz || !keys || !keys_sz)
  {
    return KD_RESULT_FAILURE;
  }

  found_ptr = kdi_GenMemOpsBlocksCompSpnWithIndex_S8(idx_ptr, ptr, sz, keys, keys_sz);

  return found_ptr ? KD_RESULT_SUCCESS : KD_RESULT_FAILURE;
}


void*
kdGenMemOpsBlocksCompSpn(void* ptr, kd_usize_t sz, void* key_blocks, kd_usize_t key_block_sz, kd_usize_t key_blocks_sz)
{
  if (!ptr || !sz || !key_blocks || !key_block_sz || !key_blocks_sz)
  {
    return kd_null;
  }

  switch (key_block_sz)
  {
    case 1:
      return kdi_GenMemOpsBlocksCompSpnWithIndex_S8(kd_null, ptr, sz, key_blocks, key_blocks_sz);
    case 2:
      return kdi_GenMemOpsBlocksCompSpnWithIndex_S16(kd_null, ptr, sz, key_blocks, key_blocks_sz);
    case 4:
      return kdi_GenMemOpsBlocksCompSpnWithIndex_S32(kd_null, ptr, sz, key_blocks, key_blocks_sz);
#if defined KD_ARCH_64BIT_INT
    case 8:
      return kdi_GenMemOpsBlocksCompSpnWithIndex_S64(kd_null, ptr, sz, key_blocks, key_blocks_sz);
#endif
    default:;
  }

  return kdi_GenMemOpsBlocksCompSpnWithIndex_Sn(kd_null, ptr, sz, key_blocks, key_block_sz, key_blocks_sz);
}


kd_bool_t
kdGenMemOpsBlocksCompSpnIndex(kd_usize_t* idx_ptr, void* ptr, kd_usize_t sz, void* key_blocks, kd_usize_t key_block_sz,
                              kd_usize_t key_blocks_sz)
{
  kd_byte_t* found_ptr;

  if (!idx_ptr || !ptr || !sz || !key_blocks || !key_block_sz || !key_blocks_sz)
  {
    return KD_RESULT_FAILURE;
  }

  switch (key_block_sz)
  {
    case 1:
      found_ptr = kdi_GenMemOpsBlocksCompSpnWithIndex_S8(idx_ptr, ptr, sz, key_blocks, key_blocks_sz);
      break;
    case 2:
      found_ptr = kdi_GenMemOpsBlocksCompSpnWithIndex_S16(idx_ptr, ptr, sz, key_blocks, key_blocks_sz);
      break;
    case 4:
      found_ptr = kdi_GenMemOpsBlocksCompSpnWithIndex_S32(idx_ptr, ptr, sz, key_blocks, key_blocks_sz);
      break;
#if defined KD_ARCH_64BIT_INT
    case 8:
      found_ptr = kdi_GenMemOpsBlocksCompSpnWithIndex_S64(idx_ptr, ptr, sz, key_blocks, key_blocks_sz);
      break;
#endif
    default:
      found_ptr = kdi_GenMemOpsBlocksCompSpnWithIndex_Sn(idx_ptr, ptr, sz, key_blocks, key_block_sz, key_blocks_sz);
  }

  return found_ptr ? KD_RESULT_SUCCESS : KD_RESULT_FAILURE;
}


kd_usize_t
kdGenMemOpsBytesSpn(void* ptr, kd_usize_t sz, void* keys, kd_usize_t keys_sz)
{
  if (!ptr || !sz || !keys || !keys_sz)
  {
    return 0;
  }

  return kdi_GenMemOpsBlocksSpn_S8(ptr, sz, keys, keys_sz);
}


kd_usize_t
kdGenMemOpsBlocksSpn(void* ptr, kd_usize_t sz, void* key_blocks, kd_usize_t key_block_sz, kd_usize_t key_blocks_sz)
{
  if (!ptr || !sz || !key_blocks || !key_block_sz || !key_blocks_sz)
  {
    return 0;
  }

  switch (key_block_sz)
  {
    case 1:
      return kdi_GenMemOpsBlocksSpn_S8(ptr, sz, key_blocks, key_blocks_sz);
    case 2:
      return kdi_GenMemOpsBlocksSpn_S16(ptr, sz, key_blocks, key_blocks_sz);
    case 4:
      return kdi_GenMemOpsBlocksSpn_S32(ptr, sz, key_blocks, key_blocks_sz);
#if defined KD_ARCH_64BIT_INT
    case 8:
      return kdi_GenMemOpsBlocksSpn_S64(ptr, sz, key_blocks, key_blocks_sz);
#endif
    default:;
  }

  return kdi_GenMemOpsBlocksSpn_Sn(ptr, sz, key_blocks, key_block_sz, key_blocks_sz);
}
