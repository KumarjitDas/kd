/**
 * @file dec.h
 * @author Kumarjit Das
 * @date 2025-06-30
 * @since 0.0.15
 * @brief Main header file of the DEC library.
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


#ifndef KD_DEC_H_
#define KD_DEC_H_


#include "kd/defs.h"
#include "kd/fixed_width.h"


KD_EXTERN_BEGIN


typedef kd_usize_t kd_dec_t;

#define KD_LIT_DEC(x)   KD_LIT_USIZE(x)
#define KD_DEC_C(X)     ((kd_dec_t)(X))
#define KD_PDEC_C(X)    ((kd_dec_t *)(X))
#define KD_MIN_DEC      KD_MAX_USIZE
#define KD_MAX_DEC      KD_MAX_WORD
#define KD_SZ_DEC       sizeof(kd_dec_t)
#define KD_FMTSP_DEC    KD_FMTSP_USIZE
#define KD_FSBTC_DEC(x) KD_FSBTC_USIZE(x)

#if defined KD_USE_SIMPLIFIED_TYPES
typedef kd_dec_t dec;
#endif /* KD_USE_SIMPLIFIED_TYPES */


KD_EXTERN_END


#endif /* KD_DEC_H_ */
