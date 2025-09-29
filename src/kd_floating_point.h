/**
 * @file kd_floating_point.h
 * @author Kumarjit Das
 * @version 0.0.1
 * @brief Floating-point typedefs and macro definitions.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 * @since 0.0.1
 */


#ifndef KD_FLOATING_POINT_H_
#define KD_FLOATING_POINT_H_


#include "kd_version.h"
#include "kd_platform.h"


KD_EXTERN_BEGIN


/**
 * ---------------------------------------------------------------------------------------------------------------------
 *  Type Definitions
 * ---------------------------------------------------------------------------------------------------------------------
 */

typedef float  kd_f32_t;
typedef double kd_f64_t;


/**
 * ---------------------------------------------------------------------------------------------------------------------
 *  Constant literal postfixes
 * ---------------------------------------------------------------------------------------------------------------------
 */

#define KD_LIT_F32(x) x##F
#define KD_LIT_F64(x) (kd_f64_t)(x)

#if !(defined KD_CPLUSPLUS && defined KD_GOOGLE_TEST && defined KD_OS_WINDOWS && defined KD_COMP_MSVC)
    #define KD_LIT_FMIN(x) KD_LIT_F32(x)
    #define KD_LIT_FMAX(x) KD_LIT_F64(x)
#endif


/**
 * ---------------------------------------------------------------------------------------------------------------------
 *  Minimum Values Of Defined Types
 * ---------------------------------------------------------------------------------------------------------------------
 */

#define KD_MIN_F32 KD_LIT_F32(-1.175494071E-38)
#define KD_MIN_F64 KD_LIT_F64(-2.22507385850720139E-308)

#if !(defined KD_CPLUSPLUS && defined KD_GOOGLE_TEST && defined KD_OS_WINDOWS && defined KD_COMP_MSVC)
    #define KD_MIN_FMIN KD_MIN_F32
    #define KD_MIN_FMAX KD_MIN_F64
#endif


/**
 * ---------------------------------------------------------------------------------------------------------------------
 *  Maximum Values Of Defined Types
 * ---------------------------------------------------------------------------------------------------------------------
 */

#define KD_MAX_F32 KD_LIT_F32(3.402823466E+38)
#define KD_MAX_F64 KD_LIT_F64(1.79769313486231571E+308)

#if !(defined KD_CPLUSPLUS && defined KD_GOOGLE_TEST && defined KD_OS_WINDOWS && defined KD_COMP_MSVC)
    #define KD_MAX_FMIN KD_MAX_F32
    #define KD_MAX_FMAX KD_MAX_F64
#endif


/**
 * ---------------------------------------------------------------------------------------------------------------------
 *  Sizes Of Defined Types (In Bytes)
 * ---------------------------------------------------------------------------------------------------------------------
 */

#define KD_SZ_F32    sizeof(kd_f32_t)
#define KD_SZ_F64    sizeof(kd_f64_t)


/**
 * ---------------------------------------------------------------------------------------------------------------------
 *  C-style Format Specifiers
 * ---------------------------------------------------------------------------------------------------------------------
 */

#define KD_FMTSP_F32 "%.9e"
#define KD_FMTSP_F64 "%.17e"

#if !(defined KD_CPLUSPLUS && defined KD_GOOGLE_TEST && defined KD_OS_WINDOWS && defined KD_COMP_MSVC)
    #define KD_FMTSP_FMIN "%.9e"
    #define KD_FMTSP_FMAX "%.17e"
#endif


/**
 * ---------------------------------------------------------------------------------------------------------------------
 *  C-style Format Specifier Based Type Cast
 * ---------------------------------------------------------------------------------------------------------------------
 */

#define KD_FSBTC_F32(x) (double)(x)
#define KD_FSBTC_F64(x) (x)

#if !(defined KD_CPLUSPLUS && defined KD_GOOGLE_TEST && defined KD_OS_WINDOWS && defined KD_COMP_MSVC)
    #define KD_FSBTC_FMIN(x) KD_FSBTC_F32(x)
    #define KD_FSBTC_FMAX(x) KD_FSBTC_F64(x)
#endif


/**
 * ---------------------------------------------------------------------------------------------------------------------
 *  Conditional simplified versions of typedefs and macros
 * ---------------------------------------------------------------------------------------------------------------------
 */

#if defined KD_USE_SIMPLIFIED_TYPES
typedef kd_f32_t f32;
typedef kd_f64_t f64;
#endif /* KD_USE_SIMPLIFIED_TYPES */


KD_EXTERN_END


#endif /* KD_FLOATING_POINT_H_ */
