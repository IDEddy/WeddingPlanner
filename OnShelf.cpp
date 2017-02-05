#include "OnShelf.h"
#include <iostream>
#include <cstring>



using namespace std;

namespace ict {

	OnShelf::OnShelf(const char charInput) {

		recTag_ = charInput;

	}

	fstream& OnShelf::store(std::fstream& file, bool addNewLine)const {
	
		file << recTag_ << "," << sku() << "," << name() << "," << price() << "," << taxed() << "," << quantity() << "," << qtyNeeded();

			if (addNewLine) {

				file << endl;
		
				
			}
		

		return file;

	}
	fstream& OnShelf::load(fstream& file) {
	
		char buff[2000];
		int ibuff;
		double dbuff;
		
		file.getline(buff,2000,','); 
	
		sku(buff);
		
        file.getline(buff,2000,',');
		name(buff);					
		
		file >> dbuff;
		file.ignore(2000,',');
		price(dbuff);
	
		file >> ibuff;
		file.ignore(2000,',');
		taxed(!!ibuff);

		file >> ibuff;
		file.ignore(1,',');
		quantity(ibuff);

		file >> ibuff;
		file.ignore(1,',');
		qtyNeeded(ibuff);
		

		return file;

	}

	std::ostream& OnShelf::display(ostream& os, bool linear)const {
		char isTaxed;
		if(!err_.isClear()){	
			os << err_ ;
			
		}
		else  if(err_.isClear()){

			if (linear) {
				/*left justified in MAX_SKU_LEN characters*/
				if (taxed()) {
					isTaxed = 't';
					os <<  sku() << " |" << left << setw(20) << name() << "|" << right << fixed << setprecision(2) << setw(7) << cost() << "|" << setw(2) << isTaxed << setw(2) << "|" << setw(4) << right << quantity() << "|" << right << setw(4) << qtyNeeded() << "|";
				}
				else {
					isTaxed = ' ';
					os << left << sku() << " |" << setw(20) << name() << "|" << right << fixed << setprecision(2) << setw(7) << cost() << "|" << right << setw(3) << isTaxed << "|" << setw(4) << right << quantity() << "|" << right << setw(4) << qtyNeeded() << "|";
				}
			/*	else {
					os << endl;
				}
			*/	
			}
			else {

				os << "Sku: " << sku() << endl ;
			       os << "Name: " << name() << endl;
				os << "Price: " << price() <<endl;
				if (!taxed()) {
					os << "Price after tax: N/A" << endl;
				}
				else {
					os << "Price after tax: " << cost() << endl;
				}
				os << "Quantity On Hand: " << quantity() ;
				os << endl << "Quantity Needed: " << qtyNeeded();
				


			}


		}

		return os;
	}

istream& OnShelf::conInput(istream& istr) {
		char skuTemp[2000], nameTemp[20];
		char taxTemp;
		double priceTemp;
		int qty, qtyNeededTemp;
               
		bool isValid = true;


		std::cout << "Sku: ";
		istr >> skuTemp;

	
while(isValid){
		if (istr.fail()) {
			//return istr;
			isValid = false;
		}
		else {
			sku(skuTemp);

			std::cout << "Name: ";
			istr >> nameTemp;

			name(nameTemp);


			std::cout << "Price: ";
			istr >> priceTemp;

			if (istr.fail()) {
				
				err_.message("Invalid Price Entry");
				
			isValid = false;
				//return istr;
			}else{
			price(priceTemp);

			std::cout << "Taxed: ";
			istr >> taxTemp;
						
			if (taxTemp == 'y') {
			std::cout << flush;
				taxed(true);
			}
			else if (taxTemp == 'Y') {
				std::cout << flush;
				taxed(true);
			}
			else if (taxTemp == 'N') {
				std::cout << flush;
				taxed(false);
			}
			else if (taxTemp == 'n') {
				std::cout << flush;
				taxed(false);
			}
			else {
				istr.setstate(ios::failbit);
				err_.message("Only (Y)es or (N)o are acceptable");
				//return istr;
			isValid = false;
			}




			if (istr.fail()) {
				isValid = false;
			}
			else {

				std::cout << "Quantity On hand: " << flush;
				istr >> qty;

				if (istr.fail()) {
					err_.message("Invalid Quantity Entry");
					
			isValid = false;
					//return istr;
				}
				else {

					quantity(qty);

					std::cout << "Quantity Needed: ";
					istr >> qtyNeededTemp;

					if (istr.fail()) {
						err_.message("Invalid Quantity Needed Entry");
					//	return istr;

			isValid = false;
					}
					else {

						qtyNeeded(qtyNeededTemp);

						err_.clear();
					//	return istr;
			isValid = false;
					}
				}
			}	
		}
		}
}
		return istr;

	}
}
