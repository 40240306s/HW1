#include<sstream>
#include<stdio.h>
#include<iostream>
#include<stdlib.h>

#include"fun.h"

using namespace std;
#define in :



int Conveyor::GetTime(const std::vector<int>& machinelist)
{
    //cout<<endl;
    //for(int& i:machinelist){--i;}
    for(int& e in mac_Time_left)e=0;
    //  return 0;
    for( int i=0; i<maxstuff; ++i)
    {
        auto& ThisStuff=StuffTimeUse[i];
        mac_Time_left[0]+=ThisStuff[machinelist[0]];
        for( int j=1; j<maxmac; ++j)
        {
            if(mac_Time_left[j-1]<=mac_Time_left[j])
                mac_Time_left[j]+=ThisStuff[machinelist[j]];
            else
                mac_Time_left[j]=mac_Time_left[j-1]+ThisStuff[machinelist[j]];
        }
    }
    return mac_Time_left[maxmac-1];
}


void Conveyor::LoadData(const char* fName)
{
    FILE*f=fopen(fName,"r");
    if(f==0)
    {
        cout<<"No File\n";
        throw new exception();
    }
    stringstream s;
    const int maxbuffsize=5000;
    char buff[maxbuffsize];
    fgets(buff,maxbuffsize,f);
    s<<buff;
    s>> maxstuff>>maxmac>>Name;
    mac_Time_left.resize(maxmac);
    cout<<"maxstuff:"<<maxstuff<<" maxmac:"<<maxmac<<" "<<Name<<endl;
    StuffTimeUse.resize(maxstuff);
    for(auto &mac in StuffTimeUse)mac.resize(maxmac);
    for(int i=0; i<maxmac; ++i)
    {
        s.str("");
        s.clear();
        fgets(buff,maxbuffsize,f);
        s<<buff;
        for(int j=0; j<maxstuff; ++j)
            s>>StuffTimeUse[j][i];
    }
//    for(auto i in StuffTimeUse)
//    {
//        cout<<endl;
//        for(int j in i)cout<<j<<" ";
//    }
//    cout<<endl;
fclose(f);
}




bool Iterative_Improvement::GetNext()
{
    // if(Continuous()==false)return false;
    vector<int> neighbor=NowBoard;
    //cout<<"====in"<<endl;
    //Show(NowBoard);
    //cout<<Score<<endl;
    //cout<<"===="<<endl;
    int min=Score,x=-1,y=-1,sco=0;
    for(int i=0,mi=NowBoard.size()-1; i<mi; ++i)
        for(int j=i+1,mj=NowBoard.size(); j<mj; ++j)
        {
            ++count;
            swap(neighbor[i],neighbor[j]);
            sco=conveyor.GetTime(neighbor);
            if(sco<min)
            {
                min=sco;
                x=i;
                y=j;
            }
            //Show(neighbor);
            //cout<<sco<<endl;
            swap(neighbor[i],neighbor[j]);
        }



    if(x==-1)return false;
    swap(NowBoard[x],NowBoard[y]);
    Score=min;



    return true;
}



void _Show(const std::vector<int>& b)
{
    for(int i in b)cout<< i<<' ';
}
void Serch::Show()
{
    cout<<"=="<<Score<<"==Use:"<<count<<'/'<<MaxSpan<<endl;
    _Show(NowBoard);
    cout<<endl<<"========"<<endl;

}

const std::vector<int>& ProduceBoard(int length)
{
   static std::vector<int> boa,num;
    num.resize(length);
    boa.resize(length);
    for(int i=0; i<length; ++i)num[i]=i;
    int ind=0;
    for(int i=0; i<length; ++i)
    {
        boa[i]=num[(ind=(rand()%num.size()))];
        num.erase(num.begin()+ind);
    }


    return boa;
}






