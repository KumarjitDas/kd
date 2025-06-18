/**
 * @file kdGenArrFindAll.cpp
 * @author Kumarjit Das
 * @date 2025-06-06
 * @brief kdGenArrFindAll test file.
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


TEST(GenArrFindAllTest, FindsAllOccurrences)
{
  kd_i32_t       src[] = {1, 2, 3, 2, 5, 2, 7, 3, 9, 10};
  const kd_i64_t len   = sizeof(src) / sizeof(src[0]);
  kd_i32_t       val1  = 2;
  kd_i32_t       val2  = 3;

  auto* arr        = static_cast<kd_i32_t*>(kdGenArrCreateFrom(KD_SZ_I32, len, src, len, kdMemAlloc));
  auto* found_ptrs = static_cast<kd_i32_t**>(kdGenArrCreate(KD_SZ_PTR, len, kdMemAlloc));

  EXPECT_EQ(kdGenArrFindAll(found_ptrs, arr, &val1), 3);
  EXPECT_EQ(found_ptrs[0], arr + 1);
  EXPECT_EQ(found_ptrs[1], arr + 3);
  EXPECT_EQ(found_ptrs[2], arr + 5);
  EXPECT_EQ(kdGenArrFindAll(found_ptrs, arr, &val2), 2);
  EXPECT_EQ(found_ptrs[0], arr + 2);
  EXPECT_EQ(found_ptrs[1], arr + 7);

  EXPECT_EQ(kdGenArrDestroy(arr, kdMemFree), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdGenArrDestroy(found_ptrs, kdMemFree), KD_RESULT_SUCCESS);
}

TEST(GenArrFindAllTest, ReturnsZeroIfNotFound)
{
  kd_i32_t       src[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  const kd_i64_t len   = sizeof(src) / sizeof(src[0]);
  kd_i32_t       val1  = 0;
  kd_i32_t       val2  = 11;

  auto* arr        = static_cast<kd_i32_t*>(kdGenArrCreateFrom(KD_SZ_I32, len, src, len, kdMemAlloc));
  auto* found_ptrs = static_cast<kd_i32_t**>(kdGenArrCreate(KD_SZ_PTR, len, kdMemAlloc));

  EXPECT_EQ(kdGenArrFindAll(found_ptrs, arr, &val1), 0);
  EXPECT_EQ(kdGenArrFindAll(found_ptrs, arr, &val2), 0);

  EXPECT_EQ(kdGenArrDestroy(arr, kdMemFree), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdGenArrDestroy(found_ptrs, kdMemFree), KD_RESULT_SUCCESS);
}

TEST(GenArrFindAllTest, HandlesNullPointer)
{
  kd_i32_t *dst = KD_PI32_C(0x69420), *src = KD_PI32_C(0x69420), val = 69420;

  EXPECT_EQ(kdGenArrFindAll(kd_null, kd_null, kd_null), 0);
  EXPECT_EQ(kdGenArrFindAll(kd_null, kd_null, &val), 0);
  EXPECT_EQ(kdGenArrFindAll(kd_null, src, kd_null), 0);
  EXPECT_EQ(kdGenArrFindAll(kd_null, src, &val), 0);
  EXPECT_EQ(kdGenArrFindAll(dst, kd_null, kd_null), 0);
  EXPECT_EQ(kdGenArrFindAll(dst, kd_null, &val), 0);
  EXPECT_EQ(kdGenArrFindAll(dst, src, kd_null), 0);
}
