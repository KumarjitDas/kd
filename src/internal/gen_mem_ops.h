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


EXTERN_END


#endif /* KDI_GEN_MEM_OPS_H_ */
