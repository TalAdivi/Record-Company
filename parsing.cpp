#include "parsing.hpp"

template<typename T>
std::vector<T*> initArray(mysqlx_result_t*)
{
    std::vector<T*> v;

    mysqlx_row_t* row;
    do
    {
        while( (row = mysqlx_row_fetch_one(res))!=NULL)
        {
            v.push_back(new T(row));
        }
    } while (RESULT_OK == mysqlx_next_result(res));
    mysqlx_result_free(res);

    return v;
}

Musician::Musician(mysqlx_row_t* row)
{
    int64_t x;
    char buff[256];
    size_t size = 0;
    
    size = sizeof(buff);

    mysqlx_get_sint(row, 0, &x);
    this->id = x;

    mysqlx_get_bytes(row, 1, 0, buff, &size);
    this->name = buff;
    
    mysqlx_get_bytes(row, 2, 0, buff, &size);
    this->address = buff;
    
    mysqlx_get_bytes(row, 3, 0, buff, &size);
    this->phone = buff;

    mysqlx_get_bytes(row, 4, 0, buff, &size);
    this->skill = buff;
	
}

Instrument::Instrument(mysqlx_row_t* row)
{
    int64_t x;
    char buff[256];
    size_t size = 0;
    
    size = sizeof(buff);

    mysqlx_get_sint(row, 0, &x);
    this->id = x;

    mysqlx_get_bytes(row, 1, 0, buff, &size);
    this->brand = buff;
    
    mysqlx_get_bytes(row, 2, 0, buff, &size);
    this->type = buff;
}

Producer::Producer(mysqlx_row_t* row)
{
    int64_t x;
    char buff[256];
    size_t size = 0;
    
    size = sizeof(buff);

    mysqlx_get_sint(row, 0, &x);
    this->id = x;

    mysqlx_get_bytes(row, 1, 0, buff, &size);
    this->name = buff;
}

Album::Album(mysqlx_row_t* row)
{
    int64_t x;
    char buff[256];
    size_t size = 0;
    
    size = sizeof(buff);

    mysqlx_get_sint(row, 0, &x);
    this->id = x;

    mysqlx_get_bytes(row, 1, 0, buff, &size);
    this->name = buff;
    
    mysqlx_get_bytes(row, 2, 0, buff, &size);
    this->start = buff;
    
    mysqlx_get_bytes(row, 3, 0, buff, &size);
    this->end = buff;

    mysqlx_get_sint(row, 4, &x);
    this->tracks = x;   
}
