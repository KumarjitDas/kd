/**
 * @file kdGenMemOpsMove.cpp
 * @author Kumarjit Das
 * @date 2025-06-02
 * @brief kdGenMemOpsMove test file.
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


TEST(GenMemOpsMoveTest, MovesBytesCorrectly)
{
  kd_byte_t ptr1[] = {1, 2, 3, 4, 5};
  kd_byte_t ptr2[sizeof(ptr1)];

  EXPECT_EQ(kdGenMemOpsMove(ptr1, ptr2, sizeof(ptr1)), KD_RESULT_SUCCESS);

  for (kd_usize_t i = 0; i < sizeof(ptr1); ++i)
  {
    EXPECT_EQ(ptr1[i], ptr2[i]);
  }
}

TEST(GenMemOpsMoveTest, OverlappingRegionsHandledProperly)
{
  kd_byte_t  main_ptr[] = {69, 69, 1, 2, 3, 4, 5, 69, 69, 69, 69};
  kd_byte_t* ptr1       = main_ptr + 2;
  kd_byte_t* ptr2       = main_ptr + 4;
  kd_byte_t  res1[]     = {69, 69, 1, 2, 1, 2, 3, 4, 5, 69, 69};
  kd_byte_t  res2[]     = {69, 69, 1, 2, 3, 4, 5, 4, 5, 69, 69};

  EXPECT_EQ(kdGenMemOpsMove(ptr2, ptr1, 5), KD_RESULT_SUCCESS);

  for (kd_usize_t i = 0; i < sizeof(main_ptr); ++i)
  {
    EXPECT_EQ(main_ptr[i], res1[i]);
  }

  ptr1 = main_ptr + 4;
  ptr2 = main_ptr + 2;

  EXPECT_EQ(kdGenMemOpsMove(ptr2, ptr1, 5), KD_RESULT_SUCCESS);

  for (kd_usize_t i = 0; i < sizeof(main_ptr); ++i)
  {
    EXPECT_EQ(main_ptr[i], res2[i]);
  }

  EXPECT_EQ(kdGenMemOpsMove(ptr2, ptr1, 5), KD_RESULT_SUCCESS);
}

TEST(GenMemOpsMoveTest, HandlesZeroSize)
{
  kd_byte_t ptr[32];

  EXPECT_EQ(kdGenMemOpsMove(kd_null, kd_null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsMove(kd_null, ptr, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsMove(ptr, kd_null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsMove(ptr, ptr, 0), KD_RESULT_FAILURE);
}

TEST(GenMemOpsMoveTest, HandlesNullPointers)
{
  kd_byte_t ptr[32];

  EXPECT_EQ(kdGenMemOpsMove(kd_null, kd_null, 32), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsMove(kd_null, ptr, 32), KD_RESULT_FAILURE);
  EXPECT_EQ(kdGenMemOpsMove(ptr, kd_null, 32), KD_RESULT_FAILURE);
}
