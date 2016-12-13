#ifndef GROUPRECORDS_H
#define GROUPRECORDS_H

#include <map>
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
    Records<Group*> groupRecords; //will handle the duplicate checking, can be deleted once all is complete
};
#endif // GROUPRECORDS_H
