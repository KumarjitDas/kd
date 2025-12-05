/**
 * @file mem_algn.h
 * @author Kumarjit Das
 * @version 0.0.1
 * @brief Main header file of the KD_MEM_ALGN library.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 * @since 0.0.1
 */


#ifndef KD_MEM_ALGN_H_
#define KD_MEM_ALGN_H_


#include "./version.h"
#include "./platform.h"
#include "./fixed_width.h"


KD_EXTERN_BEGIN


#define KD_MEM_ALGN_MAX_ALGN_SIZE  128
#define KD_MEM_ALGN_DEFAULT_OFFSET KD_SZ_U8
#define KD_MEM_ALGN_MAX_OFFSET     KD_SZ_UMAX


KDAPI(kd_usize_t) kdMemAlgnGetAllocSize(kd_usize_t usable_size, kd_u8_t algn_sz, kd_u8_t offset);
KDAPI(void *) kdMemAlgnGetForwardPtr(void *head_ptr, kd_u8_t algn_sz, kd_u8_t offset);
KDAPI(void *) kdMemAlgnGetBackwardPtr(void *head_ptr, kd_u8_t algn_sz, kd_u8_t offset);
KDAPI(void *) kdMemAlgnGetOffsetPtr(void *head_ptr, kd_u8_t algn_sz, kd_u8_t offset);
KDAPI(void *) kdMemAlgnGetHeadPtr(void *off_ptr, kd_u8_t offset);


#define kdMemAlgnGetDefaultAllocSize(usable_size, algn_sz) kdMemAlgnGetAllocSize(usable_size, algn_sz, KD_MEM_ALGN_DEFAULT_OFFSET)
#define kdMemAlgnGetDefaultOffsetPtr(head_ptr, algn_sz)    kdMemAlgnGetOffsetPtr(head_ptr, algn_sz, KD_MEM_ALGN_DEFAULT_OFFSET)
#define kdMemAlgnGetDefaultHeadPtr(off_ptr)                kdMemAlgnGetHeadPtr(off_ptr, KD_MEM_ALGN_DEFAULT_OFFSET)

#define MemAlgnGetAllocSize                                kdMemAlgnGetAllocSize
#define MemAlgnGetForwardPtr                               kdMemAlgnGetForwardPtr
#define MemAlgnGetBackwardPtr                              kdMemAlgnGetBackwardPtr
#define MemAlgnGetOffsetPtr                                kdMemAlgnGetOffsetPtr
#define MemAlgnGetHeadPtr                                  kdMemAlgnGetHeadPtr

#define MemAlgnGetDefaultAllocSize                         kdMemAlgnGetDefaultAllocSize
#define MemAlgnGetDefaultOffsetPtr                         kdMemAlgnGetDefaultOffsetPtr
#define MemAlgnGetDefaultHeadPtr                           kdMemAlgnGetDefaultHeadPtr


KD_EXTERN_END


#endif /* KD_MEM_ALGN_H_ */
