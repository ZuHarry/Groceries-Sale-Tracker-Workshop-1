/*


	NAME			:	MUHAMMAD ZUHAIRY BIN RAZALY
	MATRIX NUMBER	:	B032310282
	COURSE			:	BITS
	TOPIC			:	GROCERIES SALE TRACKER
	CURRENT FILE	:	main.cpp file


*/

#include <iostream>
#include <conio.h>
#include <iomanip>
#include <sstream>

#include "Menu.h"
#include "Account.h"
#include "Item.h"
#include "Category.h" 
#include "Transaction.h"
#include "Sale.h"
#include <stdio.h>
using namespace std;

void registerAccount();
void loginMenu();
void home(Account user);

void record_sale(Account user); //sale page
void item_cart(Account user, int itemID, Transaction cart); //item cart page

void sale_report(Account user);
void all_sale_report(Account user);
void all_sale_report_id(Account user);
void view_statistic(Account user);
void search_filter(Account user);

void new_item(Account user); //item page
void edit_item(Account user); //edit item page
void update_new_item(Account user, int itemID, string itemName, double itemPrice, int category_id); //update new item page
void delete_item(Account user); //delete item page
void create_new_item(Account user, string category_name); //create new item page
void all_item(Account user); //all item page

Transaction cartMenu(Account user, Transaction cart);

void all_category(Account user); //all category page
void add_category(Account user); //add category page
void edit_category(Account user, int category_id, string category_name, string category_desc);


Account profile(Account user);

//utility functions
bool isNumeric(string input);









/*

---------------------------------------------------------------------------------------------------------------------------------------
	MAIN FUNCTION
---------------------------------------------------------------------------------------------------------------------------------------

*/
int main()
{
    Menu mainmenu;
    mainmenu.header = "------------------------------------------\nWelcome to Groceries Sale Tracker\n------------------------------------------\nChoose your action = \n";
    mainmenu.addOption("Register");
    mainmenu.addOption("Login");
    mainmenu.addOption("Exit\n");

    while (1) {
        switch (mainmenu.prompt())
        {
        case 1:
            registerAccount();
            break;
        case 2:
            loginMenu();
            break;
        case 3:
            return 0;
        default:
            break;
        }
    }


}






/*

---------------------------------------------------------------------------------------------------------------------------------------
	REGISTER ACCOUNT
---------------------------------------------------------------------------------------------------------------------------------------

*/
void registerAccount() {
	Account newacc;

	Menu rgMenu;
	rgMenu.header = "------------------------------------------\nGroceries Sale Tracker\nAccount Registration\n------------------------------------------\nChoose action and input details";
	rgMenu.addOption("Username");
	rgMenu.addOption("Password");
	rgMenu.addOption("Full Name");
	rgMenu.addOption("Shop Name");
	rgMenu.addOption("Telephone");
	rgMenu.addOption("Year of Birth");
	rgMenu.addOption("Register");
	rgMenu.addOption("Back");


	string tmpinput;
	bool valid = true;
	while (1) {

		switch (rgMenu.prompt()) {
		case 1:
			cout << "Insert Username: ";
			cin >> newacc.username;
			rgMenu.setValue(0, newacc.username);
			break;
		case 2:
			cout << "Insert password: ";
			cin >> tmpinput;
			if (tmpinput.length() < 6) {
				cout << "Password must be at least 6 character long";
				_getch();
			}
			else {
				newacc.password = tmpinput;
				rgMenu.setValue(1, newacc.password);
			}
			break;
		case 3:
			cout << "Insert fullname: ";
			getline(cin, newacc.fullname);
			rgMenu.setValue(2, newacc.fullname);
			break;
		case 4:
			cout << "Insert shop name: ";
			getline(cin, newacc.shopname);
			rgMenu.setValue(3, newacc.shopname);
			break;
		case 5:
			cout << "Insert telephone: ";
			getline(cin, newacc.telephone);
			rgMenu.setValue(4, newacc.telephone);
			break;

		case 6:
			cout << "Insert yearOfBirth: ";
			cin >> tmpinput;
			if (isNumeric(tmpinput) && tmpinput.length() == 4) {

				newacc.yearOfBirth = stoi(tmpinput);

				rgMenu.setValue(5, to_string(newacc.yearOfBirth));
			}
			else {
				cout << "Input for year of birth must be number with 4 digit";
				_getch();
			}
			break;
		case 7:
			valid = true;

			// 20 years old to register,  
			if (newacc.getAge() < 20) {
				valid = false;
				cout << endl << "You must be at least 20 years old to register" << endl;
			}
			if (valid) {
				newacc.insert();
				cout << "Registered";
				_getch();
				return;
			}
			else {
				cout << "Please re-check your informations";
				_getch();
			}
			break;
		case 8:
			return;
		default:
			break;
		}
	}

}












/*

---------------------------------------------------------------------------------------------------------------------------------------
	LOGIN MENU
---------------------------------------------------------------------------------------------------------------------------------------

*/
void loginMenu() {
	Menu loginMenu;
	loginMenu.header = "----------------------\nGroceries Sale Tracker\nLogin\n----------------------\nChoose action and input details";
	loginMenu.addOption("username");
	loginMenu.addOption("password");
	loginMenu.addOption("Login");
	loginMenu.addOption("Back");

	Account user;

	while (1) {
		switch (loginMenu.prompt())
		{
		case 1:
			cout << "Insert Username: ";
			cin >> user.username;
			loginMenu.setValue(0, user.username);
			break;
		case 2:
			cout << "Insert Password: ";
			cin >> user.password;
			loginMenu.setValue(1, user.password);
			break;
		case 3:
			if (user.login()) {
				home(user);
			}
			else {
				cout << "Invalid Login";
				_getch();
			}
			break;
		case 4:
			return;
			break;
		default:
			break;
		}
	}
}










/*

---------------------------------------------------------------------------------------------------------------------------------------
	HOME PAGE
---------------------------------------------------------------------------------------------------------------------------------------

*/
void home(Account user) {
	Menu homeMenu;
	homeMenu.addOption("Profile");
	homeMenu.addOption("Shop");
	homeMenu.addOption("Sale Report");
	homeMenu.addOption("Record New Item");
	homeMenu.addOption("Logout");
	while (1) {
		homeMenu.header = "------------------------------\nWelcome to " + user.shopname + "\n------------------------------\nThis is your home page\nPlease choose your action\n";
		switch (homeMenu.prompt())
		{
		case 1:
			user = profile(user);
			break;
		case 2:
			record_sale(user);
			break;
		case 3:
			sale_report(user);
			break;
		case 4:
			new_item(user);
			break;
		case 5:
			return;
			break;
		default:
			break;
		}
	}
}








/*

---------------------------------------------------------------------------------------------------------------------------------------
	USER PROFILE
---------------------------------------------------------------------------------------------------------------------------------------

*/
Account profile(Account user) {

	Account temp = user; // copy the object

	Menu profileMenu;
	profileMenu.header = "----------------------\nGroceries Sale Tracker\nYour Profile\n----------------------\nChoose action and input details";
	profileMenu.addOption("username");
	profileMenu.addOption("password");
	profileMenu.addOption("fullname");
	profileMenu.addOption("shopname");
	profileMenu.addOption("telephone");
	profileMenu.addOption("yearOfBirth");
	profileMenu.addOption("Reset");
	profileMenu.addOption("Save");
	profileMenu.addOption("Back");
	profileMenu.addOption("Delete Account");

	string tmpInput;
	while (1) {
		profileMenu.setValue(0, temp.username);
		profileMenu.setValue(1, temp.password);
		profileMenu.setValue(2, temp.fullname);
		profileMenu.setValue(3, temp.shopname);
		profileMenu.setValue(4, temp.telephone);
		profileMenu.setValue(5, to_string(temp.yearOfBirth));
		profileMenu.footer = "You are " + to_string(temp.getAge()) + " Years old\nSelect Option and press Enter";
		profileMenu.prompt();

		//char choice;
		string option;
		cin >> option;
		//cin >> choice;

		if (option == "1") {
			cout << "\nInsert Username: ";
			cin >> temp.username;
		}
		else if (option == "2") {
			cout << "\nInsert password: ";
			cin >> temp.password;
		}
		else if (option == "3") {
			cout << "\nInsert full name: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, temp.fullname);
		}
		else if (option == "4") {
			cout << "\nInsert shop name: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, temp.shopname);
		}
		else if (option == "5") {
			cout << "\nInsert telephone: ";
			cin >> temp.telephone;
		}
		else if (option == "6") {
			cout << "\nInsert year of birth: ";
			//cin >> temp.yearOfBirth;
			cin >> tmpInput;
			if (isNumeric(tmpInput)) {
				temp.yearOfBirth = stoi(tmpInput);
			}
			else {
				cout << "\nInput for year of birth must be numeric";
				_getch();
			}
		}
		else if (option == "7") {
			temp = user;
		}
		else if (option == "8") {
			cout << "\nDo you want to update these details? (y/n)";
			char confirm;
			confirm = _getch();
			if (confirm == 'Y' || confirm == 'y') {
				user = temp;
				user.update();
				cout << "\nAccount Updated";
				_getch();
			}
		}
		else if (option == "9") {
			return user;
			break;
		}
		else if (option == "10") {
			cout << "\nDelete your account? (y/n)";
			char confirm;
			confirm = _getch();
			if (confirm == 'Y' || confirm == 'y') {
				user = temp;
				user.remove();
				main();
			}
		}
		else {
			cout << "Enter a valid option!";
			_getch();
		}
		
	}
}











/*

---------------------------------------------------------------------------------------------------------------------------------------
	RECORD SALE MAIN PAGE
---------------------------------------------------------------------------------------------------------------------------------------

*/
void record_sale(Account user) {

	Transaction cart; //initialize a transaction to hold product values
	cart.userId = user.accountId; // put currently logge in user id into the transaction


	Account temp = user;
	vector<Item> items;
	int itemID, quantity, category_id;
	string category_name, category;
	char choice;
	vector<Category> category1;
	DBConnection db;

	Item item;

	Menu saleMenu;
	saleMenu.addOption("View All Item in Cart");
	saleMenu.addOption("Show All Item");
	saleMenu.addOption("Choose by Category");
	saleMenu.addOption("Back");
	while (1) {
		saleMenu.header = "----------------------\n" + user.shopname + "\nShop\n----------------------\nItems in cart = " + to_string(cart.count()) + "\nTotal price = " + to_string(cart.total()) + "\n";
		switch (saleMenu.prompt())
		{
		case 1:
			cart = cartMenu(user, cart);
			break;
		case 2:
			items = Item::findItem();

			cout << "\nChoose Item ID = ";
			cin >> itemID;

			item = Item::findItemSale(itemID);

			if (item.itemId != NULL) {
				cout << "\nInsert Quantity = ";
				cin >> quantity;

				if (quantity > 0) {
					cout << "\nItem Name = " +item.itemName;
					cout << "\nItem Price = " +to_string(item.itemPrice)+"\n";
					cout << "\nQuantity = " + to_string(quantity);
					cout << "\nTotal Price = " +to_string(quantity*item.itemPrice);
					cout << "\nTotal after add = " + to_string(cart.total() + (quantity * item.itemPrice));
					cout << "\nAre you sure? (y-yes, n-no) \n";
					cin >> choice;

					if (choice == 'y') {
						cart.addItem(item, quantity);

						cout << endl << "Item Added into cart";

					}
					else {
						cout << endl << "Item Not Added into cart";
					}

				}
			}

			_getch();
			break;


		case 3:
			category1 = Category::findCategory();
			cout << "\nInsert Category ID: ";
			cin >> category_id;

			if (!cin.fail()) {
				db.prepareStatement("SELECT category_name FROM category WHERE category_id=?");
				db.stmt->setInt(1, category_id);


				db.QueryResult();

				if (db.res->rowsCount() > 0) {
					while (db.res->next()) {
						category_name = db.res->getString("category_name");
						cout << "You choose " << category_name << "\n";

						category = category_name;

						items = Item::findItembyCategory(category_id);

						cout << "\nChoose Item ID = ";
						cin >> itemID;

						item = Item::findItemSaleCategory(itemID, category_id);

						if (item.itemId != NULL) {
							cout << "\nInsert Quantity = ";
							cin >> quantity;

							if (quantity > 0) {
								cout << "\nItem Name = " + item.itemName;
								cout << "\nItem Price = " + to_string(item.itemPrice) + "\n";
								cout << "\nQuantity = " + to_string(quantity);
								cout << "\nTotal Price = " + to_string(quantity * item.itemPrice);
								cout << "\nTotal after add = " + to_string(cart.total() + (quantity * item.itemPrice));
								cout << "\nAre you sure? (y-yes, n-no) \n";
								cin >> choice;

								if (choice == 'y') {
									cart.addItem(item, quantity);

									cout << endl << "Item Added into cart";

								}
								else {
									cout << endl << "Item Not Added into cart";
								}

							}
						}
					}
				}
				else {
					cout << "No category found!" << endl;
				}
			}
			else {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid input. Please enter an integer." << std::endl;
			}

			_getch();
			break;
		case 4:
			home(user);
			break;
		default:
			break;
		}
	}
}




/*

---------------------------------------------------------------------------------------------------------------------------------------
	CART MENU
---------------------------------------------------------------------------------------------------------------------------------------

*/
Transaction cartMenu(Account user, Transaction cart) {
	Menu cartM;
	cartM.header = "----------------------\n" + user.shopname + "\nShop\n----------------------\nItems in cart = " + to_string(cart.count()) + "\nTotal price = " + to_string(cart.total()) + "\n\nActions";
	cartM.addOption("Checkout");
	cartM.addOption("Empty Cart");
	cartM.addOption("Back");
	stringstream ss;
	ss << "---------------------------------------------------------------------------------" << endl;
	ss << fixed << setprecision(2) << "Item\t\t\t\t|Price\t\t|Quantity\t|Subtotal\t|" << endl;
	ss << "---------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < cart.items.size(); i++) {

		if ((cart.items[i].first.itemName).length() >= 8 && (cart.items[i].first.itemName).length() <= 12) {
			ss << cart.items[i].first.itemName << "\t\t\t|" << cart.items[i].first.itemPrice << "\t\t|" << cart.items[i].second
				<< "\t\t|" << (cart.items[i].first.itemPrice * cart.items[i].second) << "\t\t|" << endl;
		}
		else if ((cart.items[i].first.itemName).length() > 12 && (cart.items[i].first.itemName).length() <= 16) {
			ss << cart.items[i].first.itemName << "\t\t|" << cart.items[i].first.itemPrice << "\t\t|" << cart.items[i].second
				<< "\t\t|" << (cart.items[i].first.itemPrice * cart.items[i].second) << "\t\t|" << endl;
		}

		else if ((cart.items[i].first.itemName).length() > 16) {
			ss << cart.items[i].first.itemName << "\t\t|" << cart.items[i].first.itemPrice << "\t\t|" << cart.items[i].second
				<< "\t\t|" << (cart.items[i].first.itemPrice * cart.items[i].second) << "\t\t|" << endl;
		}
		else {
			ss << cart.items[i].first.itemName << "\t\t\t\t|" << cart.items[i].first.itemPrice << "\t\t|" << cart.items[i].second
				<< "\t\t|" << (cart.items[i].first.itemPrice * cart.items[i].second) << "\t\t|" << endl;
		}
	}
	ss << "---------------------------------------------------------------------------------" << endl;
	ss << "\nSUM" << "\t\t\t\t|\t\t|" << cart.count() << "\t\t|" << cart.total() << "\t\t|";
	cartM.footer = "\nCart Items\n" + ss.str();
	char confirm;
	while (1)
	{
		switch (cartM.prompt())
		{
		case 1:
			cout << "\nCheck out? (y/n)\n";
			confirm = _getch();
			if (confirm == 'Y' || confirm == 'y') {
				cart.insert(cart.total());
				cout << "\nTransaction saved";
				_getch();
				record_sale(user); // go back to shop with empty cart
				break;
			}
			else {
				_getch();
				break;
			}
			
		case 2:
			cout << "\nClear your cart? (y/n)\n";
			confirm = _getch();
			if (confirm == 'Y' || confirm == 'y') {
				cout << "\nYour cart is empty";
				_getch();
				record_sale(user); // go back to shop with empty cart
			}
			_getch();
			break;
		case 3:
			return cart;
		}

	}
}







/*

---------------------------------------------------------------------------------------------------------------------------------------
	ITEM CART
---------------------------------------------------------------------------------------------------------------------------------------

*/
void item_cart(Account user, int itemID, Transaction cart) {
	Account temp = user;

	Menu cartMenu;
	cartMenu.addOption("Insert Quantity");
	cartMenu.addOption("Total Price");
	cartMenu.addOption("Back");
	while (1) {
		cartMenu.header = "----------------------\n" + user.shopname + "\nSale Report\n----------------------\nChoose action and input details";
		switch (cartMenu.prompt())
		{
		case 1:
			cout << "Total Item";
			_getch();
			break;
		case 2:
			cout << "Total Price";
			_getch();
			break;
		case 3:
			return;
			break;
		default:
			break;
		}
	}
}










/*

---------------------------------------------------------------------------------------------------------------------------------------
	SALE REPORT MAIN SECTION
---------------------------------------------------------------------------------------------------------------------------------------

*/
void sale_report(Account user) {

	Account temp = user;
	vector<Sale> sales;
	vector<Category> category1;
	vector<Item> items;

	int categoryID;
	string category, category_name;

	DBConnection db, db1;

	Menu homeMenu;
	homeMenu.addOption("Show All Sale Report");
	homeMenu.addOption("Show by Month");
	homeMenu.addOption("Show by Category");
	homeMenu.addOption("Show by Item");
	homeMenu.addOption("View Statistics");
	homeMenu.addOption("Back");
	while (1) {
		homeMenu.header = "----------------------\n" + user.shopname + "\nSale Report\n----------------------\nChoose action and input details";
		switch (homeMenu.prompt())
		{
		case 1:
			all_sale_report(user);
			break;
		case 2:
			cout << "Monthly Report";
			_getch();
			break;
		case 3:

			category1 = Category::findCategory();
			cout << "\nInsert Category ID: ";
			cin >> categoryID;


			if (!cin.fail()) {
				db.prepareStatement("SELECT category_name FROM category WHERE category_id=?");
				db.stmt->setInt(1, categoryID);


				db.QueryResult();

				if (db.res->rowsCount() > 0) {
					while (db.res->next()) {
						category_name = db.res->getString("category_name");
						cout << "\nYou choose " << category_name << "\n";

						category = category_name;


						items = Item::findItembyCategory(categoryID);
						sales = Sale::findSaleCategory(categoryID);
					}
				}
				else {
					cout << "No item found!" << endl;
				}
			}
			else {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid input. Please enter an integer." << std::endl;
			}


			_getch();
			break;
		case 4:
			all_sale_report_id(user);
			break;
		case 5:
			view_statistic(user);
			break;
		case 6:
			return;
			break;
		default:
			break;
		}
	}
}








/*

---------------------------------------------------------------------------------------------------------------------------------------
	ALL SALE REPORT BY ID
---------------------------------------------------------------------------------------------------------------------------------------

*/
void all_sale_report_id(Account user) {

	Account temp = user;
	vector<Sale> sales;
	vector<Item> items;
	DBConnection db;

	int item_id;
	string item_name;

	Menu homeMenu;
	homeMenu.addOption("Show by Item Name");
	homeMenu.addOption("Show by Item ID");
	homeMenu.addOption("Back");
	while (1) {
		homeMenu.header = "----------------------\n" + user.shopname + "\nSale Report\n----------------------\nChoose action and input details";
		switch (homeMenu.prompt())
		{
		case 1:
			cout << "\nInsert Item Name = " << endl;
			cin >> item_name;

			items = Item::findItembyName(item_name);

			db.prepareStatement("SELECT * FROM item WHERE item_name=?");
			db.stmt->setString(1, item_name);
			db.QueryResult();




			if (db.res->rowsCount() > 0) {

				while (db.res->next()) {
					item_id = db.res->getInt("item_id");
					sales = Sale::findSaleItemID(item_id);
				}
			}

			_getch();
			break;
		case 2:
			cout << "\nInsert Item ID = " << endl;
			cin >> item_id;

			items = Item::findItembyId(item_id);

			sales = Sale::findSaleItemID(item_id);
			_getch();
			break;
		case 3:
			return;
			break;
		default:
			break;
		}
	}
}












/*

---------------------------------------------------------------------------------------------------------------------------------------
	ALL SALE REPORT
---------------------------------------------------------------------------------------------------------------------------------------

*/
void all_sale_report(Account user) {

	Account temp = user;
	vector<Sale> sales;

	Menu homeMenu;
	homeMenu.addOption("Show All Sale Report by User");
	homeMenu.addOption("Show All Sale Report by Item");
	homeMenu.addOption("Search and Filter");
	homeMenu.addOption("Back");
	while (1) {
		homeMenu.header = "----------------------\n" + user.shopname + "\nSale Report\n----------------------\nChoose action and input details";
		switch (homeMenu.prompt())
		{
		case 1:
			cout << "\nAll Sale Report";

			sales = Sale::findSale();
			_getch();
			break;
		case 2:
			cout << "\nAll Sale Report";

			sales = Sale::findSaleItem();
			_getch();
			break;
		case 3:
			search_filter(user);

			break;
		case 4:
			return;
			break;
		default:
			break;
		}
	}
}











/*

---------------------------------------------------------------------------------------------------------------------------------------
	SEARCH AND FILTER
---------------------------------------------------------------------------------------------------------------------------------------

*/

void search_filter(Account user) {

	Account temp = user;
	string categoryName = "d";
	double maxValue, minValue;

	Menu itemMenu;
	itemMenu.addOption("Input Maximum");
	itemMenu.addOption("Input Mimimum");
	itemMenu.addOption("Delete Item");
	itemMenu.addOption("All Item List");
	itemMenu.addOption("Show Category");
	itemMenu.addOption("Back");
	while (1) {
		itemMenu.header = "----------------------\n" + user.shopname + "\nItem Directories\n----------------------\nChoose action and input details";
		switch (itemMenu.prompt())
		{
		case 1:
			cout << "Input maximum price value = ";
			cin >> maxValue;
			cout << fixed << showpoint;
			cout << setprecision(2);

			itemMenu.setValue(0, to_string(maxValue));

			break;
		case 2:
			cout << "Input minimum price value = ";
			cin >> minValue;

			itemMenu.setValue(1, to_string(minValue));

			break;
		case 3:
			delete_item(user);
			break;
		case 4:
			all_item(user);
			break;
		case 5:
			all_category(user);

			break;
		case 6:
			return;
			break;
		default:
			break;
		}
	}
}

















/*

---------------------------------------------------------------------------------------------------------------------------------------
	VIEW STATISTIC
---------------------------------------------------------------------------------------------------------------------------------------

*/

void view_statistic(Account user) {

	Account temp = user;
	vector<Sale> sales;
	DBConnection db, db1;
	double maxmin_sale;
	int total_item;

	Menu statMenu;
	statMenu.addOption("View by Item");
	statMenu.addOption("Highest and Lowest Sale");
	statMenu.addOption("Average Sale");
	statMenu.addOption("Sum Sale");
	statMenu.addOption("Back");
	while (1) {
		statMenu.header = "----------------------\n" + user.shopname + "\nSale Report\n----------------------\nChoose action and input details";
		switch (statMenu.prompt())
		{
		case 1:
			cout << "\nAll Sale Report";
			_getch();
			break;
		case 2:
			cout << "\nHighest Sale";
			db.prepareStatement("SELECT MAX(subtotal) FROM sale");
			db.QueryResult();
			//cout << max_sale;

			while (db.res->next()) {
				maxmin_sale = db.res->getDouble(1);
				
				sales = Sale::findSaleMaxMin(maxmin_sale);

			}

			cout << "\nLowest Sale";
			db.prepareStatement("SELECT MIN(subtotal) FROM sale");
			db.QueryResult();
			//cout << max_sale;

			while (db.res->next()) {
				maxmin_sale = db.res->getDouble(1);

				sales = Sale::findSaleMaxMin(maxmin_sale);

			}

			_getch();
			break;
		case 3:

			db.prepareStatement("SELECT AVG(subtotal) FROM sale");
			db.QueryResult();

			while (db.res->next()) {
				maxmin_sale = db.res->getDouble(1);
				
				db1.prepareStatement("SELECT COUNT(sale_id) FROM sale");
				db1.QueryResult();

				while (db1.res->next()) {
					total_item = db1.res->getInt(1);
					cout << "\nTotal Average Sale = " << maxmin_sale << endl;
					cout << "Total Sale Recorded = " << total_item << endl;
				}


			}
			_getch();
			break;
		case 4:
			db.prepareStatement("SELECT SUM(subtotal) FROM sale");
			db.QueryResult();

			while (db.res->next()) {
				maxmin_sale = db.res->getDouble(1);

				db1.prepareStatement("SELECT COUNT(sale_id) FROM sale");
				db1.QueryResult();

				while (db1.res->next()) {
					total_item = db1.res->getInt(1);
					cout << "\nTotal Sum of every Sale = " << maxmin_sale << endl;
					cout << "Total Sale Recorded = " << total_item << endl;
				}


			}
			_getch();
			break;
		case 5:
			return;
			break;
		default:
			break;
		}
	}
}










/*

---------------------------------------------------------------------------------------------------------------------------------------
	NEW ITEM SECTION
---------------------------------------------------------------------------------------------------------------------------------------

*/
void new_item(Account user) {

	Account temp = user;
	string categoryName = "d";

	Menu itemMenu;
	itemMenu.addOption("Edit Item");
	itemMenu.addOption("New Item");
	itemMenu.addOption("Delete Item");
	itemMenu.addOption("All Item List");
	itemMenu.addOption("Show Category");
	itemMenu.addOption("Back");
	while (1) {
		itemMenu.header = "----------------------\n"+user.shopname+"\nItem Directories\n----------------------\nChoose action and input details";
		switch (itemMenu.prompt())
		{
		case 1:
			edit_item(user);

			break;
		case 2:
			create_new_item(user, categoryName);

			break;
		case 3:
			delete_item(user);
			break;
		case 4:
			all_item(user);
			break;
		case 5:
			all_category(user);

			break;
		case 6:
			return;
			break;
		default:
			break;
		}
	}
}











/*

---------------------------------------------------------------------------------------------------------------------------------------
	EDIT ITEM SECTION
---------------------------------------------------------------------------------------------------------------------------------------

*/
void edit_item(Account user) {

	Account temp = user;
	vector<Item> items;
	vector<Category> category1;
	DBConnection db;
	int itemID, categoryID, category_id;
	double itemPrice;
	string itemName, category, itemNameFind;
	Item itemSingleName;

	Menu homeMenu;
	homeMenu.addOption("Choose by Item ID");
	homeMenu.addOption("Choose by Item Name");
	homeMenu.addOption("Choose by Category");
	homeMenu.addOption("Back");
	while (1) {
		homeMenu.header = "----------------------\n" + user.shopname + "\nEdit Item\n----------------------\nChoose action and input details";
		switch (homeMenu.prompt())
		{
		case 1:
			items = Item::findItem();

			cout << "Insert Item ID = ";
			cin >> itemID;

			if (!cin.fail()) {
				db.prepareStatement("SELECT * FROM item WHERE item_id=?");
				db.stmt->setInt(1, itemID);


				db.QueryResult();

				if (db.res->rowsCount() > 0) {
					while (db.res->next()) {
						itemName = db.res->getString("item_name");
						itemPrice = db.res->getDouble("item_price");
						category_id = db.res->getInt("category_id");
						update_new_item(user, itemID, itemName, itemPrice, category_id);
					}
				}
				else {
					cout << "No item found!" << endl;
				}
			}
			else {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid input. Please enter an integer." << std::endl;
			}

			_getch();
			break;
		case 2:
			items = Item::findItem();

			cout << "Insert Item Name = ";
			std::cin.clear();
			getline(cin, itemNameFind);

			db.prepareStatement("SELECT * FROM item WHERE item_name=?");
			db.stmt->setString(1, itemNameFind);

			db.QueryResult();

			if (db.res->rowsCount() > 1) {
				cout << "There are more than 1 item with same name, please choose one item ID\n";
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
				cout << "\nEnter item ID = ";
				cin >> itemID;

				if (!cin.fail()) {
					db.prepareStatement("SELECT * FROM item WHERE item_id=? AND item_name=?");
					db.stmt->setInt(1, itemID);
					db.stmt->setString(2, itemNameFind);

					db.QueryResult();

					if (db.res->rowsCount() > 0) {
						while (db.res->next()) {
							itemName = db.res->getString("item_name");
							itemPrice = db.res->getDouble("item_price");
							category_id = db.res->getInt("category_id");
							update_new_item(user, itemID, itemName, itemPrice, category_id);
						}
					}
					else {
						cout << "No item found in this name!" << endl;
					}
				}
				else {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "Invalid input. Please enter an integer." << std::endl;
				}
			}
			else if (db.res->rowsCount() == 1) {
				db.prepareStatement("SELECT * FROM item WHERE item_name=?");
				db.stmt->setString(1, itemNameFind);

				db.QueryResult();

				if (db.res->rowsCount() > 0) {
					while (db.res->next()) {
						itemID = db.res->getInt("item_id");
						itemName = db.res->getString("item_name");
						itemPrice = db.res->getDouble("item_price");
						category_id = db.res->getInt("category_id");
						update_new_item(user, itemID, itemName, itemPrice, category_id);
					}
				}
				else {
					cout << "No item found!" << endl;
					_getch();
				}
			}
			else {
				cout << "No item found!" << endl;
			}

			_getch();
			break;
		case 3:
			category1 = Category::findCategory();
			cout << "\nInsert Category ID: ";
			cin >> categoryID;
			db.prepareStatement("SELECT category_name FROM category WHERE category_id=?");
			db.stmt->setInt(1, categoryID);

			db.QueryResult();

			if (db.res->rowsCount() > 0) {
				while (db.res->next()) {
					category = db.res->getString("category_name");
					cout << "\nYou choose " << category;
					cout << "\nList of all item in " << category << " category\n";

					db.prepareStatement("SELECT * FROM item WHERE category_id=?");
					db.stmt->setInt(1, categoryID);


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
						cout << "\nEnter item ID = ";
						cin >> itemID;

						if (!cin.fail()) {
							db.prepareStatement("SELECT * FROM item WHERE item_id=? AND category_id=?");
							db.stmt->setInt(1, itemID);
							db.stmt->setInt(2, categoryID);


							db.QueryResult();

							if (db.res->rowsCount() > 0) {
								while (db.res->next()) {
									itemName = db.res->getString("item_name");
									itemPrice = db.res->getDouble("item_price");
									category_id = db.res->getInt("category_id");
									update_new_item(user, itemID, itemName, itemPrice, category_id);
								}
							}
							else {
								cout << "This Item ID unavailable in this category!" << endl;
							}
						}
						else {
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							std::cout << "Invalid input. Please enter an integer." << std::endl;
						}
					}
				}
			}
			else {
				cout << "Invalid Category ID!" << endl;
			}

			_getch();
			break;
		case 4:
			return;
			break;
		default:
			break;
		}
	}
}













/*

---------------------------------------------------------------------------------------------------------------------------------------
	UPDATE ITEM SECTION
---------------------------------------------------------------------------------------------------------------------------------------

*/
void update_new_item(Account user, int itemID, string itemName, double itemPrice, int category_id) {
	vector<Category> categoryitem;
	//Account temp = user;
	Item newitem;
	Item newItem = newitem;
	Account temp = user; // copy the object

	Category category1;
	DBConnection db;
	int item_ID;
	string item_name, item_category, category_name;
	double item_price = itemPrice;

	newitem.itemId = itemID;
	newitem.itemName = itemName;
	newitem.itemPrice = itemPrice;
	newitem.categoryId = category_id;
	string item_price1;
	item_price1 = to_string(newitem.itemPrice);

	Menu homeMenu;

	homeMenu.addOption("Item ID");
	homeMenu.addOption("Item Name");
	homeMenu.addOption("Item Price");
	homeMenu.addOption("Item Category");
	homeMenu.addOption("Reset");
	homeMenu.addOption("Save");
	homeMenu.addOption("Back");

	homeMenu.setValue(0, to_string(newitem.itemId));
	homeMenu.setValue(1, newitem.itemName);
	homeMenu.setValue(2, to_string(newitem.itemPrice));
	homeMenu.setValue(3, to_string(newitem.categoryId));
	while (1) {
		homeMenu.header = "----------------------\n" + user.shopname + "\nRecord New Item\n----------------------\nChoose action and input new data";
		switch (homeMenu.prompt())
		{
		case 1:
			cout << "Item ID is : " << newitem.itemId;
			cout << "\nYou cannot change Item ID!";
			_getch();
			break;
		case 2:
			cout << "Insert Item Name: ";
			std::cin.clear();
			getline(cin, newitem.itemName);
			homeMenu.setValue(1, newitem.itemName);
			break;
		case 3:
			cout << "Insert Item Price: ";
			cin >> newitem.itemPrice;
			item_price1 = to_string(newitem.itemPrice);

			cout << fixed << showpoint;
			cout << setprecision(2);

			homeMenu.setValue(2, to_string(newitem.itemPrice));
			break;
		case 4:
			categoryitem = Category::findCategory();
			cout << "Choose Category ID: ";
			cin >> category_id;
			db.prepareStatement("SELECT category_name FROM category WHERE category_id=?");
			db.stmt->setInt(1, category_id);


			db.QueryResult();

			if (db.res->rowsCount() > 0) {
				while (db.res->next()) {
					category_name = db.res->getString("category_name");
					cout << "You choose " << category_name;
				}
			}
			else {
				cout << "No item found!" << endl;
			}

			newitem.categoryId = category_id;
			homeMenu.setValue(3, to_string(newitem.categoryId));
			_getch();
			break;
		case 5:
			homeMenu.setValue(1, itemName);
			homeMenu.setValue(2, to_string(itemPrice));
			homeMenu.setValue(3, to_string(category_id));
			break;
		case 6:
			newItem = newitem;
			newItem.update_item();
			cout << "Item Successfully Saved";
			_getch();
			new_item(user);

			break;
		case 7:
			return;
			break;
		default:
			break;
		}
	}
}














/*

---------------------------------------------------------------------------------------------------------------------------------------
	CREATE NEW ITEM
---------------------------------------------------------------------------------------------------------------------------------------

*/
void create_new_item(Account user, string category_name) {

	vector<Category> category;
	Account temp = user;
	Item newitem;
	Category category1;
	DBConnection db;
	int category_id;
	string CategoryName;
	double item_price;
	Menu homeMenu;
	homeMenu.addOption("Insert Item Name");
	homeMenu.addOption("Insert Item Price");
	homeMenu.addOption("Choose Item Category");
	homeMenu.addOption("Save");
	homeMenu.addOption("Back");
	while (1) {
		homeMenu.header = "----------------------\n" + user.shopname + "\nRecord New Item\n----------------------\nChoose action and input new data";
		switch (homeMenu.prompt())
		{
		case 1:
			cout << "Item Name should not more than 25 characters";
			cout << "\nInsert Item Name: ";
			std::cin.clear();
			getline(cin, newitem.itemName);

			if ((newitem.itemName).length() > 25) {
				cout << "\nItem Name must less than 26 characters!";
				cout << "\nTotal characters = " + to_string((newitem.itemName).length());
				cout << "\nPlease type back!";
				_getch();
				homeMenu.setValue(0, "");
			}
			else if ((newitem.itemName).length() <= 25) {
				cout << "\nYou type = " +newitem.itemName;
				cout << "\nTotal characters = " + to_string((newitem.itemName).length());
				_getch();
				homeMenu.setValue(0, newitem.itemName);
			}
			break;
		case 2:
			cout << "Insert Item Price: ";
			cin >> newitem.itemPrice;

			cout << fixed << showpoint;
			cout << setprecision(2);

			homeMenu.setValue(1, to_string(newitem.itemPrice));
			break;
		case 3:
			category = Category::findCategory();
			cout << "\nInsert Category ID: ";
			cin >> category_id;
			db.prepareStatement("SELECT category_name FROM category WHERE category_id=?");
			db.stmt->setInt(1, category_id);


			db.QueryResult();

			if (db.res->rowsCount() > 0) {
				while (db.res->next()) {
					category_name = db.res->getString("category_name");
					cout << "You choose " << category_name;
					newitem.categoryId = category_id;
					homeMenu.setValue(2, to_string(newitem.categoryId));
				}
			}
			else {
				cout << "No category found!" << endl;
			}


			_getch();
			break;
		case 4:
			newitem.insert_item();
			cout << "Item Successfully Saved";
			_getch();
			new_item(user);
			break;
		case 5:
			return;
			break;
		default:
			break;
		}
	}
}












/*

---------------------------------------------------------------------------------------------------------------------------------------
	DELETE ITEM SECTION
---------------------------------------------------------------------------------------------------------------------------------------

*/
void delete_item(Account user) {

	vector<Category> categoryitem;
	vector<Category> category1;
	Account temp = user;
	Item item;
	Item temp1 = item;
	string itemName, category, item_name, delete_decision;
	int itemId, itemIdDelete, category_id;
	vector<Item> items, items2;
	DBConnection db;


	Menu itemMenu;
	itemMenu.addOption("List out all item");
	itemMenu.addOption("List by Category");
	itemMenu.addOption("Back");
	while (1) {
		itemMenu.header = "----------------------\n" + user.shopname + "\nDelete Item\n----------------------\nChoose action\n";
		switch (itemMenu.prompt())
		{
		case 1:
			items = Item::findItem();

			cout << "\nInsert Item ID to Delete = ";
			cin >> itemIdDelete;

			db.prepareStatement("SELECT * FROM item WHERE item_id=?");
			db.stmt->setInt(1, itemIdDelete);


			db.QueryResult();

			if (db.res->rowsCount() > 0) {
				while (db.res->next()) {
					item_name = db.res->getString("item_name");

					items = Item::findItembyId(itemIdDelete);

					cout << "\nDelete this item? (y/n) = ";
					char confirm;
					confirm = _getch();
					if (confirm == 'Y' || confirm == 'y') {
						item = temp1;
						cout << "\nItem ID " << itemIdDelete << " = " << item_name << " successfully deleted!";
						item.remove_item(itemIdDelete);
					}
				}
			}
			else {
				cout << "No item found!" << endl;
			}


			_getch();
			break;

		case 2:
			categoryitem = Category::findCategory();
			cout << "\nInsert Category ID to show: ";
			cin >> category_id;

			db.prepareStatement("SELECT * FROM category WHERE category_id=?");
			db.stmt->setInt(1, category_id);

			db.QueryResult();

			if (db.res->rowsCount() > 0) {
				cout << "\nCATEGORY ID\t|CATEGORY NAME\t\t|CATEGORY DESC\t\t\t\t|" << endl;
				cout << "---------------------------------------------------------------------------------" << endl;
				while (db.res->next()) {
					Category tmpCategory(db.res);
					category1.push_back(tmpCategory);

					cout << "" << db.res->getInt("category_id") << "\t\t|" << db.res->getString("category_name") << "      \t\t|" << db.res->getString("category_desc") << "      \t\t\t|" << endl;
					cout << fixed << showpoint;
					cout << setprecision(2);

					cout << "\nList of item available in this category = \n";

					category_id = db.res->getInt("category_id");

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
						cout << "\nEnter item ID = ";
						cin >> itemId;

						if (!cin.fail()) {
							db.prepareStatement("SELECT * FROM item WHERE item_id=? AND category=?");
							db.stmt->setInt(1, itemId);
							db.stmt->setString(2, category);


							db.QueryResult();

							if (db.res->rowsCount() > 0) {
								while (db.res->next()) {


									items2 = Item::findItembyId(itemId);

									cout << "\nDelete this item? (y/n) = ";
									char confirm;
									confirm = _getch();
									if (confirm == 'Y' || confirm == 'y') {
										item = temp1;
										db.prepareStatement("DELETE FROM item WHERE item_id=?");
										db.stmt->setInt(1, itemId);

										db.QueryResult();

										cout << "\nItem ID " << itemId << " successfully deleted!";

									}

									db.prepareStatement("DELETE FROM item WHERE item_id=?");
									db.stmt->setInt(1, itemId);

								}
							}
							else {
								cout << "This Item ID unavailable in this category!" << endl;
							}
						}
						else {
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							std::cout << "Invalid input. Please enter an integer." << std::endl;
						}
					}



				}
			}
			else {
				cout << "Invalid Category ID!" << endl;
			}


			_getch();
			break;
		case 3:
			return;
			break;
		default:
			break;
		}
	}
}









/*

---------------------------------------------------------------------------------------------------------------------------------------
	ALL ITEM
---------------------------------------------------------------------------------------------------------------------------------------

*/
void all_item(Account user) {

	Account temp = user;
	string itemName, category, category_name;
	int itemId, categoryId;
	vector<Item> items;
	vector<Category> categoryFind;
	DBConnection db;

	Menu itemMenu;
	itemMenu.addOption("List out all item");
	itemMenu.addOption("Choose Item by Category");
	itemMenu.addOption("Choose Item by ID");
	itemMenu.addOption("Choose Item by Name");
	itemMenu.addOption("Back");
	while (1) {
		itemMenu.header = "----------------------\n" + user.shopname + "\nAll Item List\n----------------------\nChoose action\n";
		switch (itemMenu.prompt())
		{
		case 1:
			items = Item::findItem();
			_getch();
			break;

		case 2:
			categoryFind = Category::findCategory();
			cout << "\nInsert Category ID: ";
			cin >> categoryId;

			if (!cin.fail()) {
				db.prepareStatement("SELECT category_name FROM category WHERE category_id=?");
				db.stmt->setInt(1, categoryId);


				db.QueryResult();

				if (db.res->rowsCount() > 0) {
					while (db.res->next()) {
						category_name = db.res->getString("category_name");
						cout << "You choose " << category_name << "\n";

						category = category_name;

						items = Item::findItembyCategory(categoryId);
					}
				}
				else {
					cout << "No item found!" << endl;
				}
			}
			else {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid input. Please enter an integer." << std::endl;
			}

			_getch();
			break;
		case 3:
			cout << "Insert Item Id to Select: ";
			cin >> itemId;
			items = Item::findItembyId(itemId);
			_getch();
			break;
		case 4:
			cout << "Insert Item Name to Show: ";

			std::cin.clear();
			getline(cin, itemName);
			items = Item::findItembyName(itemName);
			_getch();
			break;
		case 5:
			return;
			break;
		default:
			break;
		}
	}
}









/*

---------------------------------------------------------------------------------------------------------------------------------------
	ALL CATEGORY
---------------------------------------------------------------------------------------------------------------------------------------

*/
void all_category(Account user) {

	Account temp = user;
	vector<Category> category;
	int category_id;
	DBConnection db;
	Category category1;
	string category_name, category_desc;

	Menu categoryMenu;
	categoryMenu.addOption("List All Category");
	categoryMenu.addOption("Add New Category");
	categoryMenu.addOption("Edit Category");
	categoryMenu.addOption("Delete Category");
	categoryMenu.addOption("Back");
	while (1) {
		categoryMenu.header = "----------------------\n" + user.shopname + "\nCategory Section\n----------------------\nChoose action";
		switch (categoryMenu.prompt())
		{
		case 1:
			category = Category::findCategory();
			_getch();
			break;
		case 2:
			add_category(user);
			break;
		case 3:
			category = Category::findCategory();

			cout << "\nChoose category ID to edit = ";
			cin >> category_id;

			db.prepareStatement("SELECT * FROM category WHERE category_id=?");
			db.stmt->setInt(1, category_id);

			db.QueryResult();


			if (db.res->rowsCount() > 0) {
				while (db.res->next()) {
					category_name = db.res->getString("category_name");
					category_desc = db.res->getString("category_desc");
					edit_category(user, category_id, category_name, category_desc);
				}
			}
			else {
				cout << "Category ID not available!" << endl;
			}

			_getch();
			break;
		case 4:
			return;
			break;
		case 5:
			return;
			break;
		default:
			break;
		}
	}
}









/*

---------------------------------------------------------------------------------------------------------------------------------------
	ADD NEW CATEGORY
---------------------------------------------------------------------------------------------------------------------------------------

*/
void add_category(Account user) {

	Account temp = user;
	Category newcategory;

	Menu categoryMenu;
	categoryMenu.addOption("Category Name");
	categoryMenu.addOption("Category Description");
	categoryMenu.addOption("Save");
	categoryMenu.addOption("Back");
	while (1) {
		categoryMenu.header = "----------------------\n" + user.shopname + "\nAdd New Category\n----------------------\nChoose action and input details";
		switch (categoryMenu.prompt())
		{
		case 1:
			cout << "Insert Category Name: ";
			std::cin.clear();
			//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, newcategory.categoryName);
			categoryMenu.setValue(0, newcategory.categoryName);
			break;
		case 2:
			cout << "Insert Category Description: ";
			std::cin.clear();
			getline(cin, newcategory.categoryDesc);
			categoryMenu.setValue(1, newcategory.categoryDesc);
			break;

			
		case 3:
			newcategory.insert_category();
			cout << "Category Successfully Saved";
			_getch();
		case 4:
			return;
			break;
		default:
			break;
		}
	}
}








/*

---------------------------------------------------------------------------------------------------------------------------------------
	EDIT CURRENT CATEGORY
---------------------------------------------------------------------------------------------------------------------------------------

*/
void edit_category(Account user, int category_id, string category_name, string category_desc) {

	Account temp = user;
	Category newcategory;
	newcategory.categoryId = category_id;
	newcategory.categoryName = category_name;
	newcategory.categoryDesc = category_desc;

	Menu categoryMenu;
	categoryMenu.addOption("Category ID");
	categoryMenu.addOption("Category Name");
	categoryMenu.addOption("Category Description");
	categoryMenu.addOption("Reset");
	categoryMenu.addOption("Save");
	categoryMenu.addOption("Back");


	categoryMenu.setValue(0, to_string(category_id));
	categoryMenu.setValue(1, category_name);
	categoryMenu.setValue(2, category_desc);
	while (1) {
		categoryMenu.header = "----------------------\n" + user.shopname + "\nAdd New Category\n----------------------\nChoose action and input details";
		switch (categoryMenu.prompt())
		{
		case 1:
			cout << "Category ID cannot be changed!";
			_getch();
			break;
		case 2:
			cout << "Insert new Category Name = \n";
			cin >> newcategory.categoryName;

			categoryMenu.setValue(1, newcategory.categoryName);

			break;
		case 3:
			cout << "Insert new Category Description = \n";

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, newcategory.categoryDesc);
			categoryMenu.setValue(2, newcategory.categoryDesc);

			break;
		case 4:
			categoryMenu.setValue(1, category_name);
			categoryMenu.setValue(2, category_desc);
			break;
		case 5:
			newcategory.update_category();
			cout << "\nCategory Successfully Saved";
			_getch();

			all_category(user);
			break;
		case 6:
			return;
			break;
		default:
			break;
		}
	}
}















/*

---------------------------------------------------------------------------------------------------------------------------------------
	MENU
---------------------------------------------------------------------------------------------------------------------------------------

*/
bool isNumeric(string input) {
	for (int i = 0; i < input.length(); i++) {
		// loop through the string and if the character at index is not digit return false
		if (!isdigit(input.at(i))) {
			return false;
		}
	}
	// if loop finishes means all is digit so return true
	return true;
}

