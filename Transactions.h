#include <stdlib.h>
#include <iostream>
#include <string>
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/exception.h>
#include <cppconn\prepared_statement.h>
using namespace std;

class listTrans 
{
public:
	void list() {
		// List all transaction in the file
		try {
			sql::Driver *driver;
			sql::Connection *con;
			sql::Statement* stmt;
			sql::ResultSet* res;

			//res = stmt->executeQuery("SELECT * FROM arrestrecords");
			driver = get_driver_instance();
			con = driver->connect("tcp://192.168.0.12:3306", "testusername", "testpassword");
			con->setSchema("transactions");

			stmt = con->createStatement();
			res = stmt->executeQuery("SELECT * FROM records"); //can also use "SELECT * FROM arrestrecords WHERE id=65" to get all fields in that record // WHERE id=65

			while (res->next()) { //Loop through all records and output their fields
				cout << "ID: " << res->getInt("id") << ", " << "Date: " << res->getInt("date") << ", " << "Store: " << res->getString("storename")
					<< ", " << "City: " << res->getString("city") << ", " << "State: " << res->getString("state") << ", " << "Payment Type: " << res->getString("paymenttype") << ", "
					<< "Card Used: " << res->getString("card") << ", " << "Number of Items Purchased: " << res->getInt("itemno") << ", " << "Prices without Taxes: " << res->getDouble("notaxes") << ", " << "Prices with Tax Included: " << res->getDouble("taxes") << endl;
			}
			delete stmt;
			delete res;
		}
		catch (sql::SQLException &e) {
			cout << "Error listing transactions from database." << endl;
		}

		system("pause");
	}
};

class addTrans
{		
public:	
	// Pointer initializing for a int and some strings
		int *repick = new int;
		int *date = new int;
		string *storeName = new string;
		string *city = new string;
		string *state = new string;
		string *paymentType = new string;
		string *card = new string;
		int *itemNo = new int;
		double *noTaxes = new double;
		double *taxes = new double;

		//Create a function call addRec		(aka addRecord)
	void addRec() {
		// Connect to the database.
		try {
			sql::Driver *driver;
			sql::Connection *con;
			sql::PreparedStatement *pstmt;

			// Connect to the mysql database
			driver = get_driver_instance();		
			con = driver->connect("tcp://192.168.0.12:3306", "testusername", "testpassword");
			con->setSchema("transactions");

			// Prompt for user to enter data
			cout << "What date is this purchase on? (MMDDYYYY)\n";
			cin >> *date;
			cin.ignore();

			cout << "What store was this purchase from?\n";
			getline(cin, *storeName);

			cout << "What city was the purchase in?\n";
			getline(cin, *city);

			cout << "What state was the purchase in?\n";
			getline(cin, *state);

			cout << "What payment type did you use?\n";
			getline(cin, *paymentType);

			cout << "What card did you use?\n";
			getline(cin, *card);
			cin.sync();
			
			cout << "How many items did you purchase?\n";
			cin >> *itemNo;

			cout << "What was the prices before taxes?\n";
			cin >> *noTaxes;

			cout << "What was the amount you paid in taxes?\n";
			cin >> *taxes;

			delete repick;
			// Run this SQL Query
			pstmt = con->prepareStatement("INSERT INTO records (date, storename, city, state, paymenttype, card, itemno, notaxes, taxes) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
			// Replace the ? marks with these values
			pstmt->setInt(1, *date);
			pstmt->setString(2, *storeName);
			pstmt->setString(3, *city);
			pstmt->setString(4, *state);
			pstmt->setString(5, *paymentType);
			pstmt->setString(6, *card);
			pstmt->setInt(7, *itemNo);
			pstmt->setDouble(8, *noTaxes);
			pstmt->setDouble(9, *taxes);
			pstmt->executeUpdate();


			delete con;
			delete pstmt;
			delete date;
			delete storeName;
			delete city;
			delete state;
			delete card;
			delete paymentType;
			delete itemNo;
			delete noTaxes;
			delete taxes;
		}

		catch (sql::SQLException &e) {
			cout << "Error running query." << endl;
		}

		// Enter database code here

		//Prompt user for a new action
		cout << "RECORD ENTERED\n";
		cout << "1.	Add another record.\n";
		cout << "2.	List all transactions.\n";
		cout << "3.	Exit.";
		
		do { //Keep repeating this until the user picks a number from 1-3
			repick = new int;  //Create new instance of the pointer repick and set it as a new int
			cin >> *repick; //Prompt user to enter a value for the pointer repick
			switch (*repick) {
			case 1:
				system("CLS"); //Clear the screen
				delete repick;
				addRec(); //Call the function
			case 2:
				system("CLS"); //Clear the screen
				delete repick;
				listTrans l;  //Create a new instance of the listTrans class as "l"
				l.list(); //Call the function list from the listTrans class
			case 3:
				system("EXIT");  //Close the application			
			}
		} while (*repick < 1 || *repick > 3); //Repeat the do function if repick is less than 1 or more than 3
	}
};

class delRec{

public: 
	void del(){
	try {
		sql::Driver *driver;
		sql::Connection *con;
		sql::Statement* stmt;
		sql::ResultSet* res;
		sql::PreparedStatement* pstmt;

		//res = stmt->executeQuery("SELECT * FROM arrestrecords");
		driver = get_driver_instance();
		con = driver->connect("tcp://192.168.0.12:3306", "testusername", "testpassword");
		con->setSchema("transactions");
	// Calls the listTrans class and call the function list.
	listTrans l;
	l.list();

	int erase = 0;
	cout << "Enter the Id of the record you want to delete.";
	cin >> erase;

	pstmt = con->prepareStatement("DELETE FROM records WHERE id=?");
	pstmt->setInt(1, erase);
	pstmt->executeUpdate();

	delete pstmt;
	delete con;

	}
	catch (sql::SQLException &e) {
		cout << "Error while delete record";
	}
	system("pause");
	}
};