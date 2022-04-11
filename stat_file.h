#ifndef EXPERIMENTAMS_STAT_FILE_H
#define EXPERIMENTAMS_STAT_FILE_H

#include "class.h"

int StatFileSave(std::map<YearMonthDay, Stat> &); // 文件储存
int StatFileLoad(std::map<YearMonthDay, Stat> &); // 文件读取

#endif //EXPERIMENTAMS_STAT_FILE_H
