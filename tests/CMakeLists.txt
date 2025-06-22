# file: CMakeLists.txt
# author: Kumarjit Das
# date: 2025-05-31
# brief: KD library tests cmake file.

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


write_status("'tests' subdirectory added.")

include(GoogleTest)

# Define all the subdirectories that contain the examples
set(TEST_SUBDIRS
    "mem"
    "mem_algn"
    "gen_mem_ops"
    "mem_ops"
    "gen_arr"
    "arr"
)

# Create groups
foreach (TEST_SUBDIR IN LISTS TEST_SUBDIRS)
  set(GROUP_${TEST_SUBDIR} "")
endforeach ()

# Get all .cpp files in the directory
file(GLOB ALL_CPP_FILES "")
foreach (TEST_SUBDIR IN LISTS TEST_SUBDIRS)
  file(GLOB TEST_CPP_FILES "${TEST_SUBDIR}/*.cpp")
  list(APPEND "GROUP_${TEST_SUBDIR}" ${TEST_CPP_FILES})
  list(APPEND ALL_CPP_FILES ${TEST_CPP_FILES})
  list(REMOVE_ITEM ALL_CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${TEST_SUBDIR}/${TEST_SUBDIR}.cpp")
endforeach ()

# Add group tests
if (KD_GROUP_TESTING)
  foreach (TEST_SUBDIR IN LISTS TEST_SUBDIRS)
    set(GROUP_TEST_NAME "${KD_PROJECT_NAME_LOWER}_test_group-${TEST_SUBDIR}")

    # Create the executable and link
    add_executable(${GROUP_TEST_NAME} "${TEST_SUBDIR}/${TEST_SUBDIR}.cpp" ${GROUP_${TEST_SUBDIR}})
    target_link_libraries(${GROUP_TEST_NAME} PRIVATE "KD::${KD_LIBRARY_NAME}" GTest::gtest_main)

    # Setting build postfixes for different build configurations
    set_target_properties(
      ${GROUP_TEST_NAME} PROPERTIES
      CXX_STANDARD ${KD_CPP_STANDARD}
      CXX_STANDARD_REQUIRED ON
      DEBUG_POSTFIX "${KD_STATIC_POSTFIX}-d"
      RELEASE_POSTFIX "${KD_STATIC_POSTFIX}"
      MINSIZEREL_POSTFIX "${KD_STATIC_POSTFIX}-mr"
      RELWITHDEBINFO_POSTFIX "${KD_STATIC_POSTFIX}-rd"
    )

    # Check if the project builds shared libraries
    if (BUILD_SHARED_LIBS)
      set_target_properties(
        ${GROUP_TEST_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
      )
    endif ()

    write_status("Added group test: ${GROUP_TEST_NAME}")
  endforeach ()
endif ()

# Add individual tests
if (KD_INDIVIDUAL_TESTING)
  # Loop through each item in the test list
  foreach (FILE_PATH ${ALL_CPP_FILES})
    # Normalize slashes
    file(TO_CMAKE_PATH "${FILE_PATH}" NORM_FILE_PATH)

    # Remove everything before and including 'tests/'
    string(REGEX REPLACE ".*tests/" "" RELATIVE_FILE_PATH "${NORM_FILE_PATH}")

    # Remove file extension
    string(REGEX REPLACE "\\.[^.]*$" "" RELATIVE_FILE_PATH "${RELATIVE_FILE_PATH}")

    # Replace '/' with '-'
    string(REPLACE "/" "-" TEST_ITEM "${RELATIVE_FILE_PATH}")

    # Attaching library name in front of example item
    set(TEST_TARGET "${KD_PROJECT_NAME_LOWER}_test-${TEST_ITEM}")

    # Build an executable from the `TEST_ITEM` source
    add_executable(${TEST_TARGET} ${FILE_PATH})

    # Link the built executable with the main library
    target_link_libraries(${TEST_TARGET} PRIVATE "KD::${KD_LIBRARY_NAME}" GTest::gtest_main)

    # Setting build postfixes for different build configurations
    set_target_properties(
      ${TEST_TARGET} PROPERTIES
      CXX_STANDARD ${KD_CPP_STANDARD}
      CXX_STANDARD_REQUIRED ON
      DEBUG_POSTFIX "${KD_STATIC_POSTFIX}-d"
      RELEASE_POSTFIX "${KD_STATIC_POSTFIX}"
      MINSIZEREL_POSTFIX "${KD_STATIC_POSTFIX}-mr"
      RELWITHDEBINFO_POSTFIX "${KD_STATIC_POSTFIX}-rd"
    )

    # Check if the project builds shared libraries
    if (BUILD_SHARED_LIBS)
      set_target_properties(
        ${TEST_TARGET} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
      )
    endif ()

    write_status("Added test: ${TEST_TARGET}")
  endforeach ()
endif ()

set(ALL_TEST_NAME "${KD_PROJECT_NAME_LOWER}_test-all")

# Adding the all tests target
add_executable(${ALL_TEST_NAME} "all.cpp" ${ALL_CPP_FILES})
target_link_libraries(${ALL_TEST_NAME} PRIVATE "KD::${KD_LIBRARY_NAME}" GTest::gtest_main)

# Setting build postfixes for different build configurations
set_target_properties(
  ${ALL_TEST_NAME} PROPERTIES
  CXX_STANDARD ${KD_CPP_STANDARD}
  CXX_STANDARD_REQUIRED ON
  DEBUG_POSTFIX "${KD_STATIC_POSTFIX}-d"
  RELEASE_POSTFIX "${KD_STATIC_POSTFIX}"
  MINSIZEREL_POSTFIX "${KD_STATIC_POSTFIX}-mr"
  RELWITHDEBINFO_POSTFIX "${KD_STATIC_POSTFIX}-rd"
)

# Check if the project builds shared libraries
if (BUILD_SHARED_LIBS)
  set_target_properties(
    ${ALL_TEST_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  )
endif ()
