#include "functionality.hpp"

char username[256];
char password[256];

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

    std::string qstr = "select * from musician where Name Like '%"+name+"%';\0";
    query = mysqlx_sql_new(session, qstr.c_str() , MYSQLX_NULL_TERMINATED);

	if( (result = mysqlx_execute(query)) == NULL)
    {
        std::cout << "There is no musician with this name" << std::endl;
		return -1;
    }
    
    int choice = 1;

    std::vector<Musician*> v = initArray<Musician>(result);

    if(v.size() == 0)
    {
        std::cout<<"There is no user with that name want to try again ? y/n";
        char c;
        std::cin >> c;
        if(c == 'y' || c == 'Y')
            return 2;
        else
            return -1;
                
    }

    if(v.size()>1)
    {
        for(int i = 0 ; i < v.size(); ++i)
        {
            std::cout << i+1 << " - " << *v[i] << std::endl;
        }
    
        do
        {
            std::cout << "Please insert the index of the musician you want" << std::endl;
            std::cin >> choice;

            if(choice < 1 || choice > v.size())
                std::cout << "INCORRECT VALUE RETRY" << std::endl;

        }while(choice < 1 || choice > v.size());
    }

    std::string start;
    std::string end;
    std::cout << "Please input the start and end date (YEAR-MONTH-DAY)" << std::endl;
    std::cin >> start >> end;


    qstr = "select count(*) from track as t join musician_tracks as m on \
 m.t_ID = t.T_id where m_ID = "+std::to_string(v[choice-1]->getID())+" and t.Date > '"+start+"' and t.Date < '"+end+"';\0";

    query = mysqlx_sql_new(session, qstr.c_str() , MYSQLX_NULL_TERMINATED);

	if( (result = mysqlx_execute(query)) == NULL)
    {
        std::cout << "There is no musician with this name" << std::endl;
		return -1;
    }

    mysqlx_row_t* row;
    int64_t x;

    while( (row = mysqlx_row_fetch_one(result))!=NULL)
    {
        mysqlx_get_sint(row, 0, &x);
        std::cout << "The amount of tracks that " << v[choice-1]->getName() << " preformed between " << start << " and " << end << " are : " << x << std::endl << std::endl << std::endl;
    }  

    mysqlx_result_free(result);
	mysqlx_session_close(session);

    return 0;

}

int musicianAlbumBetween(std::string name)
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

    std::string qstr = "select * from musician where Name Like '%"+name+"%';\0";
    query = mysqlx_sql_new(session, qstr.c_str() , MYSQLX_NULL_TERMINATED);

	if( (result = mysqlx_execute(query)) == NULL)
    {
        std::cout << "There is no musician with this name" << std::endl;
		return -1;
    }
    
    int choice = 1;

    std::vector<Musician*> v = initArray<Musician>(result);

    if(v.size() == 0)
    {
        std::cout<<"There is no user with that name want to try again ? y/n";
        char c;
        std::cin >> c;
        if(c == 'y' || c == 'Y')
            return 2;
        else
            return -1;
                
    }

    if(v.size()>1)
    {
        for(int i = 0 ; i < v.size(); ++i)
        {
            std::cout << i+1 << " - " << *v[i] << std::endl;
        }
    
        do
        {
            std::cout << "Please insert the index of the musician you want" << std::endl;
            std::cin >> choice;

            if(choice < 1 || choice > v.size())
                std::cout << "INCORRECT VALUE RETRY" << std::endl;

        }while(choice < 1 || choice > v.size());
    }

    std::string start;
    std::string end;
    std::cout << "Please input the start and end date (YEAR-MONTH-DAY)" << std::endl;
    std::cin >> start >> end;

    std::cout << v[choice-1]->getID() << std::endl;

    qstr = "select count(*) from album as ab join (select a_ID from( (select * from album_track) as a INNER JOIN\
 (select * from musician_tracks where musician_tracks.m_ID = "+std::to_string(v[choice-1]->getID())+") as b\
 on a.t_ID = b.t_ID) group by a_ID ) as c on ab.A_id = c.a_ID where E_Date > '"+start+"' and E_Date < '"+end+"' ;\0";

    query = mysqlx_sql_new(session, qstr.c_str() , MYSQLX_NULL_TERMINATED);

	if( (result = mysqlx_execute(query)) == NULL)
    {
        std::cout << "There is no musician with this name" << std::endl;
		return -1;
    }

    mysqlx_row_t* row;
    int64_t x;

    while( (row = mysqlx_row_fetch_one(result))!=NULL)
    {
        mysqlx_get_sint(row, 0, &x);
        std::cout << "The amount of Albums that " << v[choice-1]->getName() << " released between " << start << " and " << end << " are : " << x << std::endl << std::endl << std::endl;
    }  

    mysqlx_result_free(result);
	mysqlx_session_close(session);

    return 0;
}

