#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iomanip>

#include "WPlanner.h"
#include "Good.h"
#include "OnShelf.h"
#include "CustomMade.h"
#include "ReadWritable.h"

using std::cin;
using std::cout;
using namespace std;
namespace ict {

	/*WPlanner constructor*/
	WPlanner::WPlanner(const char* filename) {
		
		strcpy(filename_, filename);
		
		for( int i = 0 ; i < 30 ; i++){
		items_[i] = nullptr;
		}
		noOfItems_ = 0;
		loadRecs();

	}

	
	/*copy and assignment prevention*/

	void WPlanner::saveRecs() {
		/*open file for writing*/
			
		datafile_.open(filename_, std::ios::out);

		/*loops through item array*/
		for (int i = 0; i < noOfItems_; i++) {
			
			items_[i]->store(datafile_);
		}
		datafile_.close();

	}

/*Load all the records from WPlanner.txt which is the filename_*/
	void WPlanner::loadRecs() {
		int readIndex = 0;
		char idChar;
		
		datafile_.open(filename_, ios::in);
				
		if (datafile_.fail()) {
			datafile_.clear();
			datafile_.close();
			datafile_.open(filename_, std::ios::out);
			datafile_.close();
		}

		else {
			while (!datafile_.fail()) {
				delete items_[readIndex];
				datafile_ >> idChar;

				if (idChar == 'C') {
					
					items_[readIndex] = new CustomMade();

			
				}
				if (idChar == 'O') {
				
					items_[readIndex] = new OnShelf();
				}
					datafile_.ignore();
					items_[readIndex]->load(datafile_);
					noOfItems_ = readIndex;
					readIndex++;
				
			}
			
			datafile_.close();
		}
		
	}
	/*Ask user for input for SKU*/
	void WPlanner::getSku(char* sku) {

		cout <<"Please enter the SKU: ";
		std::cin.getline( sku,MAX_SKU_LEN + 1);
		if (cin.fail()) {

			cin.clear();
			cout << flush;
		}


	}
/*Searches for the desired object then deletes it. Shifts array*/
	void WPlanner::deleteItem() {

		char tempSku[400];

		bool exitLoop = false;
		char getInput = '\0';

		getSku(tempSku);

		while (exitLoop == false) {
			
			if (SearchItems(tempSku) != -1) {
				int temp = SearchItems(tempSku);
				cout << endl <<"The following Item will be deleted:" << endl;
				items_[temp]->display(cout, false) << endl << endl;

				cout << "Type (Y) to confirm or (N) to abort: ";
				cin >> getInput;

				if (getInput == 'y' || getInput == 'Y') {
					delete items_[temp];
					int j = temp;
					for ( j = temp; j < noOfItems_; j++) {
						
						items_[j] = items_[j + 1];
					}
					items_[j - 1] = 0;
					noOfItems_--;
					saveRecs();
					cout << endl <<"Item deleted!" << endl << endl;
					exitLoop = true;
				}
				else {
					cout << endl  << "Aborted!" << endl <<endl;
					exitLoop = true;
				}


			}
			else {
				cout << endl << "Item Not found!" << endl << endl;
			exitLoop = true;	
			}
			
					
		}
		
	}

	/*Searches for desired sku to Object and ask user for input to update record*/
	void WPlanner::updateQty() {
		
		char theSku[200];
		int numGoods;
		bool exitLoop = false;
		
		getSku(theSku);
				
		while(exitLoop == false){
		
			if (SearchItems(theSku) != -1 ) {
				int tempItem = SearchItems(theSku);
				cout << endl;
				items_[tempItem]->display(cout, false);
				cout << endl;
				cout << "\nPlease enter the number of purchased goods: ";
				cin >> numGoods;
				
				if (cin.fail()) {
					cout << "Invalid Quantity value!" << endl;
					exitLoop = true;
				}
				else {
					if (numGoods <= items_[tempItem]->qtyNeeded()) {
						*items_[tempItem] += numGoods;
						

						cout << endl <<"Updated!" << endl << endl;
						cout.flush();
						exitLoop = true;

					}
					else {

						cout << "Too many purcahsed,only " << items_[tempItem]->qtyNeeded() <<
							" Needed,please return the extra " << numGoods - items_[tempItem]->qtyNeeded() << endl;
						cout.flush();

					}

				}

			}else {

				cout << endl << "Item Not Found" << endl;
				exitLoop = true;
			}

			
		}
			
	
		



	}
/*List all the records*/
	void WPlanner::listItems()const {
		double totalcost = 0;
		
		cout << " Row | SKU | Good Name          | Cost  |Tax| QTY|Need| Delivery" << endl
			<< "-----|-----|--------------------|-------|---|----|----|----------" << endl;

		for (int i = 0; i < noOfItems_; i++) {
			cout  << setw(4) << right << i + 1 << " | ";
			items_[i]->display(cout, true) << endl;
			totalcost += items_[i]->cost() * items_[i]->quantity();
	

		}
		

		cout << "-----+-----+--------------------+-------+---+----+----+----------" << endl;
		cout << "Total cost of the Wedding: $" << setprecision(2) << totalcost << endl;

		cout << endl;
	
	}

/*SeachItems searches for desired items by using == operator overload from the pointer of items[i] and the sku from the paramter*/
int WPlanner::SearchItems(const char* sku)const {
				
		int index = -1, i = 0;
		bool b = false;

		while(b == false && i < noOfItems_){
		if(*items_[i]==sku){
		index = i;
	        
		b = true;
		}else{
		index = -1;
		}
		
		i++;
		}

		return index;
	}


/*first checks if it's customMade. Then creates the object and assign in to the array of object and saves the record. New object will display in non linear format for the user and outputs Good added.Item not found otherwise*/
	void WPlanner::addItem(bool isCustomMade) {
		int temp = noOfItems_;

		if (isCustomMade) {
			
			items_[temp] = new CustomMade();
			
			items_[temp]->conInput(cin);

			if (cin.fail()) {
			
			items_[noOfItems_]->display(cout, false);
			cout << endl;
			}
			else {
				noOfItems_++;
				saveRecs();
				cout << "\nGood added" << endl << endl;
			}



		}
		else {
			items_[temp] = new OnShelf();
			
			items_[temp]->conInput(cin);
			if (cin.fail()) {
				items_[noOfItems_]->display(cout, false);
				cout << endl;	

				
			}
			else {
				noOfItems_++;
				saveRecs();
				cout << "\nGood added" << endl << endl;
			}




		}
	

	}
/*menu returns the proper selection*/
	int WPlanner::menu() {
		int selection = -1;

		cout << "Wedding Planner Management Program" << endl;
		cout << "1 - List goods" << endl;
		cout << "2 - Add On Shelf Good" << endl;
		cout << "3 - Add Custom-Made Good" << endl;
		cout << "4 - Update Good quantity" << endl;
		cout << "5 - Delete" << endl;
		cout << "0 - Exit program" << endl;
		cout << "> ";
		cin >> selection;

		cout << endl;
		if (selection == 1) {
			selection = 1;
		}
		else if (selection == 2) {
			selection = 2;
		}
		else if (selection == 3) {
			selection = 3;
		}
		else if (selection == 4) {
			selection = 4;
		}
		else if (selection == 5) {
			selection = 5;
		}
		else if (selection == 0) {
			selection = 0;
		}
		else {
			selection = -1;
		}
		cin.clear();
		cin.ignore(2000, '\n');
		return selection;
	}
/*depending on values from menu() it runs the proper function()*/
	int WPlanner::run() {
		bool done = false;
		while (!done) {
			switch (menu()) {
			case 1:
				listItems();

				break;
			case 2:
				addItem(false);

				break;
			case 3:
				addItem(true);


				break;
			case 4:
				updateQty();


				break;
			case 5:
				deleteItem();

				break;
			case 0:
				done = true;
				cout << "Goodbye!!" << endl << endl;
				break;
			case -1:
				cout << "===Invalid Selection, try again.===" << endl << endl;
				
				break;
			}

		}
		return 0;
	} // WPlanner::run() end
}


/* outputs

Wedding Planner Management Program
1 - List goods
2 - Add On Shelf Good
3 - Add Custom-Made Good
4 - Update Good quantity
5 - Delete
0 - Exit program
>



Not found!

Please enter the number of purchased goods:

Too many purchased, only 5 needed, please return the extra 15.

Updated!

Not implemented!

*/
