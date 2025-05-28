/**
 * @file cstr_macros.c
 * @author Kumarjit Das
 * @date 2025-05-24
 * @brief System information C-string macros example.
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
#include "kd.h"


int
       main(argc, argv)
int    argc;
char** argv;
{
  (void)argc;
  (void)argv;

  printf("System information C-string macros example :: begin\n\n");

  printf("API Version: %s\n", KD_VERSION_CSTR);
  printf("Compiler: %s\n", KD_COMP_CSTR);
  printf("Target Operating System: %s\n", KD_OS_CSTR);
  printf("Target CPU: %s\n", KD_CPU_CSTR);
  printf("Target Architecture Integer Size: %s\n", KD_ARCH_INT_CSTR);
  printf("Target Architecture Pointer(Address) Size: %s\n", KD_ARCH_PTR_CSTR);
  printf("Endianness: %s\n", KD_ENDIAN_CSTR);

  printf("\nSystem information C-string macros example :: end\n\n");

  return KD_EXIT_SUCCESS;
}
