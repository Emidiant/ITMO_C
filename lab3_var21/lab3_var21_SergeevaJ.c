#include <stdio.h>

int main(void)
{
	int x;
   	scanf("%x",&x);
	printf("decimal %d; octal %o; %o >> 1 = %o; ~%o = %o\n ", x, x, x, x>> 1, x, ~x);
	int y;
	scanf("%o",&y);
	printf("%o | %X = %o\n", y, x, y | x);
    return 0;
}

