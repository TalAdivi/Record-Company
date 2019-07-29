#include "parsing.hpp"

Musician::Musician(mysqlx_row_t* row)
{
    int64_t x;
    char buff1[256]={0};
    char buff2[256]={0};
    char buff3[256]={0};
    char buff4[256]={0};
    size_t size = 0;
    
    size = sizeof(buff1);

    mysqlx_get_sint(row, 0, &x);
    this->id = x;

    mysqlx_get_bytes(row, 1, 0, buff1, &size);
    this->name = buff1;

    size = sizeof(buff2);    
    mysqlx_get_bytes(row, 2, 0, buff2, &size);
    this->address = buff2;
    
    size = sizeof(buff3);
    mysqlx_get_bytes(row, 3, 0, buff3, &size);
    this->phone = buff3;

    size = sizeof(buff4);
    mysqlx_get_bytes(row, 4, 0, buff4, &size);
    this->skill = buff4;
	
}

Instrument::Instrument(mysqlx_row_t* row)
{
    int64_t x;
    char buff1[256]={0};
    char buff2[256]={0};

    size_t size = 0;
    
    size = sizeof(buff1);

    mysqlx_get_sint(row, 0, &x);
    this->id = x;

    mysqlx_get_bytes(row, 1, 0, buff1, &size);
    this->brand = buff1;
    
    size = sizeof(buff2);    
    mysqlx_get_bytes(row, 2, 0, buff2, &size);
    this->type = buff2;
}

Producer::Producer(mysqlx_row_t* row)
{
    int64_t x;
    char buff1[256]={0};
    size_t size = 0;
    
    size = sizeof(buff1);

    mysqlx_get_sint(row, 0, &x);
    this->id = x;

    mysqlx_get_bytes(row, 1, 0, buff1, &size);
    this->name = buff1;
}

Album::Album(mysqlx_row_t* row)
{
    int64_t x;
    char buff1[256]={0};
    char buff2[256]={0};
    char buff3[256]={0};
    size_t size = 0;
    
    size = sizeof(buff1);

    mysqlx_get_sint(row, 0, &x);
    this->id = x;

    size = sizeof(buff1);
    mysqlx_get_bytes(row, 1, 0, buff1, &size);
    this->name = buff1;
    
    size = sizeof(buff2);
    mysqlx_get_bytes(row, 2, 0, buff2, &size);
    this->start = buff2;
    
    size = sizeof(buff3);
    mysqlx_get_bytes(row, 3, 0, buff3, &size);
    this->end = buff3;

    mysqlx_get_sint(row, 4, &x);
    this->tracks = x;   
}


std::ostream& operator<<(std::ostream& os, const Musician& ob)
{
    os << ob.toString();
    return os;
}

std::ostream& operator<<(std::ostream& os, const Instrument& ob)
{
    os << ob.toString();
    return os;
}

std::ostream& operator<<(std::ostream& os, const Producer& ob)
{
    os << ob.toString();
    return os;
}

std::ostream& operator<<(std::ostream& os, const Album& ob)
{
    os << ob.toString();
    return os;
}

