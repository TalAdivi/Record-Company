#include <iostream>
#include <cstring>
#include <cstdlib>
#include "C:\Program Files\MySQL\Connector C++ 8.0\include\mysqlx\xapi.h"

using namespace std;

int main(int argc, char *argv[])
{
	mysqlx_error_t *err;

	if (argc < 4)
	{
		std::cout << "ERROR NO FILEDS" << std::endl;
		exit(-1);
	}

	mysqlx_session_t *sess = mysqlx_get_session(
		"localhost",
		DEFAULT_MYSQLX_PORT,
		argv[1],
		argv[2],
		argv[3],
		&err);

	if (err)
		cout << mysqlx_error_message(err) << "\t" << sess << endl;

	char c[256] = "";

	do
	{
		cout << endl
			 << endl;

		char tmp[256];
		cin.getline(tmp, 256);
		strcpy(c, tmp);

		cout << tmp << " " << c << " something" << endl;

		mysqlx_result_t *res = mysqlx_sql(sess, c, MYSQLX_NULL_TERMINATED);

		if (NULL != res)
		{
			char buff[256];
			size_t size = 0;

			do
			{
				mysqlx_row_t *row = mysqlx_row_fetch_one(res);
				while (NULL != row)
				{
					size = sizeof(buff);
					mysqlx_get_bytes(row, 0, 0, buff, &size);
					cout << buff << endl;
					row = mysqlx_row_fetch_one(res);
				}
			} while (RESULT_OK == mysqlx_next_result(res));
		}
		else
		{
			cerr << mysqlx_error_message(sess) << endl;
			exit(mysqlx_error_num(sess));
		}
	} while (strcmp(c, "stop") != 0);
	
	mysqlx_session_close(sess);

	getchar();
	return 0;
}