#include "group.h"

Group::Group(std::string& name, int size):groupName(name), groupSize(size)
{}

void Group::setName(std::string& name)
{
    groupName = name;
}
void Group::setSize(int size)
{
    groupSize = size;
}

const std::string& Group::getName() const
{
    return groupName;
}
const int Group::getSize() const
{
    return groupSize;
}

void Group::addPerson(Person* person)
{
    peopleRecords.addToRecords(person);
}
