/**
 * @file eltype.h
 * @author Kumarjit Das
 * @date 2025-06-30
 * @since 0.0.15
 * @brief Main header file of the ELTYPE library.
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


#ifndef KD_ELTYPE_H_
#define KD_ELTYPE_H_


#include "kd/defs.h"
#include "kd/fixed_width.h"


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
#endif                           /* KD_ARCH_64BIT_INT */

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
