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
map<YearMonthDay, Stat> StatData;
Price PriceData{}; /* NOLINT */

void CreatBill(const string &name, const int &type)
{
    BillData[name].push_back(Bill(name, type));
}

void CreatBill(const string &name, const double &value)
{
    BillData[name].push_back(Bill(name, value));
}

double GetIncompleteBill(const string &name)
{
    // ��β��ͷ�����û��˵�
    for (auto it = BillData[name].rbegin(); it != BillData[name].rend(); ++it)
    {
        // �������δ֧���˵�
        if (!it->Paid())
        {
            // �������ʱ��Ϊ0������û����д����ʱ�䣩
            if (it->GetEnd() == 0)
            {
                it->SetEnd(time(nullptr));
                it->SetFare(PriceData.CalcFare(it->GetStart(), it->GetEnd(), it->GetType()));
            }
            return it->GetFare();
        }
    }
    return 0;
}

void CompleteBill(const string &name)
{
    for (auto it = BillData[name].rbegin(); it != BillData[name].rend(); ++it)
    {
        if (!it->Paid())
        {
            it->SetPaid();
            StatUpdate(4, it->GetFare(), it->GetEnd());
            StatDataSave();
        }
    }
}

pair<int, int> GetNightRange()
{
    return PriceData.GetNightRange();
}

void PrintBill(const string &name)
{
    cout << left << setw(5) << ""
         << left << setw(12) << "���"
         << left << setw(14) << "���"
         << left << setw(25) << "�ϻ�ʱ��"
         << left << setw(25) << "�»�ʱ��"
         << left << setw(8) << "��ע"
         << endl;
    for (auto bill: BillData[name])
        bill.Print();
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

int StatDataSave()
{
    return StatFileSave(StatData);
}

int StatDataLoad()
{
    return StatFileLoad(StatData);
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

void StatUpdate(int type, double val, time_t t)
{
    // 0-���� 1-ע�� 2-��ֵ 3-�˷� 4-����
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
    cout << left << setw(15) << "����"
         << left << setw(12) << "������"
         << left << setw(12) << "���Ѷ�"
         << left << setw(12) << "�¿���"
         << left << setw(12) << "��ֵ��"
         << left << setw(12) << "��ֵ��"
         << left << setw(12) << "�˿���"
         << left << setw(12) << "�˷���"
         << left << setw(12) << "�˷Ѷ�"
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
    cout << left << setw(15) << "����"
         << left << setw(12) << "������"
         << left << setw(12) << "���Ѷ�"
         << left << setw(12) << "�¿���"
         << left << setw(12) << "��ֵ��"
         << left << setw(12) << "��ֵ��"
         << left << setw(12) << "�˿���"
         << left << setw(12) << "�˷���"
         << left << setw(12) << "�˷Ѷ�"
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