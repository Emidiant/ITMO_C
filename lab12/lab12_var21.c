//  lab12_var21

#include <time.h>
#include <stdio.h>
#define N 10
int main()
{
    FILE *f;
    f=fopen("/Users/emidiant/Desktop/Projects/C/lab_c/lab12_var21/test_lab_12.txt", "w");
    char *n[]={"\n"};
    time_t t = time(NULL);
    struct tm* date = localtime(&t);
    int i;
    for (i=0; i<=(N-1); i++)
    {
        fprintf(f, "%d %d %d", date->tm_mday, date->tm_mon+1,  date->tm_year+1900);//-> - обращение к члену структуры
        fputs(*n,f);//добавляем /n
        date->tm_mday+=1;
        time_t next = mktime(date); //mktime - функция перевода календарного времени
        date= localtime(&next);
    }
    fclose(f);
    return 0;
}

