/**
 * @file kd_mem_ops.h
 * @author Kumarjit Das
 * @version 0.0.1
 * @brief Main header file of the KD_MEM_OPS library.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 * @since 0.0.1
 */


#ifndef KD_MEM_OPS_H_
#define KD_MEM_OPS_H_


#include "./version.h"
#include "./platform.h"
#include "./fixed_width.h"
#include "./eltype.h"


KD_EXTERN_BEGIN


#define KD_MEM_OPS_VERSION_MAJOR               0
#define KD_MEM_OPS_VERSION_MINOR               0
#define KD_MEM_OPS_VERSION_PATCH               1

#define KD_MEM_OPS_VERSION_CSTR                KDI_STRINGIFY(KD_MEM_OPS_VERSION_MAJOR) "." KDI_STRINGIFY(KD_MEM_OPS_VERSION_MINOR) "." KDI_STRINGIFY(KD_MEM_OPS_VERSION_PATCH)
#define KD_MEM_OPS_VERSION_ARR                 {KD_MEM_OPS_VERSION_MAJOR, KD_MEM_OPS_VERSION_MINOR, KD_MEM_OPS_VERSION_PATCH}


#define kdMemOpsSwapByte(ptr, len, idx1, idx2) kdMemOpsSwapU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_WORD_C(idx1), KD_WORD_C(idx2))
#define kdMemOpsSwapI8(ptr, len, idx1, idx2)   kdMemOpsSwapU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_WORD_C(idx1), KD_WORD_C(idx2))
#define kdMemOpsSwapImin(ptr, len, idx1, idx2) kdMemOpsSwapU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_WORD_C(idx1), KD_WORD_C(idx2))
#define kdMemOpsSwapUmin(ptr, len, idx1, idx2) kdMemOpsSwapU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_WORD_C(idx1), KD_WORD_C(idx2))
#define kdMemOpsSwapI16(ptr, len, idx1, idx2)  kdMemOpsSwapU16(KD_PTR_C(ptr), KD_WORD_C(len), KD_WORD_C(idx1), KD_WORD_C(idx2))
#define kdMemOpsSwapI32(ptr, len, idx1, idx2)  kdMemOpsSwapU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_WORD_C(idx1), KD_WORD_C(idx2))
#define kdMemOpsSwapBool(ptr, len, idx1, idx2) kdMemOpsSwapU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_WORD_C(idx1), KD_WORD_C(idx2))
#define kdMemOpsSwapChr(ptr, len, idx1, idx2)  kdMemOpsSwapU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_WORD_C(idx1), KD_WORD_C(idx2))

#if defined KD_ARCH_64BIT_INT
    #define kdMemOpsSwapI64(ptr, len, idx1, idx2)   kdMemOpsSwapU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_WORD_C(idx1), KD_WORD_C(idx2))
    #define kdMemOpsSwapImax(ptr, len, idx1, idx2)  kdMemOpsSwapU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_WORD_C(idx1), KD_WORD_C(idx2))
    #define kdMemOpsSwapUmax(ptr, len, idx1, idx2)  kdMemOpsSwapU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_WORD_C(idx1), KD_WORD_C(idx2))
    #define kdMemOpsSwapWord(ptr, len, idx1, idx2)  kdMemOpsSwapU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_WORD_C(idx1), KD_WORD_C(idx2))
    #define kdMemOpsSwapUsize(ptr, len, idx1, idx2) kdMemOpsSwapU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_WORD_C(idx1), KD_WORD_C(idx2))
#else /* !defined KD_ARCH_64BIT_INT */
    #define kdMemOpsSwapImax(ptr, len, idx1, idx2)  kdMemOpsSwapU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_WORD_C(idx1), KD_WORD_C(idx2))
    #define kdMemOpsSwapUmax(ptr, len, idx1, idx2)  kdMemOpsSwapU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_WORD_C(idx1), KD_WORD_C(idx2))
    #define kdMemOpsSwapWord(ptr, len, idx1, idx2)  kdMemOpsSwapU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_WORD_C(idx1), KD_WORD_C(idx2))
    #define kdMemOpsSwapUsize(ptr, len, idx1, idx2) kdMemOpsSwapU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_WORD_C(idx1), KD_WORD_C(idx2))
#endif /* KD_ARCH_64BIT_INT */

#if defined KD_ARCH_64BIT_PTR
    #define kdMemOpsSwapPtr(ptr, len, idx1, idx2) kdMemOpsSwapU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_WORD_C(idx1), KD_WORD_C(idx2))
#else
    #define kdMemOpsSwapPtr(ptr, len, idx1, idx2) kdMemOpsSwapU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_WORD_C(idx1), KD_WORD_C(idx2))
#endif /* KD_ARCH_64BIT_PTR */

#define kdMemOpsSwap(ptr, len, idx1, idx2) kdMemOpsSwapWord((ptr), (len), (idx1), (idx2))


#define kdMemOpsReverseByte(ptr, len)      kdMemOpsReverseU8(KD_PTR_C(ptr), KD_WORD_C(len))
#define kdMemOpsReverseI8(ptr, len)        kdMemOpsReverseU8(KD_PTR_C(ptr), KD_WORD_C(len))
#define kdMemOpsReverseImin(ptr, len)      kdMemOpsReverseU8(KD_PTR_C(ptr), KD_WORD_C(len))
#define kdMemOpsReverseUmin(ptr, len)      kdMemOpsReverseU8(KD_PTR_C(ptr), KD_WORD_C(len))
#define kdMemOpsReverseI16(ptr, len)       kdMemOpsReverseU16(KD_PTR_C(ptr), KD_WORD_C(len))
#define kdMemOpsReverseI32(ptr, len)       kdMemOpsReverseU32(KD_PTR_C(ptr), KD_WORD_C(len))
#define kdMemOpsReverseBool(ptr, len)      kdMemOpsReverseU32(KD_PTR_C(ptr), KD_WORD_C(len))
#define kdMemOpsReverseChr(ptr, len)       kdMemOpsReverseU32(KD_PTR_C(ptr), KD_WORD_C(len))

#if defined KD_ARCH_64BIT_INT
    #define kdMemOpsReverseI64(ptr, len)   kdMemOpsReverseU64(KD_PTR_C(ptr), KD_WORD_C(len))
    #define kdMemOpsReverseImax(ptr, len)  kdMemOpsReverseU64(KD_PTR_C(ptr), KD_WORD_C(len))
    #define kdMemOpsReverseUmax(ptr, len)  kdMemOpsReverseU64(KD_PTR_C(ptr), KD_WORD_C(len))
    #define kdMemOpsReverseWord(ptr, len)  kdMemOpsReverseU64(KD_PTR_C(ptr), KD_WORD_C(len))
    #define kdMemOpsReverseUsize(ptr, len) kdMemOpsReverseU64(KD_PTR_C(ptr), KD_WORD_C(len))
#else /* !defined KD_ARCH_64BIT_INT */
    #define kdMemOpsReverseImax(ptr, len)  kdMemOpsReverseU32(KD_PTR_C(ptr), KD_WORD_C(len))
    #define kdMemOpsReverseUmax(ptr, len)  kdMemOpsReverseU32(KD_PTR_C(ptr), KD_WORD_C(len))
    #define kdMemOpsReverseWord(ptr, len)  kdMemOpsReverseU32(KD_PTR_C(ptr), KD_WORD_C(len))
    #define kdMemOpsReverseUsize(ptr, len) kdMemOpsReverseU32(KD_PTR_C(ptr), KD_WORD_C(len))
#endif /* KD_ARCH_64BIT_INT */

#if defined KD_ARCH_64BIT_PTR
    #define kdMemOpsReversePtr(ptr, len) kdMemOpsReverseU64(KD_PTR_C(ptr), KD_WORD_C(len))
#else
    #define kdMemOpsReversePtr(ptr, len) kdMemOpsReverseU32(KD_PTR_C(ptr), KD_WORD_C(len))
#endif /* KD_ARCH_64BIT_PTR */

#define kdMemOpsReverse(ptr, len)      kdMemOpsReverseWord((ptr), (len))


#define kdMemOpsSetByte(ptr, len, val) kdMemOpsSetU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_U8_C(val))
#define kdMemOpsSetI8(ptr, len, val)   kdMemOpsSetU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_U8_C(val))
#define kdMemOpsSetImin(ptr, len, val) kdMemOpsSetU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_U8_C(val))
#define kdMemOpsSetUmin(ptr, len, val) kdMemOpsSetU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_U8_C(val))
#define kdMemOpsSetI16(ptr, len, val)  kdMemOpsSetU16(KD_PTR_C(ptr), KD_WORD_C(len), KD_U16_C(val))
#define kdMemOpsSetI32(ptr, len, val)  kdMemOpsSetU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(val))
#define kdMemOpsSetBool(ptr, len, val) kdMemOpsSetU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(val))
#define kdMemOpsSetChr(ptr, len, val)  kdMemOpsSetU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(val))

#if defined KD_ARCH_64BIT_INT
    #define kdMemOpsSetI64(ptr, len, val)   kdMemOpsSetU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(val))
    #define kdMemOpsSetImax(ptr, len, val)  kdMemOpsSetU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(val))
    #define kdMemOpsSetUmax(ptr, len, val)  kdMemOpsSetU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(val))
    #define kdMemOpsSetWord(ptr, len, val)  kdMemOpsSetU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(val))
    #define kdMemOpsSetUsize(ptr, len, val) kdMemOpsSetU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(val))
#else /* !defined KD_ARCH_64BIT_INT */
    #define kdMemOpsSetImax(ptr, len, val)  kdMemOpsSetU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(val))
    #define kdMemOpsSetUmax(ptr, len, val)  kdMemOpsSetU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(val))
    #define kdMemOpsSetWord(ptr, len, val)  kdMemOpsSetU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(val))
    #define kdMemOpsSetUsize(ptr, len, val) kdMemOpsSetU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(val))
#endif /* KD_ARCH_64BIT_INT */

#if defined KD_ARCH_64BIT_PTR
    #define kdMemOpsSetPtr(ptr, len, val) kdMemOpsSetU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(val))
#else
    #define kdMemOpsSetPtr(ptr, len, val) kdMemOpsSetU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(val))
#endif /* KD_ARCH_64BIT_PTR */

#define kdMemOpsSet(ptr, len, val)     kdMemOpsSetWord((ptr), (len), (val))


#define kdMemOpsCpyByte(dst, src, len) kdMemOpsCpyU8(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
#define kdMemOpsCpyI8(dst, src, len)   kdMemOpsCpyU8(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
#define kdMemOpsCpyImin(dst, src, len) kdMemOpsCpyU8(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
#define kdMemOpsCpyUmin(dst, src, len) kdMemOpsCpyU8(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
#define kdMemOpsCpyI16(dst, src, len)  kdMemOpsCpyU16(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
#define kdMemOpsCpyI32(dst, src, len)  kdMemOpsCpyU32(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
#define kdMemOpsCpyBool(dst, src, len) kdMemOpsCpyU32(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
#define kdMemOpsCpyChr(dst, src, len)  kdMemOpsCpyU32(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))

#if defined KD_ARCH_64BIT_INT
    #define kdMemOpsCpyI64(dst, src, len)   kdMemOpsCpyU64(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
    #define kdMemOpsCpyImax(dst, src, len)  kdMemOpsCpyU64(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
    #define kdMemOpsCpyUmax(dst, src, len)  kdMemOpsCpyU64(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
    #define kdMemOpsCpyWord(dst, src, len)  kdMemOpsCpyU64(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
    #define kdMemOpsCpyUsize(dst, src, len) kdMemOpsCpyU64(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
#else /* !defined KD_ARCH_64BIT_INT */
    #define kdMemOpsCpyImax(dst, src, len)  kdMemOpsCpyU32(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
    #define kdMemOpsCpyUmax(dst, src, len)  kdMemOpsCpyU32(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
    #define kdMemOpsCpyWord(dst, src, len)  kdMemOpsCpyU32(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
    #define kdMemOpsCpyUsize(dst, src, len) kdMemOpsCpyU32(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
#endif /* KD_ARCH_64BIT_INT */

#if defined KD_ARCH_64BIT_PTR
    #define kdMemOpsCpyPtr(dst, src, len) kdMemOpsCpyU64(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
#else
    #define kdMemOpsCpyPtr(dst, src, len) kdMemOpsCpyU32(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
#endif /* KD_ARCH_64BIT_PTR */

#define kdMemOpsCpy(dst, src, len)      kdMemOpsCpyWord((dst), (src), (len))


#define kdMemOpsMoveByte(dst, src, len) kdMemOpsMoveU8(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
#define kdMemOpsMoveI8(dst, src, len)   kdMemOpsMoveU8(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
#define kdMemOpsMoveImin(dst, src, len) kdMemOpsMoveU8(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
#define kdMemOpsMoveUmin(dst, src, len) kdMemOpsMoveU8(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
#define kdMemOpsMoveI16(dst, src, len)  kdMemOpsMoveU16(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
#define kdMemOpsMoveI32(dst, src, len)  kdMemOpsMoveU32(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
#define kdMemOpsMoveBool(dst, src, len) kdMemOpsMoveU32(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
#define kdMemOpsMoveChr(dst, src, len)  kdMemOpsMoveU32(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))

#if defined KD_ARCH_64BIT_INT
    #define kdMemOpsMoveI64(dst, src, len)   kdMemOpsMoveU64(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
    #define kdMemOpsMoveImax(dst, src, len)  kdMemOpsMoveU64(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
    #define kdMemOpsMoveUmax(dst, src, len)  kdMemOpsMoveU64(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
    #define kdMemOpsMoveWord(dst, src, len)  kdMemOpsMoveU64(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
    #define kdMemOpsMoveUsize(dst, src, len) kdMemOpsMoveU64(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
#else /* !defined KD_ARCH_64BIT_INT */
    #define kdMemOpsMoveImax(dst, src, len)  kdMemOpsMoveU32(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
    #define kdMemOpsMoveUmax(dst, src, len)  kdMemOpsMoveU32(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
    #define kdMemOpsMoveWord(dst, src, len)  kdMemOpsMoveU32(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
    #define kdMemOpsMoveUsize(dst, src, len) kdMemOpsMoveU32(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
#endif /* KD_ARCH_64BIT_INT */

#if defined KD_ARCH_64BIT_PTR
    #define kdMemOpsMovePtr(dst, src, len) kdMemOpsMoveU64(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
#else
    #define kdMemOpsMovePtr(dst, src, len) kdMemOpsMoveU32(KD_PTR_C(dst), KD_PTR_C(src), KD_WORD_C(len))
#endif /* KD_ARCH_64BIT_PTR */

#define kdMemOpsMove(dst, src, len)      kdMemOpsMoveWord((dst), (src), (len))


#define kdMemOpsFindByte(ptr, len, item) kdMemOpsFindU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_U8_C(item))
#define kdMemOpsFindI8(ptr, len, item)   kdMemOpsFindU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_U8_C(item))
#define kdMemOpsFindImin(ptr, len, item) kdMemOpsFindU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_U8_C(item))
#define kdMemOpsFindUmin(ptr, len, item) kdMemOpsFindU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_U8_C(item))
#define kdMemOpsFindI16(ptr, len, item)  kdMemOpsFindU16(KD_PTR_C(ptr), KD_WORD_C(len), KD_U16_C(item))
#define kdMemOpsFindI32(ptr, len, item)  kdMemOpsFindU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
#define kdMemOpsFindBool(ptr, len, item) kdMemOpsFindU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
#define kdMemOpsFindChr(ptr, len, item)  kdMemOpsFindU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))

#if defined KD_ARCH_64BIT_INT
    #define kdMemOpsFindI64(ptr, len, item)   kdMemOpsFindU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(item))
    #define kdMemOpsFindImax(ptr, len, item)  kdMemOpsFindU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(item))
    #define kdMemOpsFindUmax(ptr, len, item)  kdMemOpsFindU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(item))
    #define kdMemOpsFindWord(ptr, len, item)  kdMemOpsFindU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(item))
    #define kdMemOpsFindUsize(ptr, len, item) kdMemOpsFindU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(item))
#else /* !defined KD_ARCH_64BIT_INT */
    #define kdMemOpsFindImax(ptr, len, item)  kdMemOpsFindU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
    #define kdMemOpsFindUmax(ptr, len, item)  kdMemOpsFindU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
    #define kdMemOpsFindWord(ptr, len, item)  kdMemOpsFindU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
    #define kdMemOpsFindUsize(ptr, len, item) kdMemOpsFindU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
#endif /* KD_ARCH_64BIT_INT */

#if defined KD_ARCH_64BIT_PTR
    #define kdMemOpsFindPtr(ptr, len, item) kdMemOpsFindU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(item))
#else
    #define kdMemOpsFindPtr(ptr, len, item) kdMemOpsFindU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
#endif /* KD_ARCH_64BIT_PTR */

#define kdMemOpsFind(ptr, len, item)          kdMemOpsFindWord((ptr), (len), (item))


#define kdMemOpsFindIndexByte(ptr, len, item) kdMemOpsFindIndexU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_U8_C(item))
#define kdMemOpsFindIndexI8(ptr, len, item)   kdMemOpsFindIndexU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_U8_C(item))
#define kdMemOpsFindIndexImin(ptr, len, item) kdMemOpsFindIndexU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_U8_C(item))
#define kdMemOpsFindIndexUmin(ptr, len, item) kdMemOpsFindIndexU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_U8_C(item))
#define kdMemOpsFindIndexI16(ptr, len, item)  kdMemOpsFindIndexU16(KD_PTR_C(ptr), KD_WORD_C(len), KD_U16_C(item))
#define kdMemOpsFindIndexI32(ptr, len, item)  kdMemOpsFindIndexU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
#define kdMemOpsFindIndexBool(ptr, len, item) kdMemOpsFindIndexU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
#define kdMemOpsFindIndexChr(ptr, len, item)  kdMemOpsFindIndexU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))

#if defined KD_ARCH_64BIT_INT
    #define kdMemOpsFindIndexI64(ptr, len, item)   kdMemOpsFindIndexU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(item))
    #define kdMemOpsFindIndexImax(ptr, len, item)  kdMemOpsFindIndexU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(item))
    #define kdMemOpsFindIndexUmax(ptr, len, item)  kdMemOpsFindIndexU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(item))
    #define kdMemOpsFindIndexWord(ptr, len, item)  kdMemOpsFindIndexU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(item))
    #define kdMemOpsFindIndexUsize(ptr, len, item) kdMemOpsFindIndexU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(item))
#else /* !defined KD_ARCH_64BIT_INT */
    #define kdMemOpsFindIndexImax(ptr, len, item)  kdMemOpsFindIndexU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
    #define kdMemOpsFindIndexUmax(ptr, len, item)  kdMemOpsFindIndexU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
    #define kdMemOpsFindIndexWord(ptr, len, item)  kdMemOpsFindIndexU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
    #define kdMemOpsFindIndexUsize(ptr, len, item) kdMemOpsFindIndexU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
#endif /* KD_ARCH_64BIT_INT */

#if defined KD_ARCH_64BIT_PTR
    #define kdMemOpsFindIndexPtr(ptr, len, item) kdMemOpsFindIndexU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(item))
#else
    #define kdMemOpsFindIndexPtr(ptr, len, item) kdMemOpsFindIndexU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
#endif /* KD_ARCH_64BIT_PTR */

#define kdMemOpsFindIndex(ptr, len, item)    kdMemOpsFindIndexWord((ptr), (len), (item))


#define kdMemOpsFindLastByte(ptr, len, item) kdMemOpsFindLastU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_U8_C(item))
#define kdMemOpsFindLastI8(ptr, len, item)   kdMemOpsFindLastU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_U8_C(item))
#define kdMemOpsFindLastImin(ptr, len, item) kdMemOpsFindLastU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_U8_C(item))
#define kdMemOpsFindLastUmin(ptr, len, item) kdMemOpsFindLastU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_U8_C(item))
#define kdMemOpsFindLastI16(ptr, len, item)  kdMemOpsFindLastU16(KD_PTR_C(ptr), KD_WORD_C(len), KD_U16_C(item))
#define kdMemOpsFindLastI32(ptr, len, item)  kdMemOpsFindLastU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
#define kdMemOpsFindLastBool(ptr, len, item) kdMemOpsFindLastU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
#define kdMemOpsFindLastChr(ptr, len, item)  kdMemOpsFindLastU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))

#if defined KD_ARCH_64BIT_INT
    #define kdMemOpsFindLastI64(ptr, len, item)   kdMemOpsFindLastU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(item))
    #define kdMemOpsFindLastImax(ptr, len, item)  kdMemOpsFindLastU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(item))
    #define kdMemOpsFindLastUmax(ptr, len, item)  kdMemOpsFindLastU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(item))
    #define kdMemOpsFindLastWord(ptr, len, item)  kdMemOpsFindLastU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(item))
    #define kdMemOpsFindLastUsize(ptr, len, item) kdMemOpsFindLastU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(item))
#else /* !defined KD_ARCH_64BIT_INT */
    #define kdMemOpsFindLastImax(ptr, len, item)  kdMemOpsFindLastU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
    #define kdMemOpsFindLastUmax(ptr, len, item)  kdMemOpsFindLastU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
    #define kdMemOpsFindLastWord(ptr, len, item)  kdMemOpsFindLastU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
    #define kdMemOpsFindLastUsize(ptr, len, item) kdMemOpsFindLastU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
#endif /* KD_ARCH_64BIT_INT */

#if defined KD_ARCH_64BIT_PTR
    #define kdMemOpsFindLastPtr(ptr, len, item) kdMemOpsFindLastU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(item))
#else
    #define kdMemOpsFindLastPtr(ptr, len, item) kdMemOpsFindLastU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
#endif /* KD_ARCH_64BIT_PTR */

#define kdMemOpsFindLast(ptr, len, item)          kdMemOpsFindLastWord((ptr), (len), (item))


#define kdMemOpsFindLastIndexByte(ptr, len, item) kdMemOpsFindLastIndexU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_U8_C(item))
#define kdMemOpsFindLastIndexI8(ptr, len, item)   kdMemOpsFindLastIndexU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_U8_C(item))
#define kdMemOpsFindLastIndexImin(ptr, len, item) kdMemOpsFindLastIndexU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_U8_C(item))
#define kdMemOpsFindLastIndexUmin(ptr, len, item) kdMemOpsFindLastIndexU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_U8_C(item))
#define kdMemOpsFindLastIndexI16(ptr, len, item)  kdMemOpsFindLastIndexU16(KD_PTR_C(ptr), KD_WORD_C(len), KD_U16_C(item))
#define kdMemOpsFindLastIndexI32(ptr, len, item)  kdMemOpsFindLastIndexU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
#define kdMemOpsFindLastIndexBool(ptr, len, item) kdMemOpsFindLastIndexU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
#define kdMemOpsFindLastIndexChr(ptr, len, item)  kdMemOpsFindLastIndexU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))

#if defined KD_ARCH_64BIT_INT
    #define kdMemOpsFindLastIndexI64(ptr, len, item)   kdMemOpsFindLastIndexU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(item))
    #define kdMemOpsFindLastIndexImax(ptr, len, item)  kdMemOpsFindLastIndexU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(item))
    #define kdMemOpsFindLastIndexUmax(ptr, len, item)  kdMemOpsFindLastIndexU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(item))
    #define kdMemOpsFindLastIndexWord(ptr, len, item)  kdMemOpsFindLastIndexU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(item))
    #define kdMemOpsFindLastIndexUsize(ptr, len, item) kdMemOpsFindLastIndexU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(item))
#else /* !defined KD_ARCH_64BIT_INT */
    #define kdMemOpsFindLastIndexImax(ptr, len, item)  kdMemOpsFindLastIndexU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
    #define kdMemOpsFindLastIndexUmax(ptr, len, item)  kdMemOpsFindLastIndexU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
    #define kdMemOpsFindLastIndexWord(ptr, len, item)  kdMemOpsFindLastIndexU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
    #define kdMemOpsFindLastIndexUsize(ptr, len, item) kdMemOpsFindLastIndexU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
#endif /* KD_ARCH_64BIT_INT */

#if defined KD_ARCH_64BIT_PTR
    #define kdMemOpsFindLastIndexPtr(ptr, len, item) kdMemOpsFindLastIndexU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_U64_C(item))
#else
    #define kdMemOpsFindLastIndexPtr(ptr, len, item) kdMemOpsFindLastIndexU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_U32_C(item))
#endif /* KD_ARCH_64BIT_PTR */

#define kdMemOpsFindLastIndex(ptr, len, item)                 kdMemOpsFindLastIndexWord((ptr), (len), (item))


#define kdMemOpsFindAllByte(dst, dst_len, ptr, ptr_len, item) kdMemOpsFindAllU8(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U8_C(item))
#define kdMemOpsFindAllI8(dst, dst_len, ptr, ptr_len, item)   kdMemOpsFindAllU8(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U8_C(item))
#define kdMemOpsFindAllImin(dst, dst_len, ptr, ptr_len, item) kdMemOpsFindAllU8(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U8_C(item))
#define kdMemOpsFindAllUmin(dst, dst_len, ptr, ptr_len, item) kdMemOpsFindAllU8(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U8_C(item))
#define kdMemOpsFindAllI16(dst, dst_len, ptr, ptr_len, item)  kdMemOpsFindAllU16(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U16_C(item))
#define kdMemOpsFindAllI32(dst, dst_len, ptr, ptr_len, item)  kdMemOpsFindAllU32(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U32_C(item))
#define kdMemOpsFindAllBool(dst, dst_len, ptr, ptr_len, item) kdMemOpsFindAllU32(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U32_C(item))
#define kdMemOpsFindAllChr(dst, dst_len, ptr, ptr_len, item)  kdMemOpsFindAllU32(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U32_C(item))

#if defined KD_ARCH_64BIT_INT
    #define kdMemOpsFindAllI64(dst, dst_len, ptr, ptr_len, item)   kdMemOpsFindAllU64(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U64_C(item))
    #define kdMemOpsFindAllImax(dst, dst_len, ptr, ptr_len, item)  kdMemOpsFindAllU64(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U64_C(item))
    #define kdMemOpsFindAllUmax(dst, dst_len, ptr, ptr_len, item)  kdMemOpsFindAllU64(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U64_C(item))
    #define kdMemOpsFindAllWord(dst, dst_len, ptr, ptr_len, item)  kdMemOpsFindAllU64(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U64_C(item))
    #define kdMemOpsFindAllUsize(dst, dst_len, ptr, ptr_len, item) kdMemOpsFindAllU64(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U64_C(item))
#else /* !defined KD_ARCH_64BIT_INT */
    #define kdMemOpsFindAllImax(dst, dst_len, ptr, ptr_len, item)  kdMemOpsFindAllU32(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U32_C(item))
    #define kdMemOpsFindAllUmax(dst, dst_len, ptr, ptr_len, item)  kdMemOpsFindAllU32(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U32_C(item))
    #define kdMemOpsFindAllWord(dst, dst_len, ptr, ptr_len, item)  kdMemOpsFindAllU32(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U32_C(item))
    #define kdMemOpsFindAllUsize(dst, dst_len, ptr, ptr_len, item) kdMemOpsFindAllU32(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U32_C(item))
#endif /* KD_ARCH_64BIT_INT */

#if defined KD_ARCH_64BIT_PTR
    #define kdMemOpsFindAllPtr(dst, dst_len, ptr, ptr_len, item) kdMemOpsFindAllU64(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U64_C(item))
#else
    #define kdMemOpsFindAllPtr(dst, dst_len, ptr, ptr_len, item) kdMemOpsFindAllU32(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U32_C(item))
#endif /* KD_ARCH_64BIT_PTR */

#define kdMemOpsFindAll(dst, dst_len, ptr, ptr_len, item) kdMemOpsFindAllWord((dst), (dst_len), (ptr), (ptr_len), (item))


#define kdMemOpsFindAllIndicesByte(idxs, idx_type, idxs_len, ptr, ptr_len, item)                                                                                                   \
    kdMemOpsFindAllIndicesU8(KD_PTR_C(idxs), KD_ELTYPE_C(idx_type), KD_WORD_C(idxs_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U8_C(item))
#define kdMemOpsFindAllIndicesI8(idxs, idx_type, idxs_len, ptr, ptr_len, item)                                                                                                     \
    kdMemOpsFindAllIndicesU8(KD_PTR_C(idxs), KD_ELTYPE_C(idx_type), KD_WORD_C(idxs_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U8_C(item))
#define kdMemOpsFindAllIndicesImin(idxs, idx_type, idxs_len, ptr, ptr_len, item)                                                                                                   \
    kdMemOpsFindAllIndicesU8(KD_PTR_C(idxs), KD_ELTYPE_C(idx_type), KD_WORD_C(idxs_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U8_C(item))
#define kdMemOpsFindAllIndicesUmin(idxs, idx_type, idxs_len, ptr, ptr_len, item)                                                                                                   \
    kdMemOpsFindAllIndicesU8(KD_PTR_C(idxs), KD_ELTYPE_C(idx_type), KD_WORD_C(idxs_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U8_C(item))
#define kdMemOpsFindAllIndicesI16(idxs, idx_type, idxs_len, ptr, ptr_len, item)                                                                                                    \
    kdMemOpsFindAllIndicesU16(KD_PTR_C(idxs), KD_ELTYPE_C(idx_type), KD_WORD_C(idxs_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U16_C(item))
#define kdMemOpsFindAllIndicesI32(idxs, idx_type, idxs_len, ptr, ptr_len, item)                                                                                                    \
    kdMemOpsFindAllIndicesU32(KD_PTR_C(idxs), KD_ELTYPE_C(idx_type), KD_WORD_C(idxs_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U32_C(item))
#define kdMemOpsFindAllIndicesBool(idxs, idx_type, idxs_len, ptr, ptr_len, item)                                                                                                   \
    kdMemOpsFindAllIndicesU32(KD_PTR_C(idxs), KD_ELTYPE_C(idx_type), KD_WORD_C(idxs_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U32_C(item))
#define kdMemOpsFindAllIndicesChr(idxs, idx_type, idxs_len, ptr, ptr_len, item)                                                                                                    \
    kdMemOpsFindAllIndicesU32(KD_PTR_C(idxs), KD_ELTYPE_C(idx_type), KD_WORD_C(idxs_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U32_C(item))

#if defined KD_ARCH_64BIT_INT
    #define kdMemOpsFindAllIndicesI64(idxs, idx_type, idxs_len, ptr, ptr_len, item)                                                                                                \
        kdMemOpsFindAllIndicesU64(KD_PTR_C(idxs), KD_ELTYPE_C(idx_type), KD_WORD_C(idxs_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U64_C(item))
    #define kdMemOpsFindAllIndicesImax(idxs, idx_type, idxs_len, ptr, ptr_len, item)                                                                                               \
        kdMemOpsFindAllIndicesU64(KD_PTR_C(idxs), KD_ELTYPE_C(idx_type), KD_WORD_C(idxs_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U64_C(item))
    #define kdMemOpsFindAllIndicesUmax(idxs, idx_type, idxs_len, ptr, ptr_len, item)                                                                                               \
        kdMemOpsFindAllIndicesU64(KD_PTR_C(idxs), KD_ELTYPE_C(idx_type), KD_WORD_C(idxs_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U64_C(item))
    #define kdMemOpsFindAllIndicesWord(idxs, idx_type, idxs_len, ptr, ptr_len, item)                                                                                               \
        kdMemOpsFindAllIndicesU64(KD_PTR_C(idxs), KD_ELTYPE_C(idx_type), KD_WORD_C(idxs_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U64_C(item))
    #define kdMemOpsFindAllIndicesUsize(idxs, idx_type, idxs_len, ptr, ptr_len, item)                                                                                              \
        kdMemOpsFindAllIndicesU64(KD_PTR_C(idxs), KD_ELTYPE_C(idx_type), KD_WORD_C(idxs_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U64_C(item))
#else /* !defined KD_ARCH_64BIT_INT */
    #define kdMemOpsFindAllIndicesImax(idxs, idx_type, idxs_len, ptr, ptr_len, item)                                                                                               \
        kdMemOpsFindAllIndicesU32(KD_PTR_C(idxs), KD_ELTYPE_C(idx_type), KD_WORD_C(idxs_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U32_C(item))
    #define kdMemOpsFindAllIndicesUmax(idxs, idx_type, idxs_len, ptr, ptr_len, item)                                                                                               \
        kdMemOpsFindAllIndicesU32(KD_PTR_C(idxs), KD_ELTYPE_C(idx_type), KD_WORD_C(idxs_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U32_C(item))
    #define kdMemOpsFindAllIndicesWord(idxs, idx_type, idxs_len, ptr, ptr_len, item)                                                                                               \
        kdMemOpsFindAllIndicesU32(KD_PTR_C(idxs), KD_ELTYPE_C(idx_type), KD_WORD_C(idxs_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U32_C(item))
    #define kdMemOpsFindAllIndicesUsize(idxs, idx_type, idxs_len, ptr, ptr_len, item)                                                                                              \
        kdMemOpsFindAllIndicesU32(KD_PTR_C(idxs), KD_ELTYPE_C(idx_type), KD_WORD_C(idxs_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U32_C(item))
#endif /* KD_ARCH_64BIT_INT */

#if defined KD_ARCH_64BIT_PTR
    #define kdMemOpsFindAllIndicesPtr(idxs, idx_type, idxs_len, ptr, ptr_len, item)                                                                                                \
        kdMemOpsFindAllIndicesU64(KD_PTR_C(idxs), KD_ELTYPE_C(idx_type), KD_WORD_C(idxs_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U64_C(item))
#else
    #define kdMemOpsFindAllIndicesPtr(idxs, idx_type, idxs_len, ptr, ptr_len, item)                                                                                                \
        kdMemOpsFindAllIndicesU32(KD_PTR_C(idxs), KD_ELTYPE_C(idx_type), KD_WORD_C(idxs_len), KD_PTR_C(ptr), KD_WORD_C(ptr_len), KD_U32_C(item))
#endif /* KD_ARCH_64BIT_PTR */

#define kdMemOpsFindAllIndices(idxs, idx_type, idxs_len, ptr, ptr_len, item) kdMemOpsFindAllIndicesWord((idxs), (idx_type), (idxs_len), (ptr), (ptr_len), (item))


#define kdMemOpsCmpByte(ptr1, ptr2, len)                                     kdMemOpsCmpU8(KD_PTR_C(ptr1), KD_PTR_C(ptr2), KD_WORD_C(len))
#define kdMemOpsCmpI8(ptr1, ptr2, len)                                       kdMemOpsCmpU8(KD_PTR_C(ptr1), KD_PTR_C(ptr2), KD_WORD_C(len))
#define kdMemOpsCmpImin(ptr1, ptr2, len)                                     kdMemOpsCmpU8(KD_PTR_C(ptr1), KD_PTR_C(ptr2), KD_WORD_C(len))
#define kdMemOpsCmpUmin(ptr1, ptr2, len)                                     kdMemOpsCmpU8(KD_PTR_C(ptr1), KD_PTR_C(ptr2), KD_WORD_C(len))
#define kdMemOpsCmpI16(ptr1, ptr2, len)                                      kdMemOpsCmpU16(KD_PTR_C(ptr1), KD_PTR_C(ptr2), KD_WORD_C(len))
#define kdMemOpsCmpI32(ptr1, ptr2, len)                                      kdMemOpsCmpU32(KD_PTR_C(ptr1), KD_PTR_C(ptr2), KD_WORD_C(len))
#define kdMemOpsCmpBool(ptr1, ptr2, len)                                     kdMemOpsCmpU32(KD_PTR_C(ptr1), KD_PTR_C(ptr2), KD_WORD_C(len))
#define kdMemOpsCmpChr(ptr1, ptr2, len)                                      kdMemOpsCmpU32(KD_PTR_C(ptr1), KD_PTR_C(ptr2), KD_WORD_C(len))

#if defined KD_ARCH_64BIT_INT
    #define kdMemOpsCmpI64(ptr1, ptr2, len)   kdMemOpsCmpU64(KD_PTR_C(ptr1), KD_PTR_C(ptr2), KD_WORD_C(len))
    #define kdMemOpsCmpImax(ptr1, ptr2, len)  kdMemOpsCmpU64(KD_PTR_C(ptr1), KD_PTR_C(ptr2), KD_WORD_C(len))
    #define kdMemOpsCmpUmax(ptr1, ptr2, len)  kdMemOpsCmpU64(KD_PTR_C(ptr1), KD_PTR_C(ptr2), KD_WORD_C(len))
    #define kdMemOpsCmpWord(ptr1, ptr2, len)  kdMemOpsCmpU64(KD_PTR_C(ptr1), KD_PTR_C(ptr2), KD_WORD_C(len))
    #define kdMemOpsCmpUsize(ptr1, ptr2, len) kdMemOpsCmpU64(KD_PTR_C(ptr1), KD_PTR_C(ptr2), KD_WORD_C(len))
#else /* !defined KD_ARCH_64BIT_INT */
    #define kdMemOpsCmpImax(ptr1, ptr2, len)  kdMemOpsCmpU32(KD_PTR_C(ptr1), KD_PTR_C(ptr2), KD_WORD_C(len))
    #define kdMemOpsCmpUmax(ptr1, ptr2, len)  kdMemOpsCmpU32(KD_PTR_C(ptr1), KD_PTR_C(ptr2), KD_WORD_C(len))
    #define kdMemOpsCmpWord(ptr1, ptr2, len)  kdMemOpsCmpU32(KD_PTR_C(ptr1), KD_PTR_C(ptr2), KD_WORD_C(len))
    #define kdMemOpsCmpUsize(ptr1, ptr2, len) kdMemOpsCmpU32(KD_PTR_C(ptr1), KD_PTR_C(ptr2), KD_WORD_C(len))
#endif /* KD_ARCH_64BIT_INT */

#if defined KD_ARCH_64BIT_PTR
    #define kdMemOpsCmpPtr(ptr1, ptr2, len) kdMemOpsCmpU64(KD_PTR_C(ptr1), KD_PTR_C(ptr2), KD_WORD_C(len))
#else
    #define kdMemOpsCmpPtr(ptr1, ptr2, len) kdMemOpsCmpU32(KD_PTR_C(ptr1), KD_PTR_C(ptr2), KD_WORD_C(len))
#endif /* KD_ARCH_64BIT_PTR */

#define kdMemOpsCmp(ptr1, ptr2, len) kdMemOpsCmpWord((ptr1), (ptr2), (len))


#define kdMemOpsCatByte(dst, dst_len, src1, src1_len, src2, src2_len)                                                                                                              \
    kdMemOpsCatU8(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(src1), KD_WORD_C(src1_len), KD_PTR_C(src2), KD_WORD_C(src2_len))
#define kdMemOpsCatI8(dst, dst_len, src1, src1_len, src2, src2_len)                                                                                                                \
    kdMemOpsCatU8(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(src1), KD_WORD_C(src1_len), KD_PTR_C(src2), KD_WORD_C(src2_len))
#define kdMemOpsCatImin(dst, dst_len, src1, src1_len, src2, src2_len)                                                                                                              \
    kdMemOpsCatU8(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(src1), KD_WORD_C(src1_len), KD_PTR_C(src2), KD_WORD_C(src2_len))
#define kdMemOpsCatUmin(dst, dst_len, src1, src1_len, src2, src2_len)                                                                                                              \
    kdMemOpsCatU8(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(src1), KD_WORD_C(src1_len), KD_PTR_C(src2), KD_WORD_C(src2_len))
#define kdMemOpsCatI16(dst, dst_len, src1, src1_len, src2, src2_len)                                                                                                               \
    kdMemOpsCatU16(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(src1), KD_WORD_C(src1_len), KD_PTR_C(src2), KD_WORD_C(src2_len))
#define kdMemOpsCatI32(dst, dst_len, src1, src1_len, src2, src2_len)                                                                                                               \
    kdMemOpsCatU32(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(src1), KD_WORD_C(src1_len), KD_PTR_C(src2), KD_WORD_C(src2_len))
#define kdMemOpsCatBool(dst, dst_len, src1, src1_len, src2, src2_len)                                                                                                              \
    kdMemOpsCatU32(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(src1), KD_WORD_C(src1_len), KD_PTR_C(src2), KD_WORD_C(src2_len))
#define kdMemOpsCatChr(dst, dst_len, src1, src1_len, src2, src2_len)                                                                                                               \
    kdMemOpsCatU32(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(src1), KD_WORD_C(src1_len), KD_PTR_C(src2), KD_WORD_C(src2_len))

#if defined KD_ARCH_64BIT_INT
    #define kdMemOpsCatI64(dst, dst_len, src1, src1_len, src2, src2_len)                                                                                                           \
        kdMemOpsCatU64(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(src1), KD_WORD_C(src1_len), KD_PTR_C(src2), KD_WORD_C(src2_len))
    #define kdMemOpsCatImax(dst, dst_len, src1, src1_len, src2, src2_len)                                                                                                          \
        kdMemOpsCatU64(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(src1), KD_WORD_C(src1_len), KD_PTR_C(src2), KD_WORD_C(src2_len))
    #define kdMemOpsCatUmax(dst, dst_len, src1, src1_len, src2, src2_len)                                                                                                          \
        kdMemOpsCatU64(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(src1), KD_WORD_C(src1_len), KD_PTR_C(src2), KD_WORD_C(src2_len))
    #define kdMemOpsCatWord(dst, dst_len, src1, src1_len, src2, src2_len)                                                                                                          \
        kdMemOpsCatU64(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(src1), KD_WORD_C(src1_len), KD_PTR_C(src2), KD_WORD_C(src2_len))
    #define kdMemOpsCatUsize(dst, dst_len, src1, src1_len, src2, src2_len)                                                                                                         \
        kdMemOpsCatU64(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(src1), KD_WORD_C(src1_len), KD_PTR_C(src2), KD_WORD_C(src2_len))
#else /* !defined KD_ARCH_64BIT_INT */
    #define kdMemOpsCatImax(dst, dst_len, src1, src1_len, src2, src2_len)                                                                                                          \
        kdMemOpsCatU32(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(src1), KD_WORD_C(src1_len), KD_PTR_C(src2), KD_WORD_C(src2_len))
    #define kdMemOpsCatUmax(dst, dst_len, src1, src1_len, src2, src2_len)                                                                                                          \
        kdMemOpsCatU32(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(src1), KD_WORD_C(src1_len), KD_PTR_C(src2), KD_WORD_C(src2_len))
    #define kdMemOpsCatWord(dst, dst_len, src1, src1_len, src2, src2_len)                                                                                                          \
        kdMemOpsCatU32(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(src1), KD_WORD_C(src1_len), KD_PTR_C(src2), KD_WORD_C(src2_len))
    #define kdMemOpsCatUsize(dst, dst_len, src1, src1_len, src2, src2_len)                                                                                                         \
        kdMemOpsCatU32(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(src1), KD_WORD_C(src1_len), KD_PTR_C(src2), KD_WORD_C(src2_len))
#endif /* KD_ARCH_64BIT_INT */

#if defined KD_ARCH_64BIT_PTR
    #define kdMemOpsCatPtr(dst, dst_len, src1, src1_len, src2, src2_len)                                                                                                           \
        kdMemOpsCatU64(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(src1), KD_WORD_C(src1_len), KD_PTR_C(src2), KD_WORD_C(src2_len))
#else
    #define kdMemOpsCatPtr(dst, dst_len, src1, src1_len, src2, src2_len)                                                                                                           \
        kdMemOpsCatU32(KD_PTR_C(dst), KD_WORD_C(dst_len), KD_PTR_C(src1), KD_WORD_C(src1_len), KD_PTR_C(src2), KD_WORD_C(src2_len))
#endif /* KD_ARCH_64BIT_PTR */

#define kdMemOpsCat(dst, dst_len, src1, src1_len, src2, src2_len) kdMemOpsCatWord((dst), (dst_len), (src1), (src1_len), (src2), (src2_len))


#define kdMemOpsCompSpnByte(ptr, len, keys, keys_len)             kdMemOpsCompSpnU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#define kdMemOpsCompSpnI8(ptr, len, keys, keys_len)               kdMemOpsCompSpnU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#define kdMemOpsCompSpnImin(ptr, len, keys, keys_len)             kdMemOpsCompSpnU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#define kdMemOpsCompSpnUmin(ptr, len, keys, keys_len)             kdMemOpsCompSpnU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#define kdMemOpsCompSpnI16(ptr, len, keys, keys_len)              kdMemOpsCompSpnU16(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#define kdMemOpsCompSpnI32(ptr, len, keys, keys_len)              kdMemOpsCompSpnU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#define kdMemOpsCompSpnBool(ptr, len, keys, keys_len)             kdMemOpsCompSpnU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#define kdMemOpsCompSpnChr(ptr, len, keys, keys_len)              kdMemOpsCompSpnU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))

#if defined KD_ARCH_64BIT_INT
    #define kdMemOpsCompSpnI64(ptr, len, keys, keys_len)   kdMemOpsCompSpnU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
    #define kdMemOpsCompSpnImax(ptr, len, keys, keys_len)  kdMemOpsCompSpnU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
    #define kdMemOpsCompSpnUmax(ptr, len, keys, keys_len)  kdMemOpsCompSpnU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
    #define kdMemOpsCompSpnWord(ptr, len, keys, keys_len)  kdMemOpsCompSpnU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
    #define kdMemOpsCompSpnUsize(ptr, len, keys, keys_len) kdMemOpsCompSpnU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#else /* !defined KD_ARCH_64BIT_INT */
    #define kdMemOpsCompSpnImax(ptr, len, keys, keys_len)  kdMemOpsCompSpnU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
    #define kdMemOpsCompSpnUmax(ptr, len, keys, keys_len)  kdMemOpsCompSpnU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
    #define kdMemOpsCompSpnWord(ptr, len, keys, keys_len)  kdMemOpsCompSpnU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
    #define kdMemOpsCompSpnUsize(ptr, len, keys, keys_len) kdMemOpsCompSpnU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#endif /* KD_ARCH_64BIT_INT */

#if defined KD_ARCH_64BIT_PTR
    #define kdMemOpsCompSpnPtr(ptr, len, keys, keys_len) kdMemOpsCompSpnU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#else
    #define kdMemOpsCompSpnPtr(ptr, len, keys, keys_len) kdMemOpsCompSpnU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#endif /* KD_ARCH_64BIT_PTR */

#define kdMemOpsCompSpn(ptr, len, keys, keys_len)          kdMemOpsCompSpnWord((ptr), (len), (keys), (keys_len))


#define kdMemOpsCompSpnIndexByte(ptr, len, keys, keys_len) kdMemOpsCompSpnIndexU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#define kdMemOpsCompSpnIndexI8(ptr, len, keys, keys_len)   kdMemOpsCompSpnIndexU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#define kdMemOpsCompSpnIndexImin(ptr, len, keys, keys_len) kdMemOpsCompSpnIndexU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#define kdMemOpsCompSpnIndexUmin(ptr, len, keys, keys_len) kdMemOpsCompSpnIndexU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#define kdMemOpsCompSpnIndexI16(ptr, len, keys, keys_len)  kdMemOpsCompSpnIndexU16(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#define kdMemOpsCompSpnIndexI32(ptr, len, keys, keys_len)  kdMemOpsCompSpnIndexU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#define kdMemOpsCompSpnIndexBool(ptr, len, keys, keys_len) kdMemOpsCompSpnIndexU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#define kdMemOpsCompSpnIndexChr(ptr, len, keys, keys_len)  kdMemOpsCompSpnIndexU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))

#if defined KD_ARCH_64BIT_INT
    #define kdMemOpsCompSpnIndexI64(ptr, len, keys, keys_len)   kdMemOpsCompSpnIndexU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
    #define kdMemOpsCompSpnIndexImax(ptr, len, keys, keys_len)  kdMemOpsCompSpnIndexU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
    #define kdMemOpsCompSpnIndexUmax(ptr, len, keys, keys_len)  kdMemOpsCompSpnIndexU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
    #define kdMemOpsCompSpnIndexWord(ptr, len, keys, keys_len)  kdMemOpsCompSpnIndexU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
    #define kdMemOpsCompSpnIndexUsize(ptr, len, keys, keys_len) kdMemOpsCompSpnIndexU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#else /* !defined KD_ARCH_64BIT_INT */
    #define kdMemOpsCompSpnIndexImax(ptr, len, keys, keys_len)  kdMemOpsCompSpnIndexU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
    #define kdMemOpsCompSpnIndexUmax(ptr, len, keys, keys_len)  kdMemOpsCompSpnIndexU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
    #define kdMemOpsCompSpnIndexWord(ptr, len, keys, keys_len)  kdMemOpsCompSpnIndexU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
    #define kdMemOpsCompSpnIndexUsize(ptr, len, keys, keys_len) kdMemOpsCompSpnIndexU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#endif /* KD_ARCH_64BIT_INT */

#if defined KD_ARCH_64BIT_PTR
    #define kdMemOpsCompSpnIndexPtr(ptr, len, keys, keys_len) kdMemOpsCompSpnIndexU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#else
    #define kdMemOpsCompSpnIndexPtr(ptr, len, keys, keys_len) kdMemOpsCompSpnIndexU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#endif /* KD_ARCH_64BIT_PTR */

#define kdMemOpsCompSpnIndex(ptr, len, keys, keys_len) kdMemOpsCompSpnIndexWord((ptr), (len), (keys), (keys_len))


#define kdMemOpsSpnByte(ptr, len, keys, keys_len)      kdMemOpsSpnU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#define kdMemOpsSpnI8(ptr, len, keys, keys_len)        kdMemOpsSpnU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#define kdMemOpsSpnImin(ptr, len, keys, keys_len)      kdMemOpsSpnU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#define kdMemOpsSpnUmin(ptr, len, keys, keys_len)      kdMemOpsSpnU8(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#define kdMemOpsSpnI16(ptr, len, keys, keys_len)       kdMemOpsSpnU16(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#define kdMemOpsSpnI32(ptr, len, keys, keys_len)       kdMemOpsSpnU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#define kdMemOpsSpnBool(ptr, len, keys, keys_len)      kdMemOpsSpnU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#define kdMemOpsSpnChr(ptr, len, keys, keys_len)       kdMemOpsSpnU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))

#if defined KD_ARCH_64BIT_INT
    #define kdMemOpsSpnI64(ptr, len, keys, keys_len)   kdMemOpsSpnU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
    #define kdMemOpsSpnImax(ptr, len, keys, keys_len)  kdMemOpsSpnU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
    #define kdMemOpsSpnUmax(ptr, len, keys, keys_len)  kdMemOpsSpnU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
    #define kdMemOpsSpnWord(ptr, len, keys, keys_len)  kdMemOpsSpnU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
    #define kdMemOpsSpnUsize(ptr, len, keys, keys_len) kdMemOpsSpnU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#else /* !defined KD_ARCH_64BIT_INT */
    #define kdMemOpsSpnImax(ptr, len, keys, keys_len)  kdMemOpsSpnU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
    #define kdMemOpsSpnUmax(ptr, len, keys, keys_len)  kdMemOpsSpnU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
    #define kdMemOpsSpnWord(ptr, len, keys, keys_len)  kdMemOpsSpnU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
    #define kdMemOpsSpnUsize(ptr, len, keys, keys_len) kdMemOpsSpnU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#endif /* KD_ARCH_64BIT_INT */

#if defined KD_ARCH_64BIT_PTR
    #define kdMemOpsSpnPtr(ptr, len, keys, keys_len) kdMemOpsSpnU64(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#else
    #define kdMemOpsSpnPtr(ptr, len, keys, keys_len) kdMemOpsSpnU32(KD_PTR_C(ptr), KD_WORD_C(len), KD_PTR_C(keys), KD_WORD_C(keys_len))
#endif /* KD_ARCH_64BIT_PTR */

#define kdMemOpsSpn(ptr, len, keys, keys_len) kdMemOpsSpnWord((ptr), (len), (keys), (keys_len))


KDAPI(kd_bool_t) kdMemOpsSwapU8(void *ptr, kd_word_t len, kd_word_t idx1, kd_word_t idx2);
KDAPI(kd_bool_t) kdMemOpsSwapU16(void *ptr, kd_word_t len, kd_word_t idx1, kd_word_t idx2);
KDAPI(kd_bool_t) kdMemOpsSwapU32(void *ptr, kd_word_t len, kd_word_t idx1, kd_word_t idx2);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_bool_t) kdMemOpsSwapU64(void *ptr, kd_word_t len, kd_word_t idx1, kd_word_t idx2);
#endif
KDAPI(kd_bool_t) kdMemOpsSwapN(void *ptr, kd_word_t len, kd_word_t n, kd_word_t idx1, kd_word_t idx2);

KDAPI(kd_bool_t) kdMemOpsReverseU8(void *ptr, kd_word_t len);
KDAPI(kd_bool_t) kdMemOpsReverseU16(void *ptr, kd_word_t len);
KDAPI(kd_bool_t) kdMemOpsReverseU32(void *ptr, kd_word_t len);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_bool_t) kdMemOpsReverseU64(void *ptr, kd_word_t len);
#endif
KDAPI(kd_bool_t) kdMemOpsReverseN(void *ptr, kd_word_t len, kd_word_t n);

KDAPI(kd_bool_t) kdMemOpsSetU8(void *ptr, kd_word_t len, kd_u8_t val);
KDAPI(kd_bool_t) kdMemOpsSetU16(void *ptr, kd_word_t len, kd_u16_t val);
KDAPI(kd_bool_t) kdMemOpsSetU32(void *ptr, kd_word_t len, kd_u32_t val);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_bool_t) kdMemOpsSetU64(void *ptr, kd_word_t len, kd_u64_t val);
#endif
KDAPI(kd_bool_t) kdMemOpsSetN(void *ptr, kd_word_t len, void *nval, kd_word_t n);

KDAPI(kd_bool_t) kdMemOpsCpyU8(void *dst, void *src, kd_word_t len);
KDAPI(kd_bool_t) kdMemOpsCpyU16(void *dst, void *src, kd_word_t len);
KDAPI(kd_bool_t) kdMemOpsCpyU32(void *dst, void *src, kd_word_t len);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_bool_t) kdMemOpsCpyU64(void *dst, void *src, kd_word_t len);
#endif
KDAPI(kd_bool_t) kdMemOpsCpyN(void *dst, void *src, kd_word_t len, kd_word_t n);

KDAPI(kd_bool_t) kdMemOpsMoveU8(void *dst, void *src, kd_word_t len);
KDAPI(kd_bool_t) kdMemOpsMoveU16(void *dst, void *src, kd_word_t len);
KDAPI(kd_bool_t) kdMemOpsMoveU32(void *dst, void *src, kd_word_t len);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_bool_t) kdMemOpsMoveU64(void *dst, void *src, kd_word_t len);
#endif
KDAPI(kd_bool_t) kdMemOpsMoveN(void *dst, void *src, kd_word_t len, kd_word_t n);

KDAPI(void *) kdMemOpsFindU8(void *ptr, kd_word_t len, kd_u8_t item);
KDAPI(void *) kdMemOpsFindU16(void *ptr, kd_word_t len, kd_u16_t item);
KDAPI(void *) kdMemOpsFindU32(void *ptr, kd_word_t len, kd_u32_t item);
#if defined KD_ARCH_64BIT_INT
KDAPI(void *) kdMemOpsFindU64(void *ptr, kd_word_t len, kd_u64_t item);
#endif
KDAPI(void *) kdMemOpsFindN(void *ptr, kd_word_t len, void *nitem, kd_word_t n);

KDAPI(kd_word_t) kdMemOpsFindIndexU8(void *ptr, kd_word_t len, kd_u8_t item);
KDAPI(kd_word_t) kdMemOpsFindIndexU16(void *ptr, kd_word_t len, kd_u16_t item);
KDAPI(kd_word_t) kdMemOpsFindIndexU32(void *ptr, kd_word_t len, kd_u32_t item);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_word_t) kdMemOpsFindIndexU64(void *ptr, kd_word_t len, kd_u64_t item);
#endif
KDAPI(kd_word_t) kdMemOpsFindIndexN(void *ptr, kd_word_t len, void *nitem, kd_word_t n);

KDAPI(void *) kdMemOpsFindLastU8(void *ptr, kd_word_t len, kd_u8_t item);
KDAPI(void *) kdMemOpsFindLastU16(void *ptr, kd_word_t len, kd_u16_t item);
KDAPI(void *) kdMemOpsFindLastU32(void *ptr, kd_word_t len, kd_u32_t item);
#if defined KD_ARCH_64BIT_INT
KDAPI(void *) kdMemOpsFindLastU64(void *ptr, kd_word_t len, kd_u64_t item);
#endif
KDAPI(void *) kdMemOpsFindLastN(void *ptr, kd_word_t len, void *nitem, kd_word_t n);

KDAPI(kd_word_t) kdMemOpsFindLastIndexU8(void *ptr, kd_word_t len, kd_u8_t item);
KDAPI(kd_word_t) kdMemOpsFindLastIndexU16(void *ptr, kd_word_t len, kd_u16_t item);
KDAPI(kd_word_t) kdMemOpsFindLastIndexU32(void *ptr, kd_word_t len, kd_u32_t item);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_word_t) kdMemOpsFindLastIndexU64(void *ptr, kd_word_t len, kd_u64_t item);
#endif
KDAPI(kd_word_t) kdMemOpsFindLastIndexN(void *ptr, kd_word_t len, void *nitem, kd_word_t n);

KDAPI(kd_word_t) kdMemOpsFindAllU8(void *dst, kd_word_t dst_len, void *ptr, kd_word_t ptr_len, kd_u8_t item);
KDAPI(kd_word_t) kdMemOpsFindAllU16(void *dst, kd_word_t dst_len, void *ptr, kd_word_t ptr_len, kd_u16_t item);
KDAPI(kd_word_t) kdMemOpsFindAllU32(void *dst, kd_word_t dst_len, void *ptr, kd_word_t ptr_len, kd_u32_t item);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_word_t) kdMemOpsFindAllU64(void *dst, kd_word_t dst_len, void *ptr, kd_word_t ptr_len, kd_u64_t item);
#endif
KDAPI(kd_word_t) kdMemOpsFindAllN(void *dst, kd_word_t dst_len, void *ptr, kd_word_t ptr_len, void *nitem, kd_word_t n);

KDAPI(kd_word_t) kdMemOpsFindAllIndicesU8(void *idxs, enum kd_eltype_t idx_type, kd_word_t idxs_len, void *ptr, kd_word_t ptr_len, kd_u8_t item);
KDAPI(kd_word_t) kdMemOpsFindAllIndicesU16(void *idxs, enum kd_eltype_t idx_type, kd_word_t idxs_len, void *ptr, kd_word_t ptr_len, kd_u16_t item);
KDAPI(kd_word_t) kdMemOpsFindAllIndicesU32(void *idxs, enum kd_eltype_t idx_type, kd_word_t idxs_len, void *ptr, kd_word_t ptr_len, kd_u32_t item);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_word_t) kdMemOpsFindAllIndicesU64(void *idxs, enum kd_eltype_t idx_type, kd_word_t idxs_len, void *ptr, kd_word_t ptr_len, kd_u64_t item);
#endif
KDAPI(kd_word_t) kdMemOpsFindAllIndicesN(void *idxs, enum kd_eltype_t idx_type, kd_word_t idxs_len, void *ptr, kd_word_t ptr_len, void *nitem, kd_word_t n);

KDAPI(kd_word_t) kdMemOpsCmpU8(void *ptr1, void *ptr2, kd_word_t len);
KDAPI(kd_word_t) kdMemOpsCmpU16(void *ptr1, void *ptr2, kd_word_t len);
KDAPI(kd_word_t) kdMemOpsCmpU32(void *ptr1, void *ptr2, kd_word_t len);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_word_t) kdMemOpsCmpU64(void *ptr1, void *ptr2, kd_word_t len);
#endif
KDAPI(kd_word_t) kdMemOpsCmpN(void *ptr1, void *ptr2, kd_word_t len, kd_word_t n);

KDAPI(kd_bool_t) kdMemOpsCatU8(void *dst, kd_word_t dst_len, void *src1, kd_word_t src1_len, void *src2, kd_word_t src2_len);
KDAPI(kd_bool_t) kdMemOpsCatU16(void *dst, kd_word_t dst_len, void *src1, kd_word_t src1_len, void *src2, kd_word_t src2_len);
KDAPI(kd_bool_t) kdMemOpsCatU32(void *dst, kd_word_t dst_len, void *src1, kd_word_t src1_len, void *src2, kd_word_t src2_len);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_bool_t) kdMemOpsCatU64(void *dst, kd_word_t dst_len, void *src1, kd_word_t src1_len, void *src2, kd_word_t src2_len);
#endif
KDAPI(kd_bool_t) kdMemOpsCatN(void *dst, kd_word_t dst_len, void *src1, kd_word_t src1_len, void *src2, kd_word_t src2_len, kd_word_t n);

KDAPI(void *) kdMemOpsCompSpnU8(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len);
KDAPI(void *) kdMemOpsCompSpnU16(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len);
KDAPI(void *) kdMemOpsCompSpnU32(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len);
#if defined KD_ARCH_64BIT_INT
KDAPI(void *) kdMemOpsCompSpnU64(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len);
#endif
KDAPI(void *) kdMemOpsCompSpnN(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len, kd_word_t n);

KDAPI(kd_word_t) kdMemOpsCompSpnIndexU8(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len);
KDAPI(kd_word_t) kdMemOpsCompSpnIndexU16(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len);
KDAPI(kd_word_t) kdMemOpsCompSpnIndexU32(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_word_t) kdMemOpsCompSpnIndexU64(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len);
#endif
KDAPI(kd_word_t) kdMemOpsCompSpnIndexN(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len, kd_word_t n);

KDAPI(kd_word_t) kdMemOpsSpnU8(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len);
KDAPI(kd_word_t) kdMemOpsSpnU16(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len);
KDAPI(kd_word_t) kdMemOpsSpnU32(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len);
#if defined KD_ARCH_64BIT_INT
KDAPI(kd_word_t) kdMemOpsSpnU64(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len);
#endif
KDAPI(kd_word_t) kdMemOpsSpnN(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len, kd_word_t n);


KD_EXTERN_END


#endif /* KD_MEM_OPS_H_ */
