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
#include "../../../include/kd/api.h"
#include "../../../include/kd/fixed_width.h"
#include "../../../include/kd/bool.h"


#if !defined OS_WINDOWS && !(defined OS_WIN32 || defined OS_WIN64)
    #error This translation unit is only compilable for Microsoft Windows platforms.
#endif


EXTERN_BEGIN


/**
 * @internal
 * Windows-specific backend implementation of kdMemAlloc().
 * Has the same contract and return semantics as kdMemAlloc().
 */
KDAPI(bool) kdi_windows_MemAlloc(void *dst_addr, usize sz);

/**
 * @internal
 * Windows-specific backend implementation of kdMemFree().
 * Has the same contract and return semantics as kdMemFree().
 */
KDAPI(bool) kdi_windows_MemFree(void *dst_addr, usize sz);

/**
 * @internal
 * Windows-specific backend implementation of kdMemRealloc().
 * Has the same contract and return semantics as kdMemRealloc().
 */
KDAPI(bool) kdi_windows_MemRealloc(void *dst_addr, usize new_sz, void *src_addr, usize old_sz);


EXTERN_END


#endif /* KDI_WINDOWS_MEM_H_ */
