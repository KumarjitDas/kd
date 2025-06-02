/**
 * @file kdGenMemOpsBytesSpn.cpp
 * @author Kumarjit Das
 * @date 2025-06-02
 * @brief kdGenMemOpsBytesSpn test file.
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


TEST(GenMemOpsBytesSpnTest, ReturnsFullSizeIfAllMatch)
{
  char str[]  = "69420";
  char keys[] = "1234567890";

  EXPECT_EQ(kdGenMemOpsBytesSpn(str, sizeof(str) - 1, keys, sizeof(keys) - 1), sizeof(str) - 1);
}

TEST(GenMemOpsBytesSpnTest, ReturnsCorrectPrefixLength)
{
  char str[]  = "129th";
  char keys[] = "1234567890";

  EXPECT_EQ(kdGenMemOpsBytesSpn(str, sizeof(str) - 1, keys, sizeof(keys) - 1), 3);
}

TEST(GenMemOpsBytesSpnTest, ReturnsZeroIfPrefixNotFound)
{
  char str[]  = "abcdefghijk";
  char keys[] = "1234567890";

  EXPECT_EQ(kdGenMemOpsBytesSpn(str, sizeof(str) - 1, keys, sizeof(keys) - 1), 0);
}

TEST(GenMemOpsBytesSpnTest, HandlesEmptyOrNull)
{
  kd_byte_t ptr[16], keys[8];

  EXPECT_EQ(kdGenMemOpsBytesSpn(kd_null, 0, kd_null, 0), 0);
  EXPECT_EQ(kdGenMemOpsBytesSpn(kd_null, 0, kd_null, sizeof(keys)), 0);
  EXPECT_EQ(kdGenMemOpsBytesSpn(kd_null, 0, keys, 0), 0);
  EXPECT_EQ(kdGenMemOpsBytesSpn(kd_null, 0, keys, sizeof(keys)), 0);
  EXPECT_EQ(kdGenMemOpsBytesSpn(kd_null, sizeof(ptr), kd_null, 0), 0);
  EXPECT_EQ(kdGenMemOpsBytesSpn(kd_null, sizeof(ptr), kd_null, sizeof(keys)), 0);
  EXPECT_EQ(kdGenMemOpsBytesSpn(kd_null, sizeof(ptr), keys, 0), 0);
  EXPECT_EQ(kdGenMemOpsBytesSpn(kd_null, sizeof(ptr), keys, sizeof(keys)), 0);
  EXPECT_EQ(kdGenMemOpsBytesSpn(ptr, 0, kd_null, 0), 0);
  EXPECT_EQ(kdGenMemOpsBytesSpn(ptr, 0, kd_null, sizeof(keys)), 0);
  EXPECT_EQ(kdGenMemOpsBytesSpn(ptr, 0, keys, 0), 0);
  EXPECT_EQ(kdGenMemOpsBytesSpn(ptr, 0, keys, sizeof(keys)), 0);
  EXPECT_EQ(kdGenMemOpsBytesSpn(ptr, sizeof(ptr), kd_null, 0), 0);
  EXPECT_EQ(kdGenMemOpsBytesSpn(ptr, sizeof(ptr), kd_null, sizeof(keys)), 0);
  EXPECT_EQ(kdGenMemOpsBytesSpn(ptr, sizeof(ptr), keys, 0), 0);
}
