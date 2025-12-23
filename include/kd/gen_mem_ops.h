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
KDAPI(kd_bool_t) kdGenMemOpsCopyRange(void *dst_base, kd_usize_t dst_base_sz, kd_usize_t *copied_sz, void *src_base, kd_usize_t src_base_sz, kd_usize_t dst_idx, kd_usize_t src_idx, kd_usize_t byte_count);

KDAPI(kd_bool_t) kdGenMemOpsMove(void *dst, void *src, kd_usize_t sz);
KDAPI(kd_bool_t) kdGenMemOpsMoveRegion(void *dst, kd_usize_t dst_sz, kd_usize_t *moved_sz, void *src, kd_usize_t src_sz);
KDAPI(kd_bool_t) kdGenMemOpsMoveRange(void *dst_base, kd_usize_t dst_base_sz, kd_usize_t *moved_sz, void *src_base, kd_usize_t src_base_sz, kd_usize_t dst_idx, kd_usize_t src_idx, kd_usize_t byte_count);

KDAPI(kd_bool_t) kdGenMemOpsConcat(void *dst, kd_usize_t dst_sz, kd_usize_t *concat_sz, void *src_1, kd_usize_t src_1_sz, void *src_2, kd_usize_t src_2_sz);
KDAPI(kd_bool_t) kdGenMemOpsConcatRange(void *dst_base, kd_usize_t dst_base_sz, kd_usize_t dst_idx, kd_usize_t *concat_sz, void *src_base_1, kd_usize_t src_base_1_sz, kd_usize_t src_1_begin_idx, kd_usize_t src_1_byte_count, void *src_base_2, kd_usize_t src_base_2_sz, kd_usize_t src_2_begin_idx, kd_usize_t src_2_byte_count);

KDAPI(kd_bool_t) kdGenMemOpsSetBytes(void *dst, kd_usize_t dst_sz, kd_byte_t val);
KDAPI(kd_bool_t) kdGenMemOpsSetBytesRange(void *base, kd_usize_t base_sz, kd_usize_t *set_sz, kd_usize_t begin_idx, kd_usize_t count, kd_byte_t val);

#define kdGenMemOpsSetZerosBytes(dst, sz)                                      kdGenMemOpsSetBytes((dst), (sz), 0)
#define kdGenMemOpsSetZerosBytesRange(base, base_sz, set_sz, begin_idx, count) kdGenMemOpsSetBytesRange((base), (base_sz), (set_sz), (begin_idx), (count), 0)

#define kdGenMemOpsSetOnesBytes(dst, sz)                                       kdGenMemOpsSetBytes((dst), (sz), 0xFF)
#define kdGenMemOpsSetOnesBytesRange(base, base_sz, set_sz, begin_idx, count)  kdGenMemOpsSetBytesRange((base), (base_sz), (set_sz), (begin_idx), (count), 0xFF)

KDAPI(kd_bool_t) kdGenMemOpsSetBlocks(void *dst, kd_usize_t dst_sz, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsSetBlocksRange(void *base, kd_usize_t base_sz, kd_usize_t *set_sz, kd_usize_t begin_idx, kd_usize_t byte_count, void *block, kd_usize_t block_sz);

#define kdGenMemOpsFill(dst, dst_sz, sequence, sequence_sz)                               kdGenMemOpsSetBlocks((dst), (dst_sz), (sequence), (sequence_sz))
#define kdGenMemOpsFillRange(base, base_sz, begin_idx, byte_count, sequence, sequence_sz) kdGenMemOpsSetBlocksRange((base), (base_sz), (begin_idx), (byte_count), (sequence), (sequence_sz))

KDAPI(kd_bool_t) kdGenMemOpsReverseBytes(void *ptr, kd_usize_t sz);
KDAPI(kd_bool_t) kdGenMemOpsReverseBytesRange(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t count);

KDAPI(kd_bool_t) kdGenMemOpsReverseBlocks(void *ptr, kd_usize_t ptr_sz, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsReverseBlocksRange(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t byte_count, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsInnerSwapBytes(void *ptr, kd_usize_t idx_1, kd_usize_t idx_2);
KDAPI(kd_bool_t) kdGenMemOpsInnerSwapBytesRange(void *base, kd_usize_t base_sz, kd_usize_t idx_1, kd_usize_t idx_2);

KDAPI(kd_bool_t) kdGenMemOpsInnerSwapBlocks(void *ptr, kd_usize_t idx_1, kd_usize_t idx_2, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsInnerSwapBlocksRange(void *base, kd_usize_t base_sz, kd_usize_t idx_1, kd_usize_t idx_2, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsSwapBytes(void *ptr_1, void *ptr_2);
KDAPI(kd_bool_t) kdGenMemOpsSwapBytesRange(void *base_1, kd_usize_t base_1_sz, kd_usize_t base_1_idx, void *base_2, kd_usize_t base_2_sz, kd_usize_t base_2_idx);

KDAPI(kd_bool_t) kdGenMemOpsSwapBlocks(void *ptr_1, void *ptr_2, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsSwapBlocksRange(void *base_1, kd_usize_t base_1_sz, kd_usize_t base_1_idx, void *base_2, kd_usize_t base_2_sz, kd_usize_t base_2_idx, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsRotateRight(void *ptr, kd_usize_t sz, kd_usize_t k);
KDAPI(kd_bool_t) kdGenMemOpsRotateRightRange(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t byte_count, kd_usize_t k);

KDAPI(kd_bool_t) kdGenMemOpsRotateLeft(void *ptr, kd_usize_t sz, kd_usize_t k);
KDAPI(kd_bool_t) kdGenMemOpsRotateLeftRange(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t byte_count, kd_usize_t k);

KDAPI(kd_bool_t) kdGenMemOpsIsEqual(kd_bool_t *result, void *ptr_1, void *ptr_2, kd_usize_t sz);
KDAPI(kd_bool_t) kdGenMemOpsIsEqualRegion(kd_bool_t *result, void *ptr_1, kd_usize_t ptr_1_sz, void *ptr_2, kd_usize_t ptr_2_sz);
KDAPI(kd_bool_t) kdGenMemOpsIsEqualRange(kd_bool_t *result, void *base_1, kd_usize_t base_1_sz, kd_usize_t base_1_idx, void *base_2, kd_usize_t base_2_sz, kd_usize_t base_2_idx, kd_usize_t byte_count);

KDAPI(kd_bool_t) kdGenMemOpsIsZeros(kd_bool_t *result, void *ptr, kd_usize_t sz);
KDAPI(kd_bool_t) kdGenMemOpsIsZerosRange(kd_bool_t *result, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t byte_count);

KDAPI(kd_bool_t) kdGenMemOpsIsOnes(kd_bool_t *result, void *ptr, kd_usize_t sz);
KDAPI(kd_bool_t) kdGenMemOpsIsOnesRange(kd_bool_t *result, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t byte_count);

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

/*
KDAPI(kd_bool_t) kdGenMemOpsInsertByteAtIndices(void *base, kd_usize_t base_cap, kd_usize_t *base_elems, kd_usize_t *idxs, kd_usize_t idxs_sz, kd_byte_t val, kd_bool_t truncate);
KDAPI(kd_bool_t) kdGenMemOpsInsertBlockAtIndices(void *base, kd_usize_t base_cap, kd_usize_t *base_elems, kd_usize_t *idxs, kd_usize_t idxs_sz, void *block, kd_usize_t block_sz, kd_bool_t truncate);
*/

KDAPI(kd_bool_t) kdGenMemOpsRemoveByteAt(void *base, kd_usize_t base_cap, kd_usize_t *base_elems, kd_usize_t idx);
KDAPI(kd_bool_t) kdGenMemOpsRemoveBlockAt(void *base, kd_usize_t base_cap, kd_usize_t *base_elems, kd_usize_t idx, kd_usize_t block_sz);

/*
KDAPI(kd_bool_t) kdGenMemOpsRemoveBytes(void *base, kd_usize_t base_cap, kd_usize_t *base_elems, kd_usize_t *removed, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsRemoveBlocks(void *base, kd_usize_t base_cap, kd_usize_t *base_elems, kd_usize_t *removed, void *block, kd_usize_t block_sz);
*/

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

KDAPI(kd_bool_t) kdGenMemOpsFindByteIndexRange(kd_usize_t *idx, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindBlockIndexRange(kd_usize_t *idx, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindNotByteIndexBound(kd_usize_t *idx, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindNotBlockIndexBound(kd_usize_t *idx, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count_byte, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindLastByteIndex(kd_usize_t *idx, void *ptr, kd_usize_t sz, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindLastBlockIndex(kd_usize_t *idx, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindLastNotByteIndex(kd_usize_t *idx, void *ptr, kd_usize_t sz, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindLastNotBlockIndex(kd_usize_t *idx, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindLastByteIndexRange(kd_usize_t *idx, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindLastBlockIndexRange(kd_usize_t *idx, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindLastNotByteIndexBound(kd_usize_t *idx, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindLastNotBlockIndexBound(kd_usize_t *idx, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count_byte, void *block, kd_usize_t block_sz);

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

KDAPI(kd_bool_t) kdGenMemOpsFindByteIndicesRangeU8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindByteIndicesRangeU16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindByteIndicesRangeU32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, kd_byte_t item);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_bool_t) kdGenMemOpsFindByteIndicesRangeU64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, kd_byte_t item);
#endif

KDAPI(kd_bool_t) kdGenMemOpsFindBlockIndicesRangeU8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindBlockIndicesRangeU16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindBlockIndicesRangeU32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, void *block, kd_usize_t block_sz);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_bool_t) kdGenMemOpsFindBlockIndicesRangeU64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, void *block, kd_usize_t block_sz);
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

KDAPI(kd_bool_t) kdGenMemOpsFindByteIndicesRange(kd_usize_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindBlockIndicesRange(kd_usize_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindNotByteIndicesBound(kd_usize_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count_byte, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindNotBlockIndicesBound(kd_usize_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count_byte, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsReplaceByte(void *ptr, kd_usize_t sz, kd_byte_t find_item, kd_byte_t new_item);
KDAPI(kd_bool_t) kdGenMemOpsReplaceBlock(void *ptr, kd_usize_t ptr_sz, void *find_block, void *new_block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsReplaceNotByte(void *ptr, kd_usize_t sz, kd_byte_t find_item, kd_byte_t new_item);
KDAPI(kd_bool_t) kdGenMemOpsReplaceNotBlock(void *ptr, kd_usize_t ptr_sz, void *find_block, void *new_block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsReplaceByteRange(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, kd_byte_t find_item, kd_byte_t new_item);
KDAPI(kd_bool_t) kdGenMemOpsReplaceBlockRange(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, void *find_block, void *new_block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsReplaceNotByteBound(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count, kd_byte_t find_item, kd_byte_t new_item);
KDAPI(kd_bool_t) kdGenMemOpsReplaceNotBlockBound(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end_count_byte, void *find_block, void *new_block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsReplaceLastByte(void *ptr, kd_usize_t sz, kd_byte_t find_item, kd_byte_t new_item);
KDAPI(kd_bool_t) kdGenMemOpsReplaceLastBlock(void *ptr, kd_usize_t ptr_sz, void *find_block, void *new_block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsReplaceLastNotByte(void *ptr, kd_usize_t sz, kd_byte_t find_item, kd_byte_t new_item);
KDAPI(kd_bool_t) kdGenMemOpsReplaceLastNotBlock(void *ptr, kd_usize_t ptr_sz, void *find_block, void *new_block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsReplaceLastByteRange(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, kd_byte_t find_item, kd_byte_t new_item);
KDAPI(kd_bool_t) kdGenMemOpsReplaceLastBlockRange(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, void *find_block, void *new_block, kd_usize_t block_sz);

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

KDAPI(kd_bool_t) kdGenMemOpsFindIndexPredicate(kd_usize_t *idx, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
KDAPI(kd_bool_t) kdGenMemOpsFindIndexBoundPredicate(kd_usize_t *idx, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, void *block, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));

KDAPI(kd_bool_t) kdGenMemOpsFindLastIndexPredicate(kd_usize_t *idx, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
KDAPI(kd_bool_t) kdGenMemOpsFindLastIndexBoundPredicate(kd_usize_t *idx, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, void *block, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));

KDAPI(kd_bool_t) kdGenMemOpsFindIndicesPredicateU8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
KDAPI(kd_bool_t) kdGenMemOpsFindIndicesPredicateU16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
KDAPI(kd_bool_t) kdGenMemOpsFindIndicesPredicateU32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_bool_t) kdGenMemOpsFindIndicesPredicateU64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
#endif

KDAPI(kd_bool_t) kdGenMemOpsFindIndicesPredicate(kd_usize_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));

KDAPI(kd_bool_t) kdGenMemOpsFindIndicesBoundPredicateU8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, void *block, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
KDAPI(kd_bool_t) kdGenMemOpsFindIndicesBoundPredicateU16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, void *block, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
KDAPI(kd_bool_t) kdGenMemOpsFindIndicesBoundPredicateU32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, void *block, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_bool_t) kdGenMemOpsFindIndicesBoundPredicateU64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, void *block, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
#endif

KDAPI(kd_bool_t) kdGenMemOpsFindIndicesBoundPredicate(kd_usize_t *idxs, kd_usize_t idxs_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, void *block, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));

KDAPI(kd_bool_t) kdGenMemOpsFindPredicate(void *dst, void *ptr, kd_usize_t ptr_sz, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
KDAPI(kd_bool_t) kdGenMemOpsFindBoundPredicate(void *dst, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));

KDAPI(kd_bool_t) kdGenMemOpsFindLastPredicate(void *dst, void *ptr, kd_usize_t ptr_sz, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
KDAPI(kd_bool_t) kdGenMemOpsFindLastBoundPredicate(void *dst, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));

KDAPI(kd_bool_t) kdGenMemOpsFindAllPredicate(void *dst, kd_usize_t dst_sz, kd_usize_t *found, void *ptr, kd_usize_t ptr_sz, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
KDAPI(kd_bool_t) kdGenMemOpsFindAllBoundPredicate(void *dst, kd_usize_t dst_sz, kd_usize_t *found, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));

KDAPI(kd_bool_t) kdGenMemOpsReplacePredicate(void *ptr, kd_usize_t ptr_sz, void *new_block, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
KDAPI(kd_bool_t) kdGenMemOpsReplaceBoundPredicate(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, void *new_block, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));

KDAPI(kd_bool_t) kdGenMemOpsReplaceLastPredicate(void *ptr, kd_usize_t ptr_sz, void *new_block, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
KDAPI(kd_bool_t) kdGenMemOpsReplaceLastBoundPredicate(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, void *new_block, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));

KDAPI(kd_bool_t) kdGenMemOpsReplaceAllPredicate(void *ptr, kd_usize_t ptr_sz, kd_usize_t *byte_count, void *new_block, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));
KDAPI(kd_bool_t) kdGenMemOpsReplaceAllBoundPredicate(void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t end, kd_usize_t *byte_count, void *new_block, kd_usize_t block_sz, void (*predicate)(kd_bool_t *result, void *block));

/* --- */

KDAPI(kd_bool_t) kdGenMemOpsFindAnyByte(void *dst, void *ptr, kd_usize_t sz, kd_byte_t *set, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindAnyByteIndex(kd_usize_t *idx_addr, void *ptr, kd_usize_t sz, kd_byte_t *set, kd_byte_t item);

KDAPI(kd_bool_t) kdGenMemOpsFindAnyLastByte(void *dst, void *ptr, kd_usize_t sz, kd_byte_t *set, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindAnyLastByteIndex(kd_usize_t *idx_addr, void *ptr, kd_usize_t sz, kd_byte_t *set, kd_byte_t item);

KDAPI(kd_bool_t) kdGenMemOpsFindAnyOfTheBytes(void *dst, kd_usize_t dst_sz, kd_usize_t *dst_elems, void *ptr, kd_usize_t ptr_sz, kd_byte_t *set, kd_byte_t item);

KDAPI(kd_bool_t) kdGenMemOpsSequenceAt(void *dst, void *base, kd_usize_t base_sz, kd_usize_t idx, kd_usize_t sequence_sz);
KDAPI(kd_bool_t) kdGenMemOpsSetSequenceAt(void *base, kd_usize_t base_sz, kd_usize_t idx, void *sequence, kd_usize_t sequence_sz);
KDAPI(kd_bool_t) kdGenMemOpsInsertSequenceAt(void *base, kd_usize_t base_cap, kd_usize_t *base_elems, kd_usize_t idx, void *sequence, kd_usize_t sequence_sz);
KDAPI(kd_bool_t) kdGenMemOpsRemoveSequenceAt(void *base, kd_usize_t base_cap, kd_usize_t *base_elems, kd_usize_t idx, void *sequence, kd_usize_t sequence_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindSequence(kd_usize_t *idx_addr, void *ptr, kd_usize_t ptr_sz, void *sequence, kd_usize_t sequence_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindLastSequence(kd_usize_t *idx_addr, void *ptr, kd_usize_t ptr_sz, void *sequence, kd_usize_t sequence_sz);

KDAPI(kd_bool_t) kdGenMemOpsReplaceSequence(void *ptr, kd_usize_t ptr_capacity, kd_usize_t *ptr_elems, kd_byte_t *find_sequence, kd_usize_t find_sequence_sz, kd_byte_t *new_sequence, kd_usize_t new_sequence_sz);
KDAPI(kd_bool_t) kdGenMemOpsReplaceLastSequence(void *ptr, kd_usize_t ptr_capacity, kd_usize_t *ptr_elems, kd_byte_t *find_sequence, kd_usize_t find_sequence_sz, kd_byte_t *new_sequence, kd_usize_t new_sequence_sz);

KDAPI(kd_bool_t) kdGenMemOpsReplaceAllSequences(kd_usize_t *replaced_byte_count_addr, void *ptr, kd_usize_t ptr_capacity, kd_usize_t *ptr_elems, kd_byte_t *find_sequence, kd_usize_t find_sequence_sz, kd_byte_t *new_sequence, kd_usize_t new_sequence_sz);

KDAPI(kd_bool_t) kdGenMemOpsCountSequences(kd_usize_t *byte_count_addr, void *ptr, kd_usize_t ptr_sz, void *sequence, kd_usize_t sequence_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindSequences(kd_usize_t *idxs, kd_usize_t idxs_sz, kd_usize_t *idx_elems, void *ptr, kd_usize_t ptr_sz, void *sequence, kd_usize_t sequence_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindSequencesU8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_usize_t *idx_elems, void *ptr, kd_usize_t ptr_sz, void *sequence, kd_usize_t sequence_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindSequencesU16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_usize_t *idx_elems, void *ptr, kd_usize_t ptr_sz, void *sequence, kd_usize_t sequence_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindSequencesU32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_usize_t *idx_elems, void *ptr, kd_usize_t ptr_sz, void *sequence, kd_usize_t sequence_sz);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_bool_t) kdGenMemOpsFindSequencesU64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_usize_t *idx_elems, void *ptr, kd_usize_t ptr_sz, void *sequence, kd_usize_t sequence_sz);
#endif

#define GenMemOpsCopy                       kdGenMemOpsCopy
#define GenMemOpsCopyRegion                 kdGenMemOpsCopyRegion
#define GenMemOpsCopyRange                  kdGenMemOpsCopyRange

#define GenMemOpsMove                       kdGenMemOpsMove
#define GenMemOpsMoveRegion                 kdGenMemOpsMoveRegion
#define GenMemOpsMoveRange                  kdGenMemOpsMoveRange

#define GenMemOpsConcat                     kdGenMemOpsConcat
#define GenMemOpsConcatRange                kdGenMemOpsConcatRange

#define GenMemOpsSetBytes                   kdGenMemOpsSetBytes
#define GenMemOpsSetBytesRange              kdGenMemOpsSetBytesRange

#define GenMemOpsSetZerosBytes              kdGenMemOpsSetZerosBytes
#define GenMemOpsSetZerosBytesRange         kdGenMemOpsSetZerosBytesRange

#define GenMemOpsSetOnesBytes               kdGenMemOpsSetOnesBytes
#define GenMemOpsSetOnesBytesRange          kdGenMemOpsSetOnesBytesRange

#define GenMemOpsSetBlocks                  kdGenMemOpsSetBlocks
#define GenMemOpsSetBlocksRange             kdGenMemOpsSetBlocksRange

#define GenMemOpsFill                       kdGenMemOpsFill
#define GenMemOpsFillRange                  kdGenMemOpsFillRange

#define GenMemOpsReverseBytes               kdGenMemOpsReverseBytes
#define GenMemOpsReverseBytesRange          kdGenMemOpsReverseBytesRange

#define GenMemOpsReverseBlocks              kdGenMemOpsReverseBlocks
#define GenMemOpsReverseBlocksRange         kdGenMemOpsReverseBlocksRange

#define GenMemOpsRotateRight                kdGenMemOpsRotateRight
#define GenMemOpsRotateRightRange           kdGenMemOpsRotateRightRange

#define GenMemOpsRotateLeft                 kdGenMemOpsRotateLeft
#define GenMemOpsRotateLeftRange            kdGenMemOpsRotateLeftRange

#define GenMemOpsInnerSwapBytes             kdGenMemOpsInnerSwapBytes
#define GenMemOpsInnerSwapBytesRange        kdGenMemOpsInnerSwapBytesRange

#define GenMemOpsInnerSwapBlocks            kdGenMemOpsInnerSwapBlocks
#define GenMemOpsInnerSwapBlocksRange       kdGenMemOpsInnerSwapBlocksRange

#define GenMemOpsSwapBytes                  kdGenMemOpsSwapBytes
#define GenMemOpsSwapBytesRange             kdGenMemOpsSwapBytesRange

#define GenMemOpsSwapBlocks                 kdGenMemOpsSwapBlocks
#define GenMemOpsSwapBlocksRange            kdGenMemOpsSwapBlocksRange

#define GenMemOpsSequenceSwap               kdGenMemOpsSequenceSwap
#define GenMemOpsSequenceSwapRange          kdGenMemOpsSequenceSwapRange

#define GenMemOpsIsEqual                    kdGenMemOpsIsEqual
#define GenMemOpsIsEqualRegion              kdGenMemOpsIsEqualRegion
#define GenMemOpsIsEqualRange               kdGenMemOpsIsEqualRange

#define GenMemOpsIsZeros                    kdGenMemOpsIsZeros
#define GenMemOpsIsZerosRange               kdGenMemOpsIsZerosRange

#define GenMemOpsIsOnes                     kdGenMemOpsIsOnes
#define GenMemOpsIsOnesRange                kdGenMemOpsIsOnesRange

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

#define GenMemOpsFindByteIndexRange         kdGenMemOpsFindByteIndexRange
#define GenMemOpsFindBlockIndexRange        kdGenMemOpsFindBlockIndexRange

#define GenMemOpsFindNotByteIndexBound      kdGenMemOpsFindNotByteIndexBound
#define GenMemOpsFindNotBlockIndexBound     kdGenMemOpsFindNotBlockIndexBound

#define GenMemOpsFindLastByteIndex          kdGenMemOpsFindLastByteIndex
#define GenMemOpsFindLastBlockIndex         kdGenMemOpsFindLastBlockIndex

#define GenMemOpsFindLastNotByteIndex       kdGenMemOpsFindLastNotByteIndex
#define GenMemOpsFindLastNotBlockIndex      kdGenMemOpsFindLastNotBlockIndex

#define GenMemOpsFindLastByteIndexRange     kdGenMemOpsFindLastByteIndexRange
#define GenMemOpsFindLastBlockIndexRange    kdGenMemOpsFindLastBlockIndexRange

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

#define GenMemOpsFindByteIndicesRangeU8  kdGenMemOpsFindByteIndicesRangeU8
#define GenMemOpsFindByteIndicesRangeU16 kdGenMemOpsFindByteIndicesRangeU16
#define GenMemOpsFindByteIndicesRangeU32 kdGenMemOpsFindByteIndicesRangeU32
#if defined KD_ARCH_64BIT_INT
    #define GenMemOpsFindByteIndicesRangeU64 kdGenMemOpsFindByteIndicesRangeU64
#endif

#define GenMemOpsFindBlockIndicesRangeU8  kdGenMemOpsFindBlockIndicesRangeU8
#define GenMemOpsFindBlockIndicesRangeU16 kdGenMemOpsFindBlockIndicesRangeU16
#define GenMemOpsFindBlockIndicesRangeU32 kdGenMemOpsFindBlockIndicesRangeU32
#if defined KD_ARCH_64BIT_INT
    #define GenMemOpsFindBlockIndicesRangeU64 kdGenMemOpsFindBlockIndicesRangeU64
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

#define GenMemOpsFindByteIndicesRange        kdGenMemOpsFindByteIndicesRange
#define GenMemOpsFindBlockIndicesRange       kdGenMemOpsFindBlockIndicesRange

#define GenMemOpsFindNotByteIndicesBound     kdGenMemOpsFindNotByteIndicesBound
#define GenMemOpsFindNotBlockIndicesBound    kdGenMemOpsFindNotBlockIndicesBound

#define GenMemOpsReplaceByte                 kdGenMemOpsReplaceByte
#define GenMemOpsReplaceBlock                kdGenMemOpsReplaceBlock

#define GenMemOpsReplaceNotByte              kdGenMemOpsReplaceNotByte
#define GenMemOpsReplaceNotBlock             kdGenMemOpsReplaceNotBlock

#define GenMemOpsReplaceNotByteBound         kdGenMemOpsReplaceNotByteBound
#define GenMemOpsReplaceNotBlockBound        kdGenMemOpsReplaceNotBlockBound

#define GenMemOpsReplaceByteRange            kdGenMemOpsReplaceByteRange
#define GenMemOpsReplaceBlockRange           kdGenMemOpsReplaceBlockRange

#define GenMemOpsReplaceLastByte             kdGenMemOpsReplaceLastByte
#define GenMemOpsReplaceLastBlock            kdGenMemOpsReplaceLastBlock

#define GenMemOpsReplaceLastNotByte          kdGenMemOpsReplaceLastNotByte
#define GenMemOpsReplaceLastNotBlock         kdGenMemOpsReplaceLastNotBlock

#define GenMemOpsReplaceLastByteRange        kdGenMemOpsReplaceLastByteRange
#define GenMemOpsReplaceLastBlockRange       kdGenMemOpsReplaceLastBlockRange

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

#define GenMemOpsFindIndicesBoundPredicate kdGenMemOpsFindIndicesBoundPredicate

#define GenMemOpsFindPredicate             kdGenMemOpsFindPredicate
#define GenMemOpsFindBoundPredicate        kdGenMemOpsFindBoundPredicate

#define GenMemOpsFindLastPredicate         kdGenMemOpsFindLastPredicate
#define GenMemOpsFindLastBoundPredicate    kdGenMemOpsFindLastBoundPredicate

#define GenMemOpsFindAllPredicate          kdGenMemOpsFindAllPredicate
#define GenMemOpsFindAllBoundPredicate     kdGenMemOpsFindAllBoundPredicate

#define GenMemOpsReplacePredicate          kdGenMemOpsReplacePredicate
#define GenMemOpsReplaceBoundPredicate     kdGenMemOpsReplaceBoundPredicate

#define GenMemOpsReplaceLastPredicate      kdGenMemOpsReplaceLastPredicate
#define GenMemOpsReplaceLastBoundPredicate kdGenMemOpsReplaceLastBoundPredicate

#define GenMemOpsReplaceAllPredicate       kdGenMemOpsReplaceAllPredicate
#define GenMemOpsReplaceAllBoundPredicate  kdGenMemOpsReplaceAllBoundPredicate


KD_EXTERN_END


#endif /* KD_GEN_MEM_OPS_H_ */
