/**
 * @file kdGenMemOpsSetBlocks.cpp
 * @author Kumarjit Das
 * @date 2025-06-02
 * @brief kdGenMemOpsSetBlocks test file.
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


TEST(GenMemOpsSetBlocksTest, FillsMemoryWithBlockPattern)
{
  kd_i16_t arr[16];

#ifdef KD_LITTLE_ENDIAN
  kd_i8_t  val_arr[] = {69, 0};
  kd_i16_t val       = *reinterpret_cast<kd_i16_t*>(val_arr);
#else
  kd_i16_t val = 69;
#endif

  EXPECT_EQ(kdGenMemOpsSetBlocks(arr, sizeof(arr), &val, sizeof(val)), KD_RESULT_SUCCESS);

  for (kd_usize_t i = 0; i < (sizeof(arr) / sizeof(*arr)); ++i)
  {
    EXPECT_EQ(arr[i], 69);
  }
}

TEST(GenMemOpsSetBlocksTest, ZeroSizeReturnsFalse)
{
  kd_byte_t ptr[16];

  EXPECT_EQ(kdGenMemOpsSetBlocks(kd_null, 0, ptr, 8), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsSetBlocks(ptr, 0, ptr, 8), KD_RESULT_FAILURE);
}

TEST(GenMemOpsSetBlocksTest, ZeroBlockSizeReturnsFalse)
{
  kd_byte_t ptr[16];

  EXPECT_EQ(kdGenMemOpsSetBlocks(ptr, sizeof(ptr), kd_null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsSetBlocks(ptr, sizeof(ptr), ptr, 0), KD_RESULT_FAILURE);
}

TEST(GenMemOpsSetBlocksTest, NullPointerReturnsFalse)
{
  kd_byte_t ptr[16];

  EXPECT_EQ(kdGenMemOpsSetBlocks(kd_null, 16, kd_null, 8), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsSetBlocks(kd_null, 16, ptr, 8), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsSetBlocks(ptr, 16, kd_null, 8), KD_RESULT_FAILURE);
}
