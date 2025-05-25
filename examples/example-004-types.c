/**
 * @file example-004-types.c
 * @author Kumarjit Das
 * @date 2025-05-24
 * @brief TYPES library example source file #2.
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

  printf("TYPES example #2 :: begin\n");

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

  printf("MIN_I8 = " FMTSP_I8 ",\n", FSBTC_I8(MIN_I8));
  printf("MIN_I16 = " FMTSP_I16 ",\n", FSBTC_I16(MIN_I16));
  printf("MIN_I32 = " FMTSP_I32 ",\n", FSBTC_I32(MIN_I32));
  printf("MIN_IMIN = " FMTSP_IMIN ",\n", FSBTC_IMIN(MIN_IMIN));
  printf("MIN_U8 = " FMTSP_U8 ",\n", FSBTC_U8(MIN_U8));
  printf("MIN_U16 = " FMTSP_U16 ",\n", FSBTC_U16(MIN_U16));
  printf("MIN_U32 = " FMTSP_U32 ",\n", FSBTC_U32(MIN_U32));
  printf("MIN_UMIN = " FMTSP_UMIN ",\n", FSBTC_UMIN(MIN_UMIN));
  printf("MIN_BYTE = " FMTSP_BYTE ",\n", FSBTC_BYTE(MIN_BYTE));
  printf("MIN_F32 = " FMTSP_F32 ",\n", FSBTC_F32(MIN_F32));
  printf("MIN_F64 = " FMTSP_F64 ",\n", FSBTC_F64(MIN_F64));
  printf("MIN_FMIN = " FMTSP_FMIN ",\n", FSBTC_FMIN(MIN_FMIN));
  printf("MIN_FMAX = " FMTSP_FMAX ",\n", FSBTC_FMAX(MIN_FMAX));
  printf("MIN_IMAX = " FMTSP_IMAX ",\n", FSBTC_IMAX(MIN_IMAX));
  printf("MIN_UMAX = " FMTSP_UMAX ",\n", FSBTC_UMAX(MIN_UMAX));
  printf("MIN_CHR = " FMTSP_CHR ",\n", FSBTC_CHR(MIN_CHR));
  printf("MIN_USIZE = " FMTSP_USIZE ",\n", FSBTC_USIZE(MIN_USIZE));
  printf("MIN_PTR = " FMTSP_PTR ",\n", FSBTC_PTR(MIN_PTR));

  #if defined TYPES_64BIT_INTEGER
  printf("MIN_I64 = " FMTSP_I64 ",\n", FSBTC_I64(MIN_I64));
  printf("MIN_U64 = " FMTSP_U64 ",\n", FSBTC_U64(MIN_U64));
  #endif  /* TYPES_64BIT_INTEGER */

  printf("\nMaximum values of types:\n\n");

  printf("MAX_I8 = " FMTSP_I8 ",\n", FSBTC_I8(MAX_I8));
  printf("MAX_I16 = " FMTSP_I16 ",\n", FSBTC_I16(MAX_I16));
  printf("MAX_I32 = " FMTSP_I32 ",\n", FSBTC_I32(MAX_I32));
  printf("MAX_IMIN = " FMTSP_IMIN ",\n", FSBTC_IMIN(MAX_IMIN));
  printf("MAX_U8 = " FMTSP_U8 ",\n", FSBTC_U8(MAX_U8));
  printf("MAX_U16 = " FMTSP_U16 ",\n", FSBTC_U16(MAX_U16));
  printf("MAX_U32 = " FMTSP_U32 ",\n", FSBTC_U32(MAX_U32));
  printf("MAX_UMIN = " FMTSP_UMIN ",\n", FSBTC_UMIN(MAX_UMIN));
  printf("MAX_BYTE = " FMTSP_BYTE ",\n", FSBTC_BYTE(MAX_BYTE));
  printf("MAX_F32 = " FMTSP_F32 ",\n", FSBTC_F32(MAX_F32));
  printf("MAX_F64 = " FMTSP_F64 ",\n", FSBTC_F64(MAX_F64));
  printf("MAX_FMIN = " FMTSP_FMIN ",\n", FSBTC_FMIN(MAX_FMIN));
  printf("MAX_FMAX = " FMTSP_FMAX ",\n", FSBTC_FMAX(MAX_FMAX));
  printf("MAX_IMAX = " FMTSP_IMAX ",\n", FSBTC_IMAX(MAX_IMAX));
  printf("MAX_UMAX = " FMTSP_UMAX ",\n", FSBTC_UMAX(MAX_UMAX));
  printf("MAX_CHR = " FMTSP_CHR ",\n", FSBTC_CHR(MAX_CHR));
  printf("MAX_USIZE = " FMTSP_USIZE ",\n", FSBTC_USIZE(MAX_USIZE));
  printf("MAX_PTR = " FMTSP_PTR ",\n", FSBTC_PTR(MAX_PTR));

  #if defined TYPES_64BIT_INTEGER
  printf("MAX_I64 = " FMTSP_I64 ",\n", FSBTC_I64(MAX_I64));
  printf("MAX_U64 = " FMTSP_U64 ",\n", FSBTC_U64(MAX_U64));
  #endif  /* TYPES_64BIT_INTEGER */

  printf("\nValues of constant values:\n\n");

  printf("true = " FMTSP_BOOL ",\n", FSBTC_BOOL(true));
  printf("false = " FMTSP_BOOL ",\n", FSBTC_BOOL(false));
  printf("null = %p,\n", null);

  printf("\nValues of types:\n\n");

  val_bool  = true;
  val_i8    = MAX_I8;
  val_i16   = MAX_I16;
  val_i32   = MAX_I32;
  val_imin  = MAX_IMIN;
  val_imax  = MAX_IMAX;
  val_u8    = MAX_U8;
  val_u16   = MAX_U16;
  val_u32   = MAX_U32;
  val_umin  = MAX_UMIN;
  val_umax  = MAX_UMAX;
  val_usize = MAX_USIZE;
  val_byte  = MAX_BYTE;
  val_chr   = MAX_CHR;
  val_f32   = MAX_F32;
  val_f64   = MAX_F64;
  val_ptr   = MAX_PTR;

  #if defined TYPES_64BIT_INTEGER
  val_i64 = MAX_I64;
  val_u64 = MAX_U64;
  #endif  /* TYPES_64BIT_INTEGER */

  SET_ANY(val_any, MAX_BYTE, MAX_BYTE, MAX_BYTE, MAX_BYTE, MAX_BYTE, MAX_BYTE, MAX_BYTE, MAX_BYTE);

  printf("val_bool = " FMTSP_BOOL ",\n", FSBTC_BOOL(val_bool));
  printf("val_i8 = " FMTSP_I8 ",\n", FSBTC_I8(val_i8));
  printf("val_i16 = " FMTSP_I16 ",\n", FSBTC_I16(val_i16));
  printf("val_i32 = " FMTSP_I32 ",\n", FSBTC_I32(val_i32));
  printf("val_imin = " FMTSP_IMIN ",\n", FSBTC_IMIN(val_imin));
  printf("val_imax = " FMTSP_IMAX ",\n", FSBTC_IMAX(val_imax));
  printf("val_u8 = " FMTSP_U8 ",\n", FSBTC_U8(val_u8));
  printf("val_u16 = " FMTSP_U16 ",\n", FSBTC_U16(val_u16));
  printf("val_u32 = " FMTSP_U32 ",\n", FSBTC_U32(val_u32));
  printf("val_umin = " FMTSP_UMIN ",\n", FSBTC_UMIN(val_umin));
  printf("val_umax = " FMTSP_UMAX ",\n", FSBTC_UMAX(val_umax));
  printf("val_usize = " FMTSP_USIZE ",\n", FSBTC_USIZE(val_usize));
  printf("val_byte = " FMTSP_BYTE ",\n", FSBTC_BYTE(val_byte));
  printf("val_chr = " FMTSP_CHR ",\n", FSBTC_CHR(val_chr));
  printf("val_f32 = " FMTSP_F32 ",\n", FSBTC_F32(val_f32));
  printf("val_f64 = " FMTSP_F64 ",\n", FSBTC_F64(val_f64));
  printf("val_ptr = " FMTSP_PTR ",\n", FSBTC_PTR(val_ptr));

  #if defined TYPES_64BIT_INTEGER
  printf("val_i64 = " FMTSP_I64 ",\n", FSBTC_I64(val_i64));
  printf("val_u64 = " FMTSP_U64 ",\n", FSBTC_U64(val_u64));
  #endif  /* TYPES_64BIT_INTEGER */

  printf("val_any: {\n");

  printf("\tval = " FMTSP_UMAX ",\n", FSBTC_UMAX(val_any.val));
  printf("\tval_bool = " FMTSP_BOOL ",\n", FSBTC_BOOL(val_any.val_bool));
  printf("\tval_i8 = " FMTSP_I8 ",\n", FSBTC_I8(val_any.val_i8));
  printf("\tval_i16 = " FMTSP_I16 ",\n", FSBTC_I16(val_any.val_i16));
  printf("\tval_i32 = " FMTSP_I32 ",\n", FSBTC_I32(val_any.val_i32));
  printf("\tval_imin = " FMTSP_IMIN ",\n", FSBTC_IMIN(val_any.val_imin));
  printf("\tval_imax = " FMTSP_IMAX ",\n", FSBTC_IMAX(val_any.val_imax));
  printf("\tval_u8 = " FMTSP_U8 ",\n", FSBTC_U8(val_any.val_u8));
  printf("\tval_u16 = " FMTSP_U16 ",\n", FSBTC_U16(val_any.val_u16));
  printf("\tval_u32 = " FMTSP_U32 ",\n", FSBTC_U32(val_any.val_u32));
  printf("\tval_umin = " FMTSP_UMIN ",\n", FSBTC_UMIN(val_any.val_umin));
  printf("\tval_umax = " FMTSP_UMAX ",\n", FSBTC_UMAX(val_any.val_umax));
  printf("\tval_usize = " FMTSP_USIZE ",\n", FSBTC_USIZE(val_any.val_usize));
  printf("\tval_byte = " FMTSP_BYTE ",\n", FSBTC_BYTE(val_any.val_byte));
  printf("\tval_chr = " FMTSP_CHR ",\n", FSBTC_CHR(val_any.val_chr));
  printf("\tval_f32 = " FMTSP_F32 ",\n", FSBTC_F32(val_any.val_f32));
  printf("\tval_f64 = " FMTSP_F64 ",\n", FSBTC_F64(val_any.val_f64));
  printf("\tptr = " FMTSP_PTR ",\n", FSBTC_PTR(val_any.ptr));
  printf("\tptr_bool = " FMTSP_PTR ",\n", FSBTC_PTR(val_any.ptr_bool));
  printf("\tptr_i8 = " FMTSP_PTR ",\n", FSBTC_PTR(val_any.ptr_i8));
  printf("\tptr_i16 = " FMTSP_PTR ",\n", FSBTC_PTR(val_any.ptr_i16));
  printf("\tptr_i32 = " FMTSP_PTR ",\n", FSBTC_PTR(val_any.ptr_i32));
  printf("\tptr_imin = " FMTSP_PTR ",\n", FSBTC_PTR(val_any.ptr_imin));
  printf("\tptr_imax = " FMTSP_PTR ",\n", FSBTC_PTR(val_any.ptr_imax));
  printf("\tptr_u8 = " FMTSP_PTR ",\n", FSBTC_PTR(val_any.ptr_u8));
  printf("\tptr_u16 = " FMTSP_PTR ",\n", FSBTC_PTR(val_any.ptr_u16));
  printf("\tptr_u32 = " FMTSP_PTR ",\n", FSBTC_PTR(val_any.ptr_u32));
  printf("\tptr_umin = " FMTSP_PTR ",\n", FSBTC_PTR(val_any.ptr_umin));
  printf("\tptr_umax = " FMTSP_PTR ",\n", FSBTC_PTR(val_any.ptr_umax));
  printf("\tptr_usize = " FMTSP_PTR ",\n", FSBTC_PTR(val_any.ptr_usize));
  printf("\tptr_byte = " FMTSP_PTR ",\n", FSBTC_PTR(val_any.ptr_byte));
  printf("\tptr_chr = " FMTSP_PTR ",\n", FSBTC_PTR(val_any.ptr_chr));
  printf("\tptr_f32 = " FMTSP_PTR ",\n", FSBTC_PTR(val_any.ptr_f32));
  printf("\tptr_f64 = " FMTSP_PTR ",\n", FSBTC_PTR(val_any.ptr_f64));
  printf("\tslice = " FMTSP_ANY_SLICES ",\n", FSBTC_ANY_SLICES(val_any));

  #if defined TYPES_64BIT_INTEGER
  printf("\tval_i64 = " FMTSP_I64 ",\n", FSBTC_I64(val_any.val_i64));
  printf("\tval_u64 = " FMTSP_U64 ",\n", FSBTC_U64(val_any.val_u64));
  printf("\tptr_i64 = " FMTSP_PTR ",\n", FSBTC_PTR(val_any.ptr_i64));
  printf("\tptr_u64 = " FMTSP_PTR ",\n", FSBTC_PTR(val_any.ptr_u64));
  #endif  /* TYPES_64BIT_INTEGER */

  printf("}\n");

  printf("\nTYPES example #2 :: end\n");

  return EXIT_SUCCESS;
}
