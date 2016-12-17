#include "peoplerecords.h"

PeopleRecords *PeopleRecords::p_instance = 0;

PeopleRecords::PeopleRecords()
{
}

PeopleRecords::~PeopleRecords()
{
    delete this->p_instance;
}
