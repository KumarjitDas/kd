/**
 * @file gen_arr.h
 * @author Kumarjit Das
 * @date 2025-06-23
 * @since 0.0.12
 * @brief Main header file of the ARR library.
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


#ifndef KD_ARR_H_
#define KD_ARR_H_


#include "kd/defs.h"
#include "kd/fixed_width.h"
#include "kd/gen_arr.h"

KD_EXTERN_BEGIN


#define kdArrCreate(len, allocator)                                         kdGenArrCreate(KD_SZ_BYTE, KD_BASE_INT_C(len), (allocator))
#define kdArrCreateByte(len, allocator)                                     kdGenArrCreate(KD_SZ_BYTE, KD_BASE_INT_C(len), (allocator))
#define kdArrCreateI8(len, allocator)                                       kdGenArrCreate(KD_SZ_I8, KD_BASE_INT_C(len), (allocator))
#define kdArrCreateU8(len, allocator)                                       kdGenArrCreate(KD_SZ_U8, KD_BASE_INT_C(len), (allocator))
#define kdArrCreateI16(len, allocator)                                      kdGenArrCreate(KD_SZ_I16, KD_BASE_INT_C(len), (allocator))
#define kdArrCreateU16(len, allocator)                                      kdGenArrCreate(KD_SZ_U16, KD_BASE_INT_C(len), (allocator))
#define kdArrCreateI32(len, allocator)                                      kdGenArrCreate(KD_SZ_I32, KD_BASE_INT_C(len), (allocator))
#define kdArrCreateU32(len, allocator)                                      kdGenArrCreate(KD_SZ_U32, KD_BASE_INT_C(len), (allocator))
#define kdArrCreateI64(len, allocator)                                      kdGenArrCreate(KD_SZ_I64, KD_BASE_INT_C(len), (allocator))
#define kdArrCreateU64(len, allocator)                                      kdGenArrCreate(KD_SZ_U64, KD_BASE_INT_C(len), (allocator))
#define kdArrCreateImin(len, allocator)                                     kdGenArrCreate(KD_SZ_IMIN, KD_BASE_INT_C(len), (allocator))
#define kdArrCreateUmin(len, allocator)                                     kdGenArrCreate(KD_SZ_UMIN, KD_BASE_INT_C(len), (allocator))
#define kdArrCreateImax(len, allocator)                                     kdGenArrCreate(KD_SZ_IMAX, KD_BASE_INT_C(len), (allocator))
#define kdArrCreateUmax(len, allocator)                                     kdGenArrCreate(KD_SZ_UMAX, KD_BASE_INT_C(len), (allocator))
#define kdArrCreateUsize(len, allocator)                                    kdGenArrCreate(KD_SZ_USIZE, KD_BASE_INT_C(len), (allocator))
#define kdArrCreateChr(len, allocator)                                      kdGenArrCreate(KD_SZ_CHR, KD_BASE_INT_C(len), (allocator))
#define kdArrCreateBool(len, allocator)                                     kdGenArrCreate(KD_SZ_BOOL, KD_BASE_INT_C(len), (allocator))
#define kdArrCreatePtr(len, allocator)                                      kdGenArrCreate(KD_SZ_PTR, KD_BASE_INT_C(len), (allocator))
#define kdArrCreateN(n, len, allocator)                                     kdGenArrCreate(KD_I32_C(n), KD_BASE_INT_C(len), (allocator))


#define kdArrCreateInitByte(len, val, allocator)                            kdArrCreateInit(KD_BASE_INT_C(len), KD_BYTE_C(val), (allocator))
#define kdArrCreateInitI8(len, val, allocator)                              kdArrCreateInit(KD_BASE_INT_C(len), KD_BYTE_C(val), (allocator))
#define kdArrCreateInitU8(len, val, allocator)                              kdArrCreateInit(KD_BASE_INT_C(len), KD_BYTE_C(val), (allocator))
#define kdArrCreateInitI16(len, val, allocator)                             kdArrCreateInitU16(KD_BASE_INT_C(len), KD_U16_C(val), (allocator))
#define kdArrCreateInitI32(len, val, allocator)                             kdArrCreateInitU32(KD_BASE_INT_C(len), KD_U32_C(val), (allocator))
#define kdArrCreateInitI64(len, val, allocator)                             kdArrCreateInitU64(KD_BASE_INT_C(len), KD_U64_C(val), (allocator))
#define kdArrCreateInitImin(len, val, allocator)                            kdArrCreateInit(KD_BASE_INT_C(len), KD_BYTE_C(val), (allocator))
#define kdArrCreateInitUmin(len, val, allocator)                            kdArrCreateInit(KD_BASE_INT_C(len), KD_BYTE_C(val), (allocator))
#define kdArrCreateInitImax(len, val, allocator)                            kdArrCreateInitU64(KD_BASE_INT_C(len), KD_BASE_UINT_C(val), (allocator))
#define kdArrCreateInitUmax(len, val, allocator)                            kdArrCreateInitU64(KD_BASE_INT_C(len), KD_BASE_UINT_C(val), (allocator))
#define kdArrCreateInitUsize(len, val, allocator)                           kdArrCreateInitU64(KD_BASE_INT_C(len), KD_BASE_UINT_C(val), (allocator))
#define kdArrCreateInitChr(len, val, allocator)                             kdArrCreateInitU32(KD_BASE_INT_C(len), KD_U32_C(val), (allocator))
#define kdArrCreateInitBool(len, val, allocator)                            kdArrCreateInitU32(KD_BASE_INT_C(len), KD_U32_C(val), (allocator))
#define kdArrCreateInitPtr(len, val, allocator)                             kdArrCreateInitU64(KD_BASE_INT_C(len), KD_BASE_UINT_C(val), (allocator))
#define kdArrCreateInitN(n, len, val_ptr, allocator)                        kdGenArrCreateInit(KD_I32_C(n), KD_BASE_INT_C(len), KD_PTR_C(val_ptr), (allocator))


#define kdArrCreateFrom(len, src, src_len, allocator)                       kdGenArrCreateFrom(KD_SZ_BYTE, KD_BASE_INT_C(len), KD_PTR_C(src), KD_BASE_INT_C(src_len), (allocator))
#define kdArrCreateFromByte(len, src, src_len, allocator)                   kdGenArrCreateFrom(KD_SZ_BYTE, KD_BASE_INT_C(len), KD_PTR_C(src), KD_BASE_INT_C(src_len), (allocator))
#define kdArrCreateFromI8(len, src, src_len, allocator)                     kdGenArrCreateFrom(KD_SZ_I8, KD_BASE_INT_C(len), KD_PTR_C(src), KD_BASE_INT_C(src_len), (allocator))
#define kdArrCreateFromU8(len, src, src_len, allocator)                     kdGenArrCreateFrom(KD_SZ_U8, KD_BASE_INT_C(len), KD_PTR_C(src), KD_BASE_INT_C(src_len), (allocator))
#define kdArrCreateFromI16(len, src, src_len, allocator)                    kdGenArrCreateFrom(KD_SZ_I16, KD_BASE_INT_C(len), KD_PTR_C(src), KD_BASE_INT_C(src_len), (allocator))
#define kdArrCreateFromU16(len, src, src_len, allocator)                    kdGenArrCreateFrom(KD_SZ_U16, KD_BASE_INT_C(len), KD_PTR_C(src), KD_BASE_INT_C(src_len), (allocator))
#define kdArrCreateFromI32(len, src, src_len, allocator)                    kdGenArrCreateFrom(KD_SZ_I32, KD_BASE_INT_C(len), KD_PTR_C(src), KD_BASE_INT_C(src_len), (allocator))
#define kdArrCreateFromU32(len, src, src_len, allocator)                    kdGenArrCreateFrom(KD_SZ_U32, KD_BASE_INT_C(len), KD_PTR_C(src), KD_BASE_INT_C(src_len), (allocator))
#define kdArrCreateFromI64(len, src, src_len, allocator)                    kdGenArrCreateFrom(KD_SZ_I64, KD_BASE_INT_C(len), KD_PTR_C(src), KD_BASE_INT_C(src_len), (allocator))
#define kdArrCreateFromU64(len, src, src_len, allocator)                    kdGenArrCreateFrom(KD_SZ_U64, KD_BASE_INT_C(len), KD_PTR_C(src), KD_BASE_INT_C(src_len), (allocator))
#define kdArrCreateFromImin(len, src, src_len, allocator)                   kdGenArrCreateFrom(KD_SZ_IMIN, KD_BASE_INT_C(len), KD_PTR_C(src), KD_BASE_INT_C(src_len), (allocator))
#define kdArrCreateFromUmin(len, src, src_len, allocator)                   kdGenArrCreateFrom(KD_SZ_UMIN, KD_BASE_INT_C(len), KD_PTR_C(src), KD_BASE_INT_C(src_len), (allocator))
#define kdArrCreateFromImax(len, src, src_len, allocator)                   kdGenArrCreateFrom(KD_SZ_IMAX, KD_BASE_INT_C(len), KD_PTR_C(src), KD_BASE_INT_C(src_len), (allocator))
#define kdArrCreateFromUmax(len, src, src_len, allocator)                   kdGenArrCreateFrom(KD_SZ_UMAX, KD_BASE_INT_C(len), KD_PTR_C(src), KD_BASE_INT_C(src_len), (allocator))
#define kdArrCreateFromUsize(len, src, src_len, allocator)                  kdGenArrCreateFrom(KD_SZ_USIZE, KD_BASE_INT_C(len), KD_PTR_C(src), KD_BASE_INT_C(src_len), (allocator))
#define kdArrCreateFromChr(len, src, src_len, allocator)                    kdGenArrCreateFrom(KD_SZ_CHR, KD_BASE_INT_C(len), KD_PTR_C(src), KD_BASE_INT_C(src_len), (allocator))
#define kdArrCreateFromBool(len, src, src_len, allocator)                   kdGenArrCreateFrom(KD_SZ_BOOL, KD_BASE_INT_C(len), KD_PTR_C(src), KD_BASE_INT_C(src_len), (allocator))
#define kdArrCreateFromPtr(len, src, src_len, allocator)                    kdGenArrCreateFrom(KD_SZ_PTR, KD_BASE_INT_C(len), KD_PTR_C(src), KD_BASE_INT_C(src_len), (allocator))
#define kdArrCreateFromN(n, len, src, src_len, allocator)                   kdGenArrCreateFrom(KD_I32_C(n), KD_BASE_INT_C(len), KD_PTR_C(src), KD_BASE_INT_C(src_len), (allocator))


#define kdArrClone(arr, allocator)                                          kdGenArrClone(KD_PTR_C(arr), (allocator))
#define kdArrCloneRange(arr, from, to, allocator)                           kdGenArrCloneRange(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), (allocator))
#define kdArrDestroy(arr, deallocator)                                      kdGenArrDestroy(KD_PTR_C(arr), (deallocator))
#define kdArrGetElemSize(arr)                                               kdGenArrGetElemSize(KD_PTR_C(arr))
#define kdArrGetMemSize(arr)                                                kdGenArrGetMemSize(KD_PTR_C(arr))
#define kdArrGetLen(arr)                                                    kdGenArrGetLen(KD_PTR_C(arr))
#define kdArrIsLE(arr)                                                      kdGenArrIsLE(KD_PTR_C(arr))
#define kdArrIsBE(arr)                                                      kdGenArrIsBE(KD_PTR_C(arr))
#define kdArrGetEnd(arr)                                                    kdGenArrGetEnd(KD_PTR_C(arr))


#define kdArrFillByte(arr, val)                                             kdArrFill(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFillI8(arr, val)                                               kdArrFill(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFillU8(arr, val)                                               kdArrFill(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFillI16(arr, val)                                              kdArrFillU16(KD_PTR_C(arr), KD_U16_C(val))
#define kdArrFillI32(arr, val)                                              kdArrFillU32(KD_PTR_C(arr), KD_U32_C(val))
#define kdArrFillI64(arr, val)                                              kdArrFillU64(KD_PTR_C(arr), KD_U64_C(val))
#define kdArrFillImin(arr, val)                                             kdArrFill(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFillUmin(arr, val)                                             kdArrFill(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFillImax(arr, val)                                             kdArrFillU64(KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFillUmax(arr, val)                                             kdArrFillU64(KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFillUsize(arr, val)                                            kdArrFillU64(KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFillChr(arr, val)                                              kdArrFillU32(KD_PTR_C(arr), KD_U32_C(val))
#define kdArrFillBool(arr, val)                                             kdArrFillU32(KD_PTR_C(arr), KD_U32_C(val))
#define kdArrFillPtr(arr, val)                                              kdArrFillU64(KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFillN(arr, val_ptr)                                            kdGenArrFill(KD_PTR_C(arr), KD_PTR_C(val_ptr))


#define kdArrFillRangeByte(arr, from, to, val)                              kdArrFillRange(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_BYTE_C(val))
#define kdArrFillRangeI8(arr, from, to, val)                                kdArrFillRange(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_BYTE_C(val))
#define kdArrFillRangeU8(arr, from, to, val)                                kdArrFillRange(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_BYTE_C(val))
#define kdArrFillRangeI16(arr, from, to, val)                               kdArrFillRangeU16(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_U16_C(val))
#define kdArrFillRangeI32(arr, from, to, val)                               kdArrFillRangeU32(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_U32_C(val))
#define kdArrFillRangeI64(arr, from, to, val)                               kdArrFillRangeU64(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_U64_C(val))
#define kdArrFillRangeImin(arr, from, to, val)                              kdArrFillRange(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_BYTE_C(val))
#define kdArrFillRangeUmin(arr, from, to, val)                              kdArrFillRange(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_BYTE_C(val))
#define kdArrFillRangeImax(arr, from, to, val)                              kdArrFillRangeU64(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_BASE_UINT_C(val))
#define kdArrFillRangeUmax(arr, from, to, val)                              kdArrFillRangeU64(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_BASE_UINT_C(val))
#define kdArrFillRangeUsize(arr, from, to, val)                             kdArrFillRangeU64(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_BASE_UINT_C(val))
#define kdArrFillRangeChr(arr, from, to, val)                               kdArrFillRangeU32(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_U32_C(val))
#define kdArrFillRangeBool(arr, from, to, val)                              kdArrFillRangeU32(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_U32_C(val))
#define kdArrFillRangePtr(arr, from, to, val)                               kdArrFillRangeU64(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_BASE_UINT_C(val))
#define kdArrFillRangeN(arr, from, to, val_ptr)                             kdGenArrFillRange(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_PTR_C(val_ptr))


#define kdArrSetByte(arr, idx, val)                                         kdArrSet(KD_PTR_C(arr), KD_BASE_INT_C(idx), KD_BYTE_C(val))
#define kdArrSetI8(arr, idx, val)                                           kdArrSet(KD_PTR_C(arr), KD_BASE_INT_C(idx), KD_BYTE_C(val))
#define kdArrSetU8(arr, idx, val)                                           kdArrSet(KD_PTR_C(arr), KD_BASE_INT_C(idx), KD_BYTE_C(val))
#define kdArrSetI16(arr, idx, val)                                          kdArrSetU16(KD_PTR_C(arr), KD_BASE_INT_C(idx), KD_U16_C(val))
#define kdArrSetI32(arr, idx, val)                                          kdArrSetU32(KD_PTR_C(arr), KD_BASE_INT_C(idx), KD_U32_C(val))
#define kdArrSetI64(arr, idx, val)                                          kdArrSetU64(KD_PTR_C(arr), KD_BASE_INT_C(idx), KD_U64_C(val))
#define kdArrSetImin(arr, idx, val)                                         kdArrSet(KD_PTR_C(arr), KD_BASE_INT_C(idx), KD_BYTE_C(val))
#define kdArrSetUmin(arr, idx, val)                                         kdArrSet(KD_PTR_C(arr), KD_BASE_INT_C(idx), KD_BYTE_C(val))
#define kdArrSetImax(arr, idx, val)                                         kdArrSetU64(KD_PTR_C(arr), KD_BASE_INT_C(idx), KD_BASE_INT_C(val))
#define kdArrSetUmax(arr, idx, val)                                         kdArrSetU64(KD_PTR_C(arr), KD_BASE_INT_C(idx), KD_BASE_INT_C(val))
#define kdArrSetUsize(arr, idx, val)                                        kdArrSetU64(KD_PTR_C(arr), KD_BASE_INT_C(idx), KD_BASE_INT_C(val))
#define kdArrSetChr(arr, idx, val)                                          kdArrSetU32(KD_PTR_C(arr), KD_BASE_INT_C(idx), KD_U32_C(val))
#define kdArrSetBool(arr, idx, val)                                         kdArrSetU32(KD_PTR_C(arr), KD_BASE_INT_C(idx), KD_U32_C(val))
#define kdArrSetPtr(arr, idx, val)                                          kdArrSetU64(KD_PTR_C(arr), KD_BASE_INT_C(idx), KD_BASE_INT_C(val))
#define kdArrSetN(arr, idx, val_ptr)                                        kdGenArrSet(KD_PTR_C(arr), KD_BASE_INT_C(idx), KD_PTR_C(val_ptr))


#define kdArrGetByte(arr, idx)                                              (KD_BYTE_C(kdArrGet(KD_PTR_C(arr), KD_BASE_INT_C(idx))))
#define kdArrGetI8(arr, idx)                                                (KD_I8_C(kdArrGet(KD_PTR_C(arr), KD_BASE_INT_C(idx))))
#define kdArrGetU8(arr, idx)                                                (KD_U8_C(kdArrGet(KD_PTR_C(arr), KD_BASE_INT_C(idx))))
#define kdArrGetI16(arr, idx)                                               (KD_I16_C(kdArrGetU16(KD_PTR_C(arr), KD_BASE_INT_C(idx))))
#define kdArrGetI32(arr, idx)                                               (KD_I32_C(kdArrGetU32(KD_PTR_C(arr), KD_BASE_INT_C(idx))))
#define kdArrGetI64(arr, idx)                                               (KD_BASE_INT_C(kdArrGetU64(KD_PTR_C(arr), KD_BASE_INT_C(idx))))
#define kdArrGetImin(arr, idx)                                              (KD_IMIN_C(kdArrGet(KD_PTR_C(arr), KD_BASE_INT_C(idx))))
#define kdArrGetUmin(arr, idx)                                              (KD_UMIN_C(kdArrGet(KD_PTR_C(arr), KD_BASE_INT_C(idx))))
#define kdArrGetImax(arr, idx)                                              (KD_IMAX_C(kdArrGetU64(KD_PTR_C(arr), KD_BASE_INT_C(idx))))
#define kdArrGetUmax(arr, idx)                                              (KD_UMAX_C(kdArrGetU64(KD_PTR_C(arr), KD_BASE_INT_C(idx))))
#define kdArrGetUsize(arr, idx)                                             (KD_USIZE_C(kdArrGetU64(KD_PTR_C(arr), KD_BASE_INT_C(idx))))
#define kdArrGetChr(arr, idx)                                               (KD_CHR_C(kdArrGetU32(KD_PTR_C(arr), KD_BASE_INT_C(idx))))
#define kdArrGetBool(arr, idx)                                              (KD_BOOL_C(kdArrGetU32(KD_PTR_C(arr), KD_BASE_INT_C(idx))))
#define kdArrGetPtr(arr, idx)                                               (KD_PTR_C(kdArrGetU64(KD_PTR_C(arr), KD_BASE_INT_C(idx))))
#define kdArrGetN(arr, idx)                                                 kdGenArrGet(KD_PTR_C(arr), KD_BASE_INT_C(idx))


#define kdArrSwap(arr, idx1, idx2)                                          kdGenArrSwap(KD_PTR_C(arr), KD_BASE_INT_C(idx1), KD_BASE_INT_C(idx2))
#define kdArrEquals(arr1, arr2)                                             kdGenArrEquals(KD_PTR_C(arr1), KD_PTR_C(arr2))


#define kdArrGetCountByte(arr, val)                                         kdArrGetCount(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrGetCountI8(arr, val)                                           kdArrGetCount(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrGetCountU8(arr, val)                                           kdArrGetCount(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrGetCountI16(arr, val)                                          kdArrGetCountU16(KD_PTR_C(arr), KD_U16_C(val))
#define kdArrGetCountI32(arr, val)                                          kdArrGetCountU32(KD_PTR_C(arr), KD_U32_C(val))
#define kdArrGetCountI64(arr, val)                                          kdArrGetCountU64(KD_PTR_C(arr), KD_U64_C(val))
#define kdArrGetCountImin(arr, val)                                         kdArrGetCount(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrGetCountUmin(arr, val)                                         kdArrGetCount(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrGetCountImax(arr, val)                                         kdArrGetCountU64(KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrGetCountUmax(arr, val)                                         kdArrGetCountU64(KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrGetCountUsize(arr, val)                                        kdArrGetCountU64(KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrGetCountChr(arr, val)                                          kdArrGetCountU32(KD_PTR_C(arr), KD_U32_C(val))
#define kdArrGetCountBool(arr, val)                                         kdArrGetCountU32(KD_PTR_C(arr), KD_U32_C(val))
#define kdArrGetCountPtr(arr, val)                                          kdArrGetCountU64(KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrGetCountN(arr, val_ptr)                                        kdGenArrGetCount(KD_PTR_C(arr), KD_PTR_C(val_ptr))


#define kdArrGetCountRangeByte(arr, from, to, val)                          kdArrGetCountRange(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_BYTE_C(val))
#define kdArrGetCountRangeI8(arr, from, to, val)                            kdArrGetCountRange(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_BYTE_C(val))
#define kdArrGetCountRangeU8(arr, from, to, val)                            kdArrGetCountRange(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_BYTE_C(val))

#define kdArrGetCountRangeI16(arr, from, to, val)                           kdArrGetCountRangeU16(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_U16_C(val))
#define kdArrGetCountRangeI32(arr, from, to, val)                           kdArrGetCountRangeU32(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_U32_C(val))
#define kdArrGetCountRangeI64(arr, from, to, val)                           kdArrGetCountRangeU64(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_U64_C(val))

#define kdArrGetCountRangeImin(arr, from, to, val)                          kdArrGetCountRange(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_BYTE_C(val))
#define kdArrGetCountRangeUmin(arr, from, to, val)                          kdArrGetCountRange(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_BYTE_C(val))

#define kdArrGetCountRangeImax(arr, from, to, val)                          kdArrGetCountRangeU64(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_BASE_UINT_C(val))
#define kdArrGetCountRangeUmax(arr, from, to, val)                          kdArrGetCountRangeU64(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_BASE_UINT_C(val))
#define kdArrGetCountRangeUsize(arr, from, to, val)                         kdArrGetCountRangeU64(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_BASE_UINT_C(val))

#define kdArrGetCountRangeChr(arr, from, to, val)                           kdArrGetCountRangeU32(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_U32_C(val))
#define kdArrGetCountRangeBool(arr, from, to, val)                          kdArrGetCountRangeU32(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_U32_C(val))

#define kdArrGetCountRangePtr(arr, from, to, val)                           kdArrGetCountRangeU64(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_BASE_UINT_C(val))

#define kdArrGetCountRangeN(arr, from, to, val_ptr)                         kdGenArrGetCountRange(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to), KD_PTR_C(val_ptr))


#define kdArrReverse(arr)                                                   kdGenArrReverse(KD_PTR_C(arr))
#define kdArrGetReversed(dst_arr, src_arr)                                  kdGenArrGetReversed(KD_PTR_C(dst_arr), KD_PTR_C(src_arr))
#define kdArrGetReversedFrom(dst_arr, src, len)                             kdGenArrGetReversedFrom(KD_PTR_C(dst_arr), KD_PTR_C(src), KD_BASE_INT_C(len))
#define kdArrGetReversedTo(dst, len, src_arr)                               kdGenArrGetReversedTo(KD_PTR_C(dst), KD_BASE_INT_C(len), KD_PTR_C(src_arr))
#define kdArrReverseRange(arr, from, to)                                    kdGenArrReverseRange(KD_PTR_C(arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to))
#define kdArrGetReversedRange(dst_arr, dst_from, src_arr, src_from, src_to) kdGenArrGetReversedRange(KD_PTR_C(dst_arr), KD_BASE_INT_C(dst_from), KD_PTR_C(src_arr), KD_BASE_INT_C(src_from), KD_BASE_INT_C(src_to))
#define kdArrGetReversedRangeFrom(dst_arr, dst_from, src, src_from, src_to) kdGenArrGetReversedRangeFrom(KD_PTR_C(dst_arr), KD_BASE_INT_C(dst_from), KD_PTR_C(src), KD_BASE_INT_C(src_from), KD_BASE_INT_C(src_to))
#define kdArrGetReversedRangeTo(dst, len, src_arr, from, to)                kdGenArrGetReversedRangeTo(KD_PTR_C(dst), KD_BASE_INT_C(len), KD_PTR_C(src_arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to))


#define kdArrCpy(dst_arr, src_arr)                                          kdGenArrCpy(KD_PTR_C(dst_arr), KD_PTR_C(src_arr))
#define kdArrCpyFrom(dst_arr, src, len)                                     kdGenArrCpyFrom(KD_PTR_C(dst_arr), KD_PTR_C(src), KD_BASE_INT_C(len))
#define kdArrCpyTo(dst, len, src_arr)                                       kdGenArrCpyTo(KD_PTR_C(dst), KD_BASE_INT_C(len), KD_PTR_C(src_arr))
#define kdArrCpyRange(dst_arr, dst_from, src_arr, src_from, src_to)         kdGenArrCpyRange(KD_PTR_C(dst_arr), KD_BASE_INT_C(dst_from), KD_PTR_C(src_arr), KD_BASE_INT_C(src_from), KD_BASE_INT_C(src_to))
#define kdArrCpyRangeFrom(dst_arr, dst_from, src, src_from, src_to)         kdGenArrCpyRangeFrom(KD_PTR_C(dst_arr), KD_BASE_INT_C(dst_from), KD_PTR_C(src), KD_BASE_INT_C(src_from), KD_BASE_INT_C(src_to))
#define kdArrCpyRangeTo(dst, len, src_arr, from, to)                        kdGenArrCpyRangeTo(KD_PTR_C(dst), KD_BASE_INT_C(len), KD_PTR_C(src_arr), KD_BASE_INT_C(from), KD_BASE_INT_C(to))


#define kdArrFindByte(arr, val)                                             kdArrFind(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindI8(arr, val)                                               kdArrFind(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindU8(arr, val)                                               kdArrFind(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindI16(arr, val)                                              kdArrFindU16(KD_PTR_C(arr), KD_U16_C(val))
#define kdArrFindI32(arr, val)                                              kdArrFindU32(KD_PTR_C(arr), KD_U32_C(val))
#define kdArrFindI64(arr, val)                                              kdArrFindU64(KD_PTR_C(arr), KD_U64_C(val))
#define kdArrFindImin(arr, val)                                             kdArrFind(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindUmin(arr, val)                                             kdArrFind(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindImax(arr, val)                                             kdArrFindU64(KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindUmax(arr, val)                                             kdArrFindU64(KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindUsize(arr, val)                                            kdArrFindU64(KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindChr(arr, val)                                              kdArrFindU32(KD_PTR_C(arr), KD_U32_C(val))
#define kdArrFindBool(arr, val)                                             kdArrFindU32(KD_PTR_C(arr), KD_U32_C(val))
#define kdArrFindPtr(arr, val)                                              kdArrFindU64(KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindN(arr, val_ptr)                                            kdGenArrFind(KD_PTR_C(arr), KD_PTR_C(val_ptr))


#define kdArrFindIndexByte(arr, val)                                        kdArrFindIndex(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindIndexI8(arr, val)                                          kdArrFindIndex(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindIndexU8(arr, val)                                          kdArrFindIndex(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindIndexI16(arr, val)                                         kdArrFindIndexU16(KD_PTR_C(arr), KD_U16_C(val))
#define kdArrFindIndexI32(arr, val)                                         kdArrFindIndexU32(KD_PTR_C(arr), KD_U32_C(val))
#define kdArrFindIndexI64(arr, val)                                         kdArrFindIndexU64(KD_PTR_C(arr), KD_U64_C(val))
#define kdArrFindIndexImin(arr, val)                                        kdArrFindIndex(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindIndexUmin(arr, val)                                        kdArrFindIndex(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindIndexImax(arr, val)                                        kdArrFindIndexU64(KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindIndexUmax(arr, val)                                        kdArrFindIndexU64(KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindIndexUsize(arr, val)                                       kdArrFindIndexU64(KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindIndexChr(arr, val)                                         kdArrFindIndexU32(KD_PTR_C(arr), KD_U32_C(val))
#define kdArrFindIndexBool(arr, val)                                        kdArrFindIndexU32(KD_PTR_C(arr), KD_U32_C(val))
#define kdArrFindIndexPtr(arr, val)                                         kdArrFindIndexU64(KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindIndexN(arr, val_ptr)                                       kdGenArrFindIndex(KD_PTR_C(arr), KD_PTR_C(val_ptr))


#define kdArrFindLastByte(arr, val)                                         kdArrFindLast(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindLastI8(arr, val)                                           kdArrFindLast(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindLastU8(arr, val)                                           kdArrFindLast(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindLastI16(arr, val)                                          kdArrFindLastU16(KD_PTR_C(arr), KD_U16_C(val))
#define kdArrFindLastI32(arr, val)                                          kdArrFindLastU32(KD_PTR_C(arr), KD_U32_C(val))
#define kdArrFindLastI64(arr, val)                                          kdArrFindLastU64(KD_PTR_C(arr), KD_U64_C(val))
#define kdArrFindLastImin(arr, val)                                         kdArrFindLast(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindLastUmin(arr, val)                                         kdArrFindLast(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindLastImax(arr, val)                                         kdArrFindLastU64(KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindLastUmax(arr, val)                                         kdArrFindLastU64(KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindLastUsize(arr, val)                                        kdArrFindLastU64(KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindLastChr(arr, val)                                          kdArrFindLastU32(KD_PTR_C(arr), KD_U32_C(val))
#define kdArrFindLastBool(arr, val)                                         kdArrFindLastU32(KD_PTR_C(arr), KD_U32_C(val))
#define kdArrFindLastPtr(arr, val)                                          kdArrFindLastU64(KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindLastN(arr, val_ptr)                                        kdGenArrFindLast(KD_PTR_C(arr), KD_PTR_C(val_ptr))


#define kdArrFindLastIndexByte(arr, val)                                    kdArrFindLastIndex(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindLastIndexI8(arr, val)                                      kdArrFindLastIndex(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindLastIndexU8(arr, val)                                      kdArrFindLastIndex(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindLastIndexI16(arr, val)                                     kdArrFindLastIndexU16(KD_PTR_C(arr), KD_U16_C(val))
#define kdArrFindLastIndexI32(arr, val)                                     kdArrFindLastIndexU32(KD_PTR_C(arr), KD_U32_C(val))
#define kdArrFindLastIndexI64(arr, val)                                     kdArrFindLastIndexU64(KD_PTR_C(arr), KD_U64_C(val))
#define kdArrFindLastIndexImin(arr, val)                                    kdArrFindLastIndex(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindLastIndexUmin(arr, val)                                    kdArrFindLastIndex(KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindLastIndexImax(arr, val)                                    kdArrFindLastIndexU64(KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindLastIndexUmax(arr, val)                                    kdArrFindLastIndexU64(KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindLastIndexUsize(arr, val)                                   kdArrFindLastIndexU64(KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindLastIndexChr(arr, val)                                     kdArrFindLastIndexU32(KD_PTR_C(arr), KD_U32_C(val))
#define kdArrFindLastIndexBool(arr, val)                                    kdArrFindLastIndexU32(KD_PTR_C(arr), KD_U32_C(val))
#define kdArrFindLastIndexPtr(arr, val)                                     kdArrFindLastIndexU64(KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindLastIndexN(arr, val_ptr)                                   kdGenArrFindLastIndex(KD_PTR_C(arr), KD_PTR_C(val_ptr))


#define kdArrFindAllByte(dst_arr, src_arr, val)                             kdArrFindAll(KD_PTR_C(dst_arr), KD_PTR_C(src_arr), KD_BYTE_C(val))
#define kdArrFindAllI8(dst_arr, src_arr, val)                               kdArrFindAll(KD_PTR_C(dst_arr), KD_PTR_C(src_arr), KD_BYTE_C(val))
#define kdArrFindAllU8(dst_arr, src_arr, val)                               kdArrFindAll(KD_PTR_C(dst_arr), KD_PTR_C(src_arr), KD_BYTE_C(val))
#define kdArrFindAllI16(dst_arr, src_arr, val)                              kdArrFindAllU16(KD_PTR_C(dst_arr), KD_PTR_C(src_arr), KD_U16_C(val))
#define kdArrFindAllI32(dst_arr, src_arr, val)                              kdArrFindAllU32(KD_PTR_C(dst_arr), KD_PTR_C(src_arr), KD_U32_C(val))
#define kdArrFindAllI64(dst_arr, src_arr, val)                              kdArrFindAllU64(KD_PTR_C(dst_arr), KD_PTR_C(src_arr), KD_U64_C(val))
#define kdArrFindAllImin(dst_arr, src_arr, val)                             kdArrFindAll(KD_PTR_C(dst_arr), KD_PTR_C(src_arr), KD_BYTE_C(val))
#define kdArrFindAllUmin(dst_arr, src_arr, val)                             kdArrFindAll(KD_PTR_C(dst_arr), KD_PTR_C(src_arr), KD_BYTE_C(val))
#define kdArrFindAllImax(dst_arr, src_arr, val)                             kdArrFindAllU64(KD_PTR_C(dst_arr), KD_PTR_C(src_arr), KD_BASE_UINT_C(val))
#define kdArrFindAllUmax(dst_arr, src_arr, val)                             kdArrFindAllU64(KD_PTR_C(dst_arr), KD_PTR_C(src_arr), KD_BASE_UINT_C(val))
#define kdArrFindAllUsize(dst_arr, src_arr, val)                            kdArrFindAllU64(KD_PTR_C(dst_arr), KD_PTR_C(src_arr), KD_BASE_UINT_C(val))
#define kdArrFindAllChr(dst_arr, src_arr, val)                              kdArrFindAllU32(KD_PTR_C(dst_arr), KD_PTR_C(src_arr), KD_U32_C(val))
#define kdArrFindAllBool(dst_arr, src_arr, val)                             kdArrFindAllU32(KD_PTR_C(dst_arr), KD_PTR_C(src_arr), KD_U32_C(val))
#define kdArrFindAllPtr(dst_arr, src_arr, val)                              kdArrFindAllU64(KD_PTR_C(dst_arr), KD_PTR_C(src_arr), KD_BASE_UINT_C(val))
#define kdArrFindAllN(dst_arr, src_arr, val_ptr)                            kdGenArrFindAll(KD_PTR_C(dst_arr), KD_PTR_C(src_arr), KD_BASE_UINT_C(val_ptr))


#define kdArrFindAllToByte(dst, len, arr, val)                              kdArrFindAllTo(KD_PTR_C(dst), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindAllToI8(dst, len, arr, val)                                kdArrFindAllTo(KD_PTR_C(dst), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindAllToU8(dst, len, arr, val)                                kdArrFindAllTo(KD_PTR_C(dst), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindAllToI16(dst, len, arr, val)                               kdArrFindAllToU16(KD_PTR_C(dst), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_U16_C(val))
#define kdArrFindAllToI32(dst, len, arr, val)                               kdArrFindAllToU32(KD_PTR_C(dst), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_U32_C(val))
#define kdArrFindAllToI64(dst, len, arr, val)                               kdArrFindAllToU64(KD_PTR_C(dst), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_U64_C(val))
#define kdArrFindAllToImin(dst, len, arr, val)                              kdArrFindAllTo(KD_PTR_C(dst), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindAllToUmin(dst, len, arr, val)                              kdArrFindAllTo(KD_PTR_C(dst), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindAllToImax(dst, len, arr, val)                              kdArrFindAllToU64(KD_PTR_C(dst), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindAllToUmax(dst, len, arr, val)                              kdArrFindAllToU64(KD_PTR_C(dst), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindAllToUsize(dst, len, arr, val)                             kdArrFindAllToU64(KD_PTR_C(dst), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindAllToChr(dst, len, arr, val)                               kdArrFindAllToU32(KD_PTR_C(dst), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_U32_C(val))
#define kdArrFindAllToBool(dst, len, arr, val)                              kdArrFindAllToU32(KD_PTR_C(dst), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_U32_C(val))
#define kdArrFindAllToPtr(dst, len, arr, val)                               kdArrFindAllToU64(KD_PTR_C(dst), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindAllToN(dst, len, arr, val_ptr)                             kdGenArrFindAllTo(KD_PTR_C(dst), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_BASE_UINT_C(val_ptr))


#define kdArrFindAllIndicesByte(idx_arr, arr, val)                          kdArrFindAllIndices(KD_PTR_C(idx_arr), KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindAllIndicesI8(idx_arr, arr, val)                            kdArrFindAllIndices(KD_PTR_C(idx_arr), KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindAllIndicesU8(idx_arr, arr, val)                            kdArrFindAllIndices(KD_PTR_C(idx_arr), KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindAllIndicesI16(idx_arr, arr, val)                           kdArrFindAllIndicesU16(KD_PTR_C(idx_arr), KD_PTR_C(arr), KD_U16_C(val))
#define kdArrFindAllIndicesI32(idx_arr, arr, val)                           kdArrFindAllIndicesU32(KD_PTR_C(idx_arr), KD_PTR_C(arr), KD_U32_C(val))
#define kdArrFindAllIndicesI64(idx_arr, arr, val)                           kdArrFindAllIndicesU64(KD_PTR_C(idx_arr), KD_PTR_C(arr), KD_U64_C(val))
#define kdArrFindAllIndicesImin(idx_arr, arr, val)                          kdArrFindAllIndices(KD_PTR_C(idx_arr), KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindAllIndicesUmin(idx_arr, arr, val)                          kdArrFindAllIndices(KD_PTR_C(idx_arr), KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindAllIndicesImax(idx_arr, arr, val)                          kdArrFindAllIndicesU64(KD_PTR_C(idx_arr), KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindAllIndicesUmax(idx_arr, arr, val)                          kdArrFindAllIndicesU64(KD_PTR_C(idx_arr), KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindAllIndicesUsize(idx_arr, arr, val)                         kdArrFindAllIndicesU64(KD_PTR_C(idx_arr), KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindAllIndicesChr(idx_arr, arr, val)                           kdArrFindAllIndicesU32(KD_PTR_C(idx_arr), KD_PTR_C(arr), KD_U32_C(val))
#define kdArrFindAllIndicesBool(idx_arr, arr, val)                          kdArrFindAllIndicesU32(KD_PTR_C(idx_arr), KD_PTR_C(arr), KD_U32_C(val))
#define kdArrFindAllIndicesPtr(idx_arr, arr, val)                           kdArrFindAllIndicesU64(KD_PTR_C(idx_arr), KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindAllIndicesN(idx_arr, arr, val_ptr)                         kdGenArrFindAllIndices(KD_PTR_C(idx_arr), KD_PTR_C(arr), KD_BASE_UINT_C(val_ptr))


#define kdArrFindAllIndicesToByte(idxs, len, arr, val)                      kdArrFindAllIndicesTo(KD_PTR_C(idxs), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindAllIndicesToI8(idxs, len, arr, val)                        kdArrFindAllIndicesTo(KD_PTR_C(idxs), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindAllIndicesToU8(idxs, len, arr, val)                        kdArrFindAllIndicesTo(KD_PTR_C(idxs), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindAllIndicesToI16(idxs, len, arr, val)                       kdArrFindAllIndicesToU16(KD_PTR_C(idxs), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_U16_C(val))
#define kdArrFindAllIndicesToI32(idxs, len, arr, val)                       kdArrFindAllIndicesToU32(KD_PTR_C(idxs), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_U32_C(val))
#define kdArrFindAllIndicesToI64(idxs, len, arr, val)                       kdArrFindAllIndicesToU64(KD_PTR_C(idxs), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_U64_C(val))
#define kdArrFindAllIndicesToImin(idxs, len, arr, val)                      kdArrFindAllIndicesTo(KD_PTR_C(idxs), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindAllIndicesToUmin(idxs, len, arr, val)                      kdArrFindAllIndicesTo(KD_PTR_C(idxs), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_BYTE_C(val))
#define kdArrFindAllIndicesToImax(idxs, len, arr, val)                      kdArrFindAllIndicesToU64(KD_PTR_C(idxs), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindAllIndicesToUmax(idxs, len, arr, val)                      kdArrFindAllIndicesToU64(KD_PTR_C(idxs), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindAllIndicesToUsize(idxs, len, arr, val)                     kdArrFindAllIndicesToU64(KD_PTR_C(idxs), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindAllIndicesToChr(idxs, len, arr, val)                       kdArrFindAllIndicesToU32(KD_PTR_C(idxs), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_U32_C(val))
#define kdArrFindAllIndicesToBool(idxs, len, arr, val)                      kdArrFindAllIndicesToU32(KD_PTR_C(idxs), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_U32_C(val))
#define kdArrFindAllIndicesToPtr(idxs, len, arr, val)                       kdArrFindAllIndicesToU64(KD_PTR_C(idxs), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_BASE_UINT_C(val))
#define kdArrFindAllIndicesToN(idxs, len, arr, val_ptr)                     kdGenArrFindAllIndicesTo(KD_PTR_C(idxs), KD_BASE_INT_C(len), KD_PTR_C(arr), KD_BASE_UINT_C(val_ptr))


KDAPI(void*) kdArrCreateInit(kd_i64_t len, kd_byte_t val, kd_bool_t (*allocator)(void*, kd_usize_t));
KDAPI(void*) kdArrCreateInitU16(kd_i64_t len, kd_u16_t val, kd_bool_t (*allocator)(void*, kd_usize_t));
KDAPI(void*) kdArrCreateInitU32(kd_i64_t len, kd_u32_t val, kd_bool_t (*allocator)(void*, kd_usize_t));
KDAPI(void*) kdArrCreateInitU64(kd_i64_t len, kd_u64_t val, kd_bool_t (*allocator)(void*, kd_usize_t));

KDAPI(kd_bool_t) kdArrFill(void* arr, kd_byte_t val);
KDAPI(kd_bool_t) kdArrFillU16(void* arr, kd_u16_t val);
KDAPI(kd_bool_t) kdArrFillU32(void* arr, kd_u32_t val);
KDAPI(kd_bool_t) kdArrFillU64(void* arr, kd_u64_t val);

KDAPI(kd_bool_t) kdArrFillRange(void* arr, kd_i64_t from, kd_i64_t to, kd_byte_t val);
KDAPI(kd_bool_t) kdArrFillRangeU16(void* arr, kd_i64_t from, kd_i64_t to, kd_u16_t val);
KDAPI(kd_bool_t) kdArrFillRangeU32(void* arr, kd_i64_t from, kd_i64_t to, kd_u32_t val);
KDAPI(kd_bool_t) kdArrFillRangeU64(void* arr, kd_i64_t from, kd_i64_t to, kd_u64_t val);

KDAPI(kd_bool_t) kdArrSet(void* arr, kd_i64_t idx, kd_byte_t val);
KDAPI(kd_bool_t) kdArrSetU16(void* arr, kd_i64_t idx, kd_u16_t val);
KDAPI(kd_bool_t) kdArrSetU32(void* arr, kd_i64_t idx, kd_u32_t val);
KDAPI(kd_bool_t) kdArrSetU64(void* arr, kd_i64_t idx, kd_u64_t val);

KDAPI(kd_byte_t) kdArrGet(void* arr, kd_i64_t idx);
KDAPI(kd_u16_t) kdArrGetU16(void* arr, kd_i64_t idx);
KDAPI(kd_u32_t) kdArrGetU32(void* arr, kd_i64_t idx);
KDAPI(kd_u64_t) kdArrGetU64(void* arr, kd_i64_t idx);

KDAPI(kd_i64_t) kdArrGetCount(void* arr, kd_byte_t val);
KDAPI(kd_i64_t) kdArrGetCountU16(void* arr, kd_u16_t val);
KDAPI(kd_i64_t) kdArrGetCountU32(void* arr, kd_u32_t val);
KDAPI(kd_i64_t) kdArrGetCountU64(void* arr, kd_u64_t val);

KDAPI(kd_i64_t) kdArrGetCountRange(void* arr, kd_i64_t from, kd_i64_t to, kd_byte_t val);
KDAPI(kd_i64_t) kdArrGetCountRangeU16(void* arr, kd_i64_t from, kd_i64_t to, kd_u16_t val);
KDAPI(kd_i64_t) kdArrGetCountRangeU32(void* arr, kd_i64_t from, kd_i64_t to, kd_u32_t val);
KDAPI(kd_i64_t) kdArrGetCountRangeU64(void* arr, kd_i64_t from, kd_i64_t to, kd_u64_t val);

KDAPI(void*) kdArrFind(void* arr, kd_byte_t val);
KDAPI(void*) kdArrFindU16(void* arr, kd_u16_t val);
KDAPI(void*) kdArrFindU32(void* arr, kd_u32_t val);
KDAPI(void*) kdArrFindU64(void* arr, kd_u64_t val);

KDAPI(kd_i64_t) kdArrFindIndex(void* arr, kd_byte_t val);
KDAPI(kd_i64_t) kdArrFindIndexU16(void* arr, kd_u16_t val);
KDAPI(kd_i64_t) kdArrFindIndexU32(void* arr, kd_u32_t val);
KDAPI(kd_i64_t) kdArrFindIndexU64(void* arr, kd_u64_t val);

KDAPI(void*) kdArrFindLast(void* arr, kd_byte_t val);
KDAPI(void*) kdArrFindLastU16(void* arr, kd_u16_t val);
KDAPI(void*) kdArrFindLastU32(void* arr, kd_u32_t val);
KDAPI(void*) kdArrFindLastU64(void* arr, kd_u64_t val);

KDAPI(kd_i64_t) kdArrFindLastIndex(void* arr, kd_byte_t val);
KDAPI(kd_i64_t) kdArrFindLastIndexU16(void* arr, kd_u16_t val);
KDAPI(kd_i64_t) kdArrFindLastIndexU32(void* arr, kd_u32_t val);
KDAPI(kd_i64_t) kdArrFindLastIndexU64(void* arr, kd_u64_t val);

KDAPI(kd_i64_t) kdArrFindAll(void* dst_arr, void* src_arr, kd_byte_t val);
KDAPI(kd_i64_t) kdArrFindAllU16(void* dst_arr, void* src_arr, kd_u16_t val);
KDAPI(kd_i64_t) kdArrFindAllU32(void* dst_arr, void* src_arr, kd_u32_t val);
KDAPI(kd_i64_t) kdArrFindAllU64(void* dst_arr, void* src_arr, kd_u64_t val);

KDAPI(kd_i64_t) kdArrFindAllTo(void* dst, kd_i64_t len, void* arr, kd_byte_t val);
KDAPI(kd_i64_t) kdArrFindAllToU16(void* dst, kd_i64_t len, void* arr, kd_u16_t val);
KDAPI(kd_i64_t) kdArrFindAllToU32(void* dst, kd_i64_t len, void* arr, kd_u32_t val);
KDAPI(kd_i64_t) kdArrFindAllToU64(void* dst, kd_i64_t len, void* arr, kd_u64_t val);

KDAPI(kd_i64_t) kdArrFindAllIndices(void* idx_arr, void* arr, kd_byte_t val);
KDAPI(kd_i64_t) kdArrFindAllIndicesU16(void* idx_arr, void* arr, kd_u16_t val);
KDAPI(kd_i64_t) kdArrFindAllIndicesU32(void* idx_arr, void* arr, kd_u32_t val);
KDAPI(kd_i64_t) kdArrFindAllIndicesU64(void* idx_arr, void* arr, kd_u64_t val);

KDAPI(kd_i64_t) kdArrFindAllIndicesTo(void* idxs, kd_i64_t len, void* arr, kd_byte_t val);
KDAPI(kd_i64_t) kdArrFindAllIndicesToU16(void* idxs, kd_i64_t len, void* arr, kd_u16_t val);
KDAPI(kd_i64_t) kdArrFindAllIndicesToU32(void* idxs, kd_i64_t len, void* arr, kd_u32_t val);
KDAPI(kd_i64_t) kdArrFindAllIndicesToU64(void* idxs, kd_i64_t len, void* arr, kd_u64_t val);


KD_EXTERN_END

#endif /* KD_ARR_H_ */
