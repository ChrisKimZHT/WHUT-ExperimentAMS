#include <fstream>
#include <map>
#include "stat_file.h"

using namespace std;

int StatFileSave(map<YearMonthDay, Stat> &StatData)
{
    int cnt = 0;
    ofstream StatDataFile;
    StatDataFile.open("./StatData.txt", ios::out);
    for (auto &stat: StatData)
    {
        StatDataFile << stat.second;
        cnt++;
    }
    StatDataFile.close();
    return cnt;
}

int StatFileLoad(map<YearMonthDay, Stat> &StatData)
{
    int cnt = 0;
    Stat temp;
    ifstream StatDataFile;
    StatDataFile.open("./StatData.txt", ios::in);
    StatData.clear();
    while (StatDataFile >> temp)
    {
        StatData[temp.GetDate()] = temp;
        cnt++;
    }
    StatDataFile.close();
    return cnt;
}