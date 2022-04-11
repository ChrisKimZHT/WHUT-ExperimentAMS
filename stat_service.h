#ifndef EXPERIMENTAMS_STAT_SERVICE_H
#define EXPERIMENTAMS_STAT_SERVICE_H

#include "class.h"

int StatDataSave(); // 保存统计
int StatDataLoad(); // 读取统计
void StatUpdate(int, double, time_t= time(nullptr)); // 更新统计 0-创卡 1-注销 2-储值 3-退费 4-消费
void PrintStat(int, int, int); // 输出统计-按年/月/日
void PrintStat(const YearMonthDay &, const YearMonthDay &); // 输出统计-按区域

#endif //EXPERIMENTAMS_STAT_SERVICE_H
