/**
 * @file gen_mem_ops.h
 * @author Kumarjit Das
 * @date 2025-06-02
 * @since 0.0.7
 * @brief Main header file of the GEN_MEM_OPS library.
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


#ifndef KD_GEN_MEM_OPS_H_
#define KD_GEN_MEM_OPS_H_


#include "kd/defs.h"
#include "kd/types/fw.h"

KD_EXTERN_BEGIN


#if defined KD_USE_SIMPLIFIED_TYPES

KDAPI(bool) kdGenMemOpsSetBytes(void* ptr, usize sz, byte val);
KDAPI(bool) kdGenMemOpsSetBlocks(void* ptr, usize sz, void* block, usize block_sz);
KDAPI(bool) kdGenMemOpsCpy(void* dst, void* src, usize sz);
KDAPI(bool) kdGenMemOpsMove(void* dst, void* src, usize sz);
KDAPI(void*) kdGenMemOpsFindByte(void* ptr, usize sz, byte item);
KDAPI(bool) kdGenMemOpsFindByteIndex(usize* idx_ptr, void* ptr, usize sz, byte item);
KDAPI(void*) kdGenMemOpsFindBlock(void* ptr, usize sz, void* block, usize block_sz);
KDAPI(bool)
kdGenMemOpsFindBlockIndex(usize* idx_ptr, void* ptr, usize sz, void* block, usize block_sz);
KDAPI(i32) kdGenMemOpsCmp(void* ptr1, void* ptr2, usize sz);
KDAPI(bool) kdGenMemOpsCat(void* dst, usize sz, void* src1, usize sz1, void* src2, usize sz2);
KDAPI(void*) kdGenMemOpsBytesCompSpn(void* ptr, usize sz, void* keys, usize keys_sz);
KDAPI(bool)
kdGenMemOpsBytesCompSpnIndex(usize* idx_ptr, void* ptr, usize sz, void* keys, usize keys_sz);
KDAPI(void*)
kdGenMemOpsBlocksCompSpn(void* ptr, usize sz, void* key_blocks, usize key_block_sz, usize key_blocks_sz);
KDAPI(bool)
kdGenMemOpsBlocksCompSpnIndex(usize* idx_ptr, void* ptr, usize sz, void* key_blocks, usize key_block_sz,
                              usize key_blocks_sz);
KDAPI(usize) kdGenMemOpsBytesSpn(void* ptr, usize sz, void* keys, usize keys_sz);
KDAPI(usize)
kdGenMemOpsBlocksSpn(void* ptr, usize sz, void* key_blocks, usize key_block_sz, usize key_blocks_sz);

#else

KDAPI(kd_bool_t) kdGenMemOpsSetBytes(void* ptr, kd_usize_t sz, kd_byte_t val);
KDAPI(kd_bool_t) kdGenMemOpsSetBlocks(void* ptr, kd_usize_t sz, void* block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsCpy(void* dst, void* src, kd_usize_t sz);
KDAPI(kd_bool_t) kdGenMemOpsMove(void* dst, void* src, kd_usize_t sz);
KDAPI(void*) kdGenMemOpsFindByte(void* ptr, kd_usize_t sz, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindByteIndex(kd_usize_t* idx_ptr, void* ptr, kd_usize_t sz, kd_byte_t item);
KDAPI(void*) kdGenMemOpsFindBlock(void* ptr, kd_usize_t sz, void* block, kd_usize_t block_sz);
KDAPI(kd_bool_t)
kdGenMemOpsFindBlockIndex(kd_usize_t* idx_ptr, void* ptr, kd_usize_t sz, void* block, kd_usize_t block_sz);
KDAPI(kd_i32_t) kdGenMemOpsCmp(void* ptr1, void* ptr2, kd_usize_t sz);
KDAPI(kd_bool_t) kdGenMemOpsCat(void* dst, kd_usize_t sz, void* src1, kd_usize_t sz1, void* src2, kd_usize_t sz2);
KDAPI(void*) kdGenMemOpsBytesCompSpn(void* ptr, kd_usize_t sz, void* keys, kd_usize_t keys_sz);
KDAPI(kd_bool_t)
kdGenMemOpsBytesCompSpnIndex(kd_usize_t* idx_ptr, void* ptr, kd_usize_t sz, void* keys, kd_usize_t keys_sz);
KDAPI(void*)
kdGenMemOpsBlocksCompSpn(void* ptr, kd_usize_t sz, void* key_blocks, kd_usize_t key_block_sz, kd_usize_t key_blocks_sz);
KDAPI(kd_bool_t)
kdGenMemOpsBlocksCompSpnIndex(kd_usize_t* idx_ptr, void* ptr, kd_usize_t sz, void* key_blocks, kd_usize_t key_block_sz,
                              kd_usize_t key_blocks_sz);
KDAPI(kd_usize_t) kdGenMemOpsBytesSpn(void* ptr, kd_usize_t sz, void* keys, kd_usize_t keys_sz);
KDAPI(kd_usize_t)
kdGenMemOpsBlocksSpn(void* ptr, kd_usize_t sz, void* key_blocks, kd_usize_t key_block_sz, kd_usize_t key_blocks_sz);

#endif /* KD_USE_SIMPLIFIED_TYPES */


KD_EXTERN_END

#endif /* KD_GEN_MEM_OPS_H_ */
