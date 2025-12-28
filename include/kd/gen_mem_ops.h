/**
 * @file gen_mem_ops.h
 * @author Kumarjit Das
 * @version 0.0.1
 * @brief Main header file of the KD_GEN_MEM_OPS library.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 * @since 0.0.1
 */


#ifndef KD_GEN_MEM_OPS_H_
#define KD_GEN_MEM_OPS_H_


#include "./version.h"
#include "./platform.h"
#include "./api.h"
#include "./fixed_width.h"
#include "./bool.h"


KD_EXTERN_BEGIN


KDAPI(kd_bool_t) kdGenMemOpsCopy(void *dst, void *src, kd_usize_t sz);
KDAPI(kd_bool_t) kdGenMemOpsCopyRegion(void *dst, kd_usize_t dst_sz, kd_usize_t *copied_sz, void *src, kd_usize_t src_sz);
KDAPI(kd_bool_t) kdGenMemOpsCopyBound(void *dst_base, kd_usize_t dst_base_sz, kd_usize_t *copied_sz, void *src_base, kd_usize_t src_base_sz, kd_usize_t dst_idx, kd_usize_t src_idx, kd_usize_t byte_count);

KDAPI(kd_bool_t) kdGenMemOpsMove(void *dst, void *src, kd_usize_t sz);
KDAPI(kd_bool_t) kdGenMemOpsMoveRegion(void *dst, kd_usize_t dst_sz, kd_usize_t *moved_sz, void *src, kd_usize_t src_sz);
KDAPI(kd_bool_t) kdGenMemOpsMoveBound(void *dst_base, kd_usize_t dst_base_sz, kd_usize_t *moved_sz, void *src_base, kd_usize_t src_base_sz, kd_usize_t dst_idx, kd_usize_t src_idx, kd_usize_t byte_count);

KDAPI(kd_bool_t) kdGenMemOpsConcat(void *dst, kd_usize_t dst_sz, void *src_1, void *src_2, kd_usize_t concat_sz);
KDAPI(kd_bool_t) kdGenMemOpsConcatRegion(void *dst, kd_usize_t dst_sz, kd_usize_t *concat_sz, void *src_1, kd_usize_t src_1_sz, void *src_2, kd_usize_t src_2_sz);
KDAPI(kd_bool_t) kdGenMemOpsConcatBound(void *dst_base, kd_usize_t dst_base_sz, kd_usize_t dst_idx, kd_usize_t *concat_sz, void *src_base_1, kd_usize_t src_base_1_sz, kd_usize_t src_1_begin_idx, kd_usize_t src_1_byte_count, void *src_base_2, kd_usize_t src_base_2_sz, kd_usize_t src_2_begin_idx, kd_usize_t src_2_byte_count);

KDAPI(kd_bool_t) kdGenMemOpsSetBytes(void *dst, kd_usize_t dst_sz, kd_byte_t val);
KDAPI(kd_bool_t) kdGenMemOpsSetBytesBound(void *base, kd_usize_t base_sz, kd_usize_t *set_sz, kd_usize_t begin_idx, kd_usize_t count, kd_byte_t val);

#define kdGenMemOpsSetZerosBytes(dst, sz)                                      kdGenMemOpsSetBytes((dst), (sz), 0)
#define kdGenMemOpsSetZerosBytesBound(base, base_sz, set_sz, begin_idx, count) kdGenMemOpsSetBytesBound((base), (base_sz), (set_sz), (begin_idx), (count), 0)

#define kdGenMemOpsSetOnesBytes(dst, sz)                                       kdGenMemOpsSetBytes((dst), (sz), 0xFF)
#define kdGenMemOpsSetOnesBytesBound(base, base_sz, set_sz, begin_idx, count)  kdGenMemOpsSetBytesBound((base), (base_sz), (set_sz), (begin_idx), (count), 0xFF)

KDAPI(kd_bool_t) kdGenMemOpsSetBlocks(void *dst, kd_usize_t dst_sz, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsSetBlocksBound(void *base, kd_usize_t base_sz, kd_usize_t *set_sz, kd_usize_t begin_idx, kd_usize_t byte_count, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsReverseBytes(void *ptr, kd_usize_t sz);
KDAPI(kd_bool_t) kdGenMemOpsReverseBytesBound(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t count);

KDAPI(kd_bool_t) kdGenMemOpsReverseBlocks(void *ptr, kd_usize_t ptr_sz, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsReverseBlocksBound(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t byte_count, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsInnerSwapBytes(void *ptr, kd_usize_t idx_1, kd_usize_t idx_2);
KDAPI(kd_bool_t) kdGenMemOpsInnerSwapBytesBound(void *base, kd_usize_t base_sz, kd_usize_t idx_1, kd_usize_t idx_2);

KDAPI(kd_bool_t) kdGenMemOpsInnerSwapBlocks(void *ptr, kd_usize_t idx_1, kd_usize_t idx_2, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsInnerSwapBlocksBound(void *base, kd_usize_t base_sz, kd_usize_t idx_1, kd_usize_t idx_2, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsSwapBytes(void *ptr_1, void *ptr_2);
KDAPI(kd_bool_t) kdGenMemOpsSwapBytesBound(void *base_1, kd_usize_t base_1_sz, kd_usize_t base_1_idx, void *base_2, kd_usize_t base_2_sz, kd_usize_t base_2_idx);

KDAPI(kd_bool_t) kdGenMemOpsSwapBlocks(void *ptr_1, void *ptr_2, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsSwapBlocksBound(void *base_1, kd_usize_t base_1_sz, kd_usize_t base_1_idx, void *base_2, kd_usize_t base_2_sz, kd_usize_t base_2_idx, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsRotateRight(void *ptr, kd_usize_t sz, kd_usize_t k);
KDAPI(kd_bool_t) kdGenMemOpsRotateRightBound(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t byte_count, kd_usize_t k);

KDAPI(kd_bool_t) kdGenMemOpsRotateLeft(void *ptr, kd_usize_t sz, kd_usize_t k);
KDAPI(kd_bool_t) kdGenMemOpsRotateLeftBound(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t byte_count, kd_usize_t k);

KDAPI(kd_bool_t) kdGenMemOpsIsEqual(kd_bool_t *result, void *ptr_1, void *ptr_2, kd_usize_t sz);
KDAPI(kd_bool_t) kdGenMemOpsIsEqualRegion(kd_bool_t *result, void *ptr_1, kd_usize_t ptr_1_sz, void *ptr_2, kd_usize_t ptr_2_sz);
KDAPI(kd_bool_t) kdGenMemOpsIsEqualBound(kd_bool_t *result, void *base_1, kd_usize_t base_1_sz, kd_usize_t base_1_idx, void *base_2, kd_usize_t base_2_sz, kd_usize_t base_2_idx, kd_usize_t byte_count);

KDAPI(kd_bool_t) kdGenMemOpsIsBytes(kd_bool_t *result, void *ptr, kd_usize_t sz, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsIsBytesBound(kd_bool_t *result, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t byte_count, kd_byte_t item);

KDAPI(kd_bool_t) kdGenMemOpsIsBlocks(kd_bool_t *result, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsIsBlocksBound(kd_bool_t *result, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t byte_count, void *block, kd_usize_t block_sz);

#define kdGenMemOpsIsZeros(result, ptr, sz)                                   kdGenMemOpsIsBytes((result), (ptr), (sz), PBYTE_C(0))
#define kdGenMemOpsIsZerosBound(result, base, base_sz, begin_idx, byte_count) kdGenMemOpsIsBytesBound((result), (base), (base_sz), (begin_idx), (byte_count), PBYTE_C(0))

#define kdGenMemOpsIsOnes(result, ptr, sz)                                    kdGenMemOpsIsBytes((result), (ptr), (sz), PBYTE_C(0xFF))
#define kdGenMemOpsIsOnesBound(result, base, base_sz, begin_idx, byte_count)  kdGenMemOpsIsBytesBound((result), (base), (base_sz), (begin_idx), (byte_count), PBYTE_C(0xFF))

KDAPI(kd_bool_t) kdGenMemOpsHasPrefix(kd_bool_t *result, void *ptr, kd_usize_t ptr_sz, void *prefix, kd_usize_t prefix_sz);
KDAPI(kd_bool_t) kdGenMemOpsHasSuffix(kd_bool_t *result, void *ptr, kd_usize_t ptr_sz, void *suffix, kd_usize_t suffix_sz);

KDAPI(kd_bool_t) kdGenMemOpsRegionOverlap(kd_bool_t *result, void *ptr_1, kd_usize_t ptr_1_sz, void *ptr_2, kd_usize_t ptr_2_sz);
KDAPI(kd_bool_t) kdGenMemOpsRegionContains(kd_bool_t *result, void *base, kd_usize_t base_sz, void *ptr, kd_usize_t ptr_sz);

KDAPI(kd_bool_t) kdGenMemOpsCheckBounds(kd_usize_t total_sz, kd_usize_t offset, kd_usize_t sz);
KDAPI(kd_bool_t) kdGenMemOpsGetOffsetChecked(void *dst_addr, void *base, kd_usize_t base_sz, kd_usize_t offset, kd_usize_t sz);

KDAPI(kd_bool_t) kdGenMemOpsElemCountFromBytes(kd_usize_t *count, kd_usize_t base_sz, kd_usize_t elem_sz);

KDAPI(kd_bool_t) kdGenMemOpsByteAt(void *dst, void *base, kd_usize_t base_sz, kd_usize_t idx);
KDAPI(kd_bool_t) kdGenMemOpsBlockAt(void *dst, void *base, kd_usize_t base_sz, kd_usize_t idx, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsSetByteAt(void *base, kd_usize_t base_sz, kd_usize_t idx, kd_byte_t val);
KDAPI(kd_bool_t) kdGenMemOpsSetBlockAt(void *base, kd_usize_t base_sz, kd_usize_t idx, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsInsertByteAt(void *base, kd_usize_t base_cap, kd_usize_t *base_elems, kd_usize_t idx, kd_byte_t val, kd_bool_t truncate);
KDAPI(kd_bool_t) kdGenMemOpsInsertBlockAt(void *base, kd_usize_t base_cap, kd_usize_t *base_elems, kd_usize_t idx, void *block, kd_usize_t block_sz, kd_bool_t truncate);

KDAPI(kd_bool_t) kdGenMemOpsRemoveByteAt(void *base, kd_usize_t base_cap, kd_usize_t *base_elems, kd_usize_t idx);
KDAPI(kd_bool_t) kdGenMemOpsRemoveBlockAt(void *base, kd_usize_t base_cap, kd_usize_t *base_elems, kd_usize_t idx, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsCountBytes(kd_usize_t *count, void *ptr, kd_usize_t sz, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsCountBlocks(kd_usize_t *count, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsCountBytesBound(kd_usize_t *count, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsCountBlocksBound(kd_usize_t *count, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count_byte, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsCountNotBytes(kd_usize_t *count, void *ptr, kd_usize_t sz, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsCountNotBlocks(kd_usize_t *count, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsCountNotBytesBound(kd_usize_t *count, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsCountNotBlocksBound(kd_usize_t *count, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count_byte, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindByteIndex(kd_usize_t *idx, void *ptr, kd_usize_t sz, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindBlockIndex(kd_usize_t *idx, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindNotByteIndex(kd_usize_t *idx, void *ptr, kd_usize_t sz, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindNotBlockIndex(kd_usize_t *idx, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindByteIndexBound(kd_usize_t *idx, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindBlockIndexBound(kd_usize_t *idx, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count_byte, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindNotByteIndexBound(kd_usize_t *idx, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindNotBlockIndexBound(kd_usize_t *idx, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count_byte, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindLastByteIndex(kd_usize_t *idx, void *ptr, kd_usize_t sz, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindLastBlockIndex(kd_usize_t *idx, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindLastNotByteIndex(kd_usize_t *idx, void *ptr, kd_usize_t sz, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindLastNotBlockIndex(kd_usize_t *idx, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindLastByteIndexBound(kd_usize_t *idx, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindLastBlockIndexBound(kd_usize_t *idx, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count_byte, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindLastNotByteIndexBound(kd_usize_t *idx, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindLastNotBlockIndexBound(kd_usize_t *idx, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count_byte, void *block, kd_usize_t block_sz);

/* Test regeneration done. */

KDAPI(kd_bool_t) kdGenMemOpsFindByteIndicesU8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindByteIndicesU16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindByteIndicesU32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, kd_byte_t item);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_bool_t) kdGenMemOpsFindByteIndicesU64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, kd_byte_t item);
#endif

KDAPI(kd_bool_t) kdGenMemOpsFindBlockIndicesU8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindBlockIndicesU16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindBlockIndicesU32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_bool_t) kdGenMemOpsFindBlockIndicesU64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);
#endif

KDAPI(kd_bool_t) kdGenMemOpsFindNotByteIndicesU8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindNotByteIndicesU16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindNotByteIndicesU32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, kd_byte_t item);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_bool_t) kdGenMemOpsFindNotByteIndicesU64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, kd_byte_t item);
#endif

KDAPI(kd_bool_t) kdGenMemOpsFindNotBlockIndicesU8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindNotBlockIndicesU16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindNotBlockIndicesU32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_bool_t) kdGenMemOpsFindNotBlockIndicesU64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);
#endif

KDAPI(kd_bool_t) kdGenMemOpsFindByteIndices(kd_usize_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindBlockIndices(kd_usize_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindNotByteIndices(kd_usize_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindNotBlockIndices(kd_usize_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);

/* ...refactoring code. */

KDAPI(kd_bool_t) kdGenMemOpsFindByteIndicesBoundU8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindByteIndicesBoundU16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindByteIndicesBoundU32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_byte_t item);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_bool_t) kdGenMemOpsFindByteIndicesBoundU64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_byte_t item);
#endif

KDAPI(kd_bool_t) kdGenMemOpsFindBlockIndicesBoundU8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count_byte, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindBlockIndicesBoundU16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count_byte, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindBlockIndicesBoundU32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count_byte, void *block, kd_usize_t block_sz);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_bool_t) kdGenMemOpsFindBlockIndicesBoundU64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count_byte, void *block, kd_usize_t block_sz);
#endif

KDAPI(kd_bool_t) kdGenMemOpsFindNotByteIndicesBoundU8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindNotByteIndicesBoundU16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindNotByteIndicesBoundU32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_byte_t item);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_bool_t) kdGenMemOpsFindNotByteIndicesBoundU64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_byte_t item);
#endif

KDAPI(kd_bool_t) kdGenMemOpsFindNotBlockIndicesBoundU8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count_byte, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindNotBlockIndicesBoundU16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count_byte, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindNotBlockIndicesBoundU32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count_byte, void *block, kd_usize_t block_sz);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_bool_t) kdGenMemOpsFindNotBlockIndicesBoundU64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count_byte, void *block, kd_usize_t block_sz);
#endif

KDAPI(kd_bool_t) kdGenMemOpsFindByteIndicesBound(kd_usize_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindBlockIndicesBound(kd_usize_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindNotByteIndicesBound(kd_usize_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count_byte, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindNotBlockIndicesBound(kd_usize_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count_byte, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsReplaceByte(void *ptr, kd_usize_t sz, kd_byte_t find_item, kd_byte_t new_item);
KDAPI(kd_bool_t) kdGenMemOpsReplaceBlock(void *ptr, kd_usize_t ptr_sz, void *find_block, void *new_block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsReplaceNotByte(void *ptr, kd_usize_t sz, kd_byte_t find_item, kd_byte_t new_item);
KDAPI(kd_bool_t) kdGenMemOpsReplaceNotBlock(void *ptr, kd_usize_t ptr_sz, void *find_block, void *new_block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsReplaceByteBound(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, kd_byte_t find_item, kd_byte_t new_item);
KDAPI(kd_bool_t) kdGenMemOpsReplaceBlockBound(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, void *find_block, void *new_block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsReplaceNotByteBound(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_byte_t find_item, kd_byte_t new_item);
KDAPI(kd_bool_t) kdGenMemOpsReplaceNotBlockBound(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count_byte, void *find_block, void *new_block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsReplaceLastByte(void *ptr, kd_usize_t sz, kd_byte_t find_item, kd_byte_t new_item);
KDAPI(kd_bool_t) kdGenMemOpsReplaceLastBlock(void *ptr, kd_usize_t ptr_sz, void *find_block, void *new_block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsReplaceLastNotByte(void *ptr, kd_usize_t sz, kd_byte_t find_item, kd_byte_t new_item);
KDAPI(kd_bool_t) kdGenMemOpsReplaceLastNotBlock(void *ptr, kd_usize_t ptr_sz, void *find_block, void *new_block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsReplaceLastByteBound(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, kd_byte_t find_item, kd_byte_t new_item);
KDAPI(kd_bool_t) kdGenMemOpsReplaceLastBlockBound(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, void *find_block, void *new_block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsReplaceLastNotByteBound(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_byte_t find_item, kd_byte_t new_item);
KDAPI(kd_bool_t) kdGenMemOpsReplaceLastNotBlockBound(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count_byte, void *find_block, void *new_block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsReplaceAllBytes(void *ptr, kd_usize_t sz, kd_usize_t *count, kd_byte_t find_item, kd_byte_t new_item);
KDAPI(kd_bool_t) kdGenMemOpsReplaceAllBlocks(void *ptr, kd_usize_t ptr_sz, kd_usize_t *byte_count, void *find_block, void *new_block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsReplaceAllNotBytes(void *ptr, kd_usize_t sz, kd_usize_t *count, kd_byte_t find_item, kd_byte_t new_item);
KDAPI(kd_bool_t) kdGenMemOpsReplaceAllNotBlocks(void *ptr, kd_usize_t ptr_sz, kd_usize_t *byte_count, void *find_block, void *new_block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsReplaceAllBytesBound(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, kd_usize_t *count, kd_byte_t find_item, kd_byte_t new_item);
KDAPI(kd_bool_t) kdGenMemOpsReplaceAllBlocksBound(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, kd_usize_t *byte_count, void *find_block, void *new_block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsReplaceAllNotBytesBound(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_usize_t *count, kd_byte_t find_item, kd_byte_t new_item);
KDAPI(kd_bool_t) kdGenMemOpsReplaceAllNotBlocksBound(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count_byte, kd_usize_t *byte_count, void *find_block, void *new_block, kd_usize_t block_sz);

/* --- */

KDAPI(kd_bool_t) kdGenMemOpsFindIndexPredicate(kd_usize_t *idx, void *ptr, kd_usize_t ptr_sz, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
KDAPI(kd_bool_t) kdGenMemOpsFindIndexBoundPredicate(kd_usize_t *idx, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));

KDAPI(kd_bool_t) kdGenMemOpsFindLastIndexPredicate(kd_usize_t *idx, void *ptr, kd_usize_t ptr_sz, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
KDAPI(kd_bool_t) kdGenMemOpsFindLastIndexBoundPredicate(kd_usize_t *idx, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));

KDAPI(kd_bool_t) kdGenMemOpsFindIndicesPredicateU8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
KDAPI(kd_bool_t) kdGenMemOpsFindIndicesPredicateU16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
KDAPI(kd_bool_t) kdGenMemOpsFindIndicesPredicateU32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_bool_t) kdGenMemOpsFindIndicesPredicateU64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
#endif

KDAPI(kd_bool_t) kdGenMemOpsFindIndicesPredicate(kd_usize_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));

KDAPI(kd_bool_t) kdGenMemOpsFindIndicesBoundPredicateU8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
KDAPI(kd_bool_t) kdGenMemOpsFindIndicesBoundPredicateU16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
KDAPI(kd_bool_t) kdGenMemOpsFindIndicesBoundPredicateU32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_bool_t) kdGenMemOpsFindIndicesBoundPredicateU64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
#endif

KDAPI(kd_bool_t) kdGenMemOpsFindIndicesBoundPredicate(kd_usize_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));

KDAPI(kd_bool_t) kdGenMemOpsFindPredicate(void *dst, void *ptr, kd_usize_t ptr_sz, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
KDAPI(kd_bool_t) kdGenMemOpsFindBoundPredicate(void *dst, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));

KDAPI(kd_bool_t) kdGenMemOpsFindLastPredicate(void *dst, void *ptr, kd_usize_t ptr_sz, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
KDAPI(kd_bool_t) kdGenMemOpsFindLastBoundPredicate(void *dst, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));

KDAPI(kd_bool_t) kdGenMemOpsFindAllPredicate(void *dst, kd_usize_t dst_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
KDAPI(kd_bool_t) kdGenMemOpsFindAllBoundPredicate(void *dst, kd_usize_t dst_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));

KDAPI(kd_bool_t) kdGenMemOpsReplacePredicate(void *ptr, kd_usize_t ptr_sz, void *new_block, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
KDAPI(kd_bool_t) kdGenMemOpsReplaceBoundPredicate(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, void *new_block, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));

KDAPI(kd_bool_t) kdGenMemOpsReplaceLastPredicate(void *ptr, kd_usize_t ptr_sz, void *new_block, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
KDAPI(kd_bool_t) kdGenMemOpsReplaceLastBoundPredicate(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, void *new_block, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));

KDAPI(kd_bool_t) kdGenMemOpsReplaceAllPredicate(void *ptr, kd_usize_t ptr_sz, kd_usize_t *byte_count, void *new_block, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
KDAPI(kd_bool_t) kdGenMemOpsReplaceAllBoundPredicate(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_usize_t *byte_count, void *new_block, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));

/* --- */

KDAPI(kd_bool_t) kdGenMemOpsSequenceAt(void *dst, kd_usize_t dst_sz, void *ptr, kd_usize_t ptr_sz, kd_usize_t idx);
KDAPI(kd_bool_t) kdGenMemOpsSetSequenceAt(void *dst, kd_usize_t dst_sz, kd_usize_t idx, void *seq, kd_usize_t seq_sz);
KDAPI(kd_bool_t) kdGenMemOpsInsertSequenceAt(void *ptr, kd_usize_t ptr_cap, kd_usize_t *ptr_elems, kd_usize_t idx, void *seq, kd_usize_t seq_sz);
KDAPI(kd_bool_t) kdGenMemOpsRemoveSequenceAt(void *ptr, kd_usize_t ptr_cap, kd_usize_t *ptr_elems, kd_usize_t idx, kd_usize_t seq_sz);

KDAPI(kd_bool_t) kdGenMemOpsSwapSequence(void *ptr, kd_usize_t idx_1, kd_usize_t end_count_1, kd_usize_t idx_2, kd_usize_t end_count_2, void *temp_buf, kd_usize_t temp_buf_sz);
KDAPI(kd_bool_t) kdGenMemOpsSwapSequenceBound(void *base, kd_usize_t base_sz, kd_usize_t idx_1, kd_usize_t end_count_1, kd_usize_t idx_2, kd_usize_t end_count_2, void *temp_buf, kd_usize_t temp_buf_sz);

KDAPI(kd_bool_t) kdGenMemOpsCountSequences(kd_usize_t *byte_count, void *ptr, kd_usize_t ptr_sz, void *seq, kd_usize_t seq_sz);
KDAPI(kd_bool_t) kdGenMemOpsCountSequencesBound(kd_usize_t *byte_count, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, void *seq, kd_usize_t seq_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindSequenceIndex(kd_usize_t *idx, void *ptr, kd_usize_t ptr_sz, void *seq, kd_usize_t seq_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindSequenceIndexBound(kd_usize_t *idx, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, void *seq, kd_usize_t seq_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindLastSequenceIndex(kd_usize_t *idx, void *ptr, kd_usize_t ptr_sz, void *seq, kd_usize_t seq_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindLastSequenceIndexBound(kd_usize_t *idx, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, void *seq, kd_usize_t seq_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindSequenceIndicesU8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, void *seq, kd_usize_t seq_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindSequenceIndicesU16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, void *seq, kd_usize_t seq_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindSequenceIndicesU32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, void *seq, kd_usize_t seq_sz);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_bool_t) kdGenMemOpsFindSequenceIndicesU64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, void *seq, kd_usize_t seq_sz);
#endif

KDAPI(kd_bool_t) kdGenMemOpsFindSequenceIndicesBoundU8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, void *seq, kd_usize_t seq_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindSequenceIndicesBoundU16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, void *seq, kd_usize_t seq_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindSequenceIndicesBoundU32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, void *seq, kd_usize_t seq_sz);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_bool_t) kdGenMemOpsFindSequenceIndicesBoundU64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, void *seq, kd_usize_t seq_sz);
#endif

KDAPI(kd_bool_t) kdGenMemOpsFindSequenceIndices(kd_usize_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, void *seq, kd_usize_t seq_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindSequenceIndicesBound(kd_usize_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, void *seq, kd_usize_t seq_sz);

KDAPI(kd_bool_t) kdGenMemOpsReplaceSequence(void *ptr, kd_usize_t ptr_sz, void *find_seq, kd_usize_t find_seq_sz, void *new_seq, kd_usize_t new_seq_sz);
KDAPI(kd_bool_t) kdGenMemOpsReplaceSequenceBound(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, void *find_seq, kd_usize_t find_seq_sz, void *new_seq, kd_usize_t new_seq_sz);

KDAPI(kd_bool_t) kdGenMemOpsReplaceAllSequences(void *ptr, kd_usize_t ptr_sz, kd_usize_t *byte_count, void *find_seq, kd_usize_t find_seq_sz, void *new_seq, kd_usize_t new_seq_sz);
KDAPI(kd_bool_t) kdGenMemOpsReplaceAllSequencesBound(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_usize_t *byte_count, void *find_seq, kd_usize_t find_seq_sz, void *new_seq, kd_usize_t new_seq_sz);

/* --- */

#define GenMemOpsCopy                       kdGenMemOpsCopy
#define GenMemOpsCopyRegion                 kdGenMemOpsCopyRegion
#define GenMemOpsCopyBound                  kdGenMemOpsCopyBound

#define GenMemOpsMove                       kdGenMemOpsMove
#define GenMemOpsMoveRegion                 kdGenMemOpsMoveRegion
#define GenMemOpsMoveBound                  kdGenMemOpsMoveBound

#define GenMemOpsConcat                     kdGenMemOpsConcat
#define GenMemOpsConcatRegion               kdGenMemOpsConcatRegion
#define GenMemOpsConcatBound                kdGenMemOpsConcatBound

#define GenMemOpsSetBytes                   kdGenMemOpsSetBytes
#define GenMemOpsSetBytesBound              kdGenMemOpsSetBytesBound

#define GenMemOpsSetZerosBytes              kdGenMemOpsSetZerosBytes
#define GenMemOpsSetZerosBytesBound         kdGenMemOpsSetZerosBytesBound

#define GenMemOpsSetOnesBytes               kdGenMemOpsSetOnesBytes
#define GenMemOpsSetOnesBytesBound          kdGenMemOpsSetOnesBytesBound

#define GenMemOpsSetBlocks                  kdGenMemOpsSetBlocks
#define GenMemOpsSetBlocksBound             kdGenMemOpsSetBlocksBound

#define GenMemOpsReverseBytes               kdGenMemOpsReverseBytes
#define GenMemOpsReverseBytesBound          kdGenMemOpsReverseBytesBound

#define GenMemOpsReverseBlocks              kdGenMemOpsReverseBlocks
#define GenMemOpsReverseBlocksBound         kdGenMemOpsReverseBlocksBound

#define GenMemOpsRotateRight                kdGenMemOpsRotateRight
#define GenMemOpsRotateRightBound           kdGenMemOpsRotateRightBound

#define GenMemOpsRotateLeft                 kdGenMemOpsRotateLeft
#define GenMemOpsRotateLeftBound            kdGenMemOpsRotateLeftBound

#define GenMemOpsInnerSwapBytes             kdGenMemOpsInnerSwapBytes
#define GenMemOpsInnerSwapBytesBound        kdGenMemOpsInnerSwapBytesBound

#define GenMemOpsInnerSwapBlocks            kdGenMemOpsInnerSwapBlocks
#define GenMemOpsInnerSwapBlocksBound       kdGenMemOpsInnerSwapBlocksBound

#define GenMemOpsSwapBytes                  kdGenMemOpsSwapBytes
#define GenMemOpsSwapBytesBound             kdGenMemOpsSwapBytesBound

#define GenMemOpsSwapBlocks                 kdGenMemOpsSwapBlocks
#define GenMemOpsSwapBlocksBound            kdGenMemOpsSwapBlocksBound

#define GenMemOpsIsEqual                    kdGenMemOpsIsEqual
#define GenMemOpsIsEqualRegion              kdGenMemOpsIsEqualRegion
#define GenMemOpsIsEqualBound               kdGenMemOpsIsEqualBound

#define GenMemOpsIsBytes                    kdGenMemOpsIsBytes
#define GenMemOpsIsBytesBound               kdGenMemOpsIsBytesBound

#define GenMemOpsIsBlocks                   kdGenMemOpsIsBlocks
#define GenMemOpsIsBlocksBound              kdGenMemOpsIsBlocksBound

#define GenMemOpsIsZeros                    kdGenMemOpsIsZeros
#define GenMemOpsIsZerosBound               kdGenMemOpsIsZerosBound

#define GenMemOpsIsOnes                     kdGenMemOpsIsOnes
#define GenMemOpsIsOnesBound                kdGenMemOpsIsOnesBound

#define GenMemOpsHasPrefix                  kdGenMemOpsHasPrefix
#define GenMemOpsHasSuffix                  kdGenMemOpsHasSuffix

#define GenMemOpsRegionOverlap              kdGenMemOpsRegionOverlap
#define GenMemOpsRegionContains             kdGenMemOpsRegionContains

#define GenMemOpsGetOffsetChecked           kdGenMemOpsGetOffsetChecked
#define GenMemOpsCheckBounds                kdGenMemOpsCheckBounds

#define GenMemOpsElemCountFromBytes         kdGenMemOpsElemCountFromBytes

#define GenMemOpsByteAt                     kdGenMemOpsByteAt
#define GenMemOpsBlockAt                    kdGenMemOpsBlockAt

#define GenMemOpsSetByteAt                  kdGenMemOpsSetByteAt
#define GenMemOpsSetBlockAt                 kdGenMemOpsSetBlockAt

#define GenMemOpsInsertByteAt               kdGenMemOpsInsertByteAt
#define GenMemOpsInsertBlockAt              kdGenMemOpsInsertBlockAt

#define GenMemOpsRemoveByteAt               kdGenMemOpsRemoveByteAt
#define GenMemOpsRemoveBlockAt              kdGenMemOpsRemoveBlockAt

#define GenMemOpsRemoveBytes                kdGenMemOpsRemoveBytes
#define GenMemOpsRemoveBlocks               kdGenMemOpsRemoveBlocks

#define GenMemOpsCountBytes                 kdGenMemOpsCountBytes
#define GenMemOpsCountBlocks                kdGenMemOpsCountBlocks
#define GenMemOpsCountBytesBound            kdGenMemOpsCountBytesBound
#define GenMemOpsCountBlocksBound           kdGenMemOpsCountBlocksBound

#define GenMemOpsCountNotBytes              kdGenMemOpsCountNotBytes
#define GenMemOpsCountNotBlocks             kdGenMemOpsCountNotBlocks
#define GenMemOpsCountNotBytesBound         kdGenMemOpsCountNotBytesBound
#define GenMemOpsCountNotBlocksBound        kdGenMemOpsCountNotBlocksBound

#define GenMemOpsFindByteIndex              kdGenMemOpsFindByteIndex
#define GenMemOpsFindBlockIndex             kdGenMemOpsFindBlockIndex

#define GenMemOpsFindNotByteIndex           kdGenMemOpsFindNotByteIndex
#define GenMemOpsFindNotBlockIndex          kdGenMemOpsFindNotBlockIndex

#define GenMemOpsFindByteIndexBound         kdGenMemOpsFindByteIndexBound
#define GenMemOpsFindBlockIndexBound        kdGenMemOpsFindBlockIndexBound

#define GenMemOpsFindNotByteIndexBound      kdGenMemOpsFindNotByteIndexBound
#define GenMemOpsFindNotBlockIndexBound     kdGenMemOpsFindNotBlockIndexBound

#define GenMemOpsFindLastByteIndex          kdGenMemOpsFindLastByteIndex
#define GenMemOpsFindLastBlockIndex         kdGenMemOpsFindLastBlockIndex

#define GenMemOpsFindLastNotByteIndex       kdGenMemOpsFindLastNotByteIndex
#define GenMemOpsFindLastNotBlockIndex      kdGenMemOpsFindLastNotBlockIndex

#define GenMemOpsFindLastByteIndexBound     kdGenMemOpsFindLastByteIndexBound
#define GenMemOpsFindLastBlockIndexBound    kdGenMemOpsFindLastBlockIndexBound

#define GenMemOpsFindLastNotByteIndexBound  kdGenMemOpsFindLastNotByteIndexBound
#define GenMemOpsFindLastNotBlockIndexBound kdGenMemOpsFindLastNotBlockIndexBound

#define GenMemOpsFindByteIndicesU8          kdGenMemOpsFindByteIndicesU8
#define GenMemOpsFindByteIndicesU16         kdGenMemOpsFindByteIndicesU16
#define GenMemOpsFindByteIndicesU32         kdGenMemOpsFindByteIndicesU32
#if defined KD_ARCH_64BIT_INT
    #define GenMemOpsFindByteIndicesU64 kdGenMemOpsFindByteIndicesU64
#endif

#define GenMemOpsFindBlockIndicesU8  kdGenMemOpsFindBlockIndicesU8
#define GenMemOpsFindBlockIndicesU16 kdGenMemOpsFindBlockIndicesU16
#define GenMemOpsFindBlockIndicesU32 kdGenMemOpsFindBlockIndicesU32
#if defined KD_ARCH_64BIT_INT
    #define GenMemOpsFindBlockIndicesU64 kdGenMemOpsFindBlockIndicesU64
#endif

#define GenMemOpsFindNotByteIndicesU8  kdGenMemOpsFindNotByteIndicesU8
#define GenMemOpsFindNotByteIndicesU16 kdGenMemOpsFindNotByteIndicesU16
#define GenMemOpsFindNotByteIndicesU32 kdGenMemOpsFindNotByteIndicesU32
#if defined KD_ARCH_64BIT_INT
    #define GenMemOpsFindNotByteIndicesU64 kdGenMemOpsFindNotByteIndicesU64
#endif

#define GenMemOpsFindNotBlockIndicesU8  kdGenMemOpsFindNotBlockIndicesU8
#define GenMemOpsFindNotBlockIndicesU16 kdGenMemOpsFindNotBlockIndicesU16
#define GenMemOpsFindNotBlockIndicesU32 kdGenMemOpsFindNotBlockIndicesU32
#if defined KD_ARCH_64BIT_INT
    #define GenMemOpsFindNotBlockIndicesU64 kdGenMemOpsFindNotBlockIndicesU64
#endif

#define GenMemOpsFindByteIndices         kdGenMemOpsFindByteIndices
#define GenMemOpsFindBlockIndices        kdGenMemOpsFindBlockIndices

#define GenMemOpsFindNotByteIndices      kdGenMemOpsFindNotByteIndices
#define GenMemOpsFindNotBlockIndices     kdGenMemOpsFindNotBlockIndices

#define GenMemOpsFindByteIndicesBoundU8  kdGenMemOpsFindByteIndicesBoundU8
#define GenMemOpsFindByteIndicesBoundU16 kdGenMemOpsFindByteIndicesBoundU16
#define GenMemOpsFindByteIndicesBoundU32 kdGenMemOpsFindByteIndicesBoundU32
#if defined KD_ARCH_64BIT_INT
    #define GenMemOpsFindByteIndicesBoundU64 kdGenMemOpsFindByteIndicesBoundU64
#endif

#define GenMemOpsFindBlockIndicesBoundU8  kdGenMemOpsFindBlockIndicesBoundU8
#define GenMemOpsFindBlockIndicesBoundU16 kdGenMemOpsFindBlockIndicesBoundU16
#define GenMemOpsFindBlockIndicesBoundU32 kdGenMemOpsFindBlockIndicesBoundU32
#if defined KD_ARCH_64BIT_INT
    #define GenMemOpsFindBlockIndicesBoundU64 kdGenMemOpsFindBlockIndicesBoundU64
#endif

#define GenMemOpsFindNotByteIndicesBoundU8  kdGenMemOpsFindNotByteIndicesBoundU8
#define GenMemOpsFindNotByteIndicesBoundU16 kdGenMemOpsFindNotByteIndicesBoundU16
#define GenMemOpsFindNotByteIndicesBoundU32 kdGenMemOpsFindNotByteIndicesBoundU32
#if defined KD_ARCH_64BIT_INT
    #define GenMemOpsFindNotByteIndicesBoundU64 kdGenMemOpsFindNotByteIndicesBoundU64
#endif

#define GenMemOpsFindNotBlockIndicesBoundU8  kdGenMemOpsFindNotBlockIndicesBoundU8
#define GenMemOpsFindNotBlockIndicesBoundU16 kdGenMemOpsFindNotBlockIndicesBoundU16
#define GenMemOpsFindNotBlockIndicesBoundU32 kdGenMemOpsFindNotBlockIndicesBoundU32
#if defined KD_ARCH_64BIT_INT
    #define GenMemOpsFindNotBlockIndicesBoundU64 kdGenMemOpsFindNotBlockIndicesBoundU64
#endif

#define GenMemOpsFindByteIndicesBound        kdGenMemOpsFindByteIndicesBound
#define GenMemOpsFindBlockIndicesBound       kdGenMemOpsFindBlockIndicesBound

#define GenMemOpsFindNotByteIndicesBound     kdGenMemOpsFindNotByteIndicesBound
#define GenMemOpsFindNotBlockIndicesBound    kdGenMemOpsFindNotBlockIndicesBound

#define GenMemOpsReplaceByte                 kdGenMemOpsReplaceByte
#define GenMemOpsReplaceBlock                kdGenMemOpsReplaceBlock

#define GenMemOpsReplaceNotByte              kdGenMemOpsReplaceNotByte
#define GenMemOpsReplaceNotBlock             kdGenMemOpsReplaceNotBlock

#define GenMemOpsReplaceNotByteBound         kdGenMemOpsReplaceNotByteBound
#define GenMemOpsReplaceNotBlockBound        kdGenMemOpsReplaceNotBlockBound

#define GenMemOpsReplaceByteBound            kdGenMemOpsReplaceByteBound
#define GenMemOpsReplaceBlockBound           kdGenMemOpsReplaceBlockBound

#define GenMemOpsReplaceLastByte             kdGenMemOpsReplaceLastByte
#define GenMemOpsReplaceLastBlock            kdGenMemOpsReplaceLastBlock

#define GenMemOpsReplaceLastNotByte          kdGenMemOpsReplaceLastNotByte
#define GenMemOpsReplaceLastNotBlock         kdGenMemOpsReplaceLastNotBlock

#define GenMemOpsReplaceLastByteBound        kdGenMemOpsReplaceLastByteBound
#define GenMemOpsReplaceLastBlockBound       kdGenMemOpsReplaceLastBlockBound

#define GenMemOpsReplaceLastNotByteBound     kdGenMemOpsReplaceLastNotByteBound
#define GenMemOpsReplaceLastNotBlockBound    kdGenMemOpsReplaceLastNotBlockBound

#define GenMemOpsReplaceAllBytes             kdGenMemOpsReplaceAllBytes
#define GenMemOpsReplaceAllBlocks            kdGenMemOpsReplaceAllBlocks

#define GenMemOpsReplaceAllNotBytes          kdGenMemOpsReplaceAllNotBytes
#define GenMemOpsReplaceAllNotBlocks         kdGenMemOpsReplaceAllNotBlocks

#define GenMemOpsReplaceAllBytesBound        kdGenMemOpsReplaceAllBytesBound
#define GenMemOpsReplaceAllBlocksBound       kdGenMemOpsReplaceAllBlocksBound

#define GenMemOpsReplaceAllNotBytesBound     kdGenMemOpsReplaceAllNotBytesBound
#define GenMemOpsReplaceAllNotBlocksBound    kdGenMemOpsReplaceAllNotBlocksBound

#define GenMemOpsFindIndexPredicate          kdGenMemOpsFindIndexPredicate
#define GenMemOpsFindIndexBoundPredicate     kdGenMemOpsFindIndexBoundPredicate

#define GenMemOpsFindLastIndexPredicate      kdGenMemOpsFindLastIndexPredicate
#define GenMemOpsFindLastIndexBoundPredicate kdGenMemOpsFindLastIndexBoundPredicate

#define GenMemOpsFindIndicesPredicateU8      kdGenMemOpsFindIndicesPredicateU8
#define GenMemOpsFindIndicesPredicateU16     kdGenMemOpsFindIndicesPredicateU16
#define GenMemOpsFindIndicesPredicateU32     kdGenMemOpsFindIndicesPredicateU32
#if defined KD_ARCH_64BIT_INT
    #define GenMemOpsFindIndicesPredicateU64 kdGenMemOpsFindIndicesPredicateU64
#endif

#define GenMemOpsFindIndicesPredicate         kdGenMemOpsFindIndicesPredicate

#define GenMemOpsFindIndicesBoundPredicateU8  kdGenMemOpsFindIndicesBoundPredicateU8
#define GenMemOpsFindIndicesBoundPredicateU16 kdGenMemOpsFindIndicesBoundPredicateU16
#define GenMemOpsFindIndicesBoundPredicateU32 kdGenMemOpsFindIndicesBoundPredicateU32
#if defined KD_ARCH_64BIT_INT
    #define GenMemOpsFindIndicesBoundPredicateU64 kdGenMemOpsFindIndicesBoundPredicateU64
#endif

#define GenMemOpsFindIndicesBoundPredicate  kdGenMemOpsFindIndicesBoundPredicate

#define GenMemOpsFindPredicate              kdGenMemOpsFindPredicate
#define GenMemOpsFindBoundPredicate         kdGenMemOpsFindBoundPredicate

#define GenMemOpsFindLastPredicate          kdGenMemOpsFindLastPredicate
#define GenMemOpsFindLastBoundPredicate     kdGenMemOpsFindLastBoundPredicate

#define GenMemOpsFindAllPredicate           kdGenMemOpsFindAllPredicate
#define GenMemOpsFindAllBoundPredicate      kdGenMemOpsFindAllBoundPredicate

#define GenMemOpsReplacePredicate           kdGenMemOpsReplacePredicate
#define GenMemOpsReplaceBoundPredicate      kdGenMemOpsReplaceBoundPredicate

#define GenMemOpsReplaceLastPredicate       kdGenMemOpsReplaceLastPredicate
#define GenMemOpsReplaceLastBoundPredicate  kdGenMemOpsReplaceLastBoundPredicate

#define GenMemOpsReplaceAllPredicate        kdGenMemOpsReplaceAllPredicate
#define GenMemOpsReplaceAllBoundPredicate   kdGenMemOpsReplaceAllBoundPredicate

#define GenMemOpsSequenceAt                 kdGenMemOpsSequenceAt
#define GenMemOpsSetSequenceAt              kdGenMemOpsSetSequenceAt
#define GenMemOpsInsertSequenceAt           kdGenMemOpsInsertSequenceAt
#define GenMemOpsRemoveSequenceAt           kdGenMemOpsRemoveSequenceAt

#define GenMemOpsCountSequences             kdGenMemOpsCountSequences
#define GenMemOpsCountSequencesBound        kdGenMemOpsCountSequencesBound

#define GenMemOpsFindSequenceIndex          kdGenMemOpsFindSequenceIndex
#define GenMemOpsFindSequenceIndexBound     kdGenMemOpsFindSequenceIndexBound

#define GenMemOpsFindLastSequenceIndex      kdGenMemOpsFindLastSequenceIndex
#define GenMemOpsFindLastSequenceIndexBound kdGenMemOpsFindLastSequenceIndexBound

#define GenMemOpsFindSequenceIndicesU8      kdGenMemOpsFindSequenceIndicesU8
#define GenMemOpsFindSequenceIndicesU16     kdGenMemOpsFindSequenceIndicesU16
#define GenMemOpsFindSequenceIndicesU32     kdGenMemOpsFindSequenceIndicesU32
#if defined KD_ARCH_64BIT_INT
    #define GenMemOpsFindSequenceIndicesU64 kdGenMemOpsFindSequenceIndicesU64
#endif

#define GenMemOpsFindSequenceIndicesBoundU8  kdGenMemOpsFindSequenceIndicesBoundU8
#define GenMemOpsFindSequenceIndicesBoundU16 kdGenMemOpsFindSequenceIndicesBoundU16
#define GenMemOpsFindSequenceIndicesBoundU32 kdGenMemOpsFindSequenceIndicesBoundU32
#if defined KD_ARCH_64BIT_INT
    #define GenMemOpsFindSequenceIndicesBoundU64 kdGenMemOpsFindSequenceIndicesBoundU64
#endif

#define GenMemOpsFindSequenceIndices      kdGenMemOpsFindSequenceIndices
#define GenMemOpsFindSequenceIndicesBound kdGenMemOpsFindSequenceIndicesBound

#define GenMemOpsReplaceSequence          kdGenMemOpsReplaceSequence
#define GenMemOpsReplaceSequenceBound     kdGenMemOpsReplaceSequenceBound

#define GenMemOpsReplaceAllSequences      kdGenMemOpsReplaceAllSequences
#define GenMemOpsReplaceAllSequencesBound kdGenMemOpsReplaceAllSequencesBound


KD_EXTERN_END


#endif /* KD_GEN_MEM_OPS_H_ */
