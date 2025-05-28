# file: create_library.cmake
# author: Kumarjit Das
# date: 2025-05-24
# brief: KD library cmake library creation script.

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


# Adding the main library
add_library(${KD_LIBRARY_NAME} "")
write_status("Creating library: ${KD_LIBRARY_NAME}.")

# Setting an alias in `KD` namespace
add_library("KD::${KD_LIBRARY_NAME}" ALIAS ${KD_LIBRARY_NAME})
write_status("Adding alias to the library: KD::${KD_LIBRARY_NAME}.")

# Adding the mem library
#add_library(mem "")
#target_compile_definitions(mem INTERFACE KD_DLL=1)
#target_link_libraries(mem INTERFACE KD::${KD_LIBRARY_NAME})

# Setting the public include directory for the mem library
#target_include_directories(
#  ${MEM_LIBRARY_NAME} PUBLIC
#  $<BUILD_INTERFACE:${INCLUDE_DIR}>
#  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
#  $<INSTALL_INTERFACE:include>
#  )

# Setting an alias in `MEM` namespace
#add_library("KD::mem" ALIAS "mem")
#write_status("Adding alias to the 'mem' library: KD::mem.")
