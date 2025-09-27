/**
 * @file kd_version.h
 * @author Kumarjit Das
 * @version 0.0.1
 * @brief Version info of the KD library.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 * @since 0.0.1
 */


#ifndef KD_VERSION_H_
#define KD_VERSION_H_


#define KD_VERSION_MAJOR       0
#define KD_VERSION_MINOR       0
#define KD_VERSION_PATCH       1

#define KDI_STRINGIFY_HELPER(x) #x
#define KDI_STRINGIFY(x)        KDI_STRINGIFY_HELPER(x)

#define KD_VERSION_CSTR        KDI_STRINGIFY(KD_VERSION_MAJOR) "." KDI_STRINGIFY(KD_VERSION_MINOR) "." KDI_STRINGIFY(KD_VERSION_PATCH)
#define KD_VERSION_ARR         {KD_VERSION_MAJOR, KD_VERSION_MINOR, KD_VERSION_PATCH}


#endif /* KD_VERSION_H_ */
