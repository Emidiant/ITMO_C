//
//  lab11_var21.c

#include "header.h"


int main(void)
{
    struct rectangle rect;

    printf("Введите координаты точек:\n");
    printf("x[1]=");
    scanf("%d",&rect.x1);
    printf("y[1]=");
    scanf("%d",&rect.y1);
    printf("x[2]=");
    scanf("%d",&rect.x2);
    printf("y[2]=");
    scanf("%d",&rect.y2);
    printf("x[3]=");
    scanf("%d",&rect.x3);
    printf("y[3]=");
    scanf("%d",&rect.y3);
    printf("x[4]=");
    scanf("%d",&rect.x4);
    printf("y[4]=");
    scanf("%d",&rect.y4);

    int result;
    result = test(rect);
    if (result==4){
        printf("\nВведённая фигура - прямоугольник\n");
        }
    else{
         if (result==5) {
            printf("Вы ввели квадрат\n");
            }
         else{
              printf("Вы задали не прямоугольник\n");
          }
    }

  
    printf("\nПериметр равен: %.2f\n", perim(rect));
    
    printf("\nПлощадь равна: %.2f\n", square(rect));
    
    return 0;
}
