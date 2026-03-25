#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,N;
    scanf("%d",&N);
    int A[N];
    for (i=0;i<N;i++){
        scanf("%d",&A[i]);
    }
    for (i=1;i<N;i++){
        int Key=A[i],j=i-1;
        while (i>=0&&A[j]>Key){
          A[j+1]=A[j];
          j--;
        }
        A[j+1]=Key;
    }
    for (i=0;i<N;i++){
        printf("%d",A[i]);
    }
    return 0;
}
