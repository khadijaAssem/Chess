#include <stdio.h>
#include <stdlib.h>
int Sub(char Arr[],int i,int N,char Sub[]);
int main()
{
    int N,M;
    scanf("%d%d",&N,&M);
    char A[N],S[M];
    printf("Enter 1st\n");
    scanf("%s",&A);
    printf("Enter 2nd\n");
    scanf("%s",&S);
    printf("%d",SubString(A,S,N));
    return 0;
}
int SubString(char Arr[],char Sub[],int N){
    int i,flag;
    for (i=0;i<N;i++){
        if (Arr[i]==Sub[0]){
            flag = Subs(Arr,i,N,Sub);
            if (flag==1)
                return 1;
        }
    }
    return 0;
}
int Subs(char Arr[],int i,int N,char Sub[]){
    int j=1,M=0;
    for (i++;i<N;i++){
        if (Sub[j]=='*'){
            i--;
            j++;
            M++;
        }
        if (Arr[i]==Sub[j]){
            j++;
            M++;
        }
        if (M==j-1)
            return 1;
        return 0;
    }
}
