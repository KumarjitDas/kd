/**
 * @file kdMemRealloc.cpp
 * @author Kumarjit Das
 * @date 2025-05-31
 * @brief kdMemRealloc test file.
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


TEST(MemoryReallocationTest, BasicArguments)
{
  kd_u8_t *ptr, *dst;

  EXPECT_EQ(kdMemRealloc(kd_null, 0, kd_null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdMemRealloc(kd_null, 64, kd_null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdMemRealloc(kd_null, 0, &ptr, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(kdMemRealloc(kd_null, 128, &ptr, 0), KD_RESULT_FAILURE);

  dst = reinterpret_cast<kd_u8_t *>(69);
  EXPECT_EQ(kdMemRealloc(&dst, 0, kd_null, 0), KD_RESULT_FAILURE);
  EXPECT_EQ(dst, kd_null);

  dst = reinterpret_cast<kd_u8_t *>(69);
  EXPECT_EQ(kdMemRealloc(&dst, 64, kd_null, 0), KD_RESULT_SUCCESS);
  EXPECT_NE(dst, kd_null);
}

TEST(MemoryReallocationTest, BasicAllocationBytes)
{
  kd_u8_t *ptr, *dst;

  EXPECT_EQ(kdMemAlloc(&ptr, 1), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 64, &ptr, 1), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 128, &ptr, 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  if (dst != kd_null)
    kdMemFree(&dst);

  EXPECT_EQ(kdMemAlloc(&ptr, 64), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 128, &ptr, 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 256, &ptr, 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  if (dst != kd_null)
    kdMemFree(&dst);

  EXPECT_EQ(kdMemAlloc(&ptr, 128), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 256, &ptr, 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 512, &ptr, 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  if (dst != kd_null)
    kdMemFree(&dst);

  EXPECT_EQ(kdMemAlloc(&ptr, 256), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 512, &ptr, 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 256, &ptr, 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  if (dst != kd_null)
    kdMemFree(&dst);

  EXPECT_EQ(kdMemAlloc(&ptr, 512), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 256, &ptr, 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 128, &ptr, 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  if (dst != kd_null)
    kdMemFree(&dst);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 128, &ptr, 1024), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 64, &ptr, 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  if (dst != kd_null)
    kdMemFree(&dst);
}

TEST(MemoryReallocationTest, BasicAllocationKiloBytes)
{
  kd_u8_t *ptr, *dst;

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 1), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 1024 * 64, &ptr, 1024 * 1), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 1024 * 128, &ptr, 1024 * 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  if (dst != kd_null)
    kdMemFree(&dst);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 64), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 1024 * 128, &ptr, 1024 * 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 1024 * 256, &ptr, 1024 * 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  if (dst != kd_null)
    kdMemFree(&dst);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 128), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 1024 * 256, &ptr, 1024 * 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 1024 * 512, &ptr, 1024 * 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  if (dst != kd_null)
    kdMemFree(&dst);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 256), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 1024 * 512, &ptr, 1024 * 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 1024 * 256, &ptr, 1024 * 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  if (dst != kd_null)
    kdMemFree(&dst);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 512), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 1024 * 256, &ptr, 1024 * 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 1024 * 128, &ptr, 1024 * 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  if (dst != kd_null)
    kdMemFree(&dst);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 1024), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 1024 * 128, &ptr, 1024 * 1024), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 1024 * 64, &ptr, 1024 * 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  if (dst != kd_null)
    kdMemFree(&dst);
}

TEST(MemoryReallocationTest, BasicAllocationMegaBytes)
{
  kd_u8_t *ptr, *dst;

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 1024 * 1), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 1024 * 1024 * 64, &ptr, 1024 * 1024 * 1), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 1024 * 1024 * 128, &ptr, 1024 * 1024 * 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  if (dst != kd_null)
    kdMemFree(&dst);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 1024 * 64), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 1024 * 1024 * 128, &ptr, 1024 * 1024 * 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 1024 * 1024 * 256, &ptr, 1024 * 1024 * 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  if (dst != kd_null)
    kdMemFree(&dst);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 1024 * 128), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 1024 * 1024 * 256, &ptr, 1024 * 1024 * 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 1024 * 1024 * 512, &ptr, 1024 * 1024 * 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  if (dst != kd_null)
    kdMemFree(&dst);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 1024 * 256), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 1024 * 1024 * 512, &ptr, 1024 * 1024 * 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 1024 * 1024 * 256, &ptr, 1024 * 1024 * 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  if (dst != kd_null)
    kdMemFree(&dst);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 1024 * 512), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 1024 * 1024 * 256, &ptr, 1024 * 1024 * 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 1024 * 1024 * 128, &ptr, 1024 * 1024 * 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  if (dst != kd_null)
    kdMemFree(&dst);

  EXPECT_EQ(kdMemAlloc(&ptr, 1024 * 1024 * 1024), KD_RESULT_SUCCESS);
  ASSERT_NE(ptr, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 1024 * 1024 * 128, &ptr, 1024 * 1024 * 1024), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  EXPECT_EQ(kdMemRealloc(&dst, 1024 * 1024 * 64, &ptr, 1024 * 1024 * 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr, kd_null);
  ASSERT_NE(dst, kd_null);
  if (dst != kd_null)
    kdMemFree(&dst);
}

TEST(MemoryReallocationTest, BasicMultipleSequentialReallocationsBytes)
{
  kd_u8_t *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9, *ptr10, *ptr11;
  kd_u8_t *dst1, *dst2, *dst3, *dst4, *dst5, *dst6, *dst7, *dst8, *dst9, *dst10, *dst11;

  EXPECT_EQ(kdMemAlloc(&ptr1, 1), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemRealloc(&dst1, 64, &ptr1, 1), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr1, kd_null);
  ASSERT_NE(dst1, kd_null);

  ptr1 = dst1;
  EXPECT_EQ(kdMemRealloc(&dst1, 128, &ptr1, 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr1, kd_null);
  ASSERT_NE(dst1, kd_null);

  EXPECT_EQ(kdMemAlloc(&ptr2, 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemRealloc(&dst2, 128, &ptr2, 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr2, kd_null);
  ASSERT_NE(dst2, kd_null);

  ptr2 = dst2;
  EXPECT_EQ(kdMemRealloc(&dst2, 256, &ptr2, 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr2, kd_null);
  ASSERT_NE(dst2, kd_null);

  EXPECT_EQ(kdMemAlloc(&ptr3, 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemRealloc(&dst3, 256, &ptr3, 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr3, kd_null);
  ASSERT_NE(dst3, kd_null);

  ptr3 = dst3;
  EXPECT_EQ(kdMemRealloc(&dst3, 512, &ptr3, 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr3, kd_null);
  ASSERT_NE(dst3, kd_null);

  EXPECT_EQ(kdMemAlloc(&ptr4, 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemRealloc(&dst4, 512, &ptr4, 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr4, kd_null);
  ASSERT_NE(dst4, kd_null);

  ptr4 = dst4;
  EXPECT_EQ(kdMemRealloc(&dst4, 1024, &ptr4, 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr4, kd_null);
  ASSERT_NE(dst4, kd_null);

  EXPECT_EQ(kdMemAlloc(&ptr5, 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemRealloc(&dst5, 256, &ptr5, 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr5, kd_null);
  ASSERT_NE(dst5, kd_null);

  ptr5 = dst5;
  EXPECT_EQ(kdMemRealloc(&dst5, 128, &ptr5, 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr5, kd_null);
  ASSERT_NE(dst5, kd_null);

  EXPECT_EQ(kdMemAlloc(&ptr6, 1024), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemRealloc(&dst6, 512, &ptr6, 1024), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr6, kd_null);
  ASSERT_NE(dst6, kd_null);

  ptr6 = dst6;
  EXPECT_EQ(kdMemRealloc(&dst6, 256, &ptr6, 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr6, kd_null);
  ASSERT_NE(dst6, kd_null);

  EXPECT_EQ(kdMemAlloc(&ptr7, 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemRealloc(&dst7, 256, &ptr7, 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr7, kd_null);
  ASSERT_NE(dst7, kd_null);

  ptr7 = dst7;
  EXPECT_EQ(kdMemRealloc(&dst7, 128, &ptr7, 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr7, kd_null);
  ASSERT_NE(dst7, kd_null);

  EXPECT_EQ(kdMemAlloc(&ptr8, 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemRealloc(&dst8, 128, &ptr8, 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr8, kd_null);
  ASSERT_NE(dst8, kd_null);

  ptr8 = dst8;
  EXPECT_EQ(kdMemRealloc(&dst8, 64, &ptr8, 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr8, kd_null);
  ASSERT_NE(dst8, kd_null);

  EXPECT_EQ(kdMemAlloc(&ptr9, 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemRealloc(&dst9, 64, &ptr9, 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr9, kd_null);
  ASSERT_NE(dst9, kd_null);

  ptr9 = dst9;
  EXPECT_EQ(kdMemRealloc(&dst9, 32, &ptr9, 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr9, kd_null);
  ASSERT_NE(dst9, kd_null);

  EXPECT_EQ(kdMemAlloc(&ptr10, 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemRealloc(&dst10, 32, &ptr10, 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr10, kd_null);
  ASSERT_NE(dst10, kd_null);

  ptr10 = dst10;
  EXPECT_EQ(kdMemRealloc(&dst10, 16, &ptr10, 32), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr10, kd_null);
  ASSERT_NE(dst10, kd_null);

  EXPECT_EQ(kdMemAlloc(&ptr11, 32), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemRealloc(&dst11, 16, &ptr11, 32), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr11, kd_null);
  ASSERT_NE(dst11, kd_null);

  ptr11 = dst11;
  EXPECT_EQ(kdMemRealloc(&dst11, 1, &ptr11, 16), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr11, kd_null);
  ASSERT_NE(dst11, kd_null);

  if (dst1 != kd_null)
    kdMemFree(&dst1);
  if (dst2 != kd_null)
    kdMemFree(&dst2);
  if (dst3 != kd_null)
    kdMemFree(&dst3);
  if (dst4 != kd_null)
    kdMemFree(&dst4);
  if (dst5 != kd_null)
    kdMemFree(&dst5);
  if (dst6 != kd_null)
    kdMemFree(&dst6);
  if (dst7 != kd_null)
    kdMemFree(&dst7);
  if (dst8 != kd_null)
    kdMemFree(&dst8);
  if (dst9 != kd_null)
    kdMemFree(&dst9);
  if (dst10 != kd_null)
    kdMemFree(&dst10);
  if (dst11 != kd_null)
    kdMemFree(&dst11);
}

TEST(MemoryReallocationTest, BasicMultipleSequentialReallocationsKiloBytes)
{
  kd_u8_t *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9, *ptr10, *ptr11;
  kd_u8_t *dst1, *dst2, *dst3, *dst4, *dst5, *dst6, *dst7, *dst8, *dst9, *dst10, *dst11;

  EXPECT_EQ(kdMemAlloc(&ptr1, 1024 * 1), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemRealloc(&dst1, 1024 * 64, &ptr1, 1024 * 1), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr1, kd_null);
  ASSERT_NE(dst1, kd_null);

  ptr1 = dst1;
  EXPECT_EQ(kdMemRealloc(&dst1, 1024 * 128, &ptr1, 1024 * 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr1, kd_null);
  ASSERT_NE(dst1, kd_null);

  EXPECT_EQ(kdMemAlloc(&ptr2, 1024 * 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemRealloc(&dst2, 1024 * 128, &ptr2, 1024 * 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr2, kd_null);
  ASSERT_NE(dst2, kd_null);

  ptr2 = dst2;
  EXPECT_EQ(kdMemRealloc(&dst2, 1024 * 256, &ptr2, 1024 * 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr2, kd_null);
  ASSERT_NE(dst2, kd_null);

  EXPECT_EQ(kdMemAlloc(&ptr3, 1024 * 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemRealloc(&dst3, 1024 * 256, &ptr3, 1024 * 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr3, kd_null);
  ASSERT_NE(dst3, kd_null);

  ptr3 = dst3;
  EXPECT_EQ(kdMemRealloc(&dst3, 1024 * 512, &ptr3, 1024 * 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr3, kd_null);
  ASSERT_NE(dst3, kd_null);

  EXPECT_EQ(kdMemAlloc(&ptr4, 1024 * 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemRealloc(&dst4, 1024 * 512, &ptr4, 1024 * 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr4, kd_null);
  ASSERT_NE(dst4, kd_null);

  ptr4 = dst4;
  EXPECT_EQ(kdMemRealloc(&dst4, 1024 * 1024, &ptr4, 1024 * 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr4, kd_null);
  ASSERT_NE(dst4, kd_null);

  EXPECT_EQ(kdMemAlloc(&ptr5, 1024 * 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemRealloc(&dst5, 1024 * 256, &ptr5, 1024 * 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr5, kd_null);
  ASSERT_NE(dst5, kd_null);

  ptr5 = dst5;
  EXPECT_EQ(kdMemRealloc(&dst5, 1024 * 128, &ptr5, 1024 * 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr5, kd_null);
  ASSERT_NE(dst5, kd_null);

  EXPECT_EQ(kdMemAlloc(&ptr6, 1024 * 1024), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemRealloc(&dst6, 1024 * 512, &ptr6, 1024 * 1024), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr6, kd_null);
  ASSERT_NE(dst6, kd_null);

  ptr6 = dst6;
  EXPECT_EQ(kdMemRealloc(&dst6, 1024 * 256, &ptr6, 1024 * 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr6, kd_null);
  ASSERT_NE(dst6, kd_null);

  EXPECT_EQ(kdMemAlloc(&ptr7, 1024 * 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemRealloc(&dst7, 1024 * 256, &ptr7, 1024 * 512), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr7, kd_null);
  ASSERT_NE(dst7, kd_null);

  ptr7 = dst7;
  EXPECT_EQ(kdMemRealloc(&dst7, 1024 * 128, &ptr7, 1024 * 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr7, kd_null);
  ASSERT_NE(dst7, kd_null);

  EXPECT_EQ(kdMemAlloc(&ptr8, 1024 * 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemRealloc(&dst8, 1024 * 128, &ptr8, 1024 * 256), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr8, kd_null);
  ASSERT_NE(dst8, kd_null);

  ptr8 = dst8;
  EXPECT_EQ(kdMemRealloc(&dst8, 1024 * 64, &ptr8, 1024 * 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr8, kd_null);
  ASSERT_NE(dst8, kd_null);

  EXPECT_EQ(kdMemAlloc(&ptr9, 1024 * 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemRealloc(&dst9, 1024 * 64, &ptr9, 1024 * 128), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr9, kd_null);
  ASSERT_NE(dst9, kd_null);

  ptr9 = dst9;
  EXPECT_EQ(kdMemRealloc(&dst9, 1024 * 32, &ptr9, 1024 * 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr9, kd_null);
  ASSERT_NE(dst9, kd_null);

  EXPECT_EQ(kdMemAlloc(&ptr10, 1024 * 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemRealloc(&dst10, 1024 * 32, &ptr10, 1024 * 64), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr10, kd_null);
  ASSERT_NE(dst10, kd_null);

  ptr10 = dst10;
  EXPECT_EQ(kdMemRealloc(&dst10, 1024 * 16, &ptr10, 1024 * 32), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr10, kd_null);
  ASSERT_NE(dst10, kd_null);

  EXPECT_EQ(kdMemAlloc(&ptr11, 1024 * 32), KD_RESULT_SUCCESS);
  EXPECT_EQ(kdMemRealloc(&dst11, 1024 * 16, &ptr11, 1024 * 32), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr11, kd_null);
  ASSERT_NE(dst11, kd_null);

  ptr11 = dst11;
  EXPECT_EQ(kdMemRealloc(&dst11, 1024 * 1, &ptr11, 1024 * 16), KD_RESULT_SUCCESS);
  EXPECT_EQ(ptr11, kd_null);
  ASSERT_NE(dst11, kd_null);

  if (dst1 != kd_null)
    kdMemFree(&dst1);
  if (dst2 != kd_null)
    kdMemFree(&dst2);
  if (dst3 != kd_null)
    kdMemFree(&dst3);
  if (dst4 != kd_null)
    kdMemFree(&dst4);
  if (dst5 != kd_null)
    kdMemFree(&dst5);
  if (dst6 != kd_null)
    kdMemFree(&dst6);
  if (dst7 != kd_null)
    kdMemFree(&dst7);
  if (dst8 != kd_null)
    kdMemFree(&dst8);
  if (dst9 != kd_null)
    kdMemFree(&dst9);
  if (dst10 != kd_null)
    kdMemFree(&dst10);
  if (dst11 != kd_null)
    kdMemFree(&dst11);
}
