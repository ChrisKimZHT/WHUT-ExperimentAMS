#ifndef EXPERIMENTAMS_CLASS_H
#define EXPERIMENTAMS_CLASS_H

#include <string>
#include <ctime>
#include <utility>
#include <iostream>
#include <cstdio>
#include "tool.h"
#include <cmath>

using namespace std;

class Card // ���濨����
{
private:
    string CardName; // ����
    string CardPassword; // ����
    int CardStatus; // 0-δʹ�� 1-ʹ���� 2-��ע��
    time_t CreatTime; // ����ʱ��
    time_t DeleteTime; // ע��ʱ��
    time_t LastTime; // �ϴ�ʹ��ʱ��
    double TotalUse; // �����Ѷ�
    int UseCount; // ���Ѵ���
    double Balance; // ��ǰ���
    bool IsSettled; // �Ƿ����
public:
    /* ���캯�� */
    Card() { ; } // Ĭ�Ϲ��캯��
    Card(const string &name, const string &password, const double &money) // ���캯��
    {
        CardName = name;
        CardPassword = password;
        CardStatus = 0;
        CreatTime = time(nullptr);
        DeleteTime = 0;
        LastTime = CreatTime;
        TotalUse = 0;
        UseCount = 0;
        Balance = money;
        IsSettled = true;
    }

    /* ������Ա���� */
    string Name() { return CardName; } // ��ȡ����
    int Status() const { return CardStatus; } // ��ȡ��״̬
    double GetBalance() const { return Balance; } // ��ȡ���
    int SettleStat() const { return IsSettled; } // ��ȡ����״̬
    void Login() { CardStatus = 1; } // ���Ŀ�״̬Ϊ�ϻ�
    void Logoff() // ���Ŀ�״̬Ϊ�»�������ʹ��ʱ�䡢ʹ�ô�����
    {
        CardStatus = 0;
        LastTime = time(nullptr);
        UseCount++;
    }
    void Paid() { IsSettled = true; } // ���Ŀ�Ϊ�ѽ���
    void UnPaid() { IsSettled = false; } // ���Ŀ�Ϊδ����
    void Update(double value) { Balance += value; } // �������
    void Delete() // ע����
    {
        CardStatus = 2;
        DeleteTime = time(nullptr);
    }
    void SetPassword(const string &password) { CardPassword = password; } // ��������

    /* һ���Ա���� */
    void Print(); // ֱ�����Card����Ϣ
    void PrintBrief(); // ���н������Card����Ϣ
    bool CheckPassword(const string &); // �ȶ��˺����������ϻ���¼
    bool Charge(double); // �շ�

    /* ��������� */
    friend ostream &operator<<(ostream &, const Card &);
    friend istream &operator>>(istream &, Card &);
};

class Bill // �����˵�����
{
private:
    string CardName; // ����
    time_t StartTime; // �ϻ�ʱ��
    time_t EndTime; // �»�ʱ��
    double Fare; // ���
    int Type; // �Ʒ�����
    bool IsPaid; // �Ƿ����
public:
    /* ���캯�� */
    Bill() { ; } // Ĭ�Ϲ��캯��
    Bill(const string &name, const int &type) // ���캯��-�ϻ��˵�
    {
        CardName = name;
        StartTime = time(nullptr);
        EndTime = 0;
        IsPaid = false;
        Fare = 0;
        Type = type;
    }
    Bill(const string &name, const double &value) // ���캯��-�����˵�
    {
        CardName = name;
        StartTime = time(nullptr);
        EndTime = StartTime;
        IsPaid = true;
        Fare = value;
        Type = -1;
    }

    /* ������Ա���� */
    void SetEnd(time_t t) { EndTime = t; } // ���ý�������
    void SetPaid() { IsPaid = true; } // ���ý���
    void SetFare(double f) { Fare = f; } // ���÷���
    string GetName() { return CardName; } // ��ȡ����
    bool Paid() const { return IsPaid; } // ��ȡ�Ƿ����
    int GetType() const { return Type; } // ��ȡ����
    time_t GetStart() const { return StartTime; } // ��ȡ��ʼʱ��
    time_t GetEnd() const { return EndTime; } // ��ȡ����ʱ��
    double GetFare() const { return Fare; } // ��ȡ����

    /* һ���Ա���� */
    void Print(); // ���Bill����Ϣ

    /* ��������� */
    friend ostream &operator<<(ostream &, const Bill &);
    friend istream &operator>>(istream &, Bill &);
};

class Price // ����Ʒѵ���
{
private:
    double PricePerHalfHour;
    double PriceWholeNight;
    double PriceWholeDay;
    pair<int, int> NightRange;
public:
    /* ���캯�� */
    Price() // Ĭ�Ϲ��캯��
    {
        PricePerHalfHour = 2.0;
        PriceWholeNight = 27.0;
        PriceWholeDay = 48.0;
        NightRange.first = 22;
        NightRange.second = 7;
    }
    Price(double P_HalfHour, double P_Night, double P_Day, int NightStart, int NightEnd) // ���캯��
    {
        PricePerHalfHour = P_HalfHour;
        PriceWholeNight = P_Night;
        PriceWholeDay = P_Day;
        NightRange.first = NightStart;
        NightRange.second = NightEnd;
    }

    /* ������Ա���� */
    pair<int, int> GetNightRange() { return NightRange; } // ��ȡ��ҹ��Χ
    void Print() // ����۸�
    {
        cout << left << setw(15) << "��Сʱ�۸�: " << "��" << fixed << setprecision(2) << PricePerHalfHour << endl
             << left << setw(15) << "��ҹ�۸�: " << "��" << fixed << setprecision(2) << PriceWholeNight << endl
             << left << setw(15) << "����۸�: " << "��" << fixed << setprecision(2) << PriceWholeDay << endl
             << left << setw(15) << "��ҹʱ���: " << NightRange.first << '~' << NightRange.second << endl;
    }

    /* һ���Ա���� */
    double CalcFare(const time_t &, const time_t &, const int &) const; // ������� 0-��Сʱ�Ʒ� 1-��ҹ 2-����

    /* ��������� */
    friend ostream &operator<<(ostream &, const Price &);
    friend istream &operator>>(istream &, Price &);
};

struct YearMonthDay // �����սṹ��
{
    int Year, Month, Day;

    /* ���캯�� */
    YearMonthDay()
    {
        time_t t = time(nullptr);
        tm *t_tm = localtime(&t);
        Year = t_tm->tm_year + 1900;
        Month = t_tm->tm_mon + 1;
        Day = t_tm->tm_mday;
    }
    explicit YearMonthDay(time_t t)
    {
        tm *t_tm = localtime(&t);
        Year = t_tm->tm_year + 1900;
        Month = t_tm->tm_mon + 1;
        Day = t_tm->tm_mday;
    }
    YearMonthDay(int y, int m, int d)
    {
        Year = y;
        Month = m;
        Day = d;
    }

    /* ��������� */
    bool operator<(const YearMonthDay &t) const
    {
        if (Year != t.Year)
            return Year < t.Year;
        else if (Month != t.Month)
            return Month < t.Month;
        else if (Day != t.Day)
            return Day < t.Day;
        else
            return false;
    }
    bool operator<=(const YearMonthDay &t) const
    {
        if (Year != t.Year)
            return Year < t.Year;
        else if (Month != t.Month)
            return Month < t.Month;
        else
            return Day <= t.Day;
    }
    bool operator==(const YearMonthDay &t) const
    {
        if (Year == t.Year && Month == t.Month && Day == t.Day)
            return true;
        else
            return false;
    }
//    friend ostream &operator<<(ostream &, const YearMonthDay &);
};

class Stat // ����ͳ����Ϣ����
{
private:
    YearMonthDay Date; // ����
    int CreatCardCount; // ����������
    int DeleteCardCount; // ע��������
    int DepositCount; // ��ֵ����
    int RefundCount; // �˷Ѵ���
    int ConsumeCount; // ���Ѵ���
    double DepositAmount; // ��ֵ��
    double RefundAmount; // �˷���
    double ConsumeAmount; // ������
public:
    /* ���캯�� */
    Stat()
    {
        Date = {0, 0, 0};
        CreatCardCount = 0;
        DeleteCardCount = 0;
        DepositCount = 0;
        RefundCount = 0;
        ConsumeCount = 0;
        DepositAmount = 0.0;
        RefundAmount = 0.0;
        ConsumeAmount = 0.0;
    }
    Stat(const YearMonthDay &val)
    {
        Date = val;
        CreatCardCount = 0;
        DeleteCardCount = 0;
        DepositCount = 0;
        RefundCount = 0;
        ConsumeCount = 0;
        DepositAmount = 0.0;
        RefundAmount = 0.0;
        ConsumeAmount = 0.0;
    }

    /* ������Ա���� */
    YearMonthDay GetDate() { return Date; }
    void SetDate(const YearMonthDay &val) { Date = val; }
    void CreatCard(const double &val)
    {
        CreatCardCount++;
        Deposit(val);
    }
    void DeleteCard(const double &val)
    {
        DeleteCardCount++;
        Refund(val);
    }
    void Deposit(const double &val)
    {
        DepositCount++;
        DepositAmount += val;
    }
    void Refund(const double &val)
    {
        RefundCount++;
        RefundAmount += val;
    }
    void Consume(const double &val)
    {
        ConsumeCount++;
        ConsumeAmount += val;
    }
//    int cntCreatCard() { return CreatCardCount; }
//    int cntDeleteCard() { return DeleteCardCount; }
//    int cntDeposit() { return DepositCount; }
//    int cntRefund() { return RefundCount; }
//    int cntConsume() { return ConsumeCount; }
//    double valDeposit() { return DepositAmount; }
//    double valRefund() { return RefundAmount; }
//    double valConsume() { return ConsumeAmount; }

    /* һ���Ա���� */
    void Print(); // ���

    /* ��������� */
    friend ostream &operator<<(ostream &, const Stat &);
    friend istream &operator>>(istream &, Stat &);
    Stat operator+(const Stat &a)
    {
        Stat tmp;
        tmp.CreatCardCount = CreatCardCount + a.CreatCardCount;
        tmp.DeleteCardCount = DeleteCardCount + a.DeleteCardCount;
        tmp.DepositCount = DepositCount + a.DepositCount;
        tmp.RefundCount = RefundCount + a.RefundCount;
        tmp.ConsumeCount = ConsumeCount + a.ConsumeCount;
        tmp.DepositAmount = DepositAmount + a.DepositAmount;
        tmp.RefundAmount = RefundAmount + a.RefundAmount;
        tmp.ConsumeAmount = ConsumeAmount + a.ConsumeAmount;
        return tmp;
    }
};

#endif //EXPERIMENTAMS_CLASS_H