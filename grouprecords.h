#ifndef GROUPRECORDS_H
#define GROUPRECORDS_H

#include "group.h"
#include <vector>
#include <set>
#include <iterator>
/*
This class is in charge of holding all of the groups in a map with an index
this will be done so that I can access the different groups when I need to make
changes.

key: groups Name
*/


class GroupRecords
{
    static int index;
    std::set<Group*> groupRecords;
    static GroupRecords *_instance;
    GroupRecords();
    ~GroupRecords();
public:
    void addGroup(Group*);
    Group* fetchGroupByIndex(int);
    Group* fetchLatestGroup();
    const int getIndex()const;
    void setIndex(int index);
    static GroupRecords *instance()
    {
        if(!_instance)
        {
            _instance = new GroupRecords();
        }
        return _instance;
    }
};

#endif // GROUPRECORDS_H
