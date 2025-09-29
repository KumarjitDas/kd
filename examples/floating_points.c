/**
 * @file fixed_widths.c
 * @author Kumarjit Das
 * @brief Floating point types example.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>

#define KD_USE_SIMPLIFIED_TYPES
#include "kd.h"


int
main(int argc, char **argv)
{
    f32 val_f32;
    f64 val_f64;

    (void)argc;
    (void)argv;

    printf("Floating point types example :: begin\n");

    printf("\nAPI Version: %s\n", KD_VERSION_CSTR);

    printf("\nSizes of types:\n\n");

    printf("KD_SZ_F32 = %d,\n", (int)KD_SZ_F32);
    printf("KD_SZ_F64 = %d,\n", (int)KD_SZ_F64);

    printf("\nMinimum values of types:\n\n");

    printf("KD_MIN_F32 = " KD_FMTSP_F32 ",\n", KD_FSBTC_F32(KD_MIN_F32));
    printf("KD_MIN_F64 = " KD_FMTSP_F64 ",\n", KD_FSBTC_F64(KD_MIN_F64));
    printf("KD_MIN_FMIN = " KD_FMTSP_FMIN ",\n", KD_FSBTC_FMIN(KD_MIN_FMIN));
    printf("KD_MIN_FMAX = " KD_FMTSP_FMAX ",\n", KD_FSBTC_FMAX(KD_MIN_FMAX));

    printf("\nMaximum values of types:\n\n");

    printf("KD_MAX_F32 = " KD_FMTSP_F32 ",\n", KD_FSBTC_F32(KD_MAX_F32));
    printf("KD_MAX_F64 = " KD_FMTSP_F64 ",\n", KD_FSBTC_F64(KD_MAX_F64));
    printf("KD_MAX_FMIN = " KD_FMTSP_FMIN ",\n", KD_FSBTC_FMIN(KD_MAX_FMIN));
    printf("KD_MAX_FMAX = " KD_FMTSP_FMAX ",\n", KD_FSBTC_FMAX(KD_MAX_FMAX));

    printf("\nValues of constant values:\n\n");
    printf("...\n");

    printf("\nValues of types:\n\n");

    val_f32 = KD_MAX_F32;
    val_f64 = KD_MAX_F64;

    printf("val_f32 = " KD_FMTSP_F32 ",\n", KD_FSBTC_F32(val_f32));
    printf("val_f64 = " KD_FMTSP_F64 ",\n", KD_FSBTC_F64(val_f64));

    printf("\nFloating point types example :: end\n");

    return KD_EXIT_SUCCESS;
}
