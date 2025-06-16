/**
 * @file kdGenArrCreate.cpp
 * @author Kumarjit Das
 * @date 2025-06-16
 * @brief kdGenArrCreate test file.
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


TEST(GenArrCreateTest, AllocatesMemoryCorrectly)
{
  kd_i64_t len = 16;
  auto*    arr = static_cast<kd_i32_t*>(kdGenArrCreate(KD_SZ_I32, len, kdMemAlloc));
  ASSERT_NE(arr, kd_null);
  EXPECT_EQ(kdGenArrGetElemSize(arr), KD_SZ_I32);
  EXPECT_EQ(kdGenArrGetMemSize(arr), KD_I64_C(KD_SZ_I32) * len);
  EXPECT_EQ(kdGenArrGetLen(arr), len);
#ifdef KD_ENDIAN_BIG
  EXPECT_EQ(kdGenArrIsLE(arr), kd_false);
  EXPECT_EQ(kdGenArrIsBE(arr), kd_true);
#else
  EXPECT_EQ(kdGenArrIsLE(arr), kd_true);
  EXPECT_EQ(kdGenArrIsBE(arr), kd_false);
#endif /* KD_ENDIAN_BIG */
  EXPECT_EQ(kdGenArrGetEnd(arr), arr + (len - 1));
  EXPECT_EQ(kdGenArrDestroy(arr, kdMemFree), kd_true);
}

TEST(GenArrCreateTest, ChecksBounds)
{
  kd_i32_t* arr;

  arr = static_cast<kd_i32_t*>(kdGenArrCreate(16777220, 16, kdMemAlloc));
  ASSERT_EQ(arr, kd_null);

  arr = static_cast<kd_i32_t*>(kdGenArrCreate(KD_SZ_I32, KD_GEN_ARR_MAX_MEM_SZ, kdMemAlloc));
  ASSERT_EQ(arr, kd_null);
}

TEST(GenArrCreateTest, HandlesNullPointers) { EXPECT_EQ(kdGenArrCreate(4, 16, nullptr), kd_null); }

TEST(GenArrCreateTest, HandlesZeorSizes)
{
  EXPECT_EQ(kdGenArrCreate(0, 0, kdMemAlloc), kd_null);
  EXPECT_EQ(kdGenArrCreate(0, 16, kdMemAlloc), kd_null);
  EXPECT_EQ(kdGenArrCreate(4, 0, kdMemAlloc), kd_null);
}
