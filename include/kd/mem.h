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


#include "./version.h"
#include "./platform.h"
#include "./fixed_width.h"


KD_EXTERN_BEGIN


KDAPI(kd_bool_t) kdMemAlloc(void *dst, kd_usize_t sz);
KDAPI(kd_bool_t) kdMemFree(void *dst, kd_usize_t sz);
KDAPI(kd_bool_t) kdMemRealloc(void *dst, kd_usize_t new_sz, void *src, kd_usize_t old_sz);

#define MemAlloc   kdMemAlloc
#define MemFree    kdMemFree
#define MemRealloc kdMemRealloc


KD_EXTERN_END


#endif /* KD_MEM_H_ */
