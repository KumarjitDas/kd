/**
 * @file kd_gen_mem_ops.h
 * @author Kumarjit Das
 * @version 0.0.1
 * @brief Main header file of the KD_GEN_MEM_OPS library.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 * @since 0.0.1
 */


#ifndef KD_GEN_MEM_OPS_H_
#define KD_GEN_MEM_OPS_H_


#include "kd_version.h"
#include "kd_platform.h"
#include "kd_fixed_width.h"


KD_EXTERN_BEGIN


#define KD_GEN_MEM_OPS_VERSION_MAJOR 0
#define KD_GEN_MEM_OPS_VERSION_MINOR 0
#define KD_GEN_MEM_OPS_VERSION_PATCH 1

#define KD_GEN_MEM_OPS_VERSION_CSTR  KDI_STRINGIFY(KD_GEN_MEM_OPS_VERSION_MAJOR) "." KDI_STRINGIFY(KD_GEN_MEM_OPS_VERSION_MINOR) "." KDI_STRINGIFY(KD_GEN_MEM_OPS_VERSION_PATCH)
#define KD_GEN_MEM_OPS_VERSION_ARR   {KD_GEN_MEM_OPS_VERSION_MAJOR, KD_GEN_MEM_OPS_VERSION_MINOR, KD_GEN_MEM_OPS_VERSION_PATCH}


#define kdGenMemOpsFindAllByteIndicesUmin(idxs, idxs_sz, ptr, ptr_sz, item)                                                                                                        \
    kdGenMemOpsFindAllByteIndicesU8(KD_PU8_C(idxs), KD_USIZE_C(idxs_sz), KD_PTR_C(ptr), KD_USIZE_C(ptr_sz), KD_BYTE_C(item))

#if defined KD_ARCH_64BIT_INT
    #define kdGenMemOpsFindAllByteIndicesUmax(idxs, idxs_sz, ptr, ptr_sz, item)                                                                                                    \
        kdGenMemOpsFindAllByteIndicesU64(KD_PU64_C(idxs), KD_USIZE_C(idxs_sz), KD_PTR_C(ptr), KD_USIZE_C(ptr_sz), KD_BYTE_C(item))
    #define kdGenMemOpsFindAllByteIndicesUsize(idxs, idxs_sz, ptr, ptr_sz, item)                                                                                                   \
        kdGenMemOpsFindAllByteIndicesU64(KD_PU64_C(idxs), KD_USIZE_C(idxs_sz), KD_PTR_C(ptr), KD_USIZE_C(ptr_sz), KD_BYTE_C(item))
#else /* !defined KD_ARCH_64BIT_INT */
    #define kdGenMemOpsFindAllByteIndicesUmax(idxs, idxs_sz, ptr, ptr_sz, item)                                                                                                    \
        kdGenMemOpsFindAllByteIndicesU32(KD_PU32_C(idxs), KD_USIZE_C(idxs_sz), KD_PTR_C(ptr), KD_USIZE_C(ptr_sz), KD_BYTE_C(item))
    #define kdGenMemOpsFindAllByteIndicesUsize(idxs, idxs_sz, ptr, ptr_sz, item)                                                                                                   \
        kdGenMemOpsFindAllByteIndicesU32(KD_PU32_C(idxs), KD_USIZE_C(idxs_sz), KD_PTR_C(ptr), KD_USIZE_C(ptr_sz), KD_BYTE_C(item))
#endif /* KD_ARCH_64BIT_INT */


#define kdGenMemOpsFindAllBlockIndicesUmin(idxs, idxs_sz, ptr, ptr_sz, block, block_sz)                                                                                            \
    kdGenMemOpsFindAllBlockIndicesU8(KD_PU8_C(idxs), KD_USIZE_C(idxs_sz), KD_PTR_C(ptr), KD_USIZE_C(ptr_sz), KD_PTR_C(block), KD_USIZE_C(block_sz))

#if defined KD_ARCH_64BIT_INT
    #define kdGenMemOpsFindAllBlockIndicesUmax(idxs, idxs_sz, ptr, ptr_sz, block, block_sz)                                                                                        \
        kdGenMemOpsFindAllBlockIndicesU64(KD_PU64_C(idxs), KD_USIZE_C(idxs_sz), KD_PTR_C(ptr), KD_USIZE_C(ptr_sz), KD_PTR_C(block), KD_USIZE_C(block_sz))
    #define kdGenMemOpsFindAllBlockIndicesUsize(idxs, idxs_sz, ptr, ptr_sz, block, block_sz)                                                                                       \
        kdGenMemOpsFindAllBlockIndicesU64(KD_PU64_C(idxs), KD_USIZE_C(idxs_sz), KD_PTR_C(ptr), KD_USIZE_C(ptr_sz), KD_PTR_C(block), KD_USIZE_C(block_sz))
#else /* !defined KD_ARCH_64BIT_INT */
    #define kdGenMemOpsFindAllBlockIndicesUmax(idxs, idxs_sz, ptr, ptr_sz, block, block_sz)                                                                                        \
        kdGenMemOpsFindAllBlockIndicesU32(KD_PU32_C(idxs), KD_USIZE_C(idxs_sz), KD_PTR_C(ptr), KD_USIZE_C(ptr_sz), KD_PTR_C(block), KD_USIZE_C(block_sz))
    #define kdGenMemOpsFindAllBlockIndicesUsize(idxs, idxs_sz, ptr, ptr_sz, block, block_sz)                                                                                       \
        kdGenMemOpsFindAllBlockIndicesU32(KD_PU32_C(idxs), KD_USIZE_C(idxs_sz), KD_PTR_C(ptr), KD_USIZE_C(ptr_sz), KD_PTR_C(block), KD_USIZE_C(block_sz))
#endif /* KD_ARCH_64BIT_INT */


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
