//  lab10_var21.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define len 100
int gcd(int x, int y)
{
    int n, gc=1, i;
    if (x>=y){n=y;} else {n=x;}
    for (i=1; i<=n; i++)
        if ((x % i)==0 && (y % i)==0) {gc=i;}
    return gc;
}

int lkm(int x, int y)
{
    int n, lk=1, i, id=1;
    if (x>=y){n=y;} else {n=x;}
    for (i=1; i<=n; i++)
         if (id==1 && lk<i && (x % i)==0 && (y % i)==0){id++; lk=i;}
    return lk;
}

float* distance(int n, int *x, int *y)
{
    int i, j, k=0;
    float *d;
    d=(float*)malloc(n * sizeof(float));

    for (i=0; i<=n; i++){
        for (j=0; j<=n; j++){
            if (i!=j){
                d[k]=sqrtf(pow(x[i]-x[j], 2)+pow(y[i]-y[j], 2));
                k++;
            }
        }
    }
    return d;
}


int main(void)
{
    //task1
    int a, b;
    printf("Введите два натуральных числа: ");
    scanf("%d %d",&a, &b);
    
    printf("\nНаибольший общий делитель: %d\n", gcd(a,b));
    printf("Наименьшее общее кратное: %d\n", lkm(a,b));
    
//    task2
    int i, x[len], y[len];
    int n, k=0;
    float *result;

    printf("\nВведите n: ");
    scanf("%d", &n);
    for (i=0; i<=n; i++){
        printf("x[%d]= ",i);
        scanf("%d", &x[i]);
        printf("y[%d]= ",i);
        scanf("%d", &y[i]);
    }

    result = distance(n, x, y);
    for (k=0; k <= (n+1)*n-1; k++){
        printf("result[%d]=",k);
        printf("%0.2f ", *(result + k));
    }
    return 0;
}
