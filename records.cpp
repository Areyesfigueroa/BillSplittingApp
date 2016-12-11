#include "records.h"
#include <QTextStream>

template <class T>
Records<T>::Records()
{
}

template <class T>
Records<T>::~Records()
{
    int index = 0;
    while(!elements.empty())
    {
        delete elements[index]; //freed memory
        records[index] = NULL; //pointing dangling pointer
        index++;
    }
}

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
        QTextStream out(stdout);

        size_t index = elements.size() - 1;
        out << "Init Index: " <<index<<endl;
        //while they are not the same
        while(std::strcmp(elements[index]->getName().c_str(), var.c_str()) != 0)
        {
            if(index != 0)
            {
                index--;
                out << elements[index]->getName().c_str() << " != " << var.c_str()<<endl;
            }
            else
            {
                //if index is 0, break loop, could not find
                return false;
            }
        }
        out <<"They are the same!"<<endl;
        out << elements[index]->getName().c_str() << " = " << var.c_str()<<endl;
        return true;
    }
}
