/**
 * @file kdMemOpsFindLast.cpp
 * @author Kumarjit Das
 * @date 2025-06-09
 * @brief kdMemOpsFindLast test file.
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
#include "gtest/gtest.h"


TEST(MemOpsFindLastTest, FindsFirstOccurrence)
{
  kd_i16_t ptr_i16[] = {1, 2, 3, 8, 5, 6, 3, 8, 9, 10};
  kd_i32_t ptr_i32[] = {11, 33, 22, 55, 88, 66, 33, 88, 99, 44};

  EXPECT_EQ(kdMemOpsFindLastI16(ptr_i16, sizeof(ptr_i16) / sizeof(*ptr_i16), 3), ptr_i16 + 6);
  EXPECT_EQ(kdMemOpsFindLastI16(ptr_i16, sizeof(ptr_i16) / sizeof(*ptr_i16), 8), ptr_i16 + 7);
  EXPECT_EQ(kdMemOpsFindLastI32(ptr_i32, sizeof(ptr_i32) / sizeof(*ptr_i32), 88), ptr_i32 + 7);
  EXPECT_EQ(kdMemOpsFindLastI32(ptr_i32, sizeof(ptr_i32) / sizeof(*ptr_i32), 33), ptr_i32 + 6);
}

TEST(MemOpsFindLastTest, ReturnsNullIfNotFound)
{
  kd_i16_t ptr_i16[] = {1, 2, 3, 8, 5, 6, 3, 8, 9, 10};
  kd_i32_t ptr_i32[] = {11, 33, 22, 55, 88, 66, 33, 88, 99, 44};

  EXPECT_EQ(kdMemOpsFindLastI16(ptr_i16, sizeof(ptr_i16) / sizeof(*ptr_i16), 0), kd_null);
  EXPECT_EQ(kdMemOpsFindLastI16(ptr_i16, sizeof(ptr_i16) / sizeof(*ptr_i16), 69), kd_null);
  EXPECT_EQ(kdMemOpsFindLastI32(ptr_i32, sizeof(ptr_i32) / sizeof(*ptr_i32), 0), kd_null);
  EXPECT_EQ(kdMemOpsFindLastI32(ptr_i32, sizeof(ptr_i32) / sizeof(*ptr_i32), 420), kd_null);
}

TEST(MemOpsFindLastTest, HandlesZeroSize)
{
  kd_i16_t ptr_i16[16];
  kd_i32_t ptr_i32[16];

  EXPECT_EQ(kdMemOpsFindLastI16(kd_null, 0, 69), kd_null);
  EXPECT_EQ(kdMemOpsFindLastI16(ptr_i16, 0, 69), kd_null);
  EXPECT_EQ(kdMemOpsFindLastI32(kd_null, 0, 420), kd_null);
  EXPECT_EQ(kdMemOpsFindLastI32(ptr_i32, 0, 420), kd_null);
}

TEST(MemOpsFindLastTest, HandlesNullPointer)
{
  EXPECT_EQ(kdMemOpsFindLastI16(kd_null, 32, 69), kd_null);
  EXPECT_EQ(kdMemOpsFindLastI32(kd_null, 16, 420), kd_null);
}
