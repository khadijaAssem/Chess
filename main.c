

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct  {
    unsigned char ID;
    unsigned char CrR;
    unsigned char CrC;
    unsigned char DesR;
    unsigned char DesC;
}moves ;
typedef struct {
    unsigned char C;
    unsigned char R;
}KingIndex;

unsigned char maze[8][8];//main platform
unsigned char i,j; //Counters
unsigned char Out01[8],Out02[8];
int N01=0,N02=0;
void check_Content(moves X);
void pawn (moves X);
void Queen(moves X);
void King(moves X);
void Move(moves X);
void Bishop(moves X);
void Knight(moves X);

void Print_Maze(unsigned char N2,unsigned char N1){
 
    printf ("\t\t\tA\tB\tC\tD\tE\tF\tG\tH\n\n\n");
    for (i=0;i<8;i++){
       if (N2==1){
            printf("\t%c   ",Out02[N2]);
            N2--;
        }
        else if (N2){
            printf("\t%c  %c",Out02[N2],Out02[--N2]);
            N2-=2;
        }
        else printf("\t    ");
        printf("\t%d",i);
        for (j='A';j<='H';j++){
           printf("\t%c",maze[i][j]);
        }
        printf("\t%d\t",i);
        if (N1==1){
            printf("%c   \t",Out01[N1]);
            N1--;
        }
        else if (N1){
            printf("%c  %c\t",Out01[N1],Out01[--N1]);
            N1--;
        }
        else printf("    \t");
        printf("\n\n");
    }
    printf ("\n\n\t\t\tA\tB\tC\tD\tE\tF\tG\tH\n\n");

}
void Maze(){
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
void pieces(moves X){
    char piece = toupper(maze[X.CrR][X.CrC]);
   // printf("CrR: %d ,CrC: %c \nDesR: %d ,DesC: %c \n",X.CrR,X.CrC,X.DesR,X.DesC);
    switch(piece){
        case 'P':pawn(X);break;
        case 'R':rook(X);break;
        case 'K':King(X);break;
        case 'Q':Queen(X);break;
        case 'B':Bishop(X);break;
        case 'N':Knight(X);break;
    }
}
void rook(moves X){
    char DiffC=X.CrC-X.DesC , DiffR=X.CrR-X.DesR ;
    printf("%d\n%d\n",DiffC,DiffR);
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
            Move(X);
        else {
            printf("Not available\nPlayer%d move:\n",X.ID);
            Scan(X);
        }
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
            Move(X);
        else {
            printf("Not available\nPlayer%d move:\n",X.ID);
            Scan(X);
        }
    }
    else {
        printf("Not available\nPlayer%d move:\n",X.ID);
        Scan(X);
    }
    }
    else {
        printf("Not available\nPlayer%d move:\n",X.ID);
        Scan(X);
    }
}

void Scan(moves X){
    char move[5];
    scanf("%s",&move);
    X.CrR=move[1]-48;
    X.CrC=(char)toupper((int)move[0]);
    X.DesR=move[3]-48;
    X.DesC=(char)toupper((int)move[2]);
    pieces(X);
}


int main()
{
    N01=N02=0;
    moves X;
    Maze();
    while(1){
        printf("\nPlayer1 move:\n");
        X.ID=1;
        Scan(X);
        printf("\nPlayer2 move:\n");
        X.ID=2;
        Scan(X);

    }


    return 0;
}

void pawn (moves X){// Promotion Eating
    char DiffC=X.CrC-X.DesC ,DiffR=X.CrR-X.DesR ;
    unsigned char i,j,promotion,flag=0;
    if (X.CrR==1||X.CrR==6){
        if (((((X.ID==2)&&(DiffR==2))||((X.ID==1)&&(DiffR==-2)))&&(DiffC==0))||((((X.ID==2)&&(DiffR==1))||((X.ID==1)&&(DiffR==-1)))&&(DiffC==0)))
           flag=1;
        else flag = 0;
    }
    else if((abs(DiffC)==1&&abs(DiffR)==1)&&((X.ID==1&& DiffR==-1&&(maze[X.DesR][X.DesC]>65 && maze[X.DesR][X.DesC]<90))||(X.ID==2&&DiffR==1&&maze[X.DesR][X.DesC]>90))){
            Move(X);
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
                         Move(X);
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
                Move(X);
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
    if (flag==0){
        printf("Not available\nPlayer%d move:\n",X.ID);
        Scan(X);
    }
}

void Knight(moves X){
    printf("move from:%c%d to:%c%d\n",X.CrC,X.CrR,X.DesC,X.DesR);
    char DiffC=X.CrC-X.DesC ,DiffR=X.CrR-X.DesR ;
    if((abs(DiffR)==1&&abs(DiffC)==2) || (abs(DiffR)==2&&abs(DiffC)==1)){
        if(X.ID==1 && maze[X.CrR][X.CrC]=='n' && maze[X.DesR][X.DesC]<97)
            Move(X);
        else if (X.ID==2 && maze[X.CrR][X.CrC]=='N' && (maze[X.DesR][X.DesC]<65||maze[X.DesR][X.DesC]>90))
            Move(X);
        else{
            printf("Not available\nPlayer%d move:\n",X.ID);
            Scan(X);

        }
    }
    else {
        printf("Not available\nPlayer%d move:\n",X.ID);
        Scan(X);

    }

}


void Bishop(moves X){
    printf("move from:%c%d to:%c%d\n",X.CrC,X.CrR,X.DesC,X.DesR);
    char DiffC=X.CrC-X.DesC , DiffR=X.CrR-X.DesR ;
    unsigned char i=X.CrR,flag=0,j=X.CrC;
     if((X.ID==1 && maze[X.CrR][X.CrC]=='b' && maze[X.DesR][X.DesC]<97) || (X.ID==2 && maze[X.CrR][X.CrC]=='B' && (maze[X.DesR][X.DesC]<65||maze[X.DesR][X.DesC]>90))){
            if ((abs(DiffC)==abs(DiffR)) && (abs(DiffC)!=0)){
                    //while(i!=X.DesR){
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
                   // }
                    if(flag==0)
                        Move(X);
                    else{
                        printf("Not available\nPlayer%d move:\n",X.ID);
                        Scan(X);

                    }

            }
            }

            else{
                printf("Not available\nPlayer%d move:\n",X.ID);
                Scan(X);

            }
}


void Queen(moves X){
     char DiffC=X.CrC-X.DesC , DiffR=X.CrR-X.DesR ;
     printf("move from:%c%d to:%c%d\n",X.CrC,X.CrR,X.DesC,X.DesR);
     unsigned char i=X.CrR,flag=0,j=X.CrC;
     if((X.ID==1 && maze[X.CrR][X.CrC]=='q' && maze[X.DesR][X.DesC]<97) || (X.ID==2 && maze[X.CrR][X.CrC]=='Q' && (maze[X.DesR][X.DesC]<65||maze[X.DesR][X.DesC]>90))){
            if ((abs(DiffC)==abs(DiffR)) && (abs(DiffC)!=0)){
                    //while(i!=X.DesR){
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
                   // }
                    if(flag==0)
                        Move(X);
                    else{
                        printf("Not available\nPlayer%d move:\n",X.ID);
                        Scan(X);

                    }

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
                    Move(X);
                else{
                    printf("Not available\nPlayer%d move:\n",X.ID);
                    Scan(X);

                }
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
                    Move(X);
                else{
                    printf("Not available\nPlayer%d move:\n",X.ID);
                    Scan(X);

                }
            }

            else{
                printf("Not available\nPlayer%d move:\n",X.ID);
                Scan(X);

            }

    }
    else{
        printf("Not available\nPlayer%d move:\n",X.ID);
        Scan(X);

    }
}

void King(moves X){
    KingIndex k1;
    KingIndex k2;
    char DiffC=X.CrC-X.DesC ,DiffR=X.CrR-X.DesR ;
     if((X.ID==1 && maze[X.CrR][X.CrC]=='k' && maze[X.DesR][X.DesC]<97) || (X.ID==2 && maze[X.CrR][X.CrC]=='K' && (maze[X.DesR][X.DesC]<65||maze[X.DesR][X.DesC]>90))){
        if(((DiffC==0)&&(abs(DiffR)==1))||((abs(DiffC)==1)&&(DiffR==0))||((abs(DiffC)==1)&&(abs(DiffR)==1))){
             if (X.ID==1){
                k1.C=X.DesC;
                k1.R=X.DesR;
             }
             else {
                k2.C=X.DesC;
                k2.R=X.DesR;
             }
             Move(X);
        }
           
        else{
            printf("Not available\nPlayer%d move:\n",X.ID);
            Scan(X);
        }
     }
    else{
        printf("Not available\nPlayer%d move:\n",X.ID);
        Scan(X);
    }
}

void Move(moves X){
    if (maze[X.DesR][X.DesC]>96)
        Out01[N01++]=maze[X.DesR][X.DesC];
    else if(maze[X.DesR][X.DesC]>65&&maze[X.DesR][X.DesC]<90)
        Out02[N02++]=maze[X.DesR][X.DesC];
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

//check mate
int Check_Mate(){
    int index;
    for ()
}
