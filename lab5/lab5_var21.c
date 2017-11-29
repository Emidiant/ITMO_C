#include <stdio.h>

int main()
{
    int a[7];
    int m;
    //enter the array
    //10, 20, 30, 40, 50, 60, 70
    for (m = 0; m<7; m++)
    {
        printf("a[%d] = ", m);
        scanf("%d", &a[m]);
    }
    for (m = 0; m<7; m++)
        printf("%d ", a[m]);
    
    
    //second task
    int mat1[2][2]={{1, 1}, {1, 4}};
    int mat2[2][2]={{1, 2}, {4, 1}};
    int res[2][2]={{0, 0}, {0, 0}};
    int i,j,k;
    int N=2;

	for(i=0; i<N; i++)
	{
    		for(j=0; j<N; j++)
   		{
        	for(k = 0; k<N; k++)
        	res[i][j]+=mat1[i][k]*mat2[k][j];
  		}
	}

 	printf("\n result \n");
 	for(i=0; i<N; i++)
 	{
 		for(j=0; j<N; j++)
 		{printf(" %d ",res[i][j]);}
  		printf("\n");
 	}

return 0;
}
