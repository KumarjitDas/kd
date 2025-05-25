/**
 * @file mem.h
 * @author Kumarjit Das
 * @date 2025-05-25
 * @version 0.0.3
 * @brief Main header file of the MEM library.
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


#ifndef MEM_H_
#define MEM_H_


#include "kd.h"
#include "types.h"

KD_EXTERN_BEGIN


#if defined TYPES_64BIT_INTEGER
#define USE_64BIT 1
#endif  /* TYPES_64BIT_INTEGER */


#if defined USE_64BIT

KDAPI(bool) kdAlloc(void* dst, u64 sz);
KDAPI(bool) kdRealloc(void* dst, u64 new_sz, void* src, u64 old_sz);
KDAPI(bool) kdAllocWithSizeInfo(void* dst, u64 sz);
KDAPI(bool) kdReallocWithSizeInfo(void* dst, u64 new_sz, void* src, u64 old_sz);
KDAPI(u64)  kdGetAllocSize(void* src);

#else

KDAPI(bool) kdAlloc(void* dst, u32 sz);
KDAPI(bool) kdRealloc(void* dst, u32 new_sz, void* src, u32 old_sz);
KDAPI(bool) kdAllocWithSizeInfo(void* dst, u32 sz);
KDAPI(bool) kdReallocWithSizeInfo(void* dst, u32 new_sz, void* src, u32 old_sz);
KDAPI(u32)  kdGetAllocSize(void* src);

#endif  /* USE_64BIT */


KDAPI(bool) kdFree(void* dst);
KDAPI(bool) kdFreeWithSizeInfo(void* dst);


KD_EXTERN_END

#endif  /* MEM_H_ */
