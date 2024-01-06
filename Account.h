/*


	NAME			:	MUHAMMAD ZUHAIRY BIN RAZALY
	MATRIX NUMBER	:	B032310282
	COURSE			:	BITS
	TOPIC			:	GROCERIES SALE TRACKER
	CURRENT FILE	:	Account.h file


*/

#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account
{
public://access specifier
	int accountId, yearOfBirth; //numerical attributes
	std::string username, password, fullname, shopname, telephone; // text attributes


	Account(); // constructor method
	Account(int accountId, int yearOfBirth, std::string username, std::string password, std::string fullname, std::string shopname, std::string telephone);

	bool login();
	void insert();
	void update();
	void remove();
	int getAge();

	~Account(); //destructor method


	static Account older(Account a, Account b);


};

#endif

