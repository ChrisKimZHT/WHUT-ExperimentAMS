#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <iomanip>
#include "bill_file.h"
#include "bill_service.h"

using namespace std;

map<string, vector<Bill>> BillData;
Price PriceData{}; /* NOLINT */

void CreatBill(const string &name, const int &type)
{
    BillData[name].push_back(Bill(name, type));
}

void CreatBill(const string &name, const double &value)
{
    BillData[name].push_back(Bill(name, value));
}

pair<double, time_t> GetIncompleteBill(const string &name)
{
    // 从尾到头遍历用户账单
    for (auto it = BillData[name].rbegin(); it != BillData[name].rend(); ++it)
    {
        // 如果发现未支付账单
        if (!it->Paid())
        {
            // 如果结束时间为0（即还没有填写结束时间）
            if (it->GetEnd() == 0)
            {
                it->SetEnd(time(nullptr));
                it->SetFare(PriceData.CalcFare(it->GetStart(), it->GetEnd(), it->GetType()));
            }
            return {it->GetFare(), it->GetEnd()};
        }
    }
    return {0, 0};
}

void CompleteBill(const string &name)
{
    for (auto it = BillData[name].rbegin(); it != BillData[name].rend(); ++it)
    {
        if (!it->Paid())
        {
            it->SetPaid();
        }
    }
}

pair<int, int> GetNightRange()
{
    return PriceData.GetNightRange();
}

void PrintBill(const string &name, int year, int month, int day)
{
    cout << left << setw(5) << ""
         << left << setw(12) << "类别"
         << left << setw(14) << "金额"
         << left << setw(25) << "上机时间"
         << left << setw(25) << "下机时间"
         << left << setw(8) << "备注"
         << endl;
    if (month == 0 && day == 0)
    {
        for (const auto &bill: BillData[name])
        {
            if (YearMonthDay(bill.GetEnd()).Year == year)
            {
                bill.Print();
            }
        }
    }
    else if (month != 0 && day == 0)
    {
        for (const auto &bill: BillData[name])
        {
            if (YearMonthDay(bill.GetEnd()).Year == year &&
                YearMonthDay(bill.GetEnd()).Month == month)
            {
                bill.Print();
            }
        }
    }
    else if (month != 0)
    {
        for (const auto &bill: BillData[name])
        {
            if (YearMonthDay(bill.GetEnd()).Year == year &&
                YearMonthDay(bill.GetEnd()).Month == month &&
                YearMonthDay(bill.GetEnd()).Day == day)
            {
                bill.Print();
            }
        }
    }
}

void PrintBill(const string &name, YearMonthDay start, YearMonthDay end)
{
    cout << left << setw(5) << ""
         << left << setw(12) << "类别"
         << left << setw(14) << "金额"
         << left << setw(25) << "上机时间"
         << left << setw(25) << "下机时间"
         << left << setw(8) << "备注"
         << endl;
    for (const auto &bill: BillData[name])
    {
        YearMonthDay date{bill.GetEnd()};
        if (start <= date && date <= end)
        {
            bill.Print();
        }
    }
}

int BillDataSave()
{
    return BillFileSave(BillData);
}

int BillDataLoad()
{
    return BillFileLoad(BillData);
}

void PriceDataSave()
{
    PriceFileSave(PriceData);
}

void PriceDataLoad()
{
    PriceFileLoad(PriceData);
}

Price GetPrice()
{
    return PriceData;
}

Price ChangePrice(double P_HalfHour, double P_Night, double P_Day, int NightStart, int NightEnd)
{
    PriceData = {P_HalfHour, P_Night, P_Day, NightStart, NightEnd};
    return PriceData;
}