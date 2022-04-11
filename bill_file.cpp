#include <vector>
#include <fstream>
#include <map>
#include <string>
#include "bill_file.h"

using namespace std;

int BillFileSave(map<string, vector<Bill>> &BillData)
{
    int cnt = 0;
    ofstream StatDataFile;
    StatDataFile.open("./BillData.txt", ios::out);
    for (auto &vec: BillData)
    {
        for (auto &bill: vec.second)
        {
            StatDataFile << bill;
            cnt++;
        }
    }
    StatDataFile.close();
    return cnt;
}

int BillFileLoad(map<string, vector<Bill>> &BillData)
{
    int cnt = 0;
    Bill temp;
    ifstream StatDataFile;
    StatDataFile.open("./BillData.txt", ios::in);
    BillData.clear();
    while (StatDataFile >> temp)
    {
        BillData[temp.GetName()].push_back(temp);
        cnt++;
    }
    StatDataFile.close();
    return cnt;
}

void PriceFileSave(Price &PriceData)
{
    ofstream PriceDataFile;
    PriceDataFile.open("./PriceData.txt", ios::out);
    PriceDataFile << PriceData;
    PriceDataFile.close();
}

void PriceFileLoad(Price &PriceData)
{
    ifstream PriceDataFile;
    PriceDataFile.open("./PriceData.txt", ios::in);
    PriceDataFile >> PriceData;
    PriceDataFile.close();
}