#ifndef EXPERIMENTAMS_CARD_FILE_H
#define EXPERIMENTAMS_CARD_FILE_H

#include "linklist.h"
#include "class.h"

int CardFileSave(linklist<Card> &); // 文件储存
int CardFileLoad(linklist<Card> &); // 文件读取

#endif //EXPERIMENTAMS_CARD_FILE_H
