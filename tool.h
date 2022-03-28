#ifndef EXPERIMENTAMS_TOOL_H
#define EXPERIMENTAMS_TOOL_H

#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <cfloat>
//#include "class.h"

using namespace std;

string Date2str(time_t); // 将time_t转换为YYYY/MM/DD HH:MM:SS的string类型

void Pause(); // 暂停

void Clear(); // 清屏

bool StrMatch(string, string); // KMP算法-字符串匹配

bool InputCheck_YN(bool &); // 输入合法性检测-YN

bool InputCheck_Int(int &, int= INT32_MIN, int= INT32_MAX); // 输入合法性检测-整型

bool InputCheck_String(string &, int, int); // 输入合法性检测-字符串

bool InputCheck_Double(double &, double= DBL_MIN, double= DBL_MAX); // 输入合法性检测-双精度浮点型

#endif //EXPERIMENTAMS_TOOL_H
