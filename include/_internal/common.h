/**
 * @file common.h
 * @author Kumarjit Das
 * @date 2025-06-06
 * @since 0.0.10
 * @brief Common header file for all internal libraries.
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


#ifndef KD__INTERNAL_COMMON_H_
#define KD__INTERNAL_COMMON_H_

#include "kd/defs.h"
#include "kd/types/fw.h"

KD_EXTERN_BEGIN


/**
 * ---------------------------------------------------------------------------------------------------------------------
 *  Sizes Of Primitive Storage Types (In Bytes)
 * ---------------------------------------------------------------------------------------------------------------------
 */

#define KD_SZ_S8  KD_SZ_U8
#define KD_SZ_S16 KD_SZ_U16
#define KD_SZ_S32 KD_SZ_U32
#if defined KD_ARCH_64BIT_INT
  #define KD_SZ_S64 KD_SZ_U64
#endif


/**
 * ---------------------------------------------------------------------------------------------------------------------
 *  Type Definitions
 * ---------------------------------------------------------------------------------------------------------------------
 */

typedef kd_u8_t  kdi_s8_t;
typedef kd_u16_t kdi_s16_t;
typedef kd_u32_t kdi_s32_t;
#if defined KD_ARCH_64BIT_INT
typedef kd_u64_t kdi_s64_t;
#endif


KD_EXTERN_END

#endif /* KD__INTERNAL_COMMON_H_ */
