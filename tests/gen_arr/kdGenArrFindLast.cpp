/**
 * @file kdGenArrFindLast.cpp
 * @author Kumarjit Das
 * @date 2025-06-19
 * @brief kdGenArrFindLast test file.
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


#include "kd.h"
#include "kd/mem.h"
#include "gtest/gtest.h"


TEST(GenArrFindLastTest, FindsFirstOccurrence)
{
  kd_i16_t ptr_i16[] = {1, 6, 3, 8, 5, 6, 3, 8, 9, 10}, val1_i16 = 3, val2_i16 = 6;
  kd_i32_t ptr_i32[] = {11, 12, 17, 14, 15, 12, 17, 18, 19, 20}, val1_i32 = 12, val2_i32 = 17;

#if defined KD_ARCH_64BIT_INT
  kd_i64_t len1 = sizeof(ptr_i16) / sizeof(*ptr_i16);
  kd_i64_t len2 = sizeof(ptr_i32) / sizeof(*ptr_i32);
#else  /* !defined KD_ARCH_64BIT_INT */
  kd_i32_t len1 = sizeof(ptr_i16) / sizeof(*ptr_i16);
  kd_i32_t len2 = sizeof(ptr_i32) / sizeof(*ptr_i32);
#endif /* KD_ARCH_64BIT_INT */

  auto* arr_i16 = static_cast<kd_i16_t*>(kdGenArrCreateFrom(KD_SZ_I16, len1, ptr_i16, len1, kdMemAlloc));
  ASSERT_NE(arr_i16, kd_null);

  auto* arr_i32 = static_cast<kd_i32_t*>(kdGenArrCreateFrom(KD_SZ_I32, len2, ptr_i32, len2, kdMemAlloc));
  ASSERT_NE(arr_i32, kd_null);

  EXPECT_EQ(kdGenArrFindLast(arr_i16, &val1_i16), arr_i16 + 6);
  EXPECT_EQ(kdGenArrFindLast(arr_i16, &val2_i16), arr_i16 + 5);
  EXPECT_EQ(kdGenArrFindLast(arr_i32, &val1_i32), arr_i32 + 5);
  EXPECT_EQ(kdGenArrFindLast(arr_i32, &val2_i32), arr_i32 + 6);

  EXPECT_EQ(kdGenArrDestroy(arr_i16, kdMemFree), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdGenArrDestroy(arr_i32, kdMemFree), KD_RESULT_SUCCESS);
}

TEST(GenArrFindLastTest, ReturnsNullIfNotFound)
{
  kd_i16_t ptr_i16[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, val1_i16 = 420, val2_i16 = -69;
  kd_i32_t ptr_i32[] = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, val1_i32 = -69, val2_i32 = 420;

#if defined KD_ARCH_64BIT_INT
  kd_i64_t len_i16 = sizeof(ptr_i16) / sizeof(*ptr_i16);
  kd_i64_t len_i32 = sizeof(ptr_i32) / sizeof(*ptr_i32);
#else  /* !defined KD_ARCH_64BIT_INT */
  kd_i32_t len_i16 = sizeof(ptr_i16) / sizeof(*ptr_i16);
  kd_i32_t len_i32 = sizeof(ptr_i32) / sizeof(*ptr_i32);
#endif /* KD_ARCH_64BIT_INT */

  auto* arr_i16 = static_cast<kd_i32_t*>(kdGenArrCreateFrom(KD_SZ_I16, len_i16, ptr_i16, len_i16, kdMemAlloc));
  auto* arr_i32 = static_cast<kd_i32_t*>(kdGenArrCreateFrom(KD_SZ_I32, len_i32, ptr_i32, len_i32, kdMemAlloc));

  EXPECT_EQ(kdGenArrFindLast(arr_i16, &val1_i16), kd_null);
  EXPECT_EQ(kdGenArrFindLast(arr_i16, &val2_i16), kd_null);
  EXPECT_EQ(kdGenArrFindLast(arr_i32, &val1_i32), kd_null);
  EXPECT_EQ(kdGenArrFindLast(arr_i32, &val2_i32), kd_null);

  EXPECT_EQ(kdGenArrDestroy(arr_i16, kdMemFree), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdGenArrDestroy(arr_i32, kdMemFree), KD_RESULT_SUCCESS);
}

TEST(GenArrFindLastTest, HandlesNullPointer)
{
  kd_i32_t* arr = KD_PI32_C(0x69420);

  EXPECT_EQ(kdGenArrFindLast(kd_null, kd_null), kd_null);
  EXPECT_EQ(kdGenArrFindLast(kd_null, arr), kd_null);
  EXPECT_EQ(kdGenArrFindLast(arr, kd_null), kd_null);
}
