#pragma once

#include "includes.hpp"

class Musician
{
public:
    Musician(mysqlx_row_t *);
    ~Musician() {}

    int getID() const { return this->id; }
    std::string getName() const { return this->name; }
    std::string getAddress() const { return this->address; }
    std::string getPhone() const { return this->phone; }
    std::string getSkill() const { return this->skill; }

    std::string toString() const
    {
        std::stringstream os;
        os << this->id << ", " << this->name << ", " << this->address + ", " << this->phone << ", " << this->skill;
        return os.str();
    }

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
    Instrument(mysqlx_row_t *);
    ~Instrument() {}

    int getID() const { return this->id; }
    std::string getBrand() const { return this->brand; }
    std::string getType() const { return this->type; }

    std::string toString() const
    {
        std::stringstream os;
        os << this->id << ", " << this->brand << ", " << this->type;
        return os.str();
    }

private:
    int id;
    std::string brand;
    std::string type;
};

class Producer
{
public:
    Producer(mysqlx_row_t *);
    ~Producer() {}

    int getID() const { return this->id; }
    std::string getName() const { return this->name; }

    std::string toString() const
    {
        std::stringstream os;
        os << this->id << ", " << this->name;
        return os.str();
    }

private:
    int id;
    std::string name;
};

class Album
{
public:
    Album(mysqlx_row_t *);
    ~Album() {}

    int getID() const { return this->id; }
    std::string getName() const { return this->name; }
    std::string getStartDate() const { return this->start; }
    std::string getEndDate() const { return this->end; }
    int getTracks() const { return this->tracks; }

    std::string toString() const
    {
        std::stringstream os;
        os << this->id << ", " << this->name << ", " << this->start + ", " << this->end << ", " << tracks;
        return os.str();
    }

private:
    int id;
    std::string name;
    std::string start;
    std::string end;
    int tracks;
};

class Track
{
public:
    Track(mysqlx_row_t *);
    ~Track() {}

    int getID() const { return this->id; }
    std::string getName() const { return this->name; }
    std::string getComposer() const { return this->composer; }
    int getLength() const { return this->length; }
    std::string getLyrics() const { return this->lyrics; }
    std::string getDate() const { return this->date; }
    std::string getGenre() const { return this->genre; }
    std::string getTech() const { return this->tech; }

    std::string toString() const
    {
        std::stringstream os;
        os << this->id << ", " << this->name << ", " << this->composer << ", " << this->length << ", " << this->lyrics << ", " << this->date << ", " << this->genre << ", " << this->tech;
        return os.str();
    }

private:
    int id;
    std::string name;
    std::string composer;
    int length;
    std::string lyrics;
    std::string date;
    std::string genre;
    std::string tech;
};

std::ostream &operator<<(std::ostream &os, const Musician &ob);
std::ostream &operator<<(std::ostream &os, const Instrument &ob);
std::ostream &operator<<(std::ostream &os, const Producer &ob);
std::ostream &operator<<(std::ostream &os, const Album &ob);
std::ostream &operator<<(std::ostream &os, const Track &ob);
template <typename T>
std::vector<T *> initArray(mysqlx_result_t *res)
{
    std::vector<T *> v;

    mysqlx_row_t *row;
    do
    {
        while ((row = mysqlx_row_fetch_one(res)) != NULL)
        {
            v.push_back(new T(row));
        }
    } while (RESULT_OK == mysqlx_next_result(res));

    return v;
}