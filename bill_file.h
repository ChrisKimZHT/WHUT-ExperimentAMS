#ifndef EXPERIMENTAMS_BILL_FILE_H
#define EXPERIMENTAMS_BILL_FILE_H

#include <fstream>
#include <map>
#include <string>
#include "class.h"

int BillFileSave(map<string, vector<Bill>> &); // 文件储存

int BillFileLoad(map<string, vector<Bill>> &); // 文件读取

void PriceFileSave(Price &); // 文件储存

void PriceFileLoad(Price &); // 文件读取

int StatFileSave(map<YearMonthDay, Stat> &); // 文件储存

int StatFileLoad(map<YearMonthDay, Stat> &); // 文件读取

#endif //EXPERIMENTAMS_BILL_FILE_H
