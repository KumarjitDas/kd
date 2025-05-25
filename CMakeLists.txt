# file: CMakeLists.txt
# author: Kumarjit Das
# date: 2025-05-24
# brief: KD library main cmake file.

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


cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

# Setup all project settings/variables
include("cmake/setup_project.cmake")

# Setting the project name, version, and other descriptions
project(${KD_PROJECT_NAME}
        VERSION "${${KD_LIBRARY_NAME_UPPER}_VERSION}"
        DESCRIPTION "${${KD_PROJECT_NAME_UPPER}_DESCRIPTION}"
        HOMEPAGE_URL "https://github.com/KumarjitDas/${KD_PROJECT_NAME_LOWER}.git"
        LANGUAGES "C")

# Validate target platform
include("cmake/validate_target_platform.cmake")

# Validate the build configuration
include("cmake/validate_build_config.cmake")

# Define sublibraries
include("cmake/define_sublibraries.cmake")

# Create the main library
include("cmake/create_library.cmake")

# Add sources to the library
include("CMake/add_sources_to_target.cmake")

# Set the build output directories
include("cmake/set_build_output_directories.cmake")

# Set the installation directories
include("cmake/set_install_directories.cmake")

# Set the C standard
include("cmake/set_c_standard.cmake")

# Set the compiler flags/warnings
include("cmake/set_compiler_flags.cmake")

# Set include directories
include("cmake/set_include_directories.cmake")

# Set build postfixes for different build configurations
include("cmake/set_build_postfixes.cmake")

# Configure the versions of this project
include("cmake/configure_project_version.cmake")

# Add the source files to the main target
include("cmake/export_rules.cmake")

# Adding the package configuration for `find_package` support
include("cmake/package_configuration.cmake")

# Install all non-project files
include("cmake/install_nonproject_files.cmake")

# Adding the `Examples` directories
add_subdirectory("examples")
