/**
 * @file mem.h
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


/**
 * @brief Allocates a new memory block on the heap.
 *
 * This function allocates a block of @p sz bytes and stores the resulting
 * pointer into the location pointed to by @p dst_addr. The caller supplies
 * the storage for the pointer; @p dst_addr must therefore point to a variable
 * of type <tt>void *</tt> (or a compatible pointer type).
 *
 * On entry, @p dst_addr must be non-NULL and point to writable storage. On
 * failure, the location pointed to by @p dst_addr is set to NULL. On success,
 * it holds the address of the newly allocated block.
 *
 * Passing a size of zero or an invalid @p dst_addr pointer causes the
 * function to fail. The behavior is undefined if @p sz is so large that it
 * cannot be represented by the underlying allocation routines.
 *
 * This function is also available via the MemAlloc macro alias.
 *
 * @param dst_addr Address of a pointer variable that receives the allocated
 *                 block address. Must not be NULL.
 * @param sz       Number of bytes to allocate. Must be greater than zero.
 *
 * @return KD_RESULT_SUCCESS (kd_false / 0) on success,
 *         KD_RESULT_FAILURE (kd_true / 1) on failure.
 *
 * @see kdMemFree
 * @see kdMemRealloc
 */
KDAPI(kd_bool_t) kdMemAlloc(void *dst_addr, kd_usize_t sz);

/**
 * @brief Frees a heap-allocated memory block.
 *
 * This function releases a memory block that was previously allocated by
 * kdMemAlloc() or kdMemRealloc(). The pointer to the block must be stored in
 * the variable pointed to by @p dst_addr, and @p sz must match the size that
 * was originally supplied when the block was allocated.
 *
 * On success, the memory block is freed and the location pointed to by
 * @p dst_addr is set to NULL, preventing accidental reuse of a dangling
 * pointer. If @p dst_addr is NULL, if the stored pointer is NULL, or if
 * @p sz is zero, the function fails and no memory is freed.
 *
 * The behavior is undefined if @p sz does not correspond to the size of the
 * block currently pointed to by the variable at @p dst_addr, or if the block
 * was not obtained from this library.
 *
 * This function is also available via the MemFree macro alias.
 *
 * @param dst_addr Address of a pointer variable holding the block to free.
 *                 Must not be NULL and must point to a non-NULL pointer on
 *                 success.
 * @param sz       Size in bytes of the block to free. Must be the same value
 *                 that was used when the block was allocated and must be
 *                 greater than zero.
 *
 * @return KD_RESULT_SUCCESS (kd_false / 0) on success,
 *         KD_RESULT_FAILURE (kd_true / 1) on failure.
 *
 * @see kdMemAlloc
 * @see kdMemRealloc
 */
KDAPI(kd_bool_t) kdMemFree(void *dst_addr, kd_usize_t sz);

/**
 * @brief Allocates, resizes, or frees a heap-allocated memory block.
 *
 * This function combines allocation, reallocation, and deallocation in a
 * single API. It operates on pointer variables supplied by the caller rather
 * than returning the new pointer directly.
 *
 * The pointer to be managed is taken from @p src_addr if it is non-NULL; in
 * that case, @p src_addr must point to a variable of type <tt>void *</tt>
 * (or a compatible pointer type) holding the current block address. If
 * @p src_addr is NULL, the current block address is taken from the variable
 * pointed to by @p dst_addr instead. In both cases, @p old_sz must specify
 * the size in bytes of the existing block; if there is no valid existing
 * block, @p old_sz must be zero.
 *
 * - If there is a valid existing block and @p new_sz is zero, the block is
 *   freed. The location pointed to by @p dst_addr is set to NULL. If
 *   @p src_addr is non-NULL and different from @p dst_addr, the pointer
 *   stored at @p src_addr is also set to NULL.
 * - If there is a valid existing block and @p new_sz is non-zero, the block
 *   is resized to @p new_sz bytes. On success, the new block address is
 *   stored in the variable pointed to by @p dst_addr. If @p src_addr is
 *   non-NULL and different from @p dst_addr, the pointer stored at
 *   @p src_addr is set to NULL to indicate that ownership has moved.
 * - If there is no valid existing block and @p new_sz is non-zero, a new
 *   block of @p new_sz bytes is allocated and its address is stored in the
 *   variable pointed to by @p dst_addr.
 *
 * On allocation or reallocation failure, no block is freed, and any existing
 * block and pointer variables remain unchanged. The behavior is undefined if
 * @p dst_addr is NULL, if @p old_sz is non-zero but does not match the size
 * of the current block, or if the current block was not obtained from this
 * library.
 *
 * This function is also available via the MemRealloc macro alias.
 *
 * @param dst_addr Address of a pointer variable that receives the resulting
 *                 block address. Must not be NULL.
 * @param new_sz   New requested size in bytes. A value of zero requests that
 *                 the current block (if any) be freed.
 * @param src_addr Address of a pointer variable holding the current block
 *                 address, or NULL to use the variable pointed to by
 *                 @p dst_addr as the source. May be equal to @p dst_addr.
 * @param old_sz   Size in bytes of the current block referenced by
 *                 @p src_addr or @p dst_addr. Must be zero if there is no
 *                 valid current block.
 *
 * @return KD_RESULT_SUCCESS (kd_false / 0) on success,
 *         KD_RESULT_FAILURE (kd_true / 1) on failure.
 *
 * @see kdMemAlloc
 * @see kdMemFree
 */
KDAPI(kd_bool_t) kdMemRealloc(void *dst_addr, kd_usize_t new_sz, void *src_addr, kd_usize_t old_sz);

#define MemAlloc   kdMemAlloc   /* For documentation, see kdMemAlloc */
#define MemFree    kdMemFree    /* For documentation, see kdMemFree */
#define MemRealloc kdMemRealloc /* For documentation, see kdMemRealloc */


KD_EXTERN_END


#endif /* KD_MEM_H_ */
