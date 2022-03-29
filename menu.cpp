#include <iostream>
#include "service.h"
#include "global_var.h"
#include "tool.h"
#include "menu.h"

using namespace std;

void Init()
{
    Load_All();
}

void Index_Master()
{
    Clear();
    cout << "====================" << endl
         << "计费管理系统 -> 主菜单" << endl
         << "====================" << endl
         << "1. 消费" << endl
         << "2. 账户" << endl
         << "3. 管理" << endl
         << "0. 退出" << endl
         << "输入操作选项前序号(0~3): ";
}

void Menu(int select)
{
    switch (select)
    {
        case 1:
            Clear();
            Index_Consume();
            break;
        case 2:
            Clear();
            Index_Card();
            break;
        case 3:
            Clear();
            Index_Admin_Auth();
            break;
        case 0:
            Clear();
            Save_All();
            break;
        default:
            break;
    }
}

void Index_Consume()
{
    cout << "====================" << endl
         << "计费管理系统 -> 消费" << endl
         << "====================" << endl
         << "1. 价格" << endl
         << "2. 上机" << endl
         << "3. 下机" << endl
         << "4. 充值" << endl
         << "5. 退费" << endl
         << "6. 查询账单" << endl
         << "0. 返回" << endl;
    int select;
    while (true)
    {
        cout << "输入操作选项前序号(0~6): ";
        if (InputCheck_Int(select, 0, 6))
            break;
        else
            cout << "输入非法" << endl;
    }
    switch (select)
    {
        case 1:
            Clear();
            Price();
            break;
        case 2:
            Clear();
            Login();
            break;
        case 3:
            Clear();
            Logoff();
            break;
        case 4:
            Clear();
            Deposit();
            break;
        case 5:
            Clear();
            Refund();
            break;
        case 6:
            Clear();
            QueryBill();
            break;
        default:
            return;
    }
}

void Index_Card()
{
    cout << "====================" << endl
         << "计费管理系统 -> 账户" << endl
         << "====================" << endl
         << "1. 创建卡" << endl
         << "2. 注销卡" << endl
         << "3. 查询卡" << endl
         << "4. 重设密码" << endl
         << "0. 返回" << endl;
    int select;
    while (true)
    {
        cout << "输入操作选项前序号(0~4): ";
        if (InputCheck_Int(select, 0, 4))
            break;
        else
            cout << "输入非法" << endl;
    }
    switch (select)
    {
        case 1:
            Clear();
            CreatCard();
            break;
        case 2:
            Clear();
            Delete();
            break;
        case 3:
            Clear();
            QueryCard();
            break;
        case 4:
            Clear();
            Password();
            break;
        default:
            return;
    }
}

void Index_Admin_Auth()
{
    cout << "====================" << endl
         << "计费管理系统 -> 管理" << endl
         << "====================" << endl;
    if (!ADMIN_LOGIN)
    {
        string name, password;
        cout << "[!] 需要登陆" << endl
             << "请输入管理员账号: ";
        cin >> name;
        cout << "请输入管理员密码: ";
        cin >> password;
        if (Admin_Login(name, password))
        {
            ADMIN_LOGIN = true;
            Clear();
            Index_Admin();
        }
        else
        {
            Clear();
            cout << "====================" << endl
                 << "计费管理系统 -> 管理" << endl
                 << "====================" << endl
                 << "[!] 认证失败" << endl;
            Pause();
        }
    }
    else
    {
        Clear();
        Index_Admin();
    }
}

void Index_Admin()
{
    cout << "====================" << endl
         << "计费管理系统 -> 管理" << endl
         << "====================" << endl
         << "1. 查看收益" << endl
         << "2. 价格设置" << endl
         << "3. 登出" << endl
         << "0. 返回" << endl
         << "输入操作选项前序号(0~3): ";
    int select;
    while (true)
    {
        if (InputCheck_Int(select, 0, 3))
            break;
        else
            cout << "输入非法" << endl;
    }
    switch (select)
    {
        case 1:
            Clear();
            Admin_Stat();
            break;
        case 2:
            Clear();
            Admin_Price();
            break;
        case 3:
            ADMIN_LOGIN = false;
            break;
        default:
            return;
    }
}