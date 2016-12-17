#ifndef PEOPLERECORDS_H
#define PEOPLERECORDS_H

#include "person.h"
#include "records.h"

//FUTURE IMPLEMENTATION
//friend list instead of having to keep inputting the same user info.

class PeopleRecords
{
    static PeopleRecords *p_instance;
    PeopleRecords();
    ~PeopleRecords();
public:

    static PeopleRecords *instance()
    {
        if(!p_instance)
        {
            p_instance = new PeopleRecords();
        }
        return p_instance;
    }

    Records<Person*> peopleRecords;
};

#endif // PEOPLERECORDS_H
