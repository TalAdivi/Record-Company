#include <iostream>
#include <cstring>
#include <cstdlib>
#include "C:\Program Files\MySQL\Connector C++ 8.0\include\mysqlx\xapi.h"

using namespace std;

void printRes(mysqlx_result_t* res)
{
	if (NULL != res)
	{
		int64_t x;
		char buff[256];
		size_t size = 0;
		mysqlx_row_t* row;
		do
		{
			while( (row = mysqlx_row_fetch_one(res))!=NULL)
			{
				size = sizeof(buff);
				mysqlx_get_bytes(row, 0, 0, buff, &size);
				cout << buff << endl;
			}
			// //mysqlx_get_sint(row, 0, &x);

			
			// size = sizeof(buff);
			// row =  mysqlx_row_fetch_one(res); 
			// //mysqlx_get_sint(row, 0, &x);
			// mysqlx_get_bytes(row, 0, 0, buff, &size);
			// cout << buff << endl;

		} while (RESULT_OK == mysqlx_next_result(res));
	}
}

void initDB(){
	mysqlx_error_t *err;

	mysqlx_session_t* sess = mysqlx_get_session("localhost", DEFAULT_MYSQLX_PORT, "root", "59897", "", &err);

	if (NULL == sess) 
	{
	 	std::cout << mysqlx_error_message(err) << "\t" << sess << endl;
		exit(-1);
	}
	
	if (mysqlx_get_schema(sess, "RecordCompany", 1)) 
	{
		mysqlx_stmt_t* q2 = mysqlx_sql_new(sess, "DROP database `RecordCompany`", MYSQLX_NULL_TERMINATED);
		mysqlx_execute(q2);
	}

	mysqlx_stmt_t* q = mysqlx_sql_new(sess, "create database `RecordCompany`", MYSQLX_NULL_TERMINATED);
	mysqlx_execute(q);


	std::cout << "create !" << endl;
	getchar();

	mysqlx_session_close(sess);
	sess =  mysqlx_get_session("localhost", DEFAULT_MYSQLX_PORT, "root", "59897", "RecordCompany", &err);

	mysqlx_stmt_t* crQ = mysqlx_sql_new(sess, "CREATE TABLE `recordcompany`.`musican` ("\
  	"`id_Musican` INT NOT NULL AUTO_INCREMENT,"\
  	"`Name` VARCHAR(256) NOT NULL,"\
  	"`Address` VARCHAR(256) NOT NULL,"\
  	"`Phone` VARCHAR(256) NOT NULL,"\
  	"`Skill` VARCHAR(256) NOT NULL,"\
  	"PRIMARY KEY (`id_Musican`));", MYSQLX_NULL_TERMINATED);

	mysqlx_execute(crQ);

	crQ = mysqlx_sql_new(sess,"CREATE TABLE `recordcompany`.`instrumant` ("\
  	"`I_id` INT NOT NULL AUTO_INCREMENT,"\
  	"`Brand` VARCHAR(256) NOT NULL,"\
  	"`Type` VARCHAR(256) NOT NULL,"\
  	"PRIMARY KEY (`I_id`));", MYSQLX_NULL_TERMINATED);
	mysqlx_execute(crQ);

	crQ = mysqlx_sql_new(sess,"CREATE TABLE `recordcompany`.`track` ("\
	"`T_id` INT NOT NULL AUTO_INCREMENT,"\
	"`Name` VARCHAR(256) NOT NULL,"\
	"`Music_Compuser` VARCHAR(256) NULL,"\
	"`Length` INT NOT NULL,"\
	"`Lyrics_Composer` VARCHAR(256) NULL,"\
	"`Date` VARCHAR(256) NOT NULL,"\
	"`Genre` VARCHAR(256) NOT NULL,"\
	"`Technician` VARCHAR(256) NOT NULL,"\
	"PRIMARY KEY (`T_id`));", MYSQLX_NULL_TERMINATED);
	mysqlx_execute(crQ);

	crQ = mysqlx_sql_new(sess,"CREATE TABLE `recordcompany`.`album` ("\
	"`A_id` INT NOT NULL AUTO_INCREMENT,"\
	"`Name` VARCHAR(256) NOT NULL,"\
	"`S_Date` VARCHAR(256) NOT NULL,"\
	"`E_Date` VARCHAR(256) NOT NULL,"\
	"`Tracks_Number` INT NOT NULL,"\
	"PRIMARY KEY (`A_id`, `Tracks_Number`));", MYSQLX_NULL_TERMINATED);
	mysqlx_execute(crQ);

	crQ = mysqlx_sql_new(sess,"CREATE TABLE `recordcompany`.`producer` ("\
	"`p_ID` INT NOT NULL AUTO_INCREMENT,"\
	"`Name` VARCHAR(256) NOT NULL,"\
	"PRIMARY KEY (`p_ID`));", MYSQLX_NULL_TERMINATED);
	mysqlx_execute(crQ);

	crQ = mysqlx_sql_new(sess,"CREATE TABLE `recordcompany`.`instrumant` ("\
  	"`I_id` INT NOT NULL AUTO_INCREMENT,"\
  	"`Brand` VARCHAR(256) NOT NULL,"\
  	"`Type` VARCHAR(256) NOT NULL,"\
  	"PRIMARY KEY (`I_id`));", MYSQLX_NULL_TERMINATED);
	mysqlx_execute(crQ);

	std::cout << "new table ! !" << endl;
	getchar();
	
	mysqlx_stmt_t* q4 = mysqlx_sql_new(sess, "show tables;", MYSQLX_NULL_TERMINATED);
	mysqlx_result_t* res = mysqlx_execute(q4);
	//std::cout << mysqlx_json_fetch_one(res, NULL) << endl;

	printRes(res);

	// q4 = mysqlx_sql_new(sess, "select * from new_table;", MYSQLX_NULL_TERMINATED);
	// res = mysqlx_execute(q4);

	// printRes(res);

	mysqlx_session_close(sess);
}

int main(int argc, char *argv[])
{
	initDB();
	getchar();
	return 0;
}