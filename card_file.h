#ifndef EXPERIMENTAMS_CARD_FILE_H
#define EXPERIMENTAMS_CARD_FILE_H

#include <fstream>
#include <map>
#include <string>
#include "class.h"

int CardFileSave(map<string, Card> &); // �ļ�����

int CardFileLoad(map<string, Card> &); // �ļ���ȡ

#endif //EXPERIMENTAMS_CARD_FILE_H
