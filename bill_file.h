#ifndef EXPERIMENTAMS_BILL_FILE_H
#define EXPERIMENTAMS_BILL_FILE_H

#include "class.h"

int BillFileSave(std::map<std::string, std::vector<Bill>> &); // �ļ�����
int BillFileLoad(std::map<std::string, std::vector<Bill>> &); // �ļ���ȡ
void PriceFileSave(Price &); // �ļ�����
void PriceFileLoad(Price &); // �ļ���ȡ

#endif //EXPERIMENTAMS_BILL_FILE_H
