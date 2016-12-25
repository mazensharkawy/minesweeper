#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void start();
void play();
void count_adjacent_bombs(char** grid,int xrow,int ycol,int rows,int cols, int state);
void lose();
void load();
void leaders();
void save();
void won();

struct game{
    char **grid;
    int rows,cols,seconds,moves,mines,qmarks,flags;
};
int main()
{

    int i=0;
    printf("1.Start Game\n2.Load Game\n3.Leaderboard\nEnter the no. of the desired operation");
    scanf("%d",&i);
    while(i<1 || i>3)
    {
        printf("Please enter a valid number");
        scanf("%d",&i);
    }
    switch(i)
    {
    case 1:
        start();
    case 2:
        load();
    case 3:
        leaders();
    }
}
void start()
{
    printf("\n Enter the number of rows followed by the number of columns.");
    int rows=0;
    int cols=0;
    int i,j;

    scanf("%d",&rows);
    while(rows<5)
    {
        printf("Please enter a valid number(>=5)");
        scanf("%d",&rows);
    }
    scanf("%d",&cols);
    while(cols<5)
    {
        printf("Please enter a valid number(>=5)");
        scanf("%d",&cols);
    }
    int mines = 1 + (rows* cols)/10;

    char** grid = (char**) malloc(sizeof(char*)*rows);
    for(i=0; i<rows; i++) grid[i] =(char*) malloc(sizeof(char)*cols);
    for(i=0; i<rows; i++)
    {
        for(j=0; j<cols; j++) grid[i][j]='X';
    }

    int seconds=0;
    int flags=0;
    int qmarks=0;
    int moves=0;
    play(grid,rows,cols,seconds,flags,qmarks,moves,mines);
}

void play(char** grid,int rows,int cols,int seconds,int flags,int qmarks,int moves,int mines)
{
    time_t start,end;
    time (&start);
    int i,j,op,xrow,ycol;
    printf("  ");
    for(j=0; j<cols; j++) printf(" %d",j+1);
    if(cols<10) printf(" ");
    printf("    1.Open");
    for(i=0; i<rows; i++)
    {
        printf("\n%2d ",i+1);
        for(j=0; j<cols; j++)
        {
            if(grid[i][j]=='b')
            {
                printf("%c ",'X');
            }
            else if(grid[i][j]=='f')printf("%c ",'F');
            else if(grid[i][j]=='q')printf("%c ",'?');
            else if(grid[i][j]=='N')
            {
                grid[i][j]='X';
                printf("%c ",grid[i][j]);
            }
            else
            {
                printf("%c ",grid[i][j]);
            }
        }
        switch(i)
        {
        case 0:
            printf("    2.Flag");
            break;
        case 1:
            printf("    3.Question");
            break;
        case 2:
            printf("    4.Unmark");
            break;
        case 3:
            printf("    5.Reaveal Adjacent cells");
            break;
        case 4:
            printf("    6.Save");
            break;
        case 5:
            printf("    Enter number of operation followed by the coordinates of the cell (Row,Col)");
            break;
        case 6:
            printf("    #Moves:%3d, #Flags:%3d, #Q-marks:%3d, Time passed:%2d Minutes%3d Seconds",moves,flags,qmarks,seconds/60,seconds%60);
            break;
        }

    }
    if(rows<7)
    {
        printf("\n");
        for(i=0; i<rows*2+3; i++) printf(" ");
        printf("    Enter number of operation followed by the coordinates of the cell (Row,Col)");
    }
    if(rows<8)
    {
        printf("\n");
        for(i=0; i<rows*2+3; i++) printf(" ");
        printf("    #Moves:%3d, #Flags:%3d, #Q-marks:%3d, Time passed:%2d Minutes%3d Seconds",moves,flags,qmarks,seconds/60,seconds%60);
    }
    scanf("%d",&op);
    while(op<1 || op>7)
    {
        printf("Please enter a valid number");
        scanf("%d",&op);
    }

    srand (time(NULL));
    if(op==1)
    {
        scanf("%d",&xrow);
        while(xrow<1 || xrow>rows)
        {
            printf("Please enter a valid number");
            scanf("%d",&xrow);
        }
        scanf("%d",&ycol);
        while(ycol<1 || ycol>cols)
        {
            printf("Please enter a valid number");
            scanf("%d",&ycol);
        }
        xrow--;
        ycol--;
        if(moves==0)
        {
            int set=0;
            while(set<mines)
            {
                i=rand()%rows;
                j=rand()%cols;
                while((fabs(i-xrow)<=1 && fabs(j-ycol)<=1)||grid[i][j]=='b')
                {
                    i=rand()%rows;
                    j=rand()%cols;
                }
                grid[i][j]='b';
                set++;
            }
        }
        if(grid[xrow][ycol]=='b')
        {
            grid[xrow][ycol]='!';
            lose(grid,rows,cols);
        }
        count_adjacent_bombs(grid,xrow,ycol,rows,cols,1);
        moves++;
    }
    else if (op==2)
    {
        if (moves==0)
        {
            printf("\nCan't flag before opening at least one cell\n");
            play(grid,rows,cols,seconds,0,0,0,0);
        }
        scanf("%d",&xrow);
        while(xrow<1 || xrow>rows)
        {
            printf("Please enter a valid number");
            scanf("%d",&xrow);
        }
        scanf("%d",&ycol);
        while(ycol<1 || ycol>cols)
        {
            printf("Please enter a valid number");
            scanf("%d",&ycol);
        }
        xrow--;
        ycol--;
        if(grid[xrow][ycol]=='b' || grid[xrow][ycol]=='?') grid[xrow][ycol]='F';
        else if (grid[xrow][ycol]=='q' || grid[xrow][ycol]=='X')grid[xrow][ycol]='f';
        else printf("Can't flag an open cell");
    }
    else if(op==3)
    {
        if (moves==0)
        {
            printf("\nCan't question cell before opening at least one cell\n");
            play(grid,rows,cols,seconds,0,0,0,0);
        }
        scanf("%d",&xrow);
        while(xrow<1 || xrow>rows)
        {
            printf("Please enter a valid number");
            scanf("%d",&xrow);
        }
        scanf("%d",&ycol);
        while(ycol<1 || ycol>cols)
        {
            printf("Please enter a valid number");
            scanf("%d",&ycol);
        }
        xrow--;
        ycol--;
        if(grid[xrow][ycol]=='b' || grid[xrow][ycol]=='?') grid[xrow][ycol]='?';
        else if (grid[xrow][ycol]=='X') grid[xrow][ycol]='q';
        else printf("Can't question an open cells !!");
    }
    else if(op==4)
    {
        if (moves==0)
        {
            printf("\nCan't Unmark cell before opening at least one cell\n");
            play(grid,rows,cols,seconds,0,0,0,0);
        }
        scanf("%d",&xrow);
        while(xrow<1 || xrow>rows)
        {
            printf("Please enter a valid number");
            scanf("%d",&xrow);
        }
        scanf("%d",&ycol);
        while(ycol<1 || ycol>cols)
        {
            printf("Please enter a valid number");
            scanf("%d",&ycol);
        }
        xrow--;
        ycol--;
        if(grid[xrow][ycol]=='F' || grid[xrow][ycol]=='?') grid[xrow][ycol]='b';
        else if (grid[xrow][ycol]=='q'|| grid[xrow][ycol]=='f') grid[xrow][ycol]='X';
        else printf("Can't Unmark an open cells !!");
    }
    else if(op==6) save(grid,rows,cols,seconds,flags,qmarks,moves,mines);
    printf("\n");
    time (&end);
    seconds+=(int)difftime (end,start);
    if(moves>4) won(grid,rows,cols,mines,seconds,moves);
    play(grid,rows,cols,seconds,flags,qmarks,moves,mines);
}

void load()
{
    FILE *f=fopen("save.bin","rb");
    if(f==NULL){printf("Save file not found !!");exit(0);}
    struct game current_game;
    fread(&current_game,sizeof(struct game),1,f);
    char **grid= (char**)malloc(sizeof(char*)*current_game.rows);
    int i;
    for (i=0; i<current_game.rows; ++i) {
            grid[i]=(char*)malloc(sizeof(char)*current_game.cols);
            fread(grid[i], sizeof(grid[i][0]), current_game.cols, f);

    }
    play(grid,current_game.rows,current_game.cols,current_game.seconds,current_game.flags,current_game.qmarks,current_game.moves,current_game.mines);
}

void save(char** grid,int rows,int cols,int seconds,int flags,int qmarks,int moves,int mines)
{
    FILE *f=fopen("save.bin","wb");
    struct game current_game;
    current_game.rows=rows;
    current_game.cols=cols;
    current_game.seconds=seconds;
    current_game.flags=flags;
    current_game.qmarks=qmarks;
    current_game.moves=moves;
    current_game.mines=mines;
    fwrite(&current_game,sizeof(struct game),1,f);
    int i;
    for (i=0; i<rows; ++i) fwrite(grid[i], sizeof(grid[i][0]), cols, f);
    printf("GAME SAVED !!\nEnter 0 to continue playing and -1 to exit");
    i=3;
    scanf("%d",&i);
    while(i>0 || i<-1){printf("\nPlease enter a valid number\n");scanf("%d",&i);}
    if(i==0) return;
    else exit(0);
}

void leaders()
{
    FILE* f = fopen("leaderboard.txt","r");
    if(f==NULL){printf("\nLeaderboard file not found");exit(1);}
    char line[25];
    line[0]='\0';
    printf("\nLEADERBOARD:\n___________\n\n");
    int i=0;char c;
    fscanf(f,"%c",&c);
    fseek(f,0,SEEK_SET);
    while(!feof(f))
    {
        fgets(line,255,f);
        i++;
        printf("%s",line);

    }
    if(!i) printf("\nLeaderboard is empty");
    else printf("\n");
    printf("\nEnter 0 to return to the main menu and -1 to exit");
    i=3;
    scanf("%d",&i);
    while(i>0 || i<-1){printf("\nPlease enter a valid number\n");scanf("%d",&i);}
    if(i==0) main();
    else exit(0);
}

void count_adjacent_bombs(char** grid,int xrow,int ycol,int rows,int cols,int state)
{
    if(grid[xrow][ycol]=='b' || grid[xrow][ycol]=='F'|| grid[xrow][ycol]=='?' ||grid[xrow][ycol]=='N'||grid[xrow][ycol]==' ')
    {
        return;
    }
    int i,j;
    int bombs=0;
    if(xrow>0)
    {
        if(grid[xrow-1][ycol]=='b' || grid[xrow-1][ycol]=='F'|| grid[xrow-1][ycol]=='?') bombs++;
        if(ycol>0)
        {
            if(grid[xrow-1][ycol-1]=='b' || grid[xrow-1][ycol-1]=='F'|| grid[xrow-1][ycol]=='?')
            {
                bombs++;
            }
        }
        if(ycol<cols-1)
        {
            if(grid[xrow-1][ycol+1]=='b' || grid[xrow-1][ycol+1]=='F'|| grid[xrow-1][ycol]=='?')
            {
                bombs++;
            }
        }

    }
    if(xrow<rows-1)
    {
        if(grid[xrow+1][ycol]=='b' || grid[xrow+1][ycol]=='F'|| grid[xrow+1][ycol]=='?') bombs++;
        if(ycol>0)
        {
            if(grid[xrow+1][ycol-1]=='b' || grid[xrow+1][ycol-1]=='F'|| grid[xrow+1][ycol]=='?')
            {
                bombs++;
            }
        }
        if(ycol<cols)
        {
            if(grid[xrow+1][ycol+1]=='b' || grid[xrow+1][ycol+1]=='F'|| grid[xrow+1][ycol]=='?')
            {
                bombs++;
            }
        }
    }
    if(ycol>0)
    {
        if(grid[xrow][ycol-1]=='b' || grid[xrow][ycol-1]=='F'|| grid[xrow][ycol-1]=='?')
        {
            bombs++;
        }
    }
    if(ycol<cols-1)
    {
        if(grid[xrow][ycol+1]=='b' || grid[xrow][ycol+1]=='F' || grid[xrow][ycol+1]=='?')
        {
            bombs++;
        }
    }
    if(bombs==0)
    {
        grid[xrow][ycol]=' ';
        /**/
        if(xrow>0)
        {
            if(grid[xrow-1][ycol]=='b' || grid[xrow-1][ycol]=='F' ||grid[xrow-1][ycol]=='?'||grid[xrow-1][ycol]=='N'||grid[xrow-1][ycol]==' ') return;
            else count_adjacent_bombs(grid,xrow-1,ycol,rows,cols,0);
            if(ycol>0)
            {
                if(grid[xrow-1][ycol-1]=='b' || grid[xrow-1][ycol-1]=='F'||grid[xrow-1][ycol-1]=='?'||grid[xrow-1][ycol-1]=='N'||grid[xrow-1][ycol-1]==' ') return;
                else count_adjacent_bombs(grid,xrow-1,ycol-1,rows,cols,0);
            }
            if(ycol<cols-1)
            {
                if(grid[xrow-1][ycol+1]=='b' || grid[xrow-1][ycol+1]=='F'||grid[xrow-1][ycol+1]=='?'||grid[xrow-1][ycol+1]=='N'||grid[xrow-1][ycol+1]==' ') return;
                else count_adjacent_bombs(grid,xrow-1,ycol+1,rows,cols,0);
            }

        }
        if(xrow<rows-1)
        {
            if(grid[xrow+1][ycol]=='b' || grid[xrow+1][ycol]=='F'||grid[xrow+1][ycol]=='?'||grid[xrow+1][ycol]=='N'||grid[xrow+1][ycol]==' ') return;
            else count_adjacent_bombs(grid,xrow+1,ycol,rows,cols,0);
            if(ycol>0)
            {
                if(grid[xrow+1][ycol-1]=='b' || grid[xrow+1][ycol-1]=='F'||grid[xrow+1][ycol-1]=='?'||grid[xrow+1][ycol-1]=='N'||grid[xrow+1][ycol-1]==' ') return;
                else count_adjacent_bombs(grid,xrow+1,ycol-1,rows,cols,0);
            }
            if(ycol<cols-1)
            {
                if(grid[xrow+1][ycol+1]=='b' || grid[xrow+1][ycol+1]=='F'||grid[xrow+1][ycol+1]=='?'||grid[xrow+1][ycol+1]=='N'||grid[xrow+1][ycol+1]==' ') return;
                else count_adjacent_bombs(grid,xrow+1,ycol+1,rows,cols,0);
            }
        }
        if(ycol>0)
        {
            if(grid[xrow][ycol-1]=='b' || grid[xrow][ycol-1]=='F'||grid[xrow][ycol-1]=='?'||grid[xrow][ycol-1]=='N'||grid[xrow][ycol-1]==' ') return;
            else count_adjacent_bombs(grid,xrow,ycol-1,rows,cols,0);
        }
        if(ycol<cols-1)
        {
            if(grid[xrow][ycol+1]=='b' || grid[xrow][ycol+1]=='F'||grid[xrow][ycol+1]=='?'||grid[xrow][ycol+1]=='N'||grid[xrow][ycol+1]==' ') return;
            else count_adjacent_bombs(grid,xrow,ycol+1,rows,cols,0);
        }
    }
    else grid[xrow][ycol]=48+bombs; //ASCII code for the numbers to display them as characters
}
void lose (char** grid,int rows,int cols)
{
    int i,j;
    printf("\n%30s The bomb went \"BOOM!!!\""," ");
    for(i=0; i<rows; i++)
    {
        printf("\n%2d ",i+1);
        for(j=0; j<cols; j++)
        {
            if(grid[i][j]=='b' || grid[i][j]=='F' || grid[i][j]=='?')
            {
                printf("%c ",'*');
            }
            else if(grid[i][j]=='f')
            {
                printf("%c ",'-');
            }
            else printf("%c ",grid[i][j]);
        }
    }
    printf("\n%30s YOU LOST !!!!!"," ");
    exit(0);
}

void won(char** grid,int rows,int cols,int mines,int seconds,int moves)
{
    int i,j,not_bombs=0;
    for(i=0; i<rows; i++)
    {
        for(j=0; j<cols; j++)
        {
            if(grid[i][j]==' ') not_bombs++;
            if(grid[i][j]>48 && grid[i][j]<57) not_bombs++;
        }
    }
    if(((rows*cols)-not_bombs)!=mines) return; //x f F q ?
    printf("\n%20s YOU WON !!!!!"," ");
    int score = (pow(rows,4)*pow(cols,4)/seconds*moves);
    printf("\nYour Score= %d",score);
    printf("\nEnter Your name for Leaderboard");
    char name[25];
    char line[30];
    scanf("%s",&name);
    FILE* f = fopen("leaderboard.txt","r");
    FILE* temp = fopen("temp.txt","w");
    char ch;
    fscanf(f,"%c",&ch);
    fseek(f,0,SEEK_SET);
    while(!feof(f))
    {
        fscanf(f, "%[^,]", line);
        printf("\nscanned the name %s",line);
        int s;
        fscanf(f,",%d",&s);
        if(strcasecmp(line,name)!=0)
        {
            score+=s;
            fprintf(temp,"%s,%d",line,score);
        }
        else fprintf(temp,"%s,%d",line,s);
    }
        fclose(f);fclose(temp);
        FILE* f1;
        FILE* f2;

        f1=fopen("temp.txt","r");
        if(f1==NULL)
        {
            printf("error reading file ");
            exit(1);
        }
        f2=fopen("leaderboard.txt","w");
        if(f2==NULL)
        {
            printf("error creating file ");
            exit(1);
        }
        fscanf(f1,"%c",&ch);
        while(!feof(f1))
        {
            fprintf(f2,"%c",ch);
            fscanf(f1,"%c",&ch);
        }
        fclose(f1);
        fclose(f2);


    exit(0);
}
