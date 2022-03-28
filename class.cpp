#include "class.h"

void Card::Print()
{
    string status[4] = {"未使用", "[使用中]", "[已注销]"};
    string settle[2] = {"[未结清]", "已结清"};
    cout << left << setw(12) << "卡号：" << CardName << endl
         << left << setw(12) << "状态：" << status[CardStatus] << ' ' << settle[IsSettled] << endl
         << left << setw(12) << "余额：" << "￥" << fixed << setprecision(2) << Balance << endl
         << left << setw(12) << "累计消费：" << "￥" << fixed << setprecision(2) << TotalUse << endl
         << left << setw(12) << "使用次数：" << UseCount << "次" << endl
         << left << setw(12) << "创建时间：" << Date2str(CreatTime) << endl
         << left << setw(12) << "上次使用：" << Date2str(LastTime) << endl;
    if (CardStatus == 2)
        cout << left << setw(12) << "注销时间：" << Date2str(DeleteTime) << endl;
}

void Card::PrintBrief()
{
    string status[4] = {" 未使用 ", "[使用中]", "[已注销]"};
    string settle[2] = {"[未结清]", " 已结清 "};
    cout << left << setw(20) << CardName
         << "￥"
         << left << setw(15) << fixed << setprecision(2) << Balance
         << left << setw(20) << status[CardStatus] + ' ' + settle[IsSettled]
         << endl;
}

bool Card::CheckPassword(const string &pwd)
{
    if (CardPassword == pwd)
        return true;
    else
        return false;
}

bool Card::Charge(double fare)
{
    if (Balance < fare)
        return false;
    Balance -= fare;
    return true;
}

ostream &operator<<(ostream &os, const Card &card)
{
    os << card.CardName << ' ' << card.CardPassword << ' ' << card.CardStatus << ' '
       << card.CreatTime << ' ' << card.DeleteTime << ' ' << card.LastTime << ' '
       << card.TotalUse << ' ' << card.UseCount << ' ' << card.Balance << ' ' << card.IsSettled << endl;
    return os;
}

istream &operator>>(istream &is, Card &card)
{
    is >> card.CardName >> card.CardPassword >> card.CardStatus
       >> card.CreatTime >> card.DeleteTime >> card.LastTime
       >> card.TotalUse >> card.UseCount >> card.Balance >> card.IsSettled;
    return is;
}

void Bill::Print()
{
    string dict_type[] = {"按量付费", "包夜", "包天"};
    if (Type != -1)
    {
        if (IsPaid)
        {
            cout << left << setw(5) << "[-]"
                 << left << setw(12) << dict_type[Type]
                 << "￥" << left << setw(12) << fixed << setprecision(2) << Fare
                 << left << setw(25) << Date2str(StartTime)
                 << left << setw(25) << Date2str(EndTime)
                 << endl;
        }
        else if (Fare == 0)
        {
            cout << left << setw(5) << "(?)"
                 << left << setw(12) << dict_type[Type]
                 << "￥" << left << setw(12) << "_____"
                 << left << setw(25) << Date2str(StartTime)
                 << left << setw(25) << "___________________"
                 << left << setw(8) << "[未下机]"
                 << endl;
        }
        else
        {
            cout << left << setw(5) << "(!)"
                 << left << setw(12) << dict_type[Type]
                 << "￥" << left << setw(12) << fixed << setprecision(2) << Fare
                 << left << setw(25) << Date2str(StartTime)
                 << left << setw(25) << Date2str(EndTime)
                 << left << setw(8) << "[未结清]"
                 << endl;
        }
    }
    else if (Fare > 0)
    {
        cout << left << setw(5) << "<+>"
             << left << setw(12) << "充值"
             << "￥" << left << setw(12) << fixed << setprecision(2) << Fare
             << left << setw(25) << Date2str(StartTime)
             << left << setw(25) << ""
             << endl;
    }
    else if (Fare <= 0)
    {
        cout << left << setw(5) << "[-]"
             << left << setw(12) << "退费"
             << "￥" << left << setw(12) << fixed << setprecision(2) << -Fare
             << left << setw(25) << Date2str(StartTime)
             << left << setw(25) << ""
             << endl;
    }
}

ostream &operator<<(ostream &os, const Bill &bill)
{
    os << bill.CardName << ' ' << bill.StartTime << ' ' << bill.EndTime << ' '
       << bill.Fare << ' ' << bill.Type << ' ' << bill.IsPaid << endl;
    return os;
}

istream &operator>>(istream &is, Bill &bill)
{
    is >> bill.CardName >> bill.StartTime >> bill.EndTime
       >> bill.Fare >> bill.Type >> bill.IsPaid;
    return is;
}

double Price::CalcFare(const time_t &start, const time_t &stop, const int &type) const
{
    // 0-半小时计费 1-包夜 2-包天
    if (type == 0)
    {
        // 半小时：30*60=1800
        long long time = stop - start, unit = 1800;
        int unit_cnt = (time % unit) ? time / unit + 1 : time / unit;
        return PricePerHalfHour * unit_cnt;
    }
    else if (type == 1)
    {
        // 将上机时间转化为tm结构
        tm *login_time_tm = localtime(&start);
        // 计算包夜范围结束时刻，赋值为当天早晨
        tm night_end_tm{};
        night_end_tm.tm_year = login_time_tm->tm_year;
        night_end_tm.tm_mon = login_time_tm->tm_mon;
        night_end_tm.tm_mday = login_time_tm->tm_mday;
        night_end_tm.tm_hour = NightRange.second;
        night_end_tm.tm_min = 0;
        night_end_tm.tm_sec = 0;
        // 包夜结束时刻转回time_t
        time_t night_end_time_t = mktime(&night_end_tm);
        // 如果包夜结束比上机时间还早，那么向后调整24个小时
        if (night_end_time_t <= start)
            night_end_time_t += 24 * 60 * 60;
        // 计算超时时长
        long long out_range = stop - night_end_time_t;
        // 基础包夜费用
        double cost = PriceWholeNight;
        // 额外超时费
        if (out_range > 0)
        {
            long long unit = 1800;
            int unit_cnt = (out_range % unit) ? out_range / unit + 1 : out_range / unit;
            cost += PricePerHalfHour * unit_cnt;
        }
        return cost;
    }
    else if (type == 2)
    {
        // 一天：24*60*60=86400
        long long time = stop - start, unit = 86400;
        int unit_cnt = (time % unit) ? time / unit + 1 : time / unit;
        return PriceWholeDay * unit_cnt;
    }
    return 0;
}

ostream &operator<<(ostream &os, const Price &price)
{
    os << price.PricePerHalfHour << ' ' << price.PriceWholeNight << ' ' << price.PriceWholeDay << ' '
       << price.NightRange.first << ' ' << price.NightRange.second << endl;
    return os;
}

istream &operator>>(istream &is, Price &price)
{
    is >> price.PricePerHalfHour >> price.PriceWholeNight >> price.PriceWholeDay
       >> price.NightRange.first >> price.NightRange.second;
    return is;
}

ostream &operator<<(ostream &os, const YearMonthDay &ymd)
{
    stringstream temp;
    temp << setfill('0') << setw(4) << ymd.Year << '/'
         << setw(2) << ymd.Month << '/'
         << setw(2) << ymd.Day << setfill(' ');
    os << temp.str();
    return os;
}

void Stat::Print()
{
    cout << left << setw(15) << Date
         << left << setw(10) << ConsumeCount
         << left << setw(10) << fixed << setprecision(2) << ConsumeAmount
         << left << setw(10) << CreatCardCount
         << left << setw(10) << DepositCount
         << left << setw(10) << fixed << setprecision(2) << DepositAmount
         << left << setw(10) << DeleteCardCount
         << left << setw(10) << RefundCount
         << left << setw(10) << fixed << setprecision(2) << RefundAmount
         << endl;
}

ostream &operator<<(ostream &os, const Stat &stat)
{
    os << stat.Date.Year << ' ' << stat.Date.Month << ' ' << stat.Date.Day << ' '
       << stat.CreatCardCount << ' ' << stat.DeleteCardCount << ' '
       << stat.DepositCount << ' ' << stat.RefundCount << ' '
       << stat.ConsumeCount << ' '
       << stat.DepositAmount << ' ' << stat.RefundAmount << ' '
       << stat.ConsumeAmount << endl;
    return os;
}

istream &operator>>(istream &is, Stat &stat)
{
    is >> stat.Date.Year >> stat.Date.Month >> stat.Date.Day
       >> stat.CreatCardCount >> stat.DeleteCardCount
       >> stat.DepositCount >> stat.RefundCount
       >> stat.ConsumeCount
       >> stat.DepositAmount >> stat.RefundAmount
       >> stat.ConsumeAmount;
    return is;
}
