/**
 * @file kdMemAlloc.cpp
 * @author Kumarjit Das
 * @date 2025-05-31
 * @brief kdMemAlloc test file.
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
#include "kd/mem.h"
#include "gtest/gtest.h"


TEST(MemoryAllocationTest, BasicArguments)
{
  kd_u8_t *ptr;

  EXPECT_EQ(kdMemAlloc(kd_null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdMemAlloc(kd_null, 420000), KD_RESULT_FAILURE);
  EXPECT_EQ(kdMemAlloc(kd_null, 69), KD_RESULT_FAILURE);

  EXPECT_EQ(kdMemAlloc(&ptr, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(ptr, kd_null);

  EXPECT_EQ(kdMemAlloc(&ptr, 69000), KD_RESULT_SUCCESS);
  EXPECT_NE(ptr, kd_null);
}

TEST(MemoryAllocationTest, BasicAllocationBytes)
{
  kd_u8_t *ptr;

  EXPECT_EQ(kdMemAlloc(&ptr, 1), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  if (ptr != kd_null)
    kdMemFree(&ptr);

  EXPECT_EQ(kdMemAlloc(&ptr, 64), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  if (ptr != kd_null)
    kdMemFree(&ptr);

  EXPECT_EQ(kdMemAlloc(&ptr, 128), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  if (ptr != kd_null)
    kdMemFree(&ptr);

  EXPECT_EQ(kdMemAlloc(&ptr, 256), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  if (ptr != kd_null)
    kdMemFree(&ptr);

  EXPECT_EQ(kdMemAlloc(&ptr, 512), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  if (ptr != kd_null)
    kdMemFree(&ptr);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  if (ptr != kd_null)
    kdMemFree(&ptr);
}

TEST(MemoryAllocationTest, BasicAllocationKiloBytes)
{
  kd_u8_t *ptr;

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 1), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  if (ptr != kd_null)
    kdMemFree(&ptr);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 64), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  if (ptr != kd_null)
    kdMemFree(&ptr);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 128), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  if (ptr != kd_null)
    kdMemFree(&ptr);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 256), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  if (ptr != kd_null)
    kdMemFree(&ptr);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 512), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  if (ptr != kd_null)
    kdMemFree(&ptr);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 1024), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  if (ptr != kd_null)
    kdMemFree(&ptr);
}

TEST(MemoryAllocationTest, BasicAllocationMegaBytes)
{
  kd_u8_t *ptr;

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 1024 * 1), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  if (ptr != kd_null)
    kdMemFree(&ptr);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 1024 * 64), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  if (ptr != kd_null)
    kdMemFree(&ptr);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 1024 * 128), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  if (ptr != kd_null)
    kdMemFree(&ptr);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 1024 * 256), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  if (ptr != kd_null)
    kdMemFree(&ptr);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 1024 * 512), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  if (ptr != kd_null)
    kdMemFree(&ptr);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 1024 * 1024), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  if (ptr != kd_null)
    kdMemFree(&ptr);
}

TEST(MemoryAllocationTest, BasicMultipleSequentialAllocationsBytes)
{
  kd_u8_t *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9, *ptr10, *ptr11;

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

  ASSERT_NE(ptr1, kd_null);
  if (ptr1 != kd_null)
    kdMemFree(&ptr1);
  ASSERT_NE(ptr2, kd_null);
  if (ptr2 != kd_null)
    kdMemFree(&ptr2);
  ASSERT_NE(ptr3, kd_null);
  if (ptr3 != kd_null)
    kdMemFree(&ptr3);
  ASSERT_NE(ptr4, kd_null);
  if (ptr4 != kd_null)
    kdMemFree(&ptr4);
  ASSERT_NE(ptr5, kd_null);
  if (ptr5 != kd_null)
    kdMemFree(&ptr5);
  ASSERT_NE(ptr6, kd_null);
  if (ptr6 != kd_null)
    kdMemFree(&ptr6);
  ASSERT_NE(ptr7, kd_null);
  if (ptr7 != kd_null)
    kdMemFree(&ptr7);
  ASSERT_NE(ptr8, kd_null);
  if (ptr8 != kd_null)
    kdMemFree(&ptr8);
  ASSERT_NE(ptr9, kd_null);
  if (ptr9 != kd_null)
    kdMemFree(&ptr9);
  ASSERT_NE(ptr10, kd_null);
  if (ptr10 != kd_null)
    kdMemFree(&ptr10);
  ASSERT_NE(ptr11, kd_null);
  if (ptr11 != kd_null)
    kdMemFree(&ptr11);
}

TEST(MemoryAllocationTest, BasicMultipleSequentialAllocationsKiloBytes)
{
  kd_u8_t *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9, *ptr10, *ptr11;

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

  ASSERT_NE(ptr1, kd_null);
  if (ptr1 != kd_null)
    kdMemFree(&ptr1);
  ASSERT_NE(ptr2, kd_null);
  if (ptr2 != kd_null)
    kdMemFree(&ptr2);
  ASSERT_NE(ptr3, kd_null);
  if (ptr3 != kd_null)
    kdMemFree(&ptr3);
  ASSERT_NE(ptr4, kd_null);
  if (ptr4 != kd_null)
    kdMemFree(&ptr4);
  ASSERT_NE(ptr5, kd_null);
  if (ptr5 != kd_null)
    kdMemFree(&ptr5);
  ASSERT_NE(ptr6, kd_null);
  if (ptr6 != kd_null)
    kdMemFree(&ptr6);
  ASSERT_NE(ptr7, kd_null);
  if (ptr7 != kd_null)
    kdMemFree(&ptr7);
  ASSERT_NE(ptr8, kd_null);
  if (ptr8 != kd_null)
    kdMemFree(&ptr8);
  ASSERT_NE(ptr9, kd_null);
  if (ptr9 != kd_null)
    kdMemFree(&ptr9);
  ASSERT_NE(ptr10, kd_null);
  if (ptr10 != kd_null)
    kdMemFree(&ptr10);
  ASSERT_NE(ptr11, kd_null);
  if (ptr11 != kd_null)
    kdMemFree(&ptr11);
}

TEST(MemoryAllocationTest, BasicMultipleSequentialAllocationsMegaBytes)
{
  kd_u8_t *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9, *ptr10, *ptr11;

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

  ASSERT_NE(ptr1, kd_null);
  if (ptr1 != kd_null)
    kdMemFree(&ptr1);
  ASSERT_NE(ptr2, kd_null);
  if (ptr2 != kd_null)
    kdMemFree(&ptr2);
  ASSERT_NE(ptr3, kd_null);
  if (ptr3 != kd_null)
    kdMemFree(&ptr3);
  ASSERT_NE(ptr4, kd_null);
  if (ptr4 != kd_null)
    kdMemFree(&ptr4);
  ASSERT_NE(ptr5, kd_null);
  if (ptr5 != kd_null)
    kdMemFree(&ptr5);
  ASSERT_NE(ptr6, kd_null);
  if (ptr6 != kd_null)
    kdMemFree(&ptr6);
  ASSERT_NE(ptr7, kd_null);
  if (ptr7 != kd_null)
    kdMemFree(&ptr7);
  ASSERT_NE(ptr8, kd_null);
  if (ptr8 != kd_null)
    kdMemFree(&ptr8);
  ASSERT_NE(ptr9, kd_null);
  if (ptr9 != kd_null)
    kdMemFree(&ptr9);
  ASSERT_NE(ptr10, kd_null);
  if (ptr10 != kd_null)
    kdMemFree(&ptr10);
  ASSERT_NE(ptr11, kd_null);
  if (ptr11 != kd_null)
    kdMemFree(&ptr11);
}
