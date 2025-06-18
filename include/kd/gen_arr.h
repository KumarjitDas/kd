/**
 * @file gen_arr.h
 * @author Kumarjit Das
 * @date 2025-06-16
 * @since 0.0.11
 * @brief Main header file of the GEN_ARR library.
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


#ifndef KD_GEN_ARR_H_
#define KD_GEN_ARR_H_


#include "kd/defs.h"
#include "kd/types/fw.h"

KD_EXTERN_BEGIN


#define KD_GEN_ARR_MAX_EL_SZ (16777215)
#if defined KD_ARCH_64BIT_INT
  #define KD_GEN_ARR_MAX_MEM_SZ KD_MAX_I64
#else
  #define KD_GEN_ARR_MAX_MEM_SZ KD_MAX_I32
#endif /* KD_ARCH_64BIT_INT */


KDAPI(void*) kdGenArrCreate(kd_i32_t el_sz, kd_i64_t len, kd_bool_t (*allocator)(void*, kd_usize_t));
KDAPI(void*) kdGenArrCreateInit(kd_i32_t el_sz, kd_i64_t len, void* val_ptr, kd_bool_t (*allocator)(void*, kd_usize_t));
KDAPI(void*)
kdGenArrCreateFrom(
  kd_i32_t el_sz,
  kd_i64_t len,
  void*    src,
  kd_i64_t src_len,
  kd_bool_t (*allocator)(void*, kd_usize_t)
);
KDAPI(void*) kdGenArrClone(void* arr, kd_bool_t (*allocator)(void*, kd_usize_t));
KDAPI(void*) kdGenArrCloneRange(void* arr, kd_i64_t from, kd_i64_t to, kd_bool_t (*allocator)(void*, kd_usize_t));
KDAPI(kd_bool_t) kdGenArrDestroy(void* arr, kd_bool_t (*deallocator)(void*));

KDAPI(kd_i32_t) kdGenArrGetElemSize(void* arr);
KDAPI(kd_i64_t) kdGenArrGetMemSize(void* arr);
KDAPI(kd_i64_t) kdGenArrGetLen(void* arr);
KDAPI(kd_bool_t) kdGenArrIsLE(void* arr);
KDAPI(kd_bool_t) kdGenArrIsBE(void* arr);
KDAPI(void*) kdGenArrGetEnd(void* arr);

KDAPI(kd_bool_t) kdGenArrFill(void* arr, void* val_ptr);
KDAPI(kd_bool_t) kdGenArrFillRange(void* arr, kd_i64_t from, kd_i64_t to, void* val_ptr);

KDAPI(kd_bool_t) kdGenArrSet(void* arr, kd_i64_t idx, void* val_ptr);
KDAPI(void*) kdGenArrGet(void* arr, kd_i64_t idx);

KDAPI(kd_bool_t) kdGenArrSwap(void* arr, kd_i64_t idx1, kd_i64_t idx2);
KDAPI(kd_bool_t) kdGenArrEquals(void* arr1, void* arr2);

KDAPI(kd_i64_t) kdGenArrGetCount(void* arr, void* val_ptr);
KDAPI(kd_i64_t) kdGenArrGetCountRange(void* arr, kd_i64_t from, kd_i64_t to, void* val_ptr);

KDAPI(kd_bool_t) kdGenArrReverse(void* arr);
KDAPI(kd_bool_t) kdGenArrGetReversed(void* dst_arr, void* src_arr);
KDAPI(kd_bool_t) kdGenArrGetReversedFrom(void* dst_arr, void* src, kd_i64_t len);
KDAPI(kd_bool_t) kdGenArrGetReversedTo(void* dst, kd_i64_t len, void* src_arr);

KDAPI(kd_bool_t) kdGenArrReverseRange(void* arr, kd_i64_t from, kd_i64_t to);
KDAPI(kd_bool_t)
kdGenArrGetReversedRange(void* dst_arr, kd_i64_t dst_from, void* src_arr, kd_i64_t src_from, kd_i64_t src_to);
KDAPI(kd_bool_t)
kdGenArrGetReversedRangeFrom(void* dst_arr, kd_i64_t dst_from, void* src, kd_i64_t src_from, kd_i64_t src_to);
KDAPI(kd_bool_t) kdGenArrGetReversedRangeTo(void* dst, kd_i64_t len, void* src_arr, kd_i64_t from, kd_i64_t to);

KDAPI(kd_bool_t) kdGenArrCpy(void* dst_arr, void* src_arr);
KDAPI(kd_bool_t) kdGenArrCpyFrom(void* dst_arr, void* src, kd_i64_t len);
KDAPI(kd_bool_t) kdGenArrCpyTo(void* dst, kd_i64_t len, void* src_arr);
KDAPI(kd_bool_t)
kdGenArrCpyRange(void* dst_arr, kd_i64_t dst_from, void* src_arr, kd_i64_t src_from, kd_i64_t src_to);
KDAPI(kd_bool_t) kdGenArrCpyRangeFrom(void* dst_arr, kd_i64_t dst_from, void* src, kd_i64_t src_from, kd_i64_t src_to);
KDAPI(kd_bool_t) kdGenArrCpyRangeTo(void* dst, kd_i64_t len, void* src_arr, kd_i64_t from, kd_i64_t to);

KDAPI(void*) kdGenArrFind(void* arr, void* val_ptr);
KDAPI(kd_i64_t) kdGenArrFindIndex(void* arr, void* val_ptr);
KDAPI(void*) kdGenArrFindLast(void* arr, void* val_ptr);
KDAPI(kd_i64_t) kdGenArrFindLastIndex(void* arr, void* val_ptr);

KDAPI(kd_i64_t) kdGenArrFindAll(void* dst_arr, void* src_arr, void* val_ptr);
KDAPI(kd_i64_t) kdGenArrFindAllTo(void* dst, kd_i64_t len, void* arr, void* val_ptr);
KDAPI(kd_i64_t) kdGenArrFindAllIndices(void* idx_arr, void* arr, void* val_ptr);
KDAPI(kd_i64_t) kdGenArrFindAllIndicesTo(void* idxs, kd_i64_t len, void* arr, void* val_ptr);

/*
KDAPI(kd_bool_t) kdGenArrSort(void* arr, kd_i32_t (*comparator)(void*, void*));
KDAPI(kd_bool_t) kdGenArrSortRange(void* arr, kd_i64_t from, kd_i64_t to, kd_i32_t (*comparator)(void*, void*));
KDAPI(kd_bool_t) kdGenArrGetSorted(void* dst_arr, void* src_arr, kd_i32_t (*comparator)(void*, void*));
KDAPI(kd_bool_t)
kdGenArrGetSortedRange(
  void*    dst_arr,
  kd_i64_t dst_from,
  void*    src_arr,
  kd_i64_t src_from,
  kd_i64_t src_to,
  kd_i32_t (*comparator)(void*, void*)
);
KDAPI(kd_bool_t) kdGenArrGetSortedTo(void* dst, kd_i64_t dst_len, void* src_arr, kd_i32_t (*comparator)(void*, void*));
KDAPI(kd_bool_t)
kdGenArrGetSortedRangeTo(
  void*    dst,
  kd_i64_t dst_len,
  void*    src_arr,
  kd_i64_t from,
  kd_i64_t to,
  kd_i32_t (*comparator)(void*, void*)
);
*/


KD_EXTERN_END

#endif /* KD_GEN_ARR_H_ */
