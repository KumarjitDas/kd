/**
 * @file example-003-types.c
 * @author Kumarjit Das
 * @date 2025-05-24
 * @brief TYPES library example source file #1.
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
#include "types.h"


int main(int argc, char** argv)
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
  #endif  /* TYPES_64BIT_INTEGER */

  usize val_usize;
  byte  val_byte;
  chr   val_chr;
  f32   val_f32;
  f64   val_f64;
  any   val_any;
  void* val_ptr;

  (void) argc;
  (void) argv;

  printf("TYPES example #1 :: begin\n");

  printf("\nAPI Version: %s\n", KD_VERSION_STR);

  printf("\nSizes of types:\n\n");

  printf("SZ_BOOL = %d,\n", (int) SZ_BOOL);
  printf("SZ_I8 = %d,\n", (int) SZ_I8);
  printf("SZ_I16 = %d,\n", (int) SZ_I16);
  printf("SZ_I32 = %d,\n", (int) SZ_I32);
  printf("SZ_IMIN = %d,\n", (int) SZ_IMIN);
  printf("SZ_IMAX = %d,\n", (int) SZ_IMAX);
  printf("SZ_U8 = %d,\n", (int) SZ_U8);
  printf("SZ_U16 = %d,\n", (int) SZ_U16);
  printf("SZ_U32 = %d,\n", (int) SZ_U32);
  printf("SZ_UMIN = %d,\n", (int) SZ_UMIN);
  printf("SZ_UMAX = %d,\n", (int) SZ_UMAX);

  #if defined TYPES_64BIT_INTEGER
  printf("SZ_I64 = %d,\n", (int) SZ_I64);
  printf("SZ_U64 = %d,\n", (int) SZ_U64);
  #endif  /* TYPES_64BIT_INTEGER */

  printf("SZ_USIZE = %d,\n", (int) SZ_USIZE);
  printf("SZ_BYTE = %d,\n", (int) SZ_BYTE);
  printf("SZ_CHR = %d,\n", (int) SZ_CHR);
  printf("SZ_F32 = %d,\n", (int) SZ_F32);
  printf("SZ_F64 = %d,\n", (int) SZ_F64);
  printf("SZ_ANY = %d,\n", (int) SZ_ANY);
  printf("SZ_PTR = %d,\n", (int) SZ_PTR);

  printf("\nMinimum values of types:\n\n");

  printf("MIN_I8 = %d,\n", (int) MIN_I8);
  printf("MIN_I16 = %d,\n", (int) MIN_I16);
  printf("MIN_I32 = %ld,\n", (long) MIN_I32);
  printf("MIN_IMIN = %d,\n", (int) MIN_IMIN);

  #ifdef KD_COMP_MSVC
  printf("MIN_IMAX = %lld,\n", (long long) MIN_IMAX);
  #else
  printf("MIN_IMAX = %ld,\n", (long) MIN_IMAX);
  #endif  /* KD_COMP_MSVC */

  printf("MIN_U8 = %u,\n", (unsigned int) MIN_U8);
  printf("MIN_U16 = %u,\n", (unsigned int) MIN_U16);
  printf("MIN_U32 = %lu,\n", (unsigned long) MIN_U32);
  printf("MIN_UMIN = %u,\n", (unsigned int) MIN_UMIN);
  printf("MIN_UMAX = %lu,\n", (unsigned long) MIN_UMAX);

  #if defined TYPES_64BIT_INTEGER
  #ifdef KD_COMP_MSVC
  printf("MIN_I64 = %lld,\n", (long long) MIN_I64);
  #else
  printf("MIN_I64 = %ld,\n", (long) MIN_I64);
  #endif  /* KD_COMP_MSVC */

  #ifdef KD_COMP_MSVC
  printf("MIN_U64 = %llu,\n", (unsigned long long) MIN_U64);
  #else
  printf("MIN_U64 = %lu,\n", (unsigned long) MIN_U64);
  #endif  /* KD_COMP_MSVC */
  #endif  /* TYPES_64BIT_INTEGER */

  printf("MIN_USIZE = %lu,\n", (unsigned long) MIN_USIZE);
  printf("MIN_BYTE = %d,\n", (int) MIN_BYTE);
  printf("MIN_CHR = %lu,\n", (unsigned long) MIN_CHR);
  printf("MIN_F32 = %.9e,\n", (double) MIN_F32);
  printf("MIN_F64 = %.17e,\n", MIN_F64);
  printf("MIN_FMIN = %.9e,\n", (double) MIN_FMIN);
  printf("MIN_FMAX = %.17e,\n", MIN_FMAX);
  printf("MIN_PTR = %p,\n", MIN_PTR);

  printf("\nMaximum values of types:\n\n");

  printf("MAX_I8 = %d,\n", (int) MAX_I8);
  printf("MAX_I16 = %d,\n", (int) MAX_I16);
  printf("MAX_I32 = %ld,\n", (long) MAX_I32);
  printf("MAX_IMIN = %d,\n", (int) MAX_IMIN);

  #ifdef KD_COMP_MSVC
  printf("MAX_IMAX = %lld,\n", (long long) MAX_IMAX);
  #else
  printf("MAX_IMAX = %ld,\n", (long) MAX_IMAX);
  #endif  /* KD_COMP_MSVC */

  printf("MAX_U8 = %u,\n", (unsigned int) MAX_U8);
  printf("MAX_U16 = %u,\n", (unsigned int) MAX_U16);
  printf("MAX_U32 = %lu,\n", (unsigned long) MAX_U32);
  printf("MAX_UMIN = %u,\n", (unsigned int) MAX_UMIN);

  #ifdef KD_COMP_MSVC
  printf("MAX_UMAX = %llu,\n", (unsigned long long) MAX_UMAX);
  #else
  printf("MAX_UMAX = %lu,\n", (unsigned long) MAX_UMAX);
  #endif  /* KD_COMP_MSVC */

  #if defined TYPES_64BIT_INTEGER
  #ifdef KD_COMP_MSVC
  printf("MAX_I64 = %lld,\n", (long long) MAX_I64);
  #else
  printf("MAX_I64 = %ld,\n", (long) MAX_I64);
  #endif  /* KD_COMP_MSVC */

  #ifdef KD_COMP_MSVC
  printf("MAX_U64 = %llu,\n", (unsigned long long) MAX_U64);
  #else
  printf("MAX_U64 = %lu,\n", (unsigned long) MAX_U64);
  #endif  /* KD_COMP_MSVC */
  #endif  /* TYPES_64BIT_INTEGER */

  #ifdef KD_COMP_MSVC
  printf("MAX_USIZE = %llu,\n", (unsigned long long) MAX_USIZE);
  #else
  printf("MAX_USIZE = %lu,\n", (unsigned long) MAX_USIZE);
  #endif  /* KD_COMP_MSVC */

  printf("MAX_BYTE = %d,\n", (int) MAX_BYTE);
  printf("MAX_CHR = %lu,\n", (unsigned long) MAX_CHR);
  printf("MAX_F32 = %.9e,\n", (double) MAX_F32);
  printf("MAX_F64 = %.17e,\n", MAX_F64);
  printf("MAX_FMIN = %.9e,\n", (double) MAX_FMIN);
  printf("MAX_FMAX = %.17e,\n", MAX_FMAX);

  printf("MAX_PTR = %p,\n", MAX_PTR);

  printf("\nValues of constant values:\n\n");

  printf("true = %d,\n", true);
  printf("false = %d,\n", false);
  printf("null = %p,\n", null);

  printf("\nValues of types:\n\n");

  val_bool = true;
  val_i8   = MAX_I8;
  val_i16  = MAX_I16;
  val_i32  = MAX_I32;
  val_imin = MAX_IMIN;
  val_imax = MAX_IMAX;
  val_u8   = MAX_U8;
  val_u16  = MAX_U16;
  val_u32  = MAX_U32;
  val_umin = MAX_UMIN;
  val_umax = MAX_UMAX;

  #if defined TYPES_64BIT_INTEGER
  val_i64 = MAX_I64;
  val_u64 = MAX_U64;
  #endif  /* TYPES_64BIT_INTEGER */

  val_usize        = MAX_USIZE;
  val_byte         = MAX_BYTE;
  val_chr          = MAX_CHR;
  val_f32          = MAX_F32;
  val_f64          = MAX_F64;
  val_any.val_umax = MAX_UMAX;
  val_ptr          = MAX_PTR;

  printf("val_bool = %s,\n", val_bool ? "true" : "false");
  printf("val_i8 = %d,\n", (i32) val_i8);
  printf("val_i16 = %hd,\n", val_i16);
  printf("val_i32 = %d,\n", val_i32);
  printf("val_imin = %d,\n", (i32) val_imin);

  printf(
    "val_imax = "
    #ifdef TYPES_64BIT_INTEGER
    #ifdef KD_COMP_MSVC
    "%lld"
    #else
    "%ld"
    #endif  /* KD_COMP_MSVC */
    #else
    "%d"
    #endif  /* TYPES_64BIT_INTEGER */
    ",\n",
    val_imax
  );

  printf("val_u8 = %u,\n", (u32) val_u8);
  printf("val_u16 = %hu,\n", val_u16);
  printf("val_u32 = %u,\n", val_u32);

  #if defined TYPES_64BIT_INTEGER
  #ifdef KD_COMP_MSVC
  printf("val_i64 = %lld,\n", val_i64);
  printf("val_u64 = %llu,\n", val_u64);
  #else
  printf("val_i64 = %ld,\n", val_i64);
  printf("val_u64 = %lu,\n", val_u64);
  #endif  /* KD_COMP_MSVC */
  #endif  /* TYPES_64BIT_INTEGER */

  printf("val_umin = %u,\n", (u32) val_umin);

  printf(
    "val_umax = "
    #ifdef TYPES_64BIT_INTEGER
    #ifdef KD_COMP_MSVC
    "%llu"
    #else
    "%lu"
    #endif  /* KD_COMP_MSVC */
    #else
    "%u"
    #endif  /* TYPES_64BIT_INTEGER */
    ",\n",
    val_umax
  );

  printf(
    "val_usize = "
    #ifdef TYPES_64BIT_INTEGER
    #ifdef KD_COMP_MSVC
    "%llu"
    #else
    "%lu"
    #endif  /* KD_COMP_MSVC */
    #else
    "%u"
    #endif  /* TYPES_64BIT_INTEGER */
    ",\n",
    val_usize
  );

  printf("val_byte = %u,\n", (u32) val_byte);
  printf("val_chr = %u,\n", val_chr);
  printf("val_f32 = %f,\n", (double) val_f32);
  printf("val_f64 = %f,\n", val_f64);

  printf("val_any: {\n");
  printf(
    "\tval = "
    #ifdef TYPES_64BIT_INTEGER
    #ifdef KD_COMP_MSVC
    "%lld"
    #else
    "%ld"
    #endif  /* KD_COMP_MSVC */
    #else
    "%d"
    #endif  /* TYPES_64BIT_INTEGER */
    ",\n",
    val_any.val
  );
  printf("\tptr = %p\n", val_any.ptr);

  printf(
    "\tslice = [%d, %d, %d, %d"
    #if defined TYPES_64BIT_INTEGER
    ", %d, %d, %d, %d"
    #endif  /* TYPES_64BIT_INTEGER */
    "]\n",
    val_any.slice[0],
    val_any.slice[1],
    val_any.slice[2],
    val_any.slice[3]
    #if defined TYPES_64BIT_INTEGER
    ,
    val_any.slice[4],
    val_any.slice[5],
    val_any.slice[6],
    val_any.slice[7]
    #endif  /* TYPES_64BIT_INTEGER */
  );

  printf("\tval_bool = %s\n", val_any.val_bool ? "true" : "false");
  printf("\tval_i8 = %d\n", (i32) val_any.val_i8);
  printf("\tval_i16 = %hd\n", val_any.val_i16);
  printf("\tval_i32 = %d\n", val_any.val_i32);
  printf("\tval_imin = %d\n", (i32) val_any.val_imin);

  printf(
    "\tval_imax = "
    #ifdef TYPES_64BIT_INTEGER
    #ifdef KD_COMP_MSVC
    "%lld"
    #else
    "%ld"
    #endif  /* KD_COMP_MSVC */
    #else
    "%d"
    #endif  /* TYPES_64BIT_INTEGER */
    ",\n",
    val_any.val_imax
  );

  printf("\tval_u8 = %u\n", (u32) val_any.val_u8);
  printf("\tval_u16 = %hu\n", val_any.val_u16);
  printf("\tval_u32 = %u\n", val_any.val_u32);
  printf("\tval_umin = %u\n", (u32) val_any.val_umin);

  printf(
    "\tval_umax = "
    #ifdef TYPES_64BIT_INTEGER
    #ifdef KD_COMP_MSVC
    "%llu"
    #else
    "%lu"
    #endif  /* KD_COMP_MSVC */
    #else
    "%u"
    #endif  /* TYPES_64BIT_INTEGER */
    ",\n",
    val_any.val_umax
  );

  printf(
    "\tval_usize = "
    #ifdef TYPES_64BIT_INTEGER
    #ifdef KD_COMP_MSVC
    "%llu"
    #else
    "%lu"
    #endif  /* KD_COMP_MSVC */
    #else
    "%u"
    #endif  /* TYPES_64BIT_INTEGER */
    ",\n",
    val_any.val_usize
  );

  printf("\tval_byte = %u\n", (u32) val_any.val_byte);
  printf("\tval_chr = %u\n", val_any.val_chr);
  printf("\tval_f32 = %f\n", (double) val_any.val_f32);
  printf("\tval_f64 = %f\n", val_any.val_f64);
  printf("\tptr_bool = %p\n", (void*) val_any.ptr_bool);
  printf("\tptr_i8 = %p\n", (void*) val_any.ptr_i8);
  printf("\tptr_i16 = %p\n", (void*) val_any.ptr_i16);
  printf("\tptr_i32 = %p\n", (void*) val_any.ptr_i32);
  printf("\tptr_imin = %p\n", (void*) val_any.ptr_imin);
  printf("\tptr_imax = %p\n", (void*) val_any.ptr_imax);
  printf("\tptr_u8 = %p\n", (void*) val_any.ptr_u8);
  printf("\tptr_u16 = %p\n", (void*) val_any.ptr_u16);
  printf("\tptr_u32 = %p\n", (void*) val_any.ptr_u32);
  printf("\tptr_umin = %p\n", (void*) val_any.ptr_umin);
  printf("\tptr_umax = %p\n", (void*) val_any.ptr_umax);
  printf("\tptr_usize = %p\n", (void*) val_any.ptr_usize);
  printf("\tptr_byte = %p\n", (void*) val_any.ptr_byte);
  printf("\tptr_chr = %p\n", (void*) val_any.ptr_chr);
  printf("\tptr_f32 = %p\n", (void*) val_any.ptr_f32);
  printf("\tptr_f64 = %p\n", (void*) val_any.ptr_f64);

  #ifdef TYPES_64BIT_INTEGER
  #ifdef KD_COMP_MSVC
  printf("\tval_i64 = %lld\n", val_any.val_i64);
  printf("\tval_u64 = %llu\n", val_any.val_u64);
  #else
  printf("\tval_i64 = %ld\n", val_any.val_i64);
  printf("\tval_u64 = %lu\n", val_any.val_u64);
  #endif  /* KD_COMP_MSVC */

  printf("\tptr_i64 = %p\n", (void*) val_any.ptr_i64);
  printf("\tptr_u64 = %p\n", (void*) val_any.ptr_u64);
  #endif  /* TYPES_64BIT_INTEGER */

  printf("}\n");

  printf("val_ptr = %p,\n", val_ptr);

  printf("\nTYPES example #1 :: end\n");

  return 0;
}
