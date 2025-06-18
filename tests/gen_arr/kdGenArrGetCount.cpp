/**
 * @file kdGenArrGetCount.cpp
 * @author Kumarjit Das
 * @date 2025-06-16
 * @brief kdGenArrGetCount test file.
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
#include "gtest/gtest.h"


TEST(GenArrGetCountTest, SetsElementCorrectly)
{
  kd_i64_t len      = 16;
  kd_i32_t init_val = 69, val = 420, man_val = 1234;

  auto* arr = static_cast<kd_i32_t*>(kdGenArrCreateInit(KD_SZ_I32, len, &init_val, kdMemAlloc));
  ASSERT_NE(arr, kd_null);

  arr[3] = man_val;
  arr[4] = man_val;
  EXPECT_EQ(kdGenArrFillRange(arr, 5, 8, &val), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdGenArrGetCount(arr, &init_val), 10);
  EXPECT_EQ(kdGenArrGetCount(arr, &val), 4);
  EXPECT_EQ(kdGenArrGetCount(arr, &man_val), 2);

  EXPECT_EQ(kdGenArrDestroy(arr, kdMemFree), kd_true);
}

TEST(GenArrGetCountTest, HandlesInvalidArguments)
{
  kd_i32_t *arr = reinterpret_cast<kd_i32_t*>(0x696969), val = 420;

  EXPECT_EQ(kdGenArrGetCount(kd_null, kd_null), kd_false);
  EXPECT_EQ(kdGenArrGetCount(kd_null, &val), kd_false);
  EXPECT_EQ(kdGenArrGetCount(arr, kd_null), kd_false);
}
