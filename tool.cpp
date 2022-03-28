#include "tool.h"
#include "class.h"

using namespace std;

string Date2str(time_t date)
{
    tm *time = localtime(&date);
    char tmp[20];
    strftime(tmp, 20, "%Y-%m-%d %H:%M:%S", time);
    return tmp;
}

void Pause()
{
    system("pause");
}

void Clear()
{
    system("cls");
}

bool StrMatch(string s1, string s2) // s1-主串 s2-模式串
{
    vector<int> nxt(max(s1.size(), s2.size()) + 1); // 部分匹配表
    // 计算部分匹配表
    nxt[0] = -1;
    int i = 0, j = -1;
    int lens1 = s1.size(), lens2 = s2.size();
    while (i < lens2)
    {
        if (j == -1 || s2[i] == s2[j])
        {
            ++i;
            ++j;
            nxt[i] = j;
        }
        else
        {
            j = nxt[j];
        }
    }
    // KMP算法本体
    i = 0, j = 0;
    while (i < lens1 && j < lens2)
    {
        if (j == -1 || s1[i] == s2[j])
        {
            i++;
            j++;
        }
        else
        {
            j = nxt[j];
        }
    }
    if (j == lens2)
        return true;
    else
        return false;
}

bool InputCheck_YN(bool &var)
{
    string temp;
    cin >> temp;
    if (temp == "Y" || temp == "y")
    {
        var = true;
        return true;
    }
    else if (temp == "N" || temp == "n")
    {
        var = false;
        return true;
    }
    else
    {
        return false;
    }
}

bool InputCheck_Int(int &var, int lim_min, int lim_max)
{
    int temp;
    cin >> temp;
    if (cin.good())
    {
        if (temp >= lim_min && temp <= lim_max)
        {
            var = temp;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        cin.clear();
        cin.ignore(1024, '\n');
        return false;
    }
}

bool InputCheck_String(string &var, int lim_min, int lim_max)
{
    string temp;
    cin >> temp;
    if (temp.size() >= lim_min && temp.size() <= lim_max)
    {
        var = temp;
        return true;
    }
    else
    {
        return false;
    }
}

bool InputCheck_Double(double &var, double lim_min, double lim_max)
{
    double temp;
    cin >> temp;
    if (cin.good())
    {
        if (temp >= lim_min && temp <= lim_max)
        {
            var = temp;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        cin.clear();
        cin.ignore(1024, '\n');
        return false;
    }
}