/**
 * @file platform_cstr_macros.c
 * @author Kumarjit Das
 * @brief System information C-string macros example.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>
#include "kd.h"


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("System information C-string macros example :: begin\n\n");

    printf("API Version: %s\n", KD_VERSION_CSTR);
    printf("Compiler: %s\n", KD_COMP_CSTR);
    printf("C Standard: %s\n", KD_C_STD_CSTR);
    printf("Target Operating System: %s\n", KD_OS_CSTR);
    printf("Target CPU: %s\n", KD_CPU_CSTR);
    printf("Target Architecture Integer Size: %s\n", KD_ARCH_INT_CSTR);
    printf("Target Architecture Pointer(Address) Size: %s\n", KD_ARCH_PTR_CSTR);
    printf("Endianness: %s\n", KD_ENDIAN_CSTR);

    printf("\nSystem information C-string macros example :: end\n\n");

    return KD_EXIT_SUCCESS;
}
