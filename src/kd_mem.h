/**
 * @file kd_mem.h
 * @author Kumarjit Das
 * @version 0.0.1
 * @brief Main header file of the KD_MEM library.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 * @since 0.0.1
 */


#ifndef KD_MEM_H_
#define KD_MEM_H_


#include "kd_version.h"
#include "kd_platform.h"
#include "kd_fixed_width.h"


KD_EXTERN_BEGIN


#define KD_MEM_VERSION_MAJOR 0
#define KD_MEM_VERSION_MINOR 0
#define KD_MEM_VERSION_PATCH 1

#define KD_MEM_VERSION_CSTR  KDI_STRINGIFY(KD_MEM_VERSION_MAJOR) "." KDI_STRINGIFY(KD_MEM_VERSION_MINOR) "." KDI_STRINGIFY(KD_MEM_VERSION_PATCH)
#define KD_MEM_VERSION_ARR   {KD_MEM_VERSION_MAJOR, KD_MEM_VERSION_MINOR, KD_MEM_VERSION_PATCH}


KDAPI(kd_bool_t) kdMemAlloc(void *dst, kd_usize_t sz);
KDAPI(kd_bool_t) kdMemFree(void *dst, kd_usize_t sz);
KDAPI(kd_bool_t) kdMemRealloc(void *dst, kd_usize_t new_sz, void *src, kd_usize_t old_sz);


KD_EXTERN_END


#endif /* KD_MEM_H_ */
