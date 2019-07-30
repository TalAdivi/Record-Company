#include "DBManager.hpp"

template <typename T>
void freeVector(std::vector<T *> v)
{
  for (int i = 0; i < v.size(); ++i)
    delete v[i];
}

int correctFormat(std::string date)
{
    if(date.length() != 10 || date[4] != '-' || date[7] != '-')
        return -1;
    return 0;
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
 (1, 'Guns And Roses', 'Austria', '098-909985', 'Singer & Player') ,\
 (2, 'Michael Jackson' ,'Los Angeles', '098-373489', 'Singer & Player'),\
 (3, 'Meir Banai' ,'Israel', '067-758937', 'Singer & Player'),\
 (4, 'Ice-T' ,'New York', '068-374838', 'Singer'),\
 (5, 'Lana Del Rey' ,'Paris', '098-373489', 'Singer'),\
 (6, 'Hozier' ,'London', '096-388389', 'Singer & Player'),\
 (7, 'p!nk', 'Las Vegas' , '123-868729', 'Singer & Player'),\
 (8, 'Freddy Mercury', 'London', '028-959395', 'Singer & Player'),\
 (9, 'Bryan Adams', 'Sweden', '634-850258', 'Singer & Player'),\
 (10, 'Red Hot Chili Peppers', 'Los Angeles', '078-123963', 'Singer & Player'),\
 (11, 'Infected Mushroom', 'Israel', '063-847492', 'Singer'),\
 (12, 'Usher', 'New York', '745-942489', 'Singer'),\
 (13, 'Bob Marley', 'Jamaica', '097-125613', 'Singer'),\
 (14, 'Eminem', 'New York', '101-331015', 'Singer'),\
 (15, 'Berry Sakharof', 'Israel', '056-129314', 'Singer'),\
 (16, 'Berry Sakharof', 'Israel', '052-908528', 'Singer');",
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
 (10, 'Thriller','Michael Jackson',217,'Freddy Mercury','1984-01-23','Pop','AudioCloud'),\
 (11, 'Lobster','Berry Sakharof',184,'Balkan Beat Box','2018-08-04','Pop','Yossi Elgrabli'),\
 (12, 'Lose Yourself','Eminem',230,'Eminem','2000-09-01','Rap','Eminem'),\
 (13, 'Love The Way You Lie','Eminem',254,'Eminem','1993-11-02','Rap','Eminem'),\
 (14, 'Not Afraid','Eminem',200,'Eminem','1995-01-02','Rap','Eminem'),\
 (15, 'Castle','Eminem',212,'Eminem','2012-02-29','Rap','Eminem'),\
 (16, 'Till I Collapse','Eminem',193,'Eminem','2002-06-09','Rap','Eminem'),\
 (17, 'Babylon System', 'Bob Marley', 240, 'Bob Marley', '1980-12-22', 'Ragay', 'Rastaman'),\
 (18, 'No Woman No Cry', 'Bob Marley', 212, 'Bob Marley', '1982-03-12', 'Ragay', 'Rastaman'),\
 (19, 'Yeah!', 'Usher', 193, 'Usher', '1992-05-11', 'Rap', 'Terry A. Farris'),\
 (20, 'My Boo!', 'Usher', 201, 'Usher', '2002-09-17', 'Rap', 'Terry A. Farris'),\
 (21, 'Cities Of The Future', 'Tomer Sason', 320, 'Tomer Sason', '2007-01-27', 'Electronic', 'Infected Mushroom'),\
 (22, 'Californication', 'Red Hot Chili Peppers', 203, 'Red Hot Chili Peppers', '1994-08-07', 'Funk', 'AudioCloud'),\
 (23, 'Snow', 'Red Hot Chili Peppers', 243, 'Red Hot Chili Peppers', '1990-04-28', 'Funk', 'AudioCloud'),\
 (24, 'Heaven', 'Brayen Adams', 189, 'Brayen Adams', '1991-02-09', 'Rock', 'Cody Ko'),\
 (25, 'Mosh','Eminem',381,'Eminem','2003-12-12','Rap','Eminem'),\
 (26, 'Evil Needs','Eminem',254,'Eminem','2003-04-21','Rap','Eminem'),\
 (27, 'Kama Yosi','Berry Sakharof',284,'Berry Sakharof','2009-01-14','Rock','Yossi Elgrabli'),\
 (28, 'I Like It Like That', 'Kardi B', 272, 'Kardi B', '2017-04-26', 'Rap', 'Cody Ko'),\
 (29, 'Trump Rap','Eminem',242,'Eminem','2012-02-29','Freestyle','Eminem'),\
 (30, 'KillShot','Eminem',219,'Eminem','2012-02-29','Pop','Eminem'),\
 (31, 'Without Me','Eminem',312,'Eminem','2012-02-29','Pop','Eminem');",
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
 (10, 'Its Brittney', '2004-01-10', '2004-01-20', 1),\
 (11, 'The Slim Shady', '1990-06-23', '1999-06-23', 5),\
 (12, 'Live Forever', '1975-01-28', '1970-10-14', 2),\
 (13, '8701', '2000-11-08', '2001-02-09', 2),\
 (14, 'Converting Vegetarians', '2010-12-23', '2015-02-09', 1),\
 (15, 'By The Way', '2001-04-15', '2002-11-30', 2),\
 (16, 'Get Up', '2012-07-01', '2015-03-19', 1),\
 (17, 'Encore', '2002-07-01', '2004-07-28', 2),\
 (18, 'Negiaot', '1995-07-11', '1998-11-31', 1),\
 (19, 'By The Way', '2002-03-27', '2004-09-11', 1),\
 (20, 'Kamakazi', '2012-07-01', '2018-07-28', 3);",
                         MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
    return -1;

  query = mysqlx_sql_new(this->session, "INSERT INTO `instrument` (`I_id`, `Brand`, `Type`) VALUES\
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

  query = mysqlx_sql_new(this->session, "INSERT INTO `producer` (`p_ID`, `Name`) VALUES\
 (1, 'Bill McGree'),\
 (2, 'Dr Dre'),\
 (3, 'Jay-Z'),\
 (4, 'Rick Rubin'),\
 (5, 'George Martin'),\
 (6, 'Joe Meek'),\
 (7, 'Quincy Jones'),\
 (8, 'Phil Spector'),\
 (9, 'Butch Vig'),\
 (10, 'Arif Mardin'),\
 (11, 'Rick Rubin'),\
 (12, 'Erez Eisen');",
                         MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
    return -1;

  query = mysqlx_sql_new(this->session, "INSERT INTO `musician_instrument` (`m_ID`, `i_ID`) VALUES\
 (1,1),\
 (1,3),\
 (1,8),\
 (2,2),\
 (2,5),\
 (3,5),\
 (6,1),\
 (6,6),\
 (7,5),\
 (7,6),\
 (8,1),\
 (8,2),\
 (9,1),\
 (9,5),\
 (9,8),\
 (10,1),\
 (10,5),\
 (10,8);",
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
 (8,3),\
 (15,11),\
 (14,12),\
 (14,13),\
 (14,14),\
 (14,15),\
 (14,16),\
 (13,17),\
 (13,18),\
 (12,19),\
 (12,20),\
 (11,21),\
 (10,22),\
 (10,23),\
 (9,24),\
 (14,25),\
 (14,26),\
 (16,27),\
 (12,28),\
 (14,29),\
 (14,30),\
 (14,31);",
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
 (10,9),\
 (12,11),\
 (13,11),\
 (14,11),\
 (15,11),\
 (16,11),\
 (17,12),\
 (18,12),\
 (19,13),\
 (20,13),\
 (21,14),\
 (22,15),\
 (23,15),\
 (24,16),\
 (25,17),\
 (26,17),\
 (27,18),\
 (28,19),\
 (29,20),\
 (30,20),\
 (31,20);",
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
 (10,9),\
 (11,2),\
 (12,9),\
 (13,3),\
 (14,12),\
 (15,11),\
 (16,1),\
 (17,2),\
 (18,12),\
 (19,2),\
 (20,2);",
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
    std::cout << "There was an error executing the Query" << std::endl;
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

  if (correctFormat(start) == -1 || correctFormat(end) == -1)
  {
    std::cout << "incorrect date format please re-try" << std::endl;
    return -1;
  }

  qstr = "select count(*) from track as t join musician_tracks as m on \
 m.t_ID = t.T_id where m_ID = " +
         std::to_string(v[choice - 1]->getID()) + " and t.Date > '" + start + "' and t.Date < '" + end + "';\0";

  query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
  {
    std::cout << "There was an error executing the Query" << std::endl;
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
    std::cout << "There was an error executing the Query" << std::endl;
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
    std::cout << "There was an error executing the Query" << std::endl;
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
    std::cout << "There was an error executing the Query" << std::endl;
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
    query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);

    int value = -1;

    if ((result = mysqlx_execute(query)) != NULL)
    {
      if ((row = mysqlx_row_fetch_one(result)) != NULL)
      {
        mysqlx_get_sint(row, 0, &x);
        value = x;
      }
      else
      {
        std::cout << "There was an error running the Query." << std::endl;
      }

      if (value > max)
      {
        max = value;
        index = i;
      }
    }
  }

  if (max == -1 || index == -1)
    std::cout << "There was an error running the Query." << std::endl;
  else
    std::cout << "The most popular instrument is:\t" << v[index]->getBrand() << ", " << v[index]->getType() << std::endl;

  mysqlx_free(result);
  freeVector(v);
  return 0;
}

int DataBase::instrumentsInAlbum(std::string name) // two albums same name ?
{
  mysqlx_stmt_t *query;
  mysqlx_result_t *result;
  int choise = 1;

  std::string qstr = "SELECT * FROM Album where Name Like '%" + name + "%';\0";
  query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
  {
    std::cout << "There was an error executing the Query" << std::endl;
    return -1;
  }

  std::vector<Album *> album = initArray<Album>(result);

  if (album.size() == 0)
  {
    std::cout << "There is no user with that name want to try again ? y/n";
    char c;
    std::cin >> c;
    if (c == 'y' || c == 'Y')
      return 2;
    else
      return -1;
  }

  bool flag = true;

  if (album.size() > 1)
  {
    do
    {
      std::cout << "There is " << album.size() << " albums with this name" << std::endl
                << std::endl;
      std::cout << "Index\tID, Name, S_Date, E_Date, Track Number" << std::endl;
      for (int i = 0; i < album.size(); ++i)
      {
        std::cout << i + 1 << "\t" << *album[i] << std::endl;
      }
      std::cout << std::endl
                << "Please select album Index you want to check for> ";
      std::cin >> choise;
      if (choise > album.size() || choise < 1)
        std::cout << std::endl
                  << "Incorrect number please choose again" << std::endl
                  << std::endl;
      else
        flag = false;
    } while (flag);
  }

  qstr = "select * from instrument as i join\
 (select i_ID from musician_instrument as mi join\
 (select m_ID from Album_Track as a  join musician_tracks as b on a.t_ID = b.t_ID where a.a_id = " +
         std::to_string(album[choise - 1]->getID()) + ")\
 as mb on mi.m_ID = mb.m_ID) as b on i.I_id = b.I_id ;\0";

  query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
  {
    std::cout << "There was an error executing the Query" << std::endl;
    return -1;
  }

  std::vector<Instrument *> v = initArray<Instrument>(result);

  if (v.size() == 0)
    std::cout << std::endl
              << "No instruments were used in " + album[choise-1]->getName() << std::endl;
  else
  {
    std::cout << "Instruments used in this album are :" << std::endl
              << std::endl;
    std::cout << "Album Name: " + album[choise - 1]->getName() << std::endl
              << "Index\tID, Brand, Type" << std::endl;
    std::cout << "------------------------------" << std::endl;
    for (int i = 0; i < v.size(); ++i)
      std::cout << i + 1 << ".\t" << *v[i] << std::endl;
  }
  std::cout << std::endl;

  mysqlx_free(result);
  freeVector(album);
  freeVector(v);
  return 0;
}

int DataBase::producerOfAlbumBetween(std::string start, std::string end) // cant with one query?
{
  mysqlx_stmt_t *query;
  mysqlx_result_t *result;

  std::string qstr = "SELECT * FROM Producer;\0";
  query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
  {
    std::cout << "There was an error executing the Query" << std::endl;
    return -1;
  }

  std::vector<Producer *> v = initArray<Producer>(result);

  int max = -1;
  int index = -1;

  mysqlx_row_t *row;
  int64_t x;

  for (int i = 0; i < v.size(); ++i)
  {

    qstr = "select count(*) from (\
 (SELECT * FROM album_producer where p_ID = " +
           std::to_string(v[i]->getID()) + ") as a join album as b on a.a_ID = b.A_id )\
 where E_Date  > '" +
           start + "' and E_Date < '" + end + "';";
    query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);

    int value = 0;
    if ((result = mysqlx_execute(query)) != NULL)
    {
      if ((row = mysqlx_row_fetch_one(result)) != NULL)
      {
        mysqlx_get_sint(row, 0, &x);
        value = x;
      }
      else
      {
        std::cout << "There was an error running the Query." << std::endl;
      }

      if (value > max)
      {
        max = value;
        index = i;
      }
    }
  }

  if (max == -1 || index == -1)
    std::cout << "There was an error running the Query." << std::endl;
  else
    std::cout << "The most popular Producer is:\t" << v[index]->getName() << std::endl;

  mysqlx_free(result);
  freeVector(v);

  return 0;
}

int getIndex(std::vector<std::string> &v, std::string val)
{
  for (int i = 0; i < v.size(); ++i)
    if (v[i] == val)
      return i;
  return -1;
}

int findMax(std::vector<int> &v)
{
  int index = 0;
  int max = v[0];
  for (int i = 1; i < v.size(); ++i)
    if (v[i] > max)
    {
      max = v[i];
      index = i;
    }
  return index;
}

int DataBase::popularManufacterer()
{
  mysqlx_stmt_t *query;
  mysqlx_result_t *result;

  std::vector<std::string> manufacterers;
  std::vector<int> count;

  mysqlx_row_t *row;
  int64_t x;

  std::string qstr = "SELECT * FROM Instrument;\0";
  query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
  {
    std::cout << "There was an error executing the Query" << std::endl;
    return -1;
  }

  std::vector<Instrument *> v = initArray<Instrument>(result);

  for (int i = 0; i < v.size(); ++i)
  {
    qstr = "SELECT count(*) from (\
 (SELECT * FROM musician_instrument where i_ID = " +
           std::to_string(v[i]->getID()) + ") as a join musician_tracks as b\
 on a.m_ID = b.m_ID);";
    query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);

    int value = 0;
    if ((result = mysqlx_execute(query)) != NULL)
    {
      if ((row = mysqlx_row_fetch_one(result)) != NULL)
      {
        mysqlx_get_sint(row, 0, &x);
        value = x;
      }
      else
      {
        std::cout << "There was an error running the Query." << std::endl;
      }

      if (getIndex(manufacterers, v[i]->getBrand()) == -1)
      {
        manufacterers.push_back(v[i]->getBrand());
        count.push_back(value);
      }
      else
      {
        int index;
        if ((index = getIndex(manufacterers, v[i]->getBrand())) != -1)
          count[index] += x;
      }
    }
  }

  std::cout << "The most Popular Manufacterer is :" << manufacterers[findMax(count)] << std::endl;

  mysqlx_free(result);
  freeVector(v);
  return 0;
}

int DataBase::amountMusicianThroughoutYears()
{
  mysqlx_stmt_t *query;
  mysqlx_result_t *result;

  std::string qstr = "SELECT COUNT(*) FROM (SELECT * FROM musician  JOIN musician_tracks ON id_musician = m_ID group by m_ID) AS b;\0";
  query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
  {
    std::cout << "There was an error executing the Query" << std::endl;
    return -1;
  }

  mysqlx_row_t *row;
  int64_t x;

  if ((row = mysqlx_row_fetch_one(result)) != NULL)
  {
    mysqlx_get_sint(row, 0, &x);
    std::cout << "The amount of musicians recorded throughout the years is:\t" << x << std::endl
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

int getIndexInt(std::vector<int> v, int x)
{
  for (int i = 0; i < v.size(); ++i)
    if (v[i] == x)
      return i;
  return -1;
}

int DataBase::musicianCollaboratedMost()
{
  mysqlx_stmt_t *query;
  mysqlx_result_t *result;

  std::vector<int> musicians;
  std::vector<int> count;

  int64_t x;

  std::string qstr = "SELECT * FROM Track;\0";
  query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
  {
    std::cout << "There was an error executing the Query" << std::endl;
    return -1;
  }

  std::vector<Track *> v = initArray<Track>(result);

  for (int i = 0; i < v.size(); ++i)
  {
    int64_t value = 0;
    mysqlx_row_t *row;

    qstr = "select count(*) from musician_tracks where t_ID = " + std::to_string(v[i]->getID()) + " ;";
    query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);

    if ((result = mysqlx_execute(query)) != NULL)
    {
      if ((row = mysqlx_row_fetch_one(result)) != NULL)
      {
        mysqlx_get_sint(row, 0, &value);
        if (value > 1)
        {
          qstr = "select * from musician_Tracks where t_ID = '" + std::to_string(v[i]->getID()) + "';\0";
          query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);
          if ((result = mysqlx_execute(query)) != NULL)
          {
            do
            {
              while ((row = mysqlx_row_fetch_one(result)) != NULL)
              {
                mysqlx_get_sint(row, 0, &x);
                int index;
                if ((index = getIndexInt(musicians, x)) == -1)
                {
                  musicians.push_back(x);
                  count.push_back(value - 1);
                }
                else
                {
                  count[index] += (value - 1);
                }
              }
            } while (RESULT_OK == mysqlx_next_result(result));
            mysqlx_result_free(result);
          }
        }
      }
      else
      {
        std::cout << "There was an error running the Query." << std::endl;
      }
    }
  }

  if (musicians.size() == 0)
  {
    std::cout << "There was an error running the Query." << std::endl;
  }
  else
  {

    qstr = "select * from musician where id_musician = " + std::to_string(musicians[findMax(count)]) + ";\0";
    query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);

    if ((result = mysqlx_execute(query)) == NULL)
    {
      std::cout << "There was an error executing the Query" << std::endl;
      return -1;
    }

    std::vector<Musician *> m = initArray<Musician>(result);

    std::cout << "The musician who collaborated the most is: " << m[0]->getName() << std::endl;

    freeVector(m);
  }

  mysqlx_free(result);
  freeVector(v);
  return 0;
}

int DataBase::popularGenre()
{
  mysqlx_stmt_t *query;
  mysqlx_result_t *result;

  std::vector<std::string> genre;
  std::vector<int> count;

  mysqlx_row_t *row;
  int64_t x;

  std::string qstr = "SELECT * FROM Track;\0";
  query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
  {
    std::cout << "There was an error executing the Query" << std::endl;
    return -1;
  }

  std::vector<Track *> v = initArray<Track>(result);

  for (int i = 0; i < v.size(); ++i)
  {
    int index;
    if ((index = getIndex(genre, v[i]->getGenre())) == -1)
    {
      genre.push_back(v[i]->getGenre());
      count.push_back(1);
    }
    else
    {
      count[index]++;
    }
  }

  std::cout << "The most Popular Genre is :" << genre[findMax(count)] << std::endl;

  mysqlx_free(result);
  freeVector(v);
  return 0;
}

int DataBase::theMostTech(std::string start, std::string end)
{
  mysqlx_stmt_t *query;
  mysqlx_result_t *result;

  std::vector<std::string> tech;
  std::vector<int> count;

  mysqlx_row_t *row;
  int64_t x;

  std::string qstr = "select * from track where Date > '" + start + "' AND Date < '" + end + "';\0";
  query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
  {
    std::cout << "There was an error executing the Query" << std::endl;
    return -1;
  }

  std::vector<Track *> v = initArray<Track>(result);

  for (int i = 0; i < v.size(); ++i)
  {
    int index;

    if ((index = getIndex(tech, v[i]->getTech())) == -1)
    {
      tech.push_back(v[i]->getTech());
      count.push_back(1);
    }
    else
    {
      count[index]++;
    }
  }

  std::cout << "technician who worked on the most number of tracks :" << tech[findMax(count)] << std::endl;

  mysqlx_free(result);
  freeVector(v);
  return 0;
}

int DataBase::firstAlbum()
{
  mysqlx_stmt_t *query;
  mysqlx_result_t *result;

  std::vector<std::string> genre;
  std::vector<int> count;

  mysqlx_row_t *row;
  int64_t x;

  std::string qstr = "select * from Album where E_Date = (select min(E_Date) from album);\0";
  query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
  {
    std::cout << "There was an error executing the Query" << std::endl;
    return -1;
  }

  std::vector<Album *> v = initArray<Album>(result);

  std::cout << "The first album is :\t" << v[0]->getName() << std::endl;

  mysqlx_free(result);
  freeVector(v);
  return 0;
}

int DataBase::tracksInTwoAlbumsOrMore()
{
  mysqlx_stmt_t *query;
  mysqlx_result_t *result;

  int64_t x;

  std::string qstr = "SELECT * FROM Track;\0";
  query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
  {
    std::cout << "There was an error executing the Query" << std::endl;
    return -1;
  }

  std::vector<Track *> v = initArray<Track>(result);
  std::vector<Track *> choosen;

  for (int i = 0; i < v.size(); ++i)
  {
    int64_t value = 0;
    mysqlx_row_t *row;

    qstr = "select count(*) from Album_track where t_ID = " + std::to_string(v[i]->getID()) + ";";
    query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);

    if ((result = mysqlx_execute(query)) != NULL)
    {
      if ((row = mysqlx_row_fetch_one(result)) != NULL)
      {
        mysqlx_get_sint(row, 0, &value);
        if (value > 1)
        {
          choosen.push_back(v[i]);
        }
      }
      else
      {
        std::cout << "There was an error running the Query." << std::endl;
      }
    }
  }

  if (choosen.size() == 0)
  {
    std::cout << "There were no tracks that were in two or more albums." << std::endl;
  }
  else
  {
    std::cout << "The tracks that were in two or more albums :" << std::endl
              << std::endl;
    std::cout << "index\tID, Name, Music_Compuser, Length, Lyrics_Composer, Date, Genre, Technician" << std::endl;
    std::cout << "-----------------------------------------------------------------------------" << std::endl;

    for (int i = 0; i < choosen.size(); ++i)
    {
      std::cout << i << "\t" << *choosen[i] << std::endl;
    }
    std::cout << std::endl;
  }

  mysqlx_free(result);
  freeVector(v);
  return 0;
}

int DataBase::techniciansWorkedOnCompleteAlbum()
{
  mysqlx_stmt_t *query;
  mysqlx_result_t *result;

  std::vector<std::string> tech;
  std::vector<std::string> choosen;

  int64_t x;

  std::string qstr = "SELECT * FROM Track;\0";
  query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
  {
    std::cout << "There was an error executing the Query" << std::endl;
    return -1;
  }

  std::vector<Track *> v = initArray<Track>(result);

  for (int i = 0; i < v.size(); ++i)
  {
    if (getIndex(tech, v[i]->getTech()) == -1)
    {
      tech.push_back(v[i]->getTech());
    }
  }

  qstr = "SELECT * FROM Album;\0";
  query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
  {
    std::cout << "There was an error executing the Query" << std::endl;
    return -1;
  }

  std::vector<Album *> a = initArray<Album>(result);

  for (int i = 0; i < a.size(); ++i)
  {
    int albumLength = a[i]->getTracks();

    for (int j = 0; j < tech.size(); ++j)
    {
      int64_t value = 0;
      mysqlx_row_t *row;

      qstr = "select count(*) from track as a  join (select * from Album_track where a_ID = " + std::to_string(a[i]->getID()) + ")\
 as b on a.t_ID = b.t_ID\
 where Technician = '" +
             tech[j] + "';";
      query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);

      if ((result = mysqlx_execute(query)) != NULL)
      {
        if ((row = mysqlx_row_fetch_one(result)) != NULL)
        {
          mysqlx_get_sint(row, 0, &value);
          if (value == albumLength)
          {
            if (getIndex(choosen, tech[j]) == -1)
            {
              choosen.push_back(tech[j]);
            }
          }
        }
      }
    }
  }

  if (choosen.size() == 0)
  {
    std::cout << "There was an error running the Query." << std::endl;
  }
  else
  {
    std::cout << "The technicians that worked on complete albums are :" << std::endl;
    for (int i = 0; i < choosen.size(); ++i)
    {
      std::cout << choosen[i] << std::endl;
    }
    std::cout << std::endl;
  }

  mysqlx_free(result);
  freeVector(v);
  freeVector(a);
  return 0;
}

int DataBase::mostDiverseGenre()
{
  mysqlx_stmt_t *query;
  mysqlx_result_t *result;

  int max = -1;
  int index = -1;

  std::string qstr = "SELECT * FROM musician;\0";
  query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);

  if ((result = mysqlx_execute(query)) == NULL)
  {
    std::cout << "There was an error executing the Query" << std::endl;
    return -1;
  }

  std::vector<Musician *> v = initArray<Musician>(result);

  mysqlx_row_t *row;

  for (int i = 0; i < v.size(); ++i)
  {
    int64_t value;
    qstr = "select count(*) from track as a join (select * from musician_tracks where m_ID = " + std::to_string(v[i]->getID()) + ") as b on a.t_ID = b.t_ID group by Genre;";
    query = mysqlx_sql_new(this->session, qstr.c_str(), MYSQLX_NULL_TERMINATED);

    if ((result = mysqlx_execute(query)) != NULL)
    {
      if ((row = mysqlx_row_fetch_one(result)) != NULL)
      {
        mysqlx_get_sint(row, 0, &value);
        if (value > max)
        {
          index = i;
          max = value;
        }
      }
    }
  }

  if (index == -1 || max == -1)
    std::cout << "There was an error running the Query." << std::endl;
  else
    std::cout << "The musician with the most diverse musical genres is :" << v[index]->getName() << std::endl;

  mysqlx_free(result);
  freeVector(v);
  
  return 0;
}