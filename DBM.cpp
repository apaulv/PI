#include "DBM.h"

std::shared_ptr<DBM> DBM::instance = nullptr;

DBM::DBM(
	const std::string& host,
	const std::string& port,
	const std::string& schema,
	const std::string& username,
	const std::string& password)
{
	std::string address = host + ":" + port;

	driver = nullptr;
	conn = nullptr;
	stmt = nullptr;

	try
	{
		driver = get_driver_instance();

		conn = driver->connect(address, username, password);
		conn->setSchema(schema);
	}
	catch (const sql::SQLException& e)
	{
		printError(e);

		this->~DBM();

		throw sql::SQLException("Failed to connect to database.");
	}
}

void DBM::printError(const sql::SQLException& err)
{
	std::cout << "# ERR: SQLException in " << __FILE__;
	std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << "\n";
	std::cout << "# ERR: " << err.what();
	std::cout << " (MySQL error code: " << err.getErrorCode();
	std::cout << ", SQLState: " << err.getSQLState() << " )\n";
}

std::shared_ptr<DBM> DBM::getInstance(
	const std::string& host,
	const std::string& port,
	const std::string& schema,
	const std::string& username,
	const std::string& password)
{
	try
	{
		instance = std::make_shared<DBM>(DBM(host, port, schema, username, password));

		return instance;
	}
	catch (...)
	{
		return nullptr;
	}
}

sql::Statement* DBM::executeQuery(const std::string& query)
{
	sql::Statement* statement = nullptr;

	try
	{
		statement = conn->createStatement();

		if (!statement->execute(query))
		{
			throw sql::SQLException("Execution of statement: " + query + " failed.");
		}

		return statement;
	}
	catch (const sql::SQLException& e)
	{
		printError(e);
		std::cout << query;

		if (statement)
			delete statement;

		return nullptr;
	}
}

std::string DBM::getQuery(
	const std::string& queryType,
	const std::string& table,
	const std::string& data,
	const Filters& filter) const
{
	std::string query;

	if (queryType == "UPDATE")
	{
		query = std::string("UPDATE " + table + " SET " + data);
	}
	else if (queryType == "INSERT")
	{
		query = std::string("INSERT INTO " + table + " VALUES " + data);
	}
	else if (queryType == "DELETE")
	{
		query = std::string("DELETE FROM " + table);
	}
	else if (queryType == "SELECT")
	{
		query = std::string ("SELECT " + data + " FROM " + table);
	}

	if (!filter.empty())
	{
		unsigned index = 0;

		query += " WHERE ";

		for (const Filter& f : filter)
		{
			query += f.first + " = " + f.second;

			if (++index < filter.size())
			{
				query += " AND ";
			}
		}
	}

	query += ";";

	return query;
}

sql::ResultSet* DBM::runQuery(
	const QueryType& mode,
	const std::string& table,
	const std::string& data,
	const Filters& filter)
{
	std::string query = "";

	switch (mode)
	{
		case INSERT:
			query = getQuery("INSERT", table, data, Filters());
			break;
		case UPDATE:
			query = getQuery("UPDATE", table, data, filter);
			break;
		case DELETE:
			query = getQuery("DELETE", table, "", filter);
			break;
		case SELECT:
			query = getQuery("SELECT", table, data, filter);
			break;
		default:
			break;
	}

	if (stmt)
		delete stmt;
	stmt = executeQuery(query);

	if (mode == SELECT && stmt)
	{
		return stmt->getResultSet();
	}

	if (stmt)
		delete stmt;
	return nullptr;
}