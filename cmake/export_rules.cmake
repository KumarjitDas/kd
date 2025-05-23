# file: export_rules.cmake
# author: Kumarjit Das
# date: 2025-05-24
# brief: KD library cmake export rules file.

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


write_status("Generating ${KD_PROJECT_NAME_LOWER}-targets...")

# Adding this to make cache variables for install destinations
include("GNUInstallDirs")

# Creating export target for the main library
install(TARGETS ${KD_LIBRARY_NAME}
        EXPORT ${KD_PROJECT_NAME_LOWER}-targets
        LIBRARY DESTINATION "${KD_INSTALL_DIR_NAME}/${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${KD_INSTALL_DIR_NAME}/${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${KD_INSTALL_DIR_NAME}/${CMAKE_INSTALL_BINDIR}"
        INCLUDES DESTINATION "${KD_INSTALL_DIR_NAME}/${CMAKE_INSTALL_INCLUDEDIR}")

# Setting the install location of the generated export target file
install(EXPORT ${KD_PROJECT_NAME_LOWER}-targets
        FILE "${KD_PROJECT_NAME_LOWER}-targets.cmake"
        NAMESPACE KD::
        DESTINATION "${KD_INSTALL_DIR_NAME}/${CMAKE_INSTALL_LIBDIR}/${KD_INSTALL_CMAKE_DIR}")

# Rule to export all the targets directly from the build-tree
export(
  EXPORT ${KD_PROJECT_NAME_LOWER}-targets
  FILE "${PROJECT_BINARY_DIR}/${KD_PROJECT_NAME_LOWER}-targets.cmake"
  NAMESPACE KD::
  )
