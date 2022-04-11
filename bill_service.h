#ifndef EXPERIMENTAMS_BILL_SERVICE_H
#define EXPERIMENTAMS_BILL_SERVICE_H

#include "class.h"

void CreatBill(const std::string &, const int &); // 新建账单-上机账单
void CreatBill(const std::string &, const double &); // 新建账单-充退账单
std::pair<double, time_t> GetIncompleteBill(const std::string &name); // 获取未结账单价格
void CompleteBill(const std::string &); // 完成订单
std::pair<int, int> GetNightRange(); // 获取定价
void PrintBill(const std::string &, int, int, int); // 打印账单-按年/月/日
void PrintBill(const std::string &, YearMonthDay, YearMonthDay); // 打印账单--按区域
int BillDataSave(); // 保存账单
int BillDataLoad(); // 读取账单
void PriceDataSave(); // 保存价格
void PriceDataLoad(); // 读取价格
Price GetPrice(); // 获取价格
Price ChangePrice(double, double, double, int, int); // 修改价格

#endif //EXPERIMENTAMS_BILL_SERVICE_H
