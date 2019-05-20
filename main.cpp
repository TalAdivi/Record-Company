#include <iostream>
#include "C:\Program Files\MySQL\Connector C++ 8.0\include\mysqlx\xapi.h"

using namespace std;
int main(int argc, char* argv[]) {
	mysqlx_error_t* err;

	if(argc < 4)
	{
		std::cout << "ERROR NO FILEDS" << std::endl;
		exit(-1);
	}	

	mysqlx_session_t* sess = mysqlx_get_session(
		"localhost", 
		DEFAULT_MYSQLX_PORT, 
		argv[1], 
		argv[2],
		argv[3], 
		&err
		);
		
	cout << mysqlx_error_message(err) << "\t" << sess << endl;

	mysqlx_session_close(sess);

	getchar();
	return 0;
}