/**
 * @file kdMemOpsSpn.cpp
 * @author Kumarjit Das
 * @date 2025-06-09
 * @brief kdMemOpsSpn test file.
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


TEST(MemOpsSpnTest, ReturnsFullSizeIfAllBlocksMatch)
{
  kd_i16_t   ptr[]   = {'6', '9', '4', '2', '0'};
  kd_i16_t   keys[]  = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
  kd_usize_t ptr_len = sizeof(ptr) / sizeof(*ptr), keys_len = sizeof(keys) / sizeof(*keys);

  EXPECT_EQ(kdMemOpsSpnI16(ptr, ptr_len, keys, keys_len), ptr_len);
}

TEST(MemOpsSpnTest, ReturnsCorrectPrefixBlockSpan)
{
  kd_i16_t   ptr[]   = {'1', '2', '9', 't', 'h'};
  kd_i16_t   keys[]  = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
  kd_usize_t ptr_len = sizeof(ptr) / sizeof(*ptr), keys_len = sizeof(keys) / sizeof(*keys);

  EXPECT_EQ(kdMemOpsSpnI16(ptr, ptr_len, keys, keys_len), 3);
}

TEST(MemOpsSpnTest, ReturnsZeroIfPrefixNotFound)
{
  kd_i16_t   ptr[]   = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k'};
  kd_i16_t   keys[]  = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
  kd_usize_t ptr_len = sizeof(ptr) / sizeof(*ptr), keys_len = sizeof(keys) / sizeof(*keys);

  EXPECT_EQ(kdMemOpsSpnI16(ptr, ptr_len, keys, keys_len), 0);
}

TEST(MemOpsSpnTest, HandlesZeroBlockSize)
{
  kd_i16_t   ptr[16], keys[8];
  kd_usize_t ptr_len = sizeof(ptr) / sizeof(*ptr), keys_len = sizeof(keys) / sizeof(*keys);

  EXPECT_EQ(kdMemOpsSpnI16(ptr, 0, keys, 0), 0);
  EXPECT_EQ(kdMemOpsSpnI16(ptr, 0, keys, keys_len), 0);
  EXPECT_EQ(kdMemOpsSpnI16(ptr, ptr_len, keys, 0), 0);
}

TEST(MemOpsSpnTest, HandlesNullPointers)
{
  kd_i16_t   ptr[16], keys[8];
  kd_usize_t ptr_len = sizeof(ptr) / sizeof(*ptr), keys_len = sizeof(keys) / sizeof(*keys);

  EXPECT_EQ(kdMemOpsSpnI16(kd_null, ptr_len, kd_null, keys_len), 0);
  EXPECT_EQ(kdMemOpsSpnI16(kd_null, ptr_len, keys, keys_len), 0);
  EXPECT_EQ(kdMemOpsSpnI16(ptr, ptr_len, kd_null, keys_len), 0);
}
