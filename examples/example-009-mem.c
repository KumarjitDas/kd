/**
 * @file example-009-mem.c
 * @author Kumarjit Das
 * @date 2025-05-25
 * @brief MEM library example source file #5.
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

  printf("MEM example #5 :: begin\n\n");

  i32* buffer   = null;
  u32  size     = 32 * SZ_I32;
  u32  new_size = 64 * SZ_I32;

  if (!kdAllocWithSizeInfo(&buffer, size))
  {
    printf("Initial allocation failed.\n");
    return EXIT_FAILURE;
  }

  printf("Initial allocation succeeded.\n");
  printf(
    "Allocated size: "
    #if defined TYPES_64BIT_INTEGER
    FMTSP_U64
    #else
    FMTSP_U32
    #endif  /* TYPES_64BIT_INTEGER */
    " bytes\n",
    kdGetAllocSize(buffer)
  );

  i32* new_buffer = null;
  bool result     = kdReallocWithSizeInfo(&new_buffer, new_size, &buffer, size);

  if (result && new_buffer && !buffer)
  {
    printf("Reallocation successful.\n");
    printf(
      "Reallocated size: "
      #if defined TYPES_64BIT_INTEGER
      FMTSP_U64
      #else
      FMTSP_U32
      #endif  /* TYPES_64BIT_INTEGER */
      " bytes\n",
      kdGetAllocSize(new_buffer)
    );
    // Use the new_buffer...
    kdFreeWithSizeInfo(&new_buffer);
  }
  else
  {
    printf("Reallocation failed.\n");
    kdFreeWithSizeInfo(&buffer);
  }

  if (!kdAllocWithSizeInfo(&buffer, size))
  {
    printf("Allocation for size 0 test failed.\n");
    return EXIT_FAILURE;
  }

  printf("Allocation for size 0 test succeeded.\n");
  printf(
    "Allocated size: "
    #if defined TYPES_64BIT_INTEGER
    FMTSP_U64
    #else
    FMTSP_U32
    #endif  /* TYPES_64BIT_INTEGER */
    " bytes\n",
    kdGetAllocSize(buffer)
  );

  result = kdReallocWithSizeInfo(&new_buffer, 0, &buffer, size);

  if (result && !new_buffer && !buffer)
  {
    printf("Reallocation with size 0 successful.\n");
    printf(
      "Reallocated size: "
      #if defined TYPES_64BIT_INTEGER
      FMTSP_U64
      #else
      FMTSP_U32
      #endif  /* TYPES_64BIT_INTEGER */
      " bytes\n",
      kdGetAllocSize(new_buffer)
    );
    // Use the new_buffer...
    kdFreeWithSizeInfo(&new_buffer);
  }
  else
  {
    printf("Reallocation with size 0 failed.\n");
    kdFreeWithSizeInfo(&buffer);
  }

  buffer = null;
  result = kdReallocWithSizeInfo(&new_buffer, new_size, &buffer, 0);

  if (result && new_buffer)
  {
    printf("Reallocation with null buffer successful.\n");
    printf(
      "Reallocated size: "
      #if defined TYPES_64BIT_INTEGER
      FMTSP_U64
      #else
      FMTSP_U32
      #endif  /* TYPES_64BIT_INTEGER */
      " bytes\n",
      kdGetAllocSize(new_buffer)
    );
    // Use the new_buffer...
    kdFreeWithSizeInfo(&new_buffer);
  }
  else
  {
    printf("Reallocation with null buffer failed.\n");
    kdFreeWithSizeInfo(&buffer);
  }

  result = kdReallocWithSizeInfo(&new_buffer, new_size, null, 0);

  if (result && new_buffer)
  {
    printf("Reallocation with null source successful.\n");
    printf(
      "Reallocated size: "
      #if defined TYPES_64BIT_INTEGER
      FMTSP_U64
      #else
      FMTSP_U32
      #endif  /* TYPES_64BIT_INTEGER */
      " bytes\n",
      kdGetAllocSize(new_buffer)
    );
    // Use the new_buffer...
    kdFreeWithSizeInfo(&new_buffer);
  }
  else
  {
    printf("Reallocation with null source failed.\n");
    kdFreeWithSizeInfo(&buffer);
  }

  printf("\nMEM example #5 :: end\n\n");

  return result;
}
