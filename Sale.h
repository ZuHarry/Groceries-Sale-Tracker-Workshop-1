#pragma once
#ifndef SALE_H
#define SALE_h

#include <string>
#include <vector>
#include "DBConnection.h"

class Sale
{
public:
	int saleId, userId;

	double subtotal; //numerical attributes
	std::string itemName, category; //text attributes


	Sale(); //consructor method
	Sale(int saleId, int userId, double subtotal);
	Sale(sql::ResultSet* data);
	static std::vector<Sale> findSale();
	static std::vector<Sale> findSaleMaxMin(double subtotal);

	static std::vector<Sale> findSaleItem();
	static std::vector<Sale> findSaleItemID(int item_id);
	static std::vector<Sale> findSaleItemName(std::string item_name);
	static std::vector<Sale> findSaleCategory(int category_id);



	std::string date, categoryName;
	double value;

	//since sale data is computed from database, it does not need normal constructor
	//it will not exist without result set 


	//static std::vector<Sale> salesReport(std::string start, std::string end, std::vector<int> categoryIds, bool sortByDate, bool ascending);


	~Sale() {/*you can also define blank/simple method here,
		since we do not have anything to do in destructor yet
		we just declare empty method here*/
	};
};


#endif
