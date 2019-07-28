#pragma once

#include "includes.hpp"

template <typename T>
std::vector<T*> initArray(mysqlx_result_t*);

class Musician
{
public:
    Musician(mysqlx_row_t*);
    ~Musician();

    int getID() const { return this->id; }
    std::string getName() const { return this->name; }
    std::string getAddress() const { return this->address; }
    std::string getPhone() const { return this->phone; }
    std::string getSkill() const { return this->skill; }

private:
    int id;
    std::string name;
    std::string address;
    std::string phone;
    std::string skill;
};

class Instrument
{
public:
    Instrument(mysqlx_row_t*);
    ~Instrument();

    int getID() const { return this->id; }
    std::string getBrand() const { return this->brand; }
    std::string getType() const { return this->type; }

private:
    int id;
    std::string brand;
    std::string type;
};

class Producer
{
public:
    Producer(mysqlx_row_t*);
    ~Producer();

    int getID() const { return this->id; }
    std::string getName() const { return this->name; }

private:
    int id;
    std::string name;
};

class Album
{
public:
    Album(mysqlx_row_t*);
    ~Album();

    int getID() const { return this->id; }
    std::string getName() const { return this->name; }
    std::string getStartDate() const { return this->start; }
    std::string getEndDate() const { return this->end; }
    int getTracks() const { return this->tracks; }

private:
    int id;
    std::string name;
    std::string start;
    std::string end;
    int tracks;
};

