/**
 * @file gen_mem_ops.c
 * @author Kumarjit Das
 * @version 0.0.1
 * @brief Main source file of the KD_GEN_MEM_OPS library.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 * @since 0.0.1
 */


#define BUILDING_LIB 1
#include "../include/kd/gen_mem_ops.h"

#include "./internal/gen_mem_ops.h"


bool
GenMemOpsCopy(void *dst, void *src, usize sz)
{
    if (!dst || !src || !sz)
    {
        return RESULT_FAILURE;
    }

    kdi_GenMemOpsCopy(PBYTE_C(dst), PBYTE_C(src), sz);

    return RESULT_SUCCESS;
}


bool
GenMemOpsCopyRegion(void *dst, usize dst_sz, usize *copied_sz, void *src, usize src_sz)
{
    if (!copied_sz)
    {
        return RESULT_FAILURE;
    }

    *copied_sz = 0;

    if (!dst || !dst_sz || !src || !src_sz)
    {
        return RESULT_FAILURE;
    }

    *copied_sz = dst_sz < src_sz ? dst_sz : src_sz;

    kdi_GenMemOpsCopy(PBYTE_C(dst), PBYTE_C(src), *copied_sz);

    return RESULT_SUCCESS;
}


bool
GenMemOpsCopyRange(void *dst_base, usize dst_base_sz, usize *copied_sz, void *src_base, usize src_base_sz, usize dst_idx, usize src_idx, usize byte_count)
{
    usize final_dst_sz, final_src_sz;

    if (!copied_sz)
    {
        return RESULT_FAILURE;
    }

    *copied_sz = 0;

    if (!dst_base || !src_base || !src_base_sz || dst_idx >= dst_base_sz || src_idx >= src_base_sz || !byte_count)
    {
        return RESULT_FAILURE;
    }

    final_dst_sz = dst_base_sz - dst_idx;
    final_dst_sz = final_dst_sz > byte_count ? byte_count : final_dst_sz;

    final_src_sz = src_base_sz - src_idx;
    final_src_sz = final_src_sz > byte_count ? byte_count : final_src_sz;

    *copied_sz   = final_dst_sz < final_src_sz ? final_dst_sz : final_src_sz;

    kdi_GenMemOpsCopy(PBYTE_C(dst_base) + dst_idx, PBYTE_C(src_base) + src_idx, *copied_sz);

    return RESULT_SUCCESS;
}


bool
GenMemOpsMove(void *dst, void *src, usize sz)
{
    if (!dst || !src || !sz)
    {
        return RESULT_FAILURE;
    }

    kdi_GenMemOpsMove(PBYTE_C(dst), PBYTE_C(src), sz);

    return RESULT_SUCCESS;
}


bool
GenMemOpsMoveRegion(void *dst, usize dst_sz, usize *moved_sz, void *src, usize src_sz)
{
    if (!moved_sz)
    {
        return RESULT_FAILURE;
    }

    *moved_sz = 0;

    if (!dst || !dst_sz || !src || !src_sz)
    {
        return RESULT_FAILURE;
    }

    *moved_sz = dst_sz < src_sz ? dst_sz : src_sz;

    kdi_GenMemOpsMove(PBYTE_C(dst), PBYTE_C(src), *moved_sz);

    return RESULT_SUCCESS;
}


bool
GenMemOpsMoveRange(void *dst_base, usize dst_base_sz, usize *moved_sz, void *src_base, usize src_base_sz, usize dst_idx, usize src_idx, usize byte_count)
{
    usize final_dst_sz, final_src_sz;

    if (!moved_sz)
    {
        return RESULT_FAILURE;
    }

    *moved_sz = 0;

    if (!dst_base || !src_base || !src_base_sz || dst_idx >= dst_base_sz || src_idx >= src_base_sz || !byte_count)
    {
        return RESULT_FAILURE;
    }

    final_dst_sz = dst_base_sz - dst_idx;
    final_dst_sz = final_dst_sz > byte_count ? byte_count : final_dst_sz;

    final_src_sz = src_base_sz - src_idx;
    final_src_sz = final_src_sz > byte_count ? byte_count : final_src_sz;

    *moved_sz    = final_dst_sz < final_src_sz ? final_dst_sz : final_src_sz;

    kdi_GenMemOpsMove(PBYTE_C(dst_base) + dst_idx, PBYTE_C(src_base) + src_idx, *moved_sz);

    return RESULT_SUCCESS;
}


bool
GenMemOpsConcat(void *dst, usize dst_sz, usize *concat_sz, void *src_1, usize src_1_sz, void *src_2, usize src_2_sz)
{
    if (!concat_sz)
    {
        return RESULT_FAILURE;
    }

    *concat_sz = 0;

    if (!dst || !dst_sz || !src_1 || !src_1_sz || !src_2 || !src_2_sz)
    {
        return RESULT_FAILURE;
    }

    *concat_sz = src_1_sz + src_2_sz;
    *concat_sz = dst_sz < *concat_sz ? dst_sz : *concat_sz;

    kdi_GenMemOpsConcat(PBYTE_C(dst), dst_sz, PBYTE_C(src_1), src_1_sz, PBYTE_C(src_2), src_2_sz);

    return RESULT_SUCCESS;
}


bool
GenMemOpsConcatRange(void *dst_base, usize dst_base_sz, usize dst_idx, usize *concat_sz, void *src_base_1, usize src_base_1_sz, usize src_1_begin_idx, usize src_1_byte_count, void *src_base_2, usize src_base_2_sz, usize src_2_begin_idx, usize src_2_byte_count)
{
    usize final_dst_sz, final_src_1_sz, final_src_2_sz;

    if (!concat_sz)
    {
        return RESULT_FAILURE;
    }

    *concat_sz = 0;

    if (!dst_base || dst_idx >= dst_base_sz || !src_base_1 || src_1_begin_idx >= src_base_1_sz || !src_1_byte_count || !src_base_2 || src_2_begin_idx >= src_base_2_sz || !src_2_byte_count)
    {
        return RESULT_FAILURE;
    }

    final_dst_sz   = dst_base_sz - dst_idx;

    final_src_1_sz = src_base_1_sz - src_1_begin_idx;
    final_src_1_sz = final_src_1_sz > src_1_byte_count ? src_1_byte_count : final_src_1_sz;

    final_src_2_sz = src_base_1_sz - src_2_begin_idx;
    final_src_2_sz = final_src_2_sz > src_2_byte_count ? src_2_byte_count : final_src_2_sz;

    *concat_sz     = final_src_1_sz + final_src_2_sz;
    *concat_sz     = final_dst_sz < *concat_sz ? final_dst_sz : *concat_sz;

    kdi_GenMemOpsConcat(PBYTE_C(dst_base) + dst_idx, final_dst_sz, PBYTE_C(src_base_1) + src_1_begin_idx, final_src_1_sz, PBYTE_C(src_base_2) + src_2_begin_idx, final_src_2_sz);

    return RESULT_SUCCESS;
}


bool
GenMemOpsSetBytes(void *dst, usize sz, byte val)
{
    if (!dst || !sz)
    {
        return RESULT_FAILURE;
    }

    kdi_GenMemOpsSetBlocks_U8(PBYTE_C(dst), sz, val);

    return RESULT_SUCCESS;
}


bool
GenMemOpsSetBytesRange(void *base, usize base_sz, usize *set_sz, usize begin_idx, usize count, byte val)
{
    if (!set_sz)
    {
        return RESULT_FAILURE;
    }

    *set_sz = 0;

    if (!base || !base_sz || begin_idx >= base_sz || !count)
    {
        return RESULT_FAILURE;
    }

    *set_sz = base_sz - begin_idx;
    *set_sz = count < *set_sz ? count : *set_sz;

    kdi_GenMemOpsSetBlocks_U8(PBYTE_C(base) + begin_idx, *set_sz, val);

    return RESULT_SUCCESS;
}


bool
GenMemOpsSetBlocks(void *dst, usize dst_sz, void *block, usize block_sz)
{
    u8  block_val_u8;
    u16 block_val_u16;
    u32 block_val_u32;
#if defined ARCH_64BIT_INT
    u64 block_val_u64;
#endif

    if (!dst || !dst_sz || !block || !block_sz)
    {
        return RESULT_FAILURE;
    }

    if (dst_sz % block_sz)
    {
        kdi_GenMemOpsSetBlocks_Un(dst, dst_sz, block, block_sz);
        return RESULT_SUCCESS;
    }

    switch (block_sz)
    {
        case 1:
            block_val_u8 = *PU8_C(block);
            kdi_GenMemOpsSetBlocks_U8(dst, dst_sz, block_val_u8);
            break;
        case 2:
            block_val_u16 = *PU16_C(block);
            kdi_GenMemOpsSetBlocks_U16(dst, dst_sz, block_val_u16);
            break;
        case 4:
            block_val_u32 = *PU32_C(block);
            kdi_GenMemOpsSetBlocks_U32(dst, dst_sz, block_val_u32);
            break;
#if defined ARCH_64BIT_INT
        case 8:
            block_val_u64 = *PU64_C(block);
            kdi_GenMemOpsSetBlocks_U64(dst, dst_sz, block_val_u64);
            break;
#endif
        default:
            kdi_GenMemOpsSetBlocks_Un(dst, dst_sz, block, block_sz);
    }

    return RESULT_SUCCESS;
}


bool
GenMemOpsSetBlocksRange(void *base, usize base_sz, usize *set_sz, usize begin_idx, usize byte_count, void *block, usize block_sz)
{
    u8  block_val_u8;
    u16 block_val_u16;
    u32 block_val_u32;
#if defined ARCH_64BIT_INT
    u64 block_val_u64;
#endif

    if (!set_sz)
    {
        return RESULT_FAILURE;
    }

    *set_sz = 0;

    if (!base || !base_sz || begin_idx >= base_sz || !byte_count || !block || !block_sz)
    {
        return RESULT_FAILURE;
    }

    *set_sz = base_sz - begin_idx;
    *set_sz = byte_count < *set_sz ? byte_count : *set_sz;

    if (*set_sz % block_sz)
    {
        kdi_GenMemOpsSetBlocks_Un(PBYTE_C(base) + begin_idx, *set_sz, block, block_sz);
        return RESULT_SUCCESS;
    }

    switch (block_sz)
    {
        case 1:
            block_val_u8 = *PU8_C(block);
            kdi_GenMemOpsSetBlocks_U8(PU8_C(PBYTE_C(base) + begin_idx), *set_sz, block_val_u8);
            break;
        case 2:
            block_val_u16 = *PU16_C(block);
            kdi_GenMemOpsSetBlocks_U16(PU16_C(PBYTE_C(base) + begin_idx), *set_sz, block_val_u16);
            break;
        case 4:
            block_val_u32 = *PU32_C(block);
            kdi_GenMemOpsSetBlocks_U32(PU32_C(PBYTE_C(base) + begin_idx), *set_sz, block_val_u32);
            break;
#if defined ARCH_64BIT_INT
        case 8:
            block_val_u64 = *PU64_C(block);
            kdi_GenMemOpsSetBlocks_U64(PU64_C(PBYTE_C(base) + begin_idx), *set_sz, block_val_u64);
            break;
#endif
        default:
            kdi_GenMemOpsSetBlocks_Un(PBYTE_C(base) + begin_idx, *set_sz, block, block_sz);
    }

    return RESULT_SUCCESS;
}


bool
GenMemOpsReverseBytes(void *ptr, usize sz)
{
    if (!ptr)
    {
        return RESULT_FAILURE;
    }

    if (!sz)
    {
        return RESULT_SUCCESS;
    }

    kdi_GenMemOpsReverseBlocks_U8(ptr, sz);

    return RESULT_SUCCESS;
}


bool
GenMemOpsReverseBytesRange(void *base, usize base_sz, usize begin_idx, usize count)
{
    usize final_sz;

    if (!base || begin_idx >= base_sz)
    {
        return RESULT_FAILURE;
    }

    if (!count)
    {
        return RESULT_SUCCESS;
    }

    final_sz = base_sz - begin_idx;
    final_sz = count < final_sz ? count : final_sz;

    kdi_GenMemOpsReverseBlocks_U8(PBYTE_C(base) + begin_idx, final_sz);

    return RESULT_SUCCESS;
}


bool
GenMemOpsReverseBlocks(void *ptr, usize ptr_sz, usize block_sz)
{
    if (!ptr || !block_sz)
    {
        return RESULT_FAILURE;
    }

    if (!ptr_sz)
    {
        return RESULT_SUCCESS;
    }

    ptr_sz /= block_sz;

    switch (block_sz)
    {
        case 1:
            kdi_GenMemOpsReverseBlocks_U8(ptr, ptr_sz * block_sz);
            break;
        case 2:
            kdi_GenMemOpsReverseBlocks_U16(ptr, ptr_sz * block_sz);
            break;
        case 4:
            kdi_GenMemOpsReverseBlocks_U32(ptr, ptr_sz * block_sz);
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsReverseBlocks_U64(ptr, ptr_sz * block_sz);
            break;
#endif
        default:
            kdi_GenMemOpsReverseBlocks_Un(ptr, ptr_sz * block_sz, block_sz);
    }

    return RESULT_SUCCESS;
}


bool
GenMemOpsReverseBlocksRange(void *base, usize base_sz, usize begin_idx, usize byte_count, usize block_sz)
{
    usize final_sz;

    if (!base || begin_idx >= base_sz || !block_sz)
    {
        return RESULT_FAILURE;
    }

    if (!byte_count)
    {
        return RESULT_SUCCESS;
    }

    final_sz  = base_sz - begin_idx;
    final_sz  = byte_count < final_sz ? byte_count : final_sz;
    final_sz /= block_sz;

    switch (block_sz)
    {
        case 1:
            kdi_GenMemOpsReverseBlocks_U8(PU8_C(PBYTE_C(base) + begin_idx), final_sz * block_sz);
            break;
        case 2:
            kdi_GenMemOpsReverseBlocks_U16(PU16_C(PBYTE_C(base) + begin_idx), final_sz * block_sz);
            break;
        case 4:
            kdi_GenMemOpsReverseBlocks_U32(PU32_C(PBYTE_C(base) + begin_idx), final_sz * block_sz);
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsReverseBlocks_U64(PU64_C(PBYTE_C(base) + begin_idx), final_sz * block_sz);
            break;
#endif
        default:
            kdi_GenMemOpsReverseBlocks_Un(PBYTE_C(base) + begin_idx, final_sz * block_sz, block_sz);
    }

    return RESULT_SUCCESS;
}


bool
GenMemOpsInnerSwapBytes(void *ptr, usize idx_1, usize idx_2)
{
    if (!ptr)
    {
        return RESULT_FAILURE;
    }

    kdi_GenMemOpsSwapBlocks_U8(ptr, idx_1, idx_2);

    return RESULT_SUCCESS;
}


bool
GenMemOpsInnerSwapBytesRange(void *base, usize base_sz, usize idx_1, usize idx_2)
{
    if (!base || !base_sz || idx_1 >= base_sz || idx_2 >= base_sz)
    {
        return RESULT_FAILURE;
    }

    kdi_GenMemOpsSwapBlocks_U8(base, idx_1, idx_2);

    return RESULT_SUCCESS;
}


KDAPI(bool) GenMemOpsInnerSwapBlocks(void *ptr, usize idx_1, usize idx_2, usize block_sz)
{
    if (!ptr || !block_sz)
    {
        return RESULT_FAILURE;
    }

    switch (block_sz)
    {
        case 1:
            kdi_GenMemOpsSwapBlocks_U8(ptr, idx_1, idx_2);
            break;
        case 2:
            kdi_GenMemOpsSwapBlocks_U16(ptr, idx_1, idx_2);
            break;
        case 4:
            kdi_GenMemOpsSwapBlocks_U32(ptr, idx_1, idx_2);
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsSwapBlocks_U64(ptr, idx_1, idx_2);
            break;
#endif
        default:
            kdi_GenMemOpsSwapBlocks_Un(ptr, idx_1, idx_2, block_sz);
    }

    return RESULT_SUCCESS;
}


bool
GenMemOpsInnerSwapBlocksRange(void *base, usize base_sz, usize idx_1, usize idx_2, usize block_sz)
{
    if (!base || idx_1 >= base_sz || idx_2 >= base_sz || !block_sz || block_sz > base_sz || (idx_1 + block_sz) > base_sz || (idx_2 + block_sz) > base_sz)
    {
        return RESULT_FAILURE;
    }

    switch (block_sz)
    {
        case 1:
            kdi_GenMemOpsSwapBlocks_U8(base, idx_1, idx_2);
            break;
        case 2:
            kdi_GenMemOpsSwapBlocks_U16(base, idx_1, idx_2);
            break;
        case 4:
            kdi_GenMemOpsSwapBlocks_U32(base, idx_1, idx_2);
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsSwapBlocks_U64(base, idx_1, idx_2);
            break;
#endif
        default:
            kdi_GenMemOpsSwapBlocks_Un(base, idx_1, idx_2, block_sz);
    }

    return RESULT_SUCCESS;
}


bool
GenMemOpsSwapBytes(void *ptr_1, void *ptr_2)
{
    if (!ptr_1 || !ptr_2)
    {
        return RESULT_FAILURE;
    }

    kdi_GenMemOpsSwapBlockRefs_U8(ptr_1, ptr_2);

    return RESULT_SUCCESS;
}


bool
GenMemOpsSwapBytesRange(void *base_1, usize base_1_sz, usize base_1_idx, void *base_2, usize base_2_sz, usize base_2_idx)
{
    if (!base_1 || base_1_idx >= base_1_sz || !base_2 || base_2_idx >= base_2_sz)
    {
        return RESULT_FAILURE;
    }

    kdi_GenMemOpsSwapBlockRefs_U8(PBYTE_C(base_1) + base_1_idx, PBYTE_C(base_2) + base_2_idx);

    return RESULT_SUCCESS;
}


bool
GenMemOpsSwapBlocks(void *ptr_1, void *ptr_2, usize block_sz)
{
    if (!ptr_1 || !ptr_2 || !block_sz)
    {
        return RESULT_FAILURE;
    }

    switch (block_sz)
    {
        case 1:
            kdi_GenMemOpsSwapBlockRefs_U8(ptr_1, ptr_2);
            break;
        case 2:
            kdi_GenMemOpsSwapBlockRefs_U16(ptr_1, ptr_2);
            break;
        case 4:
            kdi_GenMemOpsSwapBlockRefs_U32(ptr_1, ptr_2);
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsSwapBlockRefs_U64(ptr_1, ptr_2);
            break;
#endif
        default:
            kdi_GenMemOpsSwapBlockRefs_Un(ptr_1, ptr_2, block_sz);
    }

    return RESULT_SUCCESS;
}


bool
GenMemOpsSwapBlocksRange(void *base_1, usize base_1_sz, usize base_1_idx, void *base_2, usize base_2_sz, usize base_2_idx, usize block_sz)
{
    if (!base_1 || block_sz > base_1_sz || base_1_idx >= base_1_sz || !base_2 || block_sz > base_2_sz || base_2_idx >= base_2_sz || !block_sz || (base_1_idx + block_sz) > base_1_sz || (base_2_idx + block_sz) > base_2_sz)
    {
        return RESULT_FAILURE;
    }

    switch (block_sz)
    {
        case 1:
            kdi_GenMemOpsSwapBlockRefs_U8(PU8_C(PBYTE_C(base_1) + base_1_idx), PU8_C(PBYTE_C(base_2) + base_2_idx));
            break;
        case 2:
            kdi_GenMemOpsSwapBlockRefs_U16(PU16_C(PBYTE_C(base_1) + base_1_idx), PU16_C(PBYTE_C(base_2) + base_2_idx));
            break;
        case 4:
            kdi_GenMemOpsSwapBlockRefs_U32(PU32_C(PBYTE_C(base_1) + base_1_idx), PU32_C(PBYTE_C(base_2) + base_2_idx));
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsSwapBlockRefs_U64(PU64_C(PBYTE_C(base_1) + base_1_idx), PU64_C(PBYTE_C(base_2) + base_2_idx));
            break;
#endif
        default:
            kdi_GenMemOpsSwapBlockRefs_Un(PBYTE_C(base_1) + base_1_idx, PBYTE_C(base_2) + base_2_idx, block_sz);
    }

    return RESULT_SUCCESS;
}


bool
GenMemOpsRotateRight(void *ptr, usize sz, usize k)
{
    if (!ptr)
    {
        return RESULT_FAILURE;
    }

    if (!sz)
    {
        return RESULT_SUCCESS;
    }

    k %= sz;

    if (!k)
    {
        return RESULT_SUCCESS;
    }

    kdi_GenMemOpsRotateRight(ptr, sz, k);

    return RESULT_SUCCESS;
}


bool
GenMemOpsRotateRightRange(void *base, usize base_sz, usize begin_idx, usize byte_count, usize k)
{
    usize final_sz;

    if (!base || begin_idx >= base_sz)
    {
        return RESULT_FAILURE;
    }

    if (!base_sz || !byte_count)
    {
        return RESULT_SUCCESS;
    }

    final_sz  = base_sz - begin_idx;
    final_sz  = final_sz > byte_count ? byte_count : final_sz;

    k        %= final_sz;

    if (!k)
    {
        return RESULT_SUCCESS;
    }

    kdi_GenMemOpsRotateRight(PBYTE_C(base) + begin_idx, final_sz, k);

    return RESULT_SUCCESS;
}


bool
GenMemOpsRotateLeft(void *ptr, usize sz, usize k)
{
    if (!ptr)
    {
        return RESULT_FAILURE;
    }

    if (!sz)
    {
        return RESULT_SUCCESS;
    }

    k %= sz;

    if (!k)
    {
        return RESULT_SUCCESS;
    }

    kdi_GenMemOpsRotateLeft(ptr, sz, k);

    return RESULT_SUCCESS;
}


bool
GenMemOpsRotateLeftRange(void *base, usize base_sz, usize begin_idx, usize byte_count, usize k)
{
    usize final_sz;

    if (!base || begin_idx >= base_sz)
    {
        return RESULT_FAILURE;
    }

    if (!base_sz || !byte_count)
    {
        return RESULT_SUCCESS;
    }

    final_sz  = base_sz - begin_idx;
    final_sz  = final_sz > byte_count ? byte_count : final_sz;

    k        %= final_sz;

    if (!k)
    {
        return RESULT_SUCCESS;
    }

    kdi_GenMemOpsRotateLeft(PBYTE_C(base) + begin_idx, final_sz, k);

    return RESULT_SUCCESS;
}


bool
GenMemOpsIsEqual(bool *result, void *ptr_1, void *ptr_2, usize sz)
{
    if (!result || !ptr_1 || !ptr_2)
    {
        return RESULT_FAILURE;
    }

    if (!sz)
    {
        *result = true;
        return RESULT_SUCCESS;
    }

    kdi_GenMemOpsIsEqual(result, ptr_1, ptr_2, sz);

    return RESULT_SUCCESS;
}


bool
GenMemOpsIsEqualRegion(bool *result, void *ptr_1, usize ptr_1_sz, void *ptr_2, usize ptr_2_sz)
{
    if (!result || !ptr_1 || !ptr_2)
    {
        return RESULT_FAILURE;
    }

    if (ptr_1_sz != ptr_2_sz)
    {
        *result = false;
        return RESULT_SUCCESS;
    }
    else if (!ptr_1_sz)
    {
        *result = true;
        return RESULT_SUCCESS;
    }

    kdi_GenMemOpsIsEqual(result, ptr_1, ptr_2, ptr_1_sz);

    return RESULT_SUCCESS;
}


bool
kdGenMemOpsIsEqualRange(bool *result, void *base_1, usize base_1_sz, usize base_1_idx, void *base_2, usize base_2_sz, usize base_2_idx, usize byte_count)
{
    usize base_1_final_sz, base_2_final_sz;

    if (!result || !base_1 || base_1_idx >= base_1_sz || !base_2 || base_2_idx >= base_2_sz)
    {
        return RESULT_FAILURE;
    }

    if (!byte_count)
    {
        *result = true;
        return RESULT_SUCCESS;
    }

    base_1_final_sz = base_1_sz - base_1_idx;
    base_1_final_sz = base_1_final_sz > byte_count ? byte_count : base_1_final_sz;

    base_2_final_sz = base_2_sz - base_2_idx;
    base_2_final_sz = base_2_final_sz > byte_count ? byte_count : base_2_final_sz;

    if (base_1_final_sz != base_2_final_sz)
    {
        *result = false;
        return RESULT_SUCCESS;
    }
    else if (!base_1_final_sz)
    {
        *result = true;
        return RESULT_SUCCESS;
    }

    kdi_GenMemOpsIsEqual(result, PBYTE_C(base_1) + base_1_idx, PBYTE_C(base_2) + base_2_idx, base_1_final_sz);

    return RESULT_SUCCESS;
}


bool
GenMemOpsIsZeros(bool *result, void *ptr, usize sz)
{
    if (!result || !ptr)
    {
        return RESULT_FAILURE;
    }

    if (!sz)
    {
        *result = true;
        return RESULT_SUCCESS;
    }

    kdi_GenMemOpsIsVal(result, ptr, sz, 0);

    return RESULT_SUCCESS;
}


bool
GenMemOpsIsZerosRange(bool *result, void *base, usize base_sz, usize begin_idx, usize byte_count)
{
    usize final_sz;

    if (!result || !base || begin_idx >= base_sz)
    {
        return RESULT_FAILURE;
    }

    if (!byte_count)
    {
        *result = true;
        return RESULT_SUCCESS;
    }

    final_sz = base_sz - begin_idx;
    final_sz = final_sz > byte_count ? byte_count : final_sz;

    kdi_GenMemOpsIsVal(result, PBYTE_C(base) + begin_idx, final_sz, 0);

    return RESULT_SUCCESS;
}


bool
GenMemOpsIsOnes(bool *result, void *ptr, usize sz)
{
    if (!result || !ptr)
    {
        return RESULT_FAILURE;
    }

    if (!sz)
    {
        *result = true;
        return RESULT_SUCCESS;
    }

    kdi_GenMemOpsIsVal(result, ptr, sz, 0xFF);

    return RESULT_SUCCESS;
}


bool
GenMemOpsIsOnesRange(bool *result, void *base, usize base_sz, usize begin_idx, usize byte_count)
{
    usize final_sz;

    if (!result || !base || begin_idx >= base_sz)
    {
        return RESULT_FAILURE;
    }

    if (!byte_count)
    {
        *result = true;
        return RESULT_SUCCESS;
    }

    final_sz = base_sz - begin_idx;
    final_sz = final_sz > byte_count ? byte_count : final_sz;

    kdi_GenMemOpsIsVal(result, PBYTE_C(base) + begin_idx, final_sz, 0xFF);

    return RESULT_SUCCESS;
}


bool
GenMemOpsHasPrefix(bool *result, void *ptr, usize ptr_sz, void *prefix, usize prefix_sz)
{
    if (!result || !ptr || !prefix)
    {
        return RESULT_FAILURE;
    }

    if (prefix_sz > ptr_sz)
    {
        *result = false;
        return RESULT_SUCCESS;
    }

    if (!ptr_sz || !prefix_sz)
    {
        *result = true;
        return RESULT_SUCCESS;
    }

    kdi_GenMemOpsIsEqual(result, ptr, prefix, prefix_sz);

    return RESULT_SUCCESS;
}


bool
GenMemOpsHasSuffix(bool *result, void *ptr, usize ptr_sz, void *suffix, usize suffix_sz)
{
    if (!result || !ptr || !suffix)
    {
        return RESULT_FAILURE;
    }

    if (suffix_sz > ptr_sz)
    {
        *result = false;
        return RESULT_SUCCESS;
    }

    if (!ptr_sz || !suffix_sz)
    {
        *result = true;
        return RESULT_SUCCESS;
    }

    kdi_GenMemOpsIsEqual(result, PBYTE_C(ptr) + ptr_sz - suffix_sz, suffix, suffix_sz);

    return RESULT_SUCCESS;
}


bool
GenMemOpsRegionOverlap(bool *result, void *ptr_1, usize ptr_1_sz, void *ptr_2, usize ptr_2_sz)
{
    if (!result || !ptr_1 || !ptr_2)
    {
        return RESULT_FAILURE;
    }

    if (!ptr_1_sz || !ptr_2_sz)
    {
        *result = false;
        return RESULT_SUCCESS;
    }

    kdi_GenMemOpsRegionOverlap(result, ptr_1, ptr_1_sz, ptr_2, ptr_2_sz);

    return RESULT_SUCCESS;
}


bool
GenMemOpsRegionContains(bool *result, void *base, usize base_sz, void *ptr, usize ptr_sz)
{
    if (!result || !base || !ptr)
    {
        return RESULT_FAILURE;
    }

    if (!ptr_sz)
    {
        *result = true;
        return RESULT_SUCCESS;
    }

    if (!base_sz)
    {
        *result = false;
        return RESULT_SUCCESS;
    }

    kdi_GenMemOpsRegionContains(result, base, base_sz, ptr, ptr_sz);

    return RESULT_SUCCESS;
}


bool
GenMemOpsCheckBounds(usize total_sz, usize offset, usize sz)
{
    return offset <= total_sz && (offset + sz) <= total_sz;
}


bool
GenMemOpsGetOffsetChecked(void *dst_addr, void *base, usize base_sz, usize offset, usize sz)
{
    byte **temp_dst_addr = dst_addr;

    if (!temp_dst_addr || !base)
    {
        return RESULT_FAILURE;
    }

    if (GenMemOpsCheckBounds(base_sz, offset, sz))
    {
        *temp_dst_addr = PBYTE_C(base) + offset;
        return RESULT_SUCCESS;
    }

    *temp_dst_addr = null;

    return RESULT_FAILURE;
}


bool
GenMemOpsElemCountFromBytes(usize *count, usize base_sz, usize elem_sz)
{
    if (!count || !elem_sz)
    {
        return RESULT_FAILURE;
    }

    kdi_GenMemOpsElemCountFromBytes(count, base_sz, elem_sz);

    return RESULT_SUCCESS;
}


bool
GenMemOpsByteAt(void *dst, void *base, usize base_sz, usize idx)
{
    if (!dst || !base || idx >= base_sz)
    {
        return RESULT_FAILURE;
    }

    kdi_GenMemOpsBlockAt_U8(dst, base, idx);

    return RESULT_SUCCESS;
}


bool
GenMemOpsBlockAt(void *dst, void *base, usize base_sz, usize idx, usize block_sz)
{
    if (!dst || !base || idx >= base_sz || !block_sz || block_sz > base_sz || (idx + block_sz) > base_sz)
    {
        return RESULT_FAILURE;
    }

    switch (block_sz)
    {
        case 1:
            kdi_GenMemOpsBlockAt_U8(dst, base, idx);
            break;
        case 2:
            kdi_GenMemOpsBlockAt_U16(dst, base, idx);
            break;
        case 4:
            kdi_GenMemOpsBlockAt_U32(dst, base, idx);
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsBlockAt_U64(dst, base, idx);
            break;
#endif
        default:
            kdi_GenMemOpsBlockAt_Un(dst, base, idx, block_sz);
    }

    return RESULT_SUCCESS;
}


bool
GenMemOpsSetByteAt(void *base, usize base_sz, usize idx, byte val)
{
    if (!base || idx >= base_sz)
    {
        return RESULT_FAILURE;
    }

    kdi_GenMemOpsSetBlockAt_U8(base, idx, val);

    return RESULT_SUCCESS;
}


bool
GenMemOpsSetBlockAt(void *base, usize base_sz, usize idx, void *block, usize block_sz)
{
    u8  block_val_u8;
    u16 block_val_u16;
    u32 block_val_u32;
#if defined ARCH_64BIT_INT
    u64 block_val_u64;
#endif

    if (!base || idx >= base_sz || !block || !block_sz || block_sz > base_sz || (idx + block_sz) > base_sz)
    {
        return RESULT_FAILURE;
    }

    switch (block_sz)
    {
        case 1:
            block_val_u8 = *PU8_C(block);
            kdi_GenMemOpsSetBlockAt_U8(base, idx, block_val_u8);
            break;
        case 2:
            block_val_u16 = *PU16_C(block);
            kdi_GenMemOpsSetBlockAt_U16(base, idx, block_val_u16);
            break;
        case 4:
            block_val_u32 = *PU32_C(block);
            kdi_GenMemOpsSetBlockAt_U32(base, idx, block_val_u32);
            break;
#if defined ARCH_64BIT_INT
        case 8:
            block_val_u64 = *PU64_C(block);
            kdi_GenMemOpsSetBlockAt_U64(base, idx, block_val_u64);
            break;
#endif
        default:
            kdi_GenMemOpsSetBlockAt_Un(base, idx, block, block_sz);
    }

    return RESULT_SUCCESS;
}


bool
GenMemOpsInsertByteAt(void *base, usize base_cap, usize *base_elems, usize idx, byte val, bool truncate)
{
    bool buffer_full;

    if (!base || !base_elems || idx >= base_cap || idx > *base_elems)
    {
        return RESULT_FAILURE;
    }

    buffer_full = *base_elems >= base_cap;

    if (!truncate && buffer_full)
    {
        return RESULT_FAILURE;
    }

    *base_elems = *base_elems - (buffer_full ? 1 : 0);

    kdi_GenMemOpsInsertBlockAt_U8(base, base_elems, idx, val);

    return RESULT_SUCCESS;
}


bool
GenMemOpsInsertBlockAt(void *base, usize base_cap, usize *base_elems, usize idx, void *block, usize block_sz, bool truncate)
{
    bool buffer_full;
    u8   block_val_u8;
    u16  block_val_u16;
    u32  block_val_u32;
#if defined ARCH_64BIT_INT
    u64 block_val_u64;
#endif

    if (!base || !base_elems || idx >= base_cap || idx > *base_elems || !block || !block_sz || block_sz > base_cap || (idx + block_sz) > base_cap)
    {
        return RESULT_FAILURE;
    }

    buffer_full = *base_elems >= base_cap;

    if (!truncate && buffer_full)
    {
        return RESULT_FAILURE;
    }

    *base_elems = *base_elems - (buffer_full ? block_sz : 0);

    switch (block_sz)
    {
        case 1:
            block_val_u8 = *PU8_C(block);
            kdi_GenMemOpsInsertBlockAt_U8(base, base_elems, idx, block_val_u8);
            break;
        case 2:
            block_val_u16 = *PU16_C(block);
            kdi_GenMemOpsInsertBlockAt_U16(base, base_elems, idx, block_val_u16);
            break;
        case 4:
            block_val_u32 = *PU32_C(block);
            kdi_GenMemOpsInsertBlockAt_U32(base, base_elems, idx, block_val_u32);
            break;
#if defined ARCH_64BIT_INT
        case 8:
            block_val_u64 = *PU64_C(block);
            kdi_GenMemOpsInsertBlockAt_U64(base, base_elems, idx, block_val_u64);
            break;
#endif
        default:
            kdi_GenMemOpsInsertBlockAt_Un(base, base_elems, idx, block, block_sz);
    }

    return RESULT_SUCCESS;
}


bool
GenMemOpsRemoveByteAt(void *base, usize base_cap, usize *base_elems, usize idx)
{
    if (!base || !base_elems || idx >= base_cap || idx >= *base_elems)
    {
        return RESULT_FAILURE;
    }

    kdi_GenMemOpsRemoveBlockAt_U8(base, base_elems, idx);

    return RESULT_SUCCESS;
}


bool
GenMemOpsRemoveBlockAt(void *base, usize base_cap, usize *base_elems, usize idx, usize block_sz)
{
    if (!base || !base_elems || idx >= base_cap || idx >= *base_elems || !block_sz || block_sz > base_cap || (idx + block_sz) > base_cap || (idx + block_sz) > *base_elems)
    {
        return RESULT_FAILURE;
    }

    switch (block_sz)
    {
        case 1:
            kdi_GenMemOpsRemoveBlockAt_U8(base, base_elems, idx);
            break;
        case 2:
            kdi_GenMemOpsRemoveBlockAt_U16(base, base_elems, idx);
            break;
        case 4:
            kdi_GenMemOpsRemoveBlockAt_U32(base, base_elems, idx);
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsRemoveBlockAt_U64(base, base_elems, idx);
            break;
#endif
        default:
            kdi_GenMemOpsRemoveBlockAt_Un(base, base_elems, idx, block_sz);
    }

    return RESULT_SUCCESS;
}


bool
GenMemOpsCountBytes(usize *count, void *ptr, usize sz, byte item)
{
    if (!count || !ptr)
    {
        return RESULT_FAILURE;
    }

    *count = 0;

    if (!sz)
    {
        return RESULT_SUCCESS;
    }

    kdi_GenMemOpsCountBlocks_U8(count, ptr, sz, item);

    return RESULT_SUCCESS;
}


bool
GenMemOpsCountBlocks(usize *count, void *ptr, usize ptr_sz, void *block, usize block_sz)
{
    u8  block_val_u8;
    u16 block_val_u16;
    u32 block_val_u32;
#if defined ARCH_64BIT_INT
    u64 block_val_u64;
#endif

    if (!count || !ptr || !block || !block_sz)
    {
        return RESULT_FAILURE;
    }

    *count = 0;

    if (!ptr_sz || block_sz > ptr_sz)
    {
        return RESULT_SUCCESS;
    }

    switch (block_sz)
    {
        case 1:
            block_val_u8 = *PU8_C(block);
            kdi_GenMemOpsCountBlocks_U8(count, ptr, ptr_sz, block_val_u8);
            break;
        case 2:
            block_val_u16 = *PU16_C(block);
            kdi_GenMemOpsCountBlocks_U16(count, ptr, ptr_sz, block_val_u16);
            break;
        case 4:
            block_val_u32 = *PU32_C(block);
            kdi_GenMemOpsCountBlocks_U32(count, ptr, ptr_sz, block_val_u32);
            break;
#if defined ARCH_64BIT_INT
        case 8:
            block_val_u64 = *PU64_C(block);
            kdi_GenMemOpsCountBlocks_U64(count, ptr, ptr_sz, block_val_u64);
            break;
#endif
        default:
            kdi_GenMemOpsCountBlocks_Un(count, ptr, ptr_sz, block, block_sz);
    }

    return RESULT_SUCCESS;
}


bool
GenMemOpsCountNotBytes(usize *count, void *ptr, usize sz, byte item)
{
    if (!count || !ptr)
    {
        return RESULT_FAILURE;
    }

    *count = 0;

    if (!sz)
    {
        return RESULT_SUCCESS;
    }

    kdi_GenMemOpsCountNotBlocks_U8(count, ptr, sz, item);

    return RESULT_SUCCESS;
}


bool
GenMemOpsCountNotBlocks(usize *count, void *ptr, usize ptr_sz, void *block, usize block_sz)
{
    u8  block_val_u8;
    u16 block_val_u16;
    u32 block_val_u32;
#if defined ARCH_64BIT_INT
    u64 block_val_u64;
#endif

    if (!count || !ptr || !block || !block_sz)
    {
        return RESULT_FAILURE;
    }

    *count = 0;

    if (!ptr_sz || block_sz > ptr_sz)
    {
        return RESULT_SUCCESS;
    }

    switch (block_sz)
    {
        case 1:
            block_val_u8 = *PU8_C(block);
            kdi_GenMemOpsCountNotBlocks_U8(count, ptr, ptr_sz, block_val_u8);
            break;
        case 2:
            block_val_u16 = *PU16_C(block);
            kdi_GenMemOpsCountNotBlocks_U16(count, ptr, ptr_sz, block_val_u16);
            break;
        case 4:
            block_val_u32 = *PU32_C(block);
            kdi_GenMemOpsCountNotBlocks_U32(count, ptr, ptr_sz, block_val_u32);
            break;
#if defined ARCH_64BIT_INT
        case 8:
            block_val_u64 = *PU64_C(block);
            kdi_GenMemOpsCountNotBlocks_U64(count, ptr, ptr_sz, block_val_u64);
            break;
#endif
        default:
            kdi_GenMemOpsCountNotBlocks_Un(count, ptr, ptr_sz, block, block_sz);
    }

    return RESULT_SUCCESS;
}


/*
bool
kdGenMemOpsReverseBytes(void *ptr, usize sz)
{
    if (!ptr || !sz)
    {
        return RESULT_FAILURE;
    }

    kdi_GenMemOpsReverseBlocks_U8(ptr, sz);

    return RESULT_SUCCESS;
}


bool
kdGenMemOpsReverseBlocks(void *ptr, usize sz, usize block_sz)
{
    if (!ptr || !sz || !block_sz)
    {
        return RESULT_FAILURE;
    }

    switch (block_sz)
    {
        case 1:
            kdi_GenMemOpsReverseBlocks_U8(ptr, sz);
            break;
        case 2:
            kdi_GenMemOpsReverseBlocks_U16(ptr, sz);
            break;
        case 4:
            kdi_GenMemOpsReverseBlocks_U32(ptr, sz);
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsReverseBlocks_U64(ptr, sz);
            break;
#endif
        default:
            kdi_GenMemOpsReverseBlocks_Un(ptr, sz, block_sz);
    }

    return RESULT_SUCCESS;
}


bool
kdGenMemOpsSetBytes(void *ptr, usize sz, byte val)
{
    if (!ptr || !sz)
    {
        return RESULT_FAILURE;
    }

    kdi_GenMemOpsSetBlocks_U8(ptr, sz, val);

    return RESULT_SUCCESS;
}


bool
kdGenMemOpsSetBlocks(void *ptr, usize sz, void *block, usize block_sz)
{
    u8  block_val_u8;
    u16 block_val_u16;
    u32 block_val_u32;
#if defined ARCH_64BIT_INT
    u64 block_val_u64;
#endif

    if (!ptr || !sz || !block || !block_sz)
    {
        return RESULT_FAILURE;
    }

    switch (block_sz)
    {
        case 1:
            block_val_u8 = *PU8_C(block);
            kdi_GenMemOpsSetBlocks_U8(ptr, sz, block_val_u8);
            break;
        case 2:
            block_val_u16 = *PU16_C(block);
            kdi_GenMemOpsSetBlocks_U16(ptr, sz, block_val_u16);
            break;
        case 4:
            block_val_u32 = *PU32_C(block);
            kdi_GenMemOpsSetBlocks_U32(ptr, sz, block_val_u32);
            break;
#if defined ARCH_64BIT_INT
        case 8:
            block_val_u64 = *PU64_C(block);
            kdi_GenMemOpsSetBlocks_U64(ptr, sz, block_val_u64);
            break;
#endif
        default:
            kdi_GenMemOpsSetBlocks_Un(ptr, sz, block, block_sz);
    }

    return RESULT_SUCCESS;
}


bool
kdGenMemOpsCpy(void *dst, void *src, usize sz)
{
    if (!dst || !src || !sz)
    {
        return RESULT_FAILURE;
    }

    kdi_GenMemOpsCpy(dst, src, sz);

    return RESULT_SUCCESS;
}


bool
kdGenMemOpsMove(void *dst, void *src, usize sz)
{
    if (!dst || !src || !sz)
    {
        return RESULT_FAILURE;
    }

    kdi_GenMemOpsMove(dst, src, sz);

    return RESULT_SUCCESS;
}


void *
kdGenMemOpsFindByte(void *ptr, usize sz, byte item)
{
    if (!ptr || !sz)
    {
        return null;
    }

    return kdi_GenMemOpsFindBlockWithIndex_U8(null, ptr, sz, item);
}


bool
kdGenMemOpsFindByteIndex(usize *idx_ptr, void *ptr, usize sz, byte item)
{
    void *found_ptr;

    if (!idx_ptr || !ptr || !sz)
    {
        return RESULT_FAILURE;
    }

    found_ptr = kdi_GenMemOpsFindBlockWithIndex_U8(idx_ptr, ptr, sz, item);

    return found_ptr ? RESULT_SUCCESS : RESULT_FAILURE;
}


void *
kdGenMemOpsFindLastByte(void *ptr, usize sz, byte item)
{
    if (!ptr || !sz)
    {
        return null;
    }

    return kdi_GenMemOpsFindLastBlockWithIndex_U8(null, ptr, sz, item);
}


bool
kdGenMemOpsFindLastByteIndex(usize *idx_ptr, void *ptr, usize sz, byte item)
{
    void *found_ptr;

    if (!idx_ptr || !ptr || !sz)
    {
        return RESULT_FAILURE;
    }

    found_ptr = kdi_GenMemOpsFindLastBlockWithIndex_U8(idx_ptr, ptr, sz, item);

    return found_ptr ? RESULT_SUCCESS : RESULT_FAILURE;
}


usize
kdGenMemOpsFindAllBytes(void *dst, usize dst_sz, void *ptr, usize ptr_sz, byte item)
{
    return (!dst || !ptr || !dst_sz || !ptr_sz) ? 0 : kdi_GenMemOpsFindAllBlocks_Byte(dst, dst_sz, ptr, ptr_sz, item);
}


usize
kdGenMemOpsFindAllByteIndices(usize *idxs, usize idxs_sz, void *ptr, usize ptr_sz, byte item)
{
    return (!idxs || !ptr || !idxs_sz || !ptr_sz) ? 0 :
#if defined ARCH_64BIT_INT
                                                  kdi_GenMemOpsFindAllBlockIndices_Byte_Idx64(idxs, idxs_sz, ptr, ptr_sz, item, true);
#else
                                                  kdi_GenMemOpsFindAllBlockIndices_Byte_Idx32(idxs, idxs_sz, ptr, ptr_sz, item, true);
#endif
}


usize
kdGenMemOpsFindAllByteIndicesU8(u8 *idxs, usize idxs_sz, void *ptr, usize ptr_sz, byte item)
{
    return (!idxs || !ptr || !idxs_sz || !ptr_sz) ? 0 : kdi_GenMemOpsFindAllBlockIndices_Byte_Idx8(idxs, idxs_sz, ptr, ptr_sz, item, true);
}


usize
kdGenMemOpsFindAllByteIndicesU16(u16 *idxs, usize idxs_sz, void *ptr, usize ptr_sz, byte item)
{
    return (!idxs || !ptr || !idxs_sz || !ptr_sz) ? 0 : kdi_GenMemOpsFindAllBlockIndices_Byte_Idx16(idxs, idxs_sz, ptr, ptr_sz, item, true);
}


usize
kdGenMemOpsFindAllByteIndicesU32(u32 *idxs, usize idxs_sz, void *ptr, usize ptr_sz, byte item)
{
    return (!idxs || !ptr || !idxs_sz || !ptr_sz) ? 0 : kdi_GenMemOpsFindAllBlockIndices_Byte_Idx32(idxs, idxs_sz, ptr, ptr_sz, item, true);
}


#if defined ARCH_64BIT_INT
usize
kdGenMemOpsFindAllByteIndicesU64(u64 *idxs, usize idxs_sz, void *ptr, usize ptr_sz, byte item)
{
    return (!idxs || !ptr || !idxs_sz || !ptr_sz) ? 0 : kdi_GenMemOpsFindAllBlockIndices_Byte_Idx64(idxs, idxs_sz, ptr, ptr_sz, item, true);
}
#endif


void *
kdGenMemOpsFindBlock(void *ptr, usize sz, void *block, usize block_sz)
{
    u8  block_val_u8;
    u16 block_val_u16;
    u32 block_val_u32;
#if defined ARCH_64BIT_INT
    u64 block_val_u64;
#endif

    if (!ptr || !sz || !block || !block_sz)
    {
        return null;
    }

    switch (block_sz)
    {
        case 1:
            block_val_u8 = *PU8_C(block);
            return kdi_GenMemOpsFindBlockWithIndex_U8(null, ptr, sz, block_val_u8);
        case 2:
            block_val_u16 = *PU16_C(block);
            return kdi_GenMemOpsFindBlockWithIndex_U16(null, ptr, sz, block_val_u16);
        case 4:
            block_val_u32 = *PU32_C(block);
            return kdi_GenMemOpsFindBlockWithIndex_U32(null, ptr, sz, block_val_u32);
#if defined ARCH_64BIT_INT
        case 8:
            block_val_u64 = *PU64_C(block);
            return kdi_GenMemOpsFindBlockWithIndex_U64(null, ptr, sz, block_val_u64);
#endif
        default:;
    }

    return kdi_GenMemOpsFindBlockWithIndex_Un(null, ptr, sz, block, block_sz);
}


bool
kdGenMemOpsFindBlockIndex(usize *idx_ptr, void *ptr, usize sz, void *block, usize block_sz)
{
    void *found_ptr;
    u8    block_val_u8;
    u16   block_val_u16;
    u32   block_val_u32;
#if defined ARCH_64BIT_INT
    u64 block_val_u64;
#endif

    if (!idx_ptr || !ptr || !sz || !block || !block_sz)
    {
        return RESULT_FAILURE;
    }

    switch (block_sz)
    {
        case 1:
            block_val_u8 = *PU8_C(block);
            found_ptr    = kdi_GenMemOpsFindBlockWithIndex_U8(idx_ptr, ptr, sz, block_val_u8);
            break;
        case 2:
            block_val_u16 = *PU16_C(block);
            found_ptr     = kdi_GenMemOpsFindBlockWithIndex_U16(idx_ptr, ptr, sz, block_val_u16);
            break;
        case 4:
            block_val_u32 = *PU32_C(block);
            found_ptr     = kdi_GenMemOpsFindBlockWithIndex_U32(idx_ptr, ptr, sz, block_val_u32);
            break;
#if defined ARCH_64BIT_INT
        case 8:
            block_val_u64 = *PU64_C(block);
            found_ptr     = kdi_GenMemOpsFindBlockWithIndex_U64(idx_ptr, ptr, sz, block_val_u64);
            break;
#endif
        default:
            found_ptr = kdi_GenMemOpsFindBlockWithIndex_Un(idx_ptr, ptr, sz, block, block_sz);
    }

    return found_ptr ? RESULT_SUCCESS : RESULT_FAILURE;
}


void *
kdGenMemOpsFindLastBlock(void *ptr, usize sz, void *block, usize block_sz)
{
    u8  block_val_u8;
    u16 block_val_u16;
    u32 block_val_u32;
#if defined ARCH_64BIT_INT
    u64 block_val_u64;
#endif

    if (!ptr || !sz || !block || !block_sz)
    {
        return null;
    }

    switch (block_sz)
    {
        case 1:
            block_val_u8 = *PU8_C(block);
            return kdi_GenMemOpsFindLastBlockWithIndex_U8(null, ptr, sz, block_val_u8);
        case 2:
            block_val_u16 = *PU16_C(block);
            return kdi_GenMemOpsFindLastBlockWithIndex_U16(null, ptr, sz, block_val_u16);
        case 4:
            block_val_u32 = *PU32_C(block);
            return kdi_GenMemOpsFindLastBlockWithIndex_U32(null, ptr, sz, block_val_u32);
#if defined ARCH_64BIT_INT
        case 8:
            block_val_u64 = *PU64_C(block);
            return kdi_GenMemOpsFindLastBlockWithIndex_U64(null, ptr, sz, block_val_u64);
#endif
        default:;
    }

    return kdi_GenMemOpsFindLastBlockWithIndex_Un(null, ptr, sz, block, block_sz);
}


bool
kdGenMemOpsFindLastBlockIndex(usize *idx_ptr, void *ptr, usize sz, void *block, usize block_sz)
{
    void *found_ptr;
    u8    block_val_u8;
    u16   block_val_u16;
    u32   block_val_u32;
#if defined ARCH_64BIT_INT
    u64 block_val_u64;
#endif

    if (!idx_ptr || !ptr || !sz || !block || !block_sz)
    {
        return RESULT_FAILURE;
    }

    switch (block_sz)
    {
        case 1:
            block_val_u8 = *PU8_C(block);
            found_ptr    = kdi_GenMemOpsFindLastBlockWithIndex_U8(idx_ptr, ptr, sz, block_val_u8);
            break;
        case 2:
            block_val_u16 = *PU16_C(block);
            found_ptr     = kdi_GenMemOpsFindLastBlockWithIndex_U16(idx_ptr, ptr, sz, block_val_u16);
            break;
        case 4:
            block_val_u32 = *PU32_C(block);
            found_ptr     = kdi_GenMemOpsFindLastBlockWithIndex_U32(idx_ptr, ptr, sz, block_val_u32);
            break;
#if defined ARCH_64BIT_INT
        case 8:
            block_val_u64 = *PU64_C(block);
            found_ptr     = kdi_GenMemOpsFindLastBlockWithIndex_U64(idx_ptr, ptr, sz, block_val_u64);
            break;
#endif
        default:
            found_ptr = kdi_GenMemOpsFindLastBlockWithIndex_Un(idx_ptr, ptr, sz, block, block_sz);
    }

    return found_ptr ? RESULT_SUCCESS : RESULT_FAILURE;
}


usize
kdGenMemOpsFindAllBlocks(void *dst, usize dst_sz, void *ptr, usize ptr_sz, void *block, usize block_sz)
{
    u8  block_val_u8;
    u16 block_val_u16;
    u32 block_val_u32;
#if defined ARCH_64BIT_INT
    u64 block_val_u64;
#endif

    if (!dst || !ptr || !block || !dst_sz || !ptr_sz || !block_sz)
    {
        return 0;
    }

    switch (block_sz)
    {
        case 1:
            block_val_u8 = *PU8_C(block);
            return kdi_GenMemOpsFindAllBlocks_U8(dst, dst_sz, ptr, ptr_sz, block_val_u8);
        case 2:
            block_val_u16 = *PU16_C(block);
            return kdi_GenMemOpsFindAllBlocks_U16(dst, dst_sz, ptr, ptr_sz, block_val_u16);
        case 4:
            block_val_u32 = *PU32_C(block);
            return kdi_GenMemOpsFindAllBlocks_U32(dst, dst_sz, ptr, ptr_sz, block_val_u32);
#if defined ARCH_64BIT_INT
        case 8:
            block_val_u64 = *PU64_C(block);
            return kdi_GenMemOpsFindAllBlocks_U64(dst, dst_sz, ptr, ptr_sz, block_val_u64);
#endif
        default:;
    }

    return kdi_GenMemOpsFindAllBlocks_Un(dst, dst_sz, ptr, ptr_sz, block, block_sz);
}


usize
kdGenMemOpsFindAllBlockIndices(usize *idxs, usize idxs_sz, void *ptr, usize ptr_sz, void *block, usize block_sz)
{
    u8  block_val_u8;
    u16 block_val_u16;
    u32 block_val_u32;
#if defined ARCH_64BIT_INT
    u64 block_val_u64;
#endif

    if (!idxs || !idxs_sz || !ptr || !ptr_sz || !block || !block_sz)
    {
        return 0;
    }

#if defined ARCH_64BIT_INT
    switch (block_sz)
    {
        case 1:
            block_val_u8 = *PU8_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U8_Idx64(idxs, idxs_sz, ptr, ptr_sz, block_val_u8, false);
        case 2:
            block_val_u16 = *PU16_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U16_Idx64(idxs, idxs_sz, ptr, ptr_sz, block_val_u16, false);
        case 4:
            block_val_u32 = *PU32_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U32_Idx64(idxs, idxs_sz, ptr, ptr_sz, block_val_u32, false);
        case 8:
            block_val_u64 = *PU64_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U64_Idx64(idxs, idxs_sz, ptr, ptr_sz, block_val_u64, false);
        default:;
    }

    return kdi_GenMemOpsFindAllBlockIndices_Un_Idx64(idxs, idxs_sz, ptr, ptr_sz, block, block_sz, false);
#else
    switch (block_sz)
    {
        case 1:
            block_val_u8 = *PU8_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U8_Idx32(idxs, idxs_sz, ptr, ptr_sz, block_val_u8, false);
        case 2:
            block_val_u16 = *PU16_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U16_Idx32(idxs, idxs_sz, ptr, ptr_sz, block_val_u16, false);
        case 4:
            block_val_u32 = *PU32_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U32_Idx32(idxs, idxs_sz, ptr, ptr_sz, block_val_u32, false);
        default:;
    }

    return kdi_GenMemOpsFindAllBlockIndices_Un_Idx32(idxs, idxs_sz, ptr, ptr_sz, block, block_sz, false);
#endif
}


usize
kdGenMemOpsFindAllBlockIndicesU8(u8 *idxs, usize idxs_sz, void *ptr, usize ptr_sz, void *block, usize block_sz)
{
    u8  block_val_u8;
    u16 block_val_u16;
    u32 block_val_u32;
#if defined ARCH_64BIT_INT
    u64 block_val_u64;
#endif

    if (!idxs || !idxs_sz || !ptr || !ptr_sz || !block || !block_sz)
    {
        return 0;
    }

    switch (block_sz)
    {
        case 1:
            block_val_u8 = *PU8_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U8_Idx8(idxs, idxs_sz, ptr, ptr_sz, block_val_u8, false);
        case 2:
            block_val_u16 = *PU16_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U16_Idx8(idxs, idxs_sz, ptr, ptr_sz, block_val_u16, false);
        case 4:
            block_val_u32 = *PU32_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U32_Idx8(idxs, idxs_sz, ptr, ptr_sz, block_val_u32, false);
#if defined ARCH_64BIT_INT
        case 8:
            block_val_u64 = *PU64_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U64_Idx8(idxs, idxs_sz, ptr, ptr_sz, block_val_u64, false);
#endif
        default:;
    }

    return kdi_GenMemOpsFindAllBlockIndices_Un_Idx8(idxs, idxs_sz, ptr, ptr_sz, block, block_sz, false);
}


usize
kdGenMemOpsFindAllBlockIndicesU16(u16 *idxs, usize idxs_sz, void *ptr, usize ptr_sz, void *block, usize block_sz)
{
    u8  block_val_u8;
    u16 block_val_u16;
    u32 block_val_u32;
#if defined ARCH_64BIT_INT
    u64 block_val_u64;
#endif

    if (!idxs || !idxs_sz || !ptr || !ptr_sz || !block || !block_sz)
    {
        return 0;
    }

    switch (block_sz)
    {
        case 1:
            block_val_u8 = *PU8_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U8_Idx16(idxs, idxs_sz, ptr, ptr_sz, block_val_u8, false);
        case 2:
            block_val_u16 = *PU16_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U16_Idx16(idxs, idxs_sz, ptr, ptr_sz, block_val_u16, false);
        case 4:
            block_val_u32 = *PU32_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U32_Idx16(idxs, idxs_sz, ptr, ptr_sz, block_val_u32, false);
#if defined ARCH_64BIT_INT
        case 8:
            block_val_u64 = *PU64_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U64_Idx16(idxs, idxs_sz, ptr, ptr_sz, block_val_u64, false);
#endif
        default:;
    }

    return kdi_GenMemOpsFindAllBlockIndices_Un_Idx16(idxs, idxs_sz, ptr, ptr_sz, block, block_sz, false);
}


usize
kdGenMemOpsFindAllBlockIndicesU32(u32 *idxs, usize idxs_sz, void *ptr, usize ptr_sz, void *block, usize block_sz)
{
    u8  block_val_u8;
    u16 block_val_u16;
    u32 block_val_u32;
#if defined ARCH_64BIT_INT
    u64 block_val_u64;
#endif

    if (!idxs || !idxs_sz || !ptr || !ptr_sz || !block || !block_sz)
    {
        return 0;
    }

    switch (block_sz)
    {
        case 1:
            block_val_u8 = *PU8_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U8_Idx32(idxs, idxs_sz, ptr, ptr_sz, block_val_u8, false);
        case 2:
            block_val_u16 = *PU16_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U16_Idx32(idxs, idxs_sz, ptr, ptr_sz, block_val_u16, false);
        case 4:
            block_val_u32 = *PU32_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U32_Idx32(idxs, idxs_sz, ptr, ptr_sz, block_val_u32, false);
#if defined ARCH_64BIT_INT
        case 8:
            block_val_u64 = *PU64_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U64_Idx32(idxs, idxs_sz, ptr, ptr_sz, block_val_u64, false);
#endif
        default:;
    }

    return kdi_GenMemOpsFindAllBlockIndices_Un_Idx32(idxs, idxs_sz, ptr, ptr_sz, block, block_sz, false);
}


#if defined ARCH_64BIT_INT
usize
kdGenMemOpsFindAllBlockIndicesU64(u64 *idxs, usize idxs_sz, void *ptr, usize ptr_sz, void *block, usize block_sz)
{
    u8  block_val_u8;
    u16 block_val_u16;
    u32 block_val_u32;
    u64 block_val_u64;

    if (!idxs || !idxs_sz || !ptr || !ptr_sz || !block || !block_sz)
    {
        return 0;
    }

    switch (block_sz)
    {
        case 1:
            block_val_u8 = *PU8_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U8_Idx64(idxs, idxs_sz, ptr, ptr_sz, block_val_u8, false);
        case 2:
            block_val_u16 = *PU16_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U16_Idx64(idxs, idxs_sz, ptr, ptr_sz, block_val_u16, false);
        case 4:
            block_val_u32 = *PU32_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U32_Idx64(idxs, idxs_sz, ptr, ptr_sz, block_val_u32, false);
        case 8:
            block_val_u64 = *PU64_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U64_Idx64(idxs, idxs_sz, ptr, ptr_sz, block_val_u64, false);
        default:;
    }

    return kdi_GenMemOpsFindAllBlockIndices_Un_Idx64(idxs, idxs_sz, ptr, ptr_sz, block, block_sz, false);
}
#endif


word
kdGenMemOpsCmp(void *ptr1, void *ptr2, usize sz)
{
    byte *src1_ptr, *src2_ptr;

    if (!sz)
    {
        return (ptr1 && ptr2) ? 0 : ptr1 ? 1 : ptr2 ? -1 : 0;
    }

    if (!ptr1 || !ptr2)
    {
        return ptr1 ? 1 : ptr2 ? -1 : 0;
    }

    src1_ptr = ptr1;
    src2_ptr = ptr2;

    while ((*src1_ptr == *src2_ptr) && sz--)
    {
        ++src1_ptr;
        ++src2_ptr;
    }

    return !sz ? 0 : *src1_ptr - *src2_ptr;
}


bool
kdGenMemOpsCat(void *dst, usize sz, void *src1, usize sz1, void *src2, usize sz2)
{
    byte *dst_ptr, *src1_ptr, *src2_ptr;

    if (!dst || !src1 || !src2 || !sz || !sz1 || !sz2)
    {
        return RESULT_FAILURE;
    }

    dst_ptr  = dst;
    src1_ptr = src1;
    src2_ptr = src2;

    while (sz1-- && sz--)
    {
        *dst_ptr = *src1_ptr;
        ++dst_ptr;
        ++src1_ptr;
    }

    while (sz2-- && sz--)
    {
        *dst_ptr = *src2_ptr;
        ++dst_ptr;
        ++src2_ptr;
    }

    return RESULT_SUCCESS;
}
 */
