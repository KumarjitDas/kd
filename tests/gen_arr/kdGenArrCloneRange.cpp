/**
 * @file kdGenArrCloneRange.cpp
 * @author Kumarjit Das
 * @date 2025-06-19
 * @brief kdGenArrCloneRange test file.
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


TEST(GenArrCloneRangeTest, AllocatesMemoryCorrectly)
{
  kd_i64_t len = 16, from = 2, to = 7;
  kd_i32_t src[]   = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  kd_i64_t src_len = sizeof(src) / sizeof(src[0]);
  auto*    arr     = static_cast<kd_i32_t*>(kdGenArrCreateFrom(KD_SZ_I32, len, src, src_len, kdMemAlloc));
  ASSERT_NE(arr, kd_null);

  auto* cloned_arr = static_cast<kd_i32_t*>(kdGenArrCloneRange(arr, from, to, kdMemAlloc));
  ASSERT_NE(cloned_arr, kd_null);
  EXPECT_EQ(kdGenArrGetElemSize(cloned_arr), kdGenArrGetElemSize(arr));
  EXPECT_EQ(kdGenArrGetMemSize(cloned_arr), (to - from + 1) * KD_I64_C(KD_SZ_I32));
  EXPECT_EQ(kdGenArrGetLen(cloned_arr), to - from + 1);
#ifdef KD_ENDIAN_BIG
  EXPECT_EQ(kdGenArrIsLE(cloned_arr), kdGenArrIsLE(arr));
  EXPECT_EQ(kdGenArrIsBE(cloned_arr), kdGenArrIsBE(arr));
#else
  EXPECT_EQ(kdGenArrIsLE(cloned_arr), kdGenArrIsLE(arr));
  EXPECT_EQ(kdGenArrIsBE(cloned_arr), kdGenArrIsBE(arr));
#endif /* KD_ENDIAN_BIG */
  EXPECT_EQ(kdGenArrGetEnd(cloned_arr), cloned_arr + to - from);

  for (kd_i64_t i = from; i <= to; ++i)
  {
    EXPECT_EQ(arr[i], cloned_arr[i - from]);
  }

  EXPECT_EQ(kdGenArrDestroy(arr, kdMemFree), kd_true);
  EXPECT_EQ(kdGenArrDestroy(cloned_arr, kdMemFree), kd_true);
}

TEST(GenArrCloneRangeTest, HandlesNullPointers)
{
  kd_i32_t* arr = KD_PI32_C(0x69420);

  EXPECT_EQ(kdGenArrCloneRange(kd_null, 2, 7, nullptr), kd_null);
  EXPECT_EQ(kdGenArrCloneRange(kd_null, 2, 7, kdMemAlloc), kd_null);
  EXPECT_EQ(kdGenArrCloneRange(arr, 2, 7, nullptr), kd_null);
}
