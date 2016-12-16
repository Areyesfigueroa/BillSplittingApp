#ifndef PERSON_H
#define PERSON_H

#include <map>
#include <string>
#include "records.h"

class Person
{
    std::string name;
    std::string email;
    std::string phoneNum;

    std::map<std::string, float> billRecords;

public:
    Person();
    Person(std::string& name, std::string& email, std::string& phoneNum);
    void setPersonName(std::string&);
    void setPersonEmail(std::string&);
    void setPersonPhoneNum(std::string&);

    const std::string& getPersonName()const;
    const std::string& getPersonEmail()const;
    const std::string& getPersonPhoneNum()const;

    void addToBillRecords(std::string, float);
    float getBillByKey(std::string);
    void eraseBill(std::string);
protected:
    Records<Person*> peopleRecords;
};

#endif // PERSON_H
