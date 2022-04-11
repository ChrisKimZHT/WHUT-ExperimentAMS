#ifndef EXPERIMENTAMS_BILL_SERVICE_H
#define EXPERIMENTAMS_BILL_SERVICE_H

#include "class.h"

void CreatBill(const std::string &, const int &); // �½��˵�-�ϻ��˵�
void CreatBill(const std::string &, const double &); // �½��˵�-�����˵�
std::pair<double, time_t> GetIncompleteBill(const std::string &name); // ��ȡδ���˵��۸�
void CompleteBill(const std::string &); // ��ɶ���
std::pair<int, int> GetNightRange(); // ��ȡ����
void PrintBill(const std::string &, int, int, int); // ��ӡ�˵�-����/��/��
void PrintBill(const std::string &, YearMonthDay, YearMonthDay); // ��ӡ�˵�--������
int BillDataSave(); // �����˵�
int BillDataLoad(); // ��ȡ�˵�
void PriceDataSave(); // ����۸�
void PriceDataLoad(); // ��ȡ�۸�
Price GetPrice(); // ��ȡ�۸�
Price ChangePrice(double, double, double, int, int); // �޸ļ۸�

#endif //EXPERIMENTAMS_BILL_SERVICE_H
