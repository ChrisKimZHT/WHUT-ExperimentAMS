#ifndef EXPERIMENTAMS_STAT_SERVICE_H
#define EXPERIMENTAMS_STAT_SERVICE_H

#include "class.h"

int StatDataSave(); // ����ͳ��
int StatDataLoad(); // ��ȡͳ��
void StatUpdate(int, double, time_t= time(nullptr)); // ����ͳ�� 0-���� 1-ע�� 2-��ֵ 3-�˷� 4-����
void PrintStat(int, int, int); // ���ͳ��-����/��/��
void PrintStat(const YearMonthDay &, const YearMonthDay &); // ���ͳ��-������

#endif //EXPERIMENTAMS_STAT_SERVICE_H
