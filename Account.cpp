/*


	NAME			:	MUHAMMAD ZUHAIRY BIN RAZALY
	MATRIX NUMBER	:	B032310282
	COURSE			:	BITS
	TOPIC			:	GROCERIES SALE TRACKER
	CURRENT FILE	:	Account.cpp file


*/

#include "Account.h"
#include <ctime>
#include "DBConnection.h" 
using namespace std;

Account::Account() {
	//initialize
	accountId = 0;
	yearOfBirth = 0;
	username = "";
	password = "";
	fullname = "";
	shopname = "";
	telephone = "";
}
Account::Account(int accountId, int yearOfBirth, std::string username, std::string password, std::string fullname, std::string shopname, std::string telephone) {
	this->accountId = accountId;
	this->yearOfBirth = yearOfBirth;
	this->username = username;
	this->password = password;
	this->fullname = fullname;
	this->fullname = shopname;
	this->telephone = telephone;
}
bool Account::login() {

	DBConnection db;
	db.prepareStatement("SELECT * FROM account WHERE username=? AND password=?");
	db.stmt->setString(1, username);
	db.stmt->setString(2, password);
	db.QueryResult();
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			accountId = db.res->getInt("account_id");
			username = db.res->getString("username");
			password = db.res->getString("password");
			fullname = db.res->getString("fullname");
			shopname = db.res->getString("shopname");
			telephone = db.res->getString("telephone");
			yearOfBirth = db.res->getInt("yearOfBirth");
		}
		db.~DBConnection();
		return true;
	}
	else {

		db.~DBConnection();
		return false;
	}
}
void Account::insert() {

	DBConnection db;//instantiate
	db.prepareStatement("Insert into account (username,password,fullname,shopname,telephone,yearOfBirth) VALUES (?,?,?,?,?,?)");
	db.stmt->setString(1, username); 
	db.stmt->setString(2, password);
	db.stmt->setString(3, fullname);
	db.stmt->setString(4, shopname);
	db.stmt->setString(5, telephone);
	db.stmt->setInt(6, yearOfBirth);
	db.QueryStatement();
	db.~DBConnection();
}
void Account::update() {

	DBConnection db;
	db.prepareStatement("UPDATE account SET username=?, password=?, fullname=?, shopname=?, telephone=?, yearOfBirth=? WHERE account_id=?");
	db.stmt->setString(1, username);
	db.stmt->setString(2, password);
	db.stmt->setString(3, fullname);
	db.stmt->setString(4, shopname);
	db.stmt->setString(5, telephone);
	db.stmt->setInt(6, yearOfBirth);
	db.stmt->setInt(7, accountId);
	db.QueryStatement();
	db.~DBConnection();

}
void Account::remove() {
	DBConnection db;
	db.prepareStatement("DELETE FROM account WHERE account_id=?");
	db.stmt->setInt(1, accountId);
	db.QueryStatement();
	db.~DBConnection();
}
int Account::getAge() {
	if (yearOfBirth == 0) {
		return 0;
	}
	time_t current = time(0); // get time in epoch seconds (since 1900)
	tm now; // create a struct/object of tm to hold data
	localtime_s(&now, &current); //populate the now object with data from current

	return (now.tm_year + 1900) // +1900 to the epoch year to get current year
		- yearOfBirth; // minus user year of birth to get their age
}



Account::~Account() {

}


Account Account::older(Account a, Account b) {
	if (b.getAge() > a.getAge()) {
		return b;
	}
	return a;
}
