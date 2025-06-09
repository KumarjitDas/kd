/**
 * @file gen_mem_ops_sn.h
 * @author Kumarjit Das
 * @date 2025-06-02
 * @since 0.0.8
 * @brief Main header file of the GEN_MEM_OPS_SN library (internal).
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


#ifndef KD__INTERNAL_GEN_MEM_OPS_SN_H_
#define KD__INTERNAL_GEN_MEM_OPS_SN_H_

#include "common.h"

KD_EXTERN_BEGIN


#define kdi_GenMemOpsSwapBlocks_Byte(ptr, idx1, idx2)                                                                  \
  kdi_GenMemOpsSwapBlocks_S8((kd_u8_t*)(ptr), (kd_usize_t)(idx1), (kd_usize_t)(idx2))
#define kdi_GenMemOpsSwapBlocks_I8(ptr, idx1, idx2)                                                                    \
  kdi_GenMemOpsSwapBlocks_S8((kd_u8_t*)(ptr), (kd_usize_t)(idx1), (kd_usize_t)(idx2))
#define kdi_GenMemOpsSwapBlocks_U8(ptr, idx1, idx2)                                                                    \
  kdi_GenMemOpsSwapBlocks_S8((kd_u8_t*)(ptr), (kd_usize_t)(idx1), (kd_usize_t)(idx2))

#define kdi_GenMemOpsSwapBlocks_I16(ptr, idx1, idx2)                                                                   \
  kdi_GenMemOpsSwapBlocks_S16((kd_u16_t*)(ptr), (kd_usize_t)(idx1), (kd_usize_t)(idx2))
#define kdi_GenMemOpsSwapBlocks_U16(ptr, idx1, idx2)                                                                   \
  kdi_GenMemOpsSwapBlocks_S16((kd_u16_t*)(ptr), (kd_usize_t)(idx1), (kd_usize_t)(idx2))

#define kdi_GenMemOpsSwapBlocks_I32(ptr, idx1, idx2)                                                                   \
  kdi_GenMemOpsSwapBlocks_S32((kd_u32_t*)(ptr), (kd_usize_t)(idx1), (kd_usize_t)(idx2))
#define kdi_GenMemOpsSwapBlocks_U32(ptr, idx1, idx2)                                                                   \
  kdi_GenMemOpsSwapBlocks_S32((kd_u32_t*)(ptr), (kd_usize_t)(idx1), (kd_usize_t)(idx2))

#if defined KD_ARCH_64BIT_INT
  #define kdi_GenMemOpsSwapBlocks_I64(ptr, idx1, idx2)                                                                 \
    kdi_GenMemOpsSwapBlocks_S64((kd_u64_t*)(ptr), (kd_usize_t)(idx1), (kd_usize_t)(idx2))
  #define kdi_GenMemOpsSwapBlocks_U64(ptr, idx1, idx2)                                                                 \
    kdi_GenMemOpsSwapBlocks_S64((kd_u64_t*)(ptr), (kd_usize_t)(idx1), (kd_usize_t)(idx2))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsSwapBlocks_Imin(ptr, idx1, idx2)                                                                  \
  kdi_GenMemOpsSwapBlocks_S8((kd_u8_t*)(ptr), (kd_usize_t)(idx1), (kd_usize_t)(idx2))
#define kdi_GenMemOpsSwapBlocks_Umin(ptr, idx1, idx2)                                                                  \
  kdi_GenMemOpsSwapBlocks_S8((kd_u8_t*)(ptr), (kd_usize_t)(idx1), (kd_usize_t)(idx2))

#if defined KD_ARCH_64BIT_INT
  #define kdi_GenMemOpsSwapBlocks_Imax(ptr, idx1, idx2)                                                                \
    kdi_GenMemOpsSwapBlocks_S64((kd_u64_t*)(ptr), (kd_usize_t)(idx1), (kd_usize_t)(idx2))
  #define kdi_GenMemOpsSwapBlocks_Umax(ptr, idx1, idx2)                                                                \
    kdi_GenMemOpsSwapBlocks_S64((kd_u64_t*)(ptr), (kd_usize_t)(idx1), (kd_usize_t)(idx2))
  #define kdi_GenMemOpsSwapBlocks_Usize(ptr, idx1, idx2)                                                               \
    kdi_GenMemOpsSwapBlocks_S64((kd_u64_t*)(ptr), (kd_usize_t)(idx1), (kd_usize_t)(idx2))
#else
  #define kdi_GenMemOpsSwapBlocks_Imax(ptr, idx1, idx2)                                                                \
    kdi_GenMemOpsSwapBlocks_S32((kd_u32_t*)(ptr), (kd_usize_t)(idx1), (kd_usize_t)(idx2))
  #define kdi_GenMemOpsSwapBlocks_Umax(ptr, idx1, idx2)                                                                \
    kdi_GenMemOpsSwapBlocks_S32((kd_u32_t*)(ptr), (kd_usize_t)(idx1), (kd_usize_t)(idx2))
  #define kdi_GenMemOpsSwapBlocks_Usize(ptr, idx1, idx2)                                                               \
    kdi_GenMemOpsSwapBlocks_S32((kd_u32_t*)(ptr), (kd_usize_t)(idx1), (kd_usize_t)(idx2))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsSwapBlocks_Bool(ptr, idx1, idx2)                                                                  \
  kdi_GenMemOpsSwapBlocks_S32((kd_u32_t*)(ptr), (kd_usize_t)(idx1), (kd_usize_t)(idx2))

#define kdi_GenMemOpsSwapBlocks_Chr(ptr, idx1, idx2)                                                                   \
  kdi_GenMemOpsSwapBlocks_S32((kd_u32_t*)(ptr), (kd_usize_t)(idx1), (kd_usize_t)(idx2))

#if defined KD_ARCH_64BIT_PTR
  #define kdi_GenMemOpsSwapBlocks_Ptr(ptr, idx1, idx2)                                                                 \
    kdi_GenMemOpsSwapBlocks_S64((kd_u64_t*)(ptr), (kd_usize_t)(idx1), (kd_usize_t)(idx2))
#else
  #define kdi_GenMemOpsSwapBlocks_Ptr(ptr, idx1, idx2)                                                                 \
    kdi_GenMemOpsSwapBlocks_S32((kd_u32_t*)(ptr), (kd_usize_t)(idx1), (kd_usize_t)(idx2))
#endif /* KD_ARCH_64BIT_PTR */


#define kdi_GenMemOpsReverseBlocks_Byte(ptr, len) kdi_GenMemOpsReverseBlocks_S8((kd_u8_t*)(ptr), (kd_usize_t)(len))
#define kdi_GenMemOpsReverseBlocks_I8(ptr, len)   kdi_GenMemOpsReverseBlocks_S8((kd_u8_t*)(ptr), (kd_usize_t)(len))
#define kdi_GenMemOpsReverseBlocks_U8(ptr, len)   kdi_GenMemOpsReverseBlocks_S8((kd_u8_t*)(ptr), (kd_usize_t)(len))
#define kdi_GenMemOpsReverseBlocks_I16(ptr, len)  kdi_GenMemOpsReverseBlocks_S16((kd_u16_t*)(ptr), (kd_usize_t)(len))
#define kdi_GenMemOpsReverseBlocks_U16(ptr, len)  kdi_GenMemOpsReverseBlocks_S16((kd_u16_t*)(ptr), (kd_usize_t)(len))
#define kdi_GenMemOpsReverseBlocks_I32(ptr, len)  kdi_GenMemOpsReverseBlocks_S32((kd_u32_t*)(ptr), (kd_usize_t)(len))
#define kdi_GenMemOpsReverseBlocks_U32(ptr, len)  kdi_GenMemOpsReverseBlocks_S32((kd_u32_t*)(ptr), (kd_usize_t)(len))

#if defined KD_ARCH_64BIT_INT
  #define kdi_GenMemOpsReverseBlocks_I64(ptr, len) kdi_GenMemOpsReverseBlocks_S64((kd_u64_t*)(ptr), (kd_usize_t)(len))
  #define kdi_GenMemOpsReverseBlocks_U64(ptr, len) kdi_GenMemOpsReverseBlocks_S64((kd_u64_t*)(ptr), (kd_usize_t)(len))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsReverseBlocks_Imin(ptr, len) kdi_GenMemOpsReverseBlocks_S8((kd_u8_t*)(ptr), (kd_usize_t)(len))
#define kdi_GenMemOpsReverseBlocks_Umin(ptr, len) kdi_GenMemOpsReverseBlocks_S8((kd_u8_t*)(ptr), (kd_usize_t)(len))

#if defined KD_ARCH_64BIT_INT
  #define kdi_GenMemOpsReverseBlocks_Imax(ptr, len)  kdi_GenMemOpsReverseBlocks_S64((kd_u64_t*)(ptr), (kd_usize_t)(len))
  #define kdi_GenMemOpsReverseBlocks_Umax(ptr, len)  kdi_GenMemOpsReverseBlocks_S64((kd_u64_t*)(ptr), (kd_usize_t)(len))
  #define kdi_GenMemOpsReverseBlocks_Usize(ptr, len) kdi_GenMemOpsReverseBlocks_S64((kd_u64_t*)(ptr), (kd_usize_t)(len))
#else
  #define kdi_GenMemOpsReverseBlocks_Imax(ptr, len)  kdi_GenMemOpsReverseBlocks_S32((kd_u32_t*)(ptr), (kd_usize_t)(len))
  #define kdi_GenMemOpsReverseBlocks_Umax(ptr, len)  kdi_GenMemOpsReverseBlocks_S32((kd_u32_t*)(ptr), (kd_usize_t)(len))
  #define kdi_GenMemOpsReverseBlocks_Usize(ptr, len) kdi_GenMemOpsReverseBlocks_S32((kd_u32_t*)(ptr), (kd_usize_t)(len))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsReverseBlocks_Bool(ptr, len) kdi_GenMemOpsReverseBlocks_S32((kd_u32_t*)(ptr), (kd_usize_t)(len))
#define kdi_GenMemOpsReverseBlocks_Chr(ptr, len)  kdi_GenMemOpsReverseBlocks_S32((kd_u32_t*)(ptr), (kd_usize_t)(len))

#if defined KD_ARCH_64BIT_PTR
  #define kdi_GenMemOpsReverseBlocks_Ptr(ptr, len) kdi_GenMemOpsReverseBlocks_S64((kd_u64_t*)(ptr), (kd_usize_t)(len))
#else
  #define kdi_GenMemOpsReverseBlocks_Ptr(ptr, len) kdi_GenMemOpsReverseBlocks_S32((kd_u32_t*)(ptr), (kd_usize_t)(len))
#endif /* KD_ARCH_64BIT_PTR */


#define kdi_GenMemOpsSetBlocks_Byte(ptr, sz, val)                                                                      \
  kdi_GenMemOpsSetBlocks_S8((kd_u8_t*)(ptr), (kd_usize_t)(sz), (kd_u8_t)(val))
#define kdi_GenMemOpsSetBlocks_I8(ptr, sz, val)                                                                        \
  kdi_GenMemOpsSetBlocks_S8((kd_u8_t*)(ptr), (kd_usize_t)(sz), (kd_u8_t)(val))
#define kdi_GenMemOpsSetBlocks_U8(ptr, sz, val)                                                                        \
  kdi_GenMemOpsSetBlocks_S8((kd_u8_t*)(ptr), (kd_usize_t)(sz), (kd_u8_t)(val))

#define kdi_GenMemOpsSetBlocks_I16(ptr, sz, val)                                                                       \
  kdi_GenMemOpsSetBlocks_S16((kd_u16_t*)(ptr), (kd_usize_t)(sz), (kd_u16_t)(val))
#define kdi_GenMemOpsSetBlocks_U16(ptr, sz, val)                                                                       \
  kdi_GenMemOpsSetBlocks_S16((kd_u16_t*)(ptr), (kd_usize_t)(sz), (kd_u16_t)(val))

#define kdi_GenMemOpsSetBlocks_I32(ptr, sz, val)                                                                       \
  kdi_GenMemOpsSetBlocks_S32((kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t)(val))
#define kdi_GenMemOpsSetBlocks_U32(ptr, sz, val)                                                                       \
  kdi_GenMemOpsSetBlocks_S32((kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t)(val))

#if defined KD_ARCH_64BIT_INT
  #define kdi_GenMemOpsSetBlocks_I64(ptr, sz, val)                                                                     \
    kdi_GenMemOpsSetBlocks_S64((kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t)(val))
  #define kdi_GenMemOpsSetBlocks_U64(ptr, sz, val)                                                                     \
    kdi_GenMemOpsSetBlocks_S64((kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t)(val))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsSetBlocks_Imin(ptr, sz, val)                                                                      \
  kdi_GenMemOpsSetBlocks_S8((kd_u8_t*)(ptr), (kd_usize_t)(sz), (kd_u8_t)(val))
#define kdi_GenMemOpsSetBlocks_Umin(ptr, sz, val)                                                                      \
  kdi_GenMemOpsSetBlocks_S8((kd_u8_t*)(ptr), (kd_usize_t)(sz), (kd_u8_t)(val))

#if defined KD_ARCH_64BIT_INT
  #define kdi_GenMemOpsSetBlocks_Imax(ptr, sz, val)                                                                    \
    kdi_GenMemOpsSetBlocks_S64((kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t)(val))
  #define kdi_GenMemOpsSetBlocks_Umax(ptr, sz, val)                                                                    \
    kdi_GenMemOpsSetBlocks_S64((kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t)(val))
  #define kdi_GenMemOpsSetBlocks_Usize(ptr, sz, val)                                                                   \
    kdi_GenMemOpsSetBlocks_S64((kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t)(val))
#else
  #define kdi_GenMemOpsSetBlocks_Imax(ptr, sz, val)                                                                    \
    kdi_GenMemOpsSetBlocks_S32((kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t)(val))
  #define kdi_GenMemOpsSetBlocks_Umax(ptr, sz, val)                                                                    \
    kdi_GenMemOpsSetBlocks_S32((kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t)(val))
  #define kdi_GenMemOpsSetBlocks_Usize(ptr, sz, val)                                                                   \
    kdi_GenMemOpsSetBlocks_S32((kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t)(val))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsSetBlocks_Bool(ptr, sz, val)                                                                      \
  kdi_GenMemOpsSetBlocks_S32((kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t)(val))

#define kdi_GenMemOpsSetBlocks_Chr(ptr, sz, val)                                                                       \
  kdi_GenMemOpsSetBlocks_S32((kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t)(val))

#if defined KD_ARCH_64BIT_PTR
  #define kdi_GenMemOpsSetBlocks_Ptr(ptr, sz, val)                                                                     \
    kdi_GenMemOpsSetBlocks_S64((kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t)(val))
#else
  #define kdi_GenMemOpsSetBlocks_Ptr(ptr, sz, val)                                                                     \
    kdi_GenMemOpsSetBlocks_S32((kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t)(val))
#endif /* KD_ARCH_64BIT_PTR */


#define kdi_GenMemOpsFindBlockWithIndex_Byte(idx_ptr, ptr, sz, val)                                                    \
  kdi_GenMemOpsFindBlockWithIndex_S8((kd_usize_t*)(idx_ptr), (kd_u8_t*)(ptr), (kd_usize_t)(sz), (kd_u8_t)(val))
#define kdi_GenMemOpsFindBlockWithIndex_I8(idx_ptr, ptr, sz, val)                                                      \
  kdi_GenMemOpsFindBlockWithIndex_S8((kd_usize_t*)(idx_ptr), (kd_u8_t*)(ptr), (kd_usize_t)(sz), (kd_u8_t)(val))
#define kdi_GenMemOpsFindBlockWithIndex_U8(idx_ptr, ptr, sz, val)                                                      \
  kdi_GenMemOpsFindBlockWithIndex_S8((kd_usize_t*)(idx_ptr), (kd_u8_t*)(ptr), (kd_usize_t)(sz), (kd_u8_t)(val))

#define kdi_GenMemOpsFindBlockWithIndex_I16(idx_ptr, ptr, sz, val)                                                     \
  kdi_GenMemOpsFindBlockWithIndex_S16((kd_usize_t*)(idx_ptr), (kd_u16_t*)(ptr), (kd_usize_t)(sz), (kd_u16_t)(val))
#define kdi_GenMemOpsFindBlockWithIndex_U16(idx_ptr, ptr, sz, val)                                                     \
  kdi_GenMemOpsFindBlockWithIndex_S16((kd_usize_t*)(idx_ptr), (kd_u16_t*)(ptr), (kd_usize_t)(sz), (kd_u16_t)(val))

#define kdi_GenMemOpsFindBlockWithIndex_I32(idx_ptr, ptr, sz, val)                                                     \
  kdi_GenMemOpsFindBlockWithIndex_S32((kd_usize_t*)(idx_ptr), (kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t)(val))
#define kdi_GenMemOpsFindBlockWithIndex_U32(idx_ptr, ptr, sz, val)                                                     \
  kdi_GenMemOpsFindBlockWithIndex_S32((kd_usize_t*)(idx_ptr), (kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t)(val))

#if defined KD_ARCH_64BIT_INT
  #define kdi_GenMemOpsFindBlockWithIndex_I64(idx_ptr, ptr, sz, val)                                                   \
    kdi_GenMemOpsFindBlockWithIndex_S64((kd_usize_t*)(idx_ptr), (kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t)(val))
  #define kdi_GenMemOpsFindBlockWithIndex_U64(idx_ptr, ptr, sz, val)                                                   \
    kdi_GenMemOpsFindBlockWithIndex_S64((kd_usize_t*)(idx_ptr), (kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t)(val))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsFindBlockWithIndex_Imin(idx_ptr, ptr, sz, val)                                                    \
  kdi_GenMemOpsFindBlockWithIndex_S8((kd_usize_t*)(idx_ptr), (kd_u8_t*)(ptr), (kd_usize_t)(sz), (kd_u8_t)(val))
#define kdi_GenMemOpsFindBlockWithIndex_Umin(idx_ptr, ptr, sz, val)                                                    \
  kdi_GenMemOpsFindBlockWithIndex_S8((kd_usize_t*)(idx_ptr), (kd_u8_t*)(ptr), (kd_usize_t)(sz), (kd_u8_t)(val))

#if defined KD_ARCH_64BIT_INT
  #define kdi_GenMemOpsFindBlockWithIndex_Imax(idx_ptr, ptr, sz, val)                                                  \
    kdi_GenMemOpsFindBlockWithIndex_S64((kd_usize_t*)(idx_ptr), (kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t)(val))
  #define kdi_GenMemOpsFindBlockWithIndex_Umax(idx_ptr, ptr, sz, val)                                                  \
    kdi_GenMemOpsFindBlockWithIndex_S64((kd_usize_t*)(idx_ptr), (kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t)(val))
  #define kdi_GenMemOpsFindBlockWithIndex_Usize(idx_ptr, ptr, sz, val)                                                 \
    kdi_GenMemOpsFindBlockWithIndex_S64((kd_usize_t*)(idx_ptr), (kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t)(val))
#else
  #define kdi_GenMemOpsFindBlockWithIndex_Imax(idx_ptr, ptr, sz, val)                                                  \
    kdi_GenMemOpsFindBlockWithIndex_S32((kd_usize_t*)(idx_ptr), (kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t)(val))
  #define kdi_GenMemOpsFindBlockWithIndex_Umax(idx_ptr, ptr, sz, val)                                                  \
    kdi_GenMemOpsFindBlockWithIndex_S32((kd_usize_t*)(idx_ptr), (kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t)(val))
  #define kdi_GenMemOpsFindBlockWithIndex_Usize(idx_ptr, ptr, sz, val)                                                 \
    kdi_GenMemOpsFindBlockWithIndex_S32((kd_usize_t*)(idx_ptr), (kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t)(val))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsFindBlockWithIndex_Bool(idx_ptr, ptr, sz, val)                                                    \
  kdi_GenMemOpsFindBlockWithIndex_S32((kd_usize_t*)(idx_ptr), (kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t)(val))

#define kdi_GenMemOpsFindBlockWithIndex_Chr(idx_ptr, ptr, sz, val)                                                     \
  kdi_GenMemOpsFindBlockWithIndex_S32((kd_usize_t*)(idx_ptr), (kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t)(val))

#if defined KD_ARCH_64BIT_PTR
  #define kdi_GenMemOpsFindBlockWithIndex_Ptr(idx_ptr, ptr, sz, val)                                                   \
    kdi_GenMemOpsFindBlockWithIndex_S64((kd_usize_t*)(idx_ptr), (kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t)(val))
#else
  #define kdi_GenMemOpsFindBlockWithIndex_Ptr(idx_ptr, ptr, sz, val)                                                   \
    kdi_GenMemOpsFindBlockWithIndex_S32((kd_usize_t*)(idx_ptr), (kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t)(val))
#endif /* KD_ARCH_64BIT_PTR */


#define kdi_GenMemOpsFindLastBlockWithIndex_Byte(idx_ptr, ptr, sz, val)                                                \
  kdi_GenMemOpsFindLastBlockWithIndex_S8((kd_usize_t*)(idx_ptr), (kd_u8_t*)(ptr), (kd_usize_t)(sz), (kd_u8_t)(val))
#define kdi_GenMemOpsFindLastBlockWithIndex_I8(idx_ptr, ptr, sz, val)                                                  \
  kdi_GenMemOpsFindLastBlockWithIndex_S8((kd_usize_t*)(idx_ptr), (kd_u8_t*)(ptr), (kd_usize_t)(sz), (kd_u8_t)(val))
#define kdi_GenMemOpsFindLastBlockWithIndex_U8(idx_ptr, ptr, sz, val)                                                  \
  kdi_GenMemOpsFindLastBlockWithIndex_S8((kd_usize_t*)(idx_ptr), (kd_u8_t*)(ptr), (kd_usize_t)(sz), (kd_u8_t)(val))

#define kdi_GenMemOpsFindLastBlockWithIndex_I16(idx_ptr, ptr, sz, val)                                                 \
  kdi_GenMemOpsFindLastBlockWithIndex_S16((kd_usize_t*)(idx_ptr), (kd_u16_t*)(ptr), (kd_usize_t)(sz), (kd_u16_t)(val))
#define kdi_GenMemOpsFindLastBlockWithIndex_U16(idx_ptr, ptr, sz, val)                                                 \
  kdi_GenMemOpsFindLastBlockWithIndex_S16((kd_usize_t*)(idx_ptr), (kd_u16_t*)(ptr), (kd_usize_t)(sz), (kd_u16_t)(val))

#define kdi_GenMemOpsFindLastBlockWithIndex_I32(idx_ptr, ptr, sz, val)                                                 \
  kdi_GenMemOpsFindLastBlockWithIndex_S32((kd_usize_t*)(idx_ptr), (kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t)(val))
#define kdi_GenMemOpsFindLastBlockWithIndex_U32(idx_ptr, ptr, sz, val)                                                 \
  kdi_GenMemOpsFindLastBlockWithIndex_S32((kd_usize_t*)(idx_ptr), (kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t)(val))

#if defined KD_ARCH_64BIT_INT
  #define kdi_GenMemOpsFindLastBlockWithIndex_I64(idx_ptr, ptr, sz, val)                                               \
    kdi_GenMemOpsFindLastBlockWithIndex_S64((kd_usize_t*)(idx_ptr), (kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t)(val))
  #define kdi_GenMemOpsFindLastBlockWithIndex_U64(idx_ptr, ptr, sz, val)                                               \
    kdi_GenMemOpsFindLastBlockWithIndex_S64((kd_usize_t*)(idx_ptr), (kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t)(val))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsFindLastBlockWithIndex_Imin(idx_ptr, ptr, sz, val)                                                \
  kdi_GenMemOpsFindLastBlockWithIndex_S8((kd_usize_t*)(idx_ptr), (kd_u8_t*)(ptr), (kd_usize_t)(sz), (kd_u8_t)(val))
#define kdi_GenMemOpsFindLastBlockWithIndex_Umin(idx_ptr, ptr, sz, val)                                                \
  kdi_GenMemOpsFindLastBlockWithIndex_S8((kd_usize_t*)(idx_ptr), (kd_u8_t*)(ptr), (kd_usize_t)(sz), (kd_u8_t)(val))

#if defined KD_ARCH_64BIT_INT
  #define kdi_GenMemOpsFindLastBlockWithIndex_Imax(idx_ptr, ptr, sz, val)                                              \
    kdi_GenMemOpsFindLastBlockWithIndex_S64((kd_usize_t*)(idx_ptr), (kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t)(val))
  #define kdi_GenMemOpsFindLastBlockWithIndex_Umax(idx_ptr, ptr, sz, val)                                              \
    kdi_GenMemOpsFindLastBlockWithIndex_S64((kd_usize_t*)(idx_ptr), (kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t)(val))
  #define kdi_GenMemOpsFindLastBlockWithIndex_Usize(idx_ptr, ptr, sz, val)                                             \
    kdi_GenMemOpsFindLastBlockWithIndex_S64((kd_usize_t*)(idx_ptr), (kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t)(val))
#else
  #define kdi_GenMemOpsFindLastBlockWithIndex_Imax(idx_ptr, ptr, sz, val)                                              \
    kdi_GenMemOpsFindLastBlockWithIndex_S32((kd_usize_t*)(idx_ptr), (kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t)(val))
  #define kdi_GenMemOpsFindLastBlockWithIndex_Umax(idx_ptr, ptr, sz, val)                                              \
    kdi_GenMemOpsFindLastBlockWithIndex_S32((kd_usize_t*)(idx_ptr), (kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t)(val))
  #define kdi_GenMemOpsFindLastBlockWithIndex_Usize(idx_ptr, ptr, sz, val)                                             \
    kdi_GenMemOpsFindLastBlockWithIndex_S32((kd_usize_t*)(idx_ptr), (kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t)(val))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsFindLastBlockWithIndex_Bool(idx_ptr, ptr, sz, val)                                                \
  kdi_GenMemOpsFindLastBlockWithIndex_S32((kd_usize_t*)(idx_ptr), (kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t)(val))

#define kdi_GenMemOpsFindLastBlockWithIndex_Chr(idx_ptr, ptr, sz, val)                                                 \
  kdi_GenMemOpsFindLastBlockWithIndex_S32((kd_usize_t*)(idx_ptr), (kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t)(val))

#if defined KD_ARCH_64BIT_PTR
  #define kdi_GenMemOpsFindLastBlockWithIndex_Ptr(idx_ptr, ptr, sz, val)                                               \
    kdi_GenMemOpsFindLastBlockWithIndex_S64((kd_usize_t*)(idx_ptr), (kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t)(val))
#else
  #define kdi_GenMemOpsFindLastBlockWithIndex_Ptr(idx_ptr, ptr, sz, val)                                               \
    kdi_GenMemOpsFindLastBlockWithIndex_S32((kd_usize_t*)(idx_ptr), (kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t)(val))
#endif /* KD_ARCH_64BIT_PTR */


#define kdi_GenMemOpsFindAllBlocksWithIndex_Byte(idxs, idxs_sz, ptr, ptr_sz, val)                                      \
  kdi_GenMemOpsFindAllBlocksWithIndex_S8(                                                                              \
    (kd_usize_t*)(idxs), (kd_usize_t)(idxs_sz), (kd_u8_t*)(ptr), (kd_usize_t)(ptr_sz), (kd_u8_t)(val)                  \
  )
#define kdi_GenMemOpsFindAllBlocksWithIndex_I8(idxs, idxs_sz, ptr, ptr_sz, val)                                        \
  kdi_GenMemOpsFindAllBlocksWithIndex_S8(                                                                              \
    (kd_usize_t*)(idxs), (kd_usize_t)(idxs_sz), (kd_u8_t*)(ptr), (kd_usize_t)(ptr_sz), (kd_u8_t)(val)                  \
  )
#define kdi_GenMemOpsFindAllBlocksWithIndex_U8(idxs, idxs_sz, ptr, ptr_sz, val)                                        \
  kdi_GenMemOpsFindAllBlocksWithIndex_S8(                                                                              \
    (kd_usize_t*)(idxs), (kd_usize_t)(idxs_sz), (kd_u8_t*)(ptr), (kd_usize_t)(ptr_sz), (kd_u8_t)(val)                  \
  )

#define kdi_GenMemOpsFindAllBlocksWithIndex_I16(idxs, idxs_sz, ptr, ptr_sz, val)                                       \
  kdi_GenMemOpsFindAllBlocksWithIndex_S16(                                                                             \
    (kd_usize_t*)(idxs), (kd_usize_t)(idxs_sz), (kd_u16_t*)(ptr), (kd_usize_t)(ptr_sz), (kd_u16_t)(val)                \
  )
#define kdi_GenMemOpsFindAllBlocksWithIndex_U16(idxs, idxs_sz, ptr, ptr_sz, val)                                       \
  kdi_GenMemOpsFindAllBlocksWithIndex_S16(                                                                             \
    (kd_usize_t*)(idxs), (kd_usize_t)(idxs_sz), (kd_u16_t*)(ptr), (kd_usize_t)(ptr_sz), (kd_u16_t)(val)                \
  )

#define kdi_GenMemOpsFindAllBlocksWithIndex_I32(idxs, idxs_sz, ptr, ptr_sz, val)                                       \
  kdi_GenMemOpsFindAllBlocksWithIndex_S32(                                                                             \
    (kd_usize_t*)(idxs), (kd_usize_t)(idxs_sz), (kd_u32_t*)(ptr), (kd_usize_t)(ptr_sz), (kd_u32_t)(val)                \
  )
#define kdi_GenMemOpsFindAllBlocksWithIndex_U32(idxs, idxs_sz, ptr, ptr_sz, val)                                       \
  kdi_GenMemOpsFindAllBlocksWithIndex_S32(                                                                             \
    (kd_usize_t*)(idxs), (kd_usize_t)(idxs_sz), (kd_u32_t*)(ptr), (kd_usize_t)(ptr_sz), (kd_u32_t)(val)                \
  )

#if defined KD_ARCH_64BIT_INT
  #define kdi_GenMemOpsFindAllBlocksWithIndex_I64(idxs, idxs_sz, ptr, ptr_sz, val)                                     \
    kdi_GenMemOpsFindAllBlocksWithIndex_S64(                                                                           \
      (kd_usize_t*)(idxs), (kd_usize_t)(idxs_sz), (kd_u64_t*)(ptr), (kd_usize_t)(ptr_sz), (kd_u64_t)(val)              \
    )
  #define kdi_GenMemOpsFindAllBlocksWithIndex_U64(idxs, idxs_sz, ptr, ptr_sz, val)                                     \
    kdi_GenMemOpsFindAllBlocksWithIndex_S64(                                                                           \
      (kd_usize_t*)(idxs), (kd_usize_t)(idxs_sz), (kd_u64_t*)(ptr), (kd_usize_t)(ptr_sz), (kd_u64_t)(val)              \
    )
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsFindAllBlocksWithIndex_Imin(idxs, idxs_sz, ptr, ptr_sz, val)                                      \
  kdi_GenMemOpsFindAllBlocksWithIndex_S8(                                                                              \
    (kd_usize_t*)(idxs), (kd_usize_t)(idxs_sz), (kd_u8_t*)(ptr), (kd_usize_t)(ptr_sz), (kd_u8_t)(val)                  \
  )
#define kdi_GenMemOpsFindAllBlocksWithIndex_Umin(idxs, idxs_sz, ptr, ptr_sz, val)                                      \
  kdi_GenMemOpsFindAllBlocksWithIndex_S8(                                                                              \
    (kd_usize_t*)(idxs), (kd_usize_t)(idxs_sz), (kd_u8_t*)(ptr), (kd_usize_t)(ptr_sz), (kd_u8_t)(val)                  \
  )

#if defined KD_ARCH_64BIT_INT
  #define kdi_GenMemOpsFindAllBlocksWithIndex_Imax(idxs, idxs_sz, ptr, ptr_sz, val)                                    \
    kdi_GenMemOpsFindAllBlocksWithIndex_S64(                                                                           \
      (kd_usize_t*)(idxs), (kd_usize_t)(idxs_sz), (kd_u64_t*)(ptr), (kd_usize_t)(ptr_sz), (kd_u64_t)(val)              \
    )
  #define kdi_GenMemOpsFindAllBlocksWithIndex_Umax(idxs, idxs_sz, ptr, ptr_sz, val)                                    \
    kdi_GenMemOpsFindAllBlocksWithIndex_S64(                                                                           \
      (kd_usize_t*)(idxs), (kd_usize_t)(idxs_sz), (kd_u64_t*)(ptr), (kd_usize_t)(ptr_sz), (kd_u64_t)(val)              \
    )
  #define kdi_GenMemOpsFindAllBlocksWithIndex_Usize(idxs, idxs_sz, ptr, ptr_sz, val)                                   \
    kdi_GenMemOpsFindAllBlocksWithIndex_S64(                                                                           \
      (kd_usize_t*)(idxs), (kd_usize_t)(idxs_sz), (kd_u64_t*)(ptr), (kd_usize_t)(ptr_sz), (kd_u64_t)(val)              \
    )
#else
  #define kdi_GenMemOpsFindAllBlocksWithIndex_Imax(idxs, idxs_sz, ptr, ptr_sz, val)                                    \
    kdi_GenMemOpsFindAllBlocksWithIndex_S32(                                                                           \
      (kd_usize_t*)(idxs), (kd_usize_t)(idxs_sz), (kd_u32_t*)(ptr), (kd_usize_t)(ptr_sz), (kd_u32_t)(val)              \
    )
  #define kdi_GenMemOpsFindAllBlocksWithIndex_Umax(idxs, idxs_sz, ptr, ptr_sz, val)                                    \
    kdi_GenMemOpsFindAllBlocksWithIndex_S32(                                                                           \
      (kd_usize_t*)(idxs), (kd_usize_t)(idxs_sz), (kd_u32_t*)(ptr), (kd_usize_t)(ptr_sz), (kd_u32_t)(val)              \
    )
  #define kdi_GenMemOpsFindAllBlocksWithIndex_Usize(idxs, idxs_sz, ptr, ptr_sz, val)                                   \
    kdi_GenMemOpsFindAllBlocksWithIndex_S32(                                                                           \
      (kd_usize_t*)(idxs), (kd_usize_t)(idxs_sz), (kd_u32_t*)(ptr), (kd_usize_t)(ptr_sz), (kd_u32_t)(val)              \
    )
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsFindAllBlocksWithIndex_Bool(idxs, idxs_sz, ptr, ptr_sz, val)                                      \
  kdi_GenMemOpsFindAllBlocksWithIndex_S32(                                                                             \
    (kd_usize_t*)(idxs), (kd_usize_t)(idxs_sz), (kd_u32_t*)(ptr), (kd_usize_t)(ptr_sz), (kd_u32_t)(val)                \
  )

#define kdi_GenMemOpsFindAllBlocksWithIndex_Chr(idxs, idxs_sz, ptr, ptr_sz, val)                                       \
  kdi_GenMemOpsFindAllBlocksWithIndex_S32(                                                                             \
    (kd_usize_t*)(idxs), (kd_usize_t)(idxs_sz), (kd_u32_t*)(ptr), (kd_usize_t)(ptr_sz), (kd_u32_t)(val)                \
  )

#if defined KD_ARCH_64BIT_PTR
  #define kdi_GenMemOpsFindAllBlocksWithIndex_Ptr(idxs, idxs_sz, ptr, ptr_sz, val)                                     \
    kdi_GenMemOpsFindAllBlocksWithIndex_S64(                                                                           \
      (kd_usize_t*)(idxs), (kd_usize_t)(idxs_sz), (kd_u64_t*)(ptr), (kd_usize_t)(ptr_sz), (kd_u64_t)(val)              \
    )
#else
  #define kdi_GenMemOpsFindAllBlocksWithIndex_Ptr(idxs, idxs_sz, ptr, ptr_sz, val)                                     \
    kdi_GenMemOpsFindAllBlocksWithIndex_S32(                                                                           \
      (kd_usize_t*)(idxs), (kd_usize_t)(idxs_sz), (kd_u32_t*)(ptr), (kd_usize_t)(ptr_sz), (kd_u32_t)(val)              \
    )
#endif /* KD_ARCH_64BIT_PTR */


#define kdi_GenMemOpsBlocksCompSpnWithIndex_Byte(idx_ptr, ptr, sz, keys, keys_sz)                                      \
  kdi_GenMemOpsBlocksCompSpnWithIndex_S8(                                                                              \
    (kd_usize_t*)(idx_ptr), (kd_u8_t*)(ptr), (kd_usize_t)(sz), (kd_u8_t*)(keys), (kd_usize_t)(keys_sz)                 \
  )
#define kdi_GenMemOpsBlocksCompSpnWithIndex_I8(idx_ptr, ptr, sz, keys, keys_sz)                                        \
  kdi_GenMemOpsBlocksCompSpnWithIndex_S8(                                                                              \
    (kd_usize_t*)(idx_ptr), (kd_u8_t*)(ptr), (kd_usize_t)(sz), (kd_u8_t*)(keys), (kd_usize_t)(keys_sz)                 \
  )
#define kdi_GenMemOpsBlocksCompSpnWithIndex_U8(idx_ptr, ptr, sz, keys, keys_sz)                                        \
  kdi_GenMemOpsBlocksCompSpnWithIndex_S8(                                                                              \
    (kd_usize_t*)(idx_ptr), (kd_u8_t*)(ptr), (kd_usize_t)(sz), (kd_u8_t*)(keys), (kd_usize_t)(keys_sz)                 \
  )

#define kdi_GenMemOpsBlocksCompSpnWithIndex_I16(idx_ptr, ptr, sz, keys, keys_sz)                                       \
  kdi_GenMemOpsBlocksCompSpnWithIndex_S16(                                                                             \
    (kd_usize_t*)(idx_ptr), (kd_u16_t*)(ptr), (kd_usize_t)(sz), (kd_u16_t*)(keys), (kd_usize_t)(keys_sz)               \
  )
#define kdi_GenMemOpsBlocksCompSpnWithIndex_U16(idx_ptr, ptr, sz, keys, keys_sz)                                       \
  kdi_GenMemOpsBlocksCompSpnWithIndex_S16(                                                                             \
    (kd_usize_t*)(idx_ptr), (kd_u16_t*)(ptr), (kd_usize_t)(sz), (kd_u16_t*)(keys), (kd_usize_t)(keys_sz)               \
  )

#define kdi_GenMemOpsBlocksCompSpnWithIndex_I32(idx_ptr, ptr, sz, keys, keys_sz)                                       \
  kdi_GenMemOpsBlocksCompSpnWithIndex_S32(                                                                             \
    (kd_usize_t*)(idx_ptr), (kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t*)(keys), (kd_usize_t)(keys_sz)               \
  )
#define kdi_GenMemOpsBlocksCompSpnWithIndex_U32(idx_ptr, ptr, sz, keys, keys_sz)                                       \
  kdi_GenMemOpsBlocksCompSpnWithIndex_S32(                                                                             \
    (kd_usize_t*)(idx_ptr), (kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t*)(keys), (kd_usize_t)(keys_sz)               \
  )

#if defined KD_ARCH_64BIT_INT
  #define kdi_GenMemOpsBlocksCompSpnWithIndex_I64(idx_ptr, ptr, sz, keys, keys_sz)                                     \
    kdi_GenMemOpsBlocksCompSpnWithIndex_S64(                                                                           \
      (kd_usize_t*)(idx_ptr), (kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t*)(keys), (kd_usize_t)(keys_sz)             \
    )
  #define kdi_GenMemOpsBlocksCompSpnWithIndex_U64(idx_ptr, ptr, sz, keys, keys_sz)                                     \
    kdi_GenMemOpsBlocksCompSpnWithIndex_S64(                                                                           \
      (kd_usize_t*)(idx_ptr), (kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t*)(keys), (kd_usize_t)(keys_sz)             \
    )
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsBlocksCompSpnWithIndex_Imin(idx_ptr, ptr, sz, keys, keys_sz)                                      \
  kdi_GenMemOpsBlocksCompSpnWithIndex_S8(                                                                              \
    (kd_usize_t*)(idx_ptr), (kd_u8_t*)(ptr), (kd_usize_t)(sz), (kd_u8_t*)(keys), (kd_usize_t)(keys_sz)                 \
  )
#define kdi_GenMemOpsBlocksCompSpnWithIndex_Umin(idx_ptr, ptr, sz, keys, keys_sz)                                      \
  kdi_GenMemOpsBlocksCompSpnWithIndex_S8(                                                                              \
    (kd_usize_t*)(idx_ptr), (kd_u8_t*)(ptr), (kd_usize_t)(sz), (kd_u8_t*)(keys), (kd_usize_t)(keys_sz)                 \
  )

#if defined KD_ARCH_64BIT_INT
  #define kdi_GenMemOpsBlocksCompSpnWithIndex_Imax(idx_ptr, ptr, sz, keys, keys_sz)                                    \
    kdi_GenMemOpsBlocksCompSpnWithIndex_S64(                                                                           \
      (kd_usize_t*)(idx_ptr), (kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t*)(keys), (kd_usize_t)(keys_sz)             \
    )
  #define kdi_GenMemOpsBlocksCompSpnWithIndex_Umax(idx_ptr, ptr, sz, keys, keys_sz)                                    \
    kdi_GenMemOpsBlocksCompSpnWithIndex_S64(                                                                           \
      (kd_usize_t*)(idx_ptr), (kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t*)(keys), (kd_usize_t)(keys_sz)             \
    )
  #define kdi_GenMemOpsBlocksCompSpnWithIndex_Usize(idx_ptr, ptr, sz, keys, keys_sz)                                   \
    kdi_GenMemOpsBlocksCompSpnWithIndex_S64(                                                                           \
      (kd_usize_t*)(idx_ptr), (kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t*)(keys), (kd_usize_t)(keys_sz)             \
    )
#else
  #define kdi_GenMemOpsBlocksCompSpnWithIndex_Imax(idx_ptr, ptr, sz, keys, keys_sz)                                    \
    kdi_GenMemOpsBlocksCompSpnWithIndex_S32(                                                                           \
      (kd_usize_t*)(idx_ptr), (kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t*)(keys), (kd_usize_t)(keys_sz)             \
    )
  #define kdi_GenMemOpsBlocksCompSpnWithIndex_Umax(idx_ptr, ptr, sz, keys, keys_sz)                                    \
    kdi_GenMemOpsBlocksCompSpnWithIndex_S32(                                                                           \
      (kd_usize_t*)(idx_ptr), (kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t*)(keys), (kd_usize_t)(keys_sz)             \
    )
  #define kdi_GenMemOpsBlocksCompSpnWithIndex_Usize(idx_ptr, ptr, sz, keys, keys_sz)                                   \
    kdi_GenMemOpsBlocksCompSpnWithIndex_S32(                                                                           \
      (kd_usize_t*)(idx_ptr), (kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t*)(keys), (kd_usize_t)(keys_sz)             \
    )
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsBlocksCompSpnWithIndex_Bool(idx_ptr, ptr, sz, keys, keys_sz)                                      \
  kdi_GenMemOpsBlocksCompSpnWithIndex_S32(                                                                             \
    (kd_usize_t*)(idx_ptr), (kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t*)(keys), (kd_usize_t)(keys_sz)               \
  )

#define kdi_GenMemOpsBlocksCompSpnWithIndex_Chr(idx_ptr, ptr, sz, keys, keys_sz)                                       \
  kdi_GenMemOpsBlocksCompSpnWithIndex_S32(                                                                             \
    (kd_usize_t*)(idx_ptr), (kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t*)(keys), (kd_usize_t)(keys_sz)               \
  )

#if defined KD_ARCH_64BIT_PTR
  #define kdi_GenMemOpsBlocksCompSpnWithIndex_Ptr(idx_ptr, ptr, sz, keys, keys_sz)                                     \
    kdi_GenMemOpsBlocksCompSpnWithIndex_S64(                                                                           \
      (kd_usize_t*)(idx_ptr), (kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t*)(keys), (kd_usize_t)(keys_sz)             \
    )
#else
  #define kdi_GenMemOpsBlocksCompSpnWithIndex_Ptr(idx_ptr, ptr, sz, keys, keys_sz)                                     \
    kdi_GenMemOpsBlocksCompSpnWithIndex_S32(                                                                           \
      (kd_usize_t*)(idx_ptr), (kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t*)(keys), (kd_usize_t)(keys_sz)             \
    )
#endif /* KD_ARCH_64BIT_PTR */


#define kdi_GenMemOpsBlocksSpn_Byte(ptr, sz, keys, keys_sz)                                                            \
  kdi_GenMemOpsBlocksSpn_S8((kd_u8_t*)(ptr), (kd_usize_t)(sz), (kd_u8_t*)(keys), (kd_usize_t)(keys_sz))
#define kdi_GenMemOpsBlocksSpn_I8(ptr, sz, keys, keys_sz)                                                              \
  kdi_GenMemOpsBlocksSpn_S8((kd_u8_t*)(ptr), (kd_usize_t)(sz), (kd_u8_t*)(keys), (kd_usize_t)(keys_sz))
#define kdi_GenMemOpsBlocksSpn_U8(ptr, sz, keys, keys_sz)                                                              \
  kdi_GenMemOpsBlocksSpn_S8((kd_u8_t*)(ptr), (kd_usize_t)(sz), (kd_u8_t*)(keys), (kd_usize_t)(keys_sz))

#define kdi_GenMemOpsBlocksSpn_I16(ptr, sz, keys, keys_sz)                                                             \
  kdi_GenMemOpsBlocksSpn_S16((kd_u16_t*)(ptr), (kd_usize_t)(sz), (kd_u16_t*)(keys), (kd_usize_t)(keys_sz))
#define kdi_GenMemOpsBlocksSpn_U16(ptr, sz, keys, keys_sz)                                                             \
  kdi_GenMemOpsBlocksSpn_S16((kd_u16_t*)(ptr), (kd_usize_t)(sz), (kd_u16_t*)(keys), (kd_usize_t)(keys_sz))

#define kdi_GenMemOpsBlocksSpn_I32(ptr, sz, keys, keys_sz)                                                             \
  kdi_GenMemOpsBlocksSpn_S32((kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t*)(keys), (kd_usize_t)(keys_sz))
#define kdi_GenMemOpsBlocksSpn_U32(ptr, sz, keys, keys_sz)                                                             \
  kdi_GenMemOpsBlocksSpn_S32((kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t*)(keys), (kd_usize_t)(keys_sz))

#if defined KD_ARCH_64BIT_INT
  #define kdi_GenMemOpsBlocksSpn_I64(ptr, sz, keys, keys_sz)                                                           \
    kdi_GenMemOpsBlocksSpn_S64((kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t*)(keys), (kd_usize_t)(keys_sz))
  #define kdi_GenMemOpsBlocksSpn_U64(ptr, sz, keys, keys_sz)                                                           \
    kdi_GenMemOpsBlocksSpn_S64((kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t*)(keys), (kd_usize_t)(keys_sz))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsBlocksSpn_Imin(ptr, sz, keys, keys_sz)                                                            \
  kdi_GenMemOpsBlocksSpn_S8((kd_u8_t*)(ptr), (kd_usize_t)(sz), (kd_u8_t*)(keys), (kd_usize_t)(keys_sz))
#define kdi_GenMemOpsBlocksSpn_Umin(ptr, sz, keys, keys_sz)                                                            \
  kdi_GenMemOpsBlocksSpn_S8((kd_u8_t*)(ptr), (kd_usize_t)(sz), (kd_u8_t*)(keys), (kd_usize_t)(keys_sz))

#if defined KD_ARCH_64BIT_INT
  #define kdi_GenMemOpsBlocksSpn_Imax(ptr, sz, keys, keys_sz)                                                          \
    kdi_GenMemOpsBlocksSpn_S64((kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t*)(keys), (kd_usize_t)(keys_sz))
  #define kdi_GenMemOpsBlocksSpn_Umax(ptr, sz, keys, keys_sz)                                                          \
    kdi_GenMemOpsBlocksSpn_S64((kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t*)(keys), (kd_usize_t)(keys_sz))
  #define kdi_GenMemOpsBlocksSpn_Usize(ptr, sz, keys, keys_sz)                                                         \
    kdi_GenMemOpsBlocksSpn_S64((kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t*)(keys), (kd_usize_t)(keys_sz))
#else
  #define kdi_GenMemOpsBlocksSpn_Imax(ptr, sz, keys, keys_sz)                                                          \
    kdi_GenMemOpsBlocksSpn_S32((kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t*)(keys), (kd_usize_t)(keys_sz))
  #define kdi_GenMemOpsBlocksSpn_Umax(ptr, sz, keys, keys_sz)                                                          \
    kdi_GenMemOpsBlocksSpn_S32((kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t*)(keys), (kd_usize_t)(keys_sz))
  #define kdi_GenMemOpsBlocksSpn_Usize(ptr, sz, keys, keys_sz)                                                         \
    kdi_GenMemOpsBlocksSpn_S32((kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t*)(keys), (kd_usize_t)(keys_sz))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsBlocksSpn_Bool(ptr, sz, keys, keys_sz)                                                            \
  kdi_GenMemOpsBlocksSpn_S32((kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t*)(keys), (kd_usize_t)(keys_sz))

#define kdi_GenMemOpsBlocksSpn_Chr(ptr, sz, keys, keys_sz)                                                             \
  kdi_GenMemOpsBlocksSpn_S32((kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t*)(keys), (kd_usize_t)(keys_sz))

#if defined KD_ARCH_64BIT_PTR
  #define kdi_GenMemOpsBlocksSpn_Ptr(ptr, sz, keys, keys_sz)                                                           \
    kdi_GenMemOpsBlocksSpn_S64((kd_u64_t*)(ptr), (kd_usize_t)(sz), (kd_u64_t*)(keys), (kd_usize_t)(keys_sz))
#else
  #define kdi_GenMemOpsBlocksSpn_Ptr(ptr, sz, keys, keys_sz)                                                           \
    kdi_GenMemOpsBlocksSpn_S32((kd_u32_t*)(ptr), (kd_usize_t)(sz), (kd_u32_t*)(keys), (kd_usize_t)(keys_sz))
#endif /* KD_ARCH_64BIT_PTR */


KDAPI(void) kdi_GenMemOpsSwapBlocks_S8(kd_u8_t* ptr, kd_usize_t idx1, kd_usize_t idx2);
KDAPI(void) kdi_GenMemOpsSwapBlocks_S16(kd_u16_t* ptr, kd_usize_t idx1, kd_usize_t idx2);
KDAPI(void) kdi_GenMemOpsSwapBlocks_S32(kd_u32_t* ptr, kd_usize_t idx1, kd_usize_t idx2);
#if defined KD_ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsSwapBlocks_S64(kd_u64_t* ptr, kd_usize_t idx1, kd_usize_t idx2);
#endif
KDAPI(void)
kdi_GenMemOpsSwapBlocks_Sn(void* ptr, kd_usize_t block_sz, kd_usize_t idx1, kd_usize_t idx2);

KDAPI(void) kdi_GenMemOpsReverseBlocks_S8(kd_u8_t* ptr, kd_usize_t sz);
KDAPI(void) kdi_GenMemOpsReverseBlocks_S16(kd_u16_t* ptr, kd_usize_t sz);
KDAPI(void) kdi_GenMemOpsReverseBlocks_S32(kd_u32_t* ptr, kd_usize_t sz);
#if defined KD_ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsReverseBlocks_S64(kd_u64_t* ptr, kd_usize_t sz);
#endif
KDAPI(void) kdi_GenMemOpsReverseBlocks_Sn(void* ptr, kd_usize_t sz, kd_usize_t block_sz);

KDAPI(void) kdi_GenMemOpsSetBlocks_S8(kd_u8_t* ptr, kd_usize_t sz, kd_u8_t val);
KDAPI(void) kdi_GenMemOpsSetBlocks_S16(kd_u16_t* ptr, kd_usize_t sz, kd_u16_t val);
KDAPI(void) kdi_GenMemOpsSetBlocks_S32(kd_u32_t* ptr, kd_usize_t sz, kd_u32_t val);
#if defined KD_ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsSetBlocks_S64(kd_u64_t* ptr, kd_usize_t sz, kd_u64_t val);
#endif
KDAPI(void) kdi_GenMemOpsSetBlocks_Sn(void* ptr, kd_usize_t sz, void* block, kd_usize_t block_sz);

KDAPI(void*)
kdi_GenMemOpsFindBlockWithIndex_S8(kd_usize_t* idx_ptr, kd_u8_t* ptr, kd_usize_t sz, kd_u8_t val);
KDAPI(void*)
kdi_GenMemOpsFindBlockWithIndex_S16(kd_usize_t* idx_ptr, kd_u16_t* ptr, kd_usize_t sz, kd_u16_t val);
KDAPI(void*)
kdi_GenMemOpsFindBlockWithIndex_S32(kd_usize_t* idx_ptr, kd_u32_t* ptr, kd_usize_t sz, kd_u32_t val);
#if defined KD_ARCH_64BIT_INT
KDAPI(void*)
kdi_GenMemOpsFindBlockWithIndex_S64(kd_usize_t* idx_ptr, kd_u64_t* ptr, kd_usize_t sz, kd_u64_t val);
#endif
KDAPI(void*)
kdi_GenMemOpsFindBlockWithIndex_Sn(kd_usize_t* idx_ptr, void* ptr, kd_usize_t sz, void* block, kd_usize_t block_sz);

KDAPI(void*)
kdi_GenMemOpsFindLastBlockWithIndex_S8(kd_usize_t* idx_ptr, kd_u8_t* ptr, kd_usize_t sz, kd_u8_t val);
KDAPI(void*)
kdi_GenMemOpsFindLastBlockWithIndex_S16(kd_usize_t* idx_ptr, kd_u16_t* ptr, kd_usize_t sz, kd_u16_t val);
KDAPI(void*)
kdi_GenMemOpsFindLastBlockWithIndex_S32(kd_usize_t* idx_ptr, kd_u32_t* ptr, kd_usize_t sz, kd_u32_t val);
#if defined KD_ARCH_64BIT_INT
KDAPI(void*)
kdi_GenMemOpsFindLastBlockWithIndex_S64(kd_usize_t* idx_ptr, kd_u64_t* ptr, kd_usize_t sz, kd_u64_t val);
#endif
KDAPI(void*)
kdi_GenMemOpsFindLastBlockWithIndex_Sn(kd_usize_t* idx_ptr, void* ptr, kd_usize_t sz, void* block, kd_usize_t block_sz);

KDAPI(kd_usize_t)
kdi_GenMemOpsFindAllBlocksWithIndex_S8(
  kd_usize_t* idxs,
  kd_usize_t  idxs_sz,
  kd_u8_t*    ptr,
  kd_usize_t  ptr_sz,
  kd_u8_t     val
);
KDAPI(kd_usize_t)
kdi_GenMemOpsFindAllBlocksWithIndex_S16(
  kd_usize_t* idxs,
  kd_usize_t  idxs_sz,
  kd_u16_t*   ptr,
  kd_usize_t  ptr_sz,
  kd_u16_t    val
);
KDAPI(kd_usize_t)
kdi_GenMemOpsFindAllBlocksWithIndex_S32(
  kd_usize_t* idxs,
  kd_usize_t  idxs_sz,
  kd_u32_t*   ptr,
  kd_usize_t  ptr_sz,
  kd_u32_t    val
);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_usize_t)
kdi_GenMemOpsFindAllBlocksWithIndex_S64(
  kd_usize_t* idxs,
  kd_usize_t  idxs_sz,
  kd_u64_t*   ptr,
  kd_usize_t  ptr_sz,
  kd_u64_t    val
);
#endif
KDAPI(kd_usize_t)
kdi_GenMemOpsFindAllBlocksWithIndex_Sn(
  kd_usize_t* idxs,
  kd_usize_t  idxs_sz,
  void*       ptr,
  kd_usize_t  ptr_sz,
  void*       block,
  kd_usize_t  block_sz
);

KDAPI(void*)
kdi_GenMemOpsBlocksCompSpnWithIndex_S8(
  kd_usize_t* idx_ptr,
  kd_u8_t*    ptr,
  kd_usize_t  sz,
  kd_u8_t*    keys,
  kd_usize_t  keys_sz
);
KDAPI(void*)
kdi_GenMemOpsBlocksCompSpnWithIndex_S16(
  kd_usize_t* idx_ptr,
  kd_u16_t*   ptr,
  kd_usize_t  sz,
  kd_u16_t*   keys,
  kd_usize_t  keys_sz
);
KDAPI(void*)
kdi_GenMemOpsBlocksCompSpnWithIndex_S32(
  kd_usize_t* idx_ptr,
  kd_u32_t*   ptr,
  kd_usize_t  sz,
  kd_u32_t*   keys,
  kd_usize_t  keys_sz
);
#if defined KD_ARCH_64BIT_INT
KDAPI(void*)
kdi_GenMemOpsBlocksCompSpnWithIndex_S64(
  kd_usize_t* idx_ptr,
  kd_u64_t*   ptr,
  kd_usize_t  sz,
  kd_u64_t*   keys,
  kd_usize_t  keys_sz
);
#endif
KDAPI(void*)
kdi_GenMemOpsBlocksCompSpnWithIndex_Sn(
  kd_usize_t* idx_ptr,
  void*       ptr,
  kd_usize_t  sz,
  void*       key_blocks,
  kd_usize_t  key_block_sz,
  kd_usize_t  key_blocks_sz
);

KDAPI(kd_usize_t) kdi_GenMemOpsBlocksSpn_S8(kd_u8_t* ptr, kd_usize_t sz, kd_u8_t* keys, kd_usize_t keys_sz);
KDAPI(kd_usize_t) kdi_GenMemOpsBlocksSpn_S16(kd_u16_t* ptr, kd_usize_t sz, kd_u16_t* keys, kd_usize_t keys_sz);
KDAPI(kd_usize_t) kdi_GenMemOpsBlocksSpn_S32(kd_u32_t* ptr, kd_usize_t sz, kd_u32_t* keys, kd_usize_t keys_sz);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_usize_t) kdi_GenMemOpsBlocksSpn_S64(kd_u64_t* ptr, kd_usize_t sz, kd_u64_t* keys, kd_usize_t keys_sz);
#endif
KDAPI(kd_usize_t)
kdi_GenMemOpsBlocksSpn_Sn(
  void*      ptr,
  kd_usize_t sz,
  void*      key_blocks,
  kd_usize_t key_block_sz,
  kd_usize_t key_blocks_sz
);


KD_EXTERN_END

#endif /* KD__INTERNAL_GEN_MEM_OPS_SN_H_ */
