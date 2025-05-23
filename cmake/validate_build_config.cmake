# file: validate_build_config.cmake
# author: Kumarjit Das
# date: 2025-05-24
# brief: KD library cmake build configuration file.

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


write_status("Validating build configuration...")

if ("${CMAKE_GENERATOR}" STREQUAL "Ninja Multi-Config")
  set(VALID_BUILD_TYPES "Release" "Debug" "RelWithDebInfo")
else ()
  set(VALID_BUILD_TYPES "Release" "Debug" "MinSizeRel" "RelWithDebInfo")
endif ()

# Validate build configuration
if (NOT CMAKE_CONFIGURATION_TYPES)
  # Setting the default build type to release
  if (${CMAKE_BUILD_TYPE} STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build configuration" FORCE)
  endif ()

  # Checking validity of build type in multiple build configuration
  list(FIND VALID_BUILD_TYPES ${CMAKE_BUILD_TYPE} INDEX)
  if (${INDEX} MATCHES -1)
    message(FATAL_ERROR "Invalid build type. Valid build types are: ${VALID_BUILD_TYPES}")
  endif ()

  # Setting all valid build type in multiple build configuration
  if (DEFINED CMAKE_BUILD_TYPE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${VALID_BUILD_TYPES})
  endif ()
endif ()
