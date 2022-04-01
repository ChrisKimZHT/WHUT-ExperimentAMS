#ifndef EXPERIMENTAMS_BILL_SERVICE_H
#define EXPERIMENTAMS_BILL_SERVICE_H

#include "class.h"

void CreatBill(const std::string &, const int &); // �½��˵�-�ϻ��˵�
void CreatBill(const std::string &, const double &); // �½��˵�-�����˵�
double GetIncompleteBill(const std::string &name); // ��ȡδ���˵��۸�
void CompleteBill(const std::string &); // ��ɶ���
std::pair<int, int> GetNightRange(); // ��ȡ����
void PrintBill(const std::string &); // ��ӡ�˵�
int BillDataSave(); // �����˵�
int BillDataLoad(); // ��ȡ�˵�
void PriceDataSave(); // ����۸�
void PriceDataLoad(); // ��ȡ�۸�
int StatDataSave(); // ����ͳ��
int StatDataLoad(); // ��ȡͳ��
Price GetPrice(); // ��ȡ�۸�
Price ChangePrice(double, double, double, int, int); // �޸ļ۸�
void StatUpdate(int, double, time_t= time(nullptr)); // ����ͳ�� 0-���� 1-ע�� 2-��ֵ 3-�˷� 4-����
void PrintStat(int, int, int); // ���ͳ��-����/��/��
void PrintStat(const YearMonthDay &, const YearMonthDay &); // ���ͳ��-������

#endif //EXPERIMENTAMS_BILL_SERVICE_H
