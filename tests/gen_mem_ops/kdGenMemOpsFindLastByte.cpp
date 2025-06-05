/**
 * @file kdGenMemOpsFindLastByte.cpp
 * @author Kumarjit Das
 * @date 2025-06-06
 * @brief kdGenMemOpsFindLastByte test file.
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


TEST(GenMemOpsFindLastByteTest, FindsLastOccurrence)
{
  kd_byte_t ptr[] = {1, 2, 3, 8, 5, 6, 3, 8, 9, 10};

  EXPECT_EQ(kdGenMemOpsFindLastByte(ptr, sizeof(ptr), 3), ptr + 6);
  EXPECT_EQ(kdGenMemOpsFindLastByte(ptr, sizeof(ptr), 8), ptr + 7);
}

TEST(GenMemOpsFindLastByteTest, ReturnsNullIfNotFound)
{
  kd_byte_t ptr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(kdGenMemOpsFindLastByte(ptr, sizeof(ptr), 0), kd_null);
  EXPECT_EQ(kdGenMemOpsFindLastByte(ptr, sizeof(ptr), 69), kd_null);
}

TEST(GenMemOpsFindLastByteTest, HandlesZeroSize)
{
  kd_byte_t ptr[16];

  EXPECT_EQ(kdGenMemOpsFindLastByte(kd_null, 0, 69), kd_null);
  EXPECT_EQ(kdGenMemOpsFindLastByte(ptr, 0, 69), kd_null);
}

TEST(GenMemOpsFindLastByteTest, HandlesNullPointer) { EXPECT_EQ(kdGenMemOpsFindLastByte(kd_null, 16, 69), kd_null); }
