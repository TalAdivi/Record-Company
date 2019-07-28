/* insert musucians data */

INSERT INTO `musician` (`id_musician`, `Name`, `Address`, `Phone`, `Skill`) VALUES 
 (1, 'Beethover', 'Austria', '098-909985', 'Player') ,
 (2, 'Michael Jackson' ,'Los Angeles', '098-373489', 'Singer & Player'),
 (3, 'James Cameron' ,'Los Angeles', '067-758937', 'Player'),
 (4, 'Ice-T' ,'New York', '068-374838', 'Singer'),
 (5, 'P-Dog' ,'New York', '098-373489', 'Singer'),
 (6, 'Roger Waters' ,'London', '096-388389', 'Singer & Player'),
 (7, 'p!nk', 'Las Vegas' , '123-868729', 'Singer & Player'),
 (8, 'Freddy Mercury', 'London', '028-959395', 'Singer & Player'),
 (9, 'ABBA', 'Sweden', '634-850258', 'Singer & Player'),
 (10, 'Danny Gonzales', 'Oragon', '078-123963', 'Singer'),
 (11, 'TMG', 'Los Angeles', '063-847492', 'Singer');

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
 (10, 'Thriller','Michael Jackson',217,'Freddy Mercury','1984-01-23','Pop','AudioCloud');

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
 (10, 'Its Brittney', '2004-01-10', '2004-01-20', 1);

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
 (10, 'Arif Mardin');

/* insert musician instruments relation data */

INSERT INTO `musician_instrument` (`m_ID`, `i_ID`) VALUES
 (1,1),
 (2,2),
 (2,5),
 (3,10),
 (6,1),
 (6,6),
 (7,5),
 (7,6),
 (8,1),
 (8,2),
 (9,1),
 (9,5),
 (9,8);

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
 (8,3);

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
 (10,9);

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
 (10,9);