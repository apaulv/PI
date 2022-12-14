#pragma once

// Including dependencies
#include <memory>
#include <utility>
#include <string>
#include <map>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class DBM
{
private:
	static std::shared_ptr<DBM> instance;

	sql::Driver* driver;
	sql::Connection* conn;
	sql::Statement* stmt;

	typedef std::map<std::string, std::string> Filters;
	typedef std::pair<std::string, std::string> Filter;

	void printError(const sql::SQLException& err);

	explicit DBM(
		const std::string& host,
		const std::string& port,
		const std::string& schema,
		const std::string& username,
		const std::string& password);

	std::string getQuery(
		const std::string& queryType,
		const std::string& table,
		const std::string& data,
		const Filters& filter) const;

	sql::Statement* executeQuery(const std::string& query);

public:
	enum QueryType
	{
		UPDATE,
		INSERT,
		DELETE,
		SELECT
	};

	virtual ~DBM() = default;


	
	
	
	static std::shared_ptr<DBM> getInstance(
		const std::string& host,
		const std::string& port,
		const std::string& schema,
		const std::string& username,
		const std::string& password);
	
	sql::ResultSet* runQuery(
		const QueryType& mode,
		const std::string& table,
		const std::string& data,
		const Filters& filter);
};

