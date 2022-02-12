#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#define tol printf("\n");

void initialise (int t[][10]);
void ShowGrid(int t[][10]);
void ShowInsideGame(int t[][10]);
void FillGrid(int t[][10],int *n,int *c);
int Count(int t[][10],int i,int j);
void Place(int t[][10]);
void Display(time_t bdina);

/* So the approach used is integers instead of characters and it works like this:
	-the cell with no bomb contains a number between 0--8 and whe chosen and digged becomes 10-18
	-the bomb cell contains 9 and when digged immediate loss
	-the marked cell contains a number between 20--29 and can not be digged again

	the display will depend directly to cell value range and the cell value modulo 10
*/

int main()
{
    system("cmd.exe /c MODE 50,35");
    SetConsoleTitle("Don't explode the map ");
    system("cmd.exe /c COLOR 1f");
    system("clear");
    int le3ba_l_kol[10][10]; 
    time_t bdina =time(NULL);
    initialise(le3ba_l_kol);
	//the game starts here
    Display(bdina);
    int nb,c;
    FillGrid(le3ba_l_kol,&nb,&c);
    tol tol
    Place(le3ba_l_kol);
    system("clear");
    Display(bdina);
    printf("\tThere are %d grenades\n\n",c);
    printf("\n\tGame Started:\n");
    int x,y,ans=0,a;
    next:;
    ShowInsideGame(le3ba_l_kol);
    do
    {
        printf("\n Choose the cell (row column):  ");
        scanf("%d %d",&x,&y);
    } while (x<1 || x>9 || y<1 || y>9);
    do
    {
        printf("Choose the move:\n 1-Dig\n 2-Mark\n 3-Remove marking\n ==>");
        scanf("%d",&a);
    } while (a!=1 && a!=2 && a!=3);
	//if the choice is to dig the cell
    if (a==1)
    {
        if (le3ba_l_kol[x-1][y-1]!=9) //no grenade
        {
            system("clear");
            Display(bdina);
            printf("\tThere are %d grenades\n\n",c);
            if(le3ba_l_kol[x-1][y-1]<10) //to check that it's not digged already
            {
                ++ans;//to count how many digged cells
                le3ba_l_kol[x-1][y-1]+=10;
            }
            printf("\n\tGood move\n\n\tStill %d cells to find\n",81-c-ans);
            //Check if it is a win
            if (ans==81-c) 
            {
                system("clear");
                system("cmd.exe /c COLOR A0 ");
                Display(bdina);
                printf("\n\n\t   *** Congratulations you won :) ***\n\n");
                time_t wfina = time(NULL);
                printf("\t      You played for %3d seconds\n",wfina-bdina);
                ShowGrid(le3ba_l_kol);
                tol tol
                system("cmd.exe /c pause");
                return 0;
            }
            else
            {
				//if they still no win we get back to start with keeping
				//the modification we made in that cell
                goto next;
            }
        }
        else //if the cell digged is a grenade=> loss
        {
            system("clear");
            system("cmd.exe /c COLOR 4f ");
            Display(bdina);
            //printf("\tThere are %d grenades\n\n",c);
            printf("\n\n\t      *** OOPS you lost :( ***\n\n");
            time_t wfina = time(NULL);
            printf("\t      You played for %3d seconds\n",wfina - bdina);
            ShowGrid(le3ba_l_kol);
            tol tol
            system("cmd.exe /c pause");
            return 0;
        }
    }
    else if (a==2) //the choice is mark the cell
    {
        if (le3ba_l_kol[x-1][y-1]>=10) //if the cell is digged
        {
            system("clear");
            Display(bdina);
            printf("\tThere are %d grenades\n\n",c);
            printf("\n\tYou already digged that cell\n\n\tStill %d cells to find\n",81-c-ans);
            goto next;
        }
        le3ba_l_kol[x-1][y-1]+=20; //marking by adding 20 to the value
        system("clear");
        Display(bdina);
        printf("\tThere are %d grenades\n\n",c);
        printf("\n\tCell marked\n\n\tStill %d cells to find\n",81-c-ans);
        goto next;
    }
    else //the choice is remove marking
    {
        if (le3ba_l_kol[x-1][y-1]<20 && le3ba_l_kol[x-1][y-1]>=10)
        {//cheks if it is already digged while is not marked before
            system("clear");
            Display(bdina);
            printf("\tThere are %d grenades\n\n",c);
            printf("\n\tYou already digged that cell\n\n\tStill %d cells to find\n",81-c-ans);
            goto next;
        }
        le3ba_l_kol[x-1][y-1]=le3ba_l_kol[x-1][y-1]%10;
        system("clear");
        Display(bdina);
        printf("\tThere are %d grenades\n\n",c);
        printf("\n\tMarking removed\n\n\tStill %d cells to find\n",81-c-ans);
        goto next;
    }
}

void initialise (int t[][10])
{//initialize everything to 0
    for(int i=0;i<10;++i)
    {
        for (int j=0;j<10;++j)
        {
            t[i][j]=0;
        }
    }
}

void ShowGrid(int t[][10])
{//final display of the grid with the result
    printf("\n\n");
    printf("\t   | 1  2  3  4  5  6  7  8  9 \n");//making borders
    printf("\t___|___________________________\n");
    for(int i=0;i<9;i++)
    {
        printf("\t %d | ",i+1);
        for(int j=0;j<9;j++)
        {
            if (t[i][j]%10==9) 
            {
                printf("*  ");//display * if its grenade
            }
            else if (t[i][j]>=10) 
            {
                printf("%d  ",t[i][j]%10); // display normally the cells that was modified 
            }
            else 
            {
                printf("%d  ",t[i][j]); // display normal cells
            }
        }
        tol
    }
}

void ShowInsideGame(int t[][10])
{//the display of the grid inside the game while changing cell by cell
    printf("\n\n");
    printf("\t   | 1  2  3  4  5  6  7  8  9 \n");
    printf("\t___|___________________________\n");
    for(int i=0;i<9;i++)
    {
        printf("\t %d | ",i+1);
        for(int j=0;j<9;j++)
        {
            if (t[i][j]>=20) //if the cell is marked we show &
            {
                printf ("&  ");
            }
            else if (t[i][j]>=10) //when digged safely we show the number
            {
                printf("%d  ",t[i][j]%10);//when its digged the number is between 10--18
            }
            else 
            {
                printf(".  "); //when the cell is not touched yet
            }
        }
        tol
    }
}

void FillGrid(int t[][10],int *n,int *c) //the *c is to keep a copy of the number of grenades back to the main func
{//filling the grid process
    int choice;
    srand(time(NULL));
    printf ("\tLevel 1: 10 grenades\n\tLevel 2: 20 grenades\n\tLevel 3: 30 grenades\n\ttest  4: 80 grenades (just dig 1 1)\n");
    do
    {
        printf ("\tChoose the level: ");
        scanf("%d",&choice);
    }while (choice!=1 && choice!=2 && choice !=3 && choice!=4);
    switch (choice)
    {
        case 1: *n=10;  break;
        case 2: *n=20;  break;
        case 3: *n=30;  break;
        case 4: *n=80;  break;
    }
    int i,j;   *c=*n;//we keep the copy in *c and we can use *n 
    printf("\tThere are %d grenades\n",*n);
    while (*n)
    {
        if (choice==4) // test level (if needed) we fill all grid with grenades except the 0 0 wich corresponds to 1 1 in UI
        {
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j< 9; j++)
                {
                    if (i+j) t[i][j]=9;
                }
            }
            break;
        }
        else
        {//we put grenades in random positions until their total number *n becomes 0
            i=rand()%9;
            j=rand()%9;
            if (t[i][j]!=9)// to avoid 2 grenades in the same spot 
            {
                t[i][j]=9;
                (*n)--;
            }
        }
    }
}

int Count(int t[][10],int i,int j)
{//count the number of grenades around the cell
    int x=0;
    if (i==0)// if the cell in the first row
    {
        if (j==0) // if it is in first colomn
        {
            for (int k = i; k <= i+1; ++k)
            {
                for (int z= j ; z <= j+1; ++z)
                {
                    if (t[k][z]==9) 
                    {
                        ++x;
                    }
                }
            }
        }
        else
        {
            for (int k = i; k <= i+1; ++k)
            {
                for (int z= j-1 ; z <= j+1; ++z)
                {
                    if (t[k][z]==9) 
                    {
                        ++x;
                    }
                }
            }
        }
    }
    else
    {
        if (j==0) // if it is in first colomn
        {
            for (int k = i-1; k <= i+1; ++k)
            {
                for (int z= j ; z <= j+1; ++z)
                {
                    if (t[k][z]==9) 
                    {
                        ++x;
                    }
                }
            }
        }
        else
        {
            for (int k = i-1; k <= i+1; ++k)
            {
                for (int z= j-1 ; z <= j+1; ++z)
                {
                    if (t[k][z]==9) 
                    {
                        ++x;
                    }
                }
            }
        }
    }
    return x;
}

void Place(int t[][10])
{//we put each number to its cell 
    for (int i=0;i<9;++i)
    {
        for (int j=0;j<9;++j)
        {
            if (t[i][j]!=9) //apart from grenades because they are grenades
            {
                t[i][j]=Count(t,i,j);
            }
        }
    }
}

void Display(time_t bdina)
{//a displaying template
    tol
    time_t wfina = time(NULL);
    printf("\t ________________________________\n");
    printf("\t|                                |\n");
    printf("\t|    Don't Explode the map       |\n");
    printf("\t|           by Sting             |\n");
    printf("\t|      t3adaw %3d seconda        |\n",wfina - bdina);
    printf("\t|________________________________|\n\n");
}