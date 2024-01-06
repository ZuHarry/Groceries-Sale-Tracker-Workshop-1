#include "Sale.h"
#include <ctime>
#include <iomanip>
#include "DBConnection.h"
#include "Item.h"
#include <fstream>
using namespace std;
using namespace sql;

Sale::Sale() {
	//initialize
	saleId = 0;
	userId = 0;
	subtotal= 0;
	//categoryId = 0;
}

Sale::Sale(int saleId, int userId, double subtotal) {
	this->saleId = saleId;
	this->userId = userId;
	this->subtotal = subtotal;
	//this->categoryId = category_id;

}

Sale::Sale(sql::ResultSet* data) {
	saleId = data->getInt("sale_id");
	userId = data->getInt("user_id");
	subtotal = data->getDouble("subtotal");

}







//list all sale by user
vector<Sale> Sale::findSale() {

	string query = "SELECT * FROM sale";

	DBConnection db;
	db.prepareStatement(query);

	vector<Sale> sales;

	db.QueryResult();

	if (db.res->rowsCount() > 0) {
		cout << "\n\n---------------------------------------------------------";
		cout << "\nSALE ID\t\t|USER ID\t|TOTAL\t\t\t|" << endl;
		cout << "---------------------------------------------------------" << endl;
		while (db.res->next()) {
			Sale tmpSale(db.res);
			sales.push_back(tmpSale);

				cout << "" << db.res->getInt("sale_id") << "\t\t|" << db.res->getInt("user_id") << "      \t|" << db.res->getDouble("subtotal") << "      \t\t|" << endl;
				cout << fixed << showpoint;
				cout << setprecision(2);

		}
		cout << "---------------------------------------------------------" << endl;
	}

	db.~DBConnection();
	return sales;
}




//list all sale by user
vector<Sale> Sale::findSaleMaxMin(double subtotal) {

	string query = "SELECT * FROM sale WHERE subtotal=?";

	DBConnection db, db1, db2;
	db.prepareStatement(query);
	db.stmt->setDouble(1, subtotal);

	int itemId;
	double itemPrice, totalPrice;

	vector<Sale> sales;

	db.QueryResult();

	if (db.res->rowsCount() > 0) {
		cout << "\n\n---------------------------------------------------------";
		cout << "\nSALE ID\t\t|USER ID\t|TOTAL\t\t\t|" << endl;
		cout << "---------------------------------------------------------" << endl;
		while (db.res->next()) {
			Sale tmpSale(db.res);
			sales.push_back(tmpSale);

			cout << "" << db.res->getInt("sale_id") << "\t\t|" << db.res->getInt("user_id") << "      \t|" << db.res->getDouble("subtotal") << "      \t\t|" << endl;
			cout << fixed << showpoint;
			cout << setprecision(2);

			cout << "---------------------------------------------------------" << endl;


			cout << "\nSale Breakdown";

			db1.prepareStatement("SELECT * FROM sale_item WHERE sale_id=?");
			db1.stmt->setInt(1, db.res->getInt("sale_id"));
			db1.QueryResult();

			if (db1.res->rowsCount() > 0) {
				cout << "\n\n-------------------------------------------------------------------------------------------------";
				cout << "\nSALE ID\t\t|ITEM ID\t|ITEM PRICE\t\t|QUANTITY\t|TOTAL PRICE\t\t|" << endl;
				cout << "-------------------------------------------------------------------------------------------------" << endl;

				while (db1.res->next()) {
					itemId = db1.res->getInt("item_id");
					db2.prepareStatement("SELECT * FROM item WHERE item_id=?");
					db2.stmt->setInt(1, itemId);
					db2.QueryResult();

					if (db2.res->rowsCount() > 0) {
						while (db2.res->next()) {

							itemPrice = db2.res->getDouble("item_price");
							totalPrice = itemPrice * (db1.res->getInt("quantity"));

							cout << "" << db1.res->getInt("sale_id") << "\t\t|" << db1.res->getInt("item_id") << "      \t|" << fixed << setprecision(2) << itemPrice << "      \t\t|" << db1.res->getInt("quantity") << "      \t|" << fixed << setprecision(2) << totalPrice << "      \t\t|" << endl;
							cout << fixed << showpoint;
							cout << setprecision(2);

						}

					}



					
				}
				cout << "-------------------------------------------------------------------------------------------------" << endl;
			}





		}
		//cout << "---------------------------------------------------------" << endl;
	}

	db.~DBConnection();
	return sales;
}












//list all sale by item
vector<Sale> Sale::findSaleItem() {

	DBConnection db,db1;
	int itemId;
	double itemPrice, totalPrice;

	string query = "SELECT * FROM sale_item";

	db.prepareStatement(query);

	vector<Sale> sales;

	db.QueryResult();

	if (db.res->rowsCount() > 0) {
		cout << "\n\n-------------------------------------------------------------------------------------------------";
		cout << "\nSALE ID\t\t|ITEM ID\t|ITEM PRICE\t\t|QUANTITY\t|TOTAL PRICE\t\t|" << endl;
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		while (db.res->next()) {

			itemId = db.res->getInt("item_id");
			db1.prepareStatement("SELECT * FROM item WHERE item_id=?");
			db1.stmt->setInt(1, itemId);
			db1.QueryResult();

			if (db1.res->rowsCount() > 0) {
				while (db1.res->next()) {

					itemPrice = db1.res->getDouble("item_price");
					totalPrice = itemPrice * (db.res->getInt("quantity"));

					cout << "" << db.res->getInt("sale_id") << "\t\t|" << db.res->getInt("item_id") << "      \t|" << fixed << setprecision(2) << itemPrice << "      \t\t|" << db.res->getInt("quantity") << "      \t|" << fixed << setprecision(2) << totalPrice << "      \t\t|" << endl;
					cout << fixed << showpoint;
					cout << setprecision(2);

				}
			}


			

		}
		cout << "-------------------------------------------------------------------------------------------------\n";
	}

	db.~DBConnection();
	return sales;
}











//list all sale by item
vector<Sale> Sale::findSaleCategory(int category_id) {

	DBConnection db, db1;
	int itemId, categoryId;
	double itemPrice, totalPrice, subtotal;

	subtotal = 0;

	string query = "SELECT * FROM sale_item";

	db.prepareStatement(query);

	vector<Sale> sales;

	db.QueryResult();

	if (db.res->rowsCount() > 0) {
		cout << "\nSALES IN THIS CATEGORY";
		cout << "\n\n-------------------------------------------------------------------------------------------------";
		cout << "\nSALE ID\t\t|ITEM ID\t|ITEM PRICE\t\t|QUANTITY\t|TOTAL PRICE\t\t|" << endl;
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		while (db.res->next()) {

			itemId = db.res->getInt("item_id");
			db1.prepareStatement("SELECT * FROM item WHERE item_id=?");
			db1.stmt->setInt(1, itemId);
			db1.QueryResult();

			if (db1.res->rowsCount() > 0) {
				while (db1.res->next()) {

					categoryId = db1.res->getInt("category_id");

					if (categoryId == category_id) {
						itemPrice = db1.res->getDouble("item_price");
						totalPrice = itemPrice * (db.res->getInt("quantity"));
						subtotal = subtotal + totalPrice;

						cout << "" << db.res->getInt("sale_id") << "\t\t|" << db.res->getInt("item_id") << "      \t|" << fixed << setprecision(2) << itemPrice << "      \t\t|" << db.res->getInt("quantity") << "      \t|" << fixed << setprecision(2) << totalPrice << "      \t\t|" << endl;
						cout << fixed << showpoint;
						cout << setprecision(2);
					}


				}
			}





		}
		cout << "-------------------------------------------------------------------------------------------------\n";
		cout << "       \t\t|       \t|          \t\t|SUM     \t|" << subtotal <<"      \t\t|" << endl;
		cout << "-------------------------------------------------------------------------------------------------" << endl;
	}

	db.~DBConnection();
	return sales;
}






//list all sale by item
vector<Sale> Sale::findSaleItemID(int item_id) {

	DBConnection db, db1;
	int itemId, categoryId, item_ID;
	double itemPrice, totalPrice, subtotal;

	subtotal = 0;

	string query = "SELECT * FROM sale_item";

	db.prepareStatement("SELECT * FROM sale_item WHERE item_id=?");
	db.stmt->setInt(1, item_id);

	vector<Sale> sales;

	db.QueryResult();

	if (db.res->rowsCount() > 0) {
		cout << "\nSALES FOR THIS ITEM";
		cout << "\n\n-------------------------------------------------------------------------------------------------";
		cout << "\nSALE ID\t\t|ITEM ID\t|ITEM PRICE\t\t|QUANTITY\t|TOTAL PRICE\t\t|" << endl;
		cout << "-------------------------------------------------------------------------------------------------" << endl;
		while (db.res->next()) {

			db1.prepareStatement("SELECT * FROM item WHERE item_id=?");
			db1.stmt->setInt(1, item_id);
			db1.QueryResult();

			if (db1.res->rowsCount() > 0) {
				while (db1.res->next()) {

						itemPrice = db1.res->getDouble("item_price");
						totalPrice = itemPrice * (db.res->getInt("quantity"));
						subtotal = subtotal + totalPrice;

						cout << "" << db.res->getInt("sale_id") << "\t\t|" << db.res->getInt("item_id") << "      \t|" << fixed << setprecision(2) << itemPrice << "      \t\t|" << db.res->getInt("quantity") << "      \t|" << fixed << setprecision(2) << totalPrice << "      \t\t|" << endl;
						cout << fixed << showpoint;
						cout << setprecision(2);



				}
			}





		}
		cout << "-------------------------------------------------------------------------------------------------\n";
		cout << "       \t\t|       \t|          \t\t|SUM     \t|" << subtotal << "      \t\t|" << endl;
		cout << "-------------------------------------------------------------------------------------------------" << endl;
	}
	else {
		cout << "\nItem ID not found!";
	}

	db.~DBConnection();
	return sales;
}





//list all sale by item name
//vector<Sale> Sale::findSaleItemName(string item_name) {
//
//	DBConnection db, db1, dbItem;
//	int itemId, categoryId, item_ID;
//	double itemPrice, totalPrice, subtotal;
//
//	subtotal = 0;
//
//
//	dbItem.prepareStatement("");
//
//	db.prepareStatement("SELECT * FROM sale_item WHERE item_id=?");
//	db.stmt->setInt(1, item_id);
//
//	vector<Sale> sales;
//
//	db.QueryResult();
//
//	if (db.res->rowsCount() > 0) {
//		cout << "\nSALES FOR THIS ITEM";
//		cout << "\n\n-------------------------------------------------------------------------------------------------";
//		cout << "\nSALE ID\t\t|ITEM ID\t|ITEM PRICE\t\t|QUANTITY\t|TOTAL PRICE\t\t|" << endl;
//		cout << "-------------------------------------------------------------------------------------------------" << endl;
//		while (db.res->next()) {
//
//			db1.prepareStatement("SELECT * FROM item WHERE item_id=?");
//			db1.stmt->setInt(1, item_id);
//			db1.QueryResult();
//
//			if (db1.res->rowsCount() > 0) {
//				while (db1.res->next()) {
//
//					itemPrice = db1.res->getDouble("item_price");
//					totalPrice = itemPrice * (db.res->getInt("quantity"));
//					subtotal = subtotal + totalPrice;
//
//					cout << "" << db.res->getInt("sale_id") << "\t\t|" << db.res->getInt("item_id") << "      \t|" << fixed << setprecision(2) << itemPrice << "      \t\t|" << db.res->getInt("quantity") << "      \t|" << fixed << setprecision(2) << totalPrice << "      \t\t|" << endl;
//					cout << fixed << showpoint;
//					cout << setprecision(2);
//
//
//
//				}
//			}
//
//
//
//
//
//		}
//		cout << "-------------------------------------------------------------------------------------------------\n";
//		cout << "       \t\t|       \t|          \t\t|SUM     \t|" << subtotal << "      \t\t|" << endl;
//		cout << "-------------------------------------------------------------------------------------------------" << endl;
//	}
//	else {
//		cout << "\nItem ID not found!";
//	}
//
//	db.~DBConnection();
//	return sales;
//}
