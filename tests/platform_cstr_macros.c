/**
 * @file platform_cstr_macros.c
 * @author Kumarjit Das
 * @brief System information C-string macros test.
 * @license BSD 3-Clause License
 * @copyright Copyright (c) 2025, Kumarjit Das.
 */


#include <stdio.h>

#include "../include/kd.h"


int
main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    printf("System information C-string macros test :: begin\n\n");

    printf("API Version: %s\n", KD_VERSION_CSTR);
    printf("Compiler: %s\n", COMP_CSTR);
    printf("C Standard: %s\n", C_STD_CSTR);
    printf("Target Operating System: %s\n", OS_CSTR);
    printf("Target CPU: %s\n", CPU_CSTR);
    printf("Target Architecture Integer Size: %s\n", ARCH_INT_CSTR);
    printf("Target Architecture Pointer(Address) Size: %s\n", ARCH_PTR_CSTR);
    printf("Endianness: %s\n", ENDIAN_CSTR);

    printf("\nSystem information C-string macros test :: end\n\n");

    return EXIT_SUCCESS;
}
