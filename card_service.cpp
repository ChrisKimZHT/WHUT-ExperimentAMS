#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include "card_service.h"
#include "card_file.h"
#include "tool.h"

using namespace std;

linklist<Card> CardData;

void SaveCard(const string &name, const Card &NewCard)
{
    CardData.push_front(NewCard);
}

bool IsExist(const string &name)
{
    for (int i = 0; i < CardData.size(); i++)
    {
        if (CardData[i].Name() == name)
            return true;
    }
    return false;
}

void PrintCard(const string &name, bool is_admin)
{
    for (int i = 0; i < CardData.size(); i++)
    {
        if (CardData[i].Name() == name)
        {
            CardData[i].Print(is_admin);
            break;
        }
    }
}

void PrintSimilarCard(const string &name)
{
    int cnt = 0;
    string buf;
    for (int i = 0; i < CardData.size(); i++)
    {
        if (StrMatch(CardData[i].Name(), name))
        {
            cnt++;
            buf += CardData[i].Name() + '\n';
        }
    }
    if (cnt)
    {
        cout << "[!] ���¶�����Ŷ�Ӧ�ÿ���Ƭ�Σ��������������ż�����ѯ��" << endl;
        cout << buf;
    }
    else
    {
        cout << "[!] δ��ѯ���ÿ��š�" << endl;
    }
}

void PrintAllCard()
{
    cout << left << setw(16) << "����"
         << left << setw(16) << "����"
         << left << setw(18) << "���"
         << left << setw(18) << "�ۼ�����"
         << left << setw(8) << "����"
         << left << setw(24) << "����ʱ��"
         << left << setw(20) << "��ע"
         << endl;
    for (int i = 0; i < CardData.size(); i++)
        CardData[i].PrintOneline();
    cout << setfill('-') << setw(110) << "" << setfill(' ') << endl;
    cout << "���ƣ�" << CardData.size() << "��" << endl;
}

bool PasswordCheck(const string &name, const string &password)
{
    int i;
    for (i = 0; i < CardData.size(); i++)
    {
        if (CardData[i].Name() == name)
            break;
    }
    return CardData[i].CheckPassword(password);
}

int CheckLogin(const string &name, const string &password)
{
    int i;
    for (i = 0; i < CardData.size(); i++)
    {
        if (CardData[i].Name() == name)
            break;
    }
    // 0-�ɹ� 1-������/�˺Ż�������� 2-�ѵ�¼ 3-����ע�� 4-�˵�δ����
    if (!IsExist(name) || !CardData[i].CheckPassword(password))
        return 1;
    else
    {
        if (CardData[i].Status() == 1)
            return 2;
        else if (CardData[i].Status() == 2)
            return 3;
        else if (CardData[i].SettleStat() == false)
            return 4;
        else
        {
            CardData[i].Login();
            CardData[i].UnPaid();
            return 0;
        }
    }
}

int CheckLogoff(const string &name, const string &password)
{
    int i;
    for (i = 0; i < CardData.size(); i++)
    {
        if (CardData[i].Name() == name)
            break;
    }
    // 0-�ɹ� 1-������/�˺Ż�������� 2-�ѵǳ� 3-����ע��
    if (!IsExist(name) || !CardData[i].CheckPassword(password))
        return 1;
    else
    {
        if (CardData[i].Status() == 0)
            return 2;
        else if (CardData[i].Status() == 2)
            return 3;
        else
        {
            CardData[i].Logoff();
            return 0;
        }
    }
}

bool Charge(const string &name, const double &money)
{
    int i;
    for (i = 0; i < CardData.size(); i++)
    {
        if (CardData[i].Name() == name)
            break;
    }
    return CardData[i].Charge(money);
}

void SetPaid(const string &name)
{
    for (int i = 0; i < CardData.size(); i++)
    {
        if (CardData[i].Name() == name)
            return CardData[i].Paid();
    }
}

double GetBalance(const string &name)
{
    int i;
    for (i = 0; i < CardData.size(); i++)
    {
        if (CardData[i].Name() == name)
            break;
    }
    return CardData[i].GetBalance();
}

void UpdateBalance(const string &name, const double &val)
{
    for (int i = 0; i < CardData.size(); i++)
    {
        if (CardData[i].Name() == name)
            return CardData[i].Update(val);
    }
}

bool IsSettled(const string &name)
{
    int i;
    for (i = 0; i < CardData.size(); i++)
    {
        if (CardData[i].Name() == name)
            break;
    }
    return CardData[i].SettleStat();
}

void DeleteCard(const string &name)
{
    for (int i = 0; i < CardData.size(); i++)
    {
        if (CardData[i].Name() == name)
        {
            CardData[i].Delete();
            break;
        }
    }
}

int GetStatus(const string &name)
{
    int i;
    for (i = 0; i < CardData.size(); i++)
    {
        if (CardData[i].Name() == name)
            break;
    }
    return CardData[i].Status();
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
    for (int i = 0; i < CardData.size(); i++)
    {
        if (CardData[i].Name() == name)
        {
            CardData[i].SetPassword(password);
            break;
        }
    }
}