/**
 * @file api.h
 * @author Kumarjit Das
 * @version 0.0.1
 * @brief Main API of the kd library.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 * @since 0.0.1
 */


#ifndef KD_API_H_
#define KD_API_H_


#include "./platform.h"


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
 *  Simplified versions of macros without library initials/prefix
 * ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

#define CDECL    KD_CDECL
#define STDCALL  KD_STDCALL
#define FASTCALL KD_FASTCALL

#define IMPORTEXPORT KD_IMPORTEXPORT


#endif /* KD_API_H_ */
