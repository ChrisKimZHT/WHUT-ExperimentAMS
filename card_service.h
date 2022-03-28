#ifndef EXPERIMENTAMS_CARD_SERVICE_H
#define EXPERIMENTAMS_CARD_SERVICE_H

#include <string>
#include "class.h"
#include <vector>
#include <map>
#include "card_file.h"

void SaveCard(const string &, const Card &); // ���濨
bool IsExist(const string &); // ��ѯ�Ƿ���ڸÿ�
void PrintCard(const string &); // ����ÿ�
void FuzzyPrintCard(const string &); // ģ������ÿ�
bool PasswordCheck(const string &, const string &); // �����˺�������
int CheckLogin(const string &, const string &); // ��¼ 0-�ɹ� 1-������/�˺Ż�������� 2-�ѵ�¼ 3-����ע�� 4-�˵�δ����
int CheckLogoff(const string &, const string &); // �ǳ� 0-�ɹ� 1-������/�˺Ż�������� 2-�ѵǳ� 3-����ע��
bool Charge(const string &, const double &); // �շѣ����и�����⣩
void SetPaid(const string &); // ��������Ϊ�ѽ���
double GetBalance(const string &); // ��ѯ���
void UpdateBalance(const string &name, const double &val); // ������û�кϷ��Լ�⣩
bool IsSettled(const string &); // ��ѯ�Ƿ����
void DeleteCard(const string &); // ע����
int GetStatus(const string &); // ��ѯ��״̬
void SetPassword(const string &, const string &); // ��������
int CardDataSave(); // ���濨
int CardDataLoad(); // ��ȡ��

#endif //EXPERIMENTAMS_CARD_SERVICE_H
