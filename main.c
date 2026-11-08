/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oerrachi <oerrachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by and printf,       #+#    #+#             */
/*   Updated: 2026/11/07 18:12:21 by oerrachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include "ft_printf.h"

/* we deliberately pass odd things to printf, so silence format warnings */
#pragma GCC diagnostic ignored "-Wformat"
#pragma GCC diagnostic ignored "-Wformat-extra-args"
#pragma GCC diagnostic ignored "-Wformat-security"
#pragma GCC diagnostic ignored "-Wformat-zero-length"
#pragma GCC diagnostic ignored "-Wnonnull"

#define BUF_SIZE 70000

static int		g_total;
static int		g_ok;
static int		g_saved;
static FILE		*g_tmp;

/* ---------- capture stdout (fd 1) into a temp file ---------- */

static void	cap_start(void)
{
	fflush(stdout);
	g_tmp = tmpfile();
	g_saved = dup(STDOUT_FILENO);
	dup2(fileno(g_tmp), STDOUT_FILENO);
}

static size_t	cap_end(char *buf)
{
	size_t	n;

	fflush(stdout);
	dup2(g_saved, STDOUT_FILENO);
	close(g_saved);
	fflush(g_tmp);
	rewind(g_tmp);
	n = fread(buf, 1, BUF_SIZE - 1, g_tmp);
	buf[n] = '\0';
	fclose(g_tmp);
	return (n);
}

/* ---------- reporting ---------- */

static void	show(const char *s, size_t n)
{
	size_t	i;

	printf("[");
	for (i = 0; i < n && i < 60; i++)
	{
		if (s[i] == '\n')
			printf("\\n");
		else if (s[i] == '\0')
			printf("\\0");
		else if ((unsigned char)s[i] < 32 || (unsigned char)s[i] > 126)
			printf("\\x%02x", (unsigned char)s[i]);
		else
			putchar(s[i]);
	}
	if (n > 60)
		printf("...(%zu bytes)", n);
	printf("]");
}

static void	report(const char *name, char *b1, size_t n1, int r1,
				char *b2, size_t n2, int r2)
{
	int	ok;

	ok = (n1 == n2 && memcmp(b1, b2, n1) == 0 && r1 == r2);
	g_total++;
	if (ok)
	{
		g_ok++;
		printf("\033[32m[OK]\033[0m   %s\n", name);
		return ;
	}
	printf("\033[31m[FAIL]\033[0m %s\n", name);
	printf("   mine: ");
	show(b1, n1);
	printf("  return=%d\n   real: ", r1);
	show(b2, n2);
	printf("  return=%d\n", r2);
}

#define TEST(...) do { \
	char	*b1_ = malloc(BUF_SIZE); \
	char	*b2_ = malloc(BUF_SIZE); \
	size_t	n1_; \
	size_t	n2_; \
	int		r1_; \
	int		r2_; \
	cap_start(); \
	r1_ = ft_printf(__VA_ARGS__); \
	n1_ = cap_end(b1_); \
	cap_start(); \
	r2_ = printf(__VA_ARGS__); \
	n2_ = cap_end(b2_); \
	report(#__VA_ARGS__, b1_, n1_, r1_, b2_, n2_, r2_); \
	free(b1_); \
	free(b2_); \
} while (0)

static void	title(const char *s)
{
	printf("\n\033[1m=== %s ===\033[0m\n", s);
}

/* ---------- tests ---------- */

int	main(void)
{
	int		x = 42;
	char	*nul = NULL;
	void	*vnul = NULL;
	char	longstr[5001];

	memset(longstr, 'a', 5000);
	longstr[5000] = '\0';

	title("no conversion / plain text");
	TEST("");
	TEST("Hello");
	TEST("Hello, World!\n");
	TEST("   spaces   and\ttabs\n");
	TEST("\n\n\n");

	title("%c");
	TEST("%c", 'A');
	TEST("%c", 'z');
	TEST("%c", '0');
	TEST("%c", ' ');
	TEST("%c", '\n');
	TEST("%c", '\0');
	TEST("%c", 127);
	TEST("%c", 128);
	TEST("%c", 255);
	TEST("%c", -1);
	TEST("%c%c%c", 'a', 'b', 'c');
	TEST("[%c]", 'x');
	TEST("%c and %c", '\0', 'Z');
	TEST("%c%c", '\0', '\0');

	title("%s");
	TEST("%s", "hello");
	TEST("%s", "");
	TEST("%s", nul);
	TEST("[%s]", nul);
	TEST("%s", "with\nnewline");
	TEST("%s", "  leading and trailing  ");
	TEST("%s%s", "ab", "cd");
	TEST("%s %s %s", "one", "two", "three");
	TEST("%s", "100%");
	TEST("%s", "%d %s %c");
	TEST("%s", longstr);
	TEST("start %s end", "middle");
	TEST("%s|%s", "", "");
	TEST("%s|%s", nul, "x");

	title("%d");
	TEST("%d", 0);
	TEST("%d", 1);
	TEST("%d", -1);
	TEST("%d", 9);
	TEST("%d", 10);
	TEST("%d", 42);
	TEST("%d", -42);
	TEST("%d", 100);
	TEST("%d", 12345);
	TEST("%d", -12345);
	TEST("%d", INT_MAX);
	TEST("%d", INT_MIN);
	TEST("%d", INT_MAX - 1);
	TEST("%d", INT_MIN + 1);
	TEST("%d", 1000000000);
	TEST("%d", -1000000000);
	TEST("%d%d", 1, 2);
	TEST("%d %d %d", INT_MIN, 0, INT_MAX);
	TEST("val=%d.", -7);

	title("%i");
	TEST("%i", 0);
	TEST("%i", 1);
	TEST("%i", -1);
	TEST("%i", 42);
	TEST("%i", -42);
	TEST("%i", INT_MAX);
	TEST("%i", INT_MIN);
	TEST("%i %i", INT_MIN, INT_MAX);
	TEST("%i", 0x7fffffff);

	title("%u");
	TEST("%u", 0);
	TEST("%u", 1);
	TEST("%u", 42);
	TEST("%u", 9);
	TEST("%u", 10);
	TEST("%u", INT_MAX);
	TEST("%u", (unsigned int)INT_MAX + 1);
	TEST("%u", UINT_MAX);
	TEST("%u", -1);
	TEST("%u", INT_MIN);
	TEST("%u %u", 0u, UINT_MAX);
	TEST("%u", 4294967295u);
	TEST("%u", 1000000000u);

	title("%x");
	TEST("%x", 0);
	TEST("%x", 1);
	TEST("%x", 9);
	TEST("%x", 10);
	TEST("%x", 15);
	TEST("%x", 16);
	TEST("%x", 255);
	TEST("%x", 256);
	TEST("%x", 0xabcdef);
	TEST("%x", 0xdeadbeef);
	TEST("%x", INT_MAX);
	TEST("%x", UINT_MAX);
	TEST("%x", -1);
	TEST("%x", INT_MIN);
	TEST("%x %x", 0, UINT_MAX);
	TEST("0x%x", 42);

	title("%X");
	TEST("%X", 0);
	TEST("%X", 1);
	TEST("%X", 10);
	TEST("%X", 15);
	TEST("%X", 16);
	TEST("%X", 255);
	TEST("%X", 0xabcdef);
	TEST("%X", 0xdeadbeef);
	TEST("%X", INT_MAX);
	TEST("%X", UINT_MAX);
	TEST("%X", -1);
	TEST("%X", INT_MIN);
	TEST("%x %X", 0xabc, 0xabc);

	title("%p  (NULL prints (nil) on Linux, 0x0 on macOS: compared to YOUR libc)");
	TEST("%p", &x);
	TEST("%p", vnul);
	TEST("%p", nul);
	TEST("%p", (void *)1);
	TEST("%p", (void *)16);
	TEST("%p", (void *)255);
	TEST("%p", (void *)0xdeadbeef);
	TEST("%p", (void *)LONG_MAX);
	TEST("%p", (void *)LONG_MIN);
	TEST("%p", (void *)ULONG_MAX);
	TEST("%p", (void *)-1);
	TEST("%p", (void *)main);
	TEST("%p", (void *)longstr);
	TEST("%p %p", &x, vnul);
	TEST("[%p]", (void *)0x1234);

	title("%%");
	TEST("%%");
	TEST("%%%%");
	TEST("%%%%%%");
	TEST("100%%");
	TEST("%%d");
	TEST("%%s %%c");
	TEST("%c%%%c", 'a', 'b');
	TEST("%d%%", 50);
	TEST("%%%d%%", 50);
	TEST("%% %% %%");

	title("mixed conversions");
	TEST("%c %s %d %i %u %x %X %%", 'a', "str", -1, 2, 3u, 255, 255);
	TEST("%s is %d years old", "Rofix", 25);
	TEST("%d%s%c%u", 1, "two", '3', 4u);
	TEST("%x%X%x", 10, 10, 10);
	TEST("%p %s %c", &x, "txt", 'c');
	TEST("%d %d %d %d %d %d %d %d", 1, 2, 3, 4, 5, 6, 7, 8);
	TEST("%s%s%s%s%s", "a", "b", "c", "d", "e");
	TEST("%c%c%c%c%c%c%c%c%c%c", '0', '1', '2', '3', '4',
		'5', '6', '7', '8', '9');
	TEST("%u %d %x", UINT_MAX, INT_MIN, UINT_MAX);
	TEST("%%%c%%%s%%%d%%", 'x', "y", 3);
	TEST("text%dtext%stext%ctext", 1, "s", 'c');

	title("return value only matters (long outputs)");
	TEST("%s%s", longstr, longstr);
	TEST("%s%d%s", longstr, INT_MIN, longstr);

	/*
	** UNDEFINED BEHAVIOR (not graded, do not rely on these):
	**   ft_printf("%");          lone % at end
	**   ft_printf("%z");         unknown conversion
	**   ft_printf("%d");         missing argument
	** You may test them by hand but crashes there are not counted against you.
	*/

	printf("\n\033[1mResult: %d / %d tests passed\033[0m\n", g_ok, g_total);
	return (g_ok == g_total ? 0 : 1);
}