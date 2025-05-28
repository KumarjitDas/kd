/**
 * @file fp.h
 * @author Kumarjit Das
 * @date 2025-05-28
 * @since 0.0.4
 * @brief Floating-point typedefs and macro definitions.
 */
/**
 * LICENSE: BSD 3-Clause License
 *
 * Copyright (c) 2025, Kumarjit Das.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef KD_TYPES_FP_H_
#define KD_TYPES_FP_H_


#include "kd/defs.h"


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

#define KD_SZ_F32 sizeof(kd_f32_t)
#define KD_SZ_F64 sizeof(kd_f64_t)


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


#endif /* KD_TYPES_FP_H_ */
