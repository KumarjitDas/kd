/**
 * @file kd_mem_ops.c
 * @author Kumarjit Das
 * @version 0.0.1
 * @brief Main source file of the KD_MEM_OPS library.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 * @since 0.0.1
 */


#include "kd_version.h"

#define KD_BUILDING_LIB 1
#include "kd_platform.h"

#include "kd_fixed_width.h"
#include "kd_eltype.h"
#include "kd_gen_mem_ops.h"
#include "kd_mem_ops.h"

#include "internal/kdi_gen_mem_ops.h"


kd_bool_t
kdMemOpsSwapU8(void *ptr, kd_word_t len, kd_word_t idx1, kd_word_t idx2)
{
    if (!ptr || len <= 0 || idx1 >= len || idx2 >= len)
    {
        return KD_RESULT_FAILURE;
    }

    idx1 += idx1 < 0 ? len : 0;
    idx2 += idx2 < 0 ? len : 0;

    kdi_GenMemOpsSwapBlocks_U8(ptr, KD_USIZE_C(idx1), KD_USIZE_C(idx2));

    return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsSwapU16(void *ptr, kd_word_t len, kd_word_t idx1, kd_word_t idx2)
{
    if (!ptr || len <= 0 || idx1 >= len || idx2 >= len)
    {
        return KD_RESULT_FAILURE;
    }

    idx1 += idx1 < 0 ? len : 0;
    idx2 += idx2 < 0 ? len : 0;

    kdi_GenMemOpsSwapBlocks_U16(ptr, KD_USIZE_C(idx1) * KD_SZ_U16, KD_USIZE_C(idx2) * KD_SZ_U16);

    return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsSwapU32(void *ptr, kd_word_t len, kd_word_t idx1, kd_word_t idx2)
{
    if (!ptr || len <= 0 || idx1 >= len || idx2 >= len)
    {
        return KD_RESULT_FAILURE;
    }

    idx1 += idx1 < 0 ? len : 0;
    idx2 += idx2 < 0 ? len : 0;

    kdi_GenMemOpsSwapBlocks_U32(ptr, KD_USIZE_C(idx1) * KD_SZ_U32, KD_USIZE_C(idx2) * KD_SZ_U32);

    return KD_RESULT_SUCCESS;
}


#if defined KD_ARCH_64BIT_INT
kd_bool_t
kdMemOpsSwapU64(void *ptr, kd_word_t len, kd_word_t idx1, kd_word_t idx2)
{
    if (!ptr || len <= 0 || idx1 >= len || idx2 >= len)
    {
        return KD_RESULT_FAILURE;
    }

    idx1 += idx1 < 0 ? len : 0;
    idx2 += idx2 < 0 ? len : 0;

    kdi_GenMemOpsSwapBlocks_U64(ptr, KD_USIZE_C(idx1) * KD_SZ_U64, KD_USIZE_C(idx2) * KD_SZ_U64);

    return KD_RESULT_SUCCESS;
}
#endif /* KD_ARCH_64BIT_INT */


kd_bool_t
kdMemOpsSwapN(void *ptr, kd_word_t len, kd_word_t n, kd_word_t idx1, kd_word_t idx2)
{
    if (!ptr || len <= 0 || n <= 0 || idx1 >= len || idx2 >= len)
    {
        return KD_RESULT_FAILURE;
    }

    idx1 += idx1 < 0 ? len : 0;
    idx2 += idx2 < 0 ? len : 0;

    switch (n)
    {
        case 1:
            kdi_GenMemOpsSwapBlocks_U8(ptr, KD_USIZE_C(idx1), KD_USIZE_C(idx2));
            break;
        case 2:
            kdi_GenMemOpsSwapBlocks_U16(ptr, KD_USIZE_C(idx1) * KD_SZ_U16, KD_USIZE_C(idx2) * KD_SZ_U16);
            break;
        case 4:
            kdi_GenMemOpsSwapBlocks_U32(ptr, KD_USIZE_C(idx1) * KD_SZ_U32, KD_USIZE_C(idx2) * KD_SZ_U32);
            break;
#if defined KD_ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsSwapBlocks_U64(ptr, KD_USIZE_C(idx1) * KD_SZ_U64, KD_USIZE_C(idx2) * KD_SZ_U64);
            break;
#endif
        default:
            kdi_GenMemOpsSwapBlocks_Un(ptr, KD_USIZE_C(n), KD_USIZE_C(idx1) * KD_USIZE_C(n), KD_USIZE_C(idx2) * KD_USIZE_C(n));
    }

    return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsReverseU8(void *ptr, kd_word_t len)
{
    if (!ptr || len <= 0)
    {
        return KD_RESULT_FAILURE;
    }

    kdi_GenMemOpsReverseBlocks_U8(ptr, KD_USIZE_C(len));

    return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsReverseU16(void *ptr, kd_word_t len)
{
    if (!ptr || len <= 0)
    {
        return KD_RESULT_FAILURE;
    }

    kdi_GenMemOpsReverseBlocks_U16(ptr, KD_USIZE_C(len) * KD_SZ_U16);

    return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsReverseU32(void *ptr, kd_word_t len)
{
    if (!ptr || len <= 0)
    {
        return KD_RESULT_FAILURE;
    }

    kdi_GenMemOpsReverseBlocks_U32(ptr, KD_USIZE_C(len) * KD_SZ_U32);

    return KD_RESULT_SUCCESS;
}


#if defined KD_ARCH_64BIT_INT
kd_bool_t
kdMemOpsReverseU64(void *ptr, kd_word_t len)
{
    if (!ptr || len <= 0)
    {
        return KD_RESULT_FAILURE;
    }

    kdi_GenMemOpsReverseBlocks_U64(ptr, KD_USIZE_C(len) * KD_SZ_U64);

    return KD_RESULT_SUCCESS;
}
#endif /* KD_ARCH_64BIT_INT */


kd_bool_t
kdMemOpsReverseN(void *ptr, kd_word_t len, kd_word_t n)
{
    if (!ptr || len <= 0 || n <= 0)
    {
        return KD_RESULT_FAILURE;
    }

    switch (n)
    {
        case 1:
            kdi_GenMemOpsReverseBlocks_U8(ptr, KD_USIZE_C(len));
            break;
        case 2:
            kdi_GenMemOpsReverseBlocks_U16(ptr, KD_USIZE_C(len) * KD_SZ_U16);
            break;
        case 4:
            kdi_GenMemOpsReverseBlocks_U32(ptr, KD_USIZE_C(len) * KD_SZ_U32);
            break;
#if defined KD_ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsReverseBlocks_U64(ptr, KD_USIZE_C(len) * KD_SZ_U64);
            break;
#endif
        default:
            kdi_GenMemOpsReverseBlocks_Un(ptr, KD_USIZE_C(len) * KD_USIZE_C(n), KD_USIZE_C(n));
    }

    return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsSetU8(void *ptr, kd_word_t len, kd_byte_t val)
{
    if (!ptr || len <= 0)
    {
        return KD_RESULT_FAILURE;
    }

    kdi_GenMemOpsSetBlocks_U8(ptr, KD_USIZE_C(len), val);

    return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsSetU16(void *ptr, kd_word_t len, kd_u16_t val)
{
    if (!ptr || len <= 0)
    {
        return KD_RESULT_FAILURE;
    }

    kdi_GenMemOpsSetBlocks_U16(ptr, KD_USIZE_C(len) * KD_SZ_U16, val);

    return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsSetU32(void *ptr, kd_word_t len, kd_u32_t val)
{
    if (!ptr || len <= 0)
    {
        return KD_RESULT_FAILURE;
    }

    kdi_GenMemOpsSetBlocks_U32(ptr, KD_USIZE_C(len) * KD_SZ_U32, val);

    return KD_RESULT_SUCCESS;
}


#if defined KD_ARCH_64BIT_INT
kd_bool_t
kdMemOpsSetU64(void *ptr, kd_word_t len, kd_u64_t val)
{
    if (!ptr || len <= 0)
    {
        return KD_RESULT_FAILURE;
    }

    kdi_GenMemOpsSetBlocks_U64(ptr, KD_USIZE_C(len) * KD_SZ_U64, val);

    return KD_RESULT_SUCCESS;
}
#endif /* KD_ARCH_64BIT_INT */


kd_bool_t
kdMemOpsSetN(void *ptr, kd_word_t len, void *nval, kd_word_t n)
{
    kd_u8_t  val_u8;
    kd_u16_t val_u16;
    kd_u32_t val_u32;
#if defined KD_ARCH_64BIT_INT
    kd_u64_t val_u64;
#endif

    if (!ptr || len <= 0 || !nval || n <= 0)
    {
        return KD_RESULT_FAILURE;
    }

    switch (n)
    {
        case 1:
            val_u8 = *KD_PU8_C(nval);
            kdi_GenMemOpsSetBlocks_U8(ptr, KD_USIZE_C(len), val_u8);
            break;
        case 2:
            val_u16 = *KD_PU16_C(nval);
            kdi_GenMemOpsSetBlocks_U16(ptr, KD_USIZE_C(len) * KD_SZ_U16, val_u16);
            break;
        case 4:
            val_u32 = *KD_PU32_C(nval);
            kdi_GenMemOpsSetBlocks_U32(ptr, KD_USIZE_C(len) * KD_SZ_U32, val_u32);
            break;
#if defined KD_ARCH_64BIT_INT
        case 8:
            val_u64 = *KD_PU64_C(nval);
            kdi_GenMemOpsSetBlocks_U64(ptr, KD_USIZE_C(len) * KD_SZ_U64, val_u64);
            break;
#endif
        default:
            kdi_GenMemOpsSetBlocks_Un(ptr, KD_USIZE_C(len) * KD_USIZE_C(n), nval, KD_USIZE_C(n));
    }

    return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsCpyU8(void *dst, void *src, kd_word_t len)
{
    if (!dst || !src || len <= 0)
    {
        return KD_RESULT_FAILURE;
    }

    kdi_GenMemOpsCpy(dst, src, KD_USIZE_C(len));

    return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsCpyU16(void *dst, void *src, kd_word_t len)
{
    if (!dst || !src || len <= 0)
    {
        return KD_RESULT_FAILURE;
    }

    kdi_GenMemOpsCpy(dst, src, KD_USIZE_C(len) * KD_SZ_U16);

    return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsCpyU32(void *dst, void *src, kd_word_t len)
{
    if (!dst || !src || len <= 0)
    {
        return KD_RESULT_FAILURE;
    }

    kdi_GenMemOpsCpy(dst, src, KD_USIZE_C(len) * KD_SZ_U32);

    return KD_RESULT_SUCCESS;
}


#if defined KD_ARCH_64BIT_INT
kd_bool_t
kdMemOpsCpyU64(void *dst, void *src, kd_word_t len)
{
    if (!dst || !src || len <= 0)
    {
        return KD_RESULT_FAILURE;
    }

    kdi_GenMemOpsCpy(dst, src, KD_USIZE_C(len) * KD_SZ_U64);

    return KD_RESULT_SUCCESS;
}
#endif /* KD_ARCH_64BIT_INT */


kd_bool_t
kdMemOpsCpyN(void *dst, void *src, kd_word_t len, kd_word_t n)
{
    if (!dst || !src || len <= 0 || n <= 0)
    {
        return KD_RESULT_FAILURE;
    }

    kdi_GenMemOpsCpy(dst, src, KD_USIZE_C(len) * KD_USIZE_C(n));

    return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsMoveU8(void *dst, void *src, kd_word_t len)
{
    if (!dst || !src || len <= 0)
    {
        return KD_RESULT_FAILURE;
    }

    kdi_GenMemOpsMove(dst, src, KD_USIZE_C(len));

    return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsMoveU16(void *dst, void *src, kd_word_t len)
{
    if (!dst || !src || len <= 0)
    {
        return KD_RESULT_FAILURE;
    }

    kdi_GenMemOpsMove(dst, src, KD_USIZE_C(len) * KD_SZ_U16);

    return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemOpsMoveU32(void *dst, void *src, kd_word_t len)
{
    if (!dst || !src || len <= 0)
    {
        return KD_RESULT_FAILURE;
    }

    kdi_GenMemOpsMove(dst, src, KD_USIZE_C(len) * KD_SZ_U32);

    return KD_RESULT_SUCCESS;
}


#if defined KD_ARCH_64BIT_INT
kd_bool_t
kdMemOpsMoveU64(void *dst, void *src, kd_word_t len)
{
    if (!dst || !src || len <= 0)
    {
        return KD_RESULT_FAILURE;
    }

    kdi_GenMemOpsMove(dst, src, KD_USIZE_C(len) * KD_SZ_U64);

    return KD_RESULT_SUCCESS;
}
#endif /* KD_ARCH_64BIT_INT */


kd_bool_t
kdMemOpsMoveN(void *dst, void *src, kd_word_t len, kd_word_t n)
{
    if (!dst || !src || len <= 0 || n <= 0)
    {
        return KD_RESULT_FAILURE;
    }

    kdi_GenMemOpsMove(dst, src, KD_USIZE_C(len) * KD_USIZE_C(n));

    return KD_RESULT_SUCCESS;
}


void *
kdMemOpsFindU8(void *ptr, kd_word_t len, kd_byte_t item)
{
    return (!ptr || len <= 0) ? kd_null : kdi_GenMemOpsFindBlockWithIndex_U8(kd_null, ptr, KD_USIZE_C(len), item);
}


void *
kdMemOpsFindU16(void *ptr, kd_word_t len, kd_u16_t item)
{
    return (!ptr || len <= 0) ? kd_null : kdi_GenMemOpsFindBlockWithIndex_U16(kd_null, ptr, KD_USIZE_C(len) * KD_SZ_U16, item);
}


void *
kdMemOpsFindU32(void *ptr, kd_word_t len, kd_u32_t item)
{
    return (!ptr || len <= 0) ? kd_null : kdi_GenMemOpsFindBlockWithIndex_U32(kd_null, ptr, KD_USIZE_C(len) * KD_SZ_U32, item);
}


#if defined KD_ARCH_64BIT_INT
void *
kdMemOpsFindU64(void *ptr, kd_word_t len, kd_u64_t item)
{
    return (!ptr || len <= 0) ? kd_null : kdi_GenMemOpsFindBlockWithIndex_U64(kd_null, ptr, KD_USIZE_C(len) * KD_SZ_U64, item);
}
#endif /* KD_ARCH_64BIT_INT */


void *
kdMemOpsFindN(void *ptr, kd_word_t len, void *nitem, kd_word_t n)
{
    kd_u8_t  val_u8;
    kd_u16_t val_u16;
    kd_u32_t val_u32;
#if defined KD_ARCH_64BIT_INT
    kd_u64_t val_u64;
#endif

    if (!ptr || len <= 0 || !nitem || n <= 0)
    {
        return kd_null;
    }

    switch (n)
    {
        case 1:
            val_u8 = *KD_PU8_C(nitem);
            return kdi_GenMemOpsFindBlockWithIndex_U8(kd_null, ptr, KD_USIZE_C(len), val_u8);
        case 2:
            val_u16 = *KD_PU16_C(nitem);
            return kdi_GenMemOpsFindBlockWithIndex_U16(kd_null, ptr, KD_USIZE_C(len) * KD_SZ_U16, val_u16);
        case 4:
            val_u32 = *KD_PU32_C(nitem);
            return kdi_GenMemOpsFindBlockWithIndex_U32(kd_null, ptr, KD_USIZE_C(len) * KD_SZ_U32, val_u32);
#if defined KD_ARCH_64BIT_INT
        case 8:
            val_u64 = *KD_PU64_C(nitem);
            return kdi_GenMemOpsFindBlockWithIndex_U64(kd_null, ptr, KD_USIZE_C(len) * KD_SZ_U64, val_u64);
#endif
        default:;
    }

    return kdi_GenMemOpsFindBlockWithIndex_Un(kd_null, ptr, KD_USIZE_C(len) * KD_USIZE_C(n), nitem, KD_USIZE_C(n));
}


kd_word_t
kdMemOpsFindIndexU8(void *ptr, kd_word_t len, kd_byte_t item)
{
    kd_usize_t idx;
    return (ptr && len > 0 && kdi_GenMemOpsFindBlockWithIndex_U8(&idx, ptr, len, item)) ? KD_WORD_C(idx) : -1;
}


kd_word_t
kdMemOpsFindIndexU16(void *ptr, kd_word_t len, kd_u16_t item)
{
    kd_usize_t idx;
    return (ptr && len > 0 && kdi_GenMemOpsFindBlockWithIndex_U16(&idx, ptr, KD_USIZE_C(len) * KD_SZ_U16, item)) ? KD_WORD_C(idx / KD_SZ_U16) : -1;
}


kd_word_t
kdMemOpsFindIndexU32(void *ptr, kd_word_t len, kd_u32_t item)
{
    kd_usize_t idx;
    return (ptr && len > 0 && kdi_GenMemOpsFindBlockWithIndex_U32(&idx, ptr, KD_USIZE_C(len) * KD_SZ_U32, item)) ? KD_WORD_C(idx / KD_SZ_U32) : -1;
}


#if defined KD_ARCH_64BIT_INT
kd_word_t
kdMemOpsFindIndexU64(void *ptr, kd_word_t len, kd_u64_t item)
{
    kd_usize_t idx;
    return (ptr && len > 0 && kdi_GenMemOpsFindBlockWithIndex_U64(&idx, ptr, KD_USIZE_C(len) * KD_SZ_U64, item)) ? KD_WORD_C(idx / KD_SZ_U64) : -1;
}
#endif /* KD_ARCH_64BIT_INT */


kd_word_t
kdMemOpsFindIndexN(void *ptr, kd_word_t len, void *nitem, kd_word_t n)
{
    kd_usize_t idx;
    void      *found_ptr;
    kd_u8_t    val_u8;
    kd_u16_t   val_u16;
    kd_u32_t   val_u32;
#if defined KD_ARCH_64BIT_INT
    kd_u64_t val_u64;
#endif

    if (!ptr || len <= 0 || !nitem || n <= 0)
    {
        return KD_RESULT_FAILURE;
    }

    switch (n)
    {
        case 1:
            val_u8    = *KD_PU8_C(nitem);
            found_ptr = kdi_GenMemOpsFindBlockWithIndex_U8(&idx, ptr, KD_USIZE_C(len), val_u8);
            break;
        case 2:
            val_u16   = *KD_PU16_C(nitem);
            found_ptr = kdi_GenMemOpsFindBlockWithIndex_U16(&idx, ptr, KD_USIZE_C(len) * KD_SZ_U16, val_u16);
            break;
        case 4:
            val_u32   = *KD_PU32_C(nitem);
            found_ptr = kdi_GenMemOpsFindBlockWithIndex_U32(&idx, ptr, KD_USIZE_C(len) * KD_SZ_U32, val_u32);
            break;
#if defined KD_ARCH_64BIT_INT
        case 8:
            val_u64   = *KD_PU64_C(nitem);
            found_ptr = kdi_GenMemOpsFindBlockWithIndex_U64(&idx, ptr, KD_USIZE_C(len) * KD_SZ_U64, val_u64);
            break;
#endif
        default:
            found_ptr = kdi_GenMemOpsFindBlockWithIndex_Un(&idx, ptr, KD_USIZE_C(len) * KD_USIZE_C(n), nitem, KD_USIZE_C(n));
    }

    return found_ptr ? KD_WORD_C(idx / n) : -1;
}


void *
kdMemOpsFindLastU8(void *ptr, kd_word_t len, kd_byte_t item)
{
    return (!ptr || len <= 0) ? kd_null : kdi_GenMemOpsFindLastBlockWithIndex_U8(kd_null, ptr, KD_USIZE_C(len), item);
}


void *
kdMemOpsFindLastU16(void *ptr, kd_word_t len, kd_u16_t item)
{
    return (!ptr || len <= 0) ? kd_null : kdi_GenMemOpsFindLastBlockWithIndex_U16(kd_null, ptr, KD_USIZE_C(len) * KD_SZ_U16, item);
}


void *
kdMemOpsFindLastU32(void *ptr, kd_word_t len, kd_u32_t item)
{
    return (!ptr || len <= 0) ? kd_null : kdi_GenMemOpsFindLastBlockWithIndex_U32(kd_null, ptr, KD_USIZE_C(len) * KD_SZ_U32, item);
}


#if defined KD_ARCH_64BIT_INT
void *
kdMemOpsFindLastU64(void *ptr, kd_word_t len, kd_u64_t item)
{
    return (!ptr || len <= 0) ? kd_null : kdi_GenMemOpsFindLastBlockWithIndex_U64(kd_null, ptr, KD_USIZE_C(len) * KD_SZ_U64, item);
}
#endif /* KD_ARCH_64BIT_INT */


void *
kdMemOpsFindLastN(void *ptr, kd_word_t len, void *nitem, kd_word_t n)
{
    kd_u8_t  val_u8;
    kd_u16_t val_u16;
    kd_u32_t val_u32;
#if defined KD_ARCH_64BIT_INT
    kd_u64_t val_u64;
#endif

    if (!ptr || len <= 0 || !nitem || n <= 0)
    {
        return kd_null;
    }

    switch (n)
    {
        case 1:
            val_u8 = *KD_PU8_C(nitem);
            return kdi_GenMemOpsFindLastBlockWithIndex_U8(kd_null, ptr, KD_USIZE_C(len), val_u8);
        case 2:
            val_u16 = *KD_PU16_C(nitem);
            return kdi_GenMemOpsFindLastBlockWithIndex_U16(kd_null, ptr, KD_USIZE_C(len) * KD_SZ_U16, val_u16);
        case 4:
            val_u32 = *KD_PU32_C(nitem);
            return kdi_GenMemOpsFindLastBlockWithIndex_U32(kd_null, ptr, KD_USIZE_C(len) * KD_SZ_U32, val_u32);
#if defined KD_ARCH_64BIT_INT
        case 8:
            val_u64 = *KD_PU64_C(nitem);
            return kdi_GenMemOpsFindLastBlockWithIndex_U64(kd_null, ptr, KD_USIZE_C(len) * KD_SZ_U64, val_u64);
#endif
        default:;
    }

    return kdi_GenMemOpsFindLastBlockWithIndex_Un(kd_null, ptr, KD_USIZE_C(len) * KD_USIZE_C(n), nitem, KD_USIZE_C(n));
}


kd_word_t
kdMemOpsFindLastIndexU8(void *ptr, kd_word_t len, kd_byte_t item)
{
    kd_usize_t idx;
    return (ptr && len > 0 && kdi_GenMemOpsFindLastBlockWithIndex_U8(&idx, ptr, KD_USIZE_C(len), item)) ? KD_WORD_C(idx) : -1;
}


kd_word_t
kdMemOpsFindLastIndexU16(void *ptr, kd_word_t len, kd_u16_t item)
{
    kd_usize_t idx;
    return (ptr && len > 0 && kdi_GenMemOpsFindLastBlockWithIndex_U16(&idx, ptr, KD_USIZE_C(len) * KD_SZ_U16, item)) ? KD_WORD_C(idx / KD_SZ_U16) : -1;
}


kd_word_t
kdMemOpsFindLastIndexU32(void *ptr, kd_word_t len, kd_u32_t item)
{
    kd_usize_t idx;
    return (ptr && len > 0 && kdi_GenMemOpsFindLastBlockWithIndex_U32(&idx, ptr, KD_USIZE_C(len) * KD_SZ_U32, item)) ? KD_WORD_C(idx / KD_SZ_U32) : -1;
}


#if defined KD_ARCH_64BIT_INT
kd_word_t
kdMemOpsFindLastIndexU64(void *ptr, kd_word_t len, kd_u64_t item)
{
    kd_usize_t idx;
    return (ptr && len > 0 && kdi_GenMemOpsFindLastBlockWithIndex_U64(&idx, ptr, KD_USIZE_C(len) * KD_SZ_U64, item)) ? KD_WORD_C(idx / KD_SZ_U64) : -1;
}
#endif /* KD_ARCH_64BIT_INT */


kd_word_t
kdMemOpsFindLastIndexN(void *ptr, kd_word_t len, void *nitem, kd_word_t n)
{
    kd_usize_t idx;
    void      *found_ptr;
    kd_u8_t    val_u8;
    kd_u16_t   val_u16;
    kd_u32_t   val_u32;
#if defined KD_ARCH_64BIT_INT
    kd_u64_t val_u64;
#endif

    if (!ptr || len <= 0 || !nitem || n <= 0)
    {
        return KD_RESULT_FAILURE;
    }

    switch (n)
    {
        case 1:
            val_u8    = *KD_PU8_C(nitem);
            found_ptr = kdi_GenMemOpsFindLastBlockWithIndex_U8(&idx, ptr, KD_USIZE_C(len), val_u8);
            break;
        case 2:
            val_u16   = *KD_PU16_C(nitem);
            found_ptr = kdi_GenMemOpsFindLastBlockWithIndex_U16(&idx, ptr, KD_USIZE_C(len) * KD_SZ_U16, val_u16);
            break;
        case 4:
            val_u32   = *KD_PU32_C(nitem);
            found_ptr = kdi_GenMemOpsFindLastBlockWithIndex_U32(&idx, ptr, KD_USIZE_C(len) * KD_SZ_U32, val_u32);
            break;
#if defined KD_ARCH_64BIT_INT
        case 8:
            val_u64   = *KD_PU64_C(nitem);
            found_ptr = kdi_GenMemOpsFindLastBlockWithIndex_U64(&idx, ptr, KD_USIZE_C(len) * KD_SZ_U64, val_u64);
            break;
#endif
        default:
            found_ptr = kdi_GenMemOpsFindLastBlockWithIndex_Un(&idx, ptr, KD_USIZE_C(len) * KD_USIZE_C(n), nitem, KD_USIZE_C(n));
    }

    return found_ptr ? KD_WORD_C(idx / n) : -1;
}


kd_word_t
kdMemOpsFindAllU8(void *dst, kd_word_t dst_len, void *ptr, kd_word_t ptr_len, kd_byte_t item)
{
    return (!dst || dst_len <= 0 || !ptr || ptr_len <= 0) ? 0 : KD_WORD_C(kdi_GenMemOpsFindAllBlocks_U8(dst, KD_USIZE_C(dst_len), ptr, KD_USIZE_C(ptr_len), item));
}


kd_word_t
kdMemOpsFindAllU16(void *dst, kd_word_t dst_len, void *ptr, kd_word_t ptr_len, kd_u16_t item)
{
    return (!dst || dst_len <= 0 || !ptr || ptr_len <= 0)
             ? 0
             : KD_WORD_C(kdi_GenMemOpsFindAllBlocks_U16(dst, KD_USIZE_C(dst_len) * KD_SZ_U16, ptr, KD_USIZE_C(ptr_len) * KD_SZ_U16, item));
}


kd_word_t
kdMemOpsFindAllU32(void *dst, kd_word_t dst_len, void *ptr, kd_word_t ptr_len, kd_u32_t item)
{
    return (!dst || dst_len <= 0 || !ptr || ptr_len <= 0)
             ? 0
             : KD_WORD_C(kdi_GenMemOpsFindAllBlocks_U32(dst, KD_USIZE_C(dst_len) * KD_SZ_U32, ptr, KD_USIZE_C(ptr_len) * KD_SZ_U32, item));
}


#if defined KD_ARCH_64BIT_INT
kd_word_t
kdMemOpsFindAllU64(void *dst, kd_word_t dst_len, void *ptr, kd_word_t ptr_len, kd_u64_t item)
{
    return (!dst || dst_len <= 0 || !ptr || ptr_len <= 0)
             ? 0
             : KD_WORD_C(kdi_GenMemOpsFindAllBlocks_U64(dst, KD_USIZE_C(dst_len) * KD_SZ_U64, ptr, KD_USIZE_C(ptr_len) * KD_SZ_U64, item));
}
#endif /* KD_ARCH_64BIT_INT */


kd_word_t
kdMemOpsFindAllN(void *dst, kd_word_t dst_len, void *ptr, kd_word_t ptr_len, void *nitem, kd_word_t n)
{
    kd_u8_t  val_u8;
    kd_u16_t val_u16;
    kd_u32_t val_u32;
#if defined KD_ARCH_64BIT_INT
    kd_u64_t val_u64;
#endif

    if (!dst || dst_len <= 0 || !ptr || ptr_len <= 0 || !nitem || n <= 0)
    {
        return 0;
    }

    switch (n)
    {
        case 1:
            val_u8 = *KD_PU8_C(nitem);
            return kdi_GenMemOpsFindAllBlocks_U8(dst, KD_USIZE_C(dst_len), ptr, KD_USIZE_C(ptr_len), val_u8);
        case 2:
            val_u16 = *KD_PU16_C(nitem);
            return kdi_GenMemOpsFindAllBlocks_U16(dst, KD_USIZE_C(dst_len) * KD_SZ_U16, ptr, KD_USIZE_C(ptr_len) * KD_SZ_U16, val_u16);
        case 4:
            val_u32 = *KD_PU32_C(nitem);
            return kdi_GenMemOpsFindAllBlocks_U32(dst, KD_USIZE_C(dst_len) * KD_SZ_U32, ptr, KD_USIZE_C(ptr_len) * KD_SZ_U32, val_u32);
#if defined KD_ARCH_64BIT_INT
        case 8:
            val_u64 = *KD_PU64_C(nitem);
            return kdi_GenMemOpsFindAllBlocks_U64(dst, KD_USIZE_C(dst_len) * KD_SZ_U64, ptr, KD_USIZE_C(ptr_len) * KD_SZ_U64, val_u64);
#endif
        default:;
    }

    return kdi_GenMemOpsFindAllBlocks_Un(dst, KD_USIZE_C(dst_len) * KD_USIZE_C(n), ptr, KD_USIZE_C(ptr_len) * KD_USIZE_C(n), nitem, KD_USIZE_C(n));
}


kd_word_t
kdMemOpsFindAllIndicesU8(void *idxs, enum kd_eltype_t idx_type, kd_word_t idxs_len, void *ptr, kd_word_t ptr_len, kd_byte_t item)
{
    if (!idxs || idxs_len <= 0 || !ptr || ptr_len <= 0)
    {
        return 0;
    }

    idx_type = idx_type <= 0 ? KD_ELTYPE_WORD : idx_type;

    switch (idx_type)
    {
        case KD_ELTYPE_BYTE:
        case KD_ELTYPE_I8:
        case KD_ELTYPE_U8:
        case KD_ELTYPE_IMIN:
        case KD_ELTYPE_UMIN:
            return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U8_Idx8(idxs, KD_USIZE_C(idxs_len), ptr, KD_USIZE_C(ptr_len), item, kd_true));

        case KD_ELTYPE_I16:
        case KD_ELTYPE_U16:
            return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U8_Idx16(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U16, ptr, KD_USIZE_C(ptr_len), item, kd_true));

        case KD_ELTYPE_I32:
        case KD_ELTYPE_U32:
        case KD_ELTYPE_BOOL:
        case KD_ELTYPE_CHR:
            return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U8_Idx32(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U32, ptr, KD_USIZE_C(ptr_len), item, kd_true));

#if defined KD_ARCH_64BIT_INT
        case KD_ELTYPE_I64:
        case KD_ELTYPE_U64:
#endif
        case KD_ELTYPE_UMAX:
        case KD_ELTYPE_IMAX:
        case KD_ELTYPE_WORD:
        case KD_ELTYPE_USIZE:
        case KD_ELTYPE_PTR:
#if defined KD_ARCH_64BIT_INT
            return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U8_Idx64(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U64, ptr, KD_USIZE_C(ptr_len), item, kd_true));
#else
            return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U8_Idx32(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U32, ptr, KD_USIZE_C(ptr_len), item, kd_true));
#endif

        default:;
    }

    return 0;
}


kd_word_t
kdMemOpsFindAllIndicesU16(void *idxs, enum kd_eltype_t idx_type, kd_word_t idxs_len, void *ptr, kd_word_t ptr_len, kd_u16_t item)
{
    if (!idxs || idxs_len <= 0 || !ptr || ptr_len <= 0)
    {
        return 0;
    }

    idx_type = idx_type <= 0 ? KD_ELTYPE_WORD : idx_type;

    switch (idx_type)
    {
        case KD_ELTYPE_BYTE:
        case KD_ELTYPE_I8:
        case KD_ELTYPE_U8:
        case KD_ELTYPE_IMIN:
        case KD_ELTYPE_UMIN:
            return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U16_Idx8(idxs, KD_USIZE_C(idxs_len), ptr, KD_USIZE_C(ptr_len) * KD_SZ_U16, item, kd_true));

        case KD_ELTYPE_I16:
        case KD_ELTYPE_U16:
            return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U16_Idx16(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U16, ptr, KD_USIZE_C(ptr_len) * KD_SZ_U16, item, kd_true));

        case KD_ELTYPE_I32:
        case KD_ELTYPE_U32:
        case KD_ELTYPE_BOOL:
        case KD_ELTYPE_CHR:
            return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U16_Idx32(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U32, ptr, KD_USIZE_C(ptr_len) * KD_SZ_U16, item, kd_true));

#if defined KD_ARCH_64BIT_INT
        case KD_ELTYPE_I64:
        case KD_ELTYPE_U64:
#endif
        case KD_ELTYPE_UMAX:
        case KD_ELTYPE_IMAX:
        case KD_ELTYPE_WORD:
        case KD_ELTYPE_USIZE:
        case KD_ELTYPE_PTR:
#if defined KD_ARCH_64BIT_INT
            return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U16_Idx64(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U64, ptr, KD_USIZE_C(ptr_len) * KD_SZ_U16, item, kd_true));
#else
            return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U16_Idx32(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U32, ptr, KD_USIZE_C(ptr_len) * KD_SZ_U16, item, kd_true));
#endif

        default:;
    }

    return 0;
}


kd_word_t
kdMemOpsFindAllIndicesU32(void *idxs, enum kd_eltype_t idx_type, kd_word_t idxs_len, void *ptr, kd_word_t ptr_len, kd_u32_t item)
{
    if (!idxs || idxs_len <= 0 || !ptr || ptr_len <= 0)
    {
        return 0;
    }

    idx_type = idx_type <= 0 ? KD_ELTYPE_WORD : idx_type;

    switch (idx_type)
    {
        case KD_ELTYPE_BYTE:
        case KD_ELTYPE_I8:
        case KD_ELTYPE_U8:
        case KD_ELTYPE_IMIN:
        case KD_ELTYPE_UMIN:
            return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U32_Idx8(idxs, KD_USIZE_C(idxs_len), ptr, KD_USIZE_C(ptr_len) * KD_SZ_U32, item, kd_true));

        case KD_ELTYPE_I16:
        case KD_ELTYPE_U16:
            return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U32_Idx16(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U16, ptr, KD_USIZE_C(ptr_len) * KD_SZ_U32, item, kd_true));

        case KD_ELTYPE_I32:
        case KD_ELTYPE_U32:
        case KD_ELTYPE_BOOL:
        case KD_ELTYPE_CHR:
            return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U32_Idx32(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U32, ptr, KD_USIZE_C(ptr_len) * KD_SZ_U32, item, kd_true));

#if defined KD_ARCH_64BIT_INT
        case KD_ELTYPE_I64:
        case KD_ELTYPE_U64:
#endif
        case KD_ELTYPE_UMAX:
        case KD_ELTYPE_IMAX:
        case KD_ELTYPE_WORD:
        case KD_ELTYPE_USIZE:
        case KD_ELTYPE_PTR:
#if defined KD_ARCH_64BIT_INT
            return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U32_Idx64(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U64, ptr, KD_USIZE_C(ptr_len) * KD_SZ_U32, item, kd_true));
#else
            return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U32_Idx32(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U32, ptr, KD_USIZE_C(ptr_len) * KD_SZ_U32, item, kd_true));
#endif

        default:;
    }

    return 0;
}


#if defined KD_ARCH_64BIT_INT
kd_word_t
kdMemOpsFindAllIndicesU64(void *idxs, enum kd_eltype_t idx_type, kd_word_t idxs_len, void *ptr, kd_word_t ptr_len, kd_u64_t item)
{
    if (!idxs || idxs_len <= 0 || !ptr || ptr_len <= 0)
    {
        return 0;
    }

    idx_type = idx_type <= 0 ? KD_ELTYPE_WORD : idx_type;

    switch (idx_type)
    {
        case KD_ELTYPE_BYTE:
        case KD_ELTYPE_I8:
        case KD_ELTYPE_U8:
        case KD_ELTYPE_IMIN:
        case KD_ELTYPE_UMIN:
            return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U64_Idx8(idxs, KD_USIZE_C(idxs_len), ptr, KD_USIZE_C(ptr_len) * KD_SZ_U64, item, kd_true));

        case KD_ELTYPE_I16:
        case KD_ELTYPE_U16:
            return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U64_Idx16(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U16, ptr, KD_USIZE_C(ptr_len) * KD_SZ_U64, item, kd_true));

        case KD_ELTYPE_I32:
        case KD_ELTYPE_U32:
        case KD_ELTYPE_BOOL:
        case KD_ELTYPE_CHR:
            return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U64_Idx32(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U32, ptr, KD_USIZE_C(ptr_len) * KD_SZ_U64, item, kd_true));

        case KD_ELTYPE_I64:
        case KD_ELTYPE_U64:
        case KD_ELTYPE_UMAX:
        case KD_ELTYPE_IMAX:
        case KD_ELTYPE_WORD:
        case KD_ELTYPE_USIZE:
        case KD_ELTYPE_PTR:
            return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_U64_Idx64(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U64, ptr, KD_USIZE_C(ptr_len) * KD_SZ_U64, item, kd_true));

        default:;
    }

    return 0;
}
#endif /* KD_ARCH_64BIT_INT */


kd_word_t
kdMemOpsFindAllIndicesN(void *idxs, enum kd_eltype_t idx_type, kd_word_t idxs_len, void *ptr, kd_word_t ptr_len, void *nitem, kd_word_t n)
{
    if (!idxs || idxs_len <= 0 || !ptr || ptr_len <= 0 || !nitem || n <= 0)
    {
        return 0;
    }

    idx_type = idx_type <= 0 ? KD_ELTYPE_WORD : idx_type;

    switch (idx_type)
    {
        case KD_ELTYPE_BYTE:
        case KD_ELTYPE_I8:
        case KD_ELTYPE_U8:
        case KD_ELTYPE_IMIN:
        case KD_ELTYPE_UMIN:
            return KD_WORD_C(kdi_GenMemOpsFindAllBlockIndices_Un_Idx8(idxs, KD_USIZE_C(idxs_len), ptr, KD_USIZE_C(ptr_len) * KD_USIZE_C(n), nitem, KD_USIZE_C(n), kd_true));

        case KD_ELTYPE_I16:
        case KD_ELTYPE_U16:
            return KD_WORD_C(
                kdi_GenMemOpsFindAllBlockIndices_Un_Idx16(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U16, ptr, KD_USIZE_C(ptr_len) * KD_USIZE_C(n), nitem, KD_USIZE_C(n), kd_true)
            );

        case KD_ELTYPE_I32:
        case KD_ELTYPE_U32:
        case KD_ELTYPE_BOOL:
        case KD_ELTYPE_CHR:
            return KD_WORD_C(
                kdi_GenMemOpsFindAllBlockIndices_Un_Idx32(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U32, ptr, KD_USIZE_C(ptr_len) * KD_USIZE_C(n), nitem, KD_USIZE_C(n), kd_true)
            );

#if defined KD_ARCH_64BIT_INT
        case KD_ELTYPE_I64:
        case KD_ELTYPE_U64:
#endif
        case KD_ELTYPE_UMAX:
        case KD_ELTYPE_IMAX:
        case KD_ELTYPE_WORD:
        case KD_ELTYPE_USIZE:
        case KD_ELTYPE_PTR:
#if defined KD_ARCH_64BIT_INT
            return KD_WORD_C(
                kdi_GenMemOpsFindAllBlockIndices_Un_Idx64(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U64, ptr, KD_USIZE_C(ptr_len) * KD_USIZE_C(n), nitem, KD_USIZE_C(n), kd_true)
            );
#else
            return KD_WORD_C(
                kdi_GenMemOpsFindAllBlockIndices_Un_Idx32(idxs, KD_USIZE_C(idxs_len) * KD_SZ_U32, ptr, KD_USIZE_C(ptr_len) * KD_USIZE_C(n), nitem, KD_USIZE_C(n), kd_true)
            );
#endif

        default:;
    }

    return 0;
}


kd_word_t
kdMemOpsCmpU8(void *ptr1, void *ptr2, kd_word_t len)
{
    return len < 0 ? 0 : kdGenMemOpsCmp(ptr1, ptr2, len);
}


kd_word_t
kdMemOpsCmpU16(void *ptr1, void *ptr2, kd_word_t len)
{
    return len < 0 ? 0 : kdGenMemOpsCmp(ptr1, ptr2, KD_USIZE_C(len) * KD_SZ_U16);
}


kd_word_t
kdMemOpsCmpU32(void *ptr1, void *ptr2, kd_word_t len)
{
    return len < 0 ? 0 : kdGenMemOpsCmp(ptr1, ptr2, KD_USIZE_C(len) * KD_SZ_U32);
}


#if defined KD_ARCH_64BIT_INT
kd_word_t
kdMemOpsCmpU64(void *ptr1, void *ptr2, kd_word_t len)
{
    return len < 0 ? 0 : kdGenMemOpsCmp(ptr1, ptr2, KD_USIZE_C(len) * KD_SZ_U64);
}
#endif


kd_word_t
kdMemOpsCmpN(void *ptr1, void *ptr2, kd_word_t len, kd_word_t n)
{
    return len < 0 || n <= 0 ? 0 : kdGenMemOpsCmp(ptr1, ptr2, KD_USIZE_C(len) * n);
}


kd_bool_t
kdMemOpsCatU8(void *dst, kd_word_t dst_len, void *src1, kd_word_t src1_len, void *src2, kd_word_t src2_len)
{
    return dst_len < 0 || src1_len < 0 || src2_len < 0 ? 0 : kdGenMemOpsCat(dst, KD_USIZE_C(dst_len), src1, KD_USIZE_C(src1_len), src2, KD_USIZE_C(src2_len));
}


kd_bool_t
kdMemOpsCatU16(void *dst, kd_word_t dst_len, void *src1, kd_word_t src1_len, void *src2, kd_word_t src2_len)
{
    return dst_len < 0 || src1_len < 0 || src2_len < 0
             ? 0
             : kdGenMemOpsCat(dst, KD_USIZE_C(dst_len) * KD_SZ_U16, src1, KD_USIZE_C(src1_len) * KD_SZ_U16, src2, KD_USIZE_C(src2_len) * KD_SZ_U16);
}


kd_bool_t
kdMemOpsCatU32(void *dst, kd_word_t dst_len, void *src1, kd_word_t src1_len, void *src2, kd_word_t src2_len)
{
    return dst_len < 0 || src1_len < 0 || src2_len < 0
             ? 0
             : kdGenMemOpsCat(dst, KD_USIZE_C(dst_len) * KD_SZ_U32, src1, KD_USIZE_C(src1_len) * KD_SZ_U32, src2, KD_USIZE_C(src2_len) * KD_SZ_U32);
}


#if defined KD_ARCH_64BIT_INT
kd_bool_t
kdMemOpsCatU64(void *dst, kd_word_t dst_len, void *src1, kd_word_t src1_len, void *src2, kd_word_t src2_len)
{
    return dst_len < 0 || src1_len < 0 || src2_len < 0
             ? 0
             : kdGenMemOpsCat(dst, KD_USIZE_C(dst_len) * KD_SZ_U64, src1, KD_USIZE_C(src1_len) * KD_SZ_U64, src2, KD_USIZE_C(src2_len) * KD_SZ_U64);
}
#endif


kd_bool_t
kdMemOpsCatN(void *dst, kd_word_t dst_len, void *src1, kd_word_t src1_len, void *src2, kd_word_t src2_len, kd_word_t n)
{
    return dst_len < 0 || src1_len < 0 || src2_len < 0 ? 0 : kdGenMemOpsCat(dst, KD_USIZE_C(dst_len) * KD_USIZE_C(n), src1, KD_USIZE_C(src1_len) * KD_USIZE_C(n), src2, KD_USIZE_C(src2_len) * KD_USIZE_C(n));
}


void *
kdMemOpsCompSpnU8(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len)
{
    return (!ptr || !keys || len <= 0 || keys_len <= 0) ? kd_null : kdi_GenMemOpsBlocksCompSpnWithIndex_U8(kd_null, ptr, KD_USIZE_C(len), keys, KD_USIZE_C(keys_len));
}


void *
kdMemOpsCompSpnU16(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len)
{
    return (!ptr || !keys || len <= 0 || keys_len <= 0)
             ? kd_null
             : kdi_GenMemOpsBlocksCompSpnWithIndex_U16(kd_null, ptr, KD_USIZE_C(len) * KD_SZ_U16, keys, KD_USIZE_C(keys_len) * KD_SZ_U16);
}


void *
kdMemOpsCompSpnU32(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len)
{
    return (!ptr || !keys || len <= 0 || keys_len <= 0)
             ? kd_null
             : kdi_GenMemOpsBlocksCompSpnWithIndex_U32(kd_null, ptr, KD_USIZE_C(len) * KD_SZ_U32, keys, KD_USIZE_C(keys_len) * KD_SZ_U32);
}


#if defined KD_ARCH_64BIT_INT
void *
kdMemOpsCompSpnU64(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len)
{
    return (!ptr || !keys || len <= 0 || keys_len <= 0)
             ? kd_null
             : kdi_GenMemOpsBlocksCompSpnWithIndex_U64(kd_null, ptr, KD_USIZE_C(len) * KD_SZ_U64, keys, KD_USIZE_C(keys_len) * KD_SZ_U64);
}
#endif /* KD_ARCH_64BIT_INT */


void *
kdMemOpsCompSpnN(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len, kd_word_t n)
{
    return (len < 0 || keys_len < 0 || n <= 0) ? kd_null : kdGenMemOpsBlocksCompSpn(ptr, KD_USIZE_C(len) * n, keys, n, KD_USIZE_C(keys_len) * n);
    if (!ptr || len <= 0 || !keys || keys_len <= 0 || n <= 0)
    {
        return kd_null;
    }

    switch (n)
    {
        case 1:
            return kdi_GenMemOpsBlocksCompSpnWithIndex_U8(kd_null, ptr, sz, key_blocks, KD_USIZE_C(keys_len));
        case 2:
            return kdi_GenMemOpsBlocksCompSpnWithIndex_U16(kd_null, ptr, sz, key_blocks, KD_USIZE_C(keys_len));
        case 4:
            return kdi_GenMemOpsBlocksCompSpnWithIndex_U32(kd_null, ptr, sz, key_blocks, KD_USIZE_C(keys_len));
#if defined KD_ARCH_64BIT_INT
        case 8:
            return kdi_GenMemOpsBlocksCompSpnWithIndex_U64(kd_null, ptr, sz, key_blocks, KD_USIZE_C(keys_len));
#endif
        default:;
    }

    return kdi_GenMemOpsBlocksCompSpnWithIndex_Un(kd_null, ptr, sz, key_blocks, n, KD_USIZE_C(keys_len));
}


kd_word_t
kdMemOpsCompSpnIndexU8(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len)
{
    kd_usize_t idx;
    return (ptr && len > 0 && keys && keys_len >= 0 && kdi_GenMemOpsBlocksCompSpnWithIndex_U8(&idx, ptr, KD_USIZE_C(len), keys, KD_USIZE_C(keys_len))) ? KD_WORD_C(idx) : -1;
}


kd_word_t
kdMemOpsCompSpnIndexU16(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len)
{
    kd_usize_t idx;
    return (ptr && len > 0 && keys && keys_len >= 0 && kdi_GenMemOpsBlocksCompSpnWithIndex_U16(&idx, ptr, KD_USIZE_C(len) * KD_SZ_U16, keys, KD_USIZE_C(keys_len) * KD_SZ_U16))
             ? KD_WORD_C(idx / KD_SZ_U16)
             : -1;
}


kd_word_t
kdMemOpsCompSpnIndexU32(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len)
{
    kd_usize_t idx;
    return (ptr && len > 0 && keys && keys_len >= 0 && kdi_GenMemOpsBlocksCompSpnWithIndex_U32(&idx, ptr, KD_USIZE_C(len) * KD_SZ_U32, keys, KD_USIZE_C(keys_len) * KD_SZ_U32))
             ? KD_WORD_C(idx / KD_SZ_U32)
             : -1;
}


#if defined KD_ARCH_64BIT_INT
kd_word_t
kdMemOpsCompSpnIndexU64(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len)
{
    kd_usize_t idx;
    return (ptr && len > 0 && keys && keys_len >= 0 && kdi_GenMemOpsBlocksCompSpnWithIndex_U64(&idx, ptr, KD_USIZE_C(len) * KD_SZ_U64, keys, KD_USIZE_C(keys_len) * KD_SZ_U64))
             ? KD_WORD_C(idx / KD_SZ_U64)
             : -1;
}
#endif /* KD_ARCH_64BIT_INT */


kd_word_t
kdMemOpsCompSpnIndexN(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len, kd_word_t n)
{
    return (len > 0 && keys_len > 0 && n > 0 && kdGenMemOpsBlocksCompSpnIndex(&idx, ptr, KD_USIZE_C(len) * n, keys, n, KD_USIZE_C(keys_len) * n)) ? KD_WORD_C(idx / n) : -1;

    kd_usize_t idx;
    kd_byte_t *found_ptr;

    if (!ptr || len <= 0 || !keys || keys_len <= 0 || n <= 0)
    {
        return KD_RESULT_FAILURE;
    }

    switch (n)
    {
        case 1:
            found_ptr = kdi_GenMemOpsBlocksCompSpnWithIndex_U8(&idx, ptr, KD_USIZE_C(len), keys, KD_USIZE_C(keys_len));
            break;
        case 2:
            found_ptr = kdi_GenMemOpsBlocksCompSpnWithIndex_U16(&idx, ptr, KD_USIZE_C(len), keys, KD_USIZE_C(keys_len));
            break;
        case 4:
            found_ptr = kdi_GenMemOpsBlocksCompSpnWithIndex_U32(&idx, ptr, KD_USIZE_C(len), keys, KD_USIZE_C(keys_len));
            break;
#if defined KD_ARCH_64BIT_INT
        case 8:
            found_ptr = kdi_GenMemOpsBlocksCompSpnWithIndex_U64(&idx, ptr, KD_USIZE_C(len), keys, KD_USIZE_C(keys_len));
            break;
#endif
        default:
            found_ptr = kdi_GenMemOpsBlocksCompSpnWithIndex_Un(&idx, ptr, KD_USIZE_C(len), keys, KD_USIZE_C(n), KD_USIZE_C(keys_len));
    }

    return found_ptr ? KD_RESULT_SUCCESS : KD_RESULT_FAILURE;
}


kd_word_t
kdMemOpsSpnU8(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len)
{
    return (!ptr || !keys || len <= 0 || keys_len <= 0) ? 0 : KD_WORD_C(kdi_GenMemOpsBlocksSpn_U8(ptr, len, keys, keys_len));
}


kd_word_t
kdMemOpsSpnU16(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len)
{
    return (!ptr || !keys || len <= 0 || keys_len <= 0)
             ? 0
             : KD_WORD_C(kdi_GenMemOpsBlocksSpn_U16(ptr, KD_USIZE_C(len) * KD_SZ_U16, keys, KD_USIZE_C(keys_len) * KD_SZ_U16) / KD_SZ_U16);
}


kd_word_t
kdMemOpsSpnU32(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len)
{
    return (!ptr || !keys || len <= 0 || keys_len <= 0)
             ? 0
             : KD_WORD_C(kdi_GenMemOpsBlocksSpn_U32(ptr, KD_USIZE_C(len) * KD_SZ_U32, keys, KD_USIZE_C(keys_len) * KD_SZ_U32) / KD_SZ_U32);
}


#if defined KD_ARCH_64BIT_INT
kd_word_t
kdMemOpsSpnU64(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len)
{
    return (!ptr || !keys || len <= 0 || keys_len <= 0)
             ? 0
             : KD_WORD_C(kdi_GenMemOpsBlocksSpn_U64(ptr, KD_USIZE_C(len) * KD_SZ_U64, keys, KD_USIZE_C(keys_len) * KD_SZ_U64) / KD_SZ_U64);
}
#endif /* KD_ARCH_64BIT_INT */


kd_word_t
kdMemOpsSpnN(void *ptr, kd_word_t len, void *keys, kd_word_t keys_len, kd_word_t n)
{
    return (len < 0 || keys_len < 0 || n <= 0) ? 0 : KD_WORD_C(kdGenMemOpsBlocksSpn(ptr, KD_USIZE_C(len) * n, keys, n, KD_USIZE_C(keys_len) * n) / n);
}
