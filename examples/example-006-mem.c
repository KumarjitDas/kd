/**
 * @file example-006-mem.c
 * @author Kumarjit Das
 * @date 2025-05-25
 * @brief MEM library example source file #2.
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
#include "types.h"
#include "mem.h"


int main(int argc, char** argv)
{
  (void) argc;
  (void) argv;

  printf("MEM example #2 :: begin\n\n");

  i32* buffer   = null;
  u32  size     = 32 * SZ_I32;
  u32  new_size = 64 * SZ_I32;

  if (!kdAlloc(&buffer, size))
  {
    printf("Initial allocation failed.\n");
    return EXIT_FAILURE;
  }

  printf("Initial allocation succeeded.\n");

  i32* new_buffer = null;
  bool result     = kdRealloc(&new_buffer, new_size, &buffer, size);

  if (result && new_buffer && !buffer)
  {
    printf("Reallocation successful.\n");
    // Use the new_buffer...
    kdFree(&new_buffer);
  }
  else
  {
    printf("Reallocation failed.\n");
    kdFree(&buffer);
  }

  if (!kdAlloc(&buffer, size))
  {
    printf("Allocation for size 0 test failed.\n");
    return EXIT_FAILURE;
  }

  printf("Allocation for size 0 test succeeded.\n");

  result = kdRealloc(&new_buffer, 0, &buffer, size);

  if (result && !new_buffer && !buffer)
  {
    printf("Reallocation with size 0 successful.\n");
    // Use the new_buffer...
    kdFree(&new_buffer);
  }
  else
  {
    printf("Reallocation with size 0 failed.\n");
    kdFree(&buffer);
  }

  buffer = null;
  result = kdRealloc(&new_buffer, new_size, &buffer, 0);

  if (result && new_buffer)
  {
    printf("Reallocation with null buffer successful.\n");
    // Use the new_buffer...
    kdFree(&new_buffer);
  }
  else
  {
    printf("Reallocation with null buffer failed.\n");
    kdFree(&buffer);
  }

  result = kdRealloc(&new_buffer, new_size, null, 0);

  if (result && new_buffer)
  {
    printf("Reallocation with null source successful.\n");
    // Use the new_buffer...
    kdFree(&new_buffer);
  }
  else
  {
    printf("Reallocation with null source failed.\n");
    kdFree(&buffer);
  }

  printf("\nMEM example #2 :: end\n\n");

  return result;
}
