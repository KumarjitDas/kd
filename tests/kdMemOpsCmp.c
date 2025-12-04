/**
 * @file kdMemOpsCmp.cpp
 * @author Kumarjit Das
 * @date 2025-06-09
 * @brief kdMemOpsCmp test file.
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


TEST(MemOpsCmpTest, ReturnsZeroIfEqual)
{
  kd_i32_t ptr1[] = {1, 2, 3, 4, 5};
  kd_i32_t ptr2[] = {1, 2, 3, 4, 5};

  EXPECT_EQ(kdMemOpsCmpI32(ptr1, ptr2, sizeof(ptr1) / KD_SZ_I32), 0);
}

TEST(MemOpsCmpTest, ReturnsNegativeIfFirstLess)
{
  kd_i32_t ptr1[] = {1, 2, 8, 4, 5};
  kd_i32_t ptr2[] = {1, 2, 3, 4, 5};

  EXPECT_EQ(kdMemOpsCmpI32(ptr1, ptr2, sizeof(ptr1) / KD_SZ_I32), 5);
}

TEST(MemOpsCmpTest, ReturnsPositiveIfFirstGreater)
{
  kd_i32_t ptr1[] = {1, 2, 3, 4, 5};
  kd_i32_t ptr2[] = {1, 2, 8, 4, 5};

  EXPECT_EQ(kdMemOpsCmpI32(ptr1, ptr2, sizeof(ptr1) / KD_SZ_I32), -5);
}

TEST(MemOpsCmpTest, HandlesNullPointersSafely)
{
  kd_i32_t   ptr1[16], ptr2[16];
  kd_usize_t len = sizeof(ptr1) / KD_SZ_I32;

  EXPECT_EQ(kdMemOpsCmpI32(kd_null, kd_null, 0), 0);
  EXPECT_EQ(kdMemOpsCmpI32(kd_null, kd_null, len), 0);
  EXPECT_EQ(kdMemOpsCmpI32(kd_null, ptr2, 0), -1);
  EXPECT_EQ(kdMemOpsCmpI32(kd_null, ptr2, len), -1);
  EXPECT_EQ(kdMemOpsCmpI32(ptr1, kd_null, 0), 1);
  EXPECT_EQ(kdMemOpsCmpI32(ptr1, kd_null, len), 1);
  EXPECT_EQ(kdMemOpsCmpI32(ptr1, ptr2, 0), 0);
}
