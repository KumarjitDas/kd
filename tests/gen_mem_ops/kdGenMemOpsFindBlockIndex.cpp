/**
 * @file kdGenMemOpsFindBlockIndex.cpp
 * @author Kumarjit Das
 * @date 2025-06-02
 * @brief kdGenMemOpsFindBlockIndex test file.
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


TEST(GenMemOpsFindBlockIndexTest, ReturnsCorrectIndexIfBlockFound)
{
  kd_usize_t idx;
  kd_i16_t   arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

#ifdef KD_LITTLE_ENDIAN
  kd_i8_t  val1_arr[] = {3, 0};
  kd_i8_t  val2_arr[] = {8, 0};
  kd_i16_t val1       = *reinterpret_cast<kd_i16_t*>(val1_arr);
  kd_i16_t val2       = *reinterpret_cast<kd_i16_t*>(val2_arr);
#else
  kd_i16_t val1 = 3;
  kd_i16_t val2 = 8;
#endif

  EXPECT_EQ(kdGenMemOpsFindBlockIndex(&idx, arr, sizeof(arr), &val1, sizeof(val1)), KD_RESULT_SUCCESS);
  EXPECT_EQ(idx, 2 * sizeof(val1));
  EXPECT_EQ(kdGenMemOpsFindBlockIndex(&idx, arr, sizeof(arr), &val2, sizeof(val2)), KD_RESULT_SUCCESS);
  EXPECT_EQ(idx, 7 * sizeof(val2));
}

TEST(GenMemOpsFindBlockIndexTest, ReturnsFalseIfBlockNotFound)
{
  kd_usize_t idx;
  kd_i16_t   arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  kd_i16_t   val1  = 0;

#ifdef KD_LITTLE_ENDIAN
  kd_i8_t  val2_arr[] = {11, 0};
  kd_i16_t val2       = *reinterpret_cast<kd_i16_t*>(val2_arr);
#else
  kd_i16_t val2 = 11;
#endif

  EXPECT_EQ(kdGenMemOpsFindBlockIndex(&idx, arr, sizeof(arr), &val1, sizeof(val1)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsFindBlockIndex(&idx, arr, sizeof(arr), &val2, sizeof(val2)), KD_RESULT_FAILURE);
}

TEST(GenMemOpsFindBlockIndexTest, HandlesZeroBlockSize)
{
  kd_usize_t idx;
  kd_i16_t   val;
  kd_byte_t  ptr[16];

  EXPECT_EQ(kdGenMemOpsFindBlockIndex(&idx, kd_null, 0, kd_null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsFindBlockIndex(&idx, kd_null, 0, kd_null, sizeof(val)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsFindBlockIndex(&idx, kd_null, sizeof(ptr), kd_null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsFindBlockIndex(&idx, kd_null, 0, &val, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsFindBlockIndex(&idx, kd_null, 0, &val, sizeof(val)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsFindBlockIndex(&idx, kd_null, sizeof(ptr), &val, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsFindBlockIndex(&idx, ptr, 0, kd_null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsFindBlockIndex(&idx, ptr, 0, kd_null, sizeof(val)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsFindBlockIndex(&idx, ptr, sizeof(ptr), kd_null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsFindBlockIndex(&idx, ptr, 0, &val, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsFindBlockIndex(&idx, ptr, 0, &val, sizeof(val)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsFindBlockIndex(&idx, ptr, sizeof(ptr), &val, 0), KD_RESULT_FAILURE);
}

TEST(GenMemOpsFindBlockIndexTest, HandlesNullPointerOrIndex)
{
  kd_usize_t idx;
  kd_i16_t   val;
  kd_byte_t  ptr[16];

  EXPECT_EQ(kdGenMemOpsFindBlockIndex((kd_usize_t*)kd_null, kd_null, sizeof(ptr), kd_null, sizeof(val)),
            KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsFindBlockIndex((kd_usize_t*)kd_null, kd_null, sizeof(ptr), &val, sizeof(val)),
            KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsFindBlockIndex((kd_usize_t*)kd_null, ptr, sizeof(ptr), kd_null, sizeof(val)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsFindBlockIndex((kd_usize_t*)kd_null, ptr, sizeof(ptr), &val, sizeof(val)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsFindBlockIndex(&idx, kd_null, sizeof(ptr), kd_null, sizeof(val)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsFindBlockIndex(&idx, kd_null, sizeof(ptr), &val, sizeof(val)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsFindBlockIndex(&idx, ptr, sizeof(ptr), kd_null, sizeof(val)), KD_RESULT_FAILURE);
}
