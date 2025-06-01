# file: setup_project.cmake
# author: Kumarjit Das
# date: 2025-05-24
# brief: KD library cmake project setup script.

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


# Setting the project name in lower, upper, and mixed case
set(KD_PROJECT_NAME "kd")
string(TOLOWER ${KD_PROJECT_NAME} KD_PROJECT_NAME_LOWER)
string(TOUPPER ${KD_PROJECT_NAME} KD_PROJECT_NAME_UPPER)

# Setting the main library name in both lower and upper-cases
set(KD_LIBRARY_NAME "kd")
string(TOUPPER ${KD_LIBRARY_NAME} KD_LIBRARY_NAME_UPPER)

# Setting project version
set(${KD_LIBRARY_NAME_UPPER}_VERSION_MAJOR 0)
set(${KD_LIBRARY_NAME_UPPER}_VERSION_MINOR 0)
set(${KD_LIBRARY_NAME_UPPER}_VERSION_PATCH 6)

string(CONCAT ${KD_LIBRARY_NAME_UPPER}_VERSION
       "${${KD_LIBRARY_NAME_UPPER}_VERSION_MAJOR}."
       "${${KD_LIBRARY_NAME_UPPER}_VERSION_MINOR}."
       "${${KD_LIBRARY_NAME_UPPER}_VERSION_PATCH}")

# Setting project description
string(CONCAT ${KD_PROJECT_NAME_UPPER}_DESCRIPTION
       "A modern standard library for C, designed to bring powerful data structures "
       "and algorithms to the C programming language.")

set(KD_INSTALL_DIR_NAME "${KD_PROJECT_NAME_LOWER}-v${${KD_LIBRARY_NAME_UPPER}_VERSION}")

# Creating the write_status function
function(write_status)
  set(STATUS_VARIABLE "")

  foreach (argument ${ARGV})
    set(STATUS_VARIABLE "${STATUS_VARIABLE}${argument}")
  endforeach ()

  message(STATUS "[${KD_PROJECT_NAME_UPPER}] ${STATUS_VARIABLE}")
endfunction()

write_status("Initiating the project setup...")

# Generate compile commands for IDE's
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
write_status("CMAKE_EXPORT_COMPILE_COMMANDS is set to: ${CMAKE_EXPORT_COMPILE_COMMANDS}")

# Setting the current user directory
if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
  set(KD_CURRENT_USER_PATH "C:/Users/$ENV{USERNAME}")
else ()
  set(KD_CURRENT_USER_PATH "/$ENV{USER}")
endif ()
write_status("Current user path: ${KD_CURRENT_USER_PATH}")

# Getting the build directory name from current binary directory
string(REPLACE "${CMAKE_SOURCE_DIR}/" "" KD_BUILD_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# Setting the build library type name
if (BUILD_SHARED_LIBS)
  set(KD_BUILD_LIBRARY_TYPE "shared")
else ()
  set(KD_BUILD_LIBRARY_TYPE "static")
endif ()

# Setting the build directory name
string(FIND ${KD_BUILD_DIRECTORY} ${KD_BUILD_LIBRARY_TYPE} _KD_BUILD_LIBRARY_TYPE_EXISTS)

if (${_KD_BUILD_LIBRARY_TYPE_EXISTS} EQUAL -1)
  set(KD_BUILD_DIRECTORY "${KD_BUILD_DIRECTORY}-${KD_BUILD_LIBRARY_TYPE}")
endif ()

# Set the C standard
set(KD_C_STANDARD 90)

# Setting the full path to sources directories
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
