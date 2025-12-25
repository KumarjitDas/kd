/**
 * @file utils.h
 * @author Kumarjit Das
 * @brief Test utility functions for KD libraries.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#ifndef KD_TESTS_UTILS_H
#define KD_TESTS_UTILS_H


#include "../include/kd.h"


/**
 * @brief Compare two byte arrays for equality.
 *
 * @param a First byte array
 * @param b Second byte array
 * @param sz Size in bytes to compare
 * @return kd_bool_t RESULT_SUCCESS if equal, RESULT_FAILURE otherwise
 */
kd_bool_t kdi_BytesEqual(const kd_byte_t *a, const kd_byte_t *b, kd_usize_t sz);


/**
 * @brief Fill a u8 array with sequential/incremental values.
 *
 * @param dst Destination array
 * @param sz Size of the array
 * @param start Starting value (increments by 1 for each element)
 */
void      kdi_FillSeq_u8(kd_u8_t *dst, kd_usize_t sz, kd_u8_t start);


/**
 * @brief Fill a u8 array with a constant value.
 *
 * @param dst Destination array
 * @param sz Size of the array
 * @param value Constant value to fill
 */
void      kdi_Fill_u8(kd_u8_t *dst, kd_usize_t sz, kd_u8_t value);


#endif /* KD_TESTS_UTILS_H */
