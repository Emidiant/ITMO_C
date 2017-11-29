//a, b, c, d

#include <stdio.h>
#include <stdlib.h>
#define N 4

int main()
{
    char a[N];      //задание 1
    int i;
    
    for (i = 0; i<N; i++)   //ввод
    {
        char * gets(char *);
        printf("a[%d] = ", i);
        scanf("%s", &a[i]);
    }
    for (i = 0; i<N; i++)   //вывод
        printf("%c ", *(i+a));
    
    char *ar;   //задание 2
    int k, m;
    
    printf("\n Размер массива: ");
    scanf("%d", &m);
    ar = (char*)malloc(m * sizeof(char));
    for (k = 0; k<m; k++)   //ввод
    {
        printf("ar[%d] = ", k);
        scanf("%s", &ar[k]);
    }
    for (k = 0; k<m; k++)   //вывод
        printf("%c ", ar[k]);
    free(ar);
    
    return 0;
}

