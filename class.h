#ifndef EXPERIMENTAMS_CLASS_H
#define EXPERIMENTAMS_CLASS_H

class Card // 储存卡的类
{
private:
    std::string CardName; // 卡号
    std::string CardPassword; // 密码
    int CardStatus{}; // 0-未使用 1-使用中 2-已注销
    time_t CreatTime{}; // 创建时间
    time_t DeleteTime{}; // 注销时间
    time_t LastTime{}; // 上次使用时间
    double TotalUse{}; // 总消费额
    int UseCount{}; // 消费次数
    double Balance{}; // 当前余额
    bool IsSettled{}; // 是否结清
public:
    /* 构造函数 */
    Card() { ; } // 默认构造函数
    Card(const std::string &name, const std::string &password, const double &money) // 构造函数
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

    /* 内联成员函数 */
    std::string Name() { return CardName; } // 获取卡名
    int Status() const { return CardStatus; } // 获取卡状态
    double GetBalance() const { return Balance; } // 获取余额
    int SettleStat() const { return IsSettled; } // 获取结清状态
    void Login() { CardStatus = 1; } // 更改卡状态为上机
    void Logoff() // 更改卡状态为下机（更新使用时间、使用次数）
    {
        CardStatus = 0;
        LastTime = time(nullptr);
        UseCount++;
    }
    void Paid() { IsSettled = true; } // 更改卡为已结清
    void UnPaid() { IsSettled = false; } // 更改卡为未结清
    void Update(double value) { Balance += value; } // 更新余额
    void Delete() // 注销卡
    {
        CardStatus = 2;
        DeleteTime = time(nullptr);
    }
    void SetPassword(const std::string &password) { CardPassword = password; } // 更新密码

    /* 一般成员函数 */
    void Print(bool= false); // 直接输出Card的信息，若为管理员则同时输出密码
    void PrintOneline(); // 单行输出Card的信息
    bool CheckPassword(const std::string &); // 比对账号密码用于上机登录
    bool Charge(double); // 收费

    /* 重载运算符 */
    friend std::ostream &operator<<(std::ostream &, const Card &);
    friend std::istream &operator>>(std::istream &, Card &);
};

class Bill // 储存账单的类
{
private:
    std::string CardName; // 卡号
    time_t StartTime{}; // 上机时间
    time_t EndTime{}; // 下机时间
    double Fare{}; // 金额
    int Type{}; // 计费种类
    bool IsPaid{}; // 是否结清
public:
    /* 构造函数 */
    Bill() { ; } // 默认构造函数
    Bill(const std::string &name, const int &type) // 构造函数-上机账单
    {
        CardName = name;
        StartTime = time(nullptr);
        EndTime = 0;
        IsPaid = false;
        Fare = 0;
        Type = type;
    }
    Bill(const std::string &name, const double &value) // 构造函数-充退账单
    {
        CardName = name;
        StartTime = time(nullptr);
        EndTime = StartTime;
        IsPaid = true;
        Fare = value;
        Type = -1;
    }

    /* 内联成员函数 */
    void SetEnd(time_t t) { EndTime = t; } // 设置结束日期
    void SetPaid() { IsPaid = true; } // 设置结清
    void SetFare(double f) { Fare = f; } // 设置费用
    std::string GetName() { return CardName; } // 获取卡号
    bool Paid() const { return IsPaid; } // 获取是否结清
    int GetType() const { return Type; } // 获取种类
    time_t GetStart() const { return StartTime; } // 获取开始时间
    time_t GetEnd() const { return EndTime; } // 获取结束时间
    double GetFare() const { return Fare; } // 获取费用

    /* 一般成员函数 */
    void Print() const; // 输出Bill的信息

    /* 重载运算符 */
    friend std::ostream &operator<<(std::ostream &, const Bill &);
    friend std::istream &operator>>(std::istream &, Bill &);
};

class Price // 储存计费的类
{
private:
    double PricePerHalfHour;
    double PriceWholeNight;
    double PriceWholeDay;
    std::pair<int, int> NightRange;
public:
    /* 构造函数 */
    Price(double P_HalfHour = 2.0, double P_Night = 27.0, double P_Day = 48.0, int NightStart = 22,
          int NightEnd = 7) // 构造函数
    {
        PricePerHalfHour = P_HalfHour;
        PriceWholeNight = P_Night;
        PriceWholeDay = P_Day;
        NightRange.first = NightStart;
        NightRange.second = NightEnd;
    }

    /* 内联成员函数 */
    std::pair<int, int> GetNightRange() { return NightRange; } // 获取包夜范围

    /* 一般成员函数 */
    void Print() const; // 输出价格
    double CalcFare(const time_t &, const time_t &, const int &) const; // 计算费用 0-半小时计费 1-包夜 2-包天

    /* 重载运算符 */
    friend std::ostream &operator<<(std::ostream &, const Price &);
    friend std::istream &operator>>(std::istream &, Price &);
};

struct YearMonthDay // 年月日结构体
{
    int Year, Month, Day;

    /* 构造函数 */
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

    /* 重载运算符 */
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
//    friend std::ostream &operator<<(std::ostream &, const YearMonthDay &);
};

class Stat // 储存统计信息的类
{
private:
    YearMonthDay Date; // 日期
    int CreatCardCount; // 创建卡次数
    int DeleteCardCount; // 注销卡次数
    int DepositCount; // 储值次数
    int RefundCount; // 退费次数
    int ConsumeCount; // 消费次数
    double DepositAmount; // 储值量
    double RefundAmount; // 退费量
    double ConsumeAmount; // 消费量
public:
    /* 构造函数 */
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
    explicit Stat(const YearMonthDay &val)
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

    /* 内联成员函数 */
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

    /* 一般成员函数 */
    void Print(); // 输出

    /* 重载运算符 */
    friend std::ostream &operator<<(std::ostream &, const Stat &);
    friend std::istream &operator>>(std::istream &, Stat &);
    Stat operator+(const Stat &a) const
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
