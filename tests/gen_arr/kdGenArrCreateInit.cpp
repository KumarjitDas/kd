/**
 * @file kdGenArrCreateInit.cpp
 * @author Kumarjit Das
 * @date 2025-06-19
 * @brief kdGenArrCreateInit test file.
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


TEST(GenArrCreateInitTest, AllocatesMemoryCorrectly)
{
#if defined KD_ARCH_64BIT_INT
  kd_i64_t len = 16;
#else  /* !defined KD_ARCH_64BIT_INT */
  kd_i32_t len = 16;
#endif /* KD_ARCH_64BIT_INT */

  kd_i32_t val = 69;
  auto*    arr = static_cast<kd_i32_t*>(kdGenArrCreateInit(KD_SZ_I32, len, &val, kdMemAlloc));

  ASSERT_NE(arr, kd_null);
  EXPECT_EQ(kdGenArrGetElemSize(arr), KD_SZ_I32);

#if defined KD_ARCH_64BIT_INT
  EXPECT_EQ(kdGenArrGetMemSize(arr), KD_I64_C(KD_SZ_I32) * len);
#else  /* !defined KD_ARCH_64BIT_INT */
  EXPECT_EQ(kdGenArrGetMemSize(arr), KD_I32_C(KD_SZ_I32) * len);
#endif /* KD_ARCH_64BIT_INT */

  EXPECT_EQ(kdGenArrGetLen(arr), len);
#ifdef KD_ENDIAN_BIG
  EXPECT_EQ(kdGenArrIsLE(arr), kd_false);
  EXPECT_EQ(kdGenArrIsBE(arr), kd_true);
#else
  EXPECT_EQ(kdGenArrIsLE(arr), kd_true);
  EXPECT_EQ(kdGenArrIsBE(arr), kd_false);
#endif /* KD_ENDIAN_BIG */
  EXPECT_EQ(kdGenArrGetEnd(arr), arr + (len - 1));

  for (kd_usize_t i = 0; i < KD_USIZE_C(len); ++i)
  {
    EXPECT_EQ(arr[i], val);
  }

  EXPECT_EQ(kdGenArrDestroy(arr, kdMemFree), kd_true);
}

TEST(GenArrCreateInitTest, ChecksBounds)
{
  kd_i32_t *arr, val = 69;

  arr = static_cast<kd_i32_t*>(kdGenArrCreateInit(16777220, 16, &val, kdMemAlloc));
  ASSERT_EQ(arr, kd_null);

  arr = static_cast<kd_i32_t*>(kdGenArrCreateInit(KD_SZ_I32, KD_GEN_ARR_MAX_MEM_SZ, &val, kdMemAlloc));
  ASSERT_EQ(arr, kd_null);
}

TEST(GenArrCreateInitTest, HandlesNullPointers)
{
  kd_i32_t val = 69;

  EXPECT_EQ(kdGenArrCreateInit(4, 16, kd_null, nullptr), kd_null);
  EXPECT_EQ(kdGenArrCreateInit(4, 16, kd_null, kdMemAlloc), kd_null);
  EXPECT_EQ(kdGenArrCreateInit(4, 16, &val, nullptr), kd_null);
}

TEST(GenArrCreateInitTest, HandlesZeorSizes)
{
  kd_i32_t val = 69;

  EXPECT_EQ(kdGenArrCreateInit(0, 0, &val, kdMemAlloc), kd_null);
  EXPECT_EQ(kdGenArrCreateInit(0, 16, &val, kdMemAlloc), kd_null);
  EXPECT_EQ(kdGenArrCreateInit(4, 0, &val, kdMemAlloc), kd_null);
}
