#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len)
{
    size_t i;
    for(i = 0; i < len; i++)
        printf("0x%.2x ", start[i]);
    printf("\r\n");
}

void show_int(int x)
{
    show_bytes((byte_pointer)&x, sizeof(int));
}

void show_float(float x)
{
    show_bytes((byte_pointer)&x, sizeof(float));
}

void show_pointer(void *x)
{
    show_bytes((byte_pointer)&x, sizeof(void *));
}

void inplace_swap(int *x, int *y)
{
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
}

void reverse_arry(int a[], int cnt)
{
    int first, last;
    for(first = 0, last = cnt - 1; first < last; first++, last--)
        inplace_swap(&a[first], &a[last]);
}

int main()
{
    // const char *s = "abcdef";
    // printf("% PRIu64 \r\n", strlen(s));
    // show_bytes((byte_pointer)s, strlen(s));
    printf("%d\r\n", sizeof(int));
    printf("%d\r\n", (2147483647 + 1));
    return 0;
}
