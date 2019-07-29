#pragma once

#include "includes.hpp"
#include "functionality.hpp"


class DataBase
{
public:

    DataBase(const char* username, const char* password)
    {
        
        strncpy(this->username, username, strlen(username));
        strncpy(this->password, password, strlen(password));
    }

    ~DataBase() { 	mysqlx_session_close(this->session); }

    int connect();
    int init();
    int build();

private: 
	mysqlx_session_t* session;
    mysqlx_error_t *err;
    char username[256];
    char password[256];
};

int initDB();
int initData();