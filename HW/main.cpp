#include<iostream>
#include"fun.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <algorithm>
using namespace std;
int main()
{

    FILE *f=freopen("HW1RESULT.txt","w",stdout);
    if(!f)return -1;
    try
    {
        srand(time(0));
        const long long int MaxSpan(5000000);
        int StuffNum[3]= {20,50,100},MacNum[3]= {5,10,20};
        char fbuff[100];
        Conveyor c;
        Serch* _serch[3]= {new Iterative_Improvement(c),new Simulated_annealing(c),new Tabu(c)};

#ifdef SA
        Serch* serch=new Simulated_annealing(c);
#elif II
        Serch* serch=new Iterative_Improvement(c);
#elif TA

#endif // TA
        for(int i=0; i<9; ++i)
        {
            sprintf(fbuff,"tai%d_%d_1.txt",StuffNum[i/3],MacNum[i%3]);
            c.LoadData(fbuff);
            const int maxtesttime=20;
            long long int total=0,gtotal=0,min=0xfffffff,max=0,time=0,gtime=0,gmin=min,gmax=max;
            auto GetSecond=[](time_t t)
            {
                return (double)(clock()-t)/1000;
            };
            auto PutBar=[](int t)
            {
               for(int i=0; i<t; ++i)cout<<'=';
            cout<<endl;
            };

            for(auto serch :_serch)
            {
                cout<<serch->GetName()<<endl;
                time_t timebig=clock();
                for(int testtime=0; testtime<maxtesttime; ++testtime)
                {
                    time_t timesmall=clock();
                    serch->ClearCount();
                    serch->SetMaxSpan(MaxSpan);
                    time=0;
                    total=0;
                    while(serch->Continuous())
                    {
                        ++time;
                        serch->Ini(ProduceBoard(c.MaxStuff()));
                        while(true)if(serch->GetNext()==false)break;
                        total+=serch->GetScore();
                        if(min>serch->GetScore())min=serch->GetScore();
                        if(max<serch->GetScore())max=serch->GetScore();
                    }
                    gtotal+=total;
                    gtime+=time;
                    if(gmin>min)gmin=min;
                    if(gmax<max)gmax=max;

                    cout<<"No."<<testtime+1<<"\tmax "<<max<<"\tmin "<<min<<"\tmean "<<(double)total/time<<"\t次數 "<<time<<"時間"<<GetSecond(timesmall)<<endl;
                }
                cout<<"整理:max "<<gmax<<"\tmin "<<gmin<<"\tmean "<<(double)gtotal/gtime<<"時間經過:"<<GetSecond(timebig)<<endl;

                 PutBar(40);
            }
            PutBar(80);
        }
        for(auto serch :_serch)
            delete serch;
    }
    catch(invalid_argument& e)
    {
        cout<<e.what();
    }

    fclose(f);
}

