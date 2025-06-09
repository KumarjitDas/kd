/**
 * @file mem_ops.h
 * @author Kumarjit Das
 * @date 2025-06-03
 * @since 0.0.9
 * @brief Main header file of the MEM_OPS library.
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


#ifndef KD_MEM_OPS_H_
#define KD_MEM_OPS_H_


#include "kd/defs.h"
#include "kd/types/fw.h"
#include "kd/gen_mem_ops.h"


KD_EXTERN_BEGIN


#define kdMemOpsSwapByte(ptr, len, idx1, idx2)                                                                         \
  kdMemOpsSwap((void*)(ptr), (kd_i64_t)(len), (kd_i64_t)(idx1), (kd_i64_t)(idx2))
#define kdMemOpsSwapI8(ptr, len, idx1, idx2)                                                                           \
  kdMemOpsSwap((void*)(ptr), (kd_i64_t)(len), (kd_i64_t)(idx1), (kd_i64_t)(idx2))
#define kdMemOpsSwapU8(ptr, len, idx1, idx2)                                                                           \
  kdMemOpsSwap((void*)(ptr), (kd_i64_t)(len), (kd_i64_t)(idx1), (kd_i64_t)(idx2))

#define kdMemOpsSwapI16(ptr, len, idx1, idx2)                                                                          \
  kdMemOpsSwapU16((void*)(ptr), (kd_i64_t)(len), (kd_i64_t)(idx1), (kd_i64_t)(idx2))
#define kdMemOpsSwapI32(ptr, len, idx1, idx2)                                                                          \
  kdMemOpsSwapU32((void*)(ptr), (kd_i64_t)(len), (kd_i64_t)(idx1), (kd_i64_t)(idx2))
#define kdMemOpsSwapI64(ptr, len, idx1, idx2)                                                                          \
  kdMemOpsSwapU64((void*)(ptr), (kd_i64_t)(len), (kd_i64_t)(idx1), (kd_i64_t)(idx2))

#define kdMemOpsSwapImin(ptr, len, idx1, idx2)                                                                         \
  kdMemOpsSwap((void*)(ptr), (kd_i64_t)(len), (kd_i64_t)(idx1), (kd_i64_t)(idx2))
#define kdMemOpsSwapUmin(ptr, len, idx1, idx2)                                                                         \
  kdMemOpsSwap((void*)(ptr), (kd_i64_t)(len), (kd_i64_t)(idx1), (kd_i64_t)(idx2))

#define kdMemOpsSwapImax(ptr, len, idx1, idx2)                                                                         \
  kdMemOpsSwapU64((void*)(ptr), (kd_i64_t)(len), (kd_i64_t)(idx1), (kd_i64_t)(idx2))
#define kdMemOpsSwapUmax(ptr, len, idx1, idx2)                                                                         \
  kdMemOpsSwapU64((void*)(ptr), (kd_i64_t)(len), (kd_i64_t)(idx1), (kd_i64_t)(idx2))
#define kdMemOpsSwapUsize(ptr, len, idx1, idx2)                                                                        \
  kdMemOpsSwapU64((void*)(ptr), (kd_i64_t)(len), (kd_i64_t)(idx1), (kd_i64_t)(idx2))

#define kdMemOpsSwapChr(ptr, len, idx1, idx2)                                                                          \
  kdMemOpsSwapU32((void*)(ptr), (kd_i64_t)(len), (kd_i64_t)(idx1), (kd_i64_t)(idx2))
#define kdMemOpsSwapBool(ptr, len, idx1, idx2)                                                                         \
  kdMemOpsSwapU32((void*)(ptr), (kd_i64_t)(len), (kd_i64_t)(idx1), (kd_i64_t)(idx2))

#if defined KD_ARCH_64BIT_PTR
  #define kdMemOpsSwapPtr(ptr, len, idx1, idx2)                                                                        \
    kdMemOpsSwapU64((void*)(ptr), (kd_i64_t)(len), (kd_i64_t)(idx1), (kd_i64_t)(idx2))
#else
  #define kdMemOpsSwapPtr(ptr, len, idx1, idx2)                                                                        \
    kdMemOpsSwapU32((void*)(ptr), (kd_i64_t)(len), (kd_i64_t)(idx1), (kd_i64_t)(idx2))
#endif /* KD_ARCH_64BIT_PTR */


#define kdMemOpsReverseByte(ptr, len) kdMemOpsReverse((void*)(ptr), (kd_i64_t)(len))
#define kdMemOpsReverseI8(ptr, len)   kdMemOpsReverse((void*)(ptr), (kd_i64_t)(len))
#define kdMemOpsReverseU8(ptr, len)   kdMemOpsReverse((void*)(ptr), (kd_i64_t)(len))

#define kdMemOpsReverseI16(ptr, len) kdMemOpsReverseU16((void*)(ptr), (kd_i64_t)(len))
#define kdMemOpsReverseI32(ptr, len) kdMemOpsReverseU32((void*)(ptr), (kd_i64_t)(len))
#define kdMemOpsReverseI64(ptr, len) kdMemOpsReverseU64((void*)(ptr), (kd_i64_t)(len))

#define kdMemOpsReverseImin(ptr, len) kdMemOpsReverse((void*)(ptr), (kd_i64_t)(len))
#define kdMemOpsReverseUmin(ptr, len) kdMemOpsReverse((void*)(ptr), (kd_i64_t)(len))

#define kdMemOpsReverseImax(ptr, len)  kdMemOpsReverseU64((void*)(ptr), (kd_i64_t)(len))
#define kdMemOpsReverseUmax(ptr, len)  kdMemOpsReverseU64((void*)(ptr), (kd_i64_t)(len))
#define kdMemOpsReverseUsize(ptr, len) kdMemOpsReverseU64((void*)(ptr), (kd_i64_t)(len))

#define kdMemOpsReverseChr(ptr, len)  kdMemOpsReverseU32((void*)(ptr), (kd_i64_t)(len))
#define kdMemOpsReverseBool(ptr, len) kdMemOpsReverseU32((void*)(ptr), (kd_i64_t)(len))

#if defined KD_ARCH_64BIT_PTR
  #define kdMemOpsReversePtr(ptr, len) kdMemOpsReverseU64((void*)(ptr), (kd_i64_t)(len))
#else
  #define kdMemOpsReversePtr(ptr, len) kdMemOpsReverseU32((void*)(ptr), (kd_i64_t)(len))
#endif /* KD_ARCH_64BIT_PTR */


#define kdMemOpsSetByte(ptr, len, val) kdMemOpsSet((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(val))
#define kdMemOpsSetI8(ptr, len, val)   kdMemOpsSet((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(val))
#define kdMemOpsSetU8(ptr, len, val)   kdMemOpsSet((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(val))

#define kdMemOpsSetI16(ptr, len, val) kdMemOpsSetU16((void*)(ptr), (kd_i64_t)(len), (kd_u16_t)(val))
#define kdMemOpsSetI32(ptr, len, val) kdMemOpsSetU32((void*)(ptr), (kd_i64_t)(len), (kd_u32_t)(val))
#define kdMemOpsSetI64(ptr, len, val) kdMemOpsSetU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(val))

#define kdMemOpsSetImin(ptr, len, val) kdMemOpsSet((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(val))
#define kdMemOpsSetImax(ptr, len, val) kdMemOpsSet((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(val))

#define kdMemOpsSetUmin(ptr, len, val)  kdMemOpsSetU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(val))
#define kdMemOpsSetUmax(ptr, len, val)  kdMemOpsSetU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(val))
#define kdMemOpsSetUsize(ptr, len, val) kdMemOpsSetU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(val))

#define kdMemOpsSetChr(ptr, len, val)  kdMemOpsSetU32((void*)(ptr), (kd_i64_t)(len), (kd_u32_t)(val))
#define kdMemOpsSetBool(ptr, len, val) kdMemOpsSetU32((void*)(ptr), (kd_i64_t)(len), (kd_u32_t)(val))

#if defined KD_ARCH_64BIT_PTR
  #define kdMemOpsSetPtr(ptr, len, val) kdMemOpsSetU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(val))
#else
  #define kdMemOpsSetPtr(ptr, len, val) kdMemOpsSetU32((void*)(ptr), (kd_i64_t)(len), (kd_u32_t)(val))
#endif /* KD_ARCH_64BIT_PTR */


#define kdMemOpsCpyByte(dst, src, len) kdMemOpsCpy((void*)(dst), (void*)(src), (kd_i64_t)(len))
#define kdMemOpsCpyI8(dst, src, len)   kdMemOpsCpy((void*)(dst), (void*)(src), (kd_i64_t)(len))
#define kdMemOpsCpyU8(dst, src, len)   kdMemOpsCpy((void*)(dst), (void*)(src), (kd_i64_t)(len))

#define kdMemOpsCpyI16(dst, src, len) kdMemOpsCpyU16((void*)(dst), (void*)(src), (kd_i64_t)(len))
#define kdMemOpsCpyI32(dst, src, len) kdMemOpsCpyU32((void*)(dst), (void*)(src), (kd_i64_t)(len))
#define kdMemOpsCpyI64(dst, src, len) kdMemOpsCpyU64((void*)(dst), (void*)(src), (kd_i64_t)(len))

#define kdMemOpsCpyImin(dst, src, len) kdMemOpsCpy((void*)(dst), (void*)(src), (kd_i64_t)(len))
#define kdMemOpsCpyUmin(dst, src, len) kdMemOpsCpy((void*)(dst), (void*)(src), (kd_i64_t)(len))

#define kdMemOpsCpyImax(dst, src, len)  kdMemOpsCpyU64((void*)(dst), (void*)(src), (kd_i64_t)(len))
#define kdMemOpsCpyUmax(dst, src, len)  kdMemOpsCpyU64((void*)(dst), (void*)(src), (kd_i64_t)(len))
#define kdMemOpsCpyUsize(dst, src, len) kdMemOpsCpyU64((void*)(dst), (void*)(src), (kd_i64_t)(len))

#define kdMemOpsCpyChr(dst, src, len)  kdMemOpsCpyU32((void*)(dst), (void*)(src), (kd_i64_t)(len))
#define kdMemOpsCpyBool(dst, src, len) kdMemOpsCpyU32((void*)(dst), (void*)(src), (kd_i64_t)(len))

#if defined KD_ARCH_64BIT_PTR
  #define kdMemOpsCpyPtr(dst, src, len) kdMemOpsCpyU64((void*)(dst), (void*)(src), (kd_i64_t)(len))
#else
  #define kdMemOpsCpyPtr(dst, src, len) kdMemOpsCpyU32((void*)(dst), (void*)(src), (kd_i64_t)(len))
#endif /* KD_ARCH_64BIT_PTR */


#define kdMemOpsMoveByte(dst, src, len) kdMemOpsMove((void*)(dst), (void*)(src), (kd_i64_t)(len))
#define kdMemOpsMoveI8(dst, src, len)   kdMemOpsMove((void*)(dst), (void*)(src), (kd_i64_t)(len))
#define kdMemOpsMoveU8(dst, src, len)   kdMemOpsMove((void*)(dst), (void*)(src), (kd_i64_t)(len))

#define kdMemOpsMoveI16(dst, src, len) kdMemOpsMoveU16((void*)(dst), (void*)(src), (kd_i64_t)(len))
#define kdMemOpsMoveI32(dst, src, len) kdMemOpsMoveU32((void*)(dst), (void*)(src), (kd_i64_t)(len))
#define kdMemOpsMoveI64(dst, src, len) kdMemOpsMoveU64((void*)(dst), (void*)(src), (kd_i64_t)(len))

#define kdMemOpsMoveImin(dst, src, len) kdMemOpsMove((void*)(dst), (void*)(src), (kd_i64_t)(len))
#define kdMemOpsMoveUmin(dst, src, len) kdMemOpsMove((void*)(dst), (void*)(src), (kd_i64_t)(len))

#define kdMemOpsMoveImax(dst, src, len)  kdMemOpsMoveU64((void*)(dst), (void*)(src), (kd_i64_t)(len))
#define kdMemOpsMoveUmax(dst, src, len)  kdMemOpsMoveU64((void*)(dst), (void*)(src), (kd_i64_t)(len))
#define kdMemOpsMoveUsize(dst, src, len) kdMemOpsMoveU64((void*)(dst), (void*)(src), (kd_i64_t)(len))

#define kdMemOpsMoveChr(dst, src, len)  kdMemOpsMoveU32((void*)(dst), (void*)(src), (kd_i64_t)(len))
#define kdMemOpsMoveBool(dst, src, len) kdMemOpsMoveU32((void*)(dst), (void*)(src), (kd_i64_t)(len))

#if defined KD_ARCH_64BIT_PTR
  #define kdMemOpsMovePtr(dst, src, len) kdMemOpsMoveU64((void*)(dst), (void*)(src), (kd_i64_t)(len))
#else
  #define kdMemOpsMovePtr(dst, src, len) kdMemOpsMoveU32((void*)(dst), (void*)(src), (kd_i64_t)(len))
#endif /* KD_ARCH_64BIT_PTR */


#define kdMemOpsFindByte(ptr, len, item) kdMemOpsFind((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(item))
#define kdMemOpsFindI8(ptr, len, item)   kdMemOpsFind((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(item))
#define kdMemOpsFindU8(ptr, len, item)   kdMemOpsFind((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(item))

#define kdMemOpsFindI16(ptr, len, item) kdMemOpsFindU16((void*)(ptr), (kd_i64_t)(len), (kd_u16_t)(item))
#define kdMemOpsFindI32(ptr, len, item) kdMemOpsFindU32((void*)(ptr), (kd_i64_t)(len), (kd_u32_t)(item))
#define kdMemOpsFindI64(ptr, len, item) kdMemOpsFindU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(item))

#define kdMemOpsFindImin(ptr, len, item) kdMemOpsFind((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(item))
#define kdMemOpsFindImax(ptr, len, item) kdMemOpsFind((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(item))

#define kdMemOpsFindUmin(ptr, len, item)  kdMemOpsFindU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(item))
#define kdMemOpsFindUmax(ptr, len, item)  kdMemOpsFindU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(item))
#define kdMemOpsFindUsize(ptr, len, item) kdMemOpsFindU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(item))

#define kdMemOpsFindChr(ptr, len, item)  kdMemOpsFindU32((void*)(ptr), (kd_i64_t)(len), (kd_u32_t)(item))
#define kdMemOpsFindBool(ptr, len, item) kdMemOpsFindU32((void*)(ptr), (kd_i64_t)(len), (kd_u32_t)(item))

#if defined KD_ARCH_64BIT_PTR
  #define kdMemOpsFindPtr(ptr, len, item) kdMemOpsFindU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(item))
#else
  #define kdMemOpsFindPtr(ptr, len, item) kdMemOpsFindU32((void*)(ptr), (kd_i64_t)(len), (kd_u32_t)(item))
#endif /* KD_ARCH_64BIT_PTR */


#define kdMemOpsFindIndexByte(ptr, len, item) kdMemOpsFindIndex((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(item))
#define kdMemOpsFindIndexI8(ptr, len, item)   kdMemOpsFindIndex((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(item))
#define kdMemOpsFindIndexU8(ptr, len, item)   kdMemOpsFindIndex((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(item))

#define kdMemOpsFindIndexI16(ptr, len, item) kdMemOpsFindIndexU16((void*)(ptr), (kd_i64_t)(len), (kd_u16_t)(item))
#define kdMemOpsFindIndexI32(ptr, len, item) kdMemOpsFindIndexU32((void*)(ptr), (kd_i64_t)(len), (kd_u32_t)(item))
#define kdMemOpsFindIndexI64(ptr, len, item) kdMemOpsFindIndexU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(item))

#define kdMemOpsFindIndexImin(ptr, len, item) kdMemOpsFindIndex((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(item))
#define kdMemOpsFindIndexImax(ptr, len, item) kdMemOpsFindIndex((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(item))

#define kdMemOpsFindIndexUmin(ptr, len, item)  kdMemOpsFindIndexU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(item))
#define kdMemOpsFindIndexUmax(ptr, len, item)  kdMemOpsFindIndexU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(item))
#define kdMemOpsFindIndexUsize(ptr, len, item) kdMemOpsFindIndexU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(item))

#define kdMemOpsFindIndexChr(ptr, len, item)  kdMemOpsFindIndexU32((void*)(ptr), (kd_i64_t)(len), (kd_u32_t)(item))
#define kdMemOpsFindIndexBool(ptr, len, item) kdMemOpsFindIndexU32((void*)(ptr), (kd_i64_t)(len), (kd_u32_t)(item))

#if defined KD_ARCH_64BIT_PTR
  #define kdMemOpsFindIndexPtr(ptr, len, item) kdMemOpsFindIndexU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(item))
#else
  #define kdMemOpsFindIndexPtr(ptr, len, item) kdMemOpsFindIndexU32((void*)(ptr), (kd_i64_t)(len), (kd_u32_t)(item))
#endif /* KD_ARCH_64BIT_PTR */


#define kdMemOpsFindLastByte(ptr, len, item) kdMemOpsFindLast((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(item))
#define kdMemOpsFindLastI8(ptr, len, item)   kdMemOpsFindLast((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(item))
#define kdMemOpsFindLastU8(ptr, len, item)   kdMemOpsFindLast((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(item))

#define kdMemOpsFindLastI16(ptr, len, item) kdMemOpsFindLastU16((void*)(ptr), (kd_i64_t)(len), (kd_u16_t)(item))
#define kdMemOpsFindLastI32(ptr, len, item) kdMemOpsFindLastU32((void*)(ptr), (kd_i64_t)(len), (kd_u32_t)(item))
#define kdMemOpsFindLastI64(ptr, len, item) kdMemOpsFindLastU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(item))

#define kdMemOpsFindLastImin(ptr, len, item) kdMemOpsFindLast((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(item))
#define kdMemOpsFindLastImax(ptr, len, item) kdMemOpsFindLast((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(item))

#define kdMemOpsFindLastUmin(ptr, len, item)  kdMemOpsFindLastU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(item))
#define kdMemOpsFindLastUmax(ptr, len, item)  kdMemOpsFindLastU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(item))
#define kdMemOpsFindLastUsize(ptr, len, item) kdMemOpsFindLastU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(item))

#define kdMemOpsFindLastChr(ptr, len, item)  kdMemOpsFindLastU32((void*)(ptr), (kd_i64_t)(len), (kd_u32_t)(item))
#define kdMemOpsFindLastBool(ptr, len, item) kdMemOpsFindLastU32((void*)(ptr), (kd_i64_t)(len), (kd_u32_t)(item))

#if defined KD_ARCH_64BIT_PTR
  #define kdMemOpsFindLastPtr(ptr, len, item) kdMemOpsFindLastU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(item))
#else
  #define kdMemOpsFindLastPtr(ptr, len, item) kdMemOpsFindLastU32((void*)(ptr), (kd_i64_t)(len), (kd_u32_t)(item))
#endif /* KD_ARCH_64BIT_PTR */


#define kdMemOpsFindLastIndexByte(ptr, len, item)                                                                      \
  kdMemOpsFindLastIndex((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(item))
#define kdMemOpsFindLastIndexI8(ptr, len, item) kdMemOpsFindLastIndex((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(item))
#define kdMemOpsFindLastIndexU8(ptr, len, item) kdMemOpsFindLastIndex((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(item))

#define kdMemOpsFindLastIndexI16(ptr, len, item)                                                                       \
  kdMemOpsFindLastIndexU16((void*)(ptr), (kd_i64_t)(len), (kd_u16_t)(item))
#define kdMemOpsFindLastIndexI32(ptr, len, item)                                                                       \
  kdMemOpsFindLastIndexU32((void*)(ptr), (kd_i64_t)(len), (kd_u32_t)(item))
#define kdMemOpsFindLastIndexI64(ptr, len, item)                                                                       \
  kdMemOpsFindLastIndexU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(item))

#define kdMemOpsFindLastIndexImin(ptr, len, item)                                                                      \
  kdMemOpsFindLastIndex((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(item))
#define kdMemOpsFindLastIndexImax(ptr, len, item)                                                                      \
  kdMemOpsFindLastIndex((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(item))

#define kdMemOpsFindLastIndexUmin(ptr, len, item)                                                                      \
  kdMemOpsFindLastIndexU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(item))
#define kdMemOpsFindLastIndexUmax(ptr, len, item)                                                                      \
  kdMemOpsFindLastIndexU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(item))
#define kdMemOpsFindLastIndexUsize(ptr, len, item)                                                                     \
  kdMemOpsFindLastIndexU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(item))

#define kdMemOpsFindLastIndexChr(ptr, len, item)                                                                       \
  kdMemOpsFindLastIndexU32((void*)(ptr), (kd_i64_t)(len), (kd_u32_t)(item))
#define kdMemOpsFindLastIndexBool(ptr, len, item)                                                                      \
  kdMemOpsFindLastIndexU32((void*)(ptr), (kd_i64_t)(len), (kd_u32_t)(item))

#if defined KD_ARCH_64BIT_PTR
  #define kdMemOpsFindLastIndexPtr(ptr, len, item)                                                                     \
    kdMemOpsFindLastIndexU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(item))
#else
  #define kdMemOpsFindLastIndexPtr(ptr, len, item)                                                                     \
    kdMemOpsFindLastIndexU32((void*)(ptr), (kd_i64_t)(len), (kd_u32_t)(item))
#endif /* KD_ARCH_64BIT_PTR */


#define kdMemOpsFindAllByte(dst, dst_len, ptr, ptr_len, item)                                                          \
  kdMemOpsFindAll((void*)(dst), (kd_i64_t)(dst_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_byte_t)(item))
#define kdMemOpsFindAllI8(dst, dst_len, ptr, ptr_len, item)                                                            \
  kdMemOpsFindAll((void*)(dst), (kd_i64_t)(dst_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_byte_t)(item))
#define kdMemOpsFindAllU8(dst, dst_len, ptr, ptr_len, item)                                                            \
  kdMemOpsFindAll((void*)(dst), (kd_i64_t)(dst_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_byte_t)(item))

#define kdMemOpsFindAllI16(dst, dst_len, ptr, ptr_len, item)                                                           \
  kdMemOpsFindAllU16((void*)(dst), (kd_i64_t)(dst_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_u16_t)(item))
#define kdMemOpsFindAllI32(dst, dst_len, ptr, ptr_len, item)                                                           \
  kdMemOpsFindAllU32((void*)(dst), (kd_i64_t)(dst_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_u32_t)(item))
#define kdMemOpsFindAllI64(dst, dst_len, ptr, ptr_len, item)                                                           \
  kdMemOpsFindAllU64((void*)(dst), (kd_i64_t)(dst_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_u64_t)(item))

#define kdMemOpsFindAllImin(dst, dst_len, ptr, ptr_len, item)                                                          \
  kdMemOpsFindAll((void*)(dst), (kd_i64_t)(dst_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_byte_t)(item))
#define kdMemOpsFindAllUmin(dst, dst_len, ptr, ptr_len, item)                                                          \
  kdMemOpsFindAll((void*)(dst), (kd_i64_t)(dst_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_byte_t)(item))

#define kdMemOpsFindAllImax(dst, dst_len, ptr, ptr_len, item)                                                          \
  kdMemOpsFindAllU64((void*)(dst), (kd_i64_t)(dst_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_u64_t)(item))
#define kdMemOpsFindAllUmax(dst, dst_len, ptr, ptr_len, item)                                                          \
  kdMemOpsFindAllU64((void*)(dst), (kd_i64_t)(dst_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_u64_t)(item))
#define kdMemOpsFindAllUsize(dst, dst_len, ptr, ptr_len, item)                                                         \
  kdMemOpsFindAllU64((void*)(dst), (kd_i64_t)(dst_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_u64_t)(item))

#define kdMemOpsFindAllChr(dst, dst_len, ptr, ptr_len, item)                                                           \
  kdMemOpsFindAllU32((void*)(dst), (kd_i64_t)(dst_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_u32_t)(item))
#define kdMemOpsFindAllBool(dst, dst_len, ptr, ptr_len, item)                                                          \
  kdMemOpsFindAllU32((void*)(dst), (kd_i64_t)(dst_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_u32_t)(item))

#if defined KD_ARCH_64BIT_PTR
  #define kdMemOpsFindAllPtr(dst, dst_len, ptr, ptr_len, item)                                                         \
    kdMemOpsFindAllU64((void*)(dst), (kd_i64_t)(dst_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_u64_t)(item))
#else
  #define kdMemOpsFindAllPtr(dst, dst_len, ptr, ptr_len, item)                                                         \
    kdMemOpsFindAllU32((void*)(dst), (kd_i64_t)(dst_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_u32_t)(item))
#endif /* KD_ARCH_64BIT_PTR */


#define kdMemOpsFindAllIndexByte(idxs, idxs_len, ptr, ptr_len, item)                                                   \
  kdMemOpsFindAllIndex((kd_i64_t*)(idxs), (kd_i64_t)(idxs_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_byte_t)(item))
#define kdMemOpsFindAllIndexI8(idxs, idxs_len, ptr, ptr_len, item)                                                     \
  kdMemOpsFindAllIndex((kd_i64_t*)(idxs), (kd_i64_t)(idxs_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_byte_t)(item))
#define kdMemOpsFindAllIndexU8(idxs, idxs_len, ptr, ptr_len, item)                                                     \
  kdMemOpsFindAllIndex((kd_i64_t*)(idxs), (kd_i64_t)(idxs_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_byte_t)(item))

#define kdMemOpsFindAllIndexI16(idxs, idxs_len, ptr, ptr_len, item)                                                    \
  kdMemOpsFindAllIndexU16((kd_i64_t*)(idxs), (kd_i64_t)(idxs_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_u16_t)(item))
#define kdMemOpsFindAllIndexI32(idxs, idxs_len, ptr, ptr_len, item)                                                    \
  kdMemOpsFindAllIndexU32((kd_i64_t*)(idxs), (kd_i64_t)(idxs_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_u32_t)(item))
#define kdMemOpsFindAllIndexI64(idxs, idxs_len, ptr, ptr_len, item)                                                    \
  kdMemOpsFindAllIndexU64((kd_i64_t*)(idxs), (kd_i64_t)(idxs_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_u64_t)(item))

#define kdMemOpsFindAllIndexImin(idxs, idxs_len, ptr, ptr_len, item)                                                   \
  kdMemOpsFindAllIndex((kd_i64_t*)(idxs), (kd_i64_t)(idxs_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_byte_t)(item))
#define kdMemOpsFindAllIndexUmin(idxs, idxs_len, ptr, ptr_len, item)                                                   \
  kdMemOpsFindAllIndex((kd_i64_t*)(idxs), (kd_i64_t)(idxs_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_byte_t)(item))

#define kdMemOpsFindAllIndexImax(idxs, idxs_len, ptr, ptr_len, item)                                                   \
  kdMemOpsFindAllIndexU64((kd_i64_t*)(idxs), (kd_i64_t)(idxs_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_u64_t)(item))
#define kdMemOpsFindAllIndexUmax(idxs, idxs_len, ptr, ptr_len, item)                                                   \
  kdMemOpsFindAllIndexU64((kd_i64_t*)(idxs), (kd_i64_t)(idxs_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_u64_t)(item))
#define kdMemOpsFindAllIndexUsize(idxs, idxs_len, ptr, ptr_len, item)                                                  \
  kdMemOpsFindAllIndexU64((kd_i64_t*)(idxs), (kd_i64_t)(idxs_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_u64_t)(item))

#define kdMemOpsFindAllIndexChr(idxs, idxs_len, ptr, ptr_len, item)                                                    \
  kdMemOpsFindAllIndexU32((kd_i64_t*)(idxs), (kd_i64_t)(idxs_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_u32_t)(item))
#define kdMemOpsFindAllIndexBool(idxs, idxs_len, ptr, ptr_len, item)                                                   \
  kdMemOpsFindAllIndexU32((kd_i64_t*)(idxs), (kd_i64_t)(idxs_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_u32_t)(item))

#if defined KD_ARCH_64BIT_PTR
  #define kdMemOpsFindAllIndexPtr(idxs, idxs_len, ptr, ptr_len, item)                                                  \
    kdMemOpsFindAllIndexU64(                                                                                           \
      (kd_i64_t*)(idxs), (kd_i64_t)(idxs_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_u64_t)(item)                     \
    )
#else
  #define kdMemOpsFindAllIndexPtr(idxs, idxs_len, ptr, ptr_len, item)                                                  \
    kdMemOpsFindAllIndexU32(                                                                                           \
      (kd_i64_t*)(idxs), (kd_i64_t)(idxs_len), (void*)(ptr), (kd_i64_t)(ptr_len), (kd_u32_t)(item)                     \
    )
#endif /* KD_ARCH_64BIT_PTR */


#define kdMemOpsCmpByte(ptr1, ptr2, len)  kdMemOpsCmp((void*)(ptr1), (void*)(ptr2), (kd_i64_t)(len))
#define kdMemOpsCmpI8(ptr1, ptr2, len)    kdMemOpsCmp((void*)(ptr1), (void*)(ptr2), (kd_i64_t)(len))
#define kdMemOpsCmpU8(ptr1, ptr2, len)    kdMemOpsCmp((void*)(ptr1), (void*)(ptr2), (kd_i64_t)(len))
#define kdMemOpsCmpI16(ptr1, ptr2, len)   kdMemOpsCmp((void*)(ptr1), (void*)(ptr2), (kd_i64_t)(len * KD_SZ_I16))
#define kdMemOpsCmpU16(ptr1, ptr2, len)   kdMemOpsCmp((void*)(ptr1), (void*)(ptr2), (kd_i64_t)(len * KD_SZ_U16))
#define kdMemOpsCmpI32(ptr1, ptr2, len)   kdMemOpsCmp((void*)(ptr1), (void*)(ptr2), (kd_i64_t)(len * KD_SZ_I32))
#define kdMemOpsCmpU32(ptr1, ptr2, len)   kdMemOpsCmp((void*)(ptr1), (void*)(ptr2), (kd_i64_t)(len * KD_SZ_U32))
#define kdMemOpsCmpI64(ptr1, ptr2, len)   kdMemOpsCmp((void*)(ptr1), (void*)(ptr2), (kd_i64_t)(len * KD_SZ_I64))
#define kdMemOpsCmpU64(ptr1, ptr2, len)   kdMemOpsCmp((void*)(ptr1), (void*)(ptr2), (kd_i64_t)(len * KD_SZ_U64))
#define kdMemOpsCmpImin(ptr1, ptr2, len)  kdMemOpsCmp((void*)(ptr1), (void*)(ptr2), (kd_i64_t)(len * KD_SZ_IMIN))
#define kdMemOpsCmpUmin(ptr1, ptr2, len)  kdMemOpsCmp((void*)(ptr1), (void*)(ptr2), (kd_i64_t)(len * KD_SZ_UMIN))
#define kdMemOpsCmpImax(ptr1, ptr2, len)  kdMemOpsCmp((void*)(ptr1), (void*)(ptr2), (kd_i64_t)(len * KD_SZ_IMAX))
#define kdMemOpsCmpUmax(ptr1, ptr2, len)  kdMemOpsCmp((void*)(ptr1), (void*)(ptr2), (kd_i64_t)(len * KD_SZ_UMAX))
#define kdMemOpsCmpUsize(ptr1, ptr2, len) kdMemOpsCmp((void*)(ptr1), (void*)(ptr2), (kd_i64_t)(len * KD_SZ_USIZE))
#define kdMemOpsCmpChr(ptr1, ptr2, len)   kdMemOpsCmp((void*)(ptr1), (void*)(ptr2), (kd_i64_t)(len * KD_SZ_CHR))
#define kdMemOpsCmpBool(ptr1, ptr2, len)  kdMemOpsCmp((void*)(ptr1), (void*)(ptr2), (kd_i64_t)(len * KD_SZ_BOOL))
#define kdMemOpsCmpPtr(ptr1, ptr2, len)   kdMemOpsCmp((void*)(ptr1), (void*)(ptr2), (kd_i64_t)(len * KD_SZ_PTR))


#define kdMemOpsCatByte(dst, dst_len, src1, src1_len, src2, src2_len)                                                  \
  kdMemOpsCat(                                                                                                         \
    (void*)(dst), (kd_i64_t)(dst_len), (void*)(src1), (kd_i64_t)(src1_len), (void*)(src2), (kd_i64_t)(src2_len)        \
  )
#define kdMemOpsCatI8(dst, dst_len, src1, src1_len, src2, src2_len)                                                    \
  kdMemOpsCat(                                                                                                         \
    (void*)(dst), (kd_i64_t)(dst_len), (void*)(src1), (kd_i64_t)(src1_len), (void*)(src2), (kd_i64_t)(src2_len)        \
  )
#define kdMemOpsCatU8(dst, dst_len, src1, src1_len, src2, src2_len)                                                    \
  kdMemOpsCat(                                                                                                         \
    (void*)(dst), (kd_i64_t)(dst_len), (void*)(src1), (kd_i64_t)(src1_len), (void*)(src2), (kd_i64_t)(src2_len)        \
  )

#define kdMemOpsCatI16(dst, dst_len, src1, src1_len, src2, src2_len)                                                   \
  kdMemOpsCat(                                                                                                         \
    (void*)(dst),                                                                                                      \
    (kd_i64_t)(dst_len * KD_SZ_I16),                                                                                   \
    (void*)(src1),                                                                                                     \
    (kd_i64_t)(src1_len * KD_SZ_I16),                                                                                  \
    (void*)(src2),                                                                                                     \
    (kd_i64_t)(src2_len * KD_SZ_I16)                                                                                   \
  )
#define kdMemOpsCatU16(dst, dst_len, src1, src1_len, src2, src2_len)                                                   \
  kdMemOpsCat(                                                                                                         \
    (void*)(dst),                                                                                                      \
    (kd_i64_t)(dst_len * KD_SZ_U16),                                                                                   \
    (void*)(src1),                                                                                                     \
    (kd_i64_t)(src1_len * KD_SZ_U16),                                                                                  \
    (void*)(src2),                                                                                                     \
    (kd_i64_t)(src2_len * KD_SZ_U16)                                                                                   \
  )

#define kdMemOpsCatI32(dst, dst_len, src1, src1_len, src2, src2_len)                                                   \
  kdMemOpsCat(                                                                                                         \
    (void*)(dst),                                                                                                      \
    (kd_i64_t)(dst_len * KD_SZ_I32),                                                                                   \
    (void*)(src1),                                                                                                     \
    (kd_i64_t)(src1_len * KD_SZ_I32),                                                                                  \
    (void*)(src2),                                                                                                     \
    (kd_i64_t)(src2_len * KD_SZ_I32)                                                                                   \
  )
#define kdMemOpsCatU32(dst, dst_len, src1, src1_len, src2, src2_len)                                                   \
  kdMemOpsCat(                                                                                                         \
    (void*)(dst),                                                                                                      \
    (kd_i64_t)(dst_len * KD_SZ_U32),                                                                                   \
    (void*)(src1),                                                                                                     \
    (kd_i64_t)(src1_len * KD_SZ_U32),                                                                                  \
    (void*)(src2),                                                                                                     \
    (kd_i64_t)(src2_len * KD_SZ_U32)                                                                                   \
  )

#define kdMemOpsCatI64(dst, dst_len, src1, src1_len, src2, src2_len)                                                   \
  kdMemOpsCat(                                                                                                         \
    (void*)(dst),                                                                                                      \
    (kd_i64_t)(dst_len * KD_SZ_I64),                                                                                   \
    (void*)(src1),                                                                                                     \
    (kd_i64_t)(src1_len * KD_SZ_I64),                                                                                  \
    (void*)(src2),                                                                                                     \
    (kd_i64_t)(src2_len * KD_SZ_I64)                                                                                   \
  )
#define kdMemOpsCatU64(dst, dst_len, src1, src1_len, src2, src2_len)                                                   \
  kdMemOpsCat(                                                                                                         \
    (void*)(dst),                                                                                                      \
    (kd_i64_t)(dst_len * KD_SZ_U64),                                                                                   \
    (void*)(src1),                                                                                                     \
    (kd_i64_t)(src1_len * KD_SZ_U64),                                                                                  \
    (void*)(src2),                                                                                                     \
    (kd_i64_t)(src2_len * KD_SZ_U64)                                                                                   \
  )

#define kdMemOpsCatImin(dst, dst_len, src1, src1_len, src2, src2_len)                                                  \
  kdMemOpsCat(                                                                                                         \
    (void*)(dst), (kd_i64_t)(dst_len), (void*)(src1), (kd_i64_t)(src1_len), (void*)(src2), (kd_i64_t)(src2_len)        \
  )
#define kdMemOpsCatUmin(dst, dst_len, src1, src1_len, src2, src2_len)                                                  \
  kdMemOpsCat(                                                                                                         \
    (void*)(dst), (kd_i64_t)(dst_len), (void*)(src1), (kd_i64_t)(src1_len), (void*)(src2), (kd_i64_t)(src2_len)        \
  )

#define kdMemOpsCatImax(dst, dst_len, src1, src1_len, src2, src2_len)                                                  \
  kdMemOpsCat(                                                                                                         \
    (void*)(dst),                                                                                                      \
    (kd_i64_t)(dst_len * KD_SZ_IMAX),                                                                                  \
    (void*)(src1),                                                                                                     \
    (kd_i64_t)(src1_len * KD_SZ_IMAX),                                                                                 \
    (void*)(src2),                                                                                                     \
    (kd_i64_t)(src2_len * KD_SZ_IMAX)                                                                                  \
  )
#define kdMemOpsCatUmax(dst, dst_len, src1, src1_len, src2, src2_len)                                                  \
  kdMemOpsCat(                                                                                                         \
    (void*)(dst),                                                                                                      \
    (kd_i64_t)(dst_len * KD_SZ_UMAX),                                                                                  \
    (void*)(src1),                                                                                                     \
    (kd_i64_t)(src1_len * KD_SZ_UMAX),                                                                                 \
    (void*)(src2),                                                                                                     \
    (kd_i64_t)(src2_len * KD_SZ_UMAX)                                                                                  \
  )

#define kdMemOpsCatUsize(dst, dst_len, src1, src1_len, src2, src2_len)                                                 \
  kdMemOpsCat(                                                                                                         \
    (void*)(dst),                                                                                                      \
    (kd_i64_t)(dst_len * KD_SZ_USIZE),                                                                                 \
    (void*)(src1),                                                                                                     \
    (kd_i64_t)(src1_len * KD_SZ_USIZE),                                                                                \
    (void*)(src2),                                                                                                     \
    (kd_i64_t)(src2_len * KD_SZ_USIZE)                                                                                 \
  )

#define kdMemOpsCatChr(dst, dst_len, src1, src1_len, src2, src2_len)                                                   \
  kdMemOpsCat(                                                                                                         \
    (void*)(dst),                                                                                                      \
    (kd_i64_t)(dst_len * KD_SZ_CHR),                                                                                   \
    (void*)(src1),                                                                                                     \
    (kd_i64_t)(src1_len * KD_SZ_CHR),                                                                                  \
    (void*)(src2),                                                                                                     \
    (kd_i64_t)(src2_len * KD_SZ_CHR)                                                                                   \
  )
#define kdMemOpsCatBool(dst, dst_len, src1, src1_len, src2, src2_len)                                                  \
  kdMemOpsCat(                                                                                                         \
    (void*)(dst),                                                                                                      \
    (kd_i64_t)(dst_len * KD_SZ_BOOL),                                                                                  \
    (void*)(src1),                                                                                                     \
    (kd_i64_t)(src1_len * KD_SZ_BOOL),                                                                                 \
    (void*)(src2),                                                                                                     \
    (kd_i64_t)(src2_len * KD_SZ_BOOL)                                                                                  \
  )

#define kdMemOpsCatPtr(dst, dst_len, src1, src1_len, src2, src2_len)                                                   \
  kdMemOpsCat(                                                                                                         \
    (void*)(dst),                                                                                                      \
    (kd_i64_t)(dst_len * KD_SZ_PTR),                                                                                   \
    (void*)(src1),                                                                                                     \
    (kd_i64_t)(src1_len * KD_SZ_PTR),                                                                                  \
    (void*)(src2),                                                                                                     \
    (kd_i64_t)(src2_len * KD_SZ_PTR)                                                                                   \
  )


#define kdMemOpsCompSpnByte(ptr, len, keys, keys_len)                                                                  \
  kdMemOpsCompSpn((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#define kdMemOpsCompSpnI8(ptr, len, keys, keys_len)                                                                    \
  kdMemOpsCompSpn((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#define kdMemOpsCompSpnU8(ptr, len, keys, keys_len)                                                                    \
  kdMemOpsCompSpn((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))

#define kdMemOpsCompSpnI16(ptr, len, keys, keys_len)                                                                   \
  kdMemOpsCompSpnU16((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#define kdMemOpsCompSpnI32(ptr, len, keys, keys_len)                                                                   \
  kdMemOpsCompSpnU32((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#define kdMemOpsCompSpnI64(ptr, len, keys, keys_len)                                                                   \
  kdMemOpsCompSpnU64((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))

#define kdMemOpsCompSpnImin(ptr, len, keys, keys_len)                                                                  \
  kdMemOpsCompSpn((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#define kdMemOpsCompSpnImax(ptr, len, keys, keys_len)                                                                  \
  kdMemOpsCompSpn((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))

#define kdMemOpsCompSpnUmin(ptr, len, keys, keys_len)                                                                  \
  kdMemOpsCompSpnU64((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#define kdMemOpsCompSpnUmax(ptr, len, keys, keys_len)                                                                  \
  kdMemOpsCompSpnU64((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#define kdMemOpsCompSpnUsize(ptr, len, keys, keys_len)                                                                 \
  kdMemOpsCompSpnU64((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))

#define kdMemOpsCompSpnChr(ptr, len, keys, keys_len)                                                                   \
  kdMemOpsCompSpnU32((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#define kdMemOpsCompSpnBool(ptr, len, keys, keys_len)                                                                  \
  kdMemOpsCompSpnU32((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))

#if defined KD_ARCH_64BIT_PTR
  #define kdMemOpsCompSpnPtr(ptr, len, keys, keys_len)                                                                 \
    kdMemOpsCompSpnU64((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#else
  #define kdMemOpsCompSpnPtr(ptr, len, keys, keys_len)                                                                 \
    kdMemOpsCompSpnU32((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#endif /* KD_ARCH_64BIT_PTR */


#define kdMemOpsCompSpnIndexByte(ptr, len, keys, keys_len)                                                             \
  kdMemOpsCompSpnIndex((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#define kdMemOpsCompSpnIndexI8(ptr, len, keys, keys_len)                                                               \
  kdMemOpsCompSpnIndex((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#define kdMemOpsCompSpnIndexU8(ptr, len, keys, keys_len)                                                               \
  kdMemOpsCompSpnIndex((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))

#define kdMemOpsCompSpnIndexI16(ptr, len, keys, keys_len)                                                              \
  kdMemOpsCompSpnIndexU16((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#define kdMemOpsCompSpnIndexI32(ptr, len, keys, keys_len)                                                              \
  kdMemOpsCompSpnIndexU32((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#define kdMemOpsCompSpnIndexI64(ptr, len, keys, keys_len)                                                              \
  kdMemOpsCompSpnIndexU64((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))

#define kdMemOpsCompSpnIndexImin(ptr, len, keys, keys_len)                                                             \
  kdMemOpsCompSpnIndex((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#define kdMemOpsCompSpnIndexImax(ptr, len, keys, keys_len)                                                             \
  kdMemOpsCompSpnIndex((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))

#define kdMemOpsCompSpnIndexUmin(ptr, len, keys, keys_len)                                                             \
  kdMemOpsCompSpnIndexU64((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#define kdMemOpsCompSpnIndexUmax(ptr, len, keys, keys_len)                                                             \
  kdMemOpsCompSpnIndexU64((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#define kdMemOpsCompSpnIndexUsize(ptr, len, keys, keys_len)                                                            \
  kdMemOpsCompSpnIndexU64((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))

#define kdMemOpsCompSpnIndexChr(ptr, len, keys, keys_len)                                                              \
  kdMemOpsCompSpnIndexU32((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#define kdMemOpsCompSpnIndexBool(ptr, len, keys, keys_len)                                                             \
  kdMemOpsCompSpnIndexU32((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))

#if defined KD_ARCH_64BIT_PTR
  #define kdMemOpsCompSpnIndexPtr(ptr, len, keys, keys_len)                                                            \
    kdMemOpsCompSpnIndexU64((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#else
  #define kdMemOpsCompSpnIndexPtr(ptr, len, keys, keys_len)                                                            \
    kdMemOpsCompSpnIndexU32((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#endif /* KD_ARCH_64BIT_PTR */


#define kdMemOpsSpnByte(ptr, len, keys, keys_len)                                                                      \
  kdMemOpsSpn((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#define kdMemOpsSpnI8(ptr, len, keys, keys_len)                                                                        \
  kdMemOpsSpn((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#define kdMemOpsSpnU8(ptr, len, keys, keys_len)                                                                        \
  kdMemOpsSpn((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))

#define kdMemOpsSpnI16(ptr, len, keys, keys_len)                                                                       \
  kdMemOpsSpnU16((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#define kdMemOpsSpnI32(ptr, len, keys, keys_len)                                                                       \
  kdMemOpsSpnU32((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#define kdMemOpsSpnI64(ptr, len, keys, keys_len)                                                                       \
  kdMemOpsSpnU64((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))

#define kdMemOpsSpnImin(ptr, len, keys, keys_len)                                                                      \
  kdMemOpsSpn((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#define kdMemOpsSpnUmin(ptr, len, keys, keys_len)                                                                      \
  kdMemOpsSpn((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))

#define kdMemOpsSpnImax(ptr, len, keys, keys_len)                                                                      \
  kdMemOpsSpnU64((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#define kdMemOpsSpnUmax(ptr, len, keys, keys_len)                                                                      \
  kdMemOpsSpnU64((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#define kdMemOpsSpnUsize(ptr, len, keys, keys_len)                                                                     \
  kdMemOpsSpnU64((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))

#define kdMemOpsSpnChr(ptr, len, keys, keys_len)                                                                       \
  kdMemOpsSpnU32((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#define kdMemOpsSpnBool(ptr, len, keys, keys_len)                                                                      \
  kdMemOpsSpnU32((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))

#if defined KD_ARCH_64BIT_PTR
  #define kdMemOpsSpnPtr(ptr, len, keys, keys_len)                                                                     \
    kdMemOpsSpnU64((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#else
  #define kdMemOpsSpnPtr(ptr, len, keys, keys_len)                                                                     \
    kdMemOpsSpnU32((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#endif /* KD_ARCH_64BIT_PTR */


KDAPI(kd_bool_t) kdMemOpsSwap(void* ptr, kd_i64_t len, kd_i64_t idx1, kd_i64_t idx2);
KDAPI(kd_bool_t) kdMemOpsSwapU16(void* ptr, kd_i64_t len, kd_i64_t idx1, kd_i64_t idx2);
KDAPI(kd_bool_t) kdMemOpsSwapU32(void* ptr, kd_i64_t len, kd_i64_t idx1, kd_i64_t idx2);
KDAPI(kd_bool_t) kdMemOpsSwapU64(void* ptr, kd_i64_t len, kd_i64_t idx1, kd_i64_t idx2);

KDAPI(kd_bool_t) kdMemOpsReverse(void* ptr, kd_i64_t len);
KDAPI(kd_bool_t) kdMemOpsReverseU16(void* ptr, kd_i64_t len);
KDAPI(kd_bool_t) kdMemOpsReverseU32(void* ptr, kd_i64_t len);
KDAPI(kd_bool_t) kdMemOpsReverseU64(void* ptr, kd_i64_t len);

KDAPI(kd_bool_t) kdMemOpsSet(void* ptr, kd_i64_t len, kd_byte_t val);
KDAPI(kd_bool_t) kdMemOpsSetU16(void* ptr, kd_i64_t len, kd_u16_t val);
KDAPI(kd_bool_t) kdMemOpsSetU32(void* ptr, kd_i64_t len, kd_u32_t val);
KDAPI(kd_bool_t) kdMemOpsSetU64(void* ptr, kd_i64_t len, kd_u64_t val);

KDAPI(kd_bool_t) kdMemOpsCpy(void* dst, void* src, kd_i64_t len);
KDAPI(kd_bool_t) kdMemOpsCpyU16(void* dst, void* src, kd_i64_t len);
KDAPI(kd_bool_t) kdMemOpsCpyU32(void* dst, void* src, kd_i64_t len);
KDAPI(kd_bool_t) kdMemOpsCpyU64(void* dst, void* src, kd_i64_t len);

KDAPI(kd_bool_t) kdMemOpsMove(void* dst, void* src, kd_i64_t len);
KDAPI(kd_bool_t) kdMemOpsMoveU16(void* dst, void* src, kd_i64_t len);
KDAPI(kd_bool_t) kdMemOpsMoveU32(void* dst, void* src, kd_i64_t len);
KDAPI(kd_bool_t) kdMemOpsMoveU64(void* dst, void* src, kd_i64_t len);

KDAPI(void*) kdMemOpsFind(void* ptr, kd_i64_t len, kd_byte_t item);
KDAPI(void*) kdMemOpsFindU16(void* ptr, kd_i64_t len, kd_u16_t item);
KDAPI(void*) kdMemOpsFindU32(void* ptr, kd_i64_t len, kd_u32_t item);
KDAPI(void*) kdMemOpsFindU64(void* ptr, kd_i64_t len, kd_u64_t item);

KDAPI(kd_i64_t) kdMemOpsFindIndex(void* ptr, kd_i64_t len, kd_byte_t item);
KDAPI(kd_i64_t) kdMemOpsFindIndexU16(void* ptr, kd_i64_t len, kd_u16_t item);
KDAPI(kd_i64_t) kdMemOpsFindIndexU32(void* ptr, kd_i64_t len, kd_u32_t item);
KDAPI(kd_i64_t) kdMemOpsFindIndexU64(void* ptr, kd_i64_t len, kd_u64_t item);

KDAPI(void*) kdMemOpsFindLast(void* ptr, kd_i64_t len, kd_byte_t item);
KDAPI(void*) kdMemOpsFindLastU16(void* ptr, kd_i64_t len, kd_u16_t item);
KDAPI(void*) kdMemOpsFindLastU32(void* ptr, kd_i64_t len, kd_u32_t item);
KDAPI(void*) kdMemOpsFindLastU64(void* ptr, kd_i64_t len, kd_u64_t item);

KDAPI(kd_i64_t) kdMemOpsFindLastIndex(void* ptr, kd_i64_t len, kd_byte_t item);
KDAPI(kd_i64_t) kdMemOpsFindLastIndexU16(void* ptr, kd_i64_t len, kd_u16_t item);
KDAPI(kd_i64_t) kdMemOpsFindLastIndexU32(void* ptr, kd_i64_t len, kd_u32_t item);
KDAPI(kd_i64_t) kdMemOpsFindLastIndexU64(void* ptr, kd_i64_t len, kd_u64_t item);

KDAPI(kd_i64_t) kdMemOpsFindAll(void* dst, kd_i64_t dst_len, void* ptr, kd_i64_t ptr_len, kd_byte_t item);
KDAPI(kd_i64_t) kdMemOpsFindAllU16(void* dst, kd_i64_t dst_len, void* ptr, kd_i64_t ptr_len, kd_u16_t item);
KDAPI(kd_i64_t) kdMemOpsFindAllU32(void* dst, kd_i64_t dst_len, void* ptr, kd_i64_t ptr_len, kd_u32_t item);
KDAPI(kd_i64_t) kdMemOpsFindAllU64(void* dst, kd_i64_t dst_len, void* ptr, kd_i64_t ptr_len, kd_u64_t item);

KDAPI(kd_i64_t) kdMemOpsFindAllIndex(kd_i64_t* idxs, kd_i64_t idxs_len, void* ptr, kd_i64_t ptr_len, kd_byte_t item);
KDAPI(kd_i64_t) kdMemOpsFindAllIndexU16(kd_i64_t* idxs, kd_i64_t idxs_len, void* ptr, kd_i64_t ptr_len, kd_u16_t item);
KDAPI(kd_i64_t) kdMemOpsFindAllIndexU32(kd_i64_t* idxs, kd_i64_t idxs_len, void* ptr, kd_i64_t ptr_len, kd_u32_t item);
KDAPI(kd_i64_t) kdMemOpsFindAllIndexU64(kd_i64_t* idxs, kd_i64_t idxs_len, void* ptr, kd_i64_t ptr_len, kd_u64_t item);

KDAPI(kd_i32_t) kdMemOpsCmp(void* ptr1, void* ptr2, kd_i64_t len);
KDAPI(kd_bool_t) kdMemOpsCat(void* dst, kd_i64_t dst_len, void* src1, kd_i64_t src1_len, void* src2, kd_i64_t src2_len);

KDAPI(void*) kdMemOpsCompSpn(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);
KDAPI(void*) kdMemOpsCompSpnU16(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);
KDAPI(void*) kdMemOpsCompSpnU32(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);
KDAPI(void*) kdMemOpsCompSpnU64(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);

KDAPI(kd_i64_t) kdMemOpsCompSpnIndex(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);
KDAPI(kd_i64_t) kdMemOpsCompSpnIndexU16(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);
KDAPI(kd_i64_t) kdMemOpsCompSpnIndexU32(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);
KDAPI(kd_i64_t) kdMemOpsCompSpnIndexU64(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);

KDAPI(kd_i64_t) kdMemOpsSpn(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);
KDAPI(kd_i64_t) kdMemOpsSpnU16(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);
KDAPI(kd_i64_t) kdMemOpsSpnU32(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);
KDAPI(kd_i64_t) kdMemOpsSpnU64(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);


KD_EXTERN_END


#endif /* KD_MEM_OPS_H_ */
