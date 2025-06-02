/**
 * @file kdGenMemOpsBlocksCompSpnIndex.cpp
 * @author Kumarjit Das
 * @date 2025-06-02
 * @brief kdGenMemOpsBlocksCompSpnIndex test file.
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


TEST(GenMemOpsBlocksCompSpnIndexTest, ReturnsCorrectMatchIndex)
{
  kd_usize_t idx;
  kd_i16_t   ptr[]   = {'a', 'b', 'c', 'd', '4', '5', '6', '+', '-', '&', '*', '7', '8', '9', 'e', 'f', 'g', 'h'};
  kd_i16_t   keys1[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
  kd_i16_t   keys2[] = {'!', '@', '#', '$', '%', '^', '&', '*', '-', '+'};

  EXPECT_EQ(kdGenMemOpsBlocksCompSpnIndex(&idx, ptr, sizeof(ptr), keys1, sizeof(*keys1), sizeof(keys1)),
            KD_RESULT_SUCCESS);
  EXPECT_EQ(idx, 4 * sizeof(*ptr));
  EXPECT_EQ(kdGenMemOpsBlocksCompSpnIndex(&idx, ptr, sizeof(ptr), keys2, sizeof(*keys2), sizeof(keys2)),
            KD_RESULT_SUCCESS);
  EXPECT_EQ(idx, 7 * sizeof(*ptr));
}

TEST(GenMemOpsBlocksCompSpnIndexTest, ReturnsFalseIfAllBlocksMismatch)
{
  kd_usize_t idx;
  kd_i16_t   ptr[]  = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k'};
  kd_i16_t   keys[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

  EXPECT_EQ(kdGenMemOpsBlocksCompSpnIndex(&idx, ptr, sizeof(ptr), keys, sizeof(*keys), sizeof(keys)),
            KD_RESULT_FAILURE);
}

TEST(GenMemOpsBlocksCompSpnIndexTest, HandlesZeroBlockSize)
{
  kd_usize_t idx;
  kd_i16_t   ptr[16], keys[8];

  EXPECT_EQ(kdGenMemOpsBlocksCompSpnIndex(&idx, ptr, 0, keys, 0, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsBlocksCompSpnIndex(&idx, ptr, 0, keys, 0, sizeof(keys)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsBlocksCompSpnIndex(&idx, ptr, 0, keys, sizeof(*keys), 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsBlocksCompSpnIndex(&idx, ptr, sizeof(ptr), keys, 0, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsBlocksCompSpnIndex(&idx, ptr, sizeof(ptr), keys, 0, sizeof(keys)), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsBlocksCompSpnIndex(&idx, ptr, sizeof(ptr), keys, sizeof(*keys), 0), KD_RESULT_FAILURE);
}

TEST(GenMemOpsBlocksCompSpnIndexTest, HandlesNullPointers)
{
  kd_usize_t idx;
  kd_i16_t   ptr[16], keys[8];

  EXPECT_EQ(
    kdGenMemOpsBlocksCompSpnIndex((kd_usize_t*)kd_null, kd_null, sizeof(ptr), kd_null, sizeof(*keys), sizeof(keys)),
    KD_RESULT_FAILURE);
  EXPECT_EQ(
    kdGenMemOpsBlocksCompSpnIndex((kd_usize_t*)kd_null, kd_null, sizeof(ptr), keys, sizeof(*keys), sizeof(keys)),
    KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsBlocksCompSpnIndex((kd_usize_t*)kd_null, ptr, sizeof(ptr), kd_null, sizeof(*keys), sizeof(keys)),
            KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsBlocksCompSpnIndex(&idx, kd_null, sizeof(ptr), kd_null, sizeof(*keys), sizeof(keys)),
            KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsBlocksCompSpnIndex(&idx, kd_null, sizeof(ptr), keys, sizeof(*keys), sizeof(keys)),
            KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsBlocksCompSpnIndex(&idx, ptr, sizeof(ptr), kd_null, sizeof(*keys), sizeof(keys)),
            KD_RESULT_FAILURE);
}
