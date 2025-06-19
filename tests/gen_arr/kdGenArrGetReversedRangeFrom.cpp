/**
 * @file kdGenArrGetReversedRangeFrom.cpp
 * @author Kumarjit Das
 * @date 2025-06-19
 * @brief kdGenArrGetReversedRangeFrom test file.
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


TEST(GenArrGetReversedRangeFromTest, ReversesAllBytesCorrectly)
{
  kd_i64_t len = 16, from = 3, to = 9, dst_from = 2;
  kd_i32_t src[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  kd_i32_t res[] = {10, 9, 8, 7, 6, 5, 4};

  auto* dst = static_cast<kd_i32_t*>(kdGenArrCreate(KD_SZ_I32, len, kdMemAlloc));
  ASSERT_NE(dst, kd_null);

  EXPECT_EQ(kdGenArrGetReversedRangeFrom(dst, dst_from, src, from, to), KD_RESULT_SUCCESS);

  for (kd_usize_t i = 0; i < KD_USIZE_C(to - from + 1); ++i)
  {
    EXPECT_EQ(dst[i + KD_USIZE_C(dst_from)], res[i]);
  }

  EXPECT_EQ(kdGenArrDestroy(dst, kdMemFree), KD_RESULT_SUCCESS);
}

TEST(GenArrGetReversedRangeFromTest, HandlesInvalidIndices)
{
  kd_i32_t* dst = reinterpret_cast<kd_i32_t*>(0x420420);
  kd_i32_t* src = reinterpret_cast<kd_i32_t*>(0x696969);

  EXPECT_EQ(kdGenArrGetReversedRangeFrom(dst, -2, src, -3, -9), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenArrGetReversedRangeFrom(dst, -2, src, -3, 9), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenArrGetReversedRangeFrom(dst, -2, src, 3, -9), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenArrGetReversedRangeFrom(dst, -2, src, 3, 9), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenArrGetReversedRangeFrom(dst, 2, src, -3, -9), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenArrGetReversedRangeFrom(dst, 2, src, -3, 9), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenArrGetReversedRangeFrom(dst, 2, src, 3, -9), KD_RESULT_FAILURE);
}

TEST(GenArrGetReversedRangeFromTest, NullPointerReturnsFalse)
{
  kd_i32_t* arr = reinterpret_cast<kd_i32_t*>(0x696969);

  EXPECT_EQ(kdGenArrGetReversedRangeFrom(kd_null, 2, kd_null, 3, 9), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenArrGetReversedRangeFrom(kd_null, 2, arr, 3, 9), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenArrGetReversedRangeFrom(arr, 2, kd_null, 3, 9), KD_RESULT_FAILURE);
}
