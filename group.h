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

class Group : public Person
{
    std::string groupName;
    int groupSize;

public:
    Group(std::string&, int);
    void setName(std::string&);
    void setSize(int);
    void addPerson(Person*);

    const std::string& getName() const;
    const int getSize() const;

};

#endif // GROUP_H
