
#include<iostream>
#include"fun.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

using namespace std;
int main()
{
    srand(time(0));

    int StuffNum[3]= {20,50,100},MacNum[3]= {5,10,20};
    char fbuff[100];
    Conveyor c;
    Serch* serch=new Simulated_annealing(c);
    //new Iterative_Improvement(c);

    for(int i=0; i<9; ++i)
    {
        sprintf(fbuff,"tai%d_%d_1.txt",StuffNum[i/3],MacNum[i%3]);
        c.LoadData(fbuff);

        long long int total=0,min=0xfffffff,max=0,time=0;



        serch->ClearCount();
        serch->SetMaxSpan(1000000);
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



        cout<<"max "<<max<<"  min "<<min<<" time "<<time<<" mean "<<(double)total/time<<endl;



    }
    delete serch;
}
