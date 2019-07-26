#include <iostream>
#include <cstring>
#include <cstdlib>
#include "C:\Program Files\MySQL\Connector C++ 8.0\include\mysqlx\xapi.h"

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
			//to read value from row where only has 1 col and its a text
			while( (row = mysqlx_row_fetch_one(res))!=NULL)
			{
				size = sizeof(buff);
				mysqlx_get_bytes(row, 0, 0, buff, &size);
				std::cout << buff << std::endl;
			}

			//to read value from row where has 2 colums first signed int and second is a text
			// while( (row = mysqlx_row_fetch_one(res))!=NULL)
			// {
			// 	size = sizeof(buff);
			// 	row =  mysqlx_row_fetch_one(res); 
			// 	mysqlx_get_sint(row, 0, &x);
			// 	mysqlx_get_bytes(row, 1, 0, buff, &size);
			// 	std::cout << x << ", "<< buff << std::endl;
			// }
		} while (RESULT_OK == mysqlx_next_result(res));
	}
	mysqlx_result_free(res);
}

void initDB(char* username, char* password)
{
	mysqlx_error_t *err;
	mysqlx_stmt_t* query;
	mysqlx_result_t* result;
	mysqlx_session_t* session = mysqlx_get_session("localhost", DEFAULT_MYSQLX_PORT, username, password, "", &err);

	if (NULL == session) 
	{
	 	std::cout << mysqlx_error_message(err) << "\t" << session << std::endl;
		exit(mysqlx_error_num(err));
	}
	
	//if database exists drop it and create it 
	if (mysqlx_get_schema(session, "RecordCompany", 1)) 
	{
		query = mysqlx_sql_new(session, "DROP database `RecordCompany`", MYSQLX_NULL_TERMINATED);
		if( (result = mysqlx_execute(query)) == NULL)
		{
			std::cout<< "There was an error with DB initlization" << std::endl;
			std::cout << mysqlx_error_message(err) << "\t" << session << std::endl;
			mysqlx_session_close(session);
			exit(mysqlx_error_num(err));
		}	
	}

	
	std::cout << "1" << std::endl;
	getchar();

	query = mysqlx_sql_new(session, "create database `RecordCompany`", MYSQLX_NULL_TERMINATED);

	if( (result = mysqlx_execute(query)) == NULL)
	{
		std::cout<< "There was an error with DB initlization" << std::endl;
	 	std::cout << mysqlx_error_message(err) << "\t" << session << std::endl;
		mysqlx_session_close(session);
		exit(mysqlx_error_num(err));
	}

	mysqlx_session_close(session);

	session =  mysqlx_get_session("localhost", DEFAULT_MYSQLX_PORT, username, password, "RecordCompany", &err);
	
	if (NULL == session) 
	{
	 	std::cout << mysqlx_error_message(err) << "\t" << session << std::endl;
		exit(mysqlx_error_num(err));
	}

	std::cout << "2" << std::endl;
	getchar();

	//create the main tables 

	query = mysqlx_sql_new(session, "CREATE TABLE `recordcompany`.`musican` (\
  `id_Musican` INT NOT NULL AUTO_INCREMENT,\
  `Name` VARCHAR(256) NOT NULL,\
  `Address` VARCHAR(256) NOT NULL,\
  `Phone` VARCHAR(256) NOT NULL,\
  `Skill` VARCHAR(256) NOT NULL,\
  PRIMARY KEY (`id_Musican`));", MYSQLX_NULL_TERMINATED);

	if( (result = mysqlx_execute(query)) == NULL)
	{
		std::cout<< "There was an error with DB initlization" << std::endl;
	 	std::cout << mysqlx_error_message(err) << "\t" << session << std::endl;
		mysqlx_session_close(session);
		exit(mysqlx_error_num(err));
	}

	query = mysqlx_sql_new(session,"CREATE TABLE `recordcompany`.`instrumant` (\
  `I_id` INT NOT NULL AUTO_INCREMENT,\
  `Brand` VARCHAR(256) NOT NULL,\
  `Type` VARCHAR(256) NOT NULL,\
  PRIMARY KEY (`I_id`));", MYSQLX_NULL_TERMINATED);

	if( (result = mysqlx_execute(query)) == NULL)
	{
		std::cout<< "There was an error with DB initlization" << std::endl;
	 	std::cout << mysqlx_error_message(err) << "\t" << session << std::endl;
		mysqlx_session_close(session);
		exit(mysqlx_error_num(err));
	}

	query = mysqlx_sql_new(session,"CREATE TABLE `recordcompany`.`track` (\
  `T_id` INT NOT NULL AUTO_INCREMENT,\
  `Name` VARCHAR(256) NOT NULL,\
  `Music_Compuser` VARCHAR(256) NULL,\
  `Length` INT NOT NULL,\
  `Lyrics_Composer` VARCHAR(256) NULL,\
  `Date` VARCHAR(256) NOT NULL,\
  `Genre` VARCHAR(256) NOT NULL,\
  `Technician` VARCHAR(256) NOT NULL,\
  PRIMARY KEY (`T_id`));", MYSQLX_NULL_TERMINATED);

	if( (result = mysqlx_execute(query)) == NULL)
	{
		std::cout<< "There was an error with DB initlization" << std::endl;
	 	std::cout << mysqlx_error_message(err) << "\t" << session << std::endl;
		mysqlx_session_close(session);
		exit(mysqlx_error_num(err));
	}

	query = mysqlx_sql_new(session,"CREATE TABLE `recordcompany`.`album` (\
  `A_id` INT NOT NULL AUTO_INCREMENT,\
  `Name` VARCHAR(256) NOT NULL,\
  `S_Date` VARCHAR(256) NOT NULL,\
  `E_Date` VARCHAR(256) NOT NULL,\
  `Tracks_Number` INT NOT NULL,\
  PRIMARY KEY (`A_id`, `Tracks_Number`));", MYSQLX_NULL_TERMINATED);

	if( (result = mysqlx_execute(query)) == NULL)
	{
		std::cout<< "There was an error with DB initlization" << std::endl;
	 	std::cout << mysqlx_error_message(err) << "\t" << session << std::endl;
		mysqlx_session_close(session);
		exit(mysqlx_error_num(err));
	}

	query = mysqlx_sql_new(session,"CREATE TABLE `recordcompany`.`producer` (\
  `p_ID` INT NOT NULL AUTO_INCREMENT,\
  `Name` VARCHAR(256) NOT NULL,\
  PRIMARY KEY (`p_ID`));", MYSQLX_NULL_TERMINATED);

	if( (result = mysqlx_execute(query)) == NULL)
	{
		std::cout<< "There was an error with DB initlization" << std::endl;
	 	std::cout << mysqlx_error_message(err) << "\t" << session << std::endl;
		mysqlx_session_close(session);
		exit(mysqlx_error_num(err));
	}

	//Relations tables


	query = mysqlx_sql_new(session,"CREATE TABLE `recordcompany`.`musican_instroment` (\
  `m_ID` INT NOT NULL,\
  `i_ID` INT NOT NULL,\
  PRIMARY KEY (`i_ID`, `m_ID`),\
  INDEX `MI_mID_idx` (`m_ID` ASC) VISIBLE,\
  CONSTRAINT `MI_mID`\
    FOREIGN KEY (`m_ID`)\
    REFERENCES `recordcompany`.`musican` (`id_Musican`)\
    ON DELETE NO ACTION\
    ON UPDATE NO ACTION,\
  CONSTRAINT `MI_iID`\
    FOREIGN KEY (`i_ID`)\
    REFERENCES `recordcompany`.`instrumant` (`I_id`)\
    ON DELETE NO ACTION\
    ON UPDATE NO ACTION);", MYSQLX_NULL_TERMINATED);

	if( (result = mysqlx_execute(query)) == NULL)
	{
		std::cout<< "There was an error with DB initlization" << std::endl;
	 	std::cout << mysqlx_error_message(err) << "\t" << session << std::endl;
		mysqlx_session_close(session);
		exit(mysqlx_error_num(err));
	}

	query = mysqlx_sql_new(session,"CREATE TABLE `recordcompany`.`musican_tracks` (\
  `m_ID` INT NOT NULL,\
  `t_ID` INT NOT NULL,\
  PRIMARY KEY (`m_ID`, `t_ID`),\
  INDEX `MT_tID_idx` (`t_ID` ASC) VISIBLE,\
  CONSTRAINT `MT_mID`\
    FOREIGN KEY (`m_ID`)\
    REFERENCES `recordcompany`.`musican` (`id_Musican`)\
    ON DELETE NO ACTION\
    ON UPDATE NO ACTION,\
  CONSTRAINT `MT_tID`\
    FOREIGN KEY (`t_ID`)\
    REFERENCES `recordcompany`.`track` (`T_id`)\
    ON DELETE NO ACTION\
    ON UPDATE NO ACTION);", MYSQLX_NULL_TERMINATED);

	if( (result = mysqlx_execute(query)) == NULL)
	{
		std::cout<< "There was an error with DB initlization" << std::endl;
	 	std::cout << mysqlx_error_message(err) << "\t" << session << std::endl;
		mysqlx_session_close(session);
		exit(mysqlx_error_num(err));
	}

	query = mysqlx_sql_new(session,"CREATE TABLE `recordcompany`.`album_track` (\
  `t_ID` INT NOT NULL,\
  `a_ID` INT NOT NULL,\
  PRIMARY KEY (`t_ID`, `a_ID`),\
  INDEX `AT_aID_idx` (`a_ID` ASC) VISIBLE,\
  CONSTRAINT `AT_tID`\
    FOREIGN KEY (`t_ID`)\
    REFERENCES `recordcompany`.`track` (`T_id`)\
    ON DELETE NO ACTION\
    ON UPDATE NO ACTION,\
  CONSTRAINT `AT_aID`\
    FOREIGN KEY (`a_ID`)\
    REFERENCES `recordcompany`.`album` (`A_id`)\
    ON DELETE NO ACTION\
    ON UPDATE NO ACTION);", MYSQLX_NULL_TERMINATED);

	if( (result = mysqlx_execute(query)) == NULL)
	{
		std::cout<< "There was an error with DB initlization" << std::endl;
	 	std::cout << mysqlx_error_message(err) << "\t" << session << std::endl;
		mysqlx_session_close(session);
		exit(mysqlx_error_num(err));
	}

	query = mysqlx_sql_new(session,"CREATE TABLE `recordcompany`.`album_producer` (\
  `a_ID` INT NOT NULL,\
  `p_ID` INT NOT NULL,\
  PRIMARY KEY (`a_ID`, `p_ID`),\
  INDEX `AP_pID_idx` (`p_ID` ASC) VISIBLE,\
  CONSTRAINT `AP_aID`\
    FOREIGN KEY (`a_ID`)\
    REFERENCES `recordcompany`.`album` (`A_id`)\
    ON DELETE NO ACTION\
    ON UPDATE NO ACTION,\
  CONSTRAINT `AP_pID`\
    FOREIGN KEY (`p_ID`)\
    REFERENCES `recordcompany`.`producer` (`p_ID`)\
    ON DELETE NO ACTION\
    ON UPDATE NO ACTION);", MYSQLX_NULL_TERMINATED);
	
	if( (result = mysqlx_execute(query)) == NULL)
	{
		std::cout<< "There was an error with DB initlization" << std::endl;
	 	std::cout << mysqlx_error_message(err) << "\t" << session << std::endl;
		mysqlx_session_close(session);
		exit(mysqlx_error_num(err));
	}

	mysqlx_session_close(session);
}

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		std::cout << "Please insert connection details" << std::endl;
		exit(-1);
	}
	initDB(argv[1],argv[2]);
	std::cout << "DB initlized fully" << std::endl;
	getchar();
	return 0;
}