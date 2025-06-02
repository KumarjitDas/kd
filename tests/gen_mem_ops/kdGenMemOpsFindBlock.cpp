/**
 * @file kdGenMemOpsFindBlock.cpp
 * @author Kumarjit Das
 * @date 2025-06-02
 * @brief kdGenMemOpsFindBlock test file.
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


TEST(GenMemOpsFindBlockTest, FindsFirstMatchingBlock)
{
  kd_i16_t arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

#ifdef KD_LITTLE_ENDIAN
  kd_i8_t  val1_arr[] = {3, 0};
  kd_i8_t  val2_arr[] = {8, 0};
  kd_i16_t val1       = *reinterpret_cast<kd_i16_t*>(val1_arr);
  kd_i16_t val2       = *reinterpret_cast<kd_i16_t*>(val2_arr);
#else
  kd_i16_t val1 = 3;
  kd_i16_t val2 = 8;
#endif

  EXPECT_EQ(kdGenMemOpsFindBlock(arr, sizeof(arr), &val1, sizeof(val1)), arr + 2);
  EXPECT_EQ(kdGenMemOpsFindBlock(arr, sizeof(arr), &val2, sizeof(val2)), arr + 7);
}

TEST(GenMemOpsFindBlockTest, ReturnsNullIfNoMatch)
{
  kd_i16_t arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  kd_i16_t val1  = 0;

#ifdef KD_LITTLE_ENDIAN
  kd_i8_t  val2_arr[] = {11, 0};
  kd_i16_t val2       = *reinterpret_cast<kd_i16_t*>(val2_arr);
#else
  kd_i16_t val2 = 11;
#endif

  EXPECT_EQ(kdGenMemOpsFindBlock(arr, sizeof(arr), &val1, sizeof(val1)), kd_null);
  EXPECT_EQ(kdGenMemOpsFindBlock(arr, sizeof(arr), &val2, sizeof(val2)), kd_null);
}

TEST(GenMemOpsFindBlockTest, ZeroBlockSizeReturnsNull)
{
  kd_i16_t  val;
  kd_byte_t ptr[16];

  EXPECT_EQ(kdGenMemOpsFindBlock(kd_null, 0, kd_null, 0), kd_null);
  EXPECT_EQ(kdGenMemOpsFindBlock(kd_null, 0, kd_null, sizeof(val)), kd_null);
  EXPECT_EQ(kdGenMemOpsFindBlock(kd_null, sizeof(ptr), kd_null, 0), kd_null);
  EXPECT_EQ(kdGenMemOpsFindBlock(kd_null, 0, &val, 0), kd_null);
  EXPECT_EQ(kdGenMemOpsFindBlock(kd_null, 0, &val, sizeof(val)), kd_null);
  EXPECT_EQ(kdGenMemOpsFindBlock(kd_null, sizeof(ptr), &val, 0), kd_null);
  EXPECT_EQ(kdGenMemOpsFindBlock(ptr, 0, kd_null, 0), kd_null);
  EXPECT_EQ(kdGenMemOpsFindBlock(ptr, 0, kd_null, sizeof(val)), kd_null);
  EXPECT_EQ(kdGenMemOpsFindBlock(ptr, sizeof(ptr), kd_null, 0), kd_null);
  EXPECT_EQ(kdGenMemOpsFindBlock(ptr, 0, &val, 0), kd_null);
  EXPECT_EQ(kdGenMemOpsFindBlock(ptr, 0, &val, sizeof(val)), kd_null);
  EXPECT_EQ(kdGenMemOpsFindBlock(ptr, sizeof(ptr), &val, 0), kd_null);
}

TEST(GenMemOpsFindBlockTest, HandlesNullPointer)
{
  kd_i16_t  val;
  kd_byte_t ptr[16];

  EXPECT_EQ(kdGenMemOpsFindBlock(kd_null, sizeof(ptr), kd_null, sizeof(val)), kd_null);
  EXPECT_EQ(kdGenMemOpsFindBlock(kd_null, sizeof(ptr), &val, sizeof(val)), kd_null);
  EXPECT_EQ(kdGenMemOpsFindBlock(ptr, sizeof(ptr), kd_null, sizeof(val)), kd_null);
}
