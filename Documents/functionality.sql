/*1*/

select count(*) from album where E_Date < "2017-01-01" AND E_Date > "2004-01-01";

/*2*/

select count(*) from track as t join musician_tracks on musician_tracks.m_ID = (select musician.id_musician from musician where name = "ABBA")
where t.Date < "2019-07-26" and t.Date > "1990-01-01";

/*3*/

select count(*) from (select a_ID from( (select * from album_track) as a INNER JOIN
(select * from musician_tracks where musician_tracks.m_ID = (select musician.id_musician from musician where name = "TMG")) as b
on a.t_ID = b.t_ID) group by a_ID ) as c;

/*4*/

SELECT * FROM instrument;
	foreach(i in instruments) //make instruments array using parsing function of prev results
		x = SELECT count(*) from (
(SELECT * FROM musician_instrument where i_ID = 1) as a join musician_tracks as b 
on a.m_ID = b.m_ID);
		if (max < x)
			max_index = index;
			max = x;


/*5*/
select * from album where name = name;
//might be duplicates

select * from instrument where I_id = 
(select i_ID from musician_instrument as mi join 
(select m_ID from Album_Track as a  join musician_tracks as b on a.t_ID = b.t_ID where a.a_id = 1) 
as mb on mi.m_ID = mb.m_ID);


/*6*/

SELECT * FROM producers;
	foreach(p in producers) //make producers array using parsing function of prev results
		x = select count(*) from (
(SELECT * FROM album_producer where p_ID = 1) as a join album as b on a.a_ID = b.A_id )
where E_Date  > "2015-04-14" and E_Date < "2019-04-15";
		if (max < x)
			max_index = index;
			max = x;


/*7*/
manufacturer[];
countarray[];
		
SELECT * FROM instrument;
	foreach(i in instruments) //make instruments array using parsing function of prev results
		x = SELECT count(*) from (
(SELECT * FROM musician_instrument where i_ID = 1) as a join musician_tracks as b 
on a.m_ID = b.m_ID);

		if( !i.manufacturer exists in array )
			array.push(i.manufacturer);
			countarray.push(x);
		else
			i getindex(i.manufacturer);
			countarray[i] += x;
		
maxindex = getmax(countarray);
return manufacturer[maxindex];


/*8*/
select count(*) from (select * from musician join musician_tracks on id_musician = m_ID group by m_ID) as b;


/*9*/
musicians[];
countm[];

select * from tracks select * from track;
	foreach( t in tracks)
		res = select *  from musician_Tracks where t_ID = 2;
		count = select count(*)  from musician_Tracks where t_ID = 2;

		if( count < 2)
			continue;

		for(res != null)
			if(res.id not exist)
				musicians.push(res.id)
				push(count-1)
			else 
				i = getindex(res.id);
				countm[i]+=count-1;
				
find max of countm
return select * from musician where id_musician = musicians[index of max];


/*10*/

genre[];
countm[];

	select * from tracks // inits an array 
		foreach track
			if( !genre exists in array )
				push(ganre);
				count push(1);
			else
				i = getindex(ganre)
				count[i]++;

find max count
return genre[index of max];

/*11*/

tech[];
countm[];

	select * from tracks where date < ? and date > ?;
		foreach track
			if( !tech exists in array )
				push(tech);
				count push(1);
			else 
				i = getindex(tech)
				count[i]++;

find max count
return tech[index of max];


/*12*/

select * from Album where E_Date = (select min(E_Date) from album);

/*13*/

Select * from tracks; // inits tracks array 
	foreach track in tracks
		x = select count(*) from Album_track where t_ID = 1;
		if ( x > 1)
			print ;


/*14*/

select * from tracks ;
create array of tech names;

tech[];

select * from Albums  // inits array of albums 
	foreach Album in albums
		print ( in album Album : )
		x = album.length;
		for each tech in technames
			y = select count(*) from track as a  join (select * from Album_track where a_ID = 5) 
			as b on a.T_id = b.t_ID 
			where Technician = 'Cody Ko';
			if ( y == x )
				print tech;

				
/*15*/

init array of musicians

max;
index;

foreach musician; // init musician array
	x =select count(*) from track as a join (select * from musician_tracks where m_ID = 8) as b on a.T_id = b.t_ID group by Genre;

	if max < x
		max = x
		id = i;
		
return musician[i];
