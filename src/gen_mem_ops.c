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

    kdi_GenMemOpsCopy(dst, src, sz);

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

    kdi_GenMemOpsCopy(dst, src, *copied_sz);

    return RESULT_SUCCESS;
}

bool
kdGenMemOpsCopyRange(void *dst_base, usize dst_base_sz, usize *copied_sz, void *src_base, usize src_base_sz, usize dst_idx, usize src_idx, usize byte_count)
{
    usize final_dst_sz, final_src_sz;

    if (!copied_sz)
    {
        return RESULT_FAILURE;
    }

    *copied_sz = 0;

    if (!dst_base || !dst_base_sz || !src_base || !src_base_sz || dst_idx >= dst_base_sz || src_idx >= src_base_sz || !byte_count)
    {
        return RESULT_FAILURE;
    }

    final_dst_sz = dst_base_sz - dst_idx;
    final_dst_sz = final_dst_sz > byte_count ? byte_count : final_dst_sz;

    final_src_sz = src_base_sz - src_idx;
    final_src_sz = final_src_sz > byte_count ? byte_count : final_src_sz;

    *copied_sz   = final_dst_sz < final_src_sz ? final_dst_sz : final_src_sz;

    kdi_GenMemOpsCopy(PU8_C(dst_base) + dst_idx, PU8_C(src_base) + src_idx, *copied_sz);

    return RESULT_SUCCESS;
}


/*
bool
kdGenMemOpsSwapBytes(void *ptr, usize sz, usize idx1, usize idx2)
{
    if (!ptr || !sz || idx1 >= sz || idx2 >= sz)
    {
        return RESULT_FAILURE;
    }

    kdi_GenMemOpsSwapBlocks_U8(ptr, idx1, idx2);

    return RESULT_SUCCESS;
}


bool
kdGenMemOpsSwapBlocks(void *ptr, usize sz, usize idx1, usize idx2, usize block_sz)
{
    if (!ptr || !sz || !block_sz || idx1 >= sz || idx2 >= sz)
    {
        return RESULT_FAILURE;
    }

    switch (block_sz)
    {
        case 1:
            kdi_GenMemOpsSwapBlocks_U8(ptr, idx1, idx2);
            break;
        case 2:
            kdi_GenMemOpsSwapBlocks_U16(ptr, idx1, idx2);
            break;
        case 4:
            kdi_GenMemOpsSwapBlocks_U32(ptr, idx1, idx2);
            break;
#if defined ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsSwapBlocks_U64(ptr, idx1, idx2);
            break;
#endif
        default:
            kdi_GenMemOpsSwapBlocks_Un(ptr, idx1, idx2, block_sz);
    }

    return RESULT_SUCCESS;
}


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
