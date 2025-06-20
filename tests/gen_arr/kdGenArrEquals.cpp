/**
 * @file kdGenArrEquals.cpp
 * @author Kumarjit Das
 * @date 2025-06-19
 * @brief kdGenArrEquals test file.
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


TEST(GenArrEqualsTest, SetsElementCorrectly)
{
#if defined KD_ARCH_64BIT_INT
  kd_i64_t len = 16;
#else  /* !defined KD_ARCH_64BIT_INT */
  kd_i32_t len = 16;
#endif /* KD_ARCH_64BIT_INT */

  kd_i32_t init_val = 69;

  auto* arr1 = static_cast<kd_i32_t*>(kdGenArrCreateInit(KD_SZ_I32, len, &init_val, kdMemAlloc));
  ASSERT_NE(arr1, kd_null);

  auto* arr2 = static_cast<kd_i32_t*>(kdGenArrCreateInit(KD_SZ_I32, len, &init_val, kdMemAlloc));
  ASSERT_NE(arr2, kd_null);

  EXPECT_EQ(kdGenArrEquals(arr1, arr2), kd_true);

  for (kd_usize_t i = 0; i < KD_USIZE_C(len); ++i)
  {
    EXPECT_EQ(arr1[i], arr2[i]);
  }

  EXPECT_EQ(kdGenArrDestroy(arr1, kdMemFree), kd_true);
  EXPECT_EQ(kdGenArrDestroy(arr2, kdMemFree), kd_true);
}

TEST(GenArrEqualsTest, HandlesInvalidArguments)
{
  auto* arr = reinterpret_cast<kd_i32_t*>(0x696969);

  EXPECT_EQ(kdGenArrEquals(kd_null, kd_null), kd_false);
  EXPECT_EQ(kdGenArrEquals(kd_null, arr), kd_false);
  EXPECT_EQ(kdGenArrEquals(arr, kd_null), kd_false);
}
