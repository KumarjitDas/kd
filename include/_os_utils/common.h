/**
 * @file common.h
 * @author Kumarjit Das
 * @date 2025-05-31
 * @since 0.0.5
 * @brief OS specific common definitions header file for the KD library.
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

#ifndef KD__OS_UTILS_COMMON_H_
#define KD__OS_UTILS_COMMON_H_

#include "kd/defs.h"
#include "kd/fixed_width.h"

#if defined KD_OS_WINDOWS
  #include <windows.h>
#endif

#if defined KD_OS_MINGW
  #if defined KD_OS_WINDOWS && (defined KD_OS_WIN64 || defined KD_OS_MINGW64)
    #define WINDOWS_64BIT 1
  #elif defined KD_OS_WINDOWS && (defined KD_OS_WIN32 || defined KD_OS_MINGW32)
    #define WINDOWS_32BIT 1
  #endif
#else
  #if defined KD_OS_WINDOWS && defined KD_OS_WIN32 && !defined KD_OS_WIN64
    #define WINDOWS_32BIT 1
  #elif defined KD_OS_WINDOWS && defined KD_OS_WIN64
    #define WINDOWS_64BIT 1
  #endif
#endif /* KD_OS_MINGW */

#endif /* KD__OS_UTILS_COMMON_H_ */
