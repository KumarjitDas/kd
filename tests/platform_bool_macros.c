/**
 * @file platform_bool_macros.c
 * @author Kumarjit Das
 * @brief System information boolean macros test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>

#include "../include/kd.h"


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("System information boolean macros test :: begin\n\n");

    printf("API Version: %s\n", KD_VERSION_CSTR);

    printf(
        "Compiler: %s\n",
#if defined COMP_INTEL
        "Intel C/C++"
#elif defined COMP_MIPSPRO
        "MIPSpro C/C++"
#elif defined COMP_HPCC
        "HP-UX CC"
#elif defined COMP_GCC || defined COMP_APPLECC
        "Gnu GCC"
#elif defined COMP_IBM
        "IBM C/C++"
#elif defined COMP_MSVC
        "Microsoft Visual C++"
#elif defined COMP_SUN
        "Sun Pro"
#elif defined COMP_BORLAND
        "Borland C/C++"
#elif defined COMP_METROWERKS
        "MetroWerks CodeWarrior"
#elif defined COMP_DEC
        "Compaq/DEC C/C++"
#elif defined COMP_WATCOM
        "Watcom C/C++"
#else
        "Unknown"
#endif /* COMP_INTEL */
    );

    printf(
        "Target Operating System: %s\n",
#if defined OS_LINUX
        "Linux"
#elif defined OS_CYGWIN32
        "Cygwin"
#elif defined OS_GAMECUBE
        "GameCube"
#elif defined OS_MINGW
        "MinGW"
    #if defined OS_MINGW64
        " 64-bit"
    #else
        " 32-bit"
    #endif /* defined OS_MINGW64 */
#elif defined OS_GO32
        "GO32/MS-DOS"
#elif defined OS_DOS32
        "DOS/32-bit"
#elif defined OS_UNICOS
        "UNICOS"
#elif defined OS_OSX
        "MacOS X"
#elif defined OS_SOLARIS
        "Solaris"
#elif defined OS_SUNOS
        "SunOS"
#elif defined OS_IRIX
        "Irix"
#elif defined OS_HPUX
        "HP-UX"
#elif defined OS_AIX
        "AIX"
#elif defined OS_TRU64
        "Tru64"
#elif defined OS_BEOS
        "BeOS"
#elif defined OS_AMIGA
        "Amiga"
#elif defined OS_UNIX
        "Unix-like (generic)"
#elif defined OS_XBOX
        "XBOX"
#elif defined OS_WINDOWS
        "Windows"
    #if defined OS_WINCE
        " CE"
    #elif defined OS_WIN64
        " 64-bit"
    #else
        " 32-bit"
    #endif /* defined OS_WINCE */
#elif defined OS_PALM
        "PalmOS"
#elif defined OS_MACOS
        "MacOS"
#else
        "Unknown"
#endif /* OS_LINUX */
    );


    printf(
        "Target CPU: %s\n",
#if defined CPU_PPC750
        "IBM PowerPC 750 (NGC)"
#elif defined CPU_68K
        "MC68000"
#elif defined CPU_PPC
        "PowerPC"
    #if defined CPU_PPC64
        " 64-bit"
    #endif /* defined CPU_PPC64 */
#elif defined CPU_CRAYT3E
        "Cray T3E (Alpha 21164)"
#elif defined CPU_SH3 || defined CPU_SH4
        "Hitachi SH-"
    #if defined CPU_SH4
        "4"
    #else
        "3"
    #endif /* defined CPU_SH4 */
#elif defined CPU_SPARC64
        "Sparc/64"
#elif defined CPU_SPARC
        "Sparc/32"
#elif defined CPU_STRONGARM
        "ARM"
#elif defined CPU_MIPS
        "MIPS"
#elif defined CPU_IA64
        "IA64"
#elif defined CPU_X86 || defined CPU_X86_64
    #if defined CPU_X86_64
        "AMD x86-64"
    #else
        "Intel 386+"
    #endif /* defined CPU_X86_64 */
#elif defined CPU_AXP
        "AXP"
#elif defined CPU_HPPA
        "PA-RISC"
#else
        "Unknown"
#endif /* CPU_PPC750 */
    );

    printf(
        "Target Architecture Integer Size: %s\n",
#if defined ARCH_64BIT_INT
        "64 bit"
#elif defined ARCH_32BIT_INT
        "32 bit"
#else
        "Unknown"
#endif /* ARCH_64BIT_INT */
    );

    printf(
        "Target Architecture Pointer(Address) Size: %s\n",
#if defined ARCH_64BIT_PTR
        "64 bit"
#elif defined ARCH_32BIT_PTR
        "32 bit"
#else
        "Unknown"
#endif /* ARCH_64BIT_PTR */
    );

    printf(
        "Endianness: %s\n",
#if defined ENDIAN_LITTLE
        "Little"
#else
        "Big"
#endif /* ENDIAN_LITTLE */
    );

    printf("\nSystem information boolean macros test :: end\n\n");

    return EXIT_SUCCESS;
}
