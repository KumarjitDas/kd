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


kd_bool_t
kdGenMemOpsSetBytes(void* ptr, kd_usize_t sz, kd_byte_t val)
{
  kd_byte_t* dst_ptr;

  if (!ptr || !sz)
  {
    return KD_RESULT_FAILURE;
  }

  dst_ptr = ptr;

  while (sz--)
  {
    *dst_ptr = val;
    ++dst_ptr;
  }

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdGenMemOpsSetBlocks(void* ptr, kd_usize_t sz, void* block, kd_usize_t block_sz)
{
  kd_byte_t* dst_ptr;
  kd_usize_t i;

  if (!ptr || !sz || !block || !block_sz)
  {
    return KD_RESULT_FAILURE;
  }

  dst_ptr = ptr;

  while (sz)
  {
    i = 0;
    while ((i < block_sz) && sz--)
    {
      *dst_ptr = *((kd_byte_t*)block + i++);
      ++dst_ptr;
    }
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
  kd_byte_t* src_ptr;

  if (!ptr || !sz)
  {
    return kd_null;
  }

  src_ptr = ptr;

  while (sz--)
  {
    if (*src_ptr == item)
    {
      return src_ptr;
    }
    ++src_ptr;
  }

  return kd_null;
}


kd_bool_t
kdGenMemOpsFindByteIndex(kd_usize_t* idx_ptr, void* ptr, kd_usize_t sz, kd_byte_t item)
{
  kd_byte_t* src_ptr;
  kd_usize_t idx;

  if (!idx_ptr || !ptr || !sz)
  {
    return KD_RESULT_FAILURE;
  }

  idx     = 0;
  src_ptr = (kd_byte_t*)ptr;

  while (sz--)
  {
    if (*src_ptr == item)
    {
      *idx_ptr = idx;
      return KD_RESULT_SUCCESS;
    }

    ++idx;
    ++src_ptr;
  }

  return KD_RESULT_FAILURE;
}


void*
kdGenMemOpsFindBlock(void* ptr, kd_usize_t sz, void* block, kd_usize_t block_sz)
{
  kd_byte_t* src_ptr;
  kd_usize_t i, match_cnt;

  if (!ptr || !sz || !block || !block_sz)
  {
    return kd_null;
  }

  src_ptr = (kd_byte_t*)ptr;

  while (sz)
  {
    i         = 0;
    match_cnt = 0;

    while ((i < block_sz) && sz--)
    {
      match_cnt += *src_ptr == *((kd_byte_t*)block + i++);
      ++src_ptr;
    }

    if (match_cnt == block_sz)
    {
      return src_ptr - block_sz;
    }
  }

  return kd_null;
}


kd_bool_t
kdGenMemOpsFindBlockIndex(kd_usize_t* idx_ptr, void* ptr, kd_usize_t sz, void* block, kd_usize_t block_sz)
{
  kd_byte_t* src_ptr;
  kd_usize_t i, match_cnt, idx;

  if (!idx_ptr || !ptr || !sz || !block || !block_sz)
  {
    return KD_RESULT_FAILURE;
  }

  idx     = 0;
  src_ptr = (kd_byte_t*)ptr;

  while (sz)
  {
    i         = 0;
    match_cnt = 0;

    while ((i < block_sz) && sz--)
    {
      match_cnt += *src_ptr == *((kd_byte_t*)block + i++);
      ++src_ptr;
      ++idx;
    }

    if (match_cnt == block_sz)
    {
      *idx_ptr = idx - block_sz;
      return KD_RESULT_SUCCESS;
    }
  }

  return KD_RESULT_FAILURE;
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
kdGenMemOpsBytesCompSpn(void* ptr, kd_usize_t sz, void* keys, kd_usize_t num)
{
  kd_byte_t *src_ptr, *keys_ptr;
  kd_usize_t i;

  if (!ptr || !sz || !keys || !num)
  {
    return kd_null;
  }

  src_ptr = ptr;

  while (sz--)
  {
    keys_ptr = keys;
    i        = num;

    while (i--)
    {
      if (*keys_ptr == *src_ptr)
      {
        return src_ptr;
      }
      ++keys_ptr;
    }

    ++src_ptr;
  }

  return kd_null;
}


kd_bool_t
kdGenMemOpsBytesCompSpnIndex(kd_usize_t* idx_ptr, void* ptr, kd_usize_t sz, void* keys, kd_usize_t num)
{
  kd_byte_t *src_ptr, *keys_ptr;
  kd_usize_t i, idx;

  if (!idx_ptr || !ptr || !sz || !keys || !num)
  {
    return KD_RESULT_FAILURE;
  }

  idx     = 0;
  src_ptr = ptr;

  while (sz--)
  {
    keys_ptr = keys;
    i        = num;

    while (i--)
    {
      if (*keys_ptr == *src_ptr)
      {
        *idx_ptr = idx;
        return KD_RESULT_SUCCESS;
      }
      ++keys_ptr;
    }

    ++idx;
    ++src_ptr;
  }

  return KD_RESULT_FAILURE;
}


void*
kdGenMemOpsBlocksCompSpn(void* ptr, kd_usize_t sz, void* key_blocks, kd_usize_t key_block_sz, kd_usize_t num)
{
  kd_byte_t *src_ptr, *search_ptr, *key_blocks_ptr;
  kd_usize_t n, i, match_cnt;

  if (!ptr || !sz || !key_blocks || !key_block_sz || !num)
  {
    return kd_null;
  }

  src_ptr = ptr;

  while (sz--)
  {
    key_blocks_ptr = key_blocks;
    n              = num;

    while (n--)
    {
      i          = 0;
      match_cnt  = 0;
      search_ptr = src_ptr;

      while (i < key_block_sz)
      {
        match_cnt += *search_ptr == *(key_blocks_ptr + i++);
        ++search_ptr;
      }

      if (match_cnt == key_block_sz)
      {
        return src_ptr;
      }

      key_blocks_ptr += key_block_sz;
    }

    src_ptr += key_block_sz;
  }

  return kd_null;
}


kd_bool_t
kdGenMemOpsBlocksCompSpnIndex(kd_usize_t* idx_ptr, void* ptr, kd_usize_t sz, void* key_blocks, kd_usize_t key_block_sz,
                              kd_usize_t num)
{
  kd_byte_t *src_ptr, *search_ptr, *key_blocks_ptr;
  kd_usize_t n, i, match_cnt, idx;

  if (!idx_ptr || !ptr || !sz || !key_blocks || !key_block_sz || !num)
  {
    return KD_RESULT_FAILURE;
  }

  idx     = 0;
  src_ptr = ptr;

  while (sz--)
  {
    key_blocks_ptr = key_blocks;
    n              = num;

    while (n--)
    {
      i          = 0;
      match_cnt  = 0;
      search_ptr = src_ptr;

      while (i < key_block_sz)
      {
        match_cnt += *search_ptr == *(key_blocks_ptr + i++);
        ++search_ptr;
      }

      if (match_cnt == key_block_sz)
      {
        *idx_ptr = idx;
        return KD_RESULT_SUCCESS;
      }

      key_blocks_ptr += key_block_sz;
    }

    src_ptr += key_block_sz;
    idx += key_block_sz;
  }

  return KD_RESULT_FAILURE;
}


kd_usize_t
kdGenMemOpsBytesSpn(void* ptr, kd_usize_t sz, void* keys, kd_usize_t num)
{
  kd_byte_t *src_ptr, *keys_ptr;
  kd_usize_t i, count;
  kd_bool_t  match;

  if (!ptr || !sz || !keys || !num)
  {
    return 0;
  }

  src_ptr = ptr;
  count   = 0;

  while (sz--)
  {
    keys_ptr = keys;
    i        = num;
    match    = KD_RESULT_FAILURE;

    while (i--)
    {
      if (*keys_ptr == *src_ptr)
      {
        match = KD_RESULT_SUCCESS;
        break;
      }
      ++keys_ptr;
    }

    if (!match)
    {
      if (src_ptr == (kd_byte_t*)ptr)
      {
        return 0;
      }
      break;
    }

    count += match;
    ++src_ptr;
  }

  return count;
}


kd_usize_t
kdGenMemOpsBlocksSpn(void* ptr, kd_usize_t sz, void* key_blocks, kd_usize_t key_block_sz, kd_usize_t num)
{
  kd_byte_t *src_ptr, *search_ptr, *key_blocks_ptr;
  kd_usize_t n, i, match_cnt, count;
  kd_bool_t  match;

  if (!ptr || !sz || !key_blocks || !key_block_sz || !num)
  {
    return 0;
  }

  src_ptr = ptr;
  count   = 0;

  while (sz--)
  {
    key_blocks_ptr = key_blocks;
    n              = num;
    match          = KD_RESULT_FAILURE;

    while (n--)
    {
      i          = 0;
      match_cnt  = 0;
      search_ptr = src_ptr;

      while (i < key_block_sz)
      {
        match_cnt += *search_ptr == *(key_blocks_ptr + i++);
        ++search_ptr;
      }

      if (match_cnt == key_block_sz)
      {
        match = KD_RESULT_SUCCESS;
        break;
      }

      key_blocks_ptr += key_block_sz;
    }

    if (!match)
    {
      if (src_ptr == (kd_byte_t*)ptr)
      {
        return 0;
      }
      break;
    }

    count += key_block_sz;
    src_ptr += key_block_sz;
  }

  return count;
}
