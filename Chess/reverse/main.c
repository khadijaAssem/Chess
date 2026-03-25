#include <stdio.h>
#include <stdlib.h>
void reverse(int arr[],int N1,int N2);
int main()
{
    int i,arr1[5]={1,2,3,4,5};
    reverse1(arr1,1,3);
    for (i=0;i<5;i++)
        printf("%d\t",arr1[i]);
    return 0;
}
/*void reverse(int arr[],int N1,int N2){
    int N3=N1,M1=N2;
    static int N=arr[M1],M=arr[N3];
    static int i=0,Count=0;
    i++;
    if (Count==2)
        return;
    else if (arr[i]==M){
        arr[i]=N;
        Count++;
    }
    else if (arr[i]==N){
        arr[i]=M;
        Count++;
    }
    reverse(arr,N1,N2);
}*/
void reverse1(int A[],int l ,int r){
    printf("*");
    if (l==r) return;
    if (l=(r-1)){Swap(A[l],A[r]);return;}
    reverse1(A,l+1,r-1);
    Swap(A[l],A[r]);
    return;
}
void Swap(int *Y,int *X){
    int Temp;
    Temp=*X;
    *X=*Y;
    *Y=Temp;
}
