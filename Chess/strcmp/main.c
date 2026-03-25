#include <stdio.h>
#include <stdlib.h>

int main()
{
    char Str[3]={'a','e','f'};
    char str2[3]={'a','e','c'};
    int flag=1,i=0,index;
    while (flag && i<3){
        if (Str[i]<str2[i]){
            flag=0;
            index=1;
        }
        else if (Str[i]>str2[i]>0){
            index=2;
            flag=0;
        }
        else if (Str[i]==str2[i]){
            i++;
            if (i==3){index=3;break;}
        }
    }
    printf("%d",index);
    return 0;
}
