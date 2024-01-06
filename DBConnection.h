/*


	NAME			:	MUHAMMAD ZUHAIRY BIN RAZALY
	MATRIX NUMBER	:	B032310282
	COURSE			:	BITS
	TOPIC			:	GROCERIES SALE TRACKER
	CURRENT FILE	:	DBConnection.h file


*/


#pragma once
#ifndef DBConnection_H
#define DBConnection_H
#include <mysql/jdbc.h>
#include <string>
class DBConnection
{

public:
	DBConnection();
	~DBConnection();
	void prepareStatement(std::string query);
	sql::PreparedStatement* stmt;
	sql::ResultSet* res;
	void QueryStatement(); // have no result
	void QueryResult(); // it has result
	int getGeneratedId();

private:
	sql::Connection* connection;

};


#endif // !DBConnection_H