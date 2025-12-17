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


EXTERN_END


#endif /* KDI_GEN_MEM_OPS_H_ */
