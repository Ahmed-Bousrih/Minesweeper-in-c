#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

#define tol printf("\n");

void initial (int t[][10]);
void affichi(int t[][10]);
void wostello3ba(int t[][10]);
void n3abiw(int t[][10],int *n,int *c);
int e7seb(int t[][10],int i,int j);
void placi(int t[][10]);
void temp(time_t bdina);

/* So the approach used is integers instead of characters and it works like this:
	-the cell with no bomb contains a number between 0--8 and whe chosen and digged becomes 10-18
	-the bomb cell contains 9 and when digged immediate loss
	-the marked cell contains a number between 20--29 and can not be digged again
    the display will depend directly to cell value range and the cell value modulo 10
*/

int main()
{
    system("cmd.exe /c MODE 50,35");
    SetConsoleTitle("Rod balek tfarga3ha ");
    system("cmd.exe /c COLOR 1f");
    system("clear");
    int le3ba_l_kol[10][10];
    time_t bdina =time(NULL);
    initial(le3ba_l_kol);
    //lo3ba tebda menna
    temp(bdina);
    int nb,c;
    n3abiw(le3ba_l_kol,&nb,&c);
    tol tol
    placi(le3ba_l_kol);
    system("clear");
    temp(bdina);
    printf("\tFamma %d 9nabel\n\n",c);
    printf("\n\tBdat lo3ba:\n");
    int x,y,ans=0,a;
    next:;
    wostello3ba(le3ba_l_kol);
    do
    {
        printf("\n A5tar l blassa (row column):  ");
        scanf("%d %d",&x,&y);
    } while (x<1 || x>9 || y<1 || y>9);
    do
    {
        printf("Chnoua t7eb:\n 1-te7fer\n 2-tmarki\n 3-tna7i l marquage\n ==>");
        scanf("%d",&a);
    } while (a!=1 && a!=2 && a!=3);
    //itha kan 5tar ye7fer
    if (a==1)
    {
        if (le3ba_l_kol[x-1][y-1]!=9) //ma fihach 9onbla
        {
            system("clear");
            temp(bdina);
            printf("\tFamma %d 9nabel\n\n",c);
            if(le3ba_l_kol[x-1][y-1]<10) //bach yet2aked enhi mch ma7foura deja
            {
                ++ans; //bach ya3raf 9addach ta7far 7atta l tawwa
                le3ba_l_kol[x-1][y-1]+=10;
            }
            printf("\n\tSa7it\n\n\tMazalou %d blayes yelzem tal9ahom\n",81-c-ans);
            //nthabtou fih rbe7 ou non
            if (ans==81-c) 
            {
                system("clear");
                system("cmd.exe /c COLOR A0 ");
                temp(bdina);
                printf("\n\n\t   *** Hay mabrouk rbe7t :) ***\n\n");
                time_t wfina = time(NULL);
                printf("\t      93adt tal3ab %d seconda\n",wfina-bdina);
                affichi(le3ba_l_kol);
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
        else // kan eli 7ferha 9onbla ya5sar toul
        {
            system("clear");
            system("cmd.exe /c COLOR 4f ");
            temp(bdina);
            //printf("\tFamma %d 9nabel\n\n",c);
            printf("\n\n\t      *** OOPS 5sart :( ***\n\n");
            time_t wfina = time(NULL);
            printf("\t      93adt tal3ab %d seconda\n",wfina - bdina);
            affichi(le3ba_l_kol);
            tol tol
            system("cmd.exe /c pause");
            return 0;
        }
    }
    else if (a==2) //ki ya5tar marki
    {
        if (le3ba_l_kol[x-1][y-1]>=10) //itha l blassa haki 7ferha deja
        {
            system("clear");
            temp(bdina);
            printf("\tFamma %d 9nabel\n\n",c);
            printf("\n\tDeja 7fertha hathi rak\n\n\tMazalou %d blayes yelzem tal9ahom\n",81-c-ans);
            goto next;
        }
        le3ba_l_kol[x-1][y-1]+=20; //tmarki cell ki tzidha 20 
        system("clear");
        temp(bdina);
        printf("\tFamma %d 9nabel\n\n",c);
        printf("\n\tC bon tmarkat\n\n\tMazalou %d blayes yelzem tal9ahom\n",81-c-ans);
        goto next;
    }
    else //ki ya5tar yna7i l marquage
    {
        if (le3ba_l_kol[x-1][y-1]<20 && le3ba_l_kol[x-1][y-1]>=10)
        {//ythabet itha hia mch ma7foura 9bal w mch markia 9bal
            system("clear");
            temp(bdina);
            printf("\tFamma %d 9nabel\n\n",c);
            printf("\n\tDeja 7fertha hathi rak\n\n\tMazalou %d blayes yelzem tal9ahom\n",81-c-ans);
            goto next;
        }
        le3ba_l_kol[x-1][y-1]=le3ba_l_kol[x-1][y-1]%10;
        system("clear");
        temp(bdina);
        printf("\tFamma %d 9nabel\n\n",c);
        printf("\n\tTna7a l marquage\n\n\tMazalou %d blayes yelzem tal9ahom\n",81-c-ans);
        goto next;
    }
}

void initial (int t[][10])
{//n7ottou kol chay a 0 mel loul
    for(int i=0;i<10;++i)
    {
        for (int j=0;j<10;++j)
        {
            t[i][j]=0;
        }
    }
}

void affichi(int t[][10])
{//affichage le5rani 
    printf("\n\n");
    printf("\t   | 1  2  3  4  5  6  7  8  9 \n");//tarki7 l cadre
    printf("\t___|___________________________\n");
    for(int i=0;i<9;i++)
    {
        printf("\t %d | ",i+1);
        for(int j=0;j<9;j++)
        {
            if (t[i][j]%10==9) 
            {
                printf("*  ");//ywarri * ki tebda grenade
            }
            else if (t[i][j]>=10) 
            {
                printf("%d  ",t[i][j]%10);//les cases ela tbadlou ysawarhom normal
            }
            else 
            {
                printf("%d  ",t[i][j]);//taswir les cases l normal
            }
        }
        tol
    }
}

void wostello3ba(int t[][10])
{//affichage mta3 l grid fi wost lo3ba
    printf("\n\n");
    printf("\t   | 1  2  3  4  5  6  7  8  9 \n");
    printf("\t___|___________________________\n");
    for(int i=0;i<9;i++)
    {
        printf("\t %d | ",i+1);
        for(int j=0;j<9;j++)
        {
            if (t[i][j]>=20) //ki tebda markia tetsawer &
            {
                printf ("&  ");
            }
            else if (t[i][j]>=10) //ki teta7far 3adi juste nwarriw noumrou
            {
                printf("%d  ",t[i][j]%10);
            }
            else 
            {
                printf(".  ");//ki yebda 7ad ma massha
            }
        }
        tol
    }
}

void n3abiw(int t[][10],int *n,int *c) //*c bach nesta7fthou b copie men nombre l 9nabel
{//kifach n3abiw l grid mta3na
    int choice;
    srand(time(NULL));
    printf ("\tLevel 1: 10 9nabel\n\tLevel 2: 20 9onbla\n\tLevel 3: 30 9onbla\n\ttest  4: 80 9onbla (juste e7fer 1-1)\n");
    do
    {
        printf ("\tChnoua level mta3ek?: ");
        scanf("%d",&choice);
    }while (choice!=1 && choice!=2 && choice !=3 && choice!=4);
    switch (choice)
    {
        case 1: *n=10;  break;
        case 2: *n=20;  break;
        case 3: *n=30;  break;
        case 4: *n=80;  break;
    }
    int i,j;    *c=*n;//ncheddou l copie f c w najmou nesta3mlou l *n
    printf("\tFamma %d 9nabel\n",*n);
    while (*n)
    {
        if (choice==4) //test level n7ottou 9nabel fi kol blassa kan fi 0-0 ela hia 1-1 fil UI
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
        {//juste n7ottou fihom random bel position 7atta lin toufa l n ela hia 9addach men 9onbla total
            i=rand()%9;
            j=rand()%9;
            if (t[i][j]!=9) //bach ma yjiwech 2 fou9 b3athhom
            {
                t[i][j]=9;
                (*n)--;
            }
        }
    }
}

int e7seb(int t[][10],int i,int j)
{//ne7sbou l grenades eli dayrin b cell mta3na
    int x=0;
    if (i==0)//itha kan hia f awel ligne
    {
        if (j==0) //itha kan fil comonne 1
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
        if (j==0)//itha kan hia f awel ligne
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

void placi(int t[][10])
{//neplaciw nwamer eli ne7sbouhom fi kol cell
    for (int i=0;i<9;++i)
    {
        for (int j=0;j<9;++j)
        {
            if (t[i][j]!=9) //appart l 9nabel 5aterhom deja 9nabel
            {
                t[i][j]=e7seb(t,i,j);
            }
        }
    }
}

void temp(time_t bdina)
{//template mta3 affichage 
    tol
    time_t wfina = time(NULL);
    printf("\t ________________________________\n");
    printf("\t|                                |\n");
    printf("\t|      Rod balek tfarga3ha       |\n");
    printf("\t|           by Sting             |\n");
    printf("\t|      t3adaw %3d seconda        |\n",wfina - bdina);
    printf("\t|________________________________|\n\n");
}