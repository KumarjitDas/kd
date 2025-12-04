/**
 * @file kd_gen_mem_ops.c
 * @author Kumarjit Das
 * @version 0.0.1
 * @brief Main source file of the KD_GEN_MEM_OPS library.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 * @since 0.0.1
 */


#include "kd_version.h"

#define KD_BUILDING_LIB 1
#include "kd_platform.h"

#include "kd_fixed_width.h"
#include "kd_gen_mem_ops.h"

#include "internal/kdi_gen_mem_ops.h"


kd_bool_t
kdGenMemOpsSwapBytes(void *ptr, kd_usize_t sz, kd_usize_t idx1, kd_usize_t idx2)
{
    if (!ptr || !sz || idx1 >= sz || idx2 >= sz)
    {
        return KD_RESULT_FAILURE;
    }

    kdi_GenMemOpsSwapBlocks_U8(ptr, idx1, idx2);

    return KD_RESULT_SUCCESS;
}


kd_bool_t
kdGenMemOpsSwapBlocks(void *ptr, kd_usize_t sz, kd_usize_t block_sz, kd_usize_t idx1, kd_usize_t idx2)
{
    if (!ptr || !sz || !block_sz || idx1 >= sz || idx2 >= sz)
    {
        return KD_RESULT_FAILURE;
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
#if defined KD_ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsSwapBlocks_U64(ptr, idx1, idx2);
            break;
#endif
        default:
            kdi_GenMemOpsSwapBlocks_Un(ptr, block_sz, idx1, idx2);
    }

    return KD_RESULT_SUCCESS;
}


kd_bool_t
kdGenMemOpsReverseBytes(void *ptr, kd_usize_t sz)
{
    if (!ptr || !sz)
    {
        return KD_RESULT_FAILURE;
    }

    kdi_GenMemOpsReverseBlocks_U8(ptr, sz);

    return KD_RESULT_SUCCESS;
}


kd_bool_t
kdGenMemOpsReverseBlocks(void *ptr, kd_usize_t sz, kd_usize_t block_sz)
{
    if (!ptr || !sz || !block_sz)
    {
        return KD_RESULT_FAILURE;
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
#if defined KD_ARCH_64BIT_INT
        case 8:
            kdi_GenMemOpsReverseBlocks_U64(ptr, sz);
            break;
#endif
        default:
            kdi_GenMemOpsReverseBlocks_Un(ptr, sz, block_sz);
    }

    return KD_RESULT_SUCCESS;
}


kd_bool_t
kdGenMemOpsSetBytes(void *ptr, kd_usize_t sz, kd_byte_t val)
{
    if (!ptr || !sz)
    {
        return KD_RESULT_FAILURE;
    }

    kdi_GenMemOpsSetBlocks_U8(ptr, sz, val);

    return KD_RESULT_SUCCESS;
}


kd_bool_t
kdGenMemOpsSetBlocks(void *ptr, kd_usize_t sz, void *block, kd_usize_t block_sz)
{
    kd_u8_t  block_val_u8;
    kd_u16_t block_val_u16;
    kd_u32_t block_val_u32;
#if defined KD_ARCH_64BIT_INT
    kd_u64_t block_val_u64;
#endif

    if (!ptr || !sz || !block || !block_sz)
    {
        return KD_RESULT_FAILURE;
    }

    switch (block_sz)
    {
        case 1:
            block_val_u8 = *KD_PU8_C(block);
            kdi_GenMemOpsSetBlocks_U8(ptr, sz, block_val_u8);
            break;
        case 2:
            block_val_u16 = *KD_PU16_C(block);
            kdi_GenMemOpsSetBlocks_U16(ptr, sz, block_val_u16);
            break;
        case 4:
            block_val_u32 = *KD_PU32_C(block);
            kdi_GenMemOpsSetBlocks_U32(ptr, sz, block_val_u32);
            break;
#if defined KD_ARCH_64BIT_INT
        case 8:
            block_val_u64 = *KD_PU64_C(block);
            kdi_GenMemOpsSetBlocks_U64(ptr, sz, block_val_u64);
            break;
#endif
        default:
            kdi_GenMemOpsSetBlocks_Un(ptr, sz, block, block_sz);
    }

    return KD_RESULT_SUCCESS;
}


kd_bool_t
kdGenMemOpsCpy(void *dst, void *src, kd_usize_t sz)
{
    if (!dst || !src || !sz)
    {
        return KD_RESULT_FAILURE;
    }

    kdi_GenMemOpsCpy(dst, src, sz);

    return KD_RESULT_SUCCESS;
}


kd_bool_t
kdGenMemOpsMove(void *dst, void *src, kd_usize_t sz)
{
    if (!dst || !src || !sz)
    {
        return KD_RESULT_FAILURE;
    }

    kdi_GenMemOpsMove(dst, src, sz);

    return KD_RESULT_SUCCESS;
}


void *
kdGenMemOpsFindByte(void *ptr, kd_usize_t sz, kd_byte_t item)
{
    if (!ptr || !sz)
    {
        return kd_null;
    }

    return kdi_GenMemOpsFindBlockWithIndex_U8(kd_null, ptr, sz, item);
}


kd_bool_t
kdGenMemOpsFindByteIndex(kd_usize_t *idx_ptr, void *ptr, kd_usize_t sz, kd_byte_t item)
{
    void *found_ptr;

    if (!idx_ptr || !ptr || !sz)
    {
        return KD_RESULT_FAILURE;
    }

    found_ptr = kdi_GenMemOpsFindBlockWithIndex_U8(idx_ptr, ptr, sz, item);

    return found_ptr ? KD_RESULT_SUCCESS : KD_RESULT_FAILURE;
}


void *
kdGenMemOpsFindLastByte(void *ptr, kd_usize_t sz, kd_byte_t item)
{
    if (!ptr || !sz)
    {
        return kd_null;
    }

    return kdi_GenMemOpsFindLastBlockWithIndex_U8(kd_null, ptr, sz, item);
}


kd_bool_t
kdGenMemOpsFindLastByteIndex(kd_usize_t *idx_ptr, void *ptr, kd_usize_t sz, kd_byte_t item)
{
    void *found_ptr;

    if (!idx_ptr || !ptr || !sz)
    {
        return KD_RESULT_FAILURE;
    }

    found_ptr = kdi_GenMemOpsFindLastBlockWithIndex_U8(idx_ptr, ptr, sz, item);

    return found_ptr ? KD_RESULT_SUCCESS : KD_RESULT_FAILURE;
}


kd_usize_t
kdGenMemOpsFindAllBytes(void *dst, kd_usize_t dst_sz, void *ptr, kd_usize_t ptr_sz, kd_byte_t item)
{
    return (!dst || !ptr || !dst_sz || !ptr_sz) ? 0 : kdi_GenMemOpsFindAllBlocks_Byte(dst, dst_sz, ptr, ptr_sz, item);
}


kd_usize_t
kdGenMemOpsFindAllByteIndices(kd_usize_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, kd_byte_t item)
{
    return (!idxs || !ptr || !idxs_sz || !ptr_sz) ? 0 :
#if defined KD_ARCH_64BIT_INT
                                                  kdi_GenMemOpsFindAllBlockIndices_Byte_Idx64(idxs, idxs_sz, ptr, ptr_sz, item, kd_true);
#else
                                                  kdi_GenMemOpsFindAllBlockIndices_Byte_Idx32(idxs, idxs_sz, ptr, ptr_sz, item, kd_true);
#endif
}


kd_usize_t
kdGenMemOpsFindAllByteIndicesU8(kd_u8_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, kd_byte_t item)
{
    return (!idxs || !ptr || !idxs_sz || !ptr_sz) ? 0 : kdi_GenMemOpsFindAllBlockIndices_Byte_Idx8(idxs, idxs_sz, ptr, ptr_sz, item, kd_true);
}


kd_usize_t
kdGenMemOpsFindAllByteIndicesU16(kd_u16_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, kd_byte_t item)
{
    return (!idxs || !ptr || !idxs_sz || !ptr_sz) ? 0 : kdi_GenMemOpsFindAllBlockIndices_Byte_Idx16(idxs, idxs_sz, ptr, ptr_sz, item, kd_true);
}


kd_usize_t
kdGenMemOpsFindAllByteIndicesU32(kd_u32_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, kd_byte_t item)
{
    return (!idxs || !ptr || !idxs_sz || !ptr_sz) ? 0 : kdi_GenMemOpsFindAllBlockIndices_Byte_Idx32(idxs, idxs_sz, ptr, ptr_sz, item, kd_true);
}


#if defined KD_ARCH_64BIT_INT
kd_usize_t
kdGenMemOpsFindAllByteIndicesU64(kd_u64_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, kd_byte_t item)
{
    return (!idxs || !ptr || !idxs_sz || !ptr_sz) ? 0 : kdi_GenMemOpsFindAllBlockIndices_Byte_Idx64(idxs, idxs_sz, ptr, ptr_sz, item, kd_true);
}
#endif


void *
kdGenMemOpsFindBlock(void *ptr, kd_usize_t sz, void *block, kd_usize_t block_sz)
{
    kd_u8_t  block_val_u8;
    kd_u16_t block_val_u16;
    kd_u32_t block_val_u32;
#if defined KD_ARCH_64BIT_INT
    kd_u64_t block_val_u64;
#endif

    if (!ptr || !sz || !block || !block_sz)
    {
        return kd_null;
    }

    switch (block_sz)
    {
        case 1:
            block_val_u8 = *KD_PU8_C(block);
            return kdi_GenMemOpsFindBlockWithIndex_U8(kd_null, ptr, sz, block_val_u8);
        case 2:
            block_val_u16 = *KD_PU16_C(block);
            return kdi_GenMemOpsFindBlockWithIndex_U16(kd_null, ptr, sz, block_val_u16);
        case 4:
            block_val_u32 = *KD_PU32_C(block);
            return kdi_GenMemOpsFindBlockWithIndex_U32(kd_null, ptr, sz, block_val_u32);
#if defined KD_ARCH_64BIT_INT
        case 8:
            block_val_u64 = *KD_PU64_C(block);
            return kdi_GenMemOpsFindBlockWithIndex_U64(kd_null, ptr, sz, block_val_u64);
#endif
        default:;
    }

    return kdi_GenMemOpsFindBlockWithIndex_Un(kd_null, ptr, sz, block, block_sz);
}


kd_bool_t
kdGenMemOpsFindBlockIndex(kd_usize_t *idx_ptr, void *ptr, kd_usize_t sz, void *block, kd_usize_t block_sz)
{
    void    *found_ptr;
    kd_u8_t  block_val_u8;
    kd_u16_t block_val_u16;
    kd_u32_t block_val_u32;
#if defined KD_ARCH_64BIT_INT
    kd_u64_t block_val_u64;
#endif

    if (!idx_ptr || !ptr || !sz || !block || !block_sz)
    {
        return KD_RESULT_FAILURE;
    }

    switch (block_sz)
    {
        case 1:
            block_val_u8 = *KD_PU8_C(block);
            found_ptr    = kdi_GenMemOpsFindBlockWithIndex_U8(idx_ptr, ptr, sz, block_val_u8);
            break;
        case 2:
            block_val_u16 = *KD_PU16_C(block);
            found_ptr     = kdi_GenMemOpsFindBlockWithIndex_U16(idx_ptr, ptr, sz, block_val_u16);
            break;
        case 4:
            block_val_u32 = *KD_PU32_C(block);
            found_ptr     = kdi_GenMemOpsFindBlockWithIndex_U32(idx_ptr, ptr, sz, block_val_u32);
            break;
#if defined KD_ARCH_64BIT_INT
        case 8:
            block_val_u64 = *KD_PU64_C(block);
            found_ptr     = kdi_GenMemOpsFindBlockWithIndex_U64(idx_ptr, ptr, sz, block_val_u64);
            break;
#endif
        default:
            found_ptr = kdi_GenMemOpsFindBlockWithIndex_Un(idx_ptr, ptr, sz, block, block_sz);
    }

    return found_ptr ? KD_RESULT_SUCCESS : KD_RESULT_FAILURE;
}


void *
kdGenMemOpsFindLastBlock(void *ptr, kd_usize_t sz, void *block, kd_usize_t block_sz)
{
    kd_u8_t  block_val_u8;
    kd_u16_t block_val_u16;
    kd_u32_t block_val_u32;
#if defined KD_ARCH_64BIT_INT
    kd_u64_t block_val_u64;
#endif

    if (!ptr || !sz || !block || !block_sz)
    {
        return kd_null;
    }

    switch (block_sz)
    {
        case 1:
            block_val_u8 = *KD_PU8_C(block);
            return kdi_GenMemOpsFindLastBlockWithIndex_U8(kd_null, ptr, sz, block_val_u8);
        case 2:
            block_val_u16 = *KD_PU16_C(block);
            return kdi_GenMemOpsFindLastBlockWithIndex_U16(kd_null, ptr, sz, block_val_u16);
        case 4:
            block_val_u32 = *KD_PU32_C(block);
            return kdi_GenMemOpsFindLastBlockWithIndex_U32(kd_null, ptr, sz, block_val_u32);
#if defined KD_ARCH_64BIT_INT
        case 8:
            block_val_u64 = *KD_PU64_C(block);
            return kdi_GenMemOpsFindLastBlockWithIndex_U64(kd_null, ptr, sz, block_val_u64);
#endif
        default:;
    }

    return kdi_GenMemOpsFindLastBlockWithIndex_Un(kd_null, ptr, sz, block, block_sz);
}


kd_bool_t
kdGenMemOpsFindLastBlockIndex(kd_usize_t *idx_ptr, void *ptr, kd_usize_t sz, void *block, kd_usize_t block_sz)
{
    void    *found_ptr;
    kd_u8_t  block_val_u8;
    kd_u16_t block_val_u16;
    kd_u32_t block_val_u32;
#if defined KD_ARCH_64BIT_INT
    kd_u64_t block_val_u64;
#endif

    if (!idx_ptr || !ptr || !sz || !block || !block_sz)
    {
        return KD_RESULT_FAILURE;
    }

    switch (block_sz)
    {
        case 1:
            block_val_u8 = *KD_PU8_C(block);
            found_ptr    = kdi_GenMemOpsFindLastBlockWithIndex_U8(idx_ptr, ptr, sz, block_val_u8);
            break;
        case 2:
            block_val_u16 = *KD_PU16_C(block);
            found_ptr     = kdi_GenMemOpsFindLastBlockWithIndex_U16(idx_ptr, ptr, sz, block_val_u16);
            break;
        case 4:
            block_val_u32 = *KD_PU32_C(block);
            found_ptr     = kdi_GenMemOpsFindLastBlockWithIndex_U32(idx_ptr, ptr, sz, block_val_u32);
            break;
#if defined KD_ARCH_64BIT_INT
        case 8:
            block_val_u64 = *KD_PU64_C(block);
            found_ptr     = kdi_GenMemOpsFindLastBlockWithIndex_U64(idx_ptr, ptr, sz, block_val_u64);
            break;
#endif
        default:
            found_ptr = kdi_GenMemOpsFindLastBlockWithIndex_Un(idx_ptr, ptr, sz, block, block_sz);
    }

    return found_ptr ? KD_RESULT_SUCCESS : KD_RESULT_FAILURE;
}


kd_usize_t
kdGenMemOpsFindAllBlocks(void *dst, kd_usize_t dst_sz, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz)
{
    kd_u8_t  block_val_u8;
    kd_u16_t block_val_u16;
    kd_u32_t block_val_u32;
#if defined KD_ARCH_64BIT_INT
    kd_u64_t block_val_u64;
#endif

    if (!dst || !ptr || !block || !dst_sz || !ptr_sz || !block_sz)
    {
        return 0;
    }

    switch (block_sz)
    {
        case 1:
            block_val_u8 = *KD_PU8_C(block);
            return kdi_GenMemOpsFindAllBlocks_U8(dst, dst_sz, ptr, ptr_sz, block_val_u8);
        case 2:
            block_val_u16 = *KD_PU16_C(block);
            return kdi_GenMemOpsFindAllBlocks_U16(dst, dst_sz, ptr, ptr_sz, block_val_u16);
        case 4:
            block_val_u32 = *KD_PU32_C(block);
            return kdi_GenMemOpsFindAllBlocks_U32(dst, dst_sz, ptr, ptr_sz, block_val_u32);
#if defined KD_ARCH_64BIT_INT
        case 8:
            block_val_u64 = *KD_PU64_C(block);
            return kdi_GenMemOpsFindAllBlocks_U64(dst, dst_sz, ptr, ptr_sz, block_val_u64);
#endif
        default:;
    }

    return kdi_GenMemOpsFindAllBlocks_Un(dst, dst_sz, ptr, ptr_sz, block, block_sz);
}


kd_usize_t
kdGenMemOpsFindAllBlockIndices(kd_usize_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz)
{
    kd_u8_t  block_val_u8;
    kd_u16_t block_val_u16;
    kd_u32_t block_val_u32;
#if defined KD_ARCH_64BIT_INT
    kd_u64_t block_val_u64;
#endif

    if (!idxs || !idxs_sz || !ptr || !ptr_sz || !block || !block_sz)
    {
        return 0;
    }

#if defined KD_ARCH_64BIT_INT
    switch (block_sz)
    {
        case 1:
            block_val_u8 = *KD_PU8_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U8_Idx64(idxs, idxs_sz, ptr, ptr_sz, block_val_u8, kd_false);
        case 2:
            block_val_u16 = *KD_PU16_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U16_Idx64(idxs, idxs_sz, ptr, ptr_sz, block_val_u16, kd_false);
        case 4:
            block_val_u32 = *KD_PU32_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U32_Idx64(idxs, idxs_sz, ptr, ptr_sz, block_val_u32, kd_false);
        case 8:
            block_val_u64 = *KD_PU64_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U64_Idx64(idxs, idxs_sz, ptr, ptr_sz, block_val_u64, kd_false);
        default:;
    }

    return kdi_GenMemOpsFindAllBlockIndices_Un_Idx64(idxs, idxs_sz, ptr, ptr_sz, block, block_sz, kd_false);
#else
    switch (block_sz)
    {
        case 1:
            block_val_u8 = *KD_PU8_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U8_Idx32(idxs, idxs_sz, ptr, ptr_sz, block_val_u8, kd_false);
        case 2:
            block_val_u16 = *KD_PU16_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U16_Idx32(idxs, idxs_sz, ptr, ptr_sz, block_val_u16, kd_false);
        case 4:
            block_val_u32 = *KD_PU32_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U32_Idx32(idxs, idxs_sz, ptr, ptr_sz, block_val_u32, kd_false);
        default:;
    }

    return kdi_GenMemOpsFindAllBlockIndices_Un_Idx32(idxs, idxs_sz, ptr, ptr_sz, block, block_sz, kd_false);
#endif
}


kd_usize_t
kdGenMemOpsFindAllBlockIndicesU8(kd_u8_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz)
{
    kd_u8_t  block_val_u8;
    kd_u16_t block_val_u16;
    kd_u32_t block_val_u32;
#if defined KD_ARCH_64BIT_INT
    kd_u64_t block_val_u64;
#endif

    if (!idxs || !idxs_sz || !ptr || !ptr_sz || !block || !block_sz)
    {
        return 0;
    }

    switch (block_sz)
    {
        case 1:
            block_val_u8 = *KD_PU8_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U8_Idx8(idxs, idxs_sz, ptr, ptr_sz, block_val_u8, kd_false);
        case 2:
            block_val_u16 = *KD_PU16_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U16_Idx8(idxs, idxs_sz, ptr, ptr_sz, block_val_u16, kd_false);
        case 4:
            block_val_u32 = *KD_PU32_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U32_Idx8(idxs, idxs_sz, ptr, ptr_sz, block_val_u32, kd_false);
#if defined KD_ARCH_64BIT_INT
        case 8:
            block_val_u64 = *KD_PU64_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U64_Idx8(idxs, idxs_sz, ptr, ptr_sz, block_val_u64, kd_false);
#endif
        default:;
    }

    return kdi_GenMemOpsFindAllBlockIndices_Un_Idx8(idxs, idxs_sz, ptr, ptr_sz, block, block_sz, kd_false);
}


kd_usize_t
kdGenMemOpsFindAllBlockIndicesU16(kd_u16_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz)
{
    kd_u8_t  block_val_u8;
    kd_u16_t block_val_u16;
    kd_u32_t block_val_u32;
#if defined KD_ARCH_64BIT_INT
    kd_u64_t block_val_u64;
#endif

    if (!idxs || !idxs_sz || !ptr || !ptr_sz || !block || !block_sz)
    {
        return 0;
    }

    switch (block_sz)
    {
        case 1:
            block_val_u8 = *KD_PU8_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U8_Idx16(idxs, idxs_sz, ptr, ptr_sz, block_val_u8, kd_false);
        case 2:
            block_val_u16 = *KD_PU16_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U16_Idx16(idxs, idxs_sz, ptr, ptr_sz, block_val_u16, kd_false);
        case 4:
            block_val_u32 = *KD_PU32_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U32_Idx16(idxs, idxs_sz, ptr, ptr_sz, block_val_u32, kd_false);
#if defined KD_ARCH_64BIT_INT
        case 8:
            block_val_u64 = *KD_PU64_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U64_Idx16(idxs, idxs_sz, ptr, ptr_sz, block_val_u64, kd_false);
#endif
        default:;
    }

    return kdi_GenMemOpsFindAllBlockIndices_Un_Idx16(idxs, idxs_sz, ptr, ptr_sz, block, block_sz, kd_false);
}


kd_usize_t
kdGenMemOpsFindAllBlockIndicesU32(kd_u32_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz)
{
    kd_u8_t  block_val_u8;
    kd_u16_t block_val_u16;
    kd_u32_t block_val_u32;
#if defined KD_ARCH_64BIT_INT
    kd_u64_t block_val_u64;
#endif

    if (!idxs || !idxs_sz || !ptr || !ptr_sz || !block || !block_sz)
    {
        return 0;
    }

    switch (block_sz)
    {
        case 1:
            block_val_u8 = *KD_PU8_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U8_Idx32(idxs, idxs_sz, ptr, ptr_sz, block_val_u8, kd_false);
        case 2:
            block_val_u16 = *KD_PU16_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U16_Idx32(idxs, idxs_sz, ptr, ptr_sz, block_val_u16, kd_false);
        case 4:
            block_val_u32 = *KD_PU32_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U32_Idx32(idxs, idxs_sz, ptr, ptr_sz, block_val_u32, kd_false);
#if defined KD_ARCH_64BIT_INT
        case 8:
            block_val_u64 = *KD_PU64_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U64_Idx32(idxs, idxs_sz, ptr, ptr_sz, block_val_u64, kd_false);
#endif
        default:;
    }

    return kdi_GenMemOpsFindAllBlockIndices_Un_Idx32(idxs, idxs_sz, ptr, ptr_sz, block, block_sz, kd_false);
}


#if defined KD_ARCH_64BIT_INT
kd_usize_t
kdGenMemOpsFindAllBlockIndicesU64(kd_u64_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz)
{
    kd_u8_t  block_val_u8;
    kd_u16_t block_val_u16;
    kd_u32_t block_val_u32;
    kd_u64_t block_val_u64;

    if (!idxs || !idxs_sz || !ptr || !ptr_sz || !block || !block_sz)
    {
        return 0;
    }

    switch (block_sz)
    {
        case 1:
            block_val_u8 = *KD_PU8_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U8_Idx64(idxs, idxs_sz, ptr, ptr_sz, block_val_u8, kd_false);
        case 2:
            block_val_u16 = *KD_PU16_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U16_Idx64(idxs, idxs_sz, ptr, ptr_sz, block_val_u16, kd_false);
        case 4:
            block_val_u32 = *KD_PU32_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U32_Idx64(idxs, idxs_sz, ptr, ptr_sz, block_val_u32, kd_false);
        case 8:
            block_val_u64 = *KD_PU64_C(block);
            return kdi_GenMemOpsFindAllBlockIndices_U64_Idx64(idxs, idxs_sz, ptr, ptr_sz, block_val_u64, kd_false);
        default:;
    }

    return kdi_GenMemOpsFindAllBlockIndices_Un_Idx64(idxs, idxs_sz, ptr, ptr_sz, block, block_sz, kd_false);
}
#endif


kd_word_t
kdGenMemOpsCmp(void *ptr1, void *ptr2, kd_usize_t sz)
{
    kd_byte_t *src1_ptr, *src2_ptr;

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


kd_bool_t
kdGenMemOpsCat(void *dst, kd_usize_t sz, void *src1, kd_usize_t sz1, void *src2, kd_usize_t sz2)
{
    kd_byte_t *dst_ptr, *src1_ptr, *src2_ptr;

    if (!dst || !src1 || !src2 || !sz || !sz1 || !sz2)
    {
        return KD_RESULT_FAILURE;
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

    return KD_RESULT_SUCCESS;
}
