/**
 * @file kdGenMemOpsBytesCompSpn.cpp
 * @author Kumarjit Das
 * @date 2025-06-02
 * @brief kdGenMemOpsBytesCompSpn test file.
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


TEST(GenMemOpsBytesCompSpnTest, FindsFirstMatch)
{
  char str[]   = "abcd456+-&*789efgh";
  char keys1[] = "1234567890";
  char keys2[] = "!@#$%^&*-+";

  EXPECT_EQ(kdGenMemOpsBytesCompSpn(str, sizeof(str) - 1, keys1, sizeof(keys1) - 1), str + 4);
  EXPECT_EQ(kdGenMemOpsBytesCompSpn(str, sizeof(str) - 1, keys2, sizeof(keys2) - 1), str + 7);
}

TEST(GenMemOpsBytesCompSpnTest, ReturnsNullIfAllMismatch)
{
  char str[]  = "abcdefghijk";
  char keys[] = "1234567890";

  EXPECT_EQ(kdGenMemOpsBytesCompSpn(str, sizeof(str) - 1, keys, sizeof(keys) - 1), kd_null);
}

TEST(GenMemOpsBytesCompSpnTest, HandlesNullPointers)
{
  kd_byte_t ptr[16], keys[8];

  EXPECT_EQ(kdGenMemOpsBytesCompSpn(kd_null, 0, kd_null, 0), kd_null);
  EXPECT_EQ(kdGenMemOpsBytesCompSpn(kd_null, 0, kd_null, sizeof(keys)), kd_null);
  EXPECT_EQ(kdGenMemOpsBytesCompSpn(kd_null, 0, keys, 0), kd_null);
  EXPECT_EQ(kdGenMemOpsBytesCompSpn(kd_null, 0, keys, sizeof(keys)), kd_null);
  EXPECT_EQ(kdGenMemOpsBytesCompSpn(kd_null, sizeof(ptr), kd_null, 0), kd_null);
  EXPECT_EQ(kdGenMemOpsBytesCompSpn(kd_null, sizeof(ptr), kd_null, sizeof(keys)), kd_null);
  EXPECT_EQ(kdGenMemOpsBytesCompSpn(kd_null, sizeof(ptr), keys, 0), kd_null);
  EXPECT_EQ(kdGenMemOpsBytesCompSpn(kd_null, sizeof(ptr), keys, sizeof(keys)), kd_null);
  EXPECT_EQ(kdGenMemOpsBytesCompSpn(ptr, 0, kd_null, 0), kd_null);
  EXPECT_EQ(kdGenMemOpsBytesCompSpn(ptr, 0, kd_null, sizeof(keys)), kd_null);
  EXPECT_EQ(kdGenMemOpsBytesCompSpn(ptr, 0, keys, 0), kd_null);
  EXPECT_EQ(kdGenMemOpsBytesCompSpn(ptr, 0, keys, sizeof(keys)), kd_null);
  EXPECT_EQ(kdGenMemOpsBytesCompSpn(ptr, sizeof(ptr), kd_null, 0), kd_null);
  EXPECT_EQ(kdGenMemOpsBytesCompSpn(ptr, sizeof(ptr), kd_null, sizeof(keys)), kd_null);
  EXPECT_EQ(kdGenMemOpsBytesCompSpn(ptr, sizeof(ptr), keys, 0), kd_null);
}
