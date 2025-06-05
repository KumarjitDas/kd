/**
 * @file kdGenMemOpsFindAllBlocks.cpp
 * @author Kumarjit Das
 * @date 2025-06-06
 * @brief kdGenMemOpsFindAllBlocks test file.
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


TEST(GenMemOpsFindAllBlocksTest, FindsAllOccurrences)
{
  kd_i32_t  ptr[] = {1, 2, 3, 2, 5, 2, 7, 3, 9, 10};
  kd_i32_t* found_ptrs[8];
  kd_i32_t  val1 = 2;
  kd_i32_t  val2 = 3;

  EXPECT_EQ(kdGenMemOpsFindAllBlocks(found_ptrs, sizeof(found_ptrs), ptr, sizeof(ptr), &val1, sizeof(val1)), 3);
  EXPECT_EQ(found_ptrs[0], ptr + 1);
  EXPECT_EQ(found_ptrs[1], ptr + 3);
  EXPECT_EQ(found_ptrs[2], ptr + 5);
  EXPECT_EQ(kdGenMemOpsFindAllBlocks(found_ptrs, sizeof(found_ptrs), ptr, sizeof(ptr), &val2, sizeof(val2)), 2);
  EXPECT_EQ(found_ptrs[0], ptr + 2);
  EXPECT_EQ(found_ptrs[1], ptr + 7);
}

TEST(GenMemOpsFindAllBlocksTest, ReturnsZeroIfNotFound)
{
  kd_i32_t  ptr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  kd_i32_t* found_ptrs[8];
  kd_i32_t  val1 = 0;
  kd_i32_t  val2 = 11;

  EXPECT_EQ(kdGenMemOpsFindAllBlocks(found_ptrs, sizeof(found_ptrs), ptr, sizeof(ptr), &val1, sizeof(val1)), 0);
  EXPECT_EQ(kdGenMemOpsFindAllBlocks(found_ptrs, sizeof(found_ptrs), ptr, sizeof(ptr), &val2, sizeof(val2)), 0);
}

TEST(GenMemOpsFindAllBlocksTest, HandlesZeroSize)
{
  kd_i32_t  ptr[16];
  kd_i32_t* found_ptrs[8];
  kd_i32_t  val = 6969;

  EXPECT_EQ(kdGenMemOpsFindAllBlocks(found_ptrs, 0, ptr, 0, &val, 0), 0);
  EXPECT_EQ(kdGenMemOpsFindAllBlocks(found_ptrs, 0, ptr, 0, &val, sizeof(val)), 0);
  EXPECT_EQ(kdGenMemOpsFindAllBlocks(found_ptrs, 0, ptr, sizeof(ptr), &val, 0), 0);
  EXPECT_EQ(kdGenMemOpsFindAllBlocks(found_ptrs, 0, ptr, sizeof(ptr), &val, sizeof(val)), 0);
  EXPECT_EQ(kdGenMemOpsFindAllBlocks(found_ptrs, sizeof(found_ptrs), ptr, 0, &val, 0), 0);
  EXPECT_EQ(kdGenMemOpsFindAllBlocks(found_ptrs, sizeof(found_ptrs), ptr, 0, &val, sizeof(val)), 0);
  EXPECT_EQ(kdGenMemOpsFindAllBlocks(found_ptrs, sizeof(found_ptrs), ptr, sizeof(ptr), &val, 0), 0);
}

TEST(GenMemOpsFindAllBlocksTest, HandlesNullPointer)
{
  kd_i32_t  ptr[16];
  kd_i32_t* found_ptrs[8];
  kd_i32_t  val = 6969;

  EXPECT_EQ(kdGenMemOpsFindAllBlocks(kd_null, sizeof(found_ptrs), kd_null, sizeof(ptr), kd_null, sizeof(val)), 0);
  EXPECT_EQ(kdGenMemOpsFindAllBlocks(kd_null, sizeof(found_ptrs), kd_null, sizeof(ptr), &val, sizeof(val)), 0);
  EXPECT_EQ(kdGenMemOpsFindAllBlocks(kd_null, sizeof(found_ptrs), ptr, sizeof(ptr), kd_null, sizeof(val)), 0);
  EXPECT_EQ(kdGenMemOpsFindAllBlocks(kd_null, sizeof(found_ptrs), ptr, sizeof(ptr), &val, sizeof(val)), 0);
  EXPECT_EQ(kdGenMemOpsFindAllBlocks(found_ptrs, sizeof(found_ptrs), kd_null, sizeof(ptr), kd_null, sizeof(val)), 0);
  EXPECT_EQ(kdGenMemOpsFindAllBlocks(found_ptrs, sizeof(found_ptrs), kd_null, sizeof(ptr), &val, sizeof(val)), 0);
  EXPECT_EQ(kdGenMemOpsFindAllBlocks(found_ptrs, sizeof(found_ptrs), ptr, sizeof(ptr), kd_null, sizeof(val)), 0);
}
