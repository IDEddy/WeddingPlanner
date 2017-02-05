#ifndef ICT_GOOD_H__
#define ICT_GOOD_H__
#include "ReadWritable.h"
#include "wpgeneral.h"
#include <iostream>

namespace ict {
	class Good : public ReadWritable{
		/*barcode*/
		char sku_[MAX_SKU_LEN + 1];
		char* name_;
		/*price of good*/
		double price_;

		bool taxed_;
		
		
		/*current quantity of the item*/
		int quantity_;
		
		
		/*Quantity needed to purchase*/
		int qtyNeeded_;

	public:
	
		Good();
		Good(const char* sku,const  char* name, int price, int qtyNeeded, bool taxed = true);
		Good(const Good&);
		Good& operator=(const Good&);
		virtual ~Good();

		void sku(const char* sku);
		void price(double price);
		void name(const char* name);
		void taxed(bool taxed);
		void quantity(int quantity);
		void qtyNeeded(int qtyNeeded);

		const char* sku() const ;
		double price()const ;
		char* name() const;
		bool taxed() const;
		int quantity() const;
		int qtyNeeded() const;

		double cost() const;

		bool operator==(const char*);
		int operator+=(int qtyInput);


	};

	double operator+=(double &lhs, const Good& good);

	std::istream& operator>>(std::istream& is, Good& g);
	std::ostream& operator<<(std::ostream& os, const Good& g);
}
#endif
