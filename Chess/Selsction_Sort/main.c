#include <stdio.h>
#include <stdlib.h>

int main()
{   int i,N;
    scanf("%d",&N);
    int A[N];
    for (i=0;i<N;i++){
        scanf("%d",&A[i]);
    }
    int M=0;
    for (i=0;i<N;i++){
        int Y=getMin(A,N,i,i+1);
            Swap(&A[Y],&A[M]);
            M++;
    }
    for (i=0;i<N;i++){
        printf("%d",A[i]);
    }
    return 0;
}
int getMin(int Array[],int N,int Minimum,int i){
    for (i;i<N;i++){
        if (Array[i]<Array[Minimum]){
            Minimum=i;
        }
    }
   // printf("##%d\n",Array[Minimum]);
    return Minimum;
}
void Swap(int *Y,int *X){
    int Temp;
    Temp=*X;
    *X=*Y;
    *Y=Temp;
}
