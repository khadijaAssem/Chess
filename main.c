#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct  {
    unsigned char ID;
    unsigned char CrR;
    unsigned char CrC;
    unsigned char DesR;
    unsigned char DesC;
}moves ;

typedef struct  {
    unsigned char name;
    unsigned char row;
    unsigned char colomn;
}dangerous ;

typedef struct {
    unsigned char R;
    unsigned char C;
}King_I;
unsigned char N01=0,N02=0;

unsigned char maze[8][8];//main platform
unsigned char Out01[8],Out02[8];
dangerous arr1[16],arr2[16];;

int pawn (moves X);
int Queen(moves X);
int King(moves X);
int rook(moves X);
int Bishop(moves X);
int Knight(moves X);
void Move(moves X);
void Undo(moves X);
void check(moves X);

void Print_Maze(unsigned char N1,unsigned char N2){
    unsigned char i,j;
    printf ("\t\tA\tB\tC\tD\tE\tF\tG\tH\n\n\n");
    for (i=0;i<8;i++){

        if (N1>0&&2*i<N1){
            if(N1%2==0)
                printf("%c %c",Out01[2*i],Out01[2*i+1]);
            else if (N1-1>0&&2*i<N1-1){
                printf("%c %c",Out01[2*i],Out01[2*i+1]);
            }
            if (N1%2==1&&2*i>=N1-1)
                printf("%c",Out01[N1-1]);
        }

        printf("\t%d",i);
        for (j='A';j<='H';j++){
           printf("\t%c",maze[i][j]);
        }
        printf("\t%d\t",i);
        if (N2>0&&2*i<N2){
            if(N2%2==0)
                printf("%c %c",Out02[2*i],Out02[2*i+1]);
            else if (N2-1>0&&2*i<N2-1){
                printf("%c %c",Out02[2*i],Out02[2*i+1]);
            }
            if (N2%2==1&&2*i>=N2-1)
                printf("%c",Out02[N2-1]);
        }
        printf("\n\n");
    }
    printf ("\n\n\t\tA\tB\tC\tD\tE\tF\tG\tH\n\n");

}
void Maze(){
    unsigned char i,j;
    maze [0][65]=maze[0][72]=114;
    maze [0][66]=maze[0][71]=110;
    maze [0][67]=maze[0][70]=98;
    maze [0][68]=113;
    maze [0][69]=107;

    maze [7][65]=maze[7][72]=82;
    maze [7][66]=maze[7][71]=78;
    maze [7][67]=maze[7][70]=66;
    maze [7][68]=81;
    maze [7][69]=75;

    i=1;
    for(j='A';j<='H';j++){
        maze[i][j]=112;

    }
    i+=5;
    for(j='A';j<='H';j++){
        maze[i][j]=80;
    }
    for (i=2;i<6;i++){
        for (j='A';j<='H';j++){
            if (i%2==0&&j%2==0)
                maze[i][j]='-';
            else if(i%2==0)
                maze[i][j]='.';
            else if (j%2==0)
                maze[i][j]='.';
            else
                maze[i][j]='-';
        }
    }
    Print_Maze(0,0);
}

int pieces(moves X){
    int available;
    char piece;
    piece=toupper(maze[X.CrR][X.CrC]);
    switch(piece){
        case 'P':available=pawn(X);break;
        case 'R':available=rook(X);break;
        case 'K':available=King(X);break;
        case 'Q':available=Queen(X);break;
        case 'B':available=Bishop(X);break;
        case 'N':available=Knight(X);break;
    }

    return available;
}

int main()
{
    int available;
    moves X;
    Maze();
   // Save();
   char moves[5];
    while(1){
            do{
                printf("\nPlayer1 move:\n");
                X.ID=1;
                scanf("%s",&moves);
                X.CrR=moves[1]-48;
                X.CrC=toupper(moves[0]);
                X.DesR=moves[3]-48;
                X.DesC=toupper(moves[2]);
                available=pieces(X);
                if (available==1){

                    Move(X);
                    break;
                }
                else
                    printf("Not available\n");
            } while(1);

            check(X);

           do{
                printf("\nPlayer2 move:\n");
                X.ID=2;
                scanf("%s",&moves);
                X.CrR=moves[1]-48;
                X.CrC=toupper(moves[0]);
                X.DesR=moves[3]-48;
                X.DesC=toupper(moves[2]);
                available=pieces(X);
                if (available==1){
                    Move(X);
                    break;
                }
                else
                    printf("Not available");
            } while(1);

            check(X);
    }
    return 0;
}

int pawn (moves X){
    int available;
    char DiffC=X.CrC-X.DesC ,DiffR=X.CrR-X.DesR ;
    unsigned char i,j,promotion,flag=0;
    if (X.CrR==1||X.CrR==6){
        if (((((X.ID==2)&&(DiffR==2))||((X.ID==1)&&(DiffR==-2)))&&(DiffC==0))||((((X.ID==2)&&(DiffR==1))||((X.ID==1)&&(DiffR==-1)))&&(DiffC==0)))
           flag=1;
        else if((abs(DiffC)==1&&abs(DiffR)==1)&&((X.ID==1&& DiffR==-1&&(maze[X.DesR][X.DesC]>65 && maze[X.DesR][X.DesC]<90))||(X.ID==2&&DiffR==1&&maze[X.DesR][X.DesC]>90))){
                available=1;
                flag=1;
        }
        else flag = 0;
    }
    else if((abs(DiffC)==1&&abs(DiffR)==1)&&((X.ID==1&& DiffR==-1&&(maze[X.DesR][X.DesC]>65 && maze[X.DesR][X.DesC]<90))||(X.ID==2&&DiffR==1&&maze[X.DesR][X.DesC]>90))){
            available=1;
            flag=1;
            if ((X.ID==1&&X.DesR==7)||(X.ID==2&&X.DesR==0)){
                printf("Promotion!!! choose your piece:\nQ\nR\nB\nN\n");
                scanf(" %c",&promotion);
                if (X.ID==1)
                    maze[X.DesR][X.DesC]=tolower(promotion);
                else
                    maze[X.DesR][X.DesC]=toupper(promotion);
                Print_Maze(N01,N02);

            }
    }
    else{
        if ((((X.ID==2)&&(DiffR==1))||((X.ID==1)&&(DiffR==-1)))&&(DiffC==0))
            flag=1;
        else flag = 0;
    }
    if (flag == 1 && DiffC==0){
        j=X.DesR;
        if (X.ID==1){
            for (i=X.DesR;i>X.CrR;i--){
                if (maze[i][X.CrC]=='.'||maze[i][X.CrC]=='-')
                    j--;
                else{
                    j++;
                    break;
                }
            }
                if (j==X.CrR){
                         available=1;
                        if ((X.ID==1&&X.DesR==7)||(X.ID==2&&X.DesR==0)){
                            printf("Promotion!!! choose your piece:\nQ\nR\nB\nN\n");
                            scanf(" %c",&promotion);
                            if (X.ID==1)
                                maze[X.DesR][X.DesC]=tolower(promotion);
                            else
                                maze[X.DesR][X.DesC]=toupper(promotion);
                            Print_Maze(N01,N02);
                    }
                }

                else  flag = 0;
           }
           else {
                for (i=X.DesR;i<X.CrR;i++){
                    if (maze[i][X.CrC]=='.'||maze[i][X.CrC]=='-')
                        j++;
                    else{
                        j--;
                        break;
                    }
                }
            if (j==X.CrR){
                available=1;
                if ((X.ID==1&&X.DesR==7)||(X.ID==2&&X.DesR==0)){
                    printf("Promotion!!! choose your piece:\nQ\nR\nB\nN\n");
                    scanf(" %c",&promotion);
                    if (X.ID==1)
                        maze[X.DesR][X.DesC]=tolower(promotion);
                    else
                        maze[X.DesR][X.DesC]=toupper(promotion);
                    Print_Maze(N01,N02);
                }
            }
            else  flag = 0;
           }
    }
    if (flag==0)
        available=0;
    return available;
}

int rook(moves X){
    int available;
    char DiffC=X.CrC-X.DesC , DiffR=X.CrR-X.DesR ;
    if((X.ID==1 && maze[X.CrR][X.CrC]=='r' && maze[X.DesR][X.DesC]<97) || (X.ID==2 && maze[X.CrR][X.CrC]=='R' && (maze[X.DesR][X.DesC]<65||maze[X.DesR][X.DesC]>90))){

    if ((DiffC==0)&&(DiffR!=0)){
        int j=0,i,K;
        if (X.CrR<X.DesR){
            i=X.CrR;
            K=X.DesR;
        }
        else {
            i=X.DesR;
            K=X.CrR;
        }
        j=i+1;
        for (i+=1;i<K;i++){
            if (maze[i][X.CrC]=='.'||maze[i][X.CrC]=='-')
                j++;
            else{
                j--;
                break;
            }
        }
        if (j==i)
            available=1;
        else
            available=0;
    }
    else if ((DiffR==0)&&(DiffC!=0)){
        int j=0,i,K;
        if (X.CrC<X.DesC){
            i=X.CrC;
            K=X.DesC;
        }
        else {
            i=X.DesC;
            K=X.CrC;
        }
        j=i+1;
        for (i+=1;i<K;i++){
            if (maze[X.CrR][i]=='.'||maze[X.CrR][i]=='-')
                j++;
            else  {
                j--;
                break;
            }
        }
        if (j==i)
            available=1;
        else
            available=0;
    }
    else
        available=0;
    }
    else
        available=0;

    return available;
}

int Knight(moves X){
    int available;
    char DiffC=X.CrC-X.DesC ,DiffR=X.CrR-X.DesR ;
    if((abs(DiffR)==1&&abs(DiffC)==2) || (abs(DiffR)==2&&abs(DiffC)==1)){
        if(X.ID==1 && maze[X.CrR][X.CrC]=='n' && maze[X.DesR][X.DesC]<97)
            available=1;

        else if (X.ID==2 && maze[X.CrR][X.CrC]=='N' && (maze[X.DesR][X.DesC]<65||maze[X.DesR][X.DesC]>90))
            available=1;

        else
            available=0;
    }
    else
        available=0;


    return available;
}


int Bishop(moves X){
    int available;
    char DiffC=X.CrC-X.DesC , DiffR=X.CrR-X.DesR ;
    unsigned char i=X.CrR,flag=0,j=X.CrC;
     if((X.ID==1 && maze[X.CrR][X.CrC]=='b' && maze[X.DesR][X.DesC]<97) || (X.ID==2 && maze[X.CrR][X.CrC]=='B' && (maze[X.DesR][X.DesC]<65||maze[X.DesR][X.DesC]>90))){
            if ((abs(DiffC)==abs(DiffR)) && (abs(DiffC)!=0)){
                        if (X.CrR<X.DesR && X.CrC<X.DesC){
                            while (i!=X.DesR-1){
                                if (maze[i+1][j+1]=='.' || maze[i+1][j+1]=='-')
                                    flag=0;
                                else{
                                    flag=1;
                                    break;
                                }
                                i++;
                                j++;
                                }
                        }
                        else if (X.CrR<X.DesR && X.CrC>X.DesC){
                            while (i!=X.DesR-1){
                                if (maze[i+1][j-1]=='.' || maze[i+1][j-1]=='-')
                                    flag=0;
                                else{
                                    flag=1;
                                    break;
                                }
                                i++;
                                j--;
                            }
                        }
                       else if (X.CrR>X.DesR && X.CrC>X.DesC){
                            while (i!=X.DesR+1){
                                if (maze[i-1][j-1]=='.' || maze[i-1][j-1]=='-')
                                    flag=0;
                                else{
                                    flag=1;
                                    break;
                                }
                                i--;
                                j--;
                            }
                        }
                        else if (X.CrR>X.DesR && X.CrC<X.DesC){
                            while (i!=X.DesR+1){
                                if (maze[i-1][j+1]=='.' || maze[i-1][j+1]=='-')
                                    flag=0;
                                else{
                                    flag=1;
                                    break;
                                }
                                i--;
                                j++;
                            }
                        }
                    if(flag==0)
                        available=1;
                    else
                        available=0;

            }
            }

            else
                available=0;

    return available;
}


int Queen(moves X){
    int available;
     char DiffC=X.CrC-X.DesC , DiffR=X.CrR-X.DesR ;
     unsigned char i=X.CrR,flag=0,j=X.CrC;
     if((X.ID==1 && maze[X.CrR][X.CrC]=='q' && maze[X.DesR][X.DesC]<97) || (X.ID==2 && maze[X.CrR][X.CrC]=='Q' && (maze[X.DesR][X.DesC]<65||maze[X.DesR][X.DesC]>90))){
            if ((abs(DiffC)==abs(DiffR)) && (abs(DiffC)!=0)){
                        if (X.CrR<X.DesR && X.CrC<X.DesC){
                            while (i!=X.DesR-1){
                                if (maze[i+1][j+1]=='.' || maze[i+1][j+1]=='-')
                                    flag=0;
                                else{
                                    flag=1;
                                    break;
                                }
                                i++;
                                j++;
                                }
                        }
                        else if (X.CrR<X.DesR && X.CrC>X.DesC){
                            while (i!=X.DesR-1){
                                if (maze[i+1][j-1]=='.' || maze[i+1][j-1]=='-')
                                    flag=0;
                                else{
                                    flag=1;
                                    break;
                                }
                                i++;
                                j--;
                            }
                        }
                       else if (X.CrR>X.DesR && X.CrC>X.DesC){
                            while (i!=X.DesR+1){
                                if (maze[i-1][j-1]=='.' || maze[i-1][j-1]=='-')
                                    flag=0;
                                else{
                                    flag=1;
                                    break;
                                }
                                i--;
                                j--;
                            }
                        }
                        else if (X.CrR>X.DesR && X.CrC<X.DesC){
                            while (i!=X.DesR+1){
                                if (maze[i-1][j+1]=='.' || maze[i-1][j+1]=='-')
                                    flag=0;
                                else{
                                    flag=1;
                                    break;
                                }
                                i--;
                                j++;
                            }
                        }
                    if(flag==0)
                        available=1;
                    else
                        available=0;

            }
            else if((DiffC==0)&&(DiffR!=0)){
                if (X.CrR<X.DesR){
                    for(i=X.CrR+1;i<X.DesR;i++){
                        if (maze[i][j]==45 || maze[i][j]==46)
                            flag=0;
                        else{
                            flag=1;
                            break;
                        }

                    }
                }
                else if (X.CrR>X.DesR){
                    for(i=X.CrR-1;i>X.DesR;i--){
                        if (maze[i][j]==45 || maze[i][j]==46)
                            flag=0;
                        else{
                            flag=1;
                            break;
                        }

                    }
                }
                if(flag==0)
                    available=1;
                else
                    available=0;
            }
            else if((DiffR==0)&&(DiffC!=0)){
                if (X.CrC<X.DesC){
                    for(j=X.CrC+1;j<X.DesC;j++){
                        if (maze[i][j]==45 || maze[i][j]==46)
                            flag=0;
                        else{
                            flag=1;
                            break;
                        }

                    }
                }
                else if (X.CrC>X.DesC){
                    for(j=X.CrC-1;j>X.DesC;j--){
                        if (maze[i][j]==45 || maze[i][j]==46)
                            flag=0;
                        else{
                            flag=1;
                            break;
                        }

                    }
                }
                if(flag==0)
                    available=1;
                else
                    available=0;
            }

            else
                available=0;

    }
    else
        available=0;

    return available;
}

int King(moves X){
    int available;
    char DiffC=X.CrC-X.DesC ,DiffR=X.CrR-X.DesR ;
     if((X.ID==1 && maze[X.CrR][X.CrC]=='k' && maze[X.DesR][X.DesC]<97) || (X.ID==2 && maze[X.CrR][X.CrC]=='K' && (maze[X.DesR][X.DesC]<65||maze[X.DesR][X.DesC]>90))){
        if(((DiffC==0)&&(abs(DiffR)==1))||((abs(DiffC)==1)&&(DiffR==0))||((abs(DiffC)==1)&&(abs(DiffR)==1))){
             available=1;
        }

        else
            available=0;
     }
    else
        available=0;
    return available;
}

void Move(moves X){
    if (maze[X.DesR][X.DesC]>96)
        Out01[N01++]=maze[X.DesR][X.DesC];
    else if(maze[X.DesR][X.DesC]>65&&maze[X.DesR][X.DesC]<90)
        Out02[N02++]=maze[X.DesR][X.DesC];
    //Undo(X);
    maze[X.DesR][X.DesC]=maze[X.CrR][X.CrC];
    if (X.CrR%2==0&&X.CrC%2==0)
        maze[X.CrR][X.CrC]='-';
    else if(X.CrR%2==0)
        maze[X.CrR][X.CrC]='.';
    else if (X.CrC%2==0)
        maze[X.CrR][X.CrC]='.';
    else
        maze[X.CrR][X.CrC]='-';
    Print_Maze(N01,N02);
}


/*void Undo(moves X){
    static moves NX;
    NX.CrC=X.DesC;
    NX.CrR=X.DesR;
    NX.DesC=X.CrC;
    NX.DesR=X.CrR;
    static moves Undo[2000];
    static int Count = 0;
    Undo[Count++]=NX;
}*/
/*void Save(){
    FILE *fb;
    fb=fopen("Game.txt","w");//W for write
    fprintf (fb,"\t\t\tA\tB\tC\tD\tE\tF\tG\tH\n\n\n");
    for (i=0;i<8;i++){
       if (N2==1){
            fprintf(fb,"\t%c   ",Out02[N2]);
            N2--;
        }
        else if (N2){
            fprintf(fb,"\t%c  %c",Out02[N2],Out02[--N2]);
            N2-=2;
        }
        else fprintf(fb,"\t    ");
        fprintf(fb,"\t    ");//Extra
        fprintf(fb,"\t%d",i);
        for (j='A';j<='H';j++){
           fprintf(fb,"\t%c",maze[i][j]);
        }
        fprintf(fb,"\t%d\t",i);
        if (N1==1){
            fprintf(fb,"%c   \t",Out01[N1]);
            N1--;
        }
        else if (N1){
            fprintf(fb,"%c  %c\t",Out01[N1],Out01[--N1]);
            N1--;
        }
        //else fprintf(fb,"    \t");
        fprintf(fb,"\n\n");
    fprintf(fb,"\n\n\t\t\tA\tB\tC\tD\tE\tF\tG\tH\n\n");
    fclose(fb);
}*/

void check(moves X){
    unsigned char i,j;
    int available=0 ,flag=0,n,m;
    dangerous danger;
    int counter1=0,counter2=0;
    if (X.ID==1){
        for(i=0;i<8;i++){
            for(j=0;j<'I';j++){
                if(maze[i][j]=='K'){
                    X.DesC=j;
                    X.DesR=i;
                    for (m=0;m<8;m++){
                        for(n='A';n<'I';n++){
                            X.CrC=n;
                            X.CrR=m;
                            if(maze[m][n]=='p'){
                                available=pawn(X);
                                if(available==1){
                                    danger.name='p';
                                    danger.row=m;
                                    danger.colomn=n;
                                    arr2[counter2++]=danger;
                                }
                            }
                            else if(maze[m][n]=='n'){
                                available=Knight(X);
                                if(available==1){
                                    danger.name='n';
                                    danger.row=m;
                                    danger.colomn=n;
                                    arr2[counter2++]=danger;
                                }

                            }
                            else if(maze[m][n]=='r'){
                                available=rook(X);
                                if(available==1){
                                    danger.name='r';
                                    danger.row=m;
                                    danger.colomn=n;
                                    arr2[counter2++]=danger;
                                }
                            }
                            else if(maze[m][n]=='b'){
                                available=Bishop(X);
                                if(available==1){
                                    danger.name='b';
                                    danger.row=m;
                                    danger.colomn=n;
                                    arr2[counter2++]=danger;
                                }
                            }
                            else if(maze[m][n]=='q'){
                                available=Queen(X);
                                if(available==1){
                                    danger.name='q';
                                    danger.row=m;
                                    danger.colomn=n;
                                    arr2[counter2++]=danger;
                                }
                            }
                            else if(maze[m][n]=='k'){
                                available=King(X);
                                if(available==1){
                                    danger.name='k';
                                    danger.row=m;
                                    danger.colomn=n;
                                    arr2[counter2++]=danger;
                                }
                            }

                        }
                    }
                    flag=1;
            }
            if (flag==1)
                break;
        }
        if (flag==1)
            break;
    }
    if(counter2>0)
        printf("\nCHECK PLATER2!!!\n");
    }
    else if(X.ID==2){
            for(i=0;i<8;i++){
            for(j=0;j<'I';j++){
                if(maze[i][j]=='k'){
                    X.DesC=j;
                    X.DesR=i;
                    for (m=0;m<8;m++){
                        for(n='A';n<'I';n++){
                            X.CrC=n;
                            X.CrR=m;
                            if(maze[m][n]=='P'){
                                available=pawn(X);
                                if(available==1){
                                    danger.name='P';
                                    danger.row=m;
                                    danger.colomn=n;
                                    arr1[counter1++]=danger;
                                }
                            }
                            else if(maze[m][n]=='N'){
                                available=Knight(X);
                                if(available==1){
                                    danger.name='N';
                                    danger.row=m;
                                    danger.colomn=n;
                                    arr1[counter1++]=danger;
                                }

                            }
                            else if(maze[m][n]=='R'){
                                available=rook(X);
                                if(available==1){
                                    danger.name='R';
                                    danger.row=m;
                                    danger.colomn=n;
                                    arr1[counter1++]=danger;
                                }
                            }
                            else if(maze[m][n]=='B'){
                                available=Bishop(X);
                                if(available==1){
                                    danger.name='B';
                                    danger.row=m;
                                    danger.colomn=n;
                                    arr1[counter1++]=danger;
                                }
                            }
                            else if(maze[m][n]=='Q'){
                                available=Queen(X);
                                if(available==1){
                                    danger.name='Q';
                                    danger.row=m;
                                    danger.colomn=n;
                                    arr1[counter1++]=danger;
                                }
                            }
                            else if(maze[m][n]=='K'){
                                available=King(X);
                                if(available==1){
                                    danger.name='K';
                                    danger.row=m;
                                    danger.colomn=n;
                                    arr1[counter1++]=danger;
                                }
                            }

                        }
                    }
                    flag=1;
            }
            if (flag==1)
                break;
        }
        if (flag==1)
            break;
    }
    if(counter1>0)
        printf("\nCHECK PLATER1!!!\n");
    }
}

