#include "grouprecords.h"

//Default static value
int GroupRecords::index = 0;
GroupRecords* GroupRecords::_instance = 0;


GroupRecords::GroupRecords()
{}

GroupRecords::~GroupRecords()
{
    delete this->_instance; //delete when object is destroyed
}

void GroupRecords::addGroup(Group* groupPtr)
{
    groupRecords.push_back(groupPtr);
}

Group* GroupRecords::fetchGroup(int index)
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
