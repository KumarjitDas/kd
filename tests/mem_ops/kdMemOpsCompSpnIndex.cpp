/**
 * @file kdMemOpsCompSpnIndex.cpp
 * @author Kumarjit Das
 * @date 2025-06-03
 * @brief kdMemOpsCompSpnIndex test file.
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


TEST(MemOpsCompSpnIndexTest, FindsFirstMatch)
{
  kd_i16_t  ptr_i16[]  = {'a', 'b', 'c', 'd', '4', '5', '6', '+', '-', '&', '*', '7', '8', '9', 'e', 'f', 'g', 'h'};
  kd_i16_t  keys_i16[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
  kd_i32_t  ptr_i32[]  = {'a', 'b', 'c', 'd', '4', '5', '6', '+', '-', '&', '*', '7', '8', '9', 'e', 'f', 'g', 'h'};
  kd_i32_t  keys_i32[] = {'!', '@', '#', '$', '%', '^', '&', '*', '-', '+'};
  kd_imax_t len_i16 = sizeof(ptr_i16) / sizeof(kd_i16_t), len_i32 = sizeof(ptr_i32) / sizeof(kd_i32_t);
  kd_imax_t keys_len_i16 = sizeof(keys_i16) / sizeof(kd_i16_t), keys_len_i32 = sizeof(keys_i32) / sizeof(kd_i32_t);

  EXPECT_EQ(kdMemOpsCompSpnIndexI16(ptr_i16, len_i16, keys_i16, keys_len_i16), 4);
  EXPECT_EQ(kdMemOpsCompSpnIndexI32(ptr_i32, len_i32, keys_i32, keys_len_i32), 7);
}

TEST(MemOpsCompSpnIndexTest, ReturnsNullIfAllMismatch)
{
  kd_i16_t  ptr_i16[]  = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k'};
  kd_i16_t  keys_i16[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
  kd_i32_t  ptr_i32[]  = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k'};
  kd_i32_t  keys_i32[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
  kd_imax_t len_i16 = sizeof(ptr_i16) / sizeof(kd_i16_t), len_i32 = sizeof(ptr_i32) / sizeof(kd_i32_t);
  kd_imax_t keys_len_i16 = sizeof(keys_i16) / sizeof(kd_i16_t), keys_len_i32 = sizeof(keys_i32) / sizeof(kd_i32_t);

  EXPECT_EQ(kdMemOpsCompSpnIndexI16(ptr_i16, len_i16, keys_i16, keys_len_i16), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI32(ptr_i32, len_i32, keys_i32, keys_len_i32), -1);
}

TEST(MemOpsCompSpnIndexTest, HandlesNullPointers)
{
  kd_i16_t  ptr_i16[16], keys_i16[8];
  kd_i32_t  ptr_i32[16], keys_i32[8];
  kd_imax_t len_i16 = sizeof(ptr_i16) / sizeof(kd_i16_t), len_i32 = sizeof(ptr_i32) / sizeof(kd_i32_t);
  kd_imax_t keys_len_i16 = sizeof(keys_i16) / sizeof(kd_i16_t), keys_len_i32 = sizeof(keys_i32) / sizeof(kd_i32_t);

  EXPECT_EQ(kdMemOpsCompSpnIndexI16(kd_null, 0, kd_null, 0), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI16(kd_null, 0, kd_null, keys_len_i16), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI16(kd_null, 0, keys_i16, 0), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI16(kd_null, 0, keys_i16, keys_len_i16), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI16(kd_null, len_i16, kd_null, 0), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI16(kd_null, len_i16, kd_null, keys_len_i16), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI16(kd_null, len_i16, keys_i16, 0), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI16(kd_null, len_i16, keys_i16, keys_len_i16), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI16(ptr_i16, 0, kd_null, 0), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI16(ptr_i16, 0, kd_null, keys_len_i16), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI16(ptr_i16, 0, keys_i16, 0), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI16(ptr_i16, 0, keys_i16, keys_len_i16), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI16(ptr_i16, len_i16, kd_null, 0), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI16(ptr_i16, len_i16, kd_null, keys_len_i16), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI16(ptr_i16, len_i16, keys_i16, 0), -1);

  EXPECT_EQ(kdMemOpsCompSpnIndexI32(kd_null, 0, kd_null, 0), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI32(kd_null, 0, kd_null, keys_len_i32), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI32(kd_null, 0, keys_i32, 0), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI32(kd_null, 0, keys_i32, keys_len_i32), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI32(kd_null, len_i32, kd_null, 0), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI32(kd_null, len_i32, kd_null, keys_len_i32), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI32(kd_null, len_i32, keys_i32, 0), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI32(kd_null, len_i32, keys_i32, keys_len_i32), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI32(ptr_i32, 0, kd_null, 0), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI32(ptr_i32, 0, kd_null, keys_len_i32), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI32(ptr_i32, 0, keys_i32, 0), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI32(ptr_i32, 0, keys_i32, keys_len_i32), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI32(ptr_i32, len_i32, kd_null, 0), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI32(ptr_i32, len_i32, kd_null, keys_len_i32), -1);
  EXPECT_EQ(kdMemOpsCompSpnIndexI32(ptr_i32, len_i32, keys_i32, 0), -1);
}
