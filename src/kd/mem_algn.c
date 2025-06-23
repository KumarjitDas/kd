/**
 * @file mem_algn.c
 * @author Kumarjit Das
 * @date 2025-06-01
 * @since 0.0.6
 * @brief Main source file of the MEM_ALGN library.
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
#include "kd/mem_algn.h"


static kd_bool_t
kdi_IsPowerOfTwo(kd_usize_t n)
{
  return n && !(n & (n - 1));
}


static kd_bool_t
kdi_IsValidAlgnSize(kd_u8_t algn_sz)
{
  return (algn_sz != 0) && kdi_IsPowerOfTwo(algn_sz) && (algn_sz <= KD_MEM_ALGN_MAX_ALGN_SIZE);
}


static kd_bool_t
kdi_IsValidOffset(kd_u8_t offset)
{
  return !offset || (kdi_IsPowerOfTwo(offset) && (offset <= KD_MEM_ALGN_MAX_OFFSET));
}


kd_usize_t
kdMemAlgnGetAllocSize(kd_usize_t usable_size, kd_u8_t algn_sz, kd_u8_t offset)
{
  if (!usable_size || !algn_sz || !kdi_IsValidAlgnSize(algn_sz) || !kdi_IsValidOffset(offset))
  {
    return 0;
  }
  return offset + algn_sz + usable_size;
}


void *
kdMemAlgnGetForwardPtr(void *head_ptr, kd_u8_t algn_sz, kd_u8_t offset)
{
  if (!head_ptr || !algn_sz || !kdi_IsValidAlgnSize(algn_sz) || !kdi_IsValidOffset(offset))
  {
    return kd_null;
  }

  kd_u8_t *forward = (kd_u8_t *)head_ptr + offset + algn_sz;

  return forward - ((kd_usize_t)forward % algn_sz);
}


void *
kdMemAlgnGetBackwardPtr(void *head_ptr, kd_u8_t algn_sz, kd_u8_t offset)
{
  kd_u8_t *forward = kdMemAlgnGetForwardPtr(head_ptr, algn_sz, offset);
  if (!forward)
  {
    return kd_null;
  }

  kd_u8_t *backward = forward;

  while (backward >= (kd_u8_t *)head_ptr)
  {
    backward -= algn_sz;
  }

  return backward;
}


void *
kdMemAlgnGetOffsetPtr(void *head_ptr, kd_u8_t algn_sz, kd_u8_t offset)
{
  void *forward = kdMemAlgnGetForwardPtr(head_ptr, algn_sz, offset);
  if (forward)
  {
    switch (offset)
    {
      case KD_SZ_U8:
        *((kd_u8_t *)forward - offset) = (kd_u8_t)((kd_u8_t *)forward - (kd_u8_t *)head_ptr);
        break;
      case KD_SZ_U16:
        *(kd_u16_t *)((kd_u8_t *)forward - offset) = (kd_u16_t)((kd_u8_t *)forward - (kd_u8_t *)head_ptr);
        break;
      case KD_SZ_U32:
        *(kd_u32_t *)((kd_u8_t *)forward - offset) = (kd_u32_t)((kd_u8_t *)forward - (kd_u8_t *)head_ptr);
        break;
      default:
        *(kd_umax_t *)((kd_u8_t *)forward - offset) = (kd_umax_t)((kd_u8_t *)forward - (kd_u8_t *)head_ptr);
    }
  }

  return forward;
}


void *
kdMemAlgnGetHeadPtr(void *off_ptr, kd_u8_t offset)
{
  if (!off_ptr || !kdi_IsValidOffset(offset))
  {
    return kd_null;
  }

  kd_umax_t head_offset = 0;

  switch (offset)
  {
    case KD_SZ_U8:
      head_offset = *((kd_u8_t *)off_ptr - offset);
      break;
    case KD_SZ_U16:
      head_offset = *(kd_u16_t *)((kd_u8_t *)off_ptr - offset);
      break;
    case KD_SZ_U32:
      head_offset = *(kd_u32_t *)((kd_u8_t *)off_ptr - offset);
      break;
    default:
      head_offset = *(kd_umax_t *)((kd_u8_t *)off_ptr - offset);
  }

  return (kd_u8_t *)off_ptr - head_offset;
}
