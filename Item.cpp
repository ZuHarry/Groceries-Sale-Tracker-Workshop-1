/*


	NAME			:	MUHAMMAD ZUHAIRY BIN RAZALY
	MATRIX NUMBER	:	B032310282
	COURSE			:	BITS
	TOPIC			:	GROCERIES SALE TRACKER
	CURRENT FILE	:	Item.cpp file


*/

#include "Item.h"
#include <ctime>
#include <iomanip>
#include "DBConnection.h"
using namespace std;

Item::Item() {
	//initialize
	itemId = 0;
	itemPrice = 0.1;
	itemName = "";
	categoryId = 0;
}

Item::Item(int itemId, double itemPrice, std::string itemName, int category_id) {
	this->itemId = itemId;
	this->itemPrice = itemPrice;
	this->itemName = itemName;
	this->categoryId = category_id;

}


void Item::insert_item() {

	DBConnection db;//instantiate
	db.prepareStatement("Insert into item (item_name,item_price,category_id) VALUES (?,?,?)");
	db.stmt->setString(1, itemName);
	db.stmt->setDouble(2, itemPrice);
	db.stmt->setInt(3, categoryId);
	db.QueryStatement();
	db.~DBConnection();
}

void Item::update_item() {
	DBConnection db;
	db.prepareStatement("UPDATE item SET item_name=?, item_price=?, category_id=? WHERE item_id=?");
	db.stmt->setString(1, itemName);
	db.stmt->setDouble(2, itemPrice);
	db.stmt->setInt(3, categoryId);
	db.stmt->setInt(4, itemId);
	db.QueryStatement();
	db.~DBConnection();
}

Item::Item(sql::ResultSet* data) {
	itemId = data->getInt("item_id");
	itemName = data->getString("item_name");
	categoryId = data->getInt("category_id");
	itemPrice = data->getDouble("item_price");

}


//list all item
vector<Item> Item::findItem() {
	
	string query = "SELECT * FROM item";

	DBConnection db;
	db.prepareStatement(query);

	vector<Item> items;

	db.QueryResult();

	if (db.res->rowsCount() > 0) {
		cout << "\nITEM ID\t\t|ITEM NAME\t\t\t\t|ITEM PRICE\t\t|CATEGORY\t\t|" << endl;
		cout << "---------------------------------------------------------------------------------------------------------" << endl;
		while (db.res->next()) {
			Item tmpItem(db.res);
			items.push_back(tmpItem);
			
			if ((db.res->getString("item_name")).length()>8 && (db.res->getString("item_name")).length() <= 12) {
				cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t\t|" << db.res->getDouble("item_price") << "      \t\t|" << db.res->getInt("category_id") << "\t\t\t|" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}
			else if ((db.res->getString("item_name")).length() > 12 && (db.res->getString("item_name")).length() <= 16) {
				cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t\t|" << db.res->getDouble("item_price") << "      \t\t|" << db.res->getInt("category_id") << "\t\t\t|" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}
			else if ((db.res->getString("item_name")).length() > 16) {
				cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t|" << db.res->getDouble("item_price") << "      \t\t|" << db.res->getInt("category_id") << "\t\t\t|" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}
			else {
				cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t\t\t|" << db.res->getDouble("item_price") << "      \t\t|" << db.res->getInt("category_id") << "\t\t\t|" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}

		}
	}

	db.~DBConnection();
	return items;
}


//find item by Name
vector<Item> Item::findItembyName(string itemName) {

	vector<Item> items;
	DBConnection db;
	db.prepareStatement("SELECT * FROM item WHERE item_name=?");
	db.stmt->setString(1, itemName);

	db.QueryResult();

	if (db.res->rowsCount() > 0) {
		cout << "\nITEM ID\t\t|ITEM NAME\t\t\t\t|ITEM PRICE\t\t|CATEGORY\t\t|" << endl;
		cout << "---------------------------------------------------------------------------------------------------------" << endl;
		while (db.res->next()) {
			Item tmpItem(db.res);
			items.push_back(tmpItem);

			if ((db.res->getString("item_name")).length() > 8 && (db.res->getString("item_name")).length() <= 12) {
				cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t\t|" << db.res->getDouble("item_price") << "      \t\t|" << db.res->getInt("category_id") << "\t\t\t|" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}
			else if ((db.res->getString("item_name")).length() > 12 && (db.res->getString("item_name")).length() <= 16) {
				cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t\t|" << db.res->getDouble("item_price") << "      \t\t|" << db.res->getInt("category_id") << "\t\t\t|" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}
			else if ((db.res->getString("item_name")).length() > 16) {
				cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t|" << db.res->getDouble("item_price") << "      \t\t|" << db.res->getInt("category_id") << "\t\t\t|" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}
			else {
				cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t\t\t|" << db.res->getDouble("item_price") << "      \t\t|" << db.res->getInt("category_id") << "\t\t\t|" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}

		}
	}
	else {
		cout << "No item found!" << endl;
	}

	db.~DBConnection();
	return items;
}


//find item by Category
vector<Item> Item::findItembyCategory(int category_id) {

	vector<Item> items;
	DBConnection db;
	db.prepareStatement("SELECT * FROM item WHERE category_id=?");
	db.stmt->setInt(1, category_id);

	db.QueryResult();

	if (db.res->rowsCount() > 0) {
		cout << "\nITEM ID\t\t|ITEM NAME\t\t\t\t|ITEM PRICE\t\t|CATEGORY\t\t|" << endl;
		cout << "---------------------------------------------------------------------------------------------------------" << endl;
		while (db.res->next()) {
			Item tmpItem(db.res);
			items.push_back(tmpItem);

			if ((db.res->getString("item_name")).length() > 8 && (db.res->getString("item_name")).length() <= 12) {
				cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t\t|" << db.res->getDouble("item_price") << "      \t\t|" << db.res->getInt("category_id") << "\t\t\t|" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}
			else if ((db.res->getString("item_name")).length() > 12 && (db.res->getString("item_name")).length() <= 16) {
				cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t\t|" << db.res->getDouble("item_price") << "      \t\t|" << db.res->getInt("category_id") << "\t\t\t|" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}
			else if ((db.res->getString("item_name")).length() > 16) {
				cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t|" << db.res->getDouble("item_price") << "      \t\t|" << db.res->getInt("category_id") << "\t\t\t|" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}
			else {
				cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t\t\t|" << db.res->getDouble("item_price") << "      \t\t|" << db.res->getInt("category_id") << "\t\t\t|" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}

		}
	}
	else {
		cout << "No item found!" << endl;
	}

	db.~DBConnection();
	return items;
}


//find item by Id
vector<Item> Item::findItembyId(int itemId) {

	vector<Item> items;
	DBConnection db;
	db.prepareStatement("SELECT * FROM item WHERE item_id=?");
	db.stmt->setInt(1, itemId);

	db.QueryResult();

	if (db.res->rowsCount() > 0) {
		cout << "\nITEM ID\t\t|ITEM NAME\t\t\t\t|ITEM PRICE\t\t|CATEGORY\t\t|" << endl;
		cout << "---------------------------------------------------------------------------------------------------------" << endl;
		while (db.res->next()) {
			Item tmpItem(db.res);
			items.push_back(tmpItem);

			if ((db.res->getString("item_name")).length() > 8 && (db.res->getString("item_name")).length() <= 12) {
				cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t\t|" << db.res->getDouble("item_price") << "      \t\t|" << db.res->getInt("category_id") << "\t\t\t|" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}
			else if ((db.res->getString("item_name")).length() > 12 && (db.res->getString("item_name")).length() <= 16) {
				cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t\t|" << db.res->getDouble("item_price") << "      \t\t|" << db.res->getInt("category_id") << "\t\t\t|" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}
			else if ((db.res->getString("item_name")).length() > 16) {
				cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t|" << db.res->getDouble("item_price") << "      \t\t|" << db.res->getInt("category_id") << "\t\t\t|" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}
			else {
				cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t\t\t|" << db.res->getDouble("item_price") << "      \t\t|" << db.res->getInt("category_id") << "\t\t\t|" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}

		}
	}
	else {
		cout << "No item found!" << endl;
	}

	db.~DBConnection();
	return items;
}






void Item::remove_item(int itemId) {
	DBConnection db;
	db.prepareStatement("DELETE FROM item WHERE item_id=?");
	db.stmt->setInt(1, itemId);
	db.QueryStatement();
	db.~DBConnection();
}



Item Item::findItem(int itemId) {
	DBConnection db;
	db.prepareStatement("SELECT * FROM item WHERE item_Id=?");
	db.stmt->setInt(1, itemId);
	db.QueryResult();

	Item result;
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			Item found(db.res);
			result = found;
		}
	}
	else {
		cout << "Item not found!";
	}
	db.~DBConnection();
	return result;
}


Item Item::findItemSale(int itemId) {
	DBConnection db;
	db.prepareStatement("SELECT * FROM item WHERE item_Id=?");
	db.stmt->setInt(1, itemId);
	db.QueryResult();

	Item result;
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {

			cout << "\nITEM ID\t\t|ITEM NAME\t\t\t\t|ITEM PRICE\t\t|CATEGORY\t\t|" << endl;
			cout << "---------------------------------------------------------------------------------------------------------" << endl;
			if ((db.res->getString("item_name")).length() > 8 && (db.res->getString("item_name")).length() <= 12) {
				cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t\t|" << db.res->getDouble("item_price") << "      \t\t|" << db.res->getInt("category_id") << "\t\t\t|" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}
			else if ((db.res->getString("item_name")).length() > 12 && (db.res->getString("item_name")).length() <= 16) {
				cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t\t|" << db.res->getDouble("item_price") << "      \t\t|" << db.res->getInt("category_id") << "\t\t\t|" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}
			else if ((db.res->getString("item_name")).length() > 16) {
				cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t|" << db.res->getDouble("item_price") << "      \t\t|" << db.res->getInt("category_id") << "\t\t\t|" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}
			else {
				cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t\t\t|" << db.res->getDouble("item_price") << "      \t\t|" << db.res->getInt("category_id") << "\t\t\t|" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}

			Item found(db.res);
			result = found;
		}
	}
	else {
		cout << "Item not found!";
	}
	db.~DBConnection();
	return result;
}




Item Item::findItemSaleCategory(int itemId, int category_id) {
	DBConnection db;
	db.prepareStatement("SELECT * FROM item WHERE item_Id=? AND category_id=?");
	db.stmt->setInt(1, itemId);
	db.stmt->setInt(2, category_id);
	db.QueryResult();

	Item result;
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {

			cout << "\nITEM ID\t\t|ITEM NAME\t\t\t\t|ITEM PRICE\t\t|CATEGORY\t\t|" << endl;
			cout << "---------------------------------------------------------------------------------------------------------" << endl;
			if ((db.res->getString("item_name")).length() > 8 && (db.res->getString("item_name")).length() <= 12) {
				cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t\t|" << db.res->getDouble("item_price") << "      \t\t|" << db.res->getInt("category_id") << "\t\t\t|" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}
			else if ((db.res->getString("item_name")).length() > 12 && (db.res->getString("item_name")).length() <= 16) {
				cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t\t|" << db.res->getDouble("item_price") << "      \t\t|" << db.res->getInt("category_id") << "\t\t\t|" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}
			else if ((db.res->getString("item_name")).length() > 16) {
				cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t|" << db.res->getDouble("item_price") << "      \t\t|" << db.res->getInt("category_id") << "\t\t\t|" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}
			else {
				cout << "" << db.res->getInt("item_id") << "\t\t|" << db.res->getString("item_name") << "      \t\t\t\t|" << db.res->getDouble("item_price") << "      \t\t|" << db.res->getInt("category_id") << "\t\t\t|" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);
			}

			Item found(db.res);
			result = found;
		}
	}
	else {
		cout << "Item not found in this category!";
	}
	db.~DBConnection();
	return result;
}








Item Item::findItem(string itemName) {
	DBConnection db;
	db.prepareStatement("SELECT * FROM item WHERE item_name=?");
	db.stmt->setString(1, itemName);
	db.QueryResult();

	Item result;
	if (db.res->rowsCount() >= 1) {
		while (db.res->next()) {
			Item found(db.res);
			result = found;
		}
	}


	db.~DBConnection();
	return result;
}




