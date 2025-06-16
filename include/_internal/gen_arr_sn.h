/**
 * @file gen_arr_sn.h
 * @author Kumarjit Das
 * @date 2025-06-16
 * @since 0.0.11
 * @brief Main header file of the GEN_ARR_SN library (internal).
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


#ifndef KD__INTERNAL_GEN_ARR_H_
#define KD__INTERNAL_GEN_ARR_H_

#include "common.h"

KD_EXTERN_BEGIN


#define KDI_GEN_ARR_DS_TYPE_MASK (0xFF000000)
#define KDI_GEN_ARR_EL_SIZE_MASK (0x00FFFFFF)

#define KDI_GEN_ARR_ID_BITMASK        (0x01000000)
#define KDI_GEN_ARR_DYN_BITMASK       (0x20000000)
#define KDI_GEN_ARR_BE_BITMASK        (0x40000000)
#define KDI_GEN_ARR_ARC_32BIT_BITMASK (0x80000000)

#define KDI_GEN_ARR_EL_SIZE_SZ  (KD_SZ_U32)
#define KDI_GEN_ARR_MEM_SIZE_SZ (KD_SZ_USIZE)
#define KDI_GEN_ARR_HEAD_OFFSET (KDI_GEN_ARR_EL_SIZE_SZ + KDI_GEN_ARR_MEM_SIZE_SZ)

#if defined KD_ENDIAN_BIG
  #define kdi_GenArrGetElemSize(arr) (*KD_PI32_C(KD_PBYTE_C(arr) - KDI_GEN_ARR_HEAD_OFFSET) & KDI_GEN_ARR_EL_SIZE_MASK)
#else /* !defined KD_ENDIAN_BIG */
  #define kdi_GenArrGetElemSize(arr)                                                                                   \
    ((*KD_PI32_C(KD_PBYTE_C(arr) - KDI_GEN_ARR_HEAD_OFFSET) & KDI_GEN_ARR_EL_SIZE_MASK) >> 8)
#endif /* KD_ENDIAN_BIG */

#define kdi_GenArrGetMemSize(arr) (*KD_PUSIZE_C(KD_PBYTE_C(arr) - KDI_GEN_ARR_MEM_SIZE_SZ))

KDAPI(void*) kdi_GenArrCreate(kd_u32_t el_sz, kd_usize_t sz, kd_bool_t (*allocator)(void*, kd_usize_t));


KD_EXTERN_END

#endif /* KD__INTERNAL_GEN_ARR_H_ */
