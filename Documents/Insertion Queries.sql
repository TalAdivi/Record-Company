/* insert musucians data */

INSERT INTO `musician` (`id_musician`, `Name`, `Address`, `Phone`, `Skill`) VALUES
 (1, 'Guns And Roses', 'Austria', '098-909985', 'Singer & Player') ,
 (2, 'Michael Jackson' ,'Los Angeles', '098-373489', 'Singer & Player'),
 (3, 'Meir Banai' ,'Israel', '067-758937', 'Singer & Player'),
 (4, 'Ice-T' ,'New York', '068-374838', 'Singer'),
 (5, 'Lana Del Rey' ,'Paris', '098-373489', 'Singer'),
 (6, 'Hozier' ,'London', '096-388389', 'Singer & Player'),
 (7, 'p!nk', 'Las Vegas' , '123-868729', 'Singer & Player'),
 (8, 'Freddy Mercury', 'London', '028-959395', 'Singer & Player'),
 (9, 'Bryan Adams', 'Sweden', '634-850258', 'Singer & Player'),
 (10, 'Red Hot Chili Peppers', 'Los Angeles', '078-123963', 'Singer & Player'),
 (11, 'Infected Mushroom', 'Israel', '063-847492', 'Singer'),
 (12, 'Usher', 'New York', '745-942489', 'Singer'),
 (13, 'Bob Marley', 'Jamaica', '097-125613', 'Singer'),
 (14, 'Eminem', 'New York', '101-331015', 'Singer'),
 (15, 'Berry Sakharof', 'Israel', '056-129314', 'Singer');

/* insert tracks data */

INSERT INTO `track` (`T_id`, `Name`, `Music_Compuser`, `Length`, `Lyrics_Composer`, `Date`, `Genre`, `Technician`) VALUES
 (1, 'Ode to Joy', 'Beethoven', 220, 'NULL', '1824-01-01', 'Classical', 'Beethoven'),
 (2, 'We Will Rock You','Queen',250,'Freddy Mercury','1977-10-07','Rock','Bill McGree'),
 (3, 'Toxic','Jack Hallow',164,'Kelsey Lowe','2004-01-13','Pop','Bill McGree'),
 (4, 'Johnny Johnny','Danny Gonzales',203,'Danny Gonzales','2017-06-21','Comedy','AudioCloud'),
 (5, 'Slime','Danny Gonzales',189,'Danny Gonzales','2018-01-17','Comedy','AudioCloud'),
 (6, 'No Flex','Noel Miller',89,'Noel Miller','2016-12-29','Rap','Cody Ko'),
 (7, 'Walkman','Noel Miller',197,'Cody Ko','2018-11-25','Rap','Cody Ko'),
 (8, 'Short King Anthem','Noel Miller',192,'Noel Miller','2019-02-14','Rap','Cody Ko'),
 (9, 'Disco Queen','Bjorn and Benny',184,'Bjorn and Benny','1975-08-04','Pop','Bill McGree'),
 (10, 'Thriller','Michael Jackson',217,'Freddy Mercury','1984-01-23','Pop','AudioCloud'),
 (11, 'Lobster','Berry Sakharof',184,'Balkan Beat Box','2018-08-04','Pop','Yossi Elgrabli'),
 (12, 'Lose Yourself','Eminem',230,'Eminem','2000-09-01','Rap','Eminem'),
 (13, 'Love The Way You Lie','Eminem',254,'Eminem','1993-11-02','Rap','Eminem'),
 (14, 'Not Afraid','Eminem',200,'Eminem','1995-01-02','Rap','Eminem'),
 (15, 'Castle','Eminem',212,'Eminem','2012-02-29','Rap','Eminem'),
 (16, 'Till I Collapse','Eminem',193,'Eminem','2002-06-09','Rap','Eminem'),
 (17, 'Babylon System', 'Bob Marley', 240, 'Bob Marley', '1980-12-22', 'Ragay', 'Rastaman'),
 (18, 'No Woman No Cry', 'Bob Marley', 212, 'Bob Marley', '1982-03-12', 'Ragay', 'Rastaman'),
 (19, 'Yeah!', 'Usher', 193, 'Usher', '1992-05-11', 'Rap', 'Terry A. Farris'),
 (20, 'My Boo!', 'Usher', 201, 'Usher', '2002-09-17', 'Rap', 'Terry A. Farris'),
 (21, 'Cities Of The Future', 'Tomer Sason', 320, 'Tomer Sason', '2007-01-27', 'Electronic', 'Infected Mushroom'),
 (22, 'Californication', 'Red Hot Chili Peppers', 203, 'Red Hot Chili Peppers', '1994-08-07', 'Funk', 'AudioCloud'),
 (23, 'Snow', 'Red Hot Chili Peppers', 243, 'Red Hot Chili Peppers', '1990-04-28', 'Funk', 'AudioCloud'),
 (24, 'Heaven', 'Brayen Adams', 189, 'Brayen Adams', '1991-02-09', 'Rock', 'dickbutt');

/* insert albums data */

INSERT INTO `album` (`A_id`, `Name`, `S_Date`, `E_Date`, `Tracks_Number`) VALUES
 (1, 'Ode to Joy RErelease', '2015-04-15', '2015-04-29', 1),
 (2, 'Johnny Johnny SINGLE', '2017-06-20', '2017-07-01', 1),
 (3, 'Slime SINGLE', '2018-01-15', '2018-02-02', 1),
 (4, 'Danny the Collection', '2019-01-01', '2019-01-15', 2),
 (5, 'TMG', '2016-12-20', '2019-02-20', 3),
 (6, 'Diso Queen SINGLE', '1975-08-04', '1975-08-05', 1),
 (7, 'Thriller SINGLE', '1984-01-20', '1984-01-26', 1),
 (8, 'Pop Supreme', '2016-05-28', '2016-06-10', 3),
 (9, 'Record Star', '2019-07-07', '2019-07-30', 10),
 (10, 'Its Brittney', '2004-01-10', '2004-01-20', 1),
 (11, 'The Slim Shady', '1990-06-23', '1999-06-23', 5),
 (12, 'Live Forever', '1975-01-28', '1970-10-14', 2),
 (13, '8701', '2000-11-08', '2001-02-09', 2),
 (14, 'Converting Vegetarians', '2010-12-23', '2015-02-09', 1),
 (15, 'By The Way', '2001-04-15', '2002-11-30', 2),
 (16, 'Get Up', '2012-07-01', '2015-03-19', 1);

/* insert instruments data */

INSERT INTO `instrument` (`I_id`, `Brand`, `Type`) VALUES
 (1, 'Yamhaa', 'Piano'),
 (2, 'Yamhaa', 'Synth'),
 (3, 'Gibson', 'Bass'),
 (4, 'Fender', 'Bass'),
 (5, 'Gibson', 'Guitar'),
 (6, 'Fender', 'Guitar'),
 (7, 'Epiphone', 'Guitar'),
 (8, 'Gretch', 'Drums'),
 (9, 'Ludwig', 'Drums'),
 (10, 'Remo', 'Tambourine');

/* insert producers data */

INSERT INTO `producer` (`p_ID`, `Name`) VALUES
 (1, 'Bill McGree'),
 (2, 'Dr Dre'),
 (3, 'Jay-Z'),
 (4, 'Rick Rubin'),
 (5, 'George Martin'),
 (6, 'Joe Meek'),
 (7, 'Quincy Jones'),
 (8, 'Phil Spector'),
 (9, 'Butch Vig'),
 (10, 'Arif Mardin'),
 (11, 'Rick Rubin'),
 (12, 'Erez Eisen');

/* insert musician instruments relation data */

INSERT INTO `musician_instrument` (`m_ID`, `i_ID`) VALUES
 (1,1),
 (1,3),
 (1,8),
 (2,2),
 (2,5),
 (3,5),
 (6,1),
 (6,6),
 (7,5),
 (7,6),
 (8,1),
 (8,2),
 (9,1),
 (9,5),
 (9,8),
 (10,1),
 (10,5),
 (10,8);

/* insert musucians tracks relation data */

INSERT INTO `musician_tracks` (`m_ID`, `t_ID`) VALUES
 (1,1),
 (2,10),
 (3,10),
 (8,2),
 (9,9),
 (7,3),
 (10,4),
 (10,5),
 (11,6),
 (11,7),
 (11,8),
 (4,6),
 (6,2),
 (8,3),
 (15,11),
 (14,12),
 (14,13),
 (14,14),
 (14,15),
 (14,16),
 (13,17),
 (13,18),
 (12,19),
 (12,20),
 (11,21),
 (10,22),
 (10,23),
 (9,24);

/* insert album tracks relation data */

INSERT INTO `album_track`(`t_ID`, `a_ID`) VALUES
 (1,1),
 (4,2),
 (5,3),
 (4,4),
 (5,4),
 (6,5),
 (7,5),
 (8,5),
 (9,6),
 (10,7),
 (3,8),
 (9,8),
 (10,8),
 (3,10),
 (1,9),
 (2,9),
 (3,9),
 (4,9),
 (5,9),
 (6,9),
 (7,9),
 (8,9),
 (9,9),
 (10,9),
 (12,11),
 (13,11),
 (14,11),
 (15,11),
 (16,11),
 (17,12),
 (18,12),
 (19,13),
 (20,13),
 (21,14),
 (22,15),
 (23,15),
 (24,16);

/* insert album producers relation data */

INSERT INTO `album_producer` (`a_ID`,`p_ID`) VALUES
 (1,1),
 (2,2),
 (3,2),
 (3,1),
 (4,1),
 (4,2),
 (4,3),
 (5,2),
 (5,6),
 (6,4),
 (6,5),
 (8,4),
 (8,5),
 (8,6),
 (9,1),
 (9,7),
 (9,10),
 (10,9),
 (11,2),
 (12,9),
 (13,3),
 (14,12),
 (15,11),
 (16,1);