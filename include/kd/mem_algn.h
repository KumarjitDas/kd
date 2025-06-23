/**
 * @file mem_algn.h
 * @author Kumarjit Das
 * @date 2025-06-01
 * @since 0.0.6
 * @brief Main header file of the MEM_ALGN library.
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


#ifndef KD_MEM_ALGN_H_
#define KD_MEM_ALGN_H_


#include "kd/defs.h"
#include "kd/types/fw.h"

KD_EXTERN_BEGIN


#define KD_MEM_ALGN_MAX_ALGN_SIZE                          128
#define KD_MEM_ALGN_DEFAULT_OFFSET                         KD_SZ_U8
#define KD_MEM_ALGN_MAX_OFFSET                             KD_SZ_UMAX


#define kdMemAlgnGetDefaultAllocSize(usable_size, algn_sz) kdMemAlgnGetAllocSize(usable_size, algn_sz, KD_MEM_ALGN_DEFAULT_OFFSET)
#define kdMemAlgnGetDefaultOffsetPtr(head_ptr, algn_sz)    kdMemAlgnGetOffsetPtr(head_ptr, algn_sz, KD_MEM_ALGN_DEFAULT_OFFSET)
#define kdMemAlgnGetDefaultHeadPtr(off_ptr)                kdMemAlgnGetHeadPtr(off_ptr, KD_MEM_ALGN_DEFAULT_OFFSET)


KDAPI(kd_usize_t) kdMemAlgnGetAllocSize(kd_usize_t usable_size, kd_u8_t algn_sz, kd_u8_t offset);
KDAPI(void *) kdMemAlgnGetForwardPtr(void *head_ptr, kd_u8_t algn_sz, kd_u8_t offset);
KDAPI(void *) kdMemAlgnGetBackwardPtr(void *head_ptr, kd_u8_t algn_sz, kd_u8_t offset);
KDAPI(void *) kdMemAlgnGetOffsetPtr(void *head_ptr, kd_u8_t algn_sz, kd_u8_t offset);
KDAPI(void *) kdMemAlgnGetHeadPtr(void *off_ptr, kd_u8_t offset);


KD_EXTERN_END

#endif /* KD_MEM_ALGN_H_ */
