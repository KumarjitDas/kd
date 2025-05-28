/**
 * @file bool_macros.c
 * @author Kumarjit Das
 * @date 2025-05-24
 * @brief System information boolean macros example.
 */
/**
 * LICENSE: BSD 3-Clause License
 *
 * Copyright (c) 2025, Kumarjit Das.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <stdio.h>
#include "kd.h"


int
       main(argc, argv)
int    argc;
char** argv;
{
  (void)argc;
  (void)argv;

  printf("System information boolean macros example :: begin\n\n");

  printf("API Version: %s\n", KD_VERSION_CSTR);

  printf("Compiler: %s\n",
#if defined KD_COMP_INTEL
         "Intel C/C++"
#elif defined KD_COMP_MIPSPRO
         "MIPSpro C/C++"
#elif defined KD_COMP_HPCC
         "HP-UX CC"
#elif defined KD_COMP_GCC || defined KD_COMP_APPLECC
         "Gnu GCC"
#elif defined KD_COMP_IBM
         "IBM C/C++"
#elif defined KD_COMP_MSVC
         "Microsoft Visual C++"
#elif defined KD_COMP_SUN
         "Sun Pro"
#elif defined KD_COMP_BORLAND
         "Borland C/C++"
#elif defined KD_COMP_METROWERKS
         "MetroWerks CodeWarrior"
#elif defined KD_COMP_DEC
         "Compaq/DEC C/C++"
#elif defined KD_COMP_WATCOM
         "Watcom C/C++"
#else
         "Unknown"
#endif /* KD_COMP_INTEL */
  );

  printf("Target Operating System: %s\n",
#if defined KD_OS_LINUX
         "Linux"
#elif defined KD_OS_CYGWIN32
         "Cygwin"
#elif defined KD_OS_GAMECUBE
         "GameCube"
#elif defined KD_OS_MINGW
         "MinGW"
  #if defined KD_OS_MINGW64
         " 64-bit"
  #else
         " 32-bit"
  #endif /* defined KD_OS_MINGW64 */
#elif defined KD_OS_GO32
         "GO32/MS-DOS"
#elif defined KD_OS_DOS32
         "DOS/32-bit"
#elif defined KD_OS_UNICOS
         "UNICOS"
#elif defined KD_OS_OSX
         "MacOS X"
#elif defined KD_OS_SOLARIS
         "Solaris"
#elif defined KD_OS_SUNOS
         "SunOS"
#elif defined KD_OS_IRIX
         "Irix"
#elif defined KD_OS_HPUX
         "HP-UX"
#elif defined KD_OS_AIX
         "AIX"
#elif defined KD_OS_TRU64
         "Tru64"
#elif defined KD_OS_BEOS
         "BeOS"
#elif defined KD_OS_AMIGA
         "Amiga"
#elif defined KD_OS_UNIX
         "Unix-like (generic)"
#elif defined KD_OS_XBOX
         "XBOX"
#elif defined KD_OS_WINDOWS
         "Windows"
  #if defined KD_OS_WINCE
         " CE"
  #elif defined KD_OS_WIN64
         " 64-bit"
  #else
         " 32-bit"
  #endif /* defined KD_OS_WINCE */
#elif defined KD_OS_PALM
         "PalmOS"
#elif defined KD_OS_MACOS
         "MacOS"
#else
         "Unknown"
#endif /* KD_OS_LINUX */
  );


  printf("Target CPU: %s\n",
#if defined KD_CPU_PPC750
         "IBM PowerPC 750 (NGC)"
#elif defined KD_CPU_68K
         "MC68000"
#elif defined KD_CPU_PPC
         "PowerPC"
  #if defined KD_CPU_PPC64
         " 64-bit"
  #endif /* defined KD_CPU_PPC64 */
#elif defined KD_CPU_CRAYT3E
         "Cray T3E (Alpha 21164)"
#elif defined KD_CPU_SH3 || defined KD_CPU_SH4
         "Hitachi SH-"
  #if defined KD_CPU_SH4
         "4"
  #else
         "3"
  #endif /* defined KD_CPU_SH4 */
#elif defined KD_CPU_SPARC64
         "Sparc/64"
#elif defined KD_CPU_SPARC
         "Sparc/32"
#elif defined KD_CPU_STRONGARM
         "ARM"
#elif defined KD_CPU_MIPS
         "MIPS"
#elif defined KD_CPU_IA64
         "IA64"
#elif defined KD_CPU_X86 || defined KD_CPU_X86_64
  #if defined KD_CPU_X86_64
         "AMD x86-64"
  #else
         "Intel 386+"
  #endif /* defined KD_CPU_X86_64 */
#elif defined KD_CPU_AXP
         "AXP"
#elif defined KD_CPU_HPPA
         "PA-RISC"
#else
         "Unknown"
#endif /* KD_CPU_PPC750 */
  );

  printf("Target Architecture Integer Size: %s\n",
#if defined KD_ARCH_64BIT_INT
         "64 bit"
#elif defined KD_ARCH_32BIT_INT
         "32 bit"
#else
         "Unknown"
#endif /* KD_ARCH_64BIT_INT */
  );

  printf("Target Architecture Pointer(Address) Size: %s\n",
#if defined KD_ARCH_64BIT_PTR
         "64 bit"
#elif defined KD_ARCH_32BIT_PTR
         "32 bit"
#else
         "Unknown"
#endif /* KD_ARCH_64BIT_PTR */
  );

  printf("Endianness: %s\n",
#if defined KD_ENDIAN_LITTLE
         "Little"
#else
         "Big"
#endif /* KD_ENDIAN_LITTLE */
  );

  printf("\nSystem information boolean macros example :: end\n\n");

  return KD_EXIT_SUCCESS;
}
