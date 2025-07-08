/**
 * @file any.h
 * @author Kumarjit Das
 * @date 2025-06-29
 * @since 0.0.15
 * @brief Main header file of the ANY library.
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


#ifndef KD_TYPES_ANY_H_
#define KD_TYPES_ANY_H_


#include "kd/defs.h"
#include "kd/fixed_width.h"
#include "kd/floating_point.h"
#include "kd/eltype.h"
#include "kd/dec.h"


KD_EXTERN_BEGIN


union kd_any_t
{
  kd_i8_t     _i8;
  kd_i16_t    _i16;
  kd_i32_t    _i32;
  kd_imin_t   _imin;
  kd_imax_t   _imax;
  kd_u8_t     _u8;
  kd_u16_t    _u16;
  kd_u32_t    _u32;
  kd_umin_t   _umin;
  kd_umax_t   _umax;
  kd_word_t   _word;
  kd_usize_t  _usize;
  kd_byte_t   _byte;
  kd_chr_t    _chr;
  kd_dec_t    _dec;
  kd_f32_t    _f32;
  kd_f64_t    _f64;
  void       *_ptr;
  kd_eltype_t _eltype;
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


#endif /* KD_TYPES_ANY_H_ */
