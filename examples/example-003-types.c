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
  fmin  val_fmin;
  fmax  val_fmax;
  any   val_any;
  void* val_ptr;

  (void) argc;
  (void) argv;

  (void) printf("TYPES example #1 :: begin\n");

  (void) printf("\nAPI Version: %s\n", KD_VERSION_STR);

  (void) printf("\nSizes of types:\n\n");

  (void) printf("SZ_BOOL = %d,\n", (int) SZ_BOOL);
  (void) printf("SZ_I8 = %d,\n", (int) SZ_I8);
  (void) printf("SZ_I16 = %d,\n", (int) SZ_I16);
  (void) printf("SZ_I32 = %d,\n", (int) SZ_I32);
  (void) printf("SZ_IMIN = %d,\n", (int) SZ_IMIN);
  (void) printf("SZ_IMAX = %d,\n", (int) SZ_IMAX);
  (void) printf("SZ_U8 = %d,\n", (int) SZ_U8);
  (void) printf("SZ_U16 = %d,\n", (int) SZ_U16);
  (void) printf("SZ_U32 = %d,\n", (int) SZ_U32);
  (void) printf("SZ_UMIN = %d,\n", (int) SZ_UMIN);
  (void) printf("SZ_UMAX = %d,\n", (int) SZ_UMAX);

  #if defined TYPES_64BIT_INTEGER
  (void) printf("SZ_I64 = %d,\n", (int) SZ_I64);
  (void) printf("SZ_U64 = %d,\n", (int) SZ_U64);
  #endif  /* TYPES_64BIT_INTEGER */

  (void) printf("SZ_USIZE = %d,\n", (int) SZ_USIZE);
  (void) printf("SZ_BYTE = %d,\n", (int) SZ_BYTE);
  (void) printf("SZ_CHR = %d,\n", (int) SZ_CHR);
  (void) printf("SZ_F32 = %d,\n", (int) SZ_F32);
  (void) printf("SZ_F64 = %d,\n", (int) SZ_F64);
  (void) printf("SZ_FMIN = %d,\n", (int) SZ_FMIN);
  (void) printf("SZ_FMAX = %d,\n", (int) SZ_FMAX);
  (void) printf("SZ_ANY = %d,\n", (int) SZ_ANY);
  (void) printf("SZ_PTR = %d,\n", (int) SZ_PTR);

  (void) printf("\nMinimum values of types:\n\n");

  (void) printf("MIN_I8 = %d,\n", (int) MIN_I8);
  (void) printf("MIN_I16 = %d,\n", (int) MIN_I16);
  (void) printf("MIN_I32 = %ld,\n", (long) MIN_I32);
  (void) printf("MIN_IMIN = %d,\n", (int) MIN_IMIN);

  #ifdef KD_COMP_MSVC
  (void) printf("MIN_IMAX = %lld,\n", (long long) MIN_IMAX);
  #else
  (void) printf("MIN_IMAX = %ld,\n", (long) MIN_IMAX);
  #endif  /* KD_COMP_MSVC */

  (void) printf("MIN_U8 = %u,\n", (unsigned int) MIN_U8);
  (void) printf("MIN_U16 = %u,\n", (unsigned int) MIN_U16);
  (void) printf("MIN_U32 = %lu,\n", (unsigned long) MIN_U32);
  (void) printf("MIN_UMIN = %u,\n", (unsigned int) MIN_UMIN);
  (void) printf("MIN_UMAX = %lu,\n", (unsigned long) MIN_UMAX);

  #if defined TYPES_64BIT_INTEGER
  #ifdef KD_COMP_MSVC
  (void) printf("MIN_I64 = %lld,\n", (long long) MIN_I64);
  #else
  (void) printf("MIN_I64 = %ld,\n", (long) MIN_I64);
  #endif  /* KD_COMP_MSVC */

  #ifdef KD_COMP_MSVC
  (void) printf("MIN_U64 = %llu,\n", (unsigned long long) MIN_U64);
  #else
  (void) printf("MIN_U64 = %lu,\n", (unsigned long) MIN_U64);
  #endif  /* KD_COMP_MSVC */
  #endif  /* TYPES_64BIT_INTEGER */

  (void) printf("MIN_USIZE = %lu,\n", (unsigned long) MIN_USIZE);
  (void) printf("MIN_BYTE = %d,\n", (int) MIN_BYTE);
  (void) printf("MIN_CHR = %lu,\n", (unsigned long) MIN_CHR);
  (void) printf("MIN_F32 = %.9e,\n", (double) MIN_F32);
  (void) printf("MIN_F64 = %.17e,\n", MIN_F64);
  (void) printf("MIN_FMIN = %.9e,\n", (double) MIN_FMIN);
  (void) printf("MIN_FMAX = %.17e,\n", MIN_FMAX);
  (void) printf("MIN_PTR = %p,\n", MIN_PTR);

  (void) printf("\nMaximum values of types:\n\n");

  (void) printf("MAX_I8 = %d,\n", (int) MAX_I8);
  (void) printf("MAX_I16 = %d,\n", (int) MAX_I16);
  (void) printf("MAX_I32 = %ld,\n", (long) MAX_I32);
  (void) printf("MAX_IMIN = %d,\n", (int) MAX_IMIN);

  #ifdef KD_COMP_MSVC
  (void) printf("MAX_IMAX = %lld,\n", (long long) MAX_IMAX);
  #else
  (void) printf("MAX_IMAX = %ld,\n", (long) MAX_IMAX);
  #endif  /* KD_COMP_MSVC */

  (void) printf("MAX_U8 = %u,\n", (unsigned int) MAX_U8);
  (void) printf("MAX_U16 = %u,\n", (unsigned int) MAX_U16);
  (void) printf("MAX_U32 = %lu,\n", (unsigned long) MAX_U32);
  (void) printf("MAX_UMIN = %u,\n", (unsigned int) MAX_UMIN);

  #ifdef KD_COMP_MSVC
  (void) printf("MAX_UMAX = %llu,\n", (unsigned long long) MAX_UMAX);
  #else
  (void) printf("MAX_UMAX = %lu,\n", (unsigned long) MAX_UMAX);
  #endif  /* KD_COMP_MSVC */

  #if defined TYPES_64BIT_INTEGER
  #ifdef KD_COMP_MSVC
  (void) printf("MAX_I64 = %lld,\n", (long long) MAX_I64);
  #else
  (void) printf("MAX_I64 = %ld,\n", (long) MAX_I64);
  #endif  /* KD_COMP_MSVC */

  #ifdef KD_COMP_MSVC
  (void) printf("MAX_U64 = %llu,\n", (unsigned long long) MAX_U64);
  #else
  (void) printf("MAX_U64 = %lu,\n", (unsigned long) MAX_U64);
  #endif  /* KD_COMP_MSVC */
  #endif  /* TYPES_64BIT_INTEGER */

  #ifdef KD_COMP_MSVC
  (void) printf("MAX_USIZE = %llu,\n", (unsigned long long) MAX_USIZE);
  #else
  (void) printf("MAX_USIZE = %lu,\n", (unsigned long) MAX_USIZE);
  #endif  /* KD_COMP_MSVC */

  (void) printf("MAX_BYTE = %d,\n", (int) MAX_BYTE);
  (void) printf("MAX_CHR = %lu,\n", (unsigned long) MAX_CHR);
  (void) printf("MAX_F32 = %.9e,\n", (double) MAX_F32);
  (void) printf("MAX_F64 = %.17e,\n", MAX_F64);
  (void) printf("MAX_FMIN = %.9e,\n", (double) MAX_FMIN);
  (void) printf("MAX_FMAX = %.17e,\n", MAX_FMAX);

  (void) printf("MAX_PTR = %p,\n", MAX_PTR);

  (void) printf("\nValues of constant values:\n\n");

  (void) printf("true = %d,\n", true);
  (void) printf("false = %d,\n", false);
  (void) printf("null = %p,\n", null);

  (void) printf("\nValues of types:\n\n");

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
  val_fmin         = MAX_FMIN;
  val_fmax         = MAX_FMAX;
  val_any.val_umax = MAX_UMAX;
  val_ptr          = MAX_PTR;

  (void) printf("val_bool = %s,\n", val_bool ? "true" : "false");
  (void) printf("val_i8 = %d,\n", (i32) val_i8);
  (void) printf("val_i16 = %hd,\n", val_i16);
  (void) printf("val_i32 = %d,\n", val_i32);
  (void) printf("val_imin = %d,\n", (i32) val_imin);

  (void) printf(
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

  (void) printf("val_u8 = %u,\n", (u32) val_u8);
  (void) printf("val_u16 = %hu,\n", val_u16);
  (void) printf("val_u32 = %u,\n", val_u32);

  #if defined TYPES_64BIT_INTEGER
  #ifdef KD_COMP_MSVC
  (void) printf("val_i64 = %lld,\n", val_i64);
  (void) printf("val_u64 = %llu,\n", val_u64);
  #else
  (void) printf("val_i64 = %ld,\n", val_i64);
  (void) printf("val_u64 = %lu,\n", val_u64);
  #endif  /* KD_COMP_MSVC */
  #endif  /* TYPES_64BIT_INTEGER */

  (void) printf("val_umin = %u,\n", (u32) val_umin);

  (void) printf(
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

  (void) printf(
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

  (void) printf("val_byte = %u,\n", (u32) val_byte);
  (void) printf("val_chr = %u,\n", val_chr);
  (void) printf("val_f32 = %f,\n", (double) val_f32);
  (void) printf("val_f64 = %f,\n", val_f64);
  (void) printf("val_fmin = %f,\n", (double) val_fmin);
  (void) printf("val_fmax = %f,\n", val_fmax);

  (void) printf("val_any: {\n");
  (void) printf(
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
  (void) printf("\tptr = %p\n", val_any.ptr);

  (void) printf(
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

  (void) printf("\tval_bool = %s\n", val_any.val_bool ? "true" : "false");
  (void) printf("\tval_i8 = %d\n", (i32) val_any.val_i8);
  (void) printf("\tval_i16 = %hd\n", val_any.val_i16);
  (void) printf("\tval_i32 = %d\n", val_any.val_i32);
  (void) printf("\tval_imin = %d\n", (i32) val_any.val_imin);

  (void) printf(
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

  (void) printf("\tval_u8 = %u\n", (u32) val_any.val_u8);
  (void) printf("\tval_u16 = %hu\n", val_any.val_u16);
  (void) printf("\tval_u32 = %u\n", val_any.val_u32);
  (void) printf("\tval_umin = %u\n", (u32) val_any.val_umin);

  (void) printf(
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

  (void) printf(
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

  (void) printf("\tval_byte = %u\n", (u32) val_any.val_byte);
  (void) printf("\tval_chr = %u\n", val_any.val_chr);
  (void) printf("\tval_f32 = %f\n", (double) val_any.val_f32);
  (void) printf("\tval_f64 = %f\n", val_any.val_f64);
  (void) printf("\tval_fmin = %f\n", (double) val_any.val_fmin);
  (void) printf("\tval_fmax = %f\n", val_any.val_fmax);
  (void) printf("\tptr_bool = %p\n", (void*) val_any.ptr_bool);
  (void) printf("\tptr_i8 = %p\n", (void*) val_any.ptr_i8);
  (void) printf("\tptr_i16 = %p\n", (void*) val_any.ptr_i16);
  (void) printf("\tptr_i32 = %p\n", (void*) val_any.ptr_i32);
  (void) printf("\tptr_imin = %p\n", (void*) val_any.ptr_imin);
  (void) printf("\tptr_imax = %p\n", (void*) val_any.ptr_imax);
  (void) printf("\tptr_u8 = %p\n", (void*) val_any.ptr_u8);
  (void) printf("\tptr_u16 = %p\n", (void*) val_any.ptr_u16);
  (void) printf("\tptr_u32 = %p\n", (void*) val_any.ptr_u32);
  (void) printf("\tptr_umin = %p\n", (void*) val_any.ptr_umin);
  (void) printf("\tptr_umax = %p\n", (void*) val_any.ptr_umax);
  (void) printf("\tptr_usize = %p\n", (void*) val_any.ptr_usize);
  (void) printf("\tptr_byte = %p\n", (void*) val_any.ptr_byte);
  (void) printf("\tptr_chr = %p\n", (void*) val_any.ptr_chr);
  (void) printf("\tptr_f32 = %p\n", (void*) val_any.ptr_f32);
  (void) printf("\tptr_f64 = %p\n", (void*) val_any.ptr_f64);
  (void) printf("\tptr_fmin = %p\n", (void*) val_any.ptr_fmin);
  (void) printf("\tptr_fmax = %p\n", (void*) val_any.ptr_fmax);

  #ifdef TYPES_64BIT_INTEGER
  #ifdef KD_COMP_MSVC
  (void) printf("\tval_i64 = %lld\n", val_any.val_i64);
  (void) printf("\tval_u64 = %llu\n", val_any.val_u64);
  #else
  (void) printf("\tval_i64 = %ld\n", val_any.val_i64);
  (void) printf("\tval_u64 = %lu\n", val_any.val_u64);
  #endif  /* KD_COMP_MSVC */

  (void) printf("\tptr_i64 = %p\n", (void*) val_any.ptr_i64);
  (void) printf("\tptr_u64 = %p\n", (void*) val_any.ptr_u64);
  #endif  /* TYPES_64BIT_INTEGER */

  (void) printf("}\n");

  (void) printf("val_ptr = %p,\n", val_ptr);

  (void) printf("\nTYPES example #1 :: end\n");

  return 0;
}
