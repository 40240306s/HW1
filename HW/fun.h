


#ifndef FUN__
#define FUN__
#include<vector>
#include<string>



class Conveyor
{
    std::vector<int> mac_Time_left;
    std::vector<std::vector<int>> StuffTimeUse;
    std::string Name;
    int maxmac=0,maxstuff=0;
public:
    Conveyor()=default;
    Conveyor(const char* fName)
    {
        LoadData(fName);
    }
    int GetTime(const std::vector<int>&);
    void LoadData(const char* fName);
    int MaxMac()const
    {
        return maxmac;
    }
};



class Serch
{
protected:
    long long int MaxSpan=10000;
    long long int count=0;
    int Score=0;
    std::vector<int> NowBoard;
    Conveyor& conveyor;
public:
    void SetMaxSpan(long long int i)
    {
        MaxSpan=i;
    }
    Serch(Conveyor& c):conveyor(c) {}
    virtual ~Serch() {}
    virtual bool GetNext()=0;
    const std::vector<int>& GetBoard()const
    {
        return NowBoard;
    }
    bool Continuous()
    {
        return count<=MaxSpan;
    }
    int GetScore()const
    {
        return Score;
    }
    void Ini(const std::vector<int>& b)
    {
        NowBoard=b;
        Score=conveyor.GetTime(NowBoard);
    }
    void ClearCount()
    {
        count=0;
    }
    void Show();
};

class Iterative_Improvement:public Serch
{
public:
    Iterative_Improvement(Conveyor& c):Serch(c) {}
    bool GetNext();
    ~Iterative_Improvement() {};
};

void _Show(const std::vector<int>& b);


const std::vector<int>& ProduceBoard(int length);


class Record
{
public:
//    Record()









};




#endif // FUN__
