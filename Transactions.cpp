#include <stdlib.h>
#include <iostream>
#include <string>
#include "Transactions.h"
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/exception.h>
#include <cppconn\prepared_statement.h>
using namespace std;

int main() {

	int num = 0;
	cout << "CHOOSE YOUR SELECTION\n\n\n";
	cout << "1.	Add Transaction.\n";
	cout << "2.	List all transactions.\n";
	cout << "3.	Delete a record.\n";
	cout << "4.	Exit.\n";
	do {
		cin >> num;

		switch(num) 
		{
		case 1:{
			system("CLS");
			addTrans t;
			t.addRec();
			}
		case 2: {		
			system("CLS");
			listTrans l;
			l.list();
			}
		case 3: {
			system("CLS");
			delRec d;
			d.del();
		}
		case 4:{
			system("EXIT");
			}
		}
	} while (num < 1 || num > 4);
}