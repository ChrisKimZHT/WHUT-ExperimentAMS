#include <iostream>
#include <map>
#include <iomanip>
#include "stat_service.h"
#include "stat_file.h"

using namespace std;

map<YearMonthDay, Stat> StatData;

int StatDataSave()
{
    return StatFileSave(StatData);
}

int StatDataLoad()
{
    return StatFileLoad(StatData);
}

void StatUpdate(int type, double val, time_t t)
{
    // 0-创卡 1-注销 2-储值 3-退费 4-消费
    YearMonthDay Date{t};
    if (StatData[Date].GetDate() == YearMonthDay(0, 0, 0))
        StatData[Date].SetDate(Date);
    if (type == 0)
        StatData[Date].CreatCard(val);
    else if (type == 1)
        StatData[Date].DeleteCard(val);
    else if (type == 2)
        StatData[Date].Deposit(val);
    else if (type == 3)
        StatData[Date].Refund(val);
    else if (type == 4)
        StatData[Date].Consume(val);
}

void PrintStat(int year, int month, int day)
{
    cout << setw(110) << setfill('=') << "" << setfill(' ') << endl;
    cout << left << setw(15) << "日期"
         << left << setw(12) << "消费数"
         << left << setw(12) << "消费额"
         << left << setw(12) << "新卡数"
         << left << setw(12) << "充值数"
         << left << setw(12) << "充值额"
         << left << setw(12) << "退卡数"
         << left << setw(12) << "退费数"
         << left << setw(12) << "退费额"
         << endl;
    Stat sum;
    if (month == 0 && day == 0)
    {
        for (auto stat: StatData)
        {
            if (stat.second.GetDate().Year == year)
            {
                sum = sum + stat.second;
                stat.second.Print();
            }
        }
    }
    else if (month != 0 && day == 0)
    {
        for (auto stat: StatData)
        {
            if (stat.second.GetDate().Year == year &&
                stat.second.GetDate().Month == month)
            {
                sum = sum + stat.second;
                stat.second.Print();
            }
        }
    }
    else if (month != 0)
    {
        for (auto stat: StatData)
        {
            if (stat.second.GetDate().Year == year &&
                stat.second.GetDate().Month == month &&
                stat.second.GetDate().Day == day)
            {
                sum = sum + stat.second;
                stat.second.Print();
            }
        }
    }
    cout << setw(110) << setfill('-') << "" << setfill(' ') << endl;
    sum.Print();
}

void PrintStat(const YearMonthDay &start, const YearMonthDay &end)
{
    cout << setw(110) << setfill('=') << "" << setfill(' ') << endl;
    cout << left << setw(15) << "日期"
         << left << setw(12) << "消费数"
         << left << setw(12) << "消费额"
         << left << setw(12) << "新卡数"
         << left << setw(12) << "充值数"
         << left << setw(12) << "充值额"
         << left << setw(12) << "退卡数"
         << left << setw(12) << "退费数"
         << left << setw(12) << "退费额"
         << endl;
    Stat sum;
    for (auto stat: StatData)
    {
        YearMonthDay date = stat.second.GetDate();
        if (start <= date && date <= end)
        {
            sum = sum + stat.second;
            stat.second.Print();
        }
    }
    cout << setw(110) << setfill('-') << "" << setfill(' ') << endl;
    sum.Print();
}