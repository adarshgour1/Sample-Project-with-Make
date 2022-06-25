#include "common_header.h"
#include "my_sql_header.h"
#include "connection_details.h"
using namespace std;

short ptr;

int main(int argc, char *argv[])
{
	if (argc >= 2)
		ptr = stoi(argv[1]);
	else
		ptr = 0;

	ios::sync_with_stdio(false);

	// defining connection variables
	string url = EXAMPLE_HOST;
	const string user = EXAMPLE_USER;
	const string password = EXAMPLE_PASS;
	const string database = EXAMPLE_DB;

	Log1 << "connection: [" << url << "]";
	Log1 << "user: [" << user << "]";
	Log1 << "password: [" << password << "]";
	Log1 << "database: [" << database << "]";

	std::string tempSqlString;
	stringstream sql;
	stringstream msg;

	try
	{
		sql::Driver *driver = get_driver_instance();
		std::unique_ptr<sql::Connection> con(driver->connect(url, user, password));
		std::unique_ptr<sql::Statement> stm(con->createStatement());

		tempSqlString = "USE Test";
		stm->execute(tempSqlString);

		tempSqlString = "select  id, fullname, address from Person order by id";
		std::unique_ptr<sql::ResultSet> res(stm->executeQuery(tempSqlString));

		if (res->rowsCount() == 0)
		{
			Log1 << "No Rows found";
			msg.str("");
			msg << "Error No row found";
			throw runtime_error(msg.str());
		}

		Log1 << "No of Rows found " << res->rowsCount();

		while (res->next())
		{
			Log1 << "id: " << res->getInt(1) << " "
				 << "FullName: " << res->getString(2) << " "
				 << "Address: " << res->getString(3);
		}
	}
	catch (sql::SQLException &e)
	{
		Log0 << "SQL Exception: [" << e.getErrorCode() << "] " << e.what();
		return EXIT_FAILURE;
	}
	catch (std::runtime_error &e)
	{
		Log0 << "Run tme error exception: [" << e.what();
		return EXIT_FAILURE;
	}

	Log0 << "Code completed successfully exiting..."
		 << "\n";
	return EXIT_SUCCESS;
}
