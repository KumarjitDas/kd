/**
 * @file mem.h
 * @author Kumarjit Das
 * @version 0.0.1
 * @brief Header file for Windows OS specific functionalities of KD_MEM library.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 * @since 0.0.1
 */


#ifndef KDI_WINDOWS_MEM_H_
#define KDI_WINDOWS_MEM_H_


#include "../../../include/kd/version.h"
#include "../../../include/kd/platform.h"
#include "../../../include/kd/fixed_width.h"


#if !defined KD_OS_WINDOWS && !(defined KD_OS_WIN32 || defined KD_OS_WIN64)
    #error This translation unit is only compilable for Microsoft Windows platforms.
#endif


KD_EXTERN_BEGIN


KDAPI(bool) kdi_windows_MemAlloc(void *dst, usize sz);
KDAPI(bool) kdi_windows_MemFree(void *dst, usize sz);
KDAPI(bool) kdi_windows_MemRealloc(void *dst, usize new_sz, void *src, usize old_sz);


KD_EXTERN_END


#endif /* KDI_WINDOWS_MEM_H_ */
