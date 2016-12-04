#include "grouprecords.h"

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
    groupRecords.insert(groupPtr);
}

Group* GroupRecords::fetchLatestGroup()
{
    typedef std::set<Group*>::iterator it;
    it iterator;

    iterator = groupRecords.end();
    iterator--;
    return *iterator;

}

Group* GroupRecords::fetchGroupByIndex(int index)
{
    typedef std::set<Group*>::iterator it;
    it iterator;
    int counter = 0;
   //Iterate until you reach the index
    for(iterator = groupRecords.begin(); iterator != groupRecords.end(); iterator++)
    {
        if(counter != index)
        {
            counter++;
        }
        else
        {
            return *iterator; //dereferencing a pointer
        }
    }
    //Need to create a try catch block class to make sure if
    //counter does not match index and we go through the set to
    //return an exception, saying could not find the item you are looking for
}

void GroupRecords::setIndex(int index)
{
    this->index = index;
}

const int GroupRecords::getIndex() const
{
    return index;
}
