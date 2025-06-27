/**
 * @file kdGenMemOpsFindAllByteIndices.cpp
 * @author Kumarjit Das
 * @date 2025-06-06
 * @brief kdGenMemOpsFindAllByteIndices test file.
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


TEST(GenMemOpsFindAllBytesIndexTest, FindsAllOccurrences)
{
  kd_byte_t  ptr[] = {1, 2, 3, 2, 5, 2, 7, 3, 9, 10};
  kd_usize_t idxs[8];

  EXPECT_EQ(kdGenMemOpsFindAllByteIndices(idxs, sizeof(idxs), ptr, sizeof(ptr), 2), 3);
  EXPECT_EQ(idxs[0], 1);
  EXPECT_EQ(idxs[1], 3);
  EXPECT_EQ(idxs[2], 5);
  EXPECT_EQ(kdGenMemOpsFindAllByteIndices(idxs, sizeof(idxs), ptr, sizeof(ptr), 3), 2);
  EXPECT_EQ(idxs[0], 2);
  EXPECT_EQ(idxs[1], 7);
}

TEST(GenMemOpsFindAllBytesIndexTest, ReturnsZeroIfNotFound)
{
  kd_byte_t  ptr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  kd_usize_t idxs[8];

  EXPECT_EQ(kdGenMemOpsFindAllByteIndices(idxs, sizeof(idxs), ptr, sizeof(ptr), 0), 0);
  EXPECT_EQ(kdGenMemOpsFindAllByteIndices(idxs, sizeof(idxs), ptr, sizeof(ptr), 69), 0);
}

TEST(GenMemOpsFindAllBytesIndexTest, HandlesZeroSize)
{
  kd_byte_t  ptr[16];
  kd_usize_t idxs[8];

  EXPECT_EQ(kdGenMemOpsFindAllByteIndices(idxs, 0, ptr, 0, 69), 0);
  EXPECT_EQ(kdGenMemOpsFindAllByteIndices(idxs, 0, ptr, sizeof(ptr), 69), 0);
  EXPECT_EQ(kdGenMemOpsFindAllByteIndices(idxs, sizeof(idxs), ptr, 0, 69), 0);
}

TEST(GenMemOpsFindAllBytesIndexTest, HandlesNullPointer)
{
  kd_byte_t  ptr[16];
  kd_usize_t idxs[8];

  EXPECT_EQ(kdGenMemOpsFindAllByteIndices((kd_usize_t*)kd_null, 8, kd_null, 16, 69), 0);
  EXPECT_EQ(kdGenMemOpsFindAllByteIndices((kd_usize_t*)kd_null, 8, ptr, 16, 69), 0);
  EXPECT_EQ(kdGenMemOpsFindAllByteIndices(idxs, 8, kd_null, 16, 69), 0);
}
