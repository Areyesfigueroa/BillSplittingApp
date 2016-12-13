#include "person.h"

Person::Person()
{
    name = email = phoneNum = "";
}

Person::Person(std::string& name, std::string& email, std::string& phoneNum)
    :name(name), email(email), phoneNum(phoneNum)
{}

//setters
void Person::setPersonName(std::string& name)
{
    this->name = name;
}

void Person::setPersonEmail(std::string& email)
{
    this->email = email;
}
void Person::setPersonPhoneNum(std::string& phoneNum)
{
    this->phoneNum = phoneNum;
}

//getters
const std::string& Person::getPersonName()const
{
    return this->name;
}
const std::string& Person::getPersonEmail()const
{
    return this->email;
}
const std::string& Person::getPersonPhoneNum()const
{
    return this->phoneNum;
}
