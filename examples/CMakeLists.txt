# file: CMakeLists.txt
# author: Kumarjit Das
# date: 2025-05-24
# brief: KD library examples cmake file.

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


write_status("'examples' subdirectory added.")

# Get all .c files in the directory
file(GLOB ALL_C_FILES "*.c")

# Initialize an empty list to store file names without extensions
set(EXAMPLE_LIST "")

# Loop over each file and extract the name without extension
foreach (FILE_PATH ${ALL_C_FILES})
  get_filename_component(FILE_NAME_WE ${FILE_PATH} NAME_WE)
  list(APPEND EXAMPLE_LIST ${FILE_NAME_WE})
endforeach ()

# Loop through each item in the examples list
foreach (EXAMPLE_ITEM ${EXAMPLE_LIST})
  # Attaching library name in front of example item
  set(EXAMPLE_TARGET "${KD_PROJECT_NAME_LOWER}-${EXAMPLE_ITEM}")

  # Build an executable from the `EXAMPLE_ITEM` source
  add_executable(${EXAMPLE_TARGET} "${EXAMPLE_ITEM}.c")

  # Link the built executable with the main library
  target_link_libraries(${EXAMPLE_TARGET} PRIVATE "KD::${KD_LIBRARY_NAME}")
  target_link_libraries(${EXAMPLE_TARGET} PRIVATE "KD::${MEM_LIBRARY_NAME}")

  # Setting build postfixes for different build configurations
  set_target_properties(
    ${EXAMPLE_TARGET} PROPERTIES
    C_STANDARD 99
    DEBUG_POSTFIX "${KD_STATIC_POSTFIX}-d"
    RELEASE_POSTFIX "${KD_STATIC_POSTFIX}"
    MINSIZEREL_POSTFIX "${KD_STATIC_POSTFIX}-mr"
    RELWITHDEBINFO_POSTFIX "${KD_STATIC_POSTFIX}-rd"
    )

  # Check if the project builds shared libraries
  if (BUILD_SHARED_LIBS)
    set_target_properties(
      ${EXAMPLE_TARGET} PROPERTIES
      ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
      LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
      )
  endif ()

  write_status("Added example: ${EXAMPLE_TARGET}")
endforeach ()
