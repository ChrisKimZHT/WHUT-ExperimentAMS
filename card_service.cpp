#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include "card_service.h"
#include "card_file.h"
#include "tool.h"

using namespace std;

map<string, Card> CardData;

void SaveCard(const string &name, const Card &NewCard)
{
    CardData[name] = NewCard;
}

bool IsExist(const string &name)
{
    if (CardData.find(name) != CardData.end())
        return true;
    else
        return false;
}

void PrintCard(const string &name, bool is_admin)
{
    if (is_admin)
        CardData[name].PrintDetailed();
    else
        CardData[name].Print();
}

void FuzzyPrintCard(const string &name)
{
    cout << left << setw(21) << "����"
         << left << setw(22) << "���"
         << left << setw(13) << "��ע"
         << endl;
    int cnt = 0;
    for (auto card: CardData)
    {
        if (StrMatch(card.first, name))
        {
            cnt++;
            card.second.PrintBrief();
        }
    }
    if (cnt)
        cout << "[!] �ÿ���Ƭ�ζ�Ӧ������ţ���Ҫ��ѯϸ�ڣ��������������š�" << endl;
    else
        cout << "[!] δ��ѯ���ÿ��š�" << endl;
}

bool PasswordCheck(const string &name, const string &password)
{
    return CardData[name].CheckPassword(password);
}

int CheckLogin(const string &name, const string &password)
{
    // 0-�ɹ� 1-������/�˺Ż�������� 2-�ѵ�¼ 3-����ע�� 4-�˵�δ����
    if (!IsExist(name) || !CardData[name].CheckPassword(password))
        return 1;
    else
    {
        if (CardData[name].Status() == 1)
            return 2;
        else if (CardData[name].Status() == 2)
            return 3;
        else if (CardData[name].SettleStat() == false)
            return 4;
        else
        {
            CardData[name].Login();
            CardData[name].UnPaid();
            return 0;
        }
    }
}

int CheckLogoff(const string &name, const string &password)
{
    // 0-�ɹ� 1-������/�˺Ż�������� 2-�ѵǳ� 3-����ע��
    if (!IsExist(name) || !CardData[name].CheckPassword(password))
        return 1;
    else
    {
        if (CardData[name].Status() == 0)
            return 2;
        else if (CardData[name].Status() == 2)
            return 3;
        else
        {
            CardData[name].Logoff();
            return 0;
        }
    }
}

bool Charge(const string &name, const double &money)
{
    return CardData[name].Charge(money);
}

void SetPaid(const string &name)
{
    CardData[name].Paid();
}

double GetBalance(const string &name)
{
    return CardData[name].GetBalance();
}

void UpdateBalance(const string &name, const double &val)
{
    CardData[name].Update(val);
}

bool IsSettled(const string &name)
{
    return CardData[name].SettleStat();
}

void DeleteCard(const string &name)
{
    CardData[name].Delete();
}

int GetStatus(const string &name)
{
    return CardData[name].Status();
}

int CardDataSave()
{
    return CardFileSave(CardData);
}

int CardDataLoad()
{
    return CardFileLoad(CardData);
}

void SetPassword(const string &name, const string &password)
{
    CardData[name].SetPassword(password);
}