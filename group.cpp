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

void Group::addPerson(Person* person)
{
    peopleRecords.addToRecords(person);
}

Person* Group::getLastestPerson()
{
    return peopleRecords.fetchLatestRecord();
}
