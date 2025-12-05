/**
 * @file platform.h
 * @author Kumarjit Das
 * @version 0.0.1
 * @brief Platform-specific definitions for the KD library.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 * @since 0.0.1
 */


#ifndef KD_PLATFORM_H_
#define KD_PLATFORM_H_


#if defined KD_DEFINED_LIBKD
    #undef KD_DEFINED_LIBKD
#endif /* KD_DEFINED_LIBKD */

#define KD_DEFINED_LIBKD 1


/**
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *  Current compiler
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

#if defined __ECC || defined __ICC || defined __INTEL_COMPILER
    #define KD_COMP_INTEL 1
    #define KD_COMP_CSTR  "Intel C/C++"
#endif

#if (defined __host_mips || defined __sgi) && !defined __GNUC__
    #define KD_COMP_MIPSPRO 1
    #define KD_COMP_CSTR    "MIPSpro C/C++"
#endif

#if defined __hpux && !defined __GNUC__
    #define KD_COMP_HPCC 1
    #define KD_COMP_CSTR "HP-UX CC"
#endif

#if defined __GNUC__
    #define KD_COMP_GCC  1
    #define KD_COMP_CSTR "Gnu GCC"
#endif

#if defined __APPLE_CC__
    #define KD_COMP_APPLECC 1
#endif

#if defined __IBMC__ || defined __IBMCPP__
    #define KD_COMP_IBM  1
    #define KD_COMP_CSTR "IBM C/C++"
#endif

#if defined _MSC_VER
    #define KD_COMP_MSVC 1
    #define KD_COMP_CSTR "Microsoft Visual C++"
#endif

#if defined __SUNPRO_C
    #define KD_COMP_SUN  1
    #define KD_COMP_CSTR "Sun Pro"
#endif

#if defined __BORLANDC__
    #define KD_COMP_BORLAND 1
    #define KD_COMP_CSTR    "Borland C/C++"
#endif

#if defined __MWERKS__
    #define KD_COMP_METROWERKS 1
    #define KD_COMP_CSTR       "MetroWerks CodeWarrior"
#endif

#if defined __DECC || defined __DECCXX
    #define KD_COMP_DEC  1
    #define KD_COMP_CSTR "Compaq/DEC C/C++"
#endif

#if defined __WATCOMC__
    #define KD_COMP_WATCOM 1
    #define KD_COMP_CSTR   "Watcom C/C++"
#endif

#if !defined KD_COMP_CSTR
    #define KD_COMP_CSTR "Unknown"
#endif


/**
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *  C Standard
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

#if defined(__STDC_VERSION__)
    #if (__STDC_VERSION__ >= 202311L)
        #define KD_C_STD_NO   23
        #define KD_C_STD_23   1
        #define KD_C_STD_CSTR "C23"
    #elif (__STDC_VERSION__ >= 201710L)
        #define KD_C_STD_NO   17
        #define KD_C_STD_17   1
        #define KD_C_STD_CSTR "C17"
    #elif (__STDC_VERSION__ >= 201112L)
        #define KD_C_STD_NO   11
        #define KD_C_STD_11   1
        #define KD_C_STD_CSTR "C11"
    #elif (__STDC_VERSION__ >= 199901L)
        #define KD_C_STD_NO   99
        #define KD_C_STD_99   1
        #define KD_C_STD_CSTR "C99"
    #else
        #define KD_C_STD_90 1
    #endif
#else
    #define KD_C_STD_90 1
#endif

#if defined KD_C_STD_90
    #define KD_C_STD_89    1
    #define KD_C_STD_89_90 1
    #define KD_C_STD_NO    90
    #define KD_C_STD_CSTR  "C89/C90"
#endif

#if !defined KD_C_STD_NO
    #define KD_C_STD_NO 0
#endif

#if !defined KD_C_STD_CSTR
    #define KD_C_STD_CSTR "Unknown"
#endif


/**
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *  Target Operating System
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

#if defined linux || defined __linux__
    #define KD_OS_LINUX 1
    #define KD_OS_CSTR  "Linux"
#endif

#if defined __CYGWIN32__
    #define KD_OS_CYGWIN32 1
    #define KD_OS_CSTR     "Cygwin"
#endif

#if defined GEKKO
    #define KD_OS_GAMECUBE
    #define __powerpc__
    #define KD_OS_CSTR "GameCube"
#endif

#if defined __MINGW32__
    #define KD_OS_MINGW   1
    #define KD_OS_MINGW32 1
    #undef KD_OS_CSTR
    #define KD_OS_CSTR "MinGW (32-bit)"
#endif

#if defined __MINGW64__
    #define KD_OS_MINGW   1
    #define KD_OS_MINGW64 1
    #undef KD_OS_CSTR
    #define KD_OS_CSTR "MinGW (64-bit)"
#endif

#if defined GO32 && defined DJGPP && defined __MSDOS__
    #define KD_OS_GO32 1
    #define KD_OS_CSTR "GO32/MS-DOS"
#endif

/**
 * NOTE: make sure you use /bt=DOS if compiling for 32-bit DOS,
 * otherwise Watcom assumes host=target
 */
#if defined __WATCOMC__ && defined __386__ && defined __DOS__
    #define KD_OS_DOS32 1
    #define KD_OS_CSTR  "DOS/32-bit"
#endif

#if defined _UNICOS
    #define KD_OS_UNICOS 1
    #define KD_OS_CSTR   "UNICOS"
#endif

#if (defined __MWERKS__ && defined __powerc && !defined macintosh) || defined __APPLE_CC__ || defined macosx
    #define KD_OS_OSX  1
    #define KD_OS_CSTR "MacOS X"
#endif

#if defined __sun__ || defined sun || defined __sun || defined __solaris__
    #if defined __SVR4 || defined __svr4__ || defined __solaris__
        #define KD_OS_SOLARIS 1
        #define KD_OS_CSTR    "Solaris"
    #endif
    #if !defined KD_OS_STRING
        #define KD_OS_SUNOS 1
        #define KD_OS_CSTR  "SunOS"
    #endif
#endif

#if defined __sgi__ || defined sgi || defined __sgi
    #define KD_OS_IRIX 1
    #define KD_OS_CSTR "Irix"
#endif

#if defined __hpux__ || defined __hpux
    #define KD_OS_HPUX 1
    #define KD_OS_CSTR "HP-UX"
#endif

#if defined _AIX
    #define KD_OS_AIX  1
    #define KD_OS_CSTR "AIX"
#endif

#if (defined __alpha && defined __osf__)
    #define KD_OS_TRU64 1
    #define KD_OS_CSTR  "Tru64"
#endif

#if defined __BEOS__ || defined __beos__
    #define KD_OS_BEOS 1
    #define KD_OS_CSTR "BeOS"
#endif

#if defined amiga || defined amigados || defined AMIGA || defined _AMIGA
    #define KD_OS_AMIGA 1
    #define KD_OS_CSTR  "Amiga"
#endif

#if defined __unix__
    #define KD_OS_UNIX 1

    #if !defined KD_OS_CSTR
        #define KD_OS_CSTR "Unix-like (generic)"
    #endif
#endif

#if defined _WIN32_WCE
    #define KD_OS_WINDOWS 1
    #define KD_OS_WINCE   1
    #define KD_OS_CSTR    "Windows CE"
#endif

#if defined _XBOX
    #define KD_OS_XBOX 1
    #define KD_OS_CSTR "XBOX"
#endif

#if defined _WIN32 || defined WIN32 || defined __NT__ || defined __WIN32__
    #define KD_OS_WINDOWS 1
    #define KD_OS_WIN32   1

    #if !defined KD_OS_XBOX
        #if defined _WIN64
            #define KD_OS_WIN64 1
            #undef KD_OS_CSTR
            #define KD_OS_CSTR "Windows 64-bit"
        #else
            #if !defined KD_OS_CSTR
                #define KD_OS_CSTR "Windows 32-bit"
            #endif
        #endif
    #endif
#endif

#if defined __palmos__
    #define KD_OS_PALM 1
    #define KD_OS_CSTR "PalmOS"
#endif

#if defined THINK_C || defined macintosh
    #define KD_OS_MACOS 1
    #define KD_OS_CSTR  "MacOS"
#endif

#if !defined KD_OS_CSTR
    #if defined _R5900
        #define KD_OS_STRING "Sony PS2(embedded)"
    #else
        #define KD_OS_STRING "Embedded/Unknown"
    #endif
#endif


/**
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *  Target CPU
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

#if defined GEKKO
    #define KD_CPU_PPC750 1
    #define KD_CPU_CSTR   "IBM PowerPC 750 (NGC)"
#endif

#if defined mc68000 || defined m68k || defined __MC68K__ || defined m68000
    #define KD_CPU_68K  1
    #define KD_CPU_CSTR "MC68000"
#endif

#if defined __PPC__ || defined __POWERPC__ || defined powerpc || defined _POWER || defined __ppc__ || defined __powerpc__
    #define KD_CPU_PPC 1

    #if defined __powerpc64__
        #define KD_CPU_PPC64 1
        #define KD_CPU_CSTR  "PowerPC 64-bit"
    #else
        #define KD_CPU_PPC32 1
        #define KD_CPU_CSTR  "PowerPC 32-bit"
    #endif
#endif

#if defined _CRAYT3E || defined _CRAYMPP
    /* target processor is a DEC Alpha 21164 used in a Cray T3E */
    #define KD_CPU_CRAYT3E 1
    #define KD_CPU_CSTR    "Cray T3E (Alpha 21164)"
#endif

#if defined CRAY || defined _CRAY && !defined _CRAYT3E
    #error Non-AXP Cray systems not supported
#endif

#if defined _SH3
    #define KD_CPU_SH3  1
    #define KD_CPU_CSTR "Hitachi SH-3"
#endif

#if defined __sh4__ || defined __SH4__
    #define KD_CPU_SH3  1
    #define KD_CPU_SH4  1
    #define KD_CPU_CSTR "Hitachi SH-4"
#endif

#if defined __sparc__ || defined __sparc
    #define KD_CPU_SPARC 1

    #if defined __arch64__ || defined __sparcv9 || defined __sparc_v9__
        #define KD_CPU_SPARC64 1
        #define KD_CPU_CSTR    "Sparc/64"
    #else
        #define KD_CPU_CSTR "Sparc/32"
    #endif
#endif

#if defined ARM || defined __arm__ || defined _ARM
    #define KD_CPU_ARM  1
    #define KD_CPU_CSTR "ARM"
#endif

#if defined mips || defined __mips__ || defined __MIPS__ || defined _MIPS
    #define KD_CPU_MIPS 1

    #if defined _R5900
        #define KD_CPU_CSTR "MIPS R5900 (PS2)"
    #else
        #define KD_CPU_CSTR "MIPS"
    #endif
#endif

#if defined __ia64 || defined _M_IA64 || defined __ia64__
    #define KD_CPU_IA64 1
    #define KD_CPU_CSTR "IA64"
#endif

#if defined __X86__ || defined __i386__ || defined i386 || defined _M_IX86 || defined __386__ || defined __x86_64__ || defined _M_X64
    #define KD_CPU_X86 1

    #if defined __x86_64__ || defined _M_X64
        #define KD_CPU_X86_64 1
    #endif

    #if defined KD_CPU_X86_64
        #define KD_CPU_CSTR "AMD x86-64"
    #else
        #define KD_CPU_CSTR "Intel 386+"
    #endif
#endif

#if defined __alpha || defined alpha || defined _M_ALPHA || defined __alpha__
    #define KD_CPU_AXP  1
    #define KD_CPU_CSTR "AXP"
#endif

#if defined __hppa || defined hppa
    #define KD_CPU_HPPA 1
    #define KD_CPU_CSTR "PA-RISC"
#endif

#if !defined KD_CPU_CSTR
    #define KD          could not determine the target CPU
    #define KD_CPU_CSTR "Unknown"
#endif


/**
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *  Calling Convention
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

#if defined KD_CPU_X86 && !defined KD_CPU_X86_64
    #if defined __GNUC__
        #define KD_CDECL    __attribute__((cdecl))
        #define KD_STDCALL  __attribute__((stdcall))
        #define KD_FASTCALL __attribute__((fastcall))
    #elif (defined _MSC_VER || defined __WATCOMC__ || defined __BORLANDC__ || defined __MWERKS__)
        #define KD_CDECL    __cdecl
        #define KD_STDCALL  __stdcall
        #define KD_FASTCALL __fastcall
    #endif
#else
    #define KD_CDECL
    #define KD_STDCALL
    #define KD_FASTCALL
#endif


/**
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *  Import-Export Signature
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

#ifdef BUILDING_LIB
    #define KD_BUILDING_LIB
#endif

#if defined IMPORTEXPORT
    #define KD_IMPORTEXPORT
#endif

#if defined KD_IMPORTEXPORT
    #undef KD_IMPORTEXPORT
#endif

#if defined KD_DLL
    #if defined KD_OS_WIN32
        #if defined _MSC_VER
            #if (_MSC_VER >= 800)
                #if defined KD_BUILDING_LIB
                    #define KD_IMPORTEXPORT __declspec(dllexport)
                #else
                    #define KD_IMPORTEXPORT __declspec(dllimport)
                #endif
            #else
                #if defined KD_BUILDING_LIB
                    #define KD_IMPORTEXPORT __export
                #else
                    #define KD_IMPORTEXPORT
                #endif
            #endif
        #endif /* defined _MSC_VER */
        #if defined __BORLANDC__
            #if (__BORLANDC__ >= 0x500)
                #if defined KD_BUILDING_LIB
                    #define KD_IMPORTEXPORT __declspec(dllexport)
                #else
                    #define KD_IMPORTEXPORT __declspec(dllimport)
                #endif
            #else
                #if defined KD_BUILDING_LIB
                    #define KD_IMPORTEXPORT __export
                #else
                    #define KD_IMPORTEXPORT
                #endif
            #endif
        #endif /* defined __BORLANDC__ */
        /* for all other compilers */
        #if defined __GNUC__ || defined __WATCOMC__ || defined __MWERKS__
            #if defined KD_BUILDING_LIB
                #define KD_IMPORTEXPORT __declspec(dllexport)
            #else
                #define KD_IMPORTEXPORT __declspec(dllimport)
            #endif
        #endif /* all other compilers */
        #if !defined KD_IMPORTEXPORT
            #error Building DLLs not supported on this compiler
        #endif
    #endif /* defined KD_OS_WIN32 */
#endif

#if !defined KD_IMPORTEXPORT
    #define KD_IMPORTEXPORT
#endif


/**
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *  Public API Export Signature
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

#ifdef KDAPI
    #undef KDAPI
#endif

#if ((defined _MSC_VER) && (_MSC_VER < 800)) || (defined __BORLANDC__ && (__BORLANDC__ < 0x500))
    #define KDAPI(T) extern T KD_IMPORTEXPORT
#else
    #define KDAPI(T) extern KD_IMPORTEXPORT T
#endif


/**
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *  C++ Detection and Extern Indicators
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

#ifdef __cplusplus
    #define KD_CPLUSPLUS 1
#endif

#if defined KD_CPLUSPLUS
    /* clang-format off */
    #define KD_EXTERN_BEGIN  extern "C" {
    #define KD_EXTERN_END }
#else
    #define KD_EXTERN_BEGIN
    #define KD_EXTERN_END
#endif /* KD_CPLUSPLUS */


/**
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *  Endianness
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

#if defined KD_CPU_X86 || defined KD_CPU_AXP || defined KD_CPU_STRONGARM || defined KD_OS_WIN32 || defined KD_OS_WINCE || defined __MIPSEL__
    #define KD_ENDIAN_LITTLE 1
    #define KD_ENDIAN_CSTR   "little"
#else
    #define KD_ENDIAN_BIG  1
    #define KD_ENDIAN_CSTR "big"
#endif


/**
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *  Architecture Detection
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

#if defined _MSC_VER || defined __BORLANDC__ || defined __WATCOMC__ || (defined __alpha && defined __DECC)
    #define KD_ARCH_64BIT_INT 1
#elif defined __GNUC__ || defined __MWERKS__ || defined __SUNPRO_C || defined __SUNPRO_CC || defined __APPLE_CC__ || defined KD_OS_IRIX || defined _LONG_LONG || defined _CRAYC
    #if defined __x86_64__ || defined __ppc64__ || defined __aarch64__ || defined __LP64__ || defined _WIN64 || __SIZEOF_POINTER__ == 8 || __SIZEOF_LONG__ == 8
        #define KD_ARCH_64BIT_INT 1
    #endif
#elif defined __LP64__ || defined __powerpc64__ || defined KD_CPU_SPARC64
    #define KD_ARCH_64BIT_INT 1
#endif

#if !defined KD_ARCH_64BIT_INT
    #define KD_ARCH_32BIT_INT 1
#endif

#if defined KD_ARCH_64BIT_INT
    #define KD_ARCH_INT_CSTR "64 bit"
#elif defined KD_ARCH_32BIT_INT
    #define KD_ARCH_INT_CSTR "32 bit"
#else
    #define KD_ARCH_INT_CSTR "Unknown"
#endif /* KD_ARCH_64BIT_INT */

#if defined KD_CPU_AXP && (defined KD_OS_TRU64 || defined KD_OS_LINUX)
    #define KD_ARCH_64BIT_PTR 1
#endif

#if defined KD_CPU_X86_64 && defined KD_OS_LINUX
    #define KD_ARCH_64BIT_PTR 1
#endif

#if defined KD_CPU_SPARC64 || defined KD_OS_WIN64 || defined __64BIT__ || defined __LP64 || defined _LP64 || defined __LP64__ || defined _ADDR64 || defined _CRAYC
    #define KD_ARCH_64BIT_PTR 1
#endif

#if !defined KD_ARCH_64BIT_PTR
    #define KD_ARCH_32BIT_PTR 1
#endif

#if defined KD_ARCH_64BIT_PTR
    #define KD_ARCH_PTR_CSTR "64 bit"
#elif defined KD_ARCH_32BIT_PTR
    #define KD_ARCH_PTR_CSTR "32 bit"
#else
    #define KD_ARCH_PTR_CSTR "Unknown"
#endif /* KD_ARCH_64BIT_PTR */


/**
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *  Constant Values/Macros
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

#define KD_RESULT_SUCCESS 0
#define KD_RESULT_FAILURE 1
#define KD_EXIT_SUCCESS   0
#define KD_EXIT_FAILURE   1


/**
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *  Simplified versions of macros without library initials/prefix
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

#define RESULT_SUCCESS KD_RESULT_SUCCESS
#define RESULT_FAILURE KD_RESULT_FAILURE
#define EXIT_SUCCESS   KD_EXIT_SUCCESS
#define EXIT_FAILURE   KD_EXIT_FAILURE

#define COMP_CSTR KD_COMP_CSTR

#if defined KD_COMP_INTEL
  #define COMP_INTEL KD_COMP_INTEL
#endif

#if defined KD_COMP_MIPSPRO
  #define COMP_MIPSPRO KD_COMP_MIPSPRO
#endif

#if defined KD_COMP_HPCC
  #define COMP_HPCC KD_COMP_HPCC
#endif

#if defined KD_COMP_GCC
  #define COMP_GCC KD_COMP_GCC
#endif

#if defined KD_COMP_APPLECC
  #define COMP_APPLECC KD_COMP_APPLECC
#endif

#if defined KD_COMP_IBM
  #define COMP_IBM KD_COMP_IBM
#endif

#if defined KD_COMP_MSVC
  #define COMP_MSVC KD_COMP_MSVC
#endif

#if defined KD_COMP_SUN
  #define COMP_SUN KD_COMP_SUN
#endif

#if defined KD_COMP_BORLAND
  #define COMP_BORLAND KD_COMP_BORLAND
#endif

#if defined KD_COMP_METROWERKS
  #define COMP_METROWERKS KD_COMP_METROWERKS
#endif

#if defined KD_COMP_DEC
  #define COMP_DEC KD_COMP_DEC
#endif

#if defined KD_COMP_WATCOM
  #define COMP_WATCOM KD_COMP_WATCOM
#endif

#define C_STD_NO   KD_C_STD_NO
#define C_STD_CSTR KD_C_STD_CSTR

#if defined KD_C_STD_23
  #define C_STD_23 KD_C_STD_23
#endif

#if defined KD_C_STD_17
  #define C_STD_17 KD_C_STD_17
#endif

#if defined KD_C_STD_11
  #define C_STD_11 KD_C_STD_11
#endif

#if defined KD_C_STD_99
  #define C_STD_99 KD_C_STD_99
#endif

#if defined KD_C_STD_90
  #define C_STD_90 KD_C_STD_90
#endif

#if defined KD_C_STD_89
  #define C_STD_89 KD_C_STD_89
#endif

#if defined KD_C_STD_89_90
  #define C_STD_89_90 KD_C_STD_89_90
#endif

#define OS_CSTR KD_OS_CSTR

#if defined KD_OS_LINUX
  #define OS_LINUX KD_OS_LINUX
#endif

#if defined KD_OS_CYGWIN32
  #define OS_CYGWIN32 KD_OS_CYGWIN32
#endif

#if defined KD_OS_GAMECUBE
  #define OS_GAMECUBE KD_OS_GAMECUBE
#endif

#if defined KD_OS_MINGW
  #define OS_MINGW KD_OS_MINGW
#endif

#if defined KD_OS_MINGW32
  #define OS_MINGW32 KD_OS_MINGW32
#endif

#if defined KD_OS_MINGW64
  #define OS_MINGW64 KD_OS_MINGW64
#endif

#if defined KD_OS_GO32
  #define OS_GO32 KD_OS_GO32
#endif

#if defined KD_OS_DOS32
  #define OS_DOS32 KD_OS_DOS32
#endif

#if defined KD_OS_UNICOS
  #define OS_UNICOS KD_OS_UNICOS
#endif

#if defined KD_OS_OSX
  #define OS_OSX KD_OS_OSX
#endif

#if defined KD_OS_SOLARIS
  #define OS_SOLARIS KD_OS_SOLARIS
#endif

#if defined KD_OS_SUNOS
  #define OS_SUNOS KD_OS_SUNOS
#endif

#if defined KD_OS_IRIX
  #define OS_IRIX KD_OS_IRIX
#endif

#if defined KD_OS_HPUX
  #define OS_HPUX KD_OS_HPUX
#endif

#if defined KD_OS_AIX
  #define OS_AIX KD_OS_AIX
#endif

#if defined KD_OS_TRU64
  #define OS_TRU64 KD_OS_TRU64
#endif

#if defined KD_OS_BEOS
  #define OS_BEOS KD_OS_BEOS
#endif

#if defined KD_OS_AMIGA
  #define OS_AMIGA KD_OS_AMIGA
#endif

#if defined KD_OS_UNIX
  #define OS_UNIX KD_OS_UNIX
#endif

#if defined KD_OS_WINDOWS
  #define OS_WINDOWS KD_OS_WINDOWS
#endif

#if defined KD_OS_WIN32
  #define OS_WIN32 KD_OS_WIN32
#endif

#if defined KD_OS_WIN64
  #define OS_WIN64 KD_OS_WIN64
#endif

#if defined KD_OS_WINCE
  #define OS_WINCE KD_OS_WINCE
#endif

#if defined KD_OS_XBOX
  #define OS_XBOX KD_OS_XBOX
#endif

#if defined KD_OS_PALM
  #define OS_PALM KD_OS_PALM
#endif

#if defined KD_OS_MACOS
  #define OS_MACOS KD_OS_MACOS
#endif

#define CPU_CSTR KD_CPU_CSTR

#if defined KD_CPU_68K
  #define CPU_68K KD_CPU_68K
#endif

#if defined KD_CPU_PPC750
  #define CPU_PPC750 KD_CPU_PPC750
#endif

#if defined KD_CPU_PPC
  #define CPU_PPC KD_CPU_PPC
#endif

#if defined KD_CPU_PPC32
  #define CPU_PPC32 KD_CPU_PPC32
#endif

#if defined KD_CPU_PPC64
  #define CPU_PPC64 KD_CPU_PPC64
#endif

#if defined KD_CPU_CRAYT3E
  #define CPU_CRAYT3E KD_CPU_CRAYT3E
#endif

#if defined KD_CPU_SH3
  #define CPU_SH3 KD_CPU_SH3
#endif

#if defined KD_CPU_SH4
  #define CPU_SH4 KD_CPU_SH4
#endif

#if defined KD_CPU_SPARC
  #define CPU_SPARC KD_CPU_SPARC
#endif

#if defined KD_CPU_SPARC64
  #define CPU_SPARC64 KD_CPU_SPARC64
#endif

#if defined KD_CPU_ARM
  #define CPU_ARM KD_CPU_ARM
#endif

#if defined KD_CPU_MIPS
  #define CPU_MIPS KD_CPU_MIPS
#endif

#if defined KD_CPU_IA64
  #define CPU_IA64 KD_CPU_IA64
#endif

#if defined KD_CPU_X86
  #define CPU_X86 KD_CPU_X86
#endif

#if defined KD_CPU_X86_64
  #define CPU_X86_64 KD_CPU_X86_64
#endif

#if defined KD_CPU_AXP
  #define CPU_AXP KD_CPU_AXP
#endif

#if defined KD_CPU_HPPA
  #define CPU_HPPA KD_CPU_HPPA
#endif

#define ENDIAN_CSTR KD_ENDIAN_CSTR

#if defined KD_ENDIAN_LITTLE
  #define ENDIAN_LITTLE KD_ENDIAN_LITTLE
#endif

#if defined KD_ENDIAN_BIG
  #define ENDIAN_BIG KD_ENDIAN_BIG
#endif

#define ARCH_INT_CSTR KD_ARCH_INT_CSTR
#define ARCH_PTR_CSTR KD_ARCH_PTR_CSTR

#if defined KD_ARCH_64BIT_INT
  #define ARCH_64BIT_INT KD_ARCH_64BIT_INT
#endif

#if defined KD_ARCH_32BIT_INT
  #define ARCH_32BIT_INT KD_ARCH_32BIT_INT
#endif

#if defined KD_ARCH_64BIT_PTR
  #define ARCH_64BIT_PTR KD_ARCH_64BIT_PTR
#endif

#if defined KD_ARCH_32BIT_PTR
  #define ARCH_32BIT_PTR KD_ARCH_32BIT_PTR
#endif

#define CDECL    KD_CDECL
#define STDCALL  KD_STDCALL
#define FASTCALL KD_FASTCALL

#define IMPORTEXPORT KD_IMPORTEXPORT

#define EXTERN_BEGIN KD_EXTERN_BEGIN
#define EXTERN_END   KD_EXTERN_END
#define CPLUSPLUS    KD_CPLUSPLUS



/**
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 *  Cleaning up
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

#ifdef KD_DLL
    #undef KD_DLL
#endif /* KD_DLL */

#ifdef KD_BUILDING_LIB
    #undef KD_BUILDING_LIB
#endif /* KD_BUILDING_LIB */

#endif /* KD_PLATFORM_H_ */
