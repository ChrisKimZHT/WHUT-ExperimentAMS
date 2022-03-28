#include "card_file.h"

using namespace std;

int CardFileSave(map<string, Card> &CardData)
{
    int cnt = 0;
    ofstream CardDataFile;
    CardDataFile.open("./CardData.txt", ios::out);
    for (auto &card: CardData)
    {
        CardDataFile << card.second;
        cnt++;
    }
    CardDataFile.close();
    return cnt;
}

int CardFileLoad(map<string, Card> &CardData)
{
    int cnt = 0;
    Card temp;
    ifstream CardDataFile;
    CardDataFile.open("./CardData.txt", ios::in);
    CardData.clear();
    while (CardDataFile >> temp)
    {
        CardData[temp.Name()] = temp;
        cnt++;
    }
    CardDataFile.close();
    return cnt;
}