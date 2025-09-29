/**
 * @file kd_eltype.h
 * @author Kumarjit Das
 * @version 0.0.1
 * @brief Main header file of the KD_ELTYPE library.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 * @since 0.0.1
 */


#ifndef KD_ELTYPE_H_
#define KD_ELTYPE_H_


#include "kd_version.h"
#include "kd_platform.h"
#include "kd_fixed_width.h"


KD_EXTERN_BEGIN


enum kd_eltype_t
{
    KD_ELTYPE_DEFAULT,

    KD_ELTYPE_BYTE,
    KD_ELTYPE_I8,
    KD_ELTYPE_U8,
    KD_ELTYPE_IMIN,
    KD_ELTYPE_UMIN,
    KD_ELTYPE_I16,
    KD_ELTYPE_U16,
    KD_ELTYPE_I32,
    KD_ELTYPE_U32,
    KD_ELTYPE_BOOL,
    KD_ELTYPE_CHR,
    KD_ELTYPE_UMAX,
    KD_ELTYPE_IMAX,
    KD_ELTYPE_WORD,
    KD_ELTYPE_USIZE,
    KD_ELTYPE_PTR,
    KD_ELTYPE_DEC,
    KD_ELTYPE_F32,
    KD_ELTYPE_F64,
    KD_ELTYPE_ANY,
#if defined KD_ARCH_64BIT_INT
    KD_ELTYPE_I64,
    KD_ELTYPE_U64,
#endif                             /* KD_ARCH_64BIT_INT */

    KDI_IGNORE_ELTYPE = KD_MAX_I32 /* Force it to be always 32-bit */
};

#if defined KD_ARCH_64BIT_INT
    #define KDI_IGNORE_ELTYPE_MAX_VAL KD_ELTYPE_U64
#else
    #define KDI_IGNORE_ELTYPE_MAX_VAL KD_ELTYPE_ANY
#endif

#define KD_LIT_ELTYPE(x)   KD_LIT_I32(x)
#define KD_ELTYPE_C(X)     ((enum kd_eltype_t)(X))
#define KD_PELTYPE_C(X)    ((enum kd_eltype_t *)(X))
#define KD_MIN_ELTYPE      KD_ELTYPE_DEFAULT
#define KD_MAX_ELTYPE      KDI_IGNORE_ELTYPE_MAX_VAL
#define KD_SZ_ELTYPE       sizeof(enum kd_eltype_t)
#define KD_FMTSP_ELTYPE    KD_FMTSP_I32
#define KD_FSBTC_ELTYPE(x) KD_FSBTC_I32(x)

#if defined KD_USE_SIMPLIFIED_TYPES
typedef enum kd_eltype_t eltype;
#endif /* KD_USE_SIMPLIFIED_TYPES */


KD_EXTERN_END


#endif /* KD_ELTYPE_H_ */
