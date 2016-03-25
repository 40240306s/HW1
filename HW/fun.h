#ifndef FUN__
#define FUN__
#include<vector>
#include<string>
#include <stdexcept>



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
    std::string Name;
public:
    const std::string& GetName()const
    {
        return Name;
    }
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
    virtual void Ini(const std::vector<int>& b)
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
    Iterative_Improvement(Conveyor& c):Serch(c)
    {
        Name="Iterative_Improvement";
    }
    bool GetNext();
    ~Iterative_Improvement() {};
};

class Simulated_annealing:public Serch
{
    double NowTemperature,IniTemperature=100,StopTemperature=0.1,alpha=0.9;
    void Lower_the_temperature()
    {
        NowTemperature*=alpha;
    }

public:
    Simulated_annealing(Conveyor& c):Serch(c)
    {
        Name="Simulated_annealing";
    }
    virtual void Ini(const std::vector<int>& b)
    {
        Serch::Ini(b);
        NowTemperature=IniTemperature;
    }
    bool GetNext();
    ~Simulated_annealing() {};
};
#include<deque>
#include<set>
class Tabu:public Serch
{
    std::deque<std::pair<int,int>> tabulist;
    std::set<std::pair<int,int>> tabumap;
    const size_t tabulength=8;
public:
    Tabu(Conveyor& c):Serch(c)
    {
        Name="   T   a   b   u   ";
    }
    virtual void Ini(const std::vector<int>& b)
    {
        Serch::Ini(b);
        tabulist.clear();
        tabumap.clear();
    }
    bool GetNext();
    ~Tabu() {};
};

void _Show(const std::vector<int>& b);


const std::vector<int>& ProduceBoard(int length);



#endif // FUN__
