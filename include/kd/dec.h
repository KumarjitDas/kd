/**
 * @file dec.h
 * @author Kumarjit Das
 * @version 0.0.1
 * @brief Main header file of the KD_DEC library.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 * @since 0.0.1
 */


#ifndef KD_DEC_H_
#define KD_DEC_H_


#include "./version.h"
#include "./platform.h"
#include "./api.h"
#include "./fixed_width.h"


KD_EXTERN_BEGIN


typedef kd_word_t kd_dec_t;

#define KD_LIT_DEC(x)   KD_LIT_WORD(x)
#define KD_DEC_C(X)     ((kd_dec_t)(X))
#define KD_PDEC_C(X)    ((kd_dec_t *)(X))
#define KD_MIN_DEC      KD_MAX_WORD
#define KD_MAX_DEC      KD_MAX_WORD
#define KD_SZ_DEC       sizeof(kd_dec_t)
#define KD_FMTSP_DEC    KD_FMTSP_WORD
#define KD_FSBTC_DEC(x) KD_FSBTC_WORD(x)

#if defined KD_USE_SIMPLIFIED_TYPES
typedef kd_dec_t dec;
#endif /* KD_USE_SIMPLIFIED_TYPES */


KD_EXTERN_END


#endif /* KD_DEC_H_ */
