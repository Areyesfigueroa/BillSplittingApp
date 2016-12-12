#ifndef RECORDS_H
#define RECORDS_H

#include <vector>
#include <string>
#include "group.h"

template <class T>
class Records
{
std::vector<T> elements;

public:
   // Records();
   // ~Records();
    void addToRecords(T const&);
    T fetchRecordsByIndex(int index);
    T fetchLatestRecord() const;
    bool checkForDuplicates(const std::string&);
};


template<class T>
void Records<T>::addToRecords(T const& record)
{
    elements.push_back(record);
}

template<class T>
T Records<T>::fetchRecordsByIndex(int index)
{
    return elements[index];
}

template<class T>
T Records<T>::fetchLatestRecord() const
{
    if(elements.empty())
    {
        return elements.back();
    }
    return elements.back();
}

template<class T>
bool Records<T>::checkForDuplicates(const std::string& var)
{
    if(elements.empty())
    {
        return false;
    }
    else
    {
        size_t index = elements.size() - 1;

        while(std::strcmp(elements[index]->getName().c_str(), var.c_str()) != 0)
        {
            if(index != 0)
            {
                index--;
            }
            else
            {
                //if index is 0, break loop, could not find
                return false;
            }
        }
        return true;
    }
}


#endif // RECORDS_H
