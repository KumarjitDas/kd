/**
 * @file kdMemAlgnGetBackwardPtr.cpp
 * @author Kumarjit Das
 * @date 2025-06-01
 * @brief kdMemAlgnGetBackwardPtr test file.
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


TEST(MemAlgnGetBackwardPtrTest, AlignsCorrectlyForGivenOffset)
{
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(4), 4, 1), reinterpret_cast<void*>(0));
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(5), 4, 1), reinterpret_cast<void*>(4));
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(6), 4, 1), reinterpret_cast<void*>(4));
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(12), 4, 1), reinterpret_cast<void*>(8));

  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(4), 4, 2), reinterpret_cast<void*>(0));
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(5), 4, 2), reinterpret_cast<void*>(4));
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(6), 4, 2), reinterpret_cast<void*>(4));
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(12), 4, 2), reinterpret_cast<void*>(8));

  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(4), 4, 4), reinterpret_cast<void*>(0));
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(5), 4, 4), reinterpret_cast<void*>(4));
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(6), 4, 4), reinterpret_cast<void*>(4));
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(12), 4, 4), reinterpret_cast<void*>(8));

  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(4), 4, 8), reinterpret_cast<void*>(0));
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(5), 4, 8), reinterpret_cast<void*>(4));
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(6), 4, 8), reinterpret_cast<void*>(4));
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(12), 4, 8), reinterpret_cast<void*>(8));
}

TEST(MemAlgnGetBackwardPtrTest, ZeroOffsetHandledCorrectly)
{
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(4), 4, 0), reinterpret_cast<void*>(0));
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(5), 4, 0), reinterpret_cast<void*>(4));
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(6), 4, 0), reinterpret_cast<void*>(4));
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(12), 4, 0), reinterpret_cast<void*>(8));

  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(8), 8, 0), reinterpret_cast<void*>(0));
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(13), 8, 0), reinterpret_cast<void*>(8));
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(14), 8, 0), reinterpret_cast<void*>(8));
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(16), 8, 0), reinterpret_cast<void*>(8));
}

TEST(MemAlgnGetBackwardPtrTest, AlignmentAndOffsetBoundaries)
{
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(4), 255, 0), null);
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(5), 4, 23), null);
}

TEST(MemAlgnGetBackwardPtrTest, InvalidAlignmentOrOffsetPanicsOrFails)
{
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(4), 0, 0), null);
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(5), 3, 0), null);
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(6), 19, 0), null);
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(7), 35, 0), null);

  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(4), 4, 3), null);
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(5), 4, 5), null);
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(6), 4, 6), null);
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(7), 4, 7), null);

  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(4), 0, 3), null);
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(5), 1, 5), null);
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(6), 19, 6), null);
  EXPECT_EQ(kdMemAlgnGetBackwardPtr(reinterpret_cast<void*>(7), 35, 7), null);
}
