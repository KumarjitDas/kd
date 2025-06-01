/**
 * @file kdMemAlgnGetAllocSize.cpp
 * @author Kumarjit Das
 * @date 2025-06-01
 * @brief kdMemAlgnGetAllocSize test file.
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


TEST(MemAlgnGetAllocSizeTest, ValidPowerOfTwoAlignmentAndOffset)
{
  EXPECT_EQ(kdMemAlgnGetAllocSize(1, 1, 1), 3);
  EXPECT_EQ(kdMemAlgnGetAllocSize(16, 4, 8), 28);
  EXPECT_EQ(kdMemAlgnGetAllocSize(16, 8, 4), 28);
}

TEST(MemAlgnGetAllocSizeTest, ZeroOffsetIsHandledCorrectly)
{
  EXPECT_EQ(kdMemAlgnGetAllocSize(0, 4, 0), 0);
  EXPECT_EQ(kdMemAlgnGetAllocSize(16, 4, 0), 20);
  EXPECT_EQ(kdMemAlgnGetAllocSize(32, 8, 0), 40);
}

TEST(MemAlgnGetAllocSizeTest, MaxAlignmentAndOffsetLimits)
{
  EXPECT_EQ(kdMemAlgnGetAllocSize(16, 128, 8), 152);
  EXPECT_EQ(kdMemAlgnGetAllocSize(16, 255, 8), 0);
  EXPECT_EQ(kdMemAlgnGetAllocSize(16, 64, 16), 0);
  EXPECT_EQ(kdMemAlgnGetAllocSize(16, 255, 32), 0);
}

TEST(MemAlgnGetAllocSizeTest, InvalidZeroAlignment)
{
  EXPECT_EQ(kdMemAlgnGetAllocSize(16, 0, 4), 0);
  EXPECT_EQ(kdMemAlgnGetAllocSize(16, 0, 8), 0);
}

TEST(MemAlgnGetAllocSizeTest, InvalidNonPowerOfTwoAlignment)
{
  EXPECT_EQ(kdMemAlgnGetAllocSize(1, 3, 1), 0);
  EXPECT_EQ(kdMemAlgnGetAllocSize(16, 5, 8), 0);
  EXPECT_EQ(kdMemAlgnGetAllocSize(16, 11, 4), 0);
}

TEST(MemAlgnGetAllocSizeTest, InvalidOffsetExceedsLimit)
{
  EXPECT_EQ(kdMemAlgnGetAllocSize(1, 1, 128), 0);
  EXPECT_EQ(kdMemAlgnGetAllocSize(16, 4, 64), 0);
  EXPECT_EQ(kdMemAlgnGetAllocSize(16, 8, 128), 0);
}

TEST(MemAlgnGetAllocSizeTest, InvalidNonPowerOfTwoOffset)
{
  EXPECT_EQ(kdMemAlgnGetAllocSize(1, 1, 3), 0);
  EXPECT_EQ(kdMemAlgnGetAllocSize(16, 4, 5), 0);
  EXPECT_EQ(kdMemAlgnGetAllocSize(16, 8, 6), 0);
  EXPECT_EQ(kdMemAlgnGetAllocSize(16, 8, 7), 0);
}
