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
unsigned char maze[8][8];//main platform
unsigned char i,j,N01,N02; //Counters
unsigned char Out01[16],Out02[16];
void check_Content(moves X);
void pawn (moves X);
void Queen(moves X);
void King(moves X);
void Move(moves X);
void Bishop(moves X);
void Knight(moves X);
void Print_Maze(unsigned char N1,unsigned char N2){
    printf ("\t\t\tA\tB\tC\tD\tE\tF\tG\tH\n\n\n");
    for (i=0;i<8;i++){
        printf("\t%d\t",i);
        for (j='A';j<='H';j++){
            printf("\t%c",maze[i][j]);
        }
        if (N1==1){
            printf("\t\t%c",Out01[N1]);
            N1--;
        }
        else if (N1){
            printf("\t\t%c  %c",Out01[N1],Out01[N1]);
            N1-=2;
        }
        if (N2==1){
            printf("\t\t%c",Out02[N2]);
            N2--;
        }
        else if (N2){
            printf("\t\t%c  %c",Out02[N2],Out02[N2]);
            N2-=2;
        }
        printf("\t\t%d",i);
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
    maze [7][68]=82;
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
    printf("CrR: %d ,CrC: %c \nDesR: %d ,DesC: %c \n",X.CrR,X.CrC,X.DesR,X.DesC);
    switch(piece){
        case 'P':pawn(X);break;
        case 'R':rook(X);break;
        case 'K':King(X);break;
        case 'Q':Queen(X);break;
        case 'B':Knight(X);break;
        case 'N':Knight(X);break;
    }
}
void rook(moves X){
    char DiffC=X.CrC-X.DesC , DiffR=X.CrR-X.DesR ;
    printf("%d\n%d\n",DiffC,DiffR);
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
        for (i+=1;i<=K;i++){
            if (maze[i][X.CrC]=='.'||maze[i][X.CrC]=='-')
                j++;
            else{
                j--;
                break;
            }
        }
        if (j==i)
            Move(X);
        else printf("\nNot available\n");
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
        for (i+=1;i<=K;i++){
            if (maze[X.CrR][i]=='.'||maze[X.CrR][i]=='-')
                j++;
            else  {
                j--;
                break;
            }
        }
        if (j==i)
            Move(X);
        else printf("\nNot available\n");
    }
    else printf("\nNot available\n");
}

void Scan(){
    moves X;
    char move[5];
    fgets(move,5,stdin);
    X.CrR=move[1]-48;
    X.CrC=(char)toupper((int)move[0]);
    X.DesR=move[3]-48;
    X.DesC=(char)toupper((int)move[2]);
   // check_Content(X);
   pieces(X);
}

int main()
{
    N01=N02=0;
    Maze();
    while(1)
        Scan();

    return 0;
}
void pawn (moves X){
    static int Y=0;
    unsigned char DiffC=X.CrC-X.DesC ,DiffR=X.CrR-X.DesR ;
    X.ID=1;
    if (Y==0){
        if (((((X.ID==1)&&(DiffR==2))||((X.ID==1)&&(DiffR==-2)))&&(DiffC==0))||((((X.ID==1)&&(DiffR==1))||((X.ID==1)&&(DiffR==-1)))&&(DiffC==0)))
            Move(X);
        else printf("\nNot available\n");
    }
    else{
        if ((((X.ID==1)&&(DiffR==1))||((X.ID==2)&&(DiffR==-1)))&&(DiffC==0))
            Move(X);
        else printf("\nNot available\n");
    }
}
void check_Content(moves X){
    if ((maze[X.DesR][X.DesC]!='.')||(maze[X.DesR][X.DesC]!='-')){
        if(abs(maze[X.DesR][X.DesC]-maze[X.CrR][X.CrC])>31){
            if (maze[X.DesR][X.DesC]<96){
                Out01[N01]=maze[X.DesR][X.DesC];
                N01++;
            }
            else{
                Out02[N02]=maze[X.DesR][X.DesC];
                N02++;
            }
            pieces(X);
        }
        else printf("\nNot available\n");
    }
    else pieces(X);
}

void Knight(moves X){
    char DiffC=X.CrC-X.DesC ,DiffR=X.CrR-X.DesR ;
    if(abs(DiffR)==1){
            if(abs(DiffC)==2)
                Move(X);
            else printf("/nnot available\n");
    }
    else if(abs(DiffR)==2){
            if(abs(DiffC)== 1)
                Move(X);
            else printf("/nnot available\n");
    }
    // We need to check content of the desired cell
}
void King(moves X){
    char DiffC=X.CrC-X.DesC ,DiffR=X.CrR-X.DesR ;
    if(((DiffC==0)&&(abs(DiffR)==1))||((abs(DiffC)==1)&&(DiffR==0))||((abs(DiffC)==1)&&(abs(DiffR)==1)))
        Move(X);
    else printf("\nnot available\n");
}
void Queen(moves X){
}
void Bishop(moves X){
}
void Move(moves X){
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
