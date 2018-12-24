
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
    unsigned char colomn;
    unsigned char row;
}parts;

typedef struct  {
    unsigned char N1;
    unsigned char N2;
}NO_out_parts;

typedef struct  {
    parts Out01[16];
    parts Out02[16];
    NO_out_parts N;
}out_parts;

typedef struct {
    unsigned char R01;
    unsigned char R02;
    unsigned char C01;
    unsigned char C02;
}King_I;

unsigned char maze[8][8];//main platform
moves Undo[2000];
int count=0;

int pawn (moves X);
int Queen(moves X);
int King(moves X);
int rook(moves X);
int Bishop(moves X);
int Knight(moves X);
void Move(moves X);
void undo(moves X);
void print_redo(int z);
void print_undo(int z);
void check_Mate(moves X);
int check(moves X,unsigned char i, unsigned char j);
int freeze(moves X);
void promotion(moves X);
out_parts OUT(moves X,int a);

void Print_Maze(out_parts total){
    unsigned char i,j;
    printf ("\t\tA\tB\tC\tD\tE\tF\tG\tH\n\n\n");

    for (i=0;i<8;i++){

        if (total.N.N1>0&&2*i<total.N.N1){
            if(total.N.N1%2==0)
                printf("%c %c",total.Out01[2*i].name,total.Out01[2*i+1].name);
            else if (total.N.N1-1>0&&2*i<total.N.N1-1){
                printf("%c %c",total.Out01[2*i].name,total.Out01[2*i+1].name);
            }
            if (total.N.N1%2==1&&2*i>=total.N.N1-1)
                printf("%c",total.Out01[total.N.N1-1].name);
        }

        printf("\t%d",i);
        for (j='A';j<='H';j++){
           printf("\t%c",maze[i][j]);
        }
        printf("\t%d\t",i);
        if (total.N.N2>0&&2*i<total.N.N2){
            if(total.N.N2%2==0)
                printf("%c %c",total.Out02[2*i].name,total.Out02[2*i+1].name);
            else if (total.N.N2-1>0&&2*i<total.N.N2-1){
                printf("%c %c",total.Out02[2*i].name,total.Out02[2*i+1].name);
            }
            if (total.N.N2%2==1&&2*i>=total.N.N2-1)
                printf("%c",total.Out02[total.N.N2-1].name);
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
    out_parts z;
    moves X;
    z=OUT(X,0);
    Print_Maze(z);
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
King_I Index(moves X,unsigned char Poo){
	static King_I index = {0,7,69,69};
	if (Poo==1){
		index.R01=X.DesR;
        index.C01=X.DesC;
        return index;
	}
	else if (Poo==2){
		index.R02=X.DesR;
        index.C02=X.DesC;
        return index;
	}
	else
		return index;
}


int main()
{
    unsigned char ch,i,j,f;
    int t1=0,t2=0,z,available;
    moves X;
    Maze();
   // Save();
   char moves[5];
    while(1){

            do{
                z=count-1;
                printf("\nPlayer1 move:\n");
                X.ID=1;
                scanf("%s",&moves);
                if(strlen(moves)==1){
                    ch=moves[0];
                    if(ch=='u' || ch=='U'){
                            if(z>=0){
                                print_undo(z);
                                z--;
                                count--;
                                t1++;
                                break;
                            }
                            else
                                printf("Not available");
                    }
                    else if(ch=='r' || ch=='R'){
                            if(t2<=t1-1){
                                print_redo(z+1);
                                z++;
                                count++;
                                t2++;
                                break;
                            }
                            else
                                printf("Not available");
                    }
                    else
                        printf("Not available");
                }

                else{
                    X.CrR=moves[1]-48;
                    X.CrC=toupper(moves[0]);
                    X.DesR=moves[3]-48;
                    X.DesC=toupper(moves[2]);
                    available=pieces(X);
                    if (available==1){
                        f=freeze(X);
                        if(f==0)
                            break;
                    }
                    else
                        printf("Not available\n");
                    }

            } while(1);

            check_Mate(X);

           do{
                z=count-1;
                printf("\nPlayer2 move:\n");
                X.ID=2;
                scanf("%s",&moves);
                if(strlen(moves)==1){
                    ch=moves[0];
                    if(ch=='u' || ch=='U'){
                            if(z>=0){
                                print_undo(z);
                                z--;
                                count--;
                                t1++;
                                break;
                            }
                            else
                                printf("Not available");
                    }
                    else if(ch=='r' || ch=='R'){
                            if(t2<=t1-1){
                                print_redo(z+1);
                                z++;
                                count++;
                                t2++;
                                break;
                            }
                            else
                                printf("Not available");

                    }
                    else
                        printf("Not available");
                }
                else{
                    X.CrR=moves[1]-48;
                    X.CrC=toupper(moves[0]);
                    X.DesR=moves[3]-48;
                    X.DesC=toupper(moves[2]);
                    available=pieces(X);
                    if (available==1){
                            f=freeze(X);
                            if(f==0)
                                break;
                    }
                    else
                        printf("Not available");
                }

            } while(1);

            check_Mate(X);
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
                if (j==X.CrR)
                         available=1;
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
            if (j==X.CrR)
                available=1;
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
    unsigned char available;
    char DiffC=X.CrC-X.DesC ,DiffR=X.CrR-X.DesR ;
     if((X.ID==1 && maze[X.CrR][X.CrC]=='k' && maze[X.DesR][X.DesC]<97) || (X.ID==2 && maze[X.CrR][X.CrC]=='K' && (maze[X.DesR][X.DesC]<65||maze[X.DesR][X.DesC]>90))){
        if(((DiffC==0)&&(abs(DiffR)==1))||((abs(DiffC)==1)&&(DiffR==0))||((abs(DiffC)==1)&&(abs(DiffR)==1))){
            //King index
             if (maze[X.CrR][X.CrC]=='k')
                Index(X,1);
            else if (maze[X.CrR][X.CrC]=='K')
                Index(X,2);
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
    out_parts N;
    N=OUT(X,1);
    undo(X);
    maze[X.DesR][X.DesC]=maze[X.CrR][X.CrC];
    if (X.CrR%2==0&&X.CrC%2==0)
        maze[X.CrR][X.CrC]='-';
    else if(X.CrR%2==0)
        maze[X.CrR][X.CrC]='.';
    else if (X.CrC%2==0)
        maze[X.CrR][X.CrC]='.';
    else
        maze[X.CrR][X.CrC]='-';
    Print_Maze(N);
}

out_parts OUT(moves X,int a){
    static out_parts total={' ',' ',' ',' ',' ',' ',' ',' '};
    parts Z;
    if(a==1){
        if (maze[X.DesR][X.DesC]>96){
            Z.row=X.DesR;
            Z.colomn=X.DesC;
            Z.name=maze[X.DesR][X.DesC];
            total.Out01[total.N.N1++]=Z;
        }

        else if(maze[X.DesR][X.DesC]>65&&maze[X.DesR][X.DesC]<90){
            Z.row=X.DesR;
            Z.colomn=X.DesC;
            Z.name=maze[X.DesR][X.DesC];
            total.Out02[total.N.N2++]=Z;
        }
    }
    else if(a==2){
        total.N.N1-=1;
    }
    else if(a==3){
        total.N.N2-=1;
    }
    else if(a==4){
        total.N.N1+=1;
    }
    else if(a==5){
        total.N.N2+=1;
    }

    return total;
}


void undo(moves X){
    moves NX;
    NX.CrC=X.DesC;
    NX.CrR=X.DesR;
    NX.DesC=X.CrC;
    NX.DesR=X.CrR;
    Undo[count++]=NX;
}

void print_undo(int z){
    unsigned char a,b,i,flag=0;
    moves X;
    out_parts total;
    total=OUT(X,0);
    if(total.N.N1>0){
        if(total.Out01[total.N.N1-1].row==Undo[z].CrR && total.Out01[total.N.N1-1].colomn==Undo[z].CrC)
            flag=1;
    }
    if(total.N.N2>0){
        if(total.Out02[total.N.N2-1].row==Undo[z].CrR && total.Out02[total.N.N2-1].colomn==Undo[z].CrC)
            flag=2;
    }

    if(flag==1){
        a=maze[Undo[z].CrR][Undo[z].CrC];
        b=total.Out01[total.N.N1-1].name;
        total=OUT(X,2);

    }
    else if(flag==2){
        a=maze[Undo[z].CrR][Undo[z].CrC];
        b=total.Out02[total.N.N2-1].name;
        total=OUT(X,3);
    }
    else{
        a=maze[Undo[z].CrR][Undo[z].CrC];
        b=maze[Undo[z].DesR][Undo[z].DesC];
    }

    maze[Undo[z].CrR][Undo[z].CrC]=b;
    maze[Undo[z].DesR][Undo[z].DesC]=a;
    Print_Maze(total);
}

void print_redo(int z){unsigned char a,b,i,flag=0;
    moves X;
    out_parts total;
    total=OUT(X,0);
    if(total.N.N1>=0){
        if(total.Out01[total.N.N1].row==Undo[z].CrR && total.Out01[total.N.N1].colomn==Undo[z].CrC)
            flag=1;
    }
    if(total.N.N2>=0){
        if(total.Out02[total.N.N2].row==Undo[z].CrR && total.Out02[total.N.N2].colomn==Undo[z].CrC)
            flag=2;
    }
    a=maze[Undo[z].CrR][Undo[z].CrC];
    b=maze[Undo[z].DesR][Undo[z].DesC];

    if(flag==1){
        maze[Undo[z].CrR][Undo[z].CrC]=b;
        if (Undo[z].DesR%2==0&&Undo[z].DesC%2==0)
            maze[Undo[z].DesR][Undo[z].DesC]='-';
        else if(Undo[z].DesR%2==0)
            maze[Undo[z].DesR][Undo[z].DesC]='.';
        else if (Undo[z].DesC%2==0)
            maze[Undo[z].DesR][Undo[z].DesC]='.';
        else
            maze[Undo[z].DesR][Undo[z].DesC]='-';

        total=OUT(X,4);

    }
    else if(flag==2){
        maze[Undo[z].CrR][Undo[z].CrC]=b;
        if (Undo[z].DesR%2==0&&Undo[z].DesC%2==0)
            maze[Undo[z].DesR][Undo[z].DesC]='-';
        else if(Undo[z].DesR%2==0)
            maze[Undo[z].DesR][Undo[z].DesC]='.';
        else if (Undo[z].DesC%2==0)
            maze[Undo[z].DesR][Undo[z].DesC]='.';
        else
            maze[Undo[z].DesR][Undo[z].DesC]='-';

        total=OUT(X,5);
    }
    else{

        maze[Undo[z].CrR][Undo[z].CrC]=b;
        maze[Undo[z].DesR][Undo[z].DesC]=a;
    }
    Print_Maze(total);
}

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

int check(moves X,unsigned char i,unsigned char j){
    unsigned char available=0,n,m;

    if (X.ID==1){
        X.DesC=j;
        X.DesR=i;
        for (m=0;m<8;m++){
            for(n='A';n<'I';n++){
                X.CrC=n;
                X.CrR=m;
                if(maze[m][n]=='p')
                    available=pawn(X);

                else if(maze[m][n]=='n')
                    available=Knight(X);

                else if(maze[m][n]=='r')
                    available=rook(X);

                else if(maze[m][n]=='b')
                    available=Bishop(X);

                else if(maze[m][n]=='q')
                    available=Queen(X);

                else if(maze[m][n]=='k')
                    available=King(X);

            }
        }
    	if(available)
        	return 1;
    }

    else if(X.ID==2){
        X.DesC=j;
        X.DesR=i;
        for (m=0;m<8;m++){
            for(n='A';n<'I';n++){
                X.CrC=n;
                X.CrR=m;
                if(maze[m][n]=='P')
                    available=pawn(X);

                else if(maze[m][n]=='N')
                    available=Knight(X);

                else if(maze[m][n]=='R')
                    available=rook(X);

                else if(maze[m][n]=='B')
                    available=Bishop(X);

                else if(maze[m][n]=='Q')
                    available=Queen(X);

                else if(maze[m][n]=='K')
                    available=King(X);

            }
        }
    	if(available)
        	return 1;
    }

    return 0;
}

int freeze(moves X){
    unsigned char a,b,f=1;
    King_I place;
    a=maze[X.CrR][X.CrC];
    b=maze[X.DesR][X.DesC];
    if(X.ID==1){
        X.ID=2;
        maze[X.DesR][X.DesC]=a;
        maze[X.CrR][X.CrC]='.';
        if(a=='k'){
            place.R01=X.DesR;
            place.C01=X.DesC;
        }
        else
            place=Index(X,0);
        f=check(X,place.R01,place.C01);
        X.ID=1;
        maze[X.DesR][X.DesC]=b;
        maze[X.CrR][X.CrC]=a;
        if(f==0){
            Move(X);
            if(a=='p')
                promotion(X);

        }
        else
            printf("Not available(frozen)\n");
    }

    else{
        X.ID=1;
        maze[X.DesR][X.DesC]=a;
        maze[X.CrR][X.CrC]='.';
        if(a=='K'){
            place.R02=X.DesR;
            place.C02=X.DesC;
        }
        else
            place=Index(X,0);
        f=check(X,place.R02,place.C02);
        X.ID=2;
        maze[X.DesR][X.DesC]=b;
        maze[X.CrR][X.CrC]=a;
        if(f==0){
            Move(X);
            if(a=='P')
                promotion(X);
        }
        else
            printf("Not available(frozen)\n");
        }

    return f;

}


void check_Mate(moves X){
	King_I index = Index(X,0);

	 char i,j,available=0,Count=0,flag=0;
	if (X.ID==1){
		for (i=index.R02-1;i<=index.R02+1;i++){
	        for (j=index.C02-1;j<=index.C02+1;j++){
	        	if (check(X,i,j)==1){
	            	if ((i == index.R02)&& (j== index.C02))
	            		flag=1;
	           	    available=1;
	                Count++;
	            }
			}
	    }
	}
	else if (X.ID==2){
		for (i=index.R01-1;i<=index.R01+1;i++){
	        for (j=index.C01-1;j<=index.C01+1;j++){
	        	if (check(X,i,j)==1){
	            	if ((i == index.R01)&& (j== index.C01))
	            		flag=1;
	           	    available=1;
	                Count++;
	            }
			}
	    }
	}

    if (flag)
        printf("\nCHECK!!!\n");
    else if (available==1&&Count==9){
    	printf ("\nCHECKMATE!!\n");
    	exit(1);
    }
    else if ((available==1)&&(Count==8)&&(flag=0)){
    	printf("\nSTALEMATE!!\n");
    	exit(1);
}
}
void promotion(moves X){
    char C;
    out_parts N;
    N=OUT(X,0);
    if((X.DesR==0&&X.ID==2) || (X.DesR==7&&X.ID==1)){
        printf("Promotion!!! choose your piece:\nQ\nR\nB\nN\n");
        scanf(" %c",&C);
        if (X.ID==1)
            maze[X.DesR][X.DesC]=tolower(C);
        else
            maze[X.DesR][X.DesC]=toupper(C);
        Print_Maze(N);
       }
}


