#ifndef EXPERIMENTAMS_CARD_SERVICE_H
#define EXPERIMENTAMS_CARD_SERVICE_H

#include <string>
#include "class.h"
#include <vector>
#include <map>
#include "card_file.h"

void SaveCard(const string &, const Card &); // 保存卡
bool IsExist(const string &); // 查询是否存在该卡
void PrintCard(const string &); // 输出该卡
void FuzzyPrintCard(const string &); // 模糊输出该卡
bool PasswordCheck(const string &, const string &); // 单纯账号密码检测
int CheckLogin(const string &, const string &); // 登录 0-成功 1-不存在/账号或密码错误 2-已登录 3-卡已注销 4-账单未结清
int CheckLogoff(const string &, const string &); // 登出 0-成功 1-不存在/账号或密码错误 2-已登出 3-卡已注销
bool Charge(const string &, const double &); // 收费（带有负数检测）
void SetPaid(const string &); // 将卡设置为已结清
double GetBalance(const string &); // 查询余额
void UpdateBalance(const string &name, const double &val); // 更新余额（没有合法性检测）
bool IsSettled(const string &); // 查询是否结清
void DeleteCard(const string &); // 注销卡
int GetStatus(const string &); // 查询卡状态
void SetPassword(const string &, const string &); // 重设密码
int CardDataSave(); // 保存卡
int CardDataLoad(); // 读取卡

#endif //EXPERIMENTAMS_CARD_SERVICE_H
