/**
 * @file fixed_width.h
 * @author Kumarjit Das
 * @version 0.0.1
 * @brief Fixed-width integral typedefs and macro definitions.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 * @since 0.0.1
 */


#ifndef KD_FIXED_WIDTH_H_
#define KD_FIXED_WIDTH_H_


#include "./version.h"
#include "./platform.h"
#include "./api.h"


KD_EXTERN_BEGIN


/**
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *  64-Bit Integer and Pointer Signatures
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *  Type Definitions
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

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
    #if defined _MSC_VER || defined __BORLANDC__ || defined __WATCOMC__ || (defined __alpha && defined __DECC) || (defined KD_OS_MINGW64 && defined KD_C_STD_89)
typedef __int64          kd_i64_t;
typedef unsigned __int64 kd_u64_t;
    #elif (defined __GNUC__ || defined __MWERKS__ || defined __SUNPRO_C || defined __SUNPRO_CC || defined __APPLE_CC__ || defined KD_OS_IRIX || defined _LONG_LONG || defined _CRAYC) && __SIZEOF_LONG__ == 8
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
typedef kd_i64_t kd_word_t;
typedef kd_u64_t kd_usize_t;
#else
typedef kd_i32_t kd_word_t;
typedef kd_u32_t kd_usize_t;
#endif /* KD_ARCH_64BIT_PTR */

typedef kd_u8_t  kd_byte_t;
typedef kd_u32_t kd_chr_t;

#if defined KD_ARCH_64BIT_INT
    #define KD_BASE_INT_T  kd_i64_t
    #define KD_BASE_UINT_T kd_u64_t
#else
    #define KD_BASE_INT_T  kd_i32_t
    #define KD_BASE_UINT_T kd_u32_t
#endif /* KD_ARCH_64BIT_INT */


/**
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *  Constant literal postfixes
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

#define KD_LIT_I8(x)  (kd_i8_t)(x)
#define KD_LIT_I16(x) (kd_i16_t)(x)
#define KD_LIT_U8(x)  (kd_u8_t)(x)
#define KD_LIT_U16(x) (kd_u16_t)(x)

#if defined KD_ARCH_32BIT_INT && __SIZEOF_INT__ == 2 && __SIZEOF_LONG__ == 4
    #define KD_LIT_I32(x) x##L
    #define KD_LIT_U32(x) x##UL
#else
    #define KD_LIT_I32(x) (kd_i32_t)(x)
    #define KD_LIT_U32(x) x##U
#endif

#if defined KD_FW_64BIT_INT
    #if defined KD_OS_MINGW64 && defined KD_C_STD_89
        #define KD_LIT_I64(x) ((kd_i64_t)(x))
        #define KD_LIT_U64(x) ((kd_u64_t)(x))
    #else
        #define KD_LIT_I64(x) ((kd_i64_t)(x##L))
        #define KD_LIT_U64(x) ((kd_u64_t)(x##UL))
    #endif

    #define KD_LIT_IMAX(x)  ((kd_imax_t)KD_LIT_I64(x))
    #define KD_LIT_UMAX(x)  ((kd_umax_t)KD_LIT_U64(x))
    #define KD_LIT_WORD(x)  ((kd_word_t)KD_LIT_I64(x))
    #define KD_LIT_USIZE(x) ((kd_usize_t)KD_LIT_U64(x))
#else
    #define KD_LIT_IMAX(x)  ((kd_imax_t)KD_LIT_I32(x))
    #define KD_LIT_UMAX(x)  ((kd_imax_t)KD_LIT_U32(x))
    #define KD_LIT_WORD(x)  ((kd_word_t)KD_LIT_I32(x))
    #define KD_LIT_USIZE(x) ((kd_usize_t)KD_LIT_U32(x))
#endif /* KD_FW_64BIT_INT */

#define KD_LIT_IMIN(x) (kd_imin_t)(x)
#define KD_LIT_UMIN(x) (kd_umin_t)(x)

#define KD_LIT_BYTE(x) (kd_byte_t)(x)
#define KD_LIT_CHR(x)  (kd_chr_t) KD_LIT_U32(x)

#if defined KD_ARCH_64BIT_PTR && defined KD_FW_64BIT_INT
    #define KD_LIT_PTR(x) (void *)KD_LIT_U64(x)
#else
    #define KD_LIT_PTR(x) (void *)KD_LIT_U32(x)
#endif


/**
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *  Type Casts
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

#define KD_I8_C(X)    ((kd_i8_t)(X))
#define KD_I16_C(X)   ((kd_i16_t)(X))
#define KD_I32_C(X)   ((kd_i32_t)(X))
#define KD_IMIN_C(X)  ((kd_imin_t)(X))
#define KD_IMAX_C(X)  ((kd_imax_t)(X))
#define KD_U8_C(X)    ((kd_u8_t)(X))
#define KD_U16_C(X)   ((kd_u16_t)(X))
#define KD_U32_C(X)   ((kd_u32_t)(X))
#define KD_UMIN_C(X)  ((kd_umin_t)(X))
#define KD_UMAX_C(X)  ((kd_umax_t)(X))
#define KD_WORD_C(X)  ((kd_word_t)(X))
#define KD_USIZE_C(X) ((kd_usize_t)(X))
#define KD_BYTE_C(X)  ((kd_byte_t)(X))
#define KD_CHR_C(X)   ((kd_chr_t)(X))
#define KD_PTR_C(X)   ((void *)(X))

#if defined KD_ARCH_64BIT_INT
    #define KD_I64_C(X) ((kd_i64_t)(X))
    #define KD_U64_C(X) ((kd_u64_t)(X))
#endif

#define KD_PI8_C(X)    ((kd_i8_t *)(X))
#define KD_PI16_C(X)   ((kd_i16_t *)(X))
#define KD_PI32_C(X)   ((kd_i32_t *)(X))
#define KD_PIMIN_C(X)  ((kd_imin_t *)(X))
#define KD_PIMAX_C(X)  ((kd_imax_t *)(X))
#define KD_PU8_C(X)    ((kd_u8_t *)(X))
#define KD_PU16_C(X)   ((kd_u16_t *)(X))
#define KD_PU32_C(X)   ((kd_u32_t *)(X))
#define KD_PUMIN_C(X)  ((kd_umin_t *)(X))
#define KD_PUMAX_C(X)  ((kd_umax_t *)(X))
#define KD_PWORD_C(X)  ((kd_word_t *)(X))
#define KD_PUSIZE_C(X) ((kd_usize_t *)(X))
#define KD_PBYTE_C(X)  ((kd_byte_t *)(X))
#define KD_PCHR_C(X)   ((kd_chr_t *)(X))

#if defined KD_ARCH_64BIT_INT
    #define KD_PI64_C(X) ((kd_i64_t *)(X))
    #define KD_PU64_C(X) ((kd_u64_t *)(X))
#endif

#define KD_BASE_INT_C(X)   ((KD_BASE_INT_T)(X))
#define KD_BASE_UINT_C(X)  ((KD_BASE_UINT_T)(X))

#define KD_BASE_PINT_C(X)  ((KD_BASE_INT_T *)(X))
#define KD_BASE_PUINT_C(X) ((KD_BASE_UINT_T *)(X))


/**
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *  Minimum Values Of Defined Types
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

#define KD_MIN_I8          KD_LIT_I8(-128)
#define KD_MIN_I16         KD_LIT_I16(-32768)
#define KD_MIN_I32         (KD_LIT_I32(-2147483647) - KD_LIT_I32(1))
#define KD_MIN_IMIN        KD_LIT_IMIN(-128)
#define KD_MIN_U8          KD_LIT_U8(0)
#define KD_MIN_U16         KD_LIT_U16(0)
#define KD_MIN_U32         KD_LIT_U32(0)
#define KD_MIN_UMIN        KD_LIT_UMIN(0)
#define KD_MIN_BYTE        KD_LIT_BYTE(0)
#define KD_MIN_CHR         KD_LIT_CHR(0)
#define KD_MIN_PTR         KD_LIT_PTR(0)

#if defined KD_ARCH_64BIT_INT
    #if defined KD_OS_MINGW64 && defined KD_C_STD_89
        #define KD_MIN_I64 ((KD_LIT_I64(0x80000000) << 31) << 1)
    #else
        #define KD_MIN_I64 (-9223372036854775807L - 1)
    #endif
    #define KD_MIN_IMAX  KD_MIN_I64
    #define KD_MIN_U64   KD_LIT_U64(0)
    #define KD_MIN_UMAX  KD_MIN_U64
    #define KD_MIN_WORD  KD_MIN_I64
    #define KD_MIN_USIZE KD_MIN_U64
#else
    #define KD_MIN_IMAX  KD_MIN_I32
    #define KD_MIN_UMAX  KD_MIN_U32
    #define KD_MIN_WORD  KD_MIN_I32
    #define KD_MIN_USIZE KD_MIN_U32
#endif /* KD_ARCH_64BIT_INT */


/**
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *  Maximum Values Of Defined Types
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
    #if defined KD_OS_MINGW64 && defined KD_C_STD_89
        #define KD_MAX_I64 (((KD_LIT_I64(0x7FFFFFFF) << 31) << 1) | 0xFFFFFFFF)
        #define KD_MAX_U64 (((KD_LIT_U64(0xFFFFFFFF) << 31) << 1) | 0xFFFFFFFF)
    #else
        #define KD_MAX_I64 9223372036854775807L
        #define KD_MAX_U64 0xffffffffffffffffUL
    #endif
    #define KD_MAX_IMAX  KD_MAX_I64
    #define KD_MAX_UMAX  KD_MAX_U64
    #define KD_MAX_WORD  KD_MAX_I64
    #define KD_MAX_USIZE KD_MAX_U64
#else
    #define KD_MAX_IMAX  KD_MAX_I32
    #define KD_MAX_UMAX  KD_MAX_U32
    #define KD_MAX_WORD  KD_MAX_I32
    #define KD_MAX_USIZE KD_MAX_U32
#endif /* KD_ARCH_64BIT_INT */

#if defined KD_ARCH_64BIT_PTR
    #if defined KD_ARCH_64BIT_INT
        #define KD_MAX_PTR ((void *)KD_MAX_U64)
    #else
        #define KD_MAX_PTR ((void *)0xFFFFFFFFFFFFFFFF)
    #endif /* KD_ARCH_64BIT_INT */
#else
    #define KD_MAX_PTR ((void *)KD_MAX_U32)
#endif     /* KD_ARCH_64BIT_PTR */


/**
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *  Sizes Of Defined Types (In Bytes)
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

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
#define KD_SZ_WORD  sizeof(kd_word_t)
#define KD_SZ_USIZE sizeof(kd_usize_t)
#define KD_SZ_BYTE  sizeof(kd_byte_t)
#define KD_SZ_CHR   sizeof(kd_chr_t)
#define KD_SZ_PTR   sizeof(void *)

#if defined KD_ARCH_64BIT_INT
    #define KD_SZ_I64 sizeof(kd_i64_t)
    #define KD_SZ_U64 sizeof(kd_u64_t)
#endif


/**
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *  C-style Format Specifiers
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

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
        #define KD_FMTSP_WORD  "%lld"
        #define KD_FMTSP_USIZE "%llu"
    #elif defined KD_OS_MINGW64 && !defined KD_C_STD_89 && (KD_C_STD_NO > 0)
        #define KD_FMTSP_I64   "%I64d"
        #define KD_FMTSP_U64   "%I64u"
        #define KD_FMTSP_IMAX  "%I64d"
        #define KD_FMTSP_UMAX  "%I64u"
        #define KD_FMTSP_WORD  "%I64d"
        #define KD_FMTSP_USIZE "%I64u"
    #else
        #define KD_FMTSP_I64   "%ld"
        #define KD_FMTSP_U64   "%lu"
        #define KD_FMTSP_IMAX  "%ld"
        #define KD_FMTSP_UMAX  "%lu"
        #define KD_FMTSP_WORD  "%ld"
        #define KD_FMTSP_USIZE "%lu"
    #endif /* KD_COMP_MSVC */
#else
    #define KD_FMTSP_IMAX  KD_FMTSP_I32
    #define KD_FMTSP_UMAX  KD_FMTSP_U32
    #define KD_FMTSP_USIZE KD_FMTSP_U32
#endif /* KD_ARCH_64BIT_INT */


/**
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *  C-style Format Specifier Based Type Cast
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

#define KD_FSBTC_I8(x)   (int)(x)
#define KD_FSBTC_I16(x)  (int)(x)
#define KD_FSBTC_IMIN(x) (int)(x)
#define KD_FSBTC_U8(x)   (unsigned int)(x)
#define KD_FSBTC_U16(x)  (unsigned int)(x)
#define KD_FSBTC_UMIN(x) (unsigned int)(x)
#define KD_FSBTC_BYTE(x) (unsigned int)(x)
#define KD_FSBTC_PTR(x)  (void *)(x)

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
        #define KD_FSBTC_WORD(x)  (long long)(x)
        #define KD_FSBTC_USIZE(x) (unsigned long long)(x)
    #else
        #define KD_FSBTC_I64(x)   (long)(x)
        #define KD_FSBTC_U64(x)   (unsigned long)(x)
        #define KD_FSBTC_IMAX(x)  (long)(x)
        #define KD_FSBTC_UMAX(x)  (unsigned long)(x)
        #define KD_FSBTC_WORD(x)  (long)(x)
        #define KD_FSBTC_USIZE(x) (unsigned long)(x)
    #endif /* KD_COMP_MSVC */
#else
    #define KD_FSBTC_IMAX(x)  KD_FSBTC_I32(x)
    #define KD_FSBTC_UMAX(x)  KD_FSBTC_U32(x)
    #define KD_FSBTC_WORD(x)  KD_FSBTC_I32(x)
    #define KD_FSBTC_USIZE(x) KD_FSBTC_U32(x)
#endif /* KD_ARCH_64BIT_INT */


/**
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *  Constant Values/Macros/Enumerations
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

#define kd_null     KD_LIT_PTR(0x00)

#define KD_LAST_IDX (-1)

#if defined KD_RESULT_SUCCESS
    #undef KD_RESULT_SUCCESS
#endif
#if defined KD_RESULT_FAILURE
    #undef KD_RESULT_FAILURE
#endif


/**
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *  Simplified versions of typedefs, macros, and miscellaneous constants without library initials/prefix
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

#undef null
#define null  kd_null
#define i8    kd_i8_t
#define i16   kd_i16_t
#define i32   kd_i32_t
#define imin  kd_imin_t
#define imax  kd_imax_t
#define u8    kd_u8_t
#define u16   kd_u16_t
#define u32   kd_u32_t
#define umin  kd_umin_t
#define umax  kd_umax_t
#define word  kd_word_t
#define usize kd_usize_t
#define byte  kd_byte_t
#define chr   kd_chr_t

#if defined KD_ARCH_64BIT_INT
    #define i64 kd_i64_t
    #define u64 kd_u64_t
#endif

#define LIT_I8(x)   KD_LIT_I8(x)
#define LIT_I16(x)  KD_LIT_I16(x)
#define LIT_U8(x)   KD_LIT_U8(x)
#define LIT_U16(x)  KD_LIT_U16(x)
#define LIT_I32(x)  KD_LIT_I32(x)
#define LIT_U32(x)  KD_LIT_U32(x)
#define LIT_IMIN(x) KD_LIT_IMIN(x)
#define LIT_UMIN(x) KD_LIT_UMIN(x)
#define LIT_BYTE(x) KD_LIT_BYTE(x)
#define LIT_CHR(x)  KD_LIT_CHR(x)
#define LIT_PTR(x)  KD_LIT_PTR(x)

#if defined KD_FW_64BIT_INT
    #define LIT_I64(x)   KD_LIT_I64(x)
    #define LIT_U64(x)   KD_LIT_U64(x)
    #define LIT_IMAX(x)  KD_LIT_IMAX(x)
    #define LIT_UMAX(x)  KD_LIT_UMAX(x)
    #define LIT_WORD(x)  KD_LIT_WORD(x)
    #define LIT_USIZE(x) KD_LIT_USIZE(x)
#else
    #define LIT_IMAX(x)  KD_LIT_IMAX(x)
    #define LIT_UMAX(x)  KD_LIT_UMAX(x)
    #define LIT_WORD(x)  KD_LIT_WORD(x)
    #define LIT_USIZE(x) KD_LIT_USIZE(x)
#endif

#define I8_C(x)    KD_I8_C(x)
#define I16_C(x)   KD_I16_C(x)
#define I32_C(x)   KD_I32_C(x)
#define IMIN_C(x)  KD_IMIN_C(x)
#define IMAX_C(x)  KD_IMAX_C(x)
#define U8_C(x)    KD_U8_C(x)
#define U16_C(x)   KD_U16_C(x)
#define U32_C(x)   KD_U32_C(x)
#define UMIN_C(x)  KD_UMIN_C(x)
#define UMAX_C(x)  KD_UMAX_C(x)
#define WORD_C(x)  KD_WORD_C(x)
#define USIZE_C(x) KD_USIZE_C(x)
#define BYTE_C(x)  KD_BYTE_C(x)
#define CHR_C(x)   KD_CHR_C(x)
#define PTR_C(x)   KD_PTR_C(x)

#if defined KD_ARCH_64BIT_INT
    #define I64_C(x) KD_I64_C(x)
    #define U64_C(x) KD_U64_C(x)
#endif

#define PI8_C(x)    KD_PI8_C(x)
#define PI16_C(x)   KD_PI16_C(x)
#define PI32_C(x)   KD_PI32_C(x)
#define PIMIN_C(x)  KD_PIMIN_C(x)
#define PIMAX_C(x)  KD_PIMAX_C(x)
#define PU8_C(x)    KD_PU8_C(x)
#define PU16_C(x)   KD_PU16_C(x)
#define PU32_C(x)   KD_PU32_C(x)
#define PUMIN_C(x)  KD_PUMIN_C(x)
#define PUMAX_C(x)  KD_PUMAX_C(x)
#define PWORD_C(x)  KD_PWORD_C(x)
#define PUSIZE_C(x) KD_PUSIZE_C(x)
#define PBYTE_C(x)  KD_PBYTE_C(x)
#define PCHR_C(x)   KD_PCHR_C(x)

#if defined KD_ARCH_64BIT_INT
    #define PI64_C(x) KD_PI64_C(x)
    #define PU64_C(x) KD_PU64_C(x)
#endif

#define BASE_INT_T      KD_BASE_INT_T
#define BASE_UINT_T     KD_BASE_UINT_T
#define BASE_INT_C(x)   KD_BASE_INT_C(x)
#define BASE_UINT_C(x)  KD_BASE_UINT_C(x)
#define BASE_PINT_C(x)  KD_BASE_PINT_C(x)
#define BASE_PUINT_C(x) KD_BASE_PUINT_C(x)

#define MIN_I8          KD_MIN_I8
#define MIN_I16         KD_MIN_I16
#define MIN_I32         KD_MIN_I32
#define MIN_IMIN        KD_MIN_IMIN
#define MIN_U8          KD_MIN_U8
#define MIN_U16         KD_MIN_U16
#define MIN_U32         KD_MIN_U32
#define MIN_UMIN        KD_MIN_UMIN
#define MIN_BYTE        KD_MIN_BYTE
#define MIN_CHR         KD_MIN_CHR
#define MIN_PTR         KD_MIN_PTR

#if defined KD_ARCH_64BIT_INT
    #define MIN_I64   KD_MIN_I64
    #define MIN_IMAX  KD_MIN_IMAX
    #define MIN_U64   KD_MIN_U64
    #define MIN_UMAX  KD_MIN_UMAX
    #define MIN_WORD  KD_MIN_WORD
    #define MIN_USIZE KD_MIN_USIZE
#else
    #define MIN_IMAX  KD_MIN_IMAX
    #define MIN_UMAX  KD_MIN_UMAX
    #define MIN_WORD  KD_MIN_WORD
    #define MIN_USIZE KD_MIN_USIZE
#endif

#define MAX_I8   KD_MAX_I8
#define MAX_I16  KD_MAX_I16
#define MAX_I32  KD_MAX_I32
#define MAX_IMIN KD_MAX_IMIN
#define MAX_U8   KD_MAX_U8
#define MAX_U16  KD_MAX_U16
#define MAX_U32  KD_MAX_U32
#define MAX_UMIN KD_MAX_UMIN
#define MAX_BYTE KD_MAX_BYTE
#define MAX_CHR  KD_MAX_CHR

#if defined KD_ARCH_64BIT_INT
    #define MAX_I64   KD_MAX_I64
    #define MAX_IMAX  KD_MAX_IMAX
    #define MAX_U64   KD_MAX_U64
    #define MAX_UMAX  KD_MAX_UMAX
    #define MAX_WORD  KD_MAX_WORD
    #define MAX_USIZE KD_MAX_USIZE
#else
    #define MAX_IMAX  KD_MAX_IMAX
    #define MAX_UMAX  KD_MAX_UMAX
    #define MAX_WORD  KD_MAX_WORD
    #define MAX_USIZE KD_MAX_USIZE
#endif

#define MAX_PTR  KD_MAX_PTR

#define SZ_I8    KD_SZ_I8
#define SZ_I16   KD_SZ_I16
#define SZ_I32   KD_SZ_I32
#define SZ_IMIN  KD_SZ_IMIN
#define SZ_IMAX  KD_SZ_IMAX
#define SZ_U8    KD_SZ_U8
#define SZ_U16   KD_SZ_U16
#define SZ_U32   KD_SZ_U32
#define SZ_UMIN  KD_SZ_UMIN
#define SZ_UMAX  KD_SZ_UMAX
#define SZ_WORD  KD_SZ_WORD
#define SZ_USIZE KD_SZ_USIZE
#define SZ_BYTE  KD_SZ_BYTE
#define SZ_CHR   KD_SZ_CHR
#define SZ_PTR   KD_SZ_PTR

#if defined KD_ARCH_64BIT_INT
    #define SZ_I64 KD_SZ_I64
    #define SZ_U64 KD_SZ_U64
#endif

#define FMTSP_I8   KD_FMTSP_I8
#define FMTSP_I16  KD_FMTSP_I16
#define FMTSP_IMIN KD_FMTSP_IMIN
#define FMTSP_U8   KD_FMTSP_U8
#define FMTSP_U16  KD_FMTSP_U16
#define FMTSP_UMIN KD_FMTSP_UMIN
#define FMTSP_BYTE KD_FMTSP_BYTE
#define FMTSP_PTR  KD_FMTSP_PTR
#define FMTSP_I32  KD_FMTSP_I32
#define FMTSP_U32  KD_FMTSP_U32
#define FMTSP_CHR  KD_FMTSP_CHR

#if defined KD_ARCH_64BIT_INT
    #define FMTSP_I64   KD_FMTSP_I64
    #define FMTSP_U64   KD_FMTSP_U64
    #define FMTSP_IMAX  KD_FMTSP_IMAX
    #define FMTSP_UMAX  KD_FMTSP_UMAX
    #define FMTSP_WORD  KD_FMTSP_WORD
    #define FMTSP_USIZE KD_FMTSP_USIZE
#else
    #define FMTSP_IMAX  KD_FMTSP_IMAX
    #define FMTSP_UMAX  KD_FMTSP_UMAX
    #define FMTSP_USIZE KD_FMTSP_USIZE
#endif

#define FSBTC_I8(x)   KD_FSBTC_I8(x)
#define FSBTC_I16(x)  KD_FSBTC_I16(x)
#define FSBTC_IMIN(x) KD_FSBTC_IMIN(x)
#define FSBTC_U8(x)   KD_FSBTC_U8(x)
#define FSBTC_U16(x)  KD_FSBTC_U16(x)
#define FSBTC_UMIN(x) KD_FSBTC_UMIN(x)
#define FSBTC_BYTE(x) KD_FSBTC_BYTE(x)
#define FSBTC_PTR(x)  KD_FSBTC_PTR(x)
#define FSBTC_I32(x)  KD_FSBTC_I32(x)
#define FSBTC_U32(x)  KD_FSBTC_U32(x)
#define FSBTC_CHR(x)  KD_FSBTC_CHR(x)

#if defined KD_ARCH_64BIT_INT
    #define FSBTC_I64(x)   KD_FSBTC_I64(x)
    #define FSBTC_U64(x)   KD_FSBTC_U64(x)
    #define FSBTC_IMAX(x)  KD_FSBTC_IMAX(x)
    #define FSBTC_UMAX(x)  KD_FSBTC_UMAX(x)
    #define FSBTC_WORD(x)  KD_FSBTC_WORD(x)
    #define FSBTC_USIZE(x) KD_FSBTC_USIZE(x)
#else
    #define FSBTC_IMAX(x)  KD_FSBTC_IMAX(x)
    #define FSBTC_UMAX(x)  KD_FSBTC_UMAX(x)
    #define FSBTC_WORD(x)  KD_FSBTC_WORD(x)
    #define FSBTC_USIZE(x) KD_FSBTC_USIZE(x)
#endif

#define LAST_IDX KD_LAST_IDX


KD_EXTERN_END


#endif /* KD_FIXED_WIDTH_H_ */
