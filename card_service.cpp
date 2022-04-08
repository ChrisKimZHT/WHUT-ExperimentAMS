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
        cout << "[!] 以下多个卡号对应该卡号片段，请输入完整卡号继续查询。" << endl;
        cout << buf;
    }
    else
    {
        cout << "[!] 未查询到该卡号。" << endl;
    }
}

void PrintAllCard()
{
    cout << left << setw(16) << "卡号"
         << left << setw(16) << "密码"
         << left << setw(18) << "余额"
         << left << setw(18) << "累计消费"
         << left << setw(8) << "次数"
         << left << setw(24) << "创建时间"
         << left << setw(20) << "备注"
         << endl;
    for (int i = 0; i < CardData.size(); i++)
        CardData[i].PrintOneline();
    cout << setfill('-') << setw(110) << "" << setfill(' ') << endl;
    cout << "共计：" << CardData.size() << "张" << endl;
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
    // 0-成功 1-不存在/账号或密码错误 2-已登录 3-卡已注销 4-账单未结清
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
    // 0-成功 1-不存在/账号或密码错误 2-已登出 3-卡已注销
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