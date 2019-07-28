#include "functionality.hpp"

extern char username[256];
extern char password[256];

int albumsBetween(std::string start, std::string end)
{
    mysqlx_error_t *err;
	mysqlx_stmt_t* query;
	mysqlx_result_t* result;
	mysqlx_session_t* session = mysqlx_get_session("localhost", DEFAULT_MYSQLX_PORT, username, password, "RecordCompany", &err);

	if (NULL == session) 
	{
	 	std::cout << mysqlx_error_message(err) << "\t" << session << std::endl;
		return -1;
	}

    std::string qstr = "select count(*) from album where E_Date > '"+start+"' AND E_Date < '"+end+"';\0";

    query = mysqlx_sql_new(session, qstr.c_str() , MYSQLX_NULL_TERMINATED);
	if( (result = mysqlx_execute(query)) == NULL)
		return -1;
    
    mysqlx_row_t* row;
    int64_t x;

    while( (row = mysqlx_row_fetch_one(result))!=NULL)
    {
        mysqlx_get_sint(row, 0, &x);
        std::cout << "The amount of albums between " << start << " and " << end << " are : " << x << std::endl << std::endl << std::endl;
    }  

    mysqlx_result_free(result);
	mysqlx_session_close(session);

    return 0;
}

int musicianSongBetween(std::string name)
{
    mysqlx_error_t *err;
	mysqlx_stmt_t* query;
	mysqlx_result_t* result;
	mysqlx_session_t* session = mysqlx_get_session("localhost", DEFAULT_MYSQLX_PORT, username, password, "RecordCompany", &err);

	if (NULL == session) 
	{
	 	std::cout << mysqlx_error_message(err) << "\t" << session << std::endl;
		return -1;
	}

    std::string qstr = "select * from musician where Name = '"+name+"';\0";
    query = mysqlx_sql_new(session, qstr.c_str() , MYSQLX_NULL_TERMINATED);

	if( (result = mysqlx_execute(query)) == NULL)
    {
        std::cout << "There is no musician with this name" << std::endl;
		return -1;
    }

    Musician m();

    std::string start;
    std::string end;

    std::cout << "Please input the start and end date (YEAR-MONTH-DAY)" << std::endl;
    std::cin >> start >> end;



    qstr = "select count(*) from track as t join musician_tracks on \
    musician_tracks.m_ID = "+m->getID()+"vwhere t.Date > '"+start+"' and t.Date < '"+end+"';\0";



}