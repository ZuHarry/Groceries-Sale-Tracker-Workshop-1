#pragma once
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <vector>
#include "Item.h"
#include "Category.h"

class Transaction
{
public:

	std::string dateTime;
	int transactionId, userId;
	double subtotal;

	std::vector<std::pair<Item, int>> items; // pair of product and its quantity, represents the transaction_item table
	//std::vector<std::pair<Category, int>> categories; // pair of product and its quantity, represents the transaction_item table

	Transaction();
	void addItem(Item item, int quantity);

	void insert(double subtotal1);
	double total();
	int count();
};


#endif
