#ifndef EXPERIMENTAMS_CARD_FILE_H
#define EXPERIMENTAMS_CARD_FILE_H

#include "class.h"

int CardFileSave(std::map<std::string, Card> &); // 文件储存
int CardFileLoad(std::map<std::string, Card> &); // 文件读取

#endif //EXPERIMENTAMS_CARD_FILE_H
