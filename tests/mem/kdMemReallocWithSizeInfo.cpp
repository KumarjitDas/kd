/**
 * @file kdMemReallocWithSizeInfo.cpp
 * @author Kumarjit Das
 * @date 2025-05-31
 * @brief kdMemReallocWithSizeInfo test file.
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


TEST(MemoryReallocWithSizeInfoTest, BasicArguments)
{
  u8* ptr = static_cast<u8*>(null);
  u8* dst = static_cast<u8*>(null);

  // All null
  EXPECT_EQ(kdMemReallocWithSizeInfo(null, 0, null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdMemReallocWithSizeInfo(null, 64, null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdMemReallocWithSizeInfo(null, 0, &ptr, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdMemReallocWithSizeInfo(null, 128, &ptr, 0), KD_RESULT_FAILURE);

  // Destination valid, source/destination data is junk
  dst = reinterpret_cast<u8*>(69);
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 0, null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(dst, null);

  dst = reinterpret_cast<u8*>(69);
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 64, null, 0), KD_RESULT_SUCCESS);
  EXPECT_EQ(dst != null, true);
  EXPECT_EQ(kdMemGetAllocSize(dst), 64);
  kdMemFreeWithSizeInfo(&dst);

  dst = reinterpret_cast<u8*>(69);
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 0, &ptr, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(dst, null);
}

TEST(MemoryReallocWithSizeInfoTest, BasicAllocationBytes)
{
  u8 *ptr = static_cast<u8*>(null), *dst = static_cast<u8*>(null);

  // Reallocate from 1 byte → 64 → 128
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 1), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr), 1);
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 64, &ptr, 1), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  ASSERT_NE(dst, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 64);
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 128, &ptr, 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  ASSERT_NE(dst, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 128);
  kdMemFreeWithSizeInfo(&dst);

  // Reallocate 64 → 128 → 256
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 64), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr), 64);
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 128, &ptr, 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  ASSERT_NE(dst, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 128);
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 256, &ptr, 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  ASSERT_NE(dst, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 256);
  kdMemFreeWithSizeInfo(&dst);

  // Reallocate 128 → 256 → 512
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 128), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 256, &ptr, 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  ASSERT_NE(dst, null);
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 512, &ptr, 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  ASSERT_NE(dst, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 512);
  kdMemFreeWithSizeInfo(&dst);
}

TEST(MemoryReallocWithSizeInfoTest, BasicAllocationKiloBytes)
{
  u8 *ptr = static_cast<u8*>(null), *dst = static_cast<u8*>(null);

  // 1 KB → 64 KB → 128 KB
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 1024 * 1), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 1024 * 64, &ptr, 1024 * 1), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  ASSERT_NE(dst, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 1024 * 64);
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 1024 * 128, &ptr, 1024 * 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  ASSERT_NE(dst, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 1024 * 128);
  kdMemFreeWithSizeInfo(&dst);

  // 64 KB → 128 KB → 256 KB
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 1024 * 64), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 1024 * 128, &ptr, 1024 * 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  ASSERT_NE(dst, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 1024 * 128);
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 1024 * 256, &ptr, 1024 * 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  ASSERT_NE(dst, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 1024 * 256);
  kdMemFreeWithSizeInfo(&dst);

  // 256 KB → 512 KB → 1 MB
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 1024 * 256), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 1024 * 512, &ptr, 1024 * 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  ASSERT_NE(dst, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 1024 * 512);
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 1024 * 1024, &ptr, 1024 * 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  ASSERT_NE(dst, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 1024 * 1024);
  kdMemFreeWithSizeInfo(&dst);
}

TEST(MemoryReallocWithSizeInfoTest, BasicAllocationMegaBytes)
{
  u8 *ptr = static_cast<u8*>(null), *dst = static_cast<u8*>(null);

  // 1 MB → 64 MB → 128 MB
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 1024 * 1024 * 1), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr), 1024 * 1024 * 1);

  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 1024 * 1024 * 64, &ptr, 1024 * 1024 * 1), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  ASSERT_NE(dst, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 1024 * 1024 * 64);

  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 1024 * 1024 * 128, &ptr, 1024 * 1024 * 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  ASSERT_NE(dst, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 1024 * 1024 * 128);

  // Downscale back to 64 MB → 32 MB → 1 MB
  ptr = dst;
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 1024 * 1024 * 64, &ptr, 1024 * 1024 * 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 1024 * 1024 * 64);

  ptr = dst;
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 1024 * 1024 * 32, &ptr, 1024 * 1024 * 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 1024 * 1024 * 32);

  ptr = dst;
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 1024 * 1024 * 1, &ptr, 1024 * 1024 * 32), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 1024 * 1024 * 1);

  kdMemFreeWithSizeInfo(&dst);
}

TEST(MemoryReallocWithSizeInfoTest, BasicMultipleSequentialReallocationsBytes)
{
  u8 *ptr = static_cast<u8*>(null), *dst = static_cast<u8*>(null);

  // 64 → 128 → 256 → 512
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 64), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 128, &ptr, 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  ASSERT_NE(dst, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 128);

  ptr = dst;
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 256, &ptr, 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  ASSERT_NE(dst, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 256);

  ptr = dst;
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 512, &ptr, 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  ASSERT_NE(dst, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 512);

  ptr = dst;
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 128, &ptr, 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  ASSERT_NE(dst, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 128);

  ptr = dst;
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 64, &ptr, 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  ASSERT_NE(dst, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 64);

  kdMemFreeWithSizeInfo(&dst);
}

TEST(MemoryReallocWithSizeInfoTest, BasicMultipleSequentialReallocationsKiloBytes)
{
  u8 *ptr = static_cast<u8*>(null), *dst = static_cast<u8*>(null);

  // 1 KB → 64 KB → 128 KB → 256 KB → 512 KB → 1 MB
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 1024 * 1), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 1024 * 64, &ptr, 1024 * 1), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  ASSERT_NE(dst, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 1024 * 64);

  ptr = dst;
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 1024 * 128, &ptr, 1024 * 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 1024 * 128);

  ptr = dst;
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 1024 * 256, &ptr, 1024 * 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 1024 * 256);

  ptr = dst;
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 1024 * 512, &ptr, 1024 * 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 1024 * 512);

  ptr = dst;
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 1024 * 1024, &ptr, 1024 * 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 1024 * 1024);

  // Now shrink back down to 64 KB
  ptr = dst;
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 1024 * 512, &ptr, 1024 * 1024), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 1024 * 512);

  ptr = dst;
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 1024 * 128, &ptr, 1024 * 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 1024 * 128);

  ptr = dst;
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 1024 * 64, &ptr, 1024 * 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 1024 * 64);

  kdMemFreeWithSizeInfo(&dst);
}
