#include <iostream>
#include "menu.h"
#include "tool.h"

using namespace std;

int main()
{
    // ��ʼ��
    Init();
    // ������
    int select = -1;
    do
    {
        Index_Master();
        if (InputCheck_Int(select, 0, 3))
            Menu(select);
        else
            cout << "�����쳣" << endl;
    } while (select);
    // �������
    cout << "[!] �������" << endl;
    Pause();
    return 0;
}
