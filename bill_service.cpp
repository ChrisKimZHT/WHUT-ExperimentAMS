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

void PrintBill(const string &name)
{
    cout << left << setw(5) << ""
         << left << setw(12) << "���"
         << left << setw(14) << "���"
         << left << setw(25) << "�ϻ�ʱ��"
         << left << setw(25) << "�»�ʱ��"
         << left << setw(8) << "��ע"
         << endl;
    for (const auto& bill: BillData[name])
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

Price GetPrice()
{
    return PriceData;
}

Price ChangePrice(double P_HalfHour, double P_Night, double P_Day, int NightStart, int NightEnd)
{
    PriceData = {P_HalfHour, P_Night, P_Day, NightStart, NightEnd};
    return PriceData;
}