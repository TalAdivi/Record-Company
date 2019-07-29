#include "DBManager.hpp"

template <typename T>
void freeVector(std::vector<T *> v)
{
  for (int i = 0; i < v.size(); ++i)
    delete v[i];
}

int DataBase::connect()
{
  this->session = mysqlx_get_session("localhost", DEFAULT_MYSQLX_PORT, this->username, this->password, "", &this->err);
  if (NULL == this->session)
  {
    std::cout << mysqlx_error_message(this->err) << "\t" << this->session << std::endl;
    return -1;
  }
  return 0;
}

int DataBase::init()
{
  mysqlx_stmt_t *query;
  mysqlx_result_t *result;

  if (mysqlx_get_schema(this->session, "RecordCompany", 1))
  {
    query = mysqlx_sql_new(this->session, "DROP database `RecordCompany`", MYSQLX_NULL_TERMINATED);

    if ((result = mysqlx_execute(query)) == NULL)
      return -1;
  }

  query = mysqlx_sql_new(this->session, "create database `RecordCompany`", MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
    return -1;

  mysqlx_session_close(session);

  this->session = mysqlx_get_session("localhost", DEFAULT_MYSQLX_PORT, this->username, this->password, "RecordCompany", &err);

  if (NULL == this->session)
  {
    std::cout << mysqlx_error_message(this->err) << "\t" << this->session << std::endl;
    return -1;
  }

  query = mysqlx_sql_new(session, "CREATE TABLE `musician` (\
 `id_musician` INT NOT NULL,\
 `Name` VARCHAR(256) NOT NULL,\
 `Address` VARCHAR(256) NOT NULL,\
 `Phone` VARCHAR(256) NOT NULL,\
 `Skill` VARCHAR(256) NOT NULL,\
 PRIMARY KEY (`id_musician`));",
                         MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
    return -1;

  query = mysqlx_sql_new(this->session, "CREATE TABLE `instrument` (\
 `I_id` INT NOT NULL UNIQUE,\
 `Brand` VARCHAR(256) NOT NULL,\
 `Type` VARCHAR(256) NOT NULL,\
 PRIMARY KEY (`I_id`, `Brand`, `Type`));",
                         MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
    return -1;

  query = mysqlx_sql_new(this->session, "CREATE TABLE `track` (\
 `T_id` INT NOT NULL,\
 `Name` VARCHAR(256) NOT NULL,\
 `Music_Compuser` VARCHAR(256) NULL,\
 `Length` INT NOT NULL,\
 `Lyrics_Composer` VARCHAR(256) NULL,\
 `Date` VARCHAR(256) NOT NULL,\
 `Genre` VARCHAR(256) NOT NULL,\
 `Technician` VARCHAR(256) NOT NULL,\
 PRIMARY KEY (`T_id`));",
                         MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
    return -1;

  query = mysqlx_sql_new(this->session, "CREATE TABLE `album` (\
 `A_id` INT NOT NULL,\
 `Name` VARCHAR(256) NOT NULL,\
 `S_Date` VARCHAR(256) NOT NULL,\
 `E_Date` VARCHAR(256) NOT NULL,\
 `Tracks_Number` INT NOT NULL,\
 PRIMARY KEY (`A_id`));",
                         MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
    return -1;

  query = mysqlx_sql_new(this->session, "CREATE TABLE `producer` (\
 `p_ID` INT NOT NULL,\
 `Name` VARCHAR(256) NOT NULL,\
 PRIMARY KEY (`p_ID`));",
                         MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
    return -1;

  //Relations tables

  query = mysqlx_sql_new(this->session, "CREATE TABLE `musician_instrument` (\
 `m_ID` INT NOT NULL,\
 `i_ID` INT NOT NULL,\
 PRIMARY KEY (`i_ID`, `m_ID`),\
 INDEX `MI_mID_idx` (`m_ID` ASC) VISIBLE,\
 CONSTRAINT `MI_mID`\
 FOREIGN KEY (`m_ID`)\
 REFERENCES `recordcompany`.`musician` (`id_musician`)\
 ON DELETE NO ACTION\
 ON UPDATE NO ACTION,\
 CONSTRAINT `MI_iID`\
 FOREIGN KEY (`i_ID`)\
 REFERENCES `recordcompany`.`instrument` (`I_id`)\
 ON DELETE NO ACTION\
 ON UPDATE NO ACTION);",
                         MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
    return -1;

  query = mysqlx_sql_new(this->session, "CREATE TABLE `musician_tracks` (\
 `m_ID` INT NOT NULL,\
 `t_ID` INT NOT NULL,\
 PRIMARY KEY (`m_ID`, `t_ID`),\
 INDEX `MT_tID_idx` (`t_ID` ASC) VISIBLE,\
 CONSTRAINT `MT_mID`\
 FOREIGN KEY (`m_ID`)\
 REFERENCES `recordcompany`.`musician` (`id_musician`)\
 ON DELETE NO ACTION\
 ON UPDATE NO ACTION,\
 CONSTRAINT `MT_tID`\
 FOREIGN KEY (`t_ID`)\
 REFERENCES `recordcompany`.`track` (`T_id`)\
 ON DELETE NO ACTION\
 ON UPDATE NO ACTION);",
                         MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
    return -1;

  query = mysqlx_sql_new(this->session, "CREATE TABLE `album_track` (\
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
 ON UPDATE NO ACTION);",
                         MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
    return -1;

  query = mysqlx_sql_new(this->session, "CREATE TABLE `album_producer` (\
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
 ON UPDATE NO ACTION);",
                         MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
    return -1;

  mysqlx_free(result);

  return 0;
}

int DataBase::build()
{
  mysqlx_stmt_t *query;
  mysqlx_result_t *result;

  query = mysqlx_sql_new(this->session, "INSERT INTO `musician` (`id_musician`, `Name`, `Address`, `Phone`, `Skill`) VALUES\
 (1, 'Beethover', 'Austria', '098-909985', 'Player') ,\
 (2, 'Michael Jackson' ,'Los Angeles', '098-373489', 'Singer & Player'),\
 (3, 'James Cameron' ,'Los Angeles', '067-758937', 'Player'),\
 (4, 'Ice-T' ,'New York', '068-374838', 'Singer'),\
 (5, 'P-Dog' ,'New York', '098-373489', 'Singer'),\
 (6, 'Roger Waters' ,'London', '096-388389', 'Singer & Player'),\
 (7, 'p!nk', 'Las Vegas' , '123-868729', 'Singer & Player'),\
 (8, 'Freddy Mercury', 'London', '028-959395', 'Singer & Player'),\
 (9, 'ABBA', 'Sweden', '634-850258', 'Singer & Player'),\
 (10, 'Danny Gonzales', 'Oragon', '078-123963', 'Singer'),\
 (11, 'TMG', 'Los Angeles', '063-847492', 'Singer'),\
 (12, 'test', 'Los Angeles', '063-847492', 'Singer'),\
 (13, 'test', 'Los Angeles', '063-847492', 'Singer');",
                         MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
    return -1;

  query = mysqlx_sql_new(this->session, "INSERT INTO `track` (`T_id`, `Name`, `Music_Compuser`, `Length`, `Lyrics_Composer`, `Date`, `Genre`, `Technician`) VALUES\
 (1, 'Ode to Joy', 'Beethoven', 220, 'NULL', '1824-01-01', 'Classical', 'Beethoven'),\
 (2, 'We Will Rock You','Queen',250,'Freddy Mercury','1977-10-07','Rock','Bill McGree'),\
 (3, 'Toxic','Jack Hallow',164,'Kelsey Lowe','2004-01-13','Pop','Bill McGree'),\
 (4, 'Johnny Johnny','Danny Gonzales',203,'Danny Gonzales','2017-06-21','Comedy','AudioCloud'),\
 (5, 'Slime','Danny Gonzales',189,'Danny Gonzales','2018-01-17','Comedy','AudioCloud'),\
 (6, 'No Flex','Noel Miller',89,'Noel Miller','2016-12-29','Rap','Cody Ko'),\
 (7, 'Walkman','Noel Miller',197,'Cody Ko','2018-11-25','Rap','Cody Ko'),\
 (8, 'Short King Anthem','Noel Miller',192,'Noel Miller','2019-02-14','Rap','Cody Ko'),\
 (9, 'Disco Queen','Bjorn and Benny',184,'Bjorn and Benny','1975-08-04','Pop','Bill McGree'),\
 (10, 'Thriller','Michael Jackson',217,'Freddy Mercury','1984-01-23','Pop','AudioCloud');",
                         MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
    return -1;

  query = mysqlx_sql_new(this->session, "INSERT INTO `album` (`A_id`, `Name`, `S_Date`, `E_Date`, `Tracks_Number`) VALUES\
 (1, 'Ode to Joy RErelease', '2015-04-15', '2015-04-29', 1),\
 (2, 'Johnny Johnny SINGLE', '2017-06-20', '2017-07-01', 1),\
 (3, 'Slime SINGLE', '2018-01-15', '2018-02-02', 1),\
 (4, 'Danny the Collection', '2019-01-01', '2019-01-15', 2),\
 (5, 'TMG', '2016-12-20', '2019-02-20', 3),\
 (6, 'Diso Queen SINGLE', '1975-08-04', '1975-08-05', 1),\
 (7, 'Thriller SINGLE', '1984-01-20', '1984-01-26', 1),\
 (8, 'Pop Supreme', '2016-05-28', '2016-06-10', 3),\
 (9, 'Record Star', '2019-07-07', '2019-07-30', 10),\
 (10, 'Its Brittney', '2004-01-10', '2004-01-20', 1);",
                         MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
    return -1;

  query = mysqlx_sql_new(this->session, "INSERT INTO `recordcompany`.`instrument` (`I_id`, `Brand`, `Type`) VALUES\
 (1, 'Yamhaa', 'Piano'),\
 (2, 'Yamhaa', 'Synth'),\
 (3, 'Gibson', 'Bass'),\
 (4, 'Fender', 'Bass'),\
 (5, 'Gibson', 'Guitar'),\
 (6, 'Fender', 'Guitar'),\
 (7, 'Epiphone', 'Guitar'),\
 (8, 'Gretch', 'Drums'),\
 (9, 'Ludwig', 'Drums'),\
 (10, 'Remo', 'Tambourine');",
                         MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
    return -1;

  query = mysqlx_sql_new(this->session, "INSERT INTO `recordcompany`.`producer` (`p_ID`, `Name`) VALUES\
 (1, 'Bill McGree'),\
 (2, 'Dr Dre'),\
 (3, 'Jay-Z'),\
 (4, 'Rick Rubin'),\
 (5, 'George Martin'),\
 (6, 'Joe Meek'),\
 (7, 'Quincy Jones'),\
 (8, 'Phil Spector'),\
 (9, 'Butch Vig'),\
 (10, 'Arif Mardin');",
                         MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
    return -1;

  query = mysqlx_sql_new(this->session, "INSERT INTO `musician_instrument` (`m_ID`, `i_ID`) VALUES\
 (1,1),\
 (2,2),\
 (2,5),\
 (3,10),\
 (6,1),\
 (6,6),\
 (7,5),\
 (7,6),\
 (8,1),\
 (8,2),\
 (9,1),\
 (9,5),\
 (9,8);",
                         MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
    return -1;

  query = mysqlx_sql_new(this->session, "INSERT INTO `musician_tracks` (`m_ID`, `t_ID`) VALUES\
 (1,1),\
 (2,10),\
 (3,10),\
 (8,2),\
 (9,9),\
 (7,3),\
 (10,4),\
 (10,5),\
 (11,6),\
 (11,7),\
 (11,8),\
 (4,6),\
 (6,2),\
 (8,3);",
                         MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
    return -1;

  query = mysqlx_sql_new(this->session, "INSERT INTO `album_track`(`t_ID`, `a_ID`) VALUES\
 (1,1),\
 (4,2),\
 (5,3),\
 (4,4),\
 (5,4),\
 (6,5),\
 (7,5),\
 (8,5),\
 (9,6),\
 (10,7),\
 (3,8),\
 (9,8),\
 (10,8),\
 (3,10),\
 (1,9),\
 (2,9),\
 (3,9),\
 (4,9),\
 (5,9),\
 (6,9),\
 (7,9),\
 (8,9),\
 (9,9),\
 (10,9);",
                         MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
    return -1;

  query = mysqlx_sql_new(this->session, "INSERT INTO `album_producer` (`a_ID`,`p_ID`) VALUES\
 (1,1),\
 (2,2),\
 (3,2),\
 (3,1),\
 (4,1),\
 (4,2),\
 (4,3),\
 (5,2),\
 (5,6),\
 (6,4),\
 (6,5),\
 (8,4),\
 (8,5),\
 (8,6),\
 (9,1),\
 (9,7),\
 (9,10),\
 (10,9);",
                         MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
    return -1;

  mysqlx_free(result);
  return 0;
}

int DataBase::albumsBetween(std::string start, std::string end)
{
  mysqlx_stmt_t *query;
  mysqlx_result_t *result;

  std::string qstr = "select count(*) from album where E_Date > '" + start + "' AND E_Date < '" + end + "';\0";

  query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);
  if ((result = mysqlx_execute(query)) == NULL)
    return -1;

  mysqlx_row_t *row;
  int64_t x;

  if ((row = mysqlx_row_fetch_one(result)) != NULL)
  {
    mysqlx_get_sint(row, 0, &x);
    std::cout << "The amount of albums between " << start << " and " << end << " are : " << x << std::endl
              << std::endl
              << std::endl;
  }
  else
  {
    std::cout << "There was an error running the Query." << std::endl;
  }

  mysqlx_free(result);

  return 0;
}

int DataBase::musicianSongBetween(std::string name)
{
  mysqlx_stmt_t *query;
  mysqlx_result_t *result;

  std::string qstr = "select * from musician where Name Like '%" + name + "%';\0";
  query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
  {
    std::cout << "There is no musician with this name" << std::endl;
    return -1;
  }

  int choice = 1;

  std::vector<Musician *> v = initArray<Musician>(result);

  if (v.size() == 0)
  {
    std::cout << "There is no user with that name want to try again ? y/n";
    char c;
    std::cin >> c;
    if (c == 'y' || c == 'Y')
      return 2;
    else
      return -1;
  }

  if (v.size() > 1)
  {
    for (int i = 0; i < v.size(); ++i)
    {
      std::cout << i + 1 << " - " << *v[i] << std::endl;
    }

    do
    {
      std::cout << "Please insert the index of the musician you want" << std::endl;
      std::cin >> choice;

      if (choice < 1 || choice > v.size())
        std::cout << "INCORRECT VALUE RETRY" << std::endl;

    } while (choice < 1 || choice > v.size());
  }

  std::string start;
  std::string end;
  std::cout << "Please input the start and end date (YEAR-MONTH-DAY)" << std::endl;
  std::cin >> start >> end;

  qstr = "select count(*) from track as t join musician_tracks as m on \
 m.t_ID = t.T_id where m_ID = " +
         std::to_string(v[choice - 1]->getID()) + " and t.Date > '" + start + "' and t.Date < '" + end + "';\0";

  query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
  {
    std::cout << "There is no musician with this name" << std::endl;
    return -1;
  }

  mysqlx_row_t *row;
  int64_t x;

  if ((row = mysqlx_row_fetch_one(result)) != NULL)
  {
    mysqlx_get_sint(row, 0, &x);
    std::cout << "The amount of tracks that " << v[choice - 1]->getName() << " preformed between " << start << " and " << end << " are : " << x << std::endl
              << std::endl
              << std::endl;
  }
  else
  {
    std::cout << "There was an error running the Query." << std::endl;
  }

  mysqlx_free(result);
  freeVector(v);

  return 0;
}

int DataBase::musicianAlbumBetween(std::string name)
{
  mysqlx_stmt_t *query;
  mysqlx_result_t *result;

  std::string qstr = "select * from musician where Name Like '%" + name + "%';\0";
  query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
  {
    std::cout << "There is no musician with this name" << std::endl;
    return -1;
  }

  int choice = 1;

  std::vector<Musician *> v = initArray<Musician>(result);

  if (v.size() == 0)
  {
    std::cout << "There is no user with that name want to try again ? y/n";
    char c;
    std::cin >> c;
    if (c == 'y' || c == 'Y')
      return 2;
    else
      return -1;
  }

  if (v.size() > 1)
  {
    for (int i = 0; i < v.size(); ++i)
    {
      std::cout << i + 1 << " - " << *v[i] << std::endl;
    }

    do
    {
      std::cout << "Please insert the index of the musician you want" << std::endl;
      std::cin >> choice;

      if (choice < 1 || choice > v.size())
        std::cout << "INCORRECT VALUE RETRY" << std::endl;

    } while (choice < 1 || choice > v.size());
  }

  std::string start;
  std::string end;
  std::cout << "Please input the start and end date (YEAR-MONTH-DAY)" << std::endl;
  std::cin >> start >> end;

  qstr = "select count(*) from album as ab join (select a_ID from( (select * from album_track) as a INNER JOIN\
 (select * from musician_tracks where musician_tracks.m_ID = " +
         std::to_string(v[choice - 1]->getID()) + ") as b\
 on a.t_ID = b.t_ID) group by a_ID ) as c on ab.A_id = c.a_ID where E_Date > '" +
         start + "' and E_Date < '" + end + "' ;\0";

  query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
  {
    std::cout << "There is no musician with this name" << std::endl;
    return -1;
  }

  mysqlx_row_t *row;
  int64_t x;

  if ((row = mysqlx_row_fetch_one(result)) != NULL)
  {
    mysqlx_get_sint(row, 0, &x);
    std::cout << "The amount of Albums that " << v[choice - 1]->getName() << " released between " << start << " and " << end << " are : " << x << std::endl
              << std::endl
              << std::endl;
  }
  else
  {
    std::cout << "There was an error running the Query." << std::endl;
  }

  mysqlx_free(result);
  freeVector(v);
  return 0;
}

int DataBase::popularInstrument()
{

  mysqlx_stmt_t *query;
  mysqlx_result_t *result;

  std::string qstr = "SELECT * FROM instrument;\0";
  query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
  {
    std::cout << "There is no musician with this name" << std::endl;
    return -1;
  }

  std::vector<Instrument *> v = initArray<Instrument>(result);
  int max = -1;
  int index = -1;

  mysqlx_row_t *row;
  int64_t x;

  for (int i = 0; i < v.size(); ++i)
  {
    qstr = "SELECT count(*) from (\
 (SELECT * FROM musician_instrument where i_ID = " +
           std::to_string(v[i]->getID()) + ") as a join musician_tracks as b \
 on a.m_ID = b.m_ID);";
    int value = -1;

    if ((result = mysqlx_execute(query)) != NULL)
    {
      if ((row = mysqlx_row_fetch_one(result)) != NULL)
      {
        value = mysqlx_get_sint(row, 0, &x);
      }
      else
      {
        std::cout << "There was an error running the Query." << std::endl;
      }

      if( value > max )
      {
        max = value;
        index = i;
      }
    }
  }

  std::cout << "The most popular instrument is:\t" << *v[index] << std::endl;

  return 0;
}