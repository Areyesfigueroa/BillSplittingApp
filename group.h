#ifndef GROUP_H
#define GROUP_H

#include <string>
#include "records.h"
#include "person.h"

class Group
{
    static int grpIndex;
    std::string groupName;
    int groupSize;
public:
    Group(std::string&, int);
    void setName(std::string&);
    void setSize(int);

    Records<Person*> peopleGrp;

    const std::string& getName() const;
    const int getSize() const;
};

#endif // GROUP_H
