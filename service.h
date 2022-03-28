#ifndef EXPERIMENTAMS_SERVICE_H
#define EXPERIMENTAMS_SERVICE_H

#include <iostream>
#include "class.h"
#include "card_service.h"
#include "tool.h"
#include "bill_service.h"
#include "global_var.h"

using namespace std;

void CreatCard(); // ����������

void QueryCard(bool); // ��������ѯ

void Price(); // �������鿴�۸�

void Login(); // �������ϻ�

void Logoff(); // �������»�

void Deposit(); // ��������ֵ

void Refund(); // �������˿�

void QueryBill(); // �������˵�

void Delete(); // ������ע��

void Password(); // ��������������

void Load_All(); // ��������ʼ��

void Save_All(); // ���������沢�˳�

void Save_Card(); // �����濨

void Save_Bill(); // �������˵�

void Save_Price(); // ������۸�

void Save_Stat(); // ������ͳ��

bool Admin_Login(const string &, const string &); // ����Ա����������

void Admin_Price(); // ����Ա���������ü۸�

void Admin_Stat(); // ����Ա�������鿴����ͳ��

#endif //EXPERIMENTAMS_SERVICE_H
