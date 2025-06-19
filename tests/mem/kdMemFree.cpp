/**
 * @file kdMemFree.cpp
 * @author Kumarjit Das
 * @date 2025-05-31
 * @brief kdMemFree test file.
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


TEST(kdMemoryDeallocationTest, BasicArguments) { EXPECT_EQ(kdMemFree(null), KD_RESULT_FAILURE); }

TEST(kdMemoryDeallocationTest, BasicDeallocationBytes)
{
  u8* ptr;

  EXPECT_EQ(kdMemAlloc(&ptr, 1), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemFree(&ptr), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);

  EXPECT_EQ(kdMemAlloc(&ptr, 64), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemFree(&ptr), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);

  EXPECT_EQ(kdMemAlloc(&ptr, 128), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemFree(&ptr), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);

  EXPECT_EQ(kdMemAlloc(&ptr, 256), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemFree(&ptr), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);

  EXPECT_EQ(kdMemAlloc(&ptr, 512), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemFree(&ptr), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemFree(&ptr), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
}

TEST(kdMemoryDeallocationTest, BasicDeallocationKiloBytes)
{
  u8* ptr;

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 1), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemFree(&ptr), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 64), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemFree(&ptr), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 128), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemFree(&ptr), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 256), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemFree(&ptr), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 512), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemFree(&ptr), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 1024), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemFree(&ptr), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
}

TEST(kdMemoryDeallocationTest, BasicDeallocationMegaBytes)
{
  u8* ptr;

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 1024 * 1), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemFree(&ptr), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 1024 * 64), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemFree(&ptr), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 1024 * 128), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemFree(&ptr), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 1024 * 256), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemFree(&ptr), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 1024 * 512), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemFree(&ptr), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 1024 * 1024), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, null);
  EXPECT_EQ(kdMemFree(&ptr), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, null);
}

TEST(kdMemoryDeallocationTest, BasicMultipleSequentialDeallocationsBytes)
{
  u8 *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9, *ptr10, *ptr11;

  EXPECT_EQ(kdMemAlloc(&ptr1, 1), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr2, 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr3, 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr4, 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr5, 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr6, 1024), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr7, 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr8, 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr9, 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr10, 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr11, 1), KD_RESULT_SUCCESS);

  ASSERT_NE(ptr1, null);
  EXPECT_EQ(kdMemFree(&ptr1), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr1, null);

  ASSERT_NE(ptr2, null);
  EXPECT_EQ(kdMemFree(&ptr2), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr2, null);

  ASSERT_NE(ptr3, null);
  EXPECT_EQ(kdMemFree(&ptr3), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr3, null);

  ASSERT_NE(ptr4, null);
  EXPECT_EQ(kdMemFree(&ptr4), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr4, null);

  ASSERT_NE(ptr5, null);
  EXPECT_EQ(kdMemFree(&ptr5), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr5, null);

  ASSERT_NE(ptr6, null);
  EXPECT_EQ(kdMemFree(&ptr6), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr6, null);

  ASSERT_NE(ptr7, null);
  EXPECT_EQ(kdMemFree(&ptr7), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr7, null);

  ASSERT_NE(ptr8, null);
  EXPECT_EQ(kdMemFree(&ptr8), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr8, null);

  ASSERT_NE(ptr9, null);
  EXPECT_EQ(kdMemFree(&ptr9), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr9, null);

  ASSERT_NE(ptr10, null);
  EXPECT_EQ(kdMemFree(&ptr10), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr10, null);

  ASSERT_NE(ptr11, null);
  EXPECT_EQ(kdMemFree(&ptr11), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr11, null);
}

TEST(kdMemoryDeallocationTest, BasicMultipleSequentialDeallocationsKiloBytes)
{
  u8 *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9, *ptr10, *ptr11;

  EXPECT_EQ(kdMemAlloc(&ptr1, 1024 * 1), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr2, 1024 * 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr3, 1024 * 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr4, 1024 * 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr5, 1024 * 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr6, 1024 * 1024), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr7, 1024 * 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr8, 1024 * 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr9, 1024 * 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr10, 1024 * 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr11, 1024 * 1), KD_RESULT_SUCCESS);

  ASSERT_NE(ptr1, null);
  EXPECT_EQ(kdMemFree(&ptr1), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr1, null);

  ASSERT_NE(ptr2, null);
  EXPECT_EQ(kdMemFree(&ptr2), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr2, null);

  ASSERT_NE(ptr3, null);
  EXPECT_EQ(kdMemFree(&ptr3), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr3, null);

  ASSERT_NE(ptr4, null);
  EXPECT_EQ(kdMemFree(&ptr4), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr4, null);

  ASSERT_NE(ptr5, null);
  EXPECT_EQ(kdMemFree(&ptr5), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr5, null);

  ASSERT_NE(ptr6, null);
  EXPECT_EQ(kdMemFree(&ptr6), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr6, null);

  ASSERT_NE(ptr7, null);
  EXPECT_EQ(kdMemFree(&ptr7), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr7, null);

  ASSERT_NE(ptr8, null);
  EXPECT_EQ(kdMemFree(&ptr8), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr8, null);

  ASSERT_NE(ptr9, null);
  EXPECT_EQ(kdMemFree(&ptr9), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr9, null);

  ASSERT_NE(ptr10, null);
  EXPECT_EQ(kdMemFree(&ptr10), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr10, null);

  ASSERT_NE(ptr11, null);
  EXPECT_EQ(kdMemFree(&ptr11), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr11, null);
}

TEST(kdMemoryDeallocationTest, BasicMultipleSequentialDeallocationsMegaBytes)
{
  u8 *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9, *ptr10, *ptr11;

  EXPECT_EQ(kdMemAlloc(&ptr1, 1024 * 1024 * 1), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr2, 1024 * 1024 * 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr3, 1024 * 1024 * 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr4, 1024 * 1024 * 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr5, 1024 * 1024 * 32), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr6, 1024 * 1024 * 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr7, 1024 * 1024 * 32), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr8, 1024 * 1024 * 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr9, 1024 * 1024 * 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr10, 1024 * 1024 * 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemAlloc(&ptr11, 1024 * 1024 * 1), KD_RESULT_SUCCESS);

  ASSERT_NE(ptr1, null);
  EXPECT_EQ(kdMemFree(&ptr1), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr1, null);

  ASSERT_NE(ptr2, null);
  EXPECT_EQ(kdMemFree(&ptr2), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr2, null);

  ASSERT_NE(ptr3, null);
  EXPECT_EQ(kdMemFree(&ptr3), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr3, null);

  ASSERT_NE(ptr4, null);
  EXPECT_EQ(kdMemFree(&ptr4), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr4, null);

  ASSERT_NE(ptr5, null);
  EXPECT_EQ(kdMemFree(&ptr5), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr5, null);

  ASSERT_NE(ptr6, null);
  EXPECT_EQ(kdMemFree(&ptr6), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr6, null);

  ASSERT_NE(ptr7, null);
  EXPECT_EQ(kdMemFree(&ptr7), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr7, null);

  ASSERT_NE(ptr8, null);
  EXPECT_EQ(kdMemFree(&ptr8), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr8, null);

  ASSERT_NE(ptr9, null);
  EXPECT_EQ(kdMemFree(&ptr9), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr9, null);

  ASSERT_NE(ptr10, null);
  EXPECT_EQ(kdMemFree(&ptr10), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr10, null);

  ASSERT_NE(ptr11, null);
  EXPECT_EQ(kdMemFree(&ptr11), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr11, null);
}
