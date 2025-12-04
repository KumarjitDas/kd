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


#include "./version.h"
#include "./platform.h"
#include "./fixed_width.h"
#include "./floating_point.h"


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

#define KD_LIT_ELTYPE(x)   KD_LIT_I32(x)
#define KD_ELTYPE_C(X)     ((enum kd_eltype_t)(X))
#define KD_PELTYPE_C(X)    ((enum kd_eltype_t *)(X))
#define KD_MIN_ELTYPE      KD_ELTYPE_DEFAULT
#define KD_MAX_ELTYPE      KD_ELTYPE_CUSTOM_STRUCT_PTR
#define KD_SZ_ELTYPE       sizeof(enum kd_eltype_t)
#define KD_FMTSP_ELTYPE    KD_FMTSP_I32
#define KD_FSBTC_ELTYPE(x) KD_FSBTC_I32(x)

#define eltype             enum kd_eltype_t

#define ELTYPE_DEFAULT     KD_ELTYPE_DEFAULT
#define ELTYPE_BYTE        KD_ELTYPE_BYTE
#define ELTYPE_I8          KD_ELTYPE_I8
#define ELTYPE_U8          KD_ELTYPE_U8
#define ELTYPE_IMIN        KD_ELTYPE_IMIN
#define ELTYPE_UMIN        KD_ELTYPE_UMIN
#define ELTYPE_I16         KD_ELTYPE_I16
#define ELTYPE_U16         KD_ELTYPE_U16
#define ELTYPE_I32         KD_ELTYPE_I32
#define ELTYPE_U32         KD_ELTYPE_U32
#define ELTYPE_BOOL        KD_ELTYPE_BOOL
#define ELTYPE_CHR         KD_ELTYPE_CHR
#define ELTYPE_UMAX        KD_ELTYPE_UMAX
#define ELTYPE_IMAX        KD_ELTYPE_IMAX
#define ELTYPE_WORD        KD_ELTYPE_WORD
#define ELTYPE_USIZE       KD_ELTYPE_USIZE
#define ELTYPE_PTR         KD_ELTYPE_PTR
#define ELTYPE_DEC         KD_ELTYPE_DEC
#define ELTYPE_F32         KD_ELTYPE_F32
#define ELTYPE_F64         KD_ELTYPE_F64
#define ELTYPE_ANY         KD_ELTYPE_ANY
#if defined KD_ARCH_64BIT_INT
    #define ELTYPE_I64 KD_ELTYPE_I64
    #define ELTYPE_U64 KD_ELTYPE_U64
#endif /* KD_ARCH_64BIT_INT */


KD_EXTERN_END


#endif /* KD_ELTYPE_H_ */
