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

# Adding the include files to the main target
set(INCLUDE_FILES
    "${INCLUDE_DIR}/kd/defs.h"
    "${INCLUDE_DIR}/kd/types/fw.h"
    "${INCLUDE_DIR}/kd/types/fp.h"
    "${INCLUDE_DIR}/kd/mem.h"
    "${INCLUDE_DIR}/kd/mem_algn.h"
    "${INCLUDE_DIR}/kd/gen_mem_ops.h")
set(INTERNAL_INCLUDE_FILES
    "${INCLUDE_DIR}/_internal/gen_mem_ops_sn.h")
target_sources(${KD_LIBRARY_NAME} PRIVATE ${INTERNAL_INCLUDE_FILES} ${INCLUDE_FILES})

# Adding the source files to the main target
set(SRC_FILES
    "${SRC_DIR}/kd/mem.c"
    "${SRC_DIR}/kd/mem_algn.c"
    "${SRC_DIR}/kd/gen_mem_ops.c")
set(INTERNAL_SRC_FILES
    "${SRC_DIR}/_internal/gen_mem_ops_sn.c")
target_sources(${KD_LIBRARY_NAME} PRIVATE ${INTERNAL_SRC_FILES} ${SRC_FILES})

# Setting the install destination for include and source file
install(FILES ${INCLUDE_FILES} DESTINATION "include")
install(FILES ${SRC_FILES} DESTINATION "src")
