/**
 * @file kdi_gen_mem_ops.h
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


KD_EXTERN_BEGIN


#define kdi_GenMemOpsSwapBlocks_Byte(ptr, idx1, idx2) kdi_GenMemOpsSwapBlocks_U8(KD_PU8_C(ptr), KD_USIZE_C(idx1), KD_USIZE_C(idx2))
#define kdi_GenMemOpsSwapBlocks_I8(ptr, idx1, idx2)   kdi_GenMemOpsSwapBlocks_U8(KD_PU8_C(ptr), KD_USIZE_C(idx1), KD_USIZE_C(idx2))
#define kdi_GenMemOpsSwapBlocks_I16(ptr, idx1, idx2)  kdi_GenMemOpsSwapBlocks_U16(KD_PU16_C(ptr), KD_USIZE_C(idx1), KD_USIZE_C(idx2))
#define kdi_GenMemOpsSwapBlocks_I32(ptr, idx1, idx2)  kdi_GenMemOpsSwapBlocks_U32(KD_PU32_C(ptr), KD_USIZE_C(idx1), KD_USIZE_C(idx2))

#if defined KD_ARCH_64BIT_INT
    #define kdi_GenMemOpsSwapBlocks_I64(ptr, idx1, idx2) kdi_GenMemOpsSwapBlocks_U64(KD_PU64_C(ptr), KD_USIZE_C(idx1), KD_USIZE_C(idx2))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsSwapBlocks_Imin(ptr, idx1, idx2) kdi_GenMemOpsSwapBlocks_U8(KD_PU8_C(ptr), KD_USIZE_C(idx1), KD_USIZE_C(idx2))
#define kdi_GenMemOpsSwapBlocks_Umin(ptr, idx1, idx2) kdi_GenMemOpsSwapBlocks_U8(KD_PU8_C(ptr), KD_USIZE_C(idx1), KD_USIZE_C(idx2))

#if defined KD_ARCH_64BIT_INT
    #define kdi_GenMemOpsSwapBlocks_Imax(ptr, idx1, idx2)  kdi_GenMemOpsSwapBlocks_U64(KD_PU64_C(ptr), KD_USIZE_C(idx1), KD_USIZE_C(idx2))
    #define kdi_GenMemOpsSwapBlocks_Umax(ptr, idx1, idx2)  kdi_GenMemOpsSwapBlocks_U64(KD_PU64_C(ptr), KD_USIZE_C(idx1), KD_USIZE_C(idx2))
    #define kdi_GenMemOpsSwapBlocks_Word(ptr, idx1, idx2)  kdi_GenMemOpsSwapBlocks_U64(KD_PU64_C(ptr), KD_USIZE_C(idx1), KD_USIZE_C(idx2))
    #define kdi_GenMemOpsSwapBlocks_Usize(ptr, idx1, idx2) kdi_GenMemOpsSwapBlocks_U64(KD_PU64_C(ptr), KD_USIZE_C(idx1), KD_USIZE_C(idx2))
#else
    #define kdi_GenMemOpsSwapBlocks_Imax(ptr, idx1, idx2)  kdi_GenMemOpsSwapBlocks_U32(KD_PU32_C(ptr), KD_USIZE_C(idx1), KD_USIZE_C(idx2))
    #define kdi_GenMemOpsSwapBlocks_Umax(ptr, idx1, idx2)  kdi_GenMemOpsSwapBlocks_U32(KD_PU32_C(ptr), KD_USIZE_C(idx1), KD_USIZE_C(idx2))
    #define kdi_GenMemOpsSwapBlocks_Word(ptr, idx1, idx2)  kdi_GenMemOpsSwapBlocks_U32(KD_PU32_C(ptr), KD_USIZE_C(idx1), KD_USIZE_C(idx2))
    #define kdi_GenMemOpsSwapBlocks_Usize(ptr, idx1, idx2) kdi_GenMemOpsSwapBlocks_U32(KD_PU32_C(ptr), KD_USIZE_C(idx1), KD_USIZE_C(idx2))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsSwapBlocks_Bool(ptr, idx1, idx2) kdi_GenMemOpsSwapBlocks_U32(KD_PU32_C(ptr), KD_USIZE_C(idx1), KD_USIZE_C(idx2))
#define kdi_GenMemOpsSwapBlocks_Chr(ptr, idx1, idx2)  kdi_GenMemOpsSwapBlocks_U32(KD_PU32_C(ptr), KD_USIZE_C(idx1), KD_USIZE_C(idx2))

#if defined KD_ARCH_64BIT_PTR
    #define kdi_GenMemOpsSwapBlocks_Ptr(ptr, idx1, idx2) kdi_GenMemOpsSwapBlocks_U64(KD_PU64_C(ptr), KD_USIZE_C(idx1), KD_USIZE_C(idx2))
#else
    #define kdi_GenMemOpsSwapBlocks_Ptr(ptr, idx1, idx2) kdi_GenMemOpsSwapBlocks_U32(KD_PU32_C(ptr), KD_USIZE_C(idx1), KD_USIZE_C(idx2))
#endif /* KD_ARCH_64BIT_PTR */


#define kdi_GenMemOpsReverseBlocks_Byte(ptr, len) kdi_GenMemOpsReverseBlocks_U8(KD_PU8_C(ptr), KD_USIZE_C(len))
#define kdi_GenMemOpsReverseBlocks_I8(ptr, len)   kdi_GenMemOpsReverseBlocks_U8(KD_PU8_C(ptr), KD_USIZE_C(len))
#define kdi_GenMemOpsReverseBlocks_I16(ptr, len)  kdi_GenMemOpsReverseBlocks_U16(KD_PU16_C(ptr), KD_USIZE_C(len))
#define kdi_GenMemOpsReverseBlocks_I32(ptr, len)  kdi_GenMemOpsReverseBlocks_U32(KD_PU32_C(ptr), KD_USIZE_C(len))

#if defined KD_ARCH_64BIT_INT
    #define kdi_GenMemOpsReverseBlocks_I64(ptr, len) kdi_GenMemOpsReverseBlocks_U64(KD_PU64_C(ptr), KD_USIZE_C(len))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsReverseBlocks_Imin(ptr, len) kdi_GenMemOpsReverseBlocks_U8(KD_PU8_C(ptr), KD_USIZE_C(len))
#define kdi_GenMemOpsReverseBlocks_Umin(ptr, len) kdi_GenMemOpsReverseBlocks_U8(KD_PU8_C(ptr), KD_USIZE_C(len))

#if defined KD_ARCH_64BIT_INT
    #define kdi_GenMemOpsReverseBlocks_Imax(ptr, len)  kdi_GenMemOpsReverseBlocks_U64(KD_PU64_C(ptr), KD_USIZE_C(len))
    #define kdi_GenMemOpsReverseBlocks_Umax(ptr, len)  kdi_GenMemOpsReverseBlocks_U64(KD_PU64_C(ptr), KD_USIZE_C(len))
    #define kdi_GenMemOpsReverseBlocks_Word(ptr, len)  kdi_GenMemOpsReverseBlocks_U64(KD_PU64_C(ptr), KD_USIZE_C(len))
    #define kdi_GenMemOpsReverseBlocks_Usize(ptr, len) kdi_GenMemOpsReverseBlocks_U64(KD_PU64_C(ptr), KD_USIZE_C(len))
#else
    #define kdi_GenMemOpsReverseBlocks_Imax(ptr, len)  kdi_GenMemOpsReverseBlocks_U32(KD_PU32_C(ptr), KD_USIZE_C(len))
    #define kdi_GenMemOpsReverseBlocks_Umax(ptr, len)  kdi_GenMemOpsReverseBlocks_U32(KD_PU32_C(ptr), KD_USIZE_C(len))
    #define kdi_GenMemOpsReverseBlocks_Word(ptr, len)  kdi_GenMemOpsReverseBlocks_U32(KD_PU32_C(ptr), KD_USIZE_C(len))
    #define kdi_GenMemOpsReverseBlocks_Usize(ptr, len) kdi_GenMemOpsReverseBlocks_U32(KD_PU32_C(ptr), KD_USIZE_C(len))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsReverseBlocks_Bool(ptr, len) kdi_GenMemOpsReverseBlocks_U32(KD_PU32_C(ptr), KD_USIZE_C(len))
#define kdi_GenMemOpsReverseBlocks_Chr(ptr, len)  kdi_GenMemOpsReverseBlocks_U32(KD_PU32_C(ptr), KD_USIZE_C(len))

#if defined KD_ARCH_64BIT_PTR
    #define kdi_GenMemOpsReverseBlocks_Ptr(ptr, len) kdi_GenMemOpsReverseBlocks_U64(KD_PU64_C(ptr), KD_USIZE_C(len))
#else
    #define kdi_GenMemOpsReverseBlocks_Ptr(ptr, len) kdi_GenMemOpsReverseBlocks_U32(KD_PU32_C(ptr), KD_USIZE_C(len))
#endif /* KD_ARCH_64BIT_PTR */


#define kdi_GenMemOpsSetBlocks_Byte(ptr, sz, val) kdi_GenMemOpsSetBlocks_U8(KD_PU8_C(ptr), KD_USIZE_C(sz), (kd_u8_t)(val))
#define kdi_GenMemOpsSetBlocks_I8(ptr, sz, val)   kdi_GenMemOpsSetBlocks_U8(KD_PU8_C(ptr), KD_USIZE_C(sz), (kd_u8_t)(val))
#define kdi_GenMemOpsSetBlocks_I16(ptr, sz, val)  kdi_GenMemOpsSetBlocks_U16(KD_PU16_C(ptr), KD_USIZE_C(sz), (kd_u16_t)(val))
#define kdi_GenMemOpsSetBlocks_I32(ptr, sz, val)  kdi_GenMemOpsSetBlocks_U32(KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))

#if defined KD_ARCH_64BIT_INT
    #define kdi_GenMemOpsSetBlocks_I64(ptr, sz, val) kdi_GenMemOpsSetBlocks_U64(KD_PU64_C(ptr), KD_USIZE_C(sz), (kd_u64_t)(val))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsSetBlocks_Imin(ptr, sz, val) kdi_GenMemOpsSetBlocks_U8(KD_PU8_C(ptr), KD_USIZE_C(sz), (kd_u8_t)(val))
#define kdi_GenMemOpsSetBlocks_Umin(ptr, sz, val) kdi_GenMemOpsSetBlocks_U8(KD_PU8_C(ptr), KD_USIZE_C(sz), (kd_u8_t)(val))

#if defined KD_ARCH_64BIT_INT
    #define kdi_GenMemOpsSetBlocks_Imax(ptr, sz, val)  kdi_GenMemOpsSetBlocks_U64(KD_PU64_C(ptr), KD_USIZE_C(sz), (kd_u64_t)(val))
    #define kdi_GenMemOpsSetBlocks_Umax(ptr, sz, val)  kdi_GenMemOpsSetBlocks_U64(KD_PU64_C(ptr), KD_USIZE_C(sz), (kd_u64_t)(val))
    #define kdi_GenMemOpsSetBlocks_Word(ptr, sz, val)  kdi_GenMemOpsSetBlocks_U64(KD_PU64_C(ptr), KD_USIZE_C(sz), (kd_u64_t)(val))
    #define kdi_GenMemOpsSetBlocks_Usize(ptr, sz, val) kdi_GenMemOpsSetBlocks_U64(KD_PU64_C(ptr), KD_USIZE_C(sz), (kd_u64_t)(val))
#else
    #define kdi_GenMemOpsSetBlocks_Imax(ptr, sz, val)  kdi_GenMemOpsSetBlocks_U32(KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))
    #define kdi_GenMemOpsSetBlocks_Umax(ptr, sz, val)  kdi_GenMemOpsSetBlocks_U32(KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))
    #define kdi_GenMemOpsSetBlocks_Word(ptr, sz, val)  kdi_GenMemOpsSetBlocks_U32(KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))
    #define kdi_GenMemOpsSetBlocks_Usize(ptr, sz, val) kdi_GenMemOpsSetBlocks_U32(KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsSetBlocks_Bool(ptr, sz, val) kdi_GenMemOpsSetBlocks_U32(KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))
#define kdi_GenMemOpsSetBlocks_Chr(ptr, sz, val)  kdi_GenMemOpsSetBlocks_U32(KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))

#if defined KD_ARCH_64BIT_PTR
    #define kdi_GenMemOpsSetBlocks_Ptr(ptr, sz, val) kdi_GenMemOpsSetBlocks_U64(KD_PU64_C(ptr), KD_USIZE_C(sz), (kd_u64_t)(val))
#else
    #define kdi_GenMemOpsSetBlocks_Ptr(ptr, sz, val) kdi_GenMemOpsSetBlocks_U32(KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))
#endif /* KD_ARCH_64BIT_PTR */


#define kdi_GenMemOpsFindBlockWithIndex_Byte(idx_ptr, ptr, sz, val) kdi_GenMemOpsFindBlockWithIndex_U8(KD_PUSIZE_C(idx_ptr), KD_PU8_C(ptr), KD_USIZE_C(sz), (kd_u8_t)(val))
#define kdi_GenMemOpsFindBlockWithIndex_I8(idx_ptr, ptr, sz, val)   kdi_GenMemOpsFindBlockWithIndex_U8(KD_PUSIZE_C(idx_ptr), KD_PU8_C(ptr), KD_USIZE_C(sz), (kd_u8_t)(val))
#define kdi_GenMemOpsFindBlockWithIndex_I16(idx_ptr, ptr, sz, val)  kdi_GenMemOpsFindBlockWithIndex_U16(KD_PUSIZE_C(idx_ptr), KD_PU16_C(ptr), KD_USIZE_C(sz), (kd_u16_t)(val))
#define kdi_GenMemOpsFindBlockWithIndex_I32(idx_ptr, ptr, sz, val)  kdi_GenMemOpsFindBlockWithIndex_U32(KD_PUSIZE_C(idx_ptr), KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))

#if defined KD_ARCH_64BIT_INT
    #define kdi_GenMemOpsFindBlockWithIndex_I64(idx_ptr, ptr, sz, val) kdi_GenMemOpsFindBlockWithIndex_U64(KD_PUSIZE_C(idx_ptr), KD_PU64_C(ptr), KD_USIZE_C(sz), (kd_u64_t)(val))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsFindBlockWithIndex_Imin(idx_ptr, ptr, sz, val) kdi_GenMemOpsFindBlockWithIndex_U8(KD_PUSIZE_C(idx_ptr), KD_PU8_C(ptr), KD_USIZE_C(sz), (kd_u8_t)(val))
#define kdi_GenMemOpsFindBlockWithIndex_Umin(idx_ptr, ptr, sz, val) kdi_GenMemOpsFindBlockWithIndex_U8(KD_PUSIZE_C(idx_ptr), KD_PU8_C(ptr), KD_USIZE_C(sz), (kd_u8_t)(val))

#if defined KD_ARCH_64BIT_INT
    #define kdi_GenMemOpsFindBlockWithIndex_Imax(idx_ptr, ptr, sz, val)  kdi_GenMemOpsFindBlockWithIndex_U64(KD_PUSIZE_C(idx_ptr), KD_PU64_C(ptr), KD_USIZE_C(sz), (kd_u64_t)(val))
    #define kdi_GenMemOpsFindBlockWithIndex_Umax(idx_ptr, ptr, sz, val)  kdi_GenMemOpsFindBlockWithIndex_U64(KD_PUSIZE_C(idx_ptr), KD_PU64_C(ptr), KD_USIZE_C(sz), (kd_u64_t)(val))
    #define kdi_GenMemOpsFindBlockWithIndex_Word(idx_ptr, ptr, sz, val)  kdi_GenMemOpsFindBlockWithIndex_U64(KD_PUSIZE_C(idx_ptr), KD_PU64_C(ptr), KD_USIZE_C(sz), (kd_u64_t)(val))
    #define kdi_GenMemOpsFindBlockWithIndex_Usize(idx_ptr, ptr, sz, val) kdi_GenMemOpsFindBlockWithIndex_U64(KD_PUSIZE_C(idx_ptr), KD_PU64_C(ptr), KD_USIZE_C(sz), (kd_u64_t)(val))
#else
    #define kdi_GenMemOpsFindBlockWithIndex_Imax(idx_ptr, ptr, sz, val)  kdi_GenMemOpsFindBlockWithIndex_U32(KD_PUSIZE_C(idx_ptr), KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))
    #define kdi_GenMemOpsFindBlockWithIndex_Umax(idx_ptr, ptr, sz, val)  kdi_GenMemOpsFindBlockWithIndex_U32(KD_PUSIZE_C(idx_ptr), KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))
    #define kdi_GenMemOpsFindBlockWithIndex_Word(idx_ptr, ptr, sz, val)  kdi_GenMemOpsFindBlockWithIndex_U32(KD_PUSIZE_C(idx_ptr), KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))
    #define kdi_GenMemOpsFindBlockWithIndex_Usize(idx_ptr, ptr, sz, val) kdi_GenMemOpsFindBlockWithIndex_U32(KD_PUSIZE_C(idx_ptr), KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsFindBlockWithIndex_Bool(idx_ptr, ptr, sz, val) kdi_GenMemOpsFindBlockWithIndex_U32(KD_PUSIZE_C(idx_ptr), KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))
#define kdi_GenMemOpsFindBlockWithIndex_Chr(idx_ptr, ptr, sz, val)  kdi_GenMemOpsFindBlockWithIndex_U32(KD_PUSIZE_C(idx_ptr), KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))

#if defined KD_ARCH_64BIT_PTR
    #define kdi_GenMemOpsFindBlockWithIndex_Ptr(idx_ptr, ptr, sz, val) kdi_GenMemOpsFindBlockWithIndex_U64(KD_PUSIZE_C(idx_ptr), KD_PU64_C(ptr), KD_USIZE_C(sz), (kd_u64_t)(val))
#else
    #define kdi_GenMemOpsFindBlockWithIndex_Ptr(idx_ptr, ptr, sz, val) kdi_GenMemOpsFindBlockWithIndex_U32(KD_PUSIZE_C(idx_ptr), KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))
#endif /* KD_ARCH_64BIT_PTR */


#define kdi_GenMemOpsFindLastBlockWithIndex_Byte(idx_ptr, ptr, sz, val) kdi_GenMemOpsFindLastBlockWithIndex_U8(KD_PUSIZE_C(idx_ptr), KD_PU8_C(ptr), KD_USIZE_C(sz), (kd_u8_t)(val))
#define kdi_GenMemOpsFindLastBlockWithIndex_I8(idx_ptr, ptr, sz, val)   kdi_GenMemOpsFindLastBlockWithIndex_U8(KD_PUSIZE_C(idx_ptr), KD_PU8_C(ptr), KD_USIZE_C(sz), (kd_u8_t)(val))
#define kdi_GenMemOpsFindLastBlockWithIndex_I16(idx_ptr, ptr, sz, val)  kdi_GenMemOpsFindLastBlockWithIndex_U16(KD_PUSIZE_C(idx_ptr), KD_PU16_C(ptr), KD_USIZE_C(sz), (kd_u16_t)(val))
#define kdi_GenMemOpsFindLastBlockWithIndex_I32(idx_ptr, ptr, sz, val)  kdi_GenMemOpsFindLastBlockWithIndex_U32(KD_PUSIZE_C(idx_ptr), KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))

#if defined KD_ARCH_64BIT_INT
    #define kdi_GenMemOpsFindLastBlockWithIndex_I64(idx_ptr, ptr, sz, val) kdi_GenMemOpsFindLastBlockWithIndex_U64(KD_PUSIZE_C(idx_ptr), KD_PU64_C(ptr), KD_USIZE_C(sz), (kd_u64_t)(val))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsFindLastBlockWithIndex_Imin(idx_ptr, ptr, sz, val) kdi_GenMemOpsFindLastBlockWithIndex_U8(KD_PUSIZE_C(idx_ptr), KD_PU8_C(ptr), KD_USIZE_C(sz), (kd_u8_t)(val))
#define kdi_GenMemOpsFindLastBlockWithIndex_Umin(idx_ptr, ptr, sz, val) kdi_GenMemOpsFindLastBlockWithIndex_U8(KD_PUSIZE_C(idx_ptr), KD_PU8_C(ptr), KD_USIZE_C(sz), (kd_u8_t)(val))

#if defined KD_ARCH_64BIT_INT
    #define kdi_GenMemOpsFindLastBlockWithIndex_Imax(idx_ptr, ptr, sz, val)  kdi_GenMemOpsFindLastBlockWithIndex_U64(KD_PUSIZE_C(idx_ptr), KD_PU64_C(ptr), KD_USIZE_C(sz), (kd_u64_t)(val))
    #define kdi_GenMemOpsFindLastBlockWithIndex_Umax(idx_ptr, ptr, sz, val)  kdi_GenMemOpsFindLastBlockWithIndex_U64(KD_PUSIZE_C(idx_ptr), KD_PU64_C(ptr), KD_USIZE_C(sz), (kd_u64_t)(val))
    #define kdi_GenMemOpsFindLastBlockWithIndex_Word(idx_ptr, ptr, sz, val)  kdi_GenMemOpsFindLastBlockWithIndex_U64(KD_PUSIZE_C(idx_ptr), KD_PU64_C(ptr), KD_USIZE_C(sz), (kd_u64_t)(val))
    #define kdi_GenMemOpsFindLastBlockWithIndex_Usize(idx_ptr, ptr, sz, val) kdi_GenMemOpsFindLastBlockWithIndex_U64(KD_PUSIZE_C(idx_ptr), KD_PU64_C(ptr), KD_USIZE_C(sz), (kd_u64_t)(val))
#else
    #define kdi_GenMemOpsFindLastBlockWithIndex_Imax(idx_ptr, ptr, sz, val)  kdi_GenMemOpsFindLastBlockWithIndex_U32(KD_PUSIZE_C(idx_ptr), KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))
    #define kdi_GenMemOpsFindLastBlockWithIndex_Umax(idx_ptr, ptr, sz, val)  kdi_GenMemOpsFindLastBlockWithIndex_U32(KD_PUSIZE_C(idx_ptr), KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))
    #define kdi_GenMemOpsFindLastBlockWithIndex_Word(idx_ptr, ptr, sz, val)  kdi_GenMemOpsFindLastBlockWithIndex_U32(KD_PUSIZE_C(idx_ptr), KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))
    #define kdi_GenMemOpsFindLastBlockWithIndex_Usize(idx_ptr, ptr, sz, val) kdi_GenMemOpsFindLastBlockWithIndex_U32(KD_PUSIZE_C(idx_ptr), KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsFindLastBlockWithIndex_Bool(idx_ptr, ptr, sz, val) kdi_GenMemOpsFindLastBlockWithIndex_U32(KD_PUSIZE_C(idx_ptr), KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))
#define kdi_GenMemOpsFindLastBlockWithIndex_Chr(idx_ptr, ptr, sz, val)  kdi_GenMemOpsFindLastBlockWithIndex_U32(KD_PUSIZE_C(idx_ptr), KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))

#if defined KD_ARCH_64BIT_PTR
    #define kdi_GenMemOpsFindLastBlockWithIndex_Ptr(idx_ptr, ptr, sz, val) kdi_GenMemOpsFindLastBlockWithIndex_U64(KD_PUSIZE_C(idx_ptr), KD_PU64_C(ptr), KD_USIZE_C(sz), (kd_u64_t)(val))
#else
    #define kdi_GenMemOpsFindLastBlockWithIndex_Ptr(idx_ptr, ptr, sz, val) kdi_GenMemOpsFindLastBlockWithIndex_U32(KD_PUSIZE_C(idx_ptr), KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))
#endif /* KD_ARCH_64BIT_PTR */


#define kdi_GenMemOpsGetBlocksCount_Byte(ptr, sz, val) kdi_GenMemOpsGetBlocksCount_U8(KD_PU8_C(ptr), KD_USIZE_C(sz), (kd_u8_t)(val))
#define kdi_GenMemOpsGetBlocksCount_I8(ptr, sz, val)   kdi_GenMemOpsGetBlocksCount_U8(KD_PU8_C(ptr), KD_USIZE_C(sz), (kd_u8_t)(val))
#define kdi_GenMemOpsGetBlocksCount_I16(ptr, sz, val)  kdi_GenMemOpsGetBlocksCount_U16(KD_PU16_C(ptr), KD_USIZE_C(sz), (kd_u16_t)(val))
#define kdi_GenMemOpsGetBlocksCount_I32(ptr, sz, val)  kdi_GenMemOpsGetBlocksCount_U32(KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))

#if defined KD_ARCH_64BIT_INT
    #define kdi_GenMemOpsGetBlocksCount_I64(ptr, sz, val) kdi_GenMemOpsGetBlocksCount_U64(KD_PU64_C(ptr), KD_USIZE_C(sz), (kd_u64_t)(val))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsGetBlocksCount_Imin(ptr, sz, val) kdi_GenMemOpsGetBlocksCount_U8(KD_PU8_C(ptr), KD_USIZE_C(sz), (kd_u8_t)(val))
#define kdi_GenMemOpsGetBlocksCount_Umin(ptr, sz, val) kdi_GenMemOpsGetBlocksCount_U8(KD_PU8_C(ptr), KD_USIZE_C(sz), (kd_u8_t)(val))

#if defined KD_ARCH_64BIT_INT
    #define kdi_GenMemOpsGetBlocksCount_Imax(ptr, sz, val)  kdi_GenMemOpsGetBlocksCount_U64(KD_PU64_C(ptr), KD_USIZE_C(sz), (kd_u64_t)(val))
    #define kdi_GenMemOpsGetBlocksCount_Umax(ptr, sz, val)  kdi_GenMemOpsGetBlocksCount_U64(KD_PU64_C(ptr), KD_USIZE_C(sz), (kd_u64_t)(val))
    #define kdi_GenMemOpsGetBlocksCount_Word(ptr, sz, val)  kdi_GenMemOpsGetBlocksCount_U64(KD_PU64_C(ptr), KD_USIZE_C(sz), (kd_u64_t)(val))
    #define kdi_GenMemOpsGetBlocksCount_Usize(ptr, sz, val) kdi_GenMemOpsGetBlocksCount_U64(KD_PU64_C(ptr), KD_USIZE_C(sz), (kd_u64_t)(val))
#else
    #define kdi_GenMemOpsGetBlocksCount_Imax(ptr, sz, val)  kdi_GenMemOpsGetBlocksCount_U32(KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))
    #define kdi_GenMemOpsGetBlocksCount_Umax(ptr, sz, val)  kdi_GenMemOpsGetBlocksCount_U32(KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))
    #define kdi_GenMemOpsGetBlocksCount_Word(ptr, sz, val)  kdi_GenMemOpsGetBlocksCount_U32(KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))
    #define kdi_GenMemOpsGetBlocksCount_Usize(ptr, sz, val) kdi_GenMemOpsGetBlocksCount_U32(KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsGetBlocksCount_Bool(ptr, sz, val) kdi_GenMemOpsGetBlocksCount_U32(KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))
#define kdi_GenMemOpsGetBlocksCount_Chr(ptr, sz, val)  kdi_GenMemOpsGetBlocksCount_U32(KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))

#if defined KD_ARCH_64BIT_PTR
    #define kdi_GenMemOpsGetBlocksCount_Ptr(ptr, sz, val) kdi_GenMemOpsGetBlocksCount_U64(KD_PU64_C(ptr), KD_USIZE_C(sz), (kd_u64_t)(val))
#else
    #define kdi_GenMemOpsGetBlocksCount_Ptr(ptr, sz, val) kdi_GenMemOpsGetBlocksCount_U32(KD_PU32_C(ptr), KD_USIZE_C(sz), (kd_u32_t)(val))
#endif /* KD_ARCH_64BIT_PTR */


#define kdi_GenMemOpsFindAllBlocks_Byte(dst, dst_sz, ptr, ptr_sz, val) kdi_GenMemOpsFindAllBlocks_U8(KD_PTR_C(dst), KD_USIZE_C(dst_sz), KD_PU8_C(ptr), KD_USIZE_C(ptr_sz), KD_U8_C(val))
#define kdi_GenMemOpsFindAllBlocks_I8(dst, dst_sz, ptr, ptr_sz, val)   kdi_GenMemOpsFindAllBlocks_U8(KD_PTR_C(dst), KD_USIZE_C(dst_sz), KD_PU8_C(ptr), KD_USIZE_C(ptr_sz), KD_U8_C(val))
#define kdi_GenMemOpsFindAllBlocks_I16(dst, dst_sz, ptr, ptr_sz, val)  kdi_GenMemOpsFindAllBlocks_U16(KD_PTR_C(dst), KD_USIZE_C(dst_sz), KD_PU16_C(ptr), KD_USIZE_C(ptr_sz), KD_U16_C(val))
#define kdi_GenMemOpsFindAllBlocks_I32(dst, dst_sz, ptr, ptr_sz, val)  kdi_GenMemOpsFindAllBlocks_U32(KD_PTR_C(dst), KD_USIZE_C(dst_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val))

#if defined KD_ARCH_64BIT_INT
    #define kdi_GenMemOpsFindAllBlocks_I64(dst, dst_sz, ptr, ptr_sz, val) kdi_GenMemOpsFindAllBlocks_U64(KD_PTR_C(dst), KD_USIZE_C(dst_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsFindAllBlocks_Imin(dst, dst_sz, ptr, ptr_sz, val) kdi_GenMemOpsFindAllBlocks_U8(KD_PTR_C(dst), KD_USIZE_C(dst_sz), KD_PU8_C(ptr), KD_USIZE_C(ptr_sz), KD_U8_C(val))
#define kdi_GenMemOpsFindAllBlocks_Umin(dst, dst_sz, ptr, ptr_sz, val) kdi_GenMemOpsFindAllBlocks_U8(KD_PTR_C(dst), KD_USIZE_C(dst_sz), KD_PU8_C(ptr), KD_USIZE_C(ptr_sz), KD_U8_C(val))

#if defined KD_ARCH_64BIT_INT
    #define kdi_GenMemOpsFindAllBlocks_Imax(dst, dst_sz, ptr, ptr_sz, val)  kdi_GenMemOpsFindAllBlocks_U64(KD_PTR_C(dst), KD_USIZE_C(dst_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val))
    #define kdi_GenMemOpsFindAllBlocks_Umax(dst, dst_sz, ptr, ptr_sz, val)  kdi_GenMemOpsFindAllBlocks_U64(KD_PTR_C(dst), KD_USIZE_C(dst_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val))
    #define kdi_GenMemOpsFindAllBlocks_Word(dst, dst_sz, ptr, ptr_sz, val)  kdi_GenMemOpsFindAllBlocks_U64(KD_PTR_C(dst), KD_USIZE_C(dst_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val))
    #define kdi_GenMemOpsFindAllBlocks_Usize(dst, dst_sz, ptr, ptr_sz, val) kdi_GenMemOpsFindAllBlocks_U64(KD_PTR_C(dst), KD_USIZE_C(dst_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val))
#else
    #define kdi_GenMemOpsFindAllBlocks_Imax(dst, dst_sz, ptr, ptr_sz, val)  kdi_GenMemOpsFindAllBlocks_U32(KD_PTR_C(dst), KD_USIZE_C(dst_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val))
    #define kdi_GenMemOpsFindAllBlocks_Umax(dst, dst_sz, ptr, ptr_sz, val)  kdi_GenMemOpsFindAllBlocks_U32(KD_PTR_C(dst), KD_USIZE_C(dst_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val))
    #define kdi_GenMemOpsFindAllBlocks_Word(dst, dst_sz, ptr, ptr_sz, val)  kdi_GenMemOpsFindAllBlocks_U32(KD_PTR_C(dst), KD_USIZE_C(dst_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val))
    #define kdi_GenMemOpsFindAllBlocks_Usize(dst, dst_sz, ptr, ptr_sz, val) kdi_GenMemOpsFindAllBlocks_U32(KD_PTR_C(dst), KD_USIZE_C(dst_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsFindAllBlocks_Bool(dst, dst_sz, ptr, ptr_sz, val) kdi_GenMemOpsFindAllBlocks_U32(KD_PTR_C(dst), KD_USIZE_C(dst_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val))
#define kdi_GenMemOpsFindAllBlocks_Chr(dst, dst_sz, ptr, ptr_sz, val)  kdi_GenMemOpsFindAllBlocks_U32(KD_PTR_C(dst), KD_USIZE_C(dst_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val))

#if defined KD_ARCH_64BIT_PTR
    #define kdi_GenMemOpsFindAllBlocks_Ptr(dst, dst_sz, ptr, ptr_sz, val) kdi_GenMemOpsFindAllBlocks_U64(KD_PTR_C(dst), KD_USIZE_C(dst_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val))
#else
    #define kdi_GenMemOpsFindAllBlocks_Ptr(dst, dst_sz, ptr, ptr_sz, val) kdi_GenMemOpsFindAllBlocks_U32(KD_PTR_C(dst), KD_USIZE_C(dst_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val))
#endif /* KD_ARCH_64BIT_PTR */


#define kdi_GenMemOpsFindAllBlockIndices_Byte_Idx8(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U8_Idx8(KD_PU8_C(idxs), KD_USIZE_C(idxs_sz), KD_PU8_C(ptr), KD_USIZE_C(ptr_sz), KD_U8_C(val), KD_BOOL_C(use_block_idx))
#define kdi_GenMemOpsFindAllBlockIndices_I8_Idx8(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)   kdi_GenMemOpsFindAllBlockIndices_U8_Idx8(KD_PU8_C(idxs), KD_USIZE_C(idxs_sz), KD_PU8_C(ptr), KD_USIZE_C(ptr_sz), KD_U8_C(val), KD_BOOL_C(use_block_idx))
#define kdi_GenMemOpsFindAllBlockIndices_I16_Idx8(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U16_Idx8(KD_PU8_C(idxs), KD_USIZE_C(idxs_sz), KD_PU16_C(ptr), KD_USIZE_C(ptr_sz), KD_U16_C(val), KD_BOOL_C(use_block_idx))
#define kdi_GenMemOpsFindAllBlockIndices_I32_Idx8(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U32_Idx8(KD_PU8_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))

#if defined KD_ARCH_64BIT_INT
    #define kdi_GenMemOpsFindAllBlockIndices_I64_Idx8(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U64_Idx8(KD_PU8_C(idxs), KD_USIZE_C(idxs_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val), KD_BOOL_C(use_block_idx))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsFindAllBlockIndices_Imin_Idx8(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U8_Idx8(KD_PU8_C(idxs), KD_USIZE_C(idxs_sz), KD_PU8_C(ptr), KD_USIZE_C(ptr_sz), KD_U8_C(val), KD_BOOL_C(use_block_idx))
#define kdi_GenMemOpsFindAllBlockIndices_Umin_Idx8(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U8_Idx8(KD_PU8_C(idxs), KD_USIZE_C(idxs_sz), KD_PU8_C(ptr), KD_USIZE_C(ptr_sz), KD_U8_C(val), KD_BOOL_C(use_block_idx))

#if defined KD_ARCH_64BIT_INT
    #define kdi_GenMemOpsFindAllBlockIndices_Imax_Idx8(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U64_Idx8(KD_PU8_C(idxs), KD_USIZE_C(idxs_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_Umax_Idx8(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U64_Idx8(KD_PU8_C(idxs), KD_USIZE_C(idxs_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_Word_Idx8(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U64_Idx8(KD_PU8_C(idxs), KD_USIZE_C(idxs_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_Usize_Idx8(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U64_Idx8(KD_PU8_C(idxs), KD_USIZE_C(idxs_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val), KD_BOOL_C(use_block_idx))
#else
    #define kdi_GenMemOpsFindAllBlockIndices_Imax_Idx8(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U32_Idx8(KD_PU8_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_Umax_Idx8(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U32_Idx8(KD_PU8_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_Word_Idx8(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U32_Idx8(KD_PU8_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_Usize_Idx8(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U32_Idx8(KD_PU8_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsFindAllBlockIndices_Bool_Idx8(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U32_Idx8(KD_PU8_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))
#define kdi_GenMemOpsFindAllBlockIndices_Chr_Idx8(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U32_Idx8(KD_PU8_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))

#if defined KD_ARCH_64BIT_PTR
    #define kdi_GenMemOpsFindAllBlockIndices_Ptr_Idx8(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U64_Idx8(KD_PU8_C(idxs), KD_USIZE_C(idxs_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val), KD_BOOL_C(use_block_idx))
#else
    #define kdi_GenMemOpsFindAllBlockIndices_Ptr_Idx8(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U32_Idx8(KD_PU8_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))
#endif /* KD_ARCH_64BIT_PTR */


#define kdi_GenMemOpsFindAllBlockIndices_Byte_Idx16(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U8_Idx16(KD_PU16_C(idxs), KD_USIZE_C(idxs_sz), KD_PU8_C(ptr), KD_USIZE_C(ptr_sz), KD_U8_C(val), KD_BOOL_C(use_block_idx))
#define kdi_GenMemOpsFindAllBlockIndices_I8_Idx16(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)   kdi_GenMemOpsFindAllBlockIndices_U8_Idx16(KD_PU16_C(idxs), KD_USIZE_C(idxs_sz), KD_PU8_C(ptr), KD_USIZE_C(ptr_sz), KD_U8_C(val), KD_BOOL_C(use_block_idx))
#define kdi_GenMemOpsFindAllBlockIndices_I16_Idx16(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U16_Idx16(KD_PU16_C(idxs), KD_USIZE_C(idxs_sz), KD_PU16_C(ptr), KD_USIZE_C(ptr_sz), KD_U16_C(val), KD_BOOL_C(use_block_idx))
#define kdi_GenMemOpsFindAllBlockIndices_I32_Idx16(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U32_Idx16(KD_PU16_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))

#if defined KD_ARCH_64BIT_INT
    #define kdi_GenMemOpsFindAllBlockIndices_I64_Idx16(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U64_Idx16(KD_PU16_C(idxs), KD_USIZE_C(idxs_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val), KD_BOOL_C(use_block_idx))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsFindAllBlockIndices_Imin_Idx16(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U8_Idx16(KD_PU16_C(idxs), KD_USIZE_C(idxs_sz), KD_PU8_C(ptr), KD_USIZE_C(ptr_sz), KD_U8_C(val), KD_BOOL_C(use_block_idx))
#define kdi_GenMemOpsFindAllBlockIndices_Umin_Idx16(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U8_Idx16(KD_PU16_C(idxs), KD_USIZE_C(idxs_sz), KD_PU8_C(ptr), KD_USIZE_C(ptr_sz), KD_U8_C(val), KD_BOOL_C(use_block_idx))

#if defined KD_ARCH_64BIT_INT
    #define kdi_GenMemOpsFindAllBlockIndices_Imax_Idx16(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U64_Idx16(KD_PU16_C(idxs), KD_USIZE_C(idxs_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_Umax_Idx16(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U64_Idx16(KD_PU16_C(idxs), KD_USIZE_C(idxs_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_Word_Idx16(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U64_Idx16(KD_PU16_C(idxs), KD_USIZE_C(idxs_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_Usize_Idx16(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U64_Idx16(KD_PU16_C(idxs), KD_USIZE_C(idxs_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val), KD_BOOL_C(use_block_idx))
#else
    #define kdi_GenMemOpsFindAllBlockIndices_Imax_Idx16(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U32_Idx16(KD_PU16_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_Umax_Idx16(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U32_Idx16(KD_PU16_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_Word_Idx16(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U32_Idx16(KD_PU16_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_Usize_Idx16(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U32_Idx16(KD_PU16_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsFindAllBlockIndices_Bool_Idx16(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U32_Idx16(KD_PU16_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))
#define kdi_GenMemOpsFindAllBlockIndices_Chr_Idx16(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U32_Idx16(KD_PU16_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))

#if defined KD_ARCH_64BIT_PTR
    #define kdi_GenMemOpsFindAllBlockIndices_Ptr_Idx16(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U64_Idx16(KD_PU16_C(idxs), KD_USIZE_C(idxs_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val), KD_BOOL_C(use_block_idx))
#else
    #define kdi_GenMemOpsFindAllBlockIndices_Ptr_Idx16(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U32_Idx16(KD_PU16_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))
#endif /* KD_ARCH_64BIT_PTR */


#define kdi_GenMemOpsFindAllBlockIndices_Byte_Idx32(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U8_Idx32(KD_PU32_C(idxs), KD_USIZE_C(idxs_sz), KD_PU8_C(ptr), KD_USIZE_C(ptr_sz), KD_U8_C(val), KD_BOOL_C(use_block_idx))
#define kdi_GenMemOpsFindAllBlockIndices_I8_Idx32(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)   kdi_GenMemOpsFindAllBlockIndices_U8_Idx32(KD_PU32_C(idxs), KD_USIZE_C(idxs_sz), KD_PU8_C(ptr), KD_USIZE_C(ptr_sz), KD_U8_C(val), KD_BOOL_C(use_block_idx))
#define kdi_GenMemOpsFindAllBlockIndices_I16_Idx32(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U16_Idx32(KD_PU32_C(idxs), KD_USIZE_C(idxs_sz), KD_PU16_C(ptr), KD_USIZE_C(ptr_sz), KD_U16_C(val), KD_BOOL_C(use_block_idx))
#define kdi_GenMemOpsFindAllBlockIndices_I32_Idx32(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U32_Idx32(KD_PU32_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))

#if defined KD_ARCH_64BIT_INT
    #define kdi_GenMemOpsFindAllBlockIndices_I64_Idx32(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U64_Idx32(KD_PU32_C(idxs), KD_USIZE_C(idxs_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val), KD_BOOL_C(use_block_idx))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsFindAllBlockIndices_Imin_Idx32(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U8_Idx32(KD_PU32_C(idxs), KD_USIZE_C(idxs_sz), KD_PU8_C(ptr), KD_USIZE_C(ptr_sz), KD_U8_C(val), KD_BOOL_C(use_block_idx))
#define kdi_GenMemOpsFindAllBlockIndices_Umin_Idx32(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U8_Idx32(KD_PU32_C(idxs), KD_USIZE_C(idxs_sz), KD_PU8_C(ptr), KD_USIZE_C(ptr_sz), KD_U8_C(val), KD_BOOL_C(use_block_idx))

#if defined KD_ARCH_64BIT_INT
    #define kdi_GenMemOpsFindAllBlockIndices_Imax_Idx32(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U64_Idx32(KD_PU32_C(idxs), KD_USIZE_C(idxs_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_Umax_Idx32(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U64_Idx32(KD_PU32_C(idxs), KD_USIZE_C(idxs_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_Word_Idx32(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U64_Idx32(KD_PU32_C(idxs), KD_USIZE_C(idxs_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_Usize_Idx32(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U64_Idx32(KD_PU32_C(idxs), KD_USIZE_C(idxs_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val), KD_BOOL_C(use_block_idx))
#else
    #define kdi_GenMemOpsFindAllBlockIndices_Imax_Idx32(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U32_Idx32(KD_PU32_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_Umax_Idx32(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U32_Idx32(KD_PU32_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_Word_Idx32(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U32_Idx32(KD_PU32_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_Usize_Idx32(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U32_Idx32(KD_PU32_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))
#endif /* KD_ARCH_64BIT_INT */

#define kdi_GenMemOpsFindAllBlockIndices_Bool_Idx32(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U32_Idx32(KD_PU32_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))
#define kdi_GenMemOpsFindAllBlockIndices_Chr_Idx32(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U32_Idx32(KD_PU32_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))

#if defined KD_ARCH_64BIT_PTR
    #define kdi_GenMemOpsFindAllBlockIndices_Ptr_Idx32(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U64_Idx32(KD_PU32_C(idxs), KD_USIZE_C(idxs_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val), KD_BOOL_C(use_block_idx))
#else
    #define kdi_GenMemOpsFindAllBlockIndices_Ptr_Idx32(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U32_Idx32(KD_PU32_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))
#endif /* KD_ARCH_64BIT_PTR */


#if defined KD_ARCH_64BIT_INT
    #define kdi_GenMemOpsFindAllBlockIndices_Byte_Idx64(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U8_Idx64(KD_PU64_C(idxs), KD_USIZE_C(idxs_sz), KD_PU8_C(ptr), KD_USIZE_C(ptr_sz), KD_U8_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_I8_Idx64(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)    kdi_GenMemOpsFindAllBlockIndices_U8_Idx64(KD_PU64_C(idxs), KD_USIZE_C(idxs_sz), KD_PU8_C(ptr), KD_USIZE_C(ptr_sz), KD_U8_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_I16_Idx64(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)   kdi_GenMemOpsFindAllBlockIndices_U16_Idx64(KD_PU64_C(idxs), KD_USIZE_C(idxs_sz), KD_PU16_C(ptr), KD_USIZE_C(ptr_sz), KD_U16_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_I32_Idx64(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)   kdi_GenMemOpsFindAllBlockIndices_U32_Idx64(KD_PU64_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_I64_Idx64(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)   kdi_GenMemOpsFindAllBlockIndices_U64_Idx64(KD_PU64_C(idxs), KD_USIZE_C(idxs_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_Imin_Idx64(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U8_Idx64(KD_PU64_C(idxs), KD_USIZE_C(idxs_sz), KD_PU8_C(ptr), KD_USIZE_C(ptr_sz), KD_U8_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_Umin_Idx64(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U8_Idx64(KD_PU64_C(idxs), KD_USIZE_C(idxs_sz), KD_PU8_C(ptr), KD_USIZE_C(ptr_sz), KD_U8_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_Imax_Idx64(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U64_Idx64(KD_PU64_C(idxs), KD_USIZE_C(idxs_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_Umax_Idx64(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U64_Idx64(KD_PU64_C(idxs), KD_USIZE_C(idxs_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_Word_Idx64(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U64_Idx64(KD_PU64_C(idxs), KD_USIZE_C(idxs_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_Usize_Idx64(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U64_Idx64(KD_PU64_C(idxs), KD_USIZE_C(idxs_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_Bool_Idx64(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)  kdi_GenMemOpsFindAllBlockIndices_U32_Idx64(KD_PU64_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))
    #define kdi_GenMemOpsFindAllBlockIndices_Chr_Idx64(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx)   kdi_GenMemOpsFindAllBlockIndices_U32_Idx64(KD_PU64_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))

    #if defined KD_ARCH_64BIT_PTR
        #define kdi_GenMemOpsFindAllBlockIndices_Ptr_Idx64(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U64_Idx64(KD_PU64_C(idxs), KD_USIZE_C(idxs_sz), KD_PU64_C(ptr), KD_USIZE_C(ptr_sz), KD_U64_C(val), KD_BOOL_C(use_block_idx))
    #else
        #define kdi_GenMemOpsFindAllBlockIndices_Ptr_Idx64(idxs, idxs_sz, ptr, ptr_sz, val, use_block_idx) kdi_GenMemOpsFindAllBlockIndices_U32_Idx64(KD_PU64_C(idxs), KD_USIZE_C(idxs_sz), KD_PU32_C(ptr), KD_USIZE_C(ptr_sz), KD_U32_C(val), KD_BOOL_C(use_block_idx))
    #endif /* KD_ARCH_64BIT_PTR */
#endif     /* KD_ARCH_64BIT_INT */


KDAPI(void) kdi_GenMemOpsSwapBlocks_U8(kd_u8_t *ptr, kd_usize_t idx1, kd_usize_t idx2);
KDAPI(void) kdi_GenMemOpsSwapBlocks_U16(kd_u16_t *ptr, kd_usize_t idx1, kd_usize_t idx2);
KDAPI(void) kdi_GenMemOpsSwapBlocks_U32(kd_u32_t *ptr, kd_usize_t idx1, kd_usize_t idx2);
#if defined KD_ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsSwapBlocks_U64(kd_u64_t *ptr, kd_usize_t idx1, kd_usize_t idx2);
#endif
KDAPI(void) kdi_GenMemOpsSwapBlocks_Un(void *ptr, kd_usize_t block_sz, kd_usize_t idx1, kd_usize_t idx2);

KDAPI(void) kdi_GenMemOpsReverseBlocks_U8(kd_u8_t *ptr, kd_usize_t sz);
KDAPI(void) kdi_GenMemOpsReverseBlocks_U16(kd_u16_t *ptr, kd_usize_t sz);
KDAPI(void) kdi_GenMemOpsReverseBlocks_U32(kd_u32_t *ptr, kd_usize_t sz);
#if defined KD_ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsReverseBlocks_U64(kd_u64_t *ptr, kd_usize_t sz);
#endif
KDAPI(void) kdi_GenMemOpsReverseBlocks_Un(void *ptr, kd_usize_t sz, kd_usize_t block_sz);

KDAPI(void) kdi_GenMemOpsSetBlocks_U8(kd_u8_t *ptr, kd_usize_t sz, kd_u8_t val);
KDAPI(void) kdi_GenMemOpsSetBlocks_U16(kd_u16_t *ptr, kd_usize_t sz, kd_u16_t val);
KDAPI(void) kdi_GenMemOpsSetBlocks_U32(kd_u32_t *ptr, kd_usize_t sz, kd_u32_t val);
#if defined KD_ARCH_64BIT_INT
KDAPI(void) kdi_GenMemOpsSetBlocks_U64(kd_u64_t *ptr, kd_usize_t sz, kd_u64_t val);
#endif
KDAPI(void) kdi_GenMemOpsSetBlocks_Un(void *ptr, kd_usize_t sz, void *block, kd_usize_t block_sz);

KDAPI(void) kdi_GenMemOpsCpy(kd_byte_t *dst, kd_byte_t *src, kd_usize_t sz);
KDAPI(void) kdi_GenMemOpsMove(kd_byte_t *dst, kd_byte_t *src, kd_usize_t sz);

KDAPI(void *) kdi_GenMemOpsFindBlockWithIndex_U8(kd_usize_t *idx_ptr, kd_u8_t *ptr, kd_usize_t sz, kd_u8_t val);
KDAPI(void *) kdi_GenMemOpsFindBlockWithIndex_U16(kd_usize_t *idx_ptr, kd_u16_t *ptr, kd_usize_t sz, kd_u16_t val);
KDAPI(void *) kdi_GenMemOpsFindBlockWithIndex_U32(kd_usize_t *idx_ptr, kd_u32_t *ptr, kd_usize_t sz, kd_u32_t val);
#if defined KD_ARCH_64BIT_INT
KDAPI(void *) kdi_GenMemOpsFindBlockWithIndex_U64(kd_usize_t *idx_ptr, kd_u64_t *ptr, kd_usize_t sz, kd_u64_t val);
#endif
KDAPI(void *) kdi_GenMemOpsFindBlockWithIndex_Un(kd_usize_t *idx_ptr, void *ptr, kd_usize_t sz, void *block, kd_usize_t block_sz);

KDAPI(void *) kdi_GenMemOpsFindLastBlockWithIndex_U8(kd_usize_t *idx_ptr, kd_u8_t *ptr, kd_usize_t sz, kd_u8_t val);
KDAPI(void *) kdi_GenMemOpsFindLastBlockWithIndex_U16(kd_usize_t *idx_ptr, kd_u16_t *ptr, kd_usize_t sz, kd_u16_t val);
KDAPI(void *) kdi_GenMemOpsFindLastBlockWithIndex_U32(kd_usize_t *idx_ptr, kd_u32_t *ptr, kd_usize_t sz, kd_u32_t val);
#if defined KD_ARCH_64BIT_INT
KDAPI(void *) kdi_GenMemOpsFindLastBlockWithIndex_U64(kd_usize_t *idx_ptr, kd_u64_t *ptr, kd_usize_t sz, kd_u64_t val);
#endif
KDAPI(void *) kdi_GenMemOpsFindLastBlockWithIndex_Un(kd_usize_t *idx_ptr, void *ptr, kd_usize_t sz, void *block, kd_usize_t block_sz);

KDAPI(void *)
kdi_GenMemOpsFindBlockWithIndex_Struct(kd_usize_t *idx_ptr, void *ptr, kd_usize_t sz, void *block, kd_usize_t block_sz, kd_bool_t (*matcher)(void *curr_ptr, void *sz_ptr, void *block, void *block_sz_ptr, void *curr_idx_ptr));
KDAPI(void *)
kdi_GenMemOpsFindLastBlockWithIndex_Struct(kd_usize_t *idx_ptr, void *ptr, kd_usize_t sz, void *block, kd_usize_t block_sz, kd_bool_t (*matcher)(void *curr_ptr, void *sz_ptr, void *block, void *block_sz_ptr, void *curr_idx_ptr));

KDAPI(kd_usize_t) kdi_GenMemOpsGetBlocksCount_U8(kd_u8_t *ptr, kd_usize_t sz, kd_u8_t val);
KDAPI(kd_usize_t) kdi_GenMemOpsGetBlocksCount_U16(kd_u16_t *ptr, kd_usize_t sz, kd_u16_t val);
KDAPI(kd_usize_t) kdi_GenMemOpsGetBlocksCount_U32(kd_u32_t *ptr, kd_usize_t sz, kd_u32_t val);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_usize_t) kdi_GenMemOpsGetBlocksCount_U64(kd_u64_t *ptr, kd_usize_t sz, kd_u64_t val);
#endif
KDAPI(kd_usize_t) kdi_GenMemOpsGetBlocksCount_Un(void *ptr, kd_usize_t sz, void *block, kd_usize_t block_sz);

KDAPI(kd_usize_t) kdi_GenMemOpsFindAllBlocks_U8(void *dst, kd_usize_t dst_sz, kd_u8_t *ptr, kd_usize_t ptr_sz, kd_u8_t val);
KDAPI(kd_usize_t) kdi_GenMemOpsFindAllBlocks_U16(void *dst, kd_usize_t dst_sz, kd_u16_t *ptr, kd_usize_t ptr_sz, kd_u16_t val);
KDAPI(kd_usize_t) kdi_GenMemOpsFindAllBlocks_U32(void *dst, kd_usize_t dst_sz, kd_u32_t *ptr, kd_usize_t ptr_sz, kd_u32_t val);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_usize_t) kdi_GenMemOpsFindAllBlocks_U64(void *dst, kd_usize_t dst_sz, kd_u64_t *ptr, kd_usize_t ptr_sz, kd_u64_t val);
#endif
KDAPI(kd_usize_t) kdi_GenMemOpsFindAllBlocks_Un(void *dst, kd_usize_t dst_sz, kd_byte_t *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz);

KDAPI(kd_usize_t)
kdi_GenMemOpsFindAllBlocks_Struct(void *dst, kd_usize_t dst_sz, kd_byte_t *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz, kd_bool_t (*matcher)(void *curr_ptr, void *sz_ptr, void *block, void *block_sz_ptr, void *curr_idx_ptr));

KDAPI(kd_usize_t) kdi_GenMemOpsFindAllBlockIndices_U8_Idx8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_u8_t *ptr, kd_usize_t ptr_sz, kd_u8_t val, kd_bool_t use_block_idx);
KDAPI(kd_usize_t) kdi_GenMemOpsFindAllBlockIndices_U8_Idx16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_u8_t *ptr, kd_usize_t ptr_sz, kd_u8_t val, kd_bool_t use_block_idx);
KDAPI(kd_usize_t) kdi_GenMemOpsFindAllBlockIndices_U8_Idx32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_u8_t *ptr, kd_usize_t ptr_sz, kd_u8_t val, kd_bool_t use_block_idx);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_usize_t) kdi_GenMemOpsFindAllBlockIndices_U8_Idx64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_u8_t *ptr, kd_usize_t ptr_sz, kd_u8_t val, kd_bool_t use_block_idx);
#endif

KDAPI(kd_usize_t) kdi_GenMemOpsFindAllBlockIndices_U16_Idx8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_u16_t *ptr, kd_usize_t ptr_sz, kd_u16_t val, kd_bool_t use_block_idx);
KDAPI(kd_usize_t) kdi_GenMemOpsFindAllBlockIndices_U16_Idx16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_u16_t *ptr, kd_usize_t ptr_sz, kd_u16_t val, kd_bool_t use_block_idx);
KDAPI(kd_usize_t) kdi_GenMemOpsFindAllBlockIndices_U16_Idx32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_u16_t *ptr, kd_usize_t ptr_sz, kd_u16_t val, kd_bool_t use_block_idx);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_usize_t) kdi_GenMemOpsFindAllBlockIndices_U16_Idx64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_u16_t *ptr, kd_usize_t ptr_sz, kd_u16_t val, kd_bool_t use_block_idx);
#endif

KDAPI(kd_usize_t) kdi_GenMemOpsFindAllBlockIndices_U32_Idx8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_u32_t *ptr, kd_usize_t ptr_sz, kd_u32_t val, kd_bool_t use_block_idx);
KDAPI(kd_usize_t) kdi_GenMemOpsFindAllBlockIndices_U32_Idx16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_u32_t *ptr, kd_usize_t ptr_sz, kd_u32_t val, kd_bool_t use_block_idx);
KDAPI(kd_usize_t) kdi_GenMemOpsFindAllBlockIndices_U32_Idx32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_u32_t *ptr, kd_usize_t ptr_sz, kd_u32_t val, kd_bool_t use_block_idx);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_usize_t) kdi_GenMemOpsFindAllBlockIndices_U32_Idx64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_u32_t *ptr, kd_usize_t ptr_sz, kd_u32_t val, kd_bool_t use_block_idx);
#endif

#if defined KD_ARCH_64BIT_INT
KDAPI(kd_usize_t) kdi_GenMemOpsFindAllBlockIndices_U64_Idx8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_u64_t *ptr, kd_usize_t ptr_sz, kd_u64_t val, kd_bool_t use_block_idx);
KDAPI(kd_usize_t) kdi_GenMemOpsFindAllBlockIndices_U64_Idx16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_u64_t *ptr, kd_usize_t ptr_sz, kd_u64_t val, kd_bool_t use_block_idx);
KDAPI(kd_usize_t) kdi_GenMemOpsFindAllBlockIndices_U64_Idx32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_u64_t *ptr, kd_usize_t ptr_sz, kd_u64_t val, kd_bool_t use_block_idx);
KDAPI(kd_usize_t) kdi_GenMemOpsFindAllBlockIndices_U64_Idx64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_u64_t *ptr, kd_usize_t ptr_sz, kd_u64_t val, kd_bool_t use_block_idx);
#endif

KDAPI(kd_usize_t)
kdi_GenMemOpsFindAllBlockIndices_Un_Idx8(kd_u8_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, void *val_block, kd_usize_t val_block_sz, kd_bool_t use_block_idx);
KDAPI(kd_usize_t)
kdi_GenMemOpsFindAllBlockIndices_Un_Idx16(kd_u16_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, void *val_block, kd_usize_t val_block_sz, kd_bool_t use_block_idx);
KDAPI(kd_usize_t)
kdi_GenMemOpsFindAllBlockIndices_Un_Idx32(kd_u32_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, void *val_block, kd_usize_t val_block_sz, kd_bool_t use_block_idx);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_usize_t)
kdi_GenMemOpsFindAllBlockIndices_Un_Idx64(kd_u64_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, void *val_block, kd_usize_t val_block_sz, kd_bool_t use_block_idx);
#endif

KDAPI(kd_usize_t)
kdi_GenMemOpsFindAllBlockIndices_Struct_Idx8(kd_u8_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, void *val_block, kd_usize_t val_block_sz, kd_bool_t use_block_idx, kd_bool_t (*matcher)(void *curr_ptr, void *sz_ptr, void *block, void *block_sz_ptr, void *curr_idx_ptr));
KDAPI(kd_usize_t)
kdi_GenMemOpsFindAllBlockIndices_Struct_Idx16(kd_u16_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, void *val_block, kd_usize_t val_block_sz, kd_bool_t use_block_idx, kd_bool_t (*matcher)(void *curr_ptr, void *sz_ptr, void *block, void *block_sz_ptr, void *curr_idx_ptr));
KDAPI(kd_usize_t)
kdi_GenMemOpsFindAllBlockIndices_Struct_Idx32(kd_u32_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, void *val_block, kd_usize_t val_block_sz, kd_bool_t use_block_idx, kd_bool_t (*matcher)(void *curr_ptr, void *sz_ptr, void *block, void *block_sz_ptr, void *curr_idx_ptr));
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_usize_t)
kdi_GenMemOpsFindAllBlockIndices_Struct_Idx64(kd_u64_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, void *val_block, kd_usize_t val_block_sz, kd_bool_t use_block_idx, kd_bool_t (*matcher)(void *curr_ptr, void *sz_ptr, void *block, void *block_sz_ptr, void *curr_idx_ptr));
#endif

KDAPI(void *) kdi_GenMemOpsBinarySearchBlockWithIndex_U8(kd_usize_t *idx_ptr, kd_u8_t *ptr, kd_usize_t sz, kd_u8_t val);
KDAPI(void *) kdi_GenMemOpsBinarySearchBlockWithIndex_U16(kd_usize_t *idx_ptr, kd_u16_t *ptr, kd_usize_t sz, kd_u16_t val);
KDAPI(void *) kdi_GenMemOpsBinarySearchBlockWithIndex_U32(kd_usize_t *idx_ptr, kd_u32_t *ptr, kd_usize_t sz, kd_u32_t val);
#if defined KD_ARCH_64BIT_INT
KDAPI(void *) kdi_GenMemOpsBinarySearchBlockWithIndex_U64(kd_usize_t *idx_ptr, kd_u64_t *ptr, kd_usize_t sz, kd_u64_t val);
#endif
KDAPI(void *)
kdi_GenMemOpsBinarySearchBlockWithIndex_Un(kd_usize_t *idx_ptr, void *ptr, kd_usize_t sz, void *block, kd_usize_t block_sz, kd_word_t (*comparator)(void *block_a_ptr, void *block_b_ptr, void *block_sz_ptr));


KD_EXTERN_END


#endif /* KDI_GEN_MEM_OPS_H_ */
