# file: set_compiler_flags.cmake
# author: Kumarjit Das
# date: 2025-05-24
# brief: KD library cmake compiler flags configuration file.

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


set(MSVC_WARNINGS /WX /W4 /w14242 /w14254 /w14263 /w14265 /w14287 /we4289 /w14296 /w14311 /w14545 /w14546 /w14547
    /w14549 /w14555 /w14619 /w14640 /w14826 /w14905 /w14906 /w14928 /permissive- /Za /Gy)

set(CLANG_WARNINGS -Werror -Wall -Wextra -Wpedantic -Wshadow -Wcast-align -Wconversion -Wsign-conversion
    -Wdouble-promotion -Wunused -Wnull-dereference)

set(GCC_WARNINGS ${CLANG_WARNINGS} -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op)

# Setting compiler warnings to the main target
if (MSVC)
  target_compile_options(${KD_LIBRARY_NAME} INTERFACE ${MSVC_WARNINGS})
  write_status("Setting compiler warnings for MSVC.")
elseif (CMAKE_C_COMPILER_ID MATCHES ".*Clang")
  target_compile_options(${KD_LIBRARY_NAME} INTERFACE ${CLANG_WARNINGS})
  write_status("Setting compiler warnings for Clang.")
elseif (CMAKE_C_COMPILER_ID STREQUAL "GNU")
  target_compile_options(${KD_LIBRARY_NAME} INTERFACE ${GCC_WARNINGS})
  write_status("Setting compiler warnings for GNU.")
else ()
  message(AUTHOR_WARNING "No compiler warnings set for ${KD_LIBRARY_NAME}")
endif ()
