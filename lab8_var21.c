//lab8_var21
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define len 80

int main() {
    
    
    //task1: summ
    char s1[len];
    char s2[len];
    
    printf("Введите строку 1: ");
    fgets(s1, len, stdin);
    int i;
    for (i=0; i<len; i++)
    {
        if (s1[i]=='\n')
        {
            s1[i] ='\0';
            break;
        }
    }
    printf("Введите строку 2: ");
    fgets(s2, len, stdin);//при использовании gets() выскакивает предупреждение, поэтому исп fgets
    strcat(s1, s2);
    puts("Результат сложения строк:");
    puts(s1);
    
    //task 7: len str
    
    char str[len];
    float length;
    
    puts("Введите строку:");
    fgets(str, len, stdin);
    printf("Длина строки: ");
    length = strlen(str)-1;
    printf("%0.f\n", length);
    
    //task 4: comparison n Примечание: более короткий вариант возможен с использованием функции strncmp...
    int k,n,m=0;
    char string1[len];
    char string2[len];
    
    printf("\nВведите строку 1: ");
    fgets(string1, len, stdin);
    printf("Введите строку 2: ");
    fgets(string2, len, stdin);
    printf("Введите n: ");
    scanf("%d",&n);
    for (k=1; k<n+1; k++)
        if (string1[k]!=string2[k])(m++);
    if (m==0) {printf("Первые n символов равны\n");}
    else {printf("Первые n симвлов не равны\n");}
    
    //task 8 
    // вариант strcspn
    char stri[len], stri1[len];
    float h;
    printf("\nВведите строку: ");
    getchar();
    fgets(stri, len, stdin);
    printf("Введите символ: ");  
    fgets(stri1, len, stdin);
    h=strcspn(stri, stri1);
    if (h+1!=strlen(stri)) {printf("%0.f\n",h+1);}
    else {printf("Такого символа в строке нет\n");}
    // без использования строковой функции strcspn
    //    int l=1,p=0;
    //    char stri[len], q;
    
    //    printf("Введите строку: ");
    //    fgets(stri, len, stdin);
    //    printf("Введите символ: ");
    //    scanf("%c",&q);
    //    while (l!=0)
    //    {
    //        if (stri[p]==q)
    //        {l=0;
    //            break;}
    //        else
    //        {p++;}
    //    }
    //    if (p<len) {printf("Первое вхождение: %d \n", p+1);}
    //    else {printf("Такого символа в строке нет\n");}
    
    //task 11
    //Определить длину отрезка одной строки, содержащего символы из множества символов, входящих во вторую строку.
    char str3 [len];
    char sym [len];
    puts("Введите первую строку:");
    fgets(str3, len, stdin);
    puts("Введите вторую строку:");
    fgets(sym, len, stdin);
    printf ("Длина сегмента: %d\n", strspn(str3,sym));
    return 0;

}

