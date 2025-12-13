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
KDAPI(void) kdi_GenMemOpsMove(byte *dst, byte *src, usize sz);

KDAPI(void) kdi_GenMemOpsConcat(byte *dst, usize dst_sz, byte *src_1, usize src_1_sz, byte *src_2, usize src_2_sz);

KDAPI(void) kdi_GenMemOpsSetBytes(byte *dst, usize sz, byte val);

KDAPI(void) kdi_GenMemOpsSetBlocks_U8(u8 *dst, usize sz, u8 val);
KDAPI(void) kdi_GenMemOpsSetBlocks_U16(u16 *dst, usize sz, u16 val);
KDAPI(void) kdi_GenMemOpsSetBlocks_U32(u32 *dst, usize sz, u32 val);
#if defined ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsSetBlocks_U64(u64 *dst, usize sz, u64 val);
#endif
KDAPI(void) kdi_GenMemOpsSetBlocks_Un(byte *dst, usize dsst_sz, byte *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsSetBlocksRange(byte *base, usize base_sz, usize begin_idx, usize count, byte *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFill(byte *dst, usize dst_sz, byte *sequence, usize sequence_sz);
KDAPI(void) kdi_GenMemOpsFillRange(byte *base, usize base_sz, usize begin_idx, usize count, byte *sequence, usize sequence_sz);

KDAPI(void) kdi_GenMemOpsSwapBytes(byte *base, usize base_sz, usize idx_1, usize idx_2);
KDAPI(void) kdi_GenMemOpsSwapBlocks(byte *base, usize base_sz, usize idx_1, usize idx_2, usize block_sz);
KDAPI(void) kdi_GenMemOpsSwapRegions(byte *ptr_1, byte *ptr_2, usize sz);

KDAPI(void) kdi_GenMemOpsSwapByteRanges(byte *dst, usize dst_sz, usize begin_idx_1, usize end_idx_1, usize begin_idx_2, usize end_idx_2, usize *swapped_sz_addr);
KDAPI(void) kdi_GenMemOpsSwapBlockRanges(byte *dst, usize dst_sz, usize begin_idx_1, usize end_idx_1, usize begin_idx_2, usize end_idx_2, usize block_sz, usize *swapped_sz_addr);
KDAPI(void) kdi_GenMemOpsSwapRegionRanges(byte *ptr_1, usize ptr_1_sz, byte *ptr_2, usize ptr_2_sz, usize *swapped_sz_addr);

KDAPI(word) kdi_GenMemOpsCompare(byte *ptr_1, byte *ptr_2, usize sz);
KDAPI(word) kdi_GenMemOpsCompareRegion(byte *ptr_1, usize ptr_1_sz, byte *ptr_2, usize ptr_2_sz);

KDAPI(void) kdi_GenMemOpsEqual(byte *ptr_1, byte *ptr_2, usize sz);
KDAPI(void) kdi_GenMemOpsEqualRegion(byte *ptr_1, usize ptr_1_sz, byte *ptr_2, usize ptr_2_sz);

KDAPI(void) kdi_GenMemOpsIsZero(byte *ptr, usize sz);
KDAPI(void) kdi_GenMemOpsIsZeroRange(byte *base, usize base_sz, usize begin_idx, usize count);

KDAPI(void) kdi_GenMemOpsHasPrefix(byte *ptr, usize ptr_sz, byte *prefix, usize prefix_sz);
KDAPI(void) kdi_GenMemOpsHasSuffix(byte *ptr, usize ptr_sz, byte *suffix, usize suffix_sz);

KDAPI(void) kdi_GenMemOpsRegionOverlap(byte *ptr_1, usize ptr_1_sz, byte *ptr_2, usize ptr_2_sz);

KDAPI(void) kdi_GenMemOpsGetOffsetChecked(byte *dst_addr, byte *base, usize base_sz, usize offset, usize sz);
KDAPI(void) kdi_GenMemOpsCheckBounds(usize total_sz, usize offset, usize sz);

KDAPI(void) kdi_GenMemOpsElemCountFromBytes(usize *sz_addr, usize base_sz, usize elem_sz);

KDAPI(void) kdi_GenMemOpsByteAt(byte *dst, byte *base, usize base_sz, usize idx);
KDAPI(void) kdi_GenMemOpsBlockAt(byte *dst, byte *base, usize base_sz, usize idx, usize block_sz);

KDAPI(void) kdi_GenMemOpsSetByteAt(byte *base, usize base_sz, usize idx, byte val);
KDAPI(void) kdi_GenMemOpsSetBlockAt(byte *base, usize base_sz, usize idx, byte *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsInsertByteAt(byte *base, usize base_capacity, usize *base_elems, usize idx, byte val);
KDAPI(void) kdi_GenMemOpsInsertBlockAt(byte *base, usize base_capacity, usize *base_elems, usize idx, byte *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsRemoveByteAt(byte *base, usize base_capacity, usize *base_elems, usize idx);
KDAPI(void) kdi_GenMemOpsRemoveBlockAt(byte *base, usize base_capacity, usize *base_elems, usize idx, usize block_sz);

KDAPI(void) kdi_GenMemOpsCountBytes(usize *count_addr, byte *ptr, usize sz, byte item);
KDAPI(void) kdi_GenMemOpsCountNotBytes(usize *count_addr, byte *ptr, usize sz, byte item);

KDAPI(void) kdi_GenMemOpsFindByte(byte *dst, byte *ptr, usize sz, byte item);
KDAPI(void) kdi_GenMemOpsFindByteIndex(usize *idx_addr, byte *ptr, usize sz, byte item);

KDAPI(void) kdi_GenMemOpsFindLastByte(byte *dst, byte *ptr, usize sz, byte item);
KDAPI(void) kdi_GenMemOpsFindLastByteIndex(usize *idx_addr, byte *ptr, usize sz, byte item);

KDAPI(void) kdi_GenMemOpsFindAllBytes(byte *dst, usize dst_sz, usize *dst_elems, byte *ptr, usize ptr_sz, byte item);

KDAPI(void) kdi_GenMemOpsReplaceByte(byte *ptr, usize sz, byte find_item, byte new_item);
KDAPI(void) kdi_GenMemOpsReplaceLastByte(byte *ptr, usize sz, byte find_item, byte new_item);

KDAPI(void) kdi_GenMemOpsReplaceAllBytes(usize *replaced_count_addr, byte *ptr, usize ptr_sz, byte find_item, byte new_item);

KDAPI(void) kdi_GenMemOpsFindNotByte(byte *dst, byte *ptr, usize sz, byte item);
KDAPI(void) kdi_GenMemOpsFindNotByteIndex(usize *idx_addr, byte *ptr, usize sz, byte item);

KDAPI(void) kdi_GenMemOpsFindNotLastByte(byte *dst, byte *ptr, usize sz, byte item);
KDAPI(void) kdi_GenMemOpsFindNotLastByteIndex(usize *idx_addr, byte *ptr, usize sz, byte item);

KDAPI(void) kdi_GenMemOpsFindNotAllBytes(byte *dst, usize dst_sz, usize *dst_elems, byte *ptr, usize ptr_sz, byte item);

KDAPI(void) kdi_GenMemOpsFindAnyByte(byte *dst, byte *ptr, usize sz, byte *set, byte item);
KDAPI(void) kdi_GenMemOpsFindAnyByteIndex(usize *idx_addr, byte *ptr, usize sz, byte *set, byte item);

KDAPI(void) kdi_GenMemOpsFindAnyLastByte(byte *dst, byte *ptr, usize sz, byte *set, byte item);
KDAPI(void) kdi_GenMemOpsFindAnyLastByteIndex(usize *idx_addr, byte *ptr, usize sz, byte *set, byte item);

KDAPI(void) kdi_GenMemOpsFindAnyOfTheBytes(byte *dst, usize dst_sz, usize *dst_elems, byte *ptr, usize ptr_sz, byte *set, byte item);

KDAPI(void) kdi_GenMemOpsFindNotAnyByte(byte *dst, byte *ptr, usize sz, byte *set, byte item);
KDAPI(void) kdi_GenMemOpsFindNotAnyByteIndex(usize *idx_addr, byte *ptr, usize sz, byte *set, byte item);

KDAPI(void) kdi_GenMemOpsFindNotAnyLastByte(byte *dst, byte *ptr, usize sz, byte *set, byte item);
KDAPI(void) kdi_GenMemOpsFindNotAnyLastByteIndex(usize *idx_addr, byte *ptr, usize sz, byte *set, byte item);

KDAPI(void) kdi_GenMemOpsFindNotAnyOfTheBytes(byte *dst, usize dst_sz, usize *dst_elems, byte *ptr, usize ptr_sz, byte *set, byte item);

KDAPI(void) kdi_GenMemOpsFindAllByteIndices(usize *idxs, usize idxs_sz, usize *idx_elems, byte *ptr, usize ptr_sz, byte item);
KDAPI(void) kdi_GenMemOpsFindAllByteIndicesU8(u8 *idxs, usize idxs_sz, usize *idx_elems, byte *ptr, usize ptr_sz, byte item);
KDAPI(void) kdi_GenMemOpsFindAllByteIndicesU16(u16 *idxs, usize idxs_sz, usize *idx_elems, byte *ptr, usize ptr_sz, byte item);
KDAPI(void) kdi_GenMemOpsFindAllByteIndicesU32(u32 *idxs, usize idxs_sz, usize *idx_elems, byte *ptr, usize ptr_sz, byte item);
#if defined KD_ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsFindAllByteIndicesU64(u64 *idxs, usize idxs_sz, usize *idx_elems, byte *ptr, usize ptr_sz, byte item);
#endif

KDAPI(void) kdi_GenMemOpsCountBlocks(usize *count_addr, byte *ptr, usize ptr_sz, byte *block, usize block_sz);
KDAPI(void) kdi_GenMemOpsCountNotBlocks(usize *count_addr, byte *ptr, usize ptr_sz, byte *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindBlock(byte *dst, byte *ptr, usize ptr_sz, byte *block, usize block_sz);
KDAPI(void) kdi_GenMemOpsFindBlockIndex(usize *idx_addr, byte *ptr, usize ptr_sz, byte *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindLastBlock(byte *dst, byte *ptr, usize ptr_sz, byte *block, usize block_sz);
KDAPI(void) kdi_GenMemOpsFindLastBlockIndex(usize *idx_addr, byte *ptr, usize ptr_sz, byte *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindAllBlocks(byte *dst, usize dst_sz, usize *dst_elems, byte *ptr, usize ptr_sz, byte *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsReplaceBlock(byte *ptr, usize sz, byte *find_block, byte *new_block, usize block_sz);
KDAPI(void) kdi_GenMemOpsReplaceLastBlock(byte *ptr, usize sz, byte *find_block, byte *new_block, usize block_sz);

KDAPI(void) kdi_GenMemOpsReplaceAllBlocks(usize *replaced_count_addr, byte *ptr, usize ptr_sz, byte *find_block, byte *new_block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindNotBlock(byte *dst, byte *ptr, usize ptr_sz, byte *block, usize block_sz);
KDAPI(void) kdi_GenMemOpsFindNotBlockIndex(usize *idx_addr, byte *ptr, usize ptr_sz, byte *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindNotLastBlock(byte *dst, byte *ptr, usize ptr_sz, byte *block, usize block_sz);
KDAPI(void) kdi_GenMemOpsFindNotLastBlockIndex(usize *idx_addr, byte *ptr, usize ptr_sz, byte *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindNotAllBlocks(byte *dst, usize dst_sz, usize *dst_elems, byte *ptr, usize ptr_sz, byte *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindAnyBlock(byte *dst, byte *ptr, usize ptr_sz, byte *set, byte *block, usize block_sz);
KDAPI(void) kdi_GenMemOpsFindAnyBlockIndex(usize *idx_addr, byte *ptr, usize ptr_sz, byte *set, byte *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindAnyLastBlock(byte *dst, byte *ptr, usize ptr_sz, byte *set, byte *block, usize block_sz);
KDAPI(void) kdi_GenMemOpsFindAnyLastBlockIndex(usize *idx_addr, byte *ptr, usize ptr_sz, byte *set, byte *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindAnyOfTheBlocks(byte *dst, usize dst_sz, usize *dst_elems, byte *ptr, usize ptr_sz, byte *set, byte *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindNotAnyBlock(byte *dst, byte *ptr, usize ptr_sz, byte *set, byte *block, usize block_sz);
KDAPI(void) kdi_GenMemOpsFindNotAnyBlockIndex(usize *idx_addr, byte *ptr, usize ptr_sz, byte *set, byte *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindNotAnyLastBlock(byte *dst, byte *ptr, usize ptr_sz, byte *set, byte *block, usize block_sz);
KDAPI(void) kdi_GenMemOpsFindNotAnyLastBlockIndex(usize *idx_addr, byte *ptr, usize ptr_sz, byte *set, byte *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindNotAnyOfTheBlocks(byte *dst, usize dst_sz, usize *dst_elems, byte *ptr, usize ptr_sz, byte *set, byte *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindAllBlockIndices(usize *idxs, usize idxs_sz, usize *idx_elems, byte *ptr, usize ptr_sz, byte *block, usize block_sz);
KDAPI(void) kdi_GenMemOpsFindAllBlockIndicesU8(u8 *idxs, usize idxs_sz, usize *idx_elems, byte *ptr, usize ptr_sz, byte *block, usize block_sz);
KDAPI(void) kdi_GenMemOpsFindAllBlockIndicesU16(u16 *idxs, usize idxs_sz, usize *idx_elems, byte *ptr, usize ptr_sz, byte *block, usize block_sz);
KDAPI(void) kdi_GenMemOpsFindAllBlockIndicesU32(u32 *idxs, usize idxs_sz, usize *idx_elems, byte *ptr, usize ptr_sz, byte *block, usize block_sz);
#if defined KD_ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsFindAllBlockIndicesU64(u64 *idxs, usize idxs_sz, usize *idx_elems, byte *ptr, usize ptr_sz, byte *block, usize block_sz);
#endif

KDAPI(void) kdi_GenMemOpsSequenceAt(byte *dst, byte *base, usize base_sz, usize idx, usize sequence_sz);
KDAPI(void) kdi_GenMemOpsSetSequenceAt(byte *base, usize base_sz, usize idx, byte *sequence, usize sequence_sz);
KDAPI(void) kdi_GenMemOpsInsertSequenceAt(byte *base, usize base_capacity, usize *base_elems, usize idx, byte *sequence, usize sequence_sz);
KDAPI(void) kdi_GenMemOpsRemoveSequenceAt(byte *base, usize base_capacity, usize *base_elems, usize idx, byte *sequence, usize sequence_sz);

KDAPI(void) kdi_GenMemOpsFindSequence(usize *idx_addr, byte *ptr, usize ptr_sz, byte *sequence, usize sequence_sz);
KDAPI(void) kdi_GenMemOpsFindLastSequence(usize *idx_addr, byte *ptr, usize ptr_sz, byte *sequence, usize sequence_sz);

KDAPI(void) kdi_GenMemOpsReplaceSequence(byte *ptr, usize ptr_capacity, usize *ptr_elems, byte *find_sequence, usize find_sequence_sz, byte *new_sequence, usize new_sequence_sz);
KDAPI(void) kdi_GenMemOpsReplaceLastSequence(byte *ptr, usize ptr_capacity, usize *ptr_elems, byte *find_sequence, usize find_sequence_sz, byte *new_sequence, usize new_sequence_sz);

KDAPI(void) kdi_GenMemOpsReplaceAllSequences(usize *replaced_count_addr, byte *ptr, usize ptr_capacity, usize *ptr_elems, byte *find_sequence, usize find_sequence_sz, byte *new_sequence, usize new_sequence_sz);

KDAPI(void) kdi_GenMemOpsCountSequences(usize *count_addr, byte *ptr, usize ptr_sz, byte *sequence, usize sequence_sz);

KDAPI(void) kdi_GenMemOpsFindAllSequences(usize *idxs, usize idxs_sz, usize *idx_elems, byte *ptr, usize ptr_sz, byte *sequence, usize sequence_sz);
KDAPI(void) kdi_GenMemOpsFindAllSequencesU8(u8 *idxs, usize idxs_sz, usize *idx_elems, byte *ptr, usize ptr_sz, byte *sequence, usize sequence_sz);
KDAPI(void) kdi_GenMemOpsFindAllSequencesU16(u16 *idxs, usize idxs_sz, usize *idx_elems, byte *ptr, usize ptr_sz, byte *sequence, usize sequence_sz);
KDAPI(void) kdi_GenMemOpsFindAllSequencesU32(u32 *idxs, usize idxs_sz, usize *idx_elems, byte *ptr, usize ptr_sz, byte *sequence, usize sequence_sz);
#if defined KD_ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsFindAllSequencesU64(u64 *idxs, usize idxs_sz, usize *idx_elems, byte *ptr, usize ptr_sz, byte *sequence, usize sequence_sz);
#endif

KDAPI(void) kdi_GenMemOpsReverseBytes(byte *ptr, usize dst_sz);
KDAPI(void) kdi_GenMemOpsReverseBlocks(byte *ptr, usize dst_sz, usize block_sz);

KDAPI(void) kdi_GenMemOpsRotateBytesRight(byte *ptr, usize dst_sz, usize k);
KDAPI(void) kdi_GenMemOpsRotateBytesLeft(byte *ptr, usize dst_sz, usize k);

KDAPI(void) kdi_GenMemOpsRotateBlocksRight(byte *ptr, usize dst_sz, usize k, usize block_sz);
KDAPI(void) kdi_GenMemOpsRotateBlocksLeft(byte *ptr, usize dst_sz, usize k, usize block_sz);

/*
KDAPI(void) kdi_GenMemOpsCopyRegion(byte *dst, usize dst_sz, byte *src, usize src_sz);
KDAPI(void) kdi_GenMemOpsCopyBytesRange(byte *dst_base, usize dst_base_sz, byte *src_base, usize src_base_sz, usize dst_idx, usize src_idx, usize count);
KDAPI(void) kdi_GenMemOpsCopyBlocksRange(byte *dst_base, usize dst_base_sz, byte *src_base, usize src_base_sz, usize dst_idx, usize src_idx, usize count, usize block_sz);
KDAPI(void) kdi_GenMemOpsMoveRegion(byte *dst, usize dst_sz, byte *src, usize src_sz);

KDAPI(void) kdi_GenMemOpsMoveBytesRange(byte *dst_base, usize dst_base_sz, byte *src_base, usize src_base_sz, usize dst_idx, usize src_idx, usize count);
KDAPI(void) kdi_GenMemOpsMoveBlocksRange(byte *dst_base, usize dst_base_sz, byte *src_base, usize src_base_sz, usize dst_idx, usize src_idx, usize count, usize block_sz);
*/

EXTERN_END


#endif /* KDI_GEN_MEM_OPS_H_ */
