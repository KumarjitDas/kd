/**
 * @file kdMemFreeWithSizeInfo.cpp
 * @author Kumarjit Das
 * @date 2025-05-31
 * @brief kdMemFreeWithSizeInfo test file.
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
#include "kd/mem.h"
#include "gtest/gtest.h"

TEST(MemoryFreeWithSizeInfoTest, BasicArguments)
{
  u8* ptr = static_cast<u8*>(null);

  // Freeing a null pointer should fail
  EXPECT_EQ(kdMemFreeWithSizeInfo(null), KD_RESULT_FAILURE);

  // Allocate and free valid memory
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 256), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr), 256);
  EXPECT_EQ(kdMemFreeWithSizeInfo(&ptr), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);

  // Double-free should fail safely
  EXPECT_EQ(kdMemFreeWithSizeInfo(&ptr), KD_RESULT_FAILURE);
}

TEST(MemoryFreeWithSizeInfoTest, BasicFreeSequence)
{
  u8 *ptr1 = static_cast<u8*>(null), *ptr2 = static_cast<u8*>(null), *ptr3 = static_cast<u8*>(null),
     *ptr4 = static_cast<u8*>(null);

  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr1, 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemGetAllocSize(ptr1), 64);
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr2, 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemGetAllocSize(ptr2), 128);
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr3, 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemGetAllocSize(ptr3), 256);
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr4, 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemGetAllocSize(ptr4), 512);

  EXPECT_EQ(kdMemFreeWithSizeInfo(&ptr1), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr1, null);
  EXPECT_EQ(kdMemFreeWithSizeInfo(&ptr2), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr2, null);
  EXPECT_EQ(kdMemFreeWithSizeInfo(&ptr3), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr3, null);
  EXPECT_EQ(kdMemFreeWithSizeInfo(&ptr4), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr4, null);
}
