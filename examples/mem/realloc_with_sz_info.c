/**
 * @file realloc_with_sz_info.c
 * @author Kumarjit Das
 * @date 2025-05-25
 * @brief Memory reallocation with size information example.
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


#define KD_USE_SIMPLIFIED_TYPES
#include "kd.h"

#include <stdio.h>


int
main(int argc, char** argv)
{
  i32 *buffer, *new_buffer;
  u32  size, new_size;
  bool result;

  (void)argc;
  (void)argv;

  printf("Memory reallocation with size information example :: begin\n\n");

  buffer   = null;
  size     = 32 * KD_SZ_I32;
  new_size = 64 * KD_SZ_I32;

  if (!kdMemAllocWithSizeInfo(&buffer, size))
  {
    printf("Initial allocation failed.\n");
    return KD_EXIT_FAILURE;
  }

  printf("Initial allocation succeeded.\n");
  printf("Allocated size: " KD_FMTSP_USIZE " bytes\n", kdMemGetAllocSize(buffer));

  new_buffer = null;
  result     = kdMemReallocWithSizeInfo(&new_buffer, new_size, &buffer, size);

  if (result && new_buffer && !buffer)
  {
    printf("Reallocation successful.\n");
    printf("Reallocated size: " KD_FMTSP_USIZE " bytes\n", kdMemGetAllocSize(new_buffer));
    /* Use the new_buffer... */
    kdMemFreeWithSizeInfo(&new_buffer);
  }
  else
  {
    printf("Reallocation failed.\n");
    kdMemFreeWithSizeInfo(&buffer);
  }

  if (!kdMemAllocWithSizeInfo(&buffer, size))
  {
    printf("Allocation for size 0 test failed.\n");
    return KD_EXIT_FAILURE;
  }

  printf("Allocation for size 0 test succeeded.\n");
  printf("Allocated size: " KD_FMTSP_USIZE " bytes\n", kdMemGetAllocSize(buffer));

  result = kdMemReallocWithSizeInfo(&new_buffer, 0, &buffer, size);

  if (result && !new_buffer && !buffer)
  {
    printf("Reallocation with size 0 successful.\n");
    printf("Reallocated size: " KD_FMTSP_USIZE " bytes\n", kdMemGetAllocSize(new_buffer));
    /* Use the new_buffer... */
    kdMemFreeWithSizeInfo(&new_buffer);
  }
  else
  {
    printf("Reallocation with size 0 failed.\n");
    kdMemFreeWithSizeInfo(&buffer);
  }

  buffer = null;
  result = kdMemReallocWithSizeInfo(&new_buffer, new_size, &buffer, 0);

  if (result && new_buffer)
  {
    printf("Reallocation with null buffer successful.\n");
    printf("Reallocated size: " KD_FMTSP_USIZE " bytes\n", kdMemGetAllocSize(new_buffer));
    /* Use the new_buffer... */
    kdMemFreeWithSizeInfo(&new_buffer);
  }
  else
  {
    printf("Reallocation with null buffer failed.\n");
    kdMemFreeWithSizeInfo(&buffer);
  }

  result = kdMemReallocWithSizeInfo(&new_buffer, new_size * 2, null, 0);

  if (result && new_buffer)
  {
    printf("Reallocation with null source successful.\n");
    printf("Reallocated size: " KD_FMTSP_USIZE " bytes\n", kdMemGetAllocSize(new_buffer));
    /* Use the new_buffer... */
    kdMemFreeWithSizeInfo(&new_buffer);
  }
  else
  {
    printf("Reallocation with null source failed.\n");
    kdMemFreeWithSizeInfo(&buffer);
  }

  printf("\nMemory reallocation with size information example :: end\n\n");

  return result ? KD_EXIT_SUCCESS : KD_EXIT_FAILURE;
}
