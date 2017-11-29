//  func_lab11.c
//  lab11_var21

#include "header.h"


int test(struct rectangle rect) //проверка на то, что мы ввели прямоугольник
{
    int a[6], b[6], t=0, k=0, m=0;
    a[0]=rect.x1-rect.x2;    b[0]=rect.y1-rect.y2;
    a[1]=rect.x1-rect.x3;    b[1]=rect.y1-rect.y3;
    a[2]=rect.x1-rect.x4;    b[2]=rect.y1-rect.y4;
    a[3]=rect.x2-rect.x3;    b[3]=rect.y2-rect.y3;
    a[4]=rect.x2-rect.x4;    b[4]=rect.y2-rect.y4;
    a[5]=rect.x3-rect.x4;    b[5]=rect.y3-rect.y4;
    
   
    for (k=0; k<=N; k++)
        for (m=k+1; m<=(N+1); m++)
            if ((a[k]*a[m]+b[k]*b[m])/(sqrt(pow(a[k], 2)+pow(b[k], 2))*sqrt(pow(a[m], 2)+pow(b[m], 2)))==0) {t++;}
    
    return t;
}


float perim(struct rectangle rect)
{
    int i;
    float p, a[6], min1=1000, min2=1000, max=-1;
    a[0]=sqrt(pow((rect.x1-rect.x2),2)+pow((rect.y1-rect.y2),2));
    a[1]=sqrt(pow((rect.x1-rect.x3),2)+pow((rect.y1-rect.y3),2));
    a[2]=sqrt(pow((rect.x1-rect.x4),2)+pow((rect.y1-rect.y4),2));
    a[3]=sqrt(pow((rect.x2-rect.x3),2)+pow((rect.y2-rect.y3),2));
    a[4]=sqrt(pow((rect.x2-rect.x4),2)+pow((rect.y2-rect.y4),2));
    a[5]=sqrt(pow((rect.x3-rect.x4),2)+pow((rect.y3-rect.y4),2));
    
    
    for (i=0; i<=(N+1); i++)
    {
        if (a[i]<min1){min1=a[i];}
        if (a[i]>max){max=a[i];} //ищем максимум, чтобы в случае ситуации с квадратом верно посчитать его параметры
    }
    for (i=0; i<=(N+1); i++)
        if (a[i]<min2 && a[i]!=min1 && a[i]!=max){min2=a[i];}
        else
        {
            if(a[i]<min2 && a[i]==max){min2=min1;}
        }
  
    p=2*min1+2*min2;
    return p;
}


float square(struct rectangle rect)
{
    int i;
    float s, a[6], min1=1000, min2=1000, max=-1;
    a[0]=sqrt(pow((rect.x1-rect.x2),2)+pow((rect.y1-rect.y2),2));
    a[1]=sqrt(pow((rect.x1-rect.x3),2)+pow((rect.y1-rect.y3),2));
    a[2]=sqrt(pow((rect.x1-rect.x4),2)+pow((rect.y1-rect.y4),2));
    a[3]=sqrt(pow((rect.x2-rect.x3),2)+pow((rect.y2-rect.y3),2));
    a[4]=sqrt(pow((rect.x2-rect.x4),2)+pow((rect.y2-rect.y4),2));
    a[5]=sqrt(pow((rect.x3-rect.x4),2)+pow((rect.y3-rect.y4),2));
    
    
    for (i=0; i<=(N+1); i++)
    {
        if (a[i]<min1){min1=a[i];}
        if (a[i]>max){max=a[i];}
    }
    for (i=0; i<=(N+1); i++)
        if (a[i]<min2 && a[i]!=min1 && a[i]!=max){min2=a[i];}
        else
        {
            if(a[i]<min2 && a[i]==max){min2=min1;}
        }
    
    s=min1*min2;
    return s;
}


