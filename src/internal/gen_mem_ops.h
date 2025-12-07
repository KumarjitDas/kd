/**
 * @file gen_mem_ops.h
 * @author Kumarjit Das
 * @version 0.0.1
 * @brief Main header file of the KDI_GEN_MEM_OPS library (internal).
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 * @since 0.0.1
 */


#ifndef KDI_GEN_MEM_OPS_H_
#define KDI_GEN_MEM_OPS_H_


#include "../../include/kd/version.h"
#include "../../include/kd/platform.h"
#include "../../include/kd/fixed_width.h"
#include "../../include/kd/floating_point.h"


EXTERN_BEGIN


KDAPI(void) kdi_GenMemOpsCopy(byte *dst, byte *src, usize sz);
KDAPI(void) kdi_GenMemOpsCopyRegion(void *dst, usize dst_sz, void *src, usize src_sz);

KDAPI(void) kdi_GenMemOpsCopyBytesRange(void *dst_base, usize dst_base_sz, void *src_base, usize src_base_sz, usize dst_idx, usize src_idx, usize count);
KDAPI(void) kdi_GenMemOpsCopyBlocksRange(void *dst_base, usize dst_base_sz, void *src_base, usize src_base_sz, usize dst_idx, usize src_idx, usize count, usize block_sz);

KDAPI(void) kdi_GenMemOpsMove(void *dst, void *src, usize dst_sz);
KDAPI(void) kdi_GenMemOpsMoveRegion(void *dst, usize dst_sz, void *src, usize src_sz);

KDAPI(void) kdi_GenMemOpsMoveBytesRange(void *dst_base, usize dst_base_sz, void *src_base, usize src_base_sz, usize dst_idx, usize src_idx, usize count);
KDAPI(void) kdi_GenMemOpsMoveBlocksRange(void *dst_base, usize dst_base_sz, void *src_base, usize src_base_sz, usize dst_idx, usize src_idx, usize count, usize block_sz);

KDAPI(void) kdi_GenMemOpsConcat(void *dst, usize dst_sz, void *src_1, usize src_1_sz, void *src_2, usize src_2_sz);

KDAPI(void) kdi_GenMemOpsConcatBytesRange(void *dst, usize dst_sz, void *src_base_1, usize src_base_1_begin_idx, usize src_base_1_count, void *src_base_2, usize src_base_2_begin_idx, usize src_base_2_count);
KDAPI(void) kdi_GenMemOpsConcatBlocksRange(void *dst, usize dst_sz, void *src_base_1, usize src_base_1_begin_idx, usize src_base_1_count, void *src_base_2, usize src_base_2_begin_idx, usize src_base_2_count, usize block_sz);

KDAPI(void) kdi_GenMemOpsSetBytes(void *dst, usize dst_sz, byte val);
KDAPI(void) kdi_GenMemOpsSetBytesRange(void *base, usize base_sz, usize begin_idx, usize count, byte val);

KDAPI(void) kdi_GenMemOpsSetZeroBytes(void *dst, usize dst_sz);
KDAPI(void) kdi_GenMemOpsSetZeroBytesRange(void *base, usize base_sz, usize begin_idx, usize count);

KDAPI(void) kdi_GenMemOpsSetBlocks(void *dst, usize dst_sz, void *block, usize block_sz);
KDAPI(void) kdi_GenMemOpsSetBlocksRange(void *base, usize base_sz, usize begin_idx, usize count, void *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFill(void *dst, usize dst_sz, void *sequence, usize sequence_sz);
KDAPI(void) kdi_GenMemOpsFillRange(void *base, usize base_sz, usize begin_idx, usize count, void *sequence, usize sequence_sz);

KDAPI(void) kdi_GenMemOpsSwapBytes(void *base, usize base_sz, usize idx_1, usize idx_2);
KDAPI(void) kdi_GenMemOpsSwapBlocks(void *base, usize base_sz, usize idx_1, usize idx_2, usize block_sz);
KDAPI(void) kdi_GenMemOpsSwapRegions(void *ptr_1, void *ptr_2, usize sz);

KDAPI(void) kdi_GenMemOpsSwapByteRanges(void *dst, usize dst_sz, usize begin_idx_1, usize end_idx_1, usize begin_idx_2, usize end_idx_2, usize *swapped_sz_addr);
KDAPI(void) kdi_GenMemOpsSwapBlockRanges(void *dst, usize dst_sz, usize begin_idx_1, usize end_idx_1, usize begin_idx_2, usize end_idx_2, usize block_sz, usize *swapped_sz_addr);
KDAPI(void) kdi_GenMemOpsSwapRegionRanges(void *ptr_1, usize ptr_1_sz, void *ptr_2, usize ptr_2_sz, usize *swapped_sz_addr);

KDAPI(word) kdi_GenMemOpsCompare(void *ptr_1, void *ptr_2, usize sz);
KDAPI(word) kdi_GenMemOpsCompareRegion(void *ptr_1, usize ptr_1_sz, void *ptr_2, usize ptr_2_sz);

KDAPI(void) kdi_GenMemOpsEqual(void *ptr_1, void *ptr_2, usize sz);
KDAPI(void) kdi_GenMemOpsEqualRegion(void *ptr_1, usize ptr_1_sz, void *ptr_2, usize ptr_2_sz);

KDAPI(void) kdi_GenMemOpsIsZero(void *ptr, usize sz);
KDAPI(void) kdi_GenMemOpsIsZeroRange(void *base, usize base_sz, usize begin_idx, usize count);

KDAPI(void) kdi_GenMemOpsHasPrefix(void *ptr, usize ptr_sz, void *prefix, usize prefix_sz);
KDAPI(void) kdi_GenMemOpsHasSuffix(void *ptr, usize ptr_sz, void *suffix, usize suffix_sz);

KDAPI(void) kdi_GenMemOpsRegionOverlap(void *ptr_1, usize ptr_1_sz, void *ptr_2, usize ptr_2_sz);

KDAPI(void) kdi_GenMemOpsGetOffsetChecked(void *dst_addr, void *base, usize base_sz, usize offset, usize sz);
KDAPI(void) kdi_GenMemOpsCheckBounds(usize total_sz, usize offset, usize sz);

KDAPI(void) kdi_GenMemOpsElemCountFromBytes(usize *sz_addr, usize base_sz, usize elem_sz);

KDAPI(void) kdi_GenMemOpsByteAt(void *dst, void *base, usize base_sz, usize idx);
KDAPI(void) kdi_GenMemOpsBlockAt(void *dst, void *base, usize base_sz, usize idx, usize block_sz);

KDAPI(void) kdi_GenMemOpsSetByteAt(void *base, usize base_sz, usize idx, byte val);
KDAPI(void) kdi_GenMemOpsSetBlockAt(void *base, usize base_sz, usize idx, void *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsInsertByteAt(void *base, usize base_capacity, usize *base_elems, usize idx, byte val);
KDAPI(void) kdi_GenMemOpsInsertBlockAt(void *base, usize base_capacity, usize *base_elems, usize idx, void *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsRemoveByteAt(void *base, usize base_capacity, usize *base_elems, usize idx);
KDAPI(void) kdi_GenMemOpsRemoveBlockAt(void *base, usize base_capacity, usize *base_elems, usize idx, usize block_sz);

KDAPI(void) kdi_GenMemOpsCountBytes(usize *count_addr, void *ptr, usize sz, byte item);
KDAPI(void) kdi_GenMemOpsCountNotBytes(usize *count_addr, void *ptr, usize sz, byte item);

KDAPI(void) kdi_GenMemOpsFindByte(void *dst, void *ptr, usize sz, byte item);
KDAPI(void) kdi_GenMemOpsFindByteIndex(usize *idx_addr, void *ptr, usize sz, byte item);

KDAPI(void) kdi_GenMemOpsFindLastByte(void *dst, void *ptr, usize sz, byte item);
KDAPI(void) kdi_GenMemOpsFindLastByteIndex(usize *idx_addr, void *ptr, usize sz, byte item);

KDAPI(void) kdi_GenMemOpsFindAllBytes(void *dst, usize dst_sz, usize *dst_elems, void *ptr, usize ptr_sz, byte item);

KDAPI(void) kdi_GenMemOpsReplaceByte(void *ptr, usize sz, byte find_item, byte new_item);
KDAPI(void) kdi_GenMemOpsReplaceLastByte(void *ptr, usize sz, byte find_item, byte new_item);

KDAPI(void) kdi_GenMemOpsReplaceAllBytes(usize *replaced_count_addr, void *ptr, usize ptr_sz, byte find_item, byte new_item);

KDAPI(void) kdi_GenMemOpsFindNotByte(void *dst, void *ptr, usize sz, byte item);
KDAPI(void) kdi_GenMemOpsFindNotByteIndex(usize *idx_addr, void *ptr, usize sz, byte item);

KDAPI(void) kdi_GenMemOpsFindNotLastByte(void *dst, void *ptr, usize sz, byte item);
KDAPI(void) kdi_GenMemOpsFindNotLastByteIndex(usize *idx_addr, void *ptr, usize sz, byte item);

KDAPI(void) kdi_GenMemOpsFindNotAllBytes(void *dst, usize dst_sz, usize *dst_elems, void *ptr, usize ptr_sz, byte item);

KDAPI(void) kdi_GenMemOpsFindAnyByte(void *dst, void *ptr, usize sz, byte *set, byte item);
KDAPI(void) kdi_GenMemOpsFindAnyByteIndex(usize *idx_addr, void *ptr, usize sz, byte *set, byte item);

KDAPI(void) kdi_GenMemOpsFindAnyLastByte(void *dst, void *ptr, usize sz, byte *set, byte item);
KDAPI(void) kdi_GenMemOpsFindAnyLastByteIndex(usize *idx_addr, void *ptr, usize sz, byte *set, byte item);

KDAPI(void) kdi_GenMemOpsFindAnyOfTheBytes(void *dst, usize dst_sz, usize *dst_elems, void *ptr, usize ptr_sz, byte *set, byte item);

KDAPI(void) kdi_GenMemOpsFindNotAnyByte(void *dst, void *ptr, usize sz, byte *set, byte item);
KDAPI(void) kdi_GenMemOpsFindNotAnyByteIndex(usize *idx_addr, void *ptr, usize sz, byte *set, byte item);

KDAPI(void) kdi_GenMemOpsFindNotAnyLastByte(void *dst, void *ptr, usize sz, byte *set, byte item);
KDAPI(void) kdi_GenMemOpsFindNotAnyLastByteIndex(usize *idx_addr, void *ptr, usize sz, byte *set, byte item);

KDAPI(void) kdi_GenMemOpsFindNotAnyOfTheBytes(void *dst, usize dst_sz, usize *dst_elems, void *ptr, usize ptr_sz, byte *set, byte item);

KDAPI(void) kdi_GenMemOpsFindAllByteIndices(usize *idxs, usize idxs_sz, usize *idx_elems, void *ptr, usize ptr_sz, byte item);
KDAPI(void) kdi_GenMemOpsFindAllByteIndicesU8(u8 *idxs, usize idxs_sz, usize *idx_elems, void *ptr, usize ptr_sz, byte item);
KDAPI(void) kdi_GenMemOpsFindAllByteIndicesU16(u16 *idxs, usize idxs_sz, usize *idx_elems, void *ptr, usize ptr_sz, byte item);
KDAPI(void) kdi_GenMemOpsFindAllByteIndicesU32(u32 *idxs, usize idxs_sz, usize *idx_elems, void *ptr, usize ptr_sz, byte item);
#if defined KD_ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsFindAllByteIndicesU64(u64 *idxs, usize idxs_sz, usize *idx_elems, void *ptr, usize ptr_sz, byte item);
#endif

KDAPI(void) kdi_GenMemOpsCountBlocks(usize *count_addr, void *ptr, usize ptr_sz, void *block, usize block_sz);
KDAPI(void) kdi_GenMemOpsCountNotBlocks(usize *count_addr, void *ptr, usize ptr_sz, void *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindBlock(void *dst, void *ptr, usize ptr_sz, void *block, usize block_sz);
KDAPI(void) kdi_GenMemOpsFindBlockIndex(usize *idx_addr, void *ptr, usize ptr_sz, void *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindLastBlock(void *dst, void *ptr, usize ptr_sz, void *block, usize block_sz);
KDAPI(void) kdi_GenMemOpsFindLastBlockIndex(usize *idx_addr, void *ptr, usize ptr_sz, void *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindAllBlocks(void *dst, usize dst_sz, usize *dst_elems, void *ptr, usize ptr_sz, void *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsReplaceBlock(void *ptr, usize sz, byte *find_block, byte *new_block, usize block_sz);
KDAPI(void) kdi_GenMemOpsReplaceLastBlock(void *ptr, usize sz, byte *find_block, byte *new_block, usize block_sz);

KDAPI(void) kdi_GenMemOpsReplaceAllBlocks(usize *replaced_count_addr, void *ptr, usize ptr_sz, byte *find_block, byte *new_block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindNotBlock(void *dst, void *ptr, usize ptr_sz, void *block, usize block_sz);
KDAPI(void) kdi_GenMemOpsFindNotBlockIndex(usize *idx_addr, void *ptr, usize ptr_sz, void *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindNotLastBlock(void *dst, void *ptr, usize ptr_sz, void *block, usize block_sz);
KDAPI(void) kdi_GenMemOpsFindNotLastBlockIndex(usize *idx_addr, void *ptr, usize ptr_sz, void *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindNotAllBlocks(void *dst, usize dst_sz, usize *dst_elems, void *ptr, usize ptr_sz, void *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindAnyBlock(void *dst, void *ptr, usize ptr_sz, byte *set, void *block, usize block_sz);
KDAPI(void) kdi_GenMemOpsFindAnyBlockIndex(usize *idx_addr, void *ptr, usize ptr_sz, byte *set, void *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindAnyLastBlock(void *dst, void *ptr, usize ptr_sz, byte *set, void *block, usize block_sz);
KDAPI(void) kdi_GenMemOpsFindAnyLastBlockIndex(usize *idx_addr, void *ptr, usize ptr_sz, byte *set, void *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindAnyOfTheBlocks(void *dst, usize dst_sz, usize *dst_elems, void *ptr, usize ptr_sz, byte *set, void *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindNotAnyBlock(void *dst, void *ptr, usize ptr_sz, byte *set, void *block, usize block_sz);
KDAPI(void) kdi_GenMemOpsFindNotAnyBlockIndex(usize *idx_addr, void *ptr, usize ptr_sz, byte *set, void *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindNotAnyLastBlock(void *dst, void *ptr, usize ptr_sz, byte *set, void *block, usize block_sz);
KDAPI(void) kdi_GenMemOpsFindNotAnyLastBlockIndex(usize *idx_addr, void *ptr, usize ptr_sz, byte *set, void *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindNotAnyOfTheBlocks(void *dst, usize dst_sz, usize *dst_elems, void *ptr, usize ptr_sz, byte *set, void *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindAllBlockIndices(usize *idxs, usize idxs_sz, usize *idx_elems, void *ptr, usize ptr_sz, void *block, usize block_sz);
KDAPI(void) kdi_GenMemOpsFindAllBlockIndicesU8(u8 *idxs, usize idxs_sz, usize *idx_elems, void *ptr, usize ptr_sz, void *block, usize block_sz);
KDAPI(void) kdi_GenMemOpsFindAllBlockIndicesU16(u16 *idxs, usize idxs_sz, usize *idx_elems, void *ptr, usize ptr_sz, void *block, usize block_sz);
KDAPI(void) kdi_GenMemOpsFindAllBlockIndicesU32(u32 *idxs, usize idxs_sz, usize *idx_elems, void *ptr, usize ptr_sz, void *block, usize block_sz);
#if defined KD_ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsFindAllBlockIndicesU64(u64 *idxs, usize idxs_sz, usize *idx_elems, void *ptr, usize ptr_sz, void *block, usize block_sz);
#endif

KDAPI(void) kdi_GenMemOpsSequenceAt(void *dst, void *base, usize base_sz, usize idx, usize sequence_sz);
KDAPI(void) kdi_GenMemOpsSetSequenceAt(void *base, usize base_sz, usize idx, void *sequence, usize sequence_sz);
KDAPI(void) kdi_GenMemOpsInsertSequenceAt(void *base, usize base_capacity, usize *base_elems, usize idx, void *sequence, usize sequence_sz);
KDAPI(void) kdi_GenMemOpsRemoveSequenceAt(void *base, usize base_capacity, usize *base_elems, usize idx, void *sequence, usize sequence_sz);

KDAPI(void) kdi_GenMemOpsFindSequence(usize *idx_addr, void *ptr, usize ptr_sz, void *sequence, usize sequence_sz);
KDAPI(void) kdi_GenMemOpsFindLastSequence(usize *idx_addr, void *ptr, usize ptr_sz, void *sequence, usize sequence_sz);

KDAPI(void) kdi_GenMemOpsReplaceSequence(void *ptr, usize ptr_capacity, usize *ptr_elems, byte *find_sequence, usize find_sequence_sz, byte *new_sequence, usize new_sequence_sz);
KDAPI(void) kdi_GenMemOpsReplaceLastSequence(void *ptr, usize ptr_capacity, usize *ptr_elems, byte *find_sequence, usize find_sequence_sz, byte *new_sequence, usize new_sequence_sz);

KDAPI(void) kdi_GenMemOpsReplaceAllSequences(usize *replaced_count_addr, void *ptr, usize ptr_capacity, usize *ptr_elems, byte *find_sequence, usize find_sequence_sz, byte *new_sequence, usize new_sequence_sz);

KDAPI(void) kdi_GenMemOpsCountSequences(usize *count_addr, void *ptr, usize ptr_sz, void *sequence, usize sequence_sz);

KDAPI(void) kdi_GenMemOpsFindAllSequences(usize *idxs, usize idxs_sz, usize *idx_elems, void *ptr, usize ptr_sz, void *sequence, usize sequence_sz);
KDAPI(void) kdi_GenMemOpsFindAllSequencesU8(u8 *idxs, usize idxs_sz, usize *idx_elems, void *ptr, usize ptr_sz, void *sequence, usize sequence_sz);
KDAPI(void) kdi_GenMemOpsFindAllSequencesU16(u16 *idxs, usize idxs_sz, usize *idx_elems, void *ptr, usize ptr_sz, void *sequence, usize sequence_sz);
KDAPI(void) kdi_GenMemOpsFindAllSequencesU32(u32 *idxs, usize idxs_sz, usize *idx_elems, void *ptr, usize ptr_sz, void *sequence, usize sequence_sz);
#if defined KD_ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsFindAllSequencesU64(u64 *idxs, usize idxs_sz, usize *idx_elems, void *ptr, usize ptr_sz, void *sequence, usize sequence_sz);
#endif

KDAPI(void) kdi_GenMemOpsReverseBytes(void *ptr, usize dst_sz);
KDAPI(void) kdi_GenMemOpsReverseBlocks(void *ptr, usize dst_sz, usize block_sz);

KDAPI(void) kdi_GenMemOpsRotateBytesRight(void *ptr, usize dst_sz, usize k);
KDAPI(void) kdi_GenMemOpsRotateBytesLeft(void *ptr, usize dst_sz, usize k);

KDAPI(void) kdi_GenMemOpsRotateBlocksRight(void *ptr, usize dst_sz, usize k, usize block_sz);
KDAPI(void) kdi_GenMemOpsRotateBlocksLeft(void *ptr, usize dst_sz, usize k, usize block_sz);


EXTERN_END


#endif /* KDI_GEN_MEM_OPS_H_ */
