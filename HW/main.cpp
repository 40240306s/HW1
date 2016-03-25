#include<iostream>
#include"fun.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

using namespace std;
int main()
{

    FILE *f=freopen("HW1RESULT.txt","w",stdout);
    if(!f)return -1;
    try
    {
        srand(time(0));
        const long long int MaxSpan(100000);
        int StuffNum[3]= {20,50,100},MacNum[3]= {5,10,20};
        char fbuff[100];
        Conveyor c;
        Serch* _serch[3]= {new Simulated_annealing(c),new Iterative_Improvement(c),new Tabu(c)};

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
            long long int total=0,min=0xfffffff,max=0,time=0;
            for(auto serch :_serch)
            {
                serch->ClearCount();
                serch->SetMaxSpan(MaxSpan);
                while(serch->Continuous())
                {
                    ++time;
                    serch->Ini(ProduceBoard(c.MaxMac()));
                    //serch->Show();
                    while(true)if(serch->GetNext()==false)break;
                    total+=serch->GetScore();
                    if(min>serch->GetScore())min=serch->GetScore();
                    if(max<serch->GetScore())max=serch->GetScore();
                    //serch->Show();
                }
                cout<<serch->GetName()<<"\tmax "<<max<<"  min "<<min<<" time "<<time<<" mean "<<(double)total/time<<endl;
            }
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

