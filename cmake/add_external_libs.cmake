# file: add_external_libs.cmake
# author: Kumarjit Das
# date: 2025-05-31
# brief: KD library cmake external libraries fetcher script.

# LICENSE: BSD 3-Clause License
#
# Copyright (c) 2025, Kumarjit Das.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
#
# * Neither the name of the copyright holder nor the names of its
#   contributors may be used to endorse or promote products derived from
#   this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


# Fetch all the external libraries
include(FetchContent)

write_status("Adding external libraries...")

set(_GTEST_LIB googletest)
set(_GTEST_VER 1.14.0)

# Check if the parent project is this project or not
if (${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
  write_status("Enabling C++ compilation as '${_GTEST_LIB}' requires it.")
  enable_language(CXX)

  write_status("Fetching external library: ${_GTEST_LIB}")

  FetchContent_Declare(
    ${_GTEST_LIB}
    URL "https://github.com/google/${_GTEST_LIB}/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip"
    SOURCE_DIR ${CMAKE_BINARY_DIR}/external/${_GTEST_LIB}
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )

  # For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

  FetchContent_MakeAvailable(${_GTEST_LIB})
endif ()
