/**
 * @file fixed_widths.c
 * @author Kumarjit Das
 * @brief Fixed width integral types example.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>

#define KD_USE_SIMPLIFIED_TYPES
#include "kd.h"


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("Fixed width integral types example :: begin\n");

    printf("\nAPI Version: %s\n", KD_VERSION_CSTR);

    printf("\nSizes of types:\n\n");
    printf("KD_SZ_BOOL = %d,\n", (int)KD_SZ_BOOL);
    printf("KD_SZ_I8 = %d,\n", (int)KD_SZ_I8);
    printf("KD_SZ_I16 = %d,\n", (int)KD_SZ_I16);
    printf("KD_SZ_I32 = %d,\n", (int)KD_SZ_I32);
    printf("KD_SZ_IMIN = %d,\n", (int)KD_SZ_IMIN);
    printf("KD_SZ_IMAX = %d,\n", (int)KD_SZ_IMAX);
    printf("KD_SZ_U8 = %d,\n", (int)KD_SZ_U8);
    printf("KD_SZ_U16 = %d,\n", (int)KD_SZ_U16);
    printf("KD_SZ_U32 = %d,\n", (int)KD_SZ_U32);
    printf("KD_SZ_UMIN = %d,\n", (int)KD_SZ_UMIN);
    printf("KD_SZ_UMAX = %d,\n", (int)KD_SZ_UMAX);
#if defined KD_FW_64BIT_INT
    printf("KD_SZ_I64 = %d,\n", (int)KD_SZ_I64);
    printf("KD_SZ_U64 = %d,\n", (int)KD_SZ_U64);
#endif /* KD_FW_64BIT_INT */
    printf("KD_SZ_WORD = %d,\n", (int)KD_SZ_WORD);
    printf("KD_SZ_USIZE = %d,\n", (int)KD_SZ_USIZE);
    printf("KD_SZ_BYTE = %d,\n", (int)KD_SZ_BYTE);
    printf("KD_SZ_CHR = %d,\n", (int)KD_SZ_CHR);
    printf("KD_SZ_PTR = %d,\n", (int)KD_SZ_PTR);

    printf("\nMinimum values of types:\n\n");
    printf("KD_MIN_I8 = " KD_FMTSP_I8 ",\n", KD_FSBTC_I8(KD_MIN_I8));
    printf("KD_MIN_I16 = " KD_FMTSP_I16 ",\n", KD_FSBTC_I16(KD_MIN_I16));
    printf("KD_MIN_I32 = " KD_FMTSP_I32 ",\n", KD_FSBTC_I32(KD_MIN_I32));
    printf("KD_MIN_IMIN = " KD_FMTSP_IMIN ",\n", KD_FSBTC_IMIN(KD_MIN_IMIN));
    printf("KD_MIN_IMAX = " KD_FMTSP_IMAX ",\n", KD_FSBTC_IMAX(KD_MIN_IMAX));
    printf("KD_MIN_U8 = " KD_FMTSP_U8 ",\n", KD_FSBTC_U8(KD_MIN_U8));
    printf("KD_MIN_U16 = " KD_FMTSP_U16 ",\n", KD_FSBTC_U16(KD_MIN_U16));
    printf("KD_MIN_U32 = " KD_FMTSP_U32 ",\n", KD_FSBTC_U32(KD_MIN_U32));
    printf("KD_MIN_UMIN = " KD_FMTSP_UMIN ",\n", KD_FSBTC_UMIN(KD_MIN_UMIN));
    printf("KD_MIN_UMAX = " KD_FMTSP_UMAX ",\n", KD_FSBTC_UMAX(KD_MIN_UMAX));
#if defined KD_FW_64BIT_INT
    printf("KD_MIN_I64 = " KD_FMTSP_I64 ",\n", KD_FSBTC_I64(KD_MIN_I64));
    printf("KD_MIN_U64 = " KD_FMTSP_U64 ",\n", KD_FSBTC_U64(KD_MIN_U64));
#endif
    printf("KD_MIN_WORD = " KD_FMTSP_WORD ",\n", KD_FSBTC_WORD(KD_MIN_WORD));
    printf("KD_MIN_USIZE = " KD_FMTSP_USIZE ",\n", KD_FSBTC_USIZE(KD_MIN_USIZE));
    printf("KD_MIN_BYTE = " KD_FMTSP_BYTE ",\n", KD_FSBTC_BYTE(KD_MIN_BYTE));
    printf("KD_MIN_CHR = " KD_FMTSP_CHR ",\n", KD_FSBTC_CHR(KD_MIN_CHR));
    printf("KD_MIN_PTR = " KD_FMTSP_PTR ",\n", KD_MIN_PTR);

    printf("\nMaximum values of types:\n\n");
    printf("KD_MAX_I8 = " KD_FMTSP_I8 ",\n", KD_FSBTC_I8(KD_MAX_I8));
    printf("KD_MAX_I16 = " KD_FMTSP_I16 ",\n", KD_FSBTC_I16(KD_MAX_I16));
    printf("KD_MAX_I32 = " KD_FMTSP_I32 ",\n", KD_FSBTC_I32(KD_MAX_I32));
    printf("KD_MAX_IMIN = " KD_FMTSP_IMIN ",\n", KD_FSBTC_IMIN(KD_MAX_IMIN));
    printf("KD_MAX_IMAX = " KD_FMTSP_IMAX ",\n", KD_FSBTC_IMAX(KD_MAX_IMAX));
    printf("KD_MAX_U8 = " KD_FMTSP_U8 ",\n", KD_FSBTC_U8(KD_MAX_U8));
    printf("KD_MAX_U16 = " KD_FMTSP_U16 ",\n", KD_FSBTC_U16(KD_MAX_U16));
    printf("KD_MAX_U32 = " KD_FMTSP_U32 ",\n", KD_FSBTC_U32(KD_MAX_U32));
    printf("KD_MAX_UMIN = " KD_FMTSP_UMIN ",\n", KD_FSBTC_UMIN(KD_MAX_UMIN));
    printf("KD_MAX_UMAX = " KD_FMTSP_UMAX ",\n", KD_FSBTC_UMAX(KD_MAX_UMAX));
#if defined KD_FW_64BIT_INT
    printf("KD_MAX_I64 = " KD_FMTSP_I64 ",\n", KD_FSBTC_I64(KD_MAX_I64));
    printf("KD_MAX_U64 = " KD_FMTSP_U64 ",\n", KD_FSBTC_U64(KD_MAX_U64));
#endif
    printf("KD_MAX_WORD = " KD_FMTSP_WORD ",\n", KD_FSBTC_WORD(KD_MAX_WORD));
    printf("KD_MAX_USIZE = " KD_FMTSP_USIZE ",\n", KD_FSBTC_USIZE(KD_MAX_USIZE));
    printf("KD_MAX_BYTE = " KD_FMTSP_BYTE ",\n", KD_FSBTC_BYTE(KD_MAX_BYTE));
    printf("KD_MAX_CHR = " KD_FMTSP_CHR ",\n", KD_FSBTC_CHR(KD_MAX_CHR));
    printf("KD_MAX_PTR = " KD_FMTSP_PTR ",\n", KD_MAX_PTR);

    printf("\nConstant values:\n\n");
    printf("true = " KD_FMTSP_BOOL ",\n", KD_FSBTC_BOOL(true));
    printf("false = " KD_FMTSP_BOOL ",\n", KD_FSBTC_BOOL(false));
    printf("null = " KD_FMTSP_PTR ",\n", null);

    printf("\nFixed width integral types example :: end\n");

    return KD_EXIT_SUCCESS;
}
