# file: validate_target_platform.cmake
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


# Defining lists of valid values
set(_VALID_TARGET_OS "windows" "linux")
set(_VALID_TARGET_ARCH "x86" "x64")

# Validate target OS configuration
write_status("Validating target OS configuration...")

if (NOT DEFINED KD_TARGET_OS AND NOT DEFINED ${KD_PROJECT_NAME_UPPER}_TARGET_OS)
  message(FATAL_ERROR "KD_TARGET_OS or ${KD_PROJECT_NAME_UPPER}_TARGET_OS is not provided.")
else ()
  if (DEFINED KD_TARGET_OS)
    set(${KD_PROJECT_NAME_UPPER}_TARGET_OS ${KD_TARGET_OS})
  endif ()

  if (DEFINED ${KD_PROJECT_NAME_UPPER}_TARGET_OS)
    set(KD_TARGET_OS ${${KD_PROJECT_NAME_UPPER}_TARGET_OS})
  endif ()
endif ()

# Validate the OS
list(FIND _VALID_TARGET_OS ${KD_TARGET_OS} _OS_INDEX)
if (_OS_INDEX EQUAL -1)
  message(FATAL_ERROR "Unsupported target OS: ${KD_TARGET_OS}. Supported values are ${_VALID_TARGET_OS}.")
endif ()

# Validate target CPU architecture configuration
write_status("Validating target CPU architecture configuration...")

if (NOT DEFINED KD_TARGET_ARCH AND NOT DEFINED ${KD_PROJECT_NAME_UPPER}_TARGET_ARCH)
  message(FATAL_ERROR "KD_TARGET_ARCH or ${KD_PROJECT_NAME_UPPER}_TARGET_ARCH is not provided.")
else ()
  if (DEFINED KD_TARGET_ARCH)
    set(${KD_PROJECT_NAME_UPPER}_TARGET_ARCH ${KD_TARGET_ARCH})
  endif ()

  if (DEFINED ${KD_PROJECT_NAME_UPPER}_TARGET_ARCH)
    set(KD_TARGET_ARCH ${${KD_PROJECT_NAME_UPPER}_TARGET_ARCH})
  endif ()
endif ()

# Validate the OS
list(FIND _VALID_TARGET_ARCH ${KD_TARGET_ARCH} _OS_INDEX)
if (_OS_INDEX EQUAL -1)
  message(FATAL_ERROR "Unsupported target CPU architecture: ${KD_TARGET_ARCH}. "
          "Supported values are ${_VALID_TARGET_ARCH}.")
endif ()

# Add the OS and CPU architecture to the installation directory name
set(KD_INSTALL_DIR_NAME "${KD_INSTALL_DIR_NAME}-${KD_TARGET_OS}-${KD_TARGET_ARCH}")
