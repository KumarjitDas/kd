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
#include "./fixed_width.h"


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

KDAPI(kd_bool_t) kdGenMemOpsInnerSwapBytes(void *ptr, kd_usize_t idx_1, kd_usize_t idx_2);
KDAPI(kd_bool_t) kdGenMemOpsInnerSwapBytesRange(void *base, kd_usize_t base_sz, kd_usize_t idx_1, kd_usize_t idx_2);

KDAPI(kd_bool_t) kdGenMemOpsInnerSwapBlocks(void *ptr, kd_usize_t idx_1, kd_usize_t idx_2, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsInnerSwapBlocksRange(void *base, kd_usize_t base_sz, kd_usize_t idx_1, kd_usize_t idx_2, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsSwapBytes(void *ptr_1, void *ptr_2);
KDAPI(kd_bool_t) kdGenMemOpsSwapBytesRange(void *base_1, kd_usize_t base_1_sz, kd_usize_t base_1_idx, void *base_2, kd_usize_t base_2_sz, kd_usize_t base_2_idx);

KDAPI(kd_bool_t) kdGenMemOpsSwapBlocks(void *ptr_1, void *ptr_2, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsSwapBlocksRange(void *base_1, kd_usize_t base_1_sz, kd_usize_t base_1_idx, void *base_2, kd_usize_t base_2_sz, kd_usize_t base_2_idx, kd_usize_t block_sz);

#define kdGenMemOpsSequenceSwap(ptr_1, ptr_2, sz)                                                           kdGenMemOpsSwapBlocks((ptr_1), (ptr_2), (sz))
#define kdGenMemOpsSequenceSwapRange(base_1, base_1_sz, base_1_idx, base_2, base_2_sz, base_2_idx, swap_sz) kdGenMemOpsSwapBlocksRange((base_1), (base_1_sz), (base_1_idx), (base_2), (base_2_sz), (base_2_idx), (swap_sz))

KDAPI(kd_bool_t) kdGenMemOpsIsEqual(kd_bool_t *result, void *ptr_1, void *ptr_2, kd_usize_t sz);
KDAPI(kd_bool_t) kdGenMemOpsIsEqualRegion(kd_bool_t *result, void *ptr_1, kd_usize_t ptr_1_sz, void *ptr_2, kd_usize_t ptr_2_sz);
KDAPI(kd_bool_t) kdGenMemOpsIsEqualRange(kd_bool_t *result, void *base_1, kd_usize_t base_1_sz, kd_usize_t base_1_idx, void *base_2, kd_usize_t base_2_sz, kd_usize_t base_2_idx, kd_usize_t byte_count);

KDAPI(kd_bool_t) kdGenMemOpsIsZeros(kd_bool_t *result, void *ptr, kd_usize_t sz);
KDAPI(kd_bool_t) kdGenMemOpsIsZerosRange(kd_bool_t *result, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t byte_count);

KDAPI(kd_bool_t) kdGenMemOpsIsOnes(kd_bool_t *result, void *ptr, kd_usize_t sz);
KDAPI(kd_bool_t) kdGenMemOpsIsOnesRange(kd_bool_t *result, void *base, kd_usize_t base_sz, kd_usize_t begin_idx, kd_usize_t byte_count);

KDAPI(kd_bool_t) kdGenMemOpsHasPrefix(void *ptr, kd_usize_t ptr_sz, void *prefix, kd_usize_t prefix_sz);
KDAPI(kd_bool_t) kdGenMemOpsHasSuffix(void *ptr, kd_usize_t ptr_sz, void *suffix, kd_usize_t suffix_sz);

KDAPI(kd_bool_t) kdGenMemOpsRegionOverlap(void *ptr_1, kd_usize_t ptr_1_sz, void *ptr_2, kd_usize_t ptr_2_sz);

KDAPI(kd_bool_t) kdGenMemOpsGetOffsetChecked(void *dst_addr, void *base, kd_usize_t base_sz, kd_usize_t offset, kd_usize_t sz);
KDAPI(kd_bool_t) kdGenMemOpsCheckBounds(kd_usize_t total_sz, kd_usize_t offset, kd_usize_t sz);

KDAPI(kd_bool_t) kdGenMemOpsElemCountFromBytes(kd_usize_t *sz_addr, kd_usize_t base_sz, kd_usize_t elem_sz);

KDAPI(kd_bool_t) kdGenMemOpsByteAt(void *dst, void *base, kd_usize_t base_sz, kd_usize_t idx);
KDAPI(kd_bool_t) kdGenMemOpsBlockAt(void *dst, void *base, kd_usize_t base_sz, kd_usize_t idx, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsSetByteAt(void *base, kd_usize_t base_sz, kd_usize_t idx, kd_byte_t val);
KDAPI(kd_bool_t) kdGenMemOpsSetBlockAt(void *base, kd_usize_t base_sz, kd_usize_t idx, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsInsertByteAt(void *base, kd_usize_t base_capacity, kd_usize_t *base_elems, kd_usize_t idx, kd_byte_t val);
KDAPI(kd_bool_t) kdGenMemOpsInsertBlockAt(void *base, kd_usize_t base_capacity, kd_usize_t *base_elems, kd_usize_t idx, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsRemoveByteAt(void *base, kd_usize_t base_capacity, kd_usize_t *base_elems, kd_usize_t idx);
KDAPI(kd_bool_t) kdGenMemOpsRemoveBlockAt(void *base, kd_usize_t base_capacity, kd_usize_t *base_elems, kd_usize_t idx, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsCountBytes(kd_usize_t *byte_count_addr, void *ptr, kd_usize_t sz, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsCountNotBytes(kd_usize_t *byte_count_addr, void *ptr, kd_usize_t sz, kd_byte_t item);

KDAPI(kd_bool_t) kdGenMemOpsFindByte(void *dst, void *ptr, kd_usize_t sz, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindByteIndex(kd_usize_t *idx_addr, void *ptr, kd_usize_t sz, kd_byte_t item);

KDAPI(kd_bool_t) kdGenMemOpsFindLastByte(void *dst, void *ptr, kd_usize_t sz, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindLastByteIndex(kd_usize_t *idx_addr, void *ptr, kd_usize_t sz, kd_byte_t item);

KDAPI(kd_bool_t) kdGenMemOpsFindAllBytes(void *dst, kd_usize_t dst_sz, kd_usize_t *dst_elems, void *ptr, kd_usize_t ptr_sz, kd_byte_t item);

KDAPI(kd_bool_t) kdGenMemOpsReplaceByte(void *ptr, kd_usize_t sz, kd_byte_t find_item, kd_byte_t new_item);
KDAPI(kd_bool_t) kdGenMemOpsReplaceLastByte(void *ptr, kd_usize_t sz, kd_byte_t find_item, kd_byte_t new_item);

KDAPI(kd_bool_t) kdGenMemOpsReplaceAllBytes(kd_usize_t *replaced_byte_count_addr, void *ptr, kd_usize_t ptr_sz, kd_byte_t find_item, kd_byte_t new_item);

KDAPI(kd_bool_t) kdGenMemOpsFindNotByte(void *dst, void *ptr, kd_usize_t sz, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindNotByteIndex(kd_usize_t *idx_addr, void *ptr, kd_usize_t sz, kd_byte_t item);

KDAPI(kd_bool_t) kdGenMemOpsFindNotLastByte(void *dst, void *ptr, kd_usize_t sz, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindNotLastByteIndex(kd_usize_t *idx_addr, void *ptr, kd_usize_t sz, kd_byte_t item);

KDAPI(kd_bool_t) kdGenMemOpsFindNotAllBytes(void *dst, kd_usize_t dst_sz, kd_usize_t *dst_elems, void *ptr, kd_usize_t ptr_sz, kd_byte_t item);

KDAPI(kd_bool_t) kdGenMemOpsFindAnyByte(void *dst, void *ptr, kd_usize_t sz, kd_byte_t *set, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindAnyByteIndex(kd_usize_t *idx_addr, void *ptr, kd_usize_t sz, kd_byte_t *set, kd_byte_t item);

KDAPI(kd_bool_t) kdGenMemOpsFindAnyLastByte(void *dst, void *ptr, kd_usize_t sz, kd_byte_t *set, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindAnyLastByteIndex(kd_usize_t *idx_addr, void *ptr, kd_usize_t sz, kd_byte_t *set, kd_byte_t item);

KDAPI(kd_bool_t) kdGenMemOpsFindAnyOfTheBytes(void *dst, kd_usize_t dst_sz, kd_usize_t *dst_elems, void *ptr, kd_usize_t ptr_sz, kd_byte_t *set, kd_byte_t item);

KDAPI(kd_bool_t) kdGenMemOpsFindNotAnyByte(void *dst, void *ptr, kd_usize_t sz, kd_byte_t *set, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindNotAnyByteIndex(kd_usize_t *idx_addr, void *ptr, kd_usize_t sz, kd_byte_t *set, kd_byte_t item);

KDAPI(kd_bool_t) kdGenMemOpsFindNotAnyLastByte(void *dst, void *ptr, kd_usize_t sz, kd_byte_t *set, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindNotAnyLastByteIndex(kd_usize_t *idx_addr, void *ptr, kd_usize_t sz, kd_byte_t *set, kd_byte_t item);

KDAPI(kd_bool_t) kdGenMemOpsFindNotAnyOfTheBytes(void *dst, kd_usize_t dst_sz, kd_usize_t *dst_elems, void *ptr, kd_usize_t ptr_sz, kd_byte_t *set, kd_byte_t item);

KDAPI(kd_bool_t) kdGenMemOpsFindAllByteIndices(kd_usize_t *idxs, kd_usize_t idxs_sz, kd_usize_t *idx_elems, void *ptr, kd_usize_t ptr_sz, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindAllByteIndicesU8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_usize_t *idx_elems, void *ptr, kd_usize_t ptr_sz, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindAllByteIndicesU16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_usize_t *idx_elems, void *ptr, kd_usize_t ptr_sz, kd_byte_t item);
KDAPI(kd_bool_t) kdGenMemOpsFindAllByteIndicesU32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_usize_t *idx_elems, void *ptr, kd_usize_t ptr_sz, kd_byte_t item);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_bool_t) kdGenMemOpsFindAllByteIndicesU64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_usize_t *idx_elems, void *ptr, kd_usize_t ptr_sz, kd_byte_t item);
#endif

KDAPI(kd_bool_t) kdGenMemOpsCountBlocks(kd_usize_t *byte_count_addr, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsCountNotBlocks(kd_usize_t *byte_count_addr, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindBlock(void *dst, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindBlockIndex(kd_usize_t *idx_addr, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindLastBlock(void *dst, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindLastBlockIndex(kd_usize_t *idx_addr, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindAllBlocks(void *dst, kd_usize_t dst_sz, kd_usize_t *dst_elems, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsReplaceBlock(void *ptr, kd_usize_t sz, kd_byte_t *find_block, kd_byte_t *new_block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsReplaceLastBlock(void *ptr, kd_usize_t sz, kd_byte_t *find_block, kd_byte_t *new_block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsReplaceAllBlocks(kd_usize_t *replaced_byte_count_addr, void *ptr, kd_usize_t ptr_sz, kd_byte_t *find_block, kd_byte_t *new_block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindNotBlock(void *dst, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindNotBlockIndex(kd_usize_t *idx_addr, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindNotLastBlock(void *dst, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindNotLastBlockIndex(kd_usize_t *idx_addr, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindNotAllBlocks(void *dst, kd_usize_t dst_sz, kd_usize_t *dst_elems, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindAnyBlock(void *dst, void *ptr, kd_usize_t ptr_sz, kd_byte_t *set, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindAnyBlockIndex(kd_usize_t *idx_addr, void *ptr, kd_usize_t ptr_sz, kd_byte_t *set, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindAnyLastBlock(void *dst, void *ptr, kd_usize_t ptr_sz, kd_byte_t *set, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindAnyLastBlockIndex(kd_usize_t *idx_addr, void *ptr, kd_usize_t ptr_sz, kd_byte_t *set, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindAnyOfTheBlocks(void *dst, kd_usize_t dst_sz, kd_usize_t *dst_elems, void *ptr, kd_usize_t ptr_sz, kd_byte_t *set, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindNotAnyBlock(void *dst, void *ptr, kd_usize_t ptr_sz, kd_byte_t *set, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindNotAnyBlockIndex(kd_usize_t *idx_addr, void *ptr, kd_usize_t ptr_sz, kd_byte_t *set, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindNotAnyLastBlock(void *dst, void *ptr, kd_usize_t ptr_sz, kd_byte_t *set, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindNotAnyLastBlockIndex(kd_usize_t *idx_addr, void *ptr, kd_usize_t ptr_sz, kd_byte_t *set, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindNotAnyOfTheBlocks(void *dst, kd_usize_t dst_sz, kd_usize_t *dst_elems, void *ptr, kd_usize_t ptr_sz, kd_byte_t *set, void *block, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindAllBlockIndices(kd_usize_t *idxs, kd_usize_t idxs_sz, kd_usize_t *idx_elems, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindAllBlockIndicesU8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_usize_t *idx_elems, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindAllBlockIndicesU16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_usize_t *idx_elems, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindAllBlockIndicesU32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_usize_t *idx_elems, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_bool_t) kdGenMemOpsFindAllBlockIndicesU64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_usize_t *idx_elems, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);
#endif

KDAPI(kd_bool_t) kdGenMemOpsSequenceAt(void *dst, void *base, kd_usize_t base_sz, kd_usize_t idx, kd_usize_t sequence_sz);
KDAPI(kd_bool_t) kdGenMemOpsSetSequenceAt(void *base, kd_usize_t base_sz, kd_usize_t idx, void *sequence, kd_usize_t sequence_sz);
KDAPI(kd_bool_t) kdGenMemOpsInsertSequenceAt(void *base, kd_usize_t base_capacity, kd_usize_t *base_elems, kd_usize_t idx, void *sequence, kd_usize_t sequence_sz);
KDAPI(kd_bool_t) kdGenMemOpsRemoveSequenceAt(void *base, kd_usize_t base_capacity, kd_usize_t *base_elems, kd_usize_t idx, void *sequence, kd_usize_t sequence_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindSequence(kd_usize_t *idx_addr, void *ptr, kd_usize_t ptr_sz, void *sequence, kd_usize_t sequence_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindLastSequence(kd_usize_t *idx_addr, void *ptr, kd_usize_t ptr_sz, void *sequence, kd_usize_t sequence_sz);

KDAPI(kd_bool_t) kdGenMemOpsReplaceSequence(void *ptr, kd_usize_t ptr_capacity, kd_usize_t *ptr_elems, kd_byte_t *find_sequence, kd_usize_t find_sequence_sz, kd_byte_t *new_sequence, kd_usize_t new_sequence_sz);
KDAPI(kd_bool_t) kdGenMemOpsReplaceLastSequence(void *ptr, kd_usize_t ptr_capacity, kd_usize_t *ptr_elems, kd_byte_t *find_sequence, kd_usize_t find_sequence_sz, kd_byte_t *new_sequence, kd_usize_t new_sequence_sz);

KDAPI(kd_bool_t) kdGenMemOpsReplaceAllSequences(kd_usize_t *replaced_byte_count_addr, void *ptr, kd_usize_t ptr_capacity, kd_usize_t *ptr_elems, kd_byte_t *find_sequence, kd_usize_t find_sequence_sz, kd_byte_t *new_sequence, kd_usize_t new_sequence_sz);

KDAPI(kd_bool_t) kdGenMemOpsCountSequences(kd_usize_t *byte_count_addr, void *ptr, kd_usize_t ptr_sz, void *sequence, kd_usize_t sequence_sz);

KDAPI(kd_bool_t) kdGenMemOpsFindAllSequences(kd_usize_t *idxs, kd_usize_t idxs_sz, kd_usize_t *idx_elems, void *ptr, kd_usize_t ptr_sz, void *sequence, kd_usize_t sequence_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindAllSequencesU8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_usize_t *idx_elems, void *ptr, kd_usize_t ptr_sz, void *sequence, kd_usize_t sequence_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindAllSequencesU16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_usize_t *idx_elems, void *ptr, kd_usize_t ptr_sz, void *sequence, kd_usize_t sequence_sz);
KDAPI(kd_bool_t) kdGenMemOpsFindAllSequencesU32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_usize_t *idx_elems, void *ptr, kd_usize_t ptr_sz, void *sequence, kd_usize_t sequence_sz);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_bool_t) kdGenMemOpsFindAllSequencesU64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_usize_t *idx_elems, void *ptr, kd_usize_t ptr_sz, void *sequence, kd_usize_t sequence_sz);
#endif

KDAPI(kd_bool_t) kdGenMemOpsReverseBytes(void *ptr, kd_usize_t dst_sz);
KDAPI(kd_bool_t) kdGenMemOpsReverseBlocks(void *ptr, kd_usize_t dst_sz, kd_usize_t block_sz);

KDAPI(kd_bool_t) kdGenMemOpsRotateBytesRight(void *ptr, kd_usize_t dst_sz, kd_usize_t k);
KDAPI(kd_bool_t) kdGenMemOpsRotateBytesLeft(void *ptr, kd_usize_t dst_sz, kd_usize_t k);

KDAPI(kd_bool_t) kdGenMemOpsRotateBlocksRight(void *ptr, kd_usize_t dst_sz, kd_usize_t k, kd_usize_t block_sz);
KDAPI(kd_bool_t) kdGenMemOpsRotateBlocksLeft(void *ptr, kd_usize_t dst_sz, kd_usize_t k, kd_usize_t block_sz);

#define kdGenMemOpsFindAllByteIndicesUmin(idxs, idxs_sz, ptr, ptr_sz, item) kdGenMemOpsFindAllByteIndicesU8(KD_PU8_C(idxs), KD_USIZE_C(idxs_sz), KD_PTR_C(ptr), KD_USIZE_C(ptr_sz), KD_BYTE_C(item))

#if defined KD_ARCH_64BIT_INT
    #define kdGenMemOpsFindAllByteIndicesUmax(idxs, idxs_sz, ptr, ptr_sz, item)  kdGenMemOpsFindAllByteIndicesU64(KD_PU64_C(idxs), KD_USIZE_C(idxs_sz), KD_PTR_C(ptr), KD_USIZE_C(ptr_sz), KD_BYTE_C(item))
    #define kdGenMemOpsFindAllByteIndicesUsize(idxs, idxs_sz, ptr, ptr_sz, item) kdGenMemOpsFindAllByteIndicesU64(KD_PU64_C(idxs), KD_USIZE_C(idxs_sz), KD_PTR_C(ptr), KD_USIZE_C(ptr_sz), KD_BYTE_C(item))
#else  /* !defined KD_ARCH_64BIT_INT */
    #define kdGenMemOpsFindAllByteIndicesUmax(idxs, idxs_sz, ptr, ptr_sz, item)  kdGenMemOpsFindAllByteIndicesU32(KD_PU32_C(idxs), KD_USIZE_C(idxs_sz), KD_PTR_C(ptr), KD_USIZE_C(ptr_sz), KD_BYTE_C(item))
    #define kdGenMemOpsFindAllByteIndicesUsize(idxs, idxs_sz, ptr, ptr_sz, item) kdGenMemOpsFindAllByteIndicesU32(KD_PU32_C(idxs), KD_USIZE_C(idxs_sz), KD_PTR_C(ptr), KD_USIZE_C(ptr_sz), KD_BYTE_C(item))
#endif /* KD_ARCH_64BIT_INT */


#define kdGenMemOpsFindAllBlockIndicesUmin(idxs, idxs_sz, ptr, ptr_sz, block, block_sz) kdGenMemOpsFindAllBlockIndicesU8(KD_PU8_C(idxs), KD_USIZE_C(idxs_sz), KD_PTR_C(ptr), KD_USIZE_C(ptr_sz), KD_PTR_C(block), KD_USIZE_C(block_sz))

#if defined KD_ARCH_64BIT_INT
    #define kdGenMemOpsFindAllBlockIndicesUmax(idxs, idxs_sz, ptr, ptr_sz, block, block_sz)  kdGenMemOpsFindAllBlockIndicesU64(KD_PU64_C(idxs), KD_USIZE_C(idxs_sz), KD_PTR_C(ptr), KD_USIZE_C(ptr_sz), KD_PTR_C(block), KD_USIZE_C(block_sz))
    #define kdGenMemOpsFindAllBlockIndicesUsize(idxs, idxs_sz, ptr, ptr_sz, block, block_sz) kdGenMemOpsFindAllBlockIndicesU64(KD_PU64_C(idxs), KD_USIZE_C(idxs_sz), KD_PTR_C(ptr), KD_USIZE_C(ptr_sz), KD_PTR_C(block), KD_USIZE_C(block_sz))
#else  /* !defined KD_ARCH_64BIT_INT */
    #define kdGenMemOpsFindAllBlockIndicesUmax(idxs, idxs_sz, ptr, ptr_sz, block, block_sz)  kdGenMemOpsFindAllBlockIndicesU32(KD_PU32_C(idxs), KD_USIZE_C(idxs_sz), KD_PTR_C(ptr), KD_USIZE_C(ptr_sz), KD_PTR_C(block), KD_USIZE_C(block_sz))
    #define kdGenMemOpsFindAllBlockIndicesUsize(idxs, idxs_sz, ptr, ptr_sz, block, block_sz) kdGenMemOpsFindAllBlockIndicesU32(KD_PU32_C(idxs), KD_USIZE_C(idxs_sz), KD_PTR_C(ptr), KD_USIZE_C(ptr_sz), KD_PTR_C(block), KD_USIZE_C(block_sz))
#endif /* KD_ARCH_64BIT_INT */

#define GenMemOpsCopy                     kdGenMemOpsCopy
#define GenMemOpsCopyRegion               kdGenMemOpsCopyRegion
#define GenMemOpsCopyRange                kdGenMemOpsCopyRange

#define GenMemOpsMove                     kdGenMemOpsMove
#define GenMemOpsMoveRegion               kdGenMemOpsMoveRegion
#define GenMemOpsMoveRange                kdGenMemOpsMoveRange

#define GenMemOpsConcat                   kdGenMemOpsConcat
#define GenMemOpsConcatRange              kdGenMemOpsConcatRange

#define GenMemOpsSetBytes                 kdGenMemOpsSetBytes
#define GenMemOpsSetBytesRange            kdGenMemOpsSetBytesRange

#define GenMemOpsSetZerosBytes            kdGenMemOpsSetZerosBytes
#define GenMemOpsSetZerosBytesRange       kdGenMemOpsSetZerosBytesRange

#define GenMemOpsSetOnesBytes             kdGenMemOpsSetOnesBytes
#define GenMemOpsSetOnesBytesRange        kdGenMemOpsSetOnesBytesRange

#define GenMemOpsSetBlocks                kdGenMemOpsSetBlocks
#define GenMemOpsSetBlocksRange           kdGenMemOpsSetBlocksRange

#define GenMemOpsFill                     kdGenMemOpsFill
#define GenMemOpsFillRange                kdGenMemOpsFillRange

#define GenMemOpsInnerSwapBytes           kdGenMemOpsInnerSwapBytes
#define GenMemOpsInnerSwapBytesRange      kdGenMemOpsInnerSwapBytesRange

#define GenMemOpsInnerSwapBlocks          kdGenMemOpsInnerSwapBlocks
#define GenMemOpsInnerSwapBlocksRange     kdGenMemOpsInnerSwapBlocksRange

#define GenMemOpsSwapBytes                kdGenMemOpsSwapBytes
#define GenMemOpsSwapBytesRange           kdGenMemOpsSwapBytesRange

#define GenMemOpsSwapBlocks               kdGenMemOpsSwapBlocks
#define GenMemOpsSwapBlocksRange          kdGenMemOpsSwapBlocksRange

#define GenMemOpsSequenceSwap             kdGenMemOpsSequenceSwap
#define GenMemOpsSequenceSwapRange        kdGenMemOpsSequenceSwapRange

#define GenMemOpsIsEqual                  kdGenMemOpsIsEqual
#define GenMemOpsIsEqualRegion            kdGenMemOpsIsEqualRegion
#define GenMemOpsIsEqualRange             kdGenMemOpsIsEqualRange

#define GenMemOpsIsZeros                  kdGenMemOpsIsZeros
#define GenMemOpsIsZerosRange             kdGenMemOpsIsZerosRange

#define GenMemOpsIsOnes                   kdGenMemOpsIsOnes
#define GenMemOpsIsOnesRange              kdGenMemOpsIsOnesRange

#define GenMemOpsHasPrefix                kdGenMemOpsHasPrefix
#define GenMemOpsHasSuffix                kdGenMemOpsHasSuffix
#define GenMemOpsRegionOverlap            kdGenMemOpsRegionOverlap
#define GenMemOpsGetOffsetChecked         kdGenMemOpsGetOffsetChecked
#define GenMemOpsCheckBounds              kdGenMemOpsCheckBounds
#define GenMemOpsElemCountFromBytes       kdGenMemOpsElemCountFromBytes
#define GenMemOpsByteAt                   kdGenMemOpsByteAt
#define GenMemOpsBlockAt                  kdGenMemOpsBlockAt
#define GenMemOpsSetByteAt                kdGenMemOpsSetByteAt
#define GenMemOpsSetBlockAt               kdGenMemOpsSetBlockAt
#define GenMemOpsInsertByteAt             kdGenMemOpsInsertByteAt
#define GenMemOpsInsertBlockAt            kdGenMemOpsInsertBlockAt
#define GenMemOpsRemoveByteAt             kdGenMemOpsRemoveByteAt
#define GenMemOpsRemoveBlockAt            kdGenMemOpsRemoveBlockAt
#define GenMemOpsCountBytes               kdGenMemOpsCountBytes
#define GenMemOpsCountNotBytes            kdGenMemOpsCountNotBytes
#define GenMemOpsFindByte                 kdGenMemOpsFindByte
#define GenMemOpsFindByteIndex            kdGenMemOpsFindByteIndex
#define GenMemOpsFindLastByte             kdGenMemOpsFindLastByte
#define GenMemOpsFindLastByteIndex        kdGenMemOpsFindLastByteIndex
#define GenMemOpsFindAllBytes             kdGenMemOpsFindAllBytes
#define GenMemOpsReplaceByte              kdGenMemOpsReplaceByte
#define GenMemOpsReplaceLastByte          kdGenMemOpsReplaceLastByte
#define GenMemOpsReplaceAllBytes          kdGenMemOpsReplaceAllBytes
#define GenMemOpsFindNotByte              kdGenMemOpsFindNotByte
#define GenMemOpsFindNotByteIndex         kdGenMemOpsFindNotByteIndex
#define GenMemOpsFindNotLastByte          kdGenMemOpsFindNotLastByte
#define GenMemOpsFindNotLastByteIndex     kdGenMemOpsFindNotLastByteIndex
#define GenMemOpsFindNotAllBytes          kdGenMemOpsFindNotAllBytes
#define GenMemOpsFindAnyByte              kdGenMemOpsFindAnyByte
#define GenMemOpsFindAnyByteIndex         kdGenMemOpsFindAnyByteIndex
#define GenMemOpsFindAnyLastByte          kdGenMemOpsFindAnyLastByte
#define GenMemOpsFindAnyLastByteIndex     kdGenMemOpsFindAnyLastByteIndex
#define GenMemOpsFindAnyOfTheBytes        kdGenMemOpsFindAnyOfTheBytes
#define GenMemOpsFindNotAnyByte           kdGenMemOpsFindNotAnyByte
#define GenMemOpsFindNotAnyByteIndex      kdGenMemOpsFindNotAnyByteIndex
#define GenMemOpsFindNotAnyLastByte       kdGenMemOpsFindNotAnyLastByte
#define GenMemOpsFindNotAnyLastByteIndex  kdGenMemOpsFindNotAnyLastByteIndex
#define GenMemOpsFindNotAnyOfTheBytes     kdGenMemOpsFindNotAnyOfTheBytes
#define GenMemOpsFindAllByteIndices       kdGenMemOpsFindAllByteIndices
#define GenMemOpsFindAllByteIndicesU8     kdGenMemOpsFindAllByteIndicesU8
#define GenMemOpsFindAllByteIndicesU16    kdGenMemOpsFindAllByteIndicesU16
#define GenMemOpsFindAllByteIndicesU32    kdGenMemOpsFindAllByteIndicesU32
#define GenMemOpsFindAllByteIndicesU64    kdGenMemOpsFindAllByteIndicesU64
#define GenMemOpsCountBlocks              kdGenMemOpsCountBlocks
#define GenMemOpsCountNotBlocks           kdGenMemOpsCountNotBlocks
#define GenMemOpsFindBlock                kdGenMemOpsFindBlock
#define GenMemOpsFindBlockIndex           kdGenMemOpsFindBlockIndex
#define GenMemOpsFindLastBlock            kdGenMemOpsFindLastBlock
#define GenMemOpsFindLastBlockIndex       kdGenMemOpsFindLastBlockIndex
#define GenMemOpsFindAllBlocks            kdGenMemOpsFindAllBlocks
#define GenMemOpsReplaceBlock             kdGenMemOpsReplaceBlock
#define GenMemOpsReplaceLastBlock         kdGenMemOpsReplaceLastBlock
#define GenMemOpsReplaceAllBlocks         kdGenMemOpsReplaceAllBlocks
#define GenMemOpsFindNotBlock             kdGenMemOpsFindNotBlock
#define GenMemOpsFindNotBlockIndex        kdGenMemOpsFindNotBlockIndex
#define GenMemOpsFindNotLastBlock         kdGenMemOpsFindNotLastBlock
#define GenMemOpsFindNotLastBlockIndex    kdGenMemOpsFindNotLastBlockIndex
#define GenMemOpsFindNotAllBlocks         kdGenMemOpsFindNotAllBlocks
#define GenMemOpsFindAnyBlock             kdGenMemOpsFindAnyBlock
#define GenMemOpsFindAnyBlockIndex        kdGenMemOpsFindAnyBlockIndex
#define GenMemOpsFindAnyLastBlock         kdGenMemOpsFindAnyLastBlock
#define GenMemOpsFindAnyLastBlockIndex    kdGenMemOpsFindAnyLastBlockIndex
#define GenMemOpsFindAnyOfTheBlocks       kdGenMemOpsFindAnyOfTheBlocks
#define GenMemOpsFindNotAnyBlock          kdGenMemOpsFindNotAnyBlock
#define GenMemOpsFindNotAnyBlockIndex     kdGenMemOpsFindNotAnyBlockIndex
#define GenMemOpsFindNotAnyLastBlock      kdGenMemOpsFindNotAnyLastBlock
#define GenMemOpsFindNotAnyLastBlockIndex kdGenMemOpsFindNotAnyLastBlockIndex
#define GenMemOpsFindNotAnyOfTheBlocks    kdGenMemOpsFindNotAnyOfTheBlocks
#define GenMemOpsFindAllBlockIndices      kdGenMemOpsFindAllBlockIndices
#define GenMemOpsFindAllBlockIndicesU8    kdGenMemOpsFindAllBlockIndicesU8
#define GenMemOpsFindAllBlockIndicesU16   kdGenMemOpsFindAllBlockIndicesU16
#define GenMemOpsFindAllBlockIndicesU32   kdGenMemOpsFindAllBlockIndicesU32
#define GenMemOpsFindAllBlockIndicesU64   kdGenMemOpsFindAllBlockIndicesU64
#define GenMemOpsSequenceAt               kdGenMemOpsSequenceAt
#define GenMemOpsSetSequenceAt            kdGenMemOpsSetSequenceAt
#define GenMemOpsInsertSequenceAt         kdGenMemOpsInsertSequenceAt
#define GenMemOpsRemoveSequenceAt         kdGenMemOpsRemoveSequenceAt
#define GenMemOpsFindSequence             kdGenMemOpsFindSequence
#define GenMemOpsFindLastSequence         kdGenMemOpsFindLastSequence
#define GenMemOpsReplaceSequence          kdGenMemOpsReplaceSequence
#define GenMemOpsReplaceLastSequence      kdGenMemOpsReplaceLastSequence
#define GenMemOpsReplaceAllSequences      kdGenMemOpsReplaceAllSequences
#define GenMemOpsCountSequences           kdGenMemOpsCountSequences
#define GenMemOpsFindAllSequences         kdGenMemOpsFindAllSequences
#define GenMemOpsFindAllSequencesU8       kdGenMemOpsFindAllSequencesU8
#define GenMemOpsFindAllSequencesU16      kdGenMemOpsFindAllSequencesU16
#define GenMemOpsFindAllSequencesU32      kdGenMemOpsFindAllSequencesU32
#define GenMemOpsFindAllSequencesU64      kdGenMemOpsFindAllSequencesU64
#define GenMemOpsReverseBytes             kdGenMemOpsReverseBytes
#define GenMemOpsReverseBlocks            kdGenMemOpsReverseBlocks
#define GenMemOpsRotateBytesRight         kdGenMemOpsRotateBytesRight
#define GenMemOpsRotateBytesLeft          kdGenMemOpsRotateBytesLeft
#define GenMemOpsRotateBlocksRight        kdGenMemOpsRotateBlocksRight
#define GenMemOpsRotateBlocksLeft         kdGenMemOpsRotateBlocksLeft


KD_EXTERN_END


#endif /* KD_GEN_MEM_OPS_H_ */
