#ifndef EXPERIMENTAMS_SERVICE_H
#define EXPERIMENTAMS_SERVICE_H

/* �û����� */
void CreatCard(); // ����������
void QueryCard(); // ��������ѯ
void Price(); // �������鿴�۸�
void Login(); // �������ϻ�
void Logoff(); // �������»�
void Deposit(); // ��������ֵ
void Refund(); // �������˿�
void QueryBill(); // �������˵�
void Delete(); // ������ע��
void Password(); // ��������������

/* ���湦�� */
void Load_All(); // ��������ʼ��
void Save_All(); // ���������沢�˳�
void Save_Card(); // �����濨
void Save_Bill(); // �������˵�
void Save_Price(); // ������۸�
void Save_Stat(); // ������ͳ��

/* ����Ա���� */
bool Admin_Login(const std::string &, const std::string &); // ����Ա����������
void Admin_Price(); // ����Ա���������ü۸�
void Admin_Stat(); // ����Ա�������鿴����ͳ��
void Admin_Card(); // ����Ա�������鿴��

#endif //EXPERIMENTAMS_SERVICE_H
