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


void
kdi_GenMemOpsConcat(byte *dst, usize dst_sz, byte *src_1, usize src_1_sz, byte *src_2, usize src_2_sz)
{
    while (src_1_sz-- && dst_sz--)
    {
        *dst = *src_1;
        ++dst;
        ++src_1;
    }

    while (src_2_sz-- && dst_sz--)
    {
        *dst = *src_2;
        ++dst;
        ++src_2;
    }
}


void
kdi_GenMemOpsSetBlocks_U8(u8 *dst, usize sz, u8 val)
{
    while (sz--)
    {
        *dst = val;
        ++dst;
    }
}


void
kdi_GenMemOpsSetBlocks_U16(u16 *dst, usize sz, u16 val)
{
    while (sz)
    {
        *dst = val;
        ++dst;
        sz -= SZ_U16;
    }
}


void
kdi_GenMemOpsSetBlocks_U32(u32 *dst, usize sz, u32 val)
{
    while (sz)
    {
        *dst = val;
        ++dst;
        sz -= SZ_U32;
    }
}


#if defined ARCH_64BIT_INT
void
kdi_GenMemOpsSetBlocks_U64(u64 *dst, usize sz, u64 val)
{
    while (sz)
    {
        *dst = val;
        ++dst;
        sz -= SZ_U64;
    }
}
#endif


void
kdi_GenMemOpsSetBlocks_Un(byte *dst, usize dst_sz, byte *block, usize block_sz)
{
    byte *block_begin = block, *block_end = block + block_sz - 1;

    while (dst_sz--)
    {
        *dst = *block_begin;
        ++dst;
        block_begin = block_begin == block_end ? block : (block_begin + 1);
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
    u16 *end = PU16_C(PBYTE_C(ptr) + sz);
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
    u32 *end = PU32_C(PBYTE_C(ptr) + sz);
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
    u64 *end = PU64_C(PBYTE_C(ptr) + sz);
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
kdi_GenMemOpsReverseBlocks_Un(byte *ptr, usize ptr_sz, usize block_sz)
{
    byte *end       = ptr + ptr_sz;
    byte *end_begin = end - block_sz;
    byte *end_end   = end - 1;
    byte *temp_end  = end_begin;
    byte  temp_val;

    while (ptr_sz-- && ptr < end)
    {
        --end;

        temp_val  = *ptr;
        *ptr      = *temp_end;
        *temp_end = temp_val;

        if (temp_end == end_end)
        {
            end_begin = end - block_sz;
            end_end   = end - 1;
            temp_end  = end_begin;
        }
        else
        {
            ++temp_end;
        }

        ++ptr;
    }
}


void
kdi_GenMemOpsSwapBlocks_U8(u8 *ptr, usize idx_1, usize idx_2)
{
    u8 *temp_ptr  = ptr + idx_1;
    u8  temp_val  = *temp_ptr;

    ptr          += idx_2;
    *temp_ptr     = *ptr;
    *ptr          = temp_val;
}


void
kdi_GenMemOpsSwapBlocks_U16(u16 *ptr, usize idx_1, usize idx_2)
{
    u16 *temp_ptr = PU16_C(PU8_C(ptr) + idx_1);
    u16  temp_val = *temp_ptr;

    ptr           = PU16_C(PU8_C(ptr) + idx_2);
    *temp_ptr     = *ptr;
    *ptr          = temp_val;
}


void
kdi_GenMemOpsSwapBlocks_U32(u32 *ptr, usize idx_1, usize idx_2)
{
    u32 *temp_ptr = PU32_C(PU8_C(ptr) + idx_1);
    u32  temp_val = *temp_ptr;

    ptr           = PU32_C(PU8_C(ptr) + idx_2);
    *temp_ptr     = *ptr;
    *ptr          = temp_val;
}


#if defined ARCH_64BIT_INT
void
kdi_GenMemOpsSwapBlocks_U64(u64 *ptr, usize idx_1, usize idx_2)
{
    u64 *temp_ptr = PU64_C(PU8_C(ptr) + idx_1);
    u64  temp_val = *temp_ptr;

    ptr           = PU64_C(PU8_C(ptr) + idx_2);
    *temp_ptr     = *ptr;
    *ptr          = temp_val;
}
#endif


void
kdi_GenMemOpsSwapBlocks_Un(byte *ptr, usize idx_1, usize idx_2, usize block_sz)
{
    byte *temp_ptr = ptr + idx_2;
    byte  temp_val;

    ptr += idx_1;

    while (block_sz--)
    {
        temp_val  = *ptr;
        *ptr      = *temp_ptr;
        *temp_ptr = temp_val;

        ++ptr;
        ++temp_ptr;
    }
}


void
kdi_GenMemOpsSwapBlockRefs_U8(u8 *ptr_1, u8 *ptr_2)
{
    u8 temp_val = *ptr_1;
    *ptr_1      = *ptr_2;
    *ptr_2      = temp_val;
}


void
kdi_GenMemOpsSwapBlockRefs_U16(u16 *ptr_1, u16 *ptr_2)
{
    u16 temp_val = *ptr_1;
    *ptr_1       = *ptr_2;
    *ptr_2       = temp_val;
}


void
kdi_GenMemOpsSwapBlockRefs_U32(u32 *ptr_1, u32 *ptr_2)
{
    u32 temp_val = *ptr_1;
    *ptr_1       = *ptr_2;
    *ptr_2       = temp_val;
}


#if defined ARCH_64BIT_INT
void
kdi_GenMemOpsSwapBlockRefs_U64(u64 *ptr_1, u64 *ptr_2)
{
    u64 temp_val = *ptr_1;
    *ptr_1       = *ptr_2;
    *ptr_2       = temp_val;
}
#endif


void
kdi_GenMemOpsSwapBlockRefs_Un(byte *ptr_1, byte *ptr_2, usize block_sz)
{
    byte temp_val;

    while (block_sz--)
    {
        temp_val = *ptr_1;
        *ptr_1   = *ptr_2;
        *ptr_2   = temp_val;

        ++ptr_1;
        ++ptr_2;
    }
}


void
kdi_GenMemOpsRotateRight(byte *ptr, usize sz, usize k)
{
    byte *ptr_end = ptr + sz;
    byte  temp;
    usize left;

    sz   -= k;
    ptr  += sz;
    left  = sz % k;

    while (sz--)
    {
        --ptr_end;
        --ptr;

        temp     = *ptr_end;
        *ptr_end = *ptr;
        *ptr     = temp;
    }

    if (!left)
    {
        return;
    }

    kdi_GenMemOpsRotateRight(ptr, k, k - left);
}


void
kdi_GenMemOpsRotateLeft(byte *ptr, usize sz, usize k)
{
    byte *ptr_begin = ptr + k;
    byte  temp;
    usize right;

    sz    -= k;
    right  = sz % k;

    while (sz--)
    {
        temp       = *ptr_begin;
        *ptr_begin = *ptr;
        *ptr       = temp;

        ++ptr_begin;
        ++ptr;
    }

    if (!right)
    {
        return;
    }

    kdi_GenMemOpsRotateLeft(ptr, k, k - right);
}


void
kdi_GenMemOpsIsEqual(bool *result, byte *ptr_1, byte *ptr_2, usize sz)
{
    *result = true;

    while (sz-- && *result)
    {
        *result = *ptr_1 == *ptr_2;

        ++ptr_1;
        ++ptr_2;
    }
}


void
kdi_GenMemOpsIsVal(bool *result, byte *ptr, usize sz, byte val)
{
    *result = true;

    while (sz-- && *result)
    {
        *result = *ptr == val;
        ++ptr;
    }
}


void
kdi_GenMemOpsRegionOverlap(bool *result, byte *ptr_1, usize ptr_1_sz, byte *ptr_2, usize ptr_2_sz)
{
    byte *temp_ptr;
    usize temp_sz;

    if (ptr_1 > ptr_2)
    {
        temp_ptr = ptr_1;
        ptr_1    = ptr_2;
        ptr_2    = temp_ptr;

        temp_sz  = ptr_1_sz;
        ptr_1_sz = ptr_2_sz;
        ptr_2_sz = temp_sz;
    }

    *result = ptr_2 >= ptr_1 && ptr_2 < (ptr_1 + ptr_1_sz);
}


void
kdi_GenMemOpsRegionContains(bool *result, byte *base, usize base_sz, byte *ptr, usize ptr_sz)
{
    byte *base_end = base + base_sz;
    *result        = ptr >= base && ptr < base_end && (ptr + ptr_sz) <= base_end;
}


void
kdi_GenMemOpsElemCountFromBytes(usize *count, usize base_sz, usize elem_sz)
{
    *count = base_sz / elem_sz;
}


void
kdi_GenMemOpsBlockAt_U8(u8 *dst, u8 *src, usize idx)
{
    *dst = *(src + idx);
}


void
kdi_GenMemOpsBlockAt_U16(u16 *dst, u16 *src, usize idx)
{
    *dst = *PU16_C(PBYTE_C(src) + idx);
}


void
kdi_GenMemOpsBlockAt_U32(u32 *dst, u32 *src, usize idx)
{
    *dst = *PU32_C(PBYTE_C(src) + idx);
}


#if defined ARCH_64BIT_INT
void
kdi_GenMemOpsBlockAt_U64(u64 *dst, u64 *src, usize idx)
{
    *dst = *PU64_C(PBYTE_C(src) + idx);
}
#endif


void
kdi_GenMemOpsBlockAt_Un(byte *dst, byte *src, usize idx, usize block_sz)
{
    kdi_GenMemOpsCopy(dst, src + idx, block_sz);
}


void
kdi_GenMemOpsSetBlockAt_U8(u8 *dst, usize idx, u8 val)
{
    dst  += idx;
    *dst  = val;
}


void
kdi_GenMemOpsSetBlockAt_U16(u16 *dst, usize idx, u16 val)
{
    dst  = PU16_C(PBYTE_C(dst) + idx);
    *dst = val;
}


void
kdi_GenMemOpsSetBlockAt_U32(u32 *dst, usize idx, u32 val)
{
    dst  = PU32_C(PBYTE_C(dst) + idx);
    *dst = val;
}


#if defined ARCH_64BIT_INT
void
kdi_GenMemOpsSetBlockAt_U64(u64 *dst, usize idx, u64 val)
{
    dst  = PU64_C(PBYTE_C(dst) + idx);
    *dst = val;
}
#endif


void
kdi_GenMemOpsSetBlockAt_Un(byte *dst, usize idx, byte *block, usize block_sz)
{
    kdi_GenMemOpsCopy(dst + idx, block, block_sz);
}


void
kdi_GenMemOpsInsertBlockAt_U8(u8 *dst, usize *dst_sz, usize idx, u8 val)
{
    u8   *ptr        = dst + *dst_sz;
    u8   *ptr_before = ptr - 1;
    usize temp_sz    = *dst_sz - idx;

    while (temp_sz--)
    {
        *ptr = *ptr_before;

        --ptr;
        --ptr_before;
    }

    *ptr    = val;
    *dst_sz = *dst_sz + 1;
}


void
kdi_GenMemOpsInsertBlockAt_U16(u16 *dst, usize *dst_sz, usize idx, u16 val)
{
    u16  *ptr        = PU16_C(PBYTE_C(dst) + *dst_sz);
    u16  *ptr_before = ptr - 1;
    usize temp_sz    = *dst_sz - idx;

    while (temp_sz)
    {
        *ptr = *ptr_before;

        --ptr;
        --ptr_before;
        temp_sz -= SZ_U16;
    }

    *ptr    = val;
    *dst_sz = *dst_sz + SZ_U16;
}


void
kdi_GenMemOpsInsertBlockAt_U32(u32 *dst, usize *dst_sz, usize idx, u32 val)
{
    u32  *ptr        = PU32_C(PBYTE_C(dst) + *dst_sz);
    u32  *ptr_before = ptr - 1;
    usize temp_sz    = *dst_sz - idx;

    while (temp_sz)
    {
        *ptr = *ptr_before;

        --ptr;
        --ptr_before;
        temp_sz -= SZ_U32;
    }

    *ptr    = val;
    *dst_sz = *dst_sz + SZ_U32;
}


#if defined ARCH_64BIT_INT
void
kdi_GenMemOpsInsertBlockAt_U64(u64 *dst, usize *dst_sz, usize idx, u64 val)
{
    u64  *ptr        = PU64_C(PBYTE_C(dst) + *dst_sz);
    u64  *ptr_before = ptr - 1;
    usize temp_sz    = *dst_sz - idx;

    while (temp_sz)
    {
        *ptr = *ptr_before;

        --ptr;
        --ptr_before;
        temp_sz -= SZ_U64;
    }

    *ptr    = val;
    *dst_sz = *dst_sz + SZ_U64;
}
#endif


void
kdi_GenMemOpsInsertBlockAt_Un(byte *dst, usize *dst_sz, usize idx, byte *block, usize block_sz)
{
    byte *ptr        = dst + *dst_sz + block_sz;
    byte *ptr_before = ptr - block_sz;
    usize temp_sz    = *dst_sz - idx;

    while (temp_sz--)
    {
        --ptr;
        --ptr_before;

        *ptr = *ptr_before;
    }

    kdi_GenMemOpsCopy(ptr_before, block, block_sz);

    *dst_sz = *dst_sz + block_sz;
}


void
kdi_GenMemOpsRemoveBlockAt_U8(u8 *dst, usize *dst_sz, usize idx)
{
    u8   *ptr_after;
    usize temp_sz  = *dst_sz - idx;

    dst           += idx;
    ptr_after      = dst + 1;

    while (temp_sz--)
    {
        *dst = *ptr_after;

        ++dst;
        ++ptr_after;
    }

    *dst_sz = *dst_sz - 1;
}


void
kdi_GenMemOpsRemoveBlockAt_U16(u16 *dst, usize *dst_sz, usize idx)
{
    u16  *ptr_after;
    usize temp_sz = *dst_sz - idx;

    dst           = PU16_C(PBYTE_C(dst) + idx);
    ptr_after     = dst + 1;

    while (temp_sz)
    {
        *dst = *ptr_after;

        ++dst;
        ++ptr_after;
        temp_sz -= SZ_U16;
    }

    *dst_sz = *dst_sz - SZ_U16;
}


void
kdi_GenMemOpsRemoveBlockAt_U32(u32 *dst, usize *dst_sz, usize idx)
{
    u32  *ptr_after;
    usize temp_sz = *dst_sz - idx;

    dst           = PU32_C(PBYTE_C(dst) + idx);
    ptr_after     = dst + 1;

    while (temp_sz)
    {
        *dst = *ptr_after;

        ++dst;
        ++ptr_after;
        temp_sz -= SZ_U32;
    }

    *dst_sz = *dst_sz - SZ_U32;
}


#if defined ARCH_64BIT_INT
void
kdi_GenMemOpsRemoveBlockAt_U64(u64 *dst, usize *dst_sz, usize idx)
{
    u64  *ptr_after;
    usize temp_sz = *dst_sz - idx;

    dst           = PU64_C(PBYTE_C(dst) + idx);
    ptr_after     = dst + 1;

    while (temp_sz)
    {
        *dst = *ptr_after;

        ++dst;
        ++ptr_after;
        temp_sz -= SZ_U64;
    }

    *dst_sz = *dst_sz - SZ_U64;
}
#endif


void
kdi_GenMemOpsRemoveBlockAt_Un(byte *dst, usize *dst_sz, usize idx, usize block_sz)
{
    byte *ptr_after;
    usize temp_sz  = *dst_sz - idx;

    dst           += idx;
    ptr_after      = dst + block_sz;

    while (temp_sz--)
    {
        *dst = *ptr_after;

        ++dst;
        ++ptr_after;
    }

    *dst_sz = *dst_sz - block_sz;
}


void
kdi_GenMemOpsCountBlocks_U8(usize *count, u8 *ptr, usize sz, u8 item)
{
    while (sz--)
    {
        *count += *ptr == item;
        ++ptr;
    }
}


void
kdi_GenMemOpsCountBlocks_U16(usize *count, u16 *ptr, usize sz, u16 item)
{
    while (sz)
    {
        *count += (*ptr == item) ? SZ_U16 : 0;

        ++ptr;
        sz -= SZ_U16;
    }
}


void
kdi_GenMemOpsCountBlocks_U32(usize *count, u32 *ptr, usize sz, u32 item)
{
    while (sz)
    {
        *count += (*ptr == item) ? SZ_U32 : 0;

        ++ptr;
        sz -= SZ_U32;
    }
}


#if defined ARCH_64BIT_INT
void
kdi_GenMemOpsCountBlocks_U64(usize *count, u64 *ptr, usize sz, u64 item)
{
    while (sz)
    {
        *count += (*ptr == item) ? SZ_U64 : 0;

        ++ptr;
        sz -= SZ_U64;
    }
}
#endif


void
kdi_GenMemOpsCountBlocks_Un(usize *count, byte *ptr, usize sz, byte *block, usize block_sz)
{
    byte *block_begin = block;
    byte *block_end   = block + block_sz - 1;
    usize match_count = 0;
    bool  match;

    while (sz--)
    {
        match_count += *ptr == *block_begin;

        match        = match_count == block_sz;

        if (block_begin == block_end)
        {
            *count      += match ? block_sz : 0;
            match_count  = 0;
            block_begin  = block;
        }
        else
        {
            match_count = match ? 0 : match_count;
            ++block_begin;
        }

        ++ptr;
    }
}


void
kdi_GenMemOpsCountNotBlocks_U8(usize *count, u8 *ptr, usize sz, u8 item)
{
    while (sz--)
    {
        *count += *ptr != item;
        ++ptr;
    }
}


void
kdi_GenMemOpsCountNotBlocks_U16(usize *count, u16 *ptr, usize sz, u16 item)
{
    while (sz)
    {
        *count += (*ptr != item) ? SZ_U16 : 0;

        ++ptr;
        sz -= SZ_U16;
    }
}


void
kdi_GenMemOpsCountNotBlocks_U32(usize *count, u32 *ptr, usize sz, u32 item)
{
    while (sz)
    {
        *count += (*ptr != item) ? SZ_U32 : 0;

        ++ptr;
        sz -= SZ_U32;
    }
}


#if defined ARCH_64BIT_INT
void
kdi_GenMemOpsCountNotBlocks_U64(usize *count, u64 *ptr, usize sz, u64 item)
{
    while (sz)
    {
        *count += (*ptr != item) ? SZ_U64 : 0;

        ++ptr;
        sz -= SZ_U64;
    }
}
#endif


void
kdi_GenMemOpsCountNotBlocks_Un(usize *count, byte *ptr, usize sz, byte *block, usize block_sz)
{
    byte *block_begin = block;
    byte *block_end   = block + block_sz - 1;
    usize match_count = 0;
    bool  match;

    while (sz--)
    {
        match_count += *ptr == *block_begin;

        match        = match_count == block_sz;

        if (block_begin == block_end)
        {
            *count      += match ? 0 : block_sz;
            match_count  = 0;
            block_begin  = block;
        }
        else
        {
            match_count = match ? 0 : match_count;
            ++block_begin;
        }

        ++ptr;
    }
}


bool
kdi_GenMemOpsFindBlockIndex_U8(usize *idx, u8 *ptr, usize sz, u8 item)
{
    usize curr_idx = 0;

    while (sz--)
    {
        if (*ptr == item)
        {
            *idx = curr_idx;
            return RESULT_SUCCESS;
        }

        ++ptr;
        ++curr_idx;
    }

    return RESULT_FAILURE;
}


bool
kdi_GenMemOpsFindBlockIndex_U16(usize *idx, u16 *ptr, usize sz, u16 item)
{
    usize curr_idx = 0;

    while (sz)
    {
        if (*ptr == item)
        {
            *idx = curr_idx;
            return RESULT_SUCCESS;
        }

        ++ptr;
        curr_idx += SZ_U16;
        sz       -= SZ_U16;
    }

    return RESULT_FAILURE;
}


bool
kdi_GenMemOpsFindBlockIndex_U32(usize *idx, u32 *ptr, usize sz, u32 item)
{
    usize curr_idx = 0;

    while (sz)
    {
        if (*ptr == item)
        {
            *idx = curr_idx;
            return RESULT_SUCCESS;
        }

        ++ptr;
        curr_idx += SZ_U32;
        sz       -= SZ_U32;
    }

    return RESULT_FAILURE;
}


#if defined ARCH_64BIT_INT
bool
kdi_GenMemOpsFindBlockIndex_U64(usize *idx, u64 *ptr, usize sz, u64 item)
{
    usize curr_idx = 0;

    while (sz)
    {
        if (*ptr == item)
        {
            *idx = curr_idx;
            return RESULT_SUCCESS;
        }

        ++ptr;
        curr_idx += SZ_U64;
        sz       -= SZ_U64;
    }

    return RESULT_FAILURE;
}
#endif


bool
kdi_GenMemOpsFindBlockIndex_Un(usize *idx, byte *ptr, usize sz, byte *block, usize block_sz)
{
    usize curr_idx    = 0;
    byte *block_begin = block;
    byte *block_end   = block + block_sz - 1;
    usize match_count = 0;
    bool  match;

    while (sz--)
    {
        match_count += *ptr == *block_begin;
        match        = match_count == block_sz;

        if (match)
        {
            *idx = curr_idx;
            return RESULT_SUCCESS;
        }

        if (block_begin == block_end)
        {
            match_count  = 0;
            curr_idx    += block_sz;
            block_begin  = block;
        }
        else
        {
            match_count = match ? 0 : match_count;
            ++block_begin;
        }

        ++ptr;
    }

    return RESULT_FAILURE;
}


bool
kdi_GenMemOpsFindNotBlockIndex_U8(usize *idx, u8 *ptr, usize sz, u8 item)
{
    usize curr_idx = 0;

    while (sz--)
    {
        if (*ptr != item)
        {
            *idx = curr_idx;
            return RESULT_SUCCESS;
        }

        ++ptr;
        ++curr_idx;
    }

    return RESULT_FAILURE;
}


bool
kdi_GenMemOpsFindNotBlockIndex_U16(usize *idx, u16 *ptr, usize sz, u16 item)
{
    usize curr_idx = 0;

    while (sz)
    {
        if (*ptr != item)
        {
            *idx = curr_idx;
            return RESULT_SUCCESS;
        }

        ++ptr;
        curr_idx += SZ_U16;
        sz       -= SZ_U16;
    }

    return RESULT_FAILURE;
}


bool
kdi_GenMemOpsFindNotBlockIndex_U32(usize *idx, u32 *ptr, usize sz, u32 item)
{
    usize curr_idx = 0;

    while (sz)
    {
        if (*ptr != item)
        {
            *idx = curr_idx;
            return RESULT_SUCCESS;
        }

        ++ptr;
        curr_idx += SZ_U32;
        sz       -= SZ_U32;
    }

    return RESULT_FAILURE;
}


#if defined ARCH_64BIT_INT
bool
kdi_GenMemOpsFindNotBlockIndex_U64(usize *idx, u64 *ptr, usize sz, u64 item)
{
    usize curr_idx = 0;

    while (sz)
    {
        if (*ptr != item)
        {
            *idx = curr_idx;
            return RESULT_SUCCESS;
        }

        ++ptr;
        curr_idx += SZ_U64;
        sz       -= SZ_U64;
    }

    return RESULT_FAILURE;
}
#endif


bool
kdi_GenMemOpsFindNotBlockIndex_Un(usize *idx, byte *ptr, usize sz, byte *block, usize block_sz)
{
    usize curr_idx    = 0;
    byte *block_begin = block;
    byte *block_end   = block + block_sz - 1;
    usize match_count = 0;
    bool  match;

    while (sz--)
    {
        match_count += *ptr == *block_begin;
        match        = match_count == block_sz;

        if (block_begin == block_end)
        {
            if (!match)
            {
                *idx = curr_idx;
                return RESULT_SUCCESS;
            }

            match_count  = 0;
            curr_idx    += block_sz;
            block_begin  = block;
        }
        else
        {
            match_count = match ? 0 : match_count;
            ++block_begin;
        }

        ++ptr;
    }

    return RESULT_FAILURE;
}


bool
kdi_GenMemOpsFindLastBlockIndex_U8(usize *idx, u8 *ptr, usize sz, u8 item)
{
    usize curr_idx  = sz;

    ptr            += sz;

    while (sz--)
    {
        --ptr;
        --curr_idx;

        if (*ptr == item)
        {
            *idx = curr_idx;
            return RESULT_SUCCESS;
        }
    }

    return RESULT_FAILURE;
}


bool
kdi_GenMemOpsFindLastBlockIndex_U16(usize *idx, u16 *ptr, usize sz, u16 item)
{
    usize curr_idx = sz;

    ptr            = PU16_C(PBYTE_C(ptr) + sz);

    while (sz)
    {
        --ptr;
        curr_idx -= SZ_U16;
        sz       -= SZ_U16;

        if (*ptr == item)
        {
            *idx = curr_idx;
            return RESULT_SUCCESS;
        }
    }

    return RESULT_FAILURE;
}


bool
kdi_GenMemOpsFindLastBlockIndex_U32(usize *idx, u32 *ptr, usize sz, u32 item)
{
    usize curr_idx = sz;

    ptr            = PU32_C(PBYTE_C(ptr) + sz);

    while (sz)
    {
        --ptr;
        curr_idx -= SZ_U32;
        sz       -= SZ_U32;

        if (*ptr == item)
        {
            *idx = curr_idx;
            return RESULT_SUCCESS;
        }
    }

    return RESULT_FAILURE;
}


#if defined ARCH_64BIT_INT
bool
kdi_GenMemOpsFindLastBlockIndex_U64(usize *idx, u64 *ptr, usize sz, u64 item)
{
    usize curr_idx = sz;

    ptr            = PU64_C(PBYTE_C(ptr) + sz);

    while (sz)
    {
        --ptr;
        curr_idx -= SZ_U64;
        sz       -= SZ_U64;

        if (*ptr == item)
        {
            *idx = curr_idx;
            return RESULT_SUCCESS;
        }
    }

    return RESULT_FAILURE;
}
#endif


bool
kdi_GenMemOpsFindLastBlockIndex_Un(usize *idx, byte *ptr, usize sz, byte *block, usize block_sz)
{
    usize curr_idx     = sz - block_sz;
    byte *block_begin  = block, *block_end;
    usize match_count  = 0;
    bool  match        = false;

    ptr               += sz - 1;
    block             += block_sz - 1;
    block_end          = block;

    while (sz--)
    {
        match_count += *ptr == *block_end;
        match        = match_count == block_sz;

        if (match)
        {
            *idx = curr_idx;
            return RESULT_SUCCESS;
        }

        if (block_begin == block_end)
        {
            match_count  = 0;
            curr_idx    -= block_sz;
            block_end    = block;
        }
        else
        {
            match_count = match ? 0 : match_count;
            --block_end;
        }

        --ptr;
    }

    return RESULT_FAILURE;
}


bool
kdi_GenMemOpsFindLastNotBlockIndex_U8(usize *idx, u8 *ptr, usize sz, u8 item)
{
    usize curr_idx  = sz;

    ptr            += sz;

    while (sz--)
    {
        --ptr;
        --curr_idx;

        if (*ptr != item)
        {
            *idx = curr_idx;
            return RESULT_SUCCESS;
        }
    }

    return RESULT_FAILURE;
}


bool
kdi_GenMemOpsFindLastNotBlockIndex_U16(usize *idx, u16 *ptr, usize sz, u16 item)
{
    usize curr_idx = sz;

    ptr            = PU16_C(PBYTE_C(ptr) + sz);

    while (sz)
    {
        --ptr;
        curr_idx -= SZ_U16;
        sz       -= SZ_U16;

        if (*ptr != item)
        {
            *idx = curr_idx;
            return RESULT_SUCCESS;
        }
    }

    return RESULT_FAILURE;
}


bool
kdi_GenMemOpsFindLastNotBlockIndex_U32(usize *idx, u32 *ptr, usize sz, u32 item)
{
    usize curr_idx = sz;

    ptr            = PU32_C(PBYTE_C(ptr) + sz);

    while (sz)
    {
        --ptr;
        curr_idx -= SZ_U32;
        sz       -= SZ_U32;

        if (*ptr != item)
        {
            *idx = curr_idx;
            return RESULT_SUCCESS;
        }
    }

    return RESULT_FAILURE;
}


#if defined ARCH_64BIT_INT
bool
kdi_GenMemOpsFindLastNotBlockIndex_U64(usize *idx, u64 *ptr, usize sz, u64 item)
{
    usize curr_idx = sz;

    ptr            = PU64_C(PBYTE_C(ptr) + sz);

    while (sz)
    {
        --ptr;
        curr_idx -= SZ_U64;
        sz       -= SZ_U64;

        if (*ptr != item)
        {
            *idx = curr_idx;
            return RESULT_SUCCESS;
        }
    }

    return RESULT_FAILURE;
}
#endif


bool
kdi_GenMemOpsFindLastNotBlockIndex_Un(usize *idx, byte *ptr, usize sz, byte *block, usize block_sz)
{
    usize curr_idx     = sz - block_sz;
    byte *block_begin  = block, *block_end;
    usize match_count  = 0;
    bool  match        = false;

    ptr               += sz - 1;
    block             += block_sz - 1;
    block_end          = block;

    while (sz--)
    {
        match_count += *ptr == *block_end;
        match        = match_count == block_sz;

        if (block_begin == block_end)
        {
            if (!match)
            {
                *idx = curr_idx;
                return RESULT_SUCCESS;
            }

            match_count  = 0;
            curr_idx    -= block_sz;
            block_end    = block;
        }
        else
        {
            match_count = match ? 0 : match_count;
            --block_end;
        }

        --ptr;
    }

    return RESULT_FAILURE;
}


void
kdi_GenMemOpsFindBlockIndicesU8_IdxU8(u8 *idxs, usize idxs_sz, usize *found, u8 *ptr, usize ptr_sz, u8 item)
{
    u8 curr_idx = 0;

    while (ptr_sz-- && idxs_sz)
    {
        if (*ptr == item)
        {
            *idxs   = curr_idx;
            *found += 1;

            ++idxs;
            --idxs_sz;
        }

        ++ptr;
        ++curr_idx;
    }
}


void
kdi_GenMemOpsFindBlockIndicesU16_IdxU8(u8 *idxs, usize idxs_sz, usize *found, u16 *ptr, usize ptr_sz, u16 item)
{
    u8 curr_idx = 0;

    while (ptr_sz && idxs_sz)
    {
        if (*ptr == item)
        {
            *idxs   = curr_idx;
            *found += SZ_U16;

            ++idxs;
            --idxs_sz;
        }

        ++ptr;
        ptr_sz   -= SZ_U16;
        curr_idx += SZ_U16;
    }
}


void
kdi_GenMemOpsFindBlockIndicesU32_IdxU8(u8 *idxs, usize idxs_sz, usize *found, u32 *ptr, usize ptr_sz, u32 item)
{
    u8 curr_idx = 0;

    while (ptr_sz && idxs_sz)
    {
        if (*ptr == item)
        {
            *idxs   = curr_idx;
            *found += SZ_U32;

            ++idxs;
            --idxs_sz;
        }

        ++ptr;
        ptr_sz   -= SZ_U32;
        curr_idx += SZ_U32;
    }
}


#if defined ARCH_64BIT_INT
void
kdi_GenMemOpsFindBlockIndicesU64_IdxU8(u8 *idxs, usize idxs_sz, usize *found, u64 *ptr, usize ptr_sz, u64 item)
{
    u8 curr_idx = 0;

    while (ptr_sz && idxs_sz)
    {
        if (*ptr == item)
        {
            *idxs   = curr_idx;
            *found += SZ_U64;

            ++idxs;
            --idxs_sz;
        }

        ++ptr;
        ptr_sz   -= SZ_U64;
        curr_idx += SZ_U64;
    }
}
#endif


void
kdi_GenMemOpsFindBlockIndicesUn_IdxU8(u8 *idxs, usize idxs_sz, usize *found, byte *ptr, usize ptr_sz, byte *block, usize block_sz)
{
    u8    curr_idx    = 0;
    byte *block_begin = block;
    byte *block_end   = block + block_sz - 1;
    usize match_count = 0;
    bool  match;

    while (ptr_sz-- && idxs_sz)
    {
        match_count += *ptr == *block_begin;
        match        = match_count == block_sz;

        if (match)
        {
            *idxs   = curr_idx;
            *found += block_sz;

            ++idxs;
            --idxs_sz;
        }

        if (block_begin == block_end)
        {
            match_count  = 0;
            curr_idx    += U8_C(block_sz);
            block_begin  = block;
        }
        else
        {
            match_count = match ? 0 : match_count;
            ++block_begin;
        }

        ++ptr;
    }
}


void
kdi_GenMemOpsFindBlockIndicesU8_IdxU16(u16 *idxs, usize idxs_sz, usize *found, u8 *ptr, usize ptr_sz, u8 item)
{
    u16 curr_idx = 0;

    while (ptr_sz-- && idxs_sz)
    {
        if (*ptr == item)
        {
            *idxs   = curr_idx;
            *found += 1;

            ++idxs;
            idxs_sz -= SZ_U16;
        }

        ++ptr;
        ++curr_idx;
    }
}


void
kdi_GenMemOpsFindBlockIndicesU16_IdxU16(u16 *idxs, usize idxs_sz, usize *found, u16 *ptr, usize ptr_sz, u16 item)
{
    u16 curr_idx = 0;

    while (ptr_sz && idxs_sz)
    {
        if (*ptr == item)
        {
            *idxs   = curr_idx;
            *found += SZ_U16;

            ++idxs;
            idxs_sz -= SZ_U16;
        }

        ++ptr;
        ptr_sz   -= SZ_U16;
        curr_idx += SZ_U16;
    }
}


void
kdi_GenMemOpsFindBlockIndicesU32_IdxU16(u16 *idxs, usize idxs_sz, usize *found, u32 *ptr, usize ptr_sz, u32 item)
{
    u16 curr_idx = 0;

    while (ptr_sz && idxs_sz)
    {
        if (*ptr == item)
        {
            *idxs   = curr_idx;
            *found += SZ_U32;

            ++idxs;
            idxs_sz -= SZ_U16;
        }

        ++ptr;
        ptr_sz   -= SZ_U32;
        curr_idx += SZ_U32;
    }
}


#if defined ARCH_64BIT_INT
void
kdi_GenMemOpsFindBlockIndicesU64_IdxU16(u16 *idxs, usize idxs_sz, usize *found, u64 *ptr, usize ptr_sz, u64 item)
{
    u16 curr_idx = 0;

    while (ptr_sz && idxs_sz)
    {
        if (*ptr == item)
        {
            *idxs   = curr_idx;
            *found += SZ_U64;

            ++idxs;
            idxs_sz -= SZ_U16;
        }

        ++ptr;
        ptr_sz   -= SZ_U64;
        curr_idx += SZ_U64;
    }
}
#endif


void
kdi_GenMemOpsFindBlockIndicesUn_IdxU16(u16 *idxs, usize idxs_sz, usize *found, byte *ptr, usize ptr_sz, byte *block, usize block_sz)
{
    u16   curr_idx    = 0;
    byte *block_begin = block;
    byte *block_end   = block + block_sz - 1;
    usize match_count = 0;
    bool  match;

    while (ptr_sz-- && idxs_sz)
    {
        match_count += *ptr == *block_begin;
        match        = match_count == block_sz;

        if (match)
        {
            *idxs   = curr_idx;
            *found += block_sz;

            ++idxs;
            --idxs_sz;
        }

        if (block_begin == block_end)
        {
            match_count  = 0;
            curr_idx    += U16_C(block_sz);
            block_begin  = block;
        }
        else
        {
            match_count = match ? 0 : match_count;
            ++block_begin;
        }

        ++ptr;
    }
}


void
kdi_GenMemOpsFindBlockIndicesU8_IdxU32(u32 *idxs, usize idxs_sz, usize *found, u8 *ptr, usize ptr_sz, u8 item)
{
    u32 curr_idx = 0;

    while (ptr_sz-- && idxs_sz)
    {
        if (*ptr == item)
        {
            *idxs   = curr_idx;
            *found += 1;

            ++idxs;
            idxs_sz -= SZ_U32;
        }

        ++ptr;
        ++curr_idx;
    }
}


void
kdi_GenMemOpsFindBlockIndicesU16_IdxU32(u32 *idxs, usize idxs_sz, usize *found, u16 *ptr, usize ptr_sz, u16 item)
{
    u32 curr_idx = 0;

    while (ptr_sz && idxs_sz)
    {
        if (*ptr == item)
        {
            *idxs   = curr_idx;
            *found += SZ_U16;

            ++idxs;
            idxs_sz -= SZ_U32;
        }

        ++ptr;
        ptr_sz   -= SZ_U16;
        curr_idx += SZ_U16;
    }
}


void
kdi_GenMemOpsFindBlockIndicesU32_IdxU32(u32 *idxs, usize idxs_sz, usize *found, u32 *ptr, usize ptr_sz, u32 item)
{
    u32 curr_idx = 0;

    while (ptr_sz && idxs_sz)
    {
        if (*ptr == item)
        {
            *idxs   = curr_idx;
            *found += SZ_U32;

            ++idxs;
            idxs_sz -= SZ_U32;
        }

        ++ptr;
        ptr_sz   -= SZ_U32;
        curr_idx += SZ_U32;
    }
}


#if defined ARCH_64BIT_INT
void
kdi_GenMemOpsFindBlockIndicesU64_IdxU32(u32 *idxs, usize idxs_sz, usize *found, u64 *ptr, usize ptr_sz, u64 item)
{
    u32 curr_idx = 0;

    while (ptr_sz && idxs_sz)
    {
        if (*ptr == item)
        {
            *idxs   = curr_idx;
            *found += SZ_U64;

            ++idxs;
            idxs_sz -= SZ_U32;
        }

        ++ptr;
        ptr_sz   -= SZ_U64;
        curr_idx += SZ_U64;
    }
}
#endif


void
kdi_GenMemOpsFindBlockIndicesUn_IdxU32(u32 *idxs, usize idxs_sz, usize *found, byte *ptr, usize ptr_sz, byte *block, usize block_sz)
{
    u32   curr_idx    = 0;
    byte *block_begin = block;
    byte *block_end   = block + block_sz - 1;
    usize match_count = 0;
    bool  match;

    while (ptr_sz-- && idxs_sz)
    {
        match_count += *ptr == *block_begin;
        match        = match_count == block_sz;

        if (match)
        {
            *idxs   = curr_idx;
            *found += block_sz;

            ++idxs;
            --idxs_sz;
        }

        if (block_begin == block_end)
        {
            match_count  = 0;
            curr_idx    += U32_C(block_sz);
            block_begin  = block;
        }
        else
        {
            match_count = match ? 0 : match_count;
            ++block_begin;
        }

        ++ptr;
    }
}


#if defined KD_ARCH_64BIT_INT
void
kdi_GenMemOpsFindBlockIndicesU8_IdxU64(u64 *idxs, usize idxs_sz, usize *found, u8 *ptr, usize ptr_sz, u8 item)
{
    u64 curr_idx = 0;

    while (ptr_sz-- && idxs_sz)
    {
        if (*ptr == item)
        {
            *idxs   = curr_idx;
            *found += 1;

            ++idxs;
            idxs_sz -= SZ_U64;
        }

        ++ptr;
        ++curr_idx;
    }
}


void
kdi_GenMemOpsFindBlockIndicesU16_IdxU64(u64 *idxs, usize idxs_sz, usize *found, u16 *ptr, usize ptr_sz, u16 item)
{
    u64 curr_idx = 0;

    while (ptr_sz && idxs_sz)
    {
        if (*ptr == item)
        {
            *idxs   = curr_idx;
            *found += SZ_U16;

            ++idxs;
            idxs_sz -= SZ_U64;
        }

        ++ptr;
        ptr_sz   -= SZ_U16;
        curr_idx += SZ_U16;
    }
}


void
kdi_GenMemOpsFindBlockIndicesU32_IdxU64(u64 *idxs, usize idxs_sz, usize *found, u32 *ptr, usize ptr_sz, u32 item)
{
    u64 curr_idx = 0;

    while (ptr_sz && idxs_sz)
    {
        if (*ptr == item)
        {
            *idxs   = curr_idx;
            *found += SZ_U32;

            ++idxs;
            idxs_sz -= SZ_U64;
        }

        ++ptr;
        ptr_sz   -= SZ_U32;
        curr_idx += SZ_U32;
    }
}


void
kdi_GenMemOpsFindBlockIndicesU64_IdxU64(u64 *idxs, usize idxs_sz, usize *found, u64 *ptr, usize ptr_sz, u64 item)
{
    u64 curr_idx = 0;

    while (ptr_sz && idxs_sz)
    {
        if (*ptr == item)
        {
            *idxs   = curr_idx;
            *found += SZ_U64;

            ++idxs;
            idxs_sz -= SZ_U64;
        }

        ++ptr;
        ptr_sz   -= SZ_U64;
        curr_idx += SZ_U64;
    }
}


void
kdi_GenMemOpsFindBlockIndicesUn_IdxU64(u64 *idxs, usize idxs_sz, usize *found, byte *ptr, usize ptr_sz, byte *block, usize block_sz)
{
    u64   curr_idx    = 0;
    byte *block_begin = block;
    byte *block_end   = block + block_sz - 1;
    usize match_count = 0;
    bool  match;

    while (ptr_sz-- && idxs_sz)
    {
        match_count += *ptr == *block_begin;
        match        = match_count == block_sz;

        if (match)
        {
            *idxs   = curr_idx;
            *found += block_sz;

            ++idxs;
            --idxs_sz;
        }

        if (block_begin == block_end)
        {
            match_count  = 0;
            curr_idx    += U64_C(block_sz);
            block_begin  = block;
        }
        else
        {
            match_count = match ? 0 : match_count;
            ++block_begin;
        }

        ++ptr;
    }
}
#endif


void
kdi_GenMemOpsFindNotBlockIndicesU8_IdxU8(u8 *idxs, usize idxs_sz, usize *found, u8 *ptr, usize ptr_sz, u8 item)
{
    u8 curr_idx = 0;

    while (ptr_sz-- && idxs_sz)
    {
        if (*ptr != item)
        {
            *idxs   = curr_idx;
            *found += 1;

            ++idxs;
            --idxs_sz;
        }

        ++ptr;
        ++curr_idx;
    }
}


void
kdi_GenMemOpsFindNotBlockIndicesU16_IdxU8(u8 *idxs, usize idxs_sz, usize *found, u16 *ptr, usize ptr_sz, u16 item)
{
    u8 curr_idx = 0;

    while (ptr_sz && idxs_sz)
    {
        if (*ptr != item)
        {
            *idxs   = curr_idx;
            *found += 1;

            ++idxs;
            --idxs_sz;
        }

        ++ptr;
        ptr_sz   -= SZ_U16;
        curr_idx += SZ_U16;
    }
}


void
kdi_GenMemOpsFindNotBlockIndicesU32_IdxU8(u8 *idxs, usize idxs_sz, usize *found, u32 *ptr, usize ptr_sz, u32 item)
{
    u8 curr_idx = 0;

    while (ptr_sz && idxs_sz)
    {
        if (*ptr != item)
        {
            *idxs   = curr_idx;
            *found += 1;

            ++idxs;
            --idxs_sz;
        }

        ++ptr;
        ptr_sz   -= SZ_U32;
        curr_idx += SZ_U32;
    }
}


#if defined ARCH_64BIT_INT
void
kdi_GenMemOpsFindNotBlockIndicesU64_IdxU8(u8 *idxs, usize idxs_sz, usize *found, u64 *ptr, usize ptr_sz, u64 item)
{
    u8 curr_idx = 0;

    while (ptr_sz && idxs_sz)
    {
        if (*ptr != item)
        {
            *idxs   = curr_idx;
            *found += 1;

            ++idxs;
            --idxs_sz;
        }

        ++ptr;
        ptr_sz   -= SZ_U64;
        curr_idx += SZ_U64;
    }
}
#endif


void
kdi_GenMemOpsFindNotBlockIndicesUn_IdxU8(u8 *idxs, usize idxs_sz, usize *found, byte *ptr, usize ptr_sz, byte *block, usize block_sz)
{
    u8    curr_idx    = 0;
    byte *block_begin = block;
    byte *block_end   = block + block_sz - 1;
    usize match_count = 0;
    bool  match;

    while (ptr_sz-- && idxs_sz)
    {
        match_count += *ptr == *block_begin;
        match        = match_count == block_sz;

        if (block_begin == block_end)
        {
            if (!match)
            {
                *idxs   = curr_idx;
                *found += 1;

                ++idxs;
                --idxs_sz;
            }

            match_count  = 0;
            curr_idx    += U8_C(block_sz);
            block_begin  = block;
        }
        else
        {
            match_count = match ? 0 : match_count;
            ++block_begin;
        }

        ++ptr;
    }
}


void
kdi_GenMemOpsFindNotBlockIndicesU8_IdxU16(u16 *idxs, usize idxs_sz, usize *found, u8 *ptr, usize ptr_sz, u8 item)
{
    u16 curr_idx = 0;

    while (ptr_sz-- && idxs_sz)
    {
        if (*ptr != item)
        {
            *idxs   = curr_idx;
            *found += SZ_U16;

            ++idxs;
            idxs_sz -= SZ_U16;
        }

        ++ptr;
        ++curr_idx;
    }
}


void
kdi_GenMemOpsFindNotBlockIndicesU16_IdxU16(u16 *idxs, usize idxs_sz, usize *found, u16 *ptr, usize ptr_sz, u16 item)
{
    u16 curr_idx = 0;

    while (ptr_sz && idxs_sz)
    {
        if (*ptr != item)
        {
            *idxs   = curr_idx;
            *found += SZ_U16;

            ++idxs;
            idxs_sz -= SZ_U16;
        }

        ++ptr;
        ptr_sz   -= SZ_U16;
        curr_idx += SZ_U16;
    }
}


void
kdi_GenMemOpsFindNotBlockIndicesU32_IdxU16(u16 *idxs, usize idxs_sz, usize *found, u32 *ptr, usize ptr_sz, u32 item)
{
    u16 curr_idx = 0;

    while (ptr_sz && idxs_sz)
    {
        if (*ptr != item)
        {
            *idxs   = curr_idx;
            *found += SZ_U16;

            ++idxs;
            idxs_sz -= SZ_U16;
        }

        ++ptr;
        ptr_sz   -= SZ_U32;
        curr_idx += SZ_U32;
    }
}


#if defined ARCH_64BIT_INT
void
kdi_GenMemOpsFindNotBlockIndicesU64_IdxU16(u16 *idxs, usize idxs_sz, usize *found, u64 *ptr, usize ptr_sz, u64 item)
{
    u16 curr_idx = 0;

    while (ptr_sz && idxs_sz)
    {
        if (*ptr != item)
        {
            *idxs   = curr_idx;
            *found += SZ_U16;

            ++idxs;
            idxs_sz -= SZ_U16;
        }

        ++ptr;
        ptr_sz   -= SZ_U64;
        curr_idx += SZ_U64;
    }
}
#endif


void
kdi_GenMemOpsFindNotBlockIndicesUn_IdxU16(u16 *idxs, usize idxs_sz, usize *found, byte *ptr, usize ptr_sz, byte *block, usize block_sz)
{
    u16   curr_idx    = 0;
    byte *block_begin = block;
    byte *block_end   = block + block_sz - 1;
    usize match_count = 0;
    bool  match;

    while (ptr_sz-- && idxs_sz)
    {
        match_count += *ptr == *block_begin;
        match        = match_count == block_sz;

        if (block_begin == block_end)
        {
            if (!match)
            {
                *idxs   = curr_idx;
                *found += SZ_U16;

                ++idxs;
                idxs_sz -= SZ_U16;
            }

            match_count  = 0;
            curr_idx    += U16_C(block_sz);
            block_begin  = block;
        }
        else
        {
            match_count = match ? 0 : match_count;
            ++block_begin;
        }

        ++ptr;
    }
}


void
kdi_GenMemOpsFindNotBlockIndicesU8_IdxU32(u32 *idxs, usize idxs_sz, usize *found, u8 *ptr, usize ptr_sz, u8 item)
{
    u32 curr_idx = 0;

    while (ptr_sz-- && idxs_sz)
    {
        if (*ptr != item)
        {
            *idxs   = curr_idx;
            *found += SZ_U32;

            ++idxs;
            idxs_sz -= SZ_U32;
        }

        ++ptr;
        ++curr_idx;
    }
}


void
kdi_GenMemOpsFindNotBlockIndicesU16_IdxU32(u32 *idxs, usize idxs_sz, usize *found, u16 *ptr, usize ptr_sz, u16 item)
{
    u32 curr_idx = 0;

    while (ptr_sz && idxs_sz)
    {
        if (*ptr != item)
        {
            *idxs   = curr_idx;
            *found += SZ_U32;

            ++idxs;
            idxs_sz -= SZ_U32;
        }

        ++ptr;
        ptr_sz   -= SZ_U16;
        curr_idx += SZ_U16;
    }
}


void
kdi_GenMemOpsFindNotBlockIndicesU32_IdxU32(u32 *idxs, usize idxs_sz, usize *found, u32 *ptr, usize ptr_sz, u32 item)
{
    u32 curr_idx = 0;

    while (ptr_sz && idxs_sz)
    {
        if (*ptr != item)
        {
            *idxs   = curr_idx;
            *found += SZ_U32;

            ++idxs;
            idxs_sz -= SZ_U32;
        }

        ++ptr;
        ptr_sz   -= SZ_U32;
        curr_idx += SZ_U32;
    }
}


#if defined ARCH_64BIT_INT
void
kdi_GenMemOpsFindNotBlockIndicesU64_IdxU32(u32 *idxs, usize idxs_sz, usize *found, u64 *ptr, usize ptr_sz, u64 item)
{
    u32 curr_idx = 0;

    while (ptr_sz && idxs_sz)
    {
        if (*ptr != item)
        {
            *idxs   = curr_idx;
            *found += SZ_U32;

            ++idxs;
            idxs_sz -= SZ_U32;
        }

        ++ptr;
        ptr_sz   -= SZ_U64;
        curr_idx += SZ_U64;
    }
}
#endif


void
kdi_GenMemOpsFindNotBlockIndicesUn_IdxU32(u32 *idxs, usize idxs_sz, usize *found, byte *ptr, usize ptr_sz, byte *block, usize block_sz)
{
    u32   curr_idx    = 0;
    byte *block_begin = block;
    byte *block_end   = block + block_sz - 1;
    usize match_count = 0;
    bool  match;

    while (ptr_sz-- && idxs_sz)
    {
        match_count += *ptr == *block_begin;
        match        = match_count == block_sz;

        if (block_begin == block_end)
        {
            if (!match)
            {
                *idxs   = curr_idx;
                *found += SZ_U32;

                ++idxs;
                idxs_sz -= SZ_U32;
            }

            match_count  = 0;
            curr_idx    += U32_C(block_sz);
            block_begin  = block;
        }
        else
        {
            match_count = match ? 0 : match_count;
            ++block_begin;
        }

        ++ptr;
    }
}


#if defined KD_ARCH_64BIT_INT
void
kdi_GenMemOpsFindNotBlockIndicesU8_IdxU64(u64 *idxs, usize idxs_sz, usize *found, u8 *ptr, usize ptr_sz, u8 item)
{
    u64 curr_idx = 0;

    while (ptr_sz-- && idxs_sz)
    {
        if (*ptr != item)
        {
            *idxs   = curr_idx;
            *found += SZ_U64;

            ++idxs;
            idxs_sz -= SZ_U64;
        }

        ++ptr;
        ++curr_idx;
    }
}


void
kdi_GenMemOpsFindNotBlockIndicesU16_IdxU64(u64 *idxs, usize idxs_sz, usize *found, u16 *ptr, usize ptr_sz, u16 item)
{
    u64 curr_idx = 0;

    while (ptr_sz && idxs_sz)
    {
        if (*ptr != item)
        {
            *idxs   = curr_idx;
            *found += SZ_U64;

            ++idxs;
            idxs_sz -= SZ_U64;
        }

        ++ptr;
        ptr_sz   -= SZ_U16;
        curr_idx += SZ_U16;
    }
}


void
kdi_GenMemOpsFindNotBlockIndicesU32_IdxU64(u64 *idxs, usize idxs_sz, usize *found, u32 *ptr, usize ptr_sz, u32 item)
{
    u64 curr_idx = 0;

    while (ptr_sz && idxs_sz)
    {
        if (*ptr != item)
        {
            *idxs   = curr_idx;
            *found += SZ_U64;

            ++idxs;
            idxs_sz -= SZ_U64;
        }

        ++ptr;
        ptr_sz   -= SZ_U32;
        curr_idx += SZ_U32;
    }
}


void
kdi_GenMemOpsFindNotBlockIndicesU64_IdxU64(u64 *idxs, usize idxs_sz, usize *found, u64 *ptr, usize ptr_sz, u64 item)
{
    u64 curr_idx = 0;

    while (ptr_sz && idxs_sz)
    {
        if (*ptr != item)
        {
            *idxs   = curr_idx;
            *found += SZ_U64;

            ++idxs;
            idxs_sz -= SZ_U64;
        }

        ++ptr;
        ptr_sz   -= SZ_U64;
        curr_idx += SZ_U64;
    }
}


void
kdi_GenMemOpsFindNotBlockIndicesUn_IdxU64(u64 *idxs, usize idxs_sz, usize *found, byte *ptr, usize ptr_sz, byte *block, usize block_sz)
{
    u64   curr_idx    = 0;
    byte *block_begin = block;
    byte *block_end   = block + block_sz - 1;
    usize match_count = 0;
    bool  match;

    while (ptr_sz-- && idxs_sz)
    {
        match_count += *ptr == *block_begin;
        match        = match_count == block_sz;

        if (block_begin == block_end)
        {
            if (!match)
            {
                *idxs   = curr_idx;
                *found += SZ_U64;

                ++idxs;
                idxs_sz -= SZ_U64;
            }

            match_count  = 0;
            curr_idx    += U64_C(block_sz);
            block_begin  = block;
        }
        else
        {
            match_count = match ? 0 : match_count;
            ++block_begin;
        }

        ++ptr;
    }
}
#endif


void
kdi_GenMemOpsReplaceBlock_U8(u8 *ptr, usize sz, u8 find_item, u8 new_item)
{
    while (sz--)
    {
        if (*ptr == find_item)
        {
            *ptr = new_item;
            break;
        }

        ++ptr;
    }
}


void
kdi_GenMemOpsReplaceBlock_U16(u16 *ptr, usize sz, u16 find_item, u16 new_item)
{
    while (sz)
    {
        if (*ptr == find_item)
        {
            *ptr = new_item;
            break;
        }

        ++ptr;
        sz -= SZ_U16;
    }
}


void
kdi_GenMemOpsReplaceBlock_U32(u32 *ptr, usize sz, u32 find_item, u32 new_item)
{
    while (sz)
    {
        if (*ptr == find_item)
        {
            *ptr = new_item;
            break;
        }

        ++ptr;
        sz -= SZ_U32;
    }
}


#if defined ARCH_64BIT_INT
void
kdi_GenMemOpsReplaceBlock_U64(u64 *ptr, usize sz, u64 find_item, u64 new_item)
{
    while (sz)
    {
        if (*ptr == find_item)
        {
            *ptr = new_item;
            break;
        }

        ++ptr;
        sz -= SZ_U64;
    }
}
#endif


void
kdi_GenMemOpsReplaceBlock_Un(byte *ptr, usize ptr_sz, byte *find_block, byte *new_block, usize block_sz)
{
    byte *find_block_begin = find_block;
    byte *find_block_end   = find_block + block_sz - 1;
    usize match_count      = 0;
    bool  match;

    while (ptr_sz--)
    {
        match_count += *ptr == *find_block_begin;
        match        = match_count == block_sz;

        if (match)
        {
            ptr -= block_sz;

            while (block_sz--)
            {
                ++ptr;
                *ptr = *new_block;
                ++new_block;
            }

            break;
        }

        if (find_block_begin == find_block_end)
        {
            match_count      = 0;
            find_block_begin = find_block;
        }
        else
        {
            match_count = match ? 0 : match_count;
            ++find_block_begin;
        }

        ++ptr;
    }
}


void
kdi_GenMemOpsReplaceNotBlock_U8(u8 *ptr, usize sz, u8 find_item, u8 new_item)
{
    while (sz--)
    {
        if (*ptr != find_item)
        {
            *ptr = new_item;
            break;
        }

        ++ptr;
    }
}


void
kdi_GenMemOpsReplaceNotBlock_U16(u16 *ptr, usize sz, u16 find_item, u16 new_item)
{
    while (sz)
    {
        if (*ptr != find_item)
        {
            *ptr = new_item;
            break;
        }

        ++ptr;
        sz -= SZ_U16;
    }
}


void
kdi_GenMemOpsReplaceNotBlock_U32(u32 *ptr, usize sz, u32 find_item, u32 new_item)
{
    while (sz)
    {
        if (*ptr != find_item)
        {
            *ptr = new_item;
            break;
        }

        ++ptr;
        sz -= SZ_U32;
    }
}


#if defined ARCH_64BIT_INT
void
kdi_GenMemOpsReplaceNotBlock_U64(u64 *ptr, usize sz, u64 find_item, u64 new_item)
{
    while (sz)
    {
        if (*ptr != find_item)
        {
            *ptr = new_item;
            break;
        }

        ++ptr;
        sz -= SZ_U64;
    }
}
#endif


void
kdi_GenMemOpsReplaceNotBlock_Un(byte *ptr, usize ptr_sz, byte *find_block, byte *new_block, usize block_sz)
{
    byte *find_block_begin = find_block;
    byte *find_block_end   = find_block + block_sz - 1;
    usize match_count      = 0;
    bool  match;

    while (ptr_sz--)
    {
        match_count += *ptr == *find_block_begin;
        match        = match_count == block_sz;

        if (find_block_begin == find_block_end)
        {
            if (!match)
            {
                ptr -= block_sz;

                while (block_sz--)
                {
                    ++ptr;
                    *ptr = *new_block;
                    ++new_block;
                }

                break;
            }

            match_count      = 0;
            find_block_begin = find_block;
        }
        else
        {
            match_count = match ? 0 : match_count;
            ++find_block_begin;
        }

        ++ptr;
    }
}


void
kdi_GenMemOpsReplaceLastBlock_U8(u8 *ptr, usize sz, u8 find_item, u8 new_item)
{
    ptr += sz;

    while (sz--)
    {
        --ptr;

        if (*ptr == find_item)
        {
            *ptr = new_item;
            break;
        }
    }
}


void
kdi_GenMemOpsReplaceLastBlock_U16(u16 *ptr, usize sz, u16 find_item, u16 new_item)
{
    ptr = PU16_C(PBYTE_C(ptr) + sz);

    while (sz)
    {
        --ptr;
        sz -= SZ_U16;

        if (*ptr == find_item)
        {
            *ptr = new_item;
            break;
        }
    }
}


void
kdi_GenMemOpsReplaceLastBlock_U32(u32 *ptr, usize sz, u32 find_item, u32 new_item)
{
    ptr = PU32_C(PBYTE_C(ptr) + sz);

    while (sz)
    {
        --ptr;
        sz -= SZ_U32;

        if (*ptr == find_item)
        {
            *ptr = new_item;
            break;
        }
    }
}


#if defined ARCH_64BIT_INT
void
kdi_GenMemOpsReplaceLastBlock_U64(u64 *ptr, usize sz, u64 find_item, u64 new_item)
{
    ptr = PU64_C(PBYTE_C(ptr) + sz);

    while (sz)
    {
        --ptr;
        sz -= SZ_U64;

        if (*ptr == find_item)
        {
            *ptr = new_item;
            break;
        }
    }
}
#endif


void
kdi_GenMemOpsReplaceLastBlock_Un(byte *ptr, usize ptr_sz, byte *find_block, byte *new_block, usize block_sz)
{
    byte *find_block_begin  = find_block, *find_block_end;
    usize match_count       = 0;
    bool  match             = false;

    ptr                    += ptr_sz - 1;
    find_block             += block_sz - 1;
    find_block_end          = find_block;

    while (ptr_sz--)
    {
        match_count += *ptr == *find_block_end;
        match        = match_count == block_sz;

        if (match)
        {
            while (block_sz--)
            {
                *ptr = *new_block;
                ++ptr;
                ++new_block;
            }

            break;
        }

        if (find_block_begin == find_block_end)
        {
            match_count    = 0;
            find_block_end = find_block;
        }
        else
        {
            match_count = match ? 0 : match_count;
            --find_block_end;
        }

        --ptr;
    }
}


void
kdi_GenMemOpsReplaceLastNotBlock_U8(u8 *ptr, usize sz, u8 find_item, u8 new_item)
{
    ptr += sz;

    while (sz--)
    {
        --ptr;

        if (*ptr != find_item)
        {
            *ptr = new_item;
            break;
        }
    }
}


void
kdi_GenMemOpsReplaceLastNotBlock_U16(u16 *ptr, usize sz, u16 find_item, u16 new_item)
{
    ptr = PU16_C(PBYTE_C(ptr) + sz);

    while (sz)
    {
        --ptr;
        sz -= SZ_U16;

        if (*ptr != find_item)
        {
            *ptr = new_item;
            break;
        }
    }
}


void
kdi_GenMemOpsReplaceLastNotBlock_U32(u32 *ptr, usize sz, u32 find_item, u32 new_item)
{
    ptr = PU32_C(PBYTE_C(ptr) + sz);

    while (sz)
    {
        --ptr;
        sz -= SZ_U32;

        if (*ptr != find_item)
        {
            *ptr = new_item;
            break;
        }
    }
}


#if defined ARCH_64BIT_INT
void
kdi_GenMemOpsReplaceLastNotBlock_U64(u64 *ptr, usize sz, u64 find_item, u64 new_item)
{
    ptr = PU64_C(PBYTE_C(ptr) + sz);

    while (sz)
    {
        --ptr;
        sz -= SZ_U64;

        if (*ptr != find_item)
        {
            *ptr = new_item;
            break;
        }
    }
}
#endif


void
kdi_GenMemOpsReplaceLastNotBlock_Un(byte *ptr, usize ptr_sz, byte *find_block, byte *new_block, usize block_sz)
{
    byte *find_block_begin  = find_block, *find_block_end;
    usize match_count       = 0;
    bool  match             = false;

    ptr                    += ptr_sz - 1;
    find_block             += block_sz - 1;
    find_block_end          = find_block;

    while (ptr_sz--)
    {
        match_count += *ptr == *find_block_end;
        match        = match_count == block_sz;

        if (find_block_begin == find_block_end)
        {
            if (!match)
            {
                while (block_sz--)
                {
                    *ptr = *new_block;
                    ++ptr;
                    ++new_block;
                }

                break;
            }

            match_count    = 0;
            find_block_end = find_block;
        }
        else
        {
            match_count = match ? 0 : match_count;
            --find_block_end;
        }

        --ptr;
    }
}


void
kdi_GenMemOpsReplaceAllBlocks_U8(u8 *ptr, usize sz, usize *count, u8 find_item, u8 new_item)
{
    while (sz--)
    {
        if (*ptr == find_item)
        {
            *ptr    = new_item;
            *count += 1;
        }

        ++ptr;
    }
}


void
kdi_GenMemOpsReplaceAllBlocks_U16(u16 *ptr, usize sz, usize *count, u16 find_item, u16 new_item)
{
    while (sz)
    {
        if (*ptr == find_item)
        {
            *ptr    = new_item;
            *count += SZ_U16;
        }

        ++ptr;
        sz -= SZ_U16;
    }
}


void
kdi_GenMemOpsReplaceAllBlocks_U32(u32 *ptr, usize sz, usize *count, u32 find_item, u32 new_item)
{
    while (sz)
    {
        if (*ptr == find_item)
        {
            *ptr    = new_item;
            *count += SZ_U32;
        }

        ++ptr;
        sz -= SZ_U32;
    }
}


#if defined ARCH_64BIT_INT
void
kdi_GenMemOpsReplaceAllBlocks_U64(u64 *ptr, usize sz, usize *count, u64 find_item, u64 new_item)
{
    while (sz)
    {
        if (*ptr == find_item)
        {
            *ptr    = new_item;
            *count += SZ_U64;
        }

        ++ptr;
        sz -= SZ_U64;
    }
}
#endif


void
kdi_GenMemOpsReplaceAllBlocks_Un(byte *ptr, usize ptr_sz, usize *count, byte *find_block, byte *new_block, usize block_sz)
{
    byte *find_block_begin = find_block;
    byte *find_block_end   = find_block + block_sz - 1;
    usize match_count      = 0;
    usize temp_block_sz;
    byte *temp_new_block, *temp_ptr;
    bool  match;

    while (ptr_sz--)
    {
        match_count += *ptr == *find_block_begin;
        match        = match_count == block_sz;

        if (match)
        {
            temp_block_sz   = block_sz;
            temp_ptr        = ptr - temp_block_sz;
            temp_new_block  = new_block;
            *count         += temp_block_sz;

            while (temp_block_sz--)
            {
                ++temp_ptr;
                *temp_ptr = *temp_new_block;
                ++temp_new_block;
            }
        }

        if (find_block_begin == find_block_end)
        {
            match_count      = 0;
            find_block_begin = find_block;
        }
        else
        {
            match_count = match ? 0 : match_count;
            ++find_block_begin;
        }

        ++ptr;
    }
}


void
kdi_GenMemOpsReplaceAllNotBlocks_U8(u8 *ptr, usize sz, usize *count, u8 find_item, u8 new_item)
{
    while (sz--)
    {
        if (*ptr != find_item)
        {
            *ptr    = new_item;
            *count += 1;
        }

        ++ptr;
    }
}


void
kdi_GenMemOpsReplaceAllNotBlocks_U16(u16 *ptr, usize sz, usize *count, u16 find_item, u16 new_item)
{
    while (sz)
    {
        if (*ptr != find_item)
        {
            *ptr    = new_item;
            *count += SZ_U16;
        }

        ++ptr;
        sz -= SZ_U16;
    }
}


void
kdi_GenMemOpsReplaceAllNotBlocks_U32(u32 *ptr, usize sz, usize *count, u32 find_item, u32 new_item)
{
    while (sz)
    {
        if (*ptr != find_item)
        {
            *ptr    = new_item;
            *count += SZ_U32;
        }

        ++ptr;
        sz -= SZ_U32;
    }
}


#if defined ARCH_64BIT_INT
void
kdi_GenMemOpsReplaceAllNotBlocks_U64(u64 *ptr, usize sz, usize *count, u64 find_item, u64 new_item)
{
    while (sz)
    {
        if (*ptr != find_item)
        {
            *ptr    = new_item;
            *count += SZ_U64;
        }

        ++ptr;
        sz -= SZ_U64;
    }
}
#endif


void
kdi_GenMemOpsReplaceAllNotBlocks_Un(byte *ptr, usize ptr_sz, usize *count, byte *find_block, byte *new_block, usize block_sz)
{
    byte *find_block_begin = find_block;
    byte *find_block_end   = find_block + block_sz - 1;
    usize match_count      = 0;
    usize temp_block_sz;
    byte *temp_new_block, *temp_ptr;
    bool  match;

    while (ptr_sz--)
    {
        match_count += *ptr == *find_block_begin;
        match        = match_count == block_sz;

        if (find_block_begin == find_block_end)
        {
            if (!match)
            {
                temp_block_sz   = block_sz;
                temp_ptr        = ptr - temp_block_sz;
                temp_new_block  = new_block;
                *count         += temp_block_sz;

                while (temp_block_sz--)
                {
                    ++temp_ptr;
                    *temp_ptr = *temp_new_block;
                    ++temp_new_block;
                }
            }

            match_count      = 0;
            find_block_begin = find_block;
        }
        else
        {
            match_count = match ? 0 : match_count;
            ++find_block_begin;
        }

        ++ptr;
    }
}
