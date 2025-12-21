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
            kdi_GenMemOpsSetBlocks_U8(dst, dst_sz, *PU8_C(block));
            break;
        case 2:
            kdi_GenMemOpsSetBlocks_U16(dst, dst_sz, *PU16_C(block));
            break;
        case 4:
            kdi_GenMemOpsSetBlocks_U32(dst, dst_sz, *PU32_C(block));
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsSetBlocks_U64(dst, dst_sz, *PU64_C(block));
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
            kdi_GenMemOpsSetBlocks_U8(PU8_C(PBYTE_C(base) + begin_idx), *set_sz, *PU8_C(block));
            break;
        case 2:
            kdi_GenMemOpsSetBlocks_U16(PU16_C(PBYTE_C(base) + begin_idx), *set_sz, *PU16_C(block));
            break;
        case 4:
            kdi_GenMemOpsSetBlocks_U32(PU32_C(PBYTE_C(base) + begin_idx), *set_sz, *PU32_C(block));
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsSetBlocks_U64(PU64_C(PBYTE_C(base) + begin_idx), *set_sz, *PU64_C(block));
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
    if (!base || idx >= base_sz || !block || !block_sz || block_sz > base_sz || (idx + block_sz) > base_sz)
    {
        return RESULT_FAILURE;
    }

    switch (block_sz)
    {
        case 1:
            kdi_GenMemOpsSetBlockAt_U8(base, idx, *PU8_C(block));
            break;
        case 2:
            kdi_GenMemOpsSetBlockAt_U16(base, idx, *PU16_C(block));
            break;
        case 4:
            kdi_GenMemOpsSetBlockAt_U32(base, idx, *PU32_C(block));
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsSetBlockAt_U64(base, idx, *PU64_C(block));
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
            kdi_GenMemOpsInsertBlockAt_U8(base, base_elems, idx, *PU8_C(block));
            break;
        case 2:
            kdi_GenMemOpsInsertBlockAt_U16(base, base_elems, idx, *PU16_C(block));
            break;
        case 4:
            kdi_GenMemOpsInsertBlockAt_U32(base, base_elems, idx, *PU32_C(block));
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsInsertBlockAt_U64(base, base_elems, idx, *PU64_C(block));
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
            kdi_GenMemOpsCountBlocks_U8(count, ptr, ptr_sz, *PU8_C(block));
            break;
        case 2:
            kdi_GenMemOpsCountBlocks_U16(count, ptr, ptr_sz, *PU16_C(block));
            break;
        case 4:
            kdi_GenMemOpsCountBlocks_U32(count, ptr, ptr_sz, *PU32_C(block));
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsCountBlocks_U64(count, ptr, ptr_sz, *PU64_C(block));
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
            kdi_GenMemOpsCountNotBlocks_U8(count, ptr, ptr_sz, *PU8_C(block));
            break;
        case 2:
            kdi_GenMemOpsCountNotBlocks_U16(count, ptr, ptr_sz, *PU16_C(block));
            break;
        case 4:
            kdi_GenMemOpsCountNotBlocks_U32(count, ptr, ptr_sz, *PU32_C(block));
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsCountNotBlocks_U64(count, ptr, ptr_sz, *PU64_C(block));
            break;
#endif
        default:
            kdi_GenMemOpsCountNotBlocks_Un(count, ptr, ptr_sz, block, block_sz);
    }

    return RESULT_SUCCESS;
}


bool
GenMemOpsFindByteIndex(usize *idx, void *ptr, usize sz, byte item)
{
    if (!idx || !ptr || !sz)
    {
        return RESULT_FAILURE;
    }

    return kdi_GenMemOpsFindBlockIndex_U8(idx, ptr, sz, item);
}


bool
GenMemOpsFindBlockIndex(usize *idx, void *ptr, usize ptr_sz, void *block, usize block_sz)
{
    if (!idx || !ptr || !ptr_sz || !block || !block_sz || block_sz > ptr_sz)
    {
        return RESULT_FAILURE;
    }

    switch (block_sz)
    {
        case 1:
            return kdi_GenMemOpsFindBlockIndex_U8(idx, ptr, ptr_sz, *PU8_C(block));
        case 2:
            return kdi_GenMemOpsFindBlockIndex_U16(idx, ptr, ptr_sz, *PU16_C(block));
        case 4:
            return kdi_GenMemOpsFindBlockIndex_U32(idx, ptr, ptr_sz, *PU32_C(block));
#if defined ARCH_64BIT_INT
        case 8:
            return kdi_GenMemOpsFindBlockIndex_U64(idx, ptr, ptr_sz, *PU64_C(block));
#endif
        default:
            return kdi_GenMemOpsFindBlockIndex_Un(idx, ptr, ptr_sz, block, block_sz);
    }
}


bool
GenMemOpsFindByteIndexRange(usize *idx, void *base, usize base_sz, usize begin_idx, usize end, byte item)
{
    bool result;

    if (!idx || !base || begin_idx >= base_sz || begin_idx >= end || end > base_sz)
    {
        return RESULT_FAILURE;
    }

    result = kdi_GenMemOpsFindBlockIndex_U8(idx, PBYTE_C(base) + begin_idx, end - begin_idx, item);

    if (result == RESULT_SUCCESS)
    {
        *idx += begin_idx;
    }

    return result;
}


bool
GenMemOpsFindBlockIndexRange(usize *idx, void *base, usize base_sz, usize begin_idx, usize end, void *block, usize block_sz)
{
    bool result;

    if (!idx || !base || begin_idx >= base_sz || begin_idx >= end || end > base_sz || !block || !block_sz || block_sz > base_sz || begin_idx % block_sz || end % block_sz)
    {
        return RESULT_FAILURE;
    }

    switch (block_sz)
    {
        case 1:
            result = kdi_GenMemOpsFindBlockIndex_U8(idx, PU8_C(PBYTE_C(base) + begin_idx), end - begin_idx, *PU8_C(block));
            break;
        case 2:
            result = kdi_GenMemOpsFindBlockIndex_U16(idx, PU16_C(PBYTE_C(base) + begin_idx), end - begin_idx, *PU16_C(block));
            break;
        case 4:
            result = kdi_GenMemOpsFindBlockIndex_U32(idx, PU32_C(PBYTE_C(base) + begin_idx), end - begin_idx, *PU32_C(block));
            break;
#if defined ARCH_64BIT_INT
        case 8:
            result = kdi_GenMemOpsFindBlockIndex_U64(idx, PU64_C(PBYTE_C(base) + begin_idx), end - begin_idx, *PU64_C(block));
            break;
#endif
        default:
            result = kdi_GenMemOpsFindBlockIndex_Un(idx, PBYTE_C(base) + begin_idx, end - begin_idx, block, block_sz);
            break;
    }

    if (result == RESULT_SUCCESS)
    {
        *idx += begin_idx;
    }

    return result;
}


bool
GenMemOpsFindLastByteIndex(usize *idx, void *ptr, usize sz, byte item)
{
    if (!idx || !ptr || !sz)
    {
        return RESULT_FAILURE;
    }

    return kdi_GenMemOpsFindLastBlockIndex_U8(idx, ptr, sz, item);
}


bool
GenMemOpsFindLastBlockIndex(usize *idx, void *ptr, usize ptr_sz, void *block, usize block_sz)
{
    if (!idx || !ptr || !ptr_sz || !block || !block_sz || block_sz > ptr_sz)
    {
        return RESULT_FAILURE;
    }

    switch (block_sz)
    {
        case 1:
            return kdi_GenMemOpsFindLastBlockIndex_U8(idx, ptr, ptr_sz, *PU8_C(block));
        case 2:
            return kdi_GenMemOpsFindLastBlockIndex_U16(idx, ptr, ptr_sz, *PU16_C(block));
        case 4:
            return kdi_GenMemOpsFindLastBlockIndex_U32(idx, ptr, ptr_sz, *PU32_C(block));
#if defined ARCH_64BIT_INT
        case 8:
            return kdi_GenMemOpsFindLastBlockIndex_U64(idx, ptr, ptr_sz, *PU64_C(block));
#endif
        default:
            return kdi_GenMemOpsFindLastBlockIndex_Un(idx, ptr, ptr_sz, block, block_sz);
    }
}


bool
GenMemOpsFindLastByteIndexRange(usize *idx, void *base, usize base_sz, usize begin_idx, usize end, byte item)
{
    bool result;

    if (!idx || !base || begin_idx >= base_sz || begin_idx >= end || end > base_sz)
    {
        return RESULT_FAILURE;
    }

    result = kdi_GenMemOpsFindLastBlockIndex_U8(idx, PBYTE_C(base) + begin_idx, end - begin_idx, item);

    if (result == RESULT_SUCCESS)
    {
        *idx += begin_idx;
    }

    return result;
}


bool
GenMemOpsFindLastBlockIndexRange(usize *idx, void *base, usize base_sz, usize begin_idx, usize end, void *block, usize block_sz)
{
    bool result;

    if (!idx || !base || begin_idx >= base_sz || begin_idx >= end || end > base_sz || !block || !block_sz || block_sz > base_sz || begin_idx % block_sz || end % block_sz)
    {
        return RESULT_FAILURE;
    }

    switch (block_sz)
    {
        case 1:
            result = kdi_GenMemOpsFindLastBlockIndex_U8(idx, PU8_C(PBYTE_C(base) + begin_idx), end - begin_idx, *PU8_C(block));
            break;
        case 2:
            result = kdi_GenMemOpsFindLastBlockIndex_U16(idx, PU16_C(PBYTE_C(base) + begin_idx), end - begin_idx, *PU16_C(block));
            break;
        case 4:
            result = kdi_GenMemOpsFindLastBlockIndex_U32(idx, PU32_C(PBYTE_C(base) + begin_idx), end - begin_idx, *PU32_C(block));
            break;
#if defined ARCH_64BIT_INT
        case 8:
            result = kdi_GenMemOpsFindLastBlockIndex_U64(idx, PU64_C(PBYTE_C(base) + begin_idx), end - begin_idx, *PU64_C(block));
            break;
#endif
        default:
            result = kdi_GenMemOpsFindLastBlockIndex_Un(idx, PBYTE_C(base) + begin_idx, end - begin_idx, block, block_sz);
            break;
    }

    if (result == RESULT_SUCCESS)
    {
        *idx += begin_idx;
    }

    return result;
}


bool
GenMemOpsFindByteIndicesU8(u8 *idxs, usize idxs_sz, usize *found, void *ptr, usize ptr_sz, byte item)
{
    if (!found)
    {
        return RESULT_FAILURE;
    }

    *found = 0;

    if (!idxs || !ptr)
    {
        return RESULT_FAILURE;
    }

    if (!idxs_sz || !ptr_sz)
    {
        return RESULT_SUCCESS;
    }

    if (idxs_sz > MAX_U8)
    {
        idxs_sz = MAX_U8;
    }

    if (ptr_sz > MAX_U8)
    {
        ptr_sz = MAX_U8;
    }

    kdi_GenMemOpsFindBlockIndicesU8_IdxU8(idxs, idxs_sz, found, ptr, ptr_sz, item);

    return RESULT_SUCCESS;
}


bool
GenMemOpsFindByteIndicesU16(u16 *idxs, usize idxs_sz, usize *found, void *ptr, usize ptr_sz, byte item)
{
    if (!found)
    {
        return RESULT_FAILURE;
    }

    *found = 0;

    if (!idxs || !ptr)
    {
        return RESULT_FAILURE;
    }

    if (!idxs_sz || idxs_sz < SZ_U16 || !ptr_sz)
    {
        return RESULT_SUCCESS;
    }

    if (idxs_sz > MAX_U16)
    {
        idxs_sz = MAX_U16;
    }

    if (ptr_sz > MAX_U16)
    {
        ptr_sz = MAX_U16;
    }

    kdi_GenMemOpsFindBlockIndicesU8_IdxU16(idxs, idxs_sz, found, ptr, ptr_sz, item);

    return RESULT_SUCCESS;
}


bool
GenMemOpsFindByteIndicesU32(u32 *idxs, usize idxs_sz, usize *found, void *ptr, usize ptr_sz, byte item)
{
    if (!found)
    {
        return RESULT_FAILURE;
    }

    *found = 0;

    if (!idxs || !ptr)
    {
        return RESULT_FAILURE;
    }

    if (!idxs_sz || idxs_sz < SZ_U32 || !ptr_sz)
    {
        return RESULT_SUCCESS;
    }

    if (idxs_sz > MAX_U32)
    {
        idxs_sz = MAX_U32;
    }

    if (ptr_sz > MAX_U32)
    {
        ptr_sz = MAX_U32;
    }

    kdi_GenMemOpsFindBlockIndicesU8_IdxU32(idxs, idxs_sz, found, ptr, ptr_sz, item);

    return RESULT_SUCCESS;
}


#if defined ARCH_64BIT_INT
bool
GenMemOpsFindByteIndicesU64(u64 *idxs, usize idxs_sz, usize *found, void *ptr, usize ptr_sz, byte item)
{
    if (!found)
    {
        return RESULT_FAILURE;
    }

    *found = 0;

    if (!idxs || !ptr)
    {
        return RESULT_FAILURE;
    }

    if (!idxs_sz || idxs_sz < SZ_U64 || !ptr_sz)
    {
        return RESULT_SUCCESS;
    }

    kdi_GenMemOpsFindBlockIndicesU8_IdxU64(idxs, idxs_sz, found, ptr, ptr_sz, item);

    return RESULT_SUCCESS;
}
#endif


bool
GenMemOpsFindBlockIndicesU8(u8 *idxs, usize idxs_sz, usize *found, void *ptr, usize ptr_sz, void *block, usize block_sz)
{
    bool exceeds_max;

    if (!found)
    {
        return RESULT_FAILURE;
    }

    *found = 0;

    if (!idxs || !ptr || !block || !block_sz)
    {
        return RESULT_FAILURE;
    }

    if (idxs_sz < SZ_U8 || !ptr_sz)
    {
        return RESULT_SUCCESS;
    }

    if (block_sz > ptr_sz)
    {
        return RESULT_FAILURE;
    }

    if (idxs_sz > MAX_U8)
    {
        idxs_sz = MAX_U8;
    }

    exceeds_max = ptr_sz > MAX_U8;

    if (exceeds_max)
    {
        ptr_sz = MAX_U8 / block_sz;
    }

    switch (block_sz)
    {
        case 1:
            kdi_GenMemOpsFindBlockIndicesU8_IdxU8(idxs, idxs_sz, found, ptr, ptr_sz * (exceeds_max ? block_sz : 1), *PU8_C(block));
            break;
        case 2:
            kdi_GenMemOpsFindBlockIndicesU16_IdxU8(idxs, idxs_sz, found, ptr, ptr_sz * (exceeds_max ? block_sz : 1), *PU16_C(block));
            break;
        case 4:
            kdi_GenMemOpsFindBlockIndicesU32_IdxU8(idxs, idxs_sz, found, ptr, ptr_sz * (exceeds_max ? block_sz : 1), *PU32_C(block));
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsFindBlockIndicesU64_IdxU8(idxs, idxs_sz, found, ptr, ptr_sz * (exceeds_max ? block_sz : 1), *PU64_C(block));
            break;
#endif
        default:
            kdi_GenMemOpsFindBlockIndicesUn_IdxU8(idxs, idxs_sz, found, ptr, ptr_sz * (exceeds_max ? block_sz : 1), block, block_sz);
    }

    return RESULT_SUCCESS;
}


bool
GenMemOpsFindBlockIndicesU16(u16 *idxs, usize idxs_sz, usize *found, void *ptr, usize ptr_sz, void *block, usize block_sz)
{
    bool exceeds_max;

    if (!found)
    {
        return RESULT_FAILURE;
    }

    *found = 0;

    if (!idxs || !ptr || !block || !block_sz)
    {
        return RESULT_FAILURE;
    }

    if (idxs_sz < SZ_U16 || !ptr_sz)
    {
        return RESULT_SUCCESS;
    }

    if (block_sz > ptr_sz)
    {
        return RESULT_FAILURE;
    }

    if (idxs_sz > MAX_U16)
    {
        idxs_sz = MAX_U16;
    }

    exceeds_max = ptr_sz > MAX_U16;

    if (exceeds_max)
    {
        ptr_sz = MAX_U16 / block_sz;
    }

    switch (block_sz)
    {
        case 1:
            kdi_GenMemOpsFindBlockIndicesU8_IdxU16(idxs, idxs_sz, found, ptr, ptr_sz * (exceeds_max ? block_sz : 1), *PU8_C(block));
            break;
        case 2:
            kdi_GenMemOpsFindBlockIndicesU16_IdxU16(idxs, idxs_sz, found, ptr, ptr_sz * (exceeds_max ? block_sz : 1), *PU16_C(block));
            break;
        case 4:
            kdi_GenMemOpsFindBlockIndicesU32_IdxU16(idxs, idxs_sz, found, ptr, ptr_sz * (exceeds_max ? block_sz : 1), *PU32_C(block));
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsFindBlockIndicesU64_IdxU16(idxs, idxs_sz, found, ptr, ptr_sz * (exceeds_max ? block_sz : 1), *PU64_C(block));
            break;
#endif
        default:
            kdi_GenMemOpsFindBlockIndicesUn_IdxU16(idxs, idxs_sz, found, ptr, ptr_sz * (exceeds_max ? block_sz : 1), block, block_sz);
    }

    return RESULT_SUCCESS;
}


bool
GenMemOpsFindBlockIndicesU32(u32 *idxs, usize idxs_sz, usize *found, void *ptr, usize ptr_sz, void *block, usize block_sz)
{
    bool exceeds_max;

    if (!found)
    {
        return RESULT_FAILURE;
    }

    *found = 0;

    if (!idxs || !ptr || !block || !block_sz)
    {
        return RESULT_FAILURE;
    }

    if (idxs_sz < SZ_U32 || !ptr_sz)
    {
        return RESULT_SUCCESS;
    }

    if (block_sz > ptr_sz)
    {
        return RESULT_FAILURE;
    }

    if (idxs_sz > MAX_U32)
    {
        idxs_sz = MAX_U32;
    }

    exceeds_max = ptr_sz > MAX_U32;

    if (exceeds_max)
    {
        ptr_sz = MAX_U32 / block_sz;
    }

    switch (block_sz)
    {
        case 1:
            kdi_GenMemOpsFindBlockIndicesU8_IdxU32(idxs, idxs_sz, found, ptr, ptr_sz * (exceeds_max ? block_sz : 1), *PU8_C(block));
            break;
        case 2:
            kdi_GenMemOpsFindBlockIndicesU16_IdxU32(idxs, idxs_sz, found, ptr, ptr_sz * (exceeds_max ? block_sz : 1), *PU16_C(block));
            break;
        case 4:
            kdi_GenMemOpsFindBlockIndicesU32_IdxU32(idxs, idxs_sz, found, ptr, ptr_sz * (exceeds_max ? block_sz : 1), *PU32_C(block));
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsFindBlockIndicesU64_IdxU32(idxs, idxs_sz, found, ptr, ptr_sz * (exceeds_max ? block_sz : 1), *PU64_C(block));
            break;
#endif
        default:
            kdi_GenMemOpsFindBlockIndicesUn_IdxU32(idxs, idxs_sz, found, ptr, ptr_sz * (exceeds_max ? block_sz : 1), block, block_sz);
    }

    return RESULT_SUCCESS;
}


#if defined ARCH_64BIT_INT
bool
GenMemOpsFindBlockIndicesU64(u64 *idxs, usize idxs_sz, usize *found, void *ptr, usize ptr_sz, void *block, usize block_sz)
{
    if (!found)
    {
        return RESULT_FAILURE;
    }

    *found = 0;

    if (!idxs || !ptr || !block || !block_sz)
    {
        return RESULT_FAILURE;
    }

    if (idxs_sz < SZ_U64 || !ptr_sz)
    {
        return RESULT_SUCCESS;
    }

    if (block_sz > ptr_sz)
    {
        return RESULT_FAILURE;
    }

    ptr_sz /= block_sz;

    switch (block_sz)
    {
        case 1:
            kdi_GenMemOpsFindBlockIndicesU8_IdxU64(idxs, idxs_sz, found, ptr, ptr_sz * block_sz, *PU8_C(block));
            break;
        case 2:
            kdi_GenMemOpsFindBlockIndicesU16_IdxU64(idxs, idxs_sz, found, ptr, ptr_sz * block_sz, *PU16_C(block));
            break;
        case 4:
            kdi_GenMemOpsFindBlockIndicesU32_IdxU64(idxs, idxs_sz, found, ptr, ptr_sz * block_sz, *PU32_C(block));
            break;
        case 8:
            kdi_GenMemOpsFindBlockIndicesU64_IdxU64(idxs, idxs_sz, found, ptr, ptr_sz * block_sz, *PU64_C(block));
            break;
        default:
            kdi_GenMemOpsFindBlockIndicesUn_IdxU64(idxs, idxs_sz, found, ptr, ptr_sz * block_sz, block, block_sz);
    }

    return RESULT_SUCCESS;
}
#endif


bool
GenMemOpsFindByteIndices(usize *idxs, usize idxs_sz, usize *found, void *ptr, usize ptr_sz, byte item)
{
#if defined ARCH_64BIT_INT
    return GenMemOpsFindByteIndicesU64(idxs, idxs_sz, found, ptr, ptr_sz, item);
#else
    return GenMemOpsFindByteIndicesU32(idxs, idxs_sz, found, ptr, ptr_sz, item);
#endif
}


bool
GenMemOpsFindBlockIndices(usize *idxs, usize idxs_sz, usize *found, void *ptr, usize ptr_sz, void *block, usize block_sz)
{
#if defined ARCH_64BIT_INT
    return GenMemOpsFindBlockIndicesU64(idxs, idxs_sz, found, ptr, ptr_sz, block, block_sz);
#else
    return GenMemOpsFindBlockIndicesU32(idxs, idxs_sz, found, ptr, ptr_sz, block, block_sz);
#endif
}


bool
GenMemOpsFindByteIndicesRangeU8(u8 *idxs, usize idxs_sz, usize *found, void *base, usize base_sz, usize begin_idx, usize end, byte item)
{
    usize final_sz, found_items, temp_idx;

    if (!found)
    {
        return RESULT_FAILURE;
    }

    *found = 0;

    if (!idxs || !base)
    {
        return RESULT_FAILURE;
    }

    if (!idxs_sz || !base_sz)
    {
        return RESULT_SUCCESS;
    }

    if (begin_idx >= base_sz || begin_idx >= end || end > base_sz)
    {
        return RESULT_FAILURE;
    }

    if (idxs_sz > MAX_U8)
    {
        idxs_sz = MAX_U8;
    }

    final_sz = end - begin_idx;

    if (final_sz > MAX_U8)
    {
        final_sz = MAX_U8;
    }

    kdi_GenMemOpsFindBlockIndicesU8_IdxU8(idxs, idxs_sz, found, PBYTE_C(base) + begin_idx, final_sz, item);

    found_items = *found;

    while (found_items)
    {
        temp_idx = *idxs + begin_idx;

        if (temp_idx >= MAX_U8)
        {
            *found -= found_items;
            break;
        }

        *idxs = U8_C(temp_idx);

        ++idxs;
        --found_items;
    }

    return RESULT_SUCCESS;
}


bool
GenMemOpsFindByteIndicesRangeU16(u16 *idxs, usize idxs_sz, usize *found, void *base, usize base_sz, usize begin_idx, usize end, byte item)
{
    usize final_sz, found_items, temp_idx;

    if (!found)
    {
        return RESULT_FAILURE;
    }

    *found = 0;

    if (!idxs || !base)
    {
        return RESULT_FAILURE;
    }

    if (idxs_sz < SZ_U16 || !base_sz)
    {
        return RESULT_SUCCESS;
    }

    if (begin_idx >= base_sz || begin_idx >= end || end > base_sz)
    {
        return RESULT_FAILURE;
    }

    if (idxs_sz > MAX_U16)
    {
        idxs_sz = MAX_U16;
    }

    final_sz = end - begin_idx;

    if (final_sz > MAX_U16)
    {
        final_sz = MAX_U16;
    }

    kdi_GenMemOpsFindBlockIndicesU8_IdxU16(idxs, idxs_sz, found, PBYTE_C(base) + begin_idx, final_sz, item);

    found_items = *found;

    while (found_items)
    {
        temp_idx = *idxs + begin_idx;

        if (temp_idx >= MAX_U16)
        {
            *found -= found_items;
            break;
        }

        *idxs = U16_C(temp_idx);

        ++idxs;
        --found_items;
    }

    return RESULT_SUCCESS;
}


bool
GenMemOpsFindByteIndicesRangeU32(u32 *idxs, usize idxs_sz, usize *found, void *base, usize base_sz, usize begin_idx, usize end, byte item)
{
    usize final_sz, found_items, temp_idx;

    if (!found)
    {
        return RESULT_FAILURE;
    }

    *found = 0;

    if (!idxs || !base)
    {
        return RESULT_FAILURE;
    }

    if (idxs_sz < SZ_U32 || !base_sz)
    {
        return RESULT_SUCCESS;
    }

    if (begin_idx >= base_sz || begin_idx >= end || end > base_sz)
    {
        return RESULT_FAILURE;
    }

    if (idxs_sz > MAX_U32)
    {
        idxs_sz = MAX_U32;
    }

    final_sz = end - begin_idx;

    if (final_sz > MAX_U32)
    {
        final_sz = MAX_U32;
    }

    kdi_GenMemOpsFindBlockIndicesU8_IdxU32(idxs, idxs_sz, found, PBYTE_C(base) + begin_idx, final_sz, item);

    found_items = *found;

    while (found_items)
    {
        temp_idx = *idxs + begin_idx;

        if (temp_idx >= MAX_U32)
        {
            *found -= found_items;
            break;
        }

        *idxs = U32_C(temp_idx);

        ++idxs;
        --found_items;
    }

    return RESULT_SUCCESS;
}


#if defined ARCH_64BIT_INT
bool
GenMemOpsFindByteIndicesRangeU64(u64 *idxs, usize idxs_sz, usize *found, void *base, usize base_sz, usize begin_idx, usize end, byte item)
{
    usize found_items, temp_idx;

    if (!found)
    {
        return RESULT_FAILURE;
    }

    *found = 0;

    if (!idxs || !base)
    {
        return RESULT_FAILURE;
    }

    if (idxs_sz < SZ_U64 || !base_sz)
    {
        return RESULT_SUCCESS;
    }

    if (begin_idx >= base_sz || begin_idx >= end || end > base_sz)
    {
        return RESULT_FAILURE;
    }

    kdi_GenMemOpsFindBlockIndicesU8_IdxU64(idxs, idxs_sz, found, PBYTE_C(base) + begin_idx, end - begin_idx, item);

    found_items = *found;

    while (found_items)
    {
        temp_idx = *idxs + begin_idx;

        if (temp_idx >= MAX_U64)
        {
            *found -= found_items;
            break;
        }

        *idxs = U64_C(temp_idx);

        ++idxs;
        --found_items;
    }

    return RESULT_SUCCESS;
}
#endif


bool
GenMemOpsFindBlockIndicesRangeU8(u8 *idxs, usize idxs_sz, usize *found, void *base, usize base_sz, usize begin_idx, usize end, void *block, usize block_sz)
{
    usize final_sz, found_items, temp_idx;
    bool  exceeds_max;

    if (!found)
    {
        return RESULT_FAILURE;
    }

    *found = 0;

    if (!idxs || !base || !block || !block_sz)
    {
        return RESULT_FAILURE;
    }

    if (idxs_sz < SZ_U8 || !base_sz)
    {
        return RESULT_SUCCESS;
    }

    if (begin_idx >= base_sz || begin_idx >= end || end > base_sz || block_sz > base_sz || begin_idx % block_sz)
    {
        return RESULT_FAILURE;
    }

    if (idxs_sz > MAX_U8)
    {
        idxs_sz = MAX_U8;
    }

    final_sz    = end - begin_idx;
    exceeds_max = final_sz > MAX_U8;

    if (exceeds_max)
    {
        final_sz = MAX_U8 / block_sz;
    }

    switch (block_sz)
    {
        case 1:
            kdi_GenMemOpsFindBlockIndicesU8_IdxU8(idxs, idxs_sz, found, PU8_C(base) + begin_idx, final_sz * (exceeds_max ? block_sz : 1), *PU8_C(block));
            break;
        case 2:
            kdi_GenMemOpsFindBlockIndicesU16_IdxU8(idxs, idxs_sz, found, PU16_C(PBYTE_C(base) + begin_idx), final_sz * (exceeds_max ? block_sz : 1), *PU16_C(block));
            break;
        case 4:
            kdi_GenMemOpsFindBlockIndicesU32_IdxU8(idxs, idxs_sz, found, PU32_C(PBYTE_C(base) + begin_idx), final_sz * (exceeds_max ? block_sz : 1), *PU32_C(block));
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsFindBlockIndicesU64_IdxU8(idxs, idxs_sz, found, PU64_C(PBYTE_C(base) + begin_idx), final_sz * (exceeds_max ? block_sz : 1), *PU64_C(block));
            break;
#endif
        default:
            kdi_GenMemOpsFindBlockIndicesUn_IdxU8(idxs, idxs_sz, found, PBYTE_C(base) + begin_idx, final_sz * (exceeds_max ? block_sz : 1), block, block_sz);
    }

    found_items = *found;

    while (found_items)
    {
        temp_idx = *idxs + begin_idx;

        if (temp_idx >= MAX_U8)
        {
            *found -= found_items;
            break;
        }

        *idxs = U8_C(temp_idx);

        ++idxs;
        found_items -= block_sz;
    }

    return RESULT_SUCCESS;
}


bool
GenMemOpsFindBlockIndicesRangeU16(u16 *idxs, usize idxs_sz, usize *found, void *base, usize base_sz, usize begin_idx, usize end, void *block, usize block_sz)
{
    usize final_sz, found_items, temp_idx;
    bool  exceeds_max;

    if (!found)
    {
        return RESULT_FAILURE;
    }

    *found = 0;

    if (!idxs || !base || !block || !block_sz)
    {
        return RESULT_FAILURE;
    }

    if (idxs_sz < SZ_U16 || !base_sz)
    {
        return RESULT_SUCCESS;
    }

    if (begin_idx >= base_sz || begin_idx >= end || end > base_sz || block_sz > base_sz || begin_idx % block_sz)
    {
        return RESULT_FAILURE;
    }

    if (idxs_sz > MAX_U16)
    {
        idxs_sz = MAX_U16;
    }

    final_sz    = end - begin_idx;
    exceeds_max = final_sz > MAX_U16;

    if (exceeds_max)
    {
        final_sz = MAX_U16 / block_sz;
    }

    switch (block_sz)
    {
        case 1:
            kdi_GenMemOpsFindBlockIndicesU8_IdxU16(idxs, idxs_sz, found, PU8_C(base) + begin_idx, final_sz * (exceeds_max ? block_sz : 1), *PU8_C(block));
            break;
        case 2:
            kdi_GenMemOpsFindBlockIndicesU16_IdxU16(idxs, idxs_sz, found, PU16_C(PBYTE_C(base) + begin_idx), final_sz * (exceeds_max ? block_sz : 1), *PU16_C(block));
            break;
        case 4:
            kdi_GenMemOpsFindBlockIndicesU32_IdxU16(idxs, idxs_sz, found, PU32_C(PBYTE_C(base) + begin_idx), final_sz * (exceeds_max ? block_sz : 1), *PU32_C(block));
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsFindBlockIndicesU64_IdxU16(idxs, idxs_sz, found, PU64_C(PBYTE_C(base) + begin_idx), final_sz * (exceeds_max ? block_sz : 1), *PU64_C(block));
            break;
#endif
        default:
            kdi_GenMemOpsFindBlockIndicesUn_IdxU16(idxs, idxs_sz, found, PBYTE_C(base) + begin_idx, final_sz * (exceeds_max ? block_sz : 1), block, block_sz);
    }

    found_items = *found;

    while (found_items)
    {
        temp_idx = *idxs + begin_idx;

        if (temp_idx >= MAX_U16)
        {
            *found -= found_items;
            break;
        }

        *idxs = U16_C(temp_idx);

        ++idxs;
        found_items -= block_sz;
    }

    return RESULT_SUCCESS;
}


bool
GenMemOpsFindBlockIndicesRangeU32(u32 *idxs, usize idxs_sz, usize *found, void *base, usize base_sz, usize begin_idx, usize end, void *block, usize block_sz)
{
    usize final_sz, found_items, temp_idx;
    bool  exceeds_max;

    if (!found)
    {
        return RESULT_FAILURE;
    }

    *found = 0;

    if (!idxs || !base || !block || !block_sz)
    {
        return RESULT_FAILURE;
    }

    if (idxs_sz < SZ_U32 || !base_sz)
    {
        return RESULT_SUCCESS;
    }

    if (begin_idx >= base_sz || begin_idx >= end || end > base_sz || block_sz > base_sz || begin_idx % block_sz)
    {
        return RESULT_FAILURE;
    }

    if (idxs_sz > MAX_U32)
    {
        idxs_sz = MAX_U32;
    }

    final_sz    = end - begin_idx;
    exceeds_max = final_sz > MAX_U32;

    if (exceeds_max)
    {
        final_sz = MAX_U32 / block_sz;
    }

    switch (block_sz)
    {
        case 1:
            kdi_GenMemOpsFindBlockIndicesU8_IdxU32(idxs, idxs_sz, found, PU8_C(base) + begin_idx, final_sz * (exceeds_max ? block_sz : 1), *PU8_C(block));
            break;
        case 2:
            kdi_GenMemOpsFindBlockIndicesU16_IdxU32(idxs, idxs_sz, found, PU16_C(PBYTE_C(base) + begin_idx), final_sz * (exceeds_max ? block_sz : 1), *PU16_C(block));
            break;
        case 4:
            kdi_GenMemOpsFindBlockIndicesU32_IdxU32(idxs, idxs_sz, found, PU32_C(PBYTE_C(base) + begin_idx), final_sz * (exceeds_max ? block_sz : 1), *PU32_C(block));
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsFindBlockIndicesU64_IdxU32(idxs, idxs_sz, found, PU64_C(PBYTE_C(base) + begin_idx), final_sz * (exceeds_max ? block_sz : 1), *PU64_C(block));
            break;
#endif
        default:
            kdi_GenMemOpsFindBlockIndicesUn_IdxU32(idxs, idxs_sz, found, PBYTE_C(base) + begin_idx, final_sz * (exceeds_max ? block_sz : 1), block, block_sz);
    }

    found_items = *found;

    while (found_items)
    {
        temp_idx = *idxs + begin_idx;

        if (temp_idx >= MAX_U32)
        {
            *found -= found_items;
            break;
        }

        *idxs = U32_C(temp_idx);

        ++idxs;
        found_items -= block_sz;
    }

    return RESULT_SUCCESS;
}


#if defined ARCH_64BIT_INT
bool
GenMemOpsFindBlockIndicesRangeU64(u64 *idxs, usize idxs_sz, usize *found, void *base, usize base_sz, usize begin_idx, usize end, void *block, usize block_sz)
{
    usize final_sz, found_items, temp_idx;

    if (!found)
    {
        return RESULT_FAILURE;
    }

    *found = 0;

    if (!idxs || !base || !block || !block_sz)
    {
        return RESULT_FAILURE;
    }

    if (idxs_sz < SZ_U64 || !base_sz)
    {
        return RESULT_SUCCESS;
    }

    if (begin_idx >= base_sz || begin_idx >= end || end > base_sz || block_sz > base_sz || begin_idx % block_sz)
    {
        return RESULT_FAILURE;
    }

    if (idxs_sz > MAX_U64)
    {
        idxs_sz = MAX_U64;
    }

    final_sz = (end - begin_idx) / block_sz;

    switch (block_sz)
    {
        case 1:
            kdi_GenMemOpsFindBlockIndicesU8_IdxU64(idxs, idxs_sz, found, PU8_C(base) + begin_idx, final_sz * block_sz, *PU8_C(block));
            break;
        case 2:
            kdi_GenMemOpsFindBlockIndicesU16_IdxU64(idxs, idxs_sz, found, PU16_C(PBYTE_C(base) + begin_idx), final_sz * block_sz, *PU16_C(block));
            break;
        case 4:
            kdi_GenMemOpsFindBlockIndicesU32_IdxU64(idxs, idxs_sz, found, PU32_C(PBYTE_C(base) + begin_idx), final_sz * block_sz, *PU32_C(block));
            break;
        case 8:
            kdi_GenMemOpsFindBlockIndicesU64_IdxU64(idxs, idxs_sz, found, PU64_C(PBYTE_C(base) + begin_idx), final_sz * block_sz, *PU64_C(block));
            break;
        default:
            kdi_GenMemOpsFindBlockIndicesUn_IdxU64(idxs, idxs_sz, found, PBYTE_C(base) + begin_idx, final_sz * block_sz, block, block_sz);
    }

    found_items = *found;

    while (found_items)
    {
        temp_idx = *idxs + begin_idx;

        if (temp_idx >= MAX_U64)
        {
            *found -= found_items;
            break;
        }

        *idxs = U64_C(temp_idx);

        ++idxs;
        found_items -= block_sz;
    }

    return RESULT_SUCCESS;
}
#endif


bool
GenMemOpsFindByteIndicesRange(usize *idxs, usize idxs_sz, usize *found, void *base, usize base_sz, usize begin_idx, usize end, byte item)
{
#if defined ARCH_64BIT_INT
    return GenMemOpsFindByteIndicesRangeU64(idxs, idxs_sz, found, base, base_sz, begin_idx, end, item);
#else
    return GenMemOpsFindByteIndicesRangeU32(idxs, idxs_sz, found, base, base_sz, begin_idx, end, item);
#endif
}


bool
GenMemOpsFindBlockIndicesRange(usize *idxs, usize idxs_sz, usize *found, void *base, usize base_sz, usize begin_idx, usize end, void *block, usize block_sz)
{
#if defined ARCH_64BIT_INT
    return GenMemOpsFindBlockIndicesRangeU64(idxs, idxs_sz, found, base, base_sz, begin_idx, end, block, block_sz);
#else
    return GenMemOpsFindBlockIndicesRangeU32(idxs, idxs_sz, found, base, base_sz, begin_idx, end, block, block_sz);
#endif
}


bool
GenMemOpsReplaceByte(void *ptr, usize sz, byte find_item, byte new_item)
{
    if (!ptr || !sz)
    {
        return RESULT_FAILURE;
    }

    kdi_GenMemOpsReplaceBlock_U8(ptr, sz, find_item, new_item);

    return RESULT_SUCCESS;
}


bool
GenMemOpsReplaceBlock(void *ptr, usize ptr_sz, void *find_block, void *new_block, usize block_sz)
{
    if (!ptr || !ptr_sz || !find_block || !new_block || !block_sz || block_sz > ptr_sz)
    {
        return RESULT_FAILURE;
    }

    switch (block_sz)
    {
        case 1:
            kdi_GenMemOpsReplaceBlock_U8(ptr, ptr_sz, *PU8_C(find_block), *PU8_C(new_block));
            break;
        case 2:
            kdi_GenMemOpsReplaceBlock_U16(ptr, ptr_sz, *PU16_C(find_block), *PU16_C(new_block));
            break;
        case 4:
            kdi_GenMemOpsReplaceBlock_U32(ptr, ptr_sz, *PU32_C(find_block), *PU32_C(new_block));
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsReplaceBlock_U64(ptr, ptr_sz, *PU64_C(find_block), *PU64_C(new_block));
            break;
#endif
        default:
            kdi_GenMemOpsReplaceBlock_Un(ptr, ptr_sz, find_block, new_block, block_sz);
    }

    return RESULT_SUCCESS;
}


bool
GenMemOpsReplaceByteRange(void *base, usize base_sz, usize begin_idx, usize end, byte find_item, byte new_item)
{
    usize final_sz;

    if (!base || begin_idx >= base_sz || !end)
    {
        return RESULT_FAILURE;
    }

    final_sz = end - begin_idx;

    if (final_sz > base_sz)
    {
        return RESULT_FAILURE;
    }

    kdi_GenMemOpsReplaceBlock_U8(PU8_C(base) + begin_idx, final_sz, find_item, new_item);

    return RESULT_SUCCESS;
}


bool
GenMemOpsReplaceBlockRange(void *base, usize base_sz, usize begin_idx, usize end, void *find_block, void *new_block, usize block_sz)
{
    usize final_sz;

    if (!base || begin_idx >= base_sz || end > base_sz || !find_block || !new_block || !block_sz || (begin_idx % block_sz))
    {
        return RESULT_FAILURE;
    }

    final_sz = end - begin_idx;

    if (final_sz > base_sz || block_sz > final_sz || (final_sz % block_sz))
    {
        return RESULT_FAILURE;
    }

    switch (block_sz)
    {
        case 1:
            kdi_GenMemOpsReplaceBlock_U8(PU8_C(base) + begin_idx, final_sz, *PU8_C(find_block), *PU8_C(new_block));
            break;
        case 2:
            kdi_GenMemOpsReplaceBlock_U16(PU16_C(PBYTE_C(base) + begin_idx), final_sz, *PU16_C(find_block), *PU16_C(new_block));
            break;
        case 4:
            kdi_GenMemOpsReplaceBlock_U32(PU32_C(PBYTE_C(base) + begin_idx), final_sz, *PU32_C(find_block), *PU32_C(new_block));
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsReplaceBlock_U64(PU64_C(PBYTE_C(base) + begin_idx), final_sz, *PU64_C(find_block), *PU64_C(new_block));
            break;
#endif
        default:
            kdi_GenMemOpsReplaceBlock_Un(PBYTE_C(base) + begin_idx, final_sz, find_block, new_block, block_sz);
    }

    return RESULT_SUCCESS;
}


bool
GenMemOpsReplaceLastByte(void *ptr, usize sz, byte find_item, byte new_item)
{
    if (!ptr || !sz)
    {
        return RESULT_FAILURE;
    }

    kdi_GenMemOpsReplaceLastBlock_U8(ptr, sz, find_item, new_item);

    return RESULT_SUCCESS;
}


bool
GenMemOpsReplaceLastBlock(void *ptr, usize ptr_sz, void *find_block, void *new_block, usize block_sz)
{
    if (!ptr || !ptr_sz || !find_block || !new_block || !block_sz || block_sz > ptr_sz)
    {
        return RESULT_FAILURE;
    }

    switch (block_sz)
    {
        case 1:
            kdi_GenMemOpsReplaceLastBlock_U8(ptr, ptr_sz, *PU8_C(find_block), *PU8_C(new_block));
            break;
        case 2:
            kdi_GenMemOpsReplaceLastBlock_U16(ptr, ptr_sz, *PU16_C(find_block), *PU16_C(new_block));
            break;
        case 4:
            kdi_GenMemOpsReplaceLastBlock_U32(ptr, ptr_sz, *PU32_C(find_block), *PU32_C(new_block));
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsReplaceLastBlock_U64(ptr, ptr_sz, *PU64_C(find_block), *PU64_C(new_block));
            break;
#endif
        default:
            kdi_GenMemOpsReplaceLastBlock_Un(ptr, ptr_sz, find_block, new_block, block_sz);
    }

    return RESULT_SUCCESS;
}


bool
GenMemOpsReplaceLastByteRange(void *base, usize base_sz, usize begin_idx, usize end, byte find_item, byte new_item)
{
    usize final_sz;

    if (!base || begin_idx >= base_sz || !end)
    {
        return RESULT_FAILURE;
    }

    final_sz = end - begin_idx;

    if (final_sz > base_sz)
    {
        return RESULT_FAILURE;
    }

    kdi_GenMemOpsReplaceLastBlock_U8(PU8_C(base) + begin_idx, final_sz, find_item, new_item);

    return RESULT_SUCCESS;
}


bool
GenMemOpsReplaceLastBlockRange(void *base, usize base_sz, usize begin_idx, usize end, void *find_block, void *new_block, usize block_sz)
{
    usize final_sz;

    if (!base || begin_idx >= base_sz || end > base_sz || !find_block || !new_block || !block_sz || (begin_idx % block_sz))
    {
        return RESULT_FAILURE;
    }

    final_sz = end - begin_idx;

    if (final_sz > base_sz || block_sz > final_sz || (final_sz % block_sz))
    {
        return RESULT_FAILURE;
    }

    switch (block_sz)
    {
        case 1:
            kdi_GenMemOpsReplaceLastBlock_U8(PU8_C(base) + begin_idx, final_sz, *PU8_C(find_block), *PU8_C(new_block));
            break;
        case 2:
            kdi_GenMemOpsReplaceLastBlock_U16(PU16_C(PBYTE_C(base) + begin_idx), final_sz, *PU16_C(find_block), *PU16_C(new_block));
            break;
        case 4:
            kdi_GenMemOpsReplaceLastBlock_U32(PU32_C(PBYTE_C(base) + begin_idx), final_sz, *PU32_C(find_block), *PU32_C(new_block));
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsReplaceLastBlock_U64(PU64_C(PBYTE_C(base) + begin_idx), final_sz, *PU64_C(find_block), *PU64_C(new_block));
            break;
#endif
        default:
            kdi_GenMemOpsReplaceLastBlock_Un(PBYTE_C(base) + begin_idx, final_sz, find_block, new_block, block_sz);
    }

    return RESULT_SUCCESS;
}


bool
GenMemOpsReplaceAllBytes(void *ptr, usize sz, usize *count, byte find_item, byte new_item)
{
    if (!count)
    {
        return RESULT_FAILURE;
    }

    *count = 0;

    if (!ptr || !sz)
    {
        return RESULT_FAILURE;
    }

    kdi_GenMemOpsReplaceAllBlocks_U8(ptr, sz, count, find_item, new_item);

    return RESULT_SUCCESS;
}


bool
GenMemOpsReplaceAllBlocks(void *ptr, usize ptr_sz, usize *byte_count, void *find_block, void *new_block, usize block_sz)
{
    if (!byte_count)
    {
        return RESULT_FAILURE;
    }

    *byte_count = 0;

    if (!ptr || !ptr_sz || !find_block || !new_block || !block_sz || block_sz > ptr_sz || (ptr_sz % block_sz))
    {
        return RESULT_FAILURE;
    }

    switch (block_sz)
    {
        case 1:
            kdi_GenMemOpsReplaceAllBlocks_U8(ptr, ptr_sz, byte_count, *PU8_C(find_block), *PU8_C(new_block));
            break;
        case 2:
            kdi_GenMemOpsReplaceAllBlocks_U16(ptr, ptr_sz, byte_count, *PU16_C(find_block), *PU16_C(new_block));
            break;
        case 4:
            kdi_GenMemOpsReplaceAllBlocks_U32(ptr, ptr_sz, byte_count, *PU32_C(find_block), *PU32_C(new_block));
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsReplaceAllBlocks_U64(ptr, ptr_sz, byte_count, *PU64_C(find_block), *PU64_C(new_block));
            break;
#endif
        default:
            kdi_GenMemOpsReplaceAllBlocks_Un(ptr, ptr_sz, byte_count, find_block, new_block, block_sz);
    }

    return RESULT_SUCCESS;
}


bool
GenMemOpsReplaceAllBytesBound(void *base, usize base_sz, usize begin_idx, usize end, usize *count, byte find_item, byte new_item)
{
    if (!count)
    {
        return RESULT_FAILURE;
    }

    *count = 0;

    if (!base || begin_idx >= base_sz || !end)
    {
        return RESULT_FAILURE;
    }

    if ((begin_idx + end) > base_sz)
    {
        end = base_sz - begin_idx;
    }

    kdi_GenMemOpsReplaceAllBlocks_U8(PU8_C(base) + begin_idx, end, count, find_item, new_item);

    return RESULT_SUCCESS;
}

bool
GenMemOpsReplaceAllBlocksBound(void *base, usize base_sz, usize begin_idx, usize end, usize *byte_count, void *find_block, void *new_block, usize block_sz)
{
    if (!byte_count)
    {
        return RESULT_FAILURE;
    }

    *byte_count = 0;

    if (!base || begin_idx >= base_sz || !find_block || !new_block || !block_sz || block_sz > base_sz || base_sz % block_sz || begin_idx % block_sz)
    {
        return RESULT_FAILURE;
    }

    end -= end % block_sz;

    if ((begin_idx + end) > base_sz)
    {
        end = base_sz - begin_idx;
    }

    switch (block_sz)
    {
        case 1:
            kdi_GenMemOpsReplaceAllBlocks_U8(PU8_C(base) + begin_idx, end, byte_count, *PU8_C(find_block), *PU8_C(new_block));
            break;
        case 2:
            kdi_GenMemOpsReplaceAllBlocks_U16(PU16_C(PBYTE_C(base) + begin_idx), end, byte_count, *PU16_C(find_block), *PU16_C(new_block));
            break;
        case 4:
            kdi_GenMemOpsReplaceAllBlocks_U32(PU32_C(PBYTE_C(base) + begin_idx), end, byte_count, *PU32_C(find_block), *PU32_C(new_block));
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsReplaceAllBlocks_U64(PU64_C(PBYTE_C(base) + begin_idx), end, byte_count, *PU64_C(find_block), *PU64_C(new_block));
            break;
#endif
        default:
            kdi_GenMemOpsReplaceAllBlocks_Un(PBYTE_C(base) + begin_idx, end, byte_count, find_block, new_block, block_sz);
    }

    return RESULT_SUCCESS;
}
