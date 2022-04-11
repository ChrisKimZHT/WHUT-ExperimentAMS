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
    cout << "========������========" << endl;
    // ���ܿ���
    while (true)
    {
        cout << "�����ÿ���(" << CARD_NAME_MIN << '~' << CARD_NAME_MAX << "λ): ";
        if (InputCheck_String(name, CARD_NAME_MIN, CARD_NAME_MAX))
        {
            if (!IsExist(name))
                break;
            else
                cout << "[!] �����ѱ�ռ��" << endl;
        }
        else
            cout << "[!] ���ȷǷ�" << endl;
    }
    // ��������
    while (true)
    {
        cout << "����������(" << CARD_PWD_MIN << '~' << CARD_PWD_MAX << "λ): ";
        if (InputCheck_String(password, CARD_PWD_MIN, CARD_PWD_MAX))
            break;
        else
            cout << "[!] ���ȷǷ�" << endl;
    }
    // �����׳�
    while (true)
    {
        cout << "��ʼ��ֵ���׳�20Ԫ�𲽣�: ��";
        if (InputCheck_Double(balance, 20.0))
            break;
        else
            cout << "[!] ���ݷǷ�" << endl;
    }
    Card new_card = Card(name, password, balance);
    Clear();
    cout << "========�����ɹ�========" << endl;
    new_card.Print();
    SaveCard(name, new_card); // ���濨���ڴ�
    Save_Card(); // ���濨���ļ�
    CreatBill(name, balance); // �����˵����ڴ�
    Save_Bill(); // �����˵����ļ�
    StatUpdate(0, balance);
    Save_Stat();
    Pause();
}

void QueryCard(bool is_admin)
{
    cout << "========��ѯ��========" << endl;
    if (is_admin)
        cout << "[!] ��ǰΪ����Ա��ѯģʽ�����뽫����ʾ" << endl;
    string name;
    while (true)
    {
        cout << "������鿨��(������q��ֹ��ѯ): ";
        cin >> name;
        if (name == "q" || name.empty())
            break;
        Clear();
        cout << "========��ѯ�ɹ�========" << endl;
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
    cout << "========�۸�========" << endl;
    GetPrice().Print();
    Pause();
}

void Login()
{
    cout << "========�ϻ�========" << endl;
    string name, password;
    cout << "�����뿨��: ";
    cin >> name;
    cout << "����������: ";
    cin >> password;
    int ret = CheckLogin(name, password);
    if (ret == 0)
    {
        int type;
        // ��һ��ѭ������ҹ���ɹ���ѡ
        while (true)
        {
            cout << "0. �����Ʒ�" << endl
                 << "1. ��ҹ" << endl
                 << "2. ����" << endl;
            // �ڶ���ѭ�������벻�ɹ�����
            while (true)
            {
                cout << "ѡ��Ʒѷ�ʽ: ";
                if (InputCheck_Int(type, 0, 2))
                    break;
                else
                    cout << "[!] ����Ƿ�" << endl;
            }
            Clear();
            if (type == 0)
            {
                cout << "========�ϻ��ɹ�========" << endl
                     << "�ϻ�ʱ��: " << Date2str(time(nullptr)) << endl;
                CreatBill(name, type);
                break;
            }
            else if (type == 1)
            {
                // ��ȡҹ��Χ
                pair<int, int> range = GetNightRange();
                // ��ȡtime_t��ʽ��ǰʱ��
                time_t now_time_t = time(nullptr);
                // ת��Ϊtm��ʽ��ǰʱ��
                tm *now_time = localtime(&now_time_t);
                if (now_time->tm_hour >= range.first ||
                    now_time->tm_hour <= range.second)
                {
                    cout << "========�ϻ��ɹ�========" << endl
                         << "�ϻ�ʱ��: " << Date2str(time(nullptr)) << endl;
                    CreatBill(name, type);
                    break;
                }
                else
                {
                    cout << "========�ϻ�ʧ��========" << endl
                         << "[!] ��ǰ���ڰ�ҹʱ����ڣ���ҹʱ���: " << range.first << '~' << range.second << endl;
                }
            }
            else if (type == 2)
            {
                Clear();
                cout << "========�ϻ��ɹ�========" << endl
                     << "�ϻ�ʱ��: " << Date2str(time(nullptr)) << endl;
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
        cout << "========�ϻ�ʧ��========" << endl
             << "[!] �˺Ż��������" << endl;
    }
    else if (ret == 2)
    {
        Clear();
        cout << "========�ϻ�ʧ��========" << endl
             << "[!] ���˺��Ѿ��ϻ�" << endl;
    }
    else if (ret == 3)
    {
        Clear();
        cout << "========�ϻ�ʧ��========" << endl
             << "[!] �ÿ���ע��" << endl;
    }
    else if (ret == 4)
    {
        Clear();
        cout << "========�ϻ�ʧ��========" << endl
             << "[!] �ÿ���δ�����˵�" << endl;
    }
    Pause();
}

void Logoff()
{
    cout << "========�»�========" << endl;
    string name, password;
    cout << "�����뿨��: ";
    cin >> name;
    cout << "����������: ";
    cin >> password;
    int ret = CheckLogoff(name, password);
    Clear();
    if (ret == 0)
    {
        cout << "========�»��ɹ�========" << endl
             << "�»�ʱ��: " << Date2str(time(nullptr)) << endl;
        auto bill = GetIncompleteBill(name);
        if (Charge(name, bill.first))
        {
            SetPaid(name);
            CompleteBill(name);
            StatUpdate(4, bill.first, bill.second);
            StatDataSave();
            cout << "�ɷѳɹ���" << endl;
            printf("��������: ��%.2lf\n�����: ��%.2lf\n", bill, GetBalance(name));
        }
        else
        {
            cout << "[!] �ɷ�ʧ�ܣ����㣡" << endl;
            printf("��������: ��%.2lf\n�����: ��%.2lf\n", bill, GetBalance(name));
        }
        Save_Card();
        Save_Bill();
    }
    else if (ret == 1)
        cout << "========�»�ʧ��========" << endl
             << "[!] �˺Ż��������" << endl;
    else if (ret == 2)
        cout << "========�»�ʧ��========" << endl
             << "[!] ���˺��Ѿ��»�" << endl;
    else if (ret == 3)
        cout << "========�»�ʧ��========" << endl
             << "[!] �ÿ���ע��" << endl;
    Pause();
}

void Deposit()
{
    cout << "========��ֵ========" << endl;
    string name;
    cout << "�����뿨��: ";
    cin >> name;
    if (IsExist(name))
    {
        if (GetStatus(name) == 0 || GetStatus(name) == 1)
        {
            double money;
            while (true)
            {
                cout << "��ǰ���: ��" << fixed << setprecision(2) << GetBalance(name) << endl
                     << "�������ֵ���: ��";
                if (InputCheck_Double(money, 0))
                    break;
                else
                    cout << "[!] ���ݷǷ�" << endl;
            }
            Clear();
            cout << "========��ֵ�ɹ�========" << endl
                 << left << setw(16) << "��ǰ���: " << "��" << fixed << setprecision(2) << GetBalance(name) << endl;
            CreatBill(name, money);
            UpdateBalance(name, money);
            cout << left << setw(16) << "��ֵ���: " << "��" << fixed << setprecision(2) << money << endl;
            if (!IsSettled(name))
            {
                auto bill = GetIncompleteBill(name);
                if (Charge(name, bill.first))
                {
                    SetPaid(name);
                    CompleteBill(name);
                    StatUpdate(4, bill.first, bill.second);
                    StatDataSave();
                    cout << left << setw(16) << "δ���˵��۳�: " << "��" << fixed << setprecision(2) << bill.first << endl;
                    SetPaid(name);
                }
                else
                {
                    cout << "[!] ��ǰ���У�" << fixed << setprecision(2) << bill.first << "δ���˵����ÿ��Բ�����" << endl;
                }
            }
            cout << "------------------------" << endl
                 << left << setw(16) << "��ǰ���: " << "��" << fixed << setprecision(2) << GetBalance(name) << endl;
            Save_Bill();
            StatUpdate(2, money);
            Save_Stat();
        }
        else if (GetStatus(name) == 2)
        {
            Clear();
            cout << "========��ֵʧ��========" << endl
                 << "[!] �ÿ���ע��" << endl;
        }
    }
    else
    {
        Clear();
        cout << "========��ֵʧ��========" << endl
             << "[!] �ÿ�������" << endl;
    }
    Pause();
}

void Refund()
{
    cout << "========�˷�========" << endl;
    string name, password;
    cout << "�����뿨��: ";
    cin >> name;
    cout << "����������: ";
    cin >> password;
    if (IsExist(name))
    {
        if (!IsSettled(name))
        {
            Clear();
            cout << "========�˷�ʧ��========" << endl
                 << "[!] �˵�����ǰ�޷��˷�" << endl;
        }
        else if (PasswordCheck(name, password))
        {
            double money;
            cout << "��ǰ���: " << "��" << fixed << setprecision(2) << GetBalance(name) << endl;
            while (true)
            {
                cout << "�������˷ѽ��: ��";
                if (InputCheck_Double(money, 0))
                    break;
                else
                    cout << "[!] ���ݷǷ�" << endl;
            }
            if (money > GetBalance(name))
            {
                Clear();
                cout << "========�˷�ʧ��========" << endl
                     << "[!] �˷Ѳ��ܳ������" << endl;
            }
            else
            {
                Clear();
                cout << "========�˷ѳɹ�========" << endl
                     << left << setw(16) << "��ʷ���: " << "��" << fixed << setprecision(2) << GetBalance(name) << endl
                     << left << setw(16) << "�˷�: " << "��" << fixed << setprecision(2) << money << endl;
                CreatBill(name, -money);
                UpdateBalance(name, -money);
                cout << "------------------------" << endl
                     << left << setw(16) << "��ǰ���: " << "��" << fixed << setprecision(2) << GetBalance(name) << endl;
                Save_Bill();
                StatUpdate(3, money);
                Save_Stat();
            }
        }
        else
        {
            Clear();
            cout << "========�˷�ʧ��========" << endl
                 << "[!] �˺Ż��������" << endl;
        }
    }
    else
    {
        Clear();
        cout << "========�˷�ʧ��========" << endl
             << "[!] �ÿ�������" << endl;
    }
    Pause();
}

void QueryBill()
{
    cout << "========�˵�========" << endl;
    string name;
    cout << "�����뿨��: ";
    cin >> name;
    Clear();
    if (IsExist(name))
    {
        cout << "========��ѯ�ɹ�========" << endl;
        PrintBill(name);
    }
    else
    {
        cout << "========��ѯʧ��========" << endl
             << "[!] �ÿ�������" << endl;
    }
    Pause();
}

void Delete()
{
    cout << "========ע��========" << endl;
    string name, password;
    cout << "�����뿨��: ";
    cin >> name;
    cout << "����������: ";
    cin >> password;
    if (IsExist(name))
    {
        if (GetStatus(name) == 1)
        {
            Clear();
            cout << "========ע��ʧ��========" << endl
                 << "[!] �ϻ�ʱ�޷�ע��" << endl;
        }
        else if (GetStatus(name) == 2)
        {
            Clear();
            cout << "========ע��ʧ��========" << endl
                 << "[!] �˿��Ѿ�ע��" << endl;
        }
        else if (!IsSettled(name))
        {
            Clear();
            cout << "========ע��ʧ��========" << endl
                 << "[!] �˵�����ǰ�޷�ע��" << endl;
        }
        else if (PasswordCheck(name, password))
        {
            cout << "[!] ע�����޷�ʹ�øÿ����Ƿ�ȷ��ע����(Y/N): ";
            bool choice;
            while (true)
            {
                if (InputCheck_YN(choice))
                    break;
                else
                    cout << "����Ƿ�" << endl;
            }
            if (choice)
            {
                Clear();
                double refund = GetBalance(name);
                cout << "========ע���ɹ�========" << endl
                     << "����˷�: ��" << fixed << setprecision(2) << refund << endl;
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
                cout << "========ע��ʧ��========" << endl
                     << "[!] �û�ȡ������" << endl;
            }
        }
        else
        {
            Clear();
            cout << "========ע��ʧ��========" << endl
                 << "[!] �˺Ż��������" << endl;
        }
    }
    else
    {
        Clear();
        cout << "========ע��ʧ��========" << endl
             << "[!] �ÿ�������" << endl;
    }
    Pause();
}

void Password()
{
    string name, password;
    cout << "========��������========" << endl;
    cout << "�����뿨��: ";
    cin >> name;
    cout << "����������: ";
    cin >> password;
    if (IsExist(name) && PasswordCheck(name, password))
    {
        string new_password;
        while (true)
        {
            cout << "������������(" << CARD_PWD_MIN << '~' << CARD_PWD_MAX << "λ): ";
            if (InputCheck_String(new_password, CARD_PWD_MIN, CARD_PWD_MAX))
                break;
            else
                cout << "[!] ���ȷǷ�" << endl;
        }
        SetPassword(name, new_password);
        Clear();
        cout << "========����ɹ�========" << endl
             << "����: " << name << endl
             << "����: " << new_password << endl;
        Save_Card();
    }
    else
    {
        Clear();
        cout << "========����ʧ��========" << endl
             << "[!] �˺Ż��������" << endl;
    }
    Pause();
}

void Load_All()
{
    bool load;
    cout << "========��ʼ��========" << endl;
    while (true)
    {
        cout << "�Ƿ��ȡ���ݣ�(Y/N): ";
        if (InputCheck_YN(load))
        {
            if (load)
            {
                PriceDataLoad();
                cout << "�ɹ����ؼ۸���Ϣ" << endl;
                cout << "�ɹ����ؿ���Ϣ: " << CardDataLoad() << "��" << endl;
                cout << "�ɹ������˵���Ϣ: " << BillDataLoad() << "��" << endl;
                cout << "�ɹ�����ͳ����Ϣ: " << StatDataLoad() << "��" << endl;
                Pause();
            }
            break;
        }
        else
            cout << "[!] ����Ƿ�" << endl;
    }
}

void Save_All()
{
    cout << "========����========" << endl;
    PriceDataSave();
    cout << "�ɹ�����۸���Ϣ" << endl;
    cout << "�ɹ����濨��Ϣ: " << CardDataSave() << "��" << endl;
    cout << "�ɹ������˵���Ϣ: " << BillDataSave() << "��" << endl;
    cout << "�ɹ�����ͳ����Ϣ: " << StatDataSave() << "��" << endl;
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
    // BEGIN �����ô��룬ע��ɾ��
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
    cout << "========�޸ļ۸�========" << endl;
    cout << "��ǰ�۸�: " << endl;
    GetPrice().Print();
    cout << "------------------------" << endl;
    bool choice;
    while (true)
    {
        cout << "�Ƿ��޸ļ۸�(Y/N): ";
        if (InputCheck_YN(choice))
            break;
        else
            cout << "[!] ����Ƿ�" << endl;
    }
    if (!choice)
        return;
    cout << "�¼۸�: " << endl;
    double P_HalfHour, P_Night, P_Day;
    int NightStart, NightEnd;
    cout << "��Сʱ�Ʒ�: ��";
    while (true)
    {
        if (InputCheck_Double(P_HalfHour, 0))
            break;
        else
            cout << "���ݷǷ�" << endl;
    }
    cout << "��ҹ�Ʒ�: ��";
    while (true)
    {
        if (InputCheck_Double(P_Night, 0))
            break;
        else
            cout << "���ݷǷ�" << endl;
    }
    cout << "����Ʒ�: ��";
    while (true)
    {
        if (InputCheck_Double(P_Day, 0))
            break;
        else
            cout << "���ݷǷ�" << endl;
    }
    cout << "��ҹʱ�俪ʼ(0~24): ";
    while (true)
    {
        if (InputCheck_Int(NightStart, 0, 24))
            break;
        else
            cout << "���ݷǷ�" << endl;
    }
    cout << "��ҹʱ�����(0~24): ";
    while (true)
    {
        if (InputCheck_Int(NightEnd, 0, 24))
            break;
        else
            cout << "���ݷǷ�" << endl;
    }
    Clear();
    cout << "========�޸ĳɹ�========" << endl
         << "�¼۸�: " << endl;
    ChangePrice(P_HalfHour, P_Night, P_Day, NightStart, NightEnd).Print();
    Save_Price();
    Pause();
}

void Admin_Stat()
{
    cout << "========����ͳ��========" << endl;
    int select;
    cout << "1. ����/��/��ͳ��" << endl
         << "2. ��ʱ���ͳ��" << endl
         << "0. ����" << endl;
    while (true)
    {
        cout << "��ѡ�����(0~2): ";
        if (InputCheck_Int(select, 0, 2))
            break;
        else
            cout << "����Ƿ�" << endl;
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
            cout << "ѡ��ͳ�Ʒ�Χ������0��ʾȱʡ��ȱʡд������\"2022 0 0\"��\"2022 3 0\"" << endl
                 << "������(YYYY MM DD): ";
            if (cin >> year >> month >> day && year >= 1900 && year <= 2100 &&
                month >= 0 && month <= 12 && day >= 0 && day <= 31)
            {
                break;
            }
            else
            {
                cin.clear();
                cin.ignore(1024, '\n');
                cout << "����Ƿ�" << endl;
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
            cout << "�����뿪ʼ����(YYYY MM DD): ";
            if (cin >> year >> month >> day && year >= 1900 && year <= 2100 &&
                month >= 1 && month <= 12 && day >= 1 && day <= 31)
            {
                break;
            }
            else
            {
                cin.clear();
                cin.ignore(1024, '\n');
                cout << "����Ƿ�" << endl;
            }
        }
        start = {year, month, day};
        while (true)
        {
            cout << "�������ֹ����(YYYY MM DD): ";
            if (cin >> year >> month >> day && year >= 1900 && year <= 2100 &&
                month >= 1 && month <= 12 && day >= 1 && day <= 31)
            {
                break;
            }
            else
            {
                cin.clear();
                cin.ignore(1024, '\n');
                cout << "����Ƿ�" << endl;
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
    cout << "========��ѯ��========" << endl;
    cout << "1. ������ѯ" << endl
         << "2. ������п�" << endl
         << "0. ����" << endl;
    int choice;
    while (true)
    {
        cout << "ѡ���ѯģʽ(0~2): ";
        if (InputCheck_Int(choice, 0, 2))
            break;
        else
            cout << "����Ƿ�" << endl;
    }
    Clear();
    if (choice == 1)
    {
        QueryCard(true);
    }
    else if (choice == 2)
    {
        cout << "========��ѯ�ɹ�========" << endl;
        PrintAllCard();
        Pause();
    }
}