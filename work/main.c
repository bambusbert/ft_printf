#include <stdio.h>
#include <limits.h>
#include "ft_printf.h"
#include "ft_printf.c"
#include "utils.c"
#include "utils_hex.c"

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
            printf(RED "FAIL (return values differ! Real: %d, Mine: %d)\n\n" RESET, real_printf_ret, ft_printf_ret); \
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

    printf("-----------------------% %-----------------------\n");
    // ===================================
    //  %% - Percent Sign
    // ===================================

    RUN_TEST("1 Percent Sign", "%");
    RUN_TEST("2 Percent Signs", "%%");
    RUN_TEST("Multiple Percent Signs", "%%%%%%");
    RUN_TEST("Percent Sign with text", "Here is a percent sign: %%");

    printf("-----------------------c-----------------------\n");
    // ===================================
    //  %c - Character
    // ===================================
    RUN_TEST("Simple Character", "Character: %c", 'A');
    RUN_TEST("The NULL character '\\0'", "The NULL char: %c", '\0');
    RUN_TEST("Non-printable character", "Non-printable: %c", 7);
    RUN_TEST("character above 127", "%c", 200);
    RUN_TEST("character above 255", "%c", 260);
    RUN_TEST("character below 0", "%c", -5);
    RUN_TEST("character below -127", "%c", -150);
    RUN_TEST("character below -255", "%c", -355);

    printf("-----------------------s-----------------------\n");
    // ===================================
    //  %s - String
    // ===================================
    RUN_TEST("Simple String", "String: %s", str);
    RUN_TEST("Empty String", "Empty string: %s", empty_str);
    RUN_TEST("NULL String Pointer", "NULL string: %s", null_str);

    printf("-----------------------i-----------------------\n");
    // ===================================
    //  %d and %i - Signed Decimal Integer
    // ===================================
    RUN_TEST("Simple Integer", "Integer: %d", 42);
    RUN_TEST("Simple Integer (i)", "Integer: %i", 42);
    RUN_TEST("Negative Integer", "Negative: %d", -42);
    RUN_TEST("Zero", "Zero: %d", 0);
    RUN_TEST("INT_MAX", "INT_MAX: %d", INT_MAX);
    RUN_TEST("INT_MIN", "INT_MIN: %d", INT_MIN);
    RUN_TEST("INT_MIN (i)", "INT_MIN: %i", INT_MIN);
    RUN_TEST("INT_MAX + 1", "INT_MAX: %d", INT_MAX + 1);
    RUN_TEST("INT_MIN - 1", "INT_MIN: %d", INT_MIN - 1);
    RUN_TEST("LONG_MIN", "INT_MIN: %d", LONG_MIN);
    RUN_TEST("LONG_MAX - 1", "INT_MIN: %d", LONG_MAX);

    printf("-----------------------u-----------------------\n");
    // ===================================
    //  %u - Unsigned Decimal Integer
    // ===================================
    RUN_TEST("Simple Unsigned", "Unsigned: %u", 42);
    RUN_TEST("Unsigned Zero", "Unsigned Zero: %u", 0);
    RUN_TEST("UINT_MAX", "UINT_MAX: %u", UINT_MAX);
    RUN_TEST("Unsigned from negative int", "Unsigned from -1: %u", -1); // Should wrap around

    printf("-----------------------x&X-----------------------\n");
    // ===================================
    //  %x and %X - Hexadecimal
    // ===================================
    RUN_TEST("Hex (lowercase) Zero", "Hex Zero: %x", 0);
    RUN_TEST("Hex (lowercase) simple", "Hex simple: %x", 255);
    RUN_TEST("Hex (lowercase) from negative", "Hex from -1: %x", -1);
    RUN_TEST("Hex (lowercase) INT_MAX", "Hex INT_MAX: %x", INT_MAX);
    RUN_TEST("Hex (uppercase) simple", "Hex simple: %X", 255);
    RUN_TEST("Hex (uppercase) from negative", "Hex from -1: %X", -1);

    printf("-----------------------p-----------------------\n");
    // ===================================
    //  %p - Pointer
    // ===================================
    RUN_TEST("Pointer to a variable", "Pointer: %p", &str);
    RUN_TEST("Pointer to NULL", "Pointer to NULL: %p", null_ptr);
    RUN_TEST("Pointer to main", "Pointer to main: %p", &main);

    printf("-----------------------combo-----------------------\n");
    // ===================================
    //  Combination Tests
    // ===================================
    RUN_TEST("Multiple Conversions", "%s %d %c %x", "Test", -123, 'Z', 42);
    RUN_TEST("No conversions", "This is just a string with no conversions.");
    RUN_TEST("Conversion at the start", "%d is the number", 123);
    RUN_TEST("Conversion at the end", "The number is %d", 456);
    RUN_TEST("All conversions", "s:%s c:%c p:%p d:%d i:%i u:%u x:%x X:%X %%",
             "str", 'C', &str, -123, -456, 789, 1024, 2048);

    // ===================================
    // Edge-case tests
    // ===================================
    //DO WE HAVE TO HANDLE IT OR IS IT JUST FOR THE BONUS???
    //RUN_TEST("Width formatting fallback", "%5d",  42);        // width=5, no flag: expect padding spaces (e.g. "   42")
    RUN_TEST("Unknown format specifier", "%k",   0);         // '%k' is not standard: should print "%k" (count 2)
    RUN_TEST("NULL string for %s", "%s", (char*)NULL);      // NULL string: should output "(null)"
    RUN_TEST("Embedded null char in %c", "%c", '\0');      // printing '\0': should output a null char (no visible output, count=1)
    RUN_TEST("Negative value for %u", "%u", -1);           // negative passed to unsigned: expect max-value (e.g. 4294967295 on 32-bit)
    RUN_TEST("Max unsigned for %u", "%u", 4294967295U);    // largest unsigned int: ensure full range printed
    RUN_TEST("Negative value for %x (hex)", "%x", -1);     // negative as hex (lowercase): expect "ffffffff" for 32-bit
    RUN_TEST("Max unsigned for %x", "%x", 4294967295U);    // largest unsigned int: hex lowercase
    RUN_TEST("Max unsigned for %X", "%X", 4294967295U);    // largest unsigned int: hex uppercase
    RUN_TEST("Literal percent sign", "%%");                // "%%" should output "%" and count as 1

    RUN_TEST("Percent Sign with non valid char", "%?");
    RUN_TEST("Percent Sign with non valid char", "%?", 4, "sdfas", 7);
    RUN_TEST("Percent Sign with non valid char - multiple", "%?%?%?%?", 453, 0, "fjsdökfj");

    return (0);
}