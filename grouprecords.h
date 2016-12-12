#ifndef GROUPRECORDS_H
#define GROUPRECORDS_H

#include "group.h"
#include "records.h"

class GroupRecords
{
    static GroupRecords *_instance;
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

    Records<Group*> groupRecords;

};



#endif // GROUPRECORDS_H
