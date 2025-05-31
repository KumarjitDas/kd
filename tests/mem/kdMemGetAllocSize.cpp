/**
 * @file kdMemGetAllocSize.cpp
 * @author Kumarjit Das
 * @date 2025-05-31
 * @brief kdMemGetAllocSize test file.
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


TEST(MemoryGetAllocSizeTest, BasicQueries)
{
  u8* ptr = static_cast<u8*>(null);

  // Null pointer should return size 0
  EXPECT_EQ(kdMemGetAllocSize(null), 0);

  // Allocate and check size
  EXPECT_EQ(kdMemAllocWithSizeInfo(&ptr, 64), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemGetAllocSize(ptr), 64);

  // Resize and check size
  u8* dst = static_cast<u8*>(null);
  EXPECT_EQ(kdMemReallocWithSizeInfo(&dst, 128, &ptr, 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
  ASSERT_NE(dst, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 128);

  // Free and check again
  EXPECT_EQ(kdMemFreeWithSizeInfo(&dst), KD_RESULT_SUCCESS);
  EXPECT_EQ(dst, null);
  EXPECT_EQ(kdMemGetAllocSize(dst), 0);
}
