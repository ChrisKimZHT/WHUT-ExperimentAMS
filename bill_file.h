#ifndef EXPERIMENTAMS_BILL_FILE_H
#define EXPERIMENTAMS_BILL_FILE_H

#include <fstream>
#include <map>
#include <string>
#include "class.h"

int BillFileSave(map<string, vector<Bill>> &); // �ļ�����

int BillFileLoad(map<string, vector<Bill>> &); // �ļ���ȡ

void PriceFileSave(Price &); // �ļ�����

void PriceFileLoad(Price &); // �ļ���ȡ

int StatFileSave(map<YearMonthDay, Stat> &); // �ļ�����

int StatFileLoad(map<YearMonthDay, Stat> &); // �ļ���ȡ

#endif //EXPERIMENTAMS_BILL_FILE_H
