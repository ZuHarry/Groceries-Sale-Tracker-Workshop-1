/*


	NAME			:	MUHAMMAD ZUHAIRY BIN RAZALY
	MATRIX NUMBER	:	B032310282
	COURSE			:	BITS
	TOPIC			:	GROCERIES SALE TRACKER
	CURRENT FILE	:	Category.h file


*/

#pragma once
#ifndef CATEGORY_H
#define	CATEGORY_H

#include <string>
#include <vector>
#include "DBConnection.h"

class Category
{
public: //access specifier
	int categoryId;
	std::string categoryName, categoryDesc; //text attributes

	void update_category();

	Category(); //consructor method
	Category(int categoryId, std::string categoryName, std::string categoryDesc);
	Category(sql::ResultSet* data);

	void insert_category();

	//~Category();//destructor method

	static std::vector<Category> findCategory();
	static std::vector<Category> findCategorybyName(std::string categoryName);
	static std::vector<Category> findCategorybyId(int categoryId);

};

#endif

