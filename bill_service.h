#ifndef EXPERIMENTAMS_BILL_SERVICE_H
#define EXPERIMENTAMS_BILL_SERVICE_H

#include <string>
#include "class.h"
#include <utility>
#include <vector>
#include <map>
#include "card_service.h"
#include "bill_file.h"

using namespace std;

void CreatBill(const string &, const int &); // 新建账单-上机账单
void CreatBill(const string &, const double &); // 新建账单-充退账单

double CompleteBill(const string &); // 结算账单

pair<int, int> GetNightRange(); // 获取定价

void PrintBill(const string &); // 打印账单

int BillDataSave(); // 保存账单

int BillDataLoad(); // 读取账单

void PriceDataSave(); // 保存价格

void PriceDataLoad(); // 读取价格

int StatDataSave(); // 保存统计

int StatDataLoad(); // 读取统计

Price GetPrice(); // 获取价格

Price ChangePrice(double, double, double, int, int); // 修改价格

void StatUpdate(int, double, time_t= time(nullptr)); // 更新统计 0-创卡 1-注销 2-储值 3-退费 4-消费

void PrintStat(int, int, int); // 输出统计-按年/月/日

void PrintStat(const YearMonthDay &, const YearMonthDay &); // 输出统计-按区域

#endif //EXPERIMENTAMS_BILL_SERVICE_H
