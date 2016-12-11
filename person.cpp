#include "person.h"

Person::Person()
{
    name = email = phoneNum = "";
}

Person::Person(std::string& name, std::string& email, std::string& phoneNum)
    :name(name), email(email), phoneNum(phoneNum)
{}

//setters
void Person::setName(std::string& name)
{
    this->name = name;
}

void Person::setEmail(std::string& email)
{
    this->email = email;
}
void Person::setPhoneNum(std::string& phoneNum)
{
    this->phoneNum = phoneNum;
}

//getters
const std::string& Person::getName()const
{
    return this->name;
}
const std::string& Person::getEmail()const
{
    return this->email;
}
const std::string& Person::getPhoneNum()const
{
    return this->phoneNum;
}
