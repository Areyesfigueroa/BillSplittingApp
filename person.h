#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person
{
    std::string name;
    std::string email;
    std::string phoneNum;
public:
    Person();
    Person(std::string& name, std::string& email, std::string& phoneNum);
    void setName(std::string&);
    void setEmail(std::string&);
    void setPhoneNum(std::string&);

    const std::string& getName()const;
    const std::string& getEmail()const;
    const std::string& getPhoneNum()const;
};

#endif // PERSON_H
