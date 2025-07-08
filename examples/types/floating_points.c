/**
 * @file floating_points.c
 * @author Kumarjit Das
 * @date 2025-05-24
 * @brief Floating point types example.
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


#include "kd/defs.h"

#define KD_USE_SIMPLIFIED_TYPES
#include "../../include/kd/floating_point.h"

#include <stdio.h>


int
main(int argc, char** argv)
{
  f32 val_f32;
  f64 val_f64;

  (void)argc;
  (void)argv;

  printf("Floating point types example :: begin\n");

  printf("\nAPI Version: %s\n", KD_VERSION_CSTR);

  printf("\nSizes of types:\n\n");

  printf("KD_SZ_F32 = %d,\n", (int)KD_SZ_F32);
  printf("KD_SZ_F64 = %d,\n", (int)KD_SZ_F64);

  printf("\nMinimum values of types:\n\n");

  printf("KD_MIN_F32 = " KD_FMTSP_F32 ",\n", KD_FSBTC_F32(KD_MIN_F32));
  printf("KD_MIN_F64 = " KD_FMTSP_F64 ",\n", KD_FSBTC_F64(KD_MIN_F64));
  printf("KD_MIN_FMIN = " KD_FMTSP_FMIN ",\n", KD_FSBTC_FMIN(KD_MIN_FMIN));
  printf("KD_MIN_FMAX = " KD_FMTSP_FMAX ",\n", KD_FSBTC_FMAX(KD_MIN_FMAX));

  printf("\nMaximum values of types:\n\n");

  printf("KD_MAX_F32 = " KD_FMTSP_F32 ",\n", KD_FSBTC_F32(KD_MAX_F32));
  printf("KD_MAX_F64 = " KD_FMTSP_F64 ",\n", KD_FSBTC_F64(KD_MAX_F64));
  printf("KD_MAX_FMIN = " KD_FMTSP_FMIN ",\n", KD_FSBTC_FMIN(KD_MAX_FMIN));
  printf("KD_MAX_FMAX = " KD_FMTSP_FMAX ",\n", KD_FSBTC_FMAX(KD_MAX_FMAX));

  printf("\nValues of constant values:\n\n");
  printf("...\n");

  printf("\nValues of types:\n\n");

  val_f32 = KD_MAX_F32;
  val_f64 = KD_MAX_F64;

  printf("val_f32 = " KD_FMTSP_F32 ",\n", KD_FSBTC_F32(val_f32));
  printf("val_f64 = " KD_FMTSP_F64 ",\n", KD_FSBTC_F64(val_f64));

  printf("\nFloating point types example :: end\n");

  return KD_EXIT_SUCCESS;
}
