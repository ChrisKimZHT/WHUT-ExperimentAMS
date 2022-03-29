#include "menu.h"

using namespace std;

void Index_Master()
{
    Clear();
    cout << "====================" << endl
         << "�Ʒѹ���ϵͳ -> ���˵�" << endl
         << "====================" << endl
         << "1. ����" << endl
         << "2. �˻�" << endl
         << "3. ��ѯ" << endl
         << "4. ����" << endl
         << "0. �˳�" << endl
         << "�������ѡ��ǰ���(0~4): ";
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
            Index_Query();
            break;
        case 4:
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
         << "�Ʒѹ���ϵͳ -> ����" << endl
         << "====================" << endl
         << "1. �۸�" << endl
         << "2. �ϻ�" << endl
         << "3. �»�" << endl
         << "0. ����" << endl
         << "�������ѡ��ǰ���(0~3): ";
    int select;
    while (true)
    {
        if (InputCheck_Int(select, 0, 3))
            break;
        else
            cout << "����Ƿ�" << endl;
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
        default:
            return;
    }
}

void Index_Card()
{
    cout << "====================" << endl
         << "�Ʒѹ���ϵͳ -> �˻�" << endl
         << "====================" << endl
         << "1. ������" << endl
         << "2. ע����" << endl
         << "3. ��������" << endl
         << "4. ��ֵ" << endl
         << "5. �˷�" << endl
         << "0. ����" << endl
         << "�������ѡ��ǰ���(0~4): ";
    int select;
    while (true)
    {
        if (InputCheck_Int(select, 0, 5))
            break;
        else
            cout << "����Ƿ�" << endl;
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
            Password();
            break;
        case 4:
            Clear();
            Deposit();
            break;
        case 5:
            Clear();
            Refund();
            break;
        default:
            return;
    }
}

void Index_Query()
{
    cout << "====================" << endl
         << "�Ʒѹ���ϵͳ -> ��ѯ" << endl
         << "====================" << endl
         << "1. ��ȷ��ѯ��" << endl
         << "2. ģ����ѯ��" << endl
         << "3. ��ѯ�����˵�" << endl
         << "0. ����" << endl
         << "�������ѡ��ǰ���(0~3): ";
    int select;
    while (true)
    {
        if (InputCheck_Int(select, 0, 3))
            break;
        else
            cout << "����Ƿ�" << endl;
    }
    switch (select)
    {
        case 1:
            Clear();
            QueryCard(false);
            break;
        case 2:
            Clear();
            QueryCard(true);
            break;
        case 3:
            Clear();
            QueryBill();
            break;
        default:
            return;
    }
}

void Index_Admin_Auth()
{
    cout << "====================" << endl
         << "�Ʒѹ���ϵͳ -> ����" << endl
         << "====================" << endl;
    if (!ADMIN_LOGIN)
    {
        string name, password;
        cout << "[!] ��Ҫ��½" << endl
             << "���������Ա�˺�: ";
        cin >> name;
        cout << "���������Ա����: ";
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
                 << "�Ʒѹ���ϵͳ -> ����" << endl
                 << "====================" << endl
                 << "[!] ��֤ʧ��" << endl;
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
         << "�Ʒѹ���ϵͳ -> ����" << endl
         << "====================" << endl
         << "1. �鿴����" << endl
         << "2. �۸�����" << endl
         << "3. �ǳ�" << endl
         << "0. ����" << endl
         << "�������ѡ��ǰ���(0~3): ";
    int select;
    while (true)
    {
        if (InputCheck_Int(select, 0, 3))
            break;
        else
            cout << "����Ƿ�" << endl;
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