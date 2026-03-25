#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,j,N,M;
    scanf("%d%d",&N,&M);
    int arr[N][M];
    int A[M][N];
    for (i=0;i<N;i++){
        for (j=0;j<M;j++)
            scanf("%d",&arr[i][j]);
    }
    for (i=0;i<N;i++){
        for (j=0;j<M;j++)
            A[i][j]=arr[j][i];
    }
    for (i=0;i<N;i++){
        for (j=0;j<M;j++)
            printf("%d\t",arr[i][j]);
        printf("\n");
    }
    for (i=0;i<N;i++){
        for (j=0;j<M;j++)
            printf("%d\t",A[i][j]);
        printf("\n");
    }
    return 0;
}
