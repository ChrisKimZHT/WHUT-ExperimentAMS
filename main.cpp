#include <iostream>
#include "menu.h"

using namespace std;

int main()
{
    // ��ʼ��
    Load_All();
    // ������
    int select = -1;
    do
    {
        Index_Master();
        if (InputCheck_Int(select, 0, 4))
            Menu(select);
        else
            cout << "�����쳣" << endl;
    } while (select);
    // �������
    cout << "�������" << endl;
    Pause();
    return 0;
}
