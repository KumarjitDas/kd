/**
 * @file kdGenMemOpsCat.cpp
 * @author Kumarjit Das
 * @date 2025-06-02
 * @brief kdGenMemOpsCat test file.
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


TEST(GenMemOpsCatTest, ConcatenatesBothSources)
{
  kd_byte_t dst[16];
  kd_byte_t src1[8] = {1, 2, 3, 4, 5, 6, 7, 8};
  kd_byte_t src2[8] = {9, 10, 11, 12, 13, 14, 15, 16};
  kd_byte_t res[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

  EXPECT_EQ(kdGenMemOpsCat(dst, sizeof(dst), src1, sizeof(src1), src2, sizeof(src2)), KD_RESULT_SUCCESS);

  for (kd_usize_t i = 0; i < sizeof(dst); ++i)
  {
    EXPECT_EQ(dst[i], res[i]);
  }
}

TEST(GenMemOpsCatTest, HandlesNullPointers)
{
  kd_byte_t dst[16], src1[8], src2[8];

  EXPECT_EQ(kdGenMemOpsCat(kd_null, 0, kd_null, 0, kd_null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, 0, kd_null, 0, kd_null, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, 0, kd_null, 0, src2, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, 0, kd_null, 0, src2, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, 0, kd_null, sizeof(src1), kd_null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, 0, kd_null, sizeof(src1), kd_null, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, 0, kd_null, sizeof(src1), src2, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, 0, kd_null, sizeof(src1), src2, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, 0, src1, 0, kd_null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, 0, src1, 0, kd_null, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, 0, src1, 0, src2, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, 0, src1, 0, src2, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, 0, src1, sizeof(src1), kd_null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, 0, src1, sizeof(src1), kd_null, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, 0, src1, sizeof(src1), src2, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, 0, src1, sizeof(src1), src2, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, sizeof(dst), kd_null, 0, kd_null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, sizeof(dst), kd_null, 0, kd_null, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, sizeof(dst), kd_null, 0, src2, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, sizeof(dst), kd_null, 0, src2, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, sizeof(dst), kd_null, sizeof(src1), kd_null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, sizeof(dst), kd_null, sizeof(src1), kd_null, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, sizeof(dst), kd_null, sizeof(src1), src2, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, sizeof(dst), kd_null, sizeof(src1), src2, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, sizeof(dst), src1, 0, kd_null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, sizeof(dst), src1, 0, kd_null, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, sizeof(dst), src1, 0, src2, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, sizeof(dst), src1, 0, src2, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, sizeof(dst), src1, sizeof(src1), kd_null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, sizeof(dst), src1, sizeof(src1), kd_null, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, sizeof(dst), src1, sizeof(src1), src2, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(kd_null, sizeof(dst), src1, sizeof(src1), src2, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, 0, kd_null, 0, kd_null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, 0, kd_null, 0, kd_null, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, 0, kd_null, 0, src2, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, 0, kd_null, 0, src2, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, 0, kd_null, sizeof(src1), kd_null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, 0, kd_null, sizeof(src1), kd_null, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, 0, kd_null, sizeof(src1), src2, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, 0, kd_null, sizeof(src1), src2, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, 0, src1, 0, kd_null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, 0, src1, 0, kd_null, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, 0, src1, 0, src2, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, 0, src1, 0, src2, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, 0, src1, sizeof(src1), kd_null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, 0, src1, sizeof(src1), kd_null, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, 0, src1, sizeof(src1), src2, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, 0, src1, sizeof(src1), src2, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, sizeof(dst), kd_null, 0, kd_null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, sizeof(dst), kd_null, 0, kd_null, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, sizeof(dst), kd_null, 0, src2, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, sizeof(dst), kd_null, 0, src2, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, sizeof(dst), kd_null, sizeof(src1), kd_null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, sizeof(dst), kd_null, sizeof(src1), kd_null, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, sizeof(dst), kd_null, sizeof(src1), src2, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, sizeof(dst), kd_null, sizeof(src1), src2, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, sizeof(dst), src1, 0, kd_null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, sizeof(dst), src1, 0, kd_null, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, sizeof(dst), src1, 0, src2, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, sizeof(dst), src1, 0, src2, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, sizeof(dst), src1, sizeof(src1), kd_null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, sizeof(dst), src1, sizeof(src1), kd_null, sizeof(src2)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsCat(dst, sizeof(dst), src1, sizeof(src1), src2, 0), KD_RESULT_FAILURE);
}
