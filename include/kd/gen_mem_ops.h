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
#include "kd/fixed_width.h"

KD_EXTERN_BEGIN


KDAPI(kd_bool_t) kdGenMemOpsSwapBytes(void *ptr, kd_usize_t sz, kd_usize_t idx1, kd_usize_t idx2);
KDAPI(kd_bool_t) kdGenMemOpsSwapBlocks(void *ptr, kd_usize_t sz, kd_usize_t block_sz, kd_usize_t idx1, kd_usize_t idx2);
KDAPI(kd_bool_t) kdGenMemOpsReverseBytes(void *ptr, kd_usize_t sz);
KDAPI(kd_bool_t) kdGenMemOpsReverseBlocks(void *ptr, kd_usize_t sz, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsSetBytes(void *ptr, kd_usize_t sz, kd_byte_t val);
KDAPI(kd_bool_t) kdGenMemOpsSetBlocks(void *ptr, kd_usize_t sz, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsCpy(void *dst, void *src, kd_usize_t sz);
KDAPI(kd_bool_t) kdGenMemOpsMove(void *dst, void *src, kd_usize_t sz);

KDAPI(void *) kdGenMemOpsFindByte(void *ptr, kd_usize_t sz, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindByteIndex(kd_usize_t *idx_ptr, void *ptr, kd_usize_t sz, kd_byte_t item);
KDAPI(void *) kdGenMemOpsFindLastByte(void *ptr, kd_usize_t sz, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindLastByteIndex(kd_usize_t *idx_ptr, void *ptr, kd_usize_t sz, kd_byte_t item);
KDAPI(kd_usize_t) kdGenMemOpsFindAllBytes(void *dst, kd_usize_t dst_sz, void *ptr, kd_usize_t ptr_sz, kd_byte_t item);

KDAPI(kd_usize_t) kdGenMemOpsFindAllByteIndices(kd_usize_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, kd_byte_t item);
KDAPI(kd_usize_t) kdGenMemOpsFindAllByteIndicesU8(kd_u8_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, kd_byte_t item);
KDAPI(kd_usize_t) kdGenMemOpsFindAllByteIndicesU16(kd_u16_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, kd_byte_t item);
KDAPI(kd_usize_t) kdGenMemOpsFindAllByteIndicesU32(kd_u32_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, kd_byte_t item);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_usize_t) kdGenMemOpsFindAllByteIndicesU64(kd_u64_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, kd_byte_t item);
#endif

KDAPI(void *) kdGenMemOpsFindBlock(void *ptr, kd_usize_t sz, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindBlockIndex(kd_usize_t *idx_ptr, void *ptr, kd_usize_t sz, void *block, kd_usize_t block_sz);
KDAPI(void *) kdGenMemOpsFindLastBlock(void *ptr, kd_usize_t sz, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindLastBlockIndex(kd_usize_t *idx_ptr, void *ptr, kd_usize_t sz, void *block, kd_usize_t block_sz);
KDAPI(kd_usize_t) kdGenMemOpsFindAllBlocks(void *dst, kd_usize_t dst_sz, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);

KDAPI(kd_usize_t) kdGenMemOpsFindAllBlockIndices(kd_usize_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);
KDAPI(kd_usize_t) kdGenMemOpsFindAllBlockIndicesU8(kd_u8_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);
KDAPI(kd_usize_t) kdGenMemOpsFindAllBlockIndicesU16(kd_u16_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);
KDAPI(kd_usize_t) kdGenMemOpsFindAllBlockIndicesU32(kd_u32_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_usize_t) kdGenMemOpsFindAllBlockIndicesU64(kd_u64_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);
#endif

KDAPI(kd_word_t) kdGenMemOpsCmp(void *ptr1, void *ptr2, kd_usize_t sz);
KDAPI(kd_bool_t) kdGenMemOpsCat(void *dst, kd_usize_t sz, void *src1, kd_usize_t sz1, void *src2, kd_usize_t sz2);

KDAPI(void *) kdGenMemOpsBytesCompSpn(void *ptr, kd_usize_t sz, void *keys, kd_usize_t keys_sz);
KDAPI(kd_bool_t) kdGenMemOpsBytesCompSpnIndex(kd_usize_t *idx_ptr, void *ptr, kd_usize_t sz, void *keys, kd_usize_t keys_sz);
KDAPI(void *) kdGenMemOpsBlocksCompSpn(void *ptr, kd_usize_t sz, void *key_blocks, kd_usize_t key_block_sz, kd_usize_t key_blocks_sz);
KDAPI(kd_bool_t) kdGenMemOpsBlocksCompSpnIndex(kd_usize_t *idx_ptr, void *ptr, kd_usize_t sz, void *key_blocks, kd_usize_t key_block_sz, kd_usize_t key_blocks_sz);

KDAPI(kd_usize_t) kdGenMemOpsBytesSpn(void *ptr, kd_usize_t sz, void *keys, kd_usize_t keys_sz);
KDAPI(kd_usize_t) kdGenMemOpsBlocksSpn(void *ptr, kd_usize_t sz, void *key_blocks, kd_usize_t key_block_sz, kd_usize_t key_blocks_sz);


KD_EXTERN_END

#endif /* KD_GEN_MEM_OPS_H_ */
