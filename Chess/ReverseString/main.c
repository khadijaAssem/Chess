#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N,i;
    scanf("%d",&N);
    char Str[N];
    scanf("%s",Str);
    RevStr(Str,0,N-1);
    for (i=0;i<N;i++)
        printf("%c",Str[i]);
    return 0;
}
int RevStr(char Str[],int Start,int End){
    int i;
    if ((Start==End-1)||(Start==End)){
        return 0;
    }
    else{
        char Temp=Str[Start];
        Str[Start]=Str[End];
        Str[End]=Temp;
        RevStr(Str,Start+1,End-1);
    }
}
