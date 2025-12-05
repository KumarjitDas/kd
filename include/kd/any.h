/**
 * @file any.h
 * @author Kumarjit Das
 * @version 0.0.1
 * @brief Main header file of the KD_ANY library.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 * @since 0.0.1
 */


#ifndef KD_ANY_H_
#define KD_ANY_H_


#include "./version.h"
#include "./platform.h"
#include "./fixed_width.h"
#include "./floating_point.h"
#include "./eltype.h"
#include "./dec.h"


KD_EXTERN_BEGIN


union kd_any_t
{
    kd_i8_t          _i8;
    kd_i16_t         _i16;
    kd_i32_t         _i32;
    kd_imin_t        _imin;
    kd_imax_t        _imax;
    kd_u8_t          _u8;
    kd_u16_t         _u16;
    kd_u32_t         _u32;
    kd_umin_t        _umin;
    kd_umax_t        _umax;
    kd_word_t        _word;
    kd_usize_t       _usize;
    kd_byte_t        _byte;
    kd_chr_t         _chr;
    kd_dec_t         _dec;
    kd_f32_t         _f32;
    kd_f64_t         _f64;
    void            *_ptr;
    enum kd_eltype_t _eltype;
#if defined KD_ARCH_64BIT_INT
    kd_byte_t _slice[8];
    kd_i64_t  _i64;
    kd_u64_t  _u64;
#else
    kd_byte_t _slice[8];
#endif /* KD_ARCH_64BIT_INT */
};

#define KD_PANY_C(X) ((union kd_any_t *)(X))
#define KD_SZ_ANY    sizeof(union kd_any_t)

#if defined KD_USE_SIMPLIFIED_TYPES
typedef union kd_any_t any;
#endif /* KD_USE_SIMPLIFIED_TYPES */


KD_EXTERN_END


#endif /* KD_ANY_H_ */
