/**
 * @file fixed_widths.c
 * @author Kumarjit Das
 * @date 2025-05-24
 * @brief Fixed width integral types example.
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


#include <stdio.h>

#define KD_USE_SIMPLIFIED_TYPES
#include "kd/types/fw.h"


int
       main(argc, argv)
int    argc;
char** argv;
{
  bool val_bool;
  i8   val_i8;
  i16  val_i16;
  i32  val_i32;
  imin val_imin;
  imax val_imax;
  u8   val_u8;
  u16  val_u16;
  u32  val_u32;
  umin val_umin;
  umax val_umax;

#if defined TYPES_64BIT_INTEGER
  i64 val_i64;
  u64 val_u64;
#endif /* TYPES_64BIT_INTEGER */

  usize val_usize;
  byte  val_byte;
  chr   val_chr;
  void* val_ptr;

  (void)argc;
  (void)argv;

  printf("Fixed width integral types example :: begin\n");

  printf("\nAPI Version: %s\n", KD_VERSION_CSTR);

  printf("\nSizes of types:\n\n");

  printf("KD_SZ_BOOL = %d,\n", (int)KD_SZ_BOOL);
  printf("KD_SZ_I8 = %d,\n", (int)KD_SZ_I8);
  printf("KD_SZ_I16 = %d,\n", (int)KD_SZ_I16);
  printf("KD_SZ_I32 = %d,\n", (int)KD_SZ_I32);
  printf("KD_SZ_IMIN = %d,\n", (int)KD_SZ_IMIN);
  printf("KD_SZ_IMAX = %d,\n", (int)KD_SZ_IMAX);
  printf("KD_SZ_U8 = %d,\n", (int)KD_SZ_U8);
  printf("KD_SZ_U16 = %d,\n", (int)KD_SZ_U16);
  printf("KD_SZ_U32 = %d,\n", (int)KD_SZ_U32);
  printf("KD_SZ_UMIN = %d,\n", (int)KD_SZ_UMIN);
  printf("KD_SZ_UMAX = %d,\n", (int)KD_SZ_UMAX);

#if defined TYPES_64BIT_INTEGER
  printf("KD_SZ_I64 = %d,\n", (int)KD_SZ_I64);
  printf("KD_SZ_U64 = %d,\n", (int)KD_SZ_U64);
#endif /* TYPES_64BIT_INTEGER */

  printf("KD_SZ_USIZE = %d,\n", (int)KD_SZ_USIZE);
  printf("KD_SZ_BYTE = %d,\n", (int)KD_SZ_BYTE);
  printf("KD_SZ_CHR = %d,\n", (int)KD_SZ_CHR);
  printf("KD_SZ_PTR = %d,\n", (int)KD_SZ_PTR);

  printf("\nMinimum values of types:\n\n");

  printf("KD_MIN_I8 = %d,\n", (int)KD_MIN_I8);
  printf("KD_MIN_I16 = %d,\n", (int)KD_MIN_I16);
  printf("KD_MIN_I32 = %ld,\n", (long)KD_MIN_I32);
  printf("KD_MIN_IMIN = %d,\n", (int)KD_MIN_IMIN);

#ifdef KD_COMP_MSVC
  printf("KD_MIN_IMAX = %lld,\n", (long long)KD_MIN_IMAX);
#else
  printf("KD_MIN_IMAX = %ld,\n", (long)KD_MIN_IMAX);
#endif /* KD_COMP_MSVC */

  printf("KD_MIN_U8 = %u,\n", (unsigned int)KD_MIN_U8);
  printf("KD_MIN_U16 = %u,\n", (unsigned int)KD_MIN_U16);
  printf("KD_MIN_U32 = %lu,\n", (unsigned long)KD_MIN_U32);
  printf("KD_MIN_UMIN = %u,\n", (unsigned int)KD_MIN_UMIN);
  printf("KD_MIN_UMAX = %lu,\n", (unsigned long)KD_MIN_UMAX);

#if defined TYPES_64BIT_INTEGER
  #ifdef KD_COMP_MSVC
  printf("KD_MIN_I64 = %lld,\n", (long long)KD_MIN_I64);
  #else
  printf("KD_MIN_I64 = %ld,\n", (long)KD_MIN_I64);
  #endif /* KD_COMP_MSVC */

  #ifdef KD_COMP_MSVC
  printf("KD_MIN_U64 = %llu,\n", (unsigned long long)KD_MIN_U64);
  #else
  printf("KD_MIN_U64 = %lu,\n", (unsigned long)KD_MIN_U64);
  #endif /* KD_COMP_MSVC */
#endif   /* TYPES_64BIT_INTEGER */

  printf("KD_MIN_USIZE = %lu,\n", (unsigned long)KD_MIN_USIZE);
  printf("KD_MIN_BYTE = %d,\n", (int)KD_MIN_BYTE);
  printf("KD_MIN_CHR = %lu,\n", (unsigned long)KD_MIN_CHR);
  printf("KD_MIN_PTR = %p,\n", KD_MIN_PTR);

  printf("\nMaximum values of types:\n\n");

  printf("KD_MAX_I8 = %d,\n", (int)KD_MAX_I8);
  printf("KD_MAX_I16 = %d,\n", (int)KD_MAX_I16);
  printf("KD_MAX_I32 = %ld,\n", (long)KD_MAX_I32);
  printf("KD_MAX_IMIN = %d,\n", (int)KD_MAX_IMIN);

#ifdef KD_COMP_MSVC
  printf("KD_MAX_IMAX = %lld,\n", (long long)KD_MAX_IMAX);
#else
  printf("KD_MAX_IMAX = %ld,\n", (long)KD_MAX_IMAX);
#endif /* KD_COMP_MSVC */

  printf("KD_MAX_U8 = %u,\n", (unsigned int)KD_MAX_U8);
  printf("KD_MAX_U16 = %u,\n", (unsigned int)KD_MAX_U16);
  printf("KD_MAX_U32 = %lu,\n", (unsigned long)KD_MAX_U32);
  printf("KD_MAX_UMIN = %u,\n", (unsigned int)KD_MAX_UMIN);

#ifdef KD_COMP_MSVC
  printf("KD_MAX_UMAX = %llu,\n", (unsigned long long)KD_MAX_UMAX);
#else
  printf("KD_MAX_UMAX = %lu,\n", (unsigned long)KD_MAX_UMAX);
#endif /* KD_COMP_MSVC */

#if defined TYPES_64BIT_INTEGER
  #ifdef KD_COMP_MSVC
  printf("KD_MAX_I64 = %lld,\n", (long long)KD_MAX_I64);
  #else
  printf("KD_MAX_I64 = %ld,\n", (long)KD_MAX_I64);
  #endif /* KD_COMP_MSVC */

  #ifdef KD_COMP_MSVC
  printf("KD_MAX_U64 = %llu,\n", (unsigned long long)KD_MAX_U64);
  #else
  printf("KD_MAX_U64 = %lu,\n", (unsigned long)KD_MAX_U64);
  #endif /* KD_COMP_MSVC */
#endif   /* TYPES_64BIT_INTEGER */

#ifdef KD_COMP_MSVC
  printf("KD_MAX_USIZE = %llu,\n", (unsigned long long)KD_MAX_USIZE);
#else
  printf("KD_MAX_USIZE = %lu,\n", (unsigned long)KD_MAX_USIZE);
#endif /* KD_COMP_MSVC */

  printf("KD_MAX_BYTE = %d,\n", (int)KD_MAX_BYTE);
  printf("KD_MAX_CHR = %lu,\n", (unsigned long)KD_MAX_CHR);

  printf("KD_MAX_PTR = %p,\n", KD_MAX_PTR);

  printf("\nValues of constant values:\n\n");

  printf("true = %d,\n", true);
  printf("false = %d,\n", false);
  printf("null = %p,\n", null);

  printf("\nValues of types:\n\n");

  val_bool = true;
  val_i8   = KD_MAX_I8;
  val_i16  = KD_MAX_I16;
  val_i32  = KD_MAX_I32;
  val_imin = KD_MAX_IMIN;
  val_imax = KD_MAX_IMAX;
  val_u8   = KD_MAX_U8;
  val_u16  = KD_MAX_U16;
  val_u32  = KD_MAX_U32;
  val_umin = KD_MAX_UMIN;
  val_umax = KD_MAX_UMAX;

#if defined TYPES_64BIT_INTEGER
  val_i64 = KD_MAX_I64;
  val_u64 = KD_MAX_U64;
#endif /* TYPES_64BIT_INTEGER */

  val_usize = KD_MAX_USIZE;
  val_byte  = KD_MAX_BYTE;
  val_chr   = KD_MAX_CHR;
  val_ptr   = KD_MAX_PTR;

  printf("val_bool = %s,\n", val_bool ? "true" : "false");
  printf("val_i8 = %d,\n", (i32)val_i8);
  printf("val_i16 = %hd,\n", val_i16);
  printf("val_i32 = %d,\n", val_i32);
  printf("val_imin = %d,\n", (i32)val_imin);

  printf("val_imax = "
#ifdef TYPES_64BIT_INTEGER
  #ifdef KD_COMP_MSVC
         "%lld"
  #else
         "%ld"
  #endif /* KD_COMP_MSVC */
#else
         "%d"
#endif /* TYPES_64BIT_INTEGER */
         ",\n",
         val_imax);

  printf("val_u8 = %u,\n", (u32)val_u8);
  printf("val_u16 = %hu,\n", val_u16);
  printf("val_u32 = %u,\n", val_u32);

#if defined TYPES_64BIT_INTEGER
  #ifdef KD_COMP_MSVC
  printf("val_i64 = %lld,\n", val_i64);
  printf("val_u64 = %llu,\n", val_u64);
  #else
  printf("val_i64 = %ld,\n", val_i64);
  printf("val_u64 = %lu,\n", val_u64);
  #endif /* KD_COMP_MSVC */
#endif   /* TYPES_64BIT_INTEGER */

  printf("val_umin = %u,\n", (u32)val_umin);

  printf("val_umax = "
#ifdef TYPES_64BIT_INTEGER
  #ifdef KD_COMP_MSVC
         "%llu"
  #else
         "%lu"
  #endif /* KD_COMP_MSVC */
#else
         "%u"
#endif /* TYPES_64BIT_INTEGER */
         ",\n",
         val_umax);

  printf("val_usize = "
#ifdef TYPES_64BIT_INTEGER
  #ifdef KD_COMP_MSVC
         "%llu"
  #else
         "%lu"
  #endif /* KD_COMP_MSVC */
#else
         "%u"
#endif /* TYPES_64BIT_INTEGER */
         ",\n",
         val_usize);

  printf("val_byte = %u,\n", (u32)val_byte);
  printf("val_chr = %u,\n", val_chr);
  printf("val_ptr = %p,\n", val_ptr);

  printf("\nFixed width integral types example :: end\n");

  return KD_EXIT_SUCCESS;
}
