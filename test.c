#include <stdio.h>
#include <stdarg.h>
 int variadic(int count, ...)
 {
    int     i;
    int total;
    va_list     arg;
    va_start(arg, count);

    i = 0;
    total = 0;
    while (i  < count)
    {
        total += va_arg(arg, int);
        i++;
    }
    va_end(arg);
    return (total);
 }

int main()
{
    printf("%d", variadic(5, 10, 20, 10, 10, 20));
    return (0);
}