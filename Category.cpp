/*


	NAME			:	MUHAMMAD ZUHAIRY BIN RAZALY
	MATRIX NUMBER	:	B032310282
	COURSE			:	BITS
	TOPIC			:	GROCERIES SALE TRACKER
	CURRENT FILE	:	Category.cpp file


*/

#include "Category.h"
#include <ctime>
#include <iomanip>
#include "DBConnection.h"
#include "Account.h"
//#include "Main.cpp"
using namespace std;

void create_new_item(string category_name);

Category::Category() {
	//initialize
	categoryId = 0;
	categoryName = "";
	categoryDesc = "";
}

Category::Category(int categoryId, std::string categoryName, std::string categoryDesc) {
	this->categoryId = categoryId;
	this->categoryName = categoryName;
	this->categoryDesc = categoryDesc;

}

Category::Category(sql::ResultSet* data) {
	categoryId = data->getInt("category_id");
	categoryName = data->getString("category_name");
	categoryDesc = data->getString("category_desc");

}

void Category::insert_category() {

	DBConnection db;//instantiate
	db.prepareStatement("Insert into category (category_name,category_desc) VALUES (?,?)");
	db.stmt->setString(1, categoryName);
	db.stmt->setString(2, categoryDesc);
	db.QueryStatement();
	db.~DBConnection();
}

void Category::update_category() {
	DBConnection db;
	db.prepareStatement("UPDATE category SET category_name=?, category_desc=? WHERE category_id=?");
	db.stmt->setString(1, categoryName);
	db.stmt->setString(2, categoryDesc);
	db.stmt->setInt(3, categoryId);
	db.QueryStatement();
	db.~DBConnection();
}

//list all item
vector<Category> Category::findCategory() {

	string query = "SELECT * FROM category";

	DBConnection db;
	db.prepareStatement(query);

	vector<Category> category;

	db.QueryResult();

	if (db.res->rowsCount() > 0) {
		cout << "\nCATEGORY ID\t|CATEGORY NAME\t\t|CATEGORY DESC\t\t\t\t|" << endl;
		cout << "---------------------------------------------------------------------------------" << endl;
		while (db.res->next()) {
			Category tmpCategory(db.res);
			category.push_back(tmpCategory);

			cout << "" << db.res->getInt("category_id") << "\t\t|" << db.res->getString("category_name") << "      \t\t|" << db.res->getString("category_desc") << "      \t\t\t|" << endl;
			cout << fixed << showpoint;
			cout << setprecision(2);
		}
	}

	db.~DBConnection();
	return category;
}

//find item by Id
vector<Category> Category::findCategorybyId(int categoryId) {

	string category_name;
	vector<Category> category;
	Category category1;
	DBConnection db;
	db.prepareStatement("SELECT category_name FROM category WHERE category_id=?");
	db.stmt->setInt(1, categoryId);

	Account user;

	db.QueryResult();

	if (db.res->rowsCount() > 0) {
		while (db.res->next()) {
			category_name = db.res->getString("category_name");
			cout << category_name;
			category1.categoryName = category_name;
			//nametoPass(category_name);
			//create_new_item(user, category_name);
		}
	}
	else {
		cout << "No item found!" << endl;
	}

	db.~DBConnection();
	return category;
}