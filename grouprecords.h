#ifndef GROUPRECORDS_H
#define GROUPRECORDS_H

#include "group.h"
#include "records.h"

class GroupRecords
{
    static GroupRecords *r_instance;
    GroupRecords();
    ~GroupRecords();
public:

    static GroupRecords *instance()
    {
        if(!r_instance)
        {
            r_instance = new GroupRecords();
        }
        return r_instance;
    }

    Records<Group*> groupRecords;
};
#endif // GROUPRECORDS_H
