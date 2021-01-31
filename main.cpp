#include <iostream>
#include <fstream>
#include <cstdlib>
#include <graphics.h>
#include<time.h>

using namespace std;
struct pozitie
{
    int X, Y;
}
d[2500], dopt[2500];
int lopt=2500;

int L[8]= {-1,-1,0,1,1,1,0,-1};
int c[8]= {0,1,1,1,0,-1,-1,-1};
int a[50][50];
int n,Li,Ci,Lf,Cf,k,latura=50;
int ns;

void citire()
{
    ifstream f("labirint.in");
    f>>n;
    f>>Li>>Ci>>Lf>>Cf;
}



void incarca_imagine(int i, int j, int val);

void afisare2()
{
    int i, x, y;
    for(i=1; i<=k; i++)
    {
        cout<<"("<<d[i].X<<","<<d[i].Y<<") ";
        x=d[i].X;
        y=d[i].Y;
        incarca_imagine(x,y,11);///11 == soricel
        delay(300);
        incarca_imagine(x,y,7);///0 == culoare

    }
    incarca_imagine(Lf,Cf,3);///3 == cascaval
    cout<<endl;
}


void afiseaza_drumul_optim()
{
    int i, x, y;
    for(i=1; i<=lopt; i++)
    {
        cout<<"("<<dopt[i].X<<","<<dopt[i].Y<<") ";
        x=dopt[i].X;
        y=dopt[i].Y;
        incarca_imagine(x,y,11);///11 == soricel
        delay(300);
        incarca_imagine(x,y,7);///0 == culoare

    }

}

void incarca_imagine(int i, int j, int val)
{
    int x, y;
    x=(j-1)*latura;
    y=(i-1)*latura;
    char nf[20];///val=1
    itoa(val, nf,10);///nf="1"
    strcat(nf,".jpg");
    readimagefile(nf,x,y,x+latura, y+latura);
}

void  actualizeaza_drum_optim()
{
    lopt=k;
    for(int i=1; i<=k; i++)
        dopt[i]=d[i];
}


void sol(int x, int y)
{
    if(a[x][y]==0)
    {
        ///prelucrari
        a[x][y]=2;
        k++;
        d[k].X=x;
        d[k].Y=y;
        if(x==Lf && y==Cf)
        {
            //afisare2();
            ns++;
            if(k<lopt)
                actualizeaza_drum_optim();
        }
        else
        {
            sol(x-1, y);
            sol(x, y+1);
            sol(x+1, y);
            sol(x, y-1);

            sol(x-1,y-1);
            sol(x-1,y+1);
            sol(x+1,y+1);
            sol(x+1,y-1);


            /*sol(x-2, y-1);
            sol(x-2, y+1);
            sol(x-1, y+2);
            sol(x+1, y+2);
            sol(x+2,y+1);
            sol(x+2,y-1);
            sol(x+1,y-2);
            sol(x-1,y-2);*/


        }

        ///demarcare
        a[x][y]=0;
        k--;
    }
}


void bordare()
{
    for(int i=0; i<=n+1; i++)
        a[0][i]=a[n+1][i]=a[i][0]=a[i][n+1]=1;
}
int H, W;
void generare_fereastra_grafica()
{

    H=n*latura;
    W=n*latura;
    initwindow(H,W,"Cursa");

}


void generez_labirint()
{
    int i, j;
    for(i=1; i<=n; i++)
        for(j=1; j<=n; j++)
        {
            if(a[i][j]==0)
                incarca_imagine(i,j,7);
            else
                incarca_imagine(i,j,a[i][j]);
        }
    incarca_imagine(Li,Ci,11);///11 este un soricel
    incarca_imagine(Lf,Cf,3);
}


int main()
{
    citire();
    cout<<Li<<Ci<<Lf<<Cf<<endl;
    srand(time(NULL));

    for(int i=1; i<=n; i++)
    {
        int nrk=0;
        for(int j=1; j<=n; j++)
        {
            int random=rand()%2;
            a[i][j]=random;
            if(a[i][j]==1)
            {
                random=rand()%3;
                if(random==1)
                    a[i][j]=1;
                if(random==2)
                    a[i][j]=4;
                if(random==0)
                    a[i][j]=5;
            }
            if(a[i][j]==1 && j>2)
                if(a[i][j-1]==a[i][j-2] && a[i][j-1]==1)
                    a[i][j]=0;
            if(a[i][j]==1 && i>2)
                if(a[i-1][j]==a[i-2][j] && a[i-1][j]==1)
                    a[i][j]=0;




        }
    }
    a[Li][Ci]=0;
    a[Lf][Cf]=0;
    generare_fereastra_grafica();
    generez_labirint();
    bordare();
    sol(Li,Ci);
    char *a="92.jpg";
    {
        if(ns==0)
            readimagefile(a,0,0,H,W);
        cout<<endl<<"Nu sunt solutii"<<endl;
        delay(3000);

    }
    afiseaza_drumul_optim();
    cout<<"gata";
    delay(1000000);
return 0;
}
