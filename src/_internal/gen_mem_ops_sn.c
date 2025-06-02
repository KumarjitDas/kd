/**
 * @file gen_mem_ops_sn.c
 * @author Kumarjit Das
 * @date 2025-06-02
 * @since 0.0.8
 * @brief Main source file of the GEN_MEM_OPS_SN library (internal).
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


void
kdi_GenMemOpsSetBlocks_S8(kd_u8_t* ptr, kd_usize_t sz, kd_u8_t val)
{
  while (sz--)
  {
    *ptr = val;
    ++ptr;
  }
}


void
kdi_GenMemOpsSetBlocks_S16(kd_u16_t* ptr, kd_usize_t sz, kd_u16_t val)
{
  while (sz)
  {
    *ptr = val;
    ++ptr;
    sz -= sizeof(kd_u16_t);
  }
}


void
kdi_GenMemOpsSetBlocks_S32(kd_u32_t* ptr, kd_usize_t sz, kd_u32_t val)
{
  while (sz)
  {
    *ptr = val;
    ++ptr;
    sz -= sizeof(kd_u32_t);
  }
}


#if defined KD_ARCH_64BIT_INT
void
kdi_GenMemOpsSetBlocks_S64(kd_u64_t* ptr, kd_usize_t sz, kd_u64_t val)
{
  while (sz)
  {
    *ptr = val;
    ++ptr;
    sz -= sizeof(kd_u64_t);
  }
}
#endif


void
kdi_GenMemOpsSetBlocks_Sn(void* ptr, kd_usize_t sz, void* block, kd_usize_t block_sz)
{
  kd_byte_t *dst_ptr, *block_ptr;
  kd_usize_t i;

  dst_ptr = ptr;

  while (sz)
  {
    block_ptr = block;
    i         = block_sz;

    while (i-- && sz--)
    {
      *dst_ptr = *block_ptr;
      ++dst_ptr;
      ++block_ptr;
    }
  }
}


void*
kdi_GenMemOpsFindBlockWithIndex_S8(kd_usize_t* idx_ptr, kd_u8_t* ptr, kd_usize_t sz, kd_u8_t val)
{
  kd_usize_t idx = 0;

  while (sz--)
  {
    if (*ptr == val)
    {
      if (idx_ptr)
      {
        *idx_ptr = idx;
      }
      return ptr;
    }

    ++ptr;
    ++idx;
  }

  return kd_null;
}


void*
kdi_GenMemOpsFindBlockWithIndex_S16(kd_usize_t* idx_ptr, kd_u16_t* ptr, kd_usize_t sz, kd_u16_t val)
{
  kd_usize_t idx = 0;

  while (sz)
  {
    if (*ptr == val)
    {
      if (idx_ptr)
      {
        *idx_ptr = idx;
      }
      return ptr;
    }

    ++ptr;
    idx += sizeof(kd_u16_t);
    sz -= sizeof(kd_u16_t);
  }

  return kd_null;
}


void*
kdi_GenMemOpsFindBlockWithIndex_S32(kd_usize_t* idx_ptr, kd_u32_t* ptr, kd_usize_t sz, kd_u32_t val)
{
  kd_usize_t idx = 0;

  while (sz)
  {
    if (*ptr == val)
    {
      if (idx_ptr)
      {
        *idx_ptr = idx;
      }
      return ptr;
    }

    ++ptr;
    idx += sizeof(kd_u32_t);
    sz -= sizeof(kd_u32_t);
  }

  return kd_null;
}


#if defined KD_ARCH_64BIT_INT
void*
kdi_GenMemOpsFindBlockWithIndex_S64(kd_usize_t* idx_ptr, kd_u64_t* ptr, kd_usize_t sz, kd_u64_t val)
{
  kd_usize_t idx = 0;

  while (sz)
  {
    if (*ptr == val)
    {
      if (idx_ptr)
      {
        *idx_ptr = idx;
      }
      return ptr;
    }

    ++ptr;
    idx += sizeof(kd_u64_t);
    sz -= sizeof(kd_u64_t);
  }

  return kd_null;
}


#endif
void*
kdi_GenMemOpsFindBlockWithIndex_Sn(kd_usize_t* idx_ptr, void* ptr, kd_usize_t sz, void* block, kd_usize_t block_sz)
{
  kd_byte_t *src_ptr = ptr, *block_ptr;
  kd_usize_t i, idx = 0, match_cnt;

  while (sz)
  {
    block_ptr = block;
    i         = 0;
    match_cnt = 0;

    while (i-- && sz--)
    {
      match_cnt += *src_ptr == *block_ptr;
      ++src_ptr;
      ++block_ptr;
    }

    if (match_cnt == block_sz)
    {
      if (idx_ptr)
      {
        *idx_ptr = idx;
      }
      return src_ptr - block_sz;
    }

    idx += block_sz;
  }

  return kd_null;
}


void*
kdi_GenMemOpsBlocksCompSpnWithIndex_S8(kd_usize_t* idx_ptr, kd_u8_t* ptr, kd_usize_t sz, kd_u8_t* keys,
                                       kd_usize_t keys_sz)
{
  kd_u8_t*   tmp_keys;
  kd_usize_t i, idx = 0;

  while (sz--)
  {
    tmp_keys = keys;
    i        = keys_sz;

    while (i--)
    {
      if (*tmp_keys == *ptr)
      {
        if (idx_ptr)
        {
          *idx_ptr = idx;
        }
        return ptr;
      }
      ++tmp_keys;
    }

    ++ptr;
    ++idx;
  }

  return kd_null;
}


void*
kdi_GenMemOpsBlocksCompSpnWithIndex_S16(kd_usize_t* idx_ptr, kd_u16_t* ptr, kd_usize_t sz, kd_u16_t* keys,
                                        kd_usize_t keys_sz)
{
  kd_u16_t*  tmp_keys;
  kd_usize_t i, idx = 0;

  while (sz)
  {
    tmp_keys = keys;
    i        = keys_sz;

    while (i)
    {
      if (*tmp_keys == *ptr)
      {
        if (idx_ptr)
        {
          *idx_ptr = idx;
        }
        return ptr;
      }
      ++tmp_keys;
      i -= sizeof(kd_u16_t);
    }

    ++ptr;
    idx += sizeof(kd_u16_t);
    sz -= sizeof(kd_u16_t);
  }

  return kd_null;
}


void*
kdi_GenMemOpsBlocksCompSpnWithIndex_S32(kd_usize_t* idx_ptr, kd_u32_t* ptr, kd_usize_t sz, kd_u32_t* keys,
                                        kd_usize_t keys_sz)
{
  kd_u32_t*  tmp_keys;
  kd_usize_t i, idx = 0;

  while (sz)
  {
    tmp_keys = keys;
    i        = keys_sz;

    while (i)
    {
      if (*tmp_keys == *ptr)
      {
        if (idx_ptr)
        {
          *idx_ptr = idx;
        }
        return ptr;
      }
      ++tmp_keys;
      i -= sizeof(kd_u32_t);
    }

    ++ptr;
    idx += sizeof(kd_u32_t);
    sz -= sizeof(kd_u32_t);
  }

  return kd_null;
}


#if defined KD_ARCH_64BIT_INT
void*
kdi_GenMemOpsBlocksCompSpnWithIndex_S64(kd_usize_t* idx_ptr, kd_u64_t* ptr, kd_usize_t sz, kd_u64_t* keys,
                                        kd_usize_t keys_sz)
{
  kd_u64_t*  tmp_keys;
  kd_usize_t i, idx = 0;

  while (sz)
  {
    tmp_keys = keys;
    i        = keys_sz;

    while (i)
    {
      if (*tmp_keys == *ptr)
      {
        if (idx_ptr)
        {
          *idx_ptr = idx;
        }
        return ptr;
      }
      ++tmp_keys;
      i -= sizeof(kd_u64_t);
    }

    ++ptr;
    idx += sizeof(kd_u64_t);
    sz -= sizeof(kd_u64_t);
  }

  return kd_null;
}
#endif


void*
kdi_GenMemOpsBlocksCompSpnWithIndex_Sn(kd_usize_t* idx_ptr, void* ptr, kd_usize_t sz, void* key_blocks,
                                       kd_usize_t key_block_sz, kd_usize_t key_blocks_sz)
{
  kd_byte_t *src_ptr = ptr, *search_ptr, *key_blocks_ptr;
  kd_usize_t n, i, idx = 0, match_cnt;

  while (sz--)
  {
    key_blocks_ptr = key_blocks;
    n              = key_blocks_sz;

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
        if (idx_ptr)
        {
          *idx_ptr = idx;
        }
        return src_ptr;
      }

      key_blocks_ptr += key_block_sz;
    }

    src_ptr += key_block_sz;
    idx += key_block_sz;
  }

  return kd_null;
}


kd_usize_t
kdi_GenMemOpsBlocksSpn_S8(kd_u8_t* ptr, kd_usize_t sz, kd_u8_t* keys, kd_usize_t keys_sz)
{
  kd_u8_t *  tmp_ptr = ptr, *tmp_keys;
  kd_usize_t i, count = 0;
  kd_bool_t  match;

  while (sz--)
  {
    tmp_keys = keys;
    i        = keys_sz;
    match    = KD_RESULT_FAILURE;

    while (i--)
    {
      if (*tmp_keys == *tmp_ptr)
      {
        match = KD_RESULT_SUCCESS;
        break;
      }
      ++tmp_keys;
    }

    if (!match)
    {
      if (tmp_ptr == ptr)
      {
        return 0;
      }
      break;
    }

    count += match;
    ++tmp_ptr;
  }

  return count;
}


kd_usize_t
kdi_GenMemOpsBlocksSpn_S16(kd_u16_t* ptr, kd_usize_t sz, kd_u16_t* keys, kd_usize_t keys_sz)
{
  kd_u16_t * tmp_ptr = ptr, *tmp_keys;
  kd_usize_t i, count = 0;
  kd_bool_t  match;

  while (sz)
  {
    tmp_keys = keys;
    i        = keys_sz;
    match    = KD_RESULT_FAILURE;

    while (i)
    {
      if (*tmp_keys == *tmp_ptr)
      {
        match = KD_RESULT_SUCCESS;
        break;
      }
      ++tmp_keys;
      i -= sizeof(kd_u16_t);
    }

    if (!match)
    {
      if (tmp_ptr == ptr)
      {
        return 0;
      }
      break;
    }

    ++tmp_ptr;
    count += sizeof(kd_u16_t);
    sz -= sizeof(kd_u16_t);
  }

  return count;
}


kd_usize_t
kdi_GenMemOpsBlocksSpn_S32(kd_u32_t* ptr, kd_usize_t sz, kd_u32_t* keys, kd_usize_t keys_sz)
{
  kd_u32_t * tmp_ptr = ptr, *tmp_keys;
  kd_usize_t i, count = 0;
  kd_bool_t  match;

  while (sz)
  {
    tmp_keys = keys;
    i        = keys_sz;
    match    = KD_RESULT_FAILURE;

    while (i)
    {
      if (*tmp_keys == *tmp_ptr)
      {
        match = KD_RESULT_SUCCESS;
        break;
      }
      ++tmp_keys;
      i -= sizeof(kd_u32_t);
    }

    if (!match)
    {
      if (tmp_ptr == ptr)
      {
        return 0;
      }
      break;
    }

    ++tmp_ptr;
    count += sizeof(kd_u32_t);
    sz -= sizeof(kd_u32_t);
  }

  return count;
}


#if defined KD_ARCH_64BIT_INT
kd_usize_t
kdi_GenMemOpsBlocksSpn_S64(kd_u64_t* ptr, kd_usize_t sz, kd_u64_t* keys, kd_usize_t keys_sz)
{
  kd_u64_t * tmp_ptr = ptr, *tmp_keys;
  kd_usize_t i, count = 0;
  kd_bool_t  match;

  while (sz)
  {
    tmp_keys = keys;
    i        = keys_sz;
    match    = KD_RESULT_FAILURE;

    while (i)
    {
      if (*tmp_keys == *tmp_ptr)
      {
        match = KD_RESULT_SUCCESS;
        break;
      }
      ++tmp_keys;
      i -= sizeof(kd_u64_t);
    }

    if (!match)
    {
      if (tmp_ptr == ptr)
      {
        return 0;
      }
      break;
    }

    ++tmp_ptr;
    count += sizeof(kd_u64_t);
    sz -= sizeof(kd_u64_t);
  }

  return count;
}
#endif


kd_usize_t
kdi_GenMemOpsBlocksSpn_Sn(void* ptr, kd_usize_t sz, void* key_blocks, kd_usize_t key_block_sz, kd_usize_t key_blocks_sz)
{
  kd_byte_t *src_ptr = ptr, *search_ptr, *key_blocks_ptr;
  kd_usize_t n, i, match_cnt, count = 0;
  kd_bool_t  match;

  while (sz--)
  {
    key_blocks_ptr = key_blocks;
    n              = key_blocks_sz;
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
