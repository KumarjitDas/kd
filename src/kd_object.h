/**
 * @file kd_object.h
 * @author Kumarjit Das
 * @version 0.0.1
 * @brief Main header file of the KD_OBJECT library.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 * @since 0.0.1
 */


#ifndef KD_OBJECT_H_
#define KD_OBJECT_H_


#include "kd_version.h"
#include "kd_platform.h"
#include "kd_eltype.h"
#include "kd_any.h"


KD_EXTERN_BEGIN


struct kd_Object_t
{
    enum kd_eltype_t type;
    union kd_any_t   value;
};


#define KD_POBJECT_C(X) ((struct kd_Object_t *)(X))
#define KD_SZ_OBJECT    sizeof(struct kd_Object_t)

#if defined KD_USE_SIMPLIFIED_TYPES
typedef struct kd_Object_t Object;
#endif /* KD_USE_SIMPLIFIED_TYPES */


KD_EXTERN_END


#endif /* KD_OBJECT_H_ */
