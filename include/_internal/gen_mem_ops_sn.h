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


#include "kd/defs.h"
#include "kd/types/fw.h"

KD_EXTERN_BEGIN


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
kdi_GenMemOpsBlocksCompSpnWithIndex_S8(kd_usize_t* idx_ptr, kd_u8_t* ptr, kd_usize_t sz, kd_u8_t* keys,
                                       kd_usize_t keys_sz);
KDAPI(void*)
kdi_GenMemOpsBlocksCompSpnWithIndex_S16(kd_usize_t* idx_ptr, kd_u16_t* ptr, kd_usize_t sz, kd_u16_t* keys,
                                        kd_usize_t keys_sz);
KDAPI(void*)
kdi_GenMemOpsBlocksCompSpnWithIndex_S32(kd_usize_t* idx_ptr, kd_u32_t* ptr, kd_usize_t sz, kd_u32_t* keys,
                                        kd_usize_t keys_sz);
#if defined KD_ARCH_64BIT_INT
KDAPI(void*)
kdi_GenMemOpsBlocksCompSpnWithIndex_S64(kd_usize_t* idx_ptr, kd_u64_t* ptr, kd_usize_t sz, kd_u64_t* keys,
                                        kd_usize_t keys_sz);
#endif
KDAPI(void*)
kdi_GenMemOpsBlocksCompSpnWithIndex_Sn(kd_usize_t* idx_ptr, void* ptr, kd_usize_t sz, void* key_blocks,
                                       kd_usize_t key_block_sz, kd_usize_t key_blocks_sz);

KDAPI(kd_usize_t) kdi_GenMemOpsBlocksSpn_S8(kd_u8_t* ptr, kd_usize_t sz, kd_u8_t* keys, kd_usize_t keys_sz);
KDAPI(kd_usize_t) kdi_GenMemOpsBlocksSpn_S16(kd_u16_t* ptr, kd_usize_t sz, kd_u16_t* keys, kd_usize_t keys_sz);
KDAPI(kd_usize_t) kdi_GenMemOpsBlocksSpn_S32(kd_u32_t* ptr, kd_usize_t sz, kd_u32_t* keys, kd_usize_t keys_sz);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_usize_t) kdi_GenMemOpsBlocksSpn_S64(kd_u64_t* ptr, kd_usize_t sz, kd_u64_t* keys, kd_usize_t keys_sz);
#endif
KDAPI(kd_usize_t)
kdi_GenMemOpsBlocksSpn_Sn(void* ptr, kd_usize_t sz, void* key_blocks, kd_usize_t key_block_sz,
                          kd_usize_t key_blocks_sz);


KD_EXTERN_END

#endif /* KD__INTERNAL_GEN_MEM_OPS_SN_H_ */
