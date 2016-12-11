#ifndef GROUPRECORDS_H
#define GROUPRECORDS_H

#include "group.h"
#include "records.h"
#include <vector>
#include <set>
/*
This class is in charge of holding all of the groups in a map with an index
this will be done so that I can access the different groups when I need to make
changes.

key: groups Name
*/


class GroupRecords
{
    static GroupRecords *_instance;
    Records<Group*> groupRecords;
    GroupRecords();
    ~GroupRecords();
public:

    static GroupRecords *instance()
    {
        if(!_instance)
        {
            _instance = new GroupRecords();
        }
        return _instance;
    }

    Records<Group*> getRecords() const;

};

#endif // GROUPRECORDS_H
