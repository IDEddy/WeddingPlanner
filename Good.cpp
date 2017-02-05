
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include "Good.h"


using namespace std;


namespace ict {

	
	Good::Good() {
		name_ = nullptr;
		sku_[0] = '\0';
		quantity_ = 0;
		price_ = 0;
		qtyNeeded_ = 0;
		taxed_ = false;
			
	}


	Good::Good(const char* sku,const char * name, int price, int qtyNeeded, bool taxed) {

		int length = strlen(name) + 1;
	
		name_ = new char[length];
		strcpy(name_, name);
		strcpy(sku_, sku);
		quantity_ = 0;
		price_ = price;
		qtyNeeded_ = qtyNeeded;
		if (taxed == false) {
			taxed_ = true;
		}


	}
	Good::~Good() 
	{
		name_[0] = '\0';
		
	}


	Good::Good(const Good& src) {
		//shallow copies

		price_ = src.price_;
		taxed_ = src.taxed_;
		quantity_ = src.quantity_;
		qtyNeeded_ = src.qtyNeeded_;
		strcpy(sku_, src.sku_);

		if (src.name_[0] != '\0') {
			int length = strlen(src.name_) + 1;
			
			name_ = new char[length];

			for (int i = 0; i < length; i++) {
				name_[i] = src.name_[i];
				
			}
			
		}
		else {
			name_[0] = '\0';
		}
	}

	Good& Good::operator=(const Good& source) {
		//check for self-assignment
		if (this != &source) {
			//shallow copy
		
			price_ = source.price_;
			taxed_ = source.taxed_;
			quantity_ = source.quantity_;
			qtyNeeded_ = source.qtyNeeded_;
			strcpy(sku_, source.sku_);

			delete[] name_;

			if (source.name_[0] != '\0') {
				int length = strlen(source.name_) + 1;
				name_ = new char[length];
				for (int i = 0; i < length; i++) {
					name_[i] = source.name_[i];
				}
							
			}
			else {
				name_[0] = '\0';
			}
		}

		return *this;

	}

	void Good::sku(const char* sku) {
		strncpy(sku_, sku,MAX_SKU_LEN + 1);
		return;
	}
	void Good::price(double priceInput) {
		price_ = priceInput;
		return;
	}
	void Good::name(const char* name) {
		delete[] name_;
		name_ = new char[strlen(name) + 1];
		strcpy(name_, name);
	

	}
	void Good::taxed(bool taxed) {
		taxed_ = taxed;
		return;
	}
	void Good::quantity(int quantity) {
		quantity_ = quantity;
		return;
	}
	void Good::qtyNeeded(int qtyNeeded) {
		qtyNeeded_ = qtyNeeded;
		return;

	}
	const char*  Good::sku()const {
		return sku_;
	}
	double  Good::price() const{
		return price_;
	}
	char* Good::name() const{
		return name_;
	}
	bool Good::taxed() const{
		return taxed_;
	}
	int Good::quantity() const{
		return quantity_;
	}
	int Good::qtyNeeded() const{
		return qtyNeeded_;

	}

	double Good::cost() const{
		
		double theprice = 0;
		if (taxed()) {
			theprice = price_ * TAX + price_;
		}
		else {
			theprice = price_;
		}
	
		return theprice;

	}

	bool Good::operator==(const char* charPointer) {
		return strcmp(sku_, charPointer) == 0;
	}
	int Good::operator+=(int qtyInput) {

	return quantity_ += qtyInput;
	

	}

	double  operator+=(double &lhs, const Good& rhs) {
		return	 lhs += rhs.cost() * rhs.quantity();
		}


	std::istream& operator>>(std::istream& is, Good& g) {

		g.conInput(is);
		return is;
	}

	std::ostream& operator<<(std::ostream& os, const Good& g) {

		g.display(os, true);
		return os;

	}


}
