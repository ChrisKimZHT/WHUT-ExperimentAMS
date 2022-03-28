#include <iostream>
#include "menu.h"

using namespace std;

int main()
{
    // 初始化
    Load_All();
    // 程序本体
    int select = -1;
    do
    {
        Index_Master();
        if (InputCheck_Int(select, 0, 4))
            Menu(select);
        else
            cout << "输入异常" << endl;
    } while (select);
    // 程序结束
    cout << "程序结束" << endl;
    Pause();
    return 0;
}
