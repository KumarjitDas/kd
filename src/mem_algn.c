/**
 * @file kd_mem_algn.c
 * @author Kumarjit Das
 * @version 0.0.1
 * @brief Main source file of the KD_MEM_ALGN library.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 * @since 0.0.1
 */


#include "kd_version.h"

#define KD_BUILDING_LIB 1
#include "kd_platform.h"

#include "kd_fixed_width.h"
#include "kd_mem_algn.h"


static kd_bool_t
kdi_IsPowerOfTwo(kd_usize_t n)
{
    return n && !(n & (n - 1));
}


static kd_bool_t
kdi_IsValidAlgnSize(kd_u8_t algn_sz)
{
    return (algn_sz != 0) && kdi_IsPowerOfTwo(algn_sz) && (algn_sz <= KD_MEM_ALGN_MAX_ALGN_SIZE);
}


static kd_bool_t
kdi_IsValidOffset(kd_u8_t offset)
{
    return !offset || (kdi_IsPowerOfTwo(offset) && (offset <= KD_MEM_ALGN_MAX_OFFSET));
}


kd_usize_t
kdMemAlgnGetAllocSize(kd_usize_t usable_size, kd_u8_t algn_sz, kd_u8_t offset)
{
    if (!usable_size || !algn_sz || !kdi_IsValidAlgnSize(algn_sz) || !kdi_IsValidOffset(offset))
    {
        return 0;
    }
    return offset + algn_sz + usable_size;
}


void *
kdMemAlgnGetForwardPtr(void *head_ptr, kd_u8_t algn_sz, kd_u8_t offset)
{
    if (!head_ptr || !algn_sz || !kdi_IsValidAlgnSize(algn_sz) || !kdi_IsValidOffset(offset))
    {
        return kd_null;
    }

    kd_u8_t *forward = KD_PU8_C(head_ptr) + offset + algn_sz;

    return forward - (KD_USIZE_C(forward) % algn_sz);
}


void *
kdMemAlgnGetBackwardPtr(void *head_ptr, kd_u8_t algn_sz, kd_u8_t offset)
{
    kd_u8_t *forward = kdMemAlgnGetForwardPtr(head_ptr, algn_sz, offset);
    if (!forward)
    {
        return kd_null;
    }

    kd_u8_t *backward = forward;

    while (backward >= KD_PU8_C(head_ptr))
    {
        backward -= algn_sz;
    }

    return backward;
}


void *
kdMemAlgnGetOffsetPtr(void *head_ptr, kd_u8_t algn_sz, kd_u8_t offset)
{
    void *forward = kdMemAlgnGetForwardPtr(head_ptr, algn_sz, offset);
    if (forward)
    {
        switch (offset)
        {
            case KD_SZ_U8:
                *(KD_PU8_C(forward) - offset) = KD_U8_C(KD_PU8_C(forward) - (kd_u8_t *)head_ptr);
                break;
            case KD_SZ_U16:
                *KD_PU16_C(KD_PU8_C(forward) - offset) = KD_U16_C(KD_PU8_C(forward) - (kd_u8_t *)head_ptr);
                break;
            case KD_SZ_U32:
                *KD_PU32_C(KD_PU8_C(forward) - offset) = KD_U32_C(KD_PU8_C(forward) - (kd_u8_t *)head_ptr);
                break;
#if defined KD_ARCH_64BIT_INT
            case KD_SZ_U64:
                *KD_PU64_C(KD_PU8_C(forward) - offset) = KD_U64_C(KD_PU8_C(forward) - (kd_u8_t *)head_ptr);
                break;
#endif /* KD_ARCH_64BIT_INT */
            default:;
        }
    }

    return forward;
}


void *
kdMemAlgnGetHeadPtr(void *off_ptr, kd_u8_t offset)
{
    if (!off_ptr || !kdi_IsValidOffset(offset))
    {
        return kd_null;
    }

    kd_umax_t head_offset = 0;

    switch (offset)
    {
        case KD_SZ_U8:
            head_offset = *(KD_PU8_C(off_ptr) - offset);
            break;
        case KD_SZ_U16:
            head_offset = *KD_PU16_C(KD_PU8_C(off_ptr) - offset);
            break;
        case KD_SZ_U32:
            head_offset = *KD_PU32_C(KD_PU8_C(off_ptr) - offset);
            break;
#if defined KD_ARCH_64BIT_INT
        case KD_SZ_U64:
            head_offset = *KD_PU64_C(KD_PU8_C(off_ptr) - offset);
            break;
#endif /* KD_ARCH_64BIT_INT */
        default:;
    }

    return KD_PU8_C(off_ptr) - head_offset;
}
