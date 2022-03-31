#ifndef EXPERIMENTAMS_CARD_SERVICE_H
#define EXPERIMENTAMS_CARD_SERVICE_H

#include "class.h"

void SaveCard(const std::string &, const Card &); // ���濨
bool IsExist(const std::string &); // ��ѯ�Ƿ���ڸÿ�
void PrintCard(const std::string &, bool); // ����ÿ�
void PrintSimilarCard(const std::string &name); // ģ������ÿ�
void PrintAllCard(); // ������п�
bool PasswordCheck(const std::string &, const std::string &); // �����˺�������
int CheckLogin(const std::string &, const std::string &); // ��¼ 0-�ɹ� 1-������/�˺Ż�������� 2-�ѵ�¼ 3-����ע�� 4-�˵�δ����
int CheckLogoff(const std::string &, const std::string &); // �ǳ� 0-�ɹ� 1-������/�˺Ż�������� 2-�ѵǳ� 3-����ע��
bool Charge(const std::string &, const double &); // �շѣ����и�����⣩
void SetPaid(const std::string &); // ��������Ϊ�ѽ���
double GetBalance(const std::string &); // ��ѯ���
void UpdateBalance(const std::string &name, const double &val); // ������û�кϷ��Լ�⣩
bool IsSettled(const std::string &); // ��ѯ�Ƿ����
void DeleteCard(const std::string &); // ע����
int GetStatus(const std::string &); // ��ѯ��״̬
void SetPassword(const std::string &, const std::string &); // ��������
int CardDataSave(); // ���濨
int CardDataLoad(); // ��ȡ��

#endif //EXPERIMENTAMS_CARD_SERVICE_H
