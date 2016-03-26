#include<sstream>
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<cmath>
#include"fun.h"

using namespace std;
#define in :



//int Conveyor::GetTime(const std::vector<int>& machinelist)
//{
//    //cout<<endl;
//    //for(int& i:machinelist){--i;}
//    for(int& e in mac_Time_left)e=0;
//    //  return 0;
//    for( int i=0; i<maxstuff; ++i)
//    {
//        auto& ThisStuff=StuffTimeUse[i];
//        mac_Time_left[0]+=ThisStuff[machinelist[0]];
//        for( int j=1; j<maxmac; ++j)
//        {
//            if(mac_Time_left[j-1]<=mac_Time_left[j])
//                mac_Time_left[j]+=ThisStuff[machinelist[j]];
//            else
//                mac_Time_left[j]=mac_Time_left[j-1]+ThisStuff[machinelist[j]];
//        }
//    }
//    return mac_Time_left[maxmac-1];
//}
int Conveyor::GetTime(const std::vector<int>& joblist)
{
    CountTimeUse[0][0]=StuffTimeUse[joblist[0]][0];

    for(int i=1; i<maxmac; ++i)   CountTimeUse[0][i]=CountTimeUse[0][i-1]+StuffTimeUse[joblist[0]][i];
    for(int i=1; i<maxstuff; ++i) CountTimeUse[i][0]=CountTimeUse[i-1][0]+StuffTimeUse[joblist[i]][0];
    for( int j=1; j<maxmac; ++j)
        for( int i=1; i<maxstuff; ++i)
            CountTimeUse[i][j]=max(CountTimeUse[i-1][j],CountTimeUse[i][j-1])+StuffTimeUse[joblist[i]][j];
    return CountTimeUse[maxstuff-1][maxmac-1];
}

void Conveyor::LoadData(const char* fName)
{
    FILE*f=fopen(fName,"r");
    if(f==0)
        throw invalid_argument( (string)"No file "+fName+"!");

    stringstream s;
    const int maxbuffsize=5000;
    char buff[maxbuffsize];
    fgets(buff,maxbuffsize,f);
    s<<buff;
    s>> maxstuff>>maxmac>>Name;
    mac_Time_left.resize(maxmac);
    cout<<"maxstuff:"<<maxstuff<<" maxmac:"<<maxmac<<" "<<Name<<endl;
    StuffTimeUse.resize(maxstuff);
    CountTimeUse.resize(maxstuff);
    for(auto &mac in StuffTimeUse)mac.resize(maxmac);
    for(auto &mac in CountTimeUse)mac.resize(maxmac);
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
    vector<int>& neighbor=NowBoard;
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

const std::vector<int> ProduceBoard(int length)
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
const std::vector<int> StartBoard(int length)
{
    static std::vector<int> boa;
    boa.resize(length);
    for(int i=0; i<length; ++i)boa[i]=i;
    return boa;
}



bool Simulated_annealing::GetNext()
{
    if(NowTemperature<=StopTemperature)return false;
    ++count;

    int x=-1,y=-1;
    swap(NowBoard[x],NowBoard[y]);

    int neiScore= conveyor.GetTime(NowBoard);

    auto Tem=[&]()
    {
        return exp((double)(Score-neiScore)/NowTemperature)>((float)rand()/(float)RAND_MAX);
    };

    if(neiScore<Score||Tem())
        Score=neiScore;
    else
        swap(NowBoard[x],NowBoard[y]);

    Lower_the_temperature();
    return true;
}

bool Tabu::GetNext()
{
    vector<int>& neighbor=NowBoard;
    int min=Score,x=-1,y=-1,sco=0;
    std::pair<int,int> temp;
    for(int i=0,mi=NowBoard.size()-1; i<mi; ++i)
    {
        temp.first=i;
        for(int j=i+1,mj=NowBoard.size(); j<mj; ++j)
        {
            temp.second=j;
            if(tabumap.find(temp)==tabumap.end())
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
                swap(neighbor[i],neighbor[j]);
            }
        }
    }
    if(x==-1)return false;
    swap(NowBoard[x],NowBoard[y]);
    Score=min;
    temp.first=x;
    temp.second=y;
    if(tabulist.size()>=tabulength)
    {
        tabumap.erase(tabulist[0]);
        tabulist.pop_front();
    }
    tabumap.insert(temp);
    tabulist.push_back(temp);
    return true;
}

