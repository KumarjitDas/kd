/**
 * @file utils.c
 * @author Kumarjit Das
 * @brief Test utility functions for KD libraries.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include "utils.h"


kd_bool_t
kdi_BytesEqual(const kd_byte_t *a, const kd_byte_t *b, kd_usize_t sz)
{
    kd_usize_t i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        if (a[i] != b[i])
        {
            return RESULT_FAILURE;
        }
    }

    return RESULT_SUCCESS;
}


void
kdi_FillSeq_u8(kd_u8_t *dst, kd_usize_t sz, kd_u8_t start)
{
    kd_usize_t i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        dst[i] = start + (kd_u8_t)i;
    }
}


void
kdi_Fill_u8(kd_u8_t *dst, kd_usize_t sz, kd_u8_t value)
{
    kd_usize_t i;

    for (i = USIZE_C(0); i < sz; ++i)
    {
        dst[i] = value;
    }
}
