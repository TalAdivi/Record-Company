#include "DBManager.hpp"

int userInterface(DataBase &db);
extern int correctFormat(std::string date);

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		std::cout << "Please insert connection details" << std::endl;
		exit(-1);
	}

	DataBase db(argv[1], argv[2]);

	if (db.connect() == -1)
	{
		std::cout << "Incorrect connnection made please reacheck username and password" << std::endl;
		exit(-1);
	}

	std::cout << "Connected successfully" << std::endl;

	if (db.init() == -1)
	{
		std::cout << "There was an error with DB initlization" << std::endl;
		exit(-1);
	}

	std::cout << "DB initlized successfully" << std::endl;

	if (db.build() == -1)
	{
		std::cout << "There was an error with Data initlization" << std::endl;
		exit(-1);
	}

	std::cout << "Data inserted successfully" << std::endl;

	userInterface(db);
	return 0;
}

int userInterface(DataBase &db)
{
	bool flag = true;
	std::string tmp1;
	std::string tmp2;
	std::string clear;

	std::cout << std::endl
			  << std::endl
			  << "Welcome to MusicCompany project" << std::endl
			  << " ---------------------------------------------------------------------- " << std::endl
			  << std::endl;
	int choice = 0;
	do
	{
		std::cout << " 1.\tHow many albums were created between two given dates\n\
 2.\tHow many songs recored by a specific musician between two given dates\n\
 3.\tHow many diffrent albums recorded specific musician between two given dates\n\
 4.\tWhat is the most popular instrument\n\
 5.\tList of instruments used in a specific album\n\
 6.\tThe most popular album producer between two given dates\n\
 7.\tThe most popular manufacturer of an instrument\n\
 8.\tHow many musicians recorded throughout the years\n\
 9.\tThe musician who collaborated the most\n\
 10.\tThe most popular music genre\n\
 11.\tThe technician who worked on the most number of tracks between two given dates\n\
 12.\tThe first album ever recorded\n\
 13.\tList of tracks that were in two or more albums\n\
 14.\tList of technicians that worked on complete albums\n\
 15.\tThe musician with the most diverse musical genres \n\
 16.\tExit Program.\n\n\
		" << std::endl;
		std::cout << "Please choose function by number >\t";
		std::cin >> choice;
		std::cout << std::endl;

		switch (choice)
		{
		case 1:
			std::cout << "Please input the two dates ( Year-Month-Day )" << std::endl
					  << std::endl;
			std::cin >> tmp1 >> tmp2;
			std::cout << std::endl;
			if (correctFormat(tmp1) == -1 || correctFormat(tmp2) == -1)
				std::cout << "incorrect date format please re-try" << std::endl;
			else
			{
				if (db.albumsBetween(tmp1, tmp2) == -1)
					std::cout << "Error occured while executing the sql query" << std::endl;
				std::cout << std::endl
						  << "Press any key to continue..."
						  << std::endl;
				getchar();
				getchar();
				std::cout << std::endl;
			}
			break;

		case 2:
			while (1)
			{
				std::cout << "Plese input musician name" << std::endl;
				std::getline(std::cin, clear);
				std::getline(std::cin, tmp1);
				std::cout << std::endl;
				if (db.musicianSongBetween(tmp1) != 2)
					break;
			}
			std::cout << std::endl
					  << "Press any key to continue..."
					  << std::endl;
			getchar();
			getchar();
			std::cout << std::endl;
			break;

		case 3:
			while (1)
			{
				std::cout << "Plese input musician name" << std::endl;
				std::getline(std::cin, clear);
				std::getline(std::cin, tmp1);
				std::cout << std::endl;
				if (db.musicianAlbumBetween(tmp1) != 2)
					break;
			}
			std::cout << std::endl
					  << "Press any key to continue..."
					  << std::endl;
			getchar();
			getchar();
			std::cout << std::endl;
			break;

		case 4:
			if (db.popularInstrument() == -1)
			{
				std::cout << "Error occured while executing the sql query" << std::endl;
			}
			std::cout << std::endl
					  << "Press any key to continue..."
					  << std::endl;
			getchar();
			getchar();
			std::cout << std::endl;
			break;

		case 5:
			while (1)
			{
				std::cout << "Plese input Album name" << std::endl;
				std::getline(std::cin, clear);
				std::getline(std::cin, tmp1);
				std::cout << std::endl;
				if (db.instrumentsInAlbum(tmp1) != 2)
					break;
			}
			std::cout << std::endl
					  << "Press any key to continue..."
					  << std::endl;
			getchar();
			getchar();

			std::cout << std::endl;
			break;

		case 6:
			std::cout << "Please input the two dates ( Year-Month-Day )" << std::endl
					  << std::endl;
			std::cin >> tmp1 >> tmp2;
			std::cout << std::endl;
			if (correctFormat(tmp1) == -1 || correctFormat(tmp2) == -1)
				std::cout << "incorrect date format please re-try" << std::endl;
			else
			{
				if (db.producerOfAlbumBetween(tmp1, tmp2) == -1)
					std::cout << "Error occured while executing the sql query" << std::endl;
				std::cout << std::endl
						  << "Press any key to continue..."
						  << std::endl;
				getchar();
				getchar();
				std::cout << std::endl;
			}
			break;

		case 7:
			if (db.popularManufacterer() == -1)
			{
				std::cout << "Error occured while executing the sql query" << std::endl;
			}
			std::cout << std::endl
					  << "Press any key to continue..."
					  << std::endl;
			getchar();
			getchar();
			std::cout << std::endl;
			break;

		case 8:
			if (db.amountMusicianThroughoutYears() == -1)
			{
				std::cout << "Error occured while executing the sql query" << std::endl;
			}
			std::cout << std::endl
					  << "Press any key to continue..."
					  << std::endl;
			getchar();
			getchar();
			std::cout << std::endl;
			break;

		case 9:
			if (db.musicianCollaboratedMost() == -1)
			{
				std::cout << "Error occured while executing the sql query" << std::endl;
			}
			std::cout << std::endl
					  << "Press any key to continue..."
					  << std::endl;
			getchar();
			getchar();
			std::cout << std::endl;
			break;

		case 10:
			if (db.popularGenre() == -1)
			{
				std::cout << "Error occured while executing the sql query" << std::endl;
			}
			std::cout << std::endl
					  << "Press any key to continue..."
					  << std::endl;
			getchar();
			getchar();
			std::cout << std::endl;
			break;

		case 11:
			std::cout << "Please input the two dates ( Year-Month-Day )" << std::endl
					  << std::endl;
			std::cin >> tmp1 >> tmp2;
			std::cout << std::endl;
			if (correctFormat(tmp1) == -1 || correctFormat(tmp2) == -1)
				std::cout << "incorrect date format please re-try" << std::endl;
			else
			{
				if (db.theMostTech(tmp1, tmp2) == -1)
					std::cout << "Error occured while executing the sql query" << std::endl;
				std::cout << std::endl
						  << "Press any key to continue..."
						  << std::endl;
				getchar();
				getchar();
				std::cout << std::endl;
			}
			break;

		case 12:
			if (db.firstAlbum() == -1)
			{
				std::cout << "Error occured while executing the sql query" << std::endl;
			}
			std::cout << std::endl
					  << "Press any key to continue..."
					  << std::endl;
			getchar();
			getchar();
			std::cout << std::endl;
			break;

		case 13:
			if (db.tracksInTwoAlbumsOrMore() == -1)
			{
				std::cout << "Error occured while executing the sql query" << std::endl;
			}
			std::cout << std::endl
					  << "Press any key to continue..."
					  << std::endl;
			getchar();
			getchar();
			std::cout << std::endl;
			break;

		case 14:
			if (db.techniciansWorkedOnCompleteAlbum() == -1)
			{
				std::cout << "Error occured while executing the sql query" << std::endl;
			}
			std::cout << std::endl
					  << "Press any key to continue..."
					  << std::endl;
			getchar();
			getchar();
			std::cout << std::endl;
			break;

		case 15:
			if (db.mostDiverseGenre() == -1)
			{
				std::cout << "Error occured while executing the sql query" << std::endl;
			}
			std::cout << std::endl
					  << "Press any key to continue..."
					  << std::endl;
			getchar();
			getchar();
			std::cout << std::endl;
			break;

		case 16:
			flag = false;
			std::cout << std::endl
					  << std::endl
					  << "Goodbye" << std::endl;
			break;

		default:
			std::cout << "Incorrect number ! this choice does not exist please re enter" << std::endl;
			break;
		}
		std::cout << std::endl
				  << " ---------------------------------------------------------------------- " << std::endl
				  << std::endl;
	} while (flag);

	return 1;
}