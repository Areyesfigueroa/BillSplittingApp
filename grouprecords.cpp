#include "grouprecords.h"


GroupRecords *GroupRecords::r_instance = 0;

GroupRecords::GroupRecords()
{
}

GroupRecords::~GroupRecords()
{
    delete this->r_instance; //delete when object is destroyed
}
