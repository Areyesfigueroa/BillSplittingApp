#ifndef GROUP_H
#define GROUP_H

#include <string>
#include "records.h"
#include "person.h"

/*
This class is in charge of storing group information
it will be stored on the heap with multiple instances
Will store and edit:
groupNames
groupSizes
*/

class Group : protected Person
{
    std::string groupName;
    int groupSize;

public:
    Group(std::string&, int);
    void setGroupName(std::string&);
    void setGroupSize(int);
    void addPerson(Person*);
    Person* getLastestPerson();


    const std::string& getGroupName() const;
    const int getGroupSize() const;

};

#endif // GROUP_H
