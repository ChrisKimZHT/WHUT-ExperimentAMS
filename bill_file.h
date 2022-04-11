#ifndef EXPERIMENTAMS_BILL_FILE_H
#define EXPERIMENTAMS_BILL_FILE_H

#include "class.h"

int BillFileSave(std::map<std::string, std::vector<Bill>> &); // 文件储存
int BillFileLoad(std::map<std::string, std::vector<Bill>> &); // 文件读取
void PriceFileSave(Price &); // 文件储存
void PriceFileLoad(Price &); // 文件读取

#endif //EXPERIMENTAMS_BILL_FILE_H
