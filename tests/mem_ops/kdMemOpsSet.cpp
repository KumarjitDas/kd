/**
 * @file kdMemOpsSet.cpp
 * @author Kumarjit Das
 * @date 2025-06-03
 * @brief kdMemOpsSet test file.
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


TEST(MemOpsSetTest, SetsAllBytesCorrectly)
{
  const kd_usize_t len = 16;
  kd_i16_t         ptr_i16[len];
  kd_i32_t         ptr_i32[len];

  EXPECT_EQ(kdMemOpsSetI16(ptr_i16, len, 69), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemOpsSetI32(ptr_i32, len, 420), KD_RESULT_SUCCESS);

  for (kd_usize_t i = 0; i < len; ++i)
  {
    EXPECT_EQ(ptr_i16[i], 69);
    EXPECT_EQ(ptr_i32[i], 420);
  }
}

TEST(MemOpsSetTest, ZeroSizeReturnsFalse)
{
  kd_i16_t ptr_i16[16];
  kd_i32_t ptr_i32[16];

  EXPECT_EQ(kdMemOpsSetI16(kd_null, 0, 69), KD_RESULT_FAILURE);
  EXPECT_EQ(kdMemOpsSetI16(ptr_i16, 0, 69), KD_RESULT_FAILURE);
  EXPECT_EQ(kdMemOpsSetI32(kd_null, 0, 420), KD_RESULT_FAILURE);
  EXPECT_EQ(kdMemOpsSetI32(ptr_i32, 0, 420), KD_RESULT_FAILURE);
}

TEST(MemOpsSetTest, NullPointerReturnsFalse)
{
  EXPECT_EQ(kdMemOpsSetI16(kd_null, 32, 69), KD_RESULT_FAILURE);
  EXPECT_EQ(kdMemOpsSetI32(kd_null, 16, 420), KD_RESULT_FAILURE);
}
