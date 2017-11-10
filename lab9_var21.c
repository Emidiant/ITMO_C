//  lab9_var21

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define len 80
#define freemin 499

int main()
{
//    task 1
//  Подсчитать количество символов цифр, а также символов строчных и прописных букв английского алфавита в строке, введённой с консоли. Результат вывести на консоль.
    char str[len];
    int title=0;
    int lower=0;
    int digit=0;
    int i;
    
    puts("Введите строку:");
    fgets(str, len, stdin);
    for (i=0; i<strlen(str)-1;i++){
        if (str[i]>='a' && str[i]<='z') {lower++;} else{
            if(str[i]>='A' && str[i]<='Z'){title++;} else{
                if(str[i]>='0' && str[i]<='9'){digit++;}
            }
        }
    }
    printf("\nКоличество строчных букв: %d\nКоличество заглавных букв: %d\nКоличество цифр: %d\n",lower, title, digit);
    
    //task2
    
    int cost=0;
    int talkmin;
    int paymounth;
    int minute;
    printf("\nМинуты за месяц: ");
    scanf("%d", &talkmin);
    printf("Абонентская плата: ");
    scanf("%d", &paymounth);
    printf("Стоимость доп. минуты: ");
    scanf("%d", &minute);
    if (talkmin<=freemin){cost=paymounth;}else{
        cost=paymounth+minute*(talkmin-freemin);
    }
    printf("Стоимость обслуживания: %d\n", cost);
    
    
    return 0;
}


