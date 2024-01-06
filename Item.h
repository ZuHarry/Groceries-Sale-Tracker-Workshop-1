/*


	NAME			:	MUHAMMAD ZUHAIRY BIN RAZALY
	MATRIX NUMBER	:	B032310282
	COURSE			:	BITS
	TOPIC			:	GROCERIES SALE TRACKER
	CURRENT FILE	:	Item.h file


*/

#pragma once
#ifndef ITEM_H
#define	ITEM_H

#include <string>
#include <vector>
#include "DBConnection.h"

class Item
{

public: //access specifier
	int itemId, categoryId;
	double itemPrice; //numerical attributes
	std::string itemName, category; //text attributes

	Item(); //consructor method
	Item(int itemId, double itemPrice, std::string itemName, int categoryId);
	Item(sql::ResultSet* data);

	void insert_item();
	void update_item();
	void remove_item(int itemId);
	void item_details();

	//~Item();//destructor method

	static Item findItem(int itemId);
	static Item findItemSale(int itemId);
	static Item findItemSaleCategory(int itemId, int categoryId);
	static Item findItem(std::string itemName);

	static std::vector<Item> findItem();
	static std::vector<Item> findItembyName(std::string itemName);
	static std::vector<Item> findItembyId(int itemId);
	static std::vector<Item> findItembyIdSale(int itemId);
	static std::vector<Item> findItembyCategory(int categoryId);

};

#endif
