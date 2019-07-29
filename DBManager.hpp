#pragma once

#include "parsing.hpp"

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
    int albumsBetween(std::string start, std::string end);
    int musicianSongBetween(std::string name);
    int musicianAlbumBetween(std::string name);
    int popularInstrument();

private: 
	mysqlx_session_t* session;
    mysqlx_error_t *err;
    char username[256];
    char password[256];
};
