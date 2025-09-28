/**
 * @file kd_mem.c
 * @author Kumarjit Das
 * @version 0.0.1
 * @brief Main source file of the KD_MEM library.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 * @since 0.0.1
 */


#include "kd_version.h"

#define KD_BUILDING_LIB 1
#include "kd_platform.h"

#if defined KD_OS_WINDOWS
KD_EXTERN_BEGIN
  #include <windows.h>
KD_EXTERN_END
#else
  #include <stdlib.h>
#endif

#include "kd_fixed_width.h"
#include "kd_mem.h"


kd_bool_t
kdMemAlloc(void *dst, kd_usize_t sz)
{
#if defined KD_OS_WINDOWS
  HANDLE heap;
#endif
  kd_byte_t *ptr;

  if (!dst)
  {
    return KD_RESULT_FAILURE;
  }

  *(kd_byte_t **)dst = kd_null;

  if (!sz)
  {
    return KD_RESULT_FAILURE;
  }

#if defined KD_OS_WINDOWS
  heap = GetProcessHeap();
  if (!heap)
  {
    return KD_RESULT_FAILURE;
  }

  ptr = HeapAlloc(heap, 0, sz);
#else
  ptr = malloc(sz);
#endif

  if (!ptr)
  {
    return KD_RESULT_FAILURE;
  }

  *(kd_byte_t **)dst = ptr;

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemFree(void *dst, kd_usize_t sz)
{
#if defined KD_OS_WINDOWS
  HANDLE heap;
#endif
  kd_byte_t **dst_adr = dst;

  (void)sz;

  if (!dst_adr || !*dst_adr)
  {
    return KD_RESULT_FAILURE;
  }

#if defined KD_OS_WINDOWS
  heap = GetProcessHeap();
  if (!heap)
  {
    return KD_RESULT_FAILURE;
  }

  if (!HeapFree(heap, 0, *dst_adr))
  {
    return KD_RESULT_FAILURE;
  }
#else
  free(*dst_adr);
#endif

  *dst_adr = kd_null;

  return KD_RESULT_SUCCESS;
}


kd_bool_t
kdMemRealloc(void *dst, kd_usize_t new_sz, void *src, kd_usize_t old_sz)
{
#if defined KD_OS_WINDOWS
  HANDLE heap;
#endif
  kd_byte_t **dst_adr = dst, **src_adr, *temp_ptr, *ptr = kd_null;

  (void)old_sz;

  if (!dst_adr)
  {
    return KD_RESULT_FAILURE;
  }

  *dst_adr = kd_null;
  src_adr  = src;
  temp_ptr = src ? *src_adr : kd_null;

#if defined KD_OS_WINDOWS
  heap = GetProcessHeap();
  if (!heap)
  {
    return KD_RESULT_FAILURE;
  }
#endif

  if (temp_ptr)
  {
    *src_adr = kd_null;

    if (!new_sz)
    {
#if defined KD_OS_WINDOWS
      return !HeapFree(heap, 0, temp_ptr);
#else
      free(temp_ptr);
      return KD_RESULT_SUCCESS;
#endif
    }

#if defined KD_OS_WINDOWS
    ptr = HeapReAlloc(heap, 0, temp_ptr, new_sz);
#else
    ptr = realloc(temp_ptr, new_sz);
#endif

    if (!ptr)
    {
      return KD_RESULT_FAILURE;
    }
  }
  else if (new_sz)
  {
#if defined KD_OS_WINDOWS
    ptr = HeapAlloc(heap, 0, new_sz);
#else
    ptr = malloc(new_sz);
#endif

    if (!ptr)
    {
      return KD_RESULT_FAILURE;
    }
  }
  else
  {
    return KD_RESULT_FAILURE;
  }

  *dst_adr = ptr;

  return KD_RESULT_SUCCESS;
}
