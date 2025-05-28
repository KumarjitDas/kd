/**
 * @file fw.h
 * @author Kumarjit Das
 * @date 2025-05-28
 * @since 0.0.4
 * @brief Fixed-width integral typedefs and macro definitions.
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


#ifndef KD_TYPES_FW_H_
#define KD_TYPES_FW_H_


#include "kd/defs.h"


KD_EXTERN_BEGIN


/**
 * ---------------------------------------------------------------------------------------------------------------------
 *  64-Bit Integer and Pointer Signatures
 * ---------------------------------------------------------------------------------------------------------------------
 */

#if defined KD_ARCH_64BIT_INT
  #define KD_FW_64BIT_INT 1
#elif defined KD_ARCH_32BIT_INT
  #define KD_FW_32BIT_INT 1
#endif

#if defined KD_ARCH_64BIT_PTR
  #define KD_FW_64BIT_PTR 1
#elif defined KD_ARCH_32BIT_PTR
  #define KD_FW_32BIT_PTR 1
#endif


/**
 * ---------------------------------------------------------------------------------------------------------------------
 *  Type Definitions
 * ---------------------------------------------------------------------------------------------------------------------
 */

#ifndef KD_CPLUSPLUS
enum kd_enum_bool_t
{
  kd_false,
  kd_true
};
typedef enum kd_enum_bool_t kd_bool_t;
#endif

typedef char          kd_i8_t;
typedef unsigned char kd_u8_t;
typedef kd_i8_t       kd_imin_t;
typedef kd_u8_t       kd_umin_t;

#if defined KD_ARCH_32BIT_INT && __SIZEOF_INT__ == 2 && __SIZEOF_LONG__ == 4
typedef int           kd_i16_t;
typedef long          kd_i32_t;
typedef unsigned int  kd_u16_t;
typedef unsigned long kd_u32_t;
#else
typedef short          kd_i16_t;
typedef int            kd_i32_t;
typedef unsigned short kd_u16_t;
typedef unsigned int   kd_u32_t;
#endif

#if defined KD_ARCH_64BIT_INT
  #if defined _MSC_VER || defined __BORLANDC__ || defined __WATCOMC__ || (defined __alpha && defined __DECC)
typedef __int64          kd_i64_t;
typedef unsigned __int64 kd_u64_t;
  #elif (defined __GNUC__ || defined __MWERKS__ || defined __SUNPRO_C || defined __SUNPRO_CC ||                        \
         defined __APPLE_CC__ || defined KD_OS_IRIX || defined _LONG_LONG || defined _CRAYC) &&                        \
    __SIZEOF_LONG__ == 8
typedef long          kd_i64_t;
typedef unsigned long kd_u64_t;
  /* #elif defined __LP64__ || defined __powerpc64__ || defined KD_CPU_SPARC64 */
  #else
typedef long          kd_i64_t;
typedef unsigned long kd_u64_t;
  #endif
typedef kd_i64_t kd_imax_t;
typedef kd_u64_t kd_umax_t;
#else
typedef kd_i32_t kd_imax_t;
typedef kd_u32_t kd_umax_t;
#endif /* KD_ARCH_64BIT_INT */

#if defined KD_ARCH_64BIT_PTR
typedef kd_u64_t kd_usize_t;
#else
typedef kd_u32_t kd_usize_t;
#endif /* KD_ARCH_64BIT_PTR */

typedef kd_u8_t  kd_byte_t;
typedef kd_u32_t kd_chr_t;


/**
 * ---------------------------------------------------------------------------------------------------------------------
 *  Constant literal postfixes
 * ---------------------------------------------------------------------------------------------------------------------
 */

#define KD_LIT_BOOL(x) (kd_bool_t)(x)
#define KD_LIT_I8(x)   (kd_i8_t)(x)
#define KD_LIT_I16(x)  (kd_i16_t)(x)
#define KD_LIT_U8(x)   (kd_u8_t)(x)
#define KD_LIT_U16(x)  (kd_u16_t)(x)

#if defined KD_ARCH_32BIT_INT && __SIZEOF_INT__ == 2 && __SIZEOF_LONG__ == 4
  #define KD_LIT_I32(x) x##L
  #define KD_LIT_U32(x) x##UL
#else
  #define KD_LIT_I32(x) (kd_i32_t)(x)
  #define KD_LIT_U32(x) x##U
#endif

#if defined KD_FW_64BIT_INT
  #if defined _MSC_VER || defined __BORLANDC__ || defined __WATCOMC__ || (defined __alpha && defined __DECC)
    #define KD_LIT_I64(x) x##LL
    #define KD_LIT_U64(x) x##ULL
  #elif (defined __GNUC__ || defined __MWERKS__ || defined __SUNPRO_C || defined __SUNPRO_CC ||                        \
         defined __APPLE_CC__ || defined KD_OS_IRIX || defined _LONG_LONG || defined _CRAYC) &&                        \
    __SIZEOF_LONG__ == 8
    #define KD_LIT_I64(x) x##L
    #define KD_LIT_U64(x) x##LU
  /* #elif defined __LP64__ || defined __powerpc64__ || defined KD_CPU_SPARC64 */
  #else
    #define KD_LIT_I64(x) (kd_i64_t)(x)
    #define KD_LIT_U64(x) (kd_u64_t)(x)
  #endif

  #define KD_LIT_IMAX(x) (kd_imax_t) KD_LIT_I64(x)
  #define KD_LIT_UMAX(x) (kd_imax_t) KD_LIT_U64(x)
#else
  #define KD_LIT_IMAX(x) (kd_imax_t) KD_LIT_I32(x)
  #define KD_LIT_UMAX(x) (kd_imax_t) KD_LIT_U32(x)
#endif /* KD_FW_64BIT_INT */

/* A hack from Posh.h library */
#if defined __MINGW32__ && defined KD_ARCH_64BIT_INT
  #undef KD_LIT_I64
  #undef KD_LIT_U64
  #define KD_LIT_I64(x) x##LL
  #define KD_LIT_U64(x) x##LLU
#endif

#define KD_LIT_IMIN(x) (kd_imin_t)(x)
#define KD_LIT_UMIN(x) (kd_umin_t)(x)

#define KD_LIT_BYTE(x) (kd_byte_t)(x)
#define KD_LIT_CHR(x)  (kd_chr_t) KD_LIT_U32(x)

#if defined KD_ARCH_64BIT_PTR && defined KD_FW_64BIT_INT
  #define KD_LIT_PTR(x) (void*)KD_LIT_U64(x)
#else
  #define KD_LIT_PTR(x) (void*)KD_LIT_U32(x)
#endif


/**
 * ---------------------------------------------------------------------------------------------------------------------
 *  Minimum Values Of Defined Types
 * ---------------------------------------------------------------------------------------------------------------------
 */

#define KD_MIN_I8   KD_LIT_I8(-128)
#define KD_MIN_I16  KD_LIT_I16(-32768)
#define KD_MIN_I32  (KD_LIT_I32(-2147483647) - KD_LIT_I32(1))
#define KD_MIN_IMIN KD_LIT_IMIN(-128)
#define KD_MIN_U8   KD_LIT_U8(0)
#define KD_MIN_U16  KD_LIT_U16(0)
#define KD_MIN_U32  KD_LIT_U32(0)
#define KD_MIN_UMIN KD_LIT_UMIN(0)
#define KD_MIN_BYTE KD_LIT_BYTE(0)
#define KD_MIN_CHR  KD_LIT_CHR(0)
#define KD_MIN_PTR  KD_LIT_PTR(0)

#if defined KD_ARCH_64BIT_INT
  #define KD_MIN_I64   (KD_LIT_I64(-9223372036854775807) - KD_LIT_I64(-1))
  #define KD_MIN_IMAX  KD_MIN_I64
  #define KD_MIN_U64   KD_LIT_I64(0)
  #define KD_MIN_UMAX  KD_MIN_U64
  #define KD_MIN_USIZE KD_MIN_U64
#else
  #define KD_MIN_IMAX  KD_MIN_I32
  #define KD_MIN_UMAX  KD_MIN_U32
  #define KD_MIN_USIZE KD_MIN_U32
#endif /* KD_ARCH_64BIT_INT */


/**
 * ---------------------------------------------------------------------------------------------------------------------
 *  Maximum Values Of Defined Types
 * ---------------------------------------------------------------------------------------------------------------------
 */

#define KD_MAX_I8   KD_LIT_I8(127)
#define KD_MAX_I16  KD_LIT_I16(32767)
#define KD_MAX_I32  KD_LIT_I32(2147483647)
#define KD_MAX_IMIN KD_LIT_IMIN(127)
#define KD_MAX_U8   KD_LIT_U8(255)
#define KD_MAX_U16  KD_LIT_U16(65535)
#define KD_MAX_U32  KD_LIT_U32(4294967295)
#define KD_MAX_UMIN KD_LIT_UMIN(255)
#define KD_MAX_BYTE KD_LIT_BYTE(255)
#define KD_MAX_CHR  KD_LIT_CHR(4294967295)

#if defined KD_ARCH_64BIT_INT
  #define KD_MAX_I64   KD_LIT_I64(9223372036854775807)
  #define KD_MAX_IMAX  KD_MAX_I64
  #define KD_MAX_U64   KD_LIT_U64(18446744073709551615)
  #define KD_MAX_UMAX  KD_MAX_U64
  #define KD_MAX_USIZE KD_MAX_U64
#else
  #define KD_MAX_IMAX  KD_MAX_I32
  #define KD_MAX_UMAX  KD_MAX_U32
  #define KD_MAX_USIZE KD_MAX_U32
#endif /* KD_ARCH_64BIT_INT */

#if defined KD_ARCH_64BIT_PTR
  #if defined KD_ARCH_64BIT_INT
    #define KD_MAX_PTR ((void*)KD_MAX_U64)
  #else
    #define KD_MAX_PTR ((void*)0xFFFFFFFFFFFFFFFF)
  #endif /* KD_ARCH_64BIT_INT */
#else
  #define KD_MAX_PTR ((void*)KD_MAX_U32)
#endif /* KD_ARCH_64BIT_PTR */


/**
 * ---------------------------------------------------------------------------------------------------------------------
 *  Constant Values/Macros
 * ---------------------------------------------------------------------------------------------------------------------
 */

#define kd_null KD_LIT_PTR(0x00)


/**
 * ---------------------------------------------------------------------------------------------------------------------
 *  Sizes Of Defined Types (In Bytes)
 * ---------------------------------------------------------------------------------------------------------------------
 */

#define KD_SZ_BOOL  sizeof(kd_bool_t)
#define KD_SZ_I8    sizeof(kd_i8_t)
#define KD_SZ_I16   sizeof(kd_i16_t)
#define KD_SZ_I32   sizeof(kd_i32_t)
#define KD_SZ_IMIN  sizeof(kd_imin_t)
#define KD_SZ_IMAX  sizeof(kd_imax_t)
#define KD_SZ_U8    sizeof(kd_u8_t)
#define KD_SZ_U16   sizeof(kd_u16_t)
#define KD_SZ_U32   sizeof(kd_u32_t)
#define KD_SZ_UMIN  sizeof(kd_umin_t)
#define KD_SZ_UMAX  sizeof(kd_umax_t)
#define KD_SZ_USIZE sizeof(kd_usize_t)
#define KD_SZ_BYTE  sizeof(kd_byte_t)
#define KD_SZ_CHR   sizeof(kd_chr_t)
#define KD_SZ_PTR   sizeof(void*)

#if defined KD_ARCH_64BIT_INT
  #define KD_SZ_I64 sizeof(kd_i64_t)
  #define KD_SZ_U64 sizeof(kd_u64_t)
#endif


/**
 * ---------------------------------------------------------------------------------------------------------------------
 *  C-style Format Specifiers
 * ---------------------------------------------------------------------------------------------------------------------
 */

#define KD_FMTSP_BOOL "%s"
#define KD_FMTSP_I8   "%d"
#define KD_FMTSP_I16  "%d"
#define KD_FMTSP_IMIN "%d"
#define KD_FMTSP_U8   "%u"
#define KD_FMTSP_U16  "%u"
#define KD_FMTSP_UMIN "%u"
#define KD_FMTSP_BYTE "%u"
#define KD_FMTSP_PTR  "%p"

#if defined KD_ARCH_32BIT_INT
  #if __SIZEOF_INT__ == 4
    #define KD_FMTSP_I32 "%d"
    #define KD_FMTSP_U32 "%u"
  #else
    #define KD_FMTSP_I32 "%ld"
    #define KD_FMTSP_U32 "%lu"
  #endif
#else
  #define KD_FMTSP_I32 "%d"
  #define KD_FMTSP_U32 "%u"
#endif /* KD_ARCH_32BIT_INT */

#define KD_FMTSP_CHR KD_FMTSP_U32

#if defined KD_ARCH_64BIT_INT
  #ifdef KD_COMP_MSVC
    #define KD_FMTSP_I64   "%lld"
    #define KD_FMTSP_U64   "%llu"
    #define KD_FMTSP_IMAX  "%lld"
    #define KD_FMTSP_UMAX  "%llu"
    #define KD_FMTSP_USIZE "%llu"
  #else
    #define KD_FMTSP_I64   "%ld"
    #define KD_FMTSP_U64   "%lu"
    #define KD_FMTSP_IMAX  "%ld"
    #define KD_FMTSP_UMAX  "%lu"
    #define KD_FMTSP_USIZE "%lu"
  #endif /* KD_COMP_MSVC */
#else
  #define KD_FMTSP_IMAX  KD_FMTSP_I32
  #define KD_FMTSP_UMAX  KD_FMTSP_U32
  #define KD_FMTSP_USIZE KD_FMTSP_U32
#endif /* KD_ARCH_64BIT_INT */


/**
 * ---------------------------------------------------------------------------------------------------------------------
 *  C-style Format Specifier Based Type Cast
 * ---------------------------------------------------------------------------------------------------------------------
 */

#define KD_FSBTC_BOOL(x) ((x) ? "kd_true" : "kd_false")
#define KD_FSBTC_I8(x)   (int)(x)
#define KD_FSBTC_I16(x)  (int)(x)
#define KD_FSBTC_IMIN(x) (int)(x)
#define KD_FSBTC_U8(x)   (unsigned int)(x)
#define KD_FSBTC_U16(x)  (unsigned int)(x)
#define KD_FSBTC_UMIN(x) (unsigned int)(x)
#define KD_FSBTC_BYTE(x) (unsigned int)(x)
#define KD_FSBTC_PTR(x)  (void*)(x)

#if defined KD_ARCH_32BIT_INT
  #if __SIZEOF_INT__ == 4
    #define KD_FSBTC_I32(x) (x)
    #define KD_FSBTC_U32(x) (unsigned int)(x)
  #else
    #define KD_FSBTC_I32(x) (long)(x)
    #define KD_FSBTC_U32(x) (unsigned long)(x)
  #endif
#else
  #define KD_FSBTC_I32(x) (x)
  #define KD_FSBTC_U32(x) (unsigned int)(x)
#endif /* KD_ARCH_32BIT_INT */

#define KD_FSBTC_CHR(x) KD_FSBTC_U32(x)

#if defined KD_ARCH_64BIT_INT
  #ifdef KD_COMP_MSVC
    #define KD_FSBTC_I64(x)   (long long)(x)
    #define KD_FSBTC_U64(x)   (unsigned long long)(x)
    #define KD_FSBTC_IMAX(x)  (long long)(x)
    #define KD_FSBTC_UMAX(x)  (unsigned long long)(x)
    #define KD_FSBTC_USIZE(x) (unsigned long long)(x)
  #else
    #define KD_FSBTC_I64(x)   (long)(x)
    #define KD_FSBTC_U64(x)   (unsigned long)(x)
    #define KD_FSBTC_IMAX(x)  (long)(x)
    #define KD_FSBTC_UMAX(x)  (unsigned long)(x)
    #define KD_FSBTC_USIZE(x) (unsigned long)(x)
  #endif /* KD_COMP_MSVC */
#else
  #define KD_FSBTC_IMAX(x)  KD_FSBTC_I32(x)
  #define KD_FSBTC_UMAX(x)  KD_FSBTC_U32(x)
  #define KD_FSBTC_USIZE(x) KD_FSBTC_U32(x)
#endif /* KD_ARCH_64BIT_INT */


/**
 * ---------------------------------------------------------------------------------------------------------------------
 *  Conditional simplified versions of typedefs and macros
 * ---------------------------------------------------------------------------------------------------------------------
 */

#if defined KD_USE_SIMPLIFIED_TYPES
  #ifndef KD_CPLUSPLUS
    #undef true
    #undef false
    #define false kd_false
    #define true  kd_true
  #endif
typedef kd_bool_t bool;
typedef kd_i8_t    i8;
typedef kd_i16_t   i16;
typedef kd_i32_t   i32;
typedef kd_imin_t  imin;
typedef kd_imax_t  imax;
typedef kd_u8_t    u8;
typedef kd_u16_t   u16;
typedef kd_u32_t   u32;
typedef kd_umin_t  umin;
typedef kd_umax_t  umax;
typedef kd_usize_t usize;
typedef kd_byte_t  byte;
typedef kd_chr_t   chr;
  #if defined KD_ARCH_64BIT_INT
typedef kd_i64_t i64;
typedef kd_u64_t u64;
  #endif /* KD_ARCH_64BIT_INT */
  #undef null
  #define null kd_null
#endif /* KD_USE_SIMPLIFIED_TYPES */


KD_EXTERN_END


#endif /* KD_TYPES_FW_H_ */
