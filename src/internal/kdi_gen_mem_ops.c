/**
 * @file kdi_gen_mem_ops.c
 * @author Kumarjit Das
 * @version 0.0.1
 * @brief Main source file of the KDI_GEN_MEM_OPS library (internal).
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 * @since 0.0.1
 */


#define KD_BUILDING_LIB 1
#include "../../include/kd/platform.h"

#include "../../include/kd/fixed_width.h"
#include "kdi_gen_mem_ops.h"


void
kdi_GenMemOpsSwapBlocks_U8(kd_u8_t *ptr, kd_usize_t idx1, kd_usize_t idx2)
{
    kd_u8_t *ptr1  = ptr + idx1;
    kd_u8_t  temp  = *ptr1;

    ptr           += idx2;
    *ptr1          = *ptr;
    *ptr           = temp;
}


void
kdi_GenMemOpsSwapBlocks_U16(kd_u16_t *ptr, kd_usize_t idx1, kd_usize_t idx2)
{
    kd_u16_t *ptr1 = (kd_u16_t *)((kd_u8_t *)ptr + idx1);
    kd_u16_t  temp = *ptr1;

    ptr            = (kd_u16_t *)((kd_u8_t *)ptr + idx2);
    *ptr1          = *ptr;
    *ptr           = temp;
}


void
kdi_GenMemOpsSwapBlocks_U32(kd_u32_t *ptr, kd_usize_t idx1, kd_usize_t idx2)
{
    kd_u32_t *ptr1 = (kd_u32_t *)((kd_u8_t *)ptr + idx1);
    kd_u32_t  temp = *ptr1;

    ptr            = (kd_u32_t *)((kd_u8_t *)ptr + idx2);
    *ptr1          = *ptr;
    *ptr           = temp;
}


#if defined KD_ARCH_64BIT_INT
void
kdi_GenMemOpsSwapBlocks_U64(kd_u64_t *ptr, kd_usize_t idx1, kd_usize_t idx2)
{
    kd_u64_t *ptr1 = (kd_u64_t *)((kd_u8_t *)ptr + idx1);
    kd_u64_t  temp = *ptr1;

    ptr            = (kd_u64_t *)((kd_u8_t *)ptr + idx2);
    *ptr1          = *ptr;
    *ptr           = temp;
}
#endif


void
kdi_GenMemOpsSwapBlocks_Un(void *ptr, kd_usize_t block_sz, kd_usize_t idx1, kd_usize_t idx2)
{
    kd_u8_t *ptr1 = (kd_byte_t *)ptr + idx1;
    kd_u8_t *ptr2 = (kd_byte_t *)ptr + idx2;
    kd_u8_t  temp;

    while (block_sz--)
    {
        temp  = *ptr1;
        *ptr1 = *ptr2;
        *ptr2 = temp;

        ++ptr1;
        ++ptr2;
    }
}


void
kdi_GenMemOpsReverseBlocks_U8(kd_u8_t *ptr, kd_usize_t sz)
{
    kd_u8_t *end = ptr + sz;
    kd_u8_t  temp;

    while (sz-- && ptr < end)
    {
        --end;

        temp = *ptr;
        *ptr = *end;
        *end = temp;

        ++ptr;
    }
}


void
kdi_GenMemOpsReverseBlocks_U16(kd_u16_t *ptr, kd_usize_t sz)
{
    kd_u16_t *end = (kd_u16_t *)((kd_u8_t *)ptr + sz);
    kd_u16_t  temp;

    while (sz-- && ptr < end)
    {
        --end;

        temp = *ptr;
        *ptr = *end;
        *end = temp;

        ++ptr;
    }
}


void
kdi_GenMemOpsReverseBlocks_U32(kd_u32_t *ptr, kd_usize_t sz)
{
    kd_u32_t *end = (kd_u32_t *)((kd_u8_t *)ptr + sz);
    kd_u32_t  temp;

    while (sz-- && ptr < end)
    {
        --end;

        temp = *ptr;
        *ptr = *end;
        *end = temp;

        ++ptr;
    }
}


#if defined KD_ARCH_64BIT_INT
void
kdi_GenMemOpsReverseBlocks_U64(kd_u64_t *ptr, kd_usize_t sz)
{
    kd_u64_t *end = (kd_u64_t *)((kd_u8_t *)ptr + sz);
    kd_u64_t  temp;

    while (sz-- && ptr < end)
    {
        --end;

        temp = *ptr;
        *ptr = *end;
        *end = temp;

        ++ptr;
    }
}
#endif


void
kdi_GenMemOpsReverseBlocks_Un(void *ptr, kd_usize_t sz, kd_usize_t block_sz)
{
    kd_u8_t   *begin = ptr, *end = begin + sz, *temp_end, temp;
    kd_usize_t temp_block_sz;

    while (sz-- && begin < end)
    {
        end           -= block_sz;
        temp_end       = end;
        temp_block_sz  = block_sz;

        while (temp_block_sz--)
        {
            temp      = *begin;
            *begin    = *temp_end;
            *temp_end = temp;

            ++begin;
            ++temp_end;
        }
    }
}


void
kdi_GenMemOpsSetBlocks_U8(kd_u8_t *ptr, kd_usize_t sz, kd_u8_t val)
{
    while (sz--)
    {
        *ptr = val;
        ++ptr;
    }
}


void
kdi_GenMemOpsSetBlocks_U16(kd_u16_t *ptr, kd_usize_t sz, kd_u16_t val)
{
    while (sz)
    {
        *ptr = val;
        ++ptr;
        sz -= KD_SZ_U16;
    }
}


void
kdi_GenMemOpsSetBlocks_U32(kd_u32_t *ptr, kd_usize_t sz, kd_u32_t val)
{
    while (sz)
    {
        *ptr = val;
        ++ptr;
        sz -= KD_SZ_U32;
    }
}


#if defined KD_ARCH_64BIT_INT
void
kdi_GenMemOpsSetBlocks_U64(kd_u64_t *ptr, kd_usize_t sz, kd_u64_t val)
{
    while (sz)
    {
        *ptr = val;
        ++ptr;
        sz -= KD_SZ_U64;
    }
}
#endif


void
kdi_GenMemOpsSetBlocks_Un(void *ptr, kd_usize_t sz, void *block, kd_usize_t block_sz)
{
    kd_byte_t *dst_ptr, *block_ptr;
    kd_usize_t i;

    dst_ptr = ptr;

    while (sz)
    {
        block_ptr = block;
        i         = block_sz;

        while (i-- && sz--)
        {
            *dst_ptr = *block_ptr;
            ++dst_ptr;
            ++block_ptr;
        }
    }
}


void
kdi_GenMemOpsCpy(kd_byte_t *dst, kd_byte_t *src, kd_usize_t sz)
{
    while (sz--)
    {
        *dst = *src;
        ++dst;
        ++src;
    }
}


void
kdi_GenMemOpsMove(kd_byte_t *dst, kd_byte_t *src, kd_usize_t sz)
{
    if (dst == src)
    {
        return;
    }

    if (dst < src)
    {
        while (sz--)
        {
            *dst = *src;
            ++dst;
            ++src;
        }
        return;
    }

    dst += sz;
    src += sz;

    while (sz--)
    {
        --dst;
        --src;
        *dst = *src;
    }
}


void *
kdi_GenMemOpsFindBlockWithIndex_U8(kd_usize_t *idx_ptr, kd_u8_t *ptr, kd_usize_t sz, kd_u8_t val)
{
    kd_usize_t idx = 0;

    while (sz--)
    {
        if (*ptr == val)
        {
            if (idx_ptr)
            {
                *idx_ptr = idx;
            }
            return ptr;
        }

        ++ptr;
        ++idx;
    }

    return kd_null;
}


void *
kdi_GenMemOpsFindBlockWithIndex_U16(kd_usize_t *idx_ptr, kd_u16_t *ptr, kd_usize_t sz, kd_u16_t val)
{
    kd_usize_t idx = 0;

    while (sz)
    {
        if (*ptr == val)
        {
            if (idx_ptr)
            {
                *idx_ptr = idx;
            }
            return ptr;
        }

        ++ptr;
        idx += KD_SZ_U16;
        sz  -= KD_SZ_U16;
    }

    return kd_null;
}


void *
kdi_GenMemOpsFindBlockWithIndex_U32(kd_usize_t *idx_ptr, kd_u32_t *ptr, kd_usize_t sz, kd_u32_t val)
{
    kd_usize_t idx = 0;

    while (sz)
    {
        if (*ptr == val)
        {
            if (idx_ptr)
            {
                *idx_ptr = idx;
            }
            return ptr;
        }

        ++ptr;
        idx += KD_SZ_U32;
        sz  -= KD_SZ_U32;
    }

    return kd_null;
}


#if defined KD_ARCH_64BIT_INT
void *
kdi_GenMemOpsFindBlockWithIndex_U64(kd_usize_t *idx_ptr, kd_u64_t *ptr, kd_usize_t sz, kd_u64_t val)
{
    kd_usize_t idx = 0;

    while (sz)
    {
        if (*ptr == val)
        {
            if (idx_ptr)
            {
                *idx_ptr = idx;
            }
            return ptr;
        }

        ++ptr;
        idx += KD_SZ_U64;
        sz  -= KD_SZ_U64;
    }

    return kd_null;
}
#endif


void *
kdi_GenMemOpsFindBlockWithIndex_Un(kd_usize_t *idx_ptr, void *ptr, kd_usize_t sz, void *block, kd_usize_t block_sz)
{
    kd_byte_t *src_ptr = ptr, *temp_src_ptr, *block_ptr;
    kd_usize_t i, idx = 0, temp_sz, match_cnt;

    while (sz)
    {
        temp_src_ptr = src_ptr;
        block_ptr    = block;
        temp_sz      = sz;
        i            = block_sz;
        match_cnt    = 0;

        while (i-- && temp_sz--)
        {
            if (*temp_src_ptr != *block_ptr)
            {
                break;
            }

            ++temp_src_ptr;
            ++block_ptr;
            ++match_cnt;
        }

        if (match_cnt == block_sz)
        {
            if (idx_ptr)
            {
                *idx_ptr = idx;
            }
            return src_ptr;
        }

        idx     += block_sz;
        src_ptr += block_sz;
        sz      -= block_sz;
    }

    return kd_null;
}


void *
kdi_GenMemOpsFindLastBlockWithIndex_U8(kd_usize_t *idx_ptr, kd_u8_t *ptr, kd_usize_t sz, kd_u8_t val)
{
    ptr += sz;

    while (sz--)
    {
        --ptr;

        if (*ptr == val)
        {
            if (idx_ptr)
            {
                *idx_ptr = sz;
            }
            return ptr;
        }
    }

    return kd_null;
}


void *
kdi_GenMemOpsFindLastBlockWithIndex_U16(kd_usize_t *idx_ptr, kd_u16_t *ptr, kd_usize_t sz, kd_u16_t val)
{
    ptr = (kd_u16_t *)((kd_byte_t *)ptr + sz);

    while (sz)
    {
        ptr  = (kd_u16_t *)((kd_byte_t *)ptr - KD_SZ_U16);
        sz  -= KD_SZ_U16;

        if (*ptr == val)
        {
            if (idx_ptr)
            {
                *idx_ptr = sz;
            }
            return ptr;
        }
    }

    return kd_null;
}


void *
kdi_GenMemOpsFindLastBlockWithIndex_U32(kd_usize_t *idx_ptr, kd_u32_t *ptr, kd_usize_t sz, kd_u32_t val)
{
    ptr = (kd_u32_t *)((kd_byte_t *)ptr + sz);

    while (sz)
    {
        ptr  = (kd_u32_t *)((kd_byte_t *)ptr - KD_SZ_U32);
        sz  -= KD_SZ_U32;

        if (*ptr == val)
        {
            if (idx_ptr)
            {
                *idx_ptr = sz;
            }
            return ptr;
        }
    }

    return kd_null;
}


#if defined KD_ARCH_64BIT_INT
void *
kdi_GenMemOpsFindLastBlockWithIndex_U64(kd_usize_t *idx_ptr, kd_u64_t *ptr, kd_usize_t sz, kd_u64_t val)
{
    ptr = (kd_u64_t *)((kd_byte_t *)ptr + sz);

    while (sz)
    {
        ptr  = (kd_u64_t *)((kd_byte_t *)ptr - KD_SZ_U64);
        sz  -= KD_SZ_U64;

        if (*ptr == val)
        {
            if (idx_ptr)
            {
                *idx_ptr = sz;
            }
            return ptr;
        }
    }

    return kd_null;
}
#endif


void *
kdi_GenMemOpsFindLastBlockWithIndex_Un(kd_usize_t *idx_ptr, void *ptr, kd_usize_t sz, void *block, kd_usize_t block_sz)
{
    kd_byte_t *src_ptr = (kd_byte_t *)ptr + sz, *temp_src_ptr, *block_ptr;
    kd_usize_t i, temp_sz, match_cnt;

    while (sz)
    {
        src_ptr      -= block_sz;
        sz           -= block_sz;

        temp_src_ptr  = src_ptr;
        block_ptr     = block;
        temp_sz       = sz;
        i             = block_sz;
        match_cnt     = 0;

        while (i-- && temp_sz--)
        {
            if (*temp_src_ptr != *block_ptr)
            {
                break;
            }

            ++temp_src_ptr;
            ++block_ptr;
            ++match_cnt;
        }

        if (match_cnt == block_sz)
        {
            if (idx_ptr)
            {
                *idx_ptr = sz;
            }
            return src_ptr;
        }
    }

    return kd_null;
}


void *
kdi_GenMemOpsFindBlockWithIndex_Struct(kd_usize_t *idx_ptr, void *ptr, kd_usize_t sz, void *block, kd_usize_t block_sz, kd_bool_t (*matcher)(void *curr_ptr, void *sz_ptr, void *block, void *block_sz_ptr, void *curr_idx_ptr))
{
    kd_byte_t *src_ptr = ptr;
    kd_usize_t i, idx = 0, orig_sz = sz, temp_sz, temp_block_sz, temp_idx;

    while (sz)
    {
        temp_sz       = orig_sz;
        temp_block_sz = block_sz;
        temp_idx      = idx;

        if (matcher(src_ptr, &temp_sz, block, &temp_block_sz, &temp_idx))
        {
            if (idx_ptr)
            {
                *idx_ptr = idx;
            }
            return src_ptr;
        }

        idx     += block_sz;
        src_ptr += block_sz;
        sz      -= block_sz;
    }

    return kd_null;
}


void *
kdi_GenMemOpsFindLastBlockWithIndex_Struct(kd_usize_t *idx_ptr, void *ptr, kd_usize_t sz, void *block, kd_usize_t block_sz, kd_bool_t (*matcher)(void *curr_ptr, void *sz_ptr, void *block, void *block_sz_ptr, void *curr_idx_ptr))
{
    kd_byte_t *src_ptr = (kd_byte_t *)ptr + sz;
    kd_usize_t i, orig_sz = sz, temp_sz, temp_block_sz, temp_idx;

    while (sz)
    {
        src_ptr       -= block_sz;
        sz            -= block_sz;

        temp_sz        = orig_sz;
        temp_block_sz  = block_sz;
        temp_idx       = sz;

        if (matcher(src_ptr, &temp_sz, block, &temp_block_sz, &temp_idx))
        {
            if (idx_ptr)
            {
                *idx_ptr = sz;
            }
            return src_ptr;
        }
    }

    return kd_null;
}


kd_usize_t
kdi_GenMemOpsGetBlocksCount_U8(kd_u8_t *ptr, kd_usize_t sz, kd_u8_t val)
{
    kd_usize_t count = 0;

    while (sz--)
    {
        count += *ptr == val;
        ++ptr;
    }

    return count;
}


kd_usize_t
kdi_GenMemOpsGetBlocksCount_U16(kd_u16_t *ptr, kd_usize_t sz, kd_u16_t val)
{
    kd_usize_t count = 0;

    while (sz)
    {
        count += *ptr == val;
        sz    -= KD_SZ_U16;
        ++ptr;
    }

    return count;
}


kd_usize_t
kdi_GenMemOpsGetBlocksCount_U32(kd_u32_t *ptr, kd_usize_t sz, kd_u32_t val)
{
    kd_usize_t count = 0;

    while (sz)
    {
        count += *ptr == val;
        sz    -= KD_SZ_U32;
        ++ptr;
    }

    return count;
}


#if defined KD_ARCH_64BIT_INT
kd_usize_t
kdi_GenMemOpsGetBlocksCount_U64(kd_u64_t *ptr, kd_usize_t sz, kd_u64_t val)
{
    kd_usize_t count = 0;

    while (sz)
    {
        count += *ptr == val;
        sz    -= KD_SZ_U64;
        ++ptr;
    }

    return count;
}
#endif


kd_usize_t
kdi_GenMemOpsGetBlocksCount_Un(void *ptr, kd_usize_t sz, void *block, kd_usize_t block_sz)
{
    kd_byte_t *src_ptr = ptr, *temp_src_ptr, *block_ptr;
    kd_usize_t i, count = 0, temp_sz, match_cnt;

    while (sz)
    {
        temp_src_ptr = src_ptr;
        block_ptr    = block;
        temp_sz      = sz;
        i            = block_sz;
        match_cnt    = 0;

        while (i-- && temp_sz--)
        {
            if (*temp_src_ptr != *block_ptr)
            {
                break;
            }

            ++temp_src_ptr;
            ++block_ptr;
            ++match_cnt;
        }

        count   += match_cnt == block_sz;
        src_ptr += block_sz;
        sz      -= block_sz;
    }

    return count;
}


kd_usize_t
kdi_GenMemOpsFindAllBlocks_U8(void *dst, kd_usize_t dst_sz, kd_u8_t *ptr, kd_usize_t ptr_sz, kd_u8_t val)
{
    kd_u8_t  **dst_adr   = dst;
    kd_usize_t found_cnt = 0;

    while (ptr_sz-- && dst_sz)
    {
        if (*ptr == val)
        {
            *dst_adr = ptr;
            ++dst_adr;
            ++found_cnt;
            dst_sz -= KD_SZ_PTR;
        }

        ++ptr;
    }

    return found_cnt;
}


kd_usize_t
kdi_GenMemOpsFindAllBlocks_U16(void *dst, kd_usize_t dst_sz, kd_u16_t *ptr, kd_usize_t ptr_sz, kd_u16_t val)
{
    kd_u16_t **dst_adr   = dst;
    kd_usize_t found_cnt = 0;

    while (ptr_sz && dst_sz)
    {
        if (*ptr == val)
        {
            *dst_adr = ptr;
            ++dst_adr;
            ++found_cnt;
            dst_sz -= KD_SZ_PTR;
        }

        ++ptr;
        ptr_sz -= KD_SZ_U16;
    }

    return found_cnt;
}


kd_usize_t
kdi_GenMemOpsFindAllBlocks_U32(void *dst, kd_usize_t dst_sz, kd_u32_t *ptr, kd_usize_t ptr_sz, kd_u32_t val)
{
    kd_u32_t **dst_adr   = dst;
    kd_usize_t found_cnt = 0;

    while (ptr_sz && dst_sz)
    {
        if (*ptr == val)
        {
            *dst_adr = ptr;
            ++dst_adr;
            ++found_cnt;
            dst_sz -= KD_SZ_PTR;
        }

        ++ptr;
        ptr_sz -= KD_SZ_U32;
    }

    return found_cnt;
}


#if defined KD_ARCH_64BIT_INT
kd_usize_t
kdi_GenMemOpsFindAllBlocks_U64(void *dst, kd_usize_t dst_sz, kd_u64_t *ptr, kd_usize_t ptr_sz, kd_u64_t val)
{
    kd_u64_t **dst_adr   = dst;
    kd_usize_t found_cnt = 0;

    while (ptr_sz && dst_sz)
    {
        if (*ptr == val)
        {
            *dst_adr = ptr;
            ++dst_adr;
            ++found_cnt;
            dst_sz -= KD_SZ_PTR;
        }

        ++ptr;
        ptr_sz -= KD_SZ_U64;
    }

    return found_cnt;
}
#endif


kd_usize_t
kdi_GenMemOpsFindAllBlocks_Un(void *dst, kd_usize_t dst_sz, kd_byte_t *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz)
{
    kd_byte_t **dst_adr   = dst, *block_ptr;
    kd_usize_t  found_cnt = 0, match_cnt, temp_block_sz;

    while (ptr_sz && dst_sz)
    {
        ptr_sz        -= block_sz;
        block_ptr      = block;
        temp_block_sz  = block_sz;
        match_cnt      = 0;

        while (temp_block_sz--)
        {
            match_cnt += *ptr == *block_ptr;
            ++ptr;
            ++block_ptr;
        }

        if (match_cnt == block_sz)
        {
            *dst_adr = ptr;
            ++dst_adr;
            ++found_cnt;
            dst_sz -= KD_SZ_USIZE;
        }
    }

    return found_cnt;
}


kd_usize_t
kdi_GenMemOpsFindAllBlocks_Struct(void *dst, kd_usize_t dst_sz, kd_byte_t *ptr, kd_usize_t ptr_sz, void *block, kd_usize_t block_sz, kd_bool_t (*matcher)(void *curr_ptr, void *sz_ptr, void *block, void *block_sz_ptr, void *curr_idx_ptr))
{
    kd_byte_t **dst_adr = dst, *src_ptr = ptr;
    kd_usize_t  idx = 0, found_cnt = 0, orig_ptr_sz = ptr_sz, temp_sz, temp_block_sz, temp_idx;

    while (ptr_sz && dst_sz)
    {
        temp_sz        = orig_ptr_sz;
        temp_block_sz  = block_sz;
        temp_idx       = orig_ptr_sz - ptr_sz;

        ptr_sz        -= block_sz;

        if (matcher(src_ptr, &temp_sz, block, &temp_block_sz, &temp_idx))
        {
            *dst_adr = src_ptr;
            ++dst_adr;
            ++found_cnt;
            dst_sz -= KD_SZ_USIZE;
        }

        src_ptr += block_sz;
    }

    return found_cnt;
}


kd_usize_t
kdi_GenMemOpsFindAllBlockIndices_U8_Idx8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_u8_t *ptr, kd_usize_t ptr_sz, kd_u8_t val, kd_bool_t use_block_idx)
{
    kd_u8_t idx = 0, found_cnt = 0;

    (void)use_block_idx;

    while (ptr_sz-- && idxs_sz)
    {
        if (*ptr == val)
        {
            *idxs = idx;
            ++idxs;
            ++found_cnt;
            --idxs_sz;
        }

        ++ptr;
        ++idx;
    }

    return KD_USIZE_C(found_cnt);
}


kd_usize_t
kdi_GenMemOpsFindAllBlockIndices_U8_Idx16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_u8_t *ptr, kd_usize_t ptr_sz, kd_u8_t val, kd_bool_t use_block_idx)
{
    kd_u16_t idx = 0, found_cnt = 0;

    (void)use_block_idx;

    while (ptr_sz-- && idxs_sz)
    {
        if (*ptr == val)
        {
            *idxs = idx;
            ++idxs;
            ++found_cnt;
            idxs_sz -= KD_SZ_U16;
        }

        ++ptr;
        ++idx;
    }

    return KD_USIZE_C(found_cnt);
}


kd_usize_t
kdi_GenMemOpsFindAllBlockIndices_U8_Idx32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_u8_t *ptr, kd_usize_t ptr_sz, kd_u8_t val, kd_bool_t use_block_idx)
{
    kd_u32_t idx = 0, found_cnt = 0;

    (void)use_block_idx;

    while (ptr_sz-- && idxs_sz)
    {
        if (*ptr == val)
        {
            *idxs = idx;
            ++idxs;
            ++found_cnt;
            idxs_sz -= KD_SZ_U32;
        }

        ++ptr;
        ++idx;
    }

    return KD_USIZE_C(found_cnt);
}


#if defined KD_ARCH_64BIT_INT
kd_usize_t
kdi_GenMemOpsFindAllBlockIndices_U8_Idx64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_u8_t *ptr, kd_usize_t ptr_sz, kd_u8_t val, kd_bool_t use_block_idx)
{
    kd_u64_t idx = 0, found_cnt = 0;

    (void)use_block_idx;

    while (ptr_sz-- && idxs_sz)
    {
        if (*ptr == val)
        {
            *idxs = idx;
            ++idxs;
            ++found_cnt;
            idxs_sz -= KD_SZ_U64;
        }

        ++ptr;
        ++idx;
    }

    return KD_USIZE_C(found_cnt);
}
#endif


kd_usize_t
kdi_GenMemOpsFindAllBlockIndices_U16_Idx8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_u16_t *ptr, kd_usize_t ptr_sz, kd_u16_t val, kd_bool_t use_block_idx)
{
    kd_u8_t idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : KD_SZ_U16;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz -= KD_SZ_U16;

        if (*ptr == val)
        {
            *idxs = idx;
            ++found_cnt;
            ++idxs;
            --idxs_sz;
        }

        ++ptr;
        idx += inc;
    }

    return KD_USIZE_C(found_cnt);
}


kd_usize_t
kdi_GenMemOpsFindAllBlockIndices_U16_Idx16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_u16_t *ptr, kd_usize_t ptr_sz, kd_u16_t val, kd_bool_t use_block_idx)
{
    kd_u16_t idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : KD_SZ_U16;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz -= KD_SZ_U16;

        if (*ptr == val)
        {
            *idxs = idx;
            ++idxs;
            ++found_cnt;
            idxs_sz -= KD_SZ_U16;
        }

        ++ptr;
        idx += inc;
    }

    return KD_USIZE_C(found_cnt);
}


kd_usize_t
kdi_GenMemOpsFindAllBlockIndices_U16_Idx32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_u16_t *ptr, kd_usize_t ptr_sz, kd_u16_t val, kd_bool_t use_block_idx)
{
    kd_u32_t idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : KD_SZ_U16;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz -= KD_SZ_U16;

        if (*ptr == val)
        {
            *idxs = idx;
            ++idxs;
            ++found_cnt;
            idxs_sz -= KD_SZ_U32;
        }

        ++ptr;
        idx += inc;
    }

    return KD_USIZE_C(found_cnt);
}


#if defined KD_ARCH_64BIT_INT
kd_usize_t
kdi_GenMemOpsFindAllBlockIndices_U16_Idx64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_u16_t *ptr, kd_usize_t ptr_sz, kd_u16_t val, kd_bool_t use_block_idx)
{
    kd_u64_t idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : KD_SZ_U16;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz -= KD_SZ_U16;

        if (*ptr == val)
        {
            *idxs = idx;
            ++idxs;
            ++found_cnt;
            idxs_sz -= KD_SZ_U64;
        }

        ++ptr;
        idx += inc;
    }

    return KD_USIZE_C(found_cnt);
}
#endif


kd_usize_t
kdi_GenMemOpsFindAllBlockIndices_U32_Idx8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_u32_t *ptr, kd_usize_t ptr_sz, kd_u32_t val, kd_bool_t use_block_idx)
{
    kd_u8_t idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : KD_SZ_U32;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz -= KD_SZ_U32;

        if (*ptr == val)
        {
            *idxs = idx;
            ++found_cnt;
            ++idxs;
            --idxs_sz;
        }

        ++ptr;
        idx += inc;
    }

    return KD_USIZE_C(found_cnt);
}


kd_usize_t
kdi_GenMemOpsFindAllBlockIndices_U32_Idx16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_u32_t *ptr, kd_usize_t ptr_sz, kd_u32_t val, kd_bool_t use_block_idx)
{
    kd_u16_t idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : KD_SZ_U32;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz -= KD_SZ_U32;

        if (*ptr == val)
        {
            *idxs = idx;
            ++idxs;
            ++found_cnt;
            idxs_sz -= KD_SZ_U16;
        }

        ++ptr;
        idx += inc;
    }

    return KD_USIZE_C(found_cnt);
}


kd_usize_t
kdi_GenMemOpsFindAllBlockIndices_U32_Idx32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_u32_t *ptr, kd_usize_t ptr_sz, kd_u32_t val, kd_bool_t use_block_idx)
{
    kd_u32_t idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : KD_SZ_U32;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz -= KD_SZ_U32;

        if (*ptr == val)
        {
            *idxs = idx;
            ++idxs;
            ++found_cnt;
            idxs_sz -= KD_SZ_U32;
        }

        ++ptr;
        idx += inc;
    }

    return KD_USIZE_C(found_cnt);
}


#if defined KD_ARCH_64BIT_INT
kd_usize_t
kdi_GenMemOpsFindAllBlockIndices_U32_Idx64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_u32_t *ptr, kd_usize_t ptr_sz, kd_u32_t val, kd_bool_t use_block_idx)
{
    kd_u64_t idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : KD_SZ_U32;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz -= KD_SZ_U32;

        if (*ptr == val)
        {
            *idxs = idx;
            ++idxs;
            ++found_cnt;
            idxs_sz -= KD_SZ_U64;
        }

        ++ptr;
        idx += inc;
    }

    return KD_USIZE_C(found_cnt);
}
#endif


#if defined KD_ARCH_64BIT_INT
kd_usize_t
kdi_GenMemOpsFindAllBlockIndices_U64_Idx8(kd_u8_t *idxs, kd_usize_t idxs_sz, kd_u64_t *ptr, kd_usize_t ptr_sz, kd_u64_t val, kd_bool_t use_block_idx)
{
    kd_u8_t idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : KD_SZ_U64;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz -= KD_SZ_U64;

        if (*ptr == val)
        {
            *idxs = idx;
            ++found_cnt;
            ++idxs;
            --idxs_sz;
        }

        ++ptr;
        idx += inc;
    }

    return KD_USIZE_C(found_cnt);
}


kd_usize_t
kdi_GenMemOpsFindAllBlockIndices_U64_Idx16(kd_u16_t *idxs, kd_usize_t idxs_sz, kd_u64_t *ptr, kd_usize_t ptr_sz, kd_u64_t val, kd_bool_t use_block_idx)
{
    kd_u16_t idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : KD_SZ_U64;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz -= KD_SZ_U64;

        if (*ptr == val)
        {
            *idxs = idx;
            ++idxs;
            ++found_cnt;
            idxs_sz -= KD_SZ_U16;
        }

        ++ptr;
        idx += inc;
    }

    return KD_USIZE_C(found_cnt);
}


kd_usize_t
kdi_GenMemOpsFindAllBlockIndices_U64_Idx32(kd_u32_t *idxs, kd_usize_t idxs_sz, kd_u64_t *ptr, kd_usize_t ptr_sz, kd_u64_t val, kd_bool_t use_block_idx)
{
    kd_u32_t idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : KD_SZ_U64;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz -= KD_SZ_U64;

        if (*ptr == val)
        {
            *idxs = idx;
            ++idxs;
            ++found_cnt;
            idxs_sz -= KD_SZ_U32;
        }

        ++ptr;
        idx += inc;
    }

    return KD_USIZE_C(found_cnt);
}


kd_usize_t
kdi_GenMemOpsFindAllBlockIndices_U64_Idx64(kd_u64_t *idxs, kd_usize_t idxs_sz, kd_u64_t *ptr, kd_usize_t ptr_sz, kd_u64_t val, kd_bool_t use_block_idx)
{
    kd_u64_t idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : KD_SZ_U64;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz -= KD_SZ_U64;

        if (*ptr == val)
        {
            *idxs = idx;
            ++idxs;
            ++found_cnt;
            idxs_sz -= KD_SZ_U64;
        }

        ++ptr;
        idx += inc;
    }

    return KD_USIZE_C(found_cnt);
}
#endif


kd_usize_t
kdi_GenMemOpsFindAllBlockIndices_Un_Idx8(kd_u8_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, void *val_block, kd_usize_t val_block_sz, kd_bool_t use_block_idx)
{
    kd_byte_t *temp_ptr = ptr, *block_ptr;
    kd_u8_t    idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : KD_U8_C(val_block_sz);
    kd_usize_t match_cnt, temp_block_sz;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz        -= val_block_sz;
        block_ptr      = val_block;
        temp_block_sz  = val_block_sz;
        match_cnt      = 0;

        while (temp_block_sz--)
        {
            match_cnt += *temp_ptr == *block_ptr;
            ++temp_ptr;
            ++block_ptr;
        }

        if (match_cnt == val_block_sz)
        {
            *idxs = idx;
            ++idxs;
            --idxs_sz;
            ++found_cnt;
        }

        idx += inc;
    }

    return found_cnt;
}


kd_usize_t
kdi_GenMemOpsFindAllBlockIndices_Un_Idx16(kd_u16_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, void *val_block, kd_usize_t val_block_sz, kd_bool_t use_block_idx)
{
    kd_byte_t *temp_ptr = ptr, *block_ptr;
    kd_u16_t   idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : KD_U16_C(val_block_sz);
    kd_usize_t match_cnt, temp_block_sz;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz        -= val_block_sz;
        block_ptr      = val_block;
        temp_block_sz  = val_block_sz;
        match_cnt      = 0;

        while (temp_block_sz--)
        {
            match_cnt += *temp_ptr == *block_ptr;
            ++temp_ptr;
            ++block_ptr;
        }

        if (match_cnt == val_block_sz)
        {
            *idxs = idx;
            ++idxs;
            idxs_sz -= KD_SZ_U16;
            ++found_cnt;
        }

        idx += inc;
    }

    return found_cnt;
}


kd_usize_t
kdi_GenMemOpsFindAllBlockIndices_Un_Idx32(kd_u32_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, void *val_block, kd_usize_t val_block_sz, kd_bool_t use_block_idx)
{
    kd_byte_t *temp_ptr = ptr, *block_ptr;
    kd_u32_t   idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : KD_U32_C(val_block_sz);
    kd_usize_t match_cnt, temp_block_sz;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz        -= val_block_sz;
        block_ptr      = val_block;
        temp_block_sz  = val_block_sz;
        match_cnt      = 0;

        while (temp_block_sz--)
        {
            match_cnt += *temp_ptr == *block_ptr;
            ++temp_ptr;
            ++block_ptr;
        }

        if (match_cnt == val_block_sz)
        {
            *idxs = idx;
            ++idxs;
            idxs_sz -= KD_SZ_U32;
            ++found_cnt;
        }

        idx += inc;
    }

    return found_cnt;
}


#if defined KD_ARCH_64BIT_INT
kd_usize_t
kdi_GenMemOpsFindAllBlockIndices_Un_Idx64(kd_u64_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, void *val_block, kd_usize_t val_block_sz, kd_bool_t use_block_idx)
{
    kd_byte_t *temp_ptr = ptr, *block_ptr;
    kd_u64_t   idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : KD_U64_C(val_block_sz);
    kd_usize_t match_cnt, temp_block_sz;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz        -= val_block_sz;
        block_ptr      = val_block;
        temp_block_sz  = val_block_sz;
        match_cnt      = 0;

        while (temp_block_sz--)
        {
            match_cnt += *temp_ptr == *block_ptr;
            ++temp_ptr;
            ++block_ptr;
        }

        if (match_cnt == val_block_sz)
        {
            *idxs = idx;
            ++idxs;
            idxs_sz -= KD_SZ_U64;
            ++found_cnt;
        }

        idx += inc;
    }

    return found_cnt;
}
#endif


kd_usize_t
kdi_GenMemOpsFindAllBlockIndices_Struct_Idx8(kd_u8_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, void *val_block, kd_usize_t val_block_sz, kd_bool_t use_block_idx, kd_bool_t (*matcher)(void *curr_ptr, void *sz_ptr, void *block, void *block_sz_ptr, void *curr_idx_ptr))
{
    kd_byte_t *src_ptr = ptr;
    kd_u8_t    idx = 0, found_cnt = 0;
    kd_usize_t orig_ptr_sz = ptr_sz, temp_sz, temp_block_sz, temp_idx;

    (void)use_block_idx;

    while (ptr_sz && idxs_sz)
    {
        temp_sz        = orig_ptr_sz;
        temp_block_sz  = val_block_sz;
        temp_idx       = use_block_idx ? idx : (orig_ptr_sz - ptr_sz);

        ptr_sz        -= val_block_sz;

        if (matcher(src_ptr, &temp_sz, val_block, &temp_block_sz, &temp_idx))
        {
            *idxs = idx;
            ++idxs;
            --idxs_sz;
            ++found_cnt;
        }

        src_ptr += val_block_sz;
        ++idx;
    }

    return KD_USIZE_C(found_cnt);
}


kd_usize_t
kdi_GenMemOpsFindAllBlockIndices_Struct_Idx16(kd_u16_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, void *val_block, kd_usize_t val_block_sz, kd_bool_t use_block_idx, kd_bool_t (*matcher)(void *curr_ptr, void *sz_ptr, void *block, void *block_sz_ptr, void *curr_idx_ptr))
{
    kd_byte_t *src_ptr = ptr;
    kd_u16_t   idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : KD_U16_C(val_block_sz);
    kd_usize_t orig_ptr_sz = ptr_sz, temp_sz, temp_block_sz, temp_idx;

    while (ptr_sz && idxs_sz)
    {
        temp_sz        = orig_ptr_sz;
        temp_block_sz  = val_block_sz;
        temp_idx       = use_block_idx ? idx : (orig_ptr_sz - ptr_sz);

        ptr_sz        -= val_block_sz;

        if (matcher(src_ptr, &temp_sz, val_block, &temp_block_sz, &temp_idx))
        {
            *idxs = idx;
            ++idxs;
            idxs_sz -= KD_SZ_U16;
            ++found_cnt;
        }

        src_ptr += val_block_sz;
        idx     += inc;
    }

    return KD_USIZE_C(found_cnt);
}


kd_usize_t
kdi_GenMemOpsFindAllBlockIndices_Struct_Idx32(kd_u32_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, void *val_block, kd_usize_t val_block_sz, kd_bool_t use_block_idx, kd_bool_t (*matcher)(void *curr_ptr, void *sz_ptr, void *block, void *block_sz_ptr, void *curr_idx_ptr))
{
    kd_byte_t *src_ptr = ptr;
    kd_u32_t   idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : KD_U32_C(val_block_sz);
    kd_usize_t orig_ptr_sz = ptr_sz, temp_sz, temp_block_sz, temp_idx;

    while (ptr_sz && idxs_sz)
    {
        temp_sz        = orig_ptr_sz;
        temp_block_sz  = val_block_sz;
        temp_idx       = use_block_idx ? idx : (orig_ptr_sz - ptr_sz);

        ptr_sz        -= val_block_sz;

        if (matcher(src_ptr, &temp_sz, val_block, &temp_block_sz, &temp_idx))
        {
            *idxs = idx;
            ++idxs;
            idxs_sz -= KD_SZ_U32;
            ++found_cnt;
        }

        src_ptr += val_block_sz;
        idx     += inc;
    }

    return KD_USIZE_C(found_cnt);
}


#if defined KD_ARCH_64BIT_INT
kd_usize_t
kdi_GenMemOpsFindAllBlockIndices_Struct_Idx64(kd_u64_t *idxs, kd_usize_t idxs_sz, void *ptr, kd_usize_t ptr_sz, void *val_block, kd_usize_t val_block_sz, kd_bool_t use_block_idx, kd_bool_t (*matcher)(void *curr_ptr, void *sz_ptr, void *block, void *block_sz_ptr, void *curr_idx_ptr))
{
    kd_byte_t *src_ptr = ptr;
    kd_u64_t   idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : KD_U64_C(val_block_sz);
    kd_usize_t orig_ptr_sz = ptr_sz, temp_sz, temp_block_sz, temp_idx;

    while (ptr_sz && idxs_sz)
    {
        temp_sz        = orig_ptr_sz;
        temp_block_sz  = val_block_sz;
        temp_idx       = use_block_idx ? idx : (orig_ptr_sz - ptr_sz);

        ptr_sz        -= val_block_sz;

        if (matcher(src_ptr, &temp_sz, val_block, &temp_block_sz, &temp_idx))
        {
            *idxs = idx;
            ++idxs;
            idxs_sz -= KD_SZ_U64;
            ++found_cnt;
        }

        src_ptr += val_block_sz;
        idx     += inc;
    }

    return KD_USIZE_C(found_cnt);
}
#endif


void *
kdi_GenMemOpsBinarySearchBlockWithIndex_U8(kd_usize_t *idx_ptr, kd_u8_t *ptr, kd_usize_t sz, kd_u8_t val)
{
    kd_u8_t   *curr_ptr = ptr;
    kd_usize_t temp_sz, div_sz;

    while (sz)
    {
        div_sz    = sz / 2;
        temp_sz   = div_sz;
        curr_ptr += div_sz;

        if (*curr_ptr == val)
        {
            if (idx_ptr)
            {
                *idx_ptr = KD_USIZE_C(ptr - curr_ptr);
            }
            return curr_ptr;
        }

        if (val < *curr_ptr)
        {
            curr_ptr -= div_sz;
        }

        if (val > *curr_ptr)
        {
            div_sz = sz - div_sz;
        }

        sz = temp_sz;
    }

    return kd_null;
}


void *
kdi_GenMemOpsBinarySearchBlockWithIndex_U16(kd_usize_t *idx_ptr, kd_u16_t *ptr, kd_usize_t sz, kd_u16_t val)
{
    kd_u16_t  *curr_ptr = ptr;
    kd_usize_t temp_sz, div_sz;

    while (sz)
    {
        div_sz   = ((sz / KD_SZ_U16) / 2) * KD_SZ_U16;
        temp_sz  = div_sz;
        curr_ptr = KD_PBYTE_C(curr_ptr) + div_sz;

        if (*curr_ptr == val)
        {
            if (idx_ptr)
            {
                *idx_ptr = KD_USIZE_C(ptr - curr_ptr);
            }
            return curr_ptr;
        }

        if (val < *curr_ptr)
        {
            curr_ptr = KD_PBYTE_C(curr_ptr) - div_sz;
        }

        if (val > *curr_ptr)
        {
            div_sz = sz - div_sz;
        }

        sz = temp_sz;
    }

    return kd_null;
}


void *
kdi_GenMemOpsBinarySearchBlockWithIndex_U32(kd_usize_t *idx_ptr, kd_u32_t *ptr, kd_usize_t sz, kd_u32_t val)
{
    kd_u32_t  *curr_ptr = ptr;
    kd_usize_t temp_sz, div_sz;

    while (sz)
    {
        div_sz   = ((sz / KD_SZ_U32) / 2) * KD_SZ_U32;
        temp_sz  = div_sz;
        curr_ptr = KD_PBYTE_C(curr_ptr) + div_sz;

        if (*curr_ptr == val)
        {
            if (idx_ptr)
            {
                *idx_ptr = KD_USIZE_C(ptr - curr_ptr);
            }
            return curr_ptr;
        }

        if (val < *curr_ptr)
        {
            curr_ptr = KD_PBYTE_C(curr_ptr) - div_sz;
        }

        if (val > *curr_ptr)
        {
            div_sz = sz - div_sz;
        }

        sz = temp_sz;
    }

    return kd_null;
}


#if defined KD_ARCH_64BIT_INT
void *
kdi_GenMemOpsBinarySearchBlockWithIndex_U64(kd_usize_t *idx_ptr, kd_u64_t *ptr, kd_usize_t sz, kd_u64_t val)
{
    kd_u64_t  *curr_ptr = ptr;
    kd_usize_t temp_sz, div_sz;

    while (sz)
    {
        div_sz   = ((sz / KD_SZ_U64) / 2) * KD_SZ_U64;
        temp_sz  = div_sz;
        curr_ptr = KD_PBYTE_C(curr_ptr) + div_sz;

        if (*curr_ptr == val)
        {
            if (idx_ptr)
            {
                *idx_ptr = KD_USIZE_C(ptr - curr_ptr);
            }
            return curr_ptr;
        }

        if (val < *curr_ptr)
        {
            curr_ptr = KD_PBYTE_C(curr_ptr) - div_sz;
        }

        if (val > *curr_ptr)
        {
            div_sz = sz - div_sz;
        }

        sz = temp_sz;
    }

    return kd_null;
}
#endif


void *
kdi_GenMemOpsFindBlockWithIndex_Un(kd_usize_t *idx_ptr, void *ptr, kd_usize_t sz, void *block, kd_usize_t block_sz)
{
    kd_byte_t *src_ptr = ptr, *temp_src_ptr, *block_ptr;
    kd_usize_t i, idx = 0, temp_sz, match_cnt;

    while (sz)
    {
        temp_src_ptr = src_ptr;
        block_ptr    = block;
        temp_sz      = sz;
        i            = block_sz;
        match_cnt    = 0;

        while (i-- && temp_sz--)
        {
            if (*temp_src_ptr != *block_ptr)
            {
                break;
            }

            ++temp_src_ptr;
            ++block_ptr;
            ++match_cnt;
        }

        if (match_cnt == block_sz)
        {
            if (idx_ptr)
            {
                *idx_ptr = idx;
            }
            return src_ptr;
        }

        idx     += block_sz;
        src_ptr += block_sz;
        sz      -= block_sz;
    }

    return kd_null;
}
