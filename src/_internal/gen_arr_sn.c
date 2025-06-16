/**
 * @file gen_arr_sn.c
 * @author Kumarjit Das
 * @date 2025-06-16
 * @since 0.0.11
 * @brief Main source file of the GEN_ARR_SN library (internal).
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
#include "_internal/common.h"
#include "_internal/gen_mem_ops_sn.h"
#include "_internal/gen_arr_sn.h"
#include "kd/gen_arr.h"


void*
kdi_GenArrCreate(kd_u32_t el_sz, kd_usize_t sz, kd_bool_t (*allocator)(void*, kd_usize_t))
{
  kd_byte_t* mem;

  if (!allocator((void*)&mem, sz + KDI_GEN_ARR_HEAD_OFFSET))
  {
    return kd_null;
  }

#if defined KD_ENDIAN_BIG
  *KD_PU32_C(mem) =
  #if defined KD_ARCH_32BIT_INT
    KDI_GEN_ARR_ARC_32BIT_BITMASK |
  #endif
    KDI_GEN_ARR_BE_BITMASK | KDI_GEN_ARR_ID_BITMASK | KD_U32_C(el_sz & KDI_GEN_ARR_EL_SIZE_MASK);
#else /* !defined KD_ENDIAN_BIG */
  *KD_PU32_C(mem) = (
  #if defined KD_ARCH_32BIT_INT
                      KDI_GEN_ARR_ARC_32BIT_BITMASK |
  #endif
                      KDI_GEN_ARR_ID_BITMASK
                    ) &
    0xFFFFFFFF;

  *KD_PU32_C(mem + KD_SZ_BYTE) = el_sz;
#endif /* #if defined KD_ENDIAN_BIG */

  *KD_PUSIZE_C(mem + KDI_GEN_ARR_EL_SIZE_SZ) = sz;

  return KD_PTR_C(mem + KDI_GEN_ARR_HEAD_OFFSET);
}
