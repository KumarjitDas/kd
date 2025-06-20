/**
 * @file kdGenArrGet.cpp
 * @author Kumarjit Das
 * @date 2025-06-19
 * @brief kdGenArrGet test file.
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
#include "kd/mem.h"
#include "gtest/gtest.h"


TEST(GenArrGetTest, SetsElementCorrectly)
{
#if defined KD_ARCH_64BIT_INT
  kd_i64_t len = 16;
#else  /* !defined KD_ARCH_64BIT_INT */
  kd_i32_t len = 16;
#endif /* KD_ARCH_64BIT_INT */

  kd_i32_t init_val = 0, val = 69;
  kd_i32_t res[] = {0, 0, 0, 0, 69, 0, 0, 0, 0, 0, 69, 0, 0, 0, 0, 0};
  auto*    arr   = static_cast<kd_i32_t*>(kdGenArrCreateInit(KD_SZ_I32, len, &init_val, kdMemAlloc));
  ASSERT_NE(arr, kd_null);

  arr[4]  = val;
  arr[10] = val;
  EXPECT_EQ(kdGenArrGet(arr, 4), arr + 4);
  EXPECT_EQ(kdGenArrGet(arr, 10), arr + 10);

  for (kd_usize_t i = 0; i < KD_USIZE_C(len); ++i)
  {
    EXPECT_EQ(arr[i], res[i]);
  }

  EXPECT_EQ(kdGenArrDestroy(arr, kdMemFree), kd_true);
}

TEST(GenArrGetTest, HandlesInvalidArguments)
{
  auto* arr = reinterpret_cast<kd_i32_t*>(0x696969);

  EXPECT_EQ(kdGenArrGet(kd_null, -3), kd_null);
  EXPECT_EQ(kdGenArrGet(kd_null, 3), kd_null);
  EXPECT_EQ(kdGenArrGet(arr, -3), kd_null);
}
