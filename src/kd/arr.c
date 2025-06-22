/**
 * @file arr.c
 * @author Kumarjit Das
 * @date 2025-06-23
 * @since 0.0.12
 * @brief Main source file of the ARR library.
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
#include "kd/gen_arr.h"
#include "kd/arr.h"


void*
kdArrCreateInit(kd_i64_t len, kd_byte_t val, kd_bool_t (*allocator)(void*, kd_usize_t))
{
  return kdGenArrCreateInit(KD_SZ_BYTE, len, &val, allocator);
}


void*
kdArrCreateInitU16(kd_i64_t len, kd_u16_t val, kd_bool_t (*allocator)(void*, kd_usize_t))
{
  return kdGenArrCreateInit(KD_SZ_U16, len, &val, allocator);
}


void*
kdArrCreateInitU32(kd_i64_t len, kd_u32_t val, kd_bool_t (*allocator)(void*, kd_usize_t))
{
  return kdGenArrCreateInit(KD_SZ_U32, len, &val, allocator);
}


void*
kdArrCreateInitU64(kd_i64_t len, kd_u64_t val, kd_bool_t (*allocator)(void*, kd_usize_t))
{
  return kdGenArrCreateInit(KD_SZ_U64, len, &val, allocator);
}


kd_bool_t
kdArrFill(void* arr, kd_byte_t val)
{
  return kdGenArrFill(arr, &val);
}


kd_bool_t
kdArrFillU16(void* arr, kd_u16_t val)
{
  return kdGenArrFill(arr, &val);
}


kd_bool_t
kdArrFillU32(void* arr, kd_u32_t val)
{
  return kdGenArrFill(arr, &val);
}


kd_bool_t
kdArrFillU64(void* arr, kd_u64_t val)
{
  return kdGenArrFill(arr, &val);
}


kd_bool_t
kdArrFillRange(void* arr, kd_i64_t from, kd_i64_t to, kd_byte_t val)
{
  return kdGenArrFillRange(arr, from, to, &val);
}


kd_bool_t
kdArrFillRangeU16(void* arr, kd_i64_t from, kd_i64_t to, kd_u16_t val)
{
  return kdGenArrFillRange(arr, from, to, &val);
}


kd_bool_t
kdArrFillRangeU32(void* arr, kd_i64_t from, kd_i64_t to, kd_u32_t val)
{
  return kdGenArrFillRange(arr, from, to, &val);
}


kd_bool_t
kdArrFillRangeU64(void* arr, kd_i64_t from, kd_i64_t to, kd_u64_t val)
{
  return kdGenArrFillRange(arr, from, to, &val);
}


kd_bool_t
kdArrSet(void* arr, kd_i64_t idx, kd_byte_t val)
{
  return kdGenArrSet(arr, idx, &val);
}


kd_bool_t
kdArrSetU16(void* arr, kd_i64_t idx, kd_u16_t val)
{
  return kdGenArrSet(arr, idx, &val);
}


kd_bool_t
kdArrSetU32(void* arr, kd_i64_t idx, kd_u32_t val)
{
  return kdGenArrSet(arr, idx, &val);
}


kd_bool_t
kdArrSetU64(void* arr, kd_i64_t idx, kd_u64_t val)
{
  return kdGenArrSet(arr, idx, &val);
}


kd_byte_t
kdArrGet(void* arr, kd_i64_t idx)
{
  kd_byte_t* val_ptr = kdGenArrGet(arr, idx);
  return val_ptr ? *val_ptr : 0;
}


kd_u16_t
kdArrGetU16(void* arr, kd_i64_t idx)
{
  kd_u16_t* val_ptr = kdGenArrGet(arr, idx);
  return val_ptr ? *val_ptr : 0;
}


kd_u32_t
kdArrGetU32(void* arr, kd_i64_t idx)
{
  kd_u32_t* val_ptr = kdGenArrGet(arr, idx);
  return val_ptr ? *val_ptr : 0;
}


kd_u64_t
kdArrGetU64(void* arr, kd_i64_t idx)
{
  kd_u64_t* val_ptr = kdGenArrGet(arr, idx);
  return val_ptr ? *val_ptr : 0;
}

kd_i64_t
kdArrGetCount(void* arr, kd_byte_t val)
{
  return kdGenArrGetCount(arr, &val);
}


kd_i64_t
kdArrGetCountU16(void* arr, kd_u16_t val)
{
  return kdGenArrGetCount(arr, &val);
}


kd_i64_t
kdArrGetCountU32(void* arr, kd_u32_t val)
{
  return kdGenArrGetCount(arr, &val);
}


kd_i64_t
kdArrGetCountU64(void* arr, kd_u64_t val)
{
  return kdGenArrGetCount(arr, &val);
}


kd_i64_t
kdArrGetCountRange(void* arr, kd_i64_t from, kd_i64_t to, kd_byte_t val)
{
  return kdGenArrGetCountRange(arr, from, to, &val);
}


kd_i64_t
kdArrGetCountRangeU16(void* arr, kd_i64_t from, kd_i64_t to, kd_u16_t val)
{
  return kdGenArrGetCountRange(arr, from, to, &val);
}


kd_i64_t
kdArrGetCountRangeU32(void* arr, kd_i64_t from, kd_i64_t to, kd_u32_t val)
{
  return kdGenArrGetCountRange(arr, from, to, &val);
}


kd_i64_t
kdArrGetCountRangeU64(void* arr, kd_i64_t from, kd_i64_t to, kd_u64_t val)
{
  return kdGenArrGetCountRange(arr, from, to, &val);
}


void*
kdArrFind(void* arr, kd_byte_t val)
{
  return kdGenArrFind(arr, &val);
}


void*
kdArrFindU16(void* arr, kd_u16_t val)
{
  return kdGenArrFind(arr, &val);
}


void*
kdArrFindU32(void* arr, kd_u32_t val)
{
  return kdGenArrFind(arr, &val);
}


void*
kdArrFindU64(void* arr, kd_u64_t val)
{
  return kdGenArrFind(arr, &val);
}


kd_i64_t
kdArrFindIndex(void* arr, kd_byte_t val)
{
  return kdGenArrFindIndex(arr, &val);
}


kd_i64_t
kdArrFindIndexU16(void* arr, kd_u16_t val)
{
  return kdGenArrFindIndex(arr, &val);
}


kd_i64_t
kdArrFindIndexU32(void* arr, kd_u32_t val)
{
  return kdGenArrFindIndex(arr, &val);
}


kd_i64_t
kdArrFindIndexU64(void* arr, kd_u64_t val)
{
  return kdGenArrFindIndex(arr, &val);
}


void*
kdArrFindLast(void* arr, kd_byte_t val)
{
  return kdGenArrFindLast(arr, &val);
}


void*
kdArrFindLastU16(void* arr, kd_u16_t val)
{
  return kdGenArrFindLast(arr, &val);
}


void*
kdArrFindLastU32(void* arr, kd_u32_t val)
{
  return kdGenArrFindLast(arr, &val);
}


void*
kdArrFindLastU64(void* arr, kd_u64_t val)
{
  return kdGenArrFindLast(arr, &val);
}


kd_i64_t
kdArrFindLastIndex(void* arr, kd_byte_t val)
{
  return kdGenArrFindLastIndex(arr, &val);
}


kd_i64_t
kdArrFindLastIndexU16(void* arr, kd_u16_t val)
{
  return kdGenArrFindLastIndex(arr, &val);
}


kd_i64_t
kdArrFindLastIndexU32(void* arr, kd_u32_t val)
{
  return kdGenArrFindLastIndex(arr, &val);
}


kd_i64_t
kdArrFindLastIndexU64(void* arr, kd_u64_t val)
{
  return kdGenArrFindLastIndex(arr, &val);
}


kd_i64_t
kdArrFindAll(void* dst_arr, void* src_arr, kd_byte_t val)
{
  return kdGenArrFindAll(dst_arr, src_arr, &val);
}


kd_i64_t
kdArrFindAllU16(void* dst_arr, void* src_arr, kd_u16_t val)
{
  return kdGenArrFindAll(dst_arr, src_arr, &val);
}


kd_i64_t
kdArrFindAllU32(void* dst_arr, void* src_arr, kd_u32_t val)
{
  return kdGenArrFindAll(dst_arr, src_arr, &val);
}


kd_i64_t
kdArrFindAllU64(void* dst_arr, void* src_arr, kd_u64_t val)
{
  return kdGenArrFindAll(dst_arr, src_arr, &val);
}


kd_i64_t
kdArrFindAllTo(void* dst, kd_i64_t len, void* arr, kd_byte_t val)
{
  return kdGenArrFindAllTo(dst, len, arr, &val);
}


kd_i64_t
kdArrFindAllToU16(void* dst, kd_i64_t len, void* arr, kd_u16_t val)
{
  return kdGenArrFindAllTo(dst, len, arr, &val);
}


kd_i64_t
kdArrFindAllToU32(void* dst, kd_i64_t len, void* arr, kd_u32_t val)
{
  return kdGenArrFindAllTo(dst, len, arr, &val);
}


kd_i64_t
kdArrFindAllToU64(void* dst, kd_i64_t len, void* arr, kd_u64_t val)
{
  return kdGenArrFindAllTo(dst, len, arr, &val);
}


kd_i64_t
kdArrFindAllIndices(void* dst_arr, void* src_arr, kd_byte_t val)
{
  return kdGenArrFindAllIndices(dst_arr, src_arr, &val);
}


kd_i64_t
kdArrFindAllIndicesU16(void* dst_arr, void* src_arr, kd_u16_t val)
{
  return kdGenArrFindAllIndices(dst_arr, src_arr, &val);
}


kd_i64_t
kdArrFindAllIndicesU32(void* dst_arr, void* src_arr, kd_u32_t val)
{
  return kdGenArrFindAllIndices(dst_arr, src_arr, &val);
}


kd_i64_t
kdArrFindAllIndicesU64(void* dst_arr, void* src_arr, kd_u64_t val)
{
  return kdGenArrFindAllIndices(dst_arr, src_arr, &val);
}


kd_i64_t
kdArrFindAllIndicesTo(void* dst, kd_i64_t len, void* arr, kd_byte_t val)
{
  return kdGenArrFindAllIndicesTo(dst, len, arr, &val);
}


kd_i64_t
kdArrFindAllIndicesToU16(void* dst, kd_i64_t len, void* arr, kd_u16_t val)
{
  return kdGenArrFindAllIndicesTo(dst, len, arr, &val);
}


kd_i64_t
kdArrFindAllIndicesToU32(void* dst, kd_i64_t len, void* arr, kd_u32_t val)
{
  return kdGenArrFindAllIndicesTo(dst, len, arr, &val);
}


kd_i64_t
kdArrFindAllIndicesToU64(void* dst, kd_i64_t len, void* arr, kd_u64_t val)
{
  return kdGenArrFindAllIndicesTo(dst, len, arr, &val);
}
