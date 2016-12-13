#ifndef PERSON_H
#define PERSON_H

#include <string>
#include "records.h"

class Person
{
    std::string name;
    std::string email;
    std::string phoneNum;


public:
    Person();
    Person(std::string& name, std::string& email, std::string& phoneNum);
    void setPersonName(std::string&);
    void setPersonEmail(std::string&);
    void setPersonPhoneNum(std::string&);

    const std::string& getPersonName()const;
    const std::string& getPersonEmail()const;
    const std::string& getPersonPhoneNum()const;

protected:
    Records<Person*> peopleRecords;
};

#endif // PERSON_H
