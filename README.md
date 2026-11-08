*This project has been created as part of the 42 curriculum by oerrachi.*

# ft_printf

## Description

**ft_printf** is a re-implementation of the C standard library function `printf()`.
The goal of the project is to learn how to write **variadic functions** in C
(functions that take a variable number of arguments) and how to build a clean,
extensible program that parses a format string and prints formatted output.

The result is a static library, `libftprintf.a`, that exposes one function:

```c
int ft_printf(const char *format, ...);
```

It behaves like the original `printf()`: it writes the formatted output to the
standard output and returns the number of characters printed.

### Supported conversions

| Conversion | Description |
|------------|-------------|
| `%c` | a single character |
| `%s` | a string (prints `(null)` for a `NULL` pointer, like the original) |
| `%p` | a `void *` pointer in hexadecimal format |
| `%d` | a signed decimal (base 10) number |
| `%i` | a signed integer in base 10 |
| `%u` | an unsigned decimal (base 10) number |
| `%x` | a number in hexadecimal, lowercase |
| `%X` | a number in hexadecimal, uppercase |
| `%%` | a percent sign |

### Project rules (summary)

- Written in C, following the 42 Norm.
- Compiled with `cc -Wall -Wextra -Werror`.
- Allowed external functions: `malloc`, `free`, `write`, `va_start`, `va_arg`,
  `va_copy`, `va_end`.
- The buffer management of the original `printf()` is **not** implemented:
  output is written directly with `write`.
- The library is built with `ar` (`libtool` is forbidden) and `libftprintf.a`
  is created at the root of the repository.
- The header file is named `ft_printf.h` and contains the prototype of `ft_printf()`.

## Instructions

### Compilation

From the root of the repository:

```bash
make          # builds libftprintf.a
make clean    # removes object files
make fclean   # removes object files and libftprintf.a
make re       # fclean + all
```

The Makefile provides the rules `$(NAME)`, `all`, `clean`, `fclean` and `re`,
and does not relink if nothing changed.

### Usage

Include the header in your code and link against the library:

```c
#include "ft_printf.h"

int main(void)
{
    int n;

    n = ft_printf("Hello %s, you are %d years old! (%x)\n", "world", 42, 255);
    ft_printf("Printed %d characters\n", n);
    return (0);
}
```

```bash
cc -Wall -Wextra -Werror main.c -L. -lftprintf -o test
./test
```

### Testing

Compare the output and the return value of `ft_printf` against the real
`printf` on edge cases such as `0`, `INT_MIN`, `UINT_MAX`, `NULL` strings and
`NULL` pointers. Memory problems can be checked with:

```bash
valgrind --leak-check=full ./test
```

## Algorithm and data structure

**Parsing.** `ft_printf` initializes the variable argument list with `va_start`,
then walks through the format string one character at a time. A normal
character is written directly with `write`. When a `%` is found, the next
character is read as the conversion specifier and the program calls a
dispatch function (`print_format`) that selects the right handler for
`c`, `s`, `p`, `d`, `i`, `u`, `x`, `X` or `%`. At the end, `va_end` is called.

**Why this approach.** Reading the string in a single pass with a dispatch
function keeps the code simple, short enough for the Norm, and easy to extend:
adding a new conversion only requires a new handler and one new case in the
dispatcher, which also makes it easier to add the bonus flags later.

**Return value.** Every printing function returns the number of characters it
wrote, and `ft_printf` adds them all up. This is how the final return value
matches the one of the original `printf()`.

**Number printing.** Instead of building strings with `malloc`, numbers are
printed recursively, digit by digit, with one helper that works in any base
(10 for `%d`, `%i`, `%u` and 16 for `%x`, `%X`, `%p`). For `%d` and `%i`, the
sign is handled first and the value is stored in a wider type so that
`INT_MIN` does not overflow. For `%p`, the address is converted to an unsigned
integer type and printed in lowercase hexadecimal after the `0x` prefix.

**Data structures.** No dynamic data structure is needed. The program only uses
the `va_list` for the arguments and a running integer counter for the number of
printed characters, so there is nothing to allocate or free.

## Resources

### References

- `man 3 printf`: description of the original function and its conversions
- `man 3 stdarg`: `va_start`, `va_arg`, `va_copy`, `va_end`
- `man 2 write`
- `man 1 ar`
- GNU Make manual: https://www.gnu.org/software/make/manual/
- The C programming language reference on variadic functions:
  https://en.cppreference.com/w/c/variadic
- The 42 Norm and the 42 subject for ft_printf (version 12.1)

### Use of AI

AI (Claude) was used as a learning aid, not to write the project code:

- To explain concepts: how variadic functions and `va_arg` work, which type to
  read for each conversion, and what each line of the subject's requirements means.
- To clarify the difference between the mandatory part and the bonus part.
- To generate a test file (`main.c`) that compares `ft_printf` with the original
  `printf()` on edge cases, which is not part of the submitted code.
- To get a final checklist (Norm, Makefile, README, forbidden functions).

The code of the library was written by me, and I can explain every part of it.
