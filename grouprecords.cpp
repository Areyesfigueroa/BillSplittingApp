#include "grouprecords.h"
#include <iostream>
#include <algorithm>
#include <QTextStream>
#include <iterator>

//Default static value
int GroupRecords::index = 0;
GroupRecords* GroupRecords::_instance = 0;

GroupRecords::GroupRecords()
{
}

GroupRecords::~GroupRecords()
{
    delete this->_instance; //delete when object is destroyed
}

void GroupRecords::addGroup(Group* groupPtr)
{
    groupRecords.push_back(groupPtr);
}

Group* GroupRecords::fetchLatestGroup()
{
    return groupRecords.back();

}

Group* GroupRecords::fetchGroupByIndex(int index)
{
    return groupRecords[index];
}

void GroupRecords::setIndex(int index)
{
    this->index = index;
}

const int GroupRecords::getIndex() const
{
    return index;
}

bool GroupRecords::checkForDuplicates(const std::string& grpName)
{
    if(groupRecords.empty())
    {
        return false;
    }
    else
    {
        QTextStream out(stdout);

        size_t index = groupRecords.size() - 1;
        out << "Init Index: " <<index<<endl;
        //while they are not the same
        while(std::strcmp(groupRecords[index]->getName().c_str(), grpName.c_str()) != 0)
        {
            if(index != 0)
            {
                index--;
                out << groupRecords[index]->getName().c_str() << " != " << grpName.c_str()<<endl;
            }
            else
            {
                //if index is 0, break loop, could not find
                return false;
            }
        }
        out <<"They are the same!"<<endl;
        out << groupRecords[index]->getName().c_str() << " = " << grpName.c_str()<<endl;
        return true;
    }
}
