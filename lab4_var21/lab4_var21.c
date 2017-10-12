#include <stdio.h>
#include <math.h>

int main()
{
    int x;
    scanf("%d",&x);
    printf("%d\n", 10<=x && x<=100);
    printf("0-false, 1-true\n");
    
    int y,z;
    scanf("%o", &y);
    z=y>>21;
    z=z % 2;
    printf("%d\n",z);
  
    return 0;
}

