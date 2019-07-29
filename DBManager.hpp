#pragma once

#include "parsing.hpp"

class DataBase
{
public:
    DataBase(const char *username, const char *password)
    {
        strncpy(this->username, username, strlen(username));
        strncpy(this->password, password, strlen(password));

        this->username[strlen(username)] = '\0';
        this->password[strlen(password)] = '\0';
    }

    ~DataBase() { mysqlx_session_close(this->session); }

    int connect();
    int init();
    int build();
    int albumsBetween(std::string start, std::string end);
    int musicianSongBetween(std::string name);
    int musicianAlbumBetween(std::string name);
    int popularInstrument();
    int instrumentsInAlbum(std::string name);
    int producerOfAlbumBetween(std::string start, std::string end);
    int popularManufacterer();
    int amountMusicianThroughoutYears();
    int musicianCollaboratedMost();
    int popularGenre();
    int theMostTech(std::string start, std::string ends);
    int firstAlbum();
    int tracksInTwoAlbumsOrMore();
    int techniciansWorkedOnCompleteAlbum();
    int mostDiverseGenre();

private:
    mysqlx_session_t *session;
    mysqlx_error_t *err;
    char username[256];
    char password[256];
};
