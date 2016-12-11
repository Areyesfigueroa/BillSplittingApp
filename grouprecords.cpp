#include "grouprecords.h"
#include <algorithm>
#include <QTextStream>
#include <iterator>

GroupRecords* GroupRecords::_instance = 0;

GroupRecords::GroupRecords()
{
}

GroupRecords::~GroupRecords()
{
    delete this->_instance; //delete when object is destroyed
}

Records<Group*> GroupRecords::getRecords() const
{
    return groupRecords;
}
