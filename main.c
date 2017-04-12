#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct SudokuPlayerDatabase
{    
    char PlayerName[10];
    char LastModificationDate[10];
    char LastModificationTime[5];
    int  Game[9][9];    
};
typedef struct SudokuPlayerDatabase SPD;

int menu();
void choice1(FILE* sudokuptr,SPD sudokugame,char* CUN);
void choice2(FILE* sudokuptr,SPD sudokugame,char* CUN);
void choice3(FILE* sudokuptr,SPD sudokugame,char* CUN);
void choice4(FILE* sudokuptr,SPD sudokugame,char* CUN);
void sudokudisplayer(SPD sudokugame);
char* datefinder();
char* timefinder();
int checker(int newvalue,SPD sudokugame,int x,int y);
float processcalculator(SPD sudokugame);
int congragulations(SPD sudokugame);

int main()
{
    int choice,i,j;
    char CUN[10];
    SPD sudokugame;

    FILE* sudokuptr;


    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            sudokugame.Game[i][j]=0;
        }
    }
    printf("Please enter your name\n");
    scanf("%s",CUN);
    printf("%s welcome to our gamewarehouse\n",CUN);
    choice=menu();
    while(1)
    {
        if(choice==1)
        {
            choice1(sudokuptr,sudokugame,CUN);
//            choice=menu();
        }
        if(choice==2)
        {
            choice2(sudokuptr,sudokugame,CUN);
//            choice=menu();
        }
        if(choice==3){
            choice3(sudokuptr,sudokugame,CUN);
//            choice=menu();
        }
        if(choice==4)
        {
            choice4(sudokuptr,sudokugame,CUN);
//            choice=menu();
        }
        if(choice=5)    
            break;
        else
        {
            printf("illegal choice\n");
            choice=menu();        
        }
    }    
    return 0;
}

int menu()
{
    int choice;
    printf("\nHere are your choices: \n"
            "1-List your games in the system\n"
            "2-Open and play one of your games\n"
            "3-Add a fresh game\n"
            "4-Delete a game\n"
            "5-Quit Game\n");
    
    scanf("%d",&choice);
    return choice;
}

void choice1(FILE* sudokuptr,SPD sudokugame,char* CUN)
{
    int GameNumberOfCUN=0,counter=0,i;
    char LastModificationDate[10];
    char LastModificationTime[5];

    
    sudokuptr=fopen("sudoku.dat","rb");
//    fread(&sudokugame,sizeof(SPD),1,sudokuptr);
//    printf("%s",sudokugame.LastModificationDate);

//    for(i=0;i<11;i++)
//        LastModificationDate[i]=sudokugame.LastModificationDate[i];
//    for(i=0;i<6;i++)
//        LastModificationTime[i]=sudokugame.LastModificationTime[i];
//    rewind(sudokuptr);
            
    while(!feof(sudokuptr))
    {
        fread(&sudokugame,sizeof(SPD),1,sudokuptr);
    //    printf("%s",sudokugame.LastModificationDate);

        for(i=0;i<11;i++)
            LastModificationDate[i]=sudokugame.LastModificationDate[i];
        for(i=0;i<6;i++)
            LastModificationTime[i]=sudokugame.LastModificationTime[i];
    //    printf("t");
        for(i=0;i<11;i++)
        {
            if(CUN[i]==sudokugame.PlayerName[i])
                counter++;
        }
        //    printf("%d  ",counter);
            if(counter==10)
            {
                GameNumberOfCUN++;
                printf("%d %s %s %.2f%\n",GameNumberOfCUN,LastModificationDate,LastModificationTime,processcalculator(sudokugame));
            }
    //    }
        counter=0;
    }
    fclose(sudokuptr);
}
void choice2(FILE* sudokuptr,SPD sudokugame,char* CUN)
{
    int counter1=0,counter2=0,counter3=0,gamechoice,i,x,y,newvalue;
    choice1(sudokuptr,sudokugame,CUN);

    sudokuptr=fopen("sudoku.dat","rb+");

    printf("Enter the number of the game you want to play\n");
    scanf("%d",&gamechoice);

    while(!feof(sudokuptr))
    {
        fread(&sudokugame,sizeof(SPD),1,sudokuptr);
        for(i=0;i<11;i++)
        {
            if(CUN[i]==sudokugame.PlayerName[i])
                counter3++;
        }    
        if(counter3==10)
            counter1++;
        if(counter1<gamechoice)
        {
            counter2++;
        }
        counter3=0;
    }
    fseek(sudokuptr,(counter2)*sizeof(SPD),SEEK_SET);
    fread(&sudokugame,sizeof(SPD),1,sudokuptr);
    sudokudisplayer(sudokugame);
    while(1)
    {    
        fseek(sudokuptr,(counter2)*sizeof(SPD),SEEK_SET);
        printf("Enter the coordinates you want to modify or enter -1 to quit the game");
        scanf("%d",&x);
        if(x==-1)
            break;
        else
        {
            scanf("%d",&y);
            printf("Enter the new value\n");
            scanf("%d",&newvalue);
            system("cls");
            if(checker(newvalue,sudokugame,x,y)==1)
            {                        
                fseek(sudokuptr,(counter2)*sizeof(SPD),SEEK_SET);
                sudokugame.Game[y][x]=newvalue;
                for(i=0;i<11;i++)
                    sudokugame.LastModificationDate[i]=datefinder()[i];
                for(i=0;i<6;i++)
                    sudokugame.LastModificationTime[i]=timefinder()[i];            
                fwrite(&sudokugame,sizeof(SPD),1,sudokuptr);                
            }
            if(congragulations(sudokugame)==1)
            {
                printf("congragulations you finished the game\n");
                break;
            }
            else
                printf("You can't enter this value\n");
            sudokudisplayer(sudokugame);
        }
    }
    fclose(sudokuptr);
}
void choice3(FILE* sudokuptr,SPD sudokugame,char* CUN)
{
    int i;

    sudokuptr=fopen("sudoku.dat","ab");
    for(i=0;i<11;i++)
    {
        sudokugame.PlayerName[i]=CUN[i];
    }
    for(i=0;i<11;i++)
        sudokugame.LastModificationDate[i]=datefinder()[i];
    printf("%s\n",sudokugame.LastModificationDate);
    for(i=0;i<6;i++)
        sudokugame.LastModificationTime[i]=timefinder()[i];
//    printf("%s\n",sudokugame.LastModificationTime);
    fwrite(&sudokugame,sizeof(SPD),1,sudokuptr);
    printf("The game is added\n");
    fclose(sudokuptr);
}
checker(int newvalue,SPD sudokugame,int x,int y)
{    
    int i    ;
    if(newvalue==0)
        return 1;
    if(newvalue<0 || newvalue>9)
        return 0;
    for(i=0;i<9;i++)
    {
        if(sudokugame.Game[y][i]==newvalue && i!=x)
            return 0;
        if(sudokugame.Game[i][x]==newvalue && i!=y)
            return 0;
    }
    return 1;

}
char* datefinder(){
    struct tm *TimeFinder = NULL ;
    int day;
    int month;
    int year;
    

    char date[10];


    time_t timeInSeconds ;                
    timeInSeconds = time(0) ;                
    TimeFinder= localtime( &timeInSeconds ) ;

    day= TimeFinder->tm_mday ;
    month= TimeFinder->tm_mon + 1 ;
    year= TimeFinder->tm_year + 1900 ;
    
    date[0]='0'+day/10;
    date[1]='0'+day-(day/10)*10;
    date[2]='/';
    date[3]='0'+month/10;
    date[4]='0'+month-(month/10)*10;
    date[5]='/';
    date[6]='0'+year/1000;
    date[7]='0'+(year%1000)/100;
    date[8]='0'+(year%100)/10;
    date[9]='0'+year%10;
    date[10]='\0';

    return date;
}

char* timefinder(){

    
    struct tm *TimeFinder = NULL ;
    int hour,minute;
    char HourMinute[5];

    time_t timeInSeconds ;                
    timeInSeconds = time(0) ;                
    TimeFinder= localtime( &timeInSeconds ) ;

    hour=TimeFinder->tm_hour;
    minute=TimeFinder->tm_min;
    HourMinute[0]='0'+hour/10;
    HourMinute[1]='0'+hour%10;
    HourMinute[2]=':';
    HourMinute[3]='0'+minute/10;
    HourMinute[4]='0'+minute%10;
    HourMinute[5]='\0';
    

    return HourMinute;
}
void sudokudisplayer(SPD sudokugame)
{
    int i,j,t;

    printf("\n");
    printf("\n");
    printf("\n");
    printf("                    I");                  
    for(i=0;i<9;i++)
        printf(" y%dI",i);
    printf("\n");
    printf("                  ");
    for(i=0;i<41;i++)
        printf("_");
    printf("\n");
    for(i=0;i<9;i++)
    {
        printf("                  ");
        printf("x%d I",i);
        for(j=0;j<9;j++)
        {
            printf(" %d I",sudokugame.Game[j][i]);
        }
        
        printf("\n");
        printf("                  ");
        for(t=0;t<41;t++)
            printf("_");
        printf("\n");
    }
}
void choice4(FILE* sudokuptr,SPD sudokugame,char* CUN)
{
    FILE* tempptr;
    int i,deletechoice,counter1=0,counter2=0,counter3=0;
    
    choice1(sudokuptr,sudokugame,CUN);

    sudokuptr=fopen("sudoku.dat","rb");
    tempptr=fopen("temp.dat","wb");

    printf("Enter the number of the file you want to delete");
    scanf("%d",&deletechoice);

    while(!feof(sudokuptr))
    {
        fread(&sudokugame,sizeof(SPD),1,sudokuptr);
        for(i=0;i<11;i++)
        {
            if(CUN[i]==sudokugame.PlayerName[i])
                counter3++;
        }    
        if(counter3==10)
            counter1++;
        if(counter1<deletechoice)
        {
            counter2++;
        }
        counter3=0;
    }
    printf("%d",counter2);
    rewind(sudokuptr);

    for(i=0;i<counter2;i++)
    {
        fread(&sudokugame,sizeof(SPD),1,sudokuptr);
        fwrite(&sudokugame,sizeof(SPD),1,tempptr);
    }
    fseek(sudokuptr,2*sizeof(SPD),SEEK_CUR);
    while(!feof(sudokuptr))
    {
        fread(&sudokugame,sizeof(SPD),1,sudokuptr);
        fwrite(&sudokugame,sizeof(SPD),1,tempptr);
    }
    fclose(sudokuptr);
    fclose(tempptr);

    sudokuptr=fopen("sudoku.dat","wb");
    tempptr=fopen("temp.dat","rb");

    while(!feof(tempptr))
    {
        fread(&sudokugame,sizeof(SPD),1,tempptr);
        fwrite(&sudokugame,sizeof(SPD),1,sudokuptr);
    }
    printf("The file is deleted");
}
float processcalculator(SPD sudokugame)
{
    float process=0;
    int i,j;

    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            if(sudokugame.Game[i][j]!=0)
                process++;
        }
    }
    process=(process/81)*100;

    return process;
}
int congragulations(SPD sudokugame)
{
    int i,j,process;
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            if(sudokugame.Game[i][j]!=0)
                process++;
        }
    }
    if(process==81)
        return 1;
    else
        return 0;
}
