#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, n,k;
    scanf("%d%d",&n,&k);
    if (n<=100000  && n>=0 && k>=0){
        int arr[n];
        for(i=0; i<n; i++)
            scanf("%d", &arr[i]);

        k = k % n;
        for(i=1; i<=k; i++)
            rotateByOneL(arr,n);
        for(i=0; i<n; i++)
            printf("%d ", arr[i]);
    }
    return 0;
}
void rotateByOne(int arr[],int n){
    int i,N=arr[n-1];
   // printf("%d\n",arr[n-1]);
    /*for (i=1;i<n;i++){
        printf("%d%d\t",arr[i],arr[i-1]);
        arr[i-1]=arr[i];
        printf("%d%d\n",arr[i-1],arr[i]);
    }*/
    for(i=n-1; i>0; i--)
    {
        arr[i] = arr[i-1];
        printf("%d  %d\t",arr[i],arr[i-1]);
    }
    arr[0]=N;
}
void rotateByOneL(int arr[],int n){
    int i,N=arr[0];
    for(i=1; i<n; i++)
    {
        arr[i-1] = arr[i];
        printf("%d  %d\t",arr[i],arr[i-1]);
    }
    arr[n-1]=N;
}

