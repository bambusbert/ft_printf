#include <stdio.h>
#include <limits.h>
#include "ft_printf.h" // Make sure this path is correct for your project
#include "ft_printf.c"

// Simple color codes for visual feedback
#define GREEN "\033[0;32m"
#define RED   "\033[0;31m"
#define RESET "\033[0m"

// A simple macro to run and check a test case
// It compares the return value of your ft_printf with the real printf
// and prints the output of both for visual inspection.
#define RUN_TEST(description, format, ...) \
    do { \
        printf("--- %s ---\n", description); \
        int real_printf_ret, ft_printf_ret; \
        \
        printf("Real printf: "); \
        fflush(stdout); /* Ensure 'Real printf: ' prints before potential crash */ \
        real_printf_ret = printf(format, ##__VA_ARGS__); \
        printf("\n"); \
        \
        printf(" ft_printf: "); \
        fflush(stdout); /* Ensure ' ft_printf: ' prints before potential crash */ \
        ft_printf_ret = ft_printf(format, ##__VA_ARGS__); \
        printf("\n"); \
        \
        if (real_printf_ret == ft_printf_ret) { \
            printf(GREEN "OK (return value: %d)\n\n" RESET, real_printf_ret); \
        } else { \
            printf(RED "FAIL (return values differ! Real: %d, Yours: %d)\n\n" RESET, real_printf_ret, ft_printf_ret); \
        } \
    } while (0)

int main(void)
{
    char    *null_str = NULL;
    char    *empty_str = "";
    char    *str = "Hello, World!";
    void    *null_ptr = NULL;

    printf("=========================================\n");
    printf("        ft_printf Mandatory Tests        \n");
    printf("=========================================\n\n");

    // ===================================
    //  %% - Percent Sign
    // ===================================
    RUN_TEST("Percent Sign", "%%");
    RUN_TEST("Multiple Percent Signs", "%%%%%%");
    RUN_TEST("Percent Sign with text", "Here is a percent sign: %%");

    // ===================================
    //  %c - Character
    // ===================================
    RUN_TEST("Simple Character", "Character: %c", 'A');
    RUN_TEST("The NULL character '\\0'", "The NULL char: %c", '\0'); // A classic edge case
    RUN_TEST("Non-printable character", "Non-printable: %c", 7);

    // ===================================
    //  %s - String
    // ===================================
    RUN_TEST("Simple String", "String: %s", str);
    RUN_TEST("Empty String", "Empty string: %s", empty_str);
    RUN_TEST("NULL String Pointer", "NULL string: %s", null_str); // CRITICAL: Must print (null)

    // ===================================
    //  %d and %i - Signed Decimal Integer
    // ===================================
    RUN_TEST("Simple Integer", "Integer: %d", 42);
    RUN_TEST("Simple Integer (i)", "Integer: %i", 42);
    RUN_TEST("Negative Integer", "Negative: %d", -42);
    RUN_TEST("Zero", "Zero: %d", 0);
    RUN_TEST("INT_MAX", "INT_MAX: %d", INT_MAX);
    RUN_TEST("INT_MIN", "INT_MIN: %d", INT_MIN); // CRITICAL: -2147483648 can break naive logic
    RUN_TEST("INT_MIN (i)", "INT_MIN: %i", INT_MIN);

    // ===================================
    //  %u - Unsigned Decimal Integer
    // ===================================
    RUN_TEST("Simple Unsigned", "Unsigned: %u", 42);
    RUN_TEST("Unsigned Zero", "Unsigned Zero: %u", 0);
    RUN_TEST("UINT_MAX", "UINT_MAX: %u", UINT_MAX);
    RUN_TEST("Unsigned from negative int", "Unsigned from -1: %u", -1); // Should wrap around

    // ===================================
    //  %x and %X - Hexadecimal
    // ===================================
    RUN_TEST("Hex (lowercase) Zero", "Hex Zero: %x", 0);
    RUN_TEST("Hex (lowercase) simple", "Hex simple: %x", 255);
    RUN_TEST("Hex (lowercase) from negative", "Hex from -1: %x", -1); // Should be ffffffff
    RUN_TEST("Hex (lowercase) INT_MAX", "Hex INT_MAX: %x", INT_MAX);
    RUN_TEST("Hex (uppercase) simple", "Hex simple: %X", 255);
    RUN_TEST("Hex (uppercase) from negative", "Hex from -1: %X", -1); // Should be FFFFFFFF

    // ===================================
    //  %p - Pointer
    // ===================================
    RUN_TEST("Pointer to a variable", "Pointer: %p", &str);
    RUN_TEST("Pointer to NULL", "Pointer to NULL: %p", null_ptr); // CRITICAL: Must handle NULL pointer
    RUN_TEST("Pointer to main", "Pointer to main: %p", &main);

    // ===================================
    //  Combination Tests
    // ===================================
    RUN_TEST("Multiple Conversions", "%s %d %c %x", "Test", -123, 'Z', 42);
    RUN_TEST("No conversions", "This is just a string with no conversions.");
    RUN_TEST("Conversion at the start", "%d is the number", 123);
    RUN_TEST("Conversion at the end", "The number is %d", 456);
    RUN_TEST("All conversions", "s:%s c:%c p:%p d:%d i:%i u:%u x:%x X:%X %%",
             "str", 'C', &str, -123, -456, 789, 1024, 2048);

    return (0);
}