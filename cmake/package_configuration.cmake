# file: package_configuration.cmake
# author: Kumarjit Das
# date: 2025-05-24
# brief: KD library cmake package configuration script.

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


# For accessing the package configuration helper functions
include("CMakePackageConfigHelpers")

# Configuring the `Config` file for packaging this library
set(CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/configs")

if (BUILD_SHARED_LIBS)
  set(CONFIG_FILE "${CONFIG_FILE}/config-shared.cmake.in")
else ()
  set(CONFIG_FILE "${CONFIG_FILE}/config-static.cmake.in")
endif ()

configure_package_config_file(
  ${CONFIG_FILE}
  "${CMAKE_CURRENT_BINARY_DIR}/${KD_PROJECT_NAME_LOWER}-config.cmake"
  INSTALL_DESTINATION "${KD_PROJECT_NAME_LOWER}/${CMAKE_INSTALL_LIBDIR}/${KD_INSTALL_CMAKE_DIR}"
  PATH_VARS KD_INSTALL_LIB_DIR KD_INSTALL_BIN_DIR KD_INSTALL_INCLUDE_DIR
  )

# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${KD_PROJECT_NAME_LOWER}-config-version.cmake"
  VERSION ${${KD_LIBRARY_NAME_UPPER}_VERSION}
  COMPATIBILITY AnyNewerVersion
  )

write_status("Configuring package config file from: ${CONFIG_FILE}")

# Setting the install location for the generated config files
install(
  FILES
  "${CMAKE_CURRENT_BINARY_DIR}/${KD_PROJECT_NAME_LOWER}-config.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/${KD_PROJECT_NAME_LOWER}-config-version.cmake"
  DESTINATION "${KD_INSTALL_DIR_NAME}/${CMAKE_INSTALL_LIBDIR}/${KD_INSTALL_CMAKE_DIR}"
  )

# Export the package for use from the build-tree
export(PACKAGE ${KD_PROJECT_NAME})
