/**
 * @file kdMemAllocWithSizeInfo.cpp
 * @author Kumarjit Das
 * @date 2025-05-31
 * @brief kdMemAllocWithSizeInfo test file.
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


TEST(MemoryAllocWithSizeInfoTest, BasicArguments)
{
  u8* ptr = static_cast<u8*>(null);

  // Null pointer
  EXPECT_EQ(kdMemAllocWithSizeInfo(null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdMemAllocWithSizeInfo(null, 1), KD_RESULT_FAILURE);
  EXPECT_EQ(kdMemAllocWithSizeInfo(null, 128), KD_RESULT_FAILURE);

  // Zero size
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(ptr, null);

  // Valid allocation - 1 byte
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 1), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr), 1);
  kdMemFreeWithSizeInfo(&ptr);

  // Valid allocation - 128 bytes
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 128), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr), 128);
  kdMemFreeWithSizeInfo(&ptr);

  // Valid allocation - 1024 bytes
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 1024), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr), 1024);
  kdMemFreeWithSizeInfo(&ptr);
}

TEST(MemoryAllocWithSizeInfoTest, BasicAllocationBytes)
{
  u8* ptr = static_cast<u8*>(null);

  // Allocate 1 byte
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 1), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr), 1);
  kdMemFreeWithSizeInfo(&ptr);

  // Allocate 64 bytes
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 64), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr), 64);
  kdMemFreeWithSizeInfo(&ptr);

  // Allocate 128 bytes
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 128), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr), 128);
  kdMemFreeWithSizeInfo(&ptr);

  // Allocate 256 bytes
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 256), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr), 256);
  kdMemFreeWithSizeInfo(&ptr);

  // Allocate 512 bytes
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 512), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr), 512);
  kdMemFreeWithSizeInfo(&ptr);

  // Allocate 1024 bytes
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 1024), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr), 1024);
  kdMemFreeWithSizeInfo(&ptr);
}

TEST(MemoryAllocWithSizeInfoTest, BasicAllocationKiloBytes)
{
  u8* ptr = static_cast<u8*>(null);

  // 1 KB
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 1024), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr), 1024);
  kdMemFreeWithSizeInfo(&ptr);

  // 64 KB
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 1024 * 64), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr), 1024 * 64);
  kdMemFreeWithSizeInfo(&ptr);

  // 128 KB
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 1024 * 128), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr), 1024 * 128);
  kdMemFreeWithSizeInfo(&ptr);

  // 256 KB
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 1024 * 256), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr), 1024 * 256);
  kdMemFreeWithSizeInfo(&ptr);

  // 512 KB
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 1024 * 512), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr), 1024 * 512);
  kdMemFreeWithSizeInfo(&ptr);

  // 1 MB
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 1024 * 1024), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr), 1024 * 1024);
  kdMemFreeWithSizeInfo(&ptr);
}

TEST(MemoryAllocWithSizeInfoTest, BasicAllocationMegaBytes)
{
  u8* ptr = static_cast<u8*>(null);

  // 1 MB
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 1024 * 1024), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr), 1024 * 1024);
  kdMemFreeWithSizeInfo(&ptr);

  // 2 MB
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 1024 * 1024 * 2), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr), 1024 * 1024 * 2);
  kdMemFreeWithSizeInfo(&ptr);

  // 4 MB
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 1024 * 1024 * 4), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr), 1024 * 1024 * 4);
  kdMemFreeWithSizeInfo(&ptr);

  // 8 MB
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 1024 * 1024 * 8), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr), 1024 * 1024 * 8);
  kdMemFreeWithSizeInfo(&ptr);

  // 16 MB
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 1024 * 1024 * 16), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr), 1024 * 1024 * 16);
  kdMemFreeWithSizeInfo(&ptr);
}

TEST(MemoryAllocWithSizeInfoTest, BasicMultipleSequentialAllocationsBytes)
{
  u8 *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6;

  // 16 bytes
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr1, 16), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr1, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr1), 16);

  // 32 bytes
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr2, 32), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr2, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr2), 32);

  // 64 bytes
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr3, 64), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr3, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr3), 64);

  // 128 bytes
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr4, 128), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr4, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr4), 128);

  // 256 bytes
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr5, 256), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr5, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr5), 256);

  // 512 bytes
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr6, 512), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr6, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr6), 512);

  // Free in reverse order
  kdMemFreeWithSizeInfo(&ptr6);
  kdMemFreeWithSizeInfo(&ptr5);
  kdMemFreeWithSizeInfo(&ptr4);
  kdMemFreeWithSizeInfo(&ptr3);
  kdMemFreeWithSizeInfo(&ptr2);
  kdMemFreeWithSizeInfo(&ptr1);
}

TEST(MemoryAllocWithSizeInfoTest, BasicMultipleSequentialAllocationsKiloBytes)
{
  u8 *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6;

  // 1 KB
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr1, 1024 * 1), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr1, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr1), 1024 * 1);

  // 2 KB
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr2, 1024 * 2), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr2, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr2), 1024 * 2);

  // 4 KB
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr3, 1024 * 4), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr3, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr3), 1024 * 4);

  // 8 KB
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr4, 1024 * 8), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr4, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr4), 1024 * 8);

  // 16 KB
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr5, 1024 * 16), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr5, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr5), 1024 * 16);

  // 32 KB
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr6, 1024 * 32), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr6, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr6), 1024 * 32);

  // Free in reverse
  kdMemFreeWithSizeInfo(&ptr6);
  kdMemFreeWithSizeInfo(&ptr5);
  kdMemFreeWithSizeInfo(&ptr4);
  kdMemFreeWithSizeInfo(&ptr3);
  kdMemFreeWithSizeInfo(&ptr2);
  kdMemFreeWithSizeInfo(&ptr1);
}
