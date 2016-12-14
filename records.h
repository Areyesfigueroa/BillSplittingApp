#ifndef RECORDS_H
#define RECORDS_H

#include <vector>
#include <string>

template <class T>
class Records
{
std::vector<T> elements;

public:
   // Records();
   // ~Records();
    void addToRecords(const T record);
    T fetchRecordsByIndex(int index);
    T fetchLatestRecord();
    bool checkForDuplicates(const std::string&);
    size_t getSize();
    bool isEmpty();
};


template<class T>
void Records<T>::addToRecords(const T record)
{
    elements.push_back(record);
}

template<class T>
T Records<T>::fetchRecordsByIndex(int index)
{
    return elements[index];
}

template<class T>
T Records<T>::fetchLatestRecord()
{
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

        while(std::strcmp(elements[index]->getGroupName().c_str(), var.c_str()) != 0)
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

template<class T>
size_t Records<T>::getSize()
{
    return elements.size();
}

template<class T>
bool Records<T>::isEmpty()
{
    return elements.empty();
}

#endif // RECORDS_H
