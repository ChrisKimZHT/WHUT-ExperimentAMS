#ifndef EXPERIMENTAMS_STAT_FILE_H
#define EXPERIMENTAMS_STAT_FILE_H

#include "class.h"

int StatFileSave(std::map<YearMonthDay, Stat> &); // �ļ�����
int StatFileLoad(std::map<YearMonthDay, Stat> &); // �ļ���ȡ

#endif //EXPERIMENTAMS_STAT_FILE_H
