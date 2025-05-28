/**
 * @file example-007-mem.c
 * @author Kumarjit Das
 * @date 2025-05-25
 * @brief MEM library example source file #3.
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
#include "../../include/kd/mem.h"
#include "kd.h"
#include "types.h"


int main(int argc, char** argv)
{
  (void) argc;
  (void) argv;

  printf("MEM example #3 :: begin\n\n");

  i16* buffer1 = null;
  i32* buffer2 = null;
  chr* buffer3 = null;

  if (!kdMemAlloc(&buffer1, 32 * SZ_I16))
  {
    printf("Buffer 1 allocation failed.\n");
    return EXIT_FAILURE;
  }
  if (!kdMemAlloc(&buffer2, 16 * SZ_I32))
  {
    printf("Buffer 2 allocation failed.\n");
    return EXIT_FAILURE;
  }
  if (!kdMemAlloc(&buffer3, 16 * SZ_CHR))
  {
    printf("Buffer 3 allocation failed.\n");
    return EXIT_FAILURE;
  }

  printf("Buffer 1: " FMTSP_PTR "\n", FSBTC_PTR(buffer1));
  printf("Buffer 2: " FMTSP_PTR "\n", FSBTC_PTR(buffer2));
  printf("Buffer 3: " FMTSP_PTR "\n", FSBTC_PTR(buffer3));

  bool result = kdFree(&buffer1);
  result &= kdFree(&buffer2);
  result &= kdFree(&buffer3);

  if (!kdMemAlloc(&buffer1, 32 * SZ_I16))
  {
    printf("Buffer 1 allocation failed.\n");
    return EXIT_FAILURE;
  }

  if (!kdMemAlloc(&buffer2, 16 * SZ_I32))
  {
    printf("Buffer 2 allocation failed.\n");
    return EXIT_FAILURE;
  }
  result &= kdFree(&buffer2);

  if (!kdMemAlloc(&buffer3, 16 * SZ_CHR))
  {
    printf("Buffer 3 allocation failed.\n");
    return EXIT_FAILURE;
  }

  if (!kdMemAlloc(&buffer2, 16 * SZ_I32))
  {
    printf("Buffer 2 allocation failed.\n");
    return EXIT_FAILURE;
  }

  printf("Buffer 1: " FMTSP_PTR "\n", FSBTC_PTR(buffer1));
  printf("Buffer 2: " FMTSP_PTR "\n", FSBTC_PTR(buffer2));
  printf("Buffer 3: " FMTSP_PTR "\n", FSBTC_PTR(buffer3));

  result &= kdFree(&buffer1);
  result &= kdFree(&buffer2);
  result &= kdFree(&buffer3);

  printf("\nMEM example #3 :: end\n\n");

  return result ? EXIT_SUCCESS : EXIT_FAILURE;
}
