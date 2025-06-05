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


#define kdMemOpsSet(ptr, len, val)     kdGenMemOpsSetBytes((void*)(ptr), (kd_usize_t)(len), (kd_byte_t)(val))
#define kdMemOpsSetI8(ptr, len, val)   kdMemOpsSet(ptr, len, val)
#define kdMemOpsSetU8(ptr, len, val)   kdMemOpsSet(ptr, len, val)
#define kdMemOpsSetByte(ptr, len, val) kdMemOpsSet(ptr, len, val)
#if defined KD_ARCH_64BIT_INT
  #define kdMemOpsSetI16(ptr, len, val)  kdMemOpsSetU16((void*)(ptr), (kd_i64_t)(len), (kd_u16_t)(val))
  #define kdMemOpsSetI32(ptr, len, val)  kdMemOpsSetU32((void*)(ptr), (kd_i64_t)(len), (kd_u32_t)(val))
  #define kdMemOpsSetI64(ptr, len, val)  kdMemOpsSetU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(val))
  #define kdMemOpsSetImin(ptr, len, val) kdMemOpsSetUmin((void*)(ptr), (kd_i64_t)(len), (kd_umin_t)(val))
  #define kdMemOpsSetImax(ptr, len, val) kdMemOpsSetUmax((void*)(ptr), (kd_i64_t)(len), (kd_umax_t)(val))
#else /* !defined KD_ARCH_64BIT_INT */
  #define kdMemOpsSetI16(ptr, len, val)  kdMemOpsSetU16((void*)(ptr), (kd_i32_t)(len), (kd_u16_t)(val))
  #define kdMemOpsSetI32(ptr, len, val)  kdMemOpsSetU32((void*)(ptr), (kd_i32_t)(len), (kd_u32_t)(val))
  #define kdMemOpsSetImin(ptr, len, val) kdMemOpsSetUmin((void*)(ptr), (kd_i32_t)(len), (kd_umin_t)(val))
  #define kdMemOpsSetImax(ptr, len, val) kdMemOpsSetUmax((void*)(ptr), (kd_i32_t)(len), (kd_umax_t)(val))
#endif /* KD_ARCH_64BIT_INT */


#define kdMemOpsCpy(dst, src, len)     kdGenMemOpsCpy((void*)(dst), (void*)(src), (kd_usize_t)(len))
#define kdMemOpsCpyByte(dst, src, len) kdMemOpsCpy(dst, src, len)
#define kdMemOpsCpyI8(dst, src, len)   kdMemOpsCpy(dst, src, len)
#define kdMemOpsCpyU8(dst, src, len)   kdMemOpsCpy(dst, src, len)
#define kdMemOpsCpyI16(dst, src, len)  kdMemOpsCpy(dst, src, (len) * KD_SZ_I16)
#define kdMemOpsCpyU16(dst, src, len)  kdMemOpsCpy(dst, src, (len) * KD_SZ_U16)
#define kdMemOpsCpyI32(dst, src, len)  kdMemOpsCpy(dst, src, (len) * KD_SZ_I32)
#define kdMemOpsCpyU32(dst, src, len)  kdMemOpsCpy(dst, src, (len) * KD_SZ_U32)
#if defined KD_ARCH_64BIT_INT
  #define kdMemOpsCpyI64(dst, src, len) kdMemOpsCpy(dst, src, (len) * KD_SZ_I64)
  #define kdMemOpsCpyU64(dst, src, len) kdMemOpsCpy(dst, src, (len) * KD_SZ_U64)
#endif /* KD_ARCH_64BIT_INT */
#define kdMemOpsCpyImin(dst, src, len)  kdMemOpsCpy(dst, src, (len) * KD_SZ_IMIN)
#define kdMemOpsCpyUmin(dst, src, len)  kdMemOpsCpy(dst, src, (len) * KD_SZ_UMIN)
#define kdMemOpsCpyImax(dst, src, len)  kdMemOpsCpy(dst, src, (len) * KD_SZ_IMAX)
#define kdMemOpsCpyUmax(dst, src, len)  kdMemOpsCpy(dst, src, (len) * KD_SZ_UMAX)
#define kdMemOpsCpyUsize(dst, src, len) kdMemOpsCpy(dst, src, (len) * KD_SZ_USIZE)
#define kdMemOpsCpyChr(dst, src, len)   kdMemOpsCpy(dst, src, (len) * KD_SZ_CHR)
#define kdMemOpsCpyBool(dst, src, len)  kdMemOpsCpy(dst, src, (len) * KD_SZ_BOOL)
#define kdMemOpsCpyPtr(dst, src, len)   kdMemOpsCpy(dst, src, (len) * KD_SZ_PTR)


#define kdMemOpsMove(dst, src, len)     kdGenMemOpsMove((void*)(dst), (void*)(src), (kd_usize_t)(len))
#define kdMemOpsMoveByte(dst, src, len) kdMemOpsMove(dst, src, len)
#define kdMemOpsMoveI8(dst, src, len)   kdMemOpsMove(dst, src, len)
#define kdMemOpsMoveU8(dst, src, len)   kdMemOpsMove(dst, src, len)
#define kdMemOpsMoveI16(dst, src, len)  kdMemOpsMove(dst, src, (len) * KD_SZ_I16)
#define kdMemOpsMoveU16(dst, src, len)  kdMemOpsMove(dst, src, (len) * KD_SZ_U16)
#define kdMemOpsMoveI32(dst, src, len)  kdMemOpsMove(dst, src, (len) * KD_SZ_I32)
#define kdMemOpsMoveU32(dst, src, len)  kdMemOpsMove(dst, src, (len) * KD_SZ_U32)
#if defined KD_ARCH_64BIT_INT
  #define kdMemOpsMoveI64(dst, src, len) kdMemOpsMove(dst, src, (len) * KD_SZ_I64)
  #define kdMemOpsMoveU64(dst, src, len) kdMemOpsMove(dst, src, (len) * KD_SZ_U64)
#endif /* KD_ARCH_64BIT_INT */
#define kdMemOpsMoveImin(dst, src, len)  kdMemOpsMove(dst, src, (len) * KD_SZ_IMIN)
#define kdMemOpsMoveUmin(dst, src, len)  kdMemOpsMove(dst, src, (len) * KD_SZ_UMIN)
#define kdMemOpsMoveImax(dst, src, len)  kdMemOpsMove(dst, src, (len) * KD_SZ_IMAX)
#define kdMemOpsMoveUmax(dst, src, len)  kdMemOpsMove(dst, src, (len) * KD_SZ_UMAX)
#define kdMemOpsMoveUsize(dst, src, len) kdMemOpsMove(dst, src, (len) * KD_SZ_USIZE)
#define kdMemOpsMoveChr(dst, src, len)   kdMemOpsMove(dst, src, (len) * KD_SZ_CHR)
#define kdMemOpsMoveBool(dst, src, len)  kdMemOpsMove(dst, src, (len) * KD_SZ_BOOL)
#define kdMemOpsMovePtr(dst, src, len)   kdMemOpsMove(dst, src, (len) * KD_SZ_PTR)


#define kdMemOpsFind(ptr, len, item)     kdGenMemOpsFindByte((void*)(ptr), (kd_usize_t)(len), (kd_byte_t)(item))
#define kdMemOpsFindI8(ptr, len, item)   kdMemOpsFind(ptr, len, item)
#define kdMemOpsFindU8(ptr, len, item)   kdMemOpsFind(ptr, len, item)
#define kdMemOpsFindByte(ptr, len, item) kdMemOpsFind(ptr, len, item)
#if defined KD_ARCH_64BIT_INT
  #define kdMemOpsFindI16(ptr, len, item)  kdMemOpsFindU16((void*)(ptr), (kd_i64_t)(len), (kd_u16_t)(item))
  #define kdMemOpsFindI32(ptr, len, item)  kdMemOpsFindU32((void*)(ptr), (kd_i64_t)(len), (kd_u32_t)(item))
  #define kdMemOpsFindI64(ptr, len, item)  kdMemOpsFindU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(item))
  #define kdMemOpsFindImin(ptr, len, item) kdMemOpsFindUmin((void*)(ptr), (kd_i64_t)(len), (kd_umin_t)(item))
  #define kdMemOpsFindImax(ptr, len, item) kdMemOpsFindUmax((void*)(ptr), (kd_i64_t)(len), (kd_umax_t)(item))
#else /* !defined KD_ARCH_64BIT_INT */
  #define kdMemOpsFindI16(ptr, len, item)  kdMemOpsFindU16((void*)(ptr), (kd_i32_t)(len), (kd_u16_t)(item))
  #define kdMemOpsFindI32(ptr, len, item)  kdMemOpsFindU32((void*)(ptr), (kd_i32_t)(len), (kd_u32_t)(item))
  #define kdMemOpsFindImin(ptr, len, item) kdMemOpsFindUmin((void*)(ptr), (kd_i32_t)(len), (kd_umin_t)(item))
  #define kdMemOpsFindImax(ptr, len, item) kdMemOpsFindUmax((void*)(ptr), (kd_i32_t)(len), (kd_umax_t)(item))
#endif /* KD_ARCH_64BIT_INT */


#if defined KD_ARCH_64BIT_INT
  #define kdMemOpsFindIndexI8(ptr, len, item)   kdMemOpsFindIndex((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(item))
  #define kdMemOpsFindIndexU8(ptr, len, item)   kdMemOpsFindIndex((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(item))
  #define kdMemOpsFindIndexByte(ptr, len, item) kdMemOpsFindIndex((void*)(ptr), (kd_i64_t)(len), (kd_byte_t)(item))
  #define kdMemOpsFindIndexI16(ptr, len, item)  kdMemOpsFindIndexU16((void*)(ptr), (kd_i64_t)(len), (kd_u16_t)(item))
  #define kdMemOpsFindIndexI32(ptr, len, item)  kdMemOpsFindIndexU32((void*)(ptr), (kd_i64_t)(len), (kd_u32_t)(item))
  #define kdMemOpsFindIndexI64(ptr, len, item)  kdMemOpsFindIndexU64((void*)(ptr), (kd_i64_t)(len), (kd_u64_t)(item))
  #define kdMemOpsFindIndexImin(ptr, len, item) kdMemOpsFindIndexUmin((void*)(ptr), (kd_i64_t)(len), (kd_umin_t)(item))
  #define kdMemOpsFindIndexImax(ptr, len, item) kdMemOpsFindIndexUmax((void*)(ptr), (kd_i64_t)(len), (kd_umax_t)(item))
#else /* !defined KD_ARCH_64BIT_INT */
  #define kdMemOpsFindIndexI8(ptr, len, item)   kdMemOpsFindIndex((void*)(ptr), (kd_i32_t)(len), (kd_byte_t)(item))
  #define kdMemOpsFindIndexU8(ptr, len, item)   kdMemOpsFindIndex((void*)(ptr), (kd_i32_t)(len), (kd_byte_t)(item))
  #define kdMemOpsFindIndexByte(ptr, len, item) kdMemOpsFindIndex((void*)(ptr), (kd_i32_t)(len), (kd_byte_t)(item))
  #define kdMemOpsFindIndexI16(ptr, len, item)  kdMemOpsFindIndexU16((void*)(ptr), (kd_i32_t)(len), (kd_u16_t)(item))
  #define kdMemOpsFindIndexI32(ptr, len, item)  kdMemOpsFindIndexU32((void*)(ptr), (kd_i32_t)(len), (kd_u32_t)(item))
  #define kdMemOpsFindIndexImin(ptr, len, item) kdMemOpsFindIndexUmin((void*)(ptr), (kd_i32_t)(len), (kd_umin_t)(item))
  #define kdMemOpsFindIndexImax(ptr, len, item) kdMemOpsFindIndexUmax((void*)(ptr), (kd_i32_t)(len), (kd_umax_t)(item))
#endif /* KD_ARCH_64BIT_INT */


#define kdMemOpsCmp(ptr1, ptr2, len)     kdGenMemOpsCmp((void*)(ptr1), (void*)(ptr2), (kd_usize_t)(len))
#define kdMemOpsCmpByte(ptr1, ptr2, len) kdMemOpsCmp(ptr1, ptr2, len)
#define kdMemOpsCmpI8(ptr1, ptr2, len)   kdMemOpsCmp(ptr1, ptr2, len)
#define kdMemOpsCmpU8(ptr1, ptr2, len)   kdMemOpsCmp(ptr1, ptr2, len)
#define kdMemOpsCmpI16(ptr1, ptr2, len)  kdMemOpsCmp(ptr1, ptr2, (len) * KD_SZ_I16)
#define kdMemOpsCmpU16(ptr1, ptr2, len)  kdMemOpsCmp(ptr1, ptr2, (len) * KD_SZ_U16)
#define kdMemOpsCmpI32(ptr1, ptr2, len)  kdMemOpsCmp(ptr1, ptr2, (len) * KD_SZ_I32)
#define kdMemOpsCmpU32(ptr1, ptr2, len)  kdMemOpsCmp(ptr1, ptr2, (len) * KD_SZ_U32)
#if defined KD_ARCH_64BIT_INT
  #define kdMemOpsCmpI64(ptr1, ptr2, len) kdMemOpsCmp(ptr1, ptr2, (len) * KD_SZ_I64)
  #define kdMemOpsCmpU64(ptr1, ptr2, len) kdMemOpsCmp(ptr1, ptr2, (len) * KD_SZ_U64)
#endif /* KD_ARCH_64BIT_INT */
#define kdMemOpsCmpImin(ptr1, ptr2, len)  kdMemOpsCmp(ptr1, ptr2, (len) * KD_SZ_IMIN)
#define kdMemOpsCmpUmin(ptr1, ptr2, len)  kdMemOpsCmp(ptr1, ptr2, (len) * KD_SZ_UMIN)
#define kdMemOpsCmpImax(ptr1, ptr2, len)  kdMemOpsCmp(ptr1, ptr2, (len) * KD_SZ_IMAX)
#define kdMemOpsCmpUmax(ptr1, ptr2, len)  kdMemOpsCmp(ptr1, ptr2, (len) * KD_SZ_UMAX)
#define kdMemOpsCmpUsize(ptr1, ptr2, len) kdMemOpsCmp(ptr1, ptr2, (len) * KD_SZ_USIZE)
#define kdMemOpsCmpChr(ptr1, ptr2, len)   kdMemOpsCmp(ptr1, ptr2, (len) * KD_SZ_CHR)
#define kdMemOpsCmpBool(ptr1, ptr2, len)  kdMemOpsCmp(ptr1, ptr2, (len) * KD_SZ_BOOL)
#define kdMemOpsCmpPtr(ptr1, ptr2, len)   kdMemOpsCmp(ptr1, ptr2, (len) * KD_SZ_PTR)


#define kdMemOpsCat(dst, len, src1, len1, src2, len2)                                                                  \
  kdGenMemOpsCat((void*)(dst), (kd_usize_t)(len), (void*)(src1), (kd_usize_t)(len1), (void*)(src2), (kd_usize_t)(len2))
#define kdMemOpsCatByte(dst, len, src1, len1, src2, len2) kdMemOpsCat(dst, len, src1, len1, src2, len2)
#define kdMemOpsCatI8(dst, len, src1, len1, src2, len2)   kdMemOpsCat(dst, len, src1, len1, src2, len2)
#define kdMemOpsCatU8(dst, len, src1, len1, src2, len2)   kdMemOpsCat(dst, len, src1, len1, src2, len2)
#define kdMemOpsCatI16(dst, len, src1, len1, src2, len2)                                                               \
  kdMemOpsCat(dst, (len) * KD_SZ_I16, src1, (len1) * KD_SZ_I16, src2, (len2) * KD_SZ_I16)
#define kdMemOpsCatU16(dst, len, src1, len1, src2, len2)                                                               \
  kdMemOpsCat(dst, (len) * KD_SZ_U16, src1, (len1) * KD_SZ_U16, src2, (len2) * KD_SZ_U16)
#define kdMemOpsCatI32(dst, len, src1, len1, src2, len2)                                                               \
  kdMemOpsCat(dst, (len) * KD_SZ_I32, src1, (len1) * KD_SZ_I32, src2, (len2) * KD_SZ_I32)
#define kdMemOpsCatU32(dst, len, src1, len1, src2, len2)                                                               \
  kdMemOpsCat(dst, (len) * KD_SZ_U32, src1, (len1) * KD_SZ_U32, src2, (len2) * KD_SZ_U32)
#if defined KD_ARCH_64BIT_INT
  #define kdMemOpsCatI64(dst, len, src1, len1, src2, len2)                                                             \
    kdMemOpsCat(dst, (len) * KD_SZ_I64, src1, (len1) * KD_SZ_I64, src2, (len2) * KD_SZ_I64)
  #define kdMemOpsCatU64(dst, len, src1, len1, src2, len2)                                                             \
    kdMemOpsCat(dst, (len) * KD_SZ_U64, src1, (len1) * KD_SZ_U64, src2, (len2) * KD_SZ_U64)
#endif /* KD_ARCH_64BIT_INT */
#define kdMemOpsCatImin(dst, len, src1, len1, src2, len2)                                                              \
  kdMemOpsCat(dst, (len) * KD_SZ_IMIN, src1, (len1) * KD_SZ_IMIN, src2, (len2) * KD_SZ_IMIN)
#define kdMemOpsCatUmin(dst, len, src1, len1, src2, len2)                                                              \
  kdMemOpsCat(dst, (len) * KD_SZ_UMIN, src1, (len1) * KD_SZ_UMIN, src2, (len2) * KD_SZ_UMIN)
#define kdMemOpsCatImax(dst, len, src1, len1, src2, len2)                                                              \
  kdMemOpsCat(dst, (len) * KD_SZ_IMAX, src1, (len1) * KD_SZ_IMAX, src2, (len2) * KD_SZ_IMAX)
#define kdMemOpsCatUmax(dst, len, src1, len1, src2, len2)                                                              \
  kdMemOpsCat(dst, (len) * KD_SZ_UMAX, src1, (len1) * KD_SZ_UMAX, src2, (len2) * KD_SZ_UMAX)
#define kdMemOpsCatUsize(dst, len, src1, len1, src2, len2)                                                             \
  kdMemOpsCat(dst, (len) * KD_SZ_USIZE, src1, (len1) * KD_SZ_USIZE, src2, (len2) * KD_SZ_USIZE)
#define kdMemOpsCatChr(dst, len, src1, len1, src2, len2)                                                               \
  kdMemOpsCat(dst, (len) * KD_SZ_CHR, src1, (len1) * KD_SZ_CHR, src2, (len2) * KD_SZ_CHR)
#define kdMemOpsCatBool(dst, len, src1, len1, src2, len2)                                                              \
  kdMemOpsCat(dst, (len) * KD_SZ_BOOL, src1, (len1) * KD_SZ_BOOL, src2, (len2) * KD_SZ_BOOL)
#define kdMemOpsCatPtr(dst, len, src1, len1, src2, len2)                                                               \
  kdMemOpsCat(dst, (len) * KD_SZ_PTR, src1, (len1) * KD_SZ_PTR, src2, (len2) * KD_SZ_PTR)


#define kdMemOpsCompSpn(ptr, len, keys, keys_len)                                                                      \
  kdGenMemOpsBytesCompSpn((void*)(ptr), (kd_usize_t)(len), (void*)(keys), (kd_usize_t)(keys_len))
#define kdMemOpsCompSpnI8(ptr, len, keys, keys_len)   kdMemOpsCompSpn(ptr, len, keys, keys_len)
#define kdMemOpsCompSpnU8(ptr, len, keys, keys_len)   kdMemOpsCompSpn(ptr, len, keys, keys_len)
#define kdMemOpsCompSpnByte(ptr, len, keys, keys_len) kdMemOpsCompSpn(ptr, len, keys, keys_len)
#if defined KD_ARCH_64BIT_INT
  #define kdMemOpsCompSpnI16(ptr, len, keys, keys_len)                                                                 \
    kdMemOpsCompSpnU16((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
  #define kdMemOpsCompSpnI32(ptr, len, keys, keys_len)                                                                 \
    kdMemOpsCompSpnU32((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
  #define kdMemOpsCompSpnI64(ptr, len, keys, keys_len)                                                                 \
    kdMemOpsCompSpnU64((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
  #define kdMemOpsCompSpnImin(ptr, len, keys, keys_len)                                                                \
    kdMemOpsCompSpnUmin((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
  #define kdMemOpsCompSpnImax(ptr, len, keys, keys_len)                                                                \
    kdMemOpsCompSpnUmax((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#else /* !defined KD_ARCH_64BIT_INT */
  #define kdMemOpsCompSpnI16(ptr, len, keys, keys_len)                                                                 \
    kdMemOpsCompSpnU16((void*)(ptr), (kd_i32_t)(len), (void*)(keys), (kd_i32_t)(keys_len))
  #define kdMemOpsCompSpnI32(ptr, len, keys, keys_len)                                                                 \
    kdMemOpsCompSpnU32((void*)(ptr), (kd_i32_t)(len), (void*)(keys), (kd_i32_t)(keys_len))
  #define kdMemOpsCompSpnImin(ptr, len, keys, keys_len)                                                                \
    kdMemOpsCompSpnUmin((void*)(ptr), (kd_i32_t)(len), (void*)(keys), (kd_i32_t)(keys_len))
  #define kdMemOpsCompSpnImax(ptr, len, keys, keys_len)                                                                \
    kdMemOpsCompSpnUmax((void*)(ptr), (kd_i32_t)(len), (void*)(keys), (kd_i32_t)(keys_len))
#endif /* KD_ARCH_64BIT_INT */


#if defined KD_ARCH_64BIT_INT
  #define kdMemOpsCompSpnIndexI8(ptr, len, keys, keys_len)                                                             \
    kdMemOpsCompSpnIndex((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
  #define kdMemOpsCompSpnIndexU8(ptr, len, keys, keys_len)                                                             \
    kdMemOpsCompSpnIndex((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
  #define kdMemOpsCompSpnIndexByte(ptr, len, keys, keys_len)                                                           \
    kdMemOpsCompSpnIndex((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
  #define kdMemOpsCompSpnIndexI16(ptr, len, keys, keys_len)                                                            \
    kdMemOpsCompSpnIndexU16((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
  #define kdMemOpsCompSpnIndexI32(ptr, len, keys, keys_len)                                                            \
    kdMemOpsCompSpnIndexU32((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
  #define kdMemOpsCompSpnIndexI64(ptr, len, keys, keys_len)                                                            \
    kdMemOpsCompSpnIndexU64((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
  #define kdMemOpsCompSpnIndexImin(ptr, len, keys, keys_len)                                                           \
    kdMemOpsCompSpnIndexUmin((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
  #define kdMemOpsCompSpnIndexImax(ptr, len, keys, keys_len)                                                           \
    kdMemOpsCompSpnIndexUmax((void*)(ptr), (kd_i64_t)(len), (void*)(keys), (kd_i64_t)(keys_len))
#else /* !defined KD_ARCH_64BIT_INT */
  #define kdMemOpsCompSpnIndexI8(ptr, len, keys, keys_len)                                                             \
    kdMemOpsCompSpnIndex((void*)(ptr), (kd_i32_t)(len), (void*)(keys), (kd_i32_t)(keys_len))
  #define kdMemOpsCompSpnIndexU8(ptr, len, keys, keys_len)                                                             \
    kdMemOpsCompSpnIndex((void*)(ptr), (kd_i32_t)(len), (void*)(keys), (kd_i32_t)(keys_len))
  #define kdMemOpsCompSpnIndexByte(ptr, len, keys, keys_len)                                                           \
    kdMemOpsCompSpnIndex((void*)(ptr), (kd_i32_t)(len), (void*)(keys), (kd_i32_t)(keys_len))
  #define kdMemOpsCompSpnIndexI16(ptr, len, keys, keys_len)                                                            \
    kdMemOpsCompSpnIndexU16((void*)(ptr), (kd_i32_t)(len), (void*)(keys), (kd_i32_t)(keys_len))
  #define kdMemOpsCompSpnIndexI32(ptr, len, keys, keys_len)                                                            \
    kdMemOpsCompSpnIndexU32((void*)(ptr), (kd_i32_t)(len), (void*)(keys), (kd_i32_t)(keys_len))
  #define kdMemOpsCompSpnIndexImin(ptr, len, keys, keys_len)                                                           \
    kdMemOpsCompSpnIndexUmin((void*)(ptr), (kd_i32_t)(len), (void*)(keys), (kd_i32_t)(keys_len))
  #define kdMemOpsCompSpnIndexImax(ptr, len, keys, keys_len)                                                           \
    kdMemOpsCompSpnIndexUmax((void*)(ptr), (kd_i32_t)(len), (void*)(keys), (kd_i32_t)(keys_len))
#endif /* KD_ARCH_64BIT_INT */


#if defined KD_ARCH_64BIT_INT
  #define kdMemOpsSpn(ptr, len, keys, keys_len)                                                                        \
    (kd_i64_t) kdGenMemOpsBytesSpn((void*)(ptr), (kd_usize_t)(len), (void*)(keys), (kd_usize_t)(keys_len))
  #define kdMemOpsSpnByte(ptr, len, keys, keys_len) (kd_i64_t)(kdMemOpsSpn(ptr, len, keys, keys_len))
  #define kdMemOpsSpnI8(ptr, len, keys, keys_len)   (kd_i64_t)(kdMemOpsSpn(ptr, len, keys, keys_len))
  #define kdMemOpsSpnU8(ptr, len, keys, keys_len)   (kd_i64_t)(kdMemOpsSpn(ptr, len, keys, keys_len))
  #define kdMemOpsSpnI16(ptr, len, keys, keys_len)                                                                     \
    (kd_i64_t)(kdMemOpsSpn(ptr, (len) * KD_SZ_I16, keys, (keys_len) * KD_SZ_I16) / KD_SZ_I16)
  #define kdMemOpsSpnU16(ptr, len, keys, keys_len)                                                                     \
    (kd_i64_t)(kdMemOpsSpn(ptr, (len) * KD_SZ_U16, keys, (keys_len) * KD_SZ_U16) / KD_SZ_U16)
  #define kdMemOpsSpnI32(ptr, len, keys, keys_len)                                                                     \
    (kd_i64_t)(kdMemOpsSpn(ptr, (len) * KD_SZ_I32, keys, (keys_len) * KD_SZ_I32) / KD_SZ_I32)
  #define kdMemOpsSpnU32(ptr, len, keys, keys_len)                                                                     \
    (kd_i64_t)(kdMemOpsSpn(ptr, (len) * KD_SZ_U32, keys, (keys_len) * KD_SZ_U32) / KD_SZ_U32)
  #define kdMemOpsSpnI64(ptr, len, keys, keys_len)                                                                     \
    (kd_i64_t)(kdMemOpsSpn(ptr, (len) * KD_SZ_I64, keys, (keys_len) * KD_SZ_I64) / KD_SZ_I64)
  #define kdMemOpsSpnU64(ptr, len, keys, keys_len)                                                                     \
    (kd_i64_t)(kdMemOpsSpn(ptr, (len) * KD_SZ_U64, keys, (keys_len) * KD_SZ_U64) / KD_SZ_U64)
  #define kdMemOpsSpnImin(ptr, len, keys, keys_len)                                                                    \
    (kd_i64_t)(kdMemOpsSpn(ptr, (len) * KD_SZ_IMIN, keys, (keys_len) * KD_SZ_IMIN) / KD_SZ_IMIN)
  #define kdMemOpsSpnUmin(ptr, len, keys, keys_len)                                                                    \
    (kd_i64_t)(kdMemOpsSpn(ptr, (len) * KD_SZ_UMIN, keys, (keys_len) * KD_SZ_UMIN) / KD_SZ_UMIN)
  #define kdMemOpsSpnImax(ptr, len, keys, keys_len)                                                                    \
    (kd_i64_t)(kdMemOpsSpn(ptr, (len) * KD_SZ_IMAX, keys, (keys_len) * KD_SZ_IMAX) / KD_SZ_IMAX)
  #define kdMemOpsSpnUmax(ptr, len, keys, keys_len)                                                                    \
    (kd_i64_t)(kdMemOpsSpn(ptr, (len) * KD_SZ_UMAX, keys, (keys_len) * KD_SZ_UMAX) / KD_SZ_UMAX)
  #define kdMemOpsSpnUsize(ptr, len, keys, keys_len)                                                                   \
    (kd_i64_t)(kdMemOpsSpn(ptr, (len) * KD_SZ_USIZE, keys, (keys_len) * KD_SZ_USIZE) / KD_SZ_USIZE)
  #define kdMemOpsSpnChr(ptr, len, keys, keys_len)                                                                     \
    (kd_i64_t)(kdMemOpsSpn(ptr, (len) * KD_SZ_CHR, keys, (keys_len) * KD_SZ_CHR) / KD_SZ_CHR)
  #define kdMemOpsSpnBool(ptr, len, keys, keys_len)                                                                    \
    (kd_i64_t)(kdMemOpsSpn(ptr, (len) * KD_SZ_BOOL, keys, (keys_len) * KD_SZ_BOOL) / KD_SZ_BOOL)
  #define kdMemOpsSpnPtr(ptr, len, keys, keys_len)                                                                     \
    (kd_i64_t)(kdMemOpsSpn(ptr, (len) * KD_SZ_PTR, keys, (keys_len) * KD_SZ_PTR) / KD_SZ_PTR)
#else /* !defined KD_ARCH_64BIT_INT */
  #define kdMemOpsSpn(ptr, len, keys, keys_len)                                                                        \
    (kd_i32_t) kdGenMemOpsBytesSpn((void*)(ptr), (kd_usize_t)(len), (void*)(keys), (kd_usize_t)(keys_len))
  #define kdMemOpsSpnByte(ptr, len, keys, keys_len) (kd_i32_t)(kdMemOpsSpn(ptr, len, keys, keys_len))
  #define kdMemOpsSpnI8(ptr, len, keys, keys_len)   (kd_i32_t)(kdMemOpsSpn(ptr, len, keys, keys_len))
  #define kdMemOpsSpnU8(ptr, len, keys, keys_len)   (kd_i32_t)(kdMemOpsSpn(ptr, len, keys, keys_len))
  #define kdMemOpsSpnI16(ptr, len, keys, keys_len)                                                                     \
    (kd_i32_t)(kdMemOpsSpn(ptr, (len) * KD_SZ_I16, keys, (keys_len) * KD_SZ_I16) / KD_SZ_I16)
  #define kdMemOpsSpnU16(ptr, len, keys, keys_len)                                                                     \
    (kd_i32_t)(kdMemOpsSpn(ptr, (len) * KD_SZ_U16, keys, (keys_len) * KD_SZ_U16) / KD_SZ_U16)
  #define kdMemOpsSpnI32(ptr, len, keys, keys_len)                                                                     \
    (kd_i32_t)(kdMemOpsSpn(ptr, (len) * KD_SZ_I32, keys, (keys_len) * KD_SZ_I32) / KD_SZ_I32)
  #define kdMemOpsSpnU32(ptr, len, keys, keys_len)                                                                     \
    (kd_i32_t)(kdMemOpsSpn(ptr, (len) * KD_SZ_U32, keys, (keys_len) * KD_SZ_U32) / KD_SZ_U32)
  #define kdMemOpsSpnImin(ptr, len, keys, keys_len)                                                                    \
    (kd_i32_t)(kdMemOpsSpn(ptr, (len) * KD_SZ_IMIN, keys, (keys_len) * KD_SZ_IMIN) / KD_SZ_IMIN)
  #define kdMemOpsSpnUmin(ptr, len, keys, keys_len)                                                                    \
    (kd_i32_t)(kdMemOpsSpn(ptr, (len) * KD_SZ_UMIN, keys, (keys_len) * KD_SZ_UMIN) / KD_SZ_UMIN)
  #define kdMemOpsSpnImax(ptr, len, keys, keys_len)                                                                    \
    (kd_i32_t)(kdMemOpsSpn(ptr, (len) * KD_SZ_IMAX, keys, (keys_len) * KD_SZ_IMAX) / KD_SZ_IMAX)
  #define kdMemOpsSpnUmax(ptr, len, keys, keys_len)                                                                    \
    (kd_i32_t)(kdMemOpsSpn(ptr, (len) * KD_SZ_UMAX, keys, (keys_len) * KD_SZ_UMAX) / KD_SZ_UMAX)
  #define kdMemOpsSpnUsize(ptr, len, keys, keys_len)                                                                   \
    (kd_i32_t)(kdMemOpsSpn(ptr, (len) * KD_SZ_USIZE, keys, (keys_len) * KD_SZ_USIZE) / KD_SZ_USIZE)
  #define kdMemOpsSpnChr(ptr, len, keys, keys_len)                                                                     \
    (kd_i32_t)(kdMemOpsSpn(ptr, (len) * KD_SZ_CHR, keys, (keys_len) * KD_SZ_CHR) / KD_SZ_CHR)
  #define kdMemOpsSpnBool(ptr, len, keys, keys_len)                                                                    \
    (kd_i32_t)(kdMemOpsSpn(ptr, (len) * KD_SZ_BOOL, keys, (keys_len) * KD_SZ_BOOL) / KD_SZ_BOOL)
  #define kdMemOpsSpnPtr(ptr, len, keys, keys_len)                                                                     \
    (kd_i32_t)(kdMemOpsSpn(ptr, (len) * KD_SZ_PTR, keys, (keys_len) * KD_SZ_PTR) / KD_SZ_PTR)
#endif /* KD_ARCH_64BIT_INT */


#if defined KD_ARCH_64BIT_INT
KDAPI(kd_bool_t) kdMemOpsSetU16(void* ptr, kd_i64_t len, kd_u16_t val);
KDAPI(kd_bool_t) kdMemOpsSetU32(void* ptr, kd_i64_t len, kd_u32_t val);
KDAPI(kd_bool_t) kdMemOpsSetU64(void* ptr, kd_i64_t len, kd_u64_t val);
KDAPI(kd_bool_t) kdMemOpsSetUmin(void* ptr, kd_i64_t len, kd_umin_t val);
KDAPI(kd_bool_t) kdMemOpsSetUmax(void* ptr, kd_i64_t len, kd_umax_t val);
KDAPI(kd_bool_t) kdMemOpsSetUsize(void* ptr, kd_i64_t len, kd_usize_t val);
KDAPI(kd_bool_t) kdMemOpsSetChr(void* ptr, kd_i64_t len, kd_chr_t val);
KDAPI(kd_bool_t) kdMemOpsSetBool(void* ptr, kd_i64_t len, kd_bool_t val);
KDAPI(kd_bool_t) kdMemOpsSetPtr(void* ptr, kd_i64_t len, void* val);

KDAPI(void*) kdMemOpsFindU16(void* ptr, kd_i64_t len, kd_u16_t item);
KDAPI(void*) kdMemOpsFindU32(void* ptr, kd_i64_t len, kd_u32_t item);
KDAPI(void*) kdMemOpsFindU64(void* ptr, kd_i64_t len, kd_u64_t item);
KDAPI(void*) kdMemOpsFindUmin(void* ptr, kd_i64_t len, kd_umin_t item);
KDAPI(void*) kdMemOpsFindUmax(void* ptr, kd_i64_t len, kd_umax_t item);
KDAPI(void*) kdMemOpsFindUsize(void* ptr, kd_i64_t len, kd_usize_t item);
KDAPI(void*) kdMemOpsFindChr(void* ptr, kd_i64_t len, kd_chr_t item);
KDAPI(void*) kdMemOpsFindBool(void* ptr, kd_i64_t len, kd_bool_t item);
KDAPI(void*) kdMemOpsFindPtr(void* ptr, kd_i64_t len, void* item);

KDAPI(kd_i64_t) kdMemOpsFindIndex(void* ptr, kd_i64_t len, kd_byte_t item);
KDAPI(kd_i64_t) kdMemOpsFindIndexU16(void* ptr, kd_i64_t len, kd_u16_t item);
KDAPI(kd_i64_t) kdMemOpsFindIndexU32(void* ptr, kd_i64_t len, kd_u32_t item);
KDAPI(kd_i64_t) kdMemOpsFindIndexU64(void* ptr, kd_i64_t len, kd_u64_t item);
KDAPI(kd_i64_t) kdMemOpsFindIndexUmin(void* ptr, kd_i64_t len, kd_umin_t item);
KDAPI(kd_i64_t) kdMemOpsFindIndexUmax(void* ptr, kd_i64_t len, kd_umax_t item);
KDAPI(kd_i64_t) kdMemOpsFindIndexUsize(void* ptr, kd_i64_t len, kd_usize_t item);
KDAPI(kd_i64_t) kdMemOpsFindIndexChr(void* ptr, kd_i64_t len, kd_chr_t item);
KDAPI(kd_i64_t) kdMemOpsFindIndexBool(void* ptr, kd_i64_t len, kd_bool_t item);
KDAPI(kd_i64_t) kdMemOpsFindIndexPtr(void* ptr, kd_i64_t len, void* item);

KDAPI(void*) kdMemOpsCompSpnU16(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);
KDAPI(void*) kdMemOpsCompSpnU32(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);
KDAPI(void*) kdMemOpsCompSpnU64(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);
KDAPI(void*) kdMemOpsCompSpnUmin(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);
KDAPI(void*) kdMemOpsCompSpnUmax(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);
KDAPI(void*) kdMemOpsCompSpnUsize(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);
KDAPI(void*) kdMemOpsCompSpnChr(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);
KDAPI(void*) kdMemOpsCompSpnBool(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);
KDAPI(void*) kdMemOpsCompSpnPtr(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);

KDAPI(kd_i64_t) kdMemOpsCompSpnIndex(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);
KDAPI(kd_i64_t) kdMemOpsCompSpnIndexU16(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);
KDAPI(kd_i64_t) kdMemOpsCompSpnIndexU32(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);
KDAPI(kd_i64_t) kdMemOpsCompSpnIndexU64(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);
KDAPI(kd_i64_t) kdMemOpsCompSpnIndexUmin(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);
KDAPI(kd_i64_t) kdMemOpsCompSpnIndexUmax(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);
KDAPI(kd_i64_t) kdMemOpsCompSpnIndexUsize(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);
KDAPI(kd_i64_t) kdMemOpsCompSpnIndexChr(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);
KDAPI(kd_i64_t) kdMemOpsCompSpnIndexBool(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);
KDAPI(kd_i64_t) kdMemOpsCompSpnIndexPtr(void* ptr, kd_i64_t len, void* keys, kd_i64_t keys_len);
#else  /* !defined KD_ARCH_64BIT_INT */
KDAPI(kd_bool_t) kdMemOpsSetU16(void* ptr, kd_i32_t len, kd_u16_t val);
KDAPI(kd_bool_t) kdMemOpsSetU32(void* ptr, kd_i32_t len, kd_u32_t val);
KDAPI(kd_bool_t) kdMemOpsSetUmin(void* ptr, kd_i32_t len, kd_umin_t val);
KDAPI(kd_bool_t) kdMemOpsSetUmax(void* ptr, kd_i32_t len, kd_umax_t val);
KDAPI(kd_bool_t) kdMemOpsSetUsize(void* ptr, kd_i32_t len, kd_usize_t val);
KDAPI(kd_bool_t) kdMemOpsSetChr(void* ptr, kd_i32_t len, kd_chr_t val);
KDAPI(kd_bool_t) kdMemOpsSetBool(void* ptr, kd_i32_t len, kd_bool_t val);
KDAPI(kd_bool_t) kdMemOpsSetPtr(void* ptr, kd_i32_t len, void* val);

KDAPI(void*) kdMemOpsFindU16(void* ptr, kd_i32_t len, kd_u16_t item);
KDAPI(void*) kdMemOpsFindU32(void* ptr, kd_i32_t len, kd_u32_t item);
KDAPI(void*) kdMemOpsFindUmin(void* ptr, kd_i32_t len, kd_umin_t item);
KDAPI(void*) kdMemOpsFindUmax(void* ptr, kd_i32_t len, kd_umax_t item);
KDAPI(void*) kdMemOpsFindUsize(void* ptr, kd_i32_t len, kd_usize_t item);
KDAPI(void*) kdMemOpsFindChr(void* ptr, kd_i32_t len, kd_chr_t item);
KDAPI(void*) kdMemOpsFindBool(void* ptr, kd_i32_t len, kd_bool_t item);
KDAPI(void*) kdMemOpsFindPtr(void* ptr, kd_i32_t len, void* item);

KDAPI(kd_i32_t) kdMemOpsFindIndex(void* ptr, kd_i32_t len, kd_byte_t item);
KDAPI(kd_i32_t) kdMemOpsFindIndexU16(void* ptr, kd_i32_t len, kd_u16_t item);
KDAPI(kd_i32_t) kdMemOpsFindIndexU32(void* ptr, kd_i32_t len, kd_u32_t item);
KDAPI(kd_i32_t) kdMemOpsFindIndexUmin(void* ptr, kd_i32_t len, kd_umin_t item);
KDAPI(kd_i32_t) kdMemOpsFindIndexUmax(void* ptr, kd_i32_t len, kd_umax_t item);
KDAPI(kd_i32_t) kdMemOpsFindIndexUsize(void* ptr, kd_i32_t len, kd_usize_t item);
KDAPI(kd_i32_t) kdMemOpsFindIndexChr(void* ptr, kd_i32_t len, kd_chr_t item);
KDAPI(kd_i32_t) kdMemOpsFindIndexBool(void* ptr, kd_i32_t len, kd_bool_t item);
KDAPI(kd_i32_t) kdMemOpsFindIndexPtr(void* ptr, kd_i32_t len, void* item);

KDAPI(void*) kdMemOpsCompSpnU16(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len);
KDAPI(void*) kdMemOpsCompSpnU32(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len);
KDAPI(void*) kdMemOpsCompSpnUmin(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len);
KDAPI(void*) kdMemOpsCompSpnUmax(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len);
KDAPI(void*) kdMemOpsCompSpnUsize(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len);
KDAPI(void*) kdMemOpsCompSpnChr(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len);
KDAPI(void*) kdMemOpsCompSpnBool(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len);
KDAPI(void*) kdMemOpsCompSpnPtr(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len);

KDAPI(kd_i32_t) kdMemOpsCompSpnIndex(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len);
KDAPI(kd_i32_t) kdMemOpsCompSpnIndexU16(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len);
KDAPI(kd_i32_t) kdMemOpsCompSpnIndexU32(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len);
KDAPI(kd_i32_t) kdMemOpsCompSpnIndexUmin(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len);
KDAPI(kd_i32_t) kdMemOpsCompSpnIndexUmax(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len);
KDAPI(kd_i32_t) kdMemOpsCompSpnIndexUsize(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len);
KDAPI(kd_i32_t) kdMemOpsCompSpnIndexChr(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len);
KDAPI(kd_i32_t) kdMemOpsCompSpnIndexBool(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len);
KDAPI(kd_i32_t) kdMemOpsCompSpnIndexPtr(void* ptr, kd_i32_t len, void* keys, kd_i32_t keys_len);
#endif /* KD_ARCH_64BIT_INT */


KD_EXTERN_END


#endif /* KD_MEM_OPS_H_ */
