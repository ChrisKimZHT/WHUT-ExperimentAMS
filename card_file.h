#ifndef EXPERIMENTAMS_CARD_FILE_H
#define EXPERIMENTAMS_CARD_FILE_H

#include <fstream>
#include <map>
#include <string>
#include "class.h"

int CardFileSave(map<string, Card> &); // 文件储存

int CardFileLoad(map<string, Card> &); // 文件读取

#endif //EXPERIMENTAMS_CARD_FILE_H
