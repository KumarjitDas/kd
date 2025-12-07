/**
 * @file gen_mem_ops.c
 * @author Kumarjit Das
 * @version 0.0.1
 * @brief Main source file of the KDI_GEN_MEM_OPS library (internal).
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 * @since 0.0.1
 */


#define BUILDING_LIB 1
#include "./gen_mem_ops.h"


void
kdi_GenMemOpsCopy(byte *dst, byte *src, usize sz)
{
    while (sz--)
    {
        *dst = *src;
        ++dst;
        ++src;
    }
}


/*
void
kdi_GenMemOpsSwapBlocks_U8(u8 *ptr, usize idx1, usize idx2)
{
    u8 *ptr1  = ptr + idx1;
    u8  temp  = *ptr1;

    ptr      += idx2;
    *ptr1     = *ptr;
    *ptr      = temp;
}


void
kdi_GenMemOpsSwapBlocks_U16(u16 *ptr, usize idx1, usize idx2)
{
    u16 *ptr1 = PU16_C(PU8_C(ptr) + idx1);
    u16  temp = *ptr1;

    ptr       = PU16_C(PU8_C(ptr) + idx2);
    *ptr1     = *ptr;
    *ptr      = temp;
}


void
kdi_GenMemOpsSwapBlocks_U32(u32 *ptr, usize idx1, usize idx2)
{
    u32 *ptr1 = PU32_C(PU8_C(ptr) + idx1);
    u32  temp = *ptr1;

    ptr       = PU32_C(PU8_C(ptr) + idx2);
    *ptr1     = *ptr;
    *ptr      = temp;
}


#if defined ARCH_64BIT_INT
void
kdi_GenMemOpsSwapBlocks_U64(u64 *ptr, usize idx1, usize idx2)
{
    u64 *ptr1 = PU64_C(PU8_C(ptr) + idx1);
    u64  temp = *ptr1;

    ptr       = PU64_C(PU8_C(ptr) + idx2);
    *ptr1     = *ptr;
    *ptr      = temp;
}
#endif


void
kdi_GenMemOpsSwapBlocks_Un(void *ptr, usize idx1, usize idx2, usize block_sz)
{
    u8 *ptr1 = PU8_C(ptr) + idx1;
    u8 *ptr2 = PU8_C(ptr) + idx2;
    u8  temp;

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
kdi_GenMemOpsReverseBlocks_U8(u8 *ptr, usize sz)
{
    u8 *end = ptr + sz;
    u8  temp;

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
kdi_GenMemOpsReverseBlocks_U16(u16 *ptr, usize sz)
{
    u16 *end = PU16_C(PU8_C(ptr) + sz);
    u16  temp;

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
kdi_GenMemOpsReverseBlocks_U32(u32 *ptr, usize sz)
{
    u32 *end = PU32_C(PU8_C(ptr) + sz);
    u32  temp;

    while (sz-- && ptr < end)
    {
        --end;

        temp = *ptr;
        *ptr = *end;
        *end = temp;

        ++ptr;
    }
}


#if defined ARCH_64BIT_INT
void
kdi_GenMemOpsReverseBlocks_U64(u64 *ptr, usize sz)
{
    u64 *end = PU64_C(PU8_C(ptr) + sz);
    u64  temp;

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
kdi_GenMemOpsReverseBlocks_Un(void *ptr, usize sz, usize block_sz)
{
    u8   *begin = ptr, *temp_end, temp;
    u8   *end   = begin + sz;
    usize temp_block_sz;

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
kdi_GenMemOpsSetBlocks_U8(u8 *ptr, usize sz, u8 val)
{
    while (sz--)
    {
        *ptr = val;
        ++ptr;
    }
}


void
kdi_GenMemOpsSetBlocks_U16(u16 *ptr, usize sz, u16 val)
{
    while (sz)
    {
        *ptr = val;
        ++ptr;
        sz -= SZ_U16;
    }
}


void
kdi_GenMemOpsSetBlocks_U32(u32 *ptr, usize sz, u32 val)
{
    while (sz)
    {
        *ptr = val;
        ++ptr;
        sz -= SZ_U32;
    }
}


#if defined ARCH_64BIT_INT
void
kdi_GenMemOpsSetBlocks_U64(u64 *ptr, usize sz, u64 val)
{
    while (sz)
    {
        *ptr = val;
        ++ptr;
        sz -= SZ_U64;
    }
}
#endif


void
kdi_GenMemOpsSetBlocks_Un(void *ptr, usize sz, void *block, usize block_sz)
{
    byte *dst_ptr = ptr;
    byte *block_ptr;
    usize i;

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
kdi_GenMemOpsCpy(byte *dst, byte *src, usize sz)
{
    while (sz--)
    {
        *dst = *src;
        ++dst;
        ++src;
    }
}


void
kdi_GenMemOpsMove(byte *dst, byte *src, usize sz)
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
kdi_GenMemOpsFindBlockWithIndex_U8(usize *idx_ptr, u8 *ptr, usize sz, u8 val)
{
    usize idx = 0;

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

    return null;
}


void *
kdi_GenMemOpsFindBlockWithIndex_U16(usize *idx_ptr, u16 *ptr, usize sz, u16 val)
{
    usize idx = 0;

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
        idx += SZ_U16;
        sz  -= SZ_U16;
    }

    return null;
}


void *
kdi_GenMemOpsFindBlockWithIndex_U32(usize *idx_ptr, u32 *ptr, usize sz, u32 val)
{
    usize idx = 0;

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
        idx += SZ_U32;
        sz  -= SZ_U32;
    }

    return null;
}


#if defined ARCH_64BIT_INT
void *
kdi_GenMemOpsFindBlockWithIndex_U64(usize *idx_ptr, u64 *ptr, usize sz, u64 val)
{
    usize idx = 0;

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
        idx += SZ_U64;
        sz  -= SZ_U64;
    }

    return null;
}
#endif


void *
kdi_GenMemOpsFindBlockWithIndex_Un(usize *idx_ptr, void *ptr, usize sz, void *block, usize block_sz)
{
    byte *src_ptr = ptr, *temp_src_ptr, *block_ptr;
    usize i, idx = 0, temp_sz, match_cnt;

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

    return null;
}


void *
kdi_GenMemOpsFindLastBlockWithIndex_U8(usize *idx_ptr, u8 *ptr, usize sz, u8 val)
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

    return null;
}


void *
kdi_GenMemOpsFindLastBlockWithIndex_U16(usize *idx_ptr, u16 *ptr, usize sz, u16 val)
{
    ptr = (u16 *)((byte *)ptr + sz);

    while (sz)
    {
        ptr  = (u16 *)((byte *)ptr - SZ_U16);
        sz  -= SZ_U16;

        if (*ptr == val)
        {
            if (idx_ptr)
            {
                *idx_ptr = sz;
            }
            return ptr;
        }
    }

    return null;
}


void *
kdi_GenMemOpsFindLastBlockWithIndex_U32(usize *idx_ptr, u32 *ptr, usize sz, u32 val)
{
    ptr = (u32 *)((byte *)ptr + sz);

    while (sz)
    {
        ptr  = (u32 *)((byte *)ptr - SZ_U32);
        sz  -= SZ_U32;

        if (*ptr == val)
        {
            if (idx_ptr)
            {
                *idx_ptr = sz;
            }
            return ptr;
        }
    }

    return null;
}


#if defined ARCH_64BIT_INT
void *
kdi_GenMemOpsFindLastBlockWithIndex_U64(usize *idx_ptr, u64 *ptr, usize sz, u64 val)
{
    ptr = (u64 *)((byte *)ptr + sz);

    while (sz)
    {
        ptr  = (u64 *)((byte *)ptr - SZ_U64);
        sz  -= SZ_U64;

        if (*ptr == val)
        {
            if (idx_ptr)
            {
                *idx_ptr = sz;
            }
            return ptr;
        }
    }

    return null;
}
#endif


void *
kdi_GenMemOpsFindLastBlockWithIndex_Un(usize *idx_ptr, void *ptr, usize sz, void *block, usize block_sz)
{
    byte *src_ptr = (byte *)ptr + sz, *temp_src_ptr, *block_ptr;
    usize i, temp_sz, match_cnt;

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

    return null;
}


void *
kdi_GenMemOpsFindBlockWithIndex_Struct(usize *idx_ptr, void *ptr, usize sz, void *block, usize block_sz, bool (*matcher)(void *curr_ptr, void *sz_ptr, void *block, void *block_sz_ptr, void *curr_idx_ptr))
{
    byte *src_ptr = ptr;
    usize i, idx = 0, orig_sz = sz, temp_sz, temp_block_sz, temp_idx;

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

    return null;
}


void *
kdi_GenMemOpsFindLastBlockWithIndex_Struct(usize *idx_ptr, void *ptr, usize sz, void *block, usize block_sz, bool (*matcher)(void *curr_ptr, void *sz_ptr, void *block, void *block_sz_ptr, void *curr_idx_ptr))
{
    byte *src_ptr = (byte *)ptr + sz;
    usize i, orig_sz = sz, temp_sz, temp_block_sz, temp_idx;

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

    return null;
}


usize
kdi_GenMemOpsGetBlocksCount_U8(u8 *ptr, usize sz, u8 val)
{
    usize count = 0;

    while (sz--)
    {
        count += *ptr == val;
        ++ptr;
    }

    return count;
}


usize
kdi_GenMemOpsGetBlocksCount_U16(u16 *ptr, usize sz, u16 val)
{
    usize count = 0;

    while (sz)
    {
        count += *ptr == val;
        sz    -= SZ_U16;
        ++ptr;
    }

    return count;
}


usize
kdi_GenMemOpsGetBlocksCount_U32(u32 *ptr, usize sz, u32 val)
{
    usize count = 0;

    while (sz)
    {
        count += *ptr == val;
        sz    -= SZ_U32;
        ++ptr;
    }

    return count;
}


#if defined ARCH_64BIT_INT
usize
kdi_GenMemOpsGetBlocksCount_U64(u64 *ptr, usize sz, u64 val)
{
    usize count = 0;

    while (sz)
    {
        count += *ptr == val;
        sz    -= SZ_U64;
        ++ptr;
    }

    return count;
}
#endif


usize
kdi_GenMemOpsGetBlocksCount_Un(void *ptr, usize sz, void *block, usize block_sz)
{
    byte *src_ptr = ptr, *temp_src_ptr, *block_ptr;
    usize i, count = 0, temp_sz, match_cnt;

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


usize
kdi_GenMemOpsFindAllBlocks_U8(void *dst, usize dst_sz, u8 *ptr, usize ptr_sz, u8 val)
{
    u8  **dst_adr   = dst;
    usize found_cnt = 0;

    while (ptr_sz-- && dst_sz)
    {
        if (*ptr == val)
        {
            *dst_adr = ptr;
            ++dst_adr;
            ++found_cnt;
            dst_sz -= SZ_PTR;
        }

        ++ptr;
    }

    return found_cnt;
}


usize
kdi_GenMemOpsFindAllBlocks_U16(void *dst, usize dst_sz, u16 *ptr, usize ptr_sz, u16 val)
{
    u16 **dst_adr   = dst;
    usize found_cnt = 0;

    while (ptr_sz && dst_sz)
    {
        if (*ptr == val)
        {
            *dst_adr = ptr;
            ++dst_adr;
            ++found_cnt;
            dst_sz -= SZ_PTR;
        }

        ++ptr;
        ptr_sz -= SZ_U16;
    }

    return found_cnt;
}


usize
kdi_GenMemOpsFindAllBlocks_U32(void *dst, usize dst_sz, u32 *ptr, usize ptr_sz, u32 val)
{
    u32 **dst_adr   = dst;
    usize found_cnt = 0;

    while (ptr_sz && dst_sz)
    {
        if (*ptr == val)
        {
            *dst_adr = ptr;
            ++dst_adr;
            ++found_cnt;
            dst_sz -= SZ_PTR;
        }

        ++ptr;
        ptr_sz -= SZ_U32;
    }

    return found_cnt;
}


#if defined ARCH_64BIT_INT
usize
kdi_GenMemOpsFindAllBlocks_U64(void *dst, usize dst_sz, u64 *ptr, usize ptr_sz, u64 val)
{
    u64 **dst_adr   = dst;
    usize found_cnt = 0;

    while (ptr_sz && dst_sz)
    {
        if (*ptr == val)
        {
            *dst_adr = ptr;
            ++dst_adr;
            ++found_cnt;
            dst_sz -= SZ_PTR;
        }

        ++ptr;
        ptr_sz -= SZ_U64;
    }

    return found_cnt;
}
#endif


usize
kdi_GenMemOpsFindAllBlocks_Un(void *dst, usize dst_sz, byte *ptr, usize ptr_sz, void *block, usize block_sz)
{
    byte **dst_adr   = dst, *block_ptr;
    usize  found_cnt = 0, match_cnt, temp_block_sz;

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
            dst_sz -= SZ_USIZE;
        }
    }

    return found_cnt;
}


usize
kdi_GenMemOpsFindAllBlocks_Struct(void *dst, usize dst_sz, byte *ptr, usize ptr_sz, void *block, usize block_sz, bool (*matcher)(void *curr_ptr, void *sz_ptr, void *block, void *block_sz_ptr, void *curr_idx_ptr))
{
    byte **dst_adr = dst, *src_ptr = ptr;
    usize  idx = 0, found_cnt = 0, orig_ptr_sz = ptr_sz, temp_sz, temp_block_sz, temp_idx;

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
            dst_sz -= SZ_USIZE;
        }

        src_ptr += block_sz;
    }

    return found_cnt;
}


usize
kdi_GenMemOpsFindAllBlockIndices_U8_Idx8(u8 *idxs, usize idxs_sz, u8 *ptr, usize ptr_sz, u8 val, bool use_block_idx)
{
    u8 idx = 0, found_cnt = 0;

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

    return USIZE_C(found_cnt);
}


usize
kdi_GenMemOpsFindAllBlockIndices_U8_Idx16(u16 *idxs, usize idxs_sz, u8 *ptr, usize ptr_sz, u8 val, bool use_block_idx)
{
    u16 idx = 0, found_cnt = 0;

    (void)use_block_idx;

    while (ptr_sz-- && idxs_sz)
    {
        if (*ptr == val)
        {
            *idxs = idx;
            ++idxs;
            ++found_cnt;
            idxs_sz -= SZ_U16;
        }

        ++ptr;
        ++idx;
    }

    return USIZE_C(found_cnt);
}


usize
kdi_GenMemOpsFindAllBlockIndices_U8_Idx32(u32 *idxs, usize idxs_sz, u8 *ptr, usize ptr_sz, u8 val, bool use_block_idx)
{
    u32 idx = 0, found_cnt = 0;

    (void)use_block_idx;

    while (ptr_sz-- && idxs_sz)
    {
        if (*ptr == val)
        {
            *idxs = idx;
            ++idxs;
            ++found_cnt;
            idxs_sz -= SZ_U32;
        }

        ++ptr;
        ++idx;
    }

    return USIZE_C(found_cnt);
}


#if defined ARCH_64BIT_INT
usize
kdi_GenMemOpsFindAllBlockIndices_U8_Idx64(u64 *idxs, usize idxs_sz, u8 *ptr, usize ptr_sz, u8 val, bool use_block_idx)
{
    u64 idx = 0, found_cnt = 0;

    (void)use_block_idx;

    while (ptr_sz-- && idxs_sz)
    {
        if (*ptr == val)
        {
            *idxs = idx;
            ++idxs;
            ++found_cnt;
            idxs_sz -= SZ_U64;
        }

        ++ptr;
        ++idx;
    }

    return USIZE_C(found_cnt);
}
#endif


usize
kdi_GenMemOpsFindAllBlockIndices_U16_Idx8(u8 *idxs, usize idxs_sz, u16 *ptr, usize ptr_sz, u16 val, bool use_block_idx)
{
    u8 idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : SZ_U16;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz -= SZ_U16;

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

    return USIZE_C(found_cnt);
}


usize
kdi_GenMemOpsFindAllBlockIndices_U16_Idx16(u16 *idxs, usize idxs_sz, u16 *ptr, usize ptr_sz, u16 val, bool use_block_idx)
{
    u16 idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : SZ_U16;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz -= SZ_U16;

        if (*ptr == val)
        {
            *idxs = idx;
            ++idxs;
            ++found_cnt;
            idxs_sz -= SZ_U16;
        }

        ++ptr;
        idx += inc;
    }

    return USIZE_C(found_cnt);
}


usize
kdi_GenMemOpsFindAllBlockIndices_U16_Idx32(u32 *idxs, usize idxs_sz, u16 *ptr, usize ptr_sz, u16 val, bool use_block_idx)
{
    u32 idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : SZ_U16;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz -= SZ_U16;

        if (*ptr == val)
        {
            *idxs = idx;
            ++idxs;
            ++found_cnt;
            idxs_sz -= SZ_U32;
        }

        ++ptr;
        idx += inc;
    }

    return USIZE_C(found_cnt);
}


#if defined ARCH_64BIT_INT
usize
kdi_GenMemOpsFindAllBlockIndices_U16_Idx64(u64 *idxs, usize idxs_sz, u16 *ptr, usize ptr_sz, u16 val, bool use_block_idx)
{
    u64 idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : SZ_U16;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz -= SZ_U16;

        if (*ptr == val)
        {
            *idxs = idx;
            ++idxs;
            ++found_cnt;
            idxs_sz -= SZ_U64;
        }

        ++ptr;
        idx += inc;
    }

    return USIZE_C(found_cnt);
}
#endif


usize
kdi_GenMemOpsFindAllBlockIndices_U32_Idx8(u8 *idxs, usize idxs_sz, u32 *ptr, usize ptr_sz, u32 val, bool use_block_idx)
{
    u8 idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : SZ_U32;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz -= SZ_U32;

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

    return USIZE_C(found_cnt);
}


usize
kdi_GenMemOpsFindAllBlockIndices_U32_Idx16(u16 *idxs, usize idxs_sz, u32 *ptr, usize ptr_sz, u32 val, bool use_block_idx)
{
    u16 idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : SZ_U32;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz -= SZ_U32;

        if (*ptr == val)
        {
            *idxs = idx;
            ++idxs;
            ++found_cnt;
            idxs_sz -= SZ_U16;
        }

        ++ptr;
        idx += inc;
    }

    return USIZE_C(found_cnt);
}


usize
kdi_GenMemOpsFindAllBlockIndices_U32_Idx32(u32 *idxs, usize idxs_sz, u32 *ptr, usize ptr_sz, u32 val, bool use_block_idx)
{
    u32 idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : SZ_U32;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz -= SZ_U32;

        if (*ptr == val)
        {
            *idxs = idx;
            ++idxs;
            ++found_cnt;
            idxs_sz -= SZ_U32;
        }

        ++ptr;
        idx += inc;
    }

    return USIZE_C(found_cnt);
}


#if defined ARCH_64BIT_INT
usize
kdi_GenMemOpsFindAllBlockIndices_U32_Idx64(u64 *idxs, usize idxs_sz, u32 *ptr, usize ptr_sz, u32 val, bool use_block_idx)
{
    u64 idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : SZ_U32;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz -= SZ_U32;

        if (*ptr == val)
        {
            *idxs = idx;
            ++idxs;
            ++found_cnt;
            idxs_sz -= SZ_U64;
        }

        ++ptr;
        idx += inc;
    }

    return USIZE_C(found_cnt);
}
#endif


#if defined ARCH_64BIT_INT
usize
kdi_GenMemOpsFindAllBlockIndices_U64_Idx8(u8 *idxs, usize idxs_sz, u64 *ptr, usize ptr_sz, u64 val, bool use_block_idx)
{
    u8 idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : SZ_U64;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz -= SZ_U64;

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

    return USIZE_C(found_cnt);
}


usize
kdi_GenMemOpsFindAllBlockIndices_U64_Idx16(u16 *idxs, usize idxs_sz, u64 *ptr, usize ptr_sz, u64 val, bool use_block_idx)
{
    u16 idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : SZ_U64;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz -= SZ_U64;

        if (*ptr == val)
        {
            *idxs = idx;
            ++idxs;
            ++found_cnt;
            idxs_sz -= SZ_U16;
        }

        ++ptr;
        idx += inc;
    }

    return USIZE_C(found_cnt);
}


usize
kdi_GenMemOpsFindAllBlockIndices_U64_Idx32(u32 *idxs, usize idxs_sz, u64 *ptr, usize ptr_sz, u64 val, bool use_block_idx)
{
    u32 idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : SZ_U64;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz -= SZ_U64;

        if (*ptr == val)
        {
            *idxs = idx;
            ++idxs;
            ++found_cnt;
            idxs_sz -= SZ_U32;
        }

        ++ptr;
        idx += inc;
    }

    return USIZE_C(found_cnt);
}


usize
kdi_GenMemOpsFindAllBlockIndices_U64_Idx64(u64 *idxs, usize idxs_sz, u64 *ptr, usize ptr_sz, u64 val, bool use_block_idx)
{
    u64 idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : SZ_U64;

    while (ptr_sz && idxs_sz)
    {
        ptr_sz -= SZ_U64;

        if (*ptr == val)
        {
            *idxs = idx;
            ++idxs;
            ++found_cnt;
            idxs_sz -= SZ_U64;
        }

        ++ptr;
        idx += inc;
    }

    return USIZE_C(found_cnt);
}
#endif


usize
kdi_GenMemOpsFindAllBlockIndices_Un_Idx8(u8 *idxs, usize idxs_sz, void *ptr, usize ptr_sz, void *val_block, usize val_block_sz, bool use_block_idx)
{
    byte *temp_ptr = ptr, *block_ptr;
    u8    idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : U8_C(val_block_sz);
    usize match_cnt, temp_block_sz;

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


usize
kdi_GenMemOpsFindAllBlockIndices_Un_Idx16(u16 *idxs, usize idxs_sz, void *ptr, usize ptr_sz, void *val_block, usize val_block_sz, bool use_block_idx)
{
    byte *temp_ptr = ptr, *block_ptr;
    u16   idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : U16_C(val_block_sz);
    usize match_cnt, temp_block_sz;

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
            idxs_sz -= SZ_U16;
            ++found_cnt;
        }

        idx += inc;
    }

    return found_cnt;
}


usize
kdi_GenMemOpsFindAllBlockIndices_Un_Idx32(u32 *idxs, usize idxs_sz, void *ptr, usize ptr_sz, void *val_block, usize val_block_sz, bool use_block_idx)
{
    byte *temp_ptr = ptr, *block_ptr;
    u32   idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : U32_C(val_block_sz);
    usize match_cnt, temp_block_sz;

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
            idxs_sz -= SZ_U32;
            ++found_cnt;
        }

        idx += inc;
    }

    return found_cnt;
}


#if defined ARCH_64BIT_INT
usize
kdi_GenMemOpsFindAllBlockIndices_Un_Idx64(u64 *idxs, usize idxs_sz, void *ptr, usize ptr_sz, void *val_block, usize val_block_sz, bool use_block_idx)
{
    byte *temp_ptr = ptr, *block_ptr;
    u64   idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : U64_C(val_block_sz);
    usize match_cnt, temp_block_sz;

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
            idxs_sz -= SZ_U64;
            ++found_cnt;
        }

        idx += inc;
    }

    return found_cnt;
}
#endif


usize
kdi_GenMemOpsFindAllBlockIndices_Struct_Idx8(u8 *idxs, usize idxs_sz, void *ptr, usize ptr_sz, void *val_block, usize val_block_sz, bool use_block_idx, bool (*matcher)(void *curr_ptr, void *sz_ptr, void *block, void *block_sz_ptr, void *curr_idx_ptr))
{
    byte *src_ptr = ptr;
    u8    idx = 0, found_cnt = 0;
    usize orig_ptr_sz = ptr_sz, temp_sz, temp_block_sz, temp_idx;

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

    return USIZE_C(found_cnt);
}


usize
kdi_GenMemOpsFindAllBlockIndices_Struct_Idx16(u16 *idxs, usize idxs_sz, void *ptr, usize ptr_sz, void *val_block, usize val_block_sz, bool use_block_idx, bool (*matcher)(void *curr_ptr, void *sz_ptr, void *block, void *block_sz_ptr, void *curr_idx_ptr))
{
    byte *src_ptr = ptr;
    u16   idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : U16_C(val_block_sz);
    usize orig_ptr_sz = ptr_sz, temp_sz, temp_block_sz, temp_idx;

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
            idxs_sz -= SZ_U16;
            ++found_cnt;
        }

        src_ptr += val_block_sz;
        idx     += inc;
    }

    return USIZE_C(found_cnt);
}


usize
kdi_GenMemOpsFindAllBlockIndices_Struct_Idx32(u32 *idxs, usize idxs_sz, void *ptr, usize ptr_sz, void *val_block, usize val_block_sz, bool use_block_idx, bool (*matcher)(void *curr_ptr, void *sz_ptr, void *block, void *block_sz_ptr, void *curr_idx_ptr))
{
    byte *src_ptr = ptr;
    u32   idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : U32_C(val_block_sz);
    usize orig_ptr_sz = ptr_sz, temp_sz, temp_block_sz, temp_idx;

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
            idxs_sz -= SZ_U32;
            ++found_cnt;
        }

        src_ptr += val_block_sz;
        idx     += inc;
    }

    return USIZE_C(found_cnt);
}


#if defined ARCH_64BIT_INT
usize
kdi_GenMemOpsFindAllBlockIndices_Struct_Idx64(u64 *idxs, usize idxs_sz, void *ptr, usize ptr_sz, void *val_block, usize val_block_sz, bool use_block_idx, bool (*matcher)(void *curr_ptr, void *sz_ptr, void *block, void *block_sz_ptr, void *curr_idx_ptr))
{
    byte *src_ptr = ptr;
    u64   idx = 0, found_cnt = 0, inc = use_block_idx ? 1 : U64_C(val_block_sz);
    usize orig_ptr_sz = ptr_sz, temp_sz, temp_block_sz, temp_idx;

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
            idxs_sz -= SZ_U64;
            ++found_cnt;
        }

        src_ptr += val_block_sz;
        idx     += inc;
    }

    return USIZE_C(found_cnt);
}
#endif


void *
kdi_GenMemOpsBinarySearchBlockWithIndex_U8(usize *idx_ptr, u8 *ptr, usize sz, u8 val)
{
    u8   *curr_ptr = ptr;
    usize temp_sz, div_sz;

    while (sz)
    {
        div_sz    = sz / 2;
        temp_sz   = div_sz;
        curr_ptr += div_sz;

        if (*curr_ptr == val)
        {
            if (idx_ptr)
            {
                *idx_ptr = USIZE_C(ptr - curr_ptr);
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

    return null;
}


void *
kdi_GenMemOpsBinarySearchBlockWithIndex_U16(usize *idx_ptr, u16 *ptr, usize sz, u16 val)
{
    u16  *curr_ptr = ptr;
    usize temp_sz, div_sz;

    while (sz)
    {
        div_sz   = ((sz / SZ_U16) / 2) * SZ_U16;
        temp_sz  = div_sz;
        curr_ptr = PBYTE_C(curr_ptr) + div_sz;

        if (*curr_ptr == val)
        {
            if (idx_ptr)
            {
                *idx_ptr = USIZE_C(ptr - curr_ptr);
            }
            return curr_ptr;
        }

        if (val < *curr_ptr)
        {
            curr_ptr = PBYTE_C(curr_ptr) - div_sz;
        }

        if (val > *curr_ptr)
        {
            div_sz = sz - div_sz;
        }

        sz = temp_sz;
    }

    return null;
}


void *
kdi_GenMemOpsBinarySearchBlockWithIndex_U32(usize *idx_ptr, u32 *ptr, usize sz, u32 val)
{
    u32  *curr_ptr = ptr;
    usize temp_sz, div_sz;

    while (sz)
    {
        div_sz   = ((sz / SZ_U32) / 2) * SZ_U32;
        temp_sz  = div_sz;
        curr_ptr = PBYTE_C(curr_ptr) + div_sz;

        if (*curr_ptr == val)
        {
            if (idx_ptr)
            {
                *idx_ptr = USIZE_C(ptr - curr_ptr);
            }
            return curr_ptr;
        }

        if (val < *curr_ptr)
        {
            curr_ptr = PBYTE_C(curr_ptr) - div_sz;
        }

        if (val > *curr_ptr)
        {
            div_sz = sz - div_sz;
        }

        sz = temp_sz;
    }

    return null;
}


#if defined ARCH_64BIT_INT
void *
kdi_GenMemOpsBinarySearchBlockWithIndex_U64(usize *idx_ptr, u64 *ptr, usize sz, u64 val)
{
    u64  *curr_ptr = ptr;
    usize temp_sz, div_sz;

    while (sz)
    {
        div_sz   = ((sz / SZ_U64) / 2) * SZ_U64;
        temp_sz  = div_sz;
        curr_ptr = PBYTE_C(curr_ptr) + div_sz;

        if (*curr_ptr == val)
        {
            if (idx_ptr)
            {
                *idx_ptr = USIZE_C(ptr - curr_ptr);
            }
            return curr_ptr;
        }

        if (val < *curr_ptr)
        {
            curr_ptr = PBYTE_C(curr_ptr) - div_sz;
        }

        if (val > *curr_ptr)
        {
            div_sz = sz - div_sz;
        }

        sz = temp_sz;
    }

    return null;
}
#endif


void *
kdi_GenMemOpsFindBlockWithIndex_Un(usize *idx_ptr, void *ptr, usize sz, void *block, usize block_sz)
{
    byte *src_ptr = ptr, *temp_src_ptr, *block_ptr;
    usize i, idx = 0, temp_sz, match_cnt;

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

    return null;
}
 */
