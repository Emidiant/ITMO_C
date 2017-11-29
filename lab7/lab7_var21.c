//  lab7_var21

#include <stdio.h>
#include <math.h>
#define Pi 3.14159265
enum Day {Mon=1, Tue, Wed, Thu, Fri, Sat, Sun} today;
enum State{off,on};

struct circle
{
    int size1;
    float size2;
};

union bytesx {
    struct byte {
        unsigned a0: 1;
        unsigned a1: 1;
        unsigned a2: 1;
                 } bytes;
    unsigned word;
};

int main()
{
    //task 1. days
    today = (enum Day) (Mon);
    printf("%d ", today);
    printf("день тяжёлый\n");
    
    //task 2. circle
    struct circle circumference;
    struct circle radius;
    struct circle area;
    struct circle rr;
    radius.size1 = 7;//вводимая переменная
    circumference.size2 =radius.size1*2*Pi;
    area.size2 =radius.size1*radius.size1*Pi;
    rr.size1=radius.size1*radius.size1;
    printf("\nЗаданный радиус окружности: %d\n", radius.size1);
    printf("Длина окружности: ~%.2f\n", circumference.size2);
    printf("Площадь окружности: ~%.2f\n", area.size2);
    printf("Уравнение окружности, где центр расположен в начале координат:\n");
    printf("x^2+y^2=%d\n",rr.size1);
    
    //task 3. ADSL
    union bytesx reg;
    scanf(" %x", &reg.word);
    if (off==reg.bytes.a0) {printf(" DLS off \n");} else {printf(" DLS on\n");}
    if (off==reg.bytes.a1) {printf(" PPP off \n");} else {printf(" PPP on\n");}
    if (off==reg.bytes.a2) {printf(" Link off \n");} else {printf(" Link on\n");}
    
    return 0;
}
