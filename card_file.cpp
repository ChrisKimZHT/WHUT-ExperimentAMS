#include <string>
#include <fstream>
#include "card_file.h"

using namespace std;

int CardFileSave(linklist<Card> &CardData)
{
    int cnt = 0;
    ofstream CardDataFile;
    CardDataFile.open("./CardData.txt", ios::out);
    for (int i = 0; i < CardData.size(); i++)
    {
        CardDataFile << CardData[i];
        cnt++;
    }
    CardDataFile.close();
    return cnt;
}

int CardFileLoad(linklist<Card> &CardData)
{
    int cnt = 0;
    Card temp;
    ifstream CardDataFile;
    CardDataFile.open("./CardData.txt", ios::in);
    CardData.clear();
    while (CardDataFile >> temp)
    {
        CardData.push_front(temp);
        cnt++;
    }
    CardDataFile.close();
    return cnt;
}