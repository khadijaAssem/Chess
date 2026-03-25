#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N,i;
    scanf("%d",&N);
    getchar();
    char Str[N];
    gets(Str);
    int P[N];
    int j=0;P[j]=0;j++;
    for (i=0;i<N;i++){
        if (Str[i]==' '){
            P[j]=i;
            j++;
        }
    }
    for (i=0;i<j;i++)
        printf("%d",P[i]);
    //char Str2[N];
    int L;
    j--;
    for (L=P[j];j>=0;L=P[j]){
        //printf("**%d",L);
        for (i=L;i<=N;i++){
            printf("%c",Str[i]);
        }
        printf(" ");
        j--;
        N=L-1;
        //printf("--%d\n",N);
    }
    return 0;
}
