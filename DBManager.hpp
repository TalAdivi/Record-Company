#ifndef DBMANAGER_HPP
#define DBMANAGER_HPP

#include "includes.hpp"

char username[256];
char password[256];

int initDB();
int initData();
void printRes(mysqlx_result_t* res);

#endif //DBManager.hpp