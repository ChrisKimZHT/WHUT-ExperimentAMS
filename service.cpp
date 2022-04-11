#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "card_service.h"
#include "bill_service.h"
#include "global_var.h"
#include "tool.h"
#include "class.h"
#include "service.h"
#include "stat_service.h"

using namespace std;

void CreatCard()
{
    string name, password;
    double balance;
    cout << "========创建卡========" << endl;
    // 接受卡号
    while (true)
    {
        cout << "请设置卡号(" << CARD_NAME_MIN << '~' << CARD_NAME_MAX << "位): ";
        if (InputCheck_String(name, CARD_NAME_MIN, CARD_NAME_MAX))
        {
            if (!IsExist(name))
                break;
            else
                cout << "[!] 卡号已被占用" << endl;
        }
        else
            cout << "[!] 长度非法" << endl;
    }
    // 接受密码
    while (true)
    {
        cout << "请设置密码(" << CARD_PWD_MIN << '~' << CARD_PWD_MAX << "位): ";
        if (InputCheck_String(password, CARD_PWD_MIN, CARD_PWD_MAX))
            break;
        else
            cout << "[!] 长度非法" << endl;
    }
    // 接受首充
    while (true)
    {
        cout << "初始充值（首充20元起步）: ￥";
        if (InputCheck_Double(balance, 20.0))
            break;
        else
            cout << "[!] 数据非法" << endl;
    }
    Card new_card = Card(name, password, balance);
    Clear();
    cout << "========创建成功========" << endl;
    new_card.Print();
    SaveCard(name, new_card); // 保存卡到内存
    Save_Card(); // 保存卡到文件
    CreatBill(name, balance); // 保存账单到内存
    Save_Bill(); // 保存账单到文件
    StatUpdate(0, balance);
    Save_Stat();
    Pause();
}

void QueryCard(bool is_admin)
{
    cout << "========查询卡========" << endl;
    if (is_admin)
        cout << "[!] 当前为管理员查询模式，密码将会显示" << endl;
    string name;
    while (true)
    {
        cout << "输入待查卡号(可输入q终止查询): ";
        cin >> name;
        if (name == "q" || name.empty())
            break;
        Clear();
        cout << "========查询成功========" << endl;
        if (IsExist(name))
        {
            PrintCard(name, is_admin);
            break;
        }
        else
        {
            PrintSimilarCard(name);
        }
    }
    Pause();
}

void Price()
{
    cout << "========价格========" << endl;
    GetPrice().Print();
    Pause();
}

void Login()
{
    cout << "========上机========" << endl;
    string name, password;
    cout << "请输入卡号: ";
    cin >> name;
    cout << "请输入密码: ";
    cin >> password;
    int ret = CheckLogin(name, password);
    if (ret == 0)
    {
        int type;
        // 第一层循环，包夜不成功重选
        while (true)
        {
            cout << "0. 按量计费" << endl
                 << "1. 包夜" << endl
                 << "2. 包天" << endl;
            // 第二层循环，输入不成功重输
            while (true)
            {
                cout << "选择计费方式: ";
                if (InputCheck_Int(type, 0, 2))
                    break;
                else
                    cout << "[!] 输入非法" << endl;
            }
            Clear();
            if (type == 0)
            {
                cout << "========上机成功========" << endl
                     << "上机时间: " << Date2str(time(nullptr)) << endl;
                CreatBill(name, type);
                break;
            }
            else if (type == 1)
            {
                // 获取夜晚范围
                pair<int, int> range = GetNightRange();
                // 获取time_t格式当前时间
                time_t now_time_t = time(nullptr);
                // 转换为tm格式当前时间
                tm *now_time = localtime(&now_time_t);
                if (now_time->tm_hour >= range.first ||
                    now_time->tm_hour <= range.second)
                {
                    cout << "========上机成功========" << endl
                         << "上机时间: " << Date2str(time(nullptr)) << endl;
                    CreatBill(name, type);
                    break;
                }
                else
                {
                    cout << "========上机失败========" << endl
                         << "[!] 当前不在包夜时间段内，包夜时间段: " << range.first << '~' << range.second << endl;
                }
            }
            else if (type == 2)
            {
                Clear();
                cout << "========上机成功========" << endl
                     << "上机时间: " << Date2str(time(nullptr)) << endl;
                CreatBill(name, type);
                break;
            }
        }
        Save_Card();
        Save_Bill();
    }
    else if (ret == 1)
    {
        Clear();
        cout << "========上机失败========" << endl
             << "[!] 账号或密码错误" << endl;
    }
    else if (ret == 2)
    {
        Clear();
        cout << "========上机失败========" << endl
             << "[!] 该账号已经上机" << endl;
    }
    else if (ret == 3)
    {
        Clear();
        cout << "========上机失败========" << endl
             << "[!] 该卡已注销" << endl;
    }
    else if (ret == 4)
    {
        Clear();
        cout << "========上机失败========" << endl
             << "[!] 该卡有未结清账单" << endl;
    }
    Pause();
}

void Logoff()
{
    cout << "========下机========" << endl;
    string name, password;
    cout << "请输入卡号: ";
    cin >> name;
    cout << "请输入密码: ";
    cin >> password;
    int ret = CheckLogoff(name, password);
    Clear();
    if (ret == 0)
    {
        cout << "========下机成功========" << endl
             << "下机时间: " << Date2str(time(nullptr)) << endl;
        auto bill = GetIncompleteBill(name);
        if (Charge(name, bill.first))
        {
            SetPaid(name);
            CompleteBill(name);
            StatUpdate(4, bill.first, bill.second);
            StatDataSave();
            cout << "缴费成功！" << endl;
            printf("本次消费: ￥%.2lf\n卡余额: ￥%.2lf\n", bill, GetBalance(name));
        }
        else
        {
            cout << "[!] 缴费失败，余额不足！" << endl;
            printf("本次消费: ￥%.2lf\n卡余额: ￥%.2lf\n", bill, GetBalance(name));
        }
        Save_Card();
        Save_Bill();
    }
    else if (ret == 1)
        cout << "========下机失败========" << endl
             << "[!] 账号或密码错误" << endl;
    else if (ret == 2)
        cout << "========下机失败========" << endl
             << "[!] 该账号已经下机" << endl;
    else if (ret == 3)
        cout << "========下机失败========" << endl
             << "[!] 该卡已注销" << endl;
    Pause();
}

void Deposit()
{
    cout << "========充值========" << endl;
    string name;
    cout << "请输入卡号: ";
    cin >> name;
    if (IsExist(name))
    {
        if (GetStatus(name) == 0 || GetStatus(name) == 1)
        {
            double money;
            while (true)
            {
                cout << "当前余额: ￥" << fixed << setprecision(2) << GetBalance(name) << endl
                     << "请输入充值金额: ￥";
                if (InputCheck_Double(money, 0))
                    break;
                else
                    cout << "[!] 数据非法" << endl;
            }
            Clear();
            cout << "========充值成功========" << endl
                 << left << setw(16) << "充前余额: " << "￥" << fixed << setprecision(2) << GetBalance(name) << endl;
            CreatBill(name, money);
            UpdateBalance(name, money);
            cout << left << setw(16) << "充值金额: " << "￥" << fixed << setprecision(2) << money << endl;
            if (!IsSettled(name))
            {
                auto bill = GetIncompleteBill(name);
                if (Charge(name, bill.first))
                {
                    SetPaid(name);
                    CompleteBill(name);
                    StatUpdate(4, bill.first, bill.second);
                    StatDataSave();
                    cout << left << setw(16) << "未结账单扣除: " << "￥" << fixed << setprecision(2) << bill.first << endl;
                    SetPaid(name);
                }
                else
                {
                    cout << "[!] 当前仍有￥" << fixed << setprecision(2) << bill.first << "未结账单，该卡仍不可用" << endl;
                }
            }
            cout << "------------------------" << endl
                 << left << setw(16) << "当前余额: " << "￥" << fixed << setprecision(2) << GetBalance(name) << endl;
            Save_Bill();
            StatUpdate(2, money);
            Save_Stat();
        }
        else if (GetStatus(name) == 2)
        {
            Clear();
            cout << "========充值失败========" << endl
                 << "[!] 该卡已注销" << endl;
        }
    }
    else
    {
        Clear();
        cout << "========充值失败========" << endl
             << "[!] 该卡不存在" << endl;
    }
    Pause();
}

void Refund()
{
    cout << "========退费========" << endl;
    string name, password;
    cout << "请输入卡号: ";
    cin >> name;
    cout << "请输入密码: ";
    cin >> password;
    if (IsExist(name))
    {
        if (!IsSettled(name))
        {
            Clear();
            cout << "========退费失败========" << endl
                 << "[!] 账单结清前无法退费" << endl;
        }
        else if (PasswordCheck(name, password))
        {
            double money;
            cout << "当前余额: " << "￥" << fixed << setprecision(2) << GetBalance(name) << endl;
            while (true)
            {
                cout << "请输入退费金额: ￥";
                if (InputCheck_Double(money, 0))
                    break;
                else
                    cout << "[!] 数据非法" << endl;
            }
            if (money > GetBalance(name))
            {
                Clear();
                cout << "========退费失败========" << endl
                     << "[!] 退费不能超过余额" << endl;
            }
            else
            {
                Clear();
                cout << "========退费成功========" << endl
                     << left << setw(16) << "历史余额: " << "￥" << fixed << setprecision(2) << GetBalance(name) << endl
                     << left << setw(16) << "退费: " << "￥" << fixed << setprecision(2) << money << endl;
                CreatBill(name, -money);
                UpdateBalance(name, -money);
                cout << "------------------------" << endl
                     << left << setw(16) << "当前余额: " << "￥" << fixed << setprecision(2) << GetBalance(name) << endl;
                Save_Bill();
                StatUpdate(3, money);
                Save_Stat();
            }
        }
        else
        {
            Clear();
            cout << "========退费失败========" << endl
                 << "[!] 账号或密码错误" << endl;
        }
    }
    else
    {
        Clear();
        cout << "========退费失败========" << endl
             << "[!] 该卡不存在" << endl;
    }
    Pause();
}

void QueryBill()
{
    cout << "========账单========" << endl;
    string name;
    cout << "请输入卡号: ";
    cin >> name;
    Clear();
    if (IsExist(name))
    {
        cout << "========查询成功========" << endl;
        PrintBill(name);
    }
    else
    {
        cout << "========查询失败========" << endl
             << "[!] 该卡不存在" << endl;
    }
    Pause();
}

void Delete()
{
    cout << "========注销========" << endl;
    string name, password;
    cout << "请输入卡号: ";
    cin >> name;
    cout << "请输入密码: ";
    cin >> password;
    if (IsExist(name))
    {
        if (GetStatus(name) == 1)
        {
            Clear();
            cout << "========注销失败========" << endl
                 << "[!] 上机时无法注销" << endl;
        }
        else if (GetStatus(name) == 2)
        {
            Clear();
            cout << "========注销失败========" << endl
                 << "[!] 此卡已经注销" << endl;
        }
        else if (!IsSettled(name))
        {
            Clear();
            cout << "========注销失败========" << endl
                 << "[!] 账单结清前无法注销" << endl;
        }
        else if (PasswordCheck(name, password))
        {
            cout << "[!] 注销后将无法使用该卡，是否确认注销？(Y/N): ";
            bool choice;
            while (true)
            {
                if (InputCheck_YN(choice))
                    break;
                else
                    cout << "输入非法" << endl;
            }
            if (choice)
            {
                Clear();
                double refund = GetBalance(name);
                cout << "========注销成功========" << endl
                     << "余额退费: ￥" << fixed << setprecision(2) << refund << endl;
                UpdateBalance(name, -refund);
                CreatBill(name, -refund);
                DeleteCard(name);
                Save_Card();
                Save_Bill();
                StatUpdate(1, refund);
            }
            else
            {
                Clear();
                cout << "========注销失败========" << endl
                     << "[!] 用户取消操作" << endl;
            }
        }
        else
        {
            Clear();
            cout << "========注销失败========" << endl
                 << "[!] 账号或密码错误" << endl;
        }
    }
    else
    {
        Clear();
        cout << "========注销失败========" << endl
             << "[!] 该卡不存在" << endl;
    }
    Pause();
}

void Password()
{
    string name, password;
    cout << "========密码重设========" << endl;
    cout << "请输入卡号: ";
    cin >> name;
    cout << "请输入密码: ";
    cin >> password;
    if (IsExist(name) && PasswordCheck(name, password))
    {
        string new_password;
        while (true)
        {
            cout << "请输入新密码(" << CARD_PWD_MIN << '~' << CARD_PWD_MAX << "位): ";
            if (InputCheck_String(new_password, CARD_PWD_MIN, CARD_PWD_MAX))
                break;
            else
                cout << "[!] 长度非法" << endl;
        }
        SetPassword(name, new_password);
        Clear();
        cout << "========重设成功========" << endl
             << "卡号: " << name << endl
             << "密码: " << new_password << endl;
        Save_Card();
    }
    else
    {
        Clear();
        cout << "========重设失败========" << endl
             << "[!] 账号或密码错误" << endl;
    }
    Pause();
}

void Load_All()
{
    bool load;
    cout << "========初始化========" << endl;
    while (true)
    {
        cout << "是否读取数据？(Y/N): ";
        if (InputCheck_YN(load))
        {
            if (load)
            {
                PriceDataLoad();
                cout << "成功加载价格信息" << endl;
                cout << "成功加载卡信息: " << CardDataLoad() << "条" << endl;
                cout << "成功加载账单信息: " << BillDataLoad() << "条" << endl;
                cout << "成功加载统计信息: " << StatDataLoad() << "条" << endl;
                Pause();
            }
            break;
        }
        else
            cout << "[!] 输入非法" << endl;
    }
}

void Save_All()
{
    cout << "========保存========" << endl;
    PriceDataSave();
    cout << "成功保存价格信息" << endl;
    cout << "成功保存卡信息: " << CardDataSave() << "条" << endl;
    cout << "成功保存账单信息: " << BillDataSave() << "条" << endl;
    cout << "成功保存统计信息: " << StatDataSave() << "条" << endl;
}

void Save_Card()
{
    CardDataSave();
}

void Save_Bill()
{
    BillDataSave();
}

void Save_Price()
{
    PriceDataSave();
}

void Save_Stat()
{
    StatDataSave();
}

bool Admin_Login(const string &name, const string &password)
{
    // BEGIN 调试用代码，注意删除
    // return true;
    // END
    ifstream AdminData;
    AdminData.open("./AdminData.txt", ios::in);
    string admin_name, admin_password;
    AdminData >> admin_name >> admin_password;
    AdminData.close();
    if (name == admin_name && password == admin_password)
        return true;
    else
        return false;
}

void Admin_Price()
{
    cout << "========修改价格========" << endl;
    cout << "当前价格: " << endl;
    GetPrice().Print();
    cout << "------------------------" << endl;
    bool choice;
    while (true)
    {
        cout << "是否修改价格？(Y/N): ";
        if (InputCheck_YN(choice))
            break;
        else
            cout << "[!] 输入非法" << endl;
    }
    if (!choice)
        return;
    cout << "新价格: " << endl;
    double P_HalfHour, P_Night, P_Day;
    int NightStart, NightEnd;
    cout << "半小时计费: ￥";
    while (true)
    {
        if (InputCheck_Double(P_HalfHour, 0))
            break;
        else
            cout << "数据非法" << endl;
    }
    cout << "包夜计费: ￥";
    while (true)
    {
        if (InputCheck_Double(P_Night, 0))
            break;
        else
            cout << "数据非法" << endl;
    }
    cout << "包天计费: ￥";
    while (true)
    {
        if (InputCheck_Double(P_Day, 0))
            break;
        else
            cout << "数据非法" << endl;
    }
    cout << "包夜时间开始(0~24): ";
    while (true)
    {
        if (InputCheck_Int(NightStart, 0, 24))
            break;
        else
            cout << "数据非法" << endl;
    }
    cout << "包夜时间结束(0~24): ";
    while (true)
    {
        if (InputCheck_Int(NightEnd, 0, 24))
            break;
        else
            cout << "数据非法" << endl;
    }
    Clear();
    cout << "========修改成功========" << endl
         << "新价格: " << endl;
    ChangePrice(P_HalfHour, P_Night, P_Day, NightStart, NightEnd).Print();
    Save_Price();
    Pause();
}

void Admin_Stat()
{
    cout << "========收益统计========" << endl;
    int select;
    cout << "1. 按年/月/日统计" << endl
         << "2. 按时间段统计" << endl
         << "0. 返回" << endl;
    while (true)
    {
        cout << "请选择操作(0~2): ";
        if (InputCheck_Int(select, 0, 2))
            break;
        else
            cout << "输入非法" << endl;
    }
    if (select == 0)
    {
        return;
    }
    else if (select == 1)
    {
        int year = 0, month = 0, day = 0;
        while (true)
        {
            cout << "选择统计范围，可用0表示缺省，缺省写法例如\"2022 0 0\"和\"2022 3 0\"" << endl
                 << "请输入(YYYY MM DD): ";
            if (cin >> year >> month >> day && year >= 1900 && year <= 2100 &&
                month >= 0 && month <= 12 && day >= 0 && day <= 31)
            {
                break;
            }
            else
            {
                cin.clear();
                cin.ignore(1024, '\n');
                cout << "输入非法" << endl;
            }
        }
        Clear();
        PrintStat(year, month, day);
    }
    else if (select == 2)
    {
        YearMonthDay start, end;
        int year, month, day;
        while (true)
        {
            cout << "请输入开始日期(YYYY MM DD): ";
            if (cin >> year >> month >> day && year >= 1900 && year <= 2100 &&
                month >= 1 && month <= 12 && day >= 1 && day <= 31)
            {
                break;
            }
            else
            {
                cin.clear();
                cin.ignore(1024, '\n');
                cout << "输入非法" << endl;
            }
        }
        start = {year, month, day};
        while (true)
        {
            cout << "请输入截止日期(YYYY MM DD): ";
            if (cin >> year >> month >> day && year >= 1900 && year <= 2100 &&
                month >= 1 && month <= 12 && day >= 1 && day <= 31)
            {
                break;
            }
            else
            {
                cin.clear();
                cin.ignore(1024, '\n');
                cout << "输入非法" << endl;
            }
        }
        end = {year, month, day};
        Clear();
        PrintStat(start, end);
    }
    Pause();
}

void Admin_Card()
{
    cout << "========查询卡========" << endl;
    cout << "1. 单卡查询" << endl
         << "2. 输出所有卡" << endl
         << "0. 返回" << endl;
    int choice;
    while (true)
    {
        cout << "选择查询模式(0~2): ";
        if (InputCheck_Int(choice, 0, 2))
            break;
        else
            cout << "输入非法" << endl;
    }
    Clear();
    if (choice == 1)
    {
        QueryCard(true);
    }
    else if (choice == 2)
    {
        cout << "========查询成功========" << endl;
        PrintAllCard();
        Pause();
    }
}