#ifndef EXPERIMENTAMS_SERVICE_H
#define EXPERIMENTAMS_SERVICE_H

/* 用户功能 */
void CreatCard(); // 操作：创建
void QueryCard(); // 操作：查询
void Price(); // 操作：查看价格
void Login(); // 操作：上机
void Logoff(); // 操作：下机
void Deposit(); // 操作：充值
void Refund(); // 操作：退款
void QueryBill(); // 操作：账单
void Delete(); // 操作：注销
void Password(); // 操作：重设密码

/* 储存功能 */
void Load_All(); // 操作：初始化
void Save_All(); // 操作：保存并退出
void Save_Card(); // 仅保存卡
void Save_Bill(); // 仅保存账单
void Save_Price(); // 仅保存价格
void Save_Stat(); // 仅保存统计

/* 管理员功能 */
bool Admin_Login(const std::string &, const std::string &); // 管理员操作：登入
void Admin_Price(); // 管理员操作：设置价格
void Admin_Stat(); // 管理员操作：查看收益统计
void Admin_Card(); // 管理员操作：查看卡

#endif //EXPERIMENTAMS_SERVICE_H
