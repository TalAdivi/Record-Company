#ifndef DBMANAGER_HPP
#define DBMANAGER_HPP

#include "includes.hpp"


int initDB();
int initData();
void printRes(mysqlx_result_t* res);

#endif //DBManager.hpp