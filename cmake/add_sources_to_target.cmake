# file: add_sources_to_target.cmake
# author: Kumarjit Das
# date: 2025-05-25
# brief: KD library cmake add target sources script.

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


write_status("Adding sources to the main library target...")

# Common include files for all sublibraries
set(COMMON_INCLUDE_FILES
    "${CMAKE_CURRENT_BINARY_DIR}/include/kd/version.h"
    "${INCLUDE_DIR}/kd/defs.h"
    "${INCLUDE_DIR}/kd/fixed_width.h"
    "${INCLUDE_DIR}/kd/floating_point.h"
    "${INCLUDE_DIR}/kd/eltype.h"
    "${INCLUDE_DIR}/kd/dec.h"
    "${INCLUDE_DIR}/kd/any.h"
    "${INCLUDE_DIR}/kd/object.h"
)

# Common include files for all internal sublibraries
set(INTERNAL_COMMON_INCLUDE_FILES ${COMMON_INCLUDE_FILES})
list(APPEND INTERNAL_COMMON_INCLUDE_FILES
     "${INCLUDE_DIR}/_internal/common.h"
)

# Output object list
set(OBJECT_LIBS "")

# List of individual libraries to be build from each source
set(LIB_NAMES
    "mem"
    "mem_algn"
    "gen_mem_ops"
    "mem_ops"
    "gen_arr"
    "arr"
)

# List of individual internal libraries to be build from each source
set(INTERNAL_LIB_NAMES
    "gen_mem_ops_sn"
    "gen_arr_sn"
)

# Include and source file lists to be installed
set(INCLUDE_FILES ${COMMON_INCLUDE_FILES})
set(SRC_FILES "")

# Build all the library objects
foreach (LIB_NAME ${LIB_NAMES})
  set(INCLUDE_FILE "${INCLUDE_DIR}/kd/${LIB_NAME}.h")
  set(SRC_FILE "${SRC_DIR}/kd/${LIB_NAME}.c")

  # Create the object
  add_library(${LIB_NAME} OBJECT ${COMMON_INCLUDE_FILES} ${INCLUDE_FILE} ${SRC_FILE})
  target_compile_definitions(${LIB_NAME} INTERFACE KD_DLL=1)

  # Use the project C standard
  set_target_properties(${LIB_NAME} PROPERTIES
                        C_STANDARD ${KD_C_STANDARD}
                        C_STANDARD_REQUIRED YES
                        C_EXTENSIONS OFF
  )

  # Add the include dirs to the object target
  target_include_directories(${LIB_NAME} PUBLIC
                             $<BUILD_INTERFACE:${INCLUDE_DIR}>
                             $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
                             $<INSTALL_INTERFACE:include>
  )

  # Put the new object in the object list
  list(APPEND OBJECT_LIBS $<TARGET_OBJECTS:${LIB_NAME}>)

  # Put the include and sources to the install list
  list(APPEND INCLUDE_FILES ${INCLUDE_FILE})
  list(APPEND SRC_FILES ${SRC_FILE})
endforeach ()

# Build all the internal library objects
foreach (INTERNAL_LIB_NAME ${INTERNAL_LIB_NAMES})
  set(INCLUDE_FILE "${INCLUDE_DIR}/_internal/${INTERNAL_LIB_NAME}.h")
  set(SRC_FILE "${SRC_DIR}/_internal/${INTERNAL_LIB_NAME}.c")

  # Set the internal library name
  set(LIB_NAME "_${INTERNAL_LIB_NAME}")

  # Create the object
  add_library(${LIB_NAME} OBJECT ${INTERNAL_COMMON_INCLUDE_FILES} ${INCLUDE_FILE} ${SRC_FILE})
  target_compile_definitions(${LIB_NAME} INTERFACE KD_DLL=1)

  # Use the project C standard
  set_target_properties(${LIB_NAME} PROPERTIES
                        C_STANDARD ${KD_C_STANDARD}
                        C_STANDARD_REQUIRED YES
                        C_EXTENSIONS OFF
  )

  # Add the include dirs to the object target
  target_include_directories(${LIB_NAME} PUBLIC
                             $<BUILD_INTERFACE:${INCLUDE_DIR}>
                             $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
                             $<INSTALL_INTERFACE:include>
  )

  # Put the new object in the object list
  list(APPEND OBJECT_LIBS $<TARGET_OBJECTS:${LIB_NAME}>)
endforeach ()

# Link with the main library target
target_link_libraries(${KD_LIBRARY_NAME} PRIVATE ${OBJECT_LIBS})

# Setting the install destination for include and source file
install(FILES ${INCLUDE_FILES} DESTINATION "include")
# install(FILES ${SRC_FILES} DESTINATION "src")
