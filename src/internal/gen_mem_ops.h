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
#include "../../include/kd/api.h"
#include "../../include/kd/fixed_width.h"
#include "../../include/kd/bool.h"
#include "../../include/kd/floating_point.h"


EXTERN_BEGIN


KDAPI(void) kdi_GenMemOpsCopy(byte *dst, byte *src, usize sz);
KDAPI(void) kdi_GenMemOpsMove(byte *dst, byte *src, usize sz);

KDAPI(void) kdi_GenMemOpsConcat(byte *dst, usize dst_sz, byte *src_1, usize src_1_sz, byte *src_2, usize src_2_sz);

KDAPI(void) kdi_GenMemOpsSetBlocks_U8(u8 *dst, usize sz, u8 val);
KDAPI(void) kdi_GenMemOpsSetBlocks_U16(u16 *dst, usize sz, u16 val);
KDAPI(void) kdi_GenMemOpsSetBlocks_U32(u32 *dst, usize sz, u32 val);
#if defined ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsSetBlocks_U64(u64 *dst, usize sz, u64 val);
#endif
KDAPI(void) kdi_GenMemOpsSetBlocks_Un(byte *dst, usize dsst_sz, byte *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsReverseBlocks_U8(u8 *ptr, usize sz);
KDAPI(void) kdi_GenMemOpsReverseBlocks_U16(u16 *ptr, usize sz);
KDAPI(void) kdi_GenMemOpsReverseBlocks_U32(u32 *ptr, usize sz);
#if defined ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsReverseBlocks_U64(u64 *ptr, usize sz);
#endif
KDAPI(void) kdi_GenMemOpsReverseBlocks_Un(byte *ptr, usize ptr_sz, usize block_sz);

KDAPI(void) kdi_GenMemOpsSwapBlocks_U8(u8 *ptr, usize idx_1, usize idx_2);
KDAPI(void) kdi_GenMemOpsSwapBlocks_U16(u16 *ptr, usize idx_1, usize idx_2);
KDAPI(void) kdi_GenMemOpsSwapBlocks_U32(u32 *ptr, usize idx_1, usize idx_2);
#if defined ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsSwapBlocks_U64(u64 *ptr, usize idx_1, usize idx_2);
#endif
KDAPI(void) kdi_GenMemOpsSwapBlocks_Un(byte *ptr, usize idx_1, usize idx_2, usize block_sz);

KDAPI(void) kdi_GenMemOpsSwapBlockRefs_U8(u8 *ptr_1, u8 *ptr_2);
KDAPI(void) kdi_GenMemOpsSwapBlockRefs_U16(u16 *ptr_1, u16 *ptr_2);
KDAPI(void) kdi_GenMemOpsSwapBlockRefs_U32(u32 *ptr_1, u32 *ptr_2);
#if defined ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsSwapBlockRefs_U64(u64 *ptr_1, u64 *ptr_2);
#endif
KDAPI(void) kdi_GenMemOpsSwapBlockRefs_Un(byte *ptr_1, byte *ptr_2, usize block_sz);

KDAPI(void) kdi_GenMemOpsRotateRight(byte *ptr, usize sz, usize k);
KDAPI(void) kdi_GenMemOpsRotateLeft(byte *ptr, usize sz, usize k);

KDAPI(void) kdi_GenMemOpsIsEqual(bool *result, byte *ptr_1, byte *ptr_2, usize sz);

KDAPI(void) kdi_GenMemOpsIsVal(bool *result, byte *ptr, usize sz, byte val);

KDAPI(void) kdi_GenMemOpsRegionOverlap(bool *result, byte *ptr_1, usize ptr_1_sz, byte *ptr_2, usize ptr_2_sz);
KDAPI(void) kdi_GenMemOpsRegionContains(bool *result, byte *base, usize base_sz, byte *ptr, usize ptr_sz);

KDAPI(void) kdi_GenMemOpsElemCountFromBytes(usize *count, usize base_sz, usize elem_sz);

KDAPI(void) kdi_GenMemOpsBlockAt_U8(u8 *dst, u8 *src, usize idx);
KDAPI(void) kdi_GenMemOpsBlockAt_U16(u16 *dst, u16 *src, usize idx);
KDAPI(void) kdi_GenMemOpsBlockAt_U32(u32 *dst, u32 *src, usize idx);
#if defined ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsBlockAt_U64(u64 *dst, u64 *src, usize idx);
#endif
KDAPI(void) kdi_GenMemOpsBlockAt_Un(byte *dst, byte *src, usize idx, usize block_sz);

KDAPI(void) kdi_GenMemOpsSetBlockAt_U8(u8 *dst, usize idx, u8 val);
KDAPI(void) kdi_GenMemOpsSetBlockAt_U16(u16 *dst, usize idx, u16 val);
KDAPI(void) kdi_GenMemOpsSetBlockAt_U32(u32 *dst, usize idx, u32 val);
#if defined ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsSetBlockAt_U64(u64 *dst, usize idx, u64 val);
#endif
KDAPI(void) kdi_GenMemOpsSetBlockAt_Un(byte *dst, usize idx, byte *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsInsertBlockAt_U8(u8 *dst, usize *dst_sz, usize idx, u8 val);
KDAPI(void) kdi_GenMemOpsInsertBlockAt_U16(u16 *dst, usize *dst_sz, usize idx, u16 val);
KDAPI(void) kdi_GenMemOpsInsertBlockAt_U32(u32 *dst, usize *dst_sz, usize idx, u32 val);
#if defined ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsInsertBlockAt_U64(u64 *dst, usize *dst_sz, usize idx, u64 val);
#endif
KDAPI(void) kdi_GenMemOpsInsertBlockAt_Un(byte *dst, usize *dst_sz, usize idx, byte *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsRemoveBlockAt_U8(u8 *dst, usize *dst_sz, usize idx);
KDAPI(void) kdi_GenMemOpsRemoveBlockAt_U16(u16 *dst, usize *dst_sz, usize idx);
KDAPI(void) kdi_GenMemOpsRemoveBlockAt_U32(u32 *dst, usize *dst_sz, usize idx);
#if defined ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsRemoveBlockAt_U64(u64 *dst, usize *dst_sz, usize idx);
#endif
KDAPI(void) kdi_GenMemOpsRemoveBlockAt_Un(byte *dst, usize *dst_sz, usize idx, usize block_sz);

KDAPI(void) kdi_GenMemOpsCountBlocks_U8(usize *count, u8 *ptr, usize sz, u8 item);
KDAPI(void) kdi_GenMemOpsCountBlocks_U16(usize *count, u16 *ptr, usize sz, u16 item);
KDAPI(void) kdi_GenMemOpsCountBlocks_U32(usize *count, u32 *ptr, usize sz, u32 item);
#if defined ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsCountBlocks_U64(usize *count, u64 *ptr, usize sz, u64 item);
#endif
KDAPI(void) kdi_GenMemOpsCountBlocks_Un(usize *count, byte *ptr, usize sz, byte *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsCountNotBlocks_U8(usize *count, u8 *ptr, usize sz, u8 item);
KDAPI(void) kdi_GenMemOpsCountNotBlocks_U16(usize *count, u16 *ptr, usize sz, u16 item);
KDAPI(void) kdi_GenMemOpsCountNotBlocks_U32(usize *count, u32 *ptr, usize sz, u32 item);
#if defined ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsCountNotBlocks_U64(usize *count, u64 *ptr, usize sz, u64 item);
#endif
KDAPI(void) kdi_GenMemOpsCountNotBlocks_Un(usize *count, byte *ptr, usize sz, byte *block, usize block_sz);

KDAPI(bool) kdi_GenMemOpsFindBlockIndex_U8(usize *idx, u8 *ptr, usize sz, u8 item);
KDAPI(bool) kdi_GenMemOpsFindBlockIndex_U16(usize *idx, u16 *ptr, usize sz, u16 item);
KDAPI(bool) kdi_GenMemOpsFindBlockIndex_U32(usize *idx, u32 *ptr, usize sz, u32 item);
#if defined ARCH_64BIT_INT
KDAPI(bool) kdi_GenMemOpsFindBlockIndex_U64(usize *idx, u64 *ptr, usize sz, u64 item);
#endif
KDAPI(bool) kdi_GenMemOpsFindBlockIndex_Un(usize *idx, byte *ptr, usize sz, byte *block, usize block_sz);

KDAPI(bool) kdi_GenMemOpsFindNotBlockIndex_U8(usize *idx, u8 *ptr, usize sz, u8 item);
KDAPI(bool) kdi_GenMemOpsFindNotBlockIndex_U16(usize *idx, u16 *ptr, usize sz, u16 item);
KDAPI(bool) kdi_GenMemOpsFindNotBlockIndex_U32(usize *idx, u32 *ptr, usize sz, u32 item);
#if defined ARCH_64BIT_INT
KDAPI(bool) kdi_GenMemOpsFindNotBlockIndex_U64(usize *idx, u64 *ptr, usize sz, u64 item);
#endif
KDAPI(bool) kdi_GenMemOpsFindNotBlockIndex_Un(usize *idx, byte *ptr, usize sz, byte *block, usize block_sz);

KDAPI(bool) kdi_GenMemOpsFindLastBlockIndex_U8(usize *idx, u8 *ptr, usize sz, u8 item);
KDAPI(bool) kdi_GenMemOpsFindLastBlockIndex_U16(usize *idx, u16 *ptr, usize sz, u16 item);
KDAPI(bool) kdi_GenMemOpsFindLastBlockIndex_U32(usize *idx, u32 *ptr, usize sz, u32 item);
#if defined ARCH_64BIT_INT
KDAPI(bool) kdi_GenMemOpsFindLastBlockIndex_U64(usize *idx, u64 *ptr, usize sz, u64 item);
#endif
KDAPI(bool) kdi_GenMemOpsFindLastBlockIndex_Un(usize *idx, byte *ptr, usize sz, byte *block, usize block_sz);

KDAPI(bool) kdi_GenMemOpsFindLastNotBlockIndex_U8(usize *idx, u8 *ptr, usize sz, u8 item);
KDAPI(bool) kdi_GenMemOpsFindLastNotBlockIndex_U16(usize *idx, u16 *ptr, usize sz, u16 item);
KDAPI(bool) kdi_GenMemOpsFindLastNotBlockIndex_U32(usize *idx, u32 *ptr, usize sz, u32 item);
#if defined ARCH_64BIT_INT
KDAPI(bool) kdi_GenMemOpsFindLastNotBlockIndex_U64(usize *idx, u64 *ptr, usize sz, u64 item);
#endif
KDAPI(bool) kdi_GenMemOpsFindLastNotBlockIndex_Un(usize *idx, byte *ptr, usize sz, byte *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindBlockIndicesU8_IdxU8(u8 *idxs, usize idxs_sz, usize *found, u8 *ptr, usize ptr_sz, u8 item);
KDAPI(void) kdi_GenMemOpsFindBlockIndicesU16_IdxU8(u8 *idxs, usize idxs_sz, usize *found, u16 *ptr, usize ptr_sz, u16 item);
KDAPI(void) kdi_GenMemOpsFindBlockIndicesU32_IdxU8(u8 *idxs, usize idxs_sz, usize *found, u32 *ptr, usize ptr_sz, u32 item);
#if defined ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsFindBlockIndicesU64_IdxU8(u8 *idxs, usize idxs_sz, usize *found, u64 *ptr, usize ptr_sz, u64 item);
#endif
KDAPI(void) kdi_GenMemOpsFindBlockIndicesUn_IdxU8(u8 *idxs, usize idxs_sz, usize *found, byte *ptr, usize ptr_sz, byte *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindBlockIndicesU8_IdxU16(u16 *idxs, usize idxs_sz, usize *found, u8 *ptr, usize ptr_sz, u8 item);
KDAPI(void) kdi_GenMemOpsFindBlockIndicesU16_IdxU16(u16 *idxs, usize idxs_sz, usize *found, u16 *ptr, usize ptr_sz, u16 item);
KDAPI(void) kdi_GenMemOpsFindBlockIndicesU32_IdxU16(u16 *idxs, usize idxs_sz, usize *found, u32 *ptr, usize ptr_sz, u32 item);
#if defined ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsFindBlockIndicesU64_IdxU16(u16 *idxs, usize idxs_sz, usize *found, u64 *ptr, usize ptr_sz, u64 item);
#endif
KDAPI(void) kdi_GenMemOpsFindBlockIndicesUn_IdxU16(u16 *idxs, usize idxs_sz, usize *found, byte *ptr, usize ptr_sz, byte *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindBlockIndicesU8_IdxU32(u32 *idxs, usize idxs_sz, usize *found, u8 *ptr, usize ptr_sz, u8 item);
KDAPI(void) kdi_GenMemOpsFindBlockIndicesU16_IdxU32(u32 *idxs, usize idxs_sz, usize *found, u16 *ptr, usize ptr_sz, u16 item);
KDAPI(void) kdi_GenMemOpsFindBlockIndicesU32_IdxU32(u32 *idxs, usize idxs_sz, usize *found, u32 *ptr, usize ptr_sz, u32 item);
#if defined ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsFindBlockIndicesU64_IdxU32(u32 *idxs, usize idxs_sz, usize *found, u64 *ptr, usize ptr_sz, u64 item);
#endif
KDAPI(void) kdi_GenMemOpsFindBlockIndicesUn_IdxU32(u32 *idxs, usize idxs_sz, usize *found, byte *ptr, usize ptr_sz, byte *block, usize block_sz);

#if defined ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsFindBlockIndicesU8_IdxU64(u64 *idxs, usize idxs_sz, usize *found, u8 *ptr, usize ptr_sz, u8 item);
KDAPI(void) kdi_GenMemOpsFindBlockIndicesU16_IdxU64(u64 *idxs, usize idxs_sz, usize *found, u16 *ptr, usize ptr_sz, u16 item);
KDAPI(void) kdi_GenMemOpsFindBlockIndicesU32_IdxU64(u64 *idxs, usize idxs_sz, usize *found, u32 *ptr, usize ptr_sz, u32 item);
KDAPI(void) kdi_GenMemOpsFindBlockIndicesU64_IdxU64(u64 *idxs, usize idxs_sz, usize *found, u64 *ptr, usize ptr_sz, u64 item);
KDAPI(void) kdi_GenMemOpsFindBlockIndicesUn_IdxU64(u64 *idxs, usize idxs_sz, usize *found, byte *ptr, usize ptr_sz, byte *block, usize block_sz);
#endif

KDAPI(void) kdi_GenMemOpsFindNotBlockIndicesU8_IdxU8(u8 *idxs, usize idxs_sz, usize *found, u8 *ptr, usize ptr_sz, u8 item);
KDAPI(void) kdi_GenMemOpsFindNotBlockIndicesU16_IdxU8(u8 *idxs, usize idxs_sz, usize *found, u16 *ptr, usize ptr_sz, u16 item);
KDAPI(void) kdi_GenMemOpsFindNotBlockIndicesU32_IdxU8(u8 *idxs, usize idxs_sz, usize *found, u32 *ptr, usize ptr_sz, u32 item);
#if defined ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsFindNotBlockIndicesU64_IdxU8(u8 *idxs, usize idxs_sz, usize *found, u64 *ptr, usize ptr_sz, u64 item);
#endif
KDAPI(void) kdi_GenMemOpsFindNotBlockIndicesUn_IdxU8(u8 *idxs, usize idxs_sz, usize *found, byte *ptr, usize ptr_sz, byte *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindNotBlockIndicesU8_IdxU16(u16 *idxs, usize idxs_sz, usize *found, u8 *ptr, usize ptr_sz, u8 item);
KDAPI(void) kdi_GenMemOpsFindNotBlockIndicesU16_IdxU16(u16 *idxs, usize idxs_sz, usize *found, u16 *ptr, usize ptr_sz, u16 item);
KDAPI(void) kdi_GenMemOpsFindNotBlockIndicesU32_IdxU16(u16 *idxs, usize idxs_sz, usize *found, u32 *ptr, usize ptr_sz, u32 item);
#if defined ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsFindNotBlockIndicesU64_IdxU16(u16 *idxs, usize idxs_sz, usize *found, u64 *ptr, usize ptr_sz, u64 item);
#endif
KDAPI(void) kdi_GenMemOpsFindNotBlockIndicesUn_IdxU16(u16 *idxs, usize idxs_sz, usize *found, byte *ptr, usize ptr_sz, byte *block, usize block_sz);

KDAPI(void) kdi_GenMemOpsFindNotBlockIndicesU8_IdxU32(u32 *idxs, usize idxs_sz, usize *found, u8 *ptr, usize ptr_sz, u8 item);
KDAPI(void) kdi_GenMemOpsFindNotBlockIndicesU16_IdxU32(u32 *idxs, usize idxs_sz, usize *found, u16 *ptr, usize ptr_sz, u16 item);
KDAPI(void) kdi_GenMemOpsFindNotBlockIndicesU32_IdxU32(u32 *idxs, usize idxs_sz, usize *found, u32 *ptr, usize ptr_sz, u32 item);
#if defined ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsFindNotBlockIndicesU64_IdxU32(u32 *idxs, usize idxs_sz, usize *found, u64 *ptr, usize ptr_sz, u64 item);
#endif
KDAPI(void) kdi_GenMemOpsFindNotBlockIndicesUn_IdxU32(u32 *idxs, usize idxs_sz, usize *found, byte *ptr, usize ptr_sz, byte *block, usize block_sz);

#if defined ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsFindNotBlockIndicesU8_IdxU64(u64 *idxs, usize idxs_sz, usize *found, u8 *ptr, usize ptr_sz, u8 item);
KDAPI(void) kdi_GenMemOpsFindNotBlockIndicesU16_IdxU64(u64 *idxs, usize idxs_sz, usize *found, u16 *ptr, usize ptr_sz, u16 item);
KDAPI(void) kdi_GenMemOpsFindNotBlockIndicesU32_IdxU64(u64 *idxs, usize idxs_sz, usize *found, u32 *ptr, usize ptr_sz, u32 item);
KDAPI(void) kdi_GenMemOpsFindNotBlockIndicesU64_IdxU64(u64 *idxs, usize idxs_sz, usize *found, u64 *ptr, usize ptr_sz, u64 item);
KDAPI(void) kdi_GenMemOpsFindNotBlockIndicesUn_IdxU64(u64 *idxs, usize idxs_sz, usize *found, byte *ptr, usize ptr_sz, byte *block, usize block_sz);
#endif

KDAPI(void) kdi_GenMemOpsReplaceBlock_U8(u8 *ptr, usize sz, u8 find_item, u8 new_item);
KDAPI(void) kdi_GenMemOpsReplaceBlock_U16(u16 *ptr, usize sz, u16 find_item, u16 new_item);
KDAPI(void) kdi_GenMemOpsReplaceBlock_U32(u32 *ptr, usize sz, u32 find_item, u32 new_item);
#if defined ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsReplaceBlock_U64(u64 *ptr, usize sz, u64 find_item, u64 new_item);
#endif
KDAPI(void) kdi_GenMemOpsReplaceBlock_Un(byte *ptr, usize ptr_sz, byte *find_block, byte *new_block, usize block_sz);

KDAPI(void) kdi_GenMemOpsReplaceNotBlock_U8(u8 *ptr, usize sz, u8 find_item, u8 new_item);
KDAPI(void) kdi_GenMemOpsReplaceNotBlock_U16(u16 *ptr, usize sz, u16 find_item, u16 new_item);
KDAPI(void) kdi_GenMemOpsReplaceNotBlock_U32(u32 *ptr, usize sz, u32 find_item, u32 new_item);
#if defined ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsReplaceNotBlock_U64(u64 *ptr, usize sz, u64 find_item, u64 new_item);
#endif
KDAPI(void) kdi_GenMemOpsReplaceNotBlock_Un(byte *ptr, usize ptr_sz, byte *find_block, byte *new_block, usize block_sz);

KDAPI(void) kdi_GenMemOpsReplaceLastBlock_U8(u8 *ptr, usize sz, u8 find_item, u8 new_item);
KDAPI(void) kdi_GenMemOpsReplaceLastBlock_U16(u16 *ptr, usize sz, u16 find_item, u16 new_item);
KDAPI(void) kdi_GenMemOpsReplaceLastBlock_U32(u32 *ptr, usize sz, u32 find_item, u32 new_item);
#if defined ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsReplaceLastBlock_U64(u64 *ptr, usize sz, u64 find_item, u64 new_item);
#endif
KDAPI(void) kdi_GenMemOpsReplaceLastBlock_Un(byte *ptr, usize ptr_sz, byte *find_block, byte *new_block, usize block_sz);

KDAPI(void) kdi_GenMemOpsReplaceLastNotBlock_U8(u8 *ptr, usize sz, u8 find_item, u8 new_item);
KDAPI(void) kdi_GenMemOpsReplaceLastNotBlock_U16(u16 *ptr, usize sz, u16 find_item, u16 new_item);
KDAPI(void) kdi_GenMemOpsReplaceLastNotBlock_U32(u32 *ptr, usize sz, u32 find_item, u32 new_item);
#if defined ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsReplaceLastNotBlock_U64(u64 *ptr, usize sz, u64 find_item, u64 new_item);
#endif
KDAPI(void) kdi_GenMemOpsReplaceLastNotBlock_Un(byte *ptr, usize ptr_sz, byte *find_block, byte *new_block, usize block_sz);

KDAPI(void) kdi_GenMemOpsReplaceAllBlocks_U8(u8 *ptr, usize sz, usize *count, u8 find_item, u8 new_item);
KDAPI(void) kdi_GenMemOpsReplaceAllBlocks_U16(u16 *ptr, usize sz, usize *count, u16 find_item, u16 new_item);
KDAPI(void) kdi_GenMemOpsReplaceAllBlocks_U32(u32 *ptr, usize sz, usize *count, u32 find_item, u32 new_item);
#if defined ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsReplaceAllBlocks_U64(u64 *ptr, usize sz, usize *count, u64 find_item, u64 new_item);
#endif
KDAPI(void) kdi_GenMemOpsReplaceAllBlocks_Un(byte *ptr, usize ptr_sz, usize *count, byte *find_block, byte *new_block, usize block_sz);

KDAPI(void) kdi_GenMemOpsReplaceAllNotBlocks_U8(u8 *ptr, usize sz, usize *count, u8 find_item, u8 new_item);
KDAPI(void) kdi_GenMemOpsReplaceAllNotBlocks_U16(u16 *ptr, usize sz, usize *count, u16 find_item, u16 new_item);
KDAPI(void) kdi_GenMemOpsReplaceAllNotBlocks_U32(u32 *ptr, usize sz, usize *count, u32 find_item, u32 new_item);
#if defined ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsReplaceAllNotBlocks_U64(u64 *ptr, usize sz, usize *count, u64 find_item, u64 new_item);
#endif
KDAPI(void) kdi_GenMemOpsReplaceAllNotBlocks_Un(byte *ptr, usize ptr_sz, usize *count, byte *find_block, byte *new_block, usize block_sz);


EXTERN_END


#endif /* KDI_GEN_MEM_OPS_H_ */
