/**
 * @file floating_point.h
 * @author Kumarjit Das
 * @version 0.0.1
 * @brief Floating-point typedefs and macro definitions.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 * @since 0.0.1
 */


#ifndef KD_FLOATING_POINT_H_
#define KD_FLOATING_POINT_H_


#include "./version.h"
#include "./platform.h"


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
 *  Simplified versions of typedefs, macros, and miscellaneous constants without library initials/prefix
 * ---------------------------------------------------------------------------------------------------------------------
 */

#define f32        kd_f32_t
#define f64        kd_f64_t

#define LIT_F32(x) KD_LIT_F32(x)
#define LIT_F64(x) KD_LIT_F64(x)

#if !(defined KD_CPLUSPLUS && defined KD_GOOGLE_TEST && defined KD_OS_WINDOWS && defined KD_COMP_MSVC)
    #define LIT_FMIN(x) KD_LIT_FMIN(x)
    #define LIT_FMAX(x) KD_LIT_FMAX(x)
#endif

#define MIN_F32 KD_MIN_F32
#define MIN_F64 KD_MIN_F64

#if !(defined KD_CPLUSPLUS && defined KD_GOOGLE_TEST && defined KD_OS_WINDOWS && defined KD_COMP_MSVC)
    #define MIN_FMIN KD_MIN_FMIN
    #define MIN_FMAX KD_MIN_FMAX
#endif

#define MAX_F32 KD_MAX_F32
#define MAX_F64 KD_MAX_F64

#if !(defined KD_CPLUSPLUS && defined KD_GOOGLE_TEST && defined KD_OS_WINDOWS && defined KD_COMP_MSVC)
    #define MAX_FMIN KD_MAX_FMIN
    #define MAX_FMAX KD_MAX_FMAX
#endif

#define SZ_F32    KD_SZ_F32
#define SZ_F64    KD_SZ_F64

#define FMTSP_F32 KD_FMTSP_F32
#define FMTSP_F64 KD_FMTSP_F64

#if !(defined KD_CPLUSPLUS && defined KD_GOOGLE_TEST && defined KD_OS_WINDOWS && defined KD_COMP_MSVC)
    #define FMTSP_FMIN KD_FMTSP_FMIN
    #define FMTSP_FMAX KD_FMTSP_FMAX
#endif

#define FSBTC_F32(x) KD_FSBTC_F32(x)
#define FSBTC_F64(x) KD_FSBTC_F64(x)

#if !(defined KD_CPLUSPLUS && defined KD_GOOGLE_TEST && defined KD_OS_WINDOWS && defined KD_COMP_MSVC)
    #define FSBTC_FMIN(x) KD_FSBTC_FMIN(x)
    #define FSBTC_FMAX(x) KD_FSBTC_FMAX(x)
#endif


KD_EXTERN_END


#endif /* KD_FLOATING_POINT_H_ */
