# file: add_os_utils_library.cmake
# author: Kumarjit Das
# date: 2025-05-31
# brief: _os_utils library configuration script.

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


# Adding the _os_utils library
add_library(_os_utils "")
target_compile_definitions(_os_utils INTERFACE KD_DLL=1)

# Use the project C standard
set_target_properties(_os_utils PROPERTIES
                      C_STANDARD ${KD_C_STANDARD}
                      C_STANDARD_REQUIRED YES
                      C_EXTENSIONS OFF
)

# Add the include dirs to the object target
target_include_directories(
  _os_utils PUBLIC
  $<BUILD_INTERFACE:${INCLUDE_DIR}>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# Link with the main library target
target_link_libraries(${KD_LIBRARY_NAME} PRIVATE _os_utils)

# Adding the version header file to the _os_utils target
target_sources(_os_utils PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/include/kd/version.h")

# Adding the _os_utils target to the export rules
install(TARGETS _os_utils EXPORT ${KD_PROJECT_NAME_LOWER}-targets)

set(INCLUDE_FILES
    "${INCLUDE_DIR}/_os_utils/common.h"
    "${INCLUDE_DIR}/_os_utils/mem.h")
set(SRC_FILES
    "${SRC_DIR}/_os_utils/mem.c")

#[[if (KD_TARGET_OS STREQUAL "Windows")
  if (KD_TARGET_ARCH STREQUAL "x86" OR KD_TARGET_ARCH STREQUAL "arm32")
    set(SRC_FILES
        "${SRC_DIR}/_os_utils/mem/win32.c")
  elseif (KD_TARGET_ARCH STREQUAL "x64" OR KD_TARGET_ARCH STREQUAL "arm64")
    set(SRC_FILES
        "${SRC_DIR}/_os_utils/mem/win64.c")
  endif ()
endif ()]]

# Adding the include file to the _os_utils target
target_sources(_os_utils PRIVATE ${INCLUDE_FILES})

# Adding the source files to the _os_utils target
target_sources(_os_utils PRIVATE ${SRC_FILES})
