#ifndef RECORDS_H
#define RECORDS_H

#include <vector>
#include <string>
#include <cstdlib>
template <class T>
class Records
{
std::vector<T> elements;

public:
    Records();
    ~Records();
    void addToRecords(const T);
    T fetchRecordsByIndex(int);
    T fetchLatestRecord();
    bool checkForDuplicates(const std::string&);
};

#endif // RECORDS_H
