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
#include "_internal/common.h"
#include "_internal/gen_mem_ops_sn.h"


void
kdi_GenMemOpsSwapBlocks_S8(kd_u8_t* ptr, kd_usize_t idx1, kd_usize_t idx2)
{
  kd_u8_t* ptr1 = ptr + idx1;
  kd_u8_t  temp = *ptr1;

  ptr += idx2;
  *ptr1 = *ptr;
  *ptr  = temp;
}


void
kdi_GenMemOpsSwapBlocks_S16(kd_u16_t* ptr, kd_usize_t idx1, kd_usize_t idx2)
{
  kd_u16_t* ptr1 = (kd_u16_t*)((kd_u8_t*)ptr + idx1);
  kd_u16_t  temp = *ptr1;

  ptr   = (kd_u16_t*)((kd_u8_t*)ptr + idx2);
  *ptr1 = *ptr;
  *ptr  = temp;
}


void
kdi_GenMemOpsSwapBlocks_S32(kd_u32_t* ptr, kd_usize_t idx1, kd_usize_t idx2)
{
  kd_u32_t* ptr1 = (kd_u32_t*)((kd_u8_t*)ptr + idx1);
  kd_u32_t  temp = *ptr1;

  ptr   = (kd_u32_t*)((kd_u8_t*)ptr + idx2);
  *ptr1 = *ptr;
  *ptr  = temp;
}


#if defined KD_ARCH_64BIT_INT
void
kdi_GenMemOpsSwapBlocks_S64(kd_u64_t* ptr, kd_usize_t idx1, kd_usize_t idx2)
{
  kd_u64_t* ptr1 = (kd_u64_t*)((kd_u8_t*)ptr + idx1);
  kd_u64_t  temp = *ptr1;

  ptr   = (kd_u64_t*)((kd_u8_t*)ptr + idx2);
  *ptr1 = *ptr;
  *ptr  = temp;
}
#endif


void
kdi_GenMemOpsSwapBlocks_Sn(void* ptr, kd_usize_t block_sz, kd_usize_t idx1, kd_usize_t idx2)
{
  kd_u8_t* ptr1 = (kd_byte_t*)ptr + idx1;
  kd_u8_t* ptr2 = (kd_byte_t*)ptr + idx2;
  kd_u8_t  temp;

  while (block_sz--)
  {
    temp  = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;

    ++ptr1;
    ++ptr2;
  }
}


void
kdi_GenMemOpsReverseBlocks_S8(kd_u8_t* ptr, kd_usize_t sz)
{
  kd_u8_t* end = ptr + sz;
  kd_u8_t  temp;

  while (sz-- && ptr < end)
  {
    --end;

    temp = *ptr;
    *ptr = *end;
    *end = temp;

    ++ptr;
  }
}


void
kdi_GenMemOpsReverseBlocks_S16(kd_u16_t* ptr, kd_usize_t sz)
{
  kd_u16_t* end = (kd_u16_t*)((kd_u8_t*)ptr + sz);
  kd_u16_t  temp;

  while (sz-- && ptr < end)
  {
    --end;

    temp = *ptr;
    *ptr = *end;
    *end = temp;

    ++ptr;
  }
}


void
kdi_GenMemOpsReverseBlocks_S32(kd_u32_t* ptr, kd_usize_t sz)
{
  kd_u32_t* end = (kd_u32_t*)((kd_u8_t*)ptr + sz);
  kd_u32_t  temp;

  while (sz-- && ptr < end)
  {
    --end;

    temp = *ptr;
    *ptr = *end;
    *end = temp;

    ++ptr;
  }
}


#if defined KD_ARCH_64BIT_INT
void
kdi_GenMemOpsReverseBlocks_S64(kd_u64_t* ptr, kd_usize_t sz)
{
  kd_u64_t* end = (kd_u64_t*)((kd_u8_t*)ptr + sz);
  kd_u64_t  temp;

  while (sz-- && ptr < end)
  {
    --end;

    temp = *ptr;
    *ptr = *end;
    *end = temp;

    ++ptr;
  }
}
#endif


void
kdi_GenMemOpsReverseBlocks_Sn(void* ptr, kd_usize_t sz, kd_usize_t block_sz)
{
  kd_u8_t *  begin = ptr, *end = begin + sz, *temp_end, temp;
  kd_usize_t temp_block_sz;

  while (sz-- && begin < end)
  {
    end -= block_sz;
    temp_end      = end;
    temp_block_sz = block_sz;

    while (temp_block_sz--)
    {
      temp      = *begin;
      *begin    = *temp_end;
      *temp_end = temp;

      ++begin;
      ++temp_end;
    }
  }
}


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
    sz -= KD_SZ_S16;
  }
}


void
kdi_GenMemOpsSetBlocks_S32(kd_u32_t* ptr, kd_usize_t sz, kd_u32_t val)
{
  while (sz)
  {
    *ptr = val;
    ++ptr;
    sz -= KD_SZ_S32;
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
    sz -= KD_SZ_S64;
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


void
kdi_GenMemOpsMove(kd_byte_t* dst, kd_byte_t* src, kd_usize_t sz)
{
  if (dst == src)
  {
    return;
  }

  if (dst < src)
  {
    while (sz--)
    {
      *dst = *src;
      ++dst;
      ++src;
    }
    return;
  }

  dst += sz;
  src += sz;

  while (sz--)
  {
    --dst;
    --src;
    *dst = *src;
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
    idx += KD_SZ_S16;
    sz -= KD_SZ_S16;
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
    idx += KD_SZ_S32;
    sz -= KD_SZ_S32;
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
    idx += KD_SZ_S64;
    sz -= KD_SZ_S64;
  }

  return kd_null;
}
#endif


void*
kdi_GenMemOpsFindBlockWithIndex_Sn(kd_usize_t* idx_ptr, void* ptr, kd_usize_t sz, void* block, kd_usize_t block_sz)
{
  kd_byte_t *src_ptr = ptr, *temp_src_ptr, *block_ptr;
  kd_usize_t i, idx = 0, temp_sz, match_cnt;

  while (sz)
  {
    temp_src_ptr = src_ptr;
    block_ptr    = block;
    temp_sz      = sz;
    i            = block_sz;
    match_cnt    = 0;

    while (i-- && temp_sz--)
    {
      if (*temp_src_ptr != *block_ptr)
      {
        break;
      }

      ++temp_src_ptr;
      ++block_ptr;
      ++match_cnt;
    }

    if (match_cnt == block_sz)
    {
      if (idx_ptr)
      {
        *idx_ptr = idx;
      }
      return src_ptr;
    }

    idx += block_sz;
    src_ptr += block_sz;
    sz -= block_sz;
  }

  return kd_null;
}


void*
kdi_GenMemOpsFindLastBlockWithIndex_S8(kd_usize_t* idx_ptr, kd_u8_t* ptr, kd_usize_t sz, kd_u8_t val)
{
  ptr += sz;

  while (sz--)
  {
    --ptr;

    if (*ptr == val)
    {
      if (idx_ptr)
      {
        *idx_ptr = sz;
      }
      return ptr;
    }
  }

  return kd_null;
}


void*
kdi_GenMemOpsFindLastBlockWithIndex_S16(kd_usize_t* idx_ptr, kd_u16_t* ptr, kd_usize_t sz, kd_u16_t val)
{
  ptr = (kd_u16_t*)((kd_byte_t*)ptr + sz);

  while (sz)
  {
    ptr = (kd_u16_t*)((kd_byte_t*)ptr - KD_SZ_S16);
    sz -= KD_SZ_S16;

    if (*ptr == val)
    {
      if (idx_ptr)
      {
        *idx_ptr = sz;
      }
      return ptr;
    }
  }

  return kd_null;
}


void*
kdi_GenMemOpsFindLastBlockWithIndex_S32(kd_usize_t* idx_ptr, kd_u32_t* ptr, kd_usize_t sz, kd_u32_t val)
{
  ptr = (kd_u32_t*)((kd_byte_t*)ptr + sz);

  while (sz)
  {
    ptr = (kd_u32_t*)((kd_byte_t*)ptr - KD_SZ_S32);
    sz -= KD_SZ_S32;

    if (*ptr == val)
    {
      if (idx_ptr)
      {
        *idx_ptr = sz;
      }
      return ptr;
    }
  }

  return kd_null;
}


#if defined KD_ARCH_64BIT_INT
void*
kdi_GenMemOpsFindLastBlockWithIndex_S64(kd_usize_t* idx_ptr, kd_u64_t* ptr, kd_usize_t sz, kd_u64_t val)
{
  ptr = (kd_u64_t*)((kd_byte_t*)ptr + sz);

  while (sz)
  {
    ptr = (kd_u64_t*)((kd_byte_t*)ptr - KD_SZ_S64);
    sz -= KD_SZ_S64;

    if (*ptr == val)
    {
      if (idx_ptr)
      {
        *idx_ptr = sz;
      }
      return ptr;
    }
  }

  return kd_null;
}
#endif


void*
kdi_GenMemOpsFindLastBlockWithIndex_Sn(kd_usize_t* idx_ptr, void* ptr, kd_usize_t sz, void* block, kd_usize_t block_sz)
{
  kd_byte_t *src_ptr = (kd_byte_t*)ptr + sz, *temp_src_ptr, *block_ptr;
  kd_usize_t i, temp_sz, match_cnt;

  while (sz)
  {
    src_ptr -= block_sz;
    sz -= block_sz;

    temp_src_ptr = src_ptr;
    block_ptr    = block;
    temp_sz      = sz;
    i            = block_sz;
    match_cnt    = 0;

    while (i-- && temp_sz--)
    {
      if (*temp_src_ptr != *block_ptr)
      {
        break;
      }

      ++temp_src_ptr;
      ++block_ptr;
      ++match_cnt;
    }

    if (match_cnt == block_sz)
    {
      if (idx_ptr)
      {
        *idx_ptr = sz;
      }
      return src_ptr;
    }
  }

  return kd_null;
}


kd_usize_t
kdi_GenMemOpsFindAllBlocksWithIndex_S8(
  kd_usize_t* idxs,
  kd_usize_t  idxs_sz,
  kd_u8_t*    ptr,
  kd_usize_t  ptr_sz,
  kd_u8_t     val
)
{
  kd_usize_t idx = 0, found_cnt = 0;

  while (ptr_sz-- && idxs_sz)
  {
    if (*ptr == val)
    {
      *idxs = idx;
      ++idxs;
      ++found_cnt;
      --idxs_sz;
    }

    ++ptr;
    ++idx;
  }

  return found_cnt;
}


kd_usize_t
kdi_GenMemOpsFindAllBlocksWithIndex_S16(
  kd_usize_t* idxs,
  kd_usize_t  idxs_sz,
  kd_u16_t*   ptr,
  kd_usize_t  ptr_sz,
  kd_u16_t    val
)
{
  kd_usize_t idx = 0, found_cnt = 0;

  while (ptr_sz && idxs_sz)
  {
    ptr_sz -= KD_SZ_S16;

    if (*ptr == val)
    {
      *idxs = idx;
      idxs  = (kd_usize_t*)((kd_byte_t*)idxs + KD_SZ_USIZE);
      idxs_sz -= KD_SZ_USIZE;
      ++found_cnt;
    }

    ptr = (kd_u16_t*)((kd_byte_t*)ptr + KD_SZ_S16);
    idx += KD_SZ_S16;
  }

  return found_cnt;
}


kd_usize_t
kdi_GenMemOpsFindAllBlocksWithIndex_S32(
  kd_usize_t* idxs,
  kd_usize_t  idxs_sz,
  kd_u32_t*   ptr,
  kd_usize_t  ptr_sz,
  kd_u32_t    val
)
{
  kd_usize_t idx = 0, found_cnt = 0;

  while (ptr_sz && idxs_sz)
  {
    ptr_sz -= KD_SZ_S32;

    if (*ptr == val)
    {
      *idxs = idx;
      idxs  = (kd_usize_t*)((kd_byte_t*)idxs + KD_SZ_USIZE);
      idxs_sz -= KD_SZ_USIZE;
      ++found_cnt;
    }

    ptr = (kd_u32_t*)((kd_byte_t*)ptr + KD_SZ_S32);
    idx += KD_SZ_S32;
  }

  return found_cnt;
}


#if defined KD_ARCH_64BIT_INT
kd_usize_t
kdi_GenMemOpsFindAllBlocksWithIndex_S64(
  kd_usize_t* idxs,
  kd_usize_t  idxs_sz,
  kd_u64_t*   ptr,
  kd_usize_t  ptr_sz,
  kd_u64_t    val
)
{
  kd_usize_t idx = 0, found_cnt = 0;

  while (ptr_sz && idxs_sz)
  {
    ptr_sz -= KD_SZ_S64;

    if (*ptr == val)
    {
      *idxs = idx;
      idxs  = (kd_usize_t*)((kd_byte_t*)idxs + KD_SZ_USIZE);
      idxs_sz -= KD_SZ_USIZE;
      ++found_cnt;
    }

    ptr = (kd_u64_t*)((kd_byte_t*)ptr + KD_SZ_S64);
    idx += KD_SZ_S64;
  }

  return found_cnt;
}


#endif
kd_usize_t
kdi_GenMemOpsFindAllBlocksWithIndex_Sn(
  kd_usize_t* idxs,
  kd_usize_t  idxs_sz,
  void*       ptr,
  kd_usize_t  ptr_sz,
  void*       block,
  kd_usize_t  block_sz
)
{
  kd_byte_t *temp_ptr = ptr, *block_ptr;
  kd_usize_t idx = 0, found_cnt = 0, match_cnt, temp_block_sz;

  while (ptr_sz && idxs_sz)
  {
    ptr_sz -= block_sz;

    block_ptr     = block;
    temp_block_sz = block_sz;
    match_cnt     = 0;

    while (temp_block_sz--)
    {
      match_cnt += *temp_ptr == *block_ptr;
      ++temp_ptr;
      ++block_ptr;
    }

    if (match_cnt == block_sz)
    {
      *idxs = idx;
      idxs  = (kd_usize_t*)((kd_byte_t*)idxs + KD_SZ_USIZE);
      idxs_sz -= KD_SZ_USIZE;
      ++found_cnt;
    }

    idx += block_sz;
  }

  return found_cnt;
}


void*
kdi_GenMemOpsBlocksCompSpnWithIndex_S8(
  kd_usize_t* idx_ptr,
  kd_u8_t*    ptr,
  kd_usize_t  sz,
  kd_u8_t*    keys,
  kd_usize_t  keys_sz
)
{
  kd_u8_t*   temp_keys;
  kd_usize_t i, idx = 0;

  while (sz--)
  {
    temp_keys = keys;
    i         = keys_sz;

    while (i--)
    {
      if (*temp_keys == *ptr)
      {
        if (idx_ptr)
        {
          *idx_ptr = idx;
        }
        return ptr;
      }
      ++temp_keys;
    }

    ++ptr;
    ++idx;
  }

  return kd_null;
}


void*
kdi_GenMemOpsBlocksCompSpnWithIndex_S16(
  kd_usize_t* idx_ptr,
  kd_u16_t*   ptr,
  kd_usize_t  sz,
  kd_u16_t*   keys,
  kd_usize_t  keys_sz
)
{
  kd_u16_t*  temp_keys;
  kd_usize_t i, idx = 0;

  while (sz)
  {
    temp_keys = keys;
    i         = keys_sz;

    while (i)
    {
      if (*temp_keys == *ptr)
      {
        if (idx_ptr)
        {
          *idx_ptr = idx;
        }
        return ptr;
      }
      ++temp_keys;
      i -= KD_SZ_S16;
    }

    ++ptr;
    idx += KD_SZ_S16;
    sz -= KD_SZ_S16;
  }

  return kd_null;
}


void*
kdi_GenMemOpsBlocksCompSpnWithIndex_S32(
  kd_usize_t* idx_ptr,
  kd_u32_t*   ptr,
  kd_usize_t  sz,
  kd_u32_t*   keys,
  kd_usize_t  keys_sz
)
{
  kd_u32_t*  temp_keys;
  kd_usize_t i, idx = 0;

  while (sz)
  {
    temp_keys = keys;
    i         = keys_sz;

    while (i)
    {
      if (*temp_keys == *ptr)
      {
        if (idx_ptr)
        {
          *idx_ptr = idx;
        }
        return ptr;
      }
      ++temp_keys;
      i -= KD_SZ_S32;
    }

    ++ptr;
    idx += KD_SZ_S32;
    sz -= KD_SZ_S32;
  }

  return kd_null;
}


#if defined KD_ARCH_64BIT_INT
void*
kdi_GenMemOpsBlocksCompSpnWithIndex_S64(
  kd_usize_t* idx_ptr,
  kd_u64_t*   ptr,
  kd_usize_t  sz,
  kd_u64_t*   keys,
  kd_usize_t  keys_sz
)
{
  kd_u64_t*  temp_keys;
  kd_usize_t i, idx = 0;

  while (sz)
  {
    temp_keys = keys;
    i         = keys_sz;

    while (i)
    {
      if (*temp_keys == *ptr)
      {
        if (idx_ptr)
        {
          *idx_ptr = idx;
        }
        return ptr;
      }
      ++temp_keys;
      i -= KD_SZ_S64;
    }

    ++ptr;
    idx += KD_SZ_S64;
    sz -= KD_SZ_S64;
  }

  return kd_null;
}
#endif


void*
kdi_GenMemOpsBlocksCompSpnWithIndex_Sn(
  kd_usize_t* idx_ptr,
  void*       ptr,
  kd_usize_t  sz,
  void*       key_blocks,
  kd_usize_t  key_block_sz,
  kd_usize_t  key_blocks_sz
)
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
  kd_u8_t *  temp_ptr = ptr, *temp_keys;
  kd_usize_t i, count = 0;
  kd_bool_t  match;

  while (sz--)
  {
    temp_keys = keys;
    i         = keys_sz;
    match     = KD_RESULT_FAILURE;

    while (i--)
    {
      if (*temp_keys == *temp_ptr)
      {
        match = KD_RESULT_SUCCESS;
        break;
      }
      ++temp_keys;
    }

    if (!match)
    {
      if (temp_ptr == ptr)
      {
        return 0;
      }
      break;
    }

    count += match;
    ++temp_ptr;
  }

  return count;
}


kd_usize_t
kdi_GenMemOpsBlocksSpn_S16(kd_u16_t* ptr, kd_usize_t sz, kd_u16_t* keys, kd_usize_t keys_sz)
{
  kd_u16_t * temp_ptr = ptr, *temp_keys;
  kd_usize_t i, count = 0;
  kd_bool_t  match;

  while (sz)
  {
    temp_keys = keys;
    i         = keys_sz;
    match     = KD_RESULT_FAILURE;

    while (i)
    {
      if (*temp_keys == *temp_ptr)
      {
        match = KD_RESULT_SUCCESS;
        break;
      }
      ++temp_keys;
      i -= KD_SZ_S16;
    }

    if (!match)
    {
      if (temp_ptr == ptr)
      {
        return 0;
      }
      break;
    }

    ++temp_ptr;
    count += KD_SZ_S16;
    sz -= KD_SZ_S16;
  }

  return count;
}


kd_usize_t
kdi_GenMemOpsBlocksSpn_S32(kd_u32_t* ptr, kd_usize_t sz, kd_u32_t* keys, kd_usize_t keys_sz)
{
  kd_u32_t * temp_ptr = ptr, *temp_keys;
  kd_usize_t i, count = 0;
  kd_bool_t  match;

  while (sz)
  {
    temp_keys = keys;
    i         = keys_sz;
    match     = KD_RESULT_FAILURE;

    while (i)
    {
      if (*temp_keys == *temp_ptr)
      {
        match = KD_RESULT_SUCCESS;
        break;
      }
      ++temp_keys;
      i -= KD_SZ_S32;
    }

    if (!match)
    {
      if (temp_ptr == ptr)
      {
        return 0;
      }
      break;
    }

    ++temp_ptr;
    count += KD_SZ_S32;
    sz -= KD_SZ_S32;
  }

  return count;
}


#if defined KD_ARCH_64BIT_INT
kd_usize_t
kdi_GenMemOpsBlocksSpn_S64(kd_u64_t* ptr, kd_usize_t sz, kd_u64_t* keys, kd_usize_t keys_sz)
{
  kd_u64_t * temp_ptr = ptr, *temp_keys;
  kd_usize_t i, count = 0;
  kd_bool_t  match;

  while (sz)
  {
    temp_keys = keys;
    i         = keys_sz;
    match     = KD_RESULT_FAILURE;

    while (i)
    {
      if (*temp_keys == *temp_ptr)
      {
        match = KD_RESULT_SUCCESS;
        break;
      }
      ++temp_keys;
      i -= KD_SZ_S64;
    }

    if (!match)
    {
      if (temp_ptr == ptr)
      {
        return 0;
      }
      break;
    }

    ++temp_ptr;
    count += KD_SZ_S64;
    sz -= KD_SZ_S64;
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
