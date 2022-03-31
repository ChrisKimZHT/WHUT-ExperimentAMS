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
    CardData[name].Print(is_admin);
}

void PrintSimilarCard(const string &name)
{
    int cnt = 0;
    string buf;
    for (auto card: CardData)
    {
        if (StrMatch(card.first, name))
        {
            cnt++;
            buf += card.second.Name() + '\n';
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
    for (auto card: CardData)
        card.second.PrintOneline();
    cout << setfill('-') << setw(110) << "" << setfill(' ') << endl;
    cout << "共计：" << CardData.size() << "张" << endl;
}

bool PasswordCheck(const string &name, const string &password)
{
    return CardData[name].CheckPassword(password);
}

int CheckLogin(const string &name, const string &password)
{
    // 0-成功 1-不存在/账号或密码错误 2-已登录 3-卡已注销 4-账单未结清
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
    // 0-成功 1-不存在/账号或密码错误 2-已登出 3-卡已注销
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