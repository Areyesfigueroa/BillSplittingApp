#include "group.h"

Group::Group(std::string& name, int size):groupName(name), groupSize(size)
{}

void Group::setGroupName(std::string& name)
{
    groupName = name;
}
void Group::setGroupSize(int size)
{
    groupSize = size;
}

const std::string& Group::getGroupName() const
{
    return groupName;
}
const int Group::getGroupSize() const
{
    return groupSize;
}
//Person functions
void Group::addPerson(Person* person)
{
    peopleRecords.addToRecords(person);
}

Person* Group::getLatestPerson()
{
    return peopleRecords.fetchLatestRecord();
}

int Group::getPeopleCount()
{
    return peopleRecords.getSize();
}

Person* Group::getPersonByIndex(int i)
{
    return peopleRecords.fetchRecordsByIndex(i);
}

